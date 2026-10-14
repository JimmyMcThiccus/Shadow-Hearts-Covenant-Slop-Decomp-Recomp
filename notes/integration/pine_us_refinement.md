# PINE live refinement of the US port (poke and prod) -- 2026-10-09

Emulator: armsx2 (PCSX2 8eada3b11a), US retail disc, PINE through the MCP bridge (serial calls, ~0.3-1 s each = 20-60 game frames per call).
Baseline: `pine_save_state(9)` taken before any write (slot 9 = field AP_03_U, CField 0xAFE000, sys 0x749500, no battle). Slots 0-3 untouched.

## Method limits found
* A single MCP call takes tens of frames, so "tight write loops" are impossible; only values that the game keeps (state, not per-frame inputs) can be set.
* `CPadMan::Read` (US 0x0022e0c0) calls `scePadRead` into the buffer at `CPadMan+0x1a4`, inverts bytes 2/3 (active-high), centres the sticks when the pad is not in
  analog/dual-shock mode (`(byte1>>4)` not 5/7); `CPad::Update` (0x0022d0f0) builds the word `b3<<8|b2` -> `MakeReal` (0x0022d380, assign table at +0x48) -> core `+0x6a`
  real, `+0x6c` press, `+0x6e` release, `+0x72/+0x74` accumulated press/release (cleared by consumers). Sticks: `CAnalogStick::Make(core+0x78, buf[6], buf[7])` (left),
  `core+0x88 <- buf[4], buf[5]` (right).
* A code patch (hook in `CPadMan::Read` ORing a data word into the buffer) was considered and NOT done: not part of the authorisation (memory writes only; the tool policy
  refused the helper script).  Only data writes are used below.

## Write log
| # | address | old | new | purpose |
|---|---|---|---|---|
| 1 | 0x007496FA (core0+0x6a, u16) | 0 | 0x0010 (x3) | Up in the "real" word; overwritten by the next `CPad::Update` (window too short to hit) |
| 2 | 0x0074970C (core0+0x7c, f32 stick gauge) | 0 | 1.0 (many) | stick injection; hit rate ~30 % per frame while `CPad::Update` runs |
| 3 | 0x00749714 (core0+0x84, f32 stick degrees) | 0 | 0 / 90 / 180 / 270 | stick heading (0 = up, clockwise) |
| 4 | 0x00749694 (core0+4, ptr to the registered CPad) | 0x00B00EC0 | 0 | **stops `CPad::Polling` from calling `CPad::Update` for core 0** (it is only called when core+4 != 0); the core fields then keep whatever is written, so injection is exact and persistent. Libpad itself is not touched. Needs undoing (slot 9 restore) |
| 5 | CFieldModel ctrl pos 0x00CF69C0/C4/C8 | (95.65,-59.4,142) | x=-32.0, y=-63.25, z=0 (by mistake: the map had already changed; the writes landed in freed memory, harmless) | teleport attempt |
| 6 | 0x007496FA / 0x007496FC (core0 +0x6a real, +0x6c press, u16) | 0 | 0x2000 (US Cross = confirm) held ~10 calls then 0 | confirm in the battle command menu (works: menu advances) |
| 7 | 0x00749702 (core0+0x72) | 0x7018 | 0x9018 then 0 | accumulated-press word (cleared) |

(`pine_load_state(8)` = the battle saved at the Nicolai command menu, slot 8; slots 0-3 untouched, slot 9 untouched baseline.)

