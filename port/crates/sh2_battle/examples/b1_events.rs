//! Developer tool (B1): `b1_events <disc dir> <chr> [us]` lists the event tracks (MosEvent, MosCncel, SE ...) of every motion of a battle character.
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let n: u32 = a[2].parse().unwrap();
    let us = a.get(3).map(|s| s == "us").unwrap_or(false);
    let files = sh2_battle::models::chr_files_for(us, n);
    let bcm = d.read(&files[0]).unwrap();
    let anm = d.read(&files[1]).unwrap();
    let (_m, motions) = sh2_gfx::bevy::character::parse_character(&[&bcm, &anm]).unwrap();
    for m in motions {
        let ev: Vec<String> = m.events.iter().map(|e| {
            let ks: Vec<String> = e.keys().iter().map(|k| format!("{}={}", k.time, k.value)).collect();
            format!("{}[b{}]({})", e.base_name(), e.bone, ks.join(","))
        }).collect();
        println!("{:5} frames {:3} fps {} flags {:02x} root {:.1}  {}", m.name, m.last_frame(), m.fps, m.flags, 0.0, ev.join(" "));
    }
}
