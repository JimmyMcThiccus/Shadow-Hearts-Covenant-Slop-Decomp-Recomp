# Round 6 RG: the field Judgement Ring (`SetRing` / `RingControl`)

## Status (2026-10-15, after the pause)

**Works:** every field ring of the US game runs as in retail through the real scripts -- `SetRing` parsed like `CField::SetRing`, `RingControl`
waits while `FieldRingRun` plays the whole `UpdateRing` control sequence (frame capture, half-black fade 300 ms, `RingActive`, result,
1 s hold, fade back 300 ms) on the ported `JRing`, read from the pad, drawn with BT's ring renderer (`COMMON/JRING.BIN` face, areas, pointer
trail, `Good!! / Miss!!` along the pointer, `HitArea` / `HitBar` flashes), result by ring kind back to the script.  Headless runs (story
walker, tests, coverage) answer at once with a perfect run per kind.

Since the pause:
* `lap_ring_matches_live` passes (10 laps, lap period x0.875 per lap = live 2.0 .. 0.601; unplayed ring fails at ~118 deg like live).
* **Field picture frozen** behind the ring: a window screenshot at `RingControl` (`CScrCapture`, control 1..2) cropped to the 4:3 picture
  (`present_rect`), drawn full screen on the ring layer under the dim until the hold ends (`CScrCapture::Delete` + `CField::Dsp`), then the
  live field shows through the fade; the texture is freed.  The ring starts once the capture is in (<= 12 frames, else over the live field).
  Measured: static picture across run / hold frames (pixel difference 0).
* **Dim matches the GS gamma-space fade**: the capture is drawn with a vertex grey of `(1 - a)^0.8` (the fader multiplies in gamma
  space, the canvas in linear light; sRGB is not a pure power curve): field brightness 64 -> 32 = retail's x0.5 (a black quad at alpha a
  gave 64 -> 43).  Over the live field (fade back / no capture) a black quad at `1 - (1 - a)^1.5` (64 -> ~36).
* **Ring sounds**: `JrEvent::Se` / `SeEnd` posted as `AudioRequest::PlayGlobalSe` / `StopGlobalSe` with the retail `HNMSnd::PlaySE` global
  ids (JP JRing.c: 0x2002 show, 0x2001 loop, 0x2004 / 0x2005 hit / strike, 0x2007 miss, 0x0300_0000 / 0x0300_0001 event-ring loop / stop;
  0x2xxx = SYSREG bank 0, resident); looping ids are released when the ring ends or the field is left.  Bank 0x0300 (the event-ring
  loop) is not known to be resident in the port: if `FindSE` misses it that one sound is silent (not verified by ear).
* Flashes / words: `HitFx::ring_area_flash` (BT, f517b06) fed from `FieldRingRun::flashes`.
* Auto aim of the dev drive aims at the middle half of an area (an area starting at 0 deg was missed by a press at 0).
* Tests: `field_ring::tests::*` (spec parser, spin ring per colour, lap ring hits, sequence phases) and `field_ring::live_cmp::*`
  (spin deceleration and lap periods against the live numbers); `cargo test -p sh2_field` all green, `cargo check --workspace
  --all-targets` clean (2026-10-15).
