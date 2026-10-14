# MenuWindowFace

Base class: `MenuWindowObject`

Style 2: character portrait holder: sprite record 0x13 of the common scene + a `SendOnLocal` bound to the face texture loaded through `MenuObj::sm_pFace` (`FI_%03d.TEX`).

## Virtual table (`__vt__MenuWindowFace`)

| slot | function |
|---|---|
| 0x08 | `__dt__14MenuWindowFaceFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__14MenuWindowFaceFiiUs` |
| 0x18 | `Connect__14MenuWindowFaceFP4_QWD` |
| 0x1c | `Destroy__14MenuWindowFaceFv` |
| 0x20 | `Clear__14MenuWindowFaceFv` |
| 0x24 | `Create__14MenuWindowFaceFP10MenuWindow` |
| 0x28 | `SetForm__16MenuWindowObjectFffff` |
| 0x2c | `SetColor__14MenuWindowFaceFUcUcUc` |
| 0x30 | `SetAlpha__14MenuWindowFaceFUc` |

## Constructed by

`Create__10MenuWindowFUcUcffff`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002871b0 | 0x70 | `__ct__14MenuWindowFaceFv` | `MenuWindowFace::MenuWindowFace()` |
| 0x00287220 | 0xac | `__dt__14MenuWindowFaceFv` | `MenuWindowFace::~MenuWindowFace()` |
| 0x002872d0 | 0xa8 | `Create__14MenuWindowFaceFP10MenuWindow` | `MenuWindowFace::Create(MenuWindow*)` |
| 0x00287380 | 0x4c | `SetColor__14MenuWindowFaceFUcUcUc` | `MenuWindowFace::SetColor(unsigned char, unsigned char, unsigned char)` |
| 0x002873d0 | 0x3c | `SetAlpha__14MenuWindowFaceFUc` | `MenuWindowFace::SetAlpha(unsigned char)` |
| 0x00287410 | 0xb0 | `Update__14MenuWindowFaceFiiUs` | `MenuWindowFace::Update(int, int, unsigned short)` |
| 0x002874c0 | 0x4c | `Connect__14MenuWindowFaceFP4_QWD` | `MenuWindowFace::Connect(_QWD*)` |
| 0x00287510 | 0x4c | `Destroy__14MenuWindowFaceFv` | `MenuWindowFace::Destroy()` |
| 0x00287560 | 0x60 | `Clear__14MenuWindowFaceFv` | `MenuWindowFace::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuWindowFace.c`
