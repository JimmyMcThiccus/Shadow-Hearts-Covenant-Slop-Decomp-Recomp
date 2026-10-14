//! dev tool: strings of record `i` of MDT chunk `ty` (`mdt_dump <disc> <path> <attach> <ty> [first [n]]`)
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let root = Msd::parse(d.read(&a[2]).expect("file")).unwrap();
    let m = root.attach_scene(a[3].parse().unwrap()).expect("attach scene");
    let ty: u16 = a[4].parse().unwrap();
    let first: usize = a.get(5).and_then(|s| s.parse().ok()).unwrap_or(0);
    let n: usize = a.get(6).and_then(|s| s.parse().ok()).unwrap_or(2);
    let c = m.find_raw(ty).expect("chunk");
    println!("type {ty} ptrs {} stride {:#x} count {}", c.ptr_count, c.stride, c.count);
    for i in first..(first + n).min(c.count) {
        println!("--- record {i} data {:02x?}", m.mdt_data(ty, i));
        for k in 0..c.ptr_count as usize {
            let s = m.mdt_str(ty, i, k);
            println!("  [{k}] {:?}", sh2_menu::sjis::decode(&s[..s.len().min(160)]));
        }
    }
}
