//! Developer tool: decode a 4 bit `BTL_nnn` JRCTex section through the 16 CLUT entries starting at an arbitrary entry (to find which part of a multi-palette CLUT a
//! `TEX0.CSA` selects).  `btl_tex_slice <disc> <nnn> <section> <start entry> <out.rgba>`
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let b = d.read(&if a[2].contains('/') { a[2].clone() } else { format!("BTLDATA/BTL_{}.BIN", a[2]) }).unwrap();
    let k: usize = a[3].parse().unwrap();
    let start: usize = a[4].parse().unwrap();
    let off = u32::from_le_bytes(b[12 + k * 8..16 + k * 8].try_into().unwrap()) as usize;
    let u16at = |o: usize| u16::from_le_bytes([b[off + o], b[off + o + 1]]) as usize;
    let (w, h, entries, npal) = (u16at(4) as u32, u16at(6) as u32, u16at(10), u16at(12) + 1);
    let pal_base = off + 0x10;
    let pix = pal_base + npal * entries * 4;
    let n = ((w * h + 1) / 2) as usize;
    let pal = if std::env::var_os("SWZ").is_some() {
        // the whole CLUT in logical order (CSM1 file -> GS order: bits 3 and 4 of the entry number swapped), then the 16 entries from `start`
        let all = sh2_gfx::texture::read_palette(&b, pal_base, entries, false).unwrap();
        (0..16).map(|i| all[sh2_gfx::texture::csm1_swizzle(start + i)]).collect::<Vec<_>>()
    } else {
        sh2_gfx::texture::read_palette(&b, pal_base + start * 4, 16, true).unwrap()
    };
    let img = sh2_gfx::texture::decode_indexed(&b[pix..pix + n], w, h, 4, &pal).unwrap();
    std::fs::write(&a[5], &img.pixels).unwrap();
    println!("{w}x{h}");
}
