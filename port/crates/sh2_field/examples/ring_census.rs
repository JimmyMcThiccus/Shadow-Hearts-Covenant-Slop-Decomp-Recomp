//! Round 6 RG: every field Judgement Ring of a disc -- `SetRing(kind, lap ms, arg, x, y, spec)` (op 0x63) and `RingControl(..)` (op 0x64)
//! call sites over all map scripts.  `ring_census [--us] [--events MAP]`
use sh2_field::pkb_compat::PkbSet;
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let list = set.list_dir_while("FIELD/MPS", |_| true).unwrap();
    let fmt = |v: Option<u32>| v.map(|v| (v as i32).to_string()).unwrap_or_else(|| "?".into());
    // `--events MAP`: the event table of one map (kind, id, entry function)
    if let Some(i) = a.iter().position(|x| x == "--events") {
        let map = &a[i + 1];
        let img = ScriptImage::parse(&set.read(&format!("FIELD/MPS/{map}.MSC")).unwrap()).unwrap();
        for s in &img.events {
            for e in &s.entries {
                println!("kind {} id {} func {}", s.kind, e.id, e.func);
            }
        }
        return;
    }
    let (mut n_set, mut n_ctl) = (0, 0);
    for e in list.iter().filter(|e| e.name.ends_with(".MSC")) {
        let map = e.name.trim_end_matches(".MSC").to_string();
        let Some(b) = set.read(&format!("FIELD/MPS/{}", e.name)) else { continue };
        let Ok(img) = ScriptImage::parse(&b) else { continue };
        for c in scan_calls(&img) {
            if c.ex != 0xc2 || (c.sub != 0x63 && c.sub != 0x64) {
                continue;
            }
            if c.sub == 0x63 {
                n_set += 1;
                let spec = c
                    .args
                    .get(5)
                    .copied()
                    .flatten()
                    .filter(|v| v & sh2_script::memory::SEG_DATA != 0)
                    .map(|v| {
                        let off = (v & 0xffff) as usize;
                        let s: Vec<u8> = img.data.get(off..).unwrap_or(&[]).iter().take_while(|&&b| b != 0).copied().collect();
                        String::from_utf8_lossy(&s).to_string()
                    })
                    .unwrap_or_else(|| "?".into());
                let args: Vec<String> = c.args.iter().take(5).map(|v| fmt(*v)).collect();
                println!("{map:10} func {:5} ip {:5}  SetRing({}, \"{spec}\")", c.func, c.ip, args.join(", "));
            } else {
                n_ctl += 1;
                let args: Vec<String> = c.args.iter().map(|v| fmt(*v)).collect();
                println!("{map:10} func {:5} ip {:5}  RingControl({})", c.func, c.ip, args.join(", "));
            }
        }
    }
    println!("SetRing sites {n_set}, RingControl sites {n_ctl}");
}
