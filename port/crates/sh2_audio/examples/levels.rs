//! Peak / RMS / clipped-sample report of BGM renders (the driver gain chain is unity; the SPU clips at 16 bit).
use sh2_audio::synth::render_seconds;
use sh2_audio::{Bank, Synth};
use sh2_core::fileio::Disc;
use sh2_script::audio::BgmParam;

fn main() {
    let disc = Disc::from_env().unwrap();
    for (_c, files) in disc.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if !up.ends_with(".SSQ") {
                continue;
            }
            let Ok(bank) = Bank::parse(&disc.read(&path).unwrap()) else { continue };
            if bank.sequences.is_empty() {
                continue;
            }
            let mut s = Synth::new();
            let h = s.add_bank(bank);
            s.play_bgm(h, 0, &BgmParam::default());
            let t0 = std::time::Instant::now();
            let pcm = render_seconds(&mut s, 30.0);
            let dt = t0.elapsed().as_secs_f32();
            let peak = pcm.iter().fold(0f32, |m, v| m.max(v.abs()));
            let clipped = pcm.iter().filter(|v| v.abs() >= 0.9999).count();
            let rms = (pcm.iter().map(|v| v * v).sum::<f32>() / pcm.len() as f32).sqrt();
            println!("{path}: peak {peak:.2} rms {rms:.3} clipped {clipped} ({:.1}x realtime, max voices {})", 30.0 / dt, s.active_voices());
        }
    }
}
