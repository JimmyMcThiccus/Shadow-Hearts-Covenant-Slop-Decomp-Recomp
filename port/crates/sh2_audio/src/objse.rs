//! Field object sounds (`CField::SetObjSE / UpdateObjSE / AutoLoadSE`, JP FIELD.BIN 0x004d5990 / 0x004d7380 / 0x004d5f10, `Calc3DPosition`
//! 0x004d65e0, `Exp3DVolume` 0x004d60e0, `Exp3DVolumeC` 0x004d7250; decomp/G/CField.c, FieldFree.c): the ambient / positional sounds of a map.
//!
//! Every map's `OBJSE` chunk (`AutoLoadSE`) names up to three SE banks and lists the sounds (48 slots); the script op 0x5c `SetObjSE` adds or
//! clears slots.  Every field frame `UpdateObjSE` places each positional sound relative to the camera (position + forward axis + focal length
//! of the active `GsxCamera`), turns the distance into a volume (three fall-off curves), the direction into a pan, attenuates sources outside
//! the view cone (0.7 .. 1.0) and starts / updates / releases the SE.
//!
//! ```text
//! OBJSE chunk   u16 count, u16 ?, u16 reverb @4, char bank[3][16] @0x10, records from 0x60
//! record        u32 se id (global), u8 kind (low nibble) | points (high nibble, kind 2), u8 flags (bits 0-1 play, bits 2-3 fall-off curve),
//!               2 B, then kind 1: one s16 point; kind 2: n s16 points (8-byte stride); kinds 3-5: s16 point + s16 x4 (angles / range)
//!               size = 16 B (kind 0 / 1), 24 B (3..5), 8 + 8 n B (kind 2)                              (GetObjSeSize 0x004d5730)
//! slot type     kind 0-2 -> 0 (point / polyline: nearest point), 3 -> 1 (cone: direction from the angles, inner / outer angle),
//!               4 / 5 -> 2 (one-sided plane: silent behind it)
//! ```
//! Coordinates are PS2 world units (y down).  Rear sources would get a negative pan byte on the console (phase inverted by the driver); the
//! port clamps the pan to 0..127.

/// One `OBJSE` record / `SetObjSE` request.
#[derive(Clone, Debug, PartialEq)]
pub struct ObjSeRec {
    /// global SE id `(wave bank << 16) | local`
    pub id: u32,
    /// kind 0..5 (low nibble of byte 4)
    pub kind: u8,
    /// byte 5: bits 0-1 = play at once (non-positional), bits 2-3 = fall-off curve
    pub flags: u8,
    pub points: Vec<[f32; 3]>,
    /// kinds 3..5: four shorts (x / y rotation in 1/4096 turns for the axis, inner / outer angle or plane width)
    pub extra: [i16; 4],
}

fn rd16(d: &[u8], o: usize) -> i16 {
    d.get(o..o + 2).map(|b| i16::from_le_bytes([b[0], b[1]])).unwrap_or(0)
}

impl ObjSeRec {
    /// Size of a record in bytes (`GetObjSeSize * 8`).
    pub fn size_of(rec: &[u8]) -> usize {
        let b = rec.get(4).copied().unwrap_or(0);
        let k = b & 0xf;
        if k == 2 {
            ((b >> 4) as usize + 1) * 8
        } else if k < 2 {
            16
        } else {
            24
        }
    }

    pub fn parse(rec: &[u8]) -> Option<ObjSeRec> {
        let id = u32::from_le_bytes(rec.get(0..4)?.try_into().ok()?);
        let b4 = *rec.get(4)?;
        let kind = b4 & 0xf;
        let n = match kind {
            0 => 0,
            2 => (b4 >> 4) as usize,
            _ => 1,
        };
        let stride = if kind == 2 { 8 } else { 6 };
        let points = (0..n).map(|i| [0, 2, 4].map(|k| rd16(rec, 8 + i * stride + k) as f32)).collect();
        let extra = if kind >= 3 { [0, 2, 4, 6].map(|k| rd16(rec, 16 + k)) } else { [0; 4] };
        Some(ObjSeRec { id, kind, flags: *rec.get(5)?, points, extra })
    }

    /// The record `SetObjSE(slot, id, flags, n, points)` of the field script (op 0x5c) builds: `flags` low nibble = kind, bits 4-5 = curve.
    pub fn from_script(id: u32, flags: u32, points: &[[f32; 3]]) -> ObjSeRec {
        let kind = (flags & 0xf) as u8;
        let n = match kind {
            0 => 0,
            2 => points.len(),
            _ => 1.min(points.len()),
        };
        ObjSeRec { id, kind, flags: (((flags >> 4) & 3) << 2) as u8, points: points[..n].to_vec(), extra: [0; 4] }
    }

