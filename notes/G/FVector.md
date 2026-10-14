# FVector

Copy of a **main-executable** class statically linked into FIELD.BIN (duplicated code of another section's class); documented by the owning section. Listed here for address mapping only.

* base: `-`; allocation size: unknown; ctor JP `0x00430c50`

| JP addr | size | method |
|---|---|---|
| `0x00430c50` | 0x20 | `FVector::FVector()` |
| `0x004312f0` | 0x40 | `FVector::Origin()` |
| `0x00431330` | 0x88 | `FVector::FVector(float, float, float, float)` |
| `0x004313c0` | 0x1c | `FVector::vw()` |
| `0x004313e0` | 0x1c | `FVector::vz()` |
| `0x00431400` | 0x1c | `FVector::vy()` |
| `0x00431420` | 0x18 | `FVector::vx()` |
| `0x00431fc0` | 0x14 | `FVector::__as(const FVector&)` |
| `0x00432160` | 0x6c | `FVector::__mi` |
| `0x004325b0` | 0x6c | `FVector::__pl` |
| `0x00432970` | 0x1c | `FVector::__ami(const FVector&)` |
| `0x00434a80` | 0x1c | `FVector::__apl(const FVector&)` |
| `0x004a8160` | 0x74 | `FVector::__ml` |
| `0x004a81e0` | 0x24 | `FVector::InnerProduct` |
| `0x004b1b50` | 0x1c | `FVector::__amu(const FVector&)` |
| `0x004d0440` | 0x8c | `FVector::__as(const IVector&)` |

Decompiled source: `decomp/G/_OverlayCopies_FVector.c`.
