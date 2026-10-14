//! **Continue loads a save made by the real game.**  A memory-card image holding the real retail `BASLUS-21041-SH2/SH2-000` (fixtures, copied from the
//! user's emulator card) is the read-only fallback of the port's save directory; the loaded session is the card's game.  Own test binary because
//! it switches the process-wide active region to the US retail build.

use sh2_core::boot::{set_active_region, Region};
use sh2_menu::memcard::{synth_card, MemCard, MemCardStorage};
use sh2_menu::save::Build;
use sh2_menu::session::{load_session, slot_used, FileStorage, GameSession};

#[test]
fn continue_loads_a_real_card_save() {
    set_active_region(Region::Us);
    let sys = include_bytes!("fixtures/us_card_system");
    let save = include_bytes!("fixtures/us_card_SH2-000");
    let img = synth_card("BASLUS-21041-SH2", &[("BASLUS-21041-SH2", sys), ("SH2-000", save)], true);
    let card = MemCardStorage::from_card(MemCard::from_bytes(img).unwrap(), "BASLUS-21041-SH2").expect("folder on card");
    let dir = std::env::temp_dir().join(format!("sh2_card_continue_{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    let mut dev = FileStorage::new(&dir).with_card(card);
    let mut s = GameSession::default();
    assert!(slot_used(&mut dev, 0), "slot 0 is listed by the card's system file");
    load_session(&mut dev, &mut s, 0).unwrap();
    assert_eq!(s.save.build, Build::Retail);
    assert_eq!(s.map, "AP_02_U");
    assert!(s.cash() > 0);
    assert!(!s.battle_party().is_empty());
    let _ = std::fs::remove_dir_all(&dir);
}

/// **Saving writes a real PS2 memory-card image**: the port card gets the real folder layout (`BASLUS-21041-SH2` with the system file, `icon.sys`, the slot
/// files), valid ECC on every programmed page, the slots of the emulator card are inherited by the first save, and the emulator card itself is never modified.
#[test]
fn saves_go_to_a_port_card_image_that_inherits_the_real_slots() {
    set_active_region(Region::Us);
    let sys = include_bytes!("fixtures/us_card_system");
    let save = include_bytes!("fixtures/us_card_SH2-000");
    let img = synth_card("BASLUS-21041-SH2", &[("BASLUS-21041-SH2", sys), ("SH2-000", save)], true);
    let emu = MemCardStorage::from_card(MemCard::from_bytes(img.clone()).unwrap(), "BASLUS-21041-SH2").unwrap();
    let dir = std::env::temp_dir().join(format!("sh2_port_card_{}", std::process::id()));
    let _ = std::fs::remove_dir_all(&dir);
    let card_path = dir.join("mcd_sh2_port.ps2");
    let mut dev = FileStorage::new(&dir).with_card(emu).with_port_card(MemCardStorage::open_or_new(&card_path, "BASLUS-21041-SH2"));
    assert!(!card_path.exists(), "the port card is only created by the first write");
    let mut s = GameSession::default();
    load_session(&mut dev, &mut s, 0).unwrap();
    s.add_cash(777);
    sh2_menu::session::save_session(&mut dev, &mut s, 3).unwrap();
    assert!(card_path.exists());

    // a fresh device on the same image: both the inherited slot 0 and the new slot 3 are listed and load
    let pc = MemCard::open(&card_path).expect("the port card is a valid card image");
    assert_eq!(pc.ecc_errors().1, 0, "valid ECC on every programmed page");
    let names: Vec<String> = pc.list_dir("BASLUS-21041-SH2").unwrap().into_iter().map(|e| e.name).collect();
    for n in ["BASLUS-21041-SH2", "SH2-000", "SH2-003", "icon.sys"] {
        assert!(names.iter().any(|x| x == n), "{n} in {names:?}");
    }
    let mut dev2 = FileStorage::new(&dir).with_port_card(MemCardStorage::open_or_new(&card_path, "BASLUS-21041-SH2"));
    assert!(slot_used(&mut dev2, 0) && slot_used(&mut dev2, 3) && !slot_used(&mut dev2, 1));
    let mut a = GameSession::default();
    load_session(&mut dev2, &mut a, 3).unwrap();
    assert_eq!(a.cash(), s.cash());
    let mut b = GameSession::default();
    load_session(&mut dev2, &mut b, 0).unwrap();
    assert_eq!(b.cash() + 777, s.cash(), "slot 0 is still the real save");
    // saving over slot 3 again replaces it in place
    s.add_cash(1);
    sh2_menu::session::save_session(&mut dev2, &mut s, 3).unwrap();
    let mut c = GameSession::default();
    load_session(&mut dev2, &mut c, 3).unwrap();
    assert_eq!(c.cash(), s.cash());
    assert_eq!(MemCard::open(&card_path).unwrap().ecc_errors().1, 0);
    let _ = std::fs::remove_dir_all(&dir);
}
