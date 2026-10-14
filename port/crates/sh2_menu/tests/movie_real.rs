//! The JP demo's title movie (`OPENING/DEMO.LSD`, `MOVS` + `PCMS` tracks) decodes start to end.
use sh2_menu::movie::{split_lsd, MovieStream};
use std::path::PathBuf;

fn root() -> Option<PathBuf> {
    std::env::var_os("SH2_DISC_DIR").map(PathBuf::from).filter(|p| p.join("PKFINFO.TBL").exists())
}

#[test]
fn title_movie_streams_have_the_expected_shape() {
    let Some(root) = root() else { return };
    let disc = sh2_core::fileio::Disc::open(&root).unwrap();
    let bytes = disc.read("OPENING/DEMO.LSD").unwrap();
    let (es, info) = split_lsd(&bytes).unwrap();
    assert_eq!((info.width, info.height), (640, 448));
    assert_eq!(&es[..4], &[0, 0, 1, 0xb3], "MPEG-2 sequence header");
    let (hdr, pcm) = info.pcm.expect("PCMS audio track");
    assert_eq!(&hdr[..4], b"PCMS");
    assert!(pcm.len() > 7_000_000);
    assert!((info.duration_secs - 132.5).abs() < 0.1);
}

/// 3871 pictures = what `ffprobe -count_frames` reports for the elementary stream (and what the PS2 decoder shows).
#[test]
fn title_movie_decodes_every_frame() {
    let Some(root) = root() else { return };
    let (n, info) = MovieStream::count_frames(root, "OPENING/DEMO.LSD".into()).unwrap();
    assert_eq!(n, 3871);
    assert_eq!((info.width, info.height), (640, 448));
    assert_eq!(info.fps, (30000, 1001));
}
