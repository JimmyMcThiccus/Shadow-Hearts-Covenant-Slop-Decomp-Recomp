//! `WaterAtomicP1` runtime (JP `Cleate` 0x0025ad00, `addTime` 0x0025ab60): the water surface is an ordinary rigid `Pack1` atomic whose
//! **U texture coordinate** is wobbled every update (the vertices do not move).
//!
//! * `Cleate` keeps a copy of the file UVs and builds two tables indexed by the *wave group* (low byte of the vertex's `w` word, a signed
//!   `char` in the original): `amplitude[g] = rand()/2^31 * 200 + 50` (UV units of 1/4096) and `phase[g] = rand()/2^31 * 2 pi`.
//! * `addTime(dt)`: for **every vertex in order**: `phase[g] += 1.5 * dt` (wrapped by `-2 pi` at `>= pi`), then
//!   `u = u0 + (short)(amplitude[g] * sin(phase[g]))`, `v = v0`.  A group with `k` vertices therefore advances `k` times per update -- kept as is.
//!
//! No model on either disc contains a water atomic (census over every `SSH1.01a` image of the JP Furokuban and the US retail disc:
//! 0 of 1,468 / 4,946), so this path is exercised by unit tests only.

use sh2_formats::model::AtomicDef;

#[derive(Clone, Debug)]
pub struct WaterState {
    amplitude: Vec<f32>,
    phase: Vec<f32>,
    base_uv: Vec<[i32; 2]>,
    groups: Vec<u8>,
}

impl WaterState {
    /// `WaterAtomicP1::Cleate`; `seed` replaces the C library `rand()` state.
    pub fn new(a: &AtomicDef, seed: u32) -> Self {
        let n = a.vertex_count as usize;
        let mut s = seed | 1;
        let mut rnd = move || {
            s = s.wrapping_mul(1664525).wrapping_add(1013904223);
            (s >> 8) as f32 / (1u32 << 24) as f32
        };
        let base_uv: Vec<[i32; 2]> = a.geometry.uvs.iter().map(|uv| [(uv[0] * 4096.0).round() as i32, (uv[1] * 4096.0).round() as i32]).collect();
        let mut amplitude = vec![0.0; n.max(256)];
        let mut phase = vec![0.0; n.max(256)];
        for &g in &a.geometry.group {
            let g = g as usize;
            amplitude[g] = rnd() * 200.0 + 50.0;
            phase[g] = rnd() * 6.283184;
        }
        WaterState { amplitude, phase, base_uv, groups: a.geometry.group.clone() }
    }

    /// `WaterAtomicP1::addTime(dt)`: returns the new UV array (0..1 units).
    pub fn add_time(&mut self, dt: f32) -> Vec<[f32; 2]> {
        let step = dt * 1.5;
        let mut out = Vec::with_capacity(self.base_uv.len());
        for (i, uv) in self.base_uv.iter().enumerate() {
            let g = self.groups.get(i).copied().unwrap_or(0) as usize;
            self.phase[g] += step;
            if self.phase[g] >= 3.141592 {
                self.phase[g] -= 6.283184;
            }
            let du = (self.amplitude[g] * self.phase[g].sin()) as i32;
            out.push([(uv[0] + du) as f32 / 4096.0, uv[1] as f32 / 4096.0]);
        }
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use sh2_formats::model::{AtomicKind, Geometry};

    fn water(n: usize, groups: Vec<u8>) -> AtomicDef {
        AtomicDef {
            name: "w".into(),
            kind: AtomicKind::Water,
            vertex_count: n as u32,
            flags: 0,
            texture: 0,
            texture2: 0,
            b14: 0x41,
            b15: 0x0e,
            b16: 0,
            b17: 0,
            shared_ref: -1,
            tri_hint: 0,
            extra20: 0,
            chunks: Vec::new(),
            geometry: Geometry { uvs: vec![[0.5, 0.25]; n], group: groups, ..Default::default() },
            file_offset: 0,
        }
    }

    #[test]
    fn u_wobbles_within_the_amplitude_and_v_is_untouched() {
        let a = water(4, vec![0, 0, 1, 1]);
        let mut w = WaterState::new(&a, 7);
        let mut lo = f32::MAX;
        let mut hi = f32::MIN;
        for _ in 0..600 {
            let uv = w.add_time(1.0 / 60.0);
            for u in &uv {
                assert_eq!(u[1], 0.25);
                lo = lo.min(u[0]);
                hi = hi.max(u[0]);
            }
        }
        // amplitude 50..250 / 4096 around u = 0.5
        assert!(hi - lo > 0.01 && hi - lo < 0.13 && lo < 0.5 && hi > 0.5, "{lo} {hi}");
    }

    #[test]
    fn group_phase_advances_once_per_vertex() {
        let a = water(3, vec![5, 5, 5]);
        let mut w = WaterState::new(&a, 1);
        let p0 = w.phase[5];
        w.add_time(0.1);
        assert!((w.phase[5] - (p0 + 3.0 * 0.15)).abs() < 1e-4 || w.phase[5] < p0);
    }
}
