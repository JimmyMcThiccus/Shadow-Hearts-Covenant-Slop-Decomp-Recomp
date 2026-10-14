# floatDemon

Context: see `solomon.md`.

* base: `CPolObj`; allocation size: 0x60; ctor JP `0x005005e0`
* vtable stores: `+0x14 __vt__10floatDemon`

| JP addr | size | method |
|---|---|---|
| `0x005005e0` | 0x4c | `floatDemon::floatDemon()` |
| `0x00500630` | 0xac | `floatDemon::~floatDemon()` |
| `0x005006e0` | 0x178 | `floatDemon::initialize(Matrix*, float, float, primLayer*)` |
| `0x00500860` | 0x7c | `floatDemon::setRGBA(int, int, int, int)` |
| `0x005008e0` | 0x148 | `floatDemon::setCurrentDemon(int)` |
| `0x00500a30` | 0x35c | `floatDemon::Polling()` |
| `0x00500d90` | 0x30 | `floatDemon::setCursor(primCursor*)` |
| `0x00500dc0` | 0x1c | `floatDemon::removeCursor()` |
| `0x00500de0` | 0x60 | `floatDemon::setSlot()` |
| `0x00500e40` | 0xd8 | `floatDemon::eraseSlot(float, float)` |

Decompiled source: `decomp/G/floatDemon.c`.
