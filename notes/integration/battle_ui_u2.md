# Battle UI pass U2 (2026-10-10): victory / message windows / game over / intro timing

Code: `port/crates/sh2_battle/src/hud_result.rs` (new), wired from `plugin.rs` (`Stage::Result / Defeat / Escaped` now carry the
`hud_result` sequences, `BattleRuntime::mes` message queue, `apply_seq_events`, `make_win_sequence`, `make_escape_sequence`,
`bonus_data`), `flow.rs` (`BattleEvent::EscapeFailed`), `ui.rs` (`BtlText::words` = raw `GetRegDat(0x2b, n)` table, `word(i)`),
`hud.rs` (drawing helpers made `pub(crate)`), `devdrive.rs` (sequence shots, `SH2_BATTLE_LOSE=1`, game-over drive),
`sh2_menu/src/plugin.rs` (retail game-over picture path / mask, stand-in text only without a picture).
Evidence: `screens/battle_ui/u2_*.png` (port, `SH2_SCREEN=native`, resampled to 512x448).  **No live capture exists yet**
(`screens/battle_live/INDEX.md`: PINE blocked), so everything below is derived from the decompiled code and the art; re-tune
against the captures when they arrive (open questions at the end).

## 1. What the real game does (retail, `SLUS_210.41` / `SH2US_BATTLE.BIN`)

### Victory (`Retail_CBattle_Phase15_Win`, 0x4958d0; `BtlBonus` 0x38d840..; `BtlResult` 0x3969b0..)
| t (s) | step | what |
|---|---|---|
| 0 | 0..1 | wait for the fighters / sounds, result BGM `ReadEntry`, battle BGM fade 500 ms, the win effect (`pBtlResult`, `EffectNext`) |
| 0.5 | 3 | party re-formed around the actor (centre, others at +-(radius+3)), `MakeResultTrophy(0)`, `ShowAllHitInfo`, **`SetWinCamera1(actor)`** |
| 0.5 | 4 | **`ParamClose` / `TurnOrderClose`** (party panel + turn strip slide out), result BGM `IOPEntry`, **`SetBtlMessage(0x69)`** = `GetRegDat(0x2b,105)` `"%i17：Skip"` in message kind 4 at (288, 312.8), owner-closed |
| 0.7 | 5 | 0.2 s later: **win pose motion 0x33** + the win voice (`DataReadEntry(0xc, 0x13, id*100 + rand%10)`); `ComboForm`/`ParamDisp`/`TurnOrderDisp` destroyed once closed |
| pose end / confirm | nCmd0 0 -> 1 | `new BtlBonus` (0x49c bytes) -- the **`Battle Bonus / You Get!` panel** over the 3D scene (OT layer 0xc); a press sets its skip flag |
| | nCmd0 1 | wait until `BtlBonus` reaches phase 4 (its fade-out), friendship +10 between the survivors, phase 0x17 End -> `BtlSocket` state 4 -> **6 `new BtlResult`** (the post-battle result screen, main executable) -> 7 BGM fade -> 8 `cbBattle(0)` -> field |

`BtlBonus::Polling` (0x38e800): phase 1 alpha 0 -> 1 at 2/s (0.5 s); phase 2 one bonus row every 0.25 s with SE 0x3002 (an empty
list still spends one 0.25 s step after the 0.25 s step phase 1 left pending); phase 3 hold **4 s or confirm**, then
`BtlFader::SetMode(1.0, 3, 0)` (screen to black); phase 4 alpha 1 -> 0 at 2/s, then the object deletes itself.
Bonus rows (retail ctor): kinds 0..6 = `Max Hit Number: %s Hits` (0x2b 314), `Max Combo Number: %s Times` (315),
`Enemy Action Number: %s Turn(s)` (316), `No-Damage Victory` (318), `All Berserk Victory` (319), `Ring No-Miss Victory` (320),
`Ring Perfect Victory` (321); value column `Exp.`/`Cash.`/`Soul.` (322..324) `+ value * BtlSocket+0x6aa/0x6ac/0x6ae %` or an item
(`"%%i%d%s"` kind-icon + name).  Rows come from `BtlSocket+0x556..` ("Pit Fight Conditions" 325); normal fights have none in the
port (left empty: `BonusData::rows`).

