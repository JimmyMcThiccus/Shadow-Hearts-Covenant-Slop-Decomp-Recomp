//! Dump a table of a retail container as u16 rows: `us_tab_dump COMMON/SSHDAT.NA table first_row nrows row_bytes`
use sh2_battle::pkb_compat::PkbDisc;
fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let a: Vec<String> = std::env::args().skip(1).collect();
    let f = d.read(&a[0]).unwrap();
    let t: usize = a[1].parse().unwrap();
    let first: usize = a[2].parse().unwrap();
    let n: usize = a[3].parse().unwrap();
    let rb: usize = a[4].parse().unwrap();
    let base = u32::from_le_bytes(f[8 + t * 8 + 4..8 + t * 8 + 8].try_into().unwrap()) as usize;
    let len = u32::from_le_bytes(f[8 + t * 8..8 + t * 8 + 4].try_into().unwrap()) as usize;
    println!("table {t} base {base:#x} len {len:#x}");
    for r in first..first + n {
        let o = base + r * rb;
        let w: Vec<u16> = (0..rb / 2).map(|i| u16::from_le_bytes([f[o + 2 * i], f[o + 2 * i + 1]])).collect();
        println!("row {r:3}: {w:?}");
    }
}
