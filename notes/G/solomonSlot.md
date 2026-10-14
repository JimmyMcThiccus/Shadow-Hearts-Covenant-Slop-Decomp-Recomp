# solomonSlot

Context: see `solomon.md`.

* base: `CPolObj`; allocation size: 0x6c; ctor JP `0x00502220`
* vtable stores: `+0x14 __vt__11solomonSlot`

| JP addr | size | method |
|---|---|---|
| `0x00502220` | 0x64 | `solomonSlot::solomonSlot(primLayer*)` |
| `0x00502290` | 0xfc | `solomonSlot::~solomonSlot()` |
| `0x00502390` | 0x274 | `solomonSlot::initialize(Matrix*, float, float, bool)` |
| `0x00502610` | 0x118 | `solomonSlot::setRGBA(int, int, int, int)` |
| `0x00502730` | 0x90 | `solomonSlot::setAlpha(int)` |
| `0x005027c0` | 0x208 | `solomonSlot::setFixEffect()` |
| `0x005029d0` | 0x3f8 | `solomonSlot::Polling()` |
| `0x00502dd0` | 0x78 | `solomonSlot::fadein(int)` |
| `0x00502e50` | 0x78 | `solomonSlot::fadeout(int)` |
| `0x00502ed0` | 0x218 | `solomonSlot::setDemon(int)` |
| `0x005030f0` | 0x1c | `solomonSlot::isDemon()` |

Decompiled source: `decomp/G/solomonSlot.c`.
