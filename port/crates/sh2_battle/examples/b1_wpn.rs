//! Developer tool (B1): `b1_wpn <disc dir> <path>` lists the entries of a package file (weapon / model bundles) with the first bytes of each.
use sh2_core::fileio::Disc;
use sh2_formats::{motion::Motion, pkb};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    let b = d.read(&a[2]).expect("read");
    println!("{}: {} bytes", a[2], b.len());
    let Some(pkg) = pkb::parse_package(&b, 0) else { println!("  no package"); return };
    for (i, e) in pkg.entries.iter().enumerate() {
        let body = &b[e.offset.min(b.len())..];
        let extra = if e.kind_str() == "anm" { match Motion::parse(body) { Ok(m) => format!("motion {:?} frames {}", m.name, m.last_frame()), Err(er) => format!("ERR {er}") } } else { format!("{:02x?}", &body[..body.len().min(16)]) };
        println!("  [{i}] {} @{:#x} {}", e.kind_str(), e.offset, extra);
    }
}
