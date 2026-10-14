use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};
fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    for pc in 0..14usize {
        if let Some(r) = data.dat.record(sh2_battle::data::SEC_PC_INIT[3], pc, 0x1c) {
            println!("pc {pc:2}: {:02x?}", r);
        }
    }
}
