//! List the SE ids of system banks (and which file owns which wave-bank id): `sysse [file ...]` (default SYSREG + SYSBTL), env SH2_DISC_DIR.
use sh2_audio::synth::render_seconds;
use sh2_audio::{Bank, Synth};
use sh2_core::fileio::Disc;
use sh2_script::audio::SeParam;

fn main() {
    let disc = Disc::from_env().unwrap();
    let args: Vec<String> = std::env::args().skip(1).collect();
    if args.first().map(|s| s.as_str()) == Some("--banks") {
        // wave-bank id -> files
        for (_c, files) in disc.listing() {
            for (path, _) in files {
                let up = path.to_uppercase();
                if !(up.ends_with(".SSE") || up.ends_with(".SSQ")) { continue; }
                if let Ok(b) = Bank::parse_opts(&disc.read(&path).unwrap(), false) {
                    println!("{:#06x} {} ({} SE ids)", b.bank_id, path, b.se_map.len());
                }
            }
        }
        return;
    }
    let files = if args.is_empty() { vec!["COMMON/SYSREG.SSE".to_string(), "BTLDATA/SOUND/SYSTEM/SYSBTL.SSE".to_string()] } else { args };
    for f in files {
        let bytes = disc.read(&f).unwrap();
        let bank = Bank::parse(&bytes).unwrap();
        println!("== {f}: bank id {:#06x}, volume {}%, {} waves, {} sequences", bank.bank_id, bank.volume_percent, bank.waves.len(), bank.sequences.len());
        for &(id, val) in &bank.se_map {
            let mut s = Synth::new();
            let h = s.add_bank(bank.clone());
            let Some(pid) = s.play_se(h, id, &SeParam::default()) else { println!("  {id:#06x} val {val:#06x}: no target"); continue };
            let pcm = render_seconds(&mut s, 3.0);
            let peak = pcm.iter().fold(0f32, |m, v| m.max(v.abs()));
            let last = pcm.chunks(2).rposition(|f| f[0].abs() > 1e-3 || f[1].abs() > 1e-3).map(|i| i as f32 / 48000.0).unwrap_or(0.0);
            println!("  {id:#06x} val {val:#06x} {:?}: sounding {:.2}s, peak {:.2}{}", bank.se_target(id).unwrap(), last, peak, if s.is_playing(pid) { " (still playing at 3 s: loop)" } else { "" });
        }
    }
}
