# `NormalDeathEfct` (2026-10-19)

Port: `sh2_battle/src/death_glow.rs` (`drive_death_glow`, 2 unit tests).  Source: `decomp/H/NormalDeathEfct.c` (JP 0x0051c960..).

* One additive sprite (`BTL_000` JRCTex JP 54 / US 36, the soft glow disc) over the screen box of the fighter's body box (8 corners `pos + off +- 2 * size` along the yaw-rotated
  axes); half edge = the larger half extent, 7/6 taller than wide.  Lifetime `t += dt * 3.75` (0.267 s); alpha `196 * min(t / 0.5, 1)`; colour white until `t = 0.5`, then
  to (139, 59, 179) at `t = 1` (GS 0..255, 0x80 = 1.0, so the colour is boosted by 196 / 128).  Spawned with the dissolve of death type 0 monsters (the port's `Act::Dissolve`).
* The port projects the box on the camera axes (a camera facing quad at the box centre); the original projects the 8 corners to the screen.
* The sparkle motes of `models.rs` (`Sparkle`) are kept: they are the separate `EffMdl` the same state starts.  Screens: `screens/death_glow/glow_sheet.png`
  (`SH2_SMOKE_SHOTS=<dir>` writes `deathglow_NNN.png`; `SH2_DEATH_GLOW=off` disables).  Not compared with a live capture.
