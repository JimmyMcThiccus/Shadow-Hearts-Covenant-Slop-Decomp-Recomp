# Floor dust: `DownSmoke`, `DownHitSmokeCall`, `FrictionSmokeCall` (2026-10-19)

Port: `sh2_battle/src/down_smoke.rs` (pure logic + `drive_smoke` system, 4 unit tests), registered in `plugin.rs` beside the combo form.
Source: `decomp/H/{DownSmoke,DownHitSmokeCall,FrictionSmokeCall}.c`; the US build constructs them from `decomp/I/us_battle_aiinit.c` (Friction at the
slide states 0x12 / 0x15 / 0x1a ..., DownHit at 0x1e and the launch landings).

## Retail behaviour (ported)
* `DownSmoke`: one billboard from the 512 x 128 sheet of `BTL_000` (12 frames of 64 px, 8 x 2, `frame = age * 30`, dead after frame 11 = 0.4 s; US section 17, JP
  JRCTex index 14 -- found by its size); half size `((ex + ey + ez) / 3 + 4) * 0.75` of the BBox extents; position by kind (0 floor `y = -3`, 1 / 2 the `+-z`
  walls, 3 / 4 the `-+x` walls at `half - 3`); `kind & 8` drifts away from the fighter (`normalize(pos - fighter) / 4` per 60 Hz frame, the wall axis zeroed).
* `DownHitSmokeCall`: every hurt BBox fires once when a corner reaches the floor (`y >= -0.5`, PS2 y down); the launched mode (param 1) also fires per wall (`half - 0.5`),
  the `z` walls only for headings within 67.5 degrees of `z`, the `x` walls only for 22.5..157.5.
* `FrictionSmokeCall`: every 1/15 s one of the friction boxes (grown by 1.2) that touches the floor gives a floor puff.

## Port mapping / open
* Triggers from the port's choreography: `Hit { flyi | blwi }` = launched (walls), `Down` / `EnemyDown` = floor only, `Hit` / `GuardHit` with a push = sliding (friction).
  The retail state numbers behind the US constructors were not mapped one by one (the sites sit in `BtlChrSequence` move states with `MoveWorkInit`).
* The friction list (`bbx` header `+0x10 / +0x14`) is approximated by the hurt-box list; the arena size comes from `StageInfo::dims`.
* Not compared with a live capture (the dust is faint on the debug map floor); screenshots `screens/down_smoke/dust_sheet.png` (port, `SH2_SMOKE_SHOTS=<dir>`).
* Dev aids: `SH2_SMOKE_SHOTS=<dir>`, `SH2_BATTLE_SMOKE=off`.
