# worldMapPoint

Context: see `worldMap.md`.

* base: `-`; allocation size: 0x80; ctor JP `0x0050cc90`

| JP addr | size | method |
|---|---|---|
| `0x0050cc90` | 0x58 | `worldMapPoint::worldMapPoint()` |
| `0x0050ccf0` | 0xc0 | `worldMapPoint::~worldMapPoint()` |
| `0x0050cdb0` | 0x234 | `worldMapPoint::initialize(primLayer*, int, worldMap::SUBMAP_DATA*, int)` |
| `0x0050cff0` | 0xe8 | `worldMapPoint::setPos(float, float)` |

Decompiled source: `decomp/G/worldMapPoint.c`.
