//! Dump retail text kinds used by the battle menu (`GetRegDat(0x2a, n)` ...).
use sh2_battle::pkb_compat::PkbDisc;
use sh2_core::regdat::UsRegDat;
fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let mes = d.read("COMMON/SSHMES.NA").unwrap();
    let dat = d.read("COMMON/SSHDAT.NA").unwrap();
    let r = UsRegDat::new(&mes, &dat).unwrap();
    let kind: u8 = std::env::args().nth(1).map(|s| u8::from_str_radix(s.trim_start_matches("0x"), 16).unwrap()).unwrap_or(0x2a);
    let n: usize = std::env::args().nth(2).map(|s| s.parse().unwrap()).unwrap_or(48);
    for i in 0..n {
        println!("{kind:#x}[{i}] = {:?}", r.text(kind, i, -1));
    }
}
