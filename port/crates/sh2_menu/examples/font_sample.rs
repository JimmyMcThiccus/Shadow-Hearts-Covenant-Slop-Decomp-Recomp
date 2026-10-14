//! dev tool: render a sample line with the disc's bitmap fonts to a PNG (`font_sample <disc dir> <out.png> [text]`)
use sh2_menu::disc::DiscDir;
use sh2_menu::gamefont::FontBank;
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
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let bank = FontBank::load(&d);
    let text = a.get(3).cloned().unwrap_or_else(|| "Items Equip Magic 0123456789 The quick brown fox".into());
    let text = sh2_menu::sjis::decode(&text.bytes().collect::<Vec<u8>>());
    let mut rows = Vec::new();
    for n in [0u8, 2, 3] { if let Some(f) = bank.fonts[n as usize].as_ref() { for set in 0..3 { if let Some(i) = f.render(&text, set, 0) { rows.push(i); } } } }
    let w = rows.iter().map(|r| r.width).max().unwrap_or(1) + 8;
    let h: u32 = rows.iter().map(|r| r.height + 4).sum::<u32>() + 4;
    let mut px = vec![60u8; (w * h * 4) as usize];
    for p in px.chunks_mut(4) { p[3] = 255; p[0] = 60; p[1] = 60; p[2] = 80; }
    let mut y0 = 4;
    for r in &rows {
        for y in 0..r.height { for x in 0..r.width {
            let s = &r.pixels[((y * r.width + x) * 4) as usize..][..4];
            let o = (((y0 + y) * w + 4 + x) * 4) as usize;
            let al = s[3] as u32;
            for k in 0..3 { px[o + k] = ((s[k] as u32 * al + px[o + k] as u32 * (255 - al)) / 255) as u8; }
        } }
        y0 += r.height + 4;
    }
    png(&a[2], w, h, &px);
    println!("wrote {} ({}x{})", a[2], w, h);
}
