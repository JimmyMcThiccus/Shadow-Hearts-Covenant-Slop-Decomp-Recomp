//! Dump what the battle menu builder sees on the retail disc: PC names, `SKIL` groups (raw name index columns), `MC_P`, the item
//! table's sort columns and the new-game scene rows.  `SH2_US_DISC_DIR` must be set; `--us` is implied.
use sh2_battle::{actions::ActionTables, data::BattleData, pkb_compat::PkbDisc};
fn u16at(b: &[u8], o: usize) -> u16 {
    u16::from_le_bytes([b[o], b[o + 1]])
}
fn main() {
    let jp = std::env::var_os("SH2_MENU_DUMP_JP").is_some();
    sh2_core::boot::set_active_region(if jp { sh2_core::boot::Region::Jp } else { sh2_core::boot::Region::Us });
    let d = PkbDisc::open(std::env::var_os(if jp { "SH2_DISC_DIR" } else { "SH2_US_DISC_DIR" }).expect("disc dir")).unwrap();
    let data = if jp { BattleData::load_jp(&d).unwrap() } else { BattleData::load_us(&d).unwrap() };
    if !jp {
        let mes = d.read("COMMON/SSHMES.NA").unwrap();
        let dat = d.read("COMMON/SSHDAT.NA").unwrap();
        let us = sh2_core::regdat::UsRegDat::new(&mes, &dat).unwrap();
        println!("== retail table 42 labels / table 43 help");
        let f = sh2_core::regdat::RegFile::new(&mes);
        for i in 0..32 {
            let t = f.entry(43);
            let off = u32::from_le_bytes(mes[t + i * 4..t + i * 4 + 4].try_into().unwrap()) as usize;
            let s = &mes[t + off..];
            let l = s.iter().position(|&c| c == 0).unwrap_or(0).min(120);
            println!("  {i:2}: {:?}  / {:?}", us.text(0x2a, i, -1).unwrap_or_default(), String::from_utf8_lossy(&s[..l]));
        }
    }
    let t = ActionTables::load(&data);
    println!("== PC names (SSHMES section 3)");
    for pc in 0..16 {
        println!("pc {pc:2}: {:?}", data.name(3, pc));
    }
    println!("== skill names (section 15 / US kind 9): {}", t.skill_names.len());
    for (i, n) in t.skill_names.iter().enumerate() {
        println!("  {i:3}: {n:?}");
    }
    println!("== SKIL groups");
    let ssec = data.dat.section(sh2_battle::data::SEC_SKILL);
    for g in 0..24 {
        let off = u32::from_le_bytes(ssec[g * 8..g * 8 + 4].try_into().unwrap());
        let cnt = u32::from_le_bytes(ssec[g * 8 + 4..g * 8 + 8].try_into().unwrap());
        println!("group {g:2}: off {off:#x} cnt {cnt}");
        if off == 0xffff_ffff || g >= 0x16 {
            continue;
        }
        for i in 0..cnt as usize {
            let o = off as usize + i * 0x40;
            let Some(r) = ssec.get(o..o + 0x40) else { break };
            let name2 = u16at(r, 2);
            let name3e = u16at(r, 0x3e);
            println!("   {i:2}: +0 {:04x} +2 {name2:5} flags {:04x} eff {:5} pow {:3} mp {:3} +0x3e {name3e:5}  name[+2]={:?} name[+3e]={:?}", u16at(r, 0), u16at(r, 4), u16at(r, 0x18) as i16, u16at(r, 0x1a) as i16, u16at(r, 0x1e), t.skill_name(name2 as usize), t.skill_name(name3e as usize));
        }
    }
    println!("== MC_P crests: {}", t.crests.len());
    for c in t.crests.iter().take(8) {
        println!("  {:2}: flags {:02x} magic {:?}", c.id, c.flags, c.magic);
    }
    println!("== magic names: {}", t.magic_names.len());
    for (i, m) in t.magic.iter().enumerate().take(40) {
        println!("  {i:3}: {:?} flags {:04x} mp {} empty {}", t.magic_name(i), m.flags, m.mp, m.empty);
    }
    println!("== items (id, name, flags, battle_use, +0x2c, +0x2e)");
    let isec = data.dat.section(sh2_battle::data::SEC_ITEM);
    for (i, r) in t.items.iter().enumerate() {
        let raw = &isec[i * 0x30..(i + 1) * 0x30];
        println!("  {i:3}: {:24} flags {:04x} use {} sort {:3} / {:3} ring {:?}", t.item_name(i), r.flags, r.battle_use, u16at(raw, 0x2c), u16at(raw, 0x2e), [u16at(raw, 0x1c) as i16, u16at(raw, 0x1e) as i16, u16at(raw, 0x20) as i16]);
    }
    println!("== item_order: {:?}", t.item_order);
    extra(&data);
    rings(&data);
    if !jp { aroma(&d); }
    for scene in 0..3 {
        println!("== scene {scene} rows");
        for r in data.scene_init(scene) {
            println!("  kind {} value {} index {}", r.kind, r.value, r.index);
        }
    }
}
// (appended) fusion rows + level finder
pub fn extra(data: &BattleData) {
    let fsec = data.dat.section(sh2_battle::data::SEC_FUSION[0]);
    println!("== FUSM rows (0x20): {}", fsec.len() / 0x20);
    for i in 0..(fsec.len() / 0x20).min(24) {
        let r = &fsec[i * 0x20..(i + 1) * 0x20];
        println!("  {i:2}: {:?} raw {:02x?}", data.name(4, i), r);
    }
    for pc in [0usize, 3, 4, 5, 0xb] {
        let rows = data.pc_levels(pc);
        let s: Vec<String> = rows.iter().enumerate().filter(|(l, _)| *l < 30).map(|(l, r)| format!("L{l}:{}/{}/{}", r.hp, r.mp, r.sp)).collect();
        println!("== pc {pc} levels: {}", s.join(" "));
    }
}
// (appended) aroma oils / combos and tarot names
pub fn aroma(d: &PkbDisc) {
    let mes = d.read("COMMON/SSHMES.NA").unwrap();
    let dat = d.read("COMMON/SSHDAT.NA").unwrap();
    let us = sh2_core::regdat::UsRegDat::new(&mes, &dat).unwrap();
    println!("== oils (kind 0x42 count {:?}; names kind 0xd)", us.count(0x42, 0));
    for i in 0..12 {
        println!("  {i}: {:?} raw {:02x?}", us.text(0xd, i, -1), us.record(0x42, i, -1).map(|r| &r[..r.len().min(0x20)]));
    }
    println!("== combos (kind 0x43 count {:?})", us.count(0x43, 0));
    for i in 0..40 {
        let Some(r) = us.record(0x43, i, -1) else { break };
        println!("  {i:2}: first {} second {} mp {} name {:?} raw {:02x?}", r[0x1c] as i8, r[0x1d] as i8, u16::from_le_bytes([r[0x1e], r[0x1f]]), us.text(0x12, i, -1), &r[..0x40.min(r.len())]);
    }
    println!("== tarot names kind 0xe");
    for i in 0..24 {
        println!("  {i:2}: {:?}", us.text(0xe, i, -1));
    }
    println!("== snap kind 0xf: {:?} / {:?}; kind 0x45 rows: {:?}", us.text(0xf, 0, -1), us.text(0xf, 1, -1), (0..2).map(|i| us.record(0x45, i, -1).map(|r| r[..0x20.min(r.len())].to_vec())).collect::<Vec<_>>());
    println!("== fusion help 21/22: {:?} / {:?}", us.text(0x18, 21, -1), us.text(0x18, 22, -1));
}
// (appended) ring columns of the action records
pub fn rings(data: &BattleData) {
    let ssec = data.dat.section(sh2_battle::data::SEC_SKILL);
    let g = |grp: usize, i: usize| -> Vec<i16> {
        let off = u32::from_le_bytes(ssec[grp * 8..grp * 8 + 4].try_into().unwrap()) as usize + i * 0x40;
        (0..14).map(|k| i16::from_le_bytes([ssec[off + 0x20 + k * 2], ssec[off + 0x21 + k * 2]])).collect()
    };
    println!("== ring columns +0x20.. (steps (s,w) x5, modulate (s,w,pct,strike))");
    println!("  Cure (g11 r0): {:?}", g(11, 0));
    println!("  Blessed Light (g11 r1): {:?}", g(11, 1));
    println!("  Heuervelk t3 (g5 r2): {:?}", g(5, 2));
    println!("  Crag (g14 r1): {:?}", g(14, 1));
    println!("  Red Comet (g1 r11): {:?}", g(1, 11));
    let msec = data.dat.section(sh2_battle::data::SEC_MAGIC);
    for id in [0usize, 1, 10] {
        let o = id * 0x44;
        let v: Vec<i16> = (0..14).map(|k| i16::from_le_bytes([msec[o + 0x20 + k * 2], msec[o + 0x21 + k * 2]])).collect();
        println!("  magic {id} {:?}: {:?}", data.name(17, id), v);
    }
    let isec = data.dat.section(sh2_battle::data::SEC_ITEM);
    for id in [0usize, 4, 15] {
        let o = id * 0x30;
        let v: Vec<i16> = (0..4).map(|k| i16::from_le_bytes([isec[o + 0x1c + k * 2], isec[o + 0x1d + k * 2]])).collect();
        println!("  item {id} {:?} +0x1c..: {:?}", data.name(12, id), v);
    }
}
