//! Which banks use the driver's LFO / key-follow / crossfade features (decides what the synth must implement).
use sh2_audio::Bank;
use sh2_core::fileio::Disc;
use std::collections::BTreeMap;

fn main() {
    let disc = Disc::from_env().unwrap();
    let mut n_prog = 0;
    let mut pitch_lfo = 0;
    let mut amp_lfo = 0;
    let mut tone_lfo_flag = BTreeMap::<u8, usize>::new();
    let mut tone_rev = BTreeMap::<u8, usize>::new();
    let mut kf = [0usize; 6];
    let mut fadeflags = (0usize, 0usize, 0usize, 0usize);
    let mut prio = BTreeMap::<(u8, u8), usize>::new();
    let mut ex = vec![];
    for (_c, files) in disc.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if !(up.ends_with(".SSE") || up.ends_with(".SSQ")) { continue; }
            let Ok(bank) = Bank::parse_opts(&disc.read(&path).unwrap(), false) else { continue };
            for p in &bank.programs {
                if p.splits.is_empty() { continue; }
                n_prog += 1;
                if p.b(9) & 0xf != 0 { pitch_lfo += 1; if ex.len() < 6 { ex.push(format!("{path} prog pitchlfo type {} period {} amp {:?}", p.b(9) & 0xf, p.u16(0xe), (p.s16(0x18), p.s16(0x1a)))); } }
                if p.b(9) >> 4 != 0 { amp_lfo += 1; println!("  amp-LFO program in {path}: type {} period {} depth {:?}", p.b(9) >> 4, p.u16(0xe), (p.s16(0x18), p.s16(0x1a))); }
                for s in &p.splits {
                    if s.fade_in { fadeflags.0 += 1; }
                    if s.fade_out { fadeflags.1 += 1; }
                }
            }
            for t in &bank.tones {
                let r = &t.raw;
                *tone_lfo_flag.entry(r.get(0x25).copied().unwrap_or(0) >> 6).or_default() += 1;
                *tone_rev.entry(r.get(5).copied().unwrap_or(0)).or_default() += 1;
                if r.len() > 0x18 {
                    for (i, o) in [0x10usize, 0x11, 0x12, 0x13].iter().enumerate() {
                        let v = r[*o];
                        let nz = if i == 3 { (v as i8) >> 3 != 0 } else if i == 2 { v & 0x1f != 0 } else { v != 0 };
                        if nz { kf[i] += 1; }
                    }
                    if (u16::from_le_bytes([r[0x12], r[0x13]]) >> 5) & 0x3f != 0 { kf[4] += 1; }
                }
                *prio.entry((r.get(6).copied().unwrap_or(0), r.get(7).copied().unwrap_or(0) & 0x3f)).or_default() += 1;
                if r.get(4).copied().unwrap_or(0) & 0x80 != 0 { fadeflags.2 += 1; }
                if r.get(2).copied().unwrap_or(0) & 0x80 != 0 { fadeflags.3 += 1; }
            }
        }
    }
    println!("programs {n_prog}, pitch LFO {pitch_lfo}, amp LFO {amp_lfo}");
    println!("tone[0x25]>>6 histogram {tone_lfo_flag:?}");
    println!("tone[5] (reverb/dry bits) histogram {tone_rev:?}");
    println!("tone key-follow nonzero: attack {} sustain-rate {} decay {} sus-level {} release {}", kf[0], kf[1], kf[2], kf[3], kf[4]);
    println!("split fade_in {} fade_out {}  tone[4].7 {} tone[2].7 {}", fadeflags.0, fadeflags.1, fadeflags.2, fadeflags.3);
    println!("(prio, group) top: {:?}", prio.iter().take(12).collect::<Vec<_>>());
    for e in ex { println!("  {e}"); }
}
