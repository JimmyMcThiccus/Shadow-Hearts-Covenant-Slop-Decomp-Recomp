# Battle UI pass U1 — ring HUD, damage numbers / hit counters, status icons (2026-10-10)

Scope: `port/crates/sh2_battle/src/hud_hits.rs` (new), surgical hooks in `plugin.rs` / `lib.rs` / `devdrive.rs`.  The gizmo ring in
`plugin.rs::draw_ring` is now only the fallback for a disc without `COMMON/JRING.BIN`.  Evidence: `screens/battle_ui/u1_*.png`
(port, `SH2_SCREEN=native`).  **No live retail capture of these states existed while this was written** (C0 blocked on PINE, see
`screens/battle_live/INDEX.md`): every layout below is taken from the decompiled classes and the art, not from a photograph.  Where
the retail overlay differs from the JP demo (texture indices, icon table, panel rows) the retail code (`SH2US_BATTLE.BIN`) was used.

## What is real (art + code)

### Font and colours (`HitInfo`, `TotalHitInfo`, `HitCntEff`)
* The italic battle font is `BTLDATA/BTL_000.BIN` entry 0 (288 x 256, PSMT4, one 96 entry CLUT = six 16 colour blocks).  The glyph table
  (73 cells `u0,v0,u1,v1`, 41 px rows) is at JP `0x651b90` / US `0x6e44e0` in the overlays and is byte identical (`hud_hits::GLYPHS`).
  `A..Z` 0..25, `a..z` 26..51, `0..9` 52..61, `! ? + - * % /` 62..68, `' . ,` 70..72.
* The colour is the GS `TEX0.CSA` block (CLUT entries `16*csa + j` with the CSM1 bit 3/4 swap): 0 blue, 1 white, 2 gold, 3 red, 4 green,
  5 blue (`FontColor`, decoded by `decode_jrc_csa`).  `EffectMesCall` (JP CBattle.c:54256): damage on an **enemy = gold (2)**, on a **party
  member = red (3)**; `Miss` the other way round; `Critical` (type 2 spin-in) same colour as the number; status inflictions (type 5
  grow-in) red on a PC, blue (0) on an enemy; stat ups green (type 7), stat downs red/gold (type 8); heals green (assumed, the recovery
  branch of `EffectMesCall` was not read).
* Number scale = `1 + hits/50` (max 2) with `hits` = hits of the current action on that target (`BtlChr+0x510`).

### Motion (`HitInfo::Polling`, seconds at 60 Hz)
| type | use | motion | life |
|---|---|---|---|
| 0 | number | `y = (rise-64) * sin(min(t*4.19, pi/2))` -> rises 64 px | 0.5 s |
| 1 | `Miss` | same | 0.5 s |
| 2/3/4 | `Critical` / `Miss` / `Defeat` | spin `2pi -> 0` (`spin += -spin/4 * 30 dt`), `y = rise*(1 - spin/2pi)`, glyph width x cos(spin) | 0.5 s |
| 5/8 | status words, `MP -n` | per glyph grow-in from the baseline (`f = clamp(5t - 2(n-k)/n)`), `y = 2*rise*t` capped | 1.0 s |
| 6/7 | `STR +n` | rise + spin | 1.0 s |
Stacked texts: each next item is delayed 0.2 s and its line is 41 px lower (`fVar14 += 0.2`, `fVar15 += 41`).  Anchor = the model's box
centre projected (`chr+0x150 + chr+0x350`).  Layout: digits advance `(w-3)*scale`, text `(w-3)*scale` / 13 for a space, glyph height
`v1-v0-5` for types 0/1, the full cell for the others; centred on the anchor.

