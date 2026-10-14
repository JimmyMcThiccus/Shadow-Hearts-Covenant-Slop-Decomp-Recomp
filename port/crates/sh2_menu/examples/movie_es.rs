//! `movie_es [--us] LSD/MOVIE_D.LSD out.m2v` : write the `MOVS` elementary stream of an LSD movie (for `ffprobe -count_frames`).
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|s| s == "--us");
    let v: Vec<&String> = a.iter().filter(|s| !s.starts_with("--")).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let disc = sh2_core::fileio::Disc::open(dir).unwrap();
    let bytes = disc.read(v[0]).unwrap();
    let (es, info) = sh2_menu::movie::split_lsd(&bytes).unwrap();
    std::fs::write(v[1], &es).unwrap();
    println!("{} bytes of video, {}x{}, duration {:.1}s, pcm {}", es.len(), info.width, info.height, info.duration_secs, info.pcm.as_ref().map(|p| p.1.len()).unwrap_or(0));
}