    fn slot_type(&self) -> u8 {
        match self.kind {
            3 => 1,
            k if k > 3 => 2,
            _ => 0,
        }
    }
}

/// The parsed `OBJSE` chunk of a map.
#[derive(Clone, Debug, Default)]
pub struct ObjSeChunk {
    pub banks: Vec<String>,
    pub reverb: u16,
    pub records: Vec<ObjSeRec>,
}

impl ObjSeChunk {
    /// `chunk` = the chunk data (from its data start: `u16 count` first).
    pub fn parse(chunk: &[u8]) -> ObjSeChunk {
        let count = rd16(chunk, 0) as u16 as usize;
        let cstr = |o: usize| -> String {
            let s = chunk.get(o..o + 16).unwrap_or(&[]);
            String::from_utf8_lossy(&s[..s.iter().position(|&c| c == 0).unwrap_or(s.len())]).into_owned()
        };
        let banks = [0x10, 0x20, 0x30].iter().map(|&o| cstr(o)).filter(|s| !s.is_empty()).collect();
        let mut records = Vec::new();
        let mut o = 0x60;
        for _ in 0..count.min(48) {
            let Some(r) = chunk.get(o..) else { break };
            if let Some(rec) = ObjSeRec::parse(r) {
                records.push(rec);
            }
            o += ObjSeRec::size_of(r);
        }
        ObjSeChunk { banks, reverb: rd16(chunk, 4) as u16, records }
    }
}

/// The listener: the active camera (`GsxCamera` frame position, its "at" axis, focal length `+0x34c`), PS2 world units.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Listener {
    pub pos: [f32; 3],
    pub at: [f32; 3],
    pub scrz: f32,
}

type V = [f32; 3];
fn sub(a: V, b: V) -> V {
    [a[0] - b[0], a[1] - b[1], a[2] - b[2]]
}
fn add(a: V, b: V) -> V {
    [a[0] + b[0], a[1] + b[1], a[2] + b[2]]
}
fn mul(a: V, s: f32) -> V {
    [a[0] * s, a[1] * s, a[2] * s]
}
fn dot(a: V, b: V) -> f32 {
    a[0] * b[0] + a[1] * b[1] + a[2] * b[2]
}
fn len(a: V) -> f32 {
    dot(a, a).sqrt()
}
fn norm(a: V) -> V {
    let l = len(a);
    if l > 1e-6 {
        mul(a, 1.0 / l)
    } else {
        a
    }
}
fn cross(a: V, b: V) -> V {
    [a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]]
}
/// `GetRad`: 4096 units per turn
fn rad(v: f32) -> f32 {
    v * std::f32::consts::TAU / 4096.0
}
/// unit z rotated by `RotX(rx)` then `RotY(ry)`
fn axis(rx: f32, ry: f32) -> V {
    let (sx, cx) = rx.sin_cos();
    let (sy, cy) = ry.sin_cos();
    // Rx * (0, 0, 1) = (0, -sin x, cos x); then Ry
    let v = [0.0, -sx, cx];
    [v[0] * cy + v[2] * sy, v[1], -v[0] * sy + v[2] * cy]
}

