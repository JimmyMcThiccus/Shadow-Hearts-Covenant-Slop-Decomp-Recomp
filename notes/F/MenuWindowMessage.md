# MenuWindowMessage

Base class: `MenuWindowObject`

Style 1: dialogue box: four sprites (records 0x14..0x17) + polygon record 0 of the common scene.

## Virtual table (`__vt__MenuWindowMessage`)

| slot | function |
|---|---|
| 0x08 | `__dt__17MenuWindowMessageFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__17MenuWindowMessageFiiUs` |
| 0x18 | `Connect__17MenuWindowMessageFP4_QWD` |
| 0x1c | `Destroy__17MenuWindowMessageFv` |
| 0x20 | `Clear__17MenuWindowMessageFv` |
| 0x24 | `Create__17MenuWindowMessageFP10MenuWindow` |
| 0x28 | `SetForm__16MenuWindowObjectFffff` |
| 0x2c | `SetColor__16MenuWindowObjectFUcUcUc` |
| 0x30 | `SetAlpha__17MenuWindowMessageFUc` |

## Constructed by

`Create__10MenuWindowFUcUcffff`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00287bc0 | 0x98 | `__ct__17MenuWindowMessageFv` | `MenuWindowMessage::MenuWindowMessage()` |
| 0x00287c60 | 0xcc | `__dt__17MenuWindowMessageFv` | `MenuWindowMessage::~MenuWindowMessage()` |
| 0x00287d30 | 0x114 | `Create__17MenuWindowMessageFP10MenuWindow` | `MenuWindowMessage::Create(MenuWindow*)` |
| 0x00287e50 | 0x90 | `SetAlpha__17MenuWindowMessageFUc` | `MenuWindowMessage::SetAlpha(unsigned char)` |
| 0x00287ee0 | 0x2b4 | `Update__17MenuWindowMessageFiiUs` | `MenuWindowMessage::Update(int, int, unsigned short)` |
| 0x002881a0 | 0xa0 | `Connect__17MenuWindowMessageFP4_QWD` | `MenuWindowMessage::Connect(_QWD*)` |
| 0x00288240 | 0x94 | `Destroy__17MenuWindowMessageFv` | `MenuWindowMessage::Destroy()` |
| 0x002882e0 | 0xac | `Clear__17MenuWindowMessageFv` | `MenuWindowMessage::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuWindowMessage.c`
