//! Write a map script's relocated code / data segments to files: `msc_dump [--us] MAP OUTDIR` -> OUTDIR/MAP.code, OUTDIR/MAP.data
use sh2_field::pkb_compat::PkbSet;
use sh2_script::image::ScriptImage;
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let pos: Vec<&String> = a.iter().filter(|x| !x.starts_with("--")).collect();
    let (map, out) = (pos[0], pos[1]);
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let img = ScriptImage::parse(&set.read(&format!("FIELD/MPS/{map}.MSC")).unwrap()).unwrap();
    std::fs::write(format!("{out}/{map}.code"), &img.code).unwrap();
    std::fs::write(format!("{out}/{map}.data"), &img.data).unwrap();
    println!("code {:#x} data {:#x}", img.code.len(), img.data.len());
}
