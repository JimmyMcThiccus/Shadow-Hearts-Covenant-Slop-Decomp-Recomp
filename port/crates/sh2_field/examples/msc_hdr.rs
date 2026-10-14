//! Print the header of map scripts: `msc_hdr [--us] MAP..`
use sh2_field::pkb_compat::PkbSet;
use sh2_script::image::ScriptImage;
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    for m in a.iter().filter(|x| !x.starts_with("--")) {
        let img = ScriptImage::parse(&set.read(&format!("FIELD/MPS/{m}.MSC")).unwrap()).unwrap();
        println!("{m}: {:?} code {:#x} data {:#x}", img.hdr, img.code.len(), img.data.len());
    }
}
