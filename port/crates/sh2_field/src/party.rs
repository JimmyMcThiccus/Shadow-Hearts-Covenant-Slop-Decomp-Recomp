//! Party changes requested by the field scripts that need the battle databases (`SSHDAT` `PC_I` / `SCEN` tables through
//! `sh2_battle::data::BattleData`): `SetFieldData(0x13)` = `SceneInit(scene)` and `SetFieldData(0x20)` = `PCAddInit(pc)`.
//! The host queues them in `ScriptState::party_ops`; the field plugin (`apply_party_ops_system`) and the headless story walker apply them.

use bevy::prelude::*;
use sh2_battle::data::BattleData;
use sh2_menu::session::GameSession;

use crate::host::PartyOp;

/// Apply queued party changes to the session.  Returns a log line per change.
pub fn apply_party_ops(data: &BattleData, session: &mut GameSession, ops: Vec<PartyOp>) -> Vec<String> {
    let mut log = vec![];
    for op in ops {
        match op {
            PartyOp::PcAdd(pc) if (0..12).contains(&pc) => {
                let tbl = sh2_battle::bridge::level_table(data);
                let had = session.save.btl.pc(pc as usize).map(|r| r.present()).unwrap_or(false);
                sh2_battle::bridge::ensure_pc(data, session, pc as u8, &tbl);
                log.push(format!("PCAddInit({pc}){}", if had { " (record already present)" } else { "" }));
            }
            PartyOp::SceneInit(0) => {
                // `BtlSaveSec::SetSceneInit(0, ..)`: the new game (Karin + Nicolai, starting items)
                sh2_battle::bridge::init_new_game_retail(data, session, 0);
                log.push(format!("SceneInit(0) -> party {:?}", session.all_members()));
            }
            PartyOp::SceneInit(scene) if scene > 0 => {
                log.push(scene_init(data, session, scene as usize));
            }
            other => log.push(format!("{other:?}: ignored")),
        }
    }
    log
}

/// Bevy system: drain the runtime's party queue (needs `sh2_battle::plugin::BattleDb`).
pub fn apply_party_ops_system(rt: Option<ResMut<crate::plugin::FieldRuntime>>, db: Option<Res<sh2_battle::plugin::BattleDb>>, mut session: ResMut<GameSession>) {
    let Some(mut rt) = rt else { return };
    if rt.st.party_ops.is_empty() {
        return;
    }
    let ops = std::mem::take(&mut rt.st.party_ops);
    match db {
        Some(db) => {
            for l in apply_party_ops(&db.0, &mut session, ops) {
                log::info!("field: {l}");
            }
        }
        None => log::warn!("field: party changes {ops:?} need the battle data (not loaded)"),
    }
}

/// One case of the retail `BtlSaveSec::SetSceneInit(scene, ..)` (US 0x003bc710, 15 cases; read from the disassembly, see
/// `notes/integration/r5_fs.md`): the bag the scenario uses (`BTL0+2`), whether that bag is cleared first, the party records created
/// (`PCInit` / `PCAddInit`) and the `SCEN` row group applied (`RegDat 0x47`).  Cases 3, 4, 7, 9, 11..13 (party bits and bag merges) are
/// in `scene_init`; case 10 (0x003bdb08) partly (see there).
pub struct SceneCase {
    pub bag: Option<u8>,
    pub clear_bag: bool,
    pub pcs: &'static [u8],
    pub group: Option<usize>,
}

pub fn scene_case(scene: usize) -> Option<SceneCase> {
    Some(match scene {
        1 => SceneCase { bag: Some(0), clear_bag: false, pcs: &[0, 1, 2], group: Some(1) },
        2 => SceneCase { bag: Some(1), clear_bag: true, pcs: &[8], group: Some(2) },
        5 => SceneCase { bag: None, clear_bag: false, pcs: &[3], group: Some(3) },
        6 => SceneCase { bag: None, clear_bag: false, pcs: &[4], group: None },
        8 => SceneCase { bag: None, clear_bag: false, pcs: &[7], group: Some(4) },
        14 => SceneCase { bag: Some(2), clear_bag: true, pcs: &[9, 10], group: Some(5) },
        _ => return None,
    })
}

