//! `BBPF` line / ribbon models of the effect host: `cusCreate` / `cusShow` (ids 1000 / 1001) -> `EffectCore::CreateCustomModel` -> `BBPLineModel`.
//!
//! JP (`SLPM_602.19`) addresses: `BBPLineModel::Create(char*, bool)` 0x003070b0, `InitPacket` 0x003073a0, `CalcMatrix` 0x003079d0, `AddTime` 0x00307960,
//! `Show` 0x00306fc0 (`World::AddOT(9)`), `Hide` 0x00307020, `BBPFrame::GetMiddle` 0x00306530, `BBPFrame::CalcMatrix` 0x00306330, `BBPLine::Create` 0x00306110,
//! `EffectModel::AddCustom` 0x00305710 / `addTime` 0x00305ae0 / `calcMatrix` 0x00305810; the VU1 program is `BBPLineMpg` (`_dma_1`, JP 0x003f4540, disassembled
//! with `tools/B/vudis.py`).
//!
//! ## File format (`P` section of the EFMG, `BBPF0001`)
//! ```text
//! +0x00 "BBPF0001"   +0x08 u16 line section offset / 16   +0x0a u16 frame section offset / 16
//! line section  "BBPL"  +0x04 u16 line count  +0x10 FVector origin (model +0x80 matrix position)  +0x20.. lines, 0x30 bytes each:
//!     A  (f32 x4)  first edge point      B  (f32 x4)  second edge point      C  (f32 x4)  step vector      (w = 1)
//! frame section "BBPR"  +0x04 u16 key count  +0x10.. keys, 0x30 bytes each (`tagBBPFrameData`):
//!     +0x00 f32 time (s)  +0x04 f32 z rotation (rad)  +0x08 f32 scale[4]  +0x18 u8 rgba[4][4] (GS scale: 0x80 = 1.0)  +0x28 u8 flags (bit0: hold, no blend to the next key)
//! ```
//! ## What the VU1 program does (per line, `MSCAL 2` at entry 49)
//! `A' = Rz(angle) * A`, `B' = Rz(angle) * B`, `C' = Rz(angle) * C`; then for the four sections `i = 0..4`:
//! `off += diag(s_i, s_i, 1, 1) * C'` (**cumulative**; `x`, `y` scaled, `z` not), vertices `A' + off` and `B' + off`, both with colour `i`.  The 8 vertices of a line
//! form a Gouraud, alpha-blended, untextured triangle strip (`PRIM = 0x4c`, `GIF REGS = RGBAQ, XYZF2 x 8`, `ADC` set on the vertices that the clip test rejects).
//! The transform is `ViewScreen * CameraInverse * Model` where *Model* = translation by (header origin + world position of the frame the model is attached to).

use glam::{Vec3, Vec4};

/// One line record (0x30 bytes in the file).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct BbpLine {
    pub a: Vec4,
    pub b: Vec4,
    pub c: Vec4,
}

/// One key of `BBPFrame` (`tagBBPFrameData`, 0x30 bytes).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct BbpKey {
    pub time: f32,
    /// z rotation, radians
    pub rot: f32,
    pub scale: [f32; 4],
    /// rgba per section, GS scale (0x80 = 1.0)
    pub color: [[u8; 4]; 4],
    pub flags: u8,
}

impl Default for BbpKey {
    fn default() -> Self {
        BbpKey { time: 0.0, rot: 0.0, scale: [0.0; 4], color: [[0; 4]; 4], flags: 0 }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum BbpError {
    Magic,
    Truncated,
}

/// Parsed `BBPF` file.
#[derive(Clone, Debug)]
pub struct Bbpf {
    /// `FVector` at line section `+0x10` (the model's `+0x80` matrix position)
    pub origin: Vec3,
    pub lines: Vec<BbpLine>,
    pub keys: Vec<BbpKey>,
}

fn rd_f32(d: &[u8], o: usize) -> Option<f32> {
    d.get(o..o + 4).map(|b| f32::from_le_bytes([b[0], b[1], b[2], b[3]]))
}
fn rd_u16(d: &[u8], o: usize) -> Option<usize> {
    d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize)
}

impl Bbpf {
    /// `BBPLineModel::Create(char*, bool)` (0x003070b0) + `BBPFrame::Create` + `BBPLine::Create`.
    pub fn parse(d: &[u8]) -> Result<Bbpf, BbpError> {
        if d.get(0..8) != Some(b"BBPF0001") {
            return Err(BbpError::Magic);
        }
        let lo = rd_u16(d, 8).ok_or(BbpError::Truncated)? * 16;
        let fo = rd_u16(d, 10).ok_or(BbpError::Truncated)? * 16;
        let n = rd_u16(d, lo + 4).ok_or(BbpError::Truncated)?;
        let origin = Vec3::new(rd_f32(d, lo + 0x10).ok_or(BbpError::Truncated)?, rd_f32(d, lo + 0x14).ok_or(BbpError::Truncated)?, rd_f32(d, lo + 0x18).ok_or(BbpError::Truncated)?);
        let v4 = |o: usize| -> Option<Vec4> { Some(Vec4::new(rd_f32(d, o)?, rd_f32(d, o + 4)?, rd_f32(d, o + 8)?, rd_f32(d, o + 12)?)) };
        let mut lines = Vec::with_capacity(n);
        for i in 0..n {
            let o = lo + 0x20 + i * 0x30;
            lines.push(BbpLine { a: v4(o).ok_or(BbpError::Truncated)?, b: v4(o + 16).ok_or(BbpError::Truncated)?, c: v4(o + 32).ok_or(BbpError::Truncated)? });
        }
        let nk = rd_u16(d, fo + 4).ok_or(BbpError::Truncated)?;
        let mut keys = Vec::with_capacity(nk);
        for i in 0..nk {
            let o = fo + 0x10 + i * 0x30;
            let g = |k: usize| rd_f32(d, o + k).ok_or(BbpError::Truncated);
            let mut color = [[0u8; 4]; 4];
            for (s, c) in color.iter_mut().enumerate() {
                let p = o + 0x18 + s * 4;
                c.copy_from_slice(d.get(p..p + 4).ok_or(BbpError::Truncated)?);
            }
            keys.push(BbpKey { time: g(0)?, rot: g(4)?, scale: [g(8)?, g(12)?, g(16)?, g(20)?], color, flags: *d.get(o + 0x28).ok_or(BbpError::Truncated)? });
        }
        Ok(Bbpf { origin, lines, keys })
    }

