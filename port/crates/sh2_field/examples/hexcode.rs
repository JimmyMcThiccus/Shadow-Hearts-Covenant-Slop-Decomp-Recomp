use sh2_field::pkb_compat::PkbSet;
use sh2_script::image::ScriptImage;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let img = ScriptImage::parse(&set.read(&format!("FIELD/MPS/{}.MSC", v[0])).unwrap()).unwrap();
    let o = usize::from_str_radix(v[1].trim_start_matches("0x"), 16).unwrap();
    let n = v.get(2).and_then(|s| s.parse().ok()).unwrap_or(48);
    for (i, b) in img.code[o..o + n].iter().enumerate() {
        print!("{:02x}{}", b, if i % 16 == 15 { "\n" } else { " " });
    }
    println!();
}
