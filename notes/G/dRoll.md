# dRoll

Context: see `tailor.md`.

* base: `CPolObj`; allocation size: 0x5c; ctor JP `0x004f18c0`
* vtable stores: `+0x20 __vt__17DelayDeleteObject`, `+0x14 __vt__5dRoll`

| JP addr | size | method |
|---|---|---|
| `0x004f18c0` | 0xa8 | `dRoll::dRoll()` |
| `0x004f1970` | 0x128 | `dRoll::~dRoll()` |
| `0x004f1aa0` | 0x1f8 | `dRoll::start()` |
| `0x004f1ca0` | 0x74 | `dRoll::stop()` |
| `0x004f1d20` | 0x380 | `dRoll::Polling()` |
| `0x004f20b0` | 0x8 | `dRoll::~dRoll()` |

Decompiled source: `decomp/G/dRoll.c`.