    /// `BBPFrame::GetMiddle` (0x00306530): the key data at time `t`.
    ///
    /// Exactly the retail search: `t == key[i].time` -> key i; `key[i].time < t < key[i+1].time` -> key i when its flag bit 0 is set, else the linear blend
    /// of rotation, the four scales and (per byte, truncating) the colours; anything else (before the first key, after the last) -> the **last** key.
    pub fn middle(&self, t: f32) -> BbpKey {
        let n = self.keys.len();
        if n == 0 {
            return BbpKey::default();
        }
        for i in 0..n.saturating_sub(1) {
            let k0 = &self.keys[i];
            if t == k0.time {
                return *k0;
            }
            let k1 = &self.keys[i + 1];
            if k0.time < t && t < k1.time {
                if k0.flags & 1 == 1 {
                    return *k0;
                }
                let f = (t - k0.time) / (k1.time - k0.time);
                let mut out = *k0;
                out.rot = k0.rot + f * (k1.rot - k0.rot);
                for s in 0..4 {
                    out.scale[s] = k0.scale[s] + f * (k1.scale[s] - k0.scale[s]);
                    for c in 0..4 {
                        let (a, b) = (k0.color[s][c] as f32, k1.color[s][c] as f32);
                        out.color[s][c] = (a + f * (b - a)) as i64 as u8;
                    }
                }
                out.time = f;
                return out;
            }
        }
        self.keys[n - 1]
    }

    /// Time of the last key (the length of the animation).
    pub fn duration(&self) -> f32 {
        self.keys.last().map(|k| k.time).unwrap_or(0.0)
    }

    /// The VU1 program (`BBPLineMpg`) for the line `l` and the key data `k`: eight strip vertices `(position in model space, rgba 0..1)`.
    /// `A'`, `B'` are rotated about z only (`RotZMatrix(key.rot)`), `C'` as well; the four sections accumulate `diag(s, s, 1) * C'`.
    pub fn strip(&self, l: &BbpLine, k: &BbpKey) -> [(Vec3, Vec4); 8] {
        let (sn, cs) = k.rot.sin_cos();
        let rz = |v: Vec4| Vec3::new(v.x * cs - v.y * sn, v.x * sn + v.y * cs, v.z);
        let (a, b, c) = (rz(l.a), rz(l.b), rz(l.c));
        let mut off = Vec3::ZERO;
        let mut out = [(Vec3::ZERO, Vec4::ZERO); 8];
        for s in 0..4 {
            off += Vec3::new(c.x * k.scale[s], c.y * k.scale[s], c.z);
            let col = Vec4::new(k.color[s][0] as f32, k.color[s][1] as f32, k.color[s][2] as f32, k.color[s][3] as f32);
            // RGB: GS 0..255 untextured; alpha: 0x80 = 1.0
            let col = Vec4::new(col.x / 255.0, col.y / 255.0, col.z / 255.0, col.w / 128.0);
            out[s * 2] = (a + off, col);
            out[s * 2 + 1] = (b + off, col);
        }
        out
    }

