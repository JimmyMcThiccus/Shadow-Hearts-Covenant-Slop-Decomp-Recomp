//! Round 5 BE: retail `SKIL` header (group offsets / counts) and a few monster skill records (groups 0x18 / 0x19).
use sh2_battle::pkb_compat::PkbDisc;
use sh2_core::regdat::RegFile;
fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let raw = d.read("COMMON/SSHDAT.NA").unwrap();
    let rf = RegFile::new(&raw);
    let o = rf.entry(13);
    let s = &raw[o..o + rf.size(13)];
    let u32at = |o: usize| u32::from_le_bytes(s[o..o + 4].try_into().unwrap());
    let first = 26 * 8;
    println!("SKIL size {:#x}, header words {}", s.len(), first / 4);
    for g in 0..first / 8 {
        println!("group {g:#x}: off {:#x} count {}", u32at(g * 8), u32at(g * 8 + 4));
    }
    let (off19, n19) = (u32at(0x19 * 8) as usize, u32at(0x19 * 8 + 4) as usize);
    let want: Vec<usize> = std::env::args().skip(1).filter_map(|a| a.parse().ok()).collect();
    let list = if want.is_empty() { vec![0usize, 1, 5, 6, 7, 9, 19, 20] } else { want };
    let data = sh2_battle::data::BattleData::load_us(&d).unwrap();
    let t = sh2_battle::actions::ActionTables::load(&data);
    for &i in &list {
        if let Some(r) = t.mon_skills.get(i) {
            println!("decoded {i}: {:?} name {:?}", r, t.skill_name(r.name_idx.max(0) as usize));
            println!("   recs {:?}", sh2_battle::actions::decode_effect_words(&r.words, 50, 100, false));
        }
    }
    for i in list {
        if i < n19 {
            let r = &s[off19 + i * 0x20..off19 + i * 0x20 + 0x20];
            println!("monskill {i}: {}", r.iter().map(|b| format!("{b:02x}")).collect::<Vec<_>>().join(" "));
        }
    }
}
// (appended) `be_skil -- <ids>`: dump monster skill records
#[allow(dead_code)]
fn _unused() {}
