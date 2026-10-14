use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
use sh2_menu::sjis;
fn u32_at(d: &[u8], o: usize) -> u32 { u32::from_le_bytes(d[o..o+4].try_into().unwrap()) }
fn cstr(d: &[u8], o: usize) -> &[u8] { if o >= d.len() { return &[]; } let e = d[o..].iter().position(|&b| b == 0).map(|p| o + p).unwrap_or(d.len()); &d[o..e] }
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(std::env::var("SH2_DISC_DIR").unwrap()).unwrap();
    let mut data = d.read(&a[1]).expect("file");
    if let Some(idx) = a.get(2).filter(|s| *s != "-") { let m = Msd::parse(data.clone()).unwrap(); let at = &m.attach_files()[idx.parse::<usize>().unwrap()]; data = data[at.offset as usize..(at.offset + at.size) as usize].to_vec(); }
    let want: Option<u16> = a.get(3).and_then(|s| s.parse().ok());
    let nrec: usize = a.get(4).and_then(|s| s.parse().ok()).unwrap_or(6);
    let m = Msd::parse(data.clone()).unwrap();
    for c in &m.chunks {
        if let Some(w) = want { if c.raw_type != w { continue; } }
        println!("chunk type {} ptrs {} stride {:#x} count {}", c.raw_type, c.ptr_count, c.stride, c.count);
        for i in 0..c.count.min(nrec) {
            let o = c.record_offset(i);
            let rec = &data[o..o + c.stride];
            let mut s = String::new();
            for k in 0..c.ptr_count as usize { let p = u32_at(rec, k * 4) as usize; s += &format!(" p{k}='{}'", sjis::decode(cstr(&data, c.offset + p))); }
            println!("  [{i}]{s} raw {:02x?}", &rec[c.ptr_count as usize * 4..]);
        }
    }
}
