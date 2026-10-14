//! Survey of `LoadCharacterByName` (op 0x07) names in the map scripts: `byname_survey [--us]`
use sh2_field::pkb_compat::PkbSet;
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;
use std::collections::BTreeMap;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let var = if a.iter().any(|x| x == "--us") { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" };
    let dir = std::env::var(var).expect(var);
    let set = PkbSet::open(&dir).unwrap();
    let list = set.list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC")).unwrap();
    let mut names: BTreeMap<String, Vec<String>> = BTreeMap::new();
    for e in list.iter().filter(|e| e.name.ends_with(".MSC")) {
        let Some(bytes) = set.read(&format!("FIELD/MPS/{}", e.name)) else { continue };
        let Ok(img) = ScriptImage::parse(&bytes) else { continue };
        for c in scan_calls(&img) {
            if c.ex == 0xc2 && c.sub == 7 {
                if let Some(Some(v)) = c.args.get(1) {
                    if *v & 0xf000_0000 == sh2_script::memory::SEG_DATA {
                        let o = (*v & 0xffff) as usize;
                        let s: Vec<u8> = img.data.get(o..).unwrap_or(&[]).iter().take_while(|b| **b != 0).cloned().collect();
                        names.entry(String::from_utf8_lossy(&s).to_string()).or_default().push(e.name.trim_end_matches(".MSC").to_string());
                    }
                }
            }
        }
    }
    for (n, m) in names { let mut m2 = m.clone(); m2.dedup(); println!("{n:?} x{} {:?}", m.len(), &m2[..m2.len().min(6)]); }
}
