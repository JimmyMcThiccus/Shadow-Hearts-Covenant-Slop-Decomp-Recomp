//! (round 5 MN) Survey of the menu-opening ops in the map scripts: `SpecialMenu` (0x7f) and retail `InvokeCmdScene` (0x4d), with their constant
//! arguments and the maps that use them.  `mn_menu_ops <disc dir> [ops, e.g. 4d,7f]`
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;
use std::collections::BTreeMap;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let disc = sh2_core::fileio::Disc::open(&a[1]).expect("disc");
    let ops: Vec<u8> = a.get(2).map(|s| s.split(',').map(|v| u8::from_str_radix(v.trim_start_matches("0x"), 16).unwrap()).collect()).unwrap_or(vec![0x4d, 0x7f]);
    let mut seen: BTreeMap<String, Vec<String>> = BTreeMap::new();
    for (dir, files) in disc.listing() {
        let _ = &dir;
        for (name, _) in files {
            if !name.contains("/MPS/") || !name.ends_with(".MSC") { continue; }
            let Some(bytes) = disc.read_opt(&name) else { eprintln!("no {name}"); continue };
            let Ok(img) = ScriptImage::parse(&bytes) else { continue };
            for c in scan_calls(&img) {
                if c.ex == 0xc2 && ops.contains(&c.sub) {
                    let args: Vec<String> = c.args.iter().map(|a| a.map(|v| format!("{v:#x}")).unwrap_or("?".into())).collect();
                    seen.entry(format!("{:02x}({})", c.sub, args.join(", "))).or_default().push(name.rsplit('/').next().unwrap_or("").trim_end_matches(".MSC").to_string());
                }
            }
        }
    }
    for (k, m) in seen {
        let mut m2 = m.clone();
        m2.dedup();
        println!("{k} x{} {:?}", m.len(), &m2[..m2.len().min(12)]);
    }
}
