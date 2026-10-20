//! Developer tool: `attr_weapons` lists the retail `WPN_` records per character (record id, model number `+4`, equip mask `+6`) with the dev drive poke that equips them
//! (`SH2_BATTLE_SAVE=<hex off>:<id>`: the weapon byte of PC `n` is at `0x2a9 + (n - 3) * 0xc0`), to find weapons for the elemental glow checks (notes/integration/attribute_glow.md).
use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};

fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let n = data.dat.count(sh2_battle::data::SEC_WEAPON, 0x34);
    for pc in 0..14usize {
        let mut v = vec![];
        for i in 0..n {
            let r = data.dat.record(sh2_battle::data::SEC_WEAPON, i, 0x34).unwrap();
            let mask = u16::from_le_bytes([r[6], r[7]]);
            let model = i16::from_le_bytes([r[4], r[5]]);
            if mask & (1 << pc) != 0 && model >= 0 {
                v.push(format!("{i:#x}:m{model}"));
            }
        }
        let off = 0x2a9 + (pc as i64 - 3) * 0xc0;
        println!("PC {pc:2} weapon byte {off:#x}: {}", v.join(" "));
    }
}
