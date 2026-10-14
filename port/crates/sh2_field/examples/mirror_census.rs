//! Debug: mirror count and plane axes of every map: `mirror_census [--us]`
use sh2_field::bevy::mirror_records;
use sh2_field::mps::Mps;
use sh2_gfx::bevy::mirror::MirrorPlane;
use sh2_gfx::bevy::Sh2Disc;

fn main() {
    let us = std::env::args().any(|x| x == "--us");
    let disc = Sh2Disc::from_env(us).unwrap();
    let mut names = Vec::new();
    disc.0.info().walk(|p, _| {
        if let Some(m) = p.strip_prefix("FIELD/MPS/").and_then(|m| m.strip_suffix(".MPS")) {
            names.push(m.to_string());
        }
    });
    for n in names {
        let Ok(b) = disc.read(&format!("FIELD/MPS/{n}.MPS")) else { continue };
        let Ok(m) = Mps::parse(b) else { continue };
        let recs = mirror_records(&m);
        if recs.is_empty() {
            continue;
        }
        let planes: Vec<String> = recs
            .iter()
            .filter_map(|r| MirrorPlane::from_corners(r.map(|v| glam::Vec3::new(v[0], v[1], v[2]))))
            .map(|p| format!("axis{} @{:.0} x[{:.0},{:.0}] y[{:.0},{:.0}] z[{:.0},{:.0}]", p.axis, p.coord(), p.lo.x, p.hi.x, p.lo.y, p.hi.y, p.lo.z, p.hi.z))
            .collect();
        println!("{n}: {} mirrors: {}", recs.len(), planes.join(" | "));
    }
}
