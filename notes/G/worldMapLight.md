# worldMapLight

Context: see `worldMap.md`.

* base: `CPolObj`; allocation size: 0x94; ctor JP `0x0050be50`
* vtable stores: `+0x14 __vt__13worldMapLight`

| JP addr | size | method |
|---|---|---|
| `0x0050be50` | 0x9c | `worldMapLight::worldMapLight()` |
| `0x0050bef0` | 0x94 | `worldMapLight::~worldMapLight()` |
| `0x0050bf90` | 0x8c | `worldMapLight::initialize(primLayer*, int, int)` |
| `0x0050c020` | 0xac | `worldMapLight::setDest(float, float)` |
| `0x0050c0d0` | 0x1a0 | `worldMapLight::setPos(float, float)` |
| `0x0050c270` | 0x4dc | `worldMapLight::select()` |
| `0x0050c750` | 0x54 | `worldMapLight::unselect()` |
| `0x0050c7b0` | 0xf0 | `worldMapLight::mReleasePoint()` |
| `0x0050c8a0` | 0x3f0 | `worldMapLight::Polling()` |

Decompiled source: `decomp/G/worldMapLight.c`.
