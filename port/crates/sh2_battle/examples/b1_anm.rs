//! Developer tool (B1): `b1_anm <disc dir> <chr no>` lists the packages/motions of a battle character.
use sh2_core::fileio::Disc;
use sh2_formats::{motion::Motion, pkb};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    for ext in ["BCM", "ANM"] {
        let n = a[2].parse::<u32>().unwrap();
        let p = if ext == "ANM" && a.get(3).is_some() { format!("BTLDATA/CHRANM/{n:03}.ANM") } else { format!("BTLDATA/CHR/{n:03}.{ext}") };
        let b = match d.read(&p) { Ok(b) => b, Err(e) => { println!("{p}: {e}"); continue } };
        println!("{p}: {} bytes", b.len());
        let Some(pkg) = pkb::parse_package(&b, 0) else { println!("  no package"); continue };
        for e in &pkg.entries {
            let body = &b[e.offset..];
            let extra = if e.kind_str() == "anm" { match Motion::parse(body) { Ok(m) => format!("motion {:?} frames {} main {}", m.name, m.last_frame(), m.is_main()), Err(er) => format!("PARSE ERR {er}") } } else { String::new() };
            println!("  {} @{:#x} {}", e.kind_str(), e.offset, extra);
        }
    }
}
