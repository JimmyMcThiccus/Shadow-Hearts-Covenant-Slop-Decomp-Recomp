# bookScrollMark

Context: see `tailor.md`.

* base: `CPolObj`; allocation size: 0x30; ctor JP `0x004f1240`
* vtable stores: `+0x14 __vt__14bookScrollMark`

| JP addr | size | method |
|---|---|---|
| `0x004f1240` | 0x44 | `bookScrollMark::bookScrollMark()` |
| `0x004f1290` | 0xac | `bookScrollMark::~bookScrollMark()` |
| `0x004f1340` | 0x8c | `bookScrollMark::initialize(primTex*, int, int)` |
| `0x004f13d0` | 0xa4 | `bookScrollMark::setDisp(bool)` |
| `0x004f1480` | 0x1e0 | `bookScrollMark::Polling()` |
| `0x004f1660` | 0x10c | `bookScrollMark::select(int)` |
| `0x004f1770` | 0x148 | `bookScrollMark::mSetupScrollMark()` |

Decompiled source: `decomp/G/bookScrollMark.c`.
