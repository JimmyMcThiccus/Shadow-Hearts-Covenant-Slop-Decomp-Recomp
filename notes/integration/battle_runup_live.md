# Attack run-up and hit timing, measured live on the US disc (2026-10-13)

Method: PCSX2 (DebugServer), Nicolai's Attack against Revenant 1 in the AP_02_U tutorial fight (MONSET 4), the Judgement Ring pressed by a bot (`tools/live/rec3.py`) inside both areas ("Good!!" x2), sampling `CBattle` + `BtlChr` slots 1 / 2 + the ring ~1 kHz, game timer `CBattle+0x3c` (ms) used to bucket the 30 Hz game frames.  No breakpoints.

## Addresses (US, this session)
* `CBattle*` 0x00AFFA20 (`[0x440000]`), phase u16 +0x28, step u16 +0x2a, game timer u32 +0x3c (ms).
* `BtlChr` stride 0x510 at CBattle+0xb0: **position vec4 +0xb0 (x, y, z, 1)**, previous / stand point +0xc0, **heading +0xd4 (degrees, -180..180)**, HP i32 +0x80.
* Judgement Ring object (found by scanning for the area table): 0x011718b0; +0x4ac pointer angle (deg, 0 = 12 o'clock, clockwise, wrapped to -180..180), +0xb4 period 1.6, +0xfc area count, areas at +0x100 stride 0x24 (`start`, `width`, `strike` u16 at +4/+6/+8) = Nicolai (169, 90, 14), (279, 72, 11).

## Timeline (phase 5 = Attack)
| t (s) | event |
|---|---|
| 0.00 | confirm target: phase (5,0); steps 0-3 take 0.32 s (camera cut to the ring shot) |
| +0.32 | (5,4) ring: intro 0.80 s, then the pointer runs at 216 deg/s (period 1.6 s, 3.6 deg per 60 Hz tick) |
| ring end | pointer stops on the second press; ring phase ends one tick later -> (5,5) |
| (5,5) +0.00 | run-up starts the same frame |
| +0.82 | first hit lands (HP 17 -> 6), frame 25 |
| +1.15 | second hit (HP -> 0), 10 frames (0.33 s) after the first (= MosEvent 9 -> 19) |
| +1.53 | phase (20,0), turn end |

## Run-up speed profile (units per 30 Hz frame)
`0, 1.11, 1.67, 2.17, 2.77, 3.34, 3.33 x5 ...` -> linear acceleration of 0.556 units/frame^2 (**500 u/s^2**) for 6 frames to a cruise speed of **3.33 units/frame = 100 u/s**; the heading eases towards the run direction by ~0.53 x the remaining angle per frame (166.9, 173.2, 176.6, -179.9).  Later the speed falls linearly again (3.64, 2.59, 2.75, 2.17, 1.58, 1.00, 0.42) and the fighter finishes with the creeping steps of the swing's root track (0.4 .. 0.2 per frame).
* **Update 2026-10-13 (jump re-measured, section below):** at frame 11 the position jumps 42 units (from (-8.56, -3.42) to (-19.89, 37.09)) and then arcs back at 3.64 / frame turning ~24 deg/frame while the camera cuts to a wide shot; the on-screen model does teleport there.  It is not understood (HomingMoveEX waypoint on the arena rim?).  The port's `run_path` detour is still the simplified version.
* Applied in `sh2_battle::choreo`: `run_ease` / `run_time` (trapezoid, `RUN_ACCEL` = 500, test `run_profile_matches_the_live_us_measurement`) replace the smoothstep for the approach, return, walk-beside legs.  The old model gave a peak speed of 1.5 x average (up to ~150 u/s); the real game never exceeds 100 u/s.

## Target reaction (answered 2026-10-13: NOT root motion)
The struck Revenant slides along the attack direction, 9.0 units in 10 frames (z 2.86 -> -6.13), and **stays there** (single-hit run: still at (-24.69, -6.17) when the next menu opens; no walk back).  It is a scripted push, not the hit motion's root track:
* the struck `BtlChr` carries a `MoveWork` block (`MoveWorkInit` JP 0x004d0ae0 / `MoveFunc` 0x004d0cc0, integrated in 1/60 s ticks: `pos += v; v += a; if v <= 0 {v = a = 0}`): live +0x34 accumulated push, +0x3c velocity, +0x40 deceleration, +0x64 elapsed time, set up by state 0x19 of `BtlChrSequence` (US `decomp/I/us_battle_aiinit.c` ~2845).
* state 0x19: `n = int(f45c * 30 / 100 + 0.5)`, `T = n (n - 1) / 2` (0 for monster 499), `v0 = (f45e / 10) * n / T`, `a = -(f45e / 10) / T`.  Live: `f45c = f45e = 70` -> n = 21, T = 210, v0 = 0.7, a = -1/30 per tick, push accumulator 1.3667 after the first 30 Hz frame, 7.2 at 0.25 s, **7.70 final** (0.35 s) -- exact.  `f45c` / `f45e` are the push time / power arguments of the damage routine (set at CBattle.c ~48210), 70 / 70 for Nicolai's Standard attack.
* the other reaction states use other formulas (`f45e / 12 * ...`, `f45e / 100 / 1.5`, `f45e * 0.024` with -0.075 / -0.1 / -0.125 per tick by size class); only 0x19 was measured.
* the motion roots do not match either: Revenant (CHR 418, `b2_root` example) has no `blwa`; `blwd` is 5 frames / +10.22, `flya` is non-monotonic (+1.2 then -11.7).
* Unexplained: the enemy also jumps (+1.07, -1.34) on the very hit frame, before the accumulator starts (total displacement 9.03 vs push 7.70).
* Ported: `sh2_battle::choreo::Push` (+ tests `knock_back_follows_the_live_us_push`, `a_struck_enemy_slides_and_stays_displaced`), started from `models.rs::knock_back` for non-lethal, non-heavy hits with `STANDARD_PUSH` = (70, 70) away from the acting fighter.  Other attack shapes (Hard Hit / High Angle / Knock Down) need their attack-table rows.

## Tooling notes
* The pad is read once per game frame: key holds < 0.12 s are lost.  After the ring bot's 2 presses the ring ended in two "Good!!" (counters (4,2) -> stop).
* Setting an EE breakpoint at `HomingMoveEX` (0x4ee6d0) and then pressing a key froze the emulated CPU (see `tools/live/README.md`).

## The mid-run-up position jump: real, camera-synchronised, only when the straight run is blocked (2026-10-13, `tools/live/rec4.py`)

Recorded every `BtlChr` (position +0xb0, heading +0xd4) of all six fighters and the whole `BtlCamera` object (`[CBattle+0x45c4]`: mode u16 +0x1c, step +0x1e, then position / look-at floats) at ~1 kHz for two attacks from the same state.
* **Run A** (target Revenant 1 at (-25.6, 2.9); another Revenant, slot 3, stands at (-8.7, 3.1) exactly in front of Nicolai's lane x = -8.6): Nicolai runs straight along x = -8.6 at 3.33/frame, then **on one game frame** his `BtlChr` position changes from (-8.6, -3.4) to (-19.5, 37.2) (heading -180 -> 82); **only Nicolai's data changes, the other five fighters do not move**.  On the *same frame* the camera object changes from mode 18 / step 1 (follow) to **mode 19 / step 1 (the attack camera)** and its position / look-at floats jump (-1.4, -18.1, -48.5 -> -74.0, -29.8, 36.9).  So it is neither a coordinate re-centring nor a position that merely follows the camera: the fighter is really moved, on the cut frame, to the start of the attack camera's shot (z = 37.2 is also about the far arena edge; the destination is 34.3 behind the enemy line, the mirror of his home row 34.6 in front of it).  From there he runs back at 3.64/frame along an arc (heading 82 -> 58 -> 34 -> 10 -> 2, 24 deg per frame) to the stand point and swings.
* **Run B** (target Revenant 4 at (24.9, 3.2), nobody in the way): **no jump**.  Nicolai runs east along his own row (z = -33, heading -89) with the same 6-frame 0.556/frame^2 ramp to 3.33/frame, turns left on an arc at 3.58-3.67/frame (heading -108, -132, -156, 179: 22-24 deg per frame, radius ~9.5 units) and approaches the target from the south along x = 25.5; the camera cut 18 -> 19 happens mid-arc at (23.8, -30.1), 33.3 units from the target, and Nicolai's position stays continuous.  The final approach speeds fluctuate (1.52, 2.74, 2.17, 1.59, 1.00, 0.42, ...) like a motion root track, ending 12 units short of the target.
* Hypothesis (not proven): the cut to mode 19 is triggered at ~33-35 units from the target; the planner (`HomingMoveEX`) normally steers around obstacles with arcs, and the jump is the blocked-lane case where it re-seats the runner on the other side.  The port's `run_path` (one waypoint detour) never teleports; this could be matched by starting the target-side leg at the camera cut, or left as is since the cut hides it.
* **Knock-back confirmed again on Run B**: Revenant 4 slid from z = 3.2 to 10.8 = 7.6 units over the same 10 frames, directly away from the attacker (+z), no initial extra step (the extra 1.3 units seen against Revenant 1 in run 5 did not repeat; its cause is unknown).
* End of turn: at phase 3 step 0 (camera mode 7) the attacker's position changes in **one frame**, with no run back in the data: (-25.7, 14.0) -> (-7.8, -26.8) after run A and (24.9, -9.0) -> (-11.6, -50.2) after run B.  Neither equals the starting row (-8.3, -31.7) / (-7.6, -32.7) and he stays there for the rest of the 12 s recording (turn start / next menu), so the destination rule (and whether the exact home is restored later) is **not** understood; only 'there is no visible run-home leg in the BtlChr data' is established.  The port's `Act::Return` run-home is therefore unverified against retail.  The struck enemy stays displaced (it is not pushed back).

## No run home (2026-10-15, round 6 GPA)
User-confirmed against the US game: a fighter's position changes **only** through its own physical attack (it runs up, swings and stays there)
and through being hit (the knock-back above, stays displaced); there is no run back to the slot after an attack, and fighters regroup only
through Combo.  Consistent with the live data above (no run-home leg in `BtlChr`).  The port now ends an attack with `Choreo::stay_here` (the
spot becomes the fighter's home, heading kept) instead of `Act::Return`, a finished knock-back also becomes the new home, and `models.rs`
keeps `BattleModel::home` / `facing` and `BattleRuntime::positions` on the current spot (targets, combos and Gathering use it).
Still open: the one-frame re-seat at phase 3 step 0 measured above (after runs A / B) is not reproduced; it did not move the fighter back
to its row either.
