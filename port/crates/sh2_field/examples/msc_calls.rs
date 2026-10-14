//! Static call sites of one map script grouped by function, with the event ids that reach each function.
//! `msc_calls [--us] MAP [--ops 0x23,0x7a]` (filter by op id)
use sh2_field::pkb_compat::PkbSet;
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let map = a.iter().find(|x| !x.starts_with("--") && x.chars().next().map(|c| c.is_ascii_uppercase()).unwrap_or(false)).cloned().unwrap();
    let filter: Option<Vec<u8>> = a.iter().position(|x| x == "--ops").and_then(|i| a.get(i + 1)).map(|s| s.split(',').map(|v| u8::from_str_radix(v.trim_start_matches("0x"), 16).unwrap()).collect());
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let b = set.read(&format!("FIELD/MPS/{map}.MSC")).unwrap();
    let img = ScriptImage::parse(&b).unwrap();
    println!("start func {:#x} end func {:#x}", img.hdr.start_func, img.hdr.end_func);
    for s in &img.events {
        for e in &s.entries {
            println!("event kind {} id {} -> func {:#x}", s.kind, e.id, e.func);
        }
    }
    let mut last = u32::MAX;
    for c in scan_calls(&img) {
        if let Some(f) = &filter {
            if c.ex != 0xc2 || !f.contains(&c.sub) {
                continue;
            }
        }
        if c.func != last {
            println!("-- func {:#x}", c.func);
            last = c.func;
        }
        let args: Vec<String> = c.args.iter().map(|a| a.map(|v| format!("{v:#x}")).unwrap_or("?".into())).collect();
        println!("  {:#06x}: {:02x}.{:02x}({})", c.ip, c.ex, c.sub, args.join(", "));
    }
}
