# G_retail - the retail (US) field engine

Section G, second pass. Programs: `SH2US_FIELD.BIN` (raw import, base 0x0045ea80) and `SLUS_210.41` (main). JP references: `SH2JP_FIELD.BIN` (base 0x00430a00), `SLPM_602.19`.

## Result in one paragraph
The retail field engine is **not a rewrite**. Same source, same function order, same constants, same data formats - compiled with a different code generator (the JP demo overlay spills every local to the stack and calls
every `FVector` operator; the retail one is register-allocated with the VU0 vector math inlined, 10-25 % smaller). That is why opcode-skeleton matching failed (best similarity < 0.3). Aligning the two builds with an
ordered DP over (callee identity, float/int constant multiset, size, structure, caller sets), anchored by the 8-byte chunk tags and the vtables, maps **435 overlay functions** (CField 181/201, CFieldModel 79/111, CNaviMap 30/32,
CFieldBG 20/24, CFloorMan 8/9, CFieldEvent 7/8, CFieldCamera 7/15 + inlined accessors, FldSpline 7/7, FldTeamChange 14/16 ...) and **~85 main-exe functions** (CFieldSocket, CSTGDB, LayerMan, ChrPosSave, CSndBufCache, field save-data accessors).
All names were applied in Ghidra (JP mangled names; `Retail_*` for functions without a JP counterpart).

## Files
| file | content |
|---|---|
| `us_map.txt` | `jp_addr us_addr name conf sizes` for every mapped function + retail-only list |
| `CField.md` | controller: layout (size 0x2770), flag repacking, differences, ~430 method rows |
| `CFieldModel.md` | actor: layout (0x340), movement identity, SetDir, sight test, menu hide |
| `CNaviMap.md`, `CFieldBG.md`, `CFieldCamera.md`, `CFloorMan.md` (+CFieldEvent) | per class |
| `CFieldSocket.md` | main-exe socket, loading-screen hand-off, start callback, CSTGDB, LayerMan, ChrPosSave |
| `../../decomp/G_retail/*.c` | cleaned C of the lifecycle: Init/Start/InitSDB/Polling/CameraUpdate/UpdateFieldCamera/GetNearestPath..., TransCallBack deltas, socket Polling, CSTGDB |
| `../../port/crates/sh2_field/src/{retail,camera,field,socket,fld_ops}.rs`, `tests/retail_us.rs` | Rust port |

## Retail vs demo - what actually changed
1. **Code generation only** for ~95 % of the engine (verified: identical constants in all but ~17 aligned pairs, identical switch/case sets, identical chunk tags).
2. **Layouts**: `CField` 0x2330 -> 0x2770 (flags re-packed, +0x300 byte block, ObjSE slot 0x28 -> 0x2c), `CFieldModel` 0x2e0 -> 0x340, `CFieldCamera` 0xd0 -> 0xf0 (+camera FX offsets), `CFieldBG::Impl` 0x1d4 -> 0xc0, `CFieldSocket` 0x6c -> 0x74, CNaviMap same size with a new animation block.
3. **New features** (code that does not exist in the demo): field monster sight (`TRILIST`, op 0x1b), event boxes as walls (`SweepHit`), camera sway/blur FX (op 0x77), map loading screen phase (0x40/0x41, world-map sub-state 8), socket start callback, SSHSys request 0x40 (leave to title/opening),
   saved-position start in `InitSDB`, FldTeamChange created in `Init`, the remaining new script ops (0x2b, 0x2f, 0x4c, 0x4d), NaviMap pulsing markers.
4. **Retuned logic**: camera follow ease (0.99 -> 0.98, extra 0.92 damping, dead tracking branch), `clipRadian` loops, `SetDir` turn handling, `UpdatePathMove` arrival rule, `LoadFace` defaults.
5. **Data now exercising old code**: `MIRROR` (23 maps), `BGCOLOR` (49), kind-4 cameras (7), rounded-corner rail cameras (15 rails, mode bit never used by the demo data), 559 maps (demo 43).
6. **Unchanged and re-validated on retail data**: `CFloorMan`, `CFieldEvent::HitCheck`, `TransCallBack` collision/slope constants, camera kinds 0-3 and nearest-segment rails.

## Open questions
See the last section of `CField.md`; additionally: the retail `GENERIC` names other than `VIBRATION` and `TRILIST` (none occur in the US maps), the purpose of the 0x300-byte block in `CField`, `SweepHit` details,
and the exact semantics of the 16 byte records `FieldMessage`/`FaceImage` share with `CField` windows (those classes belong to the message system and were only mapped where `CField` calls them).
