use sh2_battle::{bridge, data::BattleData};
use sh2_core::fileio::Disc;
use sh2_menu::session::GameSession;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let data = BattleData::load(&d).unwrap();
    let mut s = GameSession::default();
    s.new_game("AP_00_U");
    bridge::init_new_game(&data, &mut s);
    for pc in s.battle_party() {
        let r = s.save.btl.pc(pc as usize).unwrap();
        println!("pc {pc} lv {} hp {} mp {} sp {} wpn {} arm {} acc {:?} skills {:?} misc16 {:04x} raw[0x3a..0x60]={:02x?}", r.level, r.hp_max, r.mp_max, r.sp_max, r.weapon, r.armor, r.accessories, r.skills, r.misc16, &r.raw[0x3a..0x60]);
        println!("    name {}", s.pc_name(pc));
    }
    println!("skill bits: {:02x?}", &s.save.btl.data[0xaa4..0xaa4 + 16]);
}
