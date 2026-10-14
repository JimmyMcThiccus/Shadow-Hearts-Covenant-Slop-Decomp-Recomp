//! Debug: list maps whose collision floor has strongly sloped triangles (stairs, ramps): `slope_finder [--us] [MAP...]`
//! prints per map the sloped triangle count and the centroid of the biggest one (PS2 coordinates).
use sh2_field::mps::Mps;
use sh2_gfx::bevy::Sh2Disc;

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let disc = Sh2Disc::from_env(us).unwrap();
    let names: Vec<String> = if v.is_empty() {
        let mut n = Vec::new();
        disc.0.info().walk(|p, _| {
            if let Some(m) = p.strip_prefix("FIELD/MPS/").and_then(|m| m.strip_suffix(".MPS")) {
                n.push(m.to_string());
            }
        });
        n
    } else {
        v.iter().map(|s| s.to_string()).collect()
    };
    for name in names {
        let Ok(bytes) = disc.read(&format!("FIELD/MPS/{name}.MPS")) else { continue };
        let Ok(mps) = Mps::parse(bytes) else { continue };
        let Ok(Some(fl)) = mps.floor() else { continue };
        let mut n = 0;
        let mut best: Option<(f32, [f32; 3], f32)> = None;
        for t in &fl.triangles {
            let p: Vec<[f32; 3]> = t.v.iter().filter_map(|&i| fl.vertices.get(i as usize)).map(|v| [v[0], v[1], v[2]]).collect();
            if p.len() != 3 {
                continue;
            }
            let e1 = [p[1][0] - p[0][0], p[1][1] - p[0][1], p[1][2] - p[0][2]];
            let e2 = [p[2][0] - p[0][0], p[2][1] - p[0][1], p[2][2] - p[0][2]];
            let nx = e1[1] * e2[2] - e1[2] * e2[1];
            let ny = e1[2] * e2[0] - e1[0] * e2[2];
            let nz = e1[0] * e2[1] - e1[1] * e2[0];
            let l = (nx * nx + ny * ny + nz * nz).sqrt();
            if l < 1e-3 {
                continue;
            }
            let up = (ny / l).abs();
            if up < 0.95 && up > 0.5 {
                n += 1;
                let area = l * 0.5;
                let c = [(p[0][0] + p[1][0] + p[2][0]) / 3.0, (p[0][1] + p[1][1] + p[2][1]) / 3.0, (p[0][2] + p[1][2] + p[2][2]) / 3.0];
                if best.map(|b| area > b.0).unwrap_or(true) {
                    best = Some((area, c, up));
                }
            }
        }
        if n > 4 {
            let b = best.unwrap();
            println!("{name}: {n} sloped tris ({} total), biggest area {:.0} at {:.1},{:.1},{:.1} n.y {:.2}", fl.triangles.len(), b.0, b.1[0], b.1[1], b.1[2], b.2);
        }
    }
}
