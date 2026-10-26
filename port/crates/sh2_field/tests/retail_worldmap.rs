//! Retail (US) world map decoder against the real disc (`SH2_US_DISC_DIR`; skipped when unset).
use sh2_field::pkb_compat::PkbSet;
use sh2_field::worldmap::{bundle_entry, parse_msg_table, point_state, RetailWorldTable, WmResult, WmState, WorldMap};
use sh2_core::game::padbit;

fn disc() -> Option<std::path::PathBuf> {
    std::env::var_os("SH2_US_DISC_DIR").map(Into::into)
}

fn table() -> Option<RetailWorldTable> {
    RetailWorldTable::from_field_bin(&sh2_core::fileio::read_disc_file(disc()?, "FIELD.BIN").ok()?)
}

#[test]
fn point_and_world_tables() {
    let Some(t) = table() else { return };
    assert_eq!((t.points.len(), t.worlds.len()), (47, 5));
    assert_eq!(t.points[0].map, "");
    let p = |i: usize| (t.points[i].map.as_str(), t.points[i].x, t.points[i].y);
    assert_eq!(p(1), ("AP_00_U", 391, 518)); // Apoina Tower, the first point of a new game
    assert_eq!(p(2), ("DO_04_U", 328, 367)); // Domremy
    assert_eq!(p(3), ("AR_15_U", 323, 325)); // Ardennes Forest
    assert_eq!(t.points[8].entry & 0xff, 2);
    assert_eq!(t.points.iter().filter(|p| !p.map.is_empty()).count(), 42);
    // world 0 = Europe: BGM601, ids 1..4 first, a portal to world 2 (Paris) on point 4, links to Japan (world 1) on L1/R1
    let eu = &t.worlds[0];
    assert_eq!(eu.bgm, "BGM601.SSQ");
    assert_eq!(eu.list.iter().take(4).map(|e| e.id).collect::<Vec<_>>(), vec![1, 2, 3, 4]);
    assert_eq!(eu.list[3].portal, 2);
    assert_eq!(eu.links.shoulder, 1);
    assert_eq!((eu.mask, eu.max_scroll_x, eu.max_scroll_y), (8, 256, 224));
    // Paris: ids 5..8, cross returns to Europe (world 0) with point 4 selected, entered at point 7
    let paris = &t.worlds[2];
    assert_eq!(paris.list.iter().map(|e| e.id).collect::<Vec<_>>(), vec![5, 6, 7, 8]);
    assert_eq!((paris.links.back, paris.links.back_point, paris.links.enter_point), (0, 4, 7));
    assert_eq!(paris.max_scroll_x, 152);
    // every listed id has a point record
    for w in &t.worlds {
        for e in &w.list {
            assert!(e.portal >= 0 || !t.points[e.id as usize].map.is_empty(), "id {}", e.id);
        }
    }
}

#[test]
fn wmap_bundles_carry_names_and_ui_text() {
    let (Some(d), Some(t)) = (disc(), table()) else { return };
    let set = PkbSet::open(&d).unwrap();
    let b = set.read("WORLDMAP/WMAP0.DAT").unwrap();
    let names = parse_msg_table(bundle_entry(&b, 11).unwrap());
    assert_eq!(names.len(), 90);
    assert_eq!(names[0], b"Graveyard");
    assert_eq!(names[2], b"Apoina Tower"); // point id 1 -> string 2
    assert_eq!(names[4], b"Domremy");
    let ui = parse_msg_table(bundle_entry(&b, 10).unwrap());
    assert_eq!(ui.len(), 9);
    assert_eq!(ui[2], b": Confirm");
    assert_eq!(ui[3], b": Menu");
    // a fresh save (WM bytes: point 1 open) gives a one point list with the real name and position
    let open = |id: usize| if id == 1 { 2u8 } else { 0 };
    let tab = t.world_table(0, &open, &names, &ui).unwrap();
    assert_eq!(tab.maps.len(), 1);
    assert_eq!(tab.maps[0].map, "AP_00_U");
    assert_eq!(tab.maps[0].name, b"Apoina Tower");
    assert_eq!(tab.maps[0].entry, 0);
    assert_eq!(tab.maps[0].state, 1);
    // point 2 greyed, point 3 newly unlocked
    let st = |id: usize| match id {
        1 => 2u8,
        2 => 1,
        3 => 4,
        _ => 0,
    };
    let tab = t.world_table(0, &st, &names, &ui).unwrap();
    assert_eq!(tab.maps.iter().map(|m| (m.id, m.state)).collect::<Vec<_>>(), vec![(1, 1), (2, 3), (3, 2)]);
    // thumbnails exist for the listed entries (12 + thumb index)
    let n = u32::from_le_bytes(b[0..4].try_into().unwrap()) as usize;
    assert!(n >= 12 + 22);
}

#[test]
fn state_byte_semantics() {
    assert_eq!(point_state(0), 0);
    assert_eq!(point_state(2), 1);
    assert_eq!(point_state(1), 3);
    assert_eq!(point_state(4 | 2), 2);
}

#[test]
fn retail_navigation_portal_and_links() {
    let (Some(d), Some(t)) = (disc(), table()) else { return };
    let set = PkbSet::open(&d).unwrap();
    let b = set.read("WORLDMAP/WMAP0.DAT").unwrap();
    let names = parse_msg_table(bundle_entry(&b, 11).unwrap());
    let ui = parse_msg_table(bundle_entry(&b, 10).unwrap());
    let all = |_id: usize| 2u8;
    let tab = t.world_table(0, &all, &names, &ui).unwrap();
    let mut wm = WorldMap::new(&tab, 0, 4);
    wm.extra = 8;
    wm.set_ready();
    for _ in 0..40 {
        wm.tick(0);
    }
    assert_eq!(wm.state, WmState::Select);
    // circle on point 4 (Paris) opens world 2
    wm.tick(padbit::CIRCLE);
    for _ in 0..40 {
        wm.tick(0);
    }
    assert_eq!(wm.result, Some(WmResult::World { world: 2, point: None }));
    // L1 on the Europe map goes to Japan
    let mut wm = WorldMap::new(&tab, 0, 1);
    wm.extra = 8;
    wm.set_ready();
    for _ in 0..40 {
        wm.tick(0);
    }
    wm.tick(padbit::L1);
    assert!(matches!(wm.result, Some(WmResult::World { world: 1, .. })));
    // without the extra bit the links are dead
    let mut wm = WorldMap::new(&tab, 0, 1);
    wm.extra = 1;
    wm.set_ready();
    for _ in 0..40 {
        wm.tick(0);
    }
    wm.tick(padbit::L1);
    assert_eq!(wm.result, None);
    // confirming a normal point enters the map with the record's entry
    let mut wm = WorldMap::new(&tab, 0, 2);
    wm.set_ready();
    for _ in 0..40 {
        wm.tick(0);
    }
    wm.tick(padbit::CIRCLE);
    assert!(matches!(&wm.result, Some(WmResult::Enter { map, id: 2, .. }) if map == "DO_04_U"));
}
