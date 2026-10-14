use sh2_audio::synth::render_seconds;
use sh2_audio::{Bank, Synth};
use sh2_core::fileio::Disc;
fn main() {
    let disc = Disc::from_env().unwrap();
    let a: Vec<String> = std::env::args().skip(1).collect();
    let bank = Bank::parse(&disc.read(&a[0]).unwrap()).unwrap();
    let prog: u8 = a[1].parse().unwrap();
    let key: u8 = a[2].parse().unwrap();
    let mut s = Synth::new();
    let h = s.add_bank(bank);
    s.play_note(h, prog, key, 100).unwrap();
    let pcm = render_seconds(&mut s, 0.5);
    let mono: Vec<f32> = pcm.chunks(2).skip(3840).map(|f| f[0] + f[1]).collect();
    let n = 9600;
    let r0: f32 = mono[..n].iter().map(|x| x * x).sum();
    let mut r = vec![0.0f32; 1500];
    for lag in 20..1400 {
        r[lag] = (0..n).map(|i| mono[i] * mono[i + lag]).sum::<f32>() / r0;
    }
    let mut peaks = vec![];
    for lag in 21..1399 {
        if r[lag] > 0.3 && r[lag] >= r[lag - 1] && r[lag] >= r[lag + 1] {
            peaks.push((lag, r[lag]));
        }
    }
    println!("expected {:.1} Hz = lag {:.0}", 440.0 * 2f32.powf((key as f32 - 69.0) / 12.0), 48000.0 / (440.0 * 2f32.powf((key as f32 - 69.0) / 12.0)));
    for (lag, v) in peaks.iter().take(12) {
        println!("  lag {lag:4} ({:7.1} Hz) r={v:.3}", 48000.0 / *lag as f32);
    }
    // crude spectrum peak (DFT at semitone grid)
    let mut best = vec![];
    for semi in 0..96 {
        let f = 55.0 * 2f32.powf(semi as f32 / 12.0);
        let (mut re, mut im) = (0.0f32, 0.0f32);
        for (i, x) in mono[..n].iter().enumerate() {
            let w = 2.0 * std::f32::consts::PI * f * i as f32 / 48000.0;
            re += x * w.cos();
            im += x * w.sin();
        }
        best.push((re * re + im * im, f));
    }
    best.sort_by(|a, b| b.0.partial_cmp(&a.0).unwrap());
    println!("  strongest partials: {:?}", best.iter().take(5).map(|b| b.1.round()).collect::<Vec<_>>());
}
