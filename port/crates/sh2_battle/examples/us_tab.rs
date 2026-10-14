//! Print the strings of one retail sshmes.na table (offset-indexed {u32 off} header when `desc`).
use sh2_battle::pkb_compat::PkbDisc;
fn main() {
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let mes = d.read("COMMON/SSHMES.NA").unwrap();
    let t: usize = std::env::args().nth(1).unwrap().parse().unwrap();
    let max: usize = std::env::args().nth(2).map(|s| s.parse().unwrap()).unwrap_or(40);
    let o = u32::from_le_bytes(mes[8 + t * 8 + 4..8 + t * 8 + 8].try_into().unwrap()) as usize;
    let end = if t + 1 < 47 { u32::from_le_bytes(mes[8 + (t + 1) * 8 + 4..8 + (t + 1) * 8 + 8].try_into().unwrap()) as usize } else { mes.len() };
    println!("table {t} at {o:#x} len {:#x}", end - o);
    let first = u32::from_le_bytes(mes[o..o + 4].try_into().unwrap()) as usize;
    for i in 0..(first / 4).min(max) {
        let so = u32::from_le_bytes(mes[o + i * 4..o + i * 4 + 4].try_into().unwrap()) as usize;
        let s = &mes[o + so..end.min(o + so + 100)];
        println!("[{i}] {}", String::from_utf8_lossy(s).split('\0').next().unwrap().replace('\n', "\\n"));
    }
}