    /// Triangle list (position, rgba) of all lines at time `t`: the strip of every line split into six triangles (the strip winding is not needed, both faces are drawn).
    pub fn triangles(&self, t: f32) -> Vec<(Vec3, Vec4)> {
        let k = self.middle(t);
        let mut v = Vec::with_capacity(self.lines.len() * 18);
        for l in &self.lines {
            let s = self.strip(l, &k);
            for i in 0..6 {
                // triangle strip -> list (alternating winding, as the GS would draw it)
                let (i0, i1, i2) = if i % 2 == 0 { (i, i + 1, i + 2) } else { (i + 1, i, i + 2) };
                v.push(s[i0]);
                v.push(s[i1]);
                v.push(s[i2]);
            }
        }
        v
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn build() -> Vec<u8> {
        // one line, two keys
        let mut d = vec![0u8; 0x10];
        d[0..8].copy_from_slice(b"BBPF0001");
        d[8..10].copy_from_slice(&1u16.to_le_bytes());
        d[10..12].copy_from_slice(&6u16.to_le_bytes()); // 0x60
        d.extend_from_slice(b"BBPL");
        d.extend_from_slice(&1u16.to_le_bytes());
        d.resize(0x10 + 0x20, 0);
        for f in [0.0f32, -0.065, 0.0, 1.0, 0.0, 0.065, 0.0, 1.0, -1.0, 0.0, 0.0, 1.0] {
            d.extend_from_slice(&f.to_le_bytes());
        }
        assert_eq!(d.len(), 0x60);
        d.extend_from_slice(b"BBPR");
        d.extend_from_slice(&2u16.to_le_bytes());
        d.resize(0x70, 0);
        for (t, rot, sc, c, a) in [(0.0f32, 0.0f32, 0.0f32, 0x00u8, 0u8), (1.0, 0.0, 2.0, 0x80, 0x64)] {
            d.extend_from_slice(&t.to_le_bytes());
            d.extend_from_slice(&rot.to_le_bytes());
            for _ in 0..4 {
                d.extend_from_slice(&sc.to_le_bytes());
            }
            for _ in 0..4 {
                d.extend_from_slice(&[0xff, c, 0, a]);
            }
            d.extend_from_slice(&[0; 8]);
        }
        d
    }

    #[test]
    fn parse_and_blend() {
        let b = Bbpf::parse(&build()).unwrap();
        assert_eq!(b.lines.len(), 1);
        assert_eq!(b.keys.len(), 2);
        let m = b.middle(0.5);
        assert!((m.scale[0] - 1.0).abs() < 1e-6);
        assert_eq!(m.color[0], [0xff, 0x40, 0, 0x32]);
        // exact key time and "past the end" -> the key itself / the last key
        assert_eq!(b.middle(0.0).scale[0], 0.0);
        assert_eq!(b.middle(5.0).scale[0], 2.0);
        // `GetMiddle` quirk: before the first key it also falls through to the last key
        assert_eq!(b.middle(-1.0).scale[0], 2.0);
    }

    #[test]
    fn strip_is_cumulative_and_scales_xy_only() {
        let b = Bbpf::parse(&build()).unwrap();
        let k = BbpKey { scale: [1.0, 2.0, 3.0, 4.0], ..BbpKey::default() };
        let s = b.strip(&b.lines[0], &k);
        // C = (-1, 0, 0): x = -1, -3, -6, -10
        let xs: Vec<f32> = (0..4).map(|i| s[i * 2].0.x).collect();
        assert_eq!(xs, vec![-1.0, -3.0, -6.0, -10.0]);
        assert!((s[0].0.y + 0.065).abs() < 1e-6 && (s[1].0.y - 0.065).abs() < 1e-6);
    }

    #[test]
    fn rotation_is_about_z() {
        let b = Bbpf::parse(&build()).unwrap();
        let k = BbpKey { rot: std::f32::consts::FRAC_PI_2, scale: [1.0; 4], ..BbpKey::default() };
        let s = b.strip(&b.lines[0], &k);
        // C (-1, 0) rotated by 90 degrees -> (0, -1)
        assert!((s[2].0.y - s[0].0.y + 1.0).abs() < 1e-5);
    }

    /// Every `P` section of the shipped US effects parses, and effect 9 matches the layout noted in the module doc (16 rays on a circle of radius 0.065, 3 keys).
    #[test]
    fn disc_sections_parse() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = sh2_core::fileio::Disc::open(&dir) else { return };
        let mut n = 0;
        for id in [9, 10, 11, 17, 33, 34, 90, 95, 98, 100, 149, 219] {
            let Ok(bytes) = d.read(&format!("EFFECT/{id:03}_00.EFD")) else { return };
            let e = sh2_script::efmg::Efmg::parse(&bytes).unwrap();
            for (_, sec) in e.iter_kind(b'P') {
                let b = Bbpf::parse(sec).unwrap();
                assert!(!b.lines.is_empty());
                assert!(!b.keys.is_empty());
                assert!(b.keys.windows(2).all(|w| w[0].time <= w[1].time));
                assert!(b.lines.iter().all(|l| l.a.w == 1.0 && l.b.w == 1.0));
                n += 1;
            }
            if id == 9 {
                let b = Bbpf::parse(e.find(b'P', 0).unwrap()).unwrap();
                assert_eq!(b.lines.len(), 16);
                assert_eq!(b.keys.len(), 3);
                for l in &b.lines {
                    assert!((l.a.truncate().length() - 0.065).abs() < 1e-3);
                    assert!((l.a + l.b).truncate().length() < 1e-3); // B = -A
                }
                assert!((b.keys[2].time - 0.8333).abs() < 1e-3);
            }
        }
        assert!(n >= 12, "{n}");
    }
}
