//! `EFCM` (camera) and `EFLT` (light) key tables — `EffectCameraMotion` / `EffectLightMotion`.
//!
//! Both are flat tables of 0x40-byte keys, linearly interpolated by time (seconds*30?  the
//! time base is whatever `EffectCore::AddTimeAll` feeds: `add_time` scalar `1/30` per call).
//!
//! `EFCM` (section kind `E`): header `"EFCM" "0002"`, u16 key count at +4?? — see
//! `EffectCamera::Create`: the key table header is found at `data + u16(data+8)*0x10`; there `"EFCT"`,
//! u16 count at +4, keys at +0x10.
//! key (0x40): `pos:f32[4]` @0, `target:f32[4]` @0x10, `time:f32` @0x20, `fov:u16` @0x24, `roll:f32` @0x2c.
//!
//! `EFLT` (kind `L`): `"EFLT" "0001"`, header byte @8 low 3 bits = light type (0 point, 1 directional,
//! 2 spot, 3 ambient); key table header at `data + u16(data+0xc)*0x10` (`"EFLM"`, u16 count @4, keys @0x10).
//! key (0x40): `color:f32[4]` @0, `pos` @0x10 (always replaced by origin when sampled), `dir:f32[4]`
//! @0x20, `time:f32` @0x30.

fn f32_at(d: &[u8], o: usize) -> f32 {
    f32::from_le_bytes([d[o], d[o + 1], d[o + 2], d[o + 3]])
}
fn v4_at(d: &[u8], o: usize) -> [f32; 4] {
    [f32_at(d, o), f32_at(d, o + 4), f32_at(d, o + 8), f32_at(d, o + 12)]
}
fn lerp4(a: [f32; 4], b: [f32; 4], k: f32) -> [f32; 4] {
    [a[0] + k * (b[0] - a[0]), a[1] + k * (b[1] - a[1]), a[2] + k * (b[2] - a[2]), a[3] + k * (b[3] - a[3])]
}

/// NOTE: `EffectCamera::LookAt` (JP 0x003080b0) reads the vector at +0 (`pos` here) as the point looked at (`GetInter`) and the vector at +0x10 (`target` here) as the
/// **eye** (`GetPos`): the field names are historical, `sh2_gfx::effects::scene::FxScene::camera_pose` swaps them.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct CameraKey {
    pub pos: [f32; 4],
    pub target: [f32; 4],
    pub time: f32,
    pub fov: u16,
    pub roll: f32,
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct LightKey {
    pub color: [f32; 4],
    pub dir: [f32; 4],
    pub time: f32,
}

pub struct CameraMotion {
    pub keys: Vec<CameraKey>,
    /// `+8`: current time, advanced by `add_time`.
    pub time: f32,
}

pub struct LightMotion {
    pub light_type: u8,
    pub keys: Vec<LightKey>,
    pub time: f32,
}

fn u16_at(d: &[u8], o: usize) -> Option<usize> {
    d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize)
}

impl CameraMotion {
    /// Parse an `EFCM` section.
    pub fn parse(sec: &[u8]) -> Option<Self> {
        if sec.get(0..4)? != b"EFCM" {
            return None;
        }
        let hdr = u16_at(sec, 8)? * 0x10;
        let n = u16_at(sec, hdr + 4)?;
        let base = hdr + 0x10;
        let mut keys = Vec::with_capacity(n);
        for i in 0..n {
            let o = base + i * 0x40;
            sec.get(o..o + 0x40)?;
            keys.push(CameraKey {
                pos: v4_at(sec, o),
                target: v4_at(sec, o + 0x10),
                time: f32_at(sec, o + 0x20),
                fov: u16::from_le_bytes([sec[o + 0x24], sec[o + 0x25]]),
                roll: f32_at(sec, o + 0x2c),
            });
        }
        Some(CameraMotion { keys, time: 0.0 })
    }

    /// `AddTime(f)` (0x0030a3f0).
    pub fn add_time(&mut self, dt: f32) {
        self.time += dt;
    }

