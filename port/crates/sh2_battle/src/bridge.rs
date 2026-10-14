//! Glue between the persistent game state (`sh2_menu::session::GameSession`, i.e. `BtlSaveSec`) / the battle databases
//! ([`crate::data::BattleData`], i.e. `RegDatApi`) and the battle machine ([`crate::flow::Battle`]).
//!
//! * [`build_setup`]   — `CBattle::PCEntry` + `MonsterEntry`: fighters from the party's `PcRec`s and the `MONSETTbl`/`MONSTERParam` records.
//! * [`apply_victory`] / [`apply_end`] — `CBattle::MakeResultTrophy` write-back: HP/MP/SP, EXP + level-ups (`PCLevelSet`), cash, items.
//! * [`init_new_game`] — `BtlSaveSec::SetSceneInit`: the starting party from `PC_I` records (PCs 5, 0 and 1).
//!
//! PLACEHOLDERS (see `notes/integration/gameplay.md`): `MONSTERParam` EXP/cash are zero for most demo monsters; [`monster_rewards`]
//! substitutes small values derived from HP so a won battle visibly pays out.  Enemy AI (`BTLDATA/AIS`) is not ported: enemies attack a random
//! living party member.

use sh2_menu::btlsave::LevelTable;
use sh2_menu::save::{BtlSave, PC_COUNT};
use sh2_menu::session::{GameSession, RowTable};

use crate::data::{BattleData, MonSetTbl, SEC_PC_INIT};
use crate::flow::Fighter;
use crate::rules::{self, Ambush, DropSlot, Element, EscapeMode, TurnSlot};

/// What the plugin needs besides the fighters.
pub struct BattleSetup {
    pub fighters: Vec<Fighter>,
    /// display names (UTF-8, decoded from Shift-JIS)
    pub names: Vec<String>,
    /// per fighter: party id for PCs, `None` for monsters
    pub pc_ids: Vec<Option<u8>>,
    pub escape: EscapeMode,
    pub ambush: Ambush,
    /// `MonSetTbl::formation` (slot layout)
    pub formation: u16,
    /// monster-set index
    pub set: usize,
    /// `MONSTERParam` ids whose library bit a victory sets (retail battle-result list `BtlSocket+0x316`, minus the records with
    /// `MONSTERParam+0x14` bit 6)
    pub library_ids: Vec<u16>,
    /// `MONSETTbl` flags >> 2 (retail `CBattle+0x4866`, JP `bNoEvade`): 1 / 2 = the "Battle Basics" / "Combos" tutorial fights, 3 = an
    /// event fight without ambush, 4 = no enemy ambush, 5 = forced enemy ambush (see [`check_gambit`])
    pub battle_type: u8,
}

/// Accessory id whose wearer prevents enemy ambushes (`CheckGambit`: an equipped accessory `== 'I'` (73)).
pub const ACC_NO_AMBUSH: i8 = 73;

/// `CBattle::CheckGambit` (retail SH2US_BATTLE.BIN 0x4df640, integer form of JP 0x004bf000): who gets the first strike.
///
/// * battle type (`MONSETTbl` flags >> 2) 4: the enemies cannot ambush; 5: the enemies always ambush (chance 20000 / 10000) and the party never
///   strikes first; any other non-zero type: nobody (tutorials / event fights).  A unit with `bFlagsA` bit 4 also cancels it (not modelled).
/// * per side: `chance = 500 + 600 * avg(LUC) / 99 + rand() % 400` (in 1/10000), the side with the higher average AGL is rolled first
///   (`rand() % 10000 <= chance`), a side needs at least two members; an `ACC_NO_AMBUSH` accessory in the party blocks the enemy roll.
pub fn check_gambit(battle_type: u8, fighters: &[Fighter], anti_ambush: bool, rand: &mut dyn FnMut() -> u32) -> Ambush {
    let mut no_enemy = anti_ambush;
    let mut no_party = false;
    match battle_type {
        0 => {}
        4 => no_enemy = true,
        5 => no_party = true,
        _ => return Ambush::None,
    }
    let side = |enemy: bool| {
        let v: Vec<&Fighter> = fighters.iter().filter(|f| f.is_enemy == enemy).collect();
        let n = v.len() as i64;
        let agl: i64 = v.iter().map(|f| f.agl.max(0) as i64).sum();
        let luc: i64 = v.iter().map(|f| f.luc.max(0) as i64).sum();
        (n, agl, luc)
    };
    let (np, ap, lp) = side(false);
    let (ne, ae, le) = side(true);
    if np == 0 || ne == 0 {
        return Ambush::None;
    }
    let mut r = |m: u32| (rand() % m) as i64;
    let pc_chance = 500 + (lp * 600 / np) / 99 + r(400);
    let mut en_chance = 500 + (le * 600 / ne) / 99 + r(400);
    if battle_type == 5 {
        en_chance = 20000;
    }
    let pc_try = |r: &mut dyn FnMut(u32) -> i64| r(10000) <= pc_chance && np >= 2 && !no_party;
    let en_try = |r: &mut dyn FnMut(u32) -> i64| r(10000) <= en_chance && ne >= 2 && !no_enemy;
    if ap * 10000 / np >= ae * 10000 / ne {
        if pc_try(&mut r) {
            Ambush::PcFirst
        } else if en_try(&mut r) {
            Ambush::EnemyFirst
        } else {
            Ambush::None
        }
    } else if en_try(&mut r) {
        Ambush::EnemyFirst
    } else if pc_try(&mut r) {
        Ambush::PcFirst
    } else {
        Ambush::None
    }
}

