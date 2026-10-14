//! Debug: find files of the disc whose bytes contain a pattern: `grep_disc [--us] PATTERN [path-prefix] [--dump OUT]`
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let dump = a.iter().position(|x| x == "--dump").map(|i| a[i + 1].clone());
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let pat = v[0].as_bytes().to_vec();
    let prefix = v.get(1).map(|s| s.as_str()).filter(|s| Some(s.to_string()) != dump).unwrap_or("");
    let d = Disc::open(&dir).unwrap();
    let mut paths = Vec::new();
    d.info().walk(|p, f| { if p.starts_with(prefix) && f.size < 64 << 20 { paths.push(p.to_string()); } });
    for p in paths {
        let Some(b) = d.read_opt(&p) else { continue };
        let mut from = 0;
        while let Some(i) = b[from..].windows(pat.len()).position(|w| w == &pat[..]) {
            println!("{p} @ {:#x} (size {})", from + i, b.len());
            if let Some(o) = &dump { std::fs::write(o, &b).unwrap(); }
            from += i + 1;
            if from > b.len() { break; }
        }
    }
}