`BtlBonus::MakePacket` (0x38f620, GIF packets decoded in `scratchpad/us_bonus_makepacket.c`): all coordinates below are the real
ones (GS 12.4 coordinates, x offset 1792, y offset 1824 = 2048 - 224):
* panel quad **x 43..470**, `h = rows*24 (+37 if rows)`, `top = 224 - ((h+194)>>1)`, `bottom = top + 1 + (h+193)`; vertex colours
  (0x41,0x41,0x4e) top -> (0x0a,0x08,0x0a) bottom, alpha 0.6 (76.8/128).
* ornaments = `BTL_002` entry 3 (96x112): line (1,70 38x7) stretched to (70,top-5 101x7), (343,top-5), (71,bottom-3 372x7);
  verticals (0,78 14x24) at x 31 / 467 (mirrored) from top+27 to bottom-49; swirls (0,0 88x29) at (169,top-17) + mirrored at
  (255,top-17); corners (0,29 48x27) at (22,top-12) / (442,top-12 mirrored), (0,56 26x14) at (22,top+13) / (464,top+13), bottom
  (48,29 42x63) at (29,bottom-52) / (441,bottom-52 mirrored).
* titles = entry 4: `Battle Bonus` (0,0 142x23) at (185, top+16) **only with bonus rows**; `You Get!` (0,24 93x23) at (209, yg)
  with `yg = top + h + 16`.
* separators (light purple 0x82,0x7d,0x96, bright in the middle 139..373, transparent at 71 / 441): bonus rows at top+44+24i
  (4 px for the first, 2 px after), one above the totals at yg+27 (4 px).
* labels = entry 5 strip, **vertex colour (0x41,0x3f,0x4b)**: `Exp.` (0,0 41x25) at (64, yg+37), `Cash.` (41,0 52x22) at (192, yg+37),
  `Soul.` (93,0 48x22) at (331, yg+37) only when the Soul system is unlocked (`BtlSaveDat+3 & 4`), otherwise `Exp.`/`Cash.` move
  **64 px right**; `Item.` (141,0 47x22) at (54, yg+59).
* digits = entry 5 (d*13, 25, 13x22), colour 0x55 grey, 6 slots of 11 px: Exp. from x 113, Cash. from 252, Soul. from 371 (+64
  without Soul), leading zeros hidden.
* items (`WinCreate`): two columns at x 103 / 288, rows of 22 px from yg+61, `%2d` counts right-aligned at 271 / 456, text
  `"%%i%d%s"` (kind icon + name -- the icon is not drawn yet); no item -> `GetRegDat(0x2a, 50)` = `None`.
* outcome bits != 0 (escape): the magic-circle backdrop (entry 2) under the panel and `GetRegDat(0x2b, 104)` `"%i17：End"` at
  `(512 - (w + 12.8), 394)`.

`BtlResult` (JP `decomp/H/BtlResult.c`, the retail `WinCreate` is the same size and uses the same `BTL_002` entries, so the JP
layout was used with the retail entry numbers): windows open with `Open(.., 0x14d)` = 333 ms (0, 1 and the first PC window at once,
the next PC windows one per tick); phase 2 waits 0.5 s (or confirm), then per tick `rate = max(13, total/60)`: the **`You Get!`
counters count DOWN**, the PC EXP and the party cash count UP; a level crossing plays SE 0x1003 and starts the `Level Up!` flip
(angle 2 pi, `theta -= theta/4` per tick, width `104 * cos(theta)`); confirm jumps to the end; when nothing moves (and SE 0x3000
ended) the drops are applied, windows close (333 ms), `BtlFader::SetMode(0, 1, 0)`.  Layout: backdrop entry 2 full screen; totals
panel (361,54)-(492,196) with the entry-3 ornaments, bar (361,92 131x6, entry 31), `You Get!` (376,63), `Exp.` (379,106) /
`Cash.` (368,133) / `Soul.` (372,159) with the 13 px digits at 420 + 11k (soul 442 + 11k); party `Cash` logo (348,369, entry 10) +
18 px outlined digits (entry 11) at 391,401,[,406],416,426,436,[,441],451,461,471; prompt icon (450,394) + text (467,394); one
360x45 window per PC at y = 42 + 44k: grey bands (0x28 -> 0x5a), highlight (262..348, 9..19), portrait entry 12+pc (0,0 80x36)
at (6,2), name (128,2), `LEVEL` (84,3) + 12 px digits (99/109,15), `HP` (125,21) digits 141.. `/` 165 max 173.., `MP` (204,21)
220../244/252.., `SP` (283,21) 299.., `NEXT` (269,3) digits 299..331 (`-` at the cap), gauges (140/219/298, 32), `Level Up!`
(entry 4 (0,48 104x25)) flipping around x 55 at y 20.

