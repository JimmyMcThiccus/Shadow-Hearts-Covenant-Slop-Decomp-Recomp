//! Debug: render the radar of a map for a player position: `navi_render [--us] MAP PX PZ [flip_y flip_x yaw_sign] OUT.rgba`
//! Writes `u32 w, u32 h` then RGBA8 of the top-left 160 x 180 virtual pixels over a grey background.
use sh2_field::mps::Mps;
use sh2_field::navimap::NaviData;
use sh2_field::navimap_render::*;
use sh2_gfx::bevy::Sh2Disc;

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().filter(|x| !x.starts_with("--")).collect();
    let (map, px, pz) = (v[0].as_str(), v[1].parse::<f32>().unwrap(), v[2].parse::<f32>().unwrap());
    let flip_y = v.get(3).map(|s| *s == "1").unwrap_or(true);
    let flip_x = v.get(4).map(|s| *s == "1").unwrap_or(false);
    let yaw_sign = v.get(5).map(|s| s.parse::<f32>().unwrap()).unwrap_or(1.0);
    let out = v.last().unwrap();
    let disc = Sh2Disc::from_env(us).unwrap();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let mps = Mps::parse(disc.read(&format!("FIELD/MPS/{map}.MPS")).unwrap()).unwrap();
    let navi = NaviData::from_mps(&mps).expect("no navimap");
    let art = NaviArt::from_overlay(&sh2_core::fileio::read_disc_file(std::path::Path::new(&dir), "FIELD.BIN").unwrap()).expect("art");
    let o = Orient { flip_y, flip_x, yaw_sign };
    let t0 = std::time::Instant::now();
    let mut floor = navi.render_floor(o, &NaviView { player: [px, 0.0, pz], heading: 0.0 });
    for _ in 0..19 {
        floor = navi.render_floor(o, &NaviView { player: [px, 0.0, pz], heading: 0.0 });
    }
    eprintln!("render_floor: {:.3} ms / frame ({} meshes, {} verts)", t0.elapsed().as_secs_f64() * 1000.0 / 20.0, navi.meshes.len(), navi.meshes.iter().map(|m| m.pos.len()).sum::<usize>());
    let (w, h) = (160usize, 180usize);
    let mut img = vec![[40.0f32, 40.0, 44.0]; w * h];
    for y in 0..WIN_H {
        for x in 0..WIN_W {
            let (sx, sy) = (WIN_POS[0] as usize + x, WIN_POS[1] as usize + y);
            // circle coverage from the mask quadrants around (80, 88): distance from the centre lines -> texel
            let (dx, dy) = ((sx as f32 + 0.5 - CENTRE[0]).abs(), (sy as f32 + 0.5 - CENTRE[1]).abs());
            let u = 0.5 + (59.0 - dx).max(0.0) / 59.0 * 61.5;
            let vv = 0.5 + (60.0 - dy).max(0.0) / 60.0 * 61.5;
            let cov = if dx > 59.0 || dy > 60.0 { 0.0 } else { art.mask_at(u, vv) };
            let a = COPY_ALPHA * cov;
            let f = floor.rgb[y * WIN_W + x];
            let d = &mut img[sy * w + sx];
            for i in 0..3 {
                d[i] = d[i] * (1.0 - a) + f[i] * a;
            }
        }
    }
    // ring: four mirrored quadrants of the 64 x 72 frame at (16, 16)
    for k in 0..4usize {
        let (ox, oy) = (RING_POS[0] as usize + (k & 1) * 64, RING_POS[1] as usize + (k >> 1) * 72);
        for ty in 0..72usize {
            for tx in 0..64usize {
                let (sx, sy) = (ox + tx, oy + ty);
                // the stored quadrant is the top-right one with the ring centre at its bottom-left corner
                let (fx, fy) = (if k & 1 == 0 { 63 - tx } else { tx }, if k & 2 == 0 { ty } else { 71 - ty });
                let i = (fy * art.frame.w + fx) * 4;
                let p = &art.frame.rgba[i..i + 4];
                let a = p[3] as f32 / 255.0;
                let d = &mut img[sy * w + sx];
                for c in 0..3 {
                    d[c] = d[c] * (1.0 - a) + p[c] as f32 * a;
                }
            }
        }
    }
    let mut bytes = Vec::new();
    bytes.extend_from_slice(&(w as u32).to_le_bytes());
    bytes.extend_from_slice(&(h as u32).to_le_bytes());
    for p in &img {
        bytes.extend_from_slice(&[p[0].clamp(0.0, 255.0) as u8, p[1].clamp(0.0, 255.0) as u8, p[2].clamp(0.0, 255.0) as u8, 255]);
    }
    std::fs::write(out, bytes).unwrap();
}
