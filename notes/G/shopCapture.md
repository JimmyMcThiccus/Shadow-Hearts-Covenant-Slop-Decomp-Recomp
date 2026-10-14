# shopCapture

Context: see `shop.md`.

* base: `VI`; allocation size: 0x280; ctor JP `0x004e8fc0`

| JP addr | size | method |
|---|---|---|
| `0x004e8fc0` | 0x324 | `shopCapture::shopCapture(int)` |
| `0x004e92f0` | 0x11c | `shopCapture::~shopCapture()` |
| `0x004e9410` | 0x54 | `shopCapture::DelayDeleteRequest()` |
| `0x004e9470` | 0x40 | `shopCapture::startCapture()` |
| `0x004e94b0` | 0x58 | `shopCapture::changeLayer(int)` |
| `0x004e9510` | 0x84 | `shopCapture::setDisp(int, float, float, float, float)` |
| `0x004e95a0` | 0x78 | `shopCapture::setRGBA(int, int, int, int)` |
| `0x004e9620` | 0x12d4 | `shopCapture::getPacket()` |
| `0x004ea900` | 0x4c4 | `shopCapture::calcPos()` |
| `0x004eadd0` | 0x1fc | `shopCapture::mSetCenterPos()` |
| `0x004eafd0` | 0x8 | `shopCapture::~shopCapture()` |

Decompiled source: `decomp/G/shopCapture.c`.