### Battle messages (`BMesWin::Create`, retail `CBattle::SetBtlMessage` 0x672080)
Kinds: 0 centre (256,224), 1 top centre (y 16), 2 top right `x = 512 - (w + 20.8)`, 3 = kind 2 with `w >= 128` and centred rows,
4 `(288, 312.8)`; rows 20 px; `MenuWindow` style 7 (`MenuWindowCompact`), open/close `0x85` = 133 ms; close rules 1 any face
button, 2 after 2 s, 3 either, 0 owner (`SetMesWinClose`).  Retail ids -> `GetRegDat(0x2b, id)`: **0x146 raw string kind 3,
owner-closed = the action name** (`EffectFunc` / ring skill: magic, skills, items; plain weapon attacks post nothing);
0x6a/0x6b ambush (106/107, kind 0, 2 s or button); 0x6c/0x6d combo chance (108/109, kind 2, owner); 0x74/0x75 ran away
(116/117, kind 0; 0x75 owner-closed); 0x76 `Couldn't get away!` (118, kind 0, 2 s or button); 0x77 (119) no escape; 0x69/0x68/0x67
`Skip`/`End`/`Confirm` prompts (kind 4 / 4 / 5); 0x78 cannot act (120); 0x86..0x95 stat changes (kind 0, any button).
There is **no** "X is defending" message.

### Defeat (`Retail_CBattle_Phase16_Lose`, 0x499b40)
Battle BGM fade 1000 ms; at 0.5 s `SetLoseCamera1`, `MakeResultTrophy(1)`; `ParamClose` / `TurnOrderClose`; lose motions
around 1 s; at 3 s `BtlFader::SetHoldFade(1.0, 3)` (black) -> phase 0x17 -> `cbBattleA` outcome 1 -> `SSHSys` request 0x30 ->
`GameOver`.  Nothing is drawn on top (no panel, no text).
Retail `GameOverScene::GetReady` (0x3e4160): picture = MENU section short 0x29c, negative -> random among the bits of the u16 at
0x29e; the resource string of the US `GAMEOVER.MSD` is `MENU/IMG/EX/GO_%03d.TEX` (20 pictures, 512x448, the words are in the
picture).  The retail scene also has a `GameOverRetailMenu` (4 rows: continue / load / title) -- **not ported** (the port keeps
the JP `Load?` question / straight return to the title).

### Escape (`CBattle` phase 8)
Success: `SetBtlMessage(0x75)` (`%s and the others ran away!`, kind 0, owner) while the party runs off, then `new BtlBonus`
(outcome bits set: backdrop + `End` prompt) -> `BtlSocket` state 5 -> field.  Failure: 0x76 `Couldn't get away!`.

### Intro HUD timing (JP `CBattle::Polling` phase 1/2/4, same in retail)
Phase 1 step 6: the ambush message (kind 0, close 3) waits until it is gone; phase 2 step 100: `TurnOrderDisp` created;
phase 4 (`BtlMenuFunc`): **`ParamOpen` + `TurnOrderOpen` together with the first command menu** (`ParamOpen` sets the slide
offset to 300 px, `TurnOrderOpen` to -96 px; `Polling` moves them at 37.5*60 px/s = ~0.13 s) and `SetBtlMessage(0x6c)` when a
combo is possible.

