# WarpPoint

* base: `CPolObj`; allocation size: 0xe0; ctor JP `0x00432a30`

| JP addr | size | method |
|---|---|---|
| `0x00432a30` | 0x174 | `WarpPoint::WarpPoint()` |
| `0x00432c10` | 0x244 | `WarpPoint::~WarpPoint()` |
| `0x00432e60` | 0x1c8 | `WarpPoint::Create(short)` |
| `0x00433030` | 0x410 | `WarpPoint::CreateDirect(BufMemory*)` |
| `0x00433440` | 0x248 | `WarpPoint::Show(int, int, bool)` |
| `0x00433690` | 0x17c | `WarpPoint::Hide()` |
| `0x00433810` | 0x120c | `WarpPoint::Polling()` |
| `0x00434b50` | 0x168 | `WarpPoint::CheckOnPoint(FVector&)` |
| `0x00434cc0` | 0x98 | `WarpPoint::StartShowEffect()` |
| `0x00434d60` | 0x38 | `WarpPoint::StartHideEffect()` |
| `0x00434da0` | 0x90 | `WarpPoint::SetAlpha(float)` |
| `0x00434e30` | 0x200 | `WarpPoint::WarpIn(FVector&, FVector&, short, bool)` |
| `0x00435030` | 0x1e8 | `WarpPoint::WarpOut(FVector&, FVector&, short, bool)` |
| `0x00435220` | 0x300 | `WarpPoint::ShowFader(FVector&, FVector&, short, bool)` |
| `0x00435520` | 0xec | `WarpPoint::SetLight()` |
| `0x004b7a80` | 0x34 | `WarpPoint::SetPos(FVector&)` |
| `0x004b7e60` | 0x24 | `WarpPoint::SetCheckModel(Model*)` |
| `0x004b8610` | 0x54 | `WarpPoint::IsWarpEnded()` |

Decompiled source: `decomp/G/WarpPoint.c`.
