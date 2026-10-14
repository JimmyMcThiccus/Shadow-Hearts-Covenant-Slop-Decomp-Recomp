//! List the retail crests (`ActionTables::crests`): id, name, flags and the crest-magic (`MC_P`) entries each carries.
use sh2_battle::{actions::ActionTables, data::BattleData, pkb_compat::PkbDisc};
fn main() {
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let t = ActionTables::load(&data);
    for (i, c) in t.crests.iter().enumerate() {
        let magic: Vec<String> = c.magic.iter().filter(|&&m| m >= 0).map(|&m| format!("{m}:{}", t.magic_name(m as usize))).collect();
        println!("crest {i:#04x} id {} flags {:#x} magic {:?}", c.id, c.flags, magic);
    }
}
