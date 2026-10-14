//! (round 5 MN) retail help tables: categories (MDT 18) -> entry id lists, entries (MDT 19): `mn_help_dump <disc dir>`
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let root = Msd::parse(d.read("MENU/DAT/CMDMENU.MSD").unwrap()).unwrap();
    let m = root.attach_scene(13).unwrap();
    for i in 0..m.mdt_count(18) {
        let data = m.mdt_data(18, i);
        let n = i16::from_le_bytes([data[0], data[1]]) as usize;
        let ids: Vec<i16> = m.mdt_ptr_bytes(18, i, 1, n * 2).chunks(2).map(|c| i16::from_le_bytes([c[0], c[1]])).collect();
        println!("cat {i} {:?} n {n} ids {ids:?}", sh2_menu::sjis::decode(m.mdt_str(18, i, 0)));
    }
    let mut codes = std::collections::BTreeMap::new();
    for i in 0..m.mdt_count(19) {
        for k in 1..7 {
            let t = sh2_menu::sjis::decode(m.mdt_str(19, i, k));
            let mut it = t.split("%i").skip(1);
            for part in &mut it {
                let n: String = part.chars().take_while(|c| c.is_ascii_digit()).collect();
                *codes.entry(n.parse::<u32>().unwrap_or(999)).or_insert(0) += 1;
            }
        }
    }
    println!("icon codes {codes:?}");
    for i in (0..m.mdt_count(19)).filter(|&i| i < 12 || std::env::args().any(|a| a == i.to_string())) {
        println!("entry {i} {:?} data {:02x?} p1 {:?}", sh2_menu::sjis::decode(m.mdt_str(19, i, 0)), m.mdt_data(19, i), sh2_menu::sjis::decode(&m.mdt_str(19, i, 1)[..m.mdt_str(19, i, 1).len().min(60)]));
    }
}
#[allow(dead_code)]
fn icon_codes() {}
