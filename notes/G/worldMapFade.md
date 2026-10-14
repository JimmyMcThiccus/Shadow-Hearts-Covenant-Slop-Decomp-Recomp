# worldMapFade

Context: see `worldMap.md`.

* base: `CPolObj`; allocation size: unknown; ctor JP `0x0050b0c0`
* vtable stores: `+0x14 __vt__12worldMapFade`

| JP addr | size | method |
|---|---|---|
| `0x0050b0c0` | 0x3c | `worldMapFade::worldMapFade()` |
| `0x0050b100` | 0xb4 | `worldMapFade::~worldMapFade()` |
| `0x0050b1c0` | 0x4c | `worldMapFade::initialize()` |
| `0x0050b210` | 0x80 | `worldMapFade::fadeIn(int)` |
| `0x0050b290` | 0x84 | `worldMapFade::fadeOut(int)` |
| `0x0050b320` | 0x17c | `worldMapFade::Polling()` |
| `0x0050b4a0` | 0x368 | `worldMapFade::mSetFadeWin()` |

Decompiled source: `decomp/G/worldMapFade.c`.
