//! dev tool: chunk table of an attach file used as `.MDT` (`mdt_types <disc dir> <path> <attach>`): raw type, record count, stride, first strings.
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let root = Msd::parse(d.read(&a[2]).expect("file")).unwrap();
    let m = root.attach_scene(a[3].parse().unwrap()).expect("attach scene");
    for c in &m.chunks {
        let first = m.mdt_str(c.raw_type, 0, 0);
        let second = m.mdt_str(c.raw_type, 1, 1);
        println!("type {:3} ptrs {} stride {:#5x} count {:4}  [0]={:?}  [1].1={:?}", c.raw_type, c.ptr_count, c.stride, c.count,
            String::from_utf8_lossy(&first[..first.len().min(36)]), String::from_utf8_lossy(&second[..second.len().min(36)]));
    }
}
