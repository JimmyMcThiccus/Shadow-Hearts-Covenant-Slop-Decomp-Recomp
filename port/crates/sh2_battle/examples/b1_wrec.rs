//! Developer tool (B1): dump WPN_ / CLOT records of the US data (`b1_wrec`).
use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};
fn main() {
    let dir = std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let d = PkbDisc::open(dir).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    for i in 0..80usize {
        if let Some(r) = data.dat.record(sh2_battle::data::SEC_WEAPON, i, 0x34) {
            println!("WPN {i:2}: {:02x?}", &r[..0x18]);
        }
    }
    for i in 0..20usize {
        if let Some(r) = data.dat.record(18, i, 0xc) {
            println!("CLOT {i:2}: {:02x?}", r);
        }
    }
}
