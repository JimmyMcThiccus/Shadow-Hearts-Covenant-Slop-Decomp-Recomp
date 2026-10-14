//! Corpus survey: count every `CScriptEx` call site (op = ex.sub) in the map scripts of a disc (static scan, `sh2_script::disasm`).
//! `cargo run -p sh2_field --example script_survey -- [--us] [--args OP]`
use sh2_field::pkb_compat::PkbSet;
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;
use std::collections::BTreeMap;

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let var = if a.iter().any(|x| x == "--us") { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" };
    let dir = std::env::var(var).expect(var);
    let want_args: Option<u8> = a.iter().position(|x| x == "--args").and_then(|i| a.get(i + 1)).map(|s| u8::from_str_radix(s.trim_start_matches("0x"), 16).unwrap());
    let list_map: Option<String> = a.iter().position(|x| x == "--list").and_then(|i| a.get(i + 1)).cloned();
    let set = PkbSet::open(&dir).unwrap();
    let list = set.list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC")).unwrap();
    let mut counts: BTreeMap<(u8, u8), (usize, usize)> = BTreeMap::new();
    let mut nargs: BTreeMap<(u8, u8), std::collections::BTreeSet<u8>> = BTreeMap::new();
    let mut files = 0;
    for e in list.iter().filter(|e| e.name.ends_with(".MSC")) {
        let Some(bytes) = set.read(&format!("FIELD/MPS/{}", e.name)) else { continue };
        let img = match ScriptImage::parse(&bytes) {
            Ok(i) => i,
            Err(err) => {
                println!("{}: {err:?}", e.name);
                continue;
            }
        };
        files += 1;
        if a.iter().any(|x| x == "--codes") {
            let mut cnt = std::collections::BTreeMap::<String, usize>::new();
            for st in img.data.split(|b| *b == 0) {
                let mut i = 0;
                while i + 1 < st.len() {
                    if st[i] == b'%' && st[i + 1].is_ascii_alphabetic() {
                        let mut j = i + 2;
                        while j < st.len() && st[j].is_ascii_digit() && j < i + 5 { j += 1; }
                        *cnt.entry(String::from_utf8_lossy(&st[i..j]).to_string()).or_default() += 1;
                        i = j;
                    } else if st[i] == b'$' {
                        *cnt.entry("$".into()).or_default() += 1;
                        i += 1;
                    } else { i += 1; }
                }
            }
            println!("CODES {} {:?}", e.name, cnt);
        }
        if let Some(m) = &list_map {
            if e.name.starts_with(m.as_str()) {
                for c in scan_calls(&img) {
                    let name = sh2_script::opcodes::FIELD_SUBOPS.iter().find(|(o, _)| *o == c.sub).map(|(_, n)| *n).unwrap_or("?");
                    let args: Vec<String> = c.args.iter().map(|a| match a { Some(v) if *v & 0xf000_0000 == sh2_script::memory::SEG_DATA => { let o = (*v & 0xffff) as usize; let s: Vec<u8> = img.data.get(o..).unwrap_or(&[]).iter().take_while(|b| **b != 0).take(24).cloned().collect(); if s.iter().all(|b| *b >= 0x20 && *b < 0x7f) && !s.is_empty() { format!("\"{}\"", String::from_utf8_lossy(&s)) } else { format!("d{:x}", o) } } Some(v) => format!("{}", *v as i32), None => "?".into() }).collect();
                    if c.ex == 0xc2 { println!("f{:04x} @{:04x} {:02x} {:<14} {}", c.func, c.ip, c.sub, name, args.join(", ")); } else { println!("f{:04x} @{:04x} ifc {:02x} {}", c.func, c.ip, c.ex, args.join(", ")); }
                }
            }
        }
        let mut seen = std::collections::HashSet::new();
        for c in scan_calls(&img) {
            let k = (c.ex, c.sub);
            let ent = counts.entry(k).or_default();
            ent.0 += 1;
            if seen.insert(k) {
                ent.1 += 1;
            }
            nargs.entry(k).or_default().insert(c.nargs);
            if Some(c.sub) == want_args && c.ex == 0xc2 {
                println!("{} @{:04x} n={} {:x?}", e.name, c.ip, c.nargs, c.args);
            }
        }
    }
    println!("scripts: {files}");
    for ((ex, sub), (n, f)) in &counts {
        println!("{ex:02x}.{sub:02x} sites {n:5} scripts {f:3} nargs {:?}", nargs[&(*ex, *sub)]);
    }
}
