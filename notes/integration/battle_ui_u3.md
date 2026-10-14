# Battle UI finishing pass -- U3: command menu, target select, sub-menu pages (2026-10-10)

Files: `port/crates/sh2_battle/src/hud.rs` (all HUD drawing), `ui.rs` (menu state machine + the blue fallback), `build_hud_view` / `draw_battle_ui` in
`plugin.rs`, `devdrive.rs` (shot points).  Evidence: `screens/battle_ui/u3_*.png` (left = real capture when one exists, right = port, `SH2_SCREEN=native`).

## Sources read
* `decomp/H/BtlMenu.c`: `CreateMenu1` / `CreateMenu2` (sub-menu lists), `SetMagicMenu` / `SetItemMenu` / `SetGuardMenu` / `SetMoveMenu` / `SetFusionMenu`,
  `CreateCursole` (cursor = common `Cursor` type 0, shadow 2 = additive flare, direction 8 = right, rotation on); `BCursole.c` (`Polling`: sideways
  bob `x - sin(phase) * 8`, phase 2 pi per second); `decomp/F/Cursor.c` (`Polling`: `angle += dt_ms * 0.5`, `SetVertex`: half height `h/2 * cos(angle)`).
* `ParamDisp.c` (digit sprites at `x - 24.0 / -15.2 / ...` = 8.8 px pitch from 11-texel columns -> 0.8 scale; HP colour thresholds `max >> 1` / `max >> 2`),
  `TargetInfo.c` (the `?????` rule: the ten-thousands glyph is blank and the digits are shown when the fighter is a party member or the monster's "defeated"
  library bit (`BtlSave + 0xdcf`, retail `+0xf63`) is set; otherwise column 11 = `?` for every digit), `ComboForm.c` (this is the *ground* ring / area
  marker drawn in world space with `BTL` textures 44..46 -- not a panel).
* Retail: `SH2US_BATTLE.BIN` `CreateMenu1` @ 0x61a010 has the same constants as the JP build (rows 26 apart, text at `(48, +2)`, cost right edge 217,
  page dots from `219 - (pages * 12 + 5)`, scroll area `(x + 48, w - 80)`); the window rect lives in BSS (`DAT_006e5e80`) -- its bottom edge was taken
  from the retail target-select capture (rows at 290 / 316 / 342 / 368 -> bottom 394).  `SetGuardMenu` @ 0x603640: two entries `GetRegDat(0x2a, 42 + i)` =
  `Block` / `Resist`.
* Art (`BTL_000`, dumped with `examples/btl_tex_dump`): entry 2 = `HP MP SP ?? 0123456789 - ?` strip (labels at columns 1 / 20 / 39, digits at
  `77 + 11 d`, `-` 188, `?` 199 -- `ParamDisp`: `0x4d + d * 0xb`), entry 4 = blue highlight capsule 255 x 24 (`CreateMenu1` sprite 4 over the cursor
  row), entry 5 = row strip (rows 1..27, transparent on the left), header capsule (rows 29..81) and the page-dot boxes (y 83, 18 / 13 wide), entry 31 =
  soft dot (cursor glow).  `CBattle + 0x4224 + 4 k` is the `JRCTex` of `BTL_000` entry k (so `+0x4238` = entry 5, `+0x4234` = entry 4).

## Measured on the retail captures (512 x 448 virtual)
| element | real | port before | now |
|---|---|---|---|
| header text `Attack` | glyph box 278..292, cursor centre ~284 | text y 274 (box 276), cursor 292 | text 276, cursor tip (44, 285) |
| `< Standard >` | 6 px above `Attack` (box 272..286); lavender chevrons at x 94..112 / 182..200 | flat triangles, same row | font `<` `>` at 99 / 187, text y 270 |
| carousel rows | 309 / 334 / 360, light-left gradient | dark only (UV cut at 64) | full strip UV (1,1,220,27) |
| target rows | 290 / 316 / 342 / 368 (pitch 26, 4 bars) | 298 + 25.5 i | `list_layout`: 394 - 104 |
| party gauges | Karin 371, Nicolai 396 (pitch 25) | 366 / 391 | `PARTY_BAR_Y` 396 |
| party names | right edge 321, glyph box 359..374 (Karin) | right edge 318, 3 px lower | right edge 326, text y = row y |
| party digits | 8.8 px pitch, 10.4 tall (0.8 x 11 x 13), right edge 373 | 10 px pitch, 13 tall, right edge 370 | 0.8 scale, right edge gauge x + 50 |
| low HP | red (175, 0, 0) at 1/25 | only at 0 | white > max/2, yellow > max/4, red |
| acting band | teal (11,121,116) -> navy (20,36,136), wedge from x 232 | bright cyan | darker teal / navy |
| plate frame | 294..434 x 52..118, flat black, grey rim | 290..438 x 49..118, grey gradient | flat fill + rim |
| plate text | name cap top 64, `HP` 88, digits from x 360 (`?????` 360..401), bar 337..432 @ 99 | 8 px higher, digits right-aligned at 420 | as real |
| turn cards | pitch 26, visible width 23 at y 60, first card on top; target mode: pitch 20 and the cards squeezed to 20/26 (2 px gaps stay) | pitch 26 / 18.5, later cards on top, no squeeze | pitch 26 / 20, `sx = step / 26`, drawn back to front |
| help strip | 407..435, text glyph box 413..429, alpha ~0x55 | 410..436, 0x70, box 417 | 407..436, 0x54, text y 411 |
| plate ornaments | the curl at the top-left corner and the same curl mirrored at the bottom-right | texture's right half (the JP corner piece) at the bottom right | mirrored curl at (405, 72) |
| font metrics | help line 282 px wide for 37 glyphs (matches the port) | -- | unchanged; `Revenant①` is 17 px wider in the port (the circled digit is a full-width glyph here) |

