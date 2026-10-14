//! Round 5 FX: dump `BTLDATA/BTL_000.BIN` JRCTex entries as raw RGBA + size (`fx_r5_btltex <out dir> [entries..]`), for checking the trail / hit textures.
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let d = sh2_core::fileio::Disc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let b = d.read("BTLDATA/BTL_000.BIN").unwrap();
    let secs = sh2_battle::stage::sections(&b);
    for k in a[1..].iter().map(|s| s.parse::<usize>().unwrap()) {
        let (tag, sec) = &secs[k];
        let Ok(i) = sh2_gfx::texture::decode_jrc(sec, 0, 0) else { println!("{k} {tag}: not a JRCTex"); continue };
        let p = format!("{}/btl000_{k}_{}x{}.rgba", a[0], i.width, i.height);
        std::fs::write(&p, &i.pixels).unwrap();
        println!("{k} {tag} {}x{} -> {p}", i.width, i.height);
    }
}
