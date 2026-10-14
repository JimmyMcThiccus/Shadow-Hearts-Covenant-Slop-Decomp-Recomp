//! Developer tool (B1): monsters by death type (`MONSTERParam+0x15 >> 3 & 3`) and the monster sets that contain them.
use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};
fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let mut ty = std::collections::BTreeMap::new();
    for id in 0..400usize {
        if let Some(r) = data.dat.record(sh2_battle::data::SEC_MONSTER, id, 0x38) {
            let m = sh2_battle::data::MonsterParam::parse(r);
            if m.hp == 0 { continue; }
            ty.insert(id, (sh2_battle::choreo::death_type(r[0x15]), m.chr_model, i16::from_le_bytes([r[0x2e], r[0x2f]])));
        }
    }
    for t in 0..4 { println!("type {t}: {:?}", ty.iter().filter(|(_, v)| v.0 == t).map(|(k, v)| (*k, v.1, v.2)).take(40).collect::<Vec<_>>()); }
    for s in 0..130usize {
        if let Some(ms) = data.monster_set(s) {
            let tys: Vec<u8> = ms.monsters.iter().filter(|&&m| m != 0xffff).filter_map(|&m| ty.get(&(m as usize)).map(|v| v.0)).collect();
            if tys.iter().any(|&t| t > 0) { println!("set {s}: {:?} types {:?}", ms.monsters, tys); }
        }
    }
}
