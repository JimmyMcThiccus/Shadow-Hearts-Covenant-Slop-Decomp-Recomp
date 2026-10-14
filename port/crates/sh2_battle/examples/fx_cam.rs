//! Developer tool: dump the EFCM keys, light keys and model frames of an effect.
use sh2_gfx::effects::motion::{CameraMotion, LightMotion};
use sh2_script::efmg::{kind, Efmg};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let id: i32 = a[2].parse().unwrap();
    let b = d.read(&format!("EFFECT/{id:03}_00.EFD")).unwrap();
    let e = Efmg::parse(&b).unwrap();
    for (i, s) in e.iter_kind(kind::CAMERA) {
        println!("EFCM {i}: header {:02x?}", &s[..16.min(s.len())]);
        if let Some(m) = CameraMotion::parse(s) {
            for k in m.keys.iter().take(6) {
                println!("   key t={} pos={:?} target={:?} fov={} roll={}", k.time, k.pos, k.target, k.fov, k.roll);
            }
            println!("   ... {} keys", m.keys.len());
        }
    }
    for (i, s) in e.iter_kind(kind::LIGHT) {
        if let Some(m) = LightMotion::parse(s) {
            println!("EFLT {i}: type {} first {:?} last {:?} keys {}", m.light_type, m.keys.first(), m.keys.last(), m.keys.len());
        }
    }
    for (i, s) in e.iter_kind(kind::MODEL) {
        if let Ok(m) = sh2_formats::model::Model::parse(s) {
            println!("M {i}: frames {:?}", m.frames.iter().map(|f| f.name.clone()).collect::<Vec<_>>());
            println!("   bounds {:?}", sh2_gfx::bevy::model::model_bounds(&m));
        }
    }
}