    /// `GetData` (0x0030a420): returns the interpolated key and `true` once the motion is past the end.
    /// Bug-compatible: a time before the first key falls through to the last key.
    pub fn sample(&self) -> (CameraKey, bool) {
        let n = self.keys.len();
        if n == 0 {
            return (CameraKey { pos: [0.0, 0.0, 0.0, 1.0], target: [0.0, 0.0, 1.0, 1.0], time: 0.0, fov: 0, roll: 0.0 }, true);
        }
        for i in 0..n - 1 {
            let a = &self.keys[i];
            if self.time == a.time {
                return (*a, false);
            }
            let b = &self.keys[i + 1];
            if a.time < self.time && self.time < b.time {
                let k = (self.time - a.time) / (b.time - a.time);
                let mut o = *a;
                o.time = k;
                o.pos = lerp4(a.pos, b.pos, k);
                o.target = lerp4(a.target, b.target, k);
                o.fov = (a.fov as f32 + k * (b.fov as i32 - a.fov as i32) as f32) as u16;
                o.roll = a.roll + k * (b.roll - a.roll);
                return (o, false);
            }
        }
        (self.keys[n - 1], true)
    }
}

impl LightMotion {
    pub fn parse(sec: &[u8]) -> Option<Self> {
        if sec.get(0..4)? != b"EFLT" {
            return None;
        }
        let light_type = *sec.get(8)? & 7;
        let hdr = u16_at(sec, 0xc)? * 0x10;
        let n = u16_at(sec, hdr + 4)?;
        let base = hdr + 0x10;
        let mut keys = Vec::with_capacity(n);
        for i in 0..n {
            let o = base + i * 0x40;
            sec.get(o..o + 0x40)?;
            keys.push(LightKey { color: v4_at(sec, o), dir: v4_at(sec, o + 0x20), time: f32_at(sec, o + 0x30) });
        }
        Some(LightMotion { light_type, keys, time: 0.0 })
    }

    pub fn add_time(&mut self, dt: f32) {
        self.time += dt;
    }

    /// `EffectLightMotion::GetData` (0x00319620).
    pub fn sample(&self) -> (LightKey, bool) {
        let n = self.keys.len();
        if n == 0 {
            return (LightKey { color: [0.0; 4], dir: [0.0; 4], time: 0.0 }, true);
        }
        for i in 0..n - 1 {
            let a = &self.keys[i];
            if self.time == a.time {
                return (*a, false);
            }
            let b = &self.keys[i + 1];
            if a.time < self.time && self.time < b.time {
                let k = (self.time - a.time) / (b.time - a.time);
                let mut o = *a;
                o.time = k;
                o.color = lerp4(a.color, b.color, k);
                o.dir = lerp4(a.dir, b.dir, k);
                return (o, false);
            }
        }
        (self.keys[n - 1], true)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn efcm(keys: &[(f32, f32)]) -> Vec<u8> {
        // header: "EFCM0002", u16 @8 = 1 (table at 0x10), table hdr "EFCT" count @+4, keys at +0x10
        let mut d = vec![0u8; 0x10 + 0x10 + keys.len() * 0x40];
        d[0..8].copy_from_slice(b"EFCM0002");
        d[8..10].copy_from_slice(&1u16.to_le_bytes());
        d[0x10..0x14].copy_from_slice(b"EFCT");
        d[0x14..0x16].copy_from_slice(&(keys.len() as u16).to_le_bytes());
        for (i, (t, x)) in keys.iter().enumerate() {
            let o = 0x20 + i * 0x40;
            d[o..o + 4].copy_from_slice(&x.to_le_bytes());
            d[o + 0x20..o + 0x24].copy_from_slice(&t.to_le_bytes());
            d[o + 0x24..o + 0x26].copy_from_slice(&(i as u16 * 100).to_le_bytes());
        }
        d
    }

    #[test]
    fn camera_interpolates_and_ends() {
        let d = efcm(&[(0.0, 0.0), (1.0, 10.0), (2.0, 30.0)]);
        let mut m = CameraMotion::parse(&d).unwrap();
        m.add_time(0.5);
        let (k, end) = m.sample();
        assert!(!end);
        assert!((k.pos[0] - 5.0).abs() < 1e-5);
        assert_eq!(k.fov, 50);
        m.add_time(0.5); // exactly key 1
        assert_eq!(m.sample().0.pos[0], 10.0);
        m.add_time(5.0);
        let (k, end) = m.sample();
        assert!(end);
        assert_eq!(k.pos[0], 30.0);
    }
}
