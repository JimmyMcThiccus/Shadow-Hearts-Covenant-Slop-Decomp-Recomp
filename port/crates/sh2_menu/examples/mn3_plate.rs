//! Round 6 MN3: `mn3_plate <US disc dir> <element 0..6>`: colour / alpha histogram of the ELEMENT.MSD name plate (attach k, texture 3).
fn main() {
    use sh2_menu::disc::FileSource;
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_menu::disc::DiscDir::open(&a[1]).unwrap();
    let k: usize = a[2].parse().unwrap();
    let m = sh2_menu::msd::Msd::parse(d.read("MENU/MSD/ELEMENT.MSD").unwrap()).unwrap();
    let b = m.attach_data(k).unwrap();
    for t in 0..4 {
        let off = u32::from_le_bytes(b[12 + t * 8..16 + t * 8].try_into().unwrap()) as usize;
        let img = sh2_gfx::texture::decode_menu_texture(b, off).unwrap();
        let mut h = std::collections::BTreeMap::new();
        for p in img.pixels.chunks_exact(4) {
            if p[3] > 0 {
                *h.entry((p[0] >> 4, p[1] >> 4, p[2] >> 4, p[3] >> 4)).or_insert(0u32) += 1;
            }
        }
        let mut v: Vec<_> = h.into_iter().collect();
        v.sort_by_key(|x| std::cmp::Reverse(x.1));
        println!("tex {t} {}x{}: top colours (r g b a >> 4) {:?}", img.width, img.height, &v[..v.len().min(10)]);
    }
}
