# Navigation map (`CNaviMap`, the field radar) -- 2026-10-14

Code: `sh2_field::navimap` (data / parser), `navimap_render` (overlay art, view math, floor rasteriser, tests), `navimap_plugin` (Bevy side),
`examples/navi_survey.rs` (all maps), `examples/navi_render.rs` (calibration dump).  Decompile: `decomp/G/CNaviMap.c`, `notes/G_retail/CNaviMap.md`.

## What it is
A circular radar in the top-left corner of the field screen (live capture: `tools/live`, save slot 8, AP_02_U): a translucent cyan floor plan
that scrolls with the player, an eight-notch compass ring, a yellow player triangle and a green gear for the save point.

## Data (`NAVIMAP` chunk, 391 of 559 retail maps, every one parses)
* `"NAVM"` header (0x40 bytes, table in `navimap.rs`): grid cells (a cell = 10 units), origin, mesh count, picture offset, flags, three tint colours, static
  markers, zoom (u8 / 16, 0 = 1.5).  Flag byte `0x1f`: bit 4 = flat colours (349 maps; the other 42 tint by height), bit 5 = circular mask (**no shipped
  map sets it**), bits 2-3 = quarter turns of the picture (a fixed orientation per map, the map does NOT rotate with the camera).
* Meshes: triangle lists of `s16 x, y, z` (1/16) with `s16 u, v` (1/4096); the UV is simply `position / (460 * ...) + 0.5` over the whole picture, so the mesh
  only decides *which* parts are drawn (walkable cells).  The picture (4 / 8 bit, 64..512 px) is a **top-down floor plan of the room**, the doors are
  part of it.  Extra meshes (`shown` bit) are alternate areas (`CField` `DspMesh`).
* Static markers: 16-byte records (kind 0 rectangle = exits, 1/3/4 sprites).

## Rendering (verified against the live capture)
Window 108 x 108 at (26, 33); ring = four mirrored 64 x 72 quadrants of the overlay's `naviFrame` at (16, 16) => radar centre (80, 88) in the 512 x 448
frame.  Projection (`CnvVertex`): `p - centre`, rotate by the picture's quarter turns, minus the view offset (player, clamped so the window stays inside the
picture), `x * 0.9 / zoom`, `y / zoom`; screen y = -z (the stored picture is vertically flipped on screen: `Orient::default`).  The floor is drawn at full
colour (tint base `(0, 0x80, 0xa0)` x picture grey) and copied with alpha 0x50 / 0x80 under the circular mask (`naviMask`, coverage = palette index / 128).
Calibrated: floor colours within a few levels of the capture; the live ring is ~0.6 of the decoded palette brightness (`RING_ALPHA`, cause not identified).
Cursor = `csrPos` triangle (0,-4),(1.732,1),(-1.732,1) x 2 (x also x 1.1) rotated by quarter turns + the player's heading.  Markers: sprite size 24 / 25 map
units (`/ zoom`), colour = `colTbl[idx]` **halved** (`HalfCol`).  Save point = `AddItem(0x10001, pos, kind 1, colour 5)` (drawn from `rt.st.save_points`).

## Overlay art
`naviFrame` / `naviMask` / `naviIcon` are `P2GraTex` blobs in `FIELD.BIN` (JP 0x557680 / 0x556270 / 0x558c90; 8 bit palettes use GS CSM1 order = index bits 3 and 4
swapped, easy to miss).  The loader finds them by header signature so it works on both discs.

## Option
`MENU+0x275` bits **2-3** (a 2-bit field, 0 = on) -- the earlier "bit 1" in `cmd_option.rs` was wrong (JP `CmdOption` rows 6 / 7 / 8 write the three 2-bit fields of
`+0x275`; retail `CField::Update` tests `(0x275 & 0xf) >> 2 == 0`).  Fixed in `cmd_option.rs`.

## Not done
NPC arrows / script items (`SetItem` from the field script ops, kinds 2 / 4 / 5), the pulsing kind 3, multi-mesh `DspMesh` switching, the ring brightness cause,
hiding while the field GS flag (`GetFldGSFlag`) is set, `Update`'s heading when the field camera overrides (`+0xc0` bit 4).
