# solomonTutorial

Context: see `solomon.md`.

* base: `CPolObj`; allocation size: 0x48; ctor JP `0x004ffa00`
* vtable stores: `+0x14 __vt__15solomonTutorial`

| JP addr | size | method |
|---|---|---|
| `0x004ffa00` | 0x6c | `solomonTutorial::solomonTutorial()` |
| `0x004ffa70` | 0xfc | `solomonTutorial::~solomonTutorial()` |
| `0x004ffb70` | 0x50 | `solomonTutorial::initialize(primTex*)` |
| `0x004ffbc0` | 0xa00 | `solomonTutorial::Polling()` |
| `0x005005c0` | 0x1c | `solomonTutorial::isFinish()` |

Decompiled source: `decomp/G/solomonTutorial.c`.
