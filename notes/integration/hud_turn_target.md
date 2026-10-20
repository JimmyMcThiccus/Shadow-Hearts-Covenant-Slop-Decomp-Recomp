# Retail `TurnOrderDisp` / `TargetInfo` / `TotalHitInfo` -- function-level port (2026-10-19)

Code: `port/crates/sh2_battle/src/hud_turn.rs` (TurnOrderDisp), `hud_target.rs` (TargetInfo), `hud_hits.rs` (TotalHitInfo, additions only), drawing in
`hud.rs` (`draw_turn_priority`, `draw_plate`), thin hooks in `plugin.rs` (state machine drive, view fields).  Source: the retail `BATTLE.BIN` decompile
through Ghidra (`BATTLE.BIN` program, Ghidra address = US address - 0x45ea80; e.g. `TurnOrderDisp::MakePacket` 0x50d4f0 = `FUN_000aea70`, `TargetInfo::MakePacket`
0x525350 = `FUN_000c68d0`, `TotalHitInfo::MakePacket` 0x518780 = `FUN_000b9d00`).  The JP demo decompile (`decomp/H/*.c`) differs from retail in layout:
retail builds a fixed-size packet once and only rewrites vertices, the JP one rebuilds the packet every frame.  Evidence: `screens/hud_turn_target/*_sbs.png`
(left = live capture `screens/battle_live/`, right = port, `SH2_BATTLE_DEMO=2 SH2_BATTLE_BG=77 --us`, no `--autoplay`, see below).

## Covered retail functions

| class::method | US | JP | port |
|---|---|---|---|
| `TurnOrderDisp::__ct` | 0x50ce90 | 0x4ea280 | `TurnOrderDisp::new` (hidden, y = -128) |
| `TurnOrderDisp::Polling` | 0x50d190 | 0x4ea5a0 | `TurnOrderDisp::poll` |
| `TurnOrderDisp::MakePacket` | 0x50d4f0 | 0x4ea940 | `TurnOrderDisp::layout` -> `Prim`s |
| `TurnOrderDisp::TurnOrderOpen / Close` | 0x5119d0 / 0x511a20 | 0x4f0af0 / 0x4f0b40 | `open` / `close` / `want_open` |
| `TurnOrderDisp::SetSelectChr` | 0x511a60 | 0x4f0b80 | `set_select_chr` (+ `clear_select`) |
| `TurnOrderDisp::__dt / Destruct / getPacket` | 0x50d020 / 0x50d140 / 0x57dff0 | | owner's `Option`, per-frame `layout` |
| `TargetInfo::__ct` | 0x524d90 | 0x501fd0 | the plate exists while the target page is open |
| `TargetInfo::Polling` | 0x5250d0 | 0x5022c0 | `poll_phase` (pulse phase +2 rad/s wrapped at pi); icon frame clocks are `hud_hits::IconState` |
| `TargetInfo::MakePacket` | 0x525350 | 0x5024d0 | `hud_target::layout` |
| `TargetInfo::EndSet / Destruct / __dt` | 0x57df20 / 0x525070 / 0x524f10 | | owner's `Option` |
| `TotalHitInfo::Polling` | 0x517670 | 0x4f62f0 | `TotalPanel::tick_sel` (new: scale 0.9 for a marked target) |
| `TotalHitInfo::MakePacket` | 0x518780 | 0x4f69c0 | already `HitFx::draw` (U1); frame / card / row constants re-checked against the retail packet |
| `TotalHitInfo::Reset / SetDispData / ShowAll` | 0x51cfa0 / 0x51d3c0 / 0x51da80 | 0x4faca0 / 0x4fad60 | `HitFx::panel_mut` and the row fillers (comments only) |

## TurnOrderDisp (the Turn Priority plate)

Object: state `+0x38` (0 hidden / 1 opening / 2 open / 3 closing), slide `y` `+0x58`, scale `+0x64` (target `+0x60`), phase `+0x68`, select mask `+0x5c`
(2 bits per fighter: 1 ally marker, 2 enemy marker, 3 special).  `Polling` runs per frame with `dt = CBattle+0x38` (1/60 s):
* phase `+= dt * 4 pi` (2 turns / s), wrapped into `[-pi, pi)`; scale approaches its target by at most `2 dt` per frame (0.8 -> 6 frames);
* opening: `y += scale * 16 * dt * 60` px / frame from `-96 * scale` to 0 (**6 frames = 0.1 s**, not the 2250 px/s the port had); closing: `y -= ...` to `-128 * scale` (8 frames),
  `MakePacket` draws nothing once `y <= -128 * scale`.  `CBattle` calls `TurnOrderOpen` only from state 0 and `TurnOrderClose` only from state 2 (`want_open`).
