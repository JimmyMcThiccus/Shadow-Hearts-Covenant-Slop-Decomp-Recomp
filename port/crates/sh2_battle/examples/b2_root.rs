//! Developer tool (B2): `b2_root <US disc dir> <hp>` finds the monsters with that HP, then dumps the ROOT track of their hit / dash motions
//! (translation per frame) so a measured on-screen knock-back can be compared with the motion's own root travel.
use sh2_battle::data::BattleData;
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    let hp: u16 = a[2].parse().unwrap();
    let data = BattleData::load_us(&d).expect("battle data");
    let mut chrs = vec![]; let mut n = 0;
    for id in 0..2000usize {
        if let Some(m) = data.monster(id) { n += 1;
            if m.hp == hp {
                println!("monster {id}: hp {} chr_model {} size_class {}", m.hp, m.chr_model, m.size_class);
                chrs.push(m.chr_model as u32);
            }
        }
    }
    println!("{n} monsters"); chrs.sort();
    chrs.dedup();
    for n in chrs {
        let files = sh2_battle::models::chr_files_for(true, n);
        let (Ok(bcm), Ok(anm)) = (d.read(&files[0]), d.read(&files[1])) else { println!("CHR {n}: files missing"); continue };
        let Some((_m, motions)) = sh2_gfx::bevy::character::parse_character(&[&bcm, &anm]) else { continue };
        println!("== CHR {n}: {} motions", motions.len());
        for m in &motions {
            let Some(t) = m.tracks.iter().find(|t| t.name == "ROOT").or_else(|| m.tracks.first()) else { continue };
            let end = m.last_frame() as f32;
            let (a0, a1) = (t.translation_at(0.0), t.translation_at(end));
            println!("{:5} frames {:3} fps {:2}  root d=({:.2}, {:.2}, {:.2})", m.name, m.last_frame(), m.fps, a1.x - a0.x, a1.y - a0.y, a1.z - a0.z);
            if ["blwa", "flya", "defa", "koda"].contains(&m.name.as_str()) {
                let mut s = String::new();
                let mut f = 0.0;
                while f <= end {
                    let p = t.translation_at(f);
                    s += &format!("{:.0}:({:.2},{:.2}) ", f, p.x - a0.x, p.z - a0.z);
                    f += 1.0;
                }
                println!("      per frame (x,z): {s}");
            }
        }
    }
}
