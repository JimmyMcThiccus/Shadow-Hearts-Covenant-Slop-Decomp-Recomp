# Round 6 MN2: menus and meta screens (running notes, 2026-10-14)

## Status (2026-10-15, resumed after the pause)

The "menu draws nothing" problem was PF's load bug in `bevy_ui` (b814c17, kept).  Done this session, each one checked side by side with the
live captures (`tools/live/cmp.py`; the port shots are in the session scratchpad):

| screen | state | notes |
|---|---|---|
| **Menu 3D model** (`sh2_field/src/menu_model.rs`, new) | done | `CmdCache.model` / `model_ctl` per page -> `MenuModelView` -> one off-screen `Camera3d` (1024 x 768 sRGB image, layer 27, `ScreenExempt`, order -20, transparent clear) + the model under a flip root (+ weapons on EX01 / EX02), `ModelLightOverride` with the `CreateLight` rig; the image is `UiTextures` id `MODEL_TEX` and the page blits it in its draw order.  Camera = `MenuDataModel` (i16 pos / 10, f32 rot_x, f32 yaw), fov `2 atan(224 / (512 * 0.9333))`.  Motions: idle + square action list + `MenuMotionConnect` chains; L1 / R1 (held) turn.  Needs the decode-pass alpha (requests.md). |
| **Library** (`cmd_library_retail.rs`, new) | done | Monsters / Characters, the 3D model with the record's camera, banner `Monsters  No. n`, `< name >`, rule, typed description, element stone, people's portrait medallion, report `Start: List / square: Action / R: Rotate L/R` (+ triangle Details with Snap Shot data); the list (start / confirm) and the data view are not compared live.  Monster names from MON +2 (`cmd_view::monster_name_row`), also in the demo-shaped page. |
| **Personal** (`cmd_status.rs`) | 3D model + entries | `member_model`: table 63 camera, battle model + weapon when armed (field model + `P.SET` otherwise), motion tables 57 / 58.  The entry list is the member's record of demo key 7 (raw 9): Karin Status / Sword Arts / Affinity / Profile as live.  New sub lists: Tarot Card and Aromatherapy (Lucia; owned bits `BTL0+0xf3f..0xf42`, help text in the Notes), Wolf Bout, Change Dress, Snapshot / Album, the other members' skill lists.  These are generic lists, not their own retail scenes. |
| **Ring Custom** (`cmd_ring_retail.rs`, new) | done | card, menu column, banner, the member's attack ring (`attack_ring` + `PC_J` areas + `JRCUSTOM`, scale 0.91 at (311, 294)), Area / Equip fence with points (left / right), Ring Items fence (Hit Area Expand / Strike Expand / Attack Boost / add-on items; names kind 0x10, help 0x26, icon = item sheet cell 14), No. of Attacks, Ring Types + Explanation view, Auto Ring ON / OFF.  Matches `rc_main_a` / `rc_rows` / `rc_t2` / `rc_o1` within a few px. |
| **Graveyard** (`cmd_misc.rs` `GraveBoard`) | done | GRAVE.MSD picture, six stones (`ElemArt::draw_at`, stone MDT 54 of attach 0, grades / SE from `MENU+0x380`), question / Yes / No, root list and the Soul Energy orb (no cash / time), as `gy_c`. |
| **Root page** | Soul Energy orb added | CMDMENU attach 10: the orb picture at (285, 145) and the pool `%4d`, in `font_big` (live: an italic).  The gauge arc / sphere pulse are not animated. |
| **Combo Magic** | done | textured fence, rows `????` / name + `%3d` MP, cyan selection, root list, Notes `????` for unknown rows. |
| **Button Customization** | done | pad picture, connectors, ring frames, plates (common fence texture), the right list by physical button (circle / cross / triangle / square), retail swap logic (pick a row, then a second), `%iN` icons in the Notes line. |
| **Combo Setup** | fixed | style names = demo key 0x32 (raw 49), the member's style mask (demo 0x31 data byte 7), `ConvertComboKeyDefault` defaults (row byte 1).  Karin now shows Standard / Hard Hit / High Angle / Knock Down. |
| **SECHAR** (`cmd_sechar.rs`, new `CmdPage::SelectChar = 19`) | done | the shop's Equip opens the member pick (root-style member rows), then Equipment for that member; cancel closes the menu back to the shop.  Not compared live (no capture). |
| Items | small fix | `[L2][R2] : Scroll` joins the report when the list scrolls (live `it1`). |
| Element ring | fixed | the dashed ring takes the element colour (Fire red, Earth / Water teal, Wind yellow) on the Library / Magic / Graveyard stones. |

Still open (priority order):
1. The soul charge's 3D Yuri / stone: `SCCHAR.DAT` holds `chb_s / chb_i / chb_e` (15 frames, 15 atomics: not Yuri; it is probably the charge
   beam), `SCSTONE.DAT` holds the stone (`chs_*`), `SCLV_00n.DAT` the grade-up (`chh_01`).  The camera / placement of `CmdRetailPage01` is
   not decompiled.  `menu_model` can draw them once the screen feeds a `ModelReq` (it runs as a field screen, not in the menu overlay).
2. Personal: the Sword Arts list should use `sword_arts_mask` (only the highest tier learned).  The tarot / aroma / Papillon (`Joachythms`) /
   wolf / dress / album pages are generic lists, not their retail scenes (PERSONAL.MSD attaches 12..23).  No live capture of them.
3. Library: the list window and the data view are not compared live; the name / description use measured positions (CmdExplain).
4. Live re-verification of shops, Solomon's Key, tailor, save / warp points, title and Game Over (the PCSX2 instances are off).
5. Root Soul Energy number: an italic big digit font; the gauge arc should fill with the pool.

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