* **Scale 0.8 on every target page** (enemy, ally, spell) except the Combo partner page: the live title ink is 51 px against 63; the packet truncates every
  step (`x_{k+1} = (int)(x_k + 26 s)`), so the card pitch is exactly 20 (earlier notes called it a "squeeze"; 04e / 04f were wrongly believed to keep 26).

`MakePacket` draw order and geometry (screen px, `s` = scale, `y` = slide):
1. emblem (entry 20, 92 x 112) at `(14 s, y + 11 s)`;
2. glow strip at `(31 s, y + 38 s)`, 36 x 60: **entry 21 orange** behind an acting enemy; if the actor itself is marked (`select != 0`) **entry 22 cyan**, rotated 30 degrees about
   its centre and pulsing `sin(phase) * 0.25 + 1.25`;
3. nine capsules: entry 19 texels (0,0)-(37,50) at `(x_k - s, y + 40 s - s)` .. `(x_k + 36 s, ... + 49 s)`, colour 0x80;
4. the actor: party portrait at `(21 s, y + 28 s)`, enemy big letter (entry 23, 36 x 48 cells, 2 columns) at `(33 s, y + 41 s)` -- no red tint (the retail letter art is red on the orange glow);
5. nine card faces at `(x_k, y + 40 s)`: enemy = entry 24 letter (36 x 46 cells), party = the card portrait texture (33 x 46 in retail), RGB by state
   (**berserk = party member with SP 0: (0xa0,0x20,0x20); knocked out / skipped: (0x96,0x96,0x18)**, else 0x80) and **alpha 0x80 when the fighter is the actor or marked, else 0x40**;
6. outlines: entry 19 texels (37,0)-(70,46), 33 x 46 at `(x_k, y)`, colour by mask value 1 = (0x01,0x7d,0x5a) green, 2 = (0x80,0,0) red, 3 = (0x7d,0x5a,0x01); drawn over the faces;
7. entry 18 group: title (0,0,100,18) at `(79 s, y + 25 s)`, zigzag (0,18,40,50) at `(52 s, y + 75 s)`, the rail from `x = 92 s` (tail 61.5..76 only; with Combo partners
   pending [`CBattle+0x32`] the stretched piece 80.5..96 to `((last - 1) * 26 + 13) s` then the tail) and one pip (42,18,59,50) at `88 s + 26 s (k - 1)` under every pending partner's card.
