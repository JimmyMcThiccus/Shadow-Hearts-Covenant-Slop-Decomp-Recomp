//! `CPath` — ribbon trail path (sword swings, comet tails).  JP `CPath` 0x0032aae0..0x0032bd98,
//! `CPolyPath` 0x0032bdb0, `CPathControl` 0x0032cc60.  See `notes/C/Misc.md`.

use sh2_formats::math::FVector;

const MAX_KEYS: usize = 10; // `count + 1 < 0xb`

#[derive(Clone, Copy, Debug, Default)]
pub struct PathPoint {
    pub pos: FVector,
    pub dir: FVector,
    /// distance to the previous (newer) point.
    pub length: f32,
    pub age: f32,
}

#[derive(Clone, Copy, Debug)]
pub struct Key {
    pub time: f32,
    pub value: FVector,
}

#[derive(Clone, Debug, Default)]
pub struct CPath {
    pub capacity: usize,
    /// number of valid points (<= capacity)
    pub count: usize,
    /// newest point first
    pub points: Vec<PathPoint>,
    pub color_keys: Vec<Key>,
    pub st_keys: Vec<Key>,
    pub owner: i32,
}

fn add_key(keys: &mut Vec<Key>, t: f32, v: FVector) -> bool {
    if keys.is_empty() {
        keys.push(Key { time: t, value: v });
        return true;
    }
    if keys.len() + 1 >= 11 || keys.len() >= MAX_KEYS {
        return false;
    }
    if keys.last().unwrap().time < t {
        keys.push(Key { time: t, value: v });
        return true;
    }
    for i in 0..keys.len() {
        if t < keys[i].time {
            keys.insert(i, Key { time: t, value: v });
            return true;
        }
    }
    false
}

fn sample_key(keys: &[Key], t: f32, default: FVector) -> FVector {
    match keys.len() {
        0 => default,
        1 => keys[0].value,
        _ => {
            let i = keys.iter().position(|k| t < k.time).unwrap_or(keys.len());
            if i == 0 {
                return keys[0].value;
            }
            if i == keys.len() {
                return keys[i - 1].value;
            }
            let (a, b) = (keys[i - 1], keys[i]);
            let f = (t - a.time) / (b.time - a.time);
            let g = 1.0 - f;
            FVector::new(
                b.value.x * f + a.value.x * g,
                b.value.y * f + a.value.y * g,
                b.value.z * f + a.value.z * g,
                b.value.w * f + a.value.w * g,
            )
        }
    }
}

impl CPath {
    /// JP: 0x0032b170 Create__5CPathFif
    pub fn create(owner: i32, capacity: usize) -> CPath {
        CPath { capacity, count: 0, points: vec![PathPoint::default(); capacity], owner, ..Default::default() }
    }
    /// JP: 0x0032b1f0 ClearPath__5CPathFv
    pub fn clear(&mut self) {
        self.count = 0;
    }
    /// JP: 0x0032b260 AddPath__5CPathFR7FVectorR7FVector — push a point at the head.
    pub fn add_path(&mut self, pos: FVector, dir: FVector) {
        if self.capacity == 0 {
            return;
        }
        if self.count < self.capacity {
            self.count += 1;
        }
        self.points.rotate_right(1);
        let length = if self.count < 2 { 0.0 } else { (pos - self.points[1].pos).length() };
        self.points[0] = PathPoint { pos, dir, length, age: 0.0 };
    }
    /// JP: 0x0032bd50 AddTime__5CPathFf
    pub fn add_time(&mut self, dt: f32) {
        for p in self.points.iter_mut().take(self.count) {
            p.age += dt;
        }
    }
    /// JP: 0x0032aba0 AddColorKey__5CPathFfR9_RGBAReal (max 10 keys, sorted by time)
    pub fn add_color_key(&mut self, t: f32, rgba: FVector) -> bool {
        add_key(&mut self.color_keys, t, rgba)
    }
    /// JP: 0x0032ad50 AddSTKey__5CPathFfR7FVector
    pub fn add_st_key(&mut self, t: f32, st: FVector) -> bool {
        add_key(&mut self.st_keys, t, st)
    }
    /// JP: 0x0032aed0 getSTKey__5CPathFf (default (0,0,1,1))
    pub fn st_key(&self, t: f32) -> FVector {
        sample_key(&self.st_keys, t, FVector::new(0.0, 0.0, 1.0, 1.0))
    }
    /// JP: 0x0032b020 getColorKey__5CPathFf (not decompiled; assumed identical interpolation to `getSTKey`)
    pub fn color_key(&self, t: f32) -> FVector {
        sample_key(&self.color_keys, t, FVector::new(1.0, 1.0, 1.0, 1.0))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn path_ring_and_keys() {
        let mut p = CPath::create(0, 3);
        for i in 0..5 {
            p.add_path(FVector::new(i as f32, 0.0, 0.0, 1.0), FVector::new(0.0, 1.0, 0.0, 0.0));
        }
        assert_eq!(p.count, 3);
        assert_eq!(p.points[0].pos.x, 4.0);
        assert!((p.points[0].length - 1.0).abs() < 1e-6);
        assert!(p.add_color_key(0.0, FVector::new(0.0, 0.0, 0.0, 0.0)));
        assert!(p.add_color_key(1.0, FVector::new(1.0, 1.0, 1.0, 1.0)));
        let c = p.color_key(0.5);
        assert!((c.x - 0.5).abs() < 1e-6);
    }
}
