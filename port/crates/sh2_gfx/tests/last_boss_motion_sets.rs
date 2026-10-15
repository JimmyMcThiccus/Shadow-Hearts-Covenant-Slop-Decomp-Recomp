//! BE request 12 / BT round 6: the last boss's motion files carry alternate motion sets tagged `a2` / `a3` next to `anm`.
use sh2_formats::{motion::Motion, pkb};

#[test]
fn us_last_boss_alternate_motion_sets_parse() {
    let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
    let Ok(disc) = sh2_core::fileio::Disc::open(&dir) else { return };
    for chr in 499..=502 {
        let path = format!("BTLDATA/CHRANM/{chr:03}.ANM");
        let b = disc.read(&path).expect("anm file");
        let p = pkb::parse_package(&b, 0).unwrap_or_else(|| panic!("{path}: not a package"));
        let mut total = 0;
        for set in [0u8, 2, 3] {
            let names: Vec<String> = p.motions(set).map(|e| Motion::parse(&b[e.offset..]).unwrap_or_else(|er| panic!("{path} set {set}: {er}")).name).collect();
            eprintln!("{path} set {set}: {names:?}");
            total += names.len();
        }
        assert_eq!(total, p.entries.iter().filter(|e| e.is_motion()).count());
        assert!(p.motions(2).count() + p.motions(3).count() > 0, "{path}: no a2 / a3 set");
    }
}
