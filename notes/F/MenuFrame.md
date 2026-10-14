# MenuFrame

Base class: `MenuObj`

Outline frame primitive for `MenuWindowFrame` (14-qword packet).

## Virtual table (`__vt__MenuFrame`)

| slot | function |
|---|---|
| 0x08 | `__dt__9MenuFrameFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__9MenuFrameFiiUs` |
| 0x18 | `Connect__9MenuFrameFP4_QWD` |
| 0x1c | `Destroy__9MenuFrameFv` |
| 0x20 | `Clear__9MenuFrameFv` |
| 0x2c | `@24@__dt__9MenuFrameFv` |
| 0x30 | `Create__9MenuFrameFP10MenuWindowP8DrawRect` |
| 0x34 | `SetAlpha__9MenuFrameFUc` |

## Constructed by

`__ct__15MenuWindowFrameFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002781f0 | 0x70 | `__ct__9MenuFrameFv` | `MenuFrame::MenuFrame()` |
| 0x00278260 | 0xac | `__dt__9MenuFrameFv` | `MenuFrame::~MenuFrame()` |
| 0x00278310 | 0x2c | `Destroy__9MenuFrameFv` | `MenuFrame::Destroy()` |
| 0x00278340 | 0x70 | `Create__9MenuFrameFP10MenuWindowP8DrawRect` | `MenuFrame::Create(MenuWindow*, DrawRect*)` |
| 0x002783b0 | 0x70 | `SetAlpha__9MenuFrameFUc` | `MenuFrame::SetAlpha(unsigned char)` |
| 0x00278420 | 0x77c | `Update__9MenuFrameFiiUs` | `MenuFrame::Update(int, int, unsigned short)` |
| 0x00278ba0 | 0x34 | `Connect__9MenuFrameFP4_QWD` | `MenuFrame::Connect(_QWD*)` |
| 0x00278be0 | 0xa8 | `Clear__9MenuFrameFv` | `MenuFrame::Clear()` |
| 0x00278c90 | 0x8 | `@24@__dt__9MenuFrameFv` | `@24@__dt__9MenuFrameFv` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuFrame.c`
