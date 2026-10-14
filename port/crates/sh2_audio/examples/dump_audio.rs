//! Offline validation tool: render SE / BGM / stream BGM from a disc to WAV and print duration / peak / RMS.
//!
//! ```text
//! SH2_DISC_DIR=".../Shadow Hearts II (Japan) (Furokuban)" cargo run -p sh2_audio --example dump_audio -- <out_dir> [bgm_secs]
//! ```
use sh2_audio::synth::render_seconds;
use sh2_audio::{write_wav, Bank, Synth, OUT_RATE};
use sh2_core::fileio::Disc;
use sh2_script::audio::{BgmParam, SeParam};
use std::path::PathBuf;

fn stats(name: &str, pcm: &[f32]) {
    let frames = pcm.len() / 2;
    let peak = pcm.iter().fold(0f32, |m, s| m.max(s.abs()));
    let rms = (pcm.iter().map(|s| s * s).sum::<f32>() / pcm.len().max(1) as f32).sqrt();
    // active length = last frame above -60 dB
    let last = pcm.chunks(2).rposition(|f| f[0].abs() > 0.001 || f[1].abs() > 0.001).map(|i| i + 1).unwrap_or(0);
    println!("{name:<44} frames={frames:>8} active={:.3}s peak={peak:.3} rms={rms:.4}", last as f32 / OUT_RATE as f32);
}

fn main() {
    let out_dir = PathBuf::from(std::env::args().nth(1).expect("out dir"));
    let bgm_secs: f32 = std::env::args().nth(2).and_then(|s| s.parse().ok()).unwrap_or(40.0);
    std::fs::create_dir_all(&out_dir).unwrap();
    let disc = Disc::from_env().expect("SH2_DISC_DIR");

    // ---- SE: first few ids of a few banks ----
    let se_banks = ["COMMON/SYSREG.SSE", "BTLDATA/SOUND/SYSTEM/SYSBTL.SSE", "FIELD/SOUND/SE/AP_00_U.SSE", "FIELD/SOUND/SE/SYSMAJ00.SSE", "BTLDATA/SOUND/SE/000W00.SSE"];
    for path in se_banks {
        let Ok(bytes) = disc.read(path) else { println!("{path}: missing"); continue };
        let bank = Bank::parse(&bytes).unwrap();
        println!("{path}: bank id {:#x}, {} SE ids, {} waves, rates {:?}", bank.bank_id, bank.se_map.len(), bank.waves.len(), bank.waves.iter().take(6).map(|w| w.rate).collect::<Vec<_>>());
        for &(id, val) in bank.se_map.iter().take(4) {
            let mut synth = Synth::new();
            let h = synth.add_bank(bank.clone());
            let Some(pid) = synth.play_se(h, id, &SeParam::default()) else {
                println!("  se {id:#06x} (value {val:#06x}) -> no target");
                continue;
            };
            let pcm = render_seconds(&mut synth, 4.0);
            let name = format!("{}_{id:04x}", path.replace('/', "_"));
            stats(&format!("  se {id:#06x} v={val:#06x} {}", if synth.is_playing(pid) { "(still playing)" } else { "" }), &pcm);
            write_wav(&out_dir.join(format!("se_{name}.wav")), &pcm, 2, OUT_RATE).unwrap();
        }
    }

    // ---- BGM ----
    for path in ["FIELD/SOUND/BGM/BGM601.SSQ", "BTLDATA/SOUND/BGM/BGM401.SSQ", "FIELD/SOUND/BGM/BGM711.SSQ"] {
        let Ok(bytes) = disc.read(path) else { continue };
        let bank = Bank::parse(&bytes).unwrap();
        let mut synth = Synth::new();
        let h = synth.add_bank(bank);
        let pid = synth.play_bgm(h, 0, &BgmParam::default()).expect("seq 0");
        let pcm = render_seconds(&mut synth, bgm_secs);
        stats(path, &pcm);
        let _ = pid;
        write_wav(&out_dir.join(format!("bgm_{}.wav", path.replace('/', "_"))), &pcm, 2, OUT_RATE).unwrap();
    }

    // ---- stream BGM ----
    for path in ["FIELD/SOUND/BGM/BGM006.SSV", "OPENING/BGM803.SSV"] {
        let Ok(bytes) = disc.read(path) else { continue };
        let mut synth = Synth::new();
        let p = sh2_audio::stream::StreamPlayer::from_ssv(&bytes).unwrap();
        println!("{path}: {} frames decoded, rate {}, loop {:?}, end {:?}", p.dec.frames(), p.rate, p.loop_start, p.end);
        synth.add_stream(p);
        let pcm = render_seconds(&mut synth, 30.0);
        stats(path, &pcm);
        write_wav(&out_dir.join(format!("stream_{}.wav", path.replace('/', "_"))), &pcm, 2, OUT_RATE).unwrap();
    }
}
