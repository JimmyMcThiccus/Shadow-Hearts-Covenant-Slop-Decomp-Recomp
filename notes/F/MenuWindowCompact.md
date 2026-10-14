# MenuWindowCompact

Base class: `MenuWindowObject`

Style 7: five sprites (records 0x18..0x1c) -- small compact panel.

## Virtual table (`__vt__MenuWindowCompact`)

| slot | function |
|---|---|
| 0x08 | `__dt__17MenuWindowCompactFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__17MenuWindowCompactFiiUs` |
| 0x18 | `Connect__17MenuWindowCompactFP4_QWD` |
| 0x1c | `Destroy__17MenuWindowCompactFv` |
| 0x20 | `Clear__17MenuWindowCompactFv` |
| 0x24 | `Create__17MenuWindowCompactFP10MenuWindow` |
| 0x28 | `SetForm__16MenuWindowObjectFffff` |
| 0x2c | `SetColor__16MenuWindowObjectFUcUcUc` |
| 0x30 | `SetAlpha__17MenuWindowCompactFUc` |

## Constructed by

`Create__10MenuWindowFUcUcffff`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00290cb0 | 0x88 | `__ct__17MenuWindowCompactFv` | `MenuWindowCompact::MenuWindowCompact()` |
| 0x00290d40 | 0xbc | `__dt__17MenuWindowCompactFv` | `MenuWindowCompact::~MenuWindowCompact()` |
| 0x00290e00 | 0xe4 | `Create__17MenuWindowCompactFP10MenuWindow` | `MenuWindowCompact::Create(MenuWindow*)` |
| 0x00290ef0 | 0x74 | `SetAlpha__17MenuWindowCompactFUc` | `MenuWindowCompact::SetAlpha(unsigned char)` |
| 0x00290f70 | 0x284 | `Update__17MenuWindowCompactFiiUs` | `MenuWindowCompact::Update(int, int, unsigned short)` |
| 0x00291200 | 0x88 | `Connect__17MenuWindowCompactFP4_QWD` | `MenuWindowCompact::Connect(_QWD*)` |
| 0x00291290 | 0x7c | `Destroy__17MenuWindowCompactFv` | `MenuWindowCompact::Destroy()` |
| 0x00291310 | 0x94 | `Clear__17MenuWindowCompactFv` | `MenuWindowCompact::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuWindowCompact.c`
