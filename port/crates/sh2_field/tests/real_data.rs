//! Validation against the real JP demo data. Set `SH2_DISC_DIR` to the Furokuban folder; skipped otherwise.
use sh2_field::event::{FieldEvent, HitMode};
use sh2_field::floor::FloorMan;
use sh2_field::mps::Mps;
use sh2_field::pkb_compat::PkbSet;

fn set() -> Option<PkbSet> {
    PkbSet::from_env()
}

#[test]
fn all_maps_parse() {
    let Some(set) = set() else { return };
    let list = set
        .list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC"))
        .unwrap();
    let mut n = 0;
    let mut floors = 0;
    let (mut ep_total, mut ep_on_floor) = (0, 0);
    let (mut eb_total, mut eb_center_hit) = (0, 0);
    for e in list.iter().filter(|e| e.name.ends_with(".MPS")) {
        let data = set.read(&format!("FIELD/MPS/{}", e.name)).unwrap();
        let size = data.len();
        let m = Mps::parse(data).unwrap_or_else(|er| panic!("{}: {er}", e.name));
        assert_eq!(m.file_size_field() as usize, size, "{} size", e.name);
        // every typed accessor must succeed
        m.models().unwrap();
        m.lights().unwrap();
        m.entry_points().unwrap();
        m.cameras().unwrap();
        m.effects().unwrap();
        m.monster_sets().unwrap();
        m.enemy_paths().unwrap();
        let eps = m.entry_points().unwrap();
        if let Some(fd) = m.floor().unwrap() {
            floors += 1;
            let mut fm = FloorMan::new(fd).unwrap_or_else(|| panic!("{} slice count", e.name));
            for ep in &eps {
                ep_total += 1;
                if let Some(t) = fm.on_floor_chk(ep.pos) {
                    ep_on_floor += 1;
                    let h = fm.on_floor_point(ep.pos, t);
                    assert!((h - ep.pos[1]).abs() < 25.0, "{}: height {h} vs {}", e.name, ep.pos[1]);
                }
            }
        }
        let boxes = m.event_boxes().unwrap();
        let ev = FieldEvent::new(boxes.clone(), false);
        for (i, b) in boxes.iter().enumerate() {
            eb_total += 1;
            let c = [b.center[0], b.center[1], b.center[2]];
            let h = ev.hit_check(c, HitMode::All);
            if h >= 0 {
                eb_center_hit += 1;
            }
            let _ = i;
        }
        n += 1;
    }
    println!("maps={n} floors={floors} entrypoints on floor {ep_on_floor}/{ep_total}; event boxes whose centre is inside {eb_center_hit}/{eb_total}");
    assert!(n >= 40);
    assert!(ep_on_floor * 10 >= ep_total * 7, "most entry points should lie on the floor");
}

/// Retail (US) data: `SH2_US_DISC_DIR` = folder with the US PKFINFO.TBL / FIELD.PKB. Skipped when unset.
#[test]
fn us_maps_parse() {
    let Some(d) = std::env::var_os("SH2_US_DISC_DIR") else { return };
    let set = PkbSet::open(d).unwrap();
    let list = set
        .list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC"))
        .unwrap();
    let (mut n, mut mirrors, mut bgcol) = (0, 0, 0);
    for e in list.iter().filter(|e| e.name.ends_with(".MPS")) {
        let data = set.read(&format!("FIELD/MPS/{}", e.name)).unwrap();
        let m = Mps::parse(data).unwrap_or_else(|er| panic!("{}: {er}", e.name));
        m.models().unwrap();
        m.lights().unwrap();
        m.cameras().unwrap();
        m.event_boxes().unwrap();
        m.enemy_paths().unwrap();
        if !m.mirrors().unwrap().is_empty() {
            mirrors += 1;
        }
        if m.bg_color().is_some() {
            bgcol += 1;
        }
        if let Some(fd) = m.floor().unwrap() {
            assert!(FloorMan::new(fd).is_some(), "{} slice count", e.name);
        }
        n += 1;
    }
    println!("US maps={n} with MIRROR={mirrors} with BGCOLOR={bgcol}");
    assert!(n > 500);
}

/// `CField::InitSDB` + camera selection on every JP map, starting at entry point 0.
#[test]
fn field_init_and_camera() {
    use sh2_field::field::Field;
    let Some(set) = set() else { return };
    let list = set
        .list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC"))
        .unwrap();
    let (mut maps, mut with_cam, mut fixed_cams) = (0, 0, 0);
    for e in list.iter().filter(|e| e.name.ends_with(".MPS")) {
        let m = Mps::parse(set.read(&format!("FIELD/MPS/{}", e.name)).unwrap()).unwrap();
        let mut f = Field::new();
        let setup = f.init_sdb(m).unwrap();
        assert_eq!(f.state, 2);
        maps += 1;
        if setup.start_pos.is_some() && !f.cameras.is_empty() {
            let upd = f.update_field_camera(-1);
            if upd {
                with_cam += 1;
                // sanity: the evaluated rail/fixed cameras look at a point near the player and sit within a normal viewing distance
                let (c, p0) = (&f.camera, f.player_pos);
                let dist = |a: [f32; 4]| ((a[0] - p0[0]).powi(2) + (a[1] - p0[1]).powi(2) + (a[2] - p0[2]).powi(2)).sqrt();
                assert!(dist(c.target) < 100.0 && dist(c.cam_pos) < 200.0, "{}: camera goal too far from the player", e.name);
                let p = f.camera.apply(1.0 / 60.0).expect("camera pose");
                assert!(p.focal.is_finite() && p.pos[0].is_finite());
                fixed_cams += 1;
            }
        }
    }
    println!("field maps={maps} camera-evaluated={with_cam} poses={fixed_cams}");
    assert!(maps >= 40);
}

/// Walk from every on-floor entry point in 8 directions; the collision/sliding code must keep the actor on the floor.
#[test]
fn walking_stays_on_floor() {
    use sh2_field::movement::step_forward;
    let Some(set) = set() else { return };
    let list = set
        .list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC"))
        .unwrap();
    let (mut walks, mut moved, mut escaped) = (0, 0, 0);
    for e in list.iter().filter(|e| e.name.ends_with(".MPS")) {
        let m = Mps::parse(set.read(&format!("FIELD/MPS/{}", e.name)).unwrap()).unwrap();
        let Some(fd) = m.floor().unwrap() else { continue };
        let mut fm = FloorMan::new(fd).unwrap();
        for ep in m.entry_points().unwrap() {
            if fm.circle_chk(ep.pos, 4.0).is_none() {
                continue;
            }
            for k in 0..8 {
                let yaw = k as f32 * std::f32::consts::FRAC_PI_4;
                let mut p = ep.pos;
                let start = p;
                for _ in 0..300 {
                    p = step_forward(&mut fm, p, yaw, 1.2);
                    if fm.on_floor_chk(p).is_none() {
                        escaped += 1;
                        break;
                    }
                }
                walks += 1;
                if (p[0] - start[0]).abs() + (p[2] - start[2]).abs() > 5.0 {
                    moved += 1;
                }
            }
        }
    }
    println!("walks={walks} moved={moved} escaped={escaped}");
    assert!(walks > 400);
    assert_eq!(escaped, 0, "an actor walked off the floor");
    assert!(moved * 2 > walks, "most walks should make progress");
}
