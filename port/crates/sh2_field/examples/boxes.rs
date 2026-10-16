use sh2_field::mps::Mps;
use sh2_field::pkb_compat::PkbSet;
fn main() {
    // `boxes MAP [--us]`: the event boxes and entry points of a map's MPS (`--us`: the US disc, `SH2_US_DISC_DIR`)
    let map = std::env::args().nth(1).unwrap();
    let set = if std::env::args().any(|a| a == "--us") { PkbSet::open(std::env::var("SH2_US_DISC_DIR").unwrap()).unwrap() } else { PkbSet::from_env().unwrap() };
    let m = Mps::parse(set.read(&format!("FIELD/MPS/{map}.MPS")).unwrap()).unwrap();
    for (i, b) in m.event_boxes().unwrap().iter().enumerate() {
        println!("box {i}: id {} group {} kind {} flags {:#04x} center {:?}", b.id, b.group, b.kind, b.flags, b.center);
    }
    for (i, e) in m.entry_points().unwrap().iter().enumerate() {
        println!("entry {i}: {:?} dir {}", e.pos, e.dir);
    }
}