## 2. What the port does now
* `Stage::Result`: `WinSequence` -- 0.5 s: camera (`desired_camera` honours `camera_ready`), HUD hidden (`rt.hud_hidden`),
  `Skip` prompt (kind 4, icon + text); 0.7 s: `rt.win_pose` (the motion itself is not played: models are not mine); 3 s later or
  confirm: `BonusPanel` with the retail geometry and timing; fade to black (30 frames) with its fade-out; 0.3 s black;
  `ResultScreen` (uncover at once, 333 ms open, 0.5 s wait, count-down / count-up at `max(13, total/60)` per tick, level-up
  flip + SE 0x1003, auto close) -> `finish(Win)`.
* `Stage::Defeat`: `LoseSequence` -- camera + HUD close at 0.5 s, fade at 3.5 s, `cbBattle(Lose)` at 4.1 s -> `GameOver`
  (retail picture path + save mask fixed in `sh2_menu`; `GAME OVER` stand-in text only without a picture).
* `Stage::Escaped`: `EscapeSequence` -- run-away message (2.1 s), HUD hidden, `BonusPanel { escaped: true }`, finish.
* Messages: `MesQueue` on the HUD layer; action names (kind 3, owner, closed at `ActionDone` / menu submit), ambush message at
  tick 1, combo chance (kind 2) while the menu is open, `Couldn't get away!` on `BattleEvent::EscapeFailed`.  The old
  `ui::draw_banner` / stand-in panels only draw when the real art is missing.
* Strings: `BtlText::word(i)` = `GetRegDat(0x2b, i)` on the retail disc, `hud_result::msg::fallback` (the US texts) on the demo.
* Dev: `SH2_BATTLE_LOSE=1` (defeat -> game over -> title), `SH2_BATTLE_CMDS=run` (escape); shots `win_pose`, `battle_bonus`,
  `result_count`, `result_end`, `defeat`, `escape_message`, `escape_panel`, `game_over`.
* Tests (`hud_result::tests`): panel geometry (`top`/`bottom`/`yg` for 0 and 2 rows), the 0.5 / 0.5 / 4 / 0.5 s timeline, row
  reveal sounds, confirm skip, count rates, a full count-up with a level-up, message timeouts / button close / placement, the
  win-sequence event order, the `%i17` prompt escape.

## 3. Approximate / open (needs the live captures)
* **Message window frame**: a hand-drawn translucent capsule (alpha 0x60) instead of `MenuWindowCompact` (CMNMENU attach 14,
  sprite records 0x18..0x1c; `sh2_field::cmd_common::compact_frame` has the real pieces but `sh2_field` depends on `sh2_battle`).
  Also unverified: whether the retail action name really sits top right (JP kind 3 / retail 0x146 say so).
* **Prompt icon**: `%i17` is drawn as the cross button of `BTL_002` entry 33 on the retail disc (circle on the demo) -- the icon
  table index 17 was not resolved.
* **Win pose length** 3 s stands in for the motion end; the pose motion (0x33) and the formation shuffle are not played (models).
* **Label tint**: the `Exp./Cash./Soul./Item.` strip is drawn with the packet's vertex colour (0x41,0x3f,0x4b) = ~50 % grey;
  a capture should confirm the real brightness (TFX modulate assumed).
* **BtlResult layout** is the JP `WinCreate` (the retail copy was not decoded; same size, same art); the `/` and `-` glyph
  columns of entry 7 and the 12.8 px digit pitch of entry 8 are read off the sheets; the window open effect is an alpha ramp
  (`Open(.., 0x14d)` style unknown); the cursor arrow (entry 32) and the Soul Energy meter (`CmdSoulEnergy`, savedata flag) are not
  drawn; HP/MP/SP show the post-battle values (the real screen recomputes max values on each level crossing).
* **Battle Bonus rows** are never generated (which fights produce them -- Pit Fights? -- and `BtlSocket+0x6aa..` percentages
  are not ported).
