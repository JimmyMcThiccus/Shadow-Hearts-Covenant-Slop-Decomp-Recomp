# MPS field-map package (and the PKB tree it lives in)

Status: **decoded and validated** on all 43 maps of the JP Furokuban `FIELD.PKB` (`port/crates/sh2_field/src/mps.rs`,
`pkb_compat.rs`, `tests/real_data.rs`). Floor / event-box / camera consumers are ported (see `floor.rs`, `event.rs`,
`camera.rs`). Sources: JP `CSTGDB` (main 0x003c1f60-0x003c2780), `CField::InitSDB` (FIELD.BIN 0x004ab860),
`CFloorMan::SetData` (0x004bc900), `CFieldBG::Create` (0x004da750), `CFieldEvent::*`, `CField::UpdateFieldCamera`.

## 0. Naming

* "MPS" is the *map name* key. A map "AP_00_U" consists of two files in `FIELD.PKB` under `FIELD/MPS/`:
  * `AP_00_U.MPS` – the **SDB** ("stage database", class `CSTGDB`) container described here. Path built by
    `GetMapName(buf, name, 1)` (JP 0x003bd1f0): `sprintf("%sFIELD/MPS/%s.%s", pDataPath, name, "MPS")`.
  * `AP_00_U.MSC` – the compiled map script (kind 0 → `"MSC"`), loaded with `CScript::LoadScript/LoadScriptB`
    (section E). 
* `CFieldSocket::LoadMPS(name)` (0x003c0440) starts MSC load + records the map name; `CacheMPS(name)` (0x003c0630) puts both files
  into `CSndBufCache` (a small LRU of preloaded files, 0x0042bc10 `m_info`); `ReloadMPS` (0x003c06d0) re-reads only the SDB.
  `CFieldSocket::Polling` (0x003bfb60) sequences it: MSC (flag nibble 1/2/3, or preloaded 8/9) → SDB `CSTGDB::Load/LoadCB` (4) → when
  `CSTGDB.state == 2` → `CField::ClearSDB(0)`, `CField::InitSDB(sdb)`, `Restart()`, `CScript::StartScript()`.
* Special map name `"WORLDMAP"` (data symbol `WORLDMAP_NAME` 0x0040a9d4 → 0x4015c8) never loads an SDB; it switches to `worldMap`.
* Map names seen: `AP_00_U … AP_06_U` (Aphrodite?/prologue), `AR_00_S/U … AR_15_U`, `PA_00_S … PA_08_U`, `SM_07_U … SM_17_U`,
  `SU_00_U … SU_40_U` (area prefix, number, `_U` = normal, `_S` = small/special version without models/scripts).

## 1. PKFINFO.TBL / PKB tree (section G derived it independently, then switched to section F's reader `sh2_menu::disc::DiscDir` / `msd::pkf`; both agree on JP and US data)

Derived from `FileIOLib::InitPkb` (0x0022ae70), `deCode` (0x0022ca90), `SearchFile` (0x0022c7a0), `searchInfo` (0x0022c980).

* `PKFINFO.TBL`: 16-byte header (`u16 ?`, `u16 entry_size=0x10`, `u32 body_bytes` = 0x6ef0, …) then 16-byte entries (1775 on this disc).
* Entry: `name[8]` | `u32 runtime_lba` (0 on disc, filled by InitPkb) | `u32 size_or_dir`.
* **Name codec** (`deCode`): 8 bytes → 12 base-40 characters. First big-endian u16 `a` holds three digits `d0=a%40, d1=a/40%40, d2=a/1600%40`;
  the next three big-endian u16 `lo0..2` are the low 16 bits of three 22-bit words `w_i = d_i<<16 | lo_i`; each word gives four digits
  `w%40, w/40%40, w/1600%40, w/64000%40`. Digit 0 = end/blank, digit k≥1 → `".0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_"[k-1]`.
  (The charset table is at JP 0x003fda00.)
* `size_or_dir` bit 31 clear → leaf, value = byte size. Set → directory; low 31 bits = table-body byte offset (file offset − 0x10) of its first child
  **relative to the start of the list the directory entry sits in** (root list base = 0). Lists have no length field; the engine scans
  forward through the table until a name matches (root list ends at the smallest child offset: `Dircount`).
