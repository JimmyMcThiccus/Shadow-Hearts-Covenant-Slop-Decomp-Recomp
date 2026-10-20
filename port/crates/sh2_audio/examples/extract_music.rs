//! Dump every BGM track (sequenced `.SSQ`/`.SSE` banks and streamed `.SSV` files, found by scanning
//! each disc's archives for anything under a `.../BGM/` or `.../SOUND/BGM/` path) to WAV files.
//!
//! ```text
//! SH2_DISC_DIR="<disc folder>" cargo run --release -p sh2_audio --example extract_music -- <out_dir>
//! ```
use sh2_audio::stream::StreamPlayer;
use sh2_audio::synth::render_seconds;
use sh2_audio::{write_wav, Bank, Synth, OUT_RATE};
use sh2_core::fileio::Disc;
use sh2_script::audio::BgmParam;
use std::path::PathBuf;

/// Hard cap per sequenced track so a broken/non-looping sequence can't run forever.
const CAP_SECONDS: f32 = 200.0;

fn safe_name(path: &str) -> String {
    path.replace(['/', '\\'], "_")
}

fn dump_sequenced(disc: &Disc, path: &str, out_dir: &PathBuf) {
    let Ok(bytes) = disc.read(path) else { return };
    let Ok(bank) = Bank::parse(&bytes) else {
        println!("  {path}: failed to parse");
        return;
    };
    if bank.sequences.is_empty() {
        println!("  {path}: no sequences, skipping");
        return;
    }
    for seq in 0..bank.sequences.len() {
        let mut synth = Synth::new();
        let h = synth.add_bank(bank.clone());
        let Some(id) = synth.play_bgm(h, seq, &BgmParam::default()) else {
            println!("  {path} seq {seq}: could not start");
            continue;
        };
        let pcm = render_seconds(&mut synth, CAP_SECONDS);
        let marks = synth.bgm_loop_marks(id);
        // Keep two full passes through an endless loop when we found them; otherwise keep the
        // whole capped render (a one-shot track, or one whose loop didn't close inside the cap).
        let trimmed = if marks.len() >= 2 {
            &pcm[..(marks[1] as usize * 2).min(pcm.len())]
        } else {
            &pcm[..]
        };
        let frames = trimmed.len() / 2;
        let secs = frames as f32 / OUT_RATE as f32;
        let suffix = if bank.sequences.len() > 1 { format!("_seq{seq}") } else { String::new() };
        let name = format!("{}{}.wav", safe_name(path), suffix);
        write_wav(&out_dir.join(&name), trimmed, 2, OUT_RATE).unwrap();
        println!("  {name}: {secs:.1}s (loop marks {})", marks.len());
    }
}

fn dump_stream(disc: &Disc, path: &str, out_dir: &PathBuf) {
    let Ok(bytes) = disc.read(path) else { return };
    let Ok(player) = StreamPlayer::from_ssv(&bytes) else {
        println!("  {path}: failed to parse");
        return;
    };
    let rate = player.rate.max(1) as f32;
    // One full pass through the track (its loop tail is the same audio repeated).
    let secs = (player.end.unwrap_or(player.dec.frames()) as f32 / rate) + 0.25;
    let mut synth = Synth::new();
    synth.add_stream(player);
    let pcm = render_seconds(&mut synth, secs.min(CAP_SECONDS * 2.0));
    let name = format!("{}.wav", safe_name(path));
    write_wav(&out_dir.join(&name), &pcm, 2, OUT_RATE).unwrap();
    println!("  {name}: {:.1}s", pcm.len() as f32 / 2.0 / OUT_RATE as f32);
}

fn main() {
    let out_dir = PathBuf::from(std::env::args().nth(1).expect("usage: extract_music <out_dir>"));
    std::fs::create_dir_all(&out_dir).unwrap();
    let dir = std::env::var("SH2_DISC_DIR").expect("set SH2_DISC_DIR to the disc folder");
    let disc = Disc::open(&dir).expect("PKFINFO.TBL");

    let mut paths: Vec<String> = Vec::new();
    for (_container, files) in disc.listing() {
        for (path, _loc) in files {
            let up = path.to_uppercase();
            if !up.contains("/BGM/") && !up.contains("\\BGM\\") {
                continue;
            }
            if up.ends_with(".SSQ") || up.ends_with(".SSV") || up.ends_with(".SSE") {
                paths.push(path);
            }
        }
    }
    paths.sort();
    println!("{} candidate BGM files under {dir}", paths.len());

    for path in &paths {
        println!("{path}");
        if path.to_uppercase().ends_with(".SSV") {
            dump_stream(&disc, path, &out_dir);
        } else {
            dump_sequenced(&disc, path, &out_dir);
        }
    }
    println!("done -> {}", out_dir.display());
}
