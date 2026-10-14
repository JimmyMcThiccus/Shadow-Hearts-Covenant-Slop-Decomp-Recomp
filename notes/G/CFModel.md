# CFModel

* base: `Model`; allocation size: unknown; ctor JP `0x004cc280`
* vtable stores: `+0x10 __vt__7CFModel`

| JP addr | size | method |
|---|---|---|
| `0x004cacf0` | 0x24 | `CFModel::SetOwner(CFieldModel*)` |
| `0x004cc280` | 0x4c | `CFModel::CFModel()` |
| `0x004cc2d0` | 0x84 | `CFModel::~CFModel()` |
| `0x004cc360` | 0x7c | `CFModel::getPacket()` |
| `0x004cc410` | 0x74 | `CFModel::EventCallBack(const char*, const char*, int, int, unsigned int)` |
| `0x004cc490` | 0x34 | `CFModel::MotionEndCallBack(const char*)` |
| `0x004cc4d0` | 0x58 | `CFModel::TranseCallBack(const FVector&, FVector)` |
| `0x004ce020` | 0x8 | `CFModel::~CFModel()` |

Decompiled source: `decomp/G/CFModel.c`.
