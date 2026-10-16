//! Diagnostics (round 6 FX3): draw the background effects of one map / battle stage on the CPU, without the scene, to check their shape from a
//! chosen camera.  `bgfx_snap <FIELD/MPS/X.MPS | BTLDATA/BBG/062.BBG> <frames> <eye x,y,z> <target x,y,z> <out.ppm> [types]` (PS2 world, y down;
//! `SH2_US_DISC_DIR`).  Billboards are soft discs (the texture is not sampled), strips / axis quads are flat triangles; additive or alpha blended
//! like the quad says; screen quads are skipped.
use glam::{Vec2, Vec3};
use sh2_core::fileio::Disc;
use sh2_gfx::effects::bgfx::{BgCamera, BgFx, BgQuad};
use sh2_gfx::effects::sbd::parse_sbd_full;

fn bbg_sbd(b: &[u8]) -> Option<&[u8]> {
    let u = |o: usize| b.get(o..o + 4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]]) as usize);
    let n = u(0)?;
    let ents: Vec<(Vec<u8>, usize)> = (0..n).filter_map(|i| Some((b.get(8 + i * 8..12 + i * 8)?.to_vec(), u(12 + i * 8)?))).collect();
    let (_, off) = ents.iter().find(|e| e.0.starts_with(b"mbs"))?;
    let end = ents.iter().map(|e| e.1).filter(|&o| o > *off).min().unwrap_or(b.len()).min(b.len());
    b.get(*off..end)
}

fn v3(s: &str) -> Vec3 {
    let p: Vec<f32> = s.split(',').map(|x| x.parse().unwrap()).collect();
    Vec3::new(p[0], p[1], p[2])
}

fn main() {
    let a: Vec<String> = std::env::args().collect();
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let d = Disc::open(std::env::var("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let bytes = d.read(&a[1]).unwrap();
    let sbd = if a[1].to_ascii_uppercase().ends_with(".BBG") { bbg_sbd(&bytes).unwrap().to_vec() } else { bytes.clone() };
    let mut recs = parse_sbd_full(&sbd).fx_records();
    if let Some(types) = a.get(6) {
        let keep: Vec<u16> = types.split(',').map(|x| x.parse().unwrap()).collect();
        recs.retain(|r| keep.contains(&r.kind));
    }
    let frames: u32 = a[2].parse().unwrap();
    let (eye, target) = (v3(&a[3]), v3(&a[4]));
    let fwd = (target - eye).normalize();
    // PS2 view axes: y down; right = fwd x down-ish
    let right = Vec3::new(0.0, 1.0, 0.0).cross(fwd).normalize();
    let down = fwd.cross(right).normalize();
    let cam = BgCamera { pos: eye, forward: fwd, right, down, ..BgCamera::default() };
    let mut fx = BgFx::new(&recs, 7);
    println!("{} records, unsupported {:?}", recs.len(), fx.unsupported);
    for _ in 0..frames {
        fx.step_cam(1.0, &cam);
    }
    let quads = fx.quads();
    let (w, h) = (512usize, 448usize);
    let mut img = vec![[0.0f32; 3]; w * h];
    let to_px = |s: Vec2| Vec2::new(s.x + w as f32 / 2.0, s.y + h as f32 / 2.0);
    let mut drawn = 0;
    for q in &quads {
        if q.screen {
            continue;
        }
        let c = [q.rgba.x / 128.0, q.rgba.y / 128.0, q.rgba.z / 128.0];
        let al = (q.rgba.w / 128.0).clamp(0.0, 1.0);
        let mut blend = |x: usize, y: usize, k: f32| {
            let p = &mut img[y * w + x];
            for i in 0..3 {
                if q.additive {
                    p[i] += c[i] * al * k;
                } else {
                    p[i] = p[i] * (1.0 - al * k) + c[i] * al * k;
                }
            }
        };
        match q.axes {
            Some(ax) => {
                // triangle t0, t0 + ax0, t0 + ax1 (the thunder strips)
                let pts = [q.center, q.center + ax[0], q.center + ax[1]];
                let Some(s) = pts.iter().map(|p| cam.project(*p).map(to_px)).collect::<Option<Vec<_>>>() else { continue };
                let (lo, hi) = (s.iter().fold(Vec2::splat(f32::MAX), |m, p| m.min(*p)), s.iter().fold(Vec2::splat(f32::MIN), |m, p| m.max(*p)));
                if hi.x < 0.0 || hi.y < 0.0 || lo.x > w as f32 || lo.y > h as f32 || (hi - lo).max_element() > 2000.0 {
                    continue;
                }
                drawn += 1;
                let edge = |a: Vec2, b: Vec2, p: Vec2| (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
                for y in lo.y.max(0.0) as usize..(hi.y.min(h as f32 - 1.0) as usize + 1) {
                    for x in lo.x.max(0.0) as usize..(hi.x.min(w as f32 - 1.0) as usize + 1) {
                        let p = Vec2::new(x as f32 + 0.5, y as f32 + 0.5);
                        let (e0, e1, e2) = (edge(s[0], s[1], p), edge(s[1], s[2], p), edge(s[2], s[0], p));
                        if (e0 >= 0.0 && e1 >= 0.0 && e2 >= 0.0) || (e0 <= 0.0 && e1 <= 0.0 && e2 <= 0.0) {
                            blend(x, y, 1.0);
                        }
                    }
                }
            }
            None => {
                let Some(s) = cam.project(q.center) else { continue };
                let z = (q.center - cam.pos).dot(cam.forward);
                let r = q.offs[3].length() / std::f32::consts::SQRT_2 * cam.focal.x / z;
                let c0 = to_px(s);
                if r < 0.3 || c0.x + r < 0.0 || c0.y + r < 0.0 || c0.x - r > w as f32 || c0.y - r > h as f32 {
                    continue;
                }
                drawn += 1;
                for y in (c0.y - r).max(0.0) as usize..((c0.y + r).min(h as f32 - 1.0) as usize + 1) {
                    for x in (c0.x - r).max(0.0) as usize..((c0.x + r).min(w as f32 - 1.0) as usize + 1) {
                        let dd = (Vec2::new(x as f32, y as f32) - c0).length() / r;
                        if dd < 1.0 {
                            blend(x, y, 1.0 - dd * dd);
                        }
                    }
                }
            }
        }
    }
    let _ = BgQuad::clone;
    let mut out = format!("P6\n{w} {h}\n255\n").into_bytes();
    for p in &img {
        for c in p {
            out.push((c.clamp(0.0, 1.0) * 255.0) as u8);
        }
    }
    std::fs::write(&a[5], out).unwrap();
    println!("{} quads, {drawn} drawn", quads.len());
}
