use sh2_audio::Bank;
use sh2_core::fileio::Disc;
fn main() {
    let disc = Disc::from_env().unwrap();
    let (mut n, mut lfo_p, mut lfo_a, mut tw, mut prio) = (0, 0, 0, std::collections::BTreeMap::<u8, usize>::new(), std::collections::BTreeMap::<(u8, u8, u8), usize>::new());
    let mut rev = std::collections::BTreeMap::<u8, usize>::new();
    for (_c, files) in disc.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if !(up.ends_with(".SSE") || up.ends_with(".SSQ")) { continue; }
            let Ok(bank) = Bank::parse_opts(&disc.read(&path).unwrap(), false) else { continue };
            for t in &bank.timbres { for g in &t.groups { for tt in &g.tones {
                n += 1;
                let r = &tt.raw;
                if r.get(3).copied().unwrap_or(0) & 0xf != 0 { lfo_p += 1; }
                if r.get(3).copied().unwrap_or(0) >> 4 != 0 { lfo_a += 1; }
                *tw.entry(r.get(0x2b).copied().unwrap_or(0)).or_default() += 1;
                *prio.entry((r.get(8).copied().unwrap_or(0), r.get(9).copied().unwrap_or(0), r.get(10).copied().unwrap_or(0))).or_default() += 1;
                *rev.entry(r.get(0xb).copied().unwrap_or(0)).or_default() += 1;
            }}}
        }
    }
    println!("FT tones {n}: pitch LFO {lfo_p} amp LFO {lfo_a}; [0x2b] {tw:?}\n prio/group/max {prio:?}\n [0xb] {rev:?}");
}
