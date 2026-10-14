use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(std::env::var("SH2_DISC_DIR").unwrap()).unwrap();
    let mut data = d.read(&a[1]).expect("file");
    if let Some(i) = a.get(2).and_then(|s| s.parse::<usize>().ok()) { let m = Msd::parse(data.clone()).unwrap(); let at = &m.attach_files()[i]; data = data[at.offset as usize..(at.offset + at.size) as usize].to_vec(); }
    println!("len {:#x}", data.len());
    println!("hdr {:02x?}", &data[..0x40]);
    let u32at = |o: usize| u32::from_le_bytes(data[o..o+4].try_into().unwrap()) as usize;
    let u16at = |o: usize| u16::from_le_bytes(data[o..o+2].try_into().unwrap()) as usize;
    let (oc, og, or_, oa) = (u32at(0x10), u32at(0x14), u32at(0x18), u32at(0x1c));
    println!("clut@{oc:#x} glyphs@{og:#x} ranges@{or_:#x} aux@{oa:#x} nranges {}", u16at(0xc));
    for i in 0..u16at(0xc).min(40) { println!("  range {i}: start {} count {}", u16at(or_ + i*4), u16at(or_ + i*4 + 2)); }
    println!("clut {:02x?}", &data[oc..oc + 0x40]);
    println!("aux {:02x?}", &data[oa..oa + 0x40]);
    println!("half glyph area {:02x?}", &data[og..og+0x40]);
}
