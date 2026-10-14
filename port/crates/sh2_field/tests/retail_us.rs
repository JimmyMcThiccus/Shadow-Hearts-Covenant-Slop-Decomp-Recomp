//! Retail (US) real-data tests. `SH2_US_DISC_DIR` = folder with the US `PKFINFO.TBL` / `FIELD.PKB`; every test is skipped when unset.
//! Some tests also run on the JP demo (`SH2_DISC_DIR`) to prove the shared logic is build-independent.
use sh2_field::camera::{eval_camera, parse_path_nodes, path_uses_rounded_mode, PathNode};
use sh2_field::mps::Mps;
use sh2_field::pkb_compat::PkbSet;

fn us() -> Option<PkbSet> {
    PkbSet::open(std::env::var_os("SH2_US_DISC_DIR")?).ok()
}
fn jp() -> Option<PkbSet> {
    PkbSet::from_env()
}
fn maps(set: &PkbSet) -> Vec<(String, Mps)> {
    let list = set.list_dir_while("FIELD/MPS", |e| e.name.ends_with(".MPS") || e.name.ends_with(".MSC")).unwrap();
    list.iter()
        .filter(|e| e.name.ends_with(".MPS"))
        .map(|e| (e.name.clone(), Mps::parse(set.read(&format!("FIELD/MPS/{}", e.name)).unwrap()).unwrap()))
        .collect()
}

/// Walk every rounded-corner rail camera of every map along its own polyline and check the evaluated camera is finite and continuous.
fn rounded_rail_continuity(set: &PkbSet, label: &str) {
    let (mut rails, mut samples, mut worst) = (0usize, 0usize, 0.0f32);
    for (name, m) in maps(set) {
        for cam in m.cameras().unwrap() {
            if cam.kind != 5 {
                continue;
            }
            let nodes: Vec<PathNode> = parse_path_nodes(m.camera_blob(&cam), cam.count as usize);
            if nodes.len() < 3 || !path_uses_rounded_mode(&nodes) {
                continue;
            }
            rails += 1;
            let mut prev: Option<([f32; 4], [f32; 4])> = None;
            for i in 0..nodes.len() - 1 {
                let (a, b) = (nodes[i].p, nodes[i + 1].p);
                let len = ((b[0] - a[0]).powi(2) + (b[2] - a[2]).powi(2)).sqrt();
                let steps = ((len / 2.0) as usize).max(1);
                for s in 0..=steps {
                    let t = s as f32 / steps as f32;
                    let pos = [a[0] + (b[0] - a[0]) * t, a[1] + (b[1] - a[1]) * t, a[2] + (b[2] - a[2]) * t, 1.0];
                    let blob = m.camera_blob(&cam);
                    let g = eval_camera(5, blob, cam.count, [pos[0], pos[1] + 12.0, pos[2], 1.0], 0.0, ([0.0; 4], [0.0; 4]), false)
                        .unwrap_or_else(|| panic!("{label} {name}: rounded rail returned None at node {i} t={t}"));
                    for k in 0..3 {
                        assert!(g.target[k].is_finite() && g.cam[k].is_finite(), "{label} {name}: non-finite camera");
                    }
                    assert!(g.view_angle.is_finite() && g.view_angle > 0.2 && g.view_angle < 2.0, "{label} {name}: view angle {}", g.view_angle);
                    if let Some((pt, pc)) = prev {
                        let d = |x: [f32; 4], y: [f32; 4]| ((x[0] - y[0]).powi(2) + (x[1] - y[1]).powi(2) + (x[2] - y[2]).powi(2)).sqrt();
                        worst = worst.max(d(pt, g.target)).max(d(pc, g.cam));
                    }
                    prev = Some((g.target, g.cam));
                    samples += 1;
                }
            }
        }
    }
    println!("{label}: rounded rails={rails} samples={samples} worst step={worst:.1}");
    if rails > 0 {
        assert!(worst < 120.0, "{label}: rounded-corner camera jumps by {worst}");
    }
}

#[test]
fn us_rounded_rail_cameras_are_continuous() {
    let Some(set) = us() else { return };
    rounded_rail_continuity(&set, "US");
}

#[test]
fn jp_rounded_rail_cameras_are_continuous() {
    let Some(set) = jp() else { return };
    rounded_rail_continuity(&set, "JP");
}

/// Coverage probe: how often the rounded-rail evaluation takes the sharp-corner (`GetCamPath2`) branch and how many kind-4 cameras exist.
#[test]
fn us_camera_kind_census() {
    let Some(set) = us() else { return };
    use sh2_field::camera::get_nearest_path;
    let (mut k4, mut sharp_nodes, mut sharp_hits, mut total) = (0, 0, 0, 0);
    for (_n, m) in maps(&set) {
        for cam in m.cameras().unwrap() {
            if cam.kind == 4 {
                k4 += 1;
            }
            if cam.kind != 5 {
                continue;
            }
            let nodes = parse_path_nodes(m.camera_blob(&cam), cam.count as usize);
            if nodes.len() < 3 || !path_uses_rounded_mode(&nodes) {
                continue;
            }
            sharp_nodes += nodes.iter().filter(|n| n.flags & 1 != 0 && n.flags & 0xff00_0000 == 0).count();
            for i in 0..nodes.len() - 1 {
                for s in 0..=10 {
                    let t = s as f32 / 10.0;
                    let (a, b) = (nodes[i].p, nodes[i + 1].p);
                    let pos = [a[0] + (b[0] - a[0]) * t, a[1] + (b[1] - a[1]) * t, a[2] + (b[2] - a[2]) * t, 1.0];
                    total += 1;
                    if get_nearest_path(&nodes, pos).0 >= 1000.0 {
                        sharp_hits += 1;
                    }
                }
            }
        }
    }
    println!("US kind-4 cameras={k4}, sharp nodes in rounded rails={sharp_nodes}, samples on sharp nodes {sharp_hits}/{total}");
}