/// `Calc3DPosition(listener, &source, slot)`: the effective source position and a 0..1 shape factor.
pub fn calc_3d_position(listener: V, rec: &ObjSeRec) -> (V, f32) {
    let Some(&p0) = rec.points.first() else { return (listener, 1.0) };
    match rec.slot_type() {
        1 => {
            // cone: axis from the angles, full inside `inner`, fading to 0 at `inner + outer`
            let ax = norm(axis(rad(rec.extra[1] as f32), rad(rec.extra[0] as f32)));
            let to = norm(sub(listener, p0));
            let ang = dot(to, ax).clamp(-1.0, 1.0).acos() - rad(rec.extra[2] as f32);
            let outer = rad(rec.extra[3] as f32);
            let f = if ang > 0.0 {
                if outer < ang || outer <= 0.0 {
                    0.0
                } else {
                    (ang - outer) / -outer
                }
            } else {
                1.0
            };
            (p0, f)
        }
        2 => {
            // one-sided plane through p0 with the normal from the angles: silent behind, the source slides along the plane to the listener
            let ax = norm(axis(rad(rec.extra[0] as f32), rad(rec.extra[1] as f32)));
            let d = sub(listener, p0);
            let l = len(d);
            let c = dot(ax, norm(d));
            if c < 0.0 {
                return (p0, 0.0);
            }
            let mut src = add(p0, mul(ax, l * c));
            src[1] = p0[1];
            let lateral = l * c.clamp(-1.0, 1.0).acos().sin();
            let half_w = rec.extra[2] as f32 * 0.5;
            let mut f = 1.0;
            if half_w <= lateral {
                let lim = rad(rec.extra[3] as f32);
                let a = c.clamp(-1.0, 1.0).acos() - lim;
                f = if lim < a || lim <= 0.0 { 0.0 } else { (a - lim) / -lim };
            }
            (src, f.clamp(0.0, 1.0))
        }
        _ => {
            if rec.points.len() == 1 {
                return (p0, 1.0);
            }
            // polyline: nearest vertex, then the projection onto its neighbouring segments
            let (i, _) = rec.points.iter().enumerate().map(|(i, p)| (i, len(sub(*p, listener)))).fold((0, f32::MAX), |b, x| if x.1 < b.1 { x } else { b });
            let a = rec.points[i];
            let prev = if i > 0 { Some(rec.points[i - 1]) } else { None };
            let next = rec.points.get(i + 1).copied();
            let to = sub(listener, a);
            let dist = len(to);
            let ton = norm(to);
            let seg = |p: Option<V>| p.map(|p| (norm(sub(p, a)), len(sub(p, a))));
            let (pd, pl) = seg(prev).map(|(d, l)| (Some(d), l)).unwrap_or((None, 0.0));
            let (nd, nl) = seg(next).map(|(d, l)| (Some(d), l)).unwrap_or((None, 0.0));
            let cp = pd.map(|d| dot(d, ton)).unwrap_or(-1.0);
            let cn = nd.map(|d| dot(d, ton)).unwrap_or(-1.0);
            let src = if cp < 0.0 && cn < 0.0 {
                a
            } else if cp > 0.0 && cn > 0.0 {
                // between two segments: the nearer projection (clamped to the segment ends)
                let tp = (cp * dist / pl.max(1e-3)).min(1.0);
                let tn = (cn * dist / nl.max(1e-3)).min(1.0);
                if tp >= tn {
                    add(a, mul(pd.unwrap(), (cp * dist).min(pl)))
                } else {
                    add(a, mul(nd.unwrap(), (cn * dist).min(nl)))
                }
            } else if cp > 0.0 {
                add(a, mul(pd.unwrap(), (dist * cp).min(pl)))
            } else {
                add(a, mul(nd.unwrap(), (dist * cn).min(nl)))
            };
            (src, 1.0)
        }
    }
}

/// `Exp3DVolume(listener, source, at, &vol, &pan, curve)`: distance fall-off (curve 0 linear from 50, 1 and 2 inverse-square from 20 / 30) and
/// the pan from the source direction relative to the camera axis (0x40 = centre).
pub fn exp_3d_volume(listener: V, src: V, at: V, curve: u8) -> (i32, i32) {
    let d = sub(src, listener);
    let dist = len(d);
    let mut vol = 0x7f;
    match curve {
        2 if dist > 30.0 => vol = (128.0 / ((dist - 29.0) * (dist - 29.0) * 0.005)) as i32,
        1 if dist > 20.0 => vol = (128.0 / ((dist - 19.0) * (dist - 19.0) * 0.001)) as i32,
        0 if dist > 50.0 => vol = ((1.0 - (dist - 50.0) * 0.008) * 128.0) as i32,
        _ => {}
    }
    if vol < 0x50 {
        vol = (vol >> 1) + 0x28;
    }
    vol = vol.min(0x80);
    // pan: horizontal angle between the source direction and the camera axis
    let mut to = d;
    to[1] = 0.0;
    let to = norm(to);
    let mut ax = at;
    ax[1] = 0.0;
    let ax = norm(ax);
    let side = cross(norm(d), norm(at))[1];
    let c = dot(to, ax) * 64.0;
    let mut pan = if side < 0.0 {
        if c >= 0.0 {
            0x7f - c as i32
        } else {
            -0x7f - c as i32
        }
    } else {
        c as i32
    };
    if dist < 40.0 {
        let s = if pan < 0 { -1 } else { 1 };
        pan = s * ((((pan.abs() - 0x40) as f32) * (dist / 40.0)) as i32 + 0x40);
    }
    (vol, pan)
}

