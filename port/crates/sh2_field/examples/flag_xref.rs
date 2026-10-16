//! Static cross-reference of script flags: which map scripts set / clear / test which flag (`setFlag` 0xa4, `clrFlag` 0xa5, `chkFlag` 0xa6
//! with a constant argument), with the event ids whose function contains the site.
//! `flag_xref [--us] [--flags 0x4c,0x4d] [--map MAP] [--set-only]`
use sh2_field::pkb_compat::PkbSet;
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let get = |k: &str| a.iter().position(|x| x == k).and_then(|i| a.get(i + 1)).cloned();
    let p = |v: &str| if let Some(h) = v.strip_prefix("0x") { u32::from_str_radix(h, 16).unwrap() } else { v.parse().unwrap() };
    let flags: Option<Vec<u32>> = get("--flags").map(|s| s.split(',').map(p).collect());
    let regs: Option<Vec<u32>> = get("--regs").map(|s| s.split(',').map(p).collect());
    // `--regb 0x78`: byte registers 0..0xff addressed with the short form `&regb[i]` (0x10 i)
    let regb: Option<Vec<u32>> = get("--regb").map(|s| s.split(',').map(p).collect());
    let only = get("--map");
    let set_only = a.iter().any(|x| x == "--set-only");
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let list = set.list_dir_while("FIELD/MPS", |_| true).unwrap();
    for e in list.iter().filter(|e| e.name.ends_with(".MSC")) {
        let map = e.name.trim_end_matches(".MSC");
        if only.as_deref().map(|m| m != map).unwrap_or(false) {
            continue;
        }
        let Some(b) = set.read(&format!("FIELD/MPS/{}", e.name)) else { continue };
        let Ok(img) = ScriptImage::parse(&b) else { continue };
        if let Some(rb) = &regb {
            let code = &img.code;
            for i in 0..code.len().saturating_sub(2) {
                if code[i] != 0x10 || !rb.contains(&(code[i + 1] as u32)) {
                    continue;
                }
                let tail: Vec<String> = code[i + 2..(i + 8).min(code.len())].iter().map(|b| format!("{b:02x}")).collect();
                let kind = if matches!(code.get(i + 2), Some(0x20) | Some(0x21)) { "read" } else { "write?" };
                if set_only && kind == "read" {
                    continue;
                }
                println!("{map} regb {:#x} {kind} at {i:#06x} next {}", code[i + 1], tail.join(" "));
            }
            continue;
        }
        if let Some(regs) = &regs {
            // typed register byte accesses: `regT lo hi` (0x14) and the operator that follows (byte scan, may have false hits)
            let code = &img.code;
            for i in 0..code.len().saturating_sub(3) {
                if code[i] != 0x14 {
                    continue;
                }
                let r = u16::from_le_bytes([code[i + 1], code[i + 2]]) as u32;
                if !regs.contains(&r) {
                    continue;
                }
                // the next operator byte after the value pushes: st8 0x26 = write, opassign 0x80..0x89, ld 0x20/0x21 = read
                let tail: Vec<String> = code[i + 3..(i + 9).min(code.len())].iter().map(|b| format!("{b:02x}")).collect();
                let kind = match code.get(i + 3) {
                    Some(0x20) | Some(0x21) => "read",
                    _ => "write?",
                };
                if set_only && kind == "read" {
                    continue;
                }
                println!("{map} reg {r:#x} {kind} at {i:#06x} next {}", tail.join(" "));
            }
            continue;
        }
        for c in scan_calls(&img) {
            let kind = match c.ex {
                0xa4 => "set",
                0xa5 => "clr",
                0xa6 => "chk",
                _ => continue,
            };
            if set_only && kind == "chk" {
                continue;
            }
            let Some(Some(f)) = c.args.first().copied() else { continue };
            if flags.as_ref().map(|fl| !fl.contains(&f)).unwrap_or(false) {
                continue;
            }
            let evs: Vec<String> = img
                .events
                .iter()
                .flat_map(|s| s.entries.iter().filter(|x| x.func as u32 == c.func).map(move |x| format!("k{}:{}", s.kind, x.id)))
                .collect();
            let start = if c.func == img.hdr.start_func as u32 { " start" } else { "" };
            println!("{map} {kind} {f:#x} at {:#06x} func {:#x}{start} {}", c.ip, c.func, evs.join(","));
        }
    }
}
