//! Audible demo through the default output device (rodio):  `play_demo <bank path> [seconds] [seq]`  e.g. `FIELD/SOUND/BGM/BGM601.SSQ 20`.
//! Also prints which backend was used (`rodio` or the `null` fallback).
use sh2_audio::{AudioEngine, OutputKind};
use sh2_core::fileio::Disc;
use sh2_script::audio::{BgmParam, SoundBackend};

fn main() {
    let disc = Disc::from_env().expect("SH2_DISC_DIR");
    let a: Vec<String> = std::env::args().skip(1).collect();
    let path = a.first().cloned().unwrap_or("BTLDATA/SOUND/BGM/BGM401.SSQ".into());
    let secs: f32 = a.get(1).and_then(|s| s.parse().ok()).unwrap_or(5.0);
    let seq: u32 = a.get(2).and_then(|s| s.parse().ok()).unwrap_or(0);
    let mut e = AudioEngine::new(OutputKind::Device);
    println!("backend: {} (device: {})", e.name, e.has_device());
    let bank = disc.read(&path).unwrap();
    let h = e.load_sdh(&bank);
    let bgm = e.play_bgm(h, seq, 0, &BgmParam::default());
    println!("playing {path} seq {seq} as handle {bgm} for {secs}s");
    let t0 = std::time::Instant::now();
    while t0.elapsed().as_secs_f32() < secs {
        std::thread::sleep(std::time::Duration::from_millis(100));
        e.pump(0.1); // no-op with a device
    }
    println!("synth rendered {:.2}s of audio in {:.2}s wall clock", e.synth().frames_rendered() as f32 / 48000.0, t0.elapsed().as_secs_f32());
}