/// `LevelTable` backed by SSHDAT `PC_L`.
pub fn level_table(data: &BattleData) -> RowTable {
    RowTable { rows: (0..PC_COUNT).map(|pc| data.pc_levels(pc)).collect() }
}

fn rec_name(data: &BattleData, sec: usize, idx: usize) -> String {
    data.mes.record(sec, idx, 18).map(sh2_menu::sjis::decode).unwrap_or_default()
}

/// `MONSTERParam` rewards with the demo-data fallback described in the module docs.
pub fn monster_rewards(hp: u16, exp: i32, cash: i32) -> (i32, i32) {
    if exp == 0 && cash == 0 {
        (((hp as i32) / 6).max(5), ((hp as i32) / 10).max(1))
    } else {
        (exp, cash)
    }
}

fn pc_fighter(data: &BattleData, session: &GameSession, id: u8) -> Option<(Fighter, String)> {
    let r = session.save.btl.pc(id as usize)?;
    if !r.present() {
        return None;
    }
    let wpn = (r.weapon >= 0).then(|| data.weapon(r.weapon as usize)).flatten();
    let arm = (r.armor >= 0).then(|| data.armor(r.armor as usize)).flatten();
    let accs: Vec<_> = r.accessories.iter().filter(|&&a| a >= 0).filter_map(|&a| data.accessory(a as usize)).collect();
    let patk = r.str_ as i32 + wpn.map(|w| w.patk as i32).unwrap_or(0) + accs.iter().map(|a| a.patk as i32).sum::<i32>();
    let satk = r.int as i32 + wpn.map(|w| w.satk as i32).unwrap_or(0) + accs.iter().map(|a| a.satk as i32).sum::<i32>();
    let pdef = r.vit as i32 + arm.map(|a| a.pdef as i32).unwrap_or(0) + accs.iter().map(|a| a.pdef as i32).sum::<i32>();
    let sdef = r.pow as i32 + arm.map(|a| a.sdef as i32).unwrap_or(0) + accs.iter().map(|a| a.sdef as i32).sum::<i32>();
    let name = session.pc_name(id);
    let f = Fighter {
        is_enemy: false,
        char_id: id as i32,
        name: name.clone(),
        hp: (r.hp as i32).max(1),
        max_hp: r.hp_max as i32,
        mp: r.mp as i32,
        max_mp: r.mp_max as i32,
        sp: r.sp as i32,
        max_sp: r.sp_max as i32,
        agl: r.agl as i32,
        luc: r.luc as i32,
        patk,
        pdef,
        satk,
        sdef,
        element: Element::NONE,
        variance: 1.0,
        status: vec![],
        passives: vec![],
        turn: TurnSlot::default(),
        sp_frac: 0,
        // the ring has one area per hit (PC combo count `(PCParam+0x9c >> 3) & 7`, 2 for the demo party)
        hits_per_attack: 2,
        exp: 0,
        cash: 0,
        drops: [DropSlot { item: -1, chance: 0, rare: false }; 2],
        mon_id: 0,
        turns_taken: 0,
        removed: false,
    };
    Some((f, name))
}

