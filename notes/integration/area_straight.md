# `StraightArea` / `StraightCircleArea` ground markers (2026-10-19)

Port: `sh2_battle/src/area.rs` (`straight_marker`, `wall_distance`, `marker_for`, `MeshBuf`; `ui::Area::line_width`); `decomp/H/StraightArea.c` (JP 0x00538280 `MakePacket`),
`StraightCircleArea.c` (0x00539780 ..), constructors in `decomp/H/BtlMenu.c` 7700..7760.

* Shapes (`(rec[5] & 0xf) >> 1`): 3 = `StraightArea` (half width 7.5 / 12.5 / 17.5 for size 0 / 1 / 2), 4 = `StraightCircleArea` (half width 7.5, circle radius 20 / 30 / 40 for size 0 / 1 / 2).
* `StraightArea::MakePacket`: start = caster feet + `dir * its box radius` (`+0x3b0`), `dir` = unit vector caster -> chosen target (xz), length = distance to the arena wall
  (`min` of the x / z wall distances, 500 when parallel); 16 vertices: the floor strip at y = -0.2 and the two side walls (height = the half width) at the columns `0`, `10`, `len`, `len + 10`;
  orange (0xff, 0xa0, 0x20).  The alpha profile (floor 0 -> 0x70 -> 0x70 -> 0, walls 0x10 bottom / 0x30 top, 0 at both ends) is read from the packet's colour words, the vertex order
  of the strips was not decoded.
* `StraightCircleArea`: the beam from the caster up to the target's circle (circle alone when the target is within its radius).  The original's tangent-angle treatment (`asinf(w / R)`)
  of the beam's end is simplified: the beam stops at the circle's radius.
* The meshes of the beam shapes are built in world space and rebuilt when the caster / target move (`AreaMarker::key`); the circle keeps its local mesh.
* Dev aid `SH2_AREA_FORCE=<shape>:<size>` shows that marker on every target page (use the battle dev drive without `--autoplay`); screens: `screens/area_straight/beam_beamcircle_circle.png`
  (shapes 3:1, 4:2, 1:1).  Not compared with a live capture (needs a beam skill such as one of the monster / PC beam attacks on the target page).
* Members (`area::beam_members`, `GetTargetList` types 3 / 4, CBattle.c 61130..): inside the circle (shape 4), or in front of the caster (< 90 degrees off the caster -> target line)
  and within `half width + box radius` of that line; used by the red arrows and the group camera (`current_members`).  Whether the battle rules' own target list (damage) uses the same rule
  was not checked (`flow.rs` area attacks).
