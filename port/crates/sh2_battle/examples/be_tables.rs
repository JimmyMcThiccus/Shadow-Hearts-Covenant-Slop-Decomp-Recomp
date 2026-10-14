//! Round 5 BE: dump the retail battle tables (`MONSET` raw rows, `BTL_` files 34 / 35, `PIT_` file 36, monsters).
//! `cargo run -p sh2_battle --example be_tables -- [monset|btl|pit|mon] `
use sh2_battle::{data::BattleData, pkb_compat::PkbDisc};
use sh2_core::regdat::RegFile;

fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let raw = d.read("COMMON/SSHDAT.NA").unwrap();
    let rf = RegFile::new(&raw);
    let what = std::env::args().nth(1).unwrap_or_else(|| "all".into());
    let tab = |i: usize| -> &[u8] {
        let o = rf.entry(i);
        &raw[o..o + rf.size(i)]
    };
    let hex = |b: &[u8]| b.iter().map(|x| format!("{x:02x}")).collect::<Vec<_>>().join(" ");
    let mname = |id: u16| if id == 0xffff { "-".to_string() } else { data.name(8, id as usize) };
    if what == "all" || what == "monset" {
        let t = tab(6);
        for (i, r) in t.chunks_exact(0x14).enumerate() {
            let w = |o: usize| u16::from_le_bytes([r[o], r[o + 1]]);
            let mons: Vec<String> = (0..6).map(|k| w(4 + k * 2)).filter(|&m| m != 0xffff).map(|m| format!("{m}:{}", mname(m))).collect();
            println!("MONSET {i:3} id {:4} form {:#x} flags {:08x} [{}]", w(0), w(2), u32::from_le_bytes(r[16..20].try_into().unwrap()), mons.join(", "));
        }
    }
    if what == "all" || what == "btl" {
        for f in [34usize, 35] {
            let t = tab(f);
            let st = if f == 34 { 8 } else { 0x24 };
            println!("file {f} tag {:?} size {:#x}", String::from_utf8_lossy(&rf.tag(f)), t.len());
            for (i, r) in t.chunks_exact(st).enumerate() {
                println!("  {f}/{i:3}: {}", hex(r));
            }
        }
    }
    if what == "all" || what == "pit" {
        let t = tab(36);
        println!("PIT_ size {:#x}", t.len());
        for (i, r) in t.chunks_exact(0x3c).enumerate() {
            println!("  pit {i:2}: {}", hex(r));
        }
    }
    if what == "all" || what == "mon" {
        let t = tab(5);
        for (i, r) in t.chunks_exact(0x38).enumerate() {
            let m = sh2_battle::data::MonsterParam::parse(r);
            let ai = i32::from_le_bytes(r[0x20..0x24].try_into().unwrap());
            println!("MON {i:3} chr {:3} hp {:5} ai {:6} flags14 {:02x} sz {:02x} sk {} {} exp {} cash {} sp {} {}  {}", m.chr_model, m.hp, ai, r[0x14], r[0x15], i16::from_le_bytes([r[0x16], r[0x17]]), i16::from_le_bytes([r[0x18], r[0x19]]), m.exp, m.cash, m.sp_reward, mname(i as u16), hex(r));
        }
    }
}
