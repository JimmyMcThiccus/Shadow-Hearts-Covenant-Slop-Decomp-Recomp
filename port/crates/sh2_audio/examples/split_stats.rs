use sh2_audio::sdh::Bank;
use sh2_core::fileio::Disc;
use std::collections::BTreeMap;
fn main() {
    let disc = Disc::from_env().unwrap();
    let mut bend: BTreeMap<(u16, u16), usize> = BTreeMap::new();
    let mut adsr: BTreeMap<(u16, u16), usize> = BTreeMap::new();
    let mut kf: BTreeMap<Vec<u8>, usize> = BTreeMap::new();
    for (_c, files) in disc.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if !(up.ends_with(".SSQ") || up.ends_with(".SSE")) {
                continue;
            }
            let d = disc.read(&path).unwrap();
            let Ok(b) = Bank::parse_opts(&d, false) else { println!("not SDRH: {path} {:02x?}", &d[..8]); continue };
            for p in &b.programs {
                for s in &p.splits {
                    *bend.entry((s.bend_down, s.bend_up)).or_default() += 1;
                }
            }
            for t in &b.tones {
                *adsr.entry((t.adsr1(), t.adsr2())).or_default() += 1;
                *kf.entry(t.raw[16..25].to_vec()).or_default() += 1;
            }
        }
    }
    println!("bend ranges (down, up) -> count: {:?}", bend);
    let mut a: Vec<_> = adsr.into_iter().collect();
    a.sort_by_key(|x| std::cmp::Reverse(x.1));
    println!("top adsr: {:x?}", &a[..a.len().min(12)]);
    let mut k: Vec<_> = kf.into_iter().collect();
    k.sort_by_key(|x| std::cmp::Reverse(x.1));
    println!("top key-follow bytes 16..25: {:x?}", &k[..k.len().min(6)]);
}
