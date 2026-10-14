//! `movie_census [names...]` (round 5 CS): decode every `MOVS` track of every LSD file of the US disc set (`SH2_US_DISC_DIR` +
//! `SH2_US_DISC2_DIR`) to the end; prints pictures, size, rate and the LSD duration vs the video length.
use sh2_menu::movie::{MovieMsg, MovieStream};
use sh2_script::lsd::{LsdFile, TrackKind};
use std::sync::Arc;

fn main() {
    let names: Vec<String> = std::env::args().skip(1).collect();
    let disc = sh2_core::fileio::Disc::from_env_var("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let mut files: Vec<String> = Vec::new();
    for (_, fl) in disc.listing_all() {
        for (p, _) in fl {
            let up = p.to_uppercase();
            if up.starts_with("LSD/") && up.ends_with(".LSD") && (names.is_empty() || names.iter().any(|n| up.contains(&n.to_uppercase()))) {
                files.push(p);
            }
        }
    }
    files.sort();
    files.dedup();
    let (mut tracks, mut pictures, mut errors) = (0, 0usize, Vec::new());
    for f in &files {
        let Ok(bytes) = disc.read(f) else { continue };
        let movs: Vec<(usize, u32, u32)> = match LsdFile::parse(&bytes) {
            Ok(l) => l.tracks.iter().enumerate().filter(|(_, t)| TrackKind::from_tag(&t.tag) == TrackKind::Movie).map(|(i, t)| (i, t.start_tick, t.end_tick)).collect(),
            Err(_) => continue,
        };
        if movs.is_empty() {
            continue;
        }
        let bytes = Arc::new(bytes);
        for (ti, st, en) in movs {
            let s = MovieStream::from_lsd_track(bytes.clone(), ti);
            let (mut n, mut info) = (0usize, None);
            loop {
                match s.recv() {
                    Ok(MovieMsg::Info(i)) => info = Some((i.width, i.height, i.fps)),
                    Ok(MovieMsg::Frame(_)) => n += 1,
                    Ok(MovieMsg::End(_)) => break,
                    Ok(MovieMsg::Error(e)) => {
                        errors.push(format!("{f} track {ti}: {e}"));
                        break;
                    }
                    Err(_) => break,
                }
            }
            let (w, h, fps) = info.unwrap_or((0, 0, (0, 1)));
            let secs = n as f32 * fps.1 as f32 / fps.0.max(1) as f32;
            println!("{f} track {ti}: {n} pictures {w}x{h} @ {:.3} = {secs:.1}s, track ticks {st}..{en} = {:.1}s", fps.0 as f32 / fps.1.max(1) as f32, (en - st) as f32 / 30.0);
            tracks += 1;
            pictures += n;
        }
    }
    println!("\n{tracks} MOVS tracks, {pictures} pictures, {} errors {:?}", errors.len(), errors);
}
