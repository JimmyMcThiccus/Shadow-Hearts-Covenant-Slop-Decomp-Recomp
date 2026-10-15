# Round 6 MN2: menus and meta screens (running notes, 2026-10-14)

## Paused (2026-10-14 ~20:15, coordinator: max 2 running agents)

**State of the tree:** no source file of mine is half-edited.  The only new file is the dev example
`port/crates/sh2_menu/examples/mn2_library_dump.rs` (it builds and runs).  No locks held (ghidra.lock and pcsx2-3.lock deleted, Ghidra
switched back to SLUS_210.41).  No processes left running.

**Done so far:** research only.  Live captures of instance 3 and the retail Library RE are below.

**In progress:** the design of the menu 3D-model renderer (for Library, Personal and the soul charge), not started in code.

**Exact next steps:**
1. **Check this first:** on the current tree, `tools/live/menu_dev.sh` (US, AP_02_U and DB_00_U) photographs **no menu at all**.  The log
   says `cmd menu: goto Item -> true` and so on, but the screenshots show only the field
   (`scratchpad/port0`, `scratchpad/port1/item.png`).  Find out whether the menu draw or the UI camera regressed, and whose change caused it
   (`git diff ed231e6..` on `sh2_menu/src/bevy_ui.rs` and `sh2_gfx/src/bevy/screen.rs`, and the sh2_app camera setup).  Fix it if it is in MN2 files, or file a
   request if it is not.
2. Monster names (task 3): in `sh2_field/src/cmd_view.rs` ~708, replace `env.name(8, id)` with the name row
   `db.monster(id).model` (record +2, as in `sh2_battle::bridge` `name_row`).  Do the same in the retail Library.  grep for other `name(8,` uses
   (there were none in sh2_menu / sh2_field).
3. New `sh2_field/src/menu_model.rs` (add `pub mod` in lib.rs, an additive hook).  Design:
   * `CmdCache.model: Option<ModelReq>` is set by the page.  `menu_tick` copies it into a `MenuModelView` resource, and clears it when the menu closes.
   * An Update system keeps one `Camera3d` (`ScreenExempt`; `RenderTarget::Image` of a 1024x768 `Rgba8UnormSrgb` image, so the gamma
     decode pass applies and the projection is 4:3; clear colour transparent; `RenderLayers` 27, plus `Propagate` to the model,
     `HierarchyPropagatePlugin<RenderLayers>` as in `cutscene_plugin`).  It also keeps the model under a flip root (`CharacterGpu::load/spawn`), and the weapons from
     `sh2_battle::models::{weapon_files, parse_weapon}`, following frames EX01/EX02 like `follow_weapons`.  It registers the image in `UiTextures` under a fixed id
     (`UiTextures` needs an `insert_handle(id, handle, size)`), and the page blits it full screen in its draw order.
   * Camera (`CmdMenu::SetCamera`, US 0x466420): `MenuDataModel {i16 x, y, z (/10); i16 k (/10); f32 rot_x @8; f32 model_yaw @12}`.  The
     camera is at (x, y, z) in PS2 space, rotated about X by rot_x, and looks along +z.  It converts with `ps2_to_bevy` (forward = ps2(R*(0,0,1)),
     up = ps2(R*(0,-1,0))).  Projection = `SetViewMatrix(512, 0.8, 0.9333)`, so vertical fov = 2*atan(224 / (512*0.9333)) = 2*atan(0.46875).
     Library Revenant: cam (-1.2, -8.6, -25.5), rot_x 0, yaw 0.506.  Heimann: (-2.2, -9.0, -26.1), yaw -0.349.
   * Lights (`CmdMenu::CreateLight`, US 0x466600): ambient 0.2; directional colour 0.9, dir (-0.1926, -0.1926, 0.9623); directional
     colour 0.4, dir (-0.0499, 0.9975, 0.0499).  I read these as PS2 travel directions; the port needs "towards the light" in Bevy, i.e. `-ps2_to_bevy(d)`.  Build them
     through `sh2_gfx::light::LightControl::create_ambient/create_directional`, then `light_matrix`, as `sh2_battle::stage::scene_light_of` does, and put them on the
     model with `ModelLightOverride`.  Check the result against `libr_k.png`.
   * Motions (`MenuModelPack`): idle = list[0].  Square (`SetAction`) plays the next non-empty entry of the motion list (wrapping to 1).
     When a non-looping motion finishes, the connect list (pairs from -> to) chains the next one; otherwise play idle again.  The right stick rotates the yaw.
