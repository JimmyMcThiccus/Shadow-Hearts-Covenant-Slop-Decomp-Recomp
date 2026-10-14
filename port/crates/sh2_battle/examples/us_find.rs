//! Find a string in the retail sshmes.na and print its table index and offset.
use sh2_battle::pkb_compat::PkbDisc;
fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let mes = d.read("COMMON/SSHMES.NA").unwrap();
    let needle = std::env::args().nth(1).unwrap();
    let n = u32::from_le_bytes(mes[0..4].try_into().unwrap()) as usize;
    let offs: Vec<usize> = (0..n).map(|i| u32::from_le_bytes(mes[8 + i * 8 + 4..8 + i * 8 + 8].try_into().unwrap()) as usize).collect();
    let nb = needle.as_bytes();
    for (p, w) in mes.windows(nb.len()).enumerate() {
        if w == nb {
            let t = offs.iter().rposition(|&o| o <= p).unwrap();
            println!("table {t} (+{:#x}) @ {p:#x}: {}", p - offs[t], String::from_utf8_lossy(&mes[p..(p + 70).min(mes.len())]).split('\0').next().unwrap());
        }
    }
}
