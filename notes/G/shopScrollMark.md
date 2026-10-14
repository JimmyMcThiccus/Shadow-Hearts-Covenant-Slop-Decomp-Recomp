# shopScrollMark

Context: see `shop.md`.

* base: `CPolObj`; allocation size: 0x2c; ctor JP `0x004e89a0`
* vtable stores: `+0x14 __vt__14shopScrollMark`

| JP addr | size | method |
|---|---|---|
| `0x004e89a0` | 0x44 | `shopScrollMark::shopScrollMark()` |
| `0x004e89f0` | 0xac | `shopScrollMark::~shopScrollMark()` |
| `0x004e8aa0` | 0x80 | `shopScrollMark::initialize(primTex*, int, int, int)` |
| `0x004e8b20` | 0x260 | `shopScrollMark::Polling()` |
| `0x004e8d80` | 0x104 | `shopScrollMark::select(int, int, int)` |
| `0x004e8e90` | 0x130 | `shopScrollMark::mSetupScrollMark()` |

Decompiled source: `decomp/G/shopScrollMark.c`.
