//! Render every SE id of every bank and report silent ones / longest durations (sanity check of the SE paths).
use sh2_audio::synth::render_seconds;
use sh2_audio::{Bank, Synth};
use sh2_core::fileio::Disc;
use sh2_script::audio::SeParam;

fn main() {
    let disc = Disc::from_env().unwrap();
    let (mut total, mut silent, mut still) = (0, 0, 0);
    let mut worst = vec![];
    for (_c, files) in disc.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if !(up.ends_with(".SSE") || up.ends_with(".SSQ")) || up.contains("/BGM/") {
                continue;
            }
            let Ok(bank) = Bank::parse(&disc.read(&path).unwrap()) else { continue };
            for &(id, _) in &bank.se_map {
                let mut s = Synth::new();
                let h = s.add_bank(bank.clone());
                let Some(pid) = s.play_se(h, id, &SeParam::default()) else { continue };
                let pcm = render_seconds(&mut s, 2.5);
                total += 1;
                let peak = pcm.iter().fold(0f32, |m, v| m.max(v.abs()));
                if peak < 1e-4 {
                    silent += 1;
                    worst.push(format!("{path} id {id:#x} silent"));
                }
                if s.is_playing(pid) {
                    still += 1;
                }
            }
        }
    }
    println!("{total} SEs rendered, {silent} silent, {still} still playing after 2.5 s (loops / long sounds)");
    for w in worst.iter().take(30) {
        println!("  {w}");
    }
}
