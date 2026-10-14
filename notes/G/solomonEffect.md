# solomonEffect

Context: see `solomon.md`.

* base: `CPolObj`; allocation size: 0x58; ctor JP `0x004fea20`
* vtable stores: `+0x20 __vt__17DelayDeleteObject`, `+0x14 __vt__13solomonEffect`

| JP addr | size | method |
|---|---|---|
| `0x004fe990` | 0x84 | `solomonEffect::DVD_CBFunc(int, BufMemory*, int, char*, void*)` |
| `0x004fea20` | 0x94 | `solomonEffect::solomonEffect()` |
| `0x004feac0` | 0x128 | `solomonEffect::~solomonEffect()` |
| `0x004febf0` | 0x60 | `solomonEffect::DelayDeleteRequest()` |
| `0x004fec50` | 0x34 | `solomonEffect::fadein()` |
| `0x004fec90` | 0x38 | `solomonEffect::fadeout()` |
| `0x004fecd0` | 0x94 | `solomonEffect::initialize(Matrix*)` |
| `0x004fed70` | 0x5c | `solomonEffect::start(bool)` |
| `0x004fedd0` | 0x1c | `solomonEffect::isFinish()` |
| `0x004fedf0` | 0x14 | `solomonEffect::isReady()` |
| `0x004fee10` | 0xbec | `solomonEffect::Polling()` |
| `0x00506bd0` | 0x8 | `solomonEffect::~solomonEffect()` |

Decompiled source: `decomp/G/solomonEffect.c`.
