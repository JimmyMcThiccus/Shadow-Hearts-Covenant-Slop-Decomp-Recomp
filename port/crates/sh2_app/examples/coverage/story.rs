//! Story progression: built from the field check's rows (the map jumps / world-map requests the scripts made at run time), the static map
//! references of every script (map names in the `.MSC` data), the retail world-map point table (`FIELD.BIN`) and the story flags of the
//! debug menu's Flag management pages (notes/integration/debug_menu.md).
//!
//! * `map X`: reachable from `OP_00_U` through run-time edges (ok), only through static references (untested: needs story flags the
//!   headless run does not set), or not referenced at all (untested: debug / unused map).
//! * `jump A -> B:e`: every run-time jump target exists on the disc and has entry point `e`.
//! * `world map point N`: the point's map exists and its field check is not `fails`.
//! * `chapter ...`: some map script sets the chapter's clear flag (`setFlag n` with a constant, static scan) and that map is reachable.

use super::common::*;
use sh2_field::pkb_compat::PkbSet;
use std::collections::{BTreeMap, BTreeSet, VecDeque};

/// (flag, name) of the Flag management pages 1-4 (debug_menu.md "Where the flags live").
fn chapters() -> Vec<(u32, String)> {
    let first = [
        "Opening", "Apoina part A", "Domremy", "Ardennes Forest", "Paris", "Louvre 1", "Wine cellar", "Louvre 2", "Southampton", "Ronda mine", "Wales 1",
        "Firenze 1", "Manmaria Island", "Firenze 2", "SG Italy branch", "Firenze 3", "Nemeton ruins", "Firenze 4", "Cannes", "Sainte-Marguerite", "Cannes 2",
        "Wales 2", "Hermitage 1", "Petrograd 1", "Hermitage 2", "Petrograd 2", "Goreme Valley", "Mirror castle / Goreme Valley 2", "Corridor of the dead",
        "Hermitage 3", "Idar Flamme", "Apoina Tower 2", "Graveyard",
    ];
    let second = [
        "second-half opening", "red-brick warehouse", "Yokohama 1", "battleship Mikasa 1", "Todo lab 1", "Mikasa 2", "Yokohama 2", "foreign cemetery 1",
        "the other world", "Muhyoan 1", "Nihonbashi 1", "Todo lab 2", "Muhyoan 2", "Nihonbashi 2",
    ];
    let hidden = ["Sesshoseki", "Doll house", "Schwarzwald", "wakuraba (cut)", "Nemeton deepest level", "Ring Tower"];
    let wolf = ["Tetsu", "Terry", "Jerome", "Henri", "Philip", "R3", "Necross", "triple star", "Kibolin", "Eleonore", "Matsunaga", "Robo", "Henri 2", "Robo 2", "Phantom Wolf"];
    let mut v = vec![];
    for (i, n) in first.iter().enumerate() {
        v.push((8 + i as u32, format!("first half: {n}")));
    }
    for (i, n) in second.iter().enumerate() {
        v.push((0x3c + i as u32, format!("second half: {n}")));
    }
    for (i, n) in hidden.iter().enumerate() {
        v.push((0x64 + i as u32, format!("hidden dungeon: {n}")));
    }
    for (i, n) in wolf.iter().enumerate() {
        v.push((0xa0 + i as u32, format!("Wolfbout: {n}")));
    }
    v.push((0x54, "last dungeon appears".into()));
    v
}

