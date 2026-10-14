# MenuModelPrim

VIF1Prim adapter that emits a `MenuModel`'s packets into the menu OT.

## Virtual table (`__vt__MenuModelPrim`)

| slot | function |
|---|---|
| 0x08 | `__dt__13MenuModelPrimFv` |
| 0x0c | `getPacket__13MenuModelPrimFv` |

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00291a90 | 0x44 | `__ct__13MenuModelPrimFv` | `MenuModelPrim::MenuModelPrim()` |
| 0x00291ae0 | 0x74 | `__dt__13MenuModelPrimFv` | `MenuModelPrim::~MenuModelPrim()` |
| 0x00291b60 | 0x3c | `getPacket__13MenuModelPrimFv` | `MenuModelPrim::getPacket()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuModelPrim.c`
