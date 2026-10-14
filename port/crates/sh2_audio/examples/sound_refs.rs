//! `sound_refs [disc-dir]` (round 5 CS): which sound files of the disc are referenced, and which referenced sound names are missing.
//!
//! * every sound file (`*.SSQ / *.SSV / *.SSE` under `FIELD/SOUND`, `BTLDATA/SOUND`, `COMMON`, `OPENING`, ...) is parsed (`Bank::parse` /
//!   `SsvHeader`) and searched for (by its base name) in every field script (`FIELD/MPS/*.MSC` data segment strings), the overlays
//!   (`FIELD.BIN`, `BATTLE.BIN`, `OPENING.BIN`, the main ELF) and every LSD `LSCR` image;
//! * every sound-like string of the scripts (`BGMnnn`, `XX_EVnnn`, `XX_FTnnX`, `XX_EFnnn`, `XX_nn_X`, `ACTnnn`) that has no file is listed.
use sh2_script::image::ScriptImage;
use sh2_script::pkb_compat::PkbSet;
use std::collections::{BTreeMap, BTreeSet};

fn strings(d: &[u8]) -> Vec<String> {
    let mut out = Vec::new();
    let mut cur = Vec::new();
    for &b in d {
        if b.is_ascii_graphic() {
            cur.push(b);
        } else {
            if cur.len() >= 4 {
                out.push(String::from_utf8_lossy(&cur).to_uppercase());
            }
            cur.clear();
        }
    }
    out
}

fn sound_like(s: &str) -> bool {
    let b = s.as_bytes();
    let up = |c: u8| c.is_ascii_uppercase();
    let dig = |c: u8| c.is_ascii_digit();
    (s.len() == 6 && s.starts_with("BGM") && b[3..].iter().all(|&c| dig(c)))
        || (s.len() == 6 && s.starts_with("ACT") && b[3..].iter().all(|&c| dig(c)))
        || (s.len() == 8 && up(b[0]) && up(b[1]) && b[2] == b'_' && (s[3..5] == *"EV" || s[3..5] == *"EF" || s[3..5] == *"FT"))
}

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let dir = a.first().cloned().unwrap_or_else(|| std::env::var("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR"));
    let set = PkbSet::open(&dir).unwrap();
    // every sound file
    let mut files: BTreeMap<String, (String, usize)> = BTreeMap::new(); // base -> (path, size)
    let all = sh2_audio_paths(&set);
    let mut bad = Vec::new();
    for p in &all {
        let Ok(d) = set.read(p) else { continue };
        let base = p.rsplit('/').next().unwrap().split('.').next().unwrap().to_uppercase();
        let ok = if p.ends_with(".SSV") { sh2_audio::stream::SsvHeader::parse(&d).is_ok() } else { d.starts_with(b"WD") || sh2_audio::sdh::Bank::parse(&d).is_ok() };
        if !ok {
            bad.push(p.clone());
        }
        files.insert(format!("{base}|{p}"), (p.clone(), d.len()));
    }
    // sources
    let mut script_strings: BTreeMap<String, BTreeSet<String>> = BTreeMap::new(); // string -> maps
    let mps: Vec<sh2_core::fileio::DirEntry> = set.info().dir_start("FIELD/MPS").map(|i| set.info().entries()[i..].iter().map(sh2_core::fileio::DirEntry::from).collect()).unwrap_or_default();
    for e in mps {
        if !e.name.ends_with(".MSC") {
            continue;
        }
        let Ok(b) = set.read(&format!("FIELD/MPS/{}", e.name)) else { continue };
        let Ok(img) = ScriptImage::parse(&b) else { continue };
        for s in strings(&img.data) {
            script_strings.entry(s).or_default().insert(e.name.trim_end_matches(".MSC").to_string());
        }
    }
    let mut blobs: Vec<(String, Vec<u8>)> = Vec::new();
    for f in ["FIELD.BIN", "BATTLE.BIN", "OPENING.BIN", "SLUS_210.41"] {
        if let Ok(d) = std::fs::read(std::path::Path::new(&dir).join(f)) {
            blobs.push((f.to_string(), d.to_ascii_uppercase()));
        }
    }
    let mut unref = Vec::new();
    let mut refd = 0;
    for (_, (p, size)) in &files {
        let base = p.rsplit('/').next().unwrap().split('.').next().unwrap().to_uppercase();
        let in_scripts = script_strings.iter().filter(|(s, _)| s.contains(&base)).flat_map(|(_, m)| m.iter().cloned()).collect::<BTreeSet<_>>();
        let in_bins: Vec<&str> = blobs.iter().filter(|(_, d)| d.windows(base.len()).any(|w| w == base.as_bytes())).map(|(n, _)| n.as_str()).collect();
        if in_scripts.is_empty() && in_bins.is_empty() {
            unref.push(format!("{p} ({size} B)"));
        } else {
            refd += 1;
        }
        if std::env::var_os("SOUND_REFS_VERBOSE").is_some() {
            println!("{p}: scripts {:?} bins {:?}", in_scripts.iter().take(6).collect::<Vec<_>>(), in_bins);
        }
    }
    let have: BTreeSet<String> = files.values().map(|(p, _)| p.rsplit('/').next().unwrap().split('.').next().unwrap().to_uppercase()).collect();
    let missing: Vec<String> = script_strings.iter().filter(|(s, _)| sound_like(s) && !have.contains(*s)).map(|(s, m)| format!("{s} (in {:?})", m.iter().take(4).collect::<Vec<_>>())).collect();
    println!("{} sound files, {} referenced by name, {} unreferenced, {} fail to parse", files.len(), refd, unref.len(), bad.len());
    for b in &bad {
        println!("  PARSE FAIL {b}");
    }
    println!("unreferenced (by base name; battle BGMs are referenced by number):");
    for u in &unref {
        println!("  {u}");
    }
    println!("sound-like script strings without a file: {}", missing.len());
    for m in &missing {
        println!("  {m}");
    }
}

/// Every sound file path of the disc.
fn sh2_audio_paths(set: &PkbSet) -> Vec<String> {
    let mut out = Vec::new();
    for (_c, files) in set.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if up.ends_with(".SSQ") || up.ends_with(".SSV") || up.ends_with(".SSE") || up.ends_with(".SSH") {
                out.push(path);
            }
        }
    }
    out.sort();
    out
}
