//! dev tool (round 6 MN2): US text kinds 0x26 (ring items) and 8 (key items) with their indices.
fn main() {
    let d = sh2_battle::pkb_compat::PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let data = sh2_battle::data::BattleData::load_us(&d).unwrap();
    let us = data.us().unwrap();
    for kind in [7u8, 0xc, 0xf, 0x10, 0x11] {
        for i in 0..5 {
            println!("kind {kind:#x} [{i}] {:?}", us.text(kind, i, -1));
        }
    }
}
