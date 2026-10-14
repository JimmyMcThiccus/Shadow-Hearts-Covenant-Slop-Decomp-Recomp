//! Numerical validation report (no console recording is available, so everything is a self-consistency check against the hardware formulas):
//!
//! 1. pitch: driver pitch register vs the ideal equal-tempered ratio for every key (analytic) and measured fundamentals of rendered notes,
//! 2. clicks: second-difference outliers in every system SE and in BGM renders,
//! 3. loops: stream BGM seams and sequenced-BGM loop repeatability.
//!
//! `SH2_DISC_DIR=<jp or us disc> cargo run -p sh2_audio --example validate [--quick]`
use sh2_audio::spu;
use sh2_audio::stream::StreamPlayer;
use sh2_audio::synth::render_seconds;
use sh2_audio::validate::*;
use sh2_audio::{Bank, Synth};
use sh2_core::fileio::Disc;
use sh2_script::audio::{BgmParam, SeParam};

fn main() {
    let quick = std::env::args().any(|a| a == "--quick");
    let disc = Disc::from_env().unwrap();

    // ---- 1. pitch ---------------------------------------------------------------------------------------------------------------------
    println!("== pitch register vs ideal (root key 60, 48 kHz source)");
    let mut worst_lo = (0.0f32, 0);
    let mut worst_hi = (0.0f32, 0);
    for key in 0..128i32 {
        let reg = spu::pitch_reg(key * 128, 60, 48000) as f32;
        let ideal = 4096.0 * 2f32.powf((key - 60) as f32 / 12.0);
        if ideal > 16383.0 {
            continue;
        }
        let c = cents(reg, ideal);
        if key < 24 {
            if c.abs() > worst_lo.0.abs() {
                worst_lo = (c, key);
            }
        } else if c.abs() > worst_hi.0.abs() {
            worst_hi = (c, key);
        }
    }
    println!("  keys 0..23 worst error {:+.1} cents (key {}), keys 24.. worst {:+.2} cents (key {})", worst_lo.0, worst_lo.1, worst_hi.0, worst_hi.1);

    println!("== rendered loop period of sustained tones vs the ideal equal-tempered step");
    let mut errs: Vec<f32> = vec![];
    'outer: for (_c, files) in disc.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if !up.ends_with(".SSQ") || !up.contains("BGM401") && !up.contains("BGM601") && !up.contains("BGM711") && !up.contains("BGM501") {
                continue;
            }
            let Ok(bank) = Bank::parse(&disc.read(&path).unwrap()) else { continue };
            for (pi, p) in bank.programs.iter().enumerate() {
                let Some(sp) = p.splits.first() else { continue };
                let Some(set) = bank.sample_sets.get(sp.sample_set as usize) else { continue };
                let Some(&ti) = set.tones.first() else { continue };
                let t = &bank.tones[ti as usize];
                let Some(w) = bank.waves.get(t.wave() as usize) else { continue };
                let Some(ls) = w.loop_start.filter(|_| w.looping) else { continue };
                let n_loop = w.pcm.len() - ls;
                if n_loop < 64 || p.b(9) != 0 {
                    continue;
                }
                for key in [sp.key_lo.max(36), (sp.key_lo.max(36) + sp.key_hi.min(100)) / 2] {
                    if key > sp.key_hi {
                        continue;
                    }
                    let pitch = key as f32 + sp.coarse as f32 + p.coarse as f32 + (t.fine() as f32 + sp.fine as f32 + p.fine as f32) / 128.0;
                    let step = w.rate as f32 / 48000.0 * 2f32.powf((pitch - t.root_key() as f32) / 12.0);
                    let expected = n_loop as f32 / step;
                    if expected > 6000.0 || expected < 4.0 {
                        continue;
                    }
                    let mut s = Synth::new();
                    let h = s.add_bank(bank.clone());
                    s.play_note(h, pi as u8, key, 100);
                    let pcm = render_seconds(&mut s, 0.9);
                    let x = &left(&pcm)[24000..40000];
                    if let Some(lag) = period_lag(x, expected, 0.03) {
                        errs.push(cents(expected, lag));
                    }
                    if errs.len() >= 60 {
                        break 'outer;
                    }
                }
            }
        }
    }
    errs.sort_by(|a, b| a.partial_cmp(b).unwrap());
    if !errs.is_empty() {
        let worst = errs.iter().fold(0.0f32, |m, v| m.max(v.abs()));
        println!("  {} tone/key pairs: median {:+.2} cents, worst |error| {:.2} cents", errs.len(), errs[errs.len() / 2], worst);
    }

    // ---- 2. clicks ---------------------------------------------------------------------------------------------------------------------
    println!("== click scan (second-difference outliers, ratio 25, floor 0.04)");
    for f in ["COMMON/SYSREG.SSE", "BTLDATA/SOUND/SYSTEM/SYSBTL.SSE"] {
        let bank = Bank::parse(&disc.read(f).unwrap()).unwrap();
        let (mut ids, mut hit_ids, mut total_hits) = (0, 0, 0);
        for &(id, _) in &bank.se_map {
            let mut s = Synth::new();
            let h = s.add_bank(bank.clone());
            if s.play_se(h, id, &SeParam::default()).is_none() {
                continue;
            }
            let pcm = render_seconds(&mut s, 2.5);
            let c = clicks(&left(&pcm), 25.0, 0.04);
            ids += 1;
            if !c.is_empty() {
                hit_ids += 1;
                total_hits += c.len();
                println!("  {f} id {id:#06x}: {} outliers, first at {:.3}s d2 {:.3} (local rms {:.4})", c.len(), c[0].0 as f32 / 48000.0, c[0].1, c[0].2);
            }
        }
        println!("  {f}: {ids} SEs rendered, {hit_ids} with outliers ({total_hits} total)");
    }

    // ---- 3. loops ---------------------------------------------------------------------------------------------------------------------
    println!("== stream BGM loop seams");
    for (_c, files) in disc.listing() {
        for (path, _) in files {
            if !path.to_uppercase().ends_with(".SSV") {
                continue;
            }
            let bytes = disc.read(&path).unwrap();
            let Ok(mut sp) = StreamPlayer::from_ssv(&bytes) else { continue };
            let (Some(ls), Some(end)) = (sp.loop_start, sp.end) else {
                println!("  {path}: no loop");
                continue;
            };
            // render up to 3 s past the loop end (skip the first loop of long songs by seeking: decode just the tail)
            let tail = 6000usize;
            let mut out = vec![0.0f32; 2 * (end + tail)];
            if end > 3_000_000 && quick {
                println!("  {path}: skipped (--quick)");
                continue;
            }
            for chunk in out.chunks_mut(4096) {
                sp.mix(chunk);
            }
            let x = left(&out);
            let seam = end; // first frame after the wrap
            let step_seam = max_step(&x, seam - 2, seam + 3);
            let q = step_quantile(&x[seam.saturating_sub(48000 * 4)..seam], 0.999);
            // continuity of the content: how much of the signal near the seam resembles the signal near the loop start
            println!("  {path}: loop {:.2}s..{:.2}s, step at seam {:.4}, 99.9% step of the last 4 s {:.4} (ratio {:.2}), loop start frame {ls}", ls as f32 / 48000.0, end as f32 / 48000.0, step_seam, q, step_seam / q.max(1e-6));
        }
    }

    println!("== sequenced BGM loop repeatability");
    let mut bgms = vec![];
    for (_c, files) in disc.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if up.ends_with(".SSQ") && (up.contains("BGM401") || up.contains("BGM601") || up.contains("BGM711") || up.contains("BGM403")) {
                bgms.push(path);
            }
        }
    }
    bgms.truncate(if quick { 2 } else { 6 });
    for path in bgms {
        let bank = Bank::parse(&disc.read(&path).unwrap()).unwrap();
        let mut s = Synth::new();
        let h = s.add_bank(bank);
        let id = s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let rep = sh2_audio::synth::validate_sequence(&bank_seq(&path, &disc)).unwrap();
        println!("  {path}: sequence 0 has {} events, {} ticks, ends with {}", rep.events, rep.ticks, if rep.ends { "FF (no loop)" } else { "an endless F2 00 loop" });
        let mut pcm = vec![];
        let mut marks = vec![];
        for sec in 0..(if quick { 170 } else { 420 }) {
            pcm.extend(render_seconds(&mut s, 1.0));
            marks = s.bgm_loop_marks(id);
            if marks.len() >= 2 && pcm.len() / 2 > marks[1] as usize + 5 * 48000 {
                break;
            }
            let _ = sec;
        }
        if marks.len() < 2 || pcm.len() / 2 < marks[1] as usize + 5 * 48000 {
            println!("  {path}: fewer than 2 loop jumps within the render window ({} marks)", marks.len());
            continue;
        }
        let (a, b) = (marks[0] as usize, marks[1] as usize);
        let period = b - a;
        let w = (4 * 48000).min(period / 2);
        let x = left(&pcm);
        let off = 12000;
        let n12 = ncc(&x[a + off..a + off + w], &x[b + off..b + off + w]);
        let seam_clicks = clicks(&x[b.saturating_sub(4096)..(b + 4096).min(x.len())], 25.0, 0.04).len();
        println!("  {path}: loop period {:.3}s, NCC of the 4 s after jump 1 vs after jump 2: {n12:.3}, click outliers around the seam {seam_clicks}", period as f32 / 48000.0);
    }
}

fn bank_seq(path: &str, disc: &Disc) -> sh2_audio::sdh::Sequence {
    Bank::parse(&disc.read(path).unwrap()).unwrap().sequences[0].clone()
}
