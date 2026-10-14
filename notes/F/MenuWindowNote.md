# MenuWindowNote

Base class: `MenuWindowObject`

Style 3: seven sprites (common scene records 0..6) forming a note/label panel.

## Virtual table (`__vt__MenuWindowNote`)

| slot | function |
|---|---|
| 0x08 | `__dt__14MenuWindowNoteFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__14MenuWindowNoteFiiUs` |
| 0x18 | `Connect__14MenuWindowNoteFP4_QWD` |
| 0x1c | `Destroy__14MenuWindowNoteFv` |
| 0x20 | `Clear__14MenuWindowNoteFv` |
| 0x24 | `Create__14MenuWindowNoteFP10MenuWindow` |
| 0x28 | `SetForm__16MenuWindowObjectFffff` |
| 0x2c | `SetColor__16MenuWindowObjectFUcUcUc` |
| 0x30 | `SetAlpha__14MenuWindowNoteFUc` |

## Constructed by

`Create__10MenuWindowFUcUcffff`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00288390 | 0x88 | `__ct__14MenuWindowNoteFv` | `MenuWindowNote::MenuWindowNote()` |
| 0x00288420 | 0xbc | `__dt__14MenuWindowNoteFv` | `MenuWindowNote::~MenuWindowNote()` |
| 0x002884e0 | 0xdc | `Create__14MenuWindowNoteFP10MenuWindow` | `MenuWindowNote::Create(MenuWindow*)` |
| 0x002885c0 | 0x74 | `SetAlpha__14MenuWindowNoteFUc` | `MenuWindowNote::SetAlpha(unsigned char)` |
| 0x00288640 | 0x2c4 | `Update__14MenuWindowNoteFiiUs` | `MenuWindowNote::Update(int, int, unsigned short)` |
| 0x00288910 | 0x88 | `Connect__14MenuWindowNoteFP4_QWD` | `MenuWindowNote::Connect(_QWD*)` |
| 0x002889a0 | 0x7c | `Destroy__14MenuWindowNoteFv` | `MenuWindowNote::Destroy()` |
| 0x00288a20 | 0x94 | `Clear__14MenuWindowNoteFv` | `MenuWindowNote::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuWindowNote.c`
