# MenuWindowFrame

Base class: `MenuWindowObject`

Style 4: gradient fill (same colours as Plain) plus a `MenuFrame` outline (14 qwords) drawn around it.

## Virtual table (`__vt__MenuWindowFrame`)

| slot | function |
|---|---|
| 0x08 | `__dt__15MenuWindowFrameFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__15MenuWindowFrameFiiUs` |
| 0x18 | `Connect__15MenuWindowFrameFP4_QWD` |
| 0x1c | `Destroy__15MenuWindowFrameFv` |
| 0x20 | `Clear__15MenuWindowFrameFv` |
| 0x24 | `Create__15MenuWindowFrameFP10MenuWindow` |
| 0x28 | `SetForm__15MenuWindowFrameFffff` |
| 0x2c | `SetColor__15MenuWindowFrameFUcUcUc` |
| 0x30 | `SetAlpha__15MenuWindowFrameFUc` |

## Constructed by

`Create__10MenuWindowFUcUcffff`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002875c0 | 0x70 | `__ct__15MenuWindowFrameFv` | `MenuWindowFrame::MenuWindowFrame()` |
| 0x00287630 | 0xac | `__dt__15MenuWindowFrameFv` | `MenuWindowFrame::~MenuWindowFrame()` |
| 0x002876e0 | 0x150 | `Create__15MenuWindowFrameFP10MenuWindow` | `MenuWindowFrame::Create(MenuWindow*)` |
| 0x00287830 | 0xb8 | `SetForm__15MenuWindowFrameFffff` | `MenuWindowFrame::SetForm(float, float, float, float)` |
| 0x002878f0 | 0x4c | `SetColor__15MenuWindowFrameFUcUcUc` | `MenuWindowFrame::SetColor(unsigned char, unsigned char, unsigned char)` |
| 0x00287940 | 0x58 | `SetAlpha__15MenuWindowFrameFUc` | `MenuWindowFrame::SetAlpha(unsigned char)` |
| 0x002879a0 | 0x110 | `Update__15MenuWindowFrameFiiUs` | `MenuWindowFrame::Update(int, int, unsigned short)` |
| 0x00287ab0 | 0x5c | `Connect__15MenuWindowFrameFP4_QWD` | `MenuWindowFrame::Connect(_QWD*)` |
| 0x00287b10 | 0x4c | `Destroy__15MenuWindowFrameFv` | `MenuWindowFrame::Destroy()` |
| 0x00287b60 | 0x60 | `Clear__15MenuWindowFrameFv` | `MenuWindowFrame::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuWindowFrame.c`
