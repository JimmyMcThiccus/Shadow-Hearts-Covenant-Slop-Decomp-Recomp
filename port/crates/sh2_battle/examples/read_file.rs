//! Developer tool: `read_file <disc dir> <path> <out file>` extracts one file of the disc archive.
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let b = d.read(&a[2]).unwrap();
    println!("{} bytes", b.len());
    std::fs::write(&a[3], b).unwrap();
}
