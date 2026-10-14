//! Developer tool: dump SSHDAT tables of a disc folder. `btl_dump <disc> <file> <section> [stride]`.
use sh2_battle::data::Container;
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    let c = Container::parse(d.read(&a[2]).expect("read")).expect("parse");
    let sec: usize = a[3].parse().unwrap();
    let stride: usize = a.get(4).map(|s| s.parse().unwrap()).unwrap_or(0);
    let s = c.section(sec);
    println!("section {sec} tag {:?} len {}", std::str::from_utf8(&c.sections[sec].tag), s.len());
    if stride == 0 {
        return;
    }
    for i in 0..s.len() / stride {
        let r = &s[i * stride..(i + 1) * stride];
        print!("{i:3}:");
        for b in r {
            print!(" {b:02x}");
        }
        println!();
    }
}
