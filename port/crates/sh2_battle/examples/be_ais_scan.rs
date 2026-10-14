//! Round 5 BE: static scan of every retail AIS script referenced by `MONSTERParam+0x20`: statement kinds, `AIIfFunc` condition numbers,
//! `AIGetValue` functions and `GetTarget` criteria actually used, plus scripts that are missing on the disc.
//! `cargo run -p sh2_battle --example be_ais_scan [-- --dump M012_003]`
use std::collections::BTreeMap;

use sh2_battle::pkb_compat::PkbDisc;
use sh2_core::regdat::RegFile;

fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let raw = d.read("COMMON/SSHDAT.NA").unwrap();
    let rf = RegFile::new(&raw);
    let o = rf.entry(5);
    let mons = &raw[o..o + rf.size(5)];
    let args: Vec<String> = std::env::args().collect();
    let mut users: BTreeMap<i32, Vec<usize>> = BTreeMap::new();
    for (i, r) in mons.chunks_exact(0x38).enumerate() {
        let ai = i32::from_le_bytes(r[0x20..0x24].try_into().unwrap());
        users.entry(ai).or_default().push(i);
    }
    let mut conds: BTreeMap<i16, usize> = BTreeMap::new();
    let mut acts: BTreeMap<i16, usize> = BTreeMap::new();
    let mut gv: BTreeMap<i16, usize> = BTreeMap::new();
    let mut crit: BTreeMap<i16, usize> = BTreeMap::new();
    let mut unknown: BTreeMap<i16, usize> = BTreeMap::new();
    let mut missing = vec![];
    let mut files = 0;
    for (&ai, who) in &users {
        let path = sh2_battle::ai::ais_path(ai, false);
        let Ok(b) = d.read(&path) else {
            missing.push((ai, who.clone()));
            continue;
        };
        files += 1;
        let t: Vec<i16> = b.chunks_exact(2).map(|c| i16::from_le_bytes([c[0], c[1]])).collect();
        let dump = args.iter().any(|a| path.contains(a.as_str()) && a != &args[0]);
        let mut p = 2usize;
        let op = |p: &mut usize| -> (i16, i16) {
            let k = t.get(*p).copied().unwrap_or(0);
            if k == 0x15 {
                let v = t.get(*p + 1).copied().unwrap_or(0);
                *p += 2;
                (k, v)
            } else {
                *p += 1;
                (k, 0)
            }
        };
        while p < t.len() {
            let k = t[p];
            let start = p;
            match k {
                0x02 | 0x2c | 0x05 | 0x07 | 0x09 => p += 2,
                0x06 | 0x08 | 0x2e | 0x01 | 0x03 | 0x00 => p += 1,
                0x04 => {
                    p += 1;
                    let (kt, kv) = op(&mut p);
                    op(&mut p);
                    op(&mut p);
                    *conds.entry(if kt == 0x15 { kv } else { -kt }).or_default() += 1;
                }
                0x0a => {
                    p += 3;
                    while p < t.len() && t[p] != 0x0b {
                        if t[p] == 0x2d {
                            p += 1;
                            let (ft, fv) = op(&mut p);
                            op(&mut p);
                            op(&mut p);
                            *gv.entry(if ft == 0x15 { fv } else { -ft }).or_default() += 1;
                        } else if t[p] == 0x15 {
                            p += 2;
                        } else {
                            p += 1;
                        }
                    }
                    p += 1;
                }
                0x23..=0x27 => {
                    p += 1;
                    let mut o5 = [(0i16, 0i16); 5];
                    for x in o5.iter_mut() {
                        *x = op(&mut p);
                    }
                    *acts.entry(k).or_default() += 1;
                    if k != 0x27 {
                        let c = o5[2];
                        *crit.entry(if c.0 == 0x15 { c.1 } else { -c.0 }).or_default() += 1;
                    }
                }
                0x28 | 0x29 => {
                    p += 1;
                    op(&mut p);
                    op(&mut p);
                    *acts.entry(k).or_default() += 1;
                }
                0x2a => {
                    p += 1;
                    op(&mut p);
                    *acts.entry(k).or_default() += 1;
                }
                _ => {
                    *unknown.entry(k).or_default() += 1;
                    p += 1;
                }
            }
            if dump {
                println!("  {:#06x}: {:x?}", start * 2, &t[start..p.min(t.len())]);
            }
        }
    }
    println!("{files} scripts, {} referenced ids", users.len());
    println!("missing: {:?}", missing);
    println!("IF conditions (negative = variable token): {conds:x?}");
    println!("actions: {acts:x?}");
    println!("AIGetValue fns: {gv:x?}");
    println!("GetTarget criteria: {crit:?}");
    println!("unknown tokens: {unknown:x?}");
}
