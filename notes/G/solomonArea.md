# solomonArea

Context: see `solomon.md`.

* base: `CPolObj`; allocation size: 0x80; ctor JP `0x00503110`
* embedded sub-objects: `+0x18 prim`
* vtable stores: `+0x14 __vt__11solomonArea`

| JP addr | size | method |
|---|---|---|
| `0x00503110` | 0xc8 | `solomonArea::solomonArea()` |
| `0x005031e0` | 0x15c | `solomonArea::~solomonArea()` |
| `0x00503340` | 0x9c | `solomonArea::initialize(Matrix*, primLayer*, int, bool)` |
| `0x005033e0` | 0x94 | `solomonArea::setArea(int, bool, bool)` |
| `0x00503480` | 0x920 | `solomonArea::Polling()` |

Decompiled source: `decomp/G/solomonArea.c`.
