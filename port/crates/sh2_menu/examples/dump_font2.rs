use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(std::env::var("SH2_DISC_DIR").unwrap()).unwrap();
    let mut data = d.read(&a[1]).expect("file");
    if let Some(i) = a.get(2).and_then(|s| s.parse::<usize>().ok()) { let m = Msd::parse(data.clone()).unwrap(); let at = &m.attach_files()[i]; data = data[at.offset as usize..(at.offset + at.size) as usize].to_vec(); }
    let u32at = |o: usize| u32::from_le_bytes(data[o..o+4].try_into().unwrap()) as usize;
    let (og, oa) = (u32at(0x14), u32at(0x1c));
    let n8 = data[8] as usize; let n9 = data[9] as usize;
    println!("n8 {n8} n9 {n9} full {} half {}", u16::from_le_bytes([data[4], data[5]]), u16::from_le_bytes([data[6], data[7]]));
    let fb = &data[oa + (n8 + n9) * 2..];
    print!("full pairs: "); for i in 0..60 { print!("({},{}) ", fb[i*2], fb[i*2+1]); } println!();
    // find glyph for SJIS 0x82a0 (あ): index = (0x82-0x81)*0xbc + (0xa0-1-0x40)
    let code = (0x82u32 - 0x81) * 0xbc + (0xa0 - 1 - 0x40);
    println!("code index of あ = {code}");
    let ranges = u32at(0x18); let nr = u16::from_le_bytes([data[0xc], data[0xd]]) as usize;
    let mut acc = 0usize; let mut found = None;
    for i in 0..nr { let s = u16::from_le_bytes([data[ranges+i*4], data[ranges+i*4+1]]) as usize; let c = u16::from_le_bytes([data[ranges+i*4+2], data[ranges+i*4+3]]) as usize; if code as usize >= s && (code as usize) < s + c { found = Some(acc + code as usize - s); break; } acc += c; }
    println!("glyph # {:?}, pair {:?}", found, found.map(|g| (fb[g*2], fb[g*2+1])));
    if let Some(g) = found {
        let full = u16::from_le_bytes([data[4], data[5]]) as usize;
        let base = og + n8 * full + n9 * u16::from_le_bytes([data[6], data[7]]) as usize;
        let gl = &data[base + g * full..base + (g + 1) * full];
        for y in 0..20 { let mut s = String::new(); for x in 0..20 { let b = gl[y * 5 + x / 4]; let v = (b >> ((x & 3) * 2)) & 3; s.push([' ', '.', 'o', '#'][v as usize]); } println!("{s}"); }
    }
}
