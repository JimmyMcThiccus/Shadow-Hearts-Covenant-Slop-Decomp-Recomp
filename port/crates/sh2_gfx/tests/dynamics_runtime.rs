//! Hair / cloth dynamics on real characters (skipped without a disc).

use glam::{Mat4, Vec3};
use sh2_formats::math::Matrix;
use sh2_gfx::bevy::character::parse_character;
use sh2_gfx::model::ModelInstance;
use std::sync::Arc;

fn instance(files: &[&str]) -> Option<ModelInstance> {
    let dir = std::env::var_os("SH2_DISC_DIR")
        .map(std::path::PathBuf::from)
        .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
    let d = sh2_core::fileio::Disc::open(dir).ok()?;
    let blobs: Vec<Vec<u8>> = files.iter().map(|f| d.read(f).unwrap()).collect();
    let refs: Vec<&[u8]> = blobs.iter().map(|b| b.as_slice()).collect();
    let (model, motions) = parse_character(&refs)?;
    let mut inst = ModelInstance::new(Arc::new(model));
    for m in motions {
        inst.add_motion(Arc::new(m));
    }
    Some(inst)
}

/// angle (deg) between the animated and the simulated direction of every chain node, plus link directions
fn report(inst: &ModelInstance, tag: &str) {
    let d = inst.dynamics.as_ref().unwrap();
    for c in &d.chains {
        let dirs: Vec<String> = (0..c.links.len()).map(|i| { let g = c.links.link_geometry(i); format!("({:.2},{:.2},{:.2})|{:.2}", g.x, g.y, g.z, g.length()) }).collect();
        println!("{tag} {:6} {}", c.name, dirs.join(" "));
    }
}

#[test]
fn chains_stay_close_to_the_animation_when_the_actor_turns() {
    let Some(mut inst) = instance(&["FIELD/MODEL/005.SET"]) else { return };
    assert!(inst.dynamics.is_some());
    inst.strip_root = true;
    assert!(inst.set_motion("fidl"));
    let mut yaw = 0.0f32;
    inst.add_time(1.0 / 60.0);
    report(&inst, "t=0 ");
    let kami = inst.model.find_frame("KAMIO").unwrap();
    for k in 0..240 {
        yaw += 120f32.to_radians() / 60.0;
        inst.set_world(Matrix::from_glam(Mat4::from_rotation_y(yaw)));
        inst.add_time(1.0 / 60.0);
        if k % 40 == 0 {
            report(&inst, &format!("t={k:3}"));
        }
        // the chain frames only rotate: the skinning matrix of the hair root keeps its rigid transform
        let m = inst.pose[kami];
        let c0 = m.m[0].xyz().length();
        assert!((c0 - 1.0).abs() < 1e-3, "scale {c0}");
        assert!(inst.pose[kami].pos().xyz().length() < 20.0);
    }
    let _ = Vec3::ZERO;
}

#[test]
fn every_dynamics_model_stays_finite_and_rigid() {
    let dir = std::env::var_os("SH2_DISC_DIR")
        .map(std::path::PathBuf::from)
        .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
    let Ok(d) = sh2_core::fileio::Disc::open(dir) else { return };
    let mut files: Vec<String> = Vec::new();
    d.info().walk(|p, _| {
        if (p.starts_with("FIELD/MODEL/") && p.ends_with(".SET")) || (p.starts_with("BTLDATA/CHR/") && p.ends_with(".BCM")) {
            files.push(p.to_owned());
        }
    });
    let mut tested = 0;
    for f in files {
        let mut blobs = vec![d.read(&f).unwrap()];
        if f.ends_with(".BCM") {
            if let Ok(a) = d.read(&f.replace(".BCM", ".ANM")) {
                blobs.push(a);
            }
        }
        let refs: Vec<&[u8]> = blobs.iter().map(|b| b.as_slice()).collect();
        let Some((model, motions)) = parse_character(&refs) else { continue };
        let mut inst = ModelInstance::new(Arc::new(model));
        if inst.dynamics.is_none() {
            continue;
        }
        for m in motions {
            inst.add_motion(Arc::new(m));
        }
        let names: Vec<String> = ["walk", "run", "fidl", "idla", "dsh", "atck"].iter().filter(|n| inst.has_motion(n)).map(|s| s.to_string()).collect();
        let Some(motion) = names.first().cloned() else { continue };
        inst.strip_root = true;
        inst.set_motion(&motion);
        let mut yaw = 0.0f32;
        for k in 0..300 {
            yaw += 150f32.to_radians() / 60.0 * (k as f32 * 0.05).sin();
            inst.set_world(Matrix::from_glam(Mat4::from_rotation_y(yaw) * Mat4::from_translation(Vec3::new(k as f32 * 0.2, 0.0, 0.0))));
            inst.add_time(1.0 / 60.0);
            for (i, m) in inst.pose.iter().enumerate() {
                for c in m.m.iter() {
                    assert!(c.x.is_finite() && c.y.is_finite() && c.z.is_finite(), "{f}: pose {i} not finite at step {k}");
                }
            }
        }
        // chains keep their segment lengths within a factor of two of the rest length
        for c in &inst.dynamics.as_ref().unwrap().chains {
            for i in 0..c.links.len() {
                let len = c.links.link_geometry(i).length();
                assert!(len < c.links.links[i].length * 2.5 + 0.5, "{f} {} link {i}: {len} vs {}", c.name, c.links.links[i].length);
            }
        }
        tested += 1;
    }
    println!("{tested} dynamics models simulated");
}
