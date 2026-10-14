//! Build retail `BTL0` party records the way the game's `PCInit` does (`bridge::ensure_pc`), for poking into a live game:
//! `us_pc_records [ids...]` prints, per PC id, the 0xc0-byte record (at `BTL0 + 0x3c + id * 0xc0`) and its 0x10-byte ability slots
//! (`BTL0 + 0x10bc + id * 0x10`) as hex, plus the PC / weapon / armour / accessory name lists.  `SH2_US_DISC_DIR` must be set.
use sh2_battle::{bridge, data::BattleData, pkb_compat::PkbDisc};
use sh2_menu::save::retail_btl;
use sh2_menu::session::GameSession;

fn hex(b: &[u8]) -> String {
    b.iter().map(|x| format!("{x:02x}")).collect()
}

fn main() {
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let ids: Vec<u8> = std::env::args().skip(1).filter_map(|a| u8::from_str_radix(a.trim_start_matches("0x"), if a.starts_with("0x") { 16 } else { 10 }).ok()).collect();
    let mut s = GameSession::default();
    s.new_game("AP_02_U");
    let tbl = bridge::level_table(&data);
    for &id in &ids {
        bridge::ensure_pc(&data, &mut s, id, &tbl);
    }
    s.save.btl.sync_to_retail();
    let r = &s.save.btl.retail;
    for &id in &ids {
        let o = retail_btl::PC_BASE + id as usize * 0xc0;
        let k = retail_btl::SKILL_SLOTS + id as usize * 0x10;
        println!("pc {id:#x} {}", s.pc_name(id));
        println!("  rec {}", hex(&r[o..o + 0xc0]));
        println!("  slots {}", hex(&r[k..k + 0x10]));
    }
    if let Some(us) = data.us() {
        for (kind, label, n) in [(3u8, "weapon", 0x60usize), (4, "armor", 0x30), (5, "accessory", 0x60)] {
            let names: Vec<String> = (0..n).filter_map(|i| us.text(kind, i, -1).filter(|t| !t.is_empty()).map(|t| format!("{i:#x}={t}"))).collect();
            println!("{label}: {}", names.join(", "));
        }
    }
    for pc in 0..12 {
        println!("pcname {pc:#x} {:?}", data.name(3, pc));
    }
}
