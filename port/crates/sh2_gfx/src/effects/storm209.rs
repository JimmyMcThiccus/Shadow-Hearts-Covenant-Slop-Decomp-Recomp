//! Background effect type 209 `FpRetailStorm209` (US only, `notes/I/fp_retail.md`; SLUS_210.41 `Create` 0x002e3150, `CreateObjects` 0x002e17c0,
//! `FpObjectRetailStorm209B::CalculateFunc` 0x002e62d0).  Shipped in WE_01_U only (3 records).
//!
//! `Create(param)`: `InitFpFlag(param[0])` (flag byte 2 bit 0x80 -> prim `+0x58` = 0), then the variant `+0x70`: 0 by default, 1 when `+0x58 == 0`
//! and the layer `+0x54` is 10 (the default), 2 when it is 9.  WE_01_U: slot 15 (flag 0x210a0000) = variant 0, slots 18 / 19 (0x218a0000) = variant 1.
//!
//! * **Variant 1 / 2** (ported here): an electric orb at `(-28.3, -36.5, -69)` -- an `FpFlare` (colour bytes `30 6c a8 80`, size 70 x 0.73, rate 0.8,
//!   one sprite) with three 10-node free bolts (`+0xc4/+0xc8/+0xcc`: outer `dc dc ff 78`, inner `00 80 c8 50`, widths 0.1 / 0.5, 60 deg) that
//!   `CalculateFunc` re-aims every frame from the orb to a random point within +-10 per axis (`SetPos` + `ChangeForm(1)`), five 30-node
//!   symmetric arcs at fixed places (`+0x98..+0xa8`, inner `00 c8 96 32`, variant 2 alpha 0x50) and two more without depth test (`+0xb0/+0xb4`,
//!   inner `c8 32 00 32` / 0x50), all `ChangeForm(0.8)` every frame.
//! * **Variant 0** (not ported): the scripted thunderstorm (`FpObjectRetailStorm209`, a 9 KB `CalculateFunc` timeline driving 8 + 3 bolts, an
//!   `FpFlare`, an `FpSmoke`-like object and the `FpRetailLenz6B` flare); [`Storm209::new`] returns `None` for it.

use glam::{Vec3, Vec4};

use super::bgfx::{BgCamera, BgFx, BgQuad, FefFlare};
use super::compat::Rand;
use super::thunder::{Thunder, ThunderParam};

/// The orb centre of variants 1 / 2 (`CreateObjects` literal `(-28.3, -36.5, -69)`).
pub const ORB: Vec3 = Vec3::new(-28.3, -36.5, -69.0);

fn f(bits: u32) -> f32 {
    f32::from_bits(bits)
}

struct Bolt {
    t: Thunder,
    ztest: bool,
    /// `ChangeForm` argument of every frame
    form: f32,
    /// re-aimed from the orb every frame (`+0xc4/+0xc8/+0xcc`)
    sparks: bool,
}

/// One type 209 record.
pub struct Storm209 {
    pub variant: u8,
    bolts: Vec<Bolt>,
    flare: BgFx,
    acc: f32,
}

