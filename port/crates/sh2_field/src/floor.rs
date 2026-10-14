//! `CFloorMan` — walkable-floor triangle database with slice acceleration.
//!
//! JP: 0x004bc850 `__ct__9CFloorManFv`, 0x004bc900 `SetData`, 0x004bcd30 `SetRotY`, 0x004bce40 `SetObstacle`,
//! 0x004bcef0 `OnFloorChk`, 0x004bd580 `TriangleChk`, 0x004bdaf0 `OnFloorPoint`, 0x004bde90 `CircleChk`.
//!
//! Data: WORLD (extent/origin/slice count), VERTEX (16-byte `vec4`), TRIANGLE (32 bytes), SLICE (16-byte index +
//! zero-terminated triangle-index lists). The floor is a 2D bucket grid along one axis: the world rectangle
//! `[origin, origin+size)` is cut into `slice_count` strips along X (or Z when `WORLD.slices_along_x == 0`),
//! each strip lists the triangles overlapping it, sorted in strip order so the half-way scans work.

use crate::compat::{atan2f, rot_y};
use crate::mps::{rd_f32, rd_u16, rd_u32, rd_v4, tags, Mps, MpsError, World};

#[derive(Debug, Clone, Copy)]
pub struct Triangle {
    /// vertex indices (relocated to pointers by `CFloorMan::SetData` in the original).
    pub v: [u32; 3],
    /// `+0x0c` upper bound of the triangle along the slice's *other* axis.
    pub max_c: f32,
    /// `+0x10` lower bound along the other axis.
    pub min_c: f32,
    pub unk14: u16,
    /// `+0x16` non-zero => triangle disabled (written by `SetObstacle`).
    pub blocked: u8,
    /// `+0x17` obstacle group id matched by `SetObstacle(id, flag)`.
    pub obstacle_id: u8,
    pub unk18: [u8; 8],
}

#[derive(Debug, Clone)]
pub struct FloorData {
    pub world: World,
    pub vertices: Vec<[f32; 4]>,
    pub triangles: Vec<Triangle>,
    /// per slice: triangle indices (without the zero terminator)
    pub slices: Vec<Vec<u32>>,
}

impl FloorData {
    pub fn from_mps(m: &Mps) -> Result<Option<Self>, MpsError> {
        let (Some(world), Some(vc), Some(tc), Some(sc)) =
            (m.world()?, m.find(tags::VERTEX), m.find(tags::TRIANGLE), m.find(tags::SLICE))
        else {
            return Ok(None);
        };
        let d = &m.data;
        let oob = |s: &str| MpsError::OutOfRange(s.into());
        let vs = vc.data_start();
        if vs + vc.count as usize * 16 > d.len() {
            return Err(oob("VERTEX"));
        }
        let vertices = (0..vc.count as usize).map(|i| rd_v4(d, vs + i * 16)).collect();
        let ts = tc.data_start();
        if ts + tc.count as usize * 32 > d.len() {
            return Err(oob("TRIANGLE"));
        }
        let triangles = (0..tc.count as usize)
            .map(|i| {
                let o = ts + i * 32;
                let mut unk18 = [0u8; 8];
                unk18.copy_from_slice(&d[o + 0x18..o + 0x20]);
                Triangle {
                    v: [rd_u32(d, o), rd_u32(d, o + 4), rd_u32(d, o + 8)],
                    max_c: rd_f32(d, o + 0xc),
                    min_c: rd_f32(d, o + 0x10),
                    unk14: rd_u16(d, o + 0x14),
                    blocked: d[o + 0x16],
                    obstacle_id: d[o + 0x17],
                    unk18,
                }
            })
            .collect();
        let ss = sc.data_start();
        let mut slices = Vec::with_capacity(sc.count as usize);
        for i in 0..sc.count as usize {
            let e = ss + i * 16;
            if e + 16 > d.len() {
                return Err(oob("SLICE"));
            }
            let list = e + rd_u32(d, e) as usize;
            let n = rd_u32(d, e + 4) as usize;
            if list + n * 4 > d.len() {
                return Err(oob("SLICE list"));
            }
            slices.push((0..n).map(|k| rd_u32(d, list + k * 4)).collect());
        }
        Ok(Some(FloorData { world, vertices, triangles, slices }))
    }
}

