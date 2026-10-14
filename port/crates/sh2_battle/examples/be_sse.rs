//! Round 5 BE: SE bank ids / maps of battle banks (`be_sse 005M 418M ...`).
fn main() {
    let d = sh2_battle::pkb_compat::PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    for n in std::env::args().skip(1) {
        let p = format!("BTLDATA/SOUND/SE/{n}.SSE");
        let Ok(b) = d.read(&p) else { println!("{p}: missing"); continue };
        let off = b.windows(4).position(|w| w == b"SDRH").unwrap_or(0);
        match sh2_audio::sdh::Bank::parse_opts(&b[off..], false) {
            Ok(bk) => println!("{p}: bank id {:#x}, se_map {:?}", bk.bank_id, &bk.se_map[..bk.se_map.len().min(16)]),
            Err(e) => println!("{p}: {e}"),
        }
    }
}
