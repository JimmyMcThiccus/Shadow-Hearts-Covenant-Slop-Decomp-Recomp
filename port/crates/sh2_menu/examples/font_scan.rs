//! dev tool: find every bitmap font on a disc (`font_scan <disc dir> [out dir]`).  Tries `GameFont::parse` on every PKB entry and on
//! every MSD attachment, prints cell size / glyph counts, and with an out dir writes a sample PNG per distinct font.
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::gamefont::GameFont;
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

const LINES: [&str; 3] = ["ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789", "abcdefghijklmnopqrstuvwxyz .,!?'-:()&", "Yuri Karin Gepetto Joachim Lucia Blanca"];

fn sample(f: &GameFont, path: &str) {
    let imgs: Vec<_> = LINES.iter().filter_map(|l| f.render(l, 0, 0)).collect();
    if imgs.is_empty() { return; }
    let w = imgs.iter().map(|i| i.width).max().unwrap() + 8;
    let h: u32 = imgs.iter().map(|i| i.height + 4).sum::<u32>() + 4;
    let mut px = vec![0u8; (w * h * 4) as usize];
    for p in px.chunks_mut(4) { p.copy_from_slice(&[40, 40, 56, 255]); }
    let mut y0 = 4;
    for im in &imgs {
        for y in 0..im.height { for x in 0..im.width {
            let s = ((y * im.width + x) * 4) as usize;
            let a = im.pixels[s + 3] as u32;
            if a == 0 { continue; }
            let d = (((y0 + y) * w + 4 + x) * 4) as usize;
            for k in 0..3 { px[d + k] = ((im.pixels[s + k] as u32 * a + px[d + k] as u32 * (255 - a)) / 255) as u8; }
        } }
        y0 += im.height + 4;
    }
    png(path, w, h, &px);
}

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let out = a.get(2);
    let mut seen = std::collections::HashSet::new();
    let mut try_blob = |name: &str, blob: &[u8]| {
        if let Some(f) = GameFont::parse(blob) {
            let key = crc(blob);
            let dup = !seen.insert(key);
            println!("{name}\tcell {}x{}\tlen {:#x}\tcrc {key:08x}{}", f.cell_w, f.cell_h, blob.len(), if dup { "\t(dup)" } else { "" });
            if let (Some(o), false) = (out, dup) {
                sample(&f, &format!("{o}/{}_{}x{}.png", name.replace(['/', ' ', '#'], "_"), f.cell_w, f.cell_h));
            }
        }
    };
    for (_dir, files) in d.disc().listing() {
        for (name, _) in files {
            let full = name.to_string();
            let Some(data) = d.read(&full) else { continue };
            try_blob(&full, &data);
            if let Ok(m) = Msd::parse(data.clone()) {
                for i in 0..m.attach_files().len() {
                    if let Some(b) = m.attach_data(i) { try_blob(&format!("{full}#{i}"), b); }
                }
            }
        }
    }
}