* The u32 at entry+8 is the data offset **in 16-byte units** relative to the parent directory's data base (absolute 0 for root
  archives; `FIELD` → `FIELD.PKB`).
* Example: `FIELD` (root) → `MPS` dir, data base `0x20b0800` in `FIELD.PKB` → `AP_00_U.MPS` offset 0 size `0xf71b0`, `AP_00_U.MSC` at 0x21a8000 size 0x3350.
  Top-level names: `FIELD.BIN BATTLE.BIN BTLDATA COMMON EFFECT MENU FIELD OPENING SAVELOAD WORLDMAP SHOP SOLOMON LSD`.
  FIELD contains `FIELD.DAT FIELD_T.DAT TEAMCHG.DAT EFF IMG MODEL MPS SOUND SKILL.MSD`.
* All members are 0x800-aligned in the PKB (CD sector aligned); 43 `SBD 0.11` files sit at multiples of 0x800 from 0x20b0800.

## 2. Container ("SBD 0.1x", `CSTGDB`)

```
0x00 char[8]  "SBD 0.11" (also accepted: "SBD 0.10")      (CSTGDB::InitSDB compares as u64)
0x08 char[8]  "01110623"  (date stamp, checked)
0x10 char[8]  "FILEHDR "
0x18 u32      total file size
0x1c u32      offset of LINKHDR (=0x20)
@LINKHDR:
  +0 "LINKHDR "  +8 u32 chunk_count  +0xc u32 first_entry_offset (=0x10)
  entries[chunk_count] (16 bytes): +0xc u32 = offset of the chunk header *relative to the entry itself*; +0..+0xb unused (zero)
chunk header (SDB::tagHEADER, 0x20 bytes):
  +0x00 char[8] tag (space padded)   +0x08 u32 record_count   +0x0c u32 data_offset (=0x20, from header start)
  +0x10 u32 "relocated" flag (CFloorMan::SetData sets 1 after turning indices into pointers)
  +0x14.. chunk specific header bytes (only MONSET, FIELD, MIRROR use them)
```
`CSTGDB` object (0x24 bytes): `+0xc BufMemory*`, `+0x10 DvdromOrder id`, `+0x14 state (0 empty, 1 loading, 2 ready)`,
`+0x18 data*`, `+0x1c chunk_count`, `+0x20 chunk_header*[]`. `Find(tag u64)`, `GetDataNum = hdr+8`, `GetDataAddr = hdr + *(hdr+0xc)`,
`FindGenericData(name)` walks the GENERIC chunk with `strcmp` and entry stride `*(u32*)(entry+0x10)`.

The original **relocates in place**: every `u32` "offset" below is rewritten to a pointer (`entry + offset`, or `chunk_base + idx*stride`).
In the file they are plain offsets, relative to the structure that holds them unless stated.

## 3. Chunks (tags exactly as stored; 43/43 maps parse)

Order in file: FIELD MODEL LIGHT WORLD ENTRYPOS [ENMYPATH] CAMERA FOG EVENTBOX CAMEVENT EFFECT VERTEX TRIANGLE SLICE [MONSET] OBJSE [NAVIMAP] [GENERIC].
Presence counts over the 43 demo maps: FIELD/LIGHT/WORLD/ENTRYPOS/VERTEX/TRIANGLE/SLICE 43, MODEL 41, CAMERA/FOG/CAMEVENT 41, EVENTBOX 40, OBJSE 40,
EFFECT 34, NAVIMAP 34, MONSET 29, ENMYPATH 8, GENERIC 4. `MIRROR`, `BGCOLOR` are referenced by the code but never present in the demo data.
Records live inside the chunk; larger blobs (model data, camera blobs, lists) are appended after the record array, addressed by relative offsets.