pub fn run_all(out: &std::path::Path, fresh: bool, _only: Option<&str>) {
    let set = PkbSet::open(disc_dir()).expect("US disc");
    let maps = super::field::list_maps(&set);
    let mapset: BTreeSet<String> = maps.iter().cloned().collect();
    let field: BTreeMap<String, Row> = cat_files(out, "field").iter().flat_map(|f| read_rows(f)).map(|r| (r.id.clone(), r)).collect();
    let mut sink = Sink::open(out, "story", true);
    let _ = fresh;
    if field.is_empty() {
        let mut r = Row::new("story graph");
        r.status = "untested".into();
        r.detail = "run the field check first".into();
        sink.put(&r);
        return;
    }
    // ---- edges
    const WM: &str = "<world map>";
    let mut dynamic: BTreeMap<String, BTreeSet<String>> = BTreeMap::new();
    let mut jumps: Vec<(String, String, i32)> = vec![];
    for (m, r) in &field {
        if let Some(j) = r.get("jumps") {
            for t in j.split(',').filter(|x| !x.is_empty()) {
                let (dst, e) = t.rsplit_once(':').map(|(a, b)| (a.to_string(), b.parse().unwrap_or(0))).unwrap_or((t.to_string(), 0));
                dynamic.entry(m.clone()).or_default().insert(dst.clone());
                jumps.push((m.clone(), dst, e));
            }
        }
        if r.get("worldmap").is_some() {
            dynamic.entry(m.clone()).or_default().insert(WM.into());
        }
    }
    let wt = set.read("FIELD.BIN").and_then(|b| sh2_field::worldmap::RetailWorldTable::from_field_bin(&b));
    if let Some(t) = &wt {
        for p in t.points.iter().filter(|p| !p.map.is_empty()) {
            dynamic.entry(WM.into()).or_default().insert(p.map.clone());
        }
    }
    // static references + constant setFlag calls
    let mut stat: BTreeMap<String, BTreeSet<String>> = BTreeMap::new();
    let mut setters: BTreeMap<u32, BTreeSet<String>> = BTreeMap::new();
    for m in &maps {
        let Some(b) = set.read(&format!("FIELD/MPS/{m}.MSC")) else { continue };
        for o in &maps {
            if o != m && b.windows(o.len() + 1).any(|w| &w[..o.len()] == o.as_bytes() && w[o.len()] == 0) {
                stat.entry(m.clone()).or_default().insert(o.clone());
            }
        }
        if let Ok(img) = sh2_script::image::ScriptImage::parse(&b) {
            for c in sh2_script::disasm::scan_calls(&img) {
                if c.ex == sh2_script::opcodes::ifc::SET_FLAG {
                    if let Some(Some(n)) = c.args.first() {
                        setters.entry(*n).or_default().insert(m.clone());
                    }
                }
            }
        }
    }
    let reach = |edges: &[&BTreeMap<String, BTreeSet<String>>]| -> BTreeMap<String, usize> {
        let mut d: BTreeMap<String, usize> = BTreeMap::new();
        let mut q = VecDeque::new();
        d.insert("OP_00_U".into(), 0);
        q.push_back("OP_00_U".to_string());
        while let Some(n) = q.pop_front() {
            let k = d[&n];
            for e in edges {
                if let Some(nx) = e.get(&n) {
                    for x in nx {
                        if !d.contains_key(x) {
                            d.insert(x.clone(), k + 1);
                            q.push_back(x.clone());
                        }
                    }
                }
            }
        }
        d
    };
    let dyn_reach = reach(&[&dynamic]);
    let all_reach = reach(&[&dynamic, &stat]);
    let referenced: BTreeSet<String> = stat.values().flatten().chain(dynamic.values().flatten()).cloned().collect();
    // ---- disc 2: cut scenes only on disc 2 (lsd rows `disc=disc 2`) and the maps that play them / change the disc
    let disc2_only: BTreeSet<String> = cat_files(out, "lsd")
        .iter()
        .flat_map(|f| read_rows(f))
        .filter(|r| r.get("disc") == Some("disc 2"))
        .map(|r| r.id.rsplit('/').next().unwrap_or(&r.id).trim_end_matches(".LSD").to_string())
        .collect();
    let needs_disc2 = |m: &str| -> Option<String> {
        let r = field.get(m)?;
        if r.get("diskchange").is_some() {
            return Some("DiskChange".into());
        }
        let norm = |x: &str| x.rsplit('/').next().unwrap_or(x).to_uppercase().trim_end_matches(".LSD").to_string();
        let mv: Vec<String> = r.get("movies").unwrap_or("").split(',').map(norm).filter(|x| disc2_only.contains(x)).collect();
        (!mv.is_empty()).then(|| format!("disc-2 scenes {}", mv.join(" ")))
    };
    // ---- rows: summary
    let mut s = Row::new("story graph");
    s.kv("maps", maps.len());
    s.kv("runtime_reachable", dyn_reach.keys().filter(|k| mapset.contains(*k)).count());
    s.kv("static_reachable", all_reach.keys().filter(|k| mapset.contains(*k)).count());
    s.kv("runtime_edges", dynamic.values().map(|v| v.len()).sum::<usize>());
    s.kv("disc2_only_scenes", disc2_only.len());
    s.kv("maps_needing_disc2", maps.iter().filter(|m| needs_disc2(m).is_some()).count());
    s.detail = format!(
        "{} of {} maps reachable from OP_00_U through jumps the headless scripts made (+{} more through static references)",
        dyn_reach.keys().filter(|k| mapset.contains(*k)).count(),
        maps.len(),
        all_reach.keys().filter(|k| mapset.contains(*k) && !dyn_reach.contains_key(*k)).count()
    );
    sink.put(&s);
    // jumps
    let mut seen = BTreeSet::new();
    for (a, b, e) in &jumps {
        let id = format!("jump {a} -> {b}:{e}");
        if !seen.insert(id.clone()) {
            continue;
        }
        let mut r = Row::new(&id);
        if b == "WORLDMAP" || b.starts_with("WM") {
            r.kv("worldmap", 1);
        } else if b.is_empty() {
            r.status = "fails".into();
            r.detail = "MapJump with name pointer 1 = back to the saved map (`CField::MapJump`: `a0 == 1` -> `GetSavedMpsName(1)`, decomp/G/CField.c:4951); the port's host.rs 0x20 reads it as an empty map name".into();
            r.owner = "FS".into();
        } else if !mapset.contains(b) {
            r.status = "fails".into();
            r.detail = format!("target map {b} is not on the disc");
            r.owner = "FS".into();
        } else if *e >= 0 {
            let n = set.read(&format!("FIELD/MPS/{b}.MPS")).and_then(|m| sh2_field::mps::Mps::parse(m).ok()).and_then(|m| m.entry_points().ok()).map(|v| v.len()).unwrap_or(0);
            r.kv("entries", n);
            if (*e as usize) >= n && n > 0 {
                r.status = "stub".into();
                r.detail = format!("entry {e} not in {b} ({n} entry points)");
                r.owner = "FS".into();
            }
        }
        sink.put(&r);
    }
    // world map points
    if let Some(t) = &wt {
        for (i, p) in t.points.iter().enumerate() {
            if p.map.is_empty() {
                continue;
            }
            let mut r = Row::new(format!("world map point {i:02} {}", p.map));
            r.kv("entry", p.entry);
            match field.get(&p.map) {
                None => {
                    if mapset.contains(&p.map) {
                        r.status = "untested".into();
                        r.detail = "map not in the field rows".into();
                    } else {
                        r.status = "fails".into();
                        r.detail = format!("{} is not on the disc", p.map);
                        r.owner = "FS".into();
                    }
                }
                Some(fr) => {
                    r.status = if fr.status == "fails" || fr.status == "timeout" { "fails".into() } else { "ok".into() };
                    if fr.status != "ok" {
                        r.detail = format!("field check {}: {}", fr.status, fr.detail.chars().take(160).collect::<String>());
                        r.owner = fr.owner.clone();
                        if fr.status == "stub" {
                            r.status = "stub".into();
                        }
                    }
                }
            }
            sink.put(&r);
        }
    } else {
        let mut r = Row::new("world map points");
        r.status = "fails".into();
        r.detail = "RetailWorldTable::from_field_bin failed".into();
        r.owner = "FS".into();
        sink.put(&r);
    }
    // evidence of the FS headless story walk (`sh2_field --example story_walk -- --evidence tools/coverage/out/fs_story_walk.txt`): flags it set and
    // maps it played from the new game on (added by round 5 FS)
    let walk_txt = std::fs::read_to_string(out.join("fs_story_walk.txt")).unwrap_or_default();
    let walk_flags: std::collections::HashMap<u32, String> = walk_txt
        .lines()
        .filter_map(|l| l.strip_prefix("flag "))
        .filter_map(|l| l.split_once(' '))
        .filter_map(|(f, m)| u32::from_str_radix(f.trim_start_matches("0x"), 16).ok().map(|f| (f, m.to_string())))
        .collect();
    let walk_maps: std::collections::HashSet<String> = walk_txt.lines().filter_map(|l| l.strip_prefix("map ")).map(|s| s.to_string()).collect();
    // chapters
    for (flag, name) in chapters() {
        let mut r = Row::new(format!("chapter flag {flag:#06x} {name}"));
        if let Some(m) = walk_flags.get(&flag) {
            r.status = "ok".into();
            r.detail = format!("set in {m} by the FS story walk");
            sink.put(&r);
            continue;
        }
        let ms = setters.get(&flag).cloned().unwrap_or_default();
        r.kv("set_by", ms.iter().take(6).cloned().collect::<Vec<_>>().join(","));
        if let Some(d2) = ms.iter().find_map(|m| needs_disc2(m).map(|x| format!("{m}: {x}"))) {
            r.kv("needs_disc2", d2.replace([';', ','], " "));
        }
        if ms.is_empty() {
            r.status = "untested".into();
            r.detail = "no map script sets this flag with a constant (set by a cut scene / computed / debug only?)".into();
        } else if let Some(m) = ms.iter().find(|m| dyn_reach.contains_key(*m)) {
            r.status = "ok".into();
            r.detail = format!("set in {m} (reachable, depth {})", dyn_reach[m]);
            if let Some(d2) = r.get("needs_disc2").map(|x| x.to_string()) {
                r.add_detail(format!("needs disc 2 ({d2})"));
            }
        } else if let Some(m) = ms.iter().find(|m| all_reach.contains_key(*m)) {
            // jump there directly (the debug menu's chapter / flag jumps): the earlier chapters' flags set, run the map, see whether some
            // job sets the flag
            let pre: Vec<u32> = chapters().iter().map(|(f, _)| *f).filter(|f| *f < flag && *f >= 8).collect();
            match guarded(|| super::field::sets_flag(&set, m, flag, &pre)) {
                Ok(Some(job)) => {
                    r.status = "ok".into();
                    r.detail = format!("set in {m} ({job}) when the map is entered with the earlier chapter flags set; the map is reachable only through static references");
                }
                Ok(None) => {
                    r.status = "untested".into();
                    r.detail = format!("set in {m}: reachable only through static references, and no job of {m} sets it headless with the earlier chapter flags set (needs more state)");
                    r.owner = "FS".into();
                }
                Err(p) => {
                    r.status = "fails".into();
                    r.detail = format!("running {m} for the flag: {p}");
                    r.owner = owner_of_path(&p).into();
                }
            }
        } else {
            r.status = "untested".into();
            r.detail = format!("set in {} which nothing reaches from OP_00_U", ms.iter().next().unwrap());
            r.owner = "FS".into();
        }
        sink.put(&r);
    }
    // maps
    for m in &maps {
        let mut r = Row::new(format!("map {m}"));
        if let Some(d2) = needs_disc2(m) {
            r.kv("needs_disc2", d2.replace([';', ','], " "));
            r.add_detail(format!("needs disc 2: {d2}"));
        }
        if let Some(d) = dyn_reach.get(m) {
            r.kv("depth", d);
        } else if walk_maps.contains(m) {
            r.detail = "played by the FS story walk".into();
        } else if all_reach.contains_key(m) {
            r.status = "untested".into();
            r.detail = "reachable only through static references (story flags / branches the headless run does not take)".into();
            r.owner = "FS".into();
        } else if referenced.contains(m) {
            r.status = "untested".into();
            r.detail = "referenced, but not from anything reachable from OP_00_U".into();
            r.owner = "FS".into();
        } else {
            r.status = "untested".into();
            r.detail = if m.contains("DB") { "debug map (only the debug menu reaches it)".into() } else { "no script or world map point names it (unused / debug / reached by a computed name)".into() };
        }
        sink.put(&r);
    }
}
