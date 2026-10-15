//! dev tool (round 6 MN2): every chunk of the retail menu data table (CMDMENU.MSD attach 13): raw type, pointers, stride, count.
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let root = Msd::parse(d.read("MENU/DAT/CMDMENU.MSD").expect("file")).unwrap();
    let m = root.attach_scene(13).expect("attach 13");
    for c in &m.chunks {
        println!("type {:3} ptrs {:2} stride {:#5x} count {:4} @{:#x}", c.raw_type, c.ptr_count, c.stride, c.count, c.offset);
    }
    if let Some(ty) = a.get(2).and_then(|s| s.parse::<u16>().ok()) {
        let c = m.find_raw(ty).unwrap();
        for i in 0..c.count.min(20) {
            let r = m.mdt_rec(ty, i).unwrap();
            print!("rec {i:2}: {:02x?}", &r[..r.len().min(48)]);
            for k in 0..c.ptr_count as usize {
                let p = u32::from_le_bytes([r[k * 4], r[k * 4 + 1], r[k * 4 + 2], r[k * 4 + 3]]);
                print!(" | k{k} {:02x?}", m.mdt_ptr_bytes(ty, i, k, 16));
                let _ = p;
            }
            println!();
        }
    }
}