* Dev drives (dev profile, timeout-wrapped, `SH2_CUTSCENE_SPEED=32` to fast-forward the entry scenes):
  `SH2_RING_DEV=RE_00_U:25:1:0x26 SH2_FIELD_RING=4` (lottery, ticket given, choice 0): result 4 -> "Nice job!" prize;
  `SH2_RING_DEV=WE_01_U:15 SH2_FIELD_RING=1` (Roger's teleporter run, after ~3000 ticks of dialogue): result 10 -> success branch.
* Evidence: `notes/integration/screens/field_ring/spin_ring_live_vs_port.png`, `lap_ring_live_vs_port.png` (retail top, port bottom),
  `autoplay_sanity.png` (field, battle menu, battle ring, victory, field after battle, command menu: unchanged).

**Remaining differences / open (priority order):**
1. Ring intro pose: retail's first intro frames show the ring face-on (round), the port's `JRing` intro shows it flattened / lying (same
   in battle: `sh2_gfx::effects::jring` intro / `draw_ring`, BT / FX2 area).
2. The lottery prize-list window (`OpenMessage(0x1869f, -1)` before `RingControl`) prints its `%p5■` lines as `?ス@?ス` (full-width glyphs
   of the message font; FS2 / MN2 text path) -- the window itself is right.  WE_01_U leaves an empty "Roger" window up during the ring
   (retail behaviour unknown; no live capture of a script ring).
3. Sound of bank 0x0300 (event-ring loop) unverified; no live audio comparison.
4. Not driven on screen: the abnormal spin rings (arg 0..5: small / hidden / wobble / accelerating / reverse / jerky; `JRing` logic is
   ported and shared with battle) and the DB_00_U ring editor.  Kinds 0 / 3 occur in no US script.
5. Message windows (non-sprite UI layers) draw above the ring layer; retail's OT order for windows vs the ring is not checked.

## 1. Retail behaviour (decompiled + live)

JP demo `CField::SetRing / RingControl / cbRing / UpdateRing / RingResult` (decomp/G/CField.c 4457..4670) = US FIELD.BIN 0x004fad40..
(`CField+0x8a8` block; US `UpdateRing` 0x004fafc0 read with Ghidra + `tools/be/mipsdis.py`, control jump table 0x00610a00):

* `SetRing(kind, lap ms, arg, x, y, spec)`: block cleared; `kind & 7`, lap, arg, x, y; spec letters case-insensitive, blanks skipped,
  `C<n>` colour of the area being built (default 1, reset after each `E`), `S` start, `E` end (9 bits each, width = E - S + 1), colour
  4 bits; object state 2.
* `UpdateRing`: `JRing(0, 0xd)` (0x5e0 bytes), `AutoLoad`, then `SetEventRing(kind, false, kind == 1 ? arg : 1)`, callback mask 0x280,
  `SetRingPos(341.33, 224)`, `AddEventRingArea(start, width, colour)` per area.
* `RingControl(1)` -> control 1: `CApp::SetNoDraw(1)`, `CField::Clr`; 2: `CScrCapture` of the frame (OT layer 10); 3: `SetNoDraw(0)`,
  `SetFFMode(0,1,1)`, `SetFader(0, 7, 300)` (fader slot 0 mode 7 = to half black in 300 ms), `SetRotSpeed(lap * 0.001, -0.15, 1)`,
  `SetEventRingAbnormal(arg)` unless kind 1, `RingActive` -> 5: wait for `cbRing(0x80)` (result word = JRing +0x588, flag bit 3);
  timer +0x9fc = 0 -> 6: after 1000 ms delete the capture, `CField::Dsp`, `SetFader(0, 6, 300)` -> 7: fader done, `SetFFMode(0,1,2)`,
  control 0.  `RingResult` answers once control is 0 and the flag is set.  Op 0x64 yields until then.
* No ring customisation, ring item or status is applied to field rings (`UpdateRing` never calls `CustomConvert` / `SetJRingStatus`).

Result by kind: **2** = spin / "slot" ring (`EVENT_SPIN`): colour code of the area the pointer stops in, 0 = none; **1** = `arg` laps
(`LAPS_B`, period x 0.875 per lap): laps cleared; **0 / 3** = one lap, every area: hits.

### Live checks (US, instance 4 = disc 2 debug map, `tools/live/fring.py` writes the block; 2026-10-14)

| check | live | port |
|---|---|---|
| spin ring 1800 ms, 7 areas, Circle | pointer runs on, decelerates, stops one full turn after the press angle ~4.0-4.1 s later (press read at ~226 deg -> stop 226.2, result 4 = area 200..240 colour 4; a press read at ~88 -> stop 88.4, result 0) | stop = press angle + 360, 4.12 s (test `spin_deceleration_matches_live`) |
| hold / fade | control 6 ~1.0 s (ring object gone ~0.8-0.9 s into it), control 7 ~0.3-0.4 s | 1.0 s + 0.3 s (`sequence_holds_one_second_and_fades`) |
| kind 1, 2000 ms, 10 laps, 3 x 100 deg red areas (WE_01_U) | 30 presses -> **10**; lap periods 2.0 1.75 1.531 1.34 1.172 1.026 0.898 0.785 0.687 0.601 (x0.875) | `lap_ring_matches_live` passes |
| kind 1 left alone | END_MISS at 118.1 deg (area 0 ends 110 + 7.5), result 0 | same test |
| look | field frozen + dimmed to half; ring at (341, 224) with the battle ring's tilt, intro face-on then tilting; area colours 4 green / 3 blue / 2 gold / 1 red; `Good!!` words fly out **along the pointer direction** far from the ring; `HitArea` wedge flashes beyond the rim | frozen capture + gamma-matched dim + BT's renderer (words along the pointer, `HitArea` / `HitBar` flashes since f517b06) |

## 2. Every field ring of the US disc (`ring_census --us`: 44 `SetRing`, 24 `RingControl` sites)

* **Lottery** ("Lottery Member", `SYSFUKU`, needs a lottery ticket = item kind 1 id 0x26, choice 0 plays): kind 2 spin rings in
  BO_02_U, CA_01_U, GI_00_N, HE_25_N, IN_00_U, KA_02_U, MI_12_U, MS_49_U, MU_00_U, RE_00_U, RE_01_U, RE_02_U, RE_03_N, RE_03_U, RO_21_U,
  RU_04_U, RU_05_U, SA_01_U, SM_05_U, SM_31_U; lap 600..1800 ms; arg = abnormal kind (-1 none, 0 small, 1 hidden, 2 wobble, 3 accel,
  4 reverse, 5 jerky); two specs per map, the second with extra red `C1` areas (top prize) while its one-off flag (e.g. 0xb6 / 0xb7) is
  clear.  Result 1..4 = prize (switch), 0 = consolation.
* **WE_01_U** (Roger, three sites): kind 1, 2000 ms, 10 laps, three red areas; the script tests `result == 10`.
* **DB_00_U** ring editor (all arguments computed).
