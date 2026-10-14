//! dev tool: dump the attach files of a scene (nested via path "a/b": index chain), decoding menu textures to PNG
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
use sh2_gfx::texture::{decode_menu_texture, Rgba8Image};
fn crc(d: &[u8]) -> u32 { let mut c = 0xffff_ffffu32; for &b in d { c ^= b as u32; for _ in 0..8 { c = if c & 1 != 0 { 0xedb88320 ^ (c >> 1) } else { c >> 1 }; } } !c }
fn adler(d: &[u8]) -> u32 { let (mut a, mut b) = (1u32, 0u32); for &x in d { a = (a + x as u32) % 65521; b = (b + a) % 65521; } (b << 16) | a }
fn png(path: &str, img: &Rgba8Image) {
    let mut raw = Vec::new();
    for y in 0..img.height { raw.push(0); for x in 0..img.width { raw.extend_from_slice(&img.px(x, y)); } }
    let mut z = vec![0x78, 0x01];
    let mut i = 0;
    while i < raw.len() { let n = (raw.len() - i).min(65535); let last = i + n == raw.len(); z.push(last as u8); z.extend_from_slice(&(n as u16).to_le_bytes()); z.extend_from_slice(&(!(n as u16)).to_le_bytes()); z.extend_from_slice(&raw[i..i + n]); i += n; }
    z.extend_from_slice(&adler(&raw).to_be_bytes());
    let mut out = vec![0x89, b'P', b'N', b'G', 13, 10, 26, 10];
    let mut chunk = |t: &[u8], d: &[u8]| { out.extend_from_slice(&(d.len() as u32).to_be_bytes()); let mut c = t.to_vec(); c.extend_from_slice(d); out.extend_from_slice(&c); out.extend_from_slice(&crc(&c).to_be_bytes()); };
    let mut h = Vec::new(); h.extend_from_slice(&img.width.to_be_bytes()); h.extend_from_slice(&img.height.to_be_bytes()); h.extend_from_slice(&[8, 6, 0, 0, 0]);
    chunk(b"IHDR", &h); chunk(b"IDAT", &z); chunk(b"IEND", &[]);
    std::fs::write(path, out).unwrap();
}
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(std::env::var("SH2_DISC_DIR").unwrap()).unwrap();
    let mut data = d.read(&a[1]).expect("file");
    for idx in a[2].split('/').filter(|s| !s.is_empty()) {
        let m = Msd::parse(data.clone()).unwrap();
        let at = &m.attach_files()[idx.parse::<usize>().unwrap()];
        data = data[at.offset as usize..(at.offset + at.size) as usize].to_vec();
    }
    let m = Msd::parse(data.clone()).unwrap();
    let outdir = a.get(3).cloned();
    let mut imgs: Vec<(usize, Rgba8Image)> = Vec::new();
    for (i, at) in m.attach_files().iter().enumerate() {
        let b = &data[at.offset as usize..(at.offset + at.size) as usize];
        let t = decode_menu_texture(b, 0);
        println!("attach {i} id {} off {:#x} size {:#x} head {:02x?} tex {:?}", at.id, at.offset, at.size, &b[..16.min(b.len())], t.as_ref().map(|i| (i.width, i.height)).map_err(|e| e.to_string()));
        if let Ok(img) = t { imgs.push((i, img)); }
    }
    if let Some(dir) = &outdir {
        // contact sheet: grid of 4 columns of 260px cells on mid gray
        let sc: u32 = std::env::var("SCALE").ok().and_then(|v| v.parse().ok()).unwrap_or(1); let cols = if sc > 1 { 2 } else { 4u32 }; let cw = 260u32 * sc.min(2); let ch = 140u32 * sc.min(2);
        let rows = (imgs.len() as u32 + cols - 1) / cols;
        let mut sheet = Rgba8Image::new(cols * cw, rows.max(1) * ch);
        for p in sheet.pixels.chunks_mut(4) { p.copy_from_slice(&[90, 90, 110, 255]); }
        for (n, (_, img)) in imgs.iter().enumerate() {
            let (ox, oy) = ((n as u32 % cols) * cw, (n as u32 / cols) * ch);
            for y in 0..(img.height * sc).min(ch - 2) { for x in 0..(img.width * sc).min(cw - 2) {
                let s = img.px(x / sc, y / sc); let o = (((oy + y) * sheet.width + ox + x) * 4) as usize;
                let al = s[3] as u32;
                for k in 0..3 { sheet.pixels[o + k] = ((s[k] as u32 * al + sheet.pixels[o + k] as u32 * (255 - al)) / 255) as u8; }
            } }
        }
        png(&format!("{dir}/sheet.png"), &sheet);
        for (i, img) in &imgs { println!("sheet cell {} = attach {i} {}x{}", imgs.iter().position(|(j, _)| j == i).unwrap(), img.width, img.height); }
    }
}
