# shopCash

Context: see `shop.md`.

* base: `-`; allocation size: 0x18; ctor JP `0x004e8490`

| JP addr | size | method |
|---|---|---|
| `0x004e8490` | 0x20 | `shopCash::shopCash()` |
| `0x004e84b0` | 0x7c | `shopCash::~shopCash()` |
| `0x004e8530` | 0x40 | `shopCash::initialize(primTex*)` |
| `0x004e8570` | 0x38 | `shopCash::setCash(int)` |
| `0x004e85b0` | 0x30 | `shopCash::fadein()` |
| `0x004e85e0` | 0x30 | `shopCash::fadeout()` |
| `0x004e8610` | 0x190 | `shopCash::mSetupCash()` |
| `0x004e87a0` | 0x1fc | `shopCash::mCalcCash()` |

Decompiled source: `decomp/G/shopCash.c`.
