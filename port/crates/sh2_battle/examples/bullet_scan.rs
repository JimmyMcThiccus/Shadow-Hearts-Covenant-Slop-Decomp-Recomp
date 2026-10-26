//! Developer tool: list the PATK records whose PATK2 hit rows are bullet class (`rec[1] == 0x16`, `CBattle::AttackParam` / `MotionEventCallBack`),
//! with the `PATK +0x14` bullet table they use, and which monsters reference them.  (`SH2_US_DISC_DIR` must be set)
use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};
fn main() {
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let dir = std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let d = PkbDisc::open(&dir).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let mut classes = std::collections::BTreeMap::<u8, usize>::new();
    for i in 0..2000usize {
        let Some(r) = data.dat.record(23, i, 0x18) else { break };
        let base = u16::from_le_bytes([r[0xc], r[0xd]]) as usize;
        let n = r[1].max(1) as usize;
        let mut cls = vec![];
        for g in 0..n.min(16) {
            if let Some(r2) = data.dat.record(24, base + g, 0x48) {
                *classes.entry(r2[1]).or_default() += 1;
                cls.push(r2[1]);
                if r2[1] == 0x16 {
                    // the push words (`BtlChr+0x31e / +0x320 / +0x322` = row +3 / +0x44 / +0x46)
                    println!("  PATK[{i}] row {g}: hit class {} push time {} power {}", r2[3], u16::from_le_bytes([r2[0x44], r2[0x45]]), u16::from_le_bytes([r2[0x46], r2[0x47]]));
                }
            }
        }
        if cls.contains(&0x16) {
            let mons: Vec<usize> = (0..600).filter(|&m| data.monster(m).map(|mp| mp.attack_table as usize == i).unwrap_or(false)).collect();
            println!("PATK[{i}] class3={} tbl14={} hits {:?} rows {:02x?} monsters {:?}", r[3], i16::from_le_bytes([r[0x14], r[0x15]]), cls, &r[..0x18], mons);
        }
    }
    println!("row class histogram {:02x?}", classes);
    if std::env::var_os("ROW_HIST").is_some() {
        for pc in 0..14usize {
            if let Some(r) = data.dat.record(23, pc, 0x18) {
                let base = u16::from_le_bytes([r[0xc], r[0xd]]) as usize;
                let rows: Vec<String> = (0..r[1].max(1) as usize).filter_map(|g| data.dat.record(24, base + g, 0x48).map(|x| format!("k{:#x}/c{}/{}/{}", x[1], x[3], u16::from_le_bytes([x[0x44], x[0x45]]), u16::from_le_bytes([x[0x46], x[0x47]])))).collect();
                println!("PC PATK[{pc}] hits {} rows {}", r[1], rows.join(" "));
            }
        }
    }
    // hit reaction classes (PATK2 row +3) and push words of every row, by row kind (+1)
    let mut hist = std::collections::BTreeMap::<(u8, u8, u16, u16), usize>::new();
    for i in 0..4000usize {
        let Some(r2) = data.dat.record(24, i, 0x48) else { break };
        *hist.entry((r2[1], r2[3], u16::from_le_bytes([r2[0x44], r2[0x45]]), u16::from_le_bytes([r2[0x46], r2[0x47]]))).or_default() += 1;
    }
    for ((kind, class, t, p), n) in &hist {
        if std::env::var_os("ROW_HIST").is_some() {
            println!("row kind {kind:#x} hit class {class} push {t}/{p}: {n}");
        }
    }
    let mut inplace = vec![];
    for m in 0..600usize {
        let Some(mp) = data.monster(m) else { continue };
        if let Some(r) = data.dat.record(23, mp.attack_table as usize, 0x18) {
            if r[2] & 7 != 0 {
                let base = u16::from_le_bytes([r[0xc], r[0xd]]) as usize;
                let cls: Vec<u8> = (0..r[1].max(1) as usize).filter_map(|g| data.dat.record(24, base + g, 0x48).map(|x| x[1])).collect();
                inplace.push(format!("{m}:p2={:#x}:cls{:?}", r[2], cls));
            }
        }
    }
    println!("in-place monsters ({}): {}", inplace.len(), inplace.join(" "));
    // fusions whose attack table (`FUSM +6`, `CBattle::FusionChange` -> `nAtkTbl`) shoots, and the rows of every bullet table
    for (t, &sec) in sh2_battle::data::SEC_FUSION.iter().enumerate() {
        let fsec = data.dat.section(sec);
        for id in 0..fsec.len() / 0x20 {
            let r = &fsec[id * 0x20..id * 0x20 + 0x20];
            let patk = u16::from_le_bytes([r[6], r[7]]) as usize;
            let tbl = data.dat.record(23, patk, 0x18).map(|p| i16::from_le_bytes([p[0x14], p[0x15]])).unwrap_or(-1);
            if [8, 20, 21, 29, 30].contains(&patk) {
                println!("FUSM table {t} fusion {id}: PATK {patk} (bullet table {tbl}) model {}", u16::from_le_bytes([r[2], r[3]]));
            }
        }
    }
    if let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") {
        if let Ok(b) = sh2_core::fileio::read_disc_file(std::path::Path::new(&dir), "BATTLE.BIN") {
            for (t, rows) in sh2_gfx::effects::bullet::bullet_table(&b, true).iter().enumerate() {
                for (k, r) in rows.iter().enumerate() {
                    println!("bullet table {t} row {k}: kind {} source {} bbox {} pair {} offset {:?} dir {:?}", r.kind, r.source, r.bbox, r.pair, r.offset, r.dir);
                }
            }
        }
    }
    let shooters = [83usize, 85, 86, 88, 89, 102, 103, 105, 123, 124, 125, 172, 208, 209, 213];
    for i in 0..sh2_battle::headless::monset_count(&data) {
        let Some(ms) = data.monster_set(i) else { continue };
        let txt = format!("monsters {:?} formation {}", ms.monsters, ms.formation);
        if shooters.iter().any(|m| ms.monsters.contains(&(*m as u16))) {
            println!("MONSET {i}: {txt}");
        }
    }
}
