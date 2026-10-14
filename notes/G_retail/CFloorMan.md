# CFloorMan (+ CFieldEvent) - retail (US)

Ghidra `SH2US_FIELD.BIN` 0x00504e50 - 0x00506200 (JP 0x004bc850 - 0x004bde90, 9 methods; **8** matched, the constructor is inlined into `InitSDB`).
Object size 0x20, layout `{world, vertices, triangles, slices, cached, slice_along_z, slice_count, rot_y}` identical to JP (`notes/G/CFloorMan.md`).
`SetData` (0x504ec0) uses the same four chunk tags (`WORLD`, `VERTEX`, `TRIANGLE`, `SLICE`) and rewrites indices into pointers the same way; `OnFloorChk` / `TriangleChk` (3 `atan2f` edge angles + the +-20 window around `(y0+y1+y2)/3`) /
`OnFloorPoint` / `CircleChk` (centre + 8 samples, +-r and 0.707107 r) are the same algorithms with the vector math inlined. **No behavioural change**: `sh2_field::floor` is used unchanged.
Validation on retail data: all 558 maps with a SLICE chunk build (slice count == WORLD), 1427 of 1813 ENTRYPOS points lie on the floor, 4832 simulated walks (`step_forward`) never leave it.

_Generated tables use the JP mangled names as canonical keys. conf: A = anchored by chunk-tag constant / vtable, H = ordered call-graph + constant alignment (score >= 0.55), M = ordered alignment (< 0.55, tiny functions whose callees were inlined), C = hand-corrected or exact match from section G._

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004bc8a0` | `00504e70` | `__dt__9CFloorManFv` | H | 60/50 |
| `004bc900` | `00504ec0` | `SetData__9CFloorManFP6CSTGDB` | A | 430/2e0 |
| `004bcd30` | `005051a0` | `SetRotY__9CFloorManFf` | H | 110/d0 |
| `004bce40` | `00505270` | `SetObstacle__9CFloorManFii` | H | b0/70 |
| `004bcef0` | `005052e0` | `OnFloorChk__9CFloorManF7FVector` | H | 690/570 |
| `004bd580` | `00505850` | `TriangleChk__9CFloorManFPQ23SDB12tagFTRIANGLE7FVectorP6Matrix` | H | 570/3d0 |
| `004bdaf0` | `00505c20` | `OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE` | H | 3a0/330 |
| `004bde90` | `00505f50` | `CircleChk__9CFloorManF7FVectorf` | H | 300/270 |

### JP methods without a US counterpart
`__ct__9CFloorManFv` (JP 004bc850, 0x50)

# CFieldEvent (EVENTBOX / CAMEVENT)

Ghidra 0x00506c20 - 0x00507760 (JP 0x004befa0 - 0x004bf770). Object `{count, is_camera, boxes*}` (0xc bytes). `HitCheck` (0x506c90), `GetEventNum`, `GetEventBox`, `GetEventBoxFromID`, `GetEventBoxFromGroup` are unchanged;
`Init` is inlined into `InitSDB` (0x506c80 = `Init`). Retail adds **`Retail_CFieldEvent_SweepHit`** (0x507010): given an EVENTBOX index and a movement segment it transforms the box corners (`Rx`, `Ry` of `box+0x20/+0x24`, translate `box+0x10`) and the segment extended by
5 units along its direction, finds the nearest crossed edge and writes the slid position back - the box is used as a wall for the controlled model.

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004befa0` | `00506c20` | `__ct__11CFieldEventFv` | H | 20/10 |
| `004befc0` | `00506c30` | `__dt__11CFieldEventFv` | H | 60/50 |
| `004bf0b0` | `00506c90` | `HitCheck__11CFieldEventF7FVectorii` | H | 460/380 |
| `004bf510` | `00507620` | `GetEventNum__11CFieldEventFi` | H | 70/40 |
| `004bf580` | `00507660` | `GetEventBox__11CFieldEventFi` | H | 70/40 |
| `004bf5f0` | `005076a0` | `GetEventBoxFromID__11CFieldEventFiPs` | H | c0/60 |
| `004bf6b0` | `00507700` | `GetEventBoxFromGroup__11CFieldEventFiPs` | H | c0/60 |

### JP methods without a US counterpart
`Init` (JP 004bf020, 0x90)

### Retail-only
| US addr | size | name | role |
|---|---|---|---|
| `005061c0` | 0x40 | `FUN_005061c0` | `CFieldCamera` pre-constructor (clears +0x30..+0x6f) |
| `00506c80` | 0x10 | `FUN_00506c80` | `CFieldEvent::Init(boxes, count, is_camera)` |
| `00507010` | 0x610 | `Retail_CFieldEvent_SweepHit` | `CFieldEvent::SweepHit(box, p0, p1)`: slides a movement segment along the nearest edge of an EVENTBOX (wall collision against event volumes) |
| `00507760` | 0x80 | `FUN_00507760` | `_FieldDataCache` entry reference release |
| `005077e0` | 0xb0 | `Retail_FieldDataCache_TickN` | `_FieldDataCache` slot aging loop (frees entries whose count reached 0) |