## Sub-menu pages (`HudList`, `hud::draw_list`)
* Four rows per page from `list_layout`, bottom edge 394, pitch 26, row strip UV (1, 1, 220, 27), label at (48, row + 2), the cost / quantity column
  right-aligned at 217 in the game font (`CreateMenu2` formats it as a `MenuText`), unaffordable rows greyed (`SetCSA(2)`), the cursor row under the
  blue highlight capsule (entry 4, alpha 0x2c), page dots from `219 - (pages * 12 + 5)` (18 / 13 wide boxes of entry 5 at y 83), up / down scroll marks
  when there are more than four entries, the category name on a highlight capsule 30 px above the list.
* The same list draws the target pages (enemies, allies for items / healing magic, partners for Combo) -- the ally plate shows the portrait (`FI_%03d`)
  instead of the letter card and the HP digits right-aligned to column 5 (x 404).
* Defend opens `Block` / `Resist` (`ui::Page::Guard`, labels `BtlText::guard`); both report `MenuEvent::Guard`.
* Shots: `u3_item_menu.png`, `u3_skill_menu.png` (Sword Arts, 3 pages), `u3_guard_menu.png`, `u3_ally_target.png`, `u3_link_target.png`,
  `u3_combo_form.png`; crest magic and Fusion only exist for Yuri, so `u3_magic_menu.png` / `u3_fusion_menu.png` / `u3_magic_target.png` come from the
  JP demo disc (its `BTL_000` has only four textures: the turn strip there is the demo's teal glow boxes and the cursor glow falls back to a flat
  additive block).