/// Runtime floor query object (the original keeps these fields in the 0x20-byte `CFloorMan`).
#[derive(Debug, Clone)]
pub struct FloorMan {
    pub data: FloorData,
    /// `+0x14`: false => slices run along X (bucket index from x), true => along Z.
    pub slice_along_z: bool,
    /// `+0x18`: slice count (`WORLD[2]` or `WORLD[3]`).
    pub slice_count: u32,
    /// `+0x10`: last triangle hit (query cache).
    pub cached: Option<usize>,
    /// `+0x1c`: floor yaw in radians (`SetRotY`).
    pub rot_y: f32,
}

impl FloorMan {
    /// JP: 0x004bc900 CFloorMan::SetData. Returns `None` if the slice count disagrees with WORLD (the
    /// original keeps going but reports failure).
    pub fn new(data: FloorData) -> Option<Self> {
        let (slice_along_z, slice_count) = if data.world.slices_along_x == 0 {
            (true, data.world.slices_along_z)
        } else {
            (false, data.world.slices_along_x)
        };
        if data.slices.len() as u32 != slice_count {
            return None;
        }
        Some(Self { data, slice_along_z, slice_count, cached: None, rot_y: 0.0 })
    }

    /// JP: 0x004bcd30 CFloorMan::SetRotY(float degrees)
    pub fn set_rot_y(&mut self, mut deg: f32) {
        while deg >= 360.0 {
            deg -= 360.0;
        }
        while deg < 0.0 {
            deg += 360.0;
        }
        self.rot_y = if deg < 180.0 { deg * 0.017453289 } else { (deg - 360.0) * 0.017453289 };
    }

    /// JP: 0x004bce40 CFloorMan::SetObstacle(int id, int flag)
    pub fn set_obstacle(&mut self, id: u8, flag: u8) {
        for s in &self.data.slices {
            for &t in s {
                let tri = &mut self.data.triangles[t as usize];
                if tri.obstacle_id == id {
                    tri.blocked = flag;
                }
            }
        }
    }

    fn vert(&self, i: u32) -> [f32; 3] {
        let v = self.data.vertices[i as usize];
        [v[0], v[1], v[2]]
    }

    /// JP: 0x004bd580 CFloorMan::TriangleChk — point-in-triangle by three signed atan2 angle tests in XZ plus a
    /// +-20 unit height window around the (approximate, `*0.3333`) mean vertex height.
    /// `rot` is the floor yaw applied to the triangle (`Matrix*` in the original; None = identity).
    pub fn triangle_chk(&self, tri: usize, p: [f32; 3], rot: Option<f32>) -> bool {
        let t = &self.data.triangles[tri];
        let mut a = self.vert(t.v[0]);
        let mut b = self.vert(t.v[1]);
        let mut c = self.vert(t.v[2]);
        if let Some(r) = rot {
            a = rot_y(r, a);
            b = rot_y(r, b);
            c = rot_y(r, c);
        }
        if t.blocked != 0 {
            return false;
        }
        const PI: f32 = 3.141592;
        const TWO_PI: f32 = 6.283184;
        let edge = |from: [f32; 3], to: [f32; 3]| -> bool {
            // angle of edge (from-to) vs angle of (p-to), both atan2(x, z)
            let e = atan2f(from[0] - to[0], from[2] - to[2]);
            let q = atan2f(p[0] - to[0], p[2] - to[2]);
            let mut d = q - e;
            if d < -PI {
                d += TWO_PI;
            }
            if d > PI {
                d -= TWO_PI;
            }
            d >= 0.0
        };
        if !edge(a, b) || !edge(b, c) || !edge(c, a) {
            return false;
        }
        let h = (c[1] + a[1] + b[1]) * 0.3333;
        !(p[1] < h - 20.0 || h + 20.0 < p[1])
    }

