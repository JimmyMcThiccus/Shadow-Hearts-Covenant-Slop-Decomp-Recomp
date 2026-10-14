//! Validation: render single notes of every program of a bank and measure the fundamental by autocorrelation.
//! A tonal instrument played at key 60 must come out near 261.6 Hz and at key 72 near 523.3 Hz if the wave rate / root key decoding is right.
use sh2_audio::synth::render_seconds;
use sh2_audio::{Bank, Synth};
use sh2_core::fileio::Disc;

fn f0(pcm: &[f32]) -> (f32, f32) {
    // mono mix, skip the first 80 ms
    let mono: Vec<f32> = pcm.chunks(2).skip(3840).map(|f| f[0] + f[1]).collect();
    let n = 9600.min(mono.len() / 2);
    let r0: f32 = mono[..n].iter().map(|x| x * x).sum();
    if r0 < 1e-6 {
        return (0.0, 0.0);
    }
    // normalised autocorrelation, lags for 70 Hz .. 1500 Hz at 48 kHz; take the first strong local maximum (the fundamental period)
    let mut r = vec![0.0f32; 700];
    for lag in 32..685 {
        r[lag] = (0..n).map(|i| mono[i] * mono[i + lag]).sum::<f32>() / r0;
    }
    let max = r.iter().cloned().fold(0.0f32, f32::max);
    for lag in 33..684 {
        if r[lag] > 0.9 * max && r[lag] >= r[lag - 1] && r[lag] >= r[lag + 1] {
            return (48000.0 / lag as f32, r[lag]);
        }
    }
    (0.0, 0.0)
}

fn main() {
    let disc = Disc::from_env().unwrap();
    for path in std::env::args().skip(1) {
        let bytes = disc.read(&path).unwrap();
        let bank = Bank::parse(&bytes).unwrap();
        println!("{path}: {} programs", bank.programs.len());
        for prog in 0..bank.programs.len().min(24) {
            let mut line = format!("  prog {prog:2}:");
            for key in [48u8, 60, 72] {
                let mut s = Synth::new();
                let h = s.add_bank(bank.clone());
                if s.play_note(h, prog as u8, key, 100).is_none() {
                    line += "   -";
                    continue;
                }
                let pcm = render_seconds(&mut s, 0.4);
                let (f, conf) = f0(&pcm);
                let expect = 440.0 * 2f32.powf((key as f32 - 69.0) / 12.0);
                line += &format!("  k{key}: {f:7.1} Hz (x{:4.2}, conf {conf:.2})", f / expect);
            }
            println!("{line}");
        }
    }
}
