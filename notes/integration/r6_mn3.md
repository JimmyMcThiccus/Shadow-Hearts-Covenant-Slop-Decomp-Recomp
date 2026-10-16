# Round 6 MN3: menus and meta screens (2026-10-16)

## Status

| task | state | notes |
|---|---|---|
| 1. combo switch bit | **fixed** (both sides) | see "Combo switch" below: bit 0 = the battle's `Combo` command, bit 1 = the shortcut switch, copied from `MENU+0x276` at each battle start |
| 2. shortcut setting overlay (mode 0x18) | **done** | `sh2_battle/src/shortcut.rs` (`setting_row`, `SettingMenu`, `write_row`, `draw_setting`) + `plugin.rs` `run_shortcut_setting` hook; shots `screens/r6_mn3/shortcut_setting.png`, `shortcut_set.png` |
| 3. title Options / Theater hi-res | **checked + fixed** | text crisp at 1440x1080; Theater hints rebuilt as retail (3 lines + pad icons), title texts proportional + 0.8 narrow, Options cursor stuck on Vibration fixed, Sound box 6 px lower |
| 4. MN2 open items (second pass) | **Graveyard / Combo Magic / Library checked against live, fixed** | see "Task 4" below; Library data view and the soul charge 3D still not compared live |

`cargo check --workspace --all-targets` clean; `cargo test -p sh2_menu -p sh2_battle` green (262 + 88 + 4), `cargo test -p sh2_field --lib cmd_` green.
Autoplay sanity (`sh2_app --us --autoplay --boost 80`): title, field, battle menu / ring / victory, the in-game menu tour all render
(`screens/r6_mn3/autoplay_sanity.png`).

## Combo switch (US code)

* `BTL0+3`: bit 0 = `BtlSaveSec::SetComboMenuMode` (SLUS 0x3bc450, as JP); bit 1 = the US-only setter at 0x3bc420 (`SetRetailModeBit1`);
  bit 2 = soul system.  The clear-data defaults (0x3bba80 / 0x3bc710) call both with 0.
* Bit 0 readers: BATTLE `SetMainMenu` (US 0x5f6918 / 0x600ca0, `andi 1`) = the `Combo` row (JP BtlMenu.c 10539).  Writers: the combo tutorial
  (BATTLE 0x461ad8, JP CBattle.c 1091) and the field's `SceneInit` (FS2 host.rs op 0x13).  The port's `combo_menu_enabled` (bit 0) was right
  for `can_link`.
* Bit 1 readers (`dsll32 30 / dsrl32 31`): `BtlMenu::Polling` 0x5d2ffc / 0x5d5e04 / 0x5da0d4 and `MainMenuFunc` 0x5e6d9c (the triangle ->
  mode 0x18 handlers), plus JP CBattle.c 3435 / 9461 / 11301 (mode 0x17).  Writer: `BtlSocket::Polling` SLUS 0x365f30..0x365f84 sets bit 1 =
  `(MENU+0x276 & 3) != 0` at every battle start (JP BtlSocket.c 299 identical).
* `MENU+0x276` bits 0..1: US `CmdTop::SelectMenu` (FIELD 0x4699e8..0x469a20) stores the confirmed row's place `+0x16` value; `CmdRetailWin11`
  (0x4e95a0) dims row `v` and puts the cursor (`+0x3f4`) on row `v ^ 1`, so the values are **ON = 1, OFF = 0** (CMDMENU top texts 28 `ON`,
  29 `OFF`).  The user's live save has 0 (OFF; the Combo entry is not unlocked there).
* Port: `BtlSave::{combo_shortcut_enabled, set_combo_shortcut}`, `MenuSave::{combo_switch, set_combo_switch, OFF_COMBO_SWITCH}`; cmd_top's
  Combo Switch now writes `MENU+0x276` (+ bit 1 at once) instead of bit 0; the battle copies the switch at `Stage::Intro` and the mode-0x17
  gate reads bit 1.  Test `save::tests::combo_switch_and_shortcut_bit`.

## Shortcut setting overlay (`BtlMenu` mode 0x18)

Retail (JP BtlMenu.c 6435 polling, 14876 `SetComboShortCutSettingMenu`; US 0x60faa0):
* Entry: triangle with bit 1 set on the attack shapes (`{0, shape, 0xffff}`), the item list (`{1, list row, item}`), crest magic
  (`{2, (MAGI+6 >> 1) & 7, id}`) or techniques (`{3, (SKIL+6 >> 1) & 7, record}`; magic / skills only when `+4` bits 5..6 are clear, else SE 4).
* L1 / R1 / L2 / R2 write all four bytes into slot 0..3, SE 2, redraw with that slot lit, close after 1 s; cross closes without writing (SE 3).
* Layout: `y0 = ((list.y - 128) / 2 + 128) - 42` with the list rect `(0, 290, 256, 104)` (US BATTLE 0x6e5e80) = 167; band y0..y0+84; frames
  (32 x 36) at (192 / 288, y0+8) and (173 / 307, y0+40); texts right-aligned at 192 / 173, left at 320 / 339.
* Port: `SH2_BATTLE_SHORTCUT_SET=<slot>` (devdrive) triangles on the first settled page and assigns.  Run: `SH2_BATTLE_DEMO=2
  SH2_BATTLE_PARTY=0,5 SH2_BATTLE_LEVEL=8 SH2_BATTLE_CMDS=item,attack SH2_BATTLE_MENU=276:01 SH2_BATTLE_SHORTCUT_SET=1` (the MENU poke also
  proves the battle-start copy: no `SH2_BATTLE_SHORTCUT` needed).