### Total hit panel (`TotalHitInfo`, retail `MakePacket` 0x518780) and the counter pop (`HitCntEff`)
* One panel per target at x 16, y 128, the next one `sy*24+1` lower (`CBtlPAfter2::EntryDDisp`).  Frame = `BTL_000` entry 19 region
  (70,0)-(108,25) (demo: entry 16) drawn `38*sx x 25*sy`, scale 0.75 (approached at 10/s).  Card = enemy letter from entry 25 (36 x 23
  cells, A..D column 0 / E..H column 36, 24 px pitch) at `(x+sx, y)`; party members use a runtime texture indexed by `chr+0x5b2`
  (content unknown, the port scales the `FI_` portrait into the 36 x 23 card -- approximate).
* Rows from `x + 46*sx, y+1` in the font at 24 px (`scale = 24/(h-5)`): `<n>` gold + `Hit` blue(5), `-<total>` gold + `Damage` blue,
  `Combo` green + `+n` gold, then the status icons of the inflictions (19 x 23 from the icon sheet, pitch 20).  Glyph advance `(w-2)*s`,
  8*s per space and after each row.  Words: retail table 43 entries 99 `Hit`, 100 `Damage` (= `BtlText::mes(39/40)`).
* Lives 4 s after the last `Reset`, then collapses (`sy -> 0` at 10/s).  `HitCntEff`: the hit count in gold at the centre of the
  `Hit` number, scale `(min(3, n/25+1))*(t/0.2) + 1` shrinking over 0.2 s (2x -> 1x for the first hits, 4x for 50+).

### Status icons (`AbnIcon`, retail `MakePacket` 0x523b90, `IconFunc` 0x6a79f0, `GetIconList` 0x6a6f70)
* Sheet: retail `BTL_000` entry 39 (480 x 616, 48 x 56 cells, drawn from `(c*48+1, r*56+1)` 46 x 53); demo entry 57 (256 x 112, 50 px cells).
  Retail animation table `SH2US_BATTLE.BIN 0x6e3210` -> `hud_hits::ICON_FRAMES` (22 kinds, 0.1 s frames, loops).
* Kinds (retail bit order = word table 79..): 0 Poison, 1 D.Poison, 2 Paralysis, 3 Seal, 4 Petrify, 5 Panic, 6 MentalBreak, 7 Berserk
  (PC with SP 0), 8..16 the ring abnormalities (`STATUS_AUX` bits 0,1,2,3,5,6,7,9,10), 17/18 turn interval up/down, 19 record `R`.
* Billboard above the model: bottom edge at box centre + `r + sin(phase)/2` world units up (`r` = mean half extent, bob 1 Hz),
  4.6 wide x 5.3 tall (demo 5 x 5) times the fade; icons cycle every 2 s with a sine grow (0..0.25 s) / shrink (1.75..2 s); the object
  fades in/out at 4/s.  Only drawn for living fighters.  The party panel / target plate carry no icons in the code that was read
  (`ParamDisp` was not checked for icons).

### Judgement Ring (`JRing::MakePacket` / `MakeAreaPacket` / `MakeBarPacket`, SLPM main; `HitMes`)
* Art: `COMMON/JRING.BIN`: 0 = `Good!! Strike!! Perfect!! Miss!! 0..9 %` (224 x 80), 1 = the ring face (256 x 256), 2..5 = the face with the
  circle / cross / triangle / square glyph (combo flip, `e8` selects), 6 = `Combo Trial / Combo!! / Combo Miss!!`.
* Geometry: face = 34 vertex fan, radius `114*scale_y`, uv `(cos*114+128, -sin*114+128)/256`, colour 0x808080, alpha `scale_x*128`
  (the intro / outro fade); hit areas = pie wedges from the centre to radius `101*scale_y` in 11.25 deg steps, centre alpha 31/128, rim
  127/128, colours per area (step (0,a4,50), strike (e0,98,40) + tail (ff,20,18), modulate white / (20,c8,fa) / red), halved for passed
  areas; pointer = 1.5 px bar to radius `103*scale_y`, orange (ff,3f,0f) at the hub to cream (ff,ef,bf) at the tip, with a 9 frame
  trail fan (green 3f,ff,7f, alpha 8..64).  Rotation `rot` applied Z, then X, then Y (home -30 deg / +55 deg), camera at z = -512,
  `SetViewMatrix(512, 0.8, 0.9333)`: a unit ring is 91 x 106 virtual px before the tilt.  Centre `(cx, cy)` = `JRing+0x68` (256, 224).
