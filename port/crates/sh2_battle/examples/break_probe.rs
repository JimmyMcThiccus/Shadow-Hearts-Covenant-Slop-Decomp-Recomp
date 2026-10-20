//! `break_probe <disc> <chr numbers...>`: checks that the cube table of `BreakBBox::InitParam` (`break_effects::TRI_TABLE`) matches the corner order of the BBoxes
//! of battle models (every triangle must lie in one face of the box) and prints the number of BBoxes / chips.
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    for n in &a[2..] {
        let n: u32 = n.parse().unwrap();
        let b = d.read(&format!("BTLDATA/CHR/{n:03}.BCM")).unwrap();
        let secs = sh2_battle::stage::sections(&b);
        let Some((_, mdl)) = secs.iter().find(|s| s.0 == "mdl") else {
            println!("{n}: no mdl");
            continue;
        };
        let m = sh2_formats::model::Model::parse(mdl).unwrap();
        let (mut ok, mut bad, mut empty) = (0, 0, 0);
        for bb in &m.bounds {
            let c = &bb.corners;
            if c[0].x == 0.0 && c[0].y == 0.0 && c[0].z == 0.0 {
                empty += 1;
                continue;
            }
            let p = |i: u8| [c[i as usize].x, c[i as usize].y, c[i as usize].z];
            let mut all = true;
            for t in sh2_battle::break_effects::TRI_TABLE {
                let (x, y, z) = (p(t[0]), p(t[1]), p(t[2]));
                let planar = (0..3).any(|k| (x[k] - y[k]).abs() < 1e-3 && (y[k] - z[k]).abs() < 1e-3);
                all &= planar;
            }
            if all {
                ok += 1;
            } else {
                bad += 1;
            }
        }
        println!("{n}: {} BBoxes: {ok} faces ok, {bad} mismatched, {empty} empty", m.bounds.len());
        if std::env::var_os("BOX_DUMP").is_some() {
            if let Some(bb) = m.bounds.first() {
                for (i, c) in bb.corners.iter().enumerate() {
                    println!("  corner {i}: {:.2} {:.2} {:.2}", c.x, c.y, c.z);
                }
            }
        }
    }
}
