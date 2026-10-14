# MenuWindowObject

Base class: `MenuObj`

Abstract decoration base (vptr, owner window).

## Virtual table (`__vt__MenuWindowObject`)

| slot | function |
|---|---|
| 0x08 | `__dt__16MenuWindowObjectFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__7MenuObjFiiUs` |
| 0x18 | `Connect__7MenuObjFP4_QWD` |
| 0x1c | `Destroy__7MenuObjFv` |
| 0x20 | `Clear__7MenuObjFv` |
| 0x28 | `SetForm__16MenuWindowObjectFffff` |
| 0x2c | `SetColor__16MenuWindowObjectFUcUcUc` |

## Constructed by

`__ct__14MenuWindowFaceFv`, `__ct__14MenuWindowNoteFv`, `__ct__15MenuWindowFrameFv`, `__ct__15MenuWindowPlainFv`, `__ct__17MenuWindowCompactFv`, `__ct__17MenuWindowGeneralFv`, `__ct__17MenuWindowMessageFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00288ac0 | 0x3c | `__ct__16MenuWindowObjectFv` | `MenuWindowObject::MenuWindowObject()` |
| 0x00288b00 | 0x74 | `__dt__16MenuWindowObjectFv` | `MenuWindowObject::~MenuWindowObject()` |
| 0x00288b80 | 0x60 | `SetForm__16MenuWindowObjectFffff` | `MenuWindowObject::SetForm(float, float, float, float)` |
| 0x00288be0 | 0x10 | `SetColor__16MenuWindowObjectFUcUcUc` | `MenuWindowObject::SetColor(unsigned char, unsigned char, unsigned char)` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuWindowObject.c`
