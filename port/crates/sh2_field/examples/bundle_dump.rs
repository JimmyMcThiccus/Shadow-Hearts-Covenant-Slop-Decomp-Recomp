//! Debug: dump the entries of a `{count, total, {tag,off}[count]}` bundle (SHOP.DAT, TAILOR.DAT, SOLOMON.DAT, COMP.DAT ...):
//! `bundle_dump [--us] PATH OUTDIR` -> `OUTDIR/<k>.<tag>` raw + `<k>.png` when the entry is a menu texture.
use sh2_field::pkb_compat::PkbSet;
use sh2_gfx::texture::{decode_menu_texture, Rgba8Image};
fn crc(d: &[u8]) -> u32 { let mut c = 0xffff_ffffu32; for &b in d { c ^= b as u32; for _ in 0..8 { c = if c & 1 != 0 { 0xedb88320 ^ (c >> 1) } else { c >> 1 }; } } !c }
fn adler(d: &[u8]) -> u32 { let (mut a, mut b) = (1u32, 0u32); for &x in d { a = (a + x as u32) % 65521; b = (b + a) % 65521; } (b << 16) | a }
pub fn png(path: &str, img: &Rgba8Image) {
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
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();
    let b = set.read(v[0]).expect("not found");
    std::fs::create_dir_all(v[1]).unwrap();
    let n = u32::from_le_bytes(b[0..4].try_into().unwrap()) as usize;
    for k in 0..n {
        let tag = String::from_utf8_lossy(&b[8 + k * 8..8 + k * 8 + 3]).to_string();
        let ent = sh2_field::worldmap::bundle_entry(&b, k).unwrap_or(&[]);
        let off = u32::from_le_bytes(b[12 + k * 8..16 + k * 8].try_into().unwrap()) as usize;
        std::fs::write(format!("{}/{k:02}.{tag}", v[1]), ent).unwrap();
        if tag == "msg" {
            for (i, m) in sh2_field::worldmap::parse_msg_table(ent).iter().enumerate() {
                println!("   msg[{i}] {}", sh2_menu::sjis::decode(m).replace('\n', "\\n"));
            }
        }
        match decode_menu_texture(&b, off) {
            Ok(img) => { println!("{k:2} {tag} off {off:#x} len {} tex {}x{}", ent.len(), img.width, img.height); png(&format!("{}/{k:02}.png", v[1]), &img); }
            Err(e) => println!("{k:2} {tag} off {off:#x} len {} ({e:?})", ent.len()),
        }
    }
}