    /// JP: 0x004bcef0 CFloorMan::OnFloorChk — returns the triangle index under `p` (and caches it).
    pub fn on_floor_chk(&mut self, p: [f32; 3]) -> Option<usize> {
        let rot = if self.rot_y != 0.0 { Some(self.rot_y) } else { None };
        if let Some(c) = self.cached {
            if self.triangle_chk(c, p, rot) {
                return Some(c);
            }
        }
        let local = match rot {
            Some(r) => rot_y(-r, p),
            None => p,
        };
        let w = &self.data.world;
        let dx = local[0] - w.origin_x;
        let dz = local[2] - w.origin_z;
        if dx < 0.0 || dz < 0.0 || w.size_x <= dx || w.size_z <= dz {
            return None;
        }
        let (frac, other, half) = if !self.slice_along_z {
            (dx / w.size_x, local[2], dz < w.size_z * 0.5)
        } else {
            (dz / w.size_z, local[0], dx < w.size_x * 0.5)
        };
        let idx = ((self.slice_count as f32 * frac) as i64).clamp(0, self.slice_count as i64 - 1) as usize;
        let list = self.data.slices[idx].clone();
        let in_range = |this: &Self, t: u32| {
            let tri = &this.data.triangles[t as usize];
            !(other < tri.min_c || tri.max_c < other)
        };
        let hit = if half {
            list.iter().copied().find(|&t| in_range(self, t) && self.triangle_chk(t as usize, p, rot))
        } else {
            list.iter().rev().copied().find(|&t| in_range(self, t) && self.triangle_chk(t as usize, p, rot))
        };
        self.cached = hit.map(|t| t as usize);
        self.cached
    }

    /// JP: 0x004bdaf0 CFloorMan::OnFloorPoint — height of the triangle plane under `p`.
    ///
    /// Works in the frame where edge B->C lies along +Z: `t = R70.z / R50.z` is the position along B->C, the second
    /// interpolation goes across towards A. NaN/inf behaviour for degenerate triangles is the same as the original.
    pub fn on_floor_point(&self, p: [f32; 3], tri: usize) -> f32 {
        let t = &self.data.triangles[tri];
        let a = self.vert(t.v[0]);
        let b = self.vert(t.v[1]);
        let c = self.vert(t.v[2]);
        let p = rot_y(-self.rot_y, p);
        let e50 = [c[0] - b[0], c[1] - b[1], c[2] - b[2]]; // C - B
        let e60 = [a[0] - b[0], a[1] - b[1], a[2] - b[2]]; // A - B
        let e70 = [p[0] - b[0], 0.0, p[2] - b[2]];
        let ang = atan2f(e50[0], e50[2]);
        let r50 = rot_y(-ang, e50);
        let r60 = rot_y(-ang, e60);
        let r70 = rot_y(-ang, e70);
        let base = r50[1] * (r70[2] / r50[2]) + b[1];
        let corr = if r60[2] < r70[2] {
            let u = (r50[2] - r70[2]) / (r50[2] - r60[2]);
            ((c[1] + u * (a[1] - c[1])) - base) * (r70[0] / (r60[0] * u))
        } else {
            let s = r70[2] / r60[2];
            ((b[1] + r60[1] * s) - base) * (r70[0] / (r60[0] * s))
        };
        base + corr
    }

    /// JP: 0x004bde90 CFloorMan::CircleChk — the circle of radius `r` is "inside" when the centre and the 8 points
    /// at +-r (axis) / +-0.707107 r (diagonals) are all on the floor. Returns the triangle under the centre (the original returns the
    /// pointer, which `OnFloorPoint` then consumes).
    pub fn circle_chk(&mut self, p: [f32; 3], r: f32) -> Option<usize> {
        let center = self.on_floor_chk(p)?;
        let d = r * 0.707107;
        let mut q = p;
        // probe order exactly as in the original (one scratch vector mutated in sequence)
        let probes: [(f32, f32); 8] = [(r, 0.0), (-r, 0.0), (0.0, -r), (0.0, r), (-d, -d), (-d, d), (d, d), (d, -d)];
        for (dx, dz) in probes {
            q[0] = p[0] + dx;
            q[2] = p[2] + dz;
            self.on_floor_chk(q)?;
        }
        Some(center)
    }
}
