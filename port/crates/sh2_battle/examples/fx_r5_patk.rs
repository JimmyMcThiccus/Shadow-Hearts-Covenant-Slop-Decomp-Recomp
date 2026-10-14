//! Round 5 FX: every `PATK` (weapon attack, `GetRegDat(0x3a)`) row and the `PATK2` rows it points at (`+0xc` base, per hit), with the locus class
//! (`+2`: 1 blow, 2 sword) and kind (`+1`) that `CBattle::AttackParam` uses to pick the weapon trail.
use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};
fn main() {
    let dir = std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let d = PkbDisc::open(&dir).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let n1 = data.dat.section(23).len() / 0x18;
    let n2 = data.dat.section(24).len() / 0x48;
    println!("PATK {n1} rows, PATK2 {n2} rows");
    for i in 0..n1 {
        let r = data.dat.record(23, i, 0x18).unwrap();
        let base = u16::from_le_bytes([r[0xc], r[0xd]]) as usize;
        let sword = i16::from_le_bytes([r[0x14], r[0x15]]);
        let hits = r[1];
        let mut s = String::new();
        for k in 0..(hits as usize * 3).max(1) {
            if let Some(p) = data.dat.record(24, base + k, 0x48) {
                let name = |o: usize| String::from_utf8_lossy(&p[o..o + 16]).split('\0').next().unwrap_or("").to_string();
                s += &format!(" [{}: k{:#x} c{} {:?} {:?}]", base + k, p[1], p[2], name(4), name(0x14));
            }
        }
        println!("PATK[{i}] hits {} {:02x?} swordtbl {sword}:{s}", hits, &r[..0x18]);
    }
}
