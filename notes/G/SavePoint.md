# SavePoint

* base: `CPolObj`; allocation size: 0xc0; ctor JP `0x00430b80`
* embedded sub-objects: `+0x30 SvpLight`, `+0xb0 FVector`
* vtable stores: `+0x14 __vt__9SavePoint`

| JP addr | size | method |
|---|---|---|
| `0x00430b80` | 0xb0 | `SavePoint::SavePoint()` |
| `0x00430c70` | 0x208 | `SavePoint::~SavePoint()` |
| `0x00430e80` | 0xa8 | `SavePoint::Create()` |
| `0x00430f30` | 0x394 | `SavePoint::CreateDirect(BufMemory*)` |
| `0x00431440` | 0x110 | `SavePoint::Show(int, int)` |
| `0x00431550` | 0x15c | `SavePoint::Hide()` |
| `0x004316b0` | 0x34 | `SavePoint::cbOff_1()` |
| `0x004316f0` | 0x120 | `SavePoint::cbOff_2()` |
| `0x00431810` | 0x40 | `SavePoint::cbOn()` |
| `0x00431850` | 0x740 | `SavePoint::Polling()` |
| `0x00432030` | 0x130 | `SavePoint::CheckOnPoint(FVector&)` |
| `0x004321d0` | 0x34 | `SavePoint::SetPos(FVector&)` |
| `0x004b71c0` | 0x24 | `SavePoint::SetCheckModel(Model*)` |
| `0x004b7860` | 0x44 | `SavePoint::IsOn()` |

Decompiled source: `decomp/G/SavePoint.c`.