4. Retail Library page (rewrite `LibraryPage` for `is_retail()`, or a new `cmd_library_retail.rs`), data below.  Then Personal (the live `ps_b.png` has the 3D model,
   `square : Action / R : Rotate L/R`, and Status / Sword Arts / Affinity / Profile tabs) and the soul-charge 3D Yuri.
5. Ring Custom, Graveyard, Combo Magic, Button Customization, Items: build the retail layouts from the live captures listed below
   (scene files `RINGCTM.MSD`, `GRAVE.MSD`, `CBMAGIC.MSD`, `KEYCUSTOM`, `ITEM.MSD`; dump them with `cargo run -p sh2_menu --example dump_msd -- MENU/MSD/X.MSD`,
   with `SH2_DISC_DIR` set to the US disc).
6. After that: SECHAR member pick, Combo Setup defaults (BT's `ConvertComboKeyDefault`), side-quest screens, live re-verification, coverage
   `tools/coverage/run_all.sh run msd`, an OUTLINE paragraph and autoplay screenshots.

Build rule: prefix every cargo call with `CARGO_BUILD_JOBS=6`, target `%USERPROFILE%\.cache\sh2-r6-mn2`, dev profile.

## Live captures (PCSX2 instance 3, `SH2_PCSX2_INST=3`, debug map)

Unlocked the game's way: debug menu (K) > その他 (row 5) > メニュー設定 (row 9) > 三猿衆戻し（フルメニュー） (row 10).  The debug menu
remembers its last row: take a screenshot before confirming.  (A walk on the **main** instance landed on a wrong row and sent it to
the title.)  Party = Karin only.  Files are in the session scratchpad `live/r6/` (not in the tree; redo with `seq.py` if they are lost):

| file | shows |
|---|---|
| `root.png`, `root2.png` | full root list, page 1 / 2 |
| `rc_page_a` (member pick), `rc_main_a` | Ring Customization: card (portrait, `Karin`, LEVEL, HP / MP / SP), menu at (380, 25): Hit Area Width / Add-on Effects / Hit Area No. / Ring Types / Auto Ring; banner `Hit Area Width` (y ~ 205); `Ring Items / Held` window (Hit Area Expand 3, Strike Expand 3); `Area / Equip` window (Hit Area: 1 ATK ... 0); tilted ring with orange hit and red strike areas |
| `rc_rows.png`, `rc_row1..4` | the four other menu rows (Add-on Effect `--------` + Ring Items Evasion Down 1; Hit Area Number `No. of Attacks` 2 times / 1 time + Ring Items Attack Boost; Ring Types `Name` list Normal / Practice / Technical / Gamble Ring; Auto Ring ON / OFF boxes) |
| `rc_w1_a`, `w.png`, `s2.png`, `rc_a1`, `rc_n1`, `rc_t1`, `rc_t2`, `rc_o1` | sub-modes: area row edit `0 >` + `(x) : Confirm`; ring type with `Confirm / triangle : Explanation`; the explanation page (`Normal Ring` + typed text, up / down arrows); Auto Ring cursor |
| `gy_a..c`, `gy_d` | Graveyard: six stones 3 x 2, `GRADE.1`, element plate and kanji ring, `SE.  0/ 40`, `Go to the Graveyard?` Yes / No, graveyard **picture** backdrop (not the streak), root list |
| `cmg_a/b`, `cmg_k`, `cmg_i` | Combo Magic: `Name / MP` window, `????` 64 (cyan); Notes `????`; confirm / triangle do nothing |
| `opt.png` | Options (already retail in the port) |
| `bc_a/b`, `bc_k`, `bc_kd`, `bc_back` | Button Customization: pad diagram, four plates Other / Menu / Cancel / Confirm with button icons, right list `circle: Cancel / cross: Confirm / triangle: Menu / square: Other`, `Default / Confirm`; picking a button shows a white arrow on the first row and the swap target in cyan |
| `ps_pick`, `ps_b` | Personal / Status: card, EXP / Next, banner `Status`, STR / VIT / AGL / INT / POW / LUC, DCP 0/7, WGT Normal; **3D Karin**; Fire stone; menu Status / Sword Arts / Affinity / Profile; report `square : Action / R : Rotate L/R` |
| `it1`, `it2`, `it3` | Items: `Name / Held` list with icons, greyed rows, down arrow, tilted ring emblem, report `triangle : Explanation / square : Sort / L2 R2 : Scroll`; the target pick shows a portrait medallion with HP / MP / SP and the name at the top right |
| earlier `live/libr_*.png`, `lchar_*.png` (round 5) | Library monsters / characters with the 3D model |

## Retail Library (`CmdLibrary`, US FIELD.BIN; Ghidra raw = US - 0x45ea80)

* GetReady 0x497b40, Update 0x498300, UpdateData 0x498a40, SelectMenu 0x49a000, SetMonster 0x4996a0, SetNPC 0x499900, CmdLibraryInfo
  UpdateScene 0x4b48b0 (`No. %3d` with LIBRARY.MSD res 40), SetCamera 0x466420, CreateLight 0x466600.
* Records: monsters = MDT demo key 20 (retail 22), stride 0x58, 18 pointers.  k0 "", k1 short text (Notes), k2 description, **k3 ->
  MenuDataModel**, k4 idle motion, k5..k7 action list, k8..k12 motion-connect pairs.  Data `+0x48`: byte 0; byte 1 = count << 3 | bit 2
  (ML_ MMD) | bit 1 (0 = field model, 1 = battle model); u16 ids from +0x4a; u16 at +0x56 = list number.  Characters = key 19 (retail 21),
  stride 0x80, 30 pointers: k0 name, k4 / k6 short / long text, k8.. motions (`fidl agre ta_a`), k13.. connect pairs, k29 -> MenuDataModel.
  Data +0x88: bits 2.. = element, bit 1 = model kind, bit 0 = flag; +0x89 bit 0 = motion slot, bit 1 = weapon = model number, bit 2 = MMD;
  u16 +0x8a = model number.  Base id 13.
* Model files (LIBRARY.MSD res, slot order of `MenuModelManeger`): weapon res 4 / 5 (`MENU/DAT/%03d.WPN`, `BTLDATA/WPN/%03d_%02d.WPN`),
  weapon motions res 6 / 7 (only when the weapon number is >= 100: number - 100), model res 0 / 1 (`FIELD/MODEL/%03d.SET`, `BTLDATA/CHR/%03d.BCM`),
  motions res 2 / 3 (`MENU/DAT/%03d.MMS`, `BTLDATA/CHRANM/%03d.ANM`), res 9 `MENU/DAT/ML_%03d.MMD`.  Monster: model = MON +4 (chr), weapon = MON
  +0x2e, element = MON +0x14 & 7, MON +0x15 >> 5 -> MenuModelManeger arg.
* Keys (retail pad bits): square 0x8000 = SetAction; triangle 0x1000 (when the monster has data) toggles the data view
  (`CmdLibraryDetail`: HP. / MP. / WGT. / EXP. / Cash. / Souls. / Items. + ailment and stat-down resistances, LIBRARY.MSD res 12..39);
  start 0x0008 = list (`CmdLibraryList`).  The report adds lines 0xc, 7, 0x11 (only when data exists), 0xb.
* Layout (live `libr_k`): title `Library`; banner `Monsters  No. 1` at the top left; `< Revenant >` with arrows; a rule; the description
  typed out (white, font 0); the element stone at the right; the report `Start : List / square : Action / R : Rotate L/R`.  Characters also show the
  portrait medallion (LIBRARY.MSD sprite 1 at (46, 214), `MENU/FACE/FI_%03d.TEX` res 11).