| tag | rec | description |
|---|---|---|
| `FIELD` | hdr only | header `+8 char[8]` version ("1.309220"), `+0x10 u16` -> `CFieldBG.+0x1ce` byte, `+0x12 u16` bit0 → BG flag (`+0x1c4 bit1`), `+0x14 u8` ≠0 → `LayerMan_LoadLayer(0x558ff0)` (alternate GS layer table). Followed by ~0xe0 bytes of zero padding. |
| `MODEL` | 0x40 | `+0 char[16] name`, `+0x10 u8 kind` (0/1/2 BG model, 3 motion), `+0x11 u8 flags` (`(flags&7)>>2` → ExModel), `+0x14 u32 blob_off` (rel. to record; the model/motion file, "SSH1.01a" magic for models), `+0x1c u32 target_model` (kind 3: which model the motion belongs to), `+0x20 vec4 pos`, `+0x30 vec4 rot` (used as `SetPos`/`SetRot`). Kind 0 = shadow caster (flag 0x81), 1 = shadow receiver (0x82), 2 = plain (0x80). |
| `LIGHT` | 0x40 | `+0 u32` (low 5 bits kind, rest flags), `+4 f32` intensity, `+0x10 vec4` colour, `+0x20 vec4` position/direction, remainder raw. Consumed by main-exe `CBgElement` (section D). |
| `WORLD` | 0x20 | floor frame: `+0 f32 size_x`, `+4 f32 size_z`, `+8 u32 slices_along_x`, `+0xc u32 slices_along_z`, `+0x10 f32 origin_x`, `+0x14 f32 origin_z`, `+0x18/+0x1c f32` (y range?) |
| `ENTRYPOS` | 0x10 | `+0 f32[3] pos`, `+0xc i8 dir` (facing, `SetDir(dir,2,0)`). `CField::GetEntryPoint(i, &dir)`; `i<0` returns the count in `dir`. Selected by `CField+0x2a` (the entry id carried by `MapJump`). |
| `ENMYPATH` | 0x10 | `+8 u16 arg`, `+0xa u16 point_count`, `+0xc u32 off` (rel. to entry) → points `{f32 x,y,z; u32 flags(0xff)}` 16 bytes. Used by field script command 0x19 (`PathMove`) |
| `CAMERA` | 0x10 index + blobs | `+0 u32 kind` (0 fixed, 1 follow, 2 relative, 3 pivot+limits, 4 pivot+spline, 5 spline path), `+4 u32 count` (path nodes), `+8 u32 blob_off` (rel. to entry), `+0xc u8 blend_flag`. Blob: `+0 vec4 pos`, `+0x10 vec4 target`, `+0x20 u16 fov` (view angle = fov/512), kinds 3/4: pitch/yaw limits at `+0x40,+0x44,+0x50,+0x54`; kind 5: nodes at `+0x30 + i*0x40`, mode flags `u32 @+0x3c` (bit1 selects the nearest-segment algorithm). |
| `FOG` | 0x10 | `f32 near (-60 typ.)`, `f32 far (8000)`, `u32 colour` → `GsxCamera::SetFogParam/SetFogColor` |
| `EVENTBOX` | 0x70 | trigger box (see below). `+4` = event id used by script/`GetEventBoxFromID`. |
| `CAMEVENT` | 0x70 | same layout; `+4` = **CAMERA table index** that becomes active while the player is inside (`UpdateFieldCamera`). |
| `EFFECT` | 0x88 | background effect (smoke/light shafts…) descriptors consumed through `CFieldBG::StartEffect/StopEffect/EffectAlpha` and `RecreateExLight`; raw so far |
| `VERTEX` | 0x10 | `f32 x,y,z,1.0` floor vertex |
| `TRIANGLE` | 0x20 | floor triangle: `+0 u32 v0,+4 v1,+8 v2` (VERTEX indices), `+0xc f32 max_c`, `+0x10 f32 min_c` (extent along the axis *perpendicular* to the slicing axis), `+0x14 u16 ?`, `+0x16 u8 blocked` (set by `SetObstacle`), `+0x17 u8 obstacle_id`, `+0x18..0x20` zero |
| `SLICE` | 0x10 | `+0 u32 list_off` (rel. to entry), `+4 u32 count`; list = `count` u32 TRIANGLE indices (followed by a 0 terminator). `count_of_slices` must equal WORLD's slice count (else `SetData` fails). |
| `MONSET` | 4 | chunk header: `+0x14 u8 encounter_rate` → `CField::SetEncountRate`, `+0x16 u16` → field-data 6, `+0x18 u16` → field-data 7 (battle BGM/bg). Records `{u16 monster_set, u8 weight%, u8 pad}`; `CField::Polling` rolls `rand()%100` and subtracts weights. |
| `OBJSE` | var | object sound effects: `+0 u16 count`, `+2 u16`, `+4 u16 sound_data` (→ `SetSoundData(0,…)`), `+0x10/+0x20/+0x30 char[16]` SE bank names (loaded as banks 1,2,3), entries from `+0x60`, each sized by `GetObjSeSize` |
| `NAVIMAP` | var | mini-map: payload starts `"NAVM"`, `u16 ver`, `u16 hdr_size(0x40)`, `u32 size`, `u16 w,h` (46x46), `f32 origin_x,z` … → `CNaviMap::SetData(_NaviMapDataHdr*)` |
| `GENERIC` | var | named blocks: `char[16] name`, `u32 stride (+0x10)`, data at `+0x20`. Seen: `"VIBRATION"` (VIBE sequences → `CVibeMan::GetSeqData`) |

