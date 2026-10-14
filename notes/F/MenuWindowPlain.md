# MenuWindowPlain

Base class: `MenuWindowObject`

Style 5: single gradient polygon (top colour 0x30,0x30,0x60 / bottom 0x20,0x20,0x40) filling the window.

## Virtual table (`__vt__MenuWindowPlain`)

| slot | function |
|---|---|
| 0x08 | `__dt__15MenuWindowPlainFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__15MenuWindowPlainFiiUs` |
| 0x18 | `Connect__15MenuWindowPlainFP4_QWD` |
| 0x1c | `Destroy__15MenuWindowPlainFv` |
| 0x20 | `Clear__15MenuWindowPlainFv` |
| 0x24 | `Create__15MenuWindowPlainFP10MenuWindow` |
| 0x28 | `SetForm__15MenuWindowPlainFffff` |
| 0x2c | `SetColor__15MenuWindowPlainFUcUcUc` |
| 0x30 | `SetAlpha__15MenuWindowPlainFUc` |

## Constructed by

`Create__10MenuWindowFUcUcffff`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00288bf0 | 0x60 | `__ct__15MenuWindowPlainFv` | `MenuWindowPlain::MenuWindowPlain()` |
| 0x00288c50 | 0x9c | `__dt__15MenuWindowPlainFv` | `MenuWindowPlain::~MenuWindowPlain()` |
| 0x00288cf0 | 0x11c | `Create__15MenuWindowPlainFP10MenuWindow` | `MenuWindowPlain::Create(MenuWindow*)` |
| 0x00288e10 | 0xb8 | `SetForm__15MenuWindowPlainFffff` | `MenuWindowPlain::SetForm(float, float, float, float)` |
| 0x00288ed0 | 0x4c | `SetColor__15MenuWindowPlainFUcUcUc` | `MenuWindowPlain::SetColor(unsigned char, unsigned char, unsigned char)` |
| 0x00288f20 | 0x3c | `SetAlpha__15MenuWindowPlainFUc` | `MenuWindowPlain::SetAlpha(unsigned char)` |
| 0x00288f60 | 0xb0 | `Update__15MenuWindowPlainFiiUs` | `MenuWindowPlain::Update(int, int, unsigned short)` |
| 0x00289010 | 0x3c | `Connect__15MenuWindowPlainFP4_QWD` | `MenuWindowPlain::Connect(_QWD*)` |
| 0x00289050 | 0x34 | `Destroy__15MenuWindowPlainFv` | `MenuWindowPlain::Destroy()` |
| 0x00289090 | 0x48 | `Clear__15MenuWindowPlainFv` | `MenuWindowPlain::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuWindowPlain.c`
