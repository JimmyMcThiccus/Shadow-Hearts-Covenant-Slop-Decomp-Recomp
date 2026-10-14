# solomonThm

Context: see `solomon.md`.

* base: `CPolObj`; allocation size: 0x98; ctor JP `0x00503da0`
* vtable stores: `+0x14 __vt__10solomonThm`

| JP addr | size | method |
|---|---|---|
| `0x00503da0` | 0x9c | `solomonThm::solomonThm()` |
| `0x00503e40` | 0x94 | `solomonThm::~solomonThm()` |
| `0x00503ee0` | 0xbc | `solomonThm::initialize(primTex*, bool, int, int)` |
| `0x00503fa0` | 0x3c0 | `solomonThm::fadein(int)` |
| `0x00504360` | 0xb0 | `solomonThm::setDemon(int)` |
| `0x00504410` | 0x68 | `solomonThm::setArea(int)` |
| `0x00504480` | 0x54 | `solomonThm::setTitle(int)` |
| `0x005044e0` | 0x70 | `solomonThm::closeInfo()` |
| `0x00504550` | 0x10 | `solomonThm::moveRight()` |
| `0x00504560` | 0x10 | `solomonThm::moveLeft()` |
| `0x00504570` | 0x3c | `solomonThm::isMove()` |
| `0x005045b0` | 0xe10 | `solomonThm::Polling()` |
| `0x005053c0` | 0x24c | `solomonThm::mThmScroll(float)` |
| `0x00505610` | 0x6ac | `solomonThm::mSetupThmBaseWin()` |
| `0x00505cc0` | 0x140 | `solomonThm::mSetupInfoWin()` |
| `0x00505e00` | 0x140 | `solomonThm::mReleaseThmBaseWin()` |
| `0x00505f40` | 0x1a8 | `solomonThm::mSetupAreaWin()` |
| `0x005060f0` | 0x278 | `solomonThm::mSetupDemonWin()` |
| `0x00506370` | 0x224 | `solomonThm::mSetupKeyWin()` |
| `0x005065a0` | 0x34 | `solomonThm::setHintData(int, int)` |
| `0x005065e0` | 0x2c4 | `solomonThm::mSetupHintWin()` |
| `0x005068b0` | 0x318 | `solomonThm::dispHint(int)` |

Decompiled source: `decomp/G/solomonThm.c`.
