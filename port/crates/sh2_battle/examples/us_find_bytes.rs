//! Find a byte pattern (hex) in a retail file and print the table (container section) and offset: `us_find_bytes COMMON/SSHDAT.NA a900 5a00`
use sh2_battle::pkb_compat::PkbDisc;
fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let a: Vec<String> = std::env::args().skip(1).collect();
    let f = d.read(&a[0]).unwrap();
    let hex: String = a[1..].join("");
    let nb: Vec<u8> = (0..hex.len() / 2).map(|i| u8::from_str_radix(&hex[2 * i..2 * i + 2], 16).unwrap()).collect();
    let n = u32::from_le_bytes(f[0..4].try_into().unwrap()) as usize;
    let offs: Vec<usize> = (0..n).map(|i| u32::from_le_bytes(f[8 + i * 8 + 4..8 + i * 8 + 8].try_into().unwrap()) as usize).collect();
    for (p, w) in f.windows(nb.len()).enumerate() {
        if w == &nb[..] {
            let t = offs.iter().rposition(|&o| o <= p).unwrap_or(0);
            println!("table {t} (+{:#x}) @ {p:#x}", p.saturating_sub(offs[t]));
        }
    }
}