Event box (0x70): `+0 u32 ?`, `+4 i32 id`, `+8 u8 flags` (`&0xf` group, `(flags&0x3f)>>4` kind), `+0x10 vec4 centre`, `+0x20 f32 rot_a`, `+0x24 f32 rot_b`,
`+0x30,+0x40,+0x50,+0x60` four corners `{x, h, z, 0}` (only corner 0's `h` = half-height is used). `HitCheck`: translate by centre, rotate by
`-(rot_a+rot_b)` about Y, four `atan2` edge tests on XZ, `|y| < h`. Modes: 0 = kind-0 boxes, 1 = all, 2 = kind≠0.

Floor lookup (`CFloorMan`) is a bucket grid: the rectangle `[origin, origin+size)` is cut into `slice_count` strips (along X if `slices_along_x≠0`,
otherwise along Z); strip index = `(int)(count * dx/size)`; each strip lists the triangles overlapping it **sorted by the cross axis**; the query scans forward when
the point is in the first half of the cross axis, backward otherwise, skipping triangles whose `[min_c,max_c]` excludes the point. A triangle test is three signed
`atan2` angle comparisons plus a ±20 unit window around `(y0+y1+y2)*0.3333`. The last hit is cached (`CFloorMan+0x10`).

## 4. Validation results (Rust tests in `port/crates/sh2_field/tests/real_data.rs`; run with `SH2_DISC_DIR` / `SH2_US_DISC_DIR`)

* JP demo: 43/43 `.MPS` parse; the FILEHDR size field equals the PKB table size for every file; WORLD slice counts match the SLICE chunk in all 43.
* US retail: **559/559** `.MPS` parse (same "SBD 0.11" container; chunk set adds `MIRROR` in 23 maps and `BGCOLOR` in 49), all floors build.
* Floor: 153/180 JP entry points are on the floor (the others are unused/duplicate spawn slots, e.g. (0,0,0)); `OnFloorPoint` agrees with the entry height within 25 units.
* Event boxes: 196/197 box centres test inside their own box (`CFieldEvent::HitCheck` port).
* Camera: CAMERA kinds in the JP maps: 5 (spline rail) x94, 0 (fixed) x37, 3 (pivot) x12, 4 x3. `eval_camera` (kinds 0-3, kind 5 in nearest-segment mode) produces targets within 100 and cameras within 200 units of the player for all 20 maps where a CAMEVENT is hit at entry 0. Kind 4 and the rounded-corner mode of kind 5 (node-0 flags bit1) are not ported.
* Movement: 1160 simulated walks (every on-floor entry point x 8 headings x 300 frames, `step_forward` = slope scale + wall slide) never leave the floor, 93% make progress.
* Conventions confirmed by the data: `RotY` x'=x c+z s, z'=-x s+z c; `RotX` y'=y c-z s, z'=y s+z c; matrix composition by left-multiplication (`RotXMatrix` after `RotYMatrix` gives Rx*Ry).
