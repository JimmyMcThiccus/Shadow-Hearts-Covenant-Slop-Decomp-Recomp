# Round 6 RG: the field Judgement Ring (`SetRing` / `RingControl`)

## Paused (2026-10-14 ~20:25, coordinator: max 2 running agents)

State: everything compiles (`CARGO_BUILD_JOBS=6 cargo check -p sh2_field --all-targets` green, dev profile).  No locks held, no
processes running.  Target dir `%USERPROFILE%\.cache\sh2-r6-rg` (has a release build of sh2_field tests/examples; **from now on dev
profile only**, `CARGO_BUILD_JOBS=6`; the dev build of sh2_app was stopped half way).

Done:
* `sh2_field/src/field_ring.rs` (new): retail `SetRing` spec parser, `FieldRingRun` (the whole `UpdateRing` control sequence on the
  ported `JRing`), `instant_result` / `possible_results` (headless), `FieldRingPlugin` (draws with BT's `hud_hits::draw_ring` +
  `HitMes`, reads the pad, posts `ring_answer`), dev drive `SH2_RING_DEV=<map>:<event>[:<item kind>:<item id>]` + `SH2_RING_SHOTS` +
  `SH2_FIELD_RING=<colour>` (auto aim).  Tests (release, passed before the last addition): `field_ring::tests::*` (4) and
  `live_cmp::spin_deceleration_matches_live`; `live_cmp::lap_ring_matches_live` written, **not run yet**.
* Hooks (logged in requests.md "Round 6 RG"): host.rs `FieldRing { arg, x, y }` + `instant_result` fallback; story.rs walker uses
  `possible_results`; plugin.rs adds the plugin; lib.rs module.
* `examples/ring_census.rs` (all `SetRing` / `RingControl` sites; `--events MAP`), `tools/live/fring.py` (live ring starter / recorder).
* Live captures (instance 4, US disc 2, debug map) in the scratchpad `rg/live_spin1`, `rg/live_laps` (not yet copied into
  `notes/integration/screens/`).

Next steps, in order:
1. `CARGO_BUILD_JOBS=6 cargo test -p sh2_field --lib field_ring` (dev): check `lap_ring_matches_live` (periods x0.875, fail angle ~118).
2. `CARGO_BUILD_JOBS=6 cargo build -p sh2_app` (dev), then the dev drive (timeout-wrapped):
   `SH2_RING_DEV=RE_00_U:25:1:0x26 SH2_RING_SHOTS=<dir> SH2_FIELD_RING=4 SH2_MAX_SECONDS=90 timeout -k 5 100 sh2_app --us`
   (event 25 = "Lottery Member 9", needs item kind 1 id 0x26 = lottery ticket; choice 0 = play).  Check the shots; fix what differs.
3. Copy live + port frames into `notes/integration/screens/field_ring/` as side-by-side sheets; write the comparison table below.
4. The other ring kind in play: WE_01_U (kind 1, 10 laps) through its event (flags 0x258c / 0x258d) if reachable by the dev drive.
5. Autoplay sanity shots (`sh2_app --us --autoplay --boost 80 --shots <dir>`), `cargo check --workspace --all-targets`,
   `cargo test -p sh2_field`, OUTLINE.md status paragraph, final report.

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
| kind 1, 2000 ms, 10 laps, 3 x 100 deg red areas (WE_01_U) | 30 presses -> **10**; lap periods 2.0 1.75 1.531 1.34 1.172 1.026 0.898 0.785 0.687 0.601 (x0.875) | `lap_ring_matches_live` (not run yet) |
| kind 1 left alone | END_MISS at 118.1 deg (area 0 ends 110 + 7.5), result 0 | same test |
| look | field frozen + dimmed to half; ring at (341, 224) with the battle ring's tilt, intro face-on then tilting; area colours 4 green / 3 blue / 2 gold / 1 red; `Good!!` words fly out **along the pointer direction** far from the ring; `HitArea` wedge flashes beyond the rim | dim + ring + words through BT's renderer (words placed by BT's battle rule: right / left -- request 1 to BT); no `HitArea` / `HitBar` flash yet; field keeps animating behind (no frame capture) |

## 2. Every field ring of the US disc (`ring_census --us`: 44 `SetRing`, 24 `RingControl` sites)

* **Lottery** ("Lottery Member", `SYSFUKU`, needs a lottery ticket = item kind 1 id 0x26, choice 0 plays): kind 2 spin rings in
  BO_02_U, CA_01_U, GI_00_N, HE_25_N, IN_00_U, KA_02_U, MI_12_U, MS_49_U, MU_00_U, RE_00_U, RE_01_U, RE_02_U, RE_03_N, RE_03_U, RO_21_U,
  RU_04_U, RU_05_U, SA_01_U, SM_05_U, SM_31_U; lap 600..1800 ms; arg = abnormal kind (-1 none, 0 small, 1 hidden, 2 wobble, 3 accel,
  4 reverse, 5 jerky); two specs per map, the second with extra red `C1` areas (top prize) while its one-off flag (e.g. 0xb6 / 0xb7) is
  clear.  Result 1..4 = prize (switch), 0 = consolation.
* **WE_01_U** (Roger, three sites): kind 1, 2000 ms, 10 laps, three red areas; the script tests `result == 10`.
* **DB_00_U** ring editor (all arguments computed).