/// `Exp3DVolumeC(cos half fov, listener, at, source)`: 1 inside the view cone, 0.7 .. 1.0 beside it, down to 0.5 behind the camera.
pub fn exp_3d_volume_c(cos_fov: f32, listener: V, at: V, src: V) -> f32 {
    if cos_fov == 0.0 {
        return 1.0;
    }
    let c = dot(norm(at), norm(sub(src, listener)));
    if c < cos_fov {
        if c >= 0.0 {
            c / cos_fov * 0.3 + 0.7
        } else {
            c * 0.2 + 0.7
        }
    } else {
        1.0
    }
}

/// What the runtime has to do for one slot this frame.
#[derive(Clone, Debug, PartialEq)]
pub enum ObjSeAction {
    Play { slot: usize, id: u32, volume: u8, pan: u8 },
    Update { slot: usize, volume: u8, pan: u8 },
    Release { slot: usize },
}

#[derive(Clone, Debug)]
struct Slot {
    rec: ObjSeRec,
    playing: bool,
    /// `+9 bit 4`: a one-shot slot is not restarted when its sound ends
    one_shot: bool,
    /// state `+9 & 3`: 1 = start pending, 2 = started
    state: u8,
    vol: u8,
    pan: u8,
}

/// The 48 object-sound slots of the field (`CField +aObjse_slots`).
#[derive(Clone, Debug, Default)]
pub struct ObjSeMan {
    slots: Vec<Option<Slot>>,
}

impl ObjSeMan {
    pub const SLOTS: usize = 48;

    fn ensure(&mut self) {
        if self.slots.len() < Self::SLOTS {
            self.slots.resize(Self::SLOTS, None);
        }
    }

    /// `SetObjSE(slot, rec)`: `None` clears the slot (`slot < 0`: every slot).  Returns the slots to release.
    pub fn set(&mut self, slot: i32, rec: Option<ObjSeRec>, one_shot: bool) -> Vec<usize> {
        self.ensure();
        let mut rel = Vec::new();
        let Some(rec) = rec else {
            let range: Vec<usize> = if slot < 0 { (0..Self::SLOTS).collect() } else { vec![slot as usize] };
            for i in range {
                if let Some(Some(s)) = self.slots.get(i) {
                    if s.playing {
                        rel.push(i);
                    }
                }
                if let Some(x) = self.slots.get_mut(i) {
                    *x = None;
                }
            }
            return rel;
        };
        let i = if slot < 0 { self.slots.iter().position(|s| s.is_none()) } else { Some(slot as usize) };
        let Some(i) = i.filter(|i| *i < Self::SLOTS) else { return rel };
        if let Some(old) = &self.slots[i] {
            if old.playing && (old.rec.id != rec.id || old.rec.slot_type() != rec.slot_type()) {
                rel.push(i);
            }
        }
        // non-positional sounds start only when their play bits are set; positional ones are placed by the next update
        let state = if rec.points.is_empty() { if rec.flags & 3 != 0 { 1 } else { 0 } } else { 1 };
        let keep = self.slots[i].as_ref().filter(|o| o.playing && o.rec.id == rec.id && !rel.contains(&i)).map(|o| (o.vol, o.pan));
        self.slots[i] = Some(Slot { rec, playing: keep.is_some(), one_shot, state, vol: keep.map(|k| k.0).unwrap_or(0), pan: keep.map(|k| k.1).unwrap_or(0x40) });
        rel
    }

    /// A slot's sound ended on its own (the runtime saw the play id finish).
    pub fn ended(&mut self, slot: usize) {
        if let Some(Some(s)) = self.slots.get_mut(slot) {
            s.playing = false;
        }
    }

    pub fn active(&self) -> usize {
        self.slots.iter().flatten().filter(|s| s.playing).count()
    }