impl Storm209 {
    /// `Create(param)`: `flag` = the record's first word (`InitFpFlag`).  `None` for variant 0 (not ported).
    pub fn new(flag: u32, rng: &mut dyn Rand) -> Option<Storm209> {
        let b2 = (flag >> 16) as u8;
        let ztest_flag = b2 & 0x80 == 0; // `+0x58`
        let layer = if b2 & 0x40 != 0 { b2 & 0x1f } else { 10 }; // `+0x54`
        let variant = match (ztest_flag, layer) {
            (false, 10) => 1,
            (false, 9) => 2,
            _ => 0,
        };
        if variant == 0 {
            return None;
        }
        let cam = Vec3::Z;
        let mk = |start: Vec3, end: Vec3, inner: [u8; 4], nodes: i32, symmetric: bool| ThunderParam {
            start,
            end,
            c_outer: [0xdc, 0xdc, 0xff, 0x78],
            c_inner: inner,
            w_outer: 0.1,
            w_inner: 0.5,
            angle: 60.0,
            nodes,
            symmetric,
        };
        let mut bolts = Vec::new();
        // +0xc4 / +0xc8 / +0xcc: sparks around the orb
        for _ in 0..3 {
            let p = mk(Vec3::ZERO, Vec3::new(100.0, -100.0, 100.0), [0x00, 0x80, 0xc8, 0x50], 10, false);
            bolts.push(Bolt { t: Thunder::new(p, cam, rng), ztest: true, form: 1.0, sparks: true });
        }
        let a = if variant == 2 { 0x50 } else { 0x32 };
        // +0x98..+0xa8: `SetPos(start, end)` literals
        let arcs: [([u32; 3], [u32; 3]); 5] = [
            ([0x41b16a7f, 0xc205fcee, 0xc26a851f], [0x41dd5810, 0xc205fcee, 0xc29777cf]),
            ([0x417170a4, 0xc205fcee, 0xc2754189], [0x41a27efa, 0xc205fcee, 0xc29a9db2]),
            ([0x40e5a9fc, 0xc1f3f9db, 0xc27e851f], [0x414ab021, 0xc1f3f9db, 0xc29d77cf]),
            ([0x40800000, 0xc1c3f9db, 0xc282a0c5], [0x4114fdf4, 0xc1c3f9db, 0xc29e9db2]),
            ([0x40400000, 0xc18bf9db, 0xc285428f], [0x4109999a, 0xc18bf9db, 0xc2a177cf]),
        ];
        let v = |w: [u32; 3]| Vec3::new(f(w[0]), f(w[1]), f(w[2]));
        for (s, e) in arcs {
            let p = mk(v(s), v(e), [0x00, 0xc8, 0x96, a], 30, true);
            bolts.push(Bolt { t: Thunder::new(p, cam, rng), ztest: true, form: 0.8, sparks: false });
        }
        // +0xb0 / +0xb4: drawn over everything (vtable +0x30(0))
        let reds: [([u32; 3], [u32; 3]); 2] = [
            ([0x4208fae1, 0xc18c4dd3, 0xc25ff6c9], [0x4203c189, 0xc1d0ac08, 0xc26a9168]),
            ([0x421bd604, 0xc18c4fdf, 0xc28dc7ae], [0x42165f3b, 0xc1d0ac08, 0xc28bf9db]),
        ];
        for (s, e) in reds {
            let p = mk(v(s), v(e), [0xc8, 0x32, 0x00, a], 30, true);
            bolts.push(Bolt { t: Thunder::new(p, cam, rng), ztest: false, form: 0.8, sparks: false });
        }
        // +0xd0: `FpFlare::CreateFromParam` (0x002a74e0): colour bytes x 0.502, size x 0.73 (param +0x30 bit 0 clear)
        let col = |b: u8| b as f32 * 0.501_960_8;
        let fl = FefFlare {
            pos: ORB,
            color: Vec4::new(col(0x30), col(0x6c), col(0xa8), col(0x80)),
            size: 70.0 * 0.73,
            pull: 0.0,
            rate: 0.8,
            min: 0.0,
            amp: 0.0,
            phase: 0.0,
            n: 1,
            flags: 0,
            dir: Vec4::ZERO,
        };
        let flare = BgFx::from_flare(&fl, rng.rand() | 1);
        Some(Storm209 { variant, bolts, flare, acc: 0.0 })
    }

    /// `CalculateFunc` once per 1/30 s frame (`frames` may be fractional; whole frames are run).
    pub fn step(&mut self, frames: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        self.flare.step_cam(frames, cam);
        self.acc += frames;
        let fwd = if cam.forward.length_squared() > 0.0 { cam.forward.normalize() } else { Vec3::Z };
        while self.acc >= 1.0 {
            self.acc -= 1.0;
            for b in &mut self.bolts {
                if b.sparks {
                    // `20 * (0.5 - rand)` per axis (z, y, x drawn in this order)
                    let mut r = || 20.0 * (0.5 - rng.rand1());
                    let (z, y, x) = (r(), r(), r());
                    b.t.set_pos(ORB, ORB + Vec3::new(x, y, z));
                }
                b.t.change_form(b.form, fwd, rng);
            }
        }
    }

    pub fn quads(&self, alpha: f32, out: &mut Vec<BgQuad>) {
        for b in &self.bolts {
            b.t.quads(alpha, b.ztest, out);
        }
        let mut fl = self.flare.quads();
        for q in &mut fl {
            q.rgba.w *= alpha;
        }
        out.extend(fl);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn variants_from_the_flag_word() {
        let mut rng = XorShift(9);
        assert!(Storm209::new(0x210a_0000, &mut rng).is_none());
        let s = Storm209::new(0x218a_0000, &mut rng).expect("variant 1");
        assert_eq!(s.variant, 1);
        assert_eq!(s.bolts.len(), 10);
    }

    #[test]
    fn sparks_stay_near_the_orb() {
        let mut rng = XorShift(4);
        let mut s = Storm209::new(0x218a_0000, &mut rng).unwrap();
        let cam = BgCamera { pos: Vec3::new(0.0, -40.0, 100.0), forward: Vec3::new(0.0, 0.0, -1.0), ..BgCamera::default() };
        for _ in 0..10 {
            s.step(1.0, &cam, &mut rng);
        }
        let mut q = vec![];
        s.quads(1.0, &mut q);
        assert!(!q.is_empty());
        assert!(q.iter().all(|q| q.center.is_finite() && q.rgba.w >= 0.0 && q.rgba.w <= 128.5));
        // every spark bolt ends within the +-10 box around the orb
        for b in s.bolts.iter().filter(|b| b.sparks) {
            assert!(b.t.points().iter().all(|p| (*p - ORB).abs().max_element() < 25.0), "{:?}", b.t.points());
        }
        assert!(q.iter().any(|q| !q.ztest));
    }
}
