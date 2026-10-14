//! Renderer fidelity checks against real map data (`SH2_US_DISC_DIR` / `SH2_DISC_DIR`; skipped when unset).
use sh2_field::bevy::{build_lights, mirror_records};
use sh2_field::mps::{ModelKind, Mps};
use sh2_formats::model::{Model, TexFormat};
use sh2_formats::motion::Motion;
use sh2_gfx::bevy::bgmotion::{decode_event, event_keys, parse_texanim, BgEvent};
use sh2_gfx::bevy::map::{alpha_census, plan_draws};
use sh2_gfx::bevy::mirror::MirrorPlane;
use sh2_gfx::bevy::{Sh2Blend, Sh2Disc, TestMode};

fn us() -> Option<Sh2Disc> {
    Sh2Disc::from_env(true)
}
fn jp() -> Option<Sh2Disc> {
    Sh2Disc::from_env(false)
}
fn mps(d: &Sh2Disc, name: &str) -> Mps {
    Mps::parse(d.read(&format!("FIELD/MPS/{name}.MPS")).unwrap()).unwrap()
}

#[test]
fn light_chunk_decodes_like_cbgelement_create() {
    let Some(d) = jp() else { return };
    let (lights, mut lc) = build_lights(&mps(&d, "AP_00_U"));
    // directional (shadow caster), point, ambient
    assert_eq!(lights.iter().map(|l| l.kind).collect::<Vec<_>>(), vec![1, 2, 0]);
    assert!(lights[0].shadow && lights[0].active);
    assert_eq!(lights[0].level, 1);
    assert_eq!(lc.num_light, 3);
    let m = lc.light_matrix(glam::Vec3::new(0.0, 0.0, 0.0));
    assert!(m.ambient.x > 0.2 && m.count >= 1);
}

#[test]
fn map_atomics_are_alpha_blended_with_a_split_test() {
    let Some(d) = jp() else { return };
    let m = mps(&d, "PA_03_U");
    let rec = m.models().unwrap().into_iter().find(|r| matches!(r.kind, ModelKind::Bg0)).unwrap();
    let model = Model::parse(m.model_blob(&rec)).unwrap();
    // every atomic carries PRIM = 0x7c: ABE + FGE + TME
    assert!(model.atomics.iter().all(|a| a.flags & 0x70 == 0x70));
    let mut two_pass = 0;
    for a in &model.atomics {
        let t = model.textures.get(a.texture as usize).unwrap();
        let census = alpha_census(&t.to_rgba8(), 112.0);
        let plan = plan_draws(a.flags & 0xf0, Some(t), census);
        assert!(plan.draws.iter().all(|d| d.fog));
        if plan.draws.len() == 2 {
            two_pass += 1;
            assert_eq!(plan.draws[0].test, TestMode::CutIn);
            assert_eq!(plan.draws[1].blend, Sh2Blend::Normal);
        }
    }
    assert!(two_pass > 10, "foliage / shadow overlays need the two-pass split");
}

#[test]
fn mirror_records_and_planes() {
    let Some(d) = us() else { return };
    let m = mps(&d, "MS_01_U");
    let recs = mirror_records(&m);
    assert_eq!(recs.len(), 1);
    let c = recs[0].map(|v| glam::Vec3::new(v[0], v[1], v[2]));
    // a wall mirror at x = 170 spanning z 364..386
    assert!(c.iter().all(|p| (p.x - 170.0).abs() < 0.01));
    let plane = MirrorPlane::from_corners(c).unwrap();
    assert!(plane.normal.x.abs() > 0.99);
}

#[test]
fn texture_animation_and_bg_motion_events() {
    let Some(d) = us() else { return };
    let m = mps(&d, "IF_00_U");
    let recs = m.models().unwrap();
    let mut entries = 0;
    for rec in &recs {
        if matches!(rec.kind, ModelKind::Motion) {
            continue;
        }
        let blob = m.model_blob(rec);
        let model = Model::parse(blob).unwrap();
        for e in parse_texanim(blob, &model) {
            entries += 1;
            assert!(!e.frames.is_empty());
            assert_eq!(e.frames[0].len(), (e.rows * e.rrw * 4) as usize);
            assert!(model.textures[e.texture].format != TexFormat::Ipu);
        }
    }
    assert_eq!(entries, 2, "dr5 and fl");
    // DR_close_IDL / dr_op motions drive the door texture with TXAdr5 keys
    let mo = recs.iter().filter(|r| matches!(r.kind, ModelKind::Motion)).map(|r| Motion::parse(m.model_blob(r)).unwrap()).find(|mo| mo.name == "dr_op").unwrap();
    let ev = mo.events.iter().find(|e| e.name.starts_with("TXA")).unwrap();
    let keys = event_keys(ev);
    assert!(keys.len() >= 2);
    assert_eq!(decode_event(&ev.name, ev.bone, keys[1].1), Some(BgEvent::TexAnim { name: "dr5".into(), frame: keys[1].1 as usize }));
}

#[test]
fn ipu_texture_decodes_every_frame() {
    let Some(d) = us() else { return };
    let m = mps(&d, "GY_05_F");
    let mut found = false;
    for rec in m.models().unwrap() {
        if matches!(rec.kind, ModelKind::Motion) {
            continue;
        }
        let Ok(model) = Model::parse(m.model_blob(&rec)) else { continue };
        for t in model.textures.iter().filter(|t| t.format == TexFormat::Ipu) {
            let mv = sh2_gfx::ipu::decode_ipum(&t.data).expect("ipum decodes (every frame ends exactly at its start code)");
            assert_eq!((mv.width, mv.height, mv.frames.len()), (256, 256, 120));
            // frame 0 has dark borders and bright content
            let f = &mv.frames[0];
            let lum = |x: usize, y: usize| f[(y * 256 + x) * 4] as u32 + f[(y * 256 + x) * 4 + 1] as u32;
            assert!(lum(2, 2) < 60);
            assert!((0..256).step_by(8).flat_map(|y| (0..256).step_by(8).map(move |x| (x, y))).any(|(x, y)| lum(x, y) > 120));
            found = true;
        }
    }
    assert!(found);
}