* Not ported: the JRing sprites (emblem / letters / style + element icons: drawn as panels and text), byte 6 of MAGI / SKIL (b1 = 0 for magic
  and techniques; only the icon uses it), US fusion-form rows (`BTL0+0x119c`) and Ouka's per-dress rows (`+0x111c / 0x130c..0x132c`):
  fused members get no overlay.

## Title Options / Theater (1440 x 1080)

* Theater hints (US FIELD.BIN 0x5553c0): message strings 4 / 5 / 6 (`: Play`, `: Back`, `: Switch Chapters`) are three stacked `MenuText`s at
  x 370, y 380 / 402 / 358, each after 16 x 20 pad icons (cell `MENU+0x26c[k] - 8` of the common icon sheet: confirm / cancel at x 354, L1 / R1
  at 338 / 354).  The port drew one line "O: Play    X: Back    L1/R1: Switch Chapters" at (30, 408).  Now `Part::ThHint(k)` / `ThIcon(k)`
  with the `COMMON/CMNMENU.DAT` attach 6 sheet (row 1 = pad bits 8..15).
* `RetailExtras::text`: the title's texts are `MenuText`s (US 0x3dfab0, `FontItem::Clear` flags 0x18): proportional layout + 0.8 squeeze.
  Fixes "Mal ice" style gaps and the hint overflowing the screen.
* Options (`title_options` -> `cmd_option`): the four-item title page moved its cursor on the old 24 px grid (stuck on Vibration); it now uses
  the retail row table.  The two-line Sound box sits 6 px lower (live `menu5/cmp_opt.png`: Stereo row 31 px, Dolby 58 px under the Vibration
  label; port had 25 / 51); affects the in-game page too.
* Shots: `screens/r6_mn3/title_theater_1440.png` (before: `title_theater_before.png`), `title_options_sound_1440.png` (before:
  `title_options_before.png`).  Drive: `SH2_CUTSCENE=off SH2_WINDOW=1440x1080 SH2_THEATER_UNLOCK=all SH2_DRIVE="w200 p:S w100 p:S w60
  u:screen=Title w30 p:S u:screen=Menu w60 p:D w20 p:D w20 p:O u:screen=Theater w90 s:th0 ..."` (Options: `... u:screen=Menu w60 p:U w20
  p:R w20 p:O w90 s:opt0`).

## Task 4 (second pass, 2026-10-16): Graveyard, Combo Magic, Library vs live

Live references: MN2's captures (`gy_c`, `cmg_a`, `libr_k`, `lchar_b`, session cdb345cf scratchpad) and two new ones from the main PCSX2
(pad only, menu opened and closed again, the user's state untouched): `screens/r6_mn3/live_library.png`, `live_library_list.png`.
Port shots 1440 x 1080 with `SH2_SCREEN_DEV=menu:AP_02_U SH2_BATTLE_SAVE=f43:ff,f63:ff SH2_BATTLE_MENU=340:01` (monsters defeated /
snapped, combo 0 seen) and `goto:grave / combomagic / library`; before / after in `screens/r6_mn3/t4_*`.

* **Narrow menu text was ~5 % too narrow everywhere** (Graveyard notes line 397 vs live 418 px, `SE.  0/ 40` 75 vs 85): retail
  `FontDraw::Order` adds the item's shadow x to the pen of each glyph.  `bevy_ui::expand_text` now adds `shadow.x` to the spacing of every
  narrow (`hscale < 1`) run; the wide HUD / field runs are unchanged.  Fitted by `examples/mn3_text_width.rs` (sh2_menu): `(width + 1) * 0.8`
  matches both lines.  `measure_text` still measures without it (right-aligned narrow text can sit ~1 px per glyph off).
* **Teal fringe around the element name plates** (Light / Fire ... on the Graveyard, Library, Magic): the plate's transparent texels are
  teal and the canvas samples bilinearly with straight alpha.  `UiTextures::add` now bleeds the neighbours' colour into fully transparent
  texels (`bevy_ui::bleed_transparent`, test); every menu texture benefits.
* **Library**: the entry name is the field serif (`FIELD_FONT`, proportional, x 0.8; was the gothic at 1.1), the arrows moved to the live
  spots; the number after `No.` is the narrow gothic with a shadow at x 162 (was font 2 at 166).  The list (start) is LIBRARY.MSD attach 6's
  textured `Name` fence at (38, 80) with the names only and no banner (was a general frame with `No.` + name under the banner).
* **Combo Magic**: matches live (`cmg_a`) once a combination is seen; no change.  The root list beside it shows page 1 in `goto` drives
  (the menu tour enters pages directly), not a page bug.
* Still different: the lavender `GRADE.` / `No.` / `Monsters` labels are thinner in the hi-res face than the live bitmap (colour equal),
  the Library report's first line has a `:` after the START icon (live none), Library data view not compared (no live capture with Snap
  Shot data).

## Open (priority order)

1. Theater chapter / title / page texts: positions are the port's; the retail theater has a second (chapter list) page (text slot 0x11,
   items at (40, 88) / (222, 384)) that the port does not draw.  The title Options page keeps the gaps of the hidden rows (not compared live).
2. Mode 0x18 / 0x17 JRing sprites; MAGI / SKIL byte 6 in `ActionRec`; fused-form shortcut rows.
3. MN2's list: soul charge 3D, Personal sub-scenes, Library list / data view, live re-checks of shops / save points / Game Over.
