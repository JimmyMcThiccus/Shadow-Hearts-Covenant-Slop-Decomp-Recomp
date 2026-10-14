//! Developer tool: the FUSM (fusion monster) records of every chapter table + names, and which CHR packages exist.
use sh2_battle::data::{BattleData, SEC_FUSION};
use sh2_battle::pkb_compat::PkbDisc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let disc = PkbDisc::open(&a[1]).unwrap();
    let db = BattleData::load(&disc).unwrap();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    for (c, &sec) in SEC_FUSION.iter().enumerate() {
        let s = db.dat.section(sec);
        println!("chapter {c}: {} records", s.len() / 0x20);
        for i in 0..s.len() / 0x20 {
            let r = &s[i * 0x20..(i + 1) * 0x20];
            let chr = r[0] as u32;
            let has = d.read(&format!("BTLDATA/CHR/{chr:03}.BCM")).is_ok();
            println!("  {i}: name {:?} sub {} chr_exists {} bytes {:02x?}", db.name(4 + c, i), chr, has, &r[..16]);
        }
    }
}
