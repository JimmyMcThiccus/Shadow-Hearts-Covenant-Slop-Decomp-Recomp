//! dev tool (round 6 MN2): the retail library records (`CMDMENU.MSD` attach 13, MDT demo keys 20 monsters / 19 characters): pointer strings,
//! the `MenuDataModel` camera block (pointer field 3) and the data bytes.  `mn2_library_dump <US disc dir> [ty] [first] [n]`
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::{us_mdt_type, Msd};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let root = Msd::parse(d.read("MENU/DAT/CMDMENU.MSD").expect("file")).unwrap();
    let m = root.attach_scene(13).expect("attach 13").with_mdt_map(us_mdt_type);
    let ty: u16 = a.get(2).and_then(|s| s.parse().ok()).unwrap_or(20);
    let first: usize = a.get(3).and_then(|s| s.parse().ok()).unwrap_or(0);
    let n: usize = a.get(4).and_then(|s| s.parse().ok()).unwrap_or(3);
    let c = m.find_raw(ty).expect("chunk").clone();
    println!("type {ty} ptrs {} stride {:#x} count {} base {}", c.ptr_count, c.stride, c.count, m.mdt_base(ty));
    for i in first..(first + n).min(c.count) {
        let r = m.mdt_rec(ty, i).unwrap();
        println!("--- record {i} data {:02x?}", m.mdt_data(ty, i));
        for k in 0..c.ptr_count as usize {
            let p = u32::from_le_bytes([r[k * 4], r[k * 4 + 1], r[k * 4 + 2], r[k * 4 + 3]]);
            let s = m.mdt_str(ty, i, k);
            let raw = m.mdt_ptr_bytes(ty, i, k, 16);
            println!("  [{k}] ptr {p:#x} {:?} raw {:02x?}", sh2_menu::sjis::decode(&s[..s.len().min(60)]), raw);
        }
    }
}
