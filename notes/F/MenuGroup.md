# MenuGroup

Base class: `MenuPlace`

Container place (chunk type 5): children @0x4c linked via `next_place`, key place @0x48 (cursor target), Q15 alpha @0x44, running min corner @0x3c/0x40. `AddPlace` grows the group rect to enclose the child. Forwards SetColor/SetAlpha/SetBright/SetOwner/Attach/Detach/AllotPacket to the children; `Update` offsets children by the group position (x16) and scales alpha (`param_4 * alpha >> 15`). `GetKeyRect` returns the key place's rect translated by the group.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x3c | `f32` | min_x |
| 0x40 | `f32` | min_y |
| 0x44 | `u16` | alpha |
| 0x48 | `MenuPlace *` | key_place |
| 0x4c | `MenuPlace *` | children |

## Virtual table (`__vt__MenuGroup`)

| slot | function |
|---|---|
| 0x08 | `__dt__9MenuGroupFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__9MenuGroupFiiUs` |
| 0x18 | `Connect__9MenuGroupFP4_QWD` |
| 0x1c | `Destroy__7MenuObjFv` |
| 0x20 | `Clear__9MenuGroupFv` |
| 0x24 | `SetPosition__9MenuPlaceFff` |
| 0x28 | `SetSize__9MenuPlaceFff` |
| 0x2c | `SetAlpha__9MenuGroupFUc` |
| 0x30 | `SetColor__9MenuGroupFUcUcUc` |
| 0x34 | `SetBright__9MenuGroupFf` |
| 0x38 | `SetOwner__9MenuGroupFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuGroupFv` |
| 0x40 | `GetKeyRect__9MenuGroupFP8DrawRect` |
| 0x44 | `AllotPacket__9MenuGroupFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__9MenuGroupFv` |
| 0x4c | `Attach__9MenuGroupFP10MenuWindow` |
| 0x50 | `Detach__9MenuGroupFv` |

## Constructed by

`createGroup__7primWinFi`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002758d0 | 0x50 | `__ct__9MenuGroupFv` | `MenuGroup::MenuGroup()` |
| 0x00275920 | 0x74 | `__dt__9MenuGroupFv` | `MenuGroup::~MenuGroup()` |
| 0x002759a0 | 0x244 | `AddPlace__9MenuGroupFP9MenuPlace` | `MenuGroup::AddPlace(MenuPlace*)` |
| 0x00275bf0 | 0x118 | `RemovePlace__9MenuGroupFP9MenuPlace` | `MenuGroup::RemovePlace(MenuPlace*)` |
| 0x00275d10 | 0x7c | `FindPlace__9MenuGroupFs` | `MenuGroup::FindPlace(short)` |
| 0x00275d90 | 0x4c | `GetKeyPlace__9MenuGroupFv` | `MenuGroup::GetKeyPlace()` |
| 0x00275de0 | 0x13c | `GetKeyRect__9MenuGroupFP8DrawRect` | `MenuGroup::GetKeyRect(DrawRect*)` |
| 0x00275f20 | 0x108 | `AllotPacket__9MenuGroupFP4_QWDP4_QWD` | `MenuGroup::AllotPacket(_QWD*, _QWD*)` |
| 0x00276030 | 0x78 | `GetAllotCount__9MenuGroupFv` | `MenuGroup::GetAllotCount()` |
| 0x002760b0 | 0x78 | `SetColor__9MenuGroupFUcUcUc` | `MenuGroup::SetColor(unsigned char, unsigned char, unsigned char)` |
| 0x00276130 | 0x68 | `SetBright__9MenuGroupFf` | `MenuGroup::SetBright(float)` |
| 0x002761a0 | 0x74 | `SetOwner__9MenuGroupFP10MenuWindow` | `MenuGroup::SetOwner(MenuWindow*)` |
| 0x00276220 | 0x68 | `SetAlpha__9MenuGroupFUc` | `MenuGroup::SetAlpha(unsigned char)` |
| 0x00276290 | 0x8c | `Attach__9MenuGroupFP10MenuWindow` | `MenuGroup::Attach(MenuWindow*)` |
| 0x00276320 | 0x88 | `Detach__9MenuGroupFv` | `MenuGroup::Detach()` |
| 0x002763b0 | 0x198 | `Update__9MenuGroupFiiUs` | `MenuGroup::Update(int, int, unsigned short)` |
| 0x00276550 | 0x84 | `Connect__9MenuGroupFP4_QWD` | `MenuGroup::Connect(_QWD*)` |
| 0x002765e0 | 0x58 | `Clear__9MenuGroupFv` | `MenuGroup::Clear()` |

## Rust port

`widget::Group`, `Widget::group_add`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuGroup.c`