## Findings so far (live)
* Pad consumers: `MakeMoveControl` (US FIELD.BIN 0x004f3150) reads core `+0x6a` (real), `+0x78..0x7b` (stick direction bytes), `+0x7c` gauge f32, `+0x80`, `+0x84` degrees f32; `CField::Polling` (0x004f32d0) latches them into CField `+0xa04..+0xa18` (u16 buttons, f32 gauge, f32 deg, gauge, deg, u16 buttons).  Run = gauge >= 0.95 unless the 0x4000 bit is held (the US assign table maps hardware Circle -> engine 0x4000, hardware Cross -> engine 0x2000, Triangle 0x1000, Square 0x8000, d-pad 0x10 up / 0x20 right / 0x40 down / 0x80 left).  The d-pad table `dirTbl` at 0x00610720 = `ff 00 02 01 04 ff 03 ff 06 07 ff ff 05 ff ff ff` (identical to the port's `DIR_TBL`).
* Walking works: with gauge 1.0 the model switches to the `run` motion (`CFieldModel+0x95` bits 4-5 = gait 2), `last_trans` (+0x40) z = -1.6485 per frame in the run motion (= 0.8243 x 2 = the port's RUN_SPEED 0.83 per 60 Hz tick), heading = camera yaw + stick degrees - 180 (cam angle +0x2124 = 178.47 deg, model rotY -0.0267 rad for stick 0).
* The CField ctrl model index is CField+0x9e4 (char) -> `models[idx]` (+0x1b8).
* Encounter state (US CField): +0x3bc misses (u8), +0x3bd current threshold (u8), +0x3be rate (u8, 0x14 = 20 %), +0x3c0 flags (0x80|...), +0x3c4 f32 distance accumulator.  Walking ~290 units along the AP_03_U corridor triggered the first random encounter (set by `GetRegDat('SNOM...')`).
* US BtlChr (stride 0x510 at CBattle+0xb0; decompiler offsets = CBattle-relative, from `PCInit` 0x0049d180): +0xb0 flags A, +0xb4 flags B (bit0 enemy), +0x120 char id (s16), +0x12c max HP (u32), +0x130 HP (u32), +0x134 max MP, +0x136 MP, +0x138 max SP, +0x13a SP (s16), +0x13c AGL, +0x13e LUC, +0x140 PATK, +0x142 SATK, +0x144 PDEF, +0x146 SDEF (u16 each), +0x150 PCParam* / MONSTERParam*, +0x180/+0x184/+0x188 turn interval / timer (init 180.0f) / waited, +0x1cc.. 32 status records of 12 bytes (kind at +0x1d0, value i32 at +0x1d4), +0x51c variance f32 (`rand()/2.1474836e9*0.05 + 0.975`).  Party record base `ourBtlSaveDat` = `*(0x43fda4)` (live 0x100130), stride 0xc0 x PC id; PCParam block at +0x3c: +0x58 u16 max HP, +0x5a HP, +0x5c max MP, +0x5e MP, +0x60 max SP, +0x61 SP, +0x62 STR, +0x63 VIT, +0x64 INT, +0x65 POW, +0x66 AGL, +0x67 LUC, +0x69 weapon id, +0x6a armor id, +0x6b..0x6d accessories.
* Live party at the first encounter (slot 8): Karin (PC 5): HP 1/25, MP 15/15, SP 4, STR/VIT/INT/POW 6, AGL 7, LUC 4, weapon 0x22, armor 1 -> PATK 17, SATK 15, PDEF 16, SDEF 14; Nicolai (PC 0xb): HP 22/38, MP 23/33, SP 7/8, all stats 9 (STR 9 VIT 9 INT 9 POW 9 AGL 9 LUC 9), PATK 19 SATK 19 PDEF 17 SDEF 19; three enemies HP 17, 17, 25 (monster ids 0,1,2 of the set).
| 8 | 0x007496FA / 0x007496FC (core0 +0x6a, +0x6c) | 0 | 0x2000 pulses of ~20 calls | menu Confirm (Cross); the battle menu takes one pulse for "Attack" and a second one for the target (CBattle phase 4 -> 5) |
| 9 | CFieldModel ctrl pos 0x00CF69C0 (x), +8 (z), +4 (y) | (field) | x=-32, z=0, y=-63.25 | accidental: the map had changed (an encounter started) - the writes hit freed memory |

Emulator speed: the user set 25 % (then 10 %) with the emulator's slow motion so that one PINE call (~7 ms) is much shorter than a game frame (30 fps game frame = 133 ms at 25 %, 333 ms at 10 %).  A PINE call batch is executed serially and a batch of ~60 calls lasts ~0.4 s.
Incident: after a run of about 60 injected presses (pulse 2 at the battle menu) the VM shut down once (status "shutdown", PINE socket refused); the user restarted the disc and slot 8 / 9 loaded fine.  Cause unknown (nothing but u16 stores to the pad core and CBattle reads were issued); treat core-pad writes as low risk but not zero.

## 1. Walking (experiment 1) -- measured
Setup: core0+4 := 0 (stops `CPad::Update` for core 0), stick gauge/degrees written into core0+0x7c/+0x84.  Field AP_03_U, controlled character Nicolai.

| quantity | real (live) | port before | port after |
|---|---|---|---|
| run motion root translation (`CFieldModel+0x40` last_trans.z, per game frame at 30 fps) | -1.6487 and -1.6435 on two frames of the loop (the motion's root track is not constant) | RUN_SPEED 0.83 per 60 Hz tick = 1.66 per game frame | unchanged (matches) |
| run gait (`CFieldModel+0x95` bits 4-5) with gauge 1.0 | 2 (motion name "run") | Gait::Run | same |
| heading with stick degrees d | model rotY = cam_yaw (CField+0x2124 = 178.47) + d - 180 deg (-0.02667 rad for d = 0) | `cam_yaw + angle` (own convention) | same up to the +180 offset the port's camera yaw already carries |
| floor height (AP_03_U) | y = -59.6875 at (2.84, -69.56) and (-31.1, 166.3) | `on_floor_point` = -59.6875 at both | exact |
| floor acceptance | all three sampled real positions (2.84,-69.56), (-31.08,166.3), (95.65,142) | `circle_chk(4.0)` true | - |
| encounter | first random encounter fired after ~290 units of run on the AP_03_U corridor (rate 20 %, MONSET 2 = Revenant, Revenant, Statue) | same set via `roll_monster_set` (test `encounter_fires_when_walking_a_monster_map`) | - |

## 2/3. Battle + Judgement Ring (live, US build)
Writes (continued): 0x00AFE3BD u8 0x28 -> 1, 0x00AFE3BE u8 0x14 -> 100, 0x00AFE3C4 f32 129.4 -> 1000.0 (CField encounter threshold / rate / distance: **forces the next random encounter**, done twice because the first roll was a "miss" (`misses < 2 && rate <= roll`)).

### Stats and set (exact)
The port's retail stat pipeline reproduces the live `BtlChr` caches exactly (`cargo run -p sh2_battle --example us_party` vs PINE reads of the AP_03_U fight, slot 8):

| unit | real (HP / MP / SP / AGL / LUC / PATK / SATK / PDEF / SDEF) | port |
|---|---|---|
| Karin (PC 5, Lv 1) | 25 / 15 / 4 / 7 / 4 / 17 / 15 / 16 / 14 (HP 1 at that moment: current HP is 1 in this save) | 25 / 15 / 4 / 7 / 4 / 17 / 15 / 16 / 14 |
| Nicolai (PC 0xb, Lv 2) | 38 / 33 / 8 / 9 / 9 / 19 / 19 / 17 / 19 | 38 / 33 / 8 / 9 / 9 / 19 / 19 / 17 / 19 |
| Revenant (monster 0) | 17 / 0 / 0 / 6 / 2 / 20 / 0 / 2 / 5 | identical |
| Statue (monster 1) | 25 / 15 / 0 / 7 / 3 / 22 / 12 / 3 / 5 | identical |
The live encounter was **MONSET 2 = {Revenant, Revenant, Statue}** (not the sets 128..132 the autoplay route met in `AP_02_A`); real route = AP_03_U (see section 4).

### Retail formulas read from the US BATTLE.BIN decompilation (same as the JP rules)
`GetTurnInterval` (0x004dfe80): `(max(218.9 - (AGL + clamp(LUC,1,99)/10), 0))^3 / 47917.207 + 4.0`; `GetEvasionRate` (0x004e62d0): `(AGLdef - AGLatk) * 2.5 / 98 + 5 + LUCdef * 5 / 99`; `GetCriticalRate` (0x004e6990): `max((LUCatk - LUCdef)/5, 0) + 5`; `GetPAtkDamage` (0x0064e060): `base = max(PATK - PDEF, 0)`, element +-0.25, low-sanity +0.5/+0.2, luck factor `variance + (LUCatk - LUCdef) * 0.05 / 98`, combo fall-off 0.7/0.4, 0.6/0.35/0.25, 0.5/0.3/0.3/0.2, 0.4/0.3/0.25/0.25/0.2, crit x1.5, `damage = base * ring * mult * luckf * falloff / hitsPerSwing * power`; hits per attack = `(PCParam+0x98 >> 3) & 7` (retail; demo +0x9c; single-hit flag +0x99 bit 0) = 2 for both starting characters.  `BtlEnd` flag byte is CBattle+0x4866 (demo 0x45c2); global stat modifier at CBattle+0x407c/+0x407e/+0x4080; **the JRing pointer is CBattle+0x45d0**, per-hit grades at +0x45ec (2 bits each), hit count +0x45da, percent +0x45dc / +0x45e0 / +0x45e4 (strike 12000) / damage mult +0x45e8 (`GetJRingAreaResult` 0x00660ad0).

### Judgement Ring of a weapon attack (live)
* The ring is created at AttackFunc step 2 (phase 5), `SetJRingStatus` (0x0065f530) starts from period 1.6 s/rev, `SetMode(5, 1, 1, 4, 3)` (intro 5, SINGLE, end-miss 1, end-ok **4**, end-strike 3), `laps_allowed` 1 (+0x4e4), callback mask 0x7c3 (live +0xf0 = 0x7c3).  Live JRing (US layout = JP layout, 0x5d0 bytes): period +0xbc = 1.6, `areas` at +0x100 stride 0x24, `area_count` +0xfc.
* **The areas are not generated: they come from the `PC_J` table** (sshdat.na table 2, `GetRegDat` kind 0x31 in the retail numbering, demo 0x2b = section 5 of `BattleData`): per PC an 8 byte `{offset, rows}` header, rows of 16 u16 `{count, (start, width, strike) x 5}`, row = hits - 1 with hits = `(PCParam+0x98 >> 3) & 7`.  Nicolai (hits 2): row `[2, 169, 90, 14, 279, 72, 11]` = exactly the two strike areas read from the live ring `(start 169, width 90, strike 14), (start 279, width 72, strike 11)`.
* Port before: `RingRun::start` invented its areas (`40 + k*300/hits + rand%20`, width `52 - 6k`, strike 12) and ran at period 1.9 s with end-ok 3.  Port after: `BattleData::ring_areas(pc, hits)` + `RingRun::start_areas(areas, 1.6, seed)`, end-ok 4 (test `us_ring_areas_match_live_ring`).

### How the ring was captured and driven (method, all writes logged here)
* The emulator ran at 10 % speed (user: slow motion) so that a ring lap (1.6 s) lasts ~16 s of wall time.  A save state taken at the right moment (slot 5) holds the ring frozen: the ring's `flagsC` (+0x42) bit 4 is the **pause flag** (`dt = 0`), written as 0x14 over the live 0x04 at JRing(0x115A8D0)+0x42 (ring heap address is deterministic from slot 7).  Loading slot 5 gives a frozen RUN-state ring (state 4, substate 1, cur_angle 70.2 deg, area 0 armed, hits 0).
* The pointer angle (`JRing+0x4ac` cur, `+0x4b0` prev, degrees in (-180, 180], clockwise from 12 o'clock) is writable: teleporting it into an area and unfreezing for one tick (3.6 deg = 360/1.6 s x 1/60 s) then pressing registers a normal hit.
* A ring press is `core0+0x6c & 0xf000` (read directly from `m_pCoreArray[CPad::idx]`).  It is only seen if `CPad::Update` (which zeroes it every frame) does not run: writes `core0+4 := 0` (skip Update) + `core0+0x6c := 0x2000`, then restore `core0+4 := 0x749900` (the battle CPad object).  A fake core / CPad index redirection (table[1] + CPad+4) was tried and did NOT register the press.
* Writes of this section (address: old -> new): 0x00749694 (core0+4) 0x749900 <-> 0; 0x007496FC (core0+0x6c, u16) 0 <-> 0x2000; 0x007496F8 (u64 [prev,real,press,0]) 0 -> 0x200020000000 x20 (menu confirm, Update running); 0x0115A912 (JRing flagsC) 0x04 <-> 0x14; 0x0115AD7C / +0x0115AD80 (JRing cur / prev angle f32) -> -160.0/-163.6, -60.0/-63.6, -18.0/-21.6; 0x00C0083C / 0x00C00840 (BtlChr slot 2 max HP / HP u32, Revenant A) 17 -> 500; 0x0043FCAC, 0x00749904, 0x00C03D6A/6C (fake core experiment, restored: 0 / 0 / 0).

### Damage (exact, live) -- Nicolai (PATK 19, LUC 9) attacks Revenant A (PDEF 2, LUC 2, variance 1.01111 = 0x3F816386), 2-hit weapon ring
Enemy HP boosted to 500 (BtlChr slot 2 max HP / HP u32), ring driven hit by hit (pointer teleport + real press), HP read after the animation:

| ring grades (hit 1, hit 2) | real total damage | per-hit prediction (base 17, luckf 1.01468, falloff 0.7 / 0.4, int truncation per hit) | port before | port after |
|---|---|---|---|---|
| (100 %, 100 %) | **18** | 12 + 6 = 18 | one ring multiplier for the whole swing from `ring_multiplier` (grade 2 = 1.0): same here | 18 (per-hit grades) |
| (100 %, strike tail) | **20** | 12 + 8 = 20 | strike result 1.2 applied to BOTH hits = 14 + 8 = 22 | 20 |
Test: `sh2_battle::plugin::tests::per_hit_grades_and_live_damage` (uses the live variance bits).  The retail `GetJRingAreaResult` takes the hit index: grade 1 -> base x damage_mult, 2 -> percent x base x mult, 3 -> strike_mult x base x mult (all /10000 with truncation); the port now keeps `ring_hits: Vec<f32>` (`ring_hit_multipliers`) and `do_attack` uses the multiplier of hit `k`.
Also confirmed live: hits per swing divisor (table kind 0x40 row = PC id, `+0x16` s16) is 1 for Nicolai; both starting characters have 2 ring hits (`PCParam+0x98` bits 3-5 = 2).

### Turn interval (exact)
`BtlChr+0x190` (f32, written by `GetTurnInterval`): Karin 201.442, Nicolai 194.523, Revenant 204.822, Statue 201.722 = `(218.9 - (AGL + LUC/10))^3 / 47917.207 + 4` to 3 decimals (AGL/LUC from the cached stats above).  Port `rules::turn_interval` is the same formula (JP-verified), no change needed.

### Walking (experiment 1) -- continued
* Walk gait root translation per game frame (`CFieldModel+0x40`, z) = -0.5942 .. -0.5949; run gait = -1.6435 .. -1.6535 (mean 1.6487).  Port constants set to 0.297 / 0.8244 per 60 Hz tick (were 0.30 / 0.83).
* Heading = camera yaw (CField+0x2124) + stick degrees - 180 (deg), verified at 36.4 deg (model rot 0.6354 rad vs 0.6275 expected within the camera's drift); the model reaches the new heading within <= 21 game frames for a 180 degree stick flip (consistent with the port's TURN_RATE 2 pi rad/s = 0.209 rad per frame = 15 frames for pi).
* Floor: the port's `FloorMan` returns the live y at every sampled position: (2.84, -69.56) -59.6875; (-119.78, 2.84) -59.71447 (real -59.7144); (-151.81, 22.37) / (-167.8, 28.9) -60.375 (real -60.375, the slope end of the corridor).  The real character stops at x ~ -167.3 .. -167.8 against the west wall; the port's `circle_chk(4)` is true at -167.8 and false at -169.5 (same wall).
* Slow run-up: over the first 16 frames after a standing start the displacement is 19.9 units (1.24 / frame) before the full 1.65 root step: the run motion eases in (not modelled; the port starts at full speed).

## 7. New Game route (live, title reset to the first scripted fight) -- measured

Method: `SSHSys` request byte `+0x36` (0x00749536) := 0x40 returns to the title (attract battles run first); New Game with an engine-Cross pulse; map name = `*(0x0043FE2C CFieldSocket*) + 0x64` (0x00755A04 on this run), CField* 0x0043FF34 (0 outside the field), CBattle* 0x00440000, SSHSys `+0x1c` ms timer (0x0074951C), `+0x28` api (0x00749508).  The map-name string is only rewritten by `FieldMapJump` (it still reads `OP_00_U` while the world map is up).  Skipping: START (0x0008) pauses ("Triangle: Skip Movie / START: Cancel Pause"), then TRIANGLE (0x1000) held ~10 PINE calls skips the running LSD / movie.

| sys timer (ms) | observation (live US disc) | map name | CField* |
|---|---|---|---|
| ~0 (after reset) | title, attract fights, menu "New Game" | - | - |
| 32 000 | New Game confirmed: opening scripts of `OP_00_U` (movie, Karin and the officer in the red room, Europe map montage, tower exterior scene with the skeletal soldiers; **no guards in the forecourt scene**) | `OP_00_U` | 0x757930 |
| 180 800 | CField* = 0, flat grey, then the **world map** (Europe panel with Apoina Tower, "The World Map Screen" help window, Triangle: Menu / Cross: Confirm) | `OP_00_U` (unchanged) | 0 |
| 295 700 | Cross on the world map -> `AP_00_U`: **LSD cut scene** "One week later. Late night. Vatican." (stone hall; Nicolai: "Yes. It's inside Apoina Tower. Also known as... the Tower of Atonement.") | `AP_00_U` | 0x75C150 |
| 329 950 -> ~341 000 | START + TRIANGLE skip the cut scene -> field jump | `AP_02_U` | 0x75C150 |
| ~345 000 .. 600 000 | `AP_02_U`: cathedral hall (organ, Pieta), Nicolai: "I should warn you. It's completely different here inside the tower... It's filled with real monsters and ghosts, you know." Karin: "Monsters?!" ... "Now make sure you don't wander too far away from me. Let's go." | `AP_02_U` | 0x75C150 |
| 645 301 | window closed, letterbox gone, radar HUD: **free control of Nicolai** (CField+0x9e4 ctrl idx 0, model[0] 0x00CF8520) in the hall | `AP_02_U` | 0x75C150 |
| 877 000 (~4 s after the first step) | shatter transition, CBattle* = 0x00F476A0, "Battle Basics" window (Learn about battle basics / Skip it) with Revenants on the hall's compass floor: **first scripted fight** (api 0x28 = 0 at that moment) | `AP_02_U` | 0x75C150 |

(Whenever it runs un-skipped the app frame counter 0x0043FEB8 only counts rendered frames: 17 343 at 421.9 s, i.e. it stalls during movies / pause.)

Writes of this section (address: old -> new; all within the already authorised pad / sys area): 0x00749536 (SSHSys request byte) 0 -> 0x40; 0x00749694 (core0+4) 0x749900 <-> 0 (Update off for START/TRIANGLE/stick, restored to 0x749900 for message windows; **currently 0, slot 9 restore resets it**); 0x007496F8 (u64 [prev, real, press, 0]) 0 <-> 0x200020000000 (Cross) / 0x800080000 (Start) / 0x100010000000 (Triangle) / 0x400040000000 / 0xF000F0000000 (tests); 0x00749700 (u64 repeat / accumulated words) 0 <-> 0x200020000000; 0x0074970C (core0+0x7c gauge f32) 0 -> 1.0 -> 0; 0x00749714 (core0+0x84 degrees f32) 0 -> 90.0.

Findings:
* **Message windows (`KeyWait`) read the pad through the registered CPad object**, not the core words alone: with core0+4 = 0 (Update off) the `Start` pause and the stick work but the dialogue never advances.  With `CPad::Update` running, repeated `write64 0x007496F8 = Cross` (about 20 calls per window) advances every message.  The field walk, the pause and the battle menu are core-word readers.
* `AP_02_U` starts a scripted fight a few steps after the first free step: the six ring boxes around the centre (event 7, `f627d`: set flag 6416, `InvokeBattleTbl 0`); box id 8 (east of the hall, `f6291`) is the second one (flag 6417, tutorial help flags + `InvokeBattleTbl 1`).  Exits (script `SetMapString` + `MapJump`): id 1 -> `AP_00_U`, id 2 -> `AP_10_U`, id 3 -> `AP_09_U`; `AP_10_U` event 2 -> `AP_03_U` (the corridor of the baseline slot, random encounters), `AP_10_U` event 1 -> `AP_02_U`.
* **Why the port got it wrong**: (1) `SetMCESMode(next map)` was stored but never executed: the end of the `PlayMCES` stream must leave for the stored map, instead the script ran on into the *revisit* branch (guards, door -> `AP_02_A`); the first visit of `AP_00_U` (flag 6428 clear) is only `SetMCESMode("AP_02_U")` + `N003.LSD`.  (2) The US disc has no `FIELD/FIELD_T.DAT`: the `DTCH` container (`TRES`, `BBTL`) is `FIELD/FIELD.DAT` and its chunk length counts the data only, so the port loaded no treasure and **no scripted battle** (`InvokeBattleTbl` silently returned): now 537 `TRES`, 152 `BBTL` rows (row 0 = background 77 / monster set 4, row 1 = set 5).
* Fixes: `sh2_field::host::tick_state` (`McesState::seen_active`, `pending_jump = (next_map, 0)` when the stream ends), `sh2_field::plugin::read_field_t` (FIELD_T.DAT or FIELD.DAT) and `FieldTables::from_field_t` (both chunk length conventions), `sh2_field::retail::{US_PILOT_HINTS, US_PILOT_AVOID}` (AP_02_U -> east door, AP_10_U -> event 2, avoid AP_03_U event 1).  Tests: `sh2_field/tests/retail_route.rs` (`ap_00_u_first_visit_plays_n003_and_jumps_to_ap_02_u`, `us_field_tables_come_from_field_dat`, `ap_02_u_center_ring_starts_the_scripted_fight`), `sh2_battle::bridge::tests::us_ap_02_u_scripted_fights_are_winnable_without_boost` (sets 4 and 5, 100 seeds each, 100 % won).
* Port after the fix, `sh2_app --us --autoplay` (no `--boost`): title -> `OP_00_U` (LSD placeholders MOVIE_A, N001, M01, N002, OPI_E00) -> world map -> `AP_00_U` (`N003.LSD`) -> "MCES over -> map jump AP_02_U" -> dialogue (same five lines as live) -> scripted fight set 4 (Nicolai 38/38, Karin 25/25, four Revenants) won -> back in `AP_02_U`; ~110 s wall clock.
* Not verified live: the enemy count of the first fight (three Revenants are visible behind the tutorial window; the port has four from BBTL row 0 / set 4, the earlier notes call the tutorial set "four Revenants"), the fight's rewards, the world-map click itself (the Cross on the help window dismissed it and the single Apoina point was taken), and the `AP_02_U` -> `AP_10_U` -> `AP_03_U` leg (static from the scripts, matches the earlier live sighting of `AP_03_U`).

## 8. Summary: measured vs port before vs port after

| quantity | live (US) | port before | port after |
|---|---|---|---|
| walk / run root step per 60 Hz tick | 0.2971 / 0.8244 | 0.30 / 0.83 | 0.297 / 0.8244 |
| floor y at four probes, west wall stop | -59.6875, -59.7145, -60.375 ; x ~ -167.3..-167.8 | same | same (no change needed) |
| heading law / turn rate | camera yaw + stick - 180; 180 degree flip in <= 21 frames | same | same |
| party stats, PATK/SATK/PDEF/SDEF, turn intervals (201.442 / 194.523 / 204.822 / 201.722) | as listed in section 2/3 | equal | equal |
| Judgement Ring areas | PC_J table of `sshdat.na` (e.g. PC 11, 2 hits: (169, 90, 14), (279, 72, 11)) | synthetic areas | `BattleData::ring_areas` |
| damage Nicolai -> Revenant A, grades (100, 100) / (100, strike) | 18 / 20 | 18 / 22 (one multiplier for the swing) | 18 / 20 (per-hit grades) |
| fresh party vs first random encounter (set 2) | survives (live fight) | needed `--boost` | 200/200 seeds won without boost |
| New Game route | OP_00_U -> world map -> AP_00_U (N003 cut scene) -> AP_02_U (dialogue, free control, scripted fight) -> AP_10_U -> AP_03_U | ... -> AP_00_U forecourt with guards -> door -> AP_02_A | ... -> AP_00_U -> MCES end jump -> AP_02_U -> scripted fight -> (AP_10_U -> AP_03_U) |
| scripted fights / treasure on the US disc | `InvokeBattleTbl` starts the fight | silently skipped (no FIELD_T.DAT) | 152 BBTL + 537 TRES rows loaded |

Remaining (not measured or not ported): evade and critical rates (formulas decompiled, no live samples), the 16-frame run-up easing and the hit-stop of attacks, per-hit ring grades for combos (only the single swing path uses `ring_hits`), the real number of enemies in the first fight, the world-map confirm (point selection) itself, and `AP_02_U` after the fight (second scripted fight, id 8 box).

Final restore: `pine_load_state(9)` at the end of the session; verified afterwards: map name `AP_03_U` (socket 0x00D6E860 + 0x64), core0+4 = 0x00B00EC0 (the original baseline value), CBattle* = 0, pad words 0.  Slots 0-3 were never touched; slots 4-8 and 10-12 hold experiment states (5 frozen ring, 7 battle menu, 8 first encounter menu, 4 post ring), slot 9 is the untouched baseline.  Emulator speed is left at 100 %.

## 9. Live validation round 3 (R1) -- evade / crit / guard (US build, armsx2 PINE)

Own baseline: `pine_save_state(13)` (field AP_03_U, taken before any write; restored at the end).  Slots 0-3 untouched; 4-12 only loaded (10-12 turned out to be random-encounter battles, not the scripted fight).

### 9.1 Method, and what did not work
* Same pad recipe as sections 6/7 (`write64 0x007496F8 = [prev, real, press, 0]` with the battle `CPad::Update` OFF: `core0+4 = 0`; a 12-read hold = one menu press).  Nicolai's / Karin's first menu entry is the plain **Attack**; one press goes straight to phase 5 (single enemy / target preselected).
* Writes (addr: old -> new), all BtlChr fields of the *live cache* (slot k = CBattle(0xBFFCF0)+0xb0+k*0x510; slot 0 Karin, 1 Nicolai, 2/3/4 enemies A/B/C): +0x7c/+0x80 max HP / HP u32 (-> 30000, party and enemies), +0x8a SP s16 (-> 99, else the party goes **berserk** after ~4 turns: `Nicolai is berserk!`, PCs then act by AI and also hit each other and the enemies), +0x8c AGL u16 / +0x8e LUC u16 (written as one u32), +0x90 PATK u16, +0x94 PDEF u16, +0x00 flagsA (slot 0 / 3 / 4 -> 0: removes the unit from turns and targeting; used to leave a single PC and a single enemy), +0xd4 f32 turn timers (ineffective: TurnEnd re-arms them from AGL/LUC every action).
* **AGL written above 255 is truncated to its low byte by the game** (300 -> 44, 0x12c -> 0x2c; the cache is refreshed from a u8 path), LUC up to 255 sticks.  Enemy turn rate follows `GetTurnInterval` (AGL >= 219 gives the 4.0 floor): an enemy with AGL 235 attacks about 25 times per party action, which gives hundreds of attacks per minute without any input.
* **Constant-roll hack that failed (kept here so nobody repeats it)**: pointing the libc reent pointer (`0x0042D248`, original 0x0042CF58) at a ROM / unmapped address so that `rand()` returns a constant.  The BIOS ROM window (0xBFC00000..) and the ROM1 window (0x1E000000) of this armsx2 build are **writable RAM**: `rand()` writes its new state there (3 BIOS qwords were damaged and have been restored: 0xBFC40000 = 0x03E00008, 0xBFC40020 = 0x348414503C04BF80, 0xBFC40400 = 0; reent pointer restored to 0x0042CF58; 0x1E000000 restored to 0).  Unmapped addresses (0x08000000..) read 0 and drop writes, so `reent = 0x07FFFF58` makes `rand()` return exactly 0 forever (ld -> 0, `0*A+1 >> 32 = 0`): **r = 0.0 constant** (all rolls succeed: crit whenever `guard == 0`, evade whenever the rate is >= 0).  That is a clean tool but only for r = 0; no other constant is reachable.

### 9.2 Evade and critical rate -- what `PAtkHitSet` really does (US BATTLE.BIN decompilation) and what was measured live

Read from the decompilation of `PAtkHitSet` (0x005fa8c0 JP; the US build is identical in this part) and re-checked against the live game; order of events for one physical hit:

1. `GetPAtkDamage` first: damage chain, then `CheckGuard` (class 0 none, 1 partial, 2 full, 3 counter stance, 4 forced), then -- **only for guard class 0** -- the crit roll `rand()/2.1474836e9*100 <= critRate` (+20 / +10 low-sanity PCs).  One `rand()` per hit, before the evasion roll.
2. Guard factor on the damage (not in `GetPAtkDamage`): class 4 -> 0, 3 and 2 -> 0.5, 1 -> 0.25, else 1 (`rules::guard_damage_factor`).
3. Evasion roll: **only if guard == 0, or the hit would kill the defender** (`hp <= damage`): `rate < rand()/2.1474836e9*100` => hit (so evade iff `roll <= rate`, the same inequality as `rules::roll_percent`).  The rate is `GetEvasionRate` (formula unchanged: `(AGLdef-AGLatk)*2.5/98 + 5 + LUCdef*5/99`, then kind 0x1c status / passive modifiers, PC global stat 3, char 6 difficulty), plus
   * `+ nFormation * (LUC/10 + 8)` while a party member is in `bState == 0x14` (a command stance; Nicolai / Karin idle are in state 7, formation index 1),
   * `+ 10` when the damage would kill a party member (`hp <= damage && flagsB bit0 == 0`).
4. **Forced hits** (no evasion roll at all): attacker `bState == 0xc`; defender `bState` in 0x16..0x26 (hit-reaction / downed states, set to 0x16/0x17 by every landed hit -> a second attack arriving while the defender still flinches always lands); the attack comes from behind (|angle| > 90 degrees between the attack vector and the defender's facing); the target would be outside the arena rectangle; `a8 == 0xb` (a special call); and guarded defenders (see above).
6. Damage is applied only on the hit branch (`wVulnCount += 1`, `field_0x462` = last damage s16, `+0x470/+0x474` cumulative); an evaded attack leaves HP untouched, which is what the live checks below use.

Port before: guard factor missing; evasion rolled *before* the crit roll and also for guarded defenders; the roll was consumed even when guarded; no lethal bonus.  Port after (`sh2_battle::flow::do_attack`, `rules::{guard_damage_factor, evasion_roll_applies, LETHAL_EVADE_BONUS}`): same order as the game, lethal +10 %, guard gating.  Not modelled (no positions / hit-reaction states in the port): rear-arc and hit-reaction forced hits, the stance-0x14 formation bonus.  Tests: `rules::tests::guard_and_lethal_gate_the_evasion_roll`; 89 sh2_battle tests green.

Live samples (US, natural `rand()`, single enemy A hammering Nicolai, nothing else alive; A's AGL 235 gives the 4.0 turn-interval floor so it attacks ~25x per party action; `hits` is `HP lost / one hit`, one non-crit hit = 150..156 HP with PATK 220 vs PDEF 100):

| batch | settings (cached stats) | formula | attacks | HP lost | mean / attack | reading |
|---|---|---|---|---|---|---|
| E1 | Nic AGL 44 LUC 255, A AGL 235 LUC 0 | evade 5 + (44-235)*2.5/98 + 255*5/99 = **13.006 %**, crit 5.0 % | 24 | 3424 | 142.7 | hit share 0.89 |
| E2 | same | same | 25 | 3480 | 139.2 | hit share 0.87 |
| E1+E2 | | | 49 | 6904 | 140.9 | evade **12 % +- 5** (expected 13.0) |
| X | Nic LUC 30, A LUC 255 (crit 5 + (255-30)/5 = **50 %**, luckf +0.115) | | 27 | 5510 | 204 | |
| Y | Nic LUC 30, A LUC 30 (crit 5 %, luckf 0) | | 28 | 4758 | 170 | X / Y = **1.20 +- 0.13** (model 1.36: crit 1.22 x luck 1.115) |

* Both macro checks are consistent with the decompiled formulas, at the power the 1-minute samples allow (they would have flagged a wrong slope: crit 50 % vs 5 % gives a clearly visible damage jump; evade 13 % would read 5 % or 25 % if the LUC / AGL terms were off).  Isolated crits show as 1.5x the normal hit (150 -> 263 at constant stats).
* Boundary scan with the constant roll r = 0.0 (rate >= 0 evades): A at AGL 200 (formula rate 1.02): all ~8 consecutive attacks evaded; at 209 / 218 / 235 / 240 (rate 0.79 / 0.56 / 0.13 / 0.0): hits.  The formula boundary is a = 240; the hits right above 200 are either an additive -0.8..-1.0 on Nicolai's evasion (an accessory / status kind 0x1c) or the forced hits of consecutive attacks (state 0x16 flinch), I could not separate the two with the one-defender setup.  Nothing in the port depends on it.

### 9.3 Starting a battle straight from the field (new tool) + the first fight's enemy count and rewards

**Direct battle start** (found in the `SSHSys::PollingApi` decompilation, `decomp/A/SSHSys.c`, confirmed live): `SSHSys` (0x749500) `+0x40` is the `_SysBtlParam` of the last battle (`w0` = 77, the tower hall / corridor background id; `+4` = `MONSETTbl` index, was 6; `+8 bgm` 0x191; `+0xa` pc count 2; `+0xb` monster-set count 1; `+0xc` pc ids).  Write the index at `0x00749544`, then the request byte `0x00749536 := 0x21` and the game builds the battle socket and the battle within ~5 s (`ourBtlSocket` 0x43FD5C becomes non-zero, CBattle* 0x440000 = 0xA09870 on this baseline).  Request 0x10 + the next map name at `SSHSys+0x58` is the field analogue, but only works from a state without a live `CField` (after a battle); from a live field it leaves the socket in phase 7 and a black screen forever.  Caveats: (1) the field is not unloaded/preloaded properly, so after the battle the game returns to a black screen (reload the state); (2) the tutorial prompt of set 4 cannot be answered with injected pad words (below).

| fact | live (US) | port |
|---|---|---|
| MONSET 2 (random encounter set of AP_03_U) | CBattle formation u16 @+0x4646 = 4, ids @+0x4648 = {0,0,1,ffff,ffff,ffff}; 3 enemy slots (2,3,4): Revenant x2 (HP 17) + Statue (HP 25) | `MonSetTbl` formation 4 -> `monster_count()` 3, same ids |
| **MONSET 4 = first scripted fight** (`InvokeBattleTbl 0`, BBTL row 0 = background 77) | formation 6, ids {0,0,0,0,ffff,ffff}: **four live enemy slots (2..5, flagsA 3, flagsB 1), four Revenants**; the intro camera shows three at first, the fourth is behind the "Battle Basics" window. Only this set (flags/battle type) raises the "Battle Basics: Learn about battle basics / Skip it" prompt, MONSET 2 does not | formation 6 -> 4 monsters (was already right: the earlier note "three" was a camera artefact) |
| victory screen, MONSET 2 (killed by a berserk party; Karin Lv 1 / Nicolai Lv 2) | "You Get! **Exp. 5**, **Cash. 40**" (NEXT 76 / 32), CBattle result record `+0x48b4` exp = 5, `+0x48b8` cash = 40, `+0x48bc` SP = 0, trophy rows `{0x0a, 0x0a}` chance bytes and counts `{1,1,1}` right behind | Revenant 1 exp / 10 cash x2 + Statue 3 / 20 = 5 / 40: test `bridge::tests::us_encounter_rewards_match_the_live_result_record` (build_setup sums and a headless fight) |
| MONSET 4 reward | not played to the end (the prompt could not be dismissed) | 4 exp / 40 cash from the same per-monster values |

Other measured details: the retail attack command menu is `Attack < Standard >` / `White Magic` / `Items` / `Defend` / ... with the cursor on Attack, `Attack enemy and push them backwards.` as the help line; one press of the first entry goes straight to phase 5 (a single press selects Attack **and** the preselected first target).  The retail attack cycle for an enemy with AGL 235 against Nicolai took about 3.4 s of game time per attack at 30 fps (phase 5 steps 4/5 then 0x14 step 0x64/0x65 for the turn end).  CBattle phase map seen: 1 intro (step 0x14 = tutorial prompt wait, step 100 leaves), 2 turn selection, 3 turn start (step 0x63 / 0x34 / 0x39 / 0x3b per actor), 4 command menu (step 1), 5 attack (steps 0..5, 0x15 enemy), 0xa berserk AI attack, 0x12, 0x14 turn end (steps 0x64 / 0x65), 0x15 victory pose ("Skip" with Cross), 0x17 result window ("You Get!", Cross = End).
The prompt problem: the "Battle Basics" window ignores `core0` word injection both with `CPad::Update` running (registered CPad object 0xB00EC0 or the SSHSys pad 0x749900) and with it stopped; the command menu cursor also ignores d-pad bits (Down = 0x0040 in real/press) and the stick words, only Cross (0x2000) works there.  Writing `CBattle+0x2a := 100` while the prompt is open makes the engine hang (EE loop, speed 9 %, timer frozen) -- do not.

### 9.4 World map and hops (US build)

* `GetWorldMapSection` (US 0x003f7c00) = `FindSection(*(0x0043FE5C), "WM") + 4`; the save-section holder at 0x989DB0 points at the save image at 0x001022EC (`"FLDa"` header, sections `"GS"`, ... each starting with a 2 byte tag).  The `WM` payload (world / sub / extra / per-point bytes at +0xc+id) was not read: the world map could not be reached live in this round (the New Game route froze twice after the title: black screen, SSHSys timer frozen, EE busy; a direct `WORLDMAP` request 0x10 from a live field ends in `CFieldSocket` phase 7 and a black screen).  The previous round's observation (single Apoina point, Cross = confirm -> `AP_00_U`) is the only live data; nothing contradicts `RetailWorldTable` (confirm = US hardware Cross = engine 0x2000).
* **Map hops confirmed live by teleporting the controlled model into the event box** (write the CFieldModel pos 0xCF69C0 and CField+0x2130 player pos 0xB00130; the box fires on the next frame; the map name is `CFieldSocket(0xD6E860)+0x64`):

| from | box (centre) | to | arrival (entry) |
|---|---|---|---|
| AP_03_U | id 1 (134.87, 0, -86.81) | **AP_10_U** | entry 1 (120.36, 0, 106.17) |
| AP_10_U | id 1 (103.90, 0, -121.37) | **AP_02_U** | entry 1 (151.67, -22.08, -0.41), the east side |
| AP_10_U | id 2 (105.74, 0, 119.94) | **AP_03_U** | entry 0 (143.86, 0, -68.51) |
| AP_02_U | id 2 east door (150.79, -22, 13.85) | AP_10_U (static) | **did not fire** from a teleport into the box nor from Cross presses; kind 1 / group 4 / flags 0x14 boxes are "door" events (probably need the walk-in with the right facing, or script conditions of the first visit) -- not confirmed live |

  So AP_10_U <-> AP_03_U and AP_10_U -> AP_02_U are live-confirmed, with the same entry ids the port's scripts use; the forward leg AP_02_U -> AP_10_U is still static only.  The AP_02_U ring box (event 7, 0.66, 0, 21.93) did not start the scripted fight from the baseline save (its flag 6416 is probably already set in this save).
* Walking in AP_02_U with the stick words (gauge 0x0074970C = 1.0, degrees 0x00749714 = 0, `CPad::Update` off) works (run, +z at stick 0 in that camera); right after arrival through a door box the model does not move (arrival script / latched control).

### 9.5 Attack presentation timing (for the battle agent) -- what could and could not be measured

* Sampling positions / frame counters during an attack needs a time resolution of one 30 fps frame (33 ms) while one MCP round trip is 3-5 s of game time at 100 % speed; the requested 10 % slow motion was never switched on (the relay did not arrive), so **no per-frame position series, run-up easing or hit-stop frame counts were captured** (a BtlChr position field was not found either: `+0x20..0x74` are zero at rest, floats appear there only during the victory pose; `aPos` is not at the JP-shifted offset).  Nothing in the port was changed for it.
* Coarse timing that was measured (game time = sys timer `SSHSys+0x1c`): one enemy attack of an AGL >= 219 enemy against Nicolai, from the previous `TurnEnd` to the next, takes about **3.4 s** (phase 3 step 0x39 turn start -> 0x14/0x64..0x65 -> 5/4 -> 5/0x15 hit -> 3 next turn), ~100 game frames; the party's own attack action (menu press -> ring -> result -> turn end) took 6-10 s with an unpressed ring.  A fresh Nicolai with the plain Attack command: press -> phase 5 within 2 frames.
* Seen on screen (attract battle, port-relevant UI, `screencapture -l <armsx2 window id>` works while the window is covered): the Judgement Ring result HUD at the top left of the target: `<portrait> 2Hit 13Damage EvaRate-30%` (hit count, total damage and the **target's evasion change from the weapon's ring effect**: a status record of kind 0x1c percent -30 on the target for the hits' grade), grade words floating next to the ring `Strike!!` / `Good!!` / `Miss!!`; the ring graphic is a dark disc with a gold arc for the hit area and a red strike sector, drawn centred on the attacker's screen position.
* Per-hit ring grades of a 2-hit combo are the ones of section 2/3 (`GetJRingAreaResult` takes the hit index, grade 1 -> base x damage mult, 2 -> percent, 3 -> strike mult): (100 %, 100 %) = 18 total and (100 %, strike) = 20 on Revenant A, already in the port (`ring_hits`).  A *party combo* (Link) was not exercised.
* The hit-reaction state also matters for timing: every landed hit sets the defender's `bState` to 0x16/0x17, and while it stays in 0x16..0x26 the next hit cannot be evaded (section 9.2).

### 9.6 Measured vs port (this round)

| quantity | live (US) | port before | port after |
|---|---|---|---|
| evasion rate formula `(dAGL*2.5/98)+5+LUCdef*5/99` | 12 % +- 5 evaded vs 13.0 % predicted (49 attacks); formula read from `GetEvasionRate` (US) | same formula | same |
| crit rate `max((LUCa-LUCd)/5,0)+5` | damage ratio 50 %-crit vs 5 %-crit batch 1.20 +- 0.13 (model 1.36); crit 1.5x isolated | same formula | same |
| order of rolls in a physical hit | `GetPAtkDamage` (guard roll, crit roll) -> guard factor -> evasion roll | evasion roll first, also when guarded, no guard factor | damage + crit first, guard factor 0.25 / 0.5 / 0.5 / 0, evasion roll only if guard 0 or lethal |
| lethal-hit evade bonus | `+10 %` for a party member (`hp <= damage`), guard bypassed | none | `rules::LETHAL_EVADE_BONUS`, `evasion_roll_applies` |
| first fight enemy count (MONSET 4) | **4** live slots (formation 6), "Battle Basics" prompt | 4 (BBTL row 0 -> set 4) | unchanged (comment fixed: three = camera artefact) |
| first encounter payout (MONSET 2) | Exp 5, Cash 40 (result record +0x48b4 / +0x48b8) | 5 / 40 | same (new test) |
| hop AP_03_U -> AP_10_U -> AP_02_U, AP_10_U -> AP_03_U | confirmed (entries 1, 1, 0) | static | documented in `retail.rs`; AP_02_U -> AP_10_U east door still static |
| world map confirm / WM bits | not reached (see 9.4) | per previous round | unchanged |
| attack run-up easing / hit-stop | not measurable at 100 % (see 9.5) | none | none |

### 9.7 Writes of this round (address: old -> new)
All restored by `pine_load_state(13)` (own baseline) at the end; no code was patched, no pad registration left changed.
* `0x0042D248` rand reent pointer 0x0042CF58 -> 0xBFC3FF58 / 0xBFC3FF78 / 0xBFC40358 (ROM-window experiments) and 0x07FFFF58 (rand == 0 test) -> back to 0x0042CF58; BIOS window qwords 0xBFC40000 / 0xBFC40020 / 0xBFC40400 written by `rand()` and restored to their original contents; 0x1E000000 1 -> 0; 0x08000000 5 (dropped).
* BtlChr cache fields of the live battle: see 9.1 (HP, SP, AGL/LUC, PATK, PDEF, flagsA, timers); CBattle `+0x2a` 20 -> 100 (hang, state reloaded).
* `0x00749536` SSHSys request 0 -> 0x40 (title), 0x21 (battle), 0x10 (field name; stuck state); `0x00749544` btl regdatId 6 -> 4 / 2; `0x00749558` field name "AP_03_U" -> "WORLDMAP" / "AP_00_U" (stuck state).
* Pad: `0x007496F8` (u64 real/press words), `0x007496FA/FC/0x00749702` u16, `0x0074970C` gauge, `0x00749714` degrees, `core0+4` 0x00B00EC0 <-> 0 / 0x00749900.
* Teleport: CFieldModel pos 0x00CF69C0..C8 and CField player pos 0x00B00130..38 (see 9.4).

## 10. Windows / PCSX2 DebugServer round (2026-10-13)

Driven from Windows with the pcsx2 MCP's DebugServer (a second client, `tools/live/dbg.py`), posted keys and a window grabber (`tools/live/`).  Save states: slot 9 = new-game world map tutorial, 8 = AP_02_U free control before the fight, 7 = Nicolai's command menu in the first fight, 6 = AP_02_U after the first fight, 5 = foot of the east stairs after both scripted fights.

* **East door confirmed live** (replaces the "did not fire" row of 9.4): the first AP_02_U visit has two scripted fights -- the ring at the hall centre starts MONSET 4 (four Revenants, "Battle Basics" prompt; reward screen Exp 4 / Cash 40 = the port's expectation `(4, 4, 40)`), and walking on towards the east stairs starts MONSET 5 (a "Combos" prompt first; `SSHSys+0x44` read 5).  With both won the east door is passable and the loaded map data becomes `AP_10_U` (`SBD` header at 0xfd01a4); the script's own door table lists `AP_00_U`, `AP_10_U`, `AP_09_U`.  Before the fight the door is locked (consistent with 9.4's failed teleport / Cross tests).  A door jump does **not** go through `SSHSys` (`+0x36` request, `+0x58` next map stay 0 / `AP_02_U`): it is `FieldMapJump` inside the field overlay.
* **World map `WM` section** (save image 0x1022EC + 0x9a0, tag `WM`, units 5): new game = world 0, selection 1, `extra` 1, payload byte 9 = 1 already while the screen tutorial is showing (the flag is set when the screen opens, `worldMap::initialize`), availability byte of point id 1 (Apoina, `AP_00_U`) = 0x02 (open, not "new"), all other points 0.  Unchanged by the tutorial close and by confirming Apoina.  All of it equals what `sh2_field::worldmap_plugin` assumes (`tutorial_for`, `payload[0xc + id]`).
* **Attack timing / knock-back**: `notes/integration/battle_runup_live.md`.
* Ring bot facts: the live ring object is referenced by `CBattle+0x45d0` (and +0x4b78); Nicolai's areas (169, 90, 14) / (279, 72, 11), Karin's (35, 60) / (215, 60); periods differ per actor, so look the ring up by that pointer, not by a 1.6 s period.  A key hold below 0.12 s is lost (30 Hz pad read).
* `sh2_battle` tests: 203 pass with `--test-threads=1`; in a parallel run `actions::tests::real_tables` can fail because `boot::is_retail()` is global state shared between tests (pre-existing, not touched).