/// `CBattle::PCEntry` / `MonsterEntry` for a battle request (`pcs` = party ids, `monster_set` = `MONSETTbl` index).
pub fn build_setup(data: &BattleData, session: &GameSession, pcs: &[u8], monster_set: usize, rand: &mut dyn FnMut() -> u32) -> Option<BattleSetup> {
    let set: MonSetTbl = data.monster_set(monster_set)?;
    let mut fighters = Vec::new();
    let mut names = Vec::new();
    let mut ids = Vec::new();
    for &pc in pcs {
        if let Some((f, n)) = pc_fighter(data, session, pc) {
            fighters.push(f);
            names.push(n);
            ids.push(Some(pc));
        }
    }
    if fighters.is_empty() {
        return None;
    }
    let n = set.monster_count();
    let mut library_ids = Vec::new();
    for &mid in set.monsters.iter().take(n) {
        if mid == 0xffff {
            continue;
        }
        let Some(m) = data.monster(mid as usize) else { continue };
        if !m.no_library && !library_ids.contains(&mid) {
            library_ids.push(mid);
        }
        let (exp, cash) = monster_rewards(m.hp, m.exp, m.cash);
        let variance = (rand() % 1000) as f32 / 1000.0 * 0.05 + 0.975;
        fighters.push(Fighter {
            is_enemy: true,
            char_id: mid as i32,
            name: String::new(),
            hp: m.hp.max(1) as i32,
            max_hp: m.hp.max(1) as i32,
            mp: m.mp as i32,
            max_mp: m.mp as i32,
            sp: 0,
            max_sp: 0,
            agl: m.agl as i32,
            luc: m.luc as i32,
            patk: m.patk as i32,
            pdef: m.pdef as i32,
            satk: m.satk as i32,
            sdef: m.sdef as i32,
            element: Element(m.def_element),
            variance,
            status: vec![],
            passives: vec![],
            turn: TurnSlot::default(),
            sp_frac: 0,
            hits_per_attack: 1,
            exp,
            cash,
            drops: m.drop_slots(),
            mon_id: mid.min(255) as u8,
            turns_taken: 0,
            removed: false,
        });
        let nm = rec_name(data, 8, mid as usize);
        names.push(if nm.trim().is_empty() { format!("Monster {mid}") } else { nm });
        ids.push(None);
    }
    for (f, n) in fighters.iter_mut().zip(&names) {
        f.name = n.clone();
    }
    let escape = match set.escape_mode() {
        1 => EscapeMode::Never,
        2 => EscapeMode::Always,
        _ => EscapeMode::Normal,
    };
    // first strike / ambush (`CheckGambit`, after `PCEntry` / `MonsterEntry`)
    let anti = pcs.iter().filter_map(|&pc| session.save.btl.pc(pc as usize)).any(|r| r.accessories.contains(&ACC_NO_AMBUSH));
    let battle_type = set.battle_type();
    let ambush = if std::env::var_os("SH2_BATTLE_NO_AMBUSH").is_some() { Ambush::None } else { check_gambit(battle_type, &fighters, anti, rand) };
    Some(BattleSetup { fighters, names, pc_ids: ids, escape, ambush, formation: set.formation, set: monster_set, library_ids, battle_type })
}

/// Level-ups caused by one battle: `(pc id, old level, new level)`.
pub type LevelUps = Vec<(u8, u8, u8)>;

/// Write the surviving state of the party back (`MakeResultTrophy`): current HP/MP/SP (minimum 1 HP), and on a victory EXP, level-ups,
/// cash and dropped items.
pub fn apply_end(session: &mut GameSession, tbl: &dyn LevelTable, setup: &BattleSetup, fighters: &[Option<Fighter>], reward: Option<&rules::BattleReward>) -> LevelUps {
    let mut ups = Vec::new();
    for (i, id) in setup.pc_ids.iter().enumerate() {
        let (Some(pc), Some(Some(f))) = (id, fighters.get(i)) else { continue };
        let pc = *pc as usize;
        if let Some(mut r) = session.save.btl.pc(pc) {
            r.hp = f.hp.clamp(1, r.hp_max as i32) as u16;
            r.mp = f.mp.clamp(0, r.mp_max as i32) as u16;
            r.sp = f.sp.clamp(0, r.sp_max as i32) as u8;
            session.save.btl.set_pc(pc, &r);
        }
        if let Some(rw) = reward {
            let gain = rw.exp_per_pc.get(i).copied().unwrap_or(0).max(0) as u32;
            if gain > 0 {
                if let Some(mut r) = session.save.btl.pc(pc) {
                    let old = r.level;
                    r.exp = r.exp.saturating_add(gain);
                    session.save.btl.set_pc(pc, &r);
                    session.save.btl.pc_level_from_exp(pc, tbl);
                    let new = session.save.btl.level(pc);
                    if new != old {
                        ups.push((pc as u8, old, new));
                    }
                }
            }
        }
    }
    if let Some(rw) = reward {
        session.add_cash(rw.cash);
        session.battles_won += 1;
        // US `BtlResult::Polling` 0x396fa0 (and the no-result-screen / chained-battle paths of `BtlSocket::Polling` 0x3657b0): every won
        // battle sets the library bit (`BTL0+0xf43`, demo `+0xdaf`) of its monsters; the field library lists a monster once the bit is set
        for &id in &setup.library_ids {
            session.save.btl.set_monster_defeated(id as usize);
        }
        let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
        for &(item, n) in &rw.items {
            if item >= 0 {
                if let Some(slot) = session.save.btl.data.get_mut(BtlSave::OFF_ITEMS + bag + item as usize) {
                    *slot = slot.saturating_add(n);
                }
            }
        }
    }
    ups
}