* The retail ring shows **no prompt text** (the JP `Press O` stand-in stays JP only, `plugin.rs`).
* `HitMes`: the word at the pointer's rim position (`101*scale_y`), drifting outwards `3 - 5.5t` px/frame, flip-in about the vertical axis
  over 0.25 s, scale 0..1 in 0.2 s, alpha 1 from 0.2..0.7 s, gone at 0.9 s.  `Good!!` (0,0,75) green block 4, `Strike!!` (112,0,90)
  block 0, `Perfect!!` (0,24,98) block 0, `Miss!!` (112,24,70) block 2; modulate percentages as digits (x table JP 0x3f8980).

## Still approximate / open
* Everything above awaits a live capture: in particular the ring's tilt (the matrix order of `sceVu0RotMatrix*` was taken as
  `Ry*Rx*Rz`, a mirrored lean is possible), the alpha convention of the wedges (GS 127/128 = nearly opaque), and the exact box centre
  / `r` of the fighters (the port's `dims` height is still the 30 unit placeholder for the vertical extent).
* Heal numbers (green) and `Defeat`/stat-change texts are wired from what the port's events carry (`BattleEvent::Damage` only):
  `Critical`, `Miss`, number; status inflictions / MP damage / stat texts need events the battle flow does not emit yet
  (`HitFx::on_status` is ready for them).
* The PC card of the total hit panel (retail per-PC texture, `chr+0x5b2`) is a scaled portrait; the JP `TotalHitInfo` also drew a second
  outlined capsule, the retail one does not.
* `HitBar` / `HitArea` flashes of the ring and the shard animations (`CutJRing` / `CrackJRing`) are not drawn.
* Unconscious row appearance / enemy death fade (`NormalDeathEfct`) not touched.

## Evidence (`screens/battle_ui/`, port only -- no live frame existed)
* `u1_ring_phase.png` -- gizmo ring before vs the textured `JRING.BIN` ring now (`u1_ring_closeup.png` at 2x: inscription reads normally,
  orange strike area with its red tail, a second green step area, the pointer bar at 9 o'clock); `u1_ring_hit.png` -- `Good!!` after the press
  while the ring fades (END_OK shrinks `scale_x` = alpha in 0.25 s), and the intro at 30 ticks (mode 5: `scale_y` growing).
* `u1_damage_number.png` -- the old white stand-in digits vs the gold `HitInfo` number (36 px, rising) with the `[A] 1 Hit -17 Damage` panel and
  the `HitCntEff` pop; `u1_hit_panel.png` -- the panel 0.5 s later, and the `AbnIcon` poison billboards (`SH2_BATTLE_ICONS=1` forces a mask on
  every fighter; `SH2_BATTLE_HITDBG=1` logs the anchors once a second).
* `u1_font_blocks.png` (the font sheet in its six CLUT blocks with the glyph table overlaid), `u1_icon_sheet_grid.png` (retail icon sheet, 48 x 56
  grid), `u1_jring_textures.png` (`JRING.BIN`).
* Observation while photographing: the port's hit camera (`SetAttackCamera1`) often has the *target* outside the frame (the number and the
  weapon spark both sit at the target's projected box centre / head, e.g. at the top edge of `bt_07_weapon_hit`), because the attacker's
  run-up / the camera shot are not the live ones yet -- a camera / positions issue, not a HUD one.  The anchors follow the rendered model
  (`rt.actors`, PS2 -> Bevy flip), falling back to the formation slot.

## Hooks (shared files)
* `plugin.rs`: `BattleRuntime.hits: hud_hits::HitFx`; `consume_events` -> `hits.on_damage` / `new_action`; `battle_tick` -> `hits.tick`,
  `tick_icons` (masks from `Fighter.status`); `draw_battle_ui` -> textured ring + `HitMes` before `draw_hud`, `hits.draw` after it (the old
  `draw_floater` loop is the fallback without the font); `sync_battle_render` fills `hits.anchors`; `RingRun.mes` collects `JrEvent::HitMes`;
  the gizmo `draw_ring` returns early when `JRING.BIN` is loaded.  `devdrive.rs`: shots `judgement_ring_run` (75 ticks), `ring_hit`, `hit_panel`.
* Tests: `hud_hits::tests` (glyph table, number rise, spin settle, panel life, counter scale, icon mask / cycle, ring projection + CLUT swizzle).

## Test reconciliation (coordinator follow-up)
Six `hud_hits::tests` failed once the crate's test target compiled; all six were wrong *expectations*, the code follows the decompiled
source and was left unchanged: `HitCntEff` first-hit scale is `(1/25+1)*1+1 = 2.04` (not 2.0); the CSM1 CLUT swizzle swaps bits 3/4 so
`40 <-> 48` (the test had them fixed points); `TotalHitInfo` closes when `t >= 4.0` and 240 accumulated sixtieths land just under 4.0;
`HitInfo` spin decays by 0.875 per tick (0.13 rad left at 0.48 s, not < 0.1); glyph 52 (`0`) is the 22 px cell (115..137) -- I had
miscounted the row; retail poison icon frames loop every 0.6 s, so tick 40 is frame 0 again (frame 2 at 0.25 s).
The seventh assertion (`icons_cycle_every_two_seconds`, `obj == Some(2)` right after the last ailment is gone) exposed a real code
deviation: `CBattle::IconFunc` sets `AbnIcon+0x5c = 2` (fade out) in the same frame it clears `BtlChr+0x598`; `IconState::tick` did it
one frame later -- the code was fixed, the expectation kept.

## Live retune (captures `screens/battle_live/`, 2026-10-10 afternoon)
Measured in the `_512.png` files (and the 1440x1080 originals / 2.8125 x 2.4107 for sub-pixel checks) with `python3 -I` + PIL colour
bounding boxes.  Per capture: what the port did, what the live frame shows, what changed.

| capture | live | port before | change |
|---|---|---|---|
| `01a..01c` ring moving, `01f` intro, `01g` RUN frozen 70 deg | ring centred (341.33, 224) (`JRing+0x68`), rim bbox x 299..405, y 144..313 (106 x 169, leaning top-right), gold wedge area 1 + red strike, green area 2 + red strike, orange pointer line from the hub; **no HUD at all** (no turn plate / party panel / menu) | same art + same lean, ellipse 95 x 170 (`Ry(55) Rx(-30)` model: half extents 55 x 78 vs live 53 x 85 -- the rotation model holds), but centred (256, 224) with the full HUD still drawn | ring centre `(1024/3, 224)` set in `RingRun::start_areas_custom`; `draw_hud` skipped while `rt.ring` is live (`plugin.rs`, surgical); colours / pointer unchanged (they match) |
| `01d` ring miss text, `01h` hit + miss, `01m` Good!! | `Miss!!` red-orange left of the ring at centre height ((-80, +10) from the centre, pointer at the top; `01h` (-184, -14)), `Good!!` blue right of it ((+80, -10), pointer 70 deg); sprite size = the 70 x 24 / 75 x 24 cells at scale 1 | word at the pointer's rim point rotated like the ring (JP `HitMes::Initialize` reading) -> appeared under / above the ring | empirical retail placement: miss left (-80, +10), other grades right (+80, -10), outward drift kept; colours already matched (JRING texture 0 CLUT block 4 = blue, 2 = red-orange, 0 = gold) |
| `01e` ring fade | ring fades after the lap | `scale_x` = alpha fade (END states) | unchanged |
| `01i` seen from behind | the ring is a world billboard (mirrored after a camera cut) | screen-space billboard at the fixed centre | not reproduced (the port keeps the ring in screen space; a camera cut during the swing never happens in the port) |
| `01l` spell ring Cure, `01m` | one **blue** area (60, 60, 15) + red strike; `Cure` window top right | the port's flow starts no ring for spells (only `Phase::Attack`) | not reproducible yet: the spell ring must be started by the flow first (colour then = `AddStrikeArea` colour arg, live ~ (0x20,0xc8,0xfa)); the spell-name window is U2's |
| `02a`, `02b`, `02k`-`02m`, `02p` HitInfo panels on Karin / Nicolai | panel at x 14, text cell top y ~129 (`1Hit 5Damage`: yellow digits x 53..94, blue words to x 142, ink 10-11 px), portrait card 26 x 25 | same layout (frame + card at (16,128), rows from x 39+, cells 18 px) -- measured text span 108 px for 13 glyphs vs live 115 px for 12 glyphs | no change (sizes/positions within the resample tolerance; the US `TotalHitInfo` ctor / Polling were checked: 0.75 / 0.9 like the JP) |
| `02c`, `02g`, `02j` damage number | yellow `11` 18 x 20 px rising above the target (x 232..251, y 63..83), panel `1Hit 11Damage` | gold number 36 px cells rising 64 px over 0.5 s (bright ink 22 px for `19`) | no change (the US `HitInfo` ctor keeps scale 1.0; the live bright-ink height 20 vs 22 is the resample) |
| `02d` two panels stacked | second panel 13 px lower?? (INDEX) -- in the `_512` frame the two text rows are at y ~137 and ~157 | pitch `sy*24+1` = 19 px | no change |
| `02e`, `02o` panel persists into the next turn | yes, ~2+ s | 4 s after the last hit, then collapses | no change |
| `02f`, `02i` spell damage on Karin (red number, red `Defeat`) | red number on a party member; `Defeat` red | red number (block 3) | `Defeat` added (see 06b) |
| `02h` 2Hit 18Damage + blue `Defeat` on the dying enemy | panel accumulates (`2Hit 18Damage`), `Defeat` blue (block 0) at the enemy (x 143..242, y 166..210) | panel accumulated already; no `Defeat` text | `HitFx::on_defeat` on `BattleEvent::Defeated`: `HitInfo` type 4 spin-in, blue on enemies / red on party members, 0.2 s delay |
| `02n` heal `HP +16`, `02o` | green `HP +16` floating (x 215..318, y 205..225) + panel row `HP` (blue) `+16` (yellow) | a green bare number, no panel row | `HP +n` text (type 7: rise + spin, green) and the panel row `HP +n` (word 11 blue, number gold with `+`) |
| `06b` Karin KO `Defeat` red | red `Defeat` x 243..321, y 317..334 under Karin | nothing | `on_defeat` (red for a party member) |
| `06a` 0 HP party row | U3's panel row | -- | -- |

Open after the retune: the `Defeat` word in the live game is a world-space billboard (mirrored from behind in `02i`), the port draws it
as a screen-space `HitInfo`; the live `Defeat` sizes vary with the camera distance (06b 78 x 17 px, 02h ~100 px).  Status icons
could still not be compared (no ailment in the live set).  The attack-ring `Miss!!` of `01d` is drawn without the ring's rim
geometry (empirical offsets above) until the retail `HitMes` placement is read from `SLUS_210.41`.

### Evidence after the retune (`screens/battle_ui/`, live `_512` frame(s) left, port right; port = `SH2_BATTLE_DEMO=2 SH2_BATTLE_BG=77 --us`, `SH2_SCREEN=native`)
`u1_ring_run.png` (01g), `u1_ring_moving.png` (01a/01c), `u1_ring_intro.png` (01f), `u1_ring_hit_text.png` (01m Good!!, 01d Miss!!),
`u1_ring_fade.png` (01e/01h), `u1_damage_number.png` (02c/02g), `u1_hit_panel.png` (02a/02d), `u1_panel_persists.png` (02e),
`u1_defeat_text.png` (02h/06b), `u1_heal.png` (02n/02o).  Not reproducible in the port yet: `01i` (world-space ring after a camera cut),
`01l` (spell ring -- the flow starts none), `02h`'s real 2-hit accumulation (one hit per action here; the accumulation code path is the
same `TotalPanel::hits/damage`), `02f`/`02i`/`02k`/`02l` (enemy spell damage: the enemy spells run without a hit sphere in the port, the
number / panel / Defeat paths are shared with the weapon hits).  Sheets: `u1_font_blocks.png`, `u1_icon_sheet_grid.png`, `u1_jring_textures.png`.

## C1 captures (party variants, `08a..19b`): status kinds and the special-command rings
* **Status records**: retail `GetIconList` (US 0x6a6f70) reads kind **0x54** (`'T'`, aux 0x55 `'U'`) where the JP demo has 0x47 / 0x48 --
  confirmed live by C1 (`19b`: kind 0x54 value 1 = Poison skull, value 8 = Seal "!"; kind 0x47 draws nothing on the retail build).  The port's
  own rules write the JP kinds (`actions.rs` pushes `modkind::STATUS` = 0x47 records), so `icon_mask` already fired for the port's inflictions;
  it now accepts both numberings (`hud_hits::RETAIL_STATUS / RETAIL_STATUS_AUX`, test `icon_mask_follows_the_retail_bit_order`), so records
  copied from a retail image / save also produce icons.  Bit order unchanged (1 Poison, 2 D.Poison, 4 Paralysis, 8 Seal, 0x10 Panic, 0x20
  Petrify, 0x40 MentalBreak; aux bits -> the ring abnormalities).  `19b` only shows the party-row icons (U3's, from the same sheet /
  `ICON_FRAMES` -- `HitArt.icons`, `ICON_FRAMES`, `icon_mask`, `IconState::cell` are `pub`); the 3D `AbnIcon` billboard was out of frame there,
  the port's billboard shot is `u1_status_icons.png` (Poison + Seal forced on everyone, `SH2_BATTLE_ICONS=9`).
* **Special-command rings** (`09b` Crag, `10o` aroma, `10t` crest Shield, `12e` Sword Art Heuervelk, `14e` Muscle Art, `15f` Manifestation,
  `01l` Cure; `16f` Gepetto's 1-zone attack): same centre (341.33, 224), same rim box (292..405 x 144..313) and lean as the weapon ring;
  only the zone colours differ -- live averages: blue zone (45,140,187), green zone (20,135,75), red tail (200,46,32), weapon gold
  (195,125,80) = the `AddModulateArea` band (0x20,0xc8,0xfa), the `AddStepArea` default (0,0xa4,0x50), the strike tail (0xff,0x20,0x18) and
  the weapon default (0xe0,0x98,0x40) seen through the ring face.  Every special ring has its **first zone blue and the others green** with
  red tails (`12e`, `10t`, `09b`, `14e`, `15f`, `10o`), a single-zone spell (`01l` Cure) is blue only.  Added `RingRun::start_special(..)`
  (plugin.rs, next to `start_areas_custom`) building exactly that; the port's flow still starts rings only in `Phase::Attack` (skills / magic
  go through `Phase::Effect` without a ring), so the renderer was photographed through the dev override `SH2_BATTLE_RING=special|cure` on a
  weapon attack: `u1_ring_special.png` (12e / 10t vs port), `u1_ring_cure.png` (01l vs port).  When the flow gains skill rings it should call
  `start_special` with the skill's `(start, width, strike)` rows; the zone layout of the live specials (blue zone first, e.g. at 7 o'clock in
  `12e`, green zones after it) is data, not a rendering rule.
* Not in the port: the spell / skill name window during the ring (U2), the ring-hit icon glyph at the end of skill help lines (U3).
