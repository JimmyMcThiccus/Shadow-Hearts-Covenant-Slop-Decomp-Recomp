//! Weapon-trail census: which monsters / sets use which `PATK` trail class (`+3`) or per-hit `PATK2` sword kind (see notes/integration/locus_effects.md).
//! `cargo run -p sh2_battle --example locus_scan` (needs `SH2_US_DISC_DIR`)
use sh2_battle::{data::BattleData, headless, pkb_compat::PkbDisc};
fn main() {
    let dir = std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let d = PkbDisc::open(&dir).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    // per PATK row: the whole-swing class and the per-hit sword kinds (class 2 PATK2 rows)
    let n1 = data.dat.section(23).len() / 0x18;
    let mut info = vec![(0u8, vec![]); n1];
    for i in 0..n1 {
        let r = data.dat.record(23, i, 0x18).unwrap();
        let base = u16::from_le_bytes([r[0xc], r[0xd]]) as usize;
        let mut kinds = std::collections::BTreeSet::new();
        for k in 0..(r[1] as usize * 3).max(1) {
            if let Some(p) = data.dat.record(24, base + k, 0x48) {
                if p[2] == 2 {
                    kinds.insert(p[1]);
                }
            }
        }
        info[i] = (r[3], kinds.into_iter().collect());
    }
    let nm = data.dat.section(data_sec_monster()).len() / sh2_battle::data::MonsterParam::SIZE;
    println!("monster\tattack_table\tswing\tkinds");
    for m in 0..nm {
        if let Some(mp) = data.monster(m) {
            let t = mp.attack_table as usize;
            if let Some((sw, kinds)) = info.get(t) {
                if (*sw != 0 && *sw != 3) || kinds.iter().any(|k| matches!(*k, 6 | 7 | 0xc | 0x11 | 0x1b)) {
                    println!("{m}\t{t}\t{sw}\t{kinds:x?}");
                }
            }
        }
    }
    if std::env::var_os("LOCUS_WEAPONS").is_some() {
        weapons(&data);
    }
    if let Some(n) = std::env::var_os("LOCUS_MODEL") {
        model_boxes(&dir, &n.to_string_lossy());
    }
    println!("sets (monsters):");
    for s in 0..headless::monset_count(&data) {
        if let Some(ms) = data.monster_set(s) {
            let list: Vec<String> = ms.monsters.iter().filter(|m| **m != 0 && **m != 0xffff).map(|m| m.to_string()).collect();
            println!("set {s}: {}", list.join(","));
        }
    }
}
fn data_sec_monster() -> usize {
    sh2_battle::data::SEC_MONSTER
}

#[allow(dead_code)]
fn weapons(data: &BattleData) {
    let n = data.dat.section(sh2_battle::data::SEC_WEAPON).len() / 0x34;
    for i in 0..n {
        let r = data.dat.record(sh2_battle::data::SEC_WEAPON, i, 0x34).unwrap();
        println!("weapon {i}: model {} {:02x?}", i16::from_le_bytes([r[4], r[5]]), &r[..0x34]);
    }
}

/// `LOCUS_MODEL=443`: the box (`BBHD`) frame names of a battle model (`BTLDATA/CHR/%03d.BCM`).
#[allow(dead_code)]
fn model_boxes(dir: &std::ffi::OsStr, n: &str) {
    let d = sh2_core::fileio::Disc::open(dir).expect("disc");
    let b = d.read(&format!("BTLDATA/CHR/{n}.BCM")).expect("read");
    let pkg = sh2_formats::pkb::parse_package(&b, 0).expect("package");
    for e in pkg.entries.iter().filter(|e| e.kind_str() == "mdl") {
        let m = sh2_formats::model::Model::parse(&b[e.offset.min(b.len())..]).expect("model");
        let names: Vec<String> = m.bounds.iter().map(|x| m.frames.get((x.tag & 0xff) as usize).map(|f| f.name.clone()).unwrap_or_default()).collect();
        println!("model {n}: {} boxes {names:?}", m.bounds.len());
    }
}
