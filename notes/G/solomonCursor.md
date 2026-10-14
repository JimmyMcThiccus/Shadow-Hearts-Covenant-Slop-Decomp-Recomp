# solomonCursor

Context: see `solomon.md`.

* base: `CPolObj`; allocation size: 0x5c; ctor JP `0x00501720`
* vtable stores: `+0x14 __vt__13solomonCursor`

| JP addr | size | method |
|---|---|---|
| `0x00501720` | 0x54 | `solomonCursor::solomonCursor()` |
| `0x00501780` | 0xd4 | `solomonCursor::~solomonCursor()` |
| `0x00501860` | 0x2d4 | `solomonCursor::initialize(Matrix*, float, float, primLayer*)` |
| `0x00501b40` | 0x34 | `solomonCursor::fadeout()` |
| `0x00501b80` | 0x54 | `solomonCursor::setRGBA(int, int, int, int)` |
| `0x00501be0` | 0x24 | `solomonCursor::setCurrentDemon(int)` |
| `0x00501c10` | 0x1a8 | `solomonCursor::setPos(float, float)` |
| `0x00501dc0` | 0x3a0 | `solomonCursor::Polling()` |
| `0x00502160` | 0x54 | `solomonCursor::setCursor(primCursor*)` |
| `0x005021c0` | 0x58 | `solomonCursor::removeCursor()` |

Decompiled source: `decomp/G/solomonCursor.c`.
