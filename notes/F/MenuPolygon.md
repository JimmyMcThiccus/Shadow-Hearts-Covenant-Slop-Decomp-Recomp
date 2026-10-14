# MenuPolygon

Base class: `MenuItem`

Four-vertex Gouraud quad (strip order TL,BL,TR,BR) with per-vertex colour (colour 0 = item tint, 1..3 @0x74..0x7c) and optional per-vertex UV (`uv` pointer @0x80, 4x(u,v) shorts, allocated only with `Create(hasUV)`). `SetRect()` recomputes the bounding box; `SetPosition/SetSize` re-fit the vertices to the rect.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x54 | `f32` | vx0 |
| 0x58 | `f32` | vy0 |
| 0x5c | `f32` | vx1 |
| 0x60 | `f32` | vy1 |
| 0x64 | `f32` | vx2 |
| 0x68 | `f32` | vy2 |
| 0x6c | `f32` | vx3 |
| 0x70 | `f32` | vy3 |
| 0x74 | `u8` | col1[4] |
| 0x78 | `u8` | col2[4] |
| 0x7c | `u8` | col3[4] |
| 0x80 | `u16 *` | uv |

## Virtual table (`__vt__MenuPolygon`)

| slot | function |
|---|---|
| 0x08 | `__dt__11MenuPolygonFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__8MenuItemFv` |
| 0x14 | `Update__11MenuPolygonFiiUs` |
| 0x18 | `Connect__8MenuItemFP4_QWD` |
| 0x1c | `Destroy__11MenuPolygonFv` |
| 0x20 | `Clear__11MenuPolygonFv` |
| 0x24 | `SetPosition__11MenuPolygonFff` |
| 0x28 | `SetSize__11MenuPolygonFff` |
| 0x2c | `SetAlpha__11MenuPolygonFUc` |
| 0x30 | `SetColor__11MenuPolygonFUcUcUc` |
| 0x34 | `SetBright__11MenuPolygonFf` |
| 0x38 | `SetOwner__9MenuPlaceFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuPlaceFv` |
| 0x40 | `GetKeyRect__9MenuPlaceFP8DrawRect` |
| 0x44 | `AllotPacket__8MenuItemFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__8MenuItemFv` |
| 0x4c | `Attach__9MenuPlaceFP10MenuWindow` |
| 0x50 | `Detach__9MenuPlaceFv` |
| 0x5c | `@60@__dt__11MenuPolygonFv` |

## Constructed by

`SetShadow__6CursorFUc`, `WinCreate__9BtlResultFi`, `__ct__15MenuWindowFrameFv`, `__ct__15MenuWindowPlainFv`, `__ct__17MenuWindowGeneralFv`, `__ct__17MenuWindowMessageFv`, `__ct__6CursorFv`, `__ct__8primPolyFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00276640 | 0x90 | `__ct__11MenuPolygonFv` | `MenuPolygon::MenuPolygon()` |
| 0x002766d0 | 0x94 | `__dt__11MenuPolygonFv` | `MenuPolygon::~MenuPolygon()` |
| 0x00276770 | 0x158 | `Create__11MenuPolygonFUcUc` | `MenuPolygon::Create(unsigned char, unsigned char)` |
| 0x002768d0 | 0x18c | `SetRect__11MenuPolygonFv` | `MenuPolygon::SetRect()` |
| 0x00276a60 | 0xc4 | `SetVertex__11MenuPolygonFiffb` | `MenuPolygon::SetVertex(int, float, float, bool)` |
| 0x00276b30 | 0xf4 | `SetUV__11MenuPolygonFUsUsUsUs` | `MenuPolygon::SetUV(unsigned short, unsigned short, unsigned short, unsigned short)` |
| 0x00276c30 | 0xc4 | `SetColor__11MenuPolygonFiUcUcUc` | `MenuPolygon::SetColor(int, unsigned char, unsigned char, unsigned char)` |
| 0x00276d00 | 0x130 | `SetPosition__11MenuPolygonFff` | `MenuPolygon::SetPosition(float, float)` |
| 0x00276e30 | 0x130 | `SetSize__11MenuPolygonFff` | `MenuPolygon::SetSize(float, float)` |
| 0x00276f60 | 0xf0 | `SetColor__11MenuPolygonFUcUcUc` | `MenuPolygon::SetColor(unsigned char, unsigned char, unsigned char)` |
| 0x00277050 | 0x90 | `SetAlpha__11MenuPolygonFUc` | `MenuPolygon::SetAlpha(unsigned char)` |
| 0x002770e0 | 0xc4 | `SetBright__11MenuPolygonFf` | `MenuPolygon::SetBright(float)` |
| 0x002771b0 | 0x518 | `Update__11MenuPolygonFiiUs` | `MenuPolygon::Update(int, int, unsigned short)` |
| 0x002776d0 | 0x58 | `Destroy__11MenuPolygonFv` | `MenuPolygon::Destroy()` |
| 0x00277730 | 0xd8 | `Clear__11MenuPolygonFv` | `MenuPolygon::Clear()` |
| 0x00277810 | 0x8 | `@60@__dt__11MenuPolygonFv` | `@60@__dt__11MenuPolygonFv` |

## Rust port

`widget::Polygon`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuPolygon.c`
