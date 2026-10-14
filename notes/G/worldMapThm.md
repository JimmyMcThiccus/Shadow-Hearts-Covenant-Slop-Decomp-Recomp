# worldMapThm

Context: see `worldMap.md`.

* base: `-`; allocation size: 0x18; ctor JP `0x0050b810`

| JP addr | size | method |
|---|---|---|
| `0x0050b810` | 0x28 | `worldMapThm::worldMapThm()` |
| `0x0050b840` | 0x5c | `worldMapThm::~worldMapThm()` |
| `0x0050b8a0` | 0x24 | `worldMapThm::initialize(primTex*)` |
| `0x0050b8d0` | 0x74 | `worldMapThm::dispThm(int, unsigned char*, unsigned char*)` |
| `0x0050b950` | 0x58 | `worldMapThm::fadeout()` |
| `0x0050b9b0` | 0x28 | `worldMapThm::kill()` |
| `0x0050b9e0` | 0x3fc | `worldMapThm::mSetupThmWin()` |
| `0x0050bde0` | 0x70 | `worldMapThm::mReleaseThmWin()` |

Decompiled source: `decomp/G/worldMapThm.c`.
