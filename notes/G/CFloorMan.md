# CFloorMan — floor collision (JP 0x004bc850 … 0x004bde90, 9 methods, object 0x20)

Port: `port/crates/sh2_field/src/floor.rs` (all methods) — validated on the 43 JP + 559 US maps (slice counts always agree with WORLD;
entry points of the JP maps lie on the floor 153/180 times, the rest are unused/duplicate spawn slots; `OnFloorPoint` height agrees within 25 units).

| off | name | |
|---|---|---|
| 0x00 | world | -> `SDB::tagWORLD` (extent, origin, slices) |
| 0x04 | vertices | VERTEX array (vec4) |
| 0x08 | triangles | TRIANGLE array; vertex indices are rewritten to vertex *pointers* on load |
| 0x0c | slices | SLICE index array; each entry rewritten to point at its list, list entries rewritten to triangle pointers |
| 0x10 | cached | last hit triangle |
| 0x14 | slice_along_z | 0 if `WORLD[2] != 0` (slices along X) else 1 |
| 0x18 | slice_count | |
| 0x1c | rot_y | floor yaw (radians, set by `SetRotY(deg)`) |

* `SetData(CSTGDB*)` returns 0 if WORLD/VERTEX/TRIANGLE/SLICE is missing or the slice count mismatches.
* `OnFloorChk(pos)`: cache test (`TriangleChk`) -> bucket by `(int)(count*d/size)` -> scan forward when the other coordinate is in the near half else backward; per triangle `min_c <= other <= max_c` prefilter then `TriangleChk`.
* `TriangleChk`: skips blocked triangles (`+0x16`), three `atan2f(dx,dz)` edge-angle comparisons (π constants 3.141592/6.283184), then `|y - (y0+y1+y2)*0.3333| <= 20`.
* `OnFloorPoint(pos, tri)`: height of the plane, computed in the frame where edge B->C is the Z axis (see `floor.rs`).
* `CircleChk(pos, r)`: centre + 8 samples (±r axis, ±0.707107 r diagonals) must all be on floor.
* `SetObstacle(id, flag)`: toggles `blocked` on all triangles with that `obstacle_id` (doors/gates driven by script).