/// `BtlSaveSec::SetSceneInit`: create the starting party (`PC_I` records of difficulty 3, names from `SSHMES` section 3) and give the
/// starting items.  `ids` defaults to the party set of a fresh `MenuSave` (PCs 0xb and 5).
pub fn init_new_game(data: &BattleData, session: &mut GameSession) {
    if sh2_core::boot::is_retail() && !data.scene_init(0).is_empty() {
        init_new_game_retail(data, session, 0);
        return;
    }
    let tbl = level_table(data);
    // scenario 3 of the demo (`SetSceneInit(3)`) creates PCs 0, 1, 5 and 6; PC 6 has no record in the demo tables, so the party is Yuri (5),
    // then 0 and 1.
    let ids: Vec<u8> = vec![5, 0, 1];
    for &pc in &ids {
        let Some(pc_i) = data.dat.record(SEC_PC_INIT[3], pc as usize, 0x1c) else { continue };
        let name = data.mes.record(3, pc as usize, 18).unwrap_or(&[]);
        session.init_pc(pc as usize, pc_i, name, &tbl);
    }
    session.set_party(&ids);
    // starting items (placeholder: the scene init tables `RegDat 0x3f` are not decoded): three of item 0, two of item 1
    let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
    for (i, n) in [(0usize, 3u8), (1, 2)] {
        if let Some(s) = session.save.btl.data.get_mut(BtlSave::OFF_ITEMS + bag + i) {
            *s = n;
        }
    }
    session.add_cash(300);
    session.needs_party_init = false;
}

/// Retail `BtlSaveSec::SetSceneInit(scene, 0)` (US `FUN_003bc710`, case `scene`): the new game starts in scene 0 with **Karin (PC 5) and
/// Nicolai (PC 0xb)** (`FUN_003bfbe0(5)` / `(0xb)`: `PC_I` record -> save record, equipment counted into the inventory), then applies the
/// scene's rows of `RegDat 0x47` (8 Thera Leaf / Mana Leaf / Pure Leaf, 3 Talisman of Luck, 3 Tents, ...).  Starting cash is 0: the
/// routine never writes the cash slots of the MENU section.
pub fn init_new_game_retail(data: &BattleData, session: &mut GameSession, scene: usize) {
    let tbl = level_table(data);
    let ids: &[u8] = match scene {
        0 => &[5, 0xb],
        1 => &[5, 0xb, 0, 1],
        _ => &[5, 0xb],
    };
    for &pc in ids {
        let Some(pc_i) = data.dat.record(SEC_PC_INIT[3], pc as usize, 0x1c) else { continue };
        let name = data.mes.record(3, pc as usize, 18).unwrap_or(&[]);
        session.init_pc(pc as usize, pc_i, name, &tbl);
        // `FUN_003be870`: the equipped weapon / armour / accessories are also counted in the inventory arrays (cap 99)
        let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
        for (base, idx) in [(BtlSave::OFF_WEAPONS, pc_i[8]), (BtlSave::OFF_ARMOR, pc_i[9]), (BtlSave::OFF_ACCESSORIES, pc_i[10]), (BtlSave::OFF_ACCESSORIES, pc_i[11]), (BtlSave::OFF_ACCESSORIES, pc_i[12])] {
            if idx != 0xff && idx < 0x80 {
                if let Some(c) = session.save.btl.data.get_mut(base + bag + idx as usize) {
                    *c = c.saturating_add(1).min(99);
                }
            }
        }
    }
    session.set_party(&ids[..ids.len().min(4)]);
    let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
    for row in data.scene_init(scene) {
        let (base, max) = match row.kind {
            1 => (BtlSave::OFF_ITEMS, 0x40),
            2 => (BtlSave::OFF_WEAPONS, 0x60),
            3 => (BtlSave::OFF_ARMOR, 0x30),
            4 => (BtlSave::OFF_ACCESSORIES, 0x50),
            _ => continue, // 5 / 10: obtained bit sets, 6: key items, 7..9: misc flag bits (no slot in the demo-shaped save)
        };
        if (row.index as usize) < max {
            if let Some(c) = session.save.btl.data.get_mut(base + bag + row.index as usize) {
                *c = row.value;
            }
        }
    }
    session.needs_party_init = false;
}

