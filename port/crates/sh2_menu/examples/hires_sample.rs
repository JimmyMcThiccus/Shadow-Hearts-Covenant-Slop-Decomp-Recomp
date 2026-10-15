//! dev tool: the disc's menu / dialogue fonts as bitmap (nearest x`scale`) and hi-res text (`hifont::render_scaled`) one under the other
//! (`hires_sample <disc dir> <out.png> [scale] [text]`).
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::gamefont::{GameFont, TextImage};
use sh2_menu::msd::Msd;

fn crc(d: &[u8]) -> u32 { let mut c = 0xffff_ffffu32; for &b in d { c ^= b as u32; for _ in 0..8 { c = if c & 1 != 0 { 0xedb88320 ^ (c >> 1) } else { c >> 1 }; } } !c }
fn adler(d: &[u8]) -> u32 { let (mut a, mut b) = (1u32, 0u32); for &x in d { a = (a + x as u32) % 65521; b = (b + a) % 65521; } (b << 16) | a }
fn png(path: &str, w: u32, h: u32, rgba: &[u8]) {
    let mut raw = Vec::new();
    for y in 0..h { raw.push(0); raw.extend_from_slice(&rgba[(y * w * 4) as usize..((y + 1) * w * 4) as usize]); }
    let mut z = vec![0x78, 0x01];
    let mut i = 0;
    while i < raw.len() { let n = (raw.len() - i).min(65535); let last = i + n == raw.len(); z.push(last as u8); z.extend_from_slice(&(n as u16).to_le_bytes()); z.extend_from_slice(&(!(n as u16)).to_le_bytes()); z.extend_from_slice(&raw[i..i + n]); i += n; }
    z.extend_from_slice(&adler(&raw).to_be_bytes());
    let mut out = vec![0x89, b'P', b'N', b'G', 13, 10, 26, 10];
    let mut chunk = |t: &[u8], d: &[u8]| { out.extend_from_slice(&(d.len() as u32).to_be_bytes()); let mut c = t.to_vec(); c.extend_from_slice(d); out.extend_from_slice(&c); out.extend_from_slice(&crc(&c).to_be_bytes()); };
    let mut hd = Vec::new(); hd.extend_from_slice(&w.to_be_bytes()); hd.extend_from_slice(&h.to_be_bytes()); hd.extend_from_slice(&[8, 6, 0, 0, 0]);
    chunk(b"IHDR", &hd); chunk(b"IDAT", &z); chunk(b"IEND", &[]);
    std::fs::write(path, out).unwrap();
}

fn upscale(i: &TextImage, s: u32) -> TextImage {
    let (w, h) = (i.width * s, i.height * s);
    let mut px = vec![0u8; (w * h * 4) as usize];
    for y in 0..h { for x in 0..w {
        let (o, src) = (((y * w + x) * 4) as usize, (((y / s) * i.width + x / s) * 4) as usize);
        px[o..o + 4].copy_from_slice(&i.pixels[src..src + 4]);
    } }
    TextImage { width: w, height: h, pixels: px }
}

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let scale: u32 = a.get(3).and_then(|s| s.parse().ok()).unwrap_or(4);
    let text = a.get(4).cloned().unwrap_or_else(|| "Yuri: \"Let's go, Gepetto!\"  Karin & Joachim  HP 1234/5678  Equip Items Magic".into());
    let mut rows = Vec::new();
    for (path, i) in [("MENU/DAT/MFIELD.MSD", 0), ("COMMON/CMNMENU.DAT", 0), ("MENU/DAT/CMDMENU.MSD", 1)] {
        let Some(f) = d.read(path).and_then(|b| Msd::parse(b).ok()).and_then(|m| m.attach_data(i).and_then(GameFont::parse)) else { continue };
        for set in [0usize, 1] {
            if let Some(b) = f.render(&text, set, 0) { rows.push(upscale(&b, scale)); }
            if let Some(h) = sh2_menu::hifont::render_scaled(&f, &text, set, 0, scale) { rows.push(h); }
        }
    }
    let w = rows.iter().map(|r| r.width).max().unwrap_or(1) + 16;
    let h: u32 = rows.iter().map(|r| r.height + 8).sum::<u32>() + 8;
    let mut px = vec![0u8; (w * h * 4) as usize];
    for p in px.chunks_mut(4) { p.copy_from_slice(&[36, 38, 60, 255]); }
    let mut y0 = 8;
    for im in &rows {
        for y in 0..im.height { for x in 0..im.width {
            let s = ((y * im.width + x) * 4) as usize;
            let al = im.pixels[s + 3] as u32;
            let dd = (((y0 + y) * w + 8 + x) * 4) as usize;
            for k in 0..3 { px[dd + k] = ((im.pixels[s + k] as u32 * al + px[dd + k] as u32 * (255 - al)) / 255) as u8; }
        } }
        y0 += im.height + 8;
    }
    png(&a[2], w, h, &px);
}
