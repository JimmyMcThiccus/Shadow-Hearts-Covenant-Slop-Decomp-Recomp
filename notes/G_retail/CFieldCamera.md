# CFieldCamera and the CAMERA table - retail (US)

Ghidra `SH2US_FIELD.BIN` 0x005061c0 - 0x00506c20 (JP 0x004be190 - 0x004bef20, 15 methods; **7** named + `SetTargetPos`, `CompSnap`; the 8 accessors are inlined).
Object size **0xf0** (JP 0xd0): layout identical up to +0xcc, then two new FVectors (JP layout: `notes/G/CFieldCamera.md`).

_Generated tables use the JP mangled names as canonical keys. conf: A = anchored by chunk-tag constant / vtable, H = ordered call-graph + constant alignment (score >= 0.55), M = ordered alignment (< 0.55, tiny functions whose callees were inlined), C = hand-corrected or exact match from section G._

## Layout additions

| off | meaning |
|---|---|
| +0xd0 | FVector camera **position offset** (camera FX), added to the composed camera position in `Apply` |
| +0xe0 | FVector angle offsets: `.x` pitch, `.z` roll (added to `+0xc0` / `+0xc8` before the rotation matrix is built), `.y` unused |

Both are written by `CField::CameraUpdate` -> `Retail_CField_EvalCamBlurFx` (script op 0x77) and stay `(0,0,0,1)` otherwise, so the demo `FieldCamera::apply` is the retail one with zero offsets.

## UpdateFieldCamera (CAMERA table kinds)
`CField::UpdateFieldCamera` (US 0x004f4ef0, 0x1590 bytes; JP 0x004a8be0, 0x1a00) is the same switch: kinds 0 fixed, 1 follow, 2 relative, 3 pivot + angle limits, 4 pivot + limits + 100-unit leash,
5 spline rail (nearest-segment mode or rounded-corner mode when node 0's flag word has bit 1 set and no high byte). Retail data (559 maps): kind 0 x1432, 2 x18, 3 x184, **4 x7**, 5 x995 (15 rails use rounded mode, none uses a sharp-corner node).
Ported in `sh2_field::camera`: `eval_camera` now covers kinds 0-5 (`pivot_aim`, `get_nearest_path`, `get_cam_path_a`, `get_cam_path_2`, `fld_spline_position`).

* Kind 4 = kind 3's aim point `B`; the camera sits on the pivot `A` while `|A-B| <= 100`, else at `A + (B-A) * 100/|A-B|`; the target is the player (y-12).
* Rounded mode: `GetNearestPath` returns either `1000 + node` (node flag bit 0: sharp corner -> `GetCamPath2` blends the two neighbouring segment cameras 50/50 weighted by the player's position along each leg) or a fraction on
  segment `seg` (corner fillets of 5%..50% of the shorter leg are computed in plan view). `GetCamPathA` evaluates a **cubic uniform B-spline** (`FldSpline`, JP 0x4bc0a0 / US 0x504810) through the node targets and cameras of the run delimited by nodes whose
  word at +0x3c equals the float 2.0; the camera spline carries the u16 FOV (0 -> 320) in lane w, and because the accumulator starts at w = 1.0 the resulting angle is `(fov + 1) / 512`.
* Verified on US data: 1783 samples along the 15 rounded rails, largest camera step between 2-unit player steps = 3.0 units (continuous), `tests/retail_us.rs::us_rounded_rail_cameras_are_continuous`.

## Method table
| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004aa710` | `004f6480` | `bComp__12CFieldCameraFv` | H | 40/30 |
| `004be260` | `00506200` | `__dt__12CFieldCameraFv` | H | 60/50 |
| `004be2c0` | `00506250` | `Init__12CFieldCameraFv` | H | 170/140 |
| `004be450` | `00506390` | `SetTargetPos__12CFieldCameraF7FVector` | C | 70/40 |
| `004be4c0` | `005063d0` | `SetViewAngle__12CFieldCameraFf` | H | 80/50 |
| `004be540` | `00506420` | `Apply__12CFieldCameraFf` | H | 980/790 |
| `004bef20` | `00506bb0` | `CompFrame__12CFieldCameraFf` | C | 80/40 |

`FldSpline`:
| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004bc080` | `00504810` | `Clear__Q29FldSpline6_flagsFv` | H | 20/20 |
| `004bc0a0` | `00504830` | `__dt__9FldSplineFv` | H | 60/60 |
| `004bc100` | `00504890` | `Release__9FldSplineFv` | H | 80/70 |
| `004bc180` | `00504900` | `SetPoint__9FldSplineFUiP7FVector` | H | 60/30 |
| `004bc1e0` | `00504930` | `Create__9FldSplineFUiUiP7FVector` | H | 170/110 |
| `004bc350` | `00504a40` | `GetPosition__9FldSplineFf` | H | 4d0/350 |
| `004bc820` | `00504e50` | `isCreated__9FldSplineFv` | H | 30/20 |

### JP methods without a US counterpart (inlined)
`SetViewDelay` (JP 004a34a0, 0x30), `CompClear` (JP 004a3960, 0x20), `GetCameraAngle` (JP 004a82a0, 0x40), `GetCameraPos` (JP 004a89b0, 0x40), `SetCameraPos` (JP 004aa5e0, 0x40), `GetTargetPos` (JP 004aa620, 0x40), `SetCmpMode` (JP 004ab820, 0x40), `__ct__12CFieldCameraFv` (JP 004be190, 0xd0)

### Retail-only
| US addr | size | name | role |
|---|---|---|---|
| `00506bf0` | 0x30 | `Retail_CFieldCamera_CompSnap` | `CFieldCamera::CompSnap`: copy target/camera/final to the transition "from" slots and clear the transition timer |
