//! Write the attach-file textures of a menu scene (and of one nested scene) as raw RGBA files (`tNN_WxH.rgba`):
//! `msd_tex_dump FILE OUTDIR [nested]` with `SH2_DISC_DIR` pointing at the disc.
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(std::env::var("SH2_DISC_DIR").unwrap()).unwrap();
    let mut m = Msd::parse(d.read(&a[1]).expect("file")).unwrap();
    if let Some(n) = a.get(3).and_then(|s| s.parse::<usize>().ok()) {
        m = m.attach_scene(n).expect("nested scene");
    }
    std::fs::create_dir_all(&a[2]).unwrap();
    for i in 0..m.attach_files().len() {
        let Some(b) = m.attach_data(i) else { continue };
        match sh2_gfx::texture::decode_menu_texture(b, 0) {
            Ok(img) if img.width > 0 && img.height > 0 => {
                let p = format!("{}/t{i:02}_{}x{}.rgba", a[2], img.width, img.height);
                std::fs::write(&p, &img.pixels).unwrap();
                println!("{p}");
            }
            _ => println!("attach {i}: not a texture ({} bytes)", b.len()),
        }
    }
}
