//! Numerical self-consistency measurements used by `examples/validate.rs` and `tests/validation.rs`.
//!
//! There is no ground-truth recording of the console (no emulator capture available to the tools), so quality is checked by measuring
//! properties the hardware guarantees: pitch of a key against the equal-tempered ideal (driver quantisation included), envelope timing
//! against the SPU rate formulas, absence of discontinuities ("clicks") in rendered audio, and the seamlessness of loops.

/// Deinterleave the left channel.
pub fn left(pcm: &[f32]) -> Vec<f32> {
    pcm.chunks(2).map(|f| f[0]).collect()
}

/// Largest first difference `|x[n] - x[n-1]|` of `x[from..to]`.
pub fn max_step(x: &[f32], from: usize, to: usize) -> f32 {
    let to = to.min(x.len());
    (from.max(1)..to).map(|n| (x[n] - x[n - 1]).abs()).fold(0.0, f32::max)
}

/// Value below which `q` (0..1) of the first differences of `x` lie.
pub fn step_quantile(x: &[f32], q: f32) -> f32 {
    let mut d: Vec<f32> = x.windows(2).map(|w| (w[1] - w[0]).abs()).collect();
    if d.is_empty() {
        return 0.0;
    }
    d.sort_by(|a, b| a.partial_cmp(b).unwrap());
    d[((d.len() - 1) as f32 * q) as usize]
}

/// Click detector: positions where the second difference exceeds `ratio` times the local RMS of the second difference (excluding the
/// neighbourhood of the position itself) and an absolute floor.  Returns `(position, d2, local_rms)` of every hit.
pub fn clicks(x: &[f32], ratio: f32, floor: f32) -> Vec<(usize, f32, f32)> {
    let n = x.len();
    if n < 4096 {
        return vec![];
    }
    let d2: Vec<f32> = (1..n - 1).map(|i| (x[i + 1] - 2.0 * x[i] + x[i - 1]).abs()).collect();
    // prefix sums of d2^2 for the local RMS
    let mut ps = vec![0.0f64; d2.len() + 1];
    for (i, v) in d2.iter().enumerate() {
        ps[i + 1] = ps[i] + (*v as f64) * (*v as f64);
    }
    let w = 512usize;
    let mut out = vec![];
    for (i, &v) in d2.iter().enumerate() {
        if v < floor {
            continue;
        }
        let a = i.saturating_sub(w);
        let b = (i + w).min(d2.len());
        let skip_a = i.saturating_sub(8);
        let skip_b = (i + 8).min(d2.len());
        let sum = (ps[b] - ps[a]) - (ps[skip_b] - ps[skip_a]);
        let cnt = (b - a) - (skip_b - skip_a);
        if cnt == 0 {
            continue;
        }
        let rms = (sum.max(0.0) / cnt as f64).sqrt() as f32;
        if v > ratio * rms.max(1e-6) {
            out.push((i + 1, v, rms));
        }
    }
    out
}

/// Fundamental frequency by autocorrelation between `lo` and `hi` Hz (refined by parabolic interpolation).
pub fn fundamental_hz(x: &[f32], rate: f32, lo: f32, hi: f32) -> f32 {
    let n = x.len();
    let min_lag = (rate / hi) as usize;
    let max_lag = ((rate / lo) as usize).min(n / 2);
    let mut best = (0.0f64, 0usize);
    let r0: f64 = x.iter().map(|v| (*v as f64) * (*v as f64)).sum();
    if r0 <= 0.0 {
        return 0.0;
    }
    let mut ac = vec![0.0f64; max_lag + 2];
    for lag in min_lag.saturating_sub(1)..=max_lag + 1 {
        if lag >= n {
            break;
        }
        ac[lag] = x[..n - lag].iter().zip(&x[lag..]).map(|(a, b)| (*a as f64) * (*b as f64)).sum();
    }
    for lag in min_lag..=max_lag {
        if ac[lag] > best.0 {
            best = (ac[lag], lag);
        }
    }
    let (_, lag) = best;
    if lag == 0 {
        return 0.0;
    }
    // prefer the first strong peak (avoid octave-down picks): accept the smallest lag within 5% of the best correlation that is a local maximum
    let thr = best.0 * 0.95;
    let mut pick = lag;
    for l in min_lag.max(1)..=lag {
        if ac[l] >= thr && ac[l] >= ac[l - 1] && ac[l] >= ac[l + 1] {
            pick = l;
            break;
        }
    }
    let (a, b, c) = (ac[pick - 1], ac[pick], ac[pick + 1]);
    let denom = a - 2.0 * b + c;
    let off = if denom.abs() > 1e-12 { 0.5 * (a - c) / denom } else { 0.0 };
    rate / (pick as f32 + off as f32)
}

/// Pitch error in cents of `measured` against `expected` Hz.
pub fn cents(measured: f32, expected: f32) -> f32 {
    1200.0 * (measured / expected).log2()
}

/// RMS of an interleaved buffer between two times (seconds, 48 kHz).
pub fn rms(pcm: &[f32], from: f32, to: f32) -> f32 {
    let a = ((from * 48000.0) as usize * 2).min(pcm.len());
    let b = ((to * 48000.0) as usize * 2).min(pcm.len());
    if b <= a {
        return 0.0;
    }
    (pcm[a..b].iter().map(|v| v * v).sum::<f32>() / (b - a) as f32).sqrt()
}

/// Normalised cross-correlation of two equally long slices (1.0 = identical shape).
pub fn ncc(a: &[f32], b: &[f32]) -> f32 {
    let n = a.len().min(b.len());
    let (mut ab, mut aa, mut bb) = (0.0f64, 0.0f64, 0.0f64);
    for i in 0..n {
        ab += a[i] as f64 * b[i] as f64;
        aa += a[i] as f64 * a[i] as f64;
        bb += b[i] as f64 * b[i] as f64;
    }
    if aa <= 0.0 || bb <= 0.0 {
        return 0.0;
    }
    (ab / (aa.sqrt() * bb.sqrt())) as f32
}

/// Lag (in samples, fractional) of the autocorrelation maximum of `x` within `expected * (1 +- tol)`; `None` for a silent signal.
pub fn period_lag(x: &[f32], expected: f32, tol: f32) -> Option<f32> {
    let lo = ((expected * (1.0 - tol)) as usize).max(2);
    let hi = (expected * (1.0 + tol)).ceil() as usize + 1;
    if hi + 2 >= x.len() / 2 {
        return None;
    }
    let n = x.len() - hi - 2;
    let ac = |lag: usize| -> f64 { x[..n].iter().zip(&x[lag..lag + n]).map(|(a, b)| *a as f64 * *b as f64).sum() };
    let mut best = (f64::MIN, lo);
    for lag in lo..=hi {
        let v = ac(lag);
        if v > best.0 {
            best = (v, lag);
        }
    }
    if best.0 <= 0.0 || best.1 <= 2 {
        return None;
    }
    let (a, b, c) = (ac(best.1 - 1), best.0, ac(best.1 + 1));
    let d = a - 2.0 * b + c;
    let off = if d.abs() > 1e-12 { 0.5 * (a - c) / d } else { 0.0 };
    Some(best.1 as f32 + off as f32)
}
