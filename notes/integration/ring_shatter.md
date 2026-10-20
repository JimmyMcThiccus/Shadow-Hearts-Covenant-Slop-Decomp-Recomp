# Ring closing animations: `CutJRing` / `CrackJRing` (2026-10-19)

Port: `sh2_gfx::effects::jring_shard` (simulation + `MakePacket` geometry, 3 unit tests), `JRing::shard` (`ShardAnim`, now holds the simulation and takes the ring RNG),
`sh2_battle::hud_hits::{draw_shard, cam_project}` (drawing; `draw_ring` hands over while a shard exists).  Source: `decomp/D/JRing_Shard.c`.

* Battle rings end with `SetMode(5, 1, 1, 4, 3)`: a hit = end kind 4 = **CutJRing**, a strike / critical = kind 3 = **CrackJRing**, a miss = kind 1 (shrink).
  Both were only tracked for their life / clock before; nothing was drawn.
* `CutJRing`: random cut angle `x`; two 17-point half discs (fan from the disc centre, ring texture 1, uv = disc px + 128) whose origins sit
  +-57 px from the centre along the cut normal.  `Update`: origin += 8 * origin * dt (the factor decays x - x/6 * dt * 60), z spin += 3 * +-0.2792 * dt
  (3 decays 4.5 / s); life (alpha = life * 128) decays 1.5 * `+0xb8` / s.  Variant 1 (combo failed): 0.15 s of the same, then the halves fall
  (speed +1 / frame).  Variant 2 (combo ok): 0.15 s screen shake (random +-8 px, fading over the last 0.1 s), nothing moves until 1/3 s, plus the slash streak (0..0.3 s).
* `CrackJRing` (only `Initialize2` is ever constructed: `JRing::MakePacket` passes `param_4 = 1`): 6x6 jittered lattice, 25 cells each quad / "/" / "\" split
  (rejection loop: 2..24 non-quad cells), piece = polygon around its centroid with random X / Y tumble speeds (+-120 deg/s); `Update`: pos += spd * dt * (pos - 128)
  (the original expands about 128 although the face centre is 114: kept), tumble += (spd + 1) * dt * vel, spd = 3 - 4.5 t.  Variant 2 also builds the crack
  lines (lattice points sorted by distance from the centre, each linked to its placed neighbours, diagonals along the cell split, clipped to r = 101) and draws up to
  `t / (1/3) * 80` of them as z-extruded ribbons that fly at the camera after 0.25 s.
* RNG: the original `rand()`; the port draws from the ring's `Rng`, so a given cut / crack pattern is not the retail one for the same seed.
* Dev aids: `SH2_RING_END_OK=3` (crest of a successful ring ends with the crack), `SH2_BATTLE_SHOTS=<dir>` writes `ring_shatter_<n>` (every 0.05 s) with the devdrive.
  Sheets: `screens/ring_shatter/{cut,crack}_sheet.png`.
* Not compared with a live capture; the camera projection reuses `ring_project`.  Open: the slash streak's second (z-shifted, half alpha) pass, per-frame fall speed
  of variant 1 is scaled by dt * 60 (the original adds per frame).
