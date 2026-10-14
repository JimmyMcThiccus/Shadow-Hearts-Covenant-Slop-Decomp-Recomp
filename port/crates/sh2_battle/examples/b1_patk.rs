//! Developer tool (B1): dump PATK / PATK2 rows (weapon attack tables) of the US data and the MosEvent / MosCncel frames of the attack motions of a model.
use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let dir = std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let d = PkbDisc::open(&dir).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    for pc in [0usize, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13] {
        if let Some(r) = data.dat.record(23, pc, 0x18) {
            println!("PATK[{pc}] {:02x?}", r);
            let row = u16::from_le_bytes([r[0xc], r[0xd]]) as usize;
            if let Some(r2) = data.dat.record(24, row, 0x48) { println!("   PATK2[{row}] {:02x?}", r2); }
        }
    }
    let disc = sh2_core::fileio::Disc::open(&dir).unwrap();
    for n in a[1..].iter().map(|s| s.parse::<u32>().unwrap()) {
        let files = sh2_battle::models::chr_files_for(true, n);
        let (bcm, anm) = (disc.read(&files[0]).unwrap(), disc.read(&files[1]).unwrap());
        let (_m, motions) = sh2_gfx::bevy::character::parse_character(&[&bcm, &anm]).unwrap();
        println!("CHR {n}");
        for m in motions.iter().filter(|m| matches!(m.name.as_str(), "atck" | "can1" | "can2" | "can3" | "can4" | "rdy" | "srdy" | "dsh")) {
            let ev = |name: &str| m.events.iter().filter(|e| e.base_name() == name).flat_map(|e| e.keys()).map(|k| k.time).collect::<Vec<_>>();
            println!("  {:5} frames {:3} MosEvent {:?} MosCncel {:?} root travel {:.1}", m.name, m.last_frame(), ev("MosEvent"), ev("MosCncel"), 0.0);
        }
    }
}
