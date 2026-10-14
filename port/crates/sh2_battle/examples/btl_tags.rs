use sh2_battle::data::Container;
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    let c = Container::parse(d.read(&a[2]).expect("read")).expect("parse");
    for (i, s) in c.sections.iter().enumerate() {
        println!("{i:2} {:?} len {} (0x{:x})", std::str::from_utf8(&s.tag).unwrap_or("?"), s.len, s.len);
    }
}
