# Field-side systems: shops, Solomon's Key, tailor, save / warp points, NPC actors, world-map extras

Status 2026-10-10 (section G, second field pass, finished: every system below was driven in the running game on a JP map and with `--us`; screenshots in `notes/integration/screens/field2/{jp,us,cam_cmp}/`, 768x672 = half scale).
Earlier status 2026-10-09 (section G, second field pass).  Code: `port/crates/sh2_field/src/{fscreen,shop,solomon,tailor,points,screens_dev}.rs` (new) and
`{host,plugin,actors,script_actors,worldmap,worldmap_plugin}.rs` (extended).  Screenshots: `notes/integration/screens/field2/{jp,us}/`.
Everything below was exercised in the running game on both discs through the dev driver (section 8); shop and tailor also through the map script (`SH2_SCREEN_VIA`).

## 1. Framework: field screens (`fscreen.rs`)

The original opens these as scene objects (`CField::SpecialMenu` -> `new shop` / `new tailor`, `CmdMenu` page 0x15 -> `new solomon`) that poll
once per frame, draw with `prim*` / `Menu*` over a dimmed capture of the field and hand control back through an owner callback
(`cbShop`, `cbTailor`: `CField::Pause(1)`).  The port mirrors that:

* `FieldScreen` (trait: `tick(env, keys, press, io)` + `draw`) = the object's `Polling` + render; `FieldScreens` (resource) = the owner.
  It builds a screen from a `ScreenReq` (`Shop{id}`, `Tailor`, `Solomon`), runs it at 60 Hz in `GameSet::Logic` with the same `cmd_page::Env` the
  command-menu pages get (session, MSD scenes, textures, battle DB, save device) and draws into sprite layer `SCREEN_LAYER` (9, above the command
  menu's 8).  While a screen is up the field logic is locked and the script that opened it waits (`ScriptState::menu_wait`, released when the screen
  reports `finished`, like `cbShop(3)`).
* `plugin.rs`: `MenuReq::Shop` / `MenuReq::Tailor` (set by op `0x7f SpecialMenu`, kind `0x100` / `0x300`) become `ScreenReq`s (the toasts
  "Shop n (not available)" are gone); `MenuReq::Save` (`SpecialMenu(0x10)` = `CommandMenu(0x10)` = `dataAccess`) now opens the menu **straight on the
  save page** (`Act::GotoData(false)`), it used to open the main menu.  The shop's "Equip" entry opens the real equipment page the same way
  (`ScreenIo::open_menu`, the shop sleeps until the menu closes).
* The command menu can open Solomon (`HostReq::Screen(ScreenReq::Solomon)`, wired by the menu agent in `cmd_page.rs`).
* Helpers: `window` (the `primWin` panel), `coded_text` (message-table codes `%p0..7` colours, `$` line break, `%%`), `wrap_text`, `dim_field`
  (`shopCapture::setRGBA(0x40,..)`), scripted runs (`ScreenAct::{Key, Wait, Shot, Until(state), Mash}` driven by `FieldScreen::state()`).
* Tests: `plugin::tests::script_events_open_the_shop_and_the_tailor` runs every event of the real JP maps `AR_01_U` / `PA_03_U` through `FieldHost` and
  finds `MenuReq::Shop{1}` / `MenuReq::Tailor` (the op -> screen path); the screens themselves are driven by `screens_dev`.

## 2. Shop (`shop.rs`, JP `shop*` 0x004ded30.., US 0x00522a80..)

Real:

* **Tables** from the disc's own `FIELD.BIN`: `shopTbl` -> `shopNN_itemTbl` (`{u8 kind, u8 index}`, 0-terminated; kind 1 item, 2 weapon, 3 armour,
  4 accessory, 5 one-off crest, 6 ring item), `shopPointTbl`, `shopJRingTbl`.  JP: 3 shops at the overlay symbols; **US: 25 shops, table at
  0x0060ea60, `shopPointTbl` 0x00615210 (100 / 500 / 1250 / 2500 / 999999, the demo's was 5 / 12 / 25 / 99999 / 999999), ring table 0x00615230
  (found by pattern search, identical to the demo's)**.
* **Texts**: JP `shopMess_*` overlay tables (+ the main-exe string pointers, which point back into the overlay: 0x00559070 "ショップ", 0x00559810 ...);
  US: the two `msg` entries of `SHOP/SHOP.DAT` (123 texts + 25 shop names; the retail shop adds the Point Card / Gold Card texts).
* **Pictures**: `SHOP/SHOP.DAT` entries 1..5 (title "Shop", "Note", face frame, italic digits, "Cash Time"), 6.. party faces (JP 20, US 12: retail
  `FI_nnn` numbers start at 6).
* **Rules** (`mCalcPoint`, `mMakeBuyList`, `mMakeSellList`, `mCheckSelector`, `mCalcCurrentMax`, `mSetupBuyResultWin`, decompiled JP + US via Ghidra):
  shop points (`MENU + 0x2bc`) set the rank E..A; goods are bought at `GetRegDat` prices (items +0x24/+0x28, weapons +0xc, armour +0xc/+0x10,
  accessories +0x20/+0x24, ring items +0x14/+0x18); a purchase earns `(price + 99) / 100` points; **buy** may challenge a discount of
  `(rate + 1) * 10 %` (list shows the highest rate first), **sell** a price-up of `(rate + 1) * 5 %`; a *lost* discount buys at the set price, or - when the
  cash does not cover it - costs `max(1, (cash + 9 - discounted total) / 10)` points and the goods (retail; the demo's expression has the sign
  the other way round, ported as written for the JP build; rank A / Gold Card is exempt on retail); the quantity limit is `100 - owned` (buy) /
  `owned - equipped` (sell), reduced to what the cash buys at the best discount (`mCalcCurrentMax`).  Cash is capped at 99,999,999.
* **Ring**: the ported `JRing` (`SetMode(5,1,1,3,3)`, three step areas at the `shopJRingTbl` row `rand() % 5` minus `d = 30 - 5 (rate+1)`,
  width `2.5 d`, speed `1.6 - 0.1 rate`); success = result grade >= 2 (`(flags >> 1) & 3`).
* Flow (JP `Polling` states): fade-in -> main (Buy / Sell / Equip / Leave) -> list with party faces and the **equipment comparison** (stat deltas with
  the equip marks, via `cmd_equip::derived_with`) -> quantity (right / left, wraps through 0) -> query (challenge / normal / cancel) -> rate -> ring
  intro -> ring -> result (points, rank-up text) -> list (rebuilt) ... -> leave (points + cash written back, `~shop`).
* Tests (10): rank table, quantity limit, discount / mark-up maths, buy / sell outcomes, ring areas, bag arrays, **real tables of both discs**.

Approximated: windows are plain translucent `primWin`-style panels at the original coordinates (the original shop has no `.MSD` scene); the sound ids are the
menu SE ids; the comparison uses the stat sum of the equip page instead of the full `GetRealPAtk ..` rules; US kind-10 goods (obtained flags) are ignored.

## 3. Solomon's Key (`solomon.rs`, JP 0x004f20c0.., `SOLOMON/SOLOMON.DAT`)

* It is a **crest-placement board**: 72 slots (9 x 8 grid, `mSlotBaseTbl` `{x, y, area, crest}`; the table is **identical in the JP and US overlays**:
  0x00554450 / 0x0060ed60, attributes `mDemonAttr` 0x00554360 / 0x0060ec70) on an old map (4 quadrants of 512x448 = entries 0..3, the 72 seals =
  entry 6).  A crest (an `MC_P` record = a demon, owned when its bit in the bag's bit set `0xaa4` is set, the kind-5 goods of the shops) only goes into
  a slot of its own region (`mDemonAttr[crest] == slot area`); a region is **complete** when all its slots hold the crest the table names; then its slots
  are fixed, `MENU + 0x220` gets the region bit, and the region's crests teach their magic (`MC_P +6` flags -> ids at `+8/+10/+12/+14`, learned bit in the bag bit
  set `0xaae`).  Placement is saved in `MENU + 0x224 + slot` (crest + 1).
* UI: tutorial pages (first visit), main window (Crest List / Decipher Text / Reset Area), crest list (names `MC_P` -> `SSHMES` 16, notes from the texts), the map with
  the cursor (d-pad on the grid, restricted to the region of the held crest, L2 / R2 zoom), place / pick up / swap queries, region-complete message with the new magic,
  reset area.  Texts: JP overlay tables, US `msg` entries of `SOLOMON.DAT` (the retail game has no hint notes: the decipher text lists the notes of the owned crests).
* Tests (5): placement rules, completion, fixing, reset, save round trip, and the **real tables** (every crest has exactly one slot of its own region, both discs).
* Not ported: `solomonEffect` intro, `COMP.DAT` 3D frame, region silhouettes (entries 11..19), the JP demo's restriction to region 4 (`Polling` state 9 `area == 4`).

## 4. Tailor (`tailor.rs`, JP 0x004eafe0.., US 0x00534370.., `SHOP/TAILOR.DAT`)

* `SpecialMenu(0x300)`: sketch book of the dresses whose bit is set in the tailor flag word (default `0x3fe` = dresses 1..9), left / right turn pages, circle orders,
  yes / no, `mSetCloth` (`BTL +0xdaa` = worn dress, `BTL +0xda8` bit = used, `MENU +0x2fc` collection bit), the stage cut scene (stars, presentation text with
  the dress name, the class-change note, the designer's comment); a used dress gives the buzzer.  Real: list rule, state machine, the save flags, texts (JP overlay tables /
  US `msg` entries), names (`CLOT` -> `SSHMES` 14), stage art, designer portrait, stars (`mStarPos`).
* Not ported: the 3D sketch-book pages (`primModel`, entries 14..25), the `dRoll` name roll, the retail "Original Class" change itself (only its note is shown).

## 5. Save points and warp points (`points.rs`, `SavePoint` / `WarpPoint`)

* `CheckOnPoint` (8.5 horizontal, 5 vertical): `ScriptState::{on_save_point, on_warp_point}` are refreshed every frame by `points::sync_points`; triangle sets `ScriptState::menu_save_ok`
  (`CommandMenu(4, ChkSavePoint() >= 0)`: `CmdMenu +0x4a = 3`) before the real command menu opens; its Data page is the real `dataAccess` -> `SaveMenuSection`
  storage (`sh2_menu::storage`); `SpecialMenu(0x10)` (`MenuReq::Save`) pushes `Act::GotoData(false)` so the **save page opens directly**.  Live: `save_01_screen` / `save_02_after_circle` (jp, us) show the
  real slot list (name / level / play time / cash, the "save to this slot?" yes / no box); `points_01 / 02` show the ring + light column under the player and the command menu opened on it.
  *Gap*: the command menu still offers Save off a save point (needs the menu agent: `requests.md` F1).
* Models: `COMMON/SVP.BIN` (ring `save_00`, light column `save_01`, glow `save_02/03`) and `COMMON/WPN / WPA / WPJ / WPF / WPC.BIN` (kind 0 / 1 / 2 / 3-5 / 6; pad
  `warp_00`, `warp_01` out column, `warp_02` in column, `apwp_00` the Apoina pad) are split into their `mdl` + `anm` groups and spawned at the slots of the script ops
  `0x7e` / `0x65`; the column / glow appear while the player is on the point, the warp columns play with `DoWarp` (`WarpFx`; `points_04..06`: out column + screen flash, in column).
* The **warp list is the map script's own selection window** (`Select` + `DoWarp` + `MapJump`, already implemented); `WarpPoint` only draws the pad, so there is no separate list screen.
* Scripts reach the screens: `SpecialMenu(0x100, n)` -> `MenuReq::Shop`, `(0x300)` -> `MenuReq::Tailor`, `(0x10)` -> `MenuReq::Save`, `(4/5/6)` -> the menus.  Test `plugin::tests::script_events_open_the_shop_and_the_tailor`
  runs the events of the real maps in the VM (a shopkeeper's event introduces himself on the first visit - flag `0x141` - and opens the counter on the second, so each event is run twice, answering the
  selections with the cursor-down presses a player would use): JP `AR_01_U` event 7 -> shop 1, `PA_03_U` event 16 -> shop 2, event 17 -> tailor; the `#[ignore]`d `us_script_events_open_the_shop_and_the_tailor`
  (flips the process-wide region; run alone) finds US `FI_01_U` event 26 -> shop 4, `CA_02_U` event 7 -> shop 5, `GI_01_U` event 8 -> shop 11.  The US tailor (`CA_02_U` / `FI_01_U` function `0x13dc`, behind a dialogue select
  of event 6) was not reached automatically; it is opened with the same `MenuReq::Tailor` from the dev driver.

## 6. NPC actors (`actors.rs`, `script_actors.rs`, `plugin.rs::bridge_actors`)

* `LoadCharacterByName` (op 0x07, `char_id == -1`): the name is a package file (`"037W00R.SET"`, `"KANTERA.SET"`: US scripts use 45 distinct names, JP 9) -> `FIELD/MODEL/<name>`
  through `ActorSpawn::file`; several are static props without motions (no `fidl`), which is fine.  The old bridge only understood numeric names.
* `AutoMove` / `PathMove`: script actors now request the **walk / run motion** while they move and idle when they stop (`ActorOut::Gait` -> `PlayMoveMotion`), turn at the
  walking turn rate (2 pi / s) before walking (first turn on the spot when the angle is > 53 degrees), round the path nodes (`UpdatePathMove`: heading blend `sin(t pi/2) * 0.9` within 10 units of a node)
  and honour model-to-model collision (`HitChkM2M(4.0)`: wait while another displayed model with hit check stands in the way, give up after 10 s like `AutoAvoid`).
* **`PathMove` arrival fix**: the rounded corner (heading blended towards the next leg inside the last 10 units) made walkers circle a node for ever (`GI_00_U`: 4 of 7 walkers frozen in place, gait `walk`).  The original
  (`UpdatePathMove`) decides arrival by the distance *walked on the leg* (`+0x194 >= +0x190`, the leg length measured from where the model stands when the leg starts, `UpdateNodeLen`) and blends by that same
  distance; `MoveTask::Path { leg, done }` does likewise.  Test `us_npcs_walk_their_routes` (`#[ignore]`, region flip): every walker of retail `GI_00_U` covers > 150 units in 1000 frames.
* Tests: `hit_chk_m2m` geometry, a walking NPC reports walk then idle and arrives, an NPC waits for a blocker and goes on, both discs' named models parse.

## 7. World map (`worldmap.rs`, `worldmap_plugin.rs`)

* `mNewPointDemo`: a point whose state byte is 2 ("new", `WM` chunk byte `0xc + id`) is scrolled to, plays the four rays (the 64x64 ray sprite of `WMAPn.DAT` entry 2, bright corner anchored on the point, copy i turned by
  i * pi / 2 plus the animated angle 0.01 -> 0.06 -> 0.01, scale 0.5 -> 1 -> 0 over 64 frames, SE 0x1007) and becomes open; then the map scrolls back to the selection.  **JP and retail** (the retail table used to fold
  "new" into "open").  `SH2_WM_UNLOCK=<index>` forces it for tests (both builds).  Live: `jp/wm_01..05`, `us/wm_02_retail_demo`.
* `worldMapLight`: pulse (`+0x1c` / `+0x58`: alpha 0x20..0x40) + the real spotlight: the 216 x 216 texture (entry 1) is **one quarter** (opaque black at the top left, clear at the bottom right) and the four sprites of
  `worldMapLight::select` mirror it around the point (432 x 432 clear window), the four black fillers surround that square, the sun halo is the 16 x 16 `+0x60` sprite.  The picture / spotlight / points / rays moved to the
  sprite layer `WM_SCENE` (= `SPRITE_BASE + 2`): the Bevy-UI layers draw axis-aligned unflipped images only (`requests.md` F2).
* Triangle in the selection loop opens the real command menu over the map (`worldMap` state 0xc, only once the party exists); the map waits while it is open (`jp/wm_08`, `us/wm_07`).  Retail L1 / R1 (switch world): R1 / L1
  run live on the new-game world list (only world 0 is open there, so the selection returns to it); portals to another world need more story progress than a new game has.
* Not ported: the first-visit tutorial window (`mSetupTutorialWin`).

## 8. Dev driver (`screens_dev.rs`)

`SH2_SCREEN_DEV=<kind>[:arg][:map] SH2_SCREEN_SHOTS=<dir> cargo run -p sh2_app [-- --us]`, kinds `shop:<id>:<map>`, `tailor:<map>`, `solomon:<map>`, `points:<map>`, `npc:<map>`,
`save:<map>`, `worldmap` (with `SH2_WM_UNLOCK=<point>`; retail seeds the first 24 points open).  `SH2_SCREEN_VIA=<event>[:<event>..]` opens shop / tailor **through the map script** (events called in order, circle mashed through the dialogue):
`SH2_SCREEN_DEV=shop:1:AR_01_U SH2_SCREEN_VIA=7:7` (jp), `shop:4:FI_01_U SH2_SCREEN_VIA=26` (us), `tailor:PA_03_U SH2_SCREEN_VIA=17` (jp); `SH2_NPC_SHOTS=n SH2_NPC_SPACING=t` for `npc:<map>`; use `SH2_SAVE_DIR=<dir>` so the save screen does not write the real save folder.  It starts a new game with the demo party, enters the map, raises the same `menu_req` the script op sets, plays a scripted pad run
and photographs it.  Scripts: `screens_dev::script_for`.

## 9. Script camera (`host.rs`, op `0x76 SetCameraC`)

Bug found 2026-10-10 (user report: reversed camera in the US opening): `SetCameraC(type 2, pos, angles, frames)` aimed **backwards**.  `UpdateScrCamera` case 5 (JP 0x004aa750) is
`target = pos + RotY(yaw) * RotX(pitch) * (0, 0, len)` (`len` = current camera distance, 30 if 0): zero angles look along **+z**.  The port used `pos - (sin yaw cos p, -sin p, cos yaw cos p) * len`, i.e. 180 degrees off and
with the pitch inverted.  Type 2 is used by ~100 call sites in ~60 maps (AP_00_U `f62ab` has nine, JP AP_02_U the hall scene, ...).  Now `host::angles_target` (test `angle_camera_looks_along_plus_z_at_zero_angles`).
Before / after on JP `AP_02_U`: `screens/field2/cam_cmp/jp_ap_02_u_before_after_SetCameraC_type2.png` (floor and black wall -> the hall with the Pieta and the two actors).  Types 0 (absolute target) and 1 (direction x 20) match
case 3 / 4; `SetCameraA / B` (look at actors) were unaffected.  **Not done**: the live PCSX2 comparison (CField `+0x2150 / +0x2160`) - the emulator was being driven by other agents (states were swapped under me, renderer
changed), so no title reset was attempted; `examples/cam_dbg.rs` (`cam_dbg [--us] MAP [frames]`) prints every script-camera change of a map for a later live check.  Also observed: in `AP_00_U` the `f62ab` scene (script camera) is not reached by the port
because `MCES over` (end of `N003.LSD`, or the placeholder wait) jumps straight to `AP_02_U`; whether the real game runs it after the LSD is unverified.

## 10. Known gaps

3D tailor pages / name roll; Solomon intro effect and silhouettes; the save-only-on-a-save-point gate of the command menu (menu agent, `requests.md` F1); world-map tutorial window; world-switch portals on retail need
story progress; shop windows are approximations; retail-only shop goods kind 10; `AutoAvoid` (stepping around a blocker) and `MakeMoveNode` routing of `AutoMove`; the JP demo has names for only 5 crests (the rest of the
Solomon list shows blank names there); the US tailor was not reached through a script (see section 5); live camera comparison (section 9).