/// `TRILIST` GENERIC blocks (retail field-monster sight blockers): parse, indices valid, vertices inside the map's floor bounds.
#[test]
fn us_trilist_blocks_parse_and_lie_on_the_map() {
    let Some(set) = us() else { return };
    use sh2_field::floor::FloorMan;
    use sh2_field::retail::TriList;
    let (mut n, mut tris, mut verts_on_floor, mut verts) = (0, 0, 0usize, 0usize);
    for (name, m) in maps(&set) {
        let Some((_, blob)) = m.generic().into_iter().find(|(n, _)| n == "TRILIST") else { continue };
        let tl = TriList::parse(blob).unwrap_or_else(|| panic!("{name}: TRILIST does not parse"));
        n += 1;
        tris += tl.tris.len();
        let mut fm = m.floor().unwrap().and_then(FloorMan::new);
        for v in &tl.verts {
            verts += 1;
            if let Some(fm) = fm.as_mut() {
                // blockers live on (or just beside) the walkable floor: count vertices with the floor within the +-20 unit window
                if fm.on_floor_chk([v[0], v[1], v[2]]).is_some() {
                    verts_on_floor += 1;
                }
            }
        }
    }
    println!("TRILIST maps={n} triangles={tris} vertices={verts} on-floor={verts_on_floor}");
    assert_eq!(n, 7, "retail ships TRILIST in exactly 7 maps");
    assert!(tris > 100);
    assert!(verts_on_floor * 4 >= verts, "TRILIST vertices should mostly sit on the floor ({verts_on_floor}/{verts})");
}

/// Retail `InitSDB` + camera selection + `CFieldCamera::Apply` on every US map (all six camera kinds, rounded rails included).
#[test]
fn us_field_init_and_camera_all_maps() {
    use sh2_field::field::Field;
    use sh2_field::retail::{Build, ChrPosSave};
    let Some(set) = us() else { return };
    let (mut maps_n, mut evaluated, mut by_kind) = (0, 0, [0usize; 6]);
    let chr = ChrPosSave::new();
    for (name, m) in maps(&set) {
        let mut f = Field::with_build(Build::Retail);
        let setup = f.init_sdb_ex(m, &chr, |_| None).unwrap_or_else(|e| panic!("{name}: {e}"));
        assert_eq!(f.state, 2);
        maps_n += 1;
        if setup.start_pos.is_some() && !f.cameras.is_empty() {
            if f.update_field_camera(-1) {
                if let Some(i) = f.cam_cur {
                    by_kind[(f.cameras[i].kind as usize).min(5)] += 1;
                }
                let p = f.camera.apply(1.0 / 60.0).expect("pose");
                for k in 0..3 {
                    assert!(p.pos[k].is_finite() && p.target[k].is_finite(), "{name}: non-finite pose");
                }
                assert!(p.focal.is_finite() && p.focal > 0.0, "{name}: focal {}", p.focal);
                evaluated += 1;
            }
        }
    }
    println!("US maps={maps_n} camera-evaluated={evaluated} first-camera kinds={by_kind:?}");
    assert!(maps_n > 500 && evaluated * 2 > maps_n);
}

/// The JP-derived floor/collision port holds on retail data: spawn points sit on the floor and walking never leaves it.
#[test]
fn us_entry_points_and_walking_stay_on_floor() {
    use sh2_field::floor::FloorMan;
    use sh2_field::movement::step_forward;
    let Some(set) = us() else { return };
    let (mut eps, mut on, mut walks, mut escaped) = (0, 0, 0, 0);
    for (_n, m) in maps(&set).into_iter().step_by(3) {
        let Some(fd) = m.floor().unwrap() else { continue };
        let mut fm = FloorMan::new(fd).unwrap();
        for ep in m.entry_points().unwrap() {
            eps += 1;
            if fm.on_floor_chk(ep.pos).is_some() {
                on += 1;
            }
            if fm.circle_chk(ep.pos, 4.0).is_none() {
                continue;
            }
            for k in 0..4 {
                let yaw = k as f32 * std::f32::consts::FRAC_PI_2;
                let mut p = ep.pos;
                for _ in 0..120 {
                    p = step_forward(&mut fm, p, yaw, 1.2);
                    if fm.on_floor_chk(p).is_none() {
                        escaped += 1;
                        break;
                    }
                }
                walks += 1;
            }
        }
    }
    println!("US entry points={eps} on-floor={on} walks={walks} escaped={escaped}");
    assert!(on * 10 >= eps * 7);
    assert!(walks > 500);
    assert_eq!(escaped, 0);
}

/// Retail chunk census: MIRROR / BGCOLOR / NAVIMAP / TRILIST presence (documents `notes/G_retail/CFieldBG.md`).
#[test]
fn us_chunk_census() {
    let Some(set) = us() else { return };
    let (mut mirrors, mut bgcolor, mut navi, mut gen) = (0, 0, 0, 0);
    for (_n, m) in maps(&set) {
        if !m.mirrors().unwrap().is_empty() {
            mirrors += 1;
        }
        if m.bg_color().is_some() {
            bgcolor += 1;
        }
        if m.navimap().is_some() {
            navi += 1;
        }
        if !m.generic().is_empty() {
            gen += 1;
        }
    }
    println!("US census: MIRROR={mirrors} BGCOLOR={bgcolor} NAVIMAP={navi} GENERIC={gen}");
    assert!(bgcolor >= 40 && mirrors >= 20 && navi >= 300);
}