fn scene_init(data: &BattleData, session: &mut GameSession, scene: usize) -> String {
    use sh2_menu::save::BtlSave;
    match scene {
        // case 3 (US 0x003bd338): bag 0; records 0..7 that exist become "in the party", records 8.. leave it
        3 => {
            session.save.btl.data[BtlSave::OFF_BAG] = 0;
            for pc in 0..sh2_menu::save::PC_COUNT as u8 {
                let present = session.save.btl.pc(pc as usize).map(|r| r.present()).unwrap_or(false);
                if pc < 8 && present {
                    crate::host::set_pc_flag(session, pc, 2, true);
                } else if pc >= 8 {
                    crate::host::set_pc_flag(session, pc, 2, false);
                }
            }
            return "SceneInit(3): bag 0, records 0..7 in the party, 8.. out".into();
        }
        // case 4 (US 0x003bd428): Karin's record (5) back in the party; her equipment is counted into the bag (cap 99)
        4 => {
            crate::host::set_pc_flag(session, 5, 3, true);
            if let Some(r) = session.save.btl.pc(5) {
                let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
                let mut add = |base: usize, idx: i8| {
                    if idx >= 0 {
                        if let Some(c) = session.save.btl.data.get_mut(base + bag + idx as usize) {
                            *c = c.saturating_add(1).min(99);
                        }
                    }
                };
                add(BtlSave::OFF_WEAPONS, r.weapon);
                add(BtlSave::OFF_ARMOR, r.armor);
                for a in r.accessories {
                    add(BtlSave::OFF_ACCESSORIES, a);
                }
            }
            return "SceneInit(4): Karin rejoins with her equipment".into();
        }
        // cases 7 / 9 (US 0x003bda90 / 0x003be7e0): bag 0, the other bag merged in (7 also ORs the "seen" bits first,
        // 0x003bf8e0), every present record of 0..7 back in the party
        7 | 9 => {
            session.save.btl.data[BtlSave::OFF_BAG] = 0;
            if scene == 7 {
                merge_bag(session, true);
            }
            merge_bag(session, false);
            for pc in 0..8u8 {
                if pc_present(session, pc) {
                    crate::host::set_pc_flag(session, pc, 2, true);
                }
            }
            return format!("SceneInit({scene}): bag 0, the other bag merged in, records 0..7 in the party");
        }
        // case 10 (0x003bdb08): record 1's equipment is taken out of the current bag's counts, then bag 1 is cleared and becomes the
        // current one ("seen" bits merged), and every other record leaves the party (record 1 alone stays).  Not reproduced: the key-item
        // and skill-bit bookkeeping of record 1's +0x12e.. bytes and the call 0x003be870(1)
        10 => {
            if let Some(r) = session.save.btl.pc(1) {
                let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
                let mut take = |base: usize, idx: i8| {
                    if idx >= 0 {
                        if let Some(c) = session.save.btl.data.get_mut(base + bag + idx as usize) {
                            *c = c.saturating_sub(1);
                        }
                    }
                };
                take(BtlSave::OFF_WEAPONS, r.weapon);
                take(BtlSave::OFF_ARMOR, r.armor);
                for a in r.accessories {
                    take(BtlSave::OFF_ACCESSORIES, a);
                }
            }
            session.save.btl.data[BtlSave::OFF_BAG] = 1;
            let b1 = BtlSave::BAG_STRIDE;
            for base in [BtlSave::OFF_ITEMS, BtlSave::OFF_WEAPONS, BtlSave::OFF_ARMOR, BtlSave::OFF_ACCESSORIES] {
                let n = match base {
                    BtlSave::OFF_ITEMS => 0x40,
                    BtlSave::OFF_WEAPONS => 0x60,
                    BtlSave::OFF_ARMOR => 0x30,
                    _ => 0x50,
                };
                for k in 0..n {
                    if let Some(x) = session.save.btl.data.get_mut(base + b1 + k) {
                        *x = 0;
                    }
                }
            }
            merge_bag(session, true);
            for pc in 0..8u8 {
                if pc != 1 && pc_present(session, pc) {
                    crate::host::set_pc_flag(session, pc, 2, false);
                }
            }
            return "SceneInit(10): record 1 alone, bag 1 cleared and current".into();
        }
        // case 11 (0x003be250): the stash list (`BTL0+0x20bc` {id, count} pairs, 0x003bf5c0) goes into the other bag -- not reproduced
        // (the working copy has no stash list); record 1 back in the party
        11 => {
            crate::host::set_pc_flag(session, 1, 2, true);
            return "SceneInit(11): record 1 in the party (stash list not reproduced)".into();
        }
        // case 12 (0x003be278): bag 0, "seen" bits merged; present records 0..7 in the party except 1 and 7
        12 => {
            session.save.btl.data[BtlSave::OFF_BAG] = 0;
            merge_bag(session, true);
            for pc in 0..8u8 {
                if pc_present(session, pc) {
                    crate::host::set_pc_flag(session, pc, 2, pc != 1 && pc != 7);
                }
            }
            return "SceneInit(12): bag 0, records 0..7 in the party except 1 and 7".into();
        }
        // case 13 (0x003be320): the other bag merged in; records 1 and 7 in the party
        13 => {
            merge_bag(session, false);
            crate::host::set_pc_flag(session, 1, 2, true);
            crate::host::set_pc_flag(session, 7, 2, true);
            return "SceneInit(13): the other bag merged in, records 1 and 7 in the party".into();
        }
        _ => {}
    }
    let Some(c) = scene_case(scene) else { return format!("SceneInit({scene}): case not reproduced (flags only)") };
    if let Some(b) = c.bag {
        session.save.btl.data[BtlSave::OFF_BAG] = b;
    }
    let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
    if c.clear_bag {
        for base in [BtlSave::OFF_ITEMS, BtlSave::OFF_WEAPONS, BtlSave::OFF_ARMOR, BtlSave::OFF_ACCESSORIES] {
            let n = match base {
                BtlSave::OFF_ITEMS => 0x40,
                BtlSave::OFF_WEAPONS => 0x60,
                BtlSave::OFF_ARMOR => 0x30,
                _ => 0x50,
            };
            for k in 0..n {
                if let Some(x) = session.save.btl.data.get_mut(base + bag + k) {
                    *x = 0;
                }
            }
        }
    }
    let tbl = sh2_battle::bridge::level_table(data);
    for &pc in c.pcs {
        sh2_battle::bridge::ensure_pc(data, session, pc, &tbl);
        crate::host::set_pc_flag(session, pc, 3, true);
    }
    let mut rows = 0;
    if let Some(g) = c.group {
        for row in data.scene_init(g) {
            let (base, max) = match row.kind {
                1 => (BtlSave::OFF_ITEMS, 0x40),
                2 => (BtlSave::OFF_WEAPONS, 0x60),
                3 => (BtlSave::OFF_ARMOR, 0x30),
                4 => (BtlSave::OFF_ACCESSORIES, 0x50),
                5..=10 => {
                    session.save.btl.apply_scene_row(row.kind, row.index as usize, row.value);
                    rows += 1;
                    continue;
                }
                _ => continue,
            };
            if (row.index as usize) < max {
                if let Some(x) = session.save.btl.data.get_mut(base + bag + row.index as usize) {
                    *x = row.value;
                    rows += 1;
                }
            }
        }
    }
    format!("SceneInit({scene}): bag {}, records {:?}, {rows} SCEN rows", session.save.btl.bag(), c.pcs)
}

