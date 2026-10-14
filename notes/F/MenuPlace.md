# MenuPlace

Base class: `MenuObj`

A rectangular, positionable widget that can be addressed by the cursor: owner window @0x18, grid cell (`col`,`row`) @0x1c/0x1e used by `MenuWindow::GetPlace/MovePlace`, flags @0x21 (bit1 selectable, bit2 selected, bit4 key place of a group, bit5 alpha relative to parent), label @0x22, rect (x,y,w,h as floats) @0x24, attached object @0x34 (the cursor 'back object' sprite), next sibling @0x38. `IsSelected(cursor)` is how a place becomes the cursor target (see Cursor). Default `Clear()` sets col=row=-1 and flags 0x2a.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x18 | `MenuWindow *` | owner |
| 0x1c | `s16` | col |
| 0x1e | `s16` | row |
| 0x20 | `u8` | state |
| 0x21 | `u8` | pflags |
| 0x22 | `u16` | label |
| 0x24 | `f32` | x |
| 0x28 | `f32` | y |
| 0x2c | `f32` | w |
| 0x30 | `f32` | h |
| 0x34 | `MenuObj *` | attached |
| 0x38 | `MenuPlace *` | next_place |

## Virtual table (`__vt__MenuPlace`)

| slot | function |
|---|---|
| 0x08 | `__dt__9MenuPlaceFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__7MenuObjFiiUs` |
| 0x18 | `Connect__7MenuObjFP4_QWD` |
| 0x1c | `Destroy__7MenuObjFv` |
| 0x20 | `Clear__9MenuPlaceFv` |
| 0x24 | `SetPosition__9MenuPlaceFff` |
| 0x28 | `SetSize__9MenuPlaceFff` |
| 0x2c | `SetAlpha__9MenuPlaceFUc` |
| 0x30 | `SetColor__9MenuPlaceFUcUcUc` |
| 0x34 | `SetBright__9MenuPlaceFf` |
| 0x38 | `SetOwner__9MenuPlaceFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuPlaceFv` |
| 0x40 | `GetKeyRect__9MenuPlaceFP8DrawRect` |
| 0x44 | `AllotPacket__9MenuPlaceFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__9MenuPlaceFv` |
| 0x4c | `Attach__9MenuPlaceFP10MenuWindow` |
| 0x50 | `Detach__9MenuPlaceFv` |

## Constructed by

`__ct__10SoulEnergyFv`, `__ct__8MenuItemFv`, `__ct__9MenuGroupFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00278ca0 | 0x3c | `__ct__9MenuPlaceFv` | `MenuPlace::MenuPlace()` |
| 0x00278ce0 | 0x74 | `__dt__9MenuPlaceFv` | `MenuPlace::~MenuPlace()` |
| 0x00278d60 | 0x198 | `IsSelected__9MenuPlaceFP6Cursor` | `MenuPlace::IsSelected(Cursor*)` |
| 0x00278f00 | 0x68 | `IsCanceled__9MenuPlaceFP6Cursor` | `MenuPlace::IsCanceled(Cursor*)` |
| 0x00278f70 | 0xb8 | `SetPosition__9MenuPlaceFff` | `MenuPlace::SetPosition(float, float)` |
| 0x00279030 | 0xb8 | `SetSize__9MenuPlaceFff` | `MenuPlace::SetSize(float, float)` |
| 0x002790f0 | 0x10 | `SetAlpha__9MenuPlaceFUc` | `MenuPlace::SetAlpha(unsigned char)` |
| 0x00279100 | 0x10 | `SetColor__9MenuPlaceFUcUcUc` | `MenuPlace::SetColor(unsigned char, unsigned char, unsigned char)` |
| 0x00279110 | 0x10 | `SetBright__9MenuPlaceFf` | `MenuPlace::SetBright(float)` |
| 0x00279120 | 0x24 | `SetOwner__9MenuPlaceFP10MenuWindow` | `MenuPlace::SetOwner(MenuWindow*)` |
| 0x00279150 | 0x18 | `GetKeyPlace__9MenuPlaceFv` | `MenuPlace::GetKeyPlace()` |
| 0x00279170 | 0x58 | `GetKeyRect__9MenuPlaceFP8DrawRect` | `MenuPlace::GetKeyRect(DrawRect*)` |
| 0x002791d0 | 0x10 | `AllotPacket__9MenuPlaceFP4_QWDP4_QWD` | `MenuPlace::AllotPacket(_QWD*, _QWD*)` |
| 0x002791e0 | 0x14 | `GetAllotCount__9MenuPlaceFv` | `MenuPlace::GetAllotCount()` |
| 0x00279200 | 0x34 | `Attach__9MenuPlaceFP10MenuWindow` | `MenuPlace::Attach(MenuWindow*)` |
| 0x00279240 | 0x48 | `Detach__9MenuPlaceFv` | `MenuPlace::Detach()` |
| 0x00279290 | 0x90 | `Clear__9MenuPlaceFv` | `MenuPlace::Clear()` |

## Rust port

`widget::Place`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuPlace.c`
