//! Character runtime features used by the field actors / battle models: in-place root motion, `Visible ` events, cross-fades.

use sh2_formats::motion::Motion;
use sh2_gfx::bevy::character::parse_character;
use sh2_gfx::model::ModelInstance;
use std::sync::Arc;

fn disc() -> Option<sh2_core::fileio::Disc> {
    let dir = std::env::var_os("SH2_DISC_DIR")
        .map(std::path::PathBuf::from)
        .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
    sh2_core::fileio::Disc::open(dir).ok()
}

fn instance(files: &[&str]) -> Option<ModelInstance> {
    let d = disc()?;
    let blobs: Vec<Vec<u8>> = files.iter().map(|f| d.read(f).unwrap()).collect();
    let refs: Vec<&[u8]> = blobs.iter().map(|b| b.as_slice()).collect();
    let (model, motions) = parse_character(&refs)?;
    let mut inst = ModelInstance::new(Arc::new(model));
    for m in motions {
        inst.add_motion(Arc::new(m));
    }
    Some(inst)
}

#[test]
fn root_translation_is_stripped_and_reported() {
    let Some(mut inst) = instance(&["FIELD/MODEL/005.SET"]) else { return };
    inst.strip_root = true;
    assert!(inst.set_motion("walk"));
    inst.add_time(0.0);
    let waist = inst.model.find_frame("WAIST0").unwrap();
    let p0 = inst.pose[waist].pos().xyz();
    // half a second of walking: the ROOT track moves ~9 units forward (-z: the model faces -z), the skeleton stays in place
    inst.add_time(0.5);
    let off = inst.root_offset;
    assert!(off.z < -6.0 && off.z > -12.0, "root offset {off:?}");
    assert!(off.x.abs() < 0.1 && off.y.abs() < 0.1);
    let p1 = inst.pose[waist].pos().xyz();
    assert!((p1 - p0).length() < 1.5, "waist moved {:?} -> {:?}", p0, p1);
    // without stripping the pose carries the translation
    let mut raw = instance(&["FIELD/MODEL/005.SET"]).unwrap();
    raw.set_motion("walk");
    raw.add_time(0.5);
    let q = raw.pose[waist].pos().xyz();
    assert!((q.z - p1.z).abs() > 5.0, "unstripped pose should move: {q:?} vs {p1:?}");
}

/// The model faces -z and the root track walks it that way: a planted foot slides towards +z relative to the body.
#[test]
fn model_faces_minus_z_and_root_motion_walks_forward() {
    let Some(mut inst) = instance(&["FIELD/MODEL/005.SET"]) else { return };
    let toe = inst.model.find_frame("RTOE0").unwrap();
    let ankle = inst.model.find_frame("RFOOT0").unwrap();
    assert!(inst.skeleton.bones[toe].bind.pos().z < inst.skeleton.bones[ankle].bind.pos().z, "toes point to -z");
    inst.strip_root = true;
    inst.set_motion("walk");
    inst.add_time(0.5);
    assert!(inst.root_offset.z < 0.0, "forward travel is -z");
}

#[test]
fn visible_events_select_one_hand_pose_per_hand() {
    let Some(mut inst) = instance(&["BTLDATA/CHR/005.BCM", "BTLDATA/CHR/005.ANM"]) else { return };
    // before any motion every atomic is visible
    assert!(inst.visible.iter().all(|&v| v));
    assert!(inst.set_motion("idla"));
    inst.add_time(0.01);
    let vis = |name: &str| {
        let i = inst.model.atomics.iter().position(|a| a.name == name).unwrap();
        inst.visible[i]
    };
    let right = ["R_hand_A", "R_hand_B", "R_hand_C"].iter().filter(|n| vis(n)).count();
    let left = ["L_hand_A", "L_hand_B", "L_hand_C"].iter().filter(|n| vis(n)).count();
    assert_eq!((right, left), (1, 1), "exactly one hand variant per side");
}

#[test]
fn cross_fade_moves_continuously() {
    let Some(mut inst) = instance(&["FIELD/MODEL/005.SET"]) else { return };
    inst.set_motion("fidl");
    inst.add_time(0.2);
    let from = inst.pose.clone();
    inst.set_motion_blend("run", 0.2);
    inst.add_time(0.01);
    let early = inst.pose.clone();
    inst.add_time(0.3);
    let late = inst.pose.clone();
    let dist = |a: &[sh2_formats::math::Matrix], b: &[sh2_formats::math::Matrix]| -> f32 {
        a.iter().zip(b).map(|(x, y)| (0..4).map(|c| (x.m[c].x - y.m[c].x).abs() + (x.m[c].y - y.m[c].y).abs() + (x.m[c].z - y.m[c].z).abs()).sum::<f32>()).sum()
    };
    // right after the switch the pose is still close to the old one, after the fade it is the new motion's pose
    assert!(dist(&from, &early) < dist(&from, &late), "{} !< {}", dist(&from, &early), dist(&from, &late));
    let _ = Motion::parse;
}
