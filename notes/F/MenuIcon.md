# MenuIcon

Base class: `MenuObjTable`

Inline icon object for message text (button glyph), `Create(char)`, `SetOwner`, `Finish`.

## Virtual table (`__vt__MenuIcon`)

| slot | function |
|---|---|
| 0x08 | `__dt__8MenuIconFv` |

## Constructed by

`__ct__8FontItemFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0028e640 | 0x3c | `__ct__8MenuIconFv` | `MenuIcon::MenuIcon()` |
| 0x0028e680 | 0x74 | `__dt__8MenuIconFv` | `MenuIcon::~MenuIcon()` |
| 0x0028e700 | 0x2d0 | `Create__8MenuIconFc` | `MenuIcon::Create(char)` |
| 0x0028e9d0 | 0x70 | `Destroy__8MenuIconFv` | `MenuIcon::Destroy()` |
| 0x0028ea40 | 0x68 | `SetOwner__8MenuIconFP10MenuWindow` | `MenuIcon::SetOwner(MenuWindow*)` |
| 0x0028eab0 | 0x88 | `Finish__8MenuIconFv` | `MenuIcon::Finish()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuIcon.c`
