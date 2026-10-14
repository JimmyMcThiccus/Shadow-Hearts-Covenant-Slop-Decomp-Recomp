//! Developer tool: frame names of a battle character (`fx_frames <disc dir> <chr no>`; the US disc keeps the motions in `BTLDATA/CHRANM`).
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let n: u32 = a[2].parse().unwrap();
    let us = a.get(3).map(|s| s == "us").unwrap_or(false);
    let files = sh2_battle::models::chr_files_for(us, n);
    let bcm = d.read(&files[0]).unwrap();
    let anm = d.read(&files[1]).unwrap();
    let (m, motions) = sh2_gfx::bevy::character::parse_character(&[&bcm, &anm]).unwrap();
    println!("{:?}", m.frames.iter().enumerate().map(|(i, f)| format!("{i}:{}", f.name)).collect::<Vec<_>>());
    println!("motions {:?}", motions.iter().map(|m| m.name.as_str()).collect::<Vec<_>>());
}
