# CXFModel

* base: `ExModel`; allocation size: unknown; ctor JP `0x004cc530`
* vtable stores: `+0x10 __vt__8CXFModel`

| JP addr | size | method |
|---|---|---|
| `0x004cad20` | 0x24 | `CXFModel::SetOwner(CFieldModel*)` |
| `0x004cc530` | 0x4c | `CXFModel::CXFModel()` |
| `0x004cc580` | 0x84 | `CXFModel::~CXFModel()` |
| `0x004cc610` | 0x90 | `CXFModel::getPacket()` |
| `0x004cc6a0` | 0x74 | `CXFModel::EventCallBack(const char*, const char*, int, int, unsigned int)` |
| `0x004cc720` | 0x34 | `CXFModel::MotionEndCallBack(const char*)` |
| `0x004cc760` | 0x58 | `CXFModel::TranseCallBack(const FVector&, FVector)` |
| `0x004ce030` | 0x8 | `CXFModel::~CXFModel()` |

Decompiled source: `decomp/G/CXFModel.c`.
