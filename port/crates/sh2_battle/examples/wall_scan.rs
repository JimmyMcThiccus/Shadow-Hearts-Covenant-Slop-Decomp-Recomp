//! Developer tool: which monsters (and monster sets) hit with the knock-down classes that slam the target into a wall / through bystanders
//! (PATK2 row `+3` = 4 -> `BtlChrSequence` state 0x1c, 6 -> 0x1e; see notes/integration/wall_involve.md).  `SH2_US_DISC_DIR` must be set.
use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};

fn main() {
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let dir = std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let d = PkbDisc::open(&dir).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    // monster -> classes of its attack rows
    let mut by_mon = std::collections::BTreeMap::<usize, Vec<(u8, u16, u16)>>::new();
    for m in 0..600usize {
        let Some(mp) = data.monster(m) else { continue };
        let Some(r) = data.dat.record(23, mp.attack_table as usize, 0x18) else { continue };
        let base = u16::from_le_bytes([r[0xc], r[0xd]]) as usize;
        let rows: Vec<(u8, u16, u16)> = (0..r[1].max(1) as usize)
            .filter_map(|g| data.dat.record(24, base + g, 0x48).map(|x| (x[3], u16::from_le_bytes([x[0x44], x[0x45]]), u16::from_le_bytes([x[0x46], x[0x47]]))))
            .collect();
        if rows.iter().any(|r| matches!(r.0, 4 | 6)) {
            println!("monster {m} (chr {}, size class {}): attack rows (class, push time, power) {:?}", mp.chr_model, (mp.size_class >> 3) & 7, rows);
            by_mon.insert(m, rows);
        }
    }
    for s in 0..400usize {
        let Some(ms) = data.monster_set(s) else { break };
        let mons: Vec<usize> = ms.monsters.iter().filter(|&&m| m != 0xffff).map(|&m| m as usize).take(ms.monster_count()).collect();
        let hits: Vec<usize> = mons.iter().copied().filter(|m| by_mon.contains_key(m)).collect();
        if !hits.is_empty() {
            println!("set {s}: monsters {mons:?} (slammers {hits:?})");
        }
    }
}
