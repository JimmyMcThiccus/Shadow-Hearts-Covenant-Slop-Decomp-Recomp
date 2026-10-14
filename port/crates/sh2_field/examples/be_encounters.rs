//! Round 5 BE (read-only): every battle the retail field can start -- the random-encounter table (`MONSET` chunk) of every `FIELD/MPS/*.MPS`
//! and the scripted battle table (`BBTL` of `FIELD/FIELD.DAT`) -- with the battle background (`SetFieldData(7)` / BBTL word 0) checked against
//! `BTLDATA/BBG/%03d.BBG` and the monster set against the `MONSET` table.  `cargo run -p sh2_field --example be_encounters` (US disc).
//! Output: `enc MAP rate bg bgm set weight` / `bbtl i bg bgm set boss` rows, then a summary.
use std::collections::{BTreeMap, BTreeSet};

use sh2_field::mps::Mps;
use sh2_field::pkb_compat::PkbSet;

fn main() {
    let dir = std::env::var("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let set = PkbSet::open(&dir).unwrap();
    let disc = sh2_core::fileio::Disc::open(&dir).unwrap();
    let has = |p: &str| disc.info().search_file(p).is_some();
    let nset = {
        let raw = disc.read("COMMON/SSHDAT.NA").unwrap();
        let rf = sh2_core::regdat::RegFile::new(&raw);
        rf.size(6) / 0x14
    };
    let mut maps = vec![];
    for (_c, files) in disc.listing() {
        for (p, _) in files {
            if p.starts_with("FIELD/MPS/") && p.ends_with(".MPS") {
                maps.push(p);
            }
        }
    }
    maps.sort();
    let mut used_sets: BTreeMap<u16, Vec<String>> = BTreeMap::new();
    let mut bgs: BTreeSet<u16> = BTreeSet::new();
    let mut problems = vec![];
    let mut with_enc = 0;
    for p in &maps {
        let name = p.trim_start_matches("FIELD/MPS/").trim_end_matches(".MPS").to_string();
        let Some(raw) = set.read(p) else { continue };
        let Ok(m) = Mps::parse(raw) else { continue };
        let Ok(Some(ms)) = m.monster_sets() else { continue };
        if ms.entries.is_empty() {
            continue;
        }
        with_enc += 1;
        // header: +0x16 = SetFieldData(6) = BGM, +0x18 = SetFieldData(7) = battle background
        let (bgm, bg) = (ms.field_data6, ms.field_data7);
        bgs.insert(bg);
        if !has(&format!("BTLDATA/BBG/{bg:03}.BBG")) {
            problems.push(format!("{name}: BBG {bg} missing"));
        }
        for (s, w) in &ms.entries {
            println!("enc\t{name}\t{}\t{bg}\t{bgm}\t{s}\t{w}", ms.encounter_rate);
            used_sets.entry(*s).or_default().push(name.clone());
            if *s as usize >= nset {
                problems.push(format!("{name}: MONSET {s} out of range"));
            }
        }
    }
    let fdat = disc.read("FIELD/FIELD.DAT").unwrap();
    let mut t = sh2_field::host::FieldTables::default();
    t.from_field_t(&fdat);
    for (i, r) in t.bbtl.iter().enumerate() {
        let w = |o: usize| u16::from_le_bytes([r[o], r[o + 1]]);
        println!("bbtl\t{i}\t{}\t{}\t{}\t{}", w(0), w(2), w(4), r[6]);
        bgs.insert(w(0));
        used_sets.entry(w(4)).or_default().push(format!("BBTL{i}"));
        if !has(&format!("BTLDATA/BBG/{:03}.BBG", w(0))) {
            problems.push(format!("BBTL {i}: BBG {} missing", w(0)));
        }
        if w(4) as usize >= nset {
            problems.push(format!("BBTL {i}: MONSET {} out of range", w(4)));
        }
    }
    let unused: Vec<usize> = (0..nset).filter(|s| !used_sets.contains_key(&(*s as u16))).collect();
    eprintln!("{} maps, {with_enc} with random encounters, {} BBTL rows; {} distinct MONSETs used of {nset}; backgrounds {:?}", maps.len(), t.bbtl.len(), used_sets.len(), bgs);
    eprintln!("MONSETs not referenced by an encounter table or BBTL (pit fights / InvokeBattle literals / debug): {unused:?}");
    eprintln!("problems: {problems:#?}");
}