/// Create the save record of party member `pc` the way the retail `PCInit` does for a member joining later (`PC_I` record, equipment
/// counted into the inventory, level-table stats) unless it already exists; `level` (if any) re-rolls the stats at that level.  Used
/// by the dev drive's `SH2_BATTLE_PARTY` / `SH2_BATTLE_LEVEL` overrides and the menu tests.
pub fn ensure_pc(data: &BattleData, session: &mut GameSession, pc: u8, tbl: &dyn LevelTable) {
    if session.save.btl.pc(pc as usize).map(|r| r.present()).unwrap_or(false) {
        return;
    }
    let Some(pc_i) = data.dat.record(SEC_PC_INIT[3], pc as usize, 0x1c) else { return };
    let name = data.mes.record(3, pc as usize, 18).unwrap_or(&[]);
    session.init_pc(pc as usize, pc_i, name, tbl);
    let bag = session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
    for (base, idx) in [(BtlSave::OFF_WEAPONS, pc_i[8]), (BtlSave::OFF_ARMOR, pc_i[9]), (BtlSave::OFF_ACCESSORIES, pc_i[10]), (BtlSave::OFF_ACCESSORIES, pc_i[11]), (BtlSave::OFF_ACCESSORIES, pc_i[12])] {
        if idx != 0xff && idx < 0x80 {
            if let Some(c) = session.save.btl.data.get_mut(base + bag + idx as usize) {
                *c = c.saturating_add(1).min(99);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::pkb_compat::PkbDisc;

    fn data() -> Option<BattleData> {
        let d = PkbDisc::open(std::env::var_os("SH2_DISC_DIR")?).ok()?;
        BattleData::load(&d).ok()
    }

    #[test]
    fn new_game_party_and_battle_setup() {
        let Some(d) = data() else { return };
        let mut s = GameSession::default();
        s.new_game("AP_00_U");
        init_new_game(&d, &mut s);
        assert!(!s.needs_party_init);
        let party = s.battle_party();
        assert!(!party.is_empty());
        for &pc in &party {
            let r = s.save.btl.pc(pc as usize).unwrap();
            assert!(r.present(), "pc {pc}");
            assert!(r.hp_max > 0 && r.level >= 1, "pc {pc}: {r:?}");
        }
        let mut n = 0u32;
        let mut rnd = || {
            n += 17;
            n
        };
        for set in [0usize, 2, 3, 4] {
            let setup = build_setup(&d, &s, &party, set, &mut rnd).unwrap();
            assert!(setup.fighters.iter().any(|f| f.is_enemy), "set {set}");
            assert!(setup.fighters.iter().filter(|f| !f.is_enemy).count() == party.len());
        }
    }

    #[test]
    fn full_battle_pays_out() {
        let Some(d) = data() else { return };
        let mut s = GameSession::default();
        s.new_game("AP_00_U");
        init_new_game(&d, &mut s);
        let party = s.battle_party();
        let mut n = 0u32;
        let mut rnd = || {
            n += 31;
            n
        };
        let setup = build_setup(&d, &s, &party, 0, &mut rnd).unwrap();
        struct Ai;
        impl crate::flow::Host for Ai {
            fn choose_ai_command(&mut self, actor: usize, f: &[Option<Fighter>]) -> crate::flow::MenuEvent {
                let t = f.iter().position(|x| x.as_ref().map(|x| !x.is_enemy && x.hp > 0).unwrap_or(false)).unwrap_or(0);
                crate::flow::MenuEvent::Attack { actor: actor as i32, target: t as i32, kind: 0, skill: -1 }
            }
        }
        let mut b = crate::flow::Battle::new(Ai, setup.fighters.clone(), setup.ambush, setup.escape, 5);
        let enemies: Vec<usize> = setup.fighters.iter().enumerate().filter(|(_, f)| f.is_enemy).map(|(i, _)| i).collect();
        let mut guard = 0;
        while b.poll() {
            guard += 1;
            assert!(guard < 20000);
            if b.phase == crate::flow::Phase::Command {
                if let Some(a) = b.actor {
                    if !b.fighters[a].as_ref().unwrap().is_enemy {
                        let t = enemies.iter().copied().find(|&e| b.fighters[e].as_ref().map(|f| f.hp > 0).unwrap_or(false)).unwrap_or(enemies[0]);
                        b.submit(crate::flow::MenuEvent::Attack { actor: a as i32, target: t as i32, kind: 0, skill: -1 });
                    }
                }
            }
        }
        let reward = b.reward.clone().expect("victory");
        let tbl = level_table(&d);
        let cash0 = s.cash();
        assert!(!setup.library_ids.is_empty());
        assert!(setup.library_ids.iter().all(|&id| !s.save.btl.monster_defeated(id as usize)));
        // an escape / defeat (no reward) leaves the library alone
        apply_end(&mut s, &tbl, &setup, &b.fighters, None);
        assert!(setup.library_ids.iter().all(|&id| !s.save.btl.monster_defeated(id as usize)));
        apply_end(&mut s, &tbl, &setup, &b.fighters, Some(&reward));
        assert!(s.cash() > cash0);
        assert!(party.iter().any(|&p| s.save.btl.pc(p as usize).unwrap().exp > 0));
        // `BtlResult::Polling`: the won battle's monsters are now in the library (and nothing was photographed)
        assert!(setup.library_ids.iter().all(|&id| s.save.btl.monster_defeated(id as usize)));
        assert!(setup.library_ids.iter().all(|&id| !s.save.btl.monster_snapped(id as usize)));
    }

    fn us_data() -> Option<BattleData> {
        let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR")?).ok()?;
        BattleData::load_us(&d).ok()
    }

    /// Retail tables through the demo-shaped view: the tutorial monster set (4 Revenants), Karin / Nicolai as the starting party, the scene 0 items.
    #[test]
    fn us_tables_and_new_game() {
        let Some(d) = us_data() else { return };
        assert_eq!((d.dat.sections.len(), d.mes.sections.len()), (33, 44));
        let m = d.monster(0).unwrap();
        assert_eq!((m.hp, m.patk, m.pdef), (17, 20, 2));
        assert_eq!(d.name(8, 0), "Revenant");
        assert_eq!(d.name(12, 0), "Thera Leaf");
        assert_eq!(d.name(3, 11), "Nicolai");
        let set = d.monster_set(0).unwrap();
        assert_eq!((set.formation, set.monster_count()), (6, 4));
        assert_eq!(&set.monsters[..4], &[0, 0, 0, 0]);
        assert_eq!(d.dat.section(12).len() / 16, 327 + 0); // + 4 byte trailer rounds down
        // PC_L: 14 characters, level rows with growing EXP
        let rows = d.pc_levels(5);
        assert!(rows.len() >= 90, "{}", rows.len());
        assert_eq!(crate::rules::level_for_exp(&rows, 0), 1);
        // scene 0 inventory
        let sc = d.scene_init(0);
        assert_eq!(sc.len(), 8);
        assert_eq!(sc[0], crate::data::SceneItem { kind: 1, value: 8, index: 0 });
        // new game
        let mut s = GameSession::default();
        s.new_game("OP_00_U");
        init_new_game_retail(&d, &mut s, 0);
        assert_eq!(s.battle_party(), vec![5, 0xb]);
        let karin = s.save.btl.pc(5).unwrap();
        assert!(karin.present() && karin.level == 1 && karin.hp_max > 0, "{karin:?}");
        assert_eq!(s.save.btl.pc(0xb).unwrap().level, 2);
        assert_eq!(s.save.btl.item_count(0), 8); // Thera Leaf
        assert_eq!(s.save.btl.item_count(32), 3); // Tent
        assert_eq!(s.cash(), 0);
        // the first fight (monster set 0 = 4 Revenants) builds
        let mut n = 0u32;
        let mut rnd = || {
            n += 13;
            n
        };
        let setup = build_setup(&d, &s, &[5, 0xb], 0, &mut rnd).unwrap();
        assert_eq!(setup.fighters.iter().filter(|f| f.is_enemy).count(), 4);
        assert_eq!(setup.fighters.iter().filter(|f| !f.is_enemy).count(), 2);
    }

    /// The real first encounter of the retail game (PINE, AP_03_U: MONSET 2 = Revenant, Revenant, Statue) against a *fresh* Karin (25 HP) +
    /// Nicolai (38 HP): the party must win without any level boost in every one of 200 seeded fights (ring x1.0 per hit, enemies attack the
    /// first living PC).  Live damage references: Nicolai deals 12 + 6 (or 12 + 8 with a strike hit) to a Revenant.
    #[test]
    fn us_first_real_encounter_is_winnable_without_boost() {
        let Some(d) = us_data() else { return };
        let mut won = 0;
        for seed in 0..200u32 {
            let mut s = GameSession::default();
            s.new_game("OP_00_U");
            init_new_game_retail(&d, &mut s, 0);
            let party = s.battle_party();
            let mut n = seed.wrapping_mul(2654435761);
            let mut rnd = || {
                n = n.wrapping_mul(1664525).wrapping_add(1013904223);
                n >> 1
            };
            let setup = build_setup(&d, &s, &party, 2, &mut rnd).unwrap();
            assert_eq!(setup.fighters.iter().filter(|f| f.is_enemy).count(), 3);
            struct Ai;
            impl crate::flow::Host for Ai {
                fn choose_ai_command(&mut self, actor: usize, f: &[Option<Fighter>]) -> crate::flow::MenuEvent {
                    let t = f.iter().position(|x| x.as_ref().map(|x| !x.is_enemy && x.hp > 0).unwrap_or(false)).unwrap_or(0);
                    crate::flow::MenuEvent::Attack { actor: actor as i32, target: t as i32, kind: 0, skill: -1 }
                }
            }
            let mut b = crate::flow::Battle::new(Ai, setup.fighters.clone(), setup.ambush, setup.escape, seed as u64 + 1);
            let enemies: Vec<usize> = setup.fighters.iter().enumerate().filter(|(_, f)| f.is_enemy).map(|(i, _)| i).collect();
            let mut guard = 0;
            while b.poll() {
                guard += 1;
                assert!(guard < 30000);
                if b.phase == crate::flow::Phase::Command {
                    if let Some(a) = b.actor {
                        if !b.fighters[a].as_ref().unwrap().is_enemy {
                            let t = enemies.iter().copied().find(|&e| b.fighters[e].as_ref().map(|f| f.hp > 0).unwrap_or(false)).unwrap_or(enemies[0]);
                            b.submit(crate::flow::MenuEvent::Attack { actor: a as i32, target: t as i32, kind: 0, skill: -1 });
                        }
                    }
                }
            }
            if b.reward.is_some() {
                won += 1;
            }
        }
        assert_eq!(won, 200, "fresh party lost {} of 200 first encounters", 200 - won);
    }

    /// The two scripted fights of the first free-control map `AP_02_U` (`InvokeBattleTbl 0` / `1` = `BBTL` rows of the US `FIELD/FIELD.DAT`: monster
    /// sets 4 and 5, background 77): a fresh party must win them with the plain attack AI, like the live game's first scripted fight.
    #[test]
    fn us_ap_02_u_scripted_fights_are_winnable_without_boost() {
        let Some(d) = us_data() else { return };
        for monset in [4usize, 5] {
            let mut won = 0;
            for seed in 0..100u32 {
                let mut s = GameSession::default();
                s.new_game("OP_00_U");
                init_new_game_retail(&d, &mut s, 0);
                let party = s.battle_party();
                let mut n = seed.wrapping_mul(2654435761);
                let mut rnd = || {
                    n = n.wrapping_mul(1664525).wrapping_add(1013904223);
                    n >> 1
                };
                let setup = build_setup(&d, &s, &party, monset, &mut rnd).unwrap();
                struct Ai;
                impl crate::flow::Host for Ai {
                    fn choose_ai_command(&mut self, actor: usize, f: &[Option<Fighter>]) -> crate::flow::MenuEvent {
                        let t = f.iter().position(|x| x.as_ref().map(|x| !x.is_enemy && x.hp > 0).unwrap_or(false)).unwrap_or(0);
                        crate::flow::MenuEvent::Attack { actor: actor as i32, target: t as i32, kind: 0, skill: -1 }
                    }
                }
                let mut b = crate::flow::Battle::new(Ai, setup.fighters.clone(), setup.ambush, setup.escape, seed as u64 + 1);
                let enemies: Vec<usize> = setup.fighters.iter().enumerate().filter(|(_, f)| f.is_enemy).map(|(i, _)| i).collect();
                assert!(!enemies.is_empty());
                let mut guard = 0;
                while b.poll() {
                    guard += 1;
                    assert!(guard < 30000);
                    if b.phase == crate::flow::Phase::Command {
                        if let Some(a) = b.actor {
                            if !b.fighters[a].as_ref().unwrap().is_enemy {
                                let t = enemies.iter().copied().find(|&e| b.fighters[e].as_ref().map(|f| f.hp > 0).unwrap_or(false)).unwrap_or(enemies[0]);
                                b.submit(crate::flow::MenuEvent::Attack { actor: a as i32, target: t as i32, kind: 0, skill: -1 });
                            }
                        }
                    }
                }
                if b.reward.is_some() {
                    won += 1;
                }
            }
            eprintln!("US scripted monster set {monset}: fresh party won {won}/100");
            assert_eq!(won, 100, "monster set {monset}: fresh party lost {} of 100", 100 - won);
        }
    }

    /// Live (US, armsx2 over PINE, started with the SSHSys battle request for `MONSETTbl` index 2): the first random encounter's victory screen
    /// reads **Exp. 5, Cash. 40** and the CBattle result record (`+0x48b4` exp, `+0x48b8` cash) holds 5 / 40: Revenant 1 + 1, Statue 3 exp
    /// and 10 + 10 + 20 cash.  The tutorial set 4 (formation 6) spawns four live enemy slots (four Revenants: 4 exp, 40 cash).
    #[test]
    fn us_encounter_rewards_match_the_live_result_record() {
        let Some(d) = us_data() else { return };
        for (monset, exp, cash) in [(2usize, 5, 40), (4, 4, 40)] {
            let mut s = GameSession::default();
            s.new_game("OP_00_U");
            init_new_game_retail(&d, &mut s, 0);
            let party = s.battle_party();
            let mut n = 0u32;
            let mut rnd = || {
                n += 31;
                n
            };
            let setup = build_setup(&d, &s, &party, monset, &mut rnd).unwrap();
            let enemies: Vec<_> = setup.fighters.iter().filter(|f| f.is_enemy).collect();
            assert_eq!(enemies.len(), if monset == 4 { 4 } else { 3 }, "live enemy slots of set {monset}");
            assert_eq!(enemies.iter().map(|f| f.exp).sum::<i32>(), exp, "set {monset} exp");
            assert_eq!(enemies.iter().map(|f| f.cash).sum::<i32>(), cash, "set {monset} cash");
        }
        // the headless fight pays the same record out (strong party so that it is won)
        let mut s = GameSession::default();
        s.new_game("OP_00_U");
        init_new_game_retail(&d, &mut s, 0);
        let party = s.battle_party();
        let mut n = 0u32;
        let mut rnd = || {
            n += 31;
            n
        };
        let setup = build_setup(&d, &s, &party, 2, &mut rnd).unwrap();
        struct Ai;
        impl crate::flow::Host for Ai {
            fn choose_ai_command(&mut self, actor: usize, f: &[Option<Fighter>]) -> crate::flow::MenuEvent {
                let t = f.iter().position(|x| x.as_ref().map(|x| !x.is_enemy && x.hp > 0).unwrap_or(false)).unwrap_or(0);
                crate::flow::MenuEvent::Attack { actor: actor as i32, target: t as i32, kind: 0, skill: -1 }
            }
        }
        let mut fighters = setup.fighters.clone();
        for f in fighters.iter_mut().filter(|f| !f.is_enemy) {
            f.patk = 200;
            f.hp = 500;
            f.max_hp = 500;
        }
        let mut b = crate::flow::Battle::new(Ai, fighters, setup.ambush, setup.escape, 9);
        let enemies: Vec<usize> = setup.fighters.iter().enumerate().filter(|(_, f)| f.is_enemy).map(|(i, _)| i).collect();
        let mut guard = 0;
        while b.poll() {
            guard += 1;
            assert!(guard < 30000);
            if b.phase == crate::flow::Phase::Command {
                if let Some(a) = b.actor {
                    if !b.fighters[a].as_ref().unwrap().is_enemy {
                        let t = enemies.iter().copied().find(|&e| b.fighters[e].as_ref().map(|f| f.hp > 0).unwrap_or(false)).unwrap_or(enemies[0]);
                        b.submit(crate::flow::MenuEvent::Attack { actor: a as i32, target: t as i32, kind: 0, skill: -1 });
                    }
                }
            }
        }
        let r = b.reward.clone().expect("victory");
        assert_eq!((r.exp_total, r.cash), (5, 40), "reward screen of the first encounter (live: Exp. 5, Cash. 40)");
    }

    /// The retail tutorial fight (monster set 0: four Revenants) against a new game's Karin / Nicolai plays out headlessly and pays out the
    /// retail EXP / cash.
    #[test]
    fn us_first_fight_pays_out() {
        let Some(d) = us_data() else { return };
        let mut s = GameSession::default();
        s.new_game("OP_00_U");
        init_new_game_retail(&d, &mut s, 0);
        let party = s.battle_party();
        let mut n = 0u32;
        let mut rnd = || {
            n += 31;
            n
        };
        let setup = build_setup(&d, &s, &party, 0, &mut rnd).unwrap();
        struct Ai;
        impl crate::flow::Host for Ai {
            fn choose_ai_command(&mut self, actor: usize, f: &[Option<Fighter>]) -> crate::flow::MenuEvent {
                let t = f.iter().position(|x| x.as_ref().map(|x| !x.is_enemy && x.hp > 0).unwrap_or(false)).unwrap_or(0);
                crate::flow::MenuEvent::Attack { actor: actor as i32, target: t as i32, kind: 0, skill: -1 }
            }
        }
        let mut b = crate::flow::Battle::new(Ai, setup.fighters.clone(), setup.ambush, setup.escape, 5);
        let enemies: Vec<usize> = setup.fighters.iter().enumerate().filter(|(_, f)| f.is_enemy).map(|(i, _)| i).collect();
        let mut guard = 0;
        while b.poll() {
            guard += 1;
            assert!(guard < 30000);
            if b.phase == crate::flow::Phase::Command {
                if let Some(a) = b.actor {
                    if !b.fighters[a].as_ref().unwrap().is_enemy {
                        let t = enemies.iter().copied().find(|&e| b.fighters[e].as_ref().map(|f| f.hp > 0).unwrap_or(false)).unwrap_or(enemies[0]);
                        b.submit(crate::flow::MenuEvent::Attack { actor: a as i32, target: t as i32, kind: 0, skill: -1 });
                    }
                }
            }
        }
        let reward = b.reward.clone().expect("victory over four Revenants");
        assert!(reward.cash > 0);
    }
}