The "red outline on an acting enemy's cards" the port had does not exist in the packet (live `06c` / `13a`: the red is the letter art): removed.
Open: the special case `CBattle+0x28 == 9` (an enemy acting in phase 9 shows its *target's* portrait in the emblem / cards, `+0x5b0` / `+0x5b1` of `CBattle+0x48`), and the extra rail bits
for a special actor (`CBattle+0x26`, `BtlChr+0x1ac > 9`) are not reproduced.  The party card / emblem faces are `FI_` portraits (the retail 33 x 46 card textures and the emblem
portrait of `CBattle+0x4484 + 4 * (BtlChr+0x5b0 / 0x5b1)` come from files the port has not located): the card face is cut to the capsule shape with the alpha of entry 19 at load
(`hud::card_face_pixels`), the emblem face is the old 52 x 64 scaling.

## TargetInfo (the target plate)

Anchor `P = (301, 60)`; kind 1 party, 0 enemy (`?????`), 2 photographed (library bit `BtlSave+0xf63` + Anastasia in the party).  `W = max(0.8 * name image + 37.5, 96)` (168 for
kind 2; the port feeds its measured text width, `name + 42`), `H = 50` (72) + status rows (`23 - 2`, a row per 20 px pitch overflow, +9 / +10 with the separator).
* fill strip `(P.x-4, P.y-5)..(P.x+W+11, P.y+H+5)`, GS colours (0x41,0x41,0x4e) top to (0x0a,0x08,0x0a) bottom, alpha 0x4c;
* eight sprites of entry 8: top / bottom edges (42,33,58,40) stretched, left / right edges (34,34,41,50), four corners (the curls (34,0)-(65,33) top-left / bottom-right, the
  gems (0,0)-(34,49) top-right / bottom-left rotated 180 degrees) -- this is the metal frame of the live plate (the port had a flat dark box);
* separator (4 px, (0x82,0x7d,0x97), alpha 0 -> 0x80 -> 0 over `(W+13)/3 <= 64` px) at `y + 52` (71) when there are status icons;
* card: entry 19 capsule (0,0,37,50) at P and the face 36 x 46 at `P + 1` (enemy letter of entry 24, party card portrait);
* gauge: track strip `x 336 / 339 / 401 / 404`, `y + 39 .. + 47` (entry 3 rows 8..16, 3 px caps), fill from x 338, width `hp * 63 / max` + 1, texels from 2 (MP bar from 53);
* `HP` label entry 2 (1,1,20,12) at `(P.x + 37, P.y + 27)`, digits (u = 77 + 11 d, v 1..15) 8.8 px apart from `P.x + 58`, 14 px tall, column blanks by the leading-zero rule,
  **colour by the real HP (white / yellow <= half / red <= quarter or 0) also for the `?` glyphs**, the gauge fill is drawn from the real HP even while the digits are `?`;
* kind 2 adds the MP row (label (20,1,39,12) at `y + 48`, digits, track at `y + 61`), the class ring (entry 12, two 40 x 42 sprites at `(P.x+107, P.y+24)`, the dashes pulsing alpha
  `(sin/2 + 1) * 128`), the element glyph (entry 11, 22 x 25 at `u = element * 22`, alpha `((sin + 1)/4 + 1) * 128`) and the camera mark (entry 13, 27 x 42 at `(P.x+149, P.y+25)`);
  the live "small portrait" the earlier notes mention is this camera icon.
* status icons: 19 x 23 from entry 39, 20 px apart from `(309, 120)`, a new row 23 px lower when `26 + 20 k > W`.

Open: the name is drawn with the game font (retail blits a pre-rendered name image at 0.8 width -- bolder, blue outline); the circled digit of `Revenant(1)` is wider in the port font so W is a few px
too large; the ring / element colour is one lavender (live `12d`, dark) for every element (the retail `TEX0` CLUT change per element was in the part of the decompile the jump table hid);
the entry 7 mark (80 x 24, drawn when `BtlChr+0xb8` is 0x11..0x13) is not drawn; the arrow over the target (`BCursole`) is untouched.

## TotalHitInfo

Checked against the retail packet: frame = entry 19 (70,0)-(108,25) at `38 sx x 25 sy`, card 36 x 23 from entry 25 / the party card texture at `(x + sx, y)`, rows from `x + 46 sx`,
glyph scale `24 / (h - 5)`, advance `(w - 2) * scale`, space `8 sx`, status icons 19 x 23 at a `20 sx` pitch -- all equal to the U1 implementation.  New from the retail `Polling`:
the panel of a fighter that `TurnOrderDisp` marks as a target (`SetSelectChr`) scales to **0.9** instead of 0.75 (`TotalPanel::tick_sel`, mask published as `HitFx::select_mask`; the
collapsing state tests the bit `1 << chr` exactly like retail).  Open: retail only lets the 4 s clock close a panel after `ShowAll` (`+0x360 = 1`, called by the end-of-battle code),
plus status specific rules (`BtlChr+0xb8` 0x27 / 0x28 / 0x2a); the port always closes 4 s after the last `Reset`.

## Dev drive notes

* Run the battle dev drive **without `--autoplay`**: with it the autoplay's own presses win and the `SH2_BATTLE_CMDS` script never reaches the target pages (no `target_select` shot).
* `SH2_BATTLE_PAGELOG=1` logs every command page change with its tick (new, `devdrive.rs`).

## Tests

`hud_turn::tests` (12: slot x chain 84 / 110 / ... and 67 / 87 / 107 at 0.8, open 6 / close 8 frames, scale 6 frames, phase wrap, select bits, capsule / face / outline rectangles,
glow centre, rail + pips, tints), `hud_target::tests` (9: sizes, frame pieces, card / gauge / label / digit positions, `?` rule, digit colours, photographed extras, icon rows / separator, phase),
`hud_hits::tests::marked_target_panels_grow_to_nine_tenths`.  `cargo test -p sh2_battle --lib`: 313 passed.