* **Intro slide-in** of the turn strip / party panel (300 px / -96 px at 2250 px/s) is not animated (HUD geometry is U3's).
* **Defeat camera**: `CamRequest::Lose` lands in a wall in the dev stage (`u2_defeat.png`) -- camera agent.
* **Game over menu**: the retail 4-row `GameOverRetailMenu` is not ported.
* Item names on the panel lack the `%i<kind>` icon prefix.

## 4. Live retune (captures of 2026-10-10 12:27-13:05, `screens/battle_live/*_512.png`, measured with PIL)
Side-by-sides: `screens/battle_ui/u2_sbs_*.png` (left = live, right = port, both 512x448).

| capture | what differed | change |
|---|---|---|
| `03a/03b_win_pose_skip_prompt` | the prompt is `[x]:Skip` at the bottom right (icon x 444..458, text 460..490, y 392..402), not at the JP (288, 312.8) | `MesKind::Prompt` = `x = 512 - (w + 12.8)`, y 392, drawn without a frame, icon in front, colon kept (`message()` turns the `%i17：` escape into `:`) |
| `03c_you_get_panel_slide_in` | the frame slides in from the right (half visible) | **not done**: the port fades the panel in (`BtlBonus::Polling` alpha ramp); the slide is a retail addition -- open |
| `03d_battle_bonus_you_get_panel` | panel rails at x 34 / 478, top line y 123, bottom line y ~320 (= decoded geometry, top 127 / bottom 321 OK); the vertical rails run from the top line to 24 px above the bottom; `You Get!` is **purple** (160,102,233) script at x 211..298, y 145..162 (decoded 209 / yg 143 OK); separator y 170..173 (OK); `Exp.` 133 / `2` ends 237 / `Cash.` 262 / `20` ends 378 / `Item.` 55 / icon 107 + name 120 / count ends 267 (decoded columns OK within the glyph padding); the `Skip` prompt is still up while the panel shows | rails lengthened; purple title sheet built from the gold one (`load_art` -> `BtlHud::tex2[1004]`, the retail CLUT swap was not found); item names offset by the 16 px kind-icon slot; the `Skip` prompt now closes with the panel's fade-out |
| `03e_battle_bonus_panel_settled_slot22` | this capture is in fact the result screen (same as 03f) | -- |
| `03f_result_screen_you_get_end_prompt` | the retail `BtlResult` layout is not the JP one: PC windows at y 44 + 44 k are 30 px bands with a diagonal right edge ((337,0) -> (200,30)), arrow (7..19, +17), portrait 27..88, `LEVEL` (85,+4) + small level digit ending 118 (+16), name (127,+2), `HP` (126,+20) digits 147..163 / 165 / 173..197 (+18), `MP` (203,+20), `SP` (282,+20), `NEXT` (270,+4) on a dark-blue box, value ending 337, gauges HP 143..198 / MP 220..277 / SP 298..318 at +29; `You Get!` window (350..495, 47..159): title 378..465 / 65..82, separator 94..96, `Exp.` 382 / value ends 487 (y 125..140), `Cash.` 370 (y 150..165), no Soul row; `Cash` logo 352..389 / 372..389 with the total ending at 480; `[x]:End` at 460 / 394 | `ResultScreen::draw` / `draw_pc` rewritten to these numbers; the prompt is `End` (0x2b 104) |
| `05a/05b_run_away_message` | centred capsule: text 124..365 / 216..233, frame 110..380 / 208..240, fill ~0.9 black, grey-blue 2 px rim with pointed ends, the confirm icon after the text; then the **scene fades to black under the message** (05b) before the panel | `MesWin::draw` frame = text bbox +-14 x, 27 px tall, fill alpha 0x74, rim (0x52,0x52,0x60); kind-0 windows get the trailing icon; `EscapeSequence`: fade at 1.0 s, message closed + uncover + panel at 2.2 s |
| `05c/05d_spell_name_window_cure` | `Cure` window top right: text 412..441 / 19..33, frame 348..507 / 13..40 (= kind 3, min 128 wide, centred text) -- matches; **no window for enemy attacks, the Statue's spell or the party's Attack** | action-name window only for a party actor's non-Attack action (`begin_action_fx`) |
| `07a_game_over` | full-screen picture (`MENU/IMG/EX/GO_000.TEX`) with `[x]: Skip` at icon 386..393 / text 398..442 / y 396..413 | prompt added to the GameOver draw (text; the icon is a stand-in glyph) |
| `07b..07k` intro | first frame T+2.2 s after the request, characters fade in T+3.9, camera pan T+4.4, HUD slide-in (Turn Priority from the top-left, party panel from the right) T+4.7, command menu from the left ~0.3 s later, complete ~T+5.0; the same slide-in at every party turn start (07e) and the party panel is closed during enemy turns (06c) | `Stage::Intro(2.5)`; `ParamOpen` 0.3 s before the menu (`BattleRuntime::{panel_open, hud_open_t, menu_open_t}` exposed for U3's slide; the panel closes on enemy turns); the slide animation itself is U3's (hud.rs) |
Not captured (code-derived behaviour kept): count-up frames, `Level Up!`, ambush message, the fade frames before Game Over, the bonus-row section.

Status after the retune: `cargo test -p sh2_battle` green (115 tests, 10 in `hud_result`); port shots re-taken on BBG 077
(`SH2_BATTLE_DEMO=2 SH2_BATTLE_BG=77 --us`, `SH2_SCREEN=native`).  Still open from the captures: the `You Get!` panel slide-in from the
right (03c), the exact `MenuWindowCompact` rim pieces (hand-drawn quads), the game-over prompt uses a stand-in glyph for the
button, the item-kind icon on the item row, and the HUD / menu slide-in animation (U3 -- `BattleRuntime::{hud_open_t, menu_open_t,
panel_open}` carry the timings).

## 5. C1 captures (08_..19_): message rules, Tarot / Snap Shot, transformation burst
* `18a_enemy_skill_name_window_gale_spin`: the Revenant's skill gets the same top-right name window as the party's `Cure`
  (frame 350..506 / 13..40 = kind 3); `10h`: the Tarot name window grows with its text ('"High Priestess" Card', frame 314..506).
  Rule now in `begin_action_fx`: **every non-Attack action of anyone** posts the name (kind 3, owner-closed); plain attacks never.
  Open: C0's 02k/02l saw no window for the Statue's spell (0.6 s sampling) -- the retail `EffectFunc` posts 0x146 on all its paths,
  so the port shows it.
* Tarot Card (`10d..10l`): name window "Tarot Card" (kind 3) while the cards scroll, `[x]:Confirm` prompt (kind 4 text, 0x2b 103),
  after the flip the name window becomes '"<card>" Card' (0x2b 130..133 formats) and the **help strip** shows the effect text; after
  the effect a **centred ornate result window** (`10k`: dark panel x 48..465, y 320..398, text at (66, 343), confirm icon bottom
  right) = retail `SetBtlMessage(0xde)` -> `GetRegDat(0x2c, 0xde + card)` in **message kind 8**, close rule 1 (any face button).
  For D1's Tarot page: `MesKind::Ornate` (kind 8) + `MesClose::Button` via `rt.mes.post(..)`; the name window is the usual
  `MesKind::TopRightWide` / `MesClose::Owner` (post again with the card name after the flip); the effect text goes to the help
  line.  The frame art of kind 8 is approximated (dark fill + entry-3 corner pieces).
* Snap Shot (`11g..11k`): name window "Snap Shot", pose / tripod / flash, **no result message** (0.1 s sampling) -- nothing to post.
* Fusion / Demon Morph burst (`08d..08g`, `17e..17j`): no HUD, pose, purple aura, **full white flash**, model swap in the magic
  circle, then the fused character's menu immediately.  The white-out is the battle's `BtlFader` in hold mode (`SetHoldFade(1.0, 3)`
  with a white rgba -- the same object the win / lose sequences drive to black with `SetMode(1.0, 3, 0)` / `SetHoldFade`), not an
  effect-script sprite; in the port that is `BattleRuntime::cover` (black fades, `apply_seq_events` FadeOut/Uncover) and the
  existing `rt.flash` white flash -- D1 can reuse `rt.flash` (decays by itself) for the burst and `rt.cover` for held fades.
* Name-window frame re-measured against the port's `Cure` frame (`u2_sbs_spell_name.png`: port text 410..444 / 18..33 vs live
  412..441 / 19..33): the rim now sits 15 px beyond the row incl. the pointed ends and 3 px above / below (live 348..507 / 13..40).