## Evidence (`screens/battle_ui/`)
`u3_command_menu.png`, `u3_target_select.png` (real capture on the left), `u3_item_menu.png`, `u3_ally_target.png` (Thera Leaf on Karin: portrait
plate with the HP digits), `u3_guard_menu.png` (Block / Resist), `u3_skill_menu.png` (Nicolai's White Magic: Hail 6 / Rage 10 / Blaze 32),
`u3_skill_target.png`, `u3_combo_form.png` (Nicolai + Karin linked; the blue crest card in the turn strip is the combo marker of the turn-strip agent),
`u3_jp_magic_menu.png` (crest magic, two entries), `u3_jp_magic_target.png` (ally plate), `u3_jp_fusion_menu.png` (the demo's fusion name is a raw
SJIS escape in the data, not a rendering problem), `u3_jp_link_target.png`, `u3_jp_combo_form.png`.  Port shots: `SH2_SCREEN=native`, dev driver
`SH2_BATTLE_CMDS=attack,item,magic,guard,link,attack --us` (retail) and `magic,fusion,link,attack` (JP demo), composed with the scratchpad's
`u3_compose.py` (real left when a capture exists, otherwise "no capture yet").

## Still approximate / open
* Sub-menu pages (magic / skills / items / fusion / defend): layout from `CreateMenu1` (rows, pitch, cost column, dots, scroll marks) but no retail capture
  yet -- the category capsule above the list and the hidden main window are a guess (the real menu animates windows with `SetWindowMove`).
* Cursor glow and arrow shape: a dark triangle + additive soft dot tuned to the capture; the real one is the common menu cursor texture (type 0, BSS table
  `DAT_004217a8`) with a `MenuFlare` trail.
* Turn cards: the retail cards read pinker / paler (party card interior (175,154,141) vs the port's (217,180,157) before the last tint change);
  tints are (0x78,0x6c,0x68) / (0x68,0x62,0x60) at alpha 0x4c now, not re-photographed.
* Scroll marks are lavender triangles (the common `ScrollMark` art is not loaded in battle).
* Per-entry help text of spells / items (the real `SetNoteWindow` shows the spell description) -- the port shows the category note.
* `Resist` defend variant is accepted but acts as `Block`.
* Running-combo panel (`draw_combo`): chain members on short row bars at the right edge; no capture.
* Run Away: no confirmation page exists in `SetMainMenu` (code 10 is reported directly); nothing was added.
* Cursor flip: `Cursor::Polling` adds `dt_ms * 0.5` degrees per frame (8.3 deg at 60 Hz, a flip every 0.7 s), so a still can catch the arrow edge-on
  (the dark line in `u3_command_menu.png`); the glow stays.  If the live game turns out to pulse slower, lower the rate in `hud::cursor`.
* The dev driver gives a sub-menu up after 400 ticks when every entry refuses (Karin's Sword Arts all cost more than her 15 MP) and moves on.
* `Revenant①`: the circled digit is a full-width glyph here (84 px vs 67 px for the real text); the retail font's half-width circled numbers are not
  mapped by `sh2_menu::sjis`.

## Tests (2026-10-10, end of the pass)
* `cargo test -p sh2_battle -- ui:: hud::tests::` 9 passed (`list_pages_hang_from_the_window_bottom`, `hp_digits_turn_yellow_then_red`,
  `guard_opens_block_resist`, the existing menu flows, the real JP / US text tables).
* `cargo test --workspace`: every other crate green; `sh2_battle` 108 passed / 7 failed, all seven in `hud_hits::tests` (U1) and
  `hud_result::tests` (U2), which were still being written while this pass ended (their test file did not even compile for a while).

## Live retune (2026-10-10, against `screens/battle_live/*_512.png`)
Measured with PIL on the 512 x 448 resamples (colour bounding boxes); every number below is virtual pixels.

| capture | what differed from the port | change |
|---|---|---|
| `01_command_menu_c` | the root menu is a *list*, not a carousel: `Attack` stays in the capsule (text box 278..292) and the cursor walks down the rows (`01_b`: cursor on `White Magic` at y 320..324 glow, the `< >` chevrons disappear); rows' text boxes 313 / 339 / 365 (pitch 26, not 25.5); page dots at (201, 399), the down mark (lavender (155,163,194)) at x 128..142, y 395..409 | `HudMain` (all entries + cursor), `draw_main`: page 0 = capsule + 3 rows at 309 / 335 / 361 with the cursor on the row, chevrons only while the cursor is on `Attack`, dots (201, 399), mark (135, 395) |
| `04h` page 2 | rows `Combo` / `Run Away` at 282 / 308 (text boxes 286 / 312), dots 386..392, up mark (135, 250) | later pages are plain `draw_list` pages (bottom 394 with the dots row -> top 282), up mark at `top - 34` |
| `04a` White Magic, `04b` Items, `04c` Defend | category capsule 244..266 (entry 4 at a low alpha: (121,139,141) mid-grey-blue), title glyphs 249..265 starting x 40; row text boxes `Cure` 295..309 (row 290 + 5); cost right edge ~214; the help line is the entry's description (`Restores small amount of HP to one ally.`, `Restores 75 HP.`, `Reduces damage taken.`) | capsule at `top - 46` alpha 0x58, title at (40, top - 43); row text at `row + 3`; `BtlText::{item_help, magic_help, skill_help}` from `sshmes` kinds 0x1c / 0x21 / 0x22 (`BtlMenu::note` per entry) |
| `04e` / `04f` ally target | plate rim 294..411 x 52..118 (right edge = name right + 20; `Revenant①` -> 434), portrait 305..339 x 63..105, name box 66..80, `HP` 88, digits right edge 401, gauge 339..401 @ 99..103 with a light cap at 402; dark blue arrow over the ally; the party panel shows the acting row plus the targeted row; the target's Turn Priority cards outlined green (21,177,130) | `draw_plate`: width from the name, portrait (305, 63, 34 x 42), digits 357 + 5 columns, 62 px gauge + cap, blue / red arrow 16 x 24 (`04g`: red (183,31,26), x 248..263, y 157..180); `HudTurn.outline` = card silhouette drawn 1.5 px larger (`OUTLINE_ALLY` / `OUTLINE_ENEMY` (188,24,20)); `v.party.retain(acting || target)` |
| `04g`, `04j` enemy target | enemy cards outlined red; `HP ?????` digits 360..401 | same outline path; digits anchored at 357 |
| `06c`, `06d` enemy turn | only the Turn Priority plate is drawn (no party panel / menu); the big disc shows the enemy letter in red (129,31,17) on an orange glow; its cards outlined red; `06c` catches the plate still sliding (light y 0..68 vs 28..100) | `show_plate` / `show_party` / `show_menu` from the command phase + actor side; red `BIGLETTERS` tint + additive glow; outline on the acting enemy's cards |
| `06a` 0 HP / `04d` | `HP 0` red, Nicolai `12 / 38` yellow, `8` red | already `hp_colour` (half / quarter thresholds) -- confirmed |
| `07h`..`07k`, `07e` slide-in | Turn Priority enters from above, the party panel from the right (both ~0.04 / 0.13 s at 2250 px/s), the command window from the left ~0.3 s later; nothing during the ring (`01a..01m`) or the actions | `BattleRuntime.hud_since` (set by `draw_battle_ui` while `phase == Command && !hud_hidden && ring.is_none()`), `hud::slide()` offsets (`SLIDE_TURN` 96, `SLIDE_PARTY` 300, `SLIDE_MENU` 240, `MENU_DELAY` 0.3), the help strip does not slide |
| `04i` combo page | header `Combo`, partner list, help `Select character to join with in Combo Mode.`, partner cards green; the camera goes top-down and a blue marker hangs over the partner (3D, not mine) | help string + green outline + the ally plate / blue arrow; the camera is not touched |
| `04j` Blessed Light | orange translucent AoE cylinder on the ground (x 168..340, y 100..329) with red markers over all three enemies | **not implemented** (world-space marker; the HUD layer has no depth) -- noted for the effects / camera owner |

Second pass on the same captures: the `Combo` partner page is a titled list (`Combo` capsule + partner rows, no target plate, blue arrow only);
Turn Priority card tints desaturated to the live pink-grey ((151,127,118) party / (146,105,98) letter cards: `CARDS` (0x5a,0x52,0x54), `LETTERS`
(0x4c,0x46,0x48) at alpha 0x4a); the enemy-turn plate stays for 72 ticks from the turn start (the port's enemy `Command` phase is a single tick);
the help strip appears once the window has finished sliding (`07j` shows none); `menu_slide_in` / `hud_slide_in` / `enemy_turn` shot points.
U2's `hud_result` test built `BtlText` with a struct literal -- changed to `..Default::default()` so new text fields do not break it.

Third pass: Defend entry help lines are table 43 rows 41 / 42 (`Reduces damage taken.` / `Stand your ground and resist the attack.`,
`BtlText::guard_notes`); the Turn Priority strip compresses only on enemy target pages (`04g` / `04j` pitch 20; `04e` / `04f` / `04i` keep 26).
`cargo test -p sh2_battle`: 115 passed.

Still open after the retune: the Attack-row cursor's exact glow texture (the live glow sits behind the arrow's back half), the `Revenant①` glyph width, the
sub-list dots' x for lists of more than one page (only the root menu's (201, 399) was captured), the running-combo strip (no capture of a running
combo; `04i` only covers the partner selection), the Run Away message window (U2), and the AoE cylinder above.

## Party variants / special pages (C1 captures `08a`..`19b`, 2026-10-10 evening)
Measured on the `_512` files:
* **3 / 4-row party panel** (`08a`, `19a`): SP gauges at y 321 / 346 / 371 / 396 -> pitch 25 (C1's 25.3 is the resample), stacked upward from the
  same bottom edge; already how `draw_party` lays rows out (`PARTY_BAR_Y` 396, `PARTY_PITCH` 25, n up to 4).  Fused member (`08h`): the row name
  and the Turn Priority portraits become the fusion monster's (`Vastitas`) -- `BattleRuntime.fused[fighter]` (set while `Phase::Fusion` runs from
  `battle.cmd.p44`), name from `ActionTables::fusion_names`, portrait `FI_<fusion CHR>` via `effects_bridge::fusion_chr` (FI_ files 0..79 loaded now).
* **Status icons** (`19b`): 20 x 23 at x 474, y = gauge y - 15 (icon bbox 474..493 x 358..375 on Gepetto's row), right of the SP value; drawn from
  U1's retail sheet (`hud_hits::ICON_FRAMES`, `HitArt.icons`) with the kind / frame of U1's per-fighter `IconState` (`rt.hits.icons`), so the panel
  cycles exactly like the 3D icon.  `HudParty.icons`.
* **Enemy flame marker** (`13a`): the orange flame (bbox 45..60 x 53..76) is `BTL_000` entry 21 (36 x 60 orange oval) drawn additively under the big
  red letter, breathing (+-8 %).
* **Photographed enemy plate** (`12d`): rim 294..483 x 52..139; `HP 17` / gauge 339..401 @ 99, `MP` label at y 109 with its gauge at 120, the class
  ring (414..442 x 96..122) with the element kanji (entry 12 ring + entry 11 kanji), a small portrait at 458..478 x 95..120 (drawn as the letter
  card -- no monster portrait art in the HUD bundles).  `HudTargetPlate.snapped = Some((mp, max_mp, element))`.
* **Snap Shot target** (`11f`): blue marker + green outline on an enemy -> `HudTargetPlate.blue`.
* **Aromatherapy second list** (`10n`): title strip 221..238 (18 px, entry 4 at alpha 0x50) + the chosen oil on the normal capsule 244..266; rows
  unchanged.  `HudList.subtitle` (D1's `String`, empty = single header).
* **Album** (`11d`), **Demon Morph** (`17d`), **Marionette** / **Manifestations** / **Muscle Arts** lists: plain titled lists with costs -- nothing
  new in the drawing, only D1's page data.
* **Tarot Card** (`10e`..`10k`): card backs 72 x 144 at a 120 px pitch (cards at x 165..237 / 285..356 / 401..464, y 150..291) scrolling under
  cyan markers at (256, 112) / (256, 318) and `(X):Confirm` at (292..361, 318); the flip edge-on at the centre; the result face at (192, 106)
  128 x 237 with the bottom help strip (`10h`); the ornate result window (`10k`) and the name windows are U2's `BMesWin`.  Art:
  `BTLDATA/TAROT/TC_%03d.BIN` (entries 0..3 card backs grey / beige / teal / purple, 4 the face, 5 `Special Card / Reverse`, 6 glow), loaded by
  `load_hud` on the retail disc (`BtlHud.tarot`, `tarot_back`).  `HudView.tarot = Some(HudTarot { cards, scroll, stage })`, `TarotStage::{Scroll,
  Flip(card, 0..1), Result { card, help }}` -- replaces the whole HUD while set.
* **Combo page with three partners** (`17m`), **root page two** (`17l`): the existing list / `draw_main` paths (verified against the captures).

### Data D1 should feed (`build_hud_view` maps `ui::Page` -> `HudMenu`)
* `Page::Aroma` / `Aroma2 { first }`: `HudList { title: "Aromatherapy", subtitle: <first oil name or empty>, rows (cost column only on the second
  list), cursor }`, help `Select Aroma Oil.` / the combination's description or `????`.
* Snap Shot target page: `HudTargetPlate.blue = true` (plus the green outline on the target's cards); a photographed monster: `snapped =
  Some((mp, max_mp, element))` and `hp_known` from the library.
* Tarot: `HudView.tarot` from the action state (card ids = `TC_` numbers, `scroll` in px, the stage); the port's Tarot action owner should drive it.
* Until then `SH2_BATTLE_HUD_DEMO=tarot_row|tarot_flip|tarot_result|aroma|album|snap|snapped|icons` overlays a provisional page on the live view
  (`hud::apply_demo`) and the dev driver photographs it as `demo_<name>` (evidence sheets `u3_demo_*.png`).

### Evidence (party variants / special pages)
`u3_p4_command_menu.png` (4-row panel vs `08a`), `u3_p4_link_target.png` (Combo with three partners vs `17m`), `u3_p4_enemy_turn.png` (flame
marker vs `13a`), `u3_p4_target_select.png`; provisional pages through `SH2_BATTLE_HUD_DEMO` on the 4-member party (`SH2_BATTLE_PARTY=0,5,3,4`):
`u3_demo_tarot_row.png` (vs `10e`), `u3_demo_tarot_result.png` (vs `10h`), `u3_demo_aroma.png` (vs `10n`), `u3_demo_snapped.png` (vs `12d`),
`u3_demo_snap.png` (vs `11f`), `u3_demo_icons.png` (vs `19b`), `u3_demo_album.png` (vs `11d`).  Differences left: the photographed plate's small
monster portrait is the letter card; the tarot row's scroll / flip timing and the card ids come from the (future) action state; the enemy flame
marker's exact breathing rate; the fused name / portrait path (`BattleRuntime.fused`) was not exercised on the retail party (no fusion available
to Karin / Nicolai; Yuri's fusion needs the save flags).
