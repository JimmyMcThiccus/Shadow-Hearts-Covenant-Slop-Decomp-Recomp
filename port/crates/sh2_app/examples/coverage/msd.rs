//! Menu scenes: every `.MSD` on the disc parses and every record of every chunk (texts, windows, groups, sprites, polygons, menu texts,
//! messages, font draws, cursors, attached scenes) decodes.  A scene that parses but whose file name appears nowhere in the port's sources
//! is `untested` (no screen of the port loads it by that name).

use super::common::*;
use sh2_menu::msd::{ChunkType, Msd};

pub fn run_all(out: &std::path::Path, fresh: bool, only: Option<&str>) {
    let disc = sh2_core::fileio::Disc::open(disc_dir()).expect("US disc");
    let mut files = vec![];
    for (_, fl) in disc.listing() {
        for (p, _) in fl {
            if p.to_uppercase().ends_with(".MSD") {
                files.push(p);
            }
        }
    }
    files.sort();
    files.dedup();
    let src = port_sources();
    eprintln!("msd: {} files", files.len());
    let mut sink = Sink::open(out, "msd", fresh);
    for path in files {
        if !mine() || only.map(|o| !path.contains(o)).unwrap_or(false) || sink.done.contains(&path) {
            continue;
        }
        begin_item(&path, 60);
        let row = match guarded(|| check(&disc, &path, &src)) {
            Ok(r) => r,
            Err(p) => {
                let mut r = Row::new(&path);
                r.status = "fails".into();
                r.owner = owner_of_path(&p).into();
                r.detail = p;
                r
            }
        };
        end_item();
        sink.put(&row);
    }
}

/// All `.rs` sources of the port, upper-cased (for the "is it referenced" test).
pub fn port_sources() -> String {
    let mut s = String::new();
    let root = super::root().join("port/crates");
    let mut stack = vec![root];
    while let Some(d) = stack.pop() {
        let Ok(rd) = std::fs::read_dir(&d) else { continue };
        for e in rd.flatten() {
            let p = e.path();
            if p.is_dir() {
                if p.file_name().map(|n| n != "target" && n != "examples").unwrap_or(true) {
                    stack.push(p);
                }
            } else if p.extension().map(|x| x == "rs").unwrap_or(false) {
                if let Ok(t) = std::fs::read_to_string(&p) {
                    s.push_str(&t.to_uppercase());
                    s.push('\n');
                }
            }
        }
    }
    s
}

fn walk(m: &Msd, depth: usize, n: &mut [usize; 4]) -> Result<(), String> {
    // an `.MDT` data table (CMDMENU attach 11 ...) reuses the chunk header with its own type numbers (up to 51) and row sizes: the
    // scene accessors do not apply (`Msd::attach_files` / `text_entry` would read past the rows, msd.rs:121)
    if depth > 0 && m.chunks.iter().any(|c| c.raw_type > 12) {
        n[3] += 1;
        return Ok(());
    }
    // records of every chunk kind
    let kinds = [
        ChunkType::Resource,
        ChunkType::Text,
        ChunkType::FontDraw,
        ChunkType::Cursor,
        ChunkType::Window,
        ChunkType::Group,
        ChunkType::Sprite,
        ChunkType::Polygon,
        ChunkType::MenuText,
        ChunkType::Message,
    ];
    for k in kinds {
        for i in 0..m.count(k) {
            n[0] += 1;
            let ok = match k {
                ChunkType::Resource => m.resource_bytes(i).is_some(),
                ChunkType::Text => m.text_entry(i).map(|(a, b, _)| {
                    let _ = sh2_menu::sjis::decode(a);
                    let _ = sh2_menu::sjis::decode(b);
                }).is_some(),
                ChunkType::FontDraw => m.font_draw(i).is_some(),
                ChunkType::Cursor => m.cursor(i).is_some(),
                ChunkType::Window => m.window(i).is_some(),
                ChunkType::Group => m.group(i).is_some(),
                ChunkType::Sprite => m.sprite(i).is_some(),
                ChunkType::Polygon => m.polygon(i).is_some(),
                ChunkType::MenuText => m.menu_text(i).is_some(),
                ChunkType::Message => m.message(i).is_some(),
                _ => true,
            };
            if !ok {
                n[1] += 1;
            }
        }
    }
    for c in &m.chunks {
        if let ChunkType::Other(_) = ChunkType::from(c.raw_type) {
            n[3] += 1;
        }
    }
    // an `.MDT` data table (e.g. CMDMENU attach 11) reuses chunk type 12 with 8-byte rows: `Msd::attach_files` (msd.rs ~288) would
    // read past the row, so only real attach tables (12-byte rows) are followed
    let real_attach = m.find(ChunkType::Attach).map(|c| c.stride >= 12).unwrap_or(false);
    if !real_attach && m.find(ChunkType::Attach).is_some() {
        n[3] += 1;
    }
    if depth < 3 && real_attach {
        for (i, _) in m.attach_files().iter().enumerate() {
            if let Some(sub) = m.attach_scene(i) {
                n[2] += 1;
                walk(&sub, depth + 1, n)?;
            }
        }
    }
    Ok(())
}

fn check(disc: &sh2_core::fileio::Disc, path: &str, src: &str) -> Row {
    let mut row = Row::new(path);
    let bytes = match disc.read(path) {
        Ok(b) => b,
        Err(e) => {
            row.status = "fails".into();
            row.detail = format!("read: {e}");
            row.owner = "MN".into();
            return row;
        }
    };
    match Msd::parse(bytes) {
        Err(e) => {
            row.status = "fails".into();
            row.detail = format!("Msd::parse: {e:?}");
            row.owner = "MN".into();
        }
        Ok(m) => {
            let mut n = [0usize; 4];
            if let Err(e) = walk(&m, 0, &mut n) {
                row.worse("fails");
                row.add_detail(e);
            }
            row.kv("records", n[0]);
            row.kv("attached_scenes", n[2]);
            if n[1] > 0 {
                row.worse("fails");
                row.add_detail(format!("{} of {} records do not decode", n[1], n[0]));
                row.add_owner("MN");
            }
            if n[3] > 0 {
                row.kv("unknown_chunks", n[3]);
            }
            let stem = path.rsplit('/').next().unwrap_or(path).to_uppercase();
            let stem_noext = stem.trim_end_matches(".MSD");
            if !src.contains(&stem) && !src.contains(&format!("\"{stem_noext}\"")) {
                row.worse("untested");
                row.add_detail("parses; the file name appears nowhere in the port sources (no screen loads it by name)");
                row.add_owner("MN");
            }
        }
    }
    let _ = take_log();
    row
}
