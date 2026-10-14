//! Numerical validation on real disc data (skipped without a disc; JP default, `SH2_DISC_DIR` overrides).  See `examples/validate.rs` for the
//! full report.  The slow render-minutes checks are `#[ignore]`d: run them with
//! `SH2_DISC_DIR=<disc> cargo test -p sh2_audio --test validation -- --ignored`.

use sh2_audio::stream::StreamPlayer;
use sh2_audio::synth::render_seconds;
use sh2_audio::validate::*;
use sh2_audio::{spu, Bank, Synth};
use sh2_core::fileio::Disc;
use sh2_script::audio::{BgmParam, SeParam};

const JP: &str = "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)";

fn disc() -> Option<Disc> {
    Disc::open(std::env::var("SH2_DISC_DIR").unwrap_or_else(|_| JP.to_string())).ok()
}

#[test]
fn driver_pitch_table_is_equal_tempered_above_the_bottom_octaves() {
    // analytic: the integer frequency table of the IOP is exact to 12 cents from key 24 up, and up to 49 cents flat below (a property of the
    // original driver: Note2Freq truncates to whole Hz before the division)
    for key in 24..=100 {
        let reg = spu::pitch_reg(key * 128, 60, 48000) as f32;
        let ideal = 4096.0 * 2f32.powf((key - 60) as f32 / 12.0);
        if ideal > 16000.0 {
            continue;
        }
        assert!(cents(reg, ideal).abs() < 12.0, "key {key}: {} cents", cents(reg, ideal));
    }
    let worst_low = (0..24).map(|k| cents(spu::pitch_reg(k * 128, 60, 48000) as f32, 4096.0 * 2f32.powf((k - 60) as f32 / 12.0)).abs()).fold(0.0, f32::max);
    assert!(worst_low < 50.0, "{worst_low}");
}

#[test]
fn system_se_have_no_clicks_and_a_bounded_level() {
    let Some(d) = disc() else { return };
    for f in ["COMMON/SYSREG.SSE", "BTLDATA/SOUND/SYSTEM/SYSBTL.SSE"] {
        let bank = Bank::parse(&d.read(f).unwrap()).unwrap();
        for &(id, _) in &bank.se_map {
            let mut s = Synth::new();
            let h = s.add_bank(bank.clone());
            if s.play_se(h, id, &SeParam::default()).is_none() {
                continue;
            }
            let pcm = render_seconds(&mut s, 2.5);
            let c = clicks(&left(&pcm), 25.0, 0.04);
            assert!(c.is_empty(), "{f} id {id:#x}: click at {:?}", c.first());
            let peak = pcm.iter().fold(0f32, |m, v| m.max(v.abs()));
            assert!(peak > 0.01 && peak < 1.0, "{f} id {id:#x}: peak {peak}");
        }
    }
}

#[test]
fn stream_bgm_loops_without_a_seam() {
    let Some(d) = disc() else { return };
    let bytes = d.read("FIELD/SOUND/BGM/BGM006.SSV").unwrap();
    let mut sp = StreamPlayer::from_ssv(&bytes).unwrap();
    let end = sp.end.unwrap();
    let mut out = vec![0.0f32; 2 * (end + 4800)];
    for chunk in out.chunks_mut(4096) {
        sp.mix(chunk);
    }
    let x = left(&out);
    // the loop wraps at `end`; the step across the seam must be an ordinary sample step
    let seam = max_step(&x, end - 2, end + 3);
    let q = step_quantile(&x[end - 48000 * 4..end], 0.999);
    assert!(seam <= q, "seam step {seam} vs 99.9% step {q}");
}

#[test]
fn rendered_tones_are_in_tune_with_the_ideal_ratio() {
    let Some(d) = disc() else { return };
    let bank = Bank::parse(&d.read("FIELD/SOUND/BGM/BGM601.SSQ").unwrap()).unwrap();
    let mut errs = vec![];
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
        let key = sp.key_lo.max(48);
        if key > sp.key_hi {
            continue;
        }
        let pitch = key as f32 + sp.coarse as f32 + p.coarse as f32 + (t.fine() as f32 + sp.fine as f32 + p.fine as f32) / 128.0;
        let step = w.rate as f32 / 48000.0 * 2f32.powf((pitch - t.root_key() as f32) / 12.0);
        let expected = n_loop as f32 / step;
        if !(4.0..6000.0).contains(&expected) {
            continue;
        }
        let mut s = Synth::new();
        let h = s.add_bank(bank.clone());
        s.play_note(h, pi as u8, key, 100);
        let pcm = render_seconds(&mut s, 0.9);
        if let Some(lag) = period_lag(&left(&pcm)[24000..40000], expected, 0.03) {
            errs.push(cents(expected, lag).abs());
        }
    }
    assert!(errs.len() >= 3, "too few tonal programs measured: {}", errs.len());
    let worst = errs.iter().cloned().fold(0.0, f32::max);
    assert!(worst < 15.0, "worst pitch deviation {worst} cents over {} tones", errs.len());
}

/// Needs minutes of rendered audio (BGM401 loops every ~183 s): `-- --ignored`.
#[test]
#[ignore = "renders ~6 minutes of audio; run with --ignored (SH2_DISC_DIR)"]
fn sequenced_bgm_loop_repeats_sample_for_sample_closely() {
    let Some(d) = disc() else { return };
    for path in ["FIELD/SOUND/BGM/BGM601.SSQ", "BTLDATA/SOUND/BGM/BGM403.SSQ"] {
        let bank = Bank::parse(&d.read(path).unwrap()).unwrap();
        let mut s = Synth::new();
        let h = s.add_bank(bank);
        let id = s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let mut pcm = vec![];
        let mut marks = vec![];
        for _ in 0..420 {
            pcm.extend(render_seconds(&mut s, 1.0));
            marks = s.bgm_loop_marks(id);
            if marks.len() >= 2 && pcm.len() / 2 > marks[1] as usize + 5 * 48000 {
                break;
            }
        }
        assert!(marks.len() >= 2, "{path}: no loop jumps");
        let (a, b) = (marks[0] as usize, marks[1] as usize);
        let x = left(&pcm);
        let w = 4 * 48000;
        let n = ncc(&x[a + 12000..a + 12000 + w], &x[b + 12000..b + 12000 + w]);
        assert!(n > 0.95, "{path}: loop passes differ (NCC {n})");
        assert!(clicks(&x[b - 4096..b + 4096], 25.0, 0.04).is_empty(), "{path}: click at the loop seam");
    }
}