    /// `UpdateObjSE`: one field frame.
    pub fn update(&mut self, listener: Option<Listener>) -> Vec<ObjSeAction> {
        self.ensure();
        let mut out = Vec::new();
        let cos_fov = listener.map(|l| if l.scrz > 0.0 { (320.0 / l.scrz).atan().cos() } else { 0.0 }).unwrap_or(0.0);
        for (i, s) in self.slots.iter_mut().enumerate() {
            let Some(s) = s.as_mut() else { continue };
            if s.state == 0 {
                continue;
            }
            let restart = !s.one_shot || s.state == 1;
            if s.rec.points.is_empty() {
                if !s.playing {
                    if restart {
                        s.state = 2;
                        s.playing = true;
                        s.vol = 0x7f;
                        s.pan = 0x40;
                        out.push(ObjSeAction::Play { slot: i, id: s.rec.id, volume: 0x7f, pan: 0x40 });
                    }
                }
                continue;
            }
            let Some(l) = listener else { continue };
            let (src, shape) = calc_3d_position(l.pos, &s.rec);
            let (vol, pan) = exp_3d_volume(l.pos, src, l.at, (s.rec.flags >> 2) & 3);
            let c = exp_3d_volume_c(cos_fov, l.pos, l.at, src);
            let vol = (vol as f32 * shape * c) as i32;
            if vol < 1 {
                if s.playing {
                    s.playing = false;
                    out.push(ObjSeAction::Release { slot: i });
                }
                continue;
            }
            let (v, p) = (vol.min(0x7f) as u8, pan.clamp(0, 0x7f) as u8);
            if !s.playing {
                if restart {
                    s.state = 2;
                    s.playing = true;
                    s.vol = v;
                    s.pan = p;
                    out.push(ObjSeAction::Play { slot: i, id: s.rec.id, volume: v, pan: p });
                }
            } else if s.vol != v || s.pan != p {
                s.vol = v;
                s.pan = p;
                out.push(ObjSeAction::Update { slot: i, volume: v, pan: p });
            }
        }
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn rec(kind: u8, n: u8, flags: u8, pts: &[[i16; 3]]) -> Vec<u8> {
        let mut r = vec![0u8; 8];
        r[..4].copy_from_slice(&0x0003_0005u32.to_le_bytes());
        r[4] = kind | (n << 4);
        r[5] = flags;
        for p in pts {
            for c in p {
                r.extend_from_slice(&c.to_le_bytes());
            }
            if kind == 2 {
                r.extend_from_slice(&[0, 0]);
            }
        }
        while r.len() < ObjSeRec::size_of(&r) {
            r.push(0);
        }
        r
    }

    #[test]
    fn record_sizes_and_parse() {
        let a = rec(1, 0, 0, &[[100, -20, 300]]);
        assert_eq!(ObjSeRec::size_of(&a), 16);
        let r = ObjSeRec::parse(&a).unwrap();
        assert_eq!((r.id, r.kind, r.points.clone()), (0x30005, 1, vec![[100.0, -20.0, 300.0]]));
        let b = rec(2, 3, 4, &[[0, 0, 0], [100, 0, 0], [200, 0, 0]]);
        assert_eq!(ObjSeRec::size_of(&b), 32);
        assert_eq!(ObjSeRec::parse(&b).unwrap().points.len(), 3);
    }

    #[test]
    fn falloff_curves() {
        let l = [0.0, 0.0, 0.0];
        let at = [0.0, 0.0, 1.0];
        assert_eq!(exp_3d_volume(l, [0.0, 0.0, 10.0], at, 0).0, 0x7f);
        // curve 0: 1 - (d - 50) * 0.008 -> at d = 100: 0.6 * 128 = 76 -> < 0x50: 76 / 2 + 40 = 78
        assert_eq!(exp_3d_volume(l, [0.0, 0.0, 100.0], at, 0).0, 78);
        // straight ahead = centre pan
        assert_eq!(exp_3d_volume(l, [0.0, 0.0, 100.0], at, 0).1, 0x40);
        // to the side: an extreme
        let p = exp_3d_volume(l, [100.0, 0.0, 0.0], at, 0).1;
        assert!(p == 0 || p == 0x7f, "{p}");
    }

    #[test]
    fn polyline_projects_onto_the_segment() {
        let r = ObjSeRec::parse(&rec(2, 2, 0, &[[0, 0, 0], [100, 0, 0]])).unwrap();
        let (src, f) = calc_3d_position([40.0, 0.0, 30.0], &r);
        assert_eq!(f, 1.0);
        assert!((src[0] - 40.0).abs() < 1.0 && src[2].abs() < 1e-3, "{src:?}");
    }

    #[test]
    fn manager_plays_updates_and_releases() {
        let mut m = ObjSeMan::default();
        let r = ObjSeRec::parse(&rec(1, 0, 0, &[[0, 0, 100]])).unwrap();
        m.set(0, Some(r), false);
        let near = Listener { pos: [0.0, 0.0, 0.0], at: [0.0, 0.0, 1.0], scrz: 400.0 };
        let a = m.update(Some(near));
        assert!(matches!(a[0], ObjSeAction::Play { slot: 0, id: 0x30005, .. }));
        let far = Listener { pos: [0.0, 0.0, -400.0], ..near };
        let b = m.update(Some(far));
        assert!(matches!(b[0], ObjSeAction::Release { slot: 0 }), "{b:?}");
        assert_eq!(m.set(-1, None, false), Vec::<usize>::new());
    }
}