fn pc_present(session: &GameSession, pc: u8) -> bool {
    let o = sh2_menu::save::PC_REC_BASE + pc as usize * sh2_menu::save::PC_REC_SIZE;
    session.save.btl.data.get(o).map(|b| b & 1 != 0).unwrap_or(false)
}

/// `0x003bebe0` (`seen_only` = false) / `0x003bf8e0` (true): merge the other bag (bag 1 when the current one is 0, else bag 0) into the
/// current one -- item / weapon / armour / accessory counts added (cap 99; the same ranges case 10 clears), the "seen" and skill bits ORed.  On the
/// demo-shaped working copy (`BtlSave` constants; `BAG_MAP` translates to the retail block).
fn merge_bag(session: &mut GameSession, seen_only: bool) {
    use sh2_menu::save::BtlSave;
    let d = &mut session.save.btl.data;
    let cur = d[BtlSave::OFF_BAG] as usize;
    let other = if cur == 0 { 1 } else { 0 };
    let (c, o) = (cur * BtlSave::BAG_STRIDE, other * BtlSave::BAG_STRIDE);
    let or_ranges: &[(usize, usize)] = if seen_only { &[(BtlSave::OFF_ITEM_SEEN, 0x40)] } else { &[(BtlSave::OFF_ITEM_SEEN, 0x40), (BtlSave::OFF_SKILL_BITS, 0xa), (BtlSave::OFF_SKILL_BITS2, 0xa)] };
    for &(base, n) in or_ranges {
        for k in 0..n {
            let v = d.get(o + base + k).copied().unwrap_or(0);
            if let Some(x) = d.get_mut(c + base + k) {
                *x |= v;
            }
        }
    }
    if seen_only {
        return;
    }
    for (base, n) in [(BtlSave::OFF_ITEMS, 0x40), (BtlSave::OFF_WEAPONS, 0x60), (BtlSave::OFF_ARMOR, 0x30), (BtlSave::OFF_ACCESSORIES, 0x50)] {
        for k in 0..n {
            let v = d.get(o + base + k).copied().unwrap_or(0);
            if let Some(x) = d.get_mut(c + base + k) {
                *x = x.saturating_add(v).min(99);
            }
        }
    }
}
