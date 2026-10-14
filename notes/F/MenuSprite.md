# MenuSprite

Base class: `MenuItem`

Textured quad (GS sprite primitive). uv rectangle `(u0,v0,u1,v1)` in texels @0x54..0x5a, optional `linked` sprite @0x5c drawn with it. Packet = 6 qwords. `SetScale(f)` grows the rect symmetrically. Records: scene chunk type 6.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x54 | `u16` | u0 |
| 0x56 | `u16` | v0 |
| 0x58 | `u16` | u1 |
| 0x5a | `u16` | v1 |
| 0x5c | `MenuObj *` | linked |

## Virtual table (`__vt__MenuSprite`)

| slot | function |
|---|---|
| 0x08 | `__dt__10MenuSpriteFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__8MenuItemFv` |
| 0x14 | `Update__10MenuSpriteFiiUs` |
| 0x18 | `Connect__10MenuSpriteFP4_QWD` |
| 0x1c | `Destroy__10MenuSpriteFv` |
| 0x20 | `Clear__10MenuSpriteFv` |
| 0x24 | `SetPosition__9MenuPlaceFff` |
| 0x28 | `SetSize__9MenuPlaceFff` |
| 0x2c | `SetAlpha__8MenuItemFUc` |
| 0x30 | `SetColor__8MenuItemFUcUcUc` |
| 0x34 | `SetBright__8MenuItemFf` |
| 0x38 | `SetOwner__9MenuPlaceFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuPlaceFv` |
| 0x40 | `GetKeyRect__9MenuPlaceFP8DrawRect` |
| 0x44 | `AllotPacket__8MenuItemFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__8MenuItemFv` |
| 0x4c | `Attach__9MenuPlaceFP10MenuWindow` |
| 0x50 | `Detach__9MenuPlaceFv` |
| 0x5c | `@60@__dt__10MenuSpriteFv` |

## Constructed by

`Create__10ScrollMarkFUcP10MenuWindowUc`, `Create__8MenuIconFc`, `GetReady__13GameOverSceneFv`, `SetBackObject__6CursorFUc`, `WinCreate__9BtlResultFi`, `__ct__10SoulEnergyFv`, `__ct__14MenuWindowFaceFv`, `__ct__14MenuWindowNoteFv`, `__ct__17MenuWindowCompactFv`, `__ct__17MenuWindowGeneralFv`, `__ct__17MenuWindowMessageFv`, `__ct__7KeyWaitFv`, `__ct__7MenuBarFv`, `__ct__9MenuFlareFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00266140 | 0x60 | `__ct__10MenuSpriteFv` | `MenuSprite::MenuSprite()` |
| 0x002661a0 | 0x94 | `__dt__10MenuSpriteFv` | `MenuSprite::~MenuSprite()` |
| 0x00266240 | 0x68 | `Create__10MenuSpriteFUc` | `MenuSprite::Create(unsigned char)` |
| 0x002662b0 | 0xa0 | `SetUV__10MenuSpriteFUsUsUsUs` | `MenuSprite::SetUV(unsigned short, unsigned short, unsigned short, unsigned short)` |
| 0x00266350 | 0xc8 | `SetScale__10MenuSpriteFf` | `MenuSprite::SetScale(float)` |
| 0x00266420 | 0x4d4 | `Update__10MenuSpriteFiiUs` | `MenuSprite::Update(int, int, unsigned short)` |
| 0x00266900 | 0x94 | `Connect__10MenuSpriteFP4_QWD` | `MenuSprite::Connect(_QWD*)` |
| 0x002669a0 | 0x84 | `Destroy__10MenuSpriteFv` | `MenuSprite::Destroy()` |
| 0x00266a30 | 0x78 | `Clear__10MenuSpriteFv` | `MenuSprite::Clear()` |
| 0x00266ab0 | 0x8 | `@60@__dt__10MenuSpriteFv` | `@60@__dt__10MenuSpriteFv` |

## Rust port

`widget::Sprite`, `Widget::sprite_from_rec`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuSprite.c`
