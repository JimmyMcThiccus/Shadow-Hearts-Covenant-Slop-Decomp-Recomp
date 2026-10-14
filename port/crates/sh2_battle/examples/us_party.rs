//! Prints the retail new-game party the port builds (compare with the live game: notes/integration/pine_us_refinement.md).
use sh2_battle::{bridge, data::BattleData, pkb_compat::PkbDisc};
use sh2_menu::session::GameSession;
fn main() {
    let dir = std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let d = PkbDisc::open(dir).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let mut s = GameSession::default();
    s.new_game("OP_00_U");
    bridge::init_new_game_retail(&data, &mut s, 0);
    for pc in s.battle_party() {
        let r = s.save.btl.pc(pc as usize).unwrap();
        println!("pc {pc} {} flags {:02x} kind {} lv {} hp {}/{} mp {}/{} sp {}/{} str {} vit {} int {} pow {} agl {} luc {} s2c {} wpn {} arm {} acc {:?} skills {:?} exp {}", s.pc_name(pc), r.flags, r.kind, r.level, r.hp, r.hp_max, r.mp, r.mp_max, r.sp, r.sp_max, r.str_, r.vit, r.int, r.pow, r.agl, r.luc, r.stat_2c, r.weapon, r.armor, r.accessories, r.skills, r.exp);
        println!("   raw {:02x?}", &r.raw[..]);
    }
    println!("cash {}", s.cash());
    let mut n = 0u32;
    let mut rnd = || { n += 13; n };
    for set in 0..8usize {
        if let Some(setup) = bridge::build_setup(&data, &s, &[5, 0xb], set, &mut rnd) {
            println!("MONSET {set}: formation {:?}", data.monster_set(set).map(|m| (m.formation, m.monsters)));
            for f in &setup.fighters {
                println!("  {:>12} id {:3} hp {}/{} mp {}/{} sp {}/{} agl {} luc {} patk {} satk {} pdef {} sdef {} exp {} cash {}", f.name, f.char_id, f.hp, f.max_hp, f.mp, f.max_mp, f.sp, f.max_sp, f.agl, f.luc, f.patk, f.satk, f.pdef, f.sdef, f.exp, f.cash);
            }
        }
    }
    let b = &s.save.btl;
    for (n, base, len) in [("items", 0xabcusize, 0x40usize), ("weapons", 0xb2c, 0x60), ("armor", 0xb8c, 0x30), ("acc", 0xbbc, 0x50)] {
        let nz: Vec<(usize, u8)> = (0..len).map(|i| (i, b.data[base.min(0) + i])).filter(|x| x.1 != 0).collect();
        let _ = nz;
        let _ = n;
    }
    for i in 0..0x40 { if b.item_count(i) != 0 { println!("item {i} x{}", b.item_count(i)); } }
    for i in 0..0x60 { if b.weapon_count(i) != 0 { println!("weapon {i} x{}", b.weapon_count(i)); } }
    for i in 0..0x30 { if b.armor_count(i) != 0 { println!("armor {i} x{}", b.armor_count(i)); } }
}
