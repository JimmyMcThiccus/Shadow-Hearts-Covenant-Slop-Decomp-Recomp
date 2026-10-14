# pageScrollMark

Context: see `tailor.md`.

* base: `CPolObj`; allocation size: 0x34; ctor JP `0x00500f20`
* vtable stores: `+0x14 __vt__14pageScrollMark`

| JP addr | size | method |
|---|---|---|
| `0x00500f20` | 0x44 | `pageScrollMark::pageScrollMark()` |
| `0x00500f70` | 0xac | `pageScrollMark::~pageScrollMark()` |
| `0x00501020` | 0xa4 | `pageScrollMark::initialize(primTex*, int, int, int)` |
| `0x005010d0` | 0xdc | `pageScrollMark::setDisp(bool)` |
| `0x005011b0` | 0x260 | `pageScrollMark::Polling()` |
| `0x00501410` | 0x15c | `pageScrollMark::select(int, int, int)` |
| `0x00501570` | 0x1b0 | `pageScrollMark::mSetupScrollMark()` |

Decompiled source: `decomp/G/pageScrollMark.c`.
