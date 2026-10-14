//! Table of the SE ids of a bank with their rendered length: `se_table <path>...`
use sh2_audio::synth::render_seconds;
use sh2_audio::{Bank, Synth};
use sh2_core::fileio::Disc;
use sh2_script::audio::SeParam;
fn main() {
    let disc = Disc::from_env().unwrap();
    for path in std::env::args().skip(1) {
        let bank = Bank::parse(&disc.read(&path).unwrap()).unwrap();
        println!("{path} (wave bank {:#06x}, volume {}%)", bank.bank_id, bank.volume_percent);
        for &(id, val) in &bank.se_map {
            let mut s = Synth::new();
            let h = s.add_bank(bank.clone());
            let Some(pid) = s.play_se(h, id, &SeParam::default()) else { println!("  {id:#06x} -> {val:#06x}: no target"); continue };
            let pcm = render_seconds(&mut s, 4.0);
            let last = pcm.chunks(2).rposition(|f| f[0].abs() > 0.001 || f[1].abs() > 0.001).map(|i| i + 1).unwrap_or(0);
            let peak = pcm.iter().fold(0f32, |m, v| m.max(v.abs()));
            println!("  {id:#06x} -> {val:#06x} {:<28} {:5.2}s peak {peak:.2}{}", format!("{:?}", bank.se_target(id).unwrap()), last as f32 / 48000.0, if s.is_playing(pid) { " (loops/sustains)" } else { "" });
        }
    }
}
