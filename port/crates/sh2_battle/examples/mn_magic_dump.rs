//! (round 5 MN) retail `MAGI` / `MC_P` rows as the menu sees them: `mn_magic_dump [first] [count]`.  `SH2_US_DISC_DIR` must be set.
use sh2_battle::{actions::ActionTables, data::BattleData, pkb_compat::PkbDisc};
fn main() {
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let t = ActionTables::load(&data);
    let a: Vec<usize> = std::env::args().skip(1).filter_map(|s| s.parse().ok()).collect();
    let (f, n) = (a.first().copied().unwrap_or(0), a.get(1).copied().unwrap_or(40));
    for (i, m) in t.magic.iter().enumerate().skip(f).take(n) {
        println!("magic {i:3} {:20} flags {:#06x} use {} mp {} eff {:#x}", t.magic_name(i), m.flags, (m.flags & 0x1f) >> 3, m.mp, m.effect_id);
    }
    if std::env::args().any(|x| x == "--kinds") {
        let u = data.us().unwrap();
        for k in 0..0x48u8 {
            println!("kind {k:#x}: {:?} | {:?} | {:?}", u.text(k, 0, -1), u.text(k, 1, -1), u.text(k, 0, 0));
        }
        return;
    }
    let sec = data.dat.section(20);
    for (i, c) in t.crests.iter().enumerate() {
        let raw = sec.get(i * 0x1c..i * 0x1c + 0x1c).unwrap_or(&[]);
        println!("crest {i:2} {:14} flags {:#04x} magic {:?} raw {}", data.us().and_then(|u| u.text(0x10, i, -1)).unwrap_or_default(), c.flags, c.magic, hex(raw));
    }
}

#[allow(dead_code)]
fn hex(b: &[u8]) -> String {
    b.iter().map(|x| format!("{x:02x}")).collect::<Vec<_>>().join(" ")
}
