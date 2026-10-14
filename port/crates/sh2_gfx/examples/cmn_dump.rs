//! Developer tool (E3): `cmn_dump <disc> <out dir>` writes every `COMMON/CMNEFF.DAT` entry as `<n>_rgb.ppm` / `<n>_a.pgm` and prints the sizes.
use sh2_core::fileio::Disc;
use sh2_gfx::effects::bgfx_render::parse_cmneff;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let out = std::path::PathBuf::from(&a[2]);
    std::fs::create_dir_all(&out).unwrap();
    let t = parse_cmneff(&d.read("COMMON/CMNEFF.DAT").unwrap());
    for (i, e) in t.iter().enumerate() {
        println!("{i}: {}x{}", e.w, e.h);
        let mut rgb = format!("P6\n{} {}\n255\n", e.w, e.h).into_bytes();
        for p in &e.rgb {
            rgb.extend_from_slice(p);
        }
        std::fs::write(out.join(format!("{i:02}_rgb.ppm")), rgb).unwrap();
        let mut al = format!("P5\n{} {}\n255\n", e.w, e.h).into_bytes();
        al.extend_from_slice(&e.a);
        std::fs::write(out.join(format!("{i:02}_a.pgm")), al).unwrap();
    }
}
