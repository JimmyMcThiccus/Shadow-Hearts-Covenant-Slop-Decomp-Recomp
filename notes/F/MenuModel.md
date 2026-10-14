# MenuModel

3D model shown inside menus (character viewer in equip/status): model + motion player; `Order`, `CalcMatrix`, `SetAngle`, alpha/colour override, callbacks for translation/event/motion end.

## Virtual table (`__vt__MenuModel`)

| slot | function |
|---|---|
| 0x08 | `__dt__9MenuModelFv` |
| 0x0c | `getPacket__9MenuModelFv` |
| 0x18 | `@20@__dt__9MenuModelFv` |
| 0x1c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x20 | `create__5ModelFP9BufMemory` |
| 0x24 | `create__5ModelFPUc` |
| 0x28 | `calcMatrix__5ModelFP6Matrix` |
| 0x2c | `addTime__5ModelFf` |
| 0x30 | `TranseCallBack__9MenuModelFRC7FVector7FVector` |
| 0x34 | `EventCallBack__9MenuModelFPCcPCciiUi` |
| 0x38 | `MotionEndCallBack__9MenuModelFPCc` |
| 0x3c | `setAtomic__5ModelFP16_ModelFileHeaderP20_ModelTriangleHeader` |
| 0x40 | `DeleteSetUp__9MenuModelFv` |
| 0x44 | `ShadowProcess__5ModelFv` |

## Constructed by

`Create__13MenuModelPackFP16MenuModelManeger`, `Polling__16MenuModelManegerFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00281a80 | 0xc4 | `__ct__9MenuModelFv` | `MenuModel::MenuModel()` |
| 0x00281b50 | 0xc0 | `__dt__9MenuModelFv` | `MenuModel::~MenuModel()` |
| 0x00281c10 | 0x6c | `Order__9MenuModelFP13MenuModelPackii` | `MenuModel::Order(MenuModelPack*, int, int)` |
| 0x00281c80 | 0x140 | `CalcMatrix__9MenuModelFv` | `MenuModel::CalcMatrix()` |
| 0x00281dc0 | 0xac | `EnableAlpha__9MenuModelFv` | `MenuModel::EnableAlpha()` |
| 0x00281e70 | 0xac | `DisableAlpha__9MenuModelFv` | `MenuModel::DisableAlpha()` |
| 0x00281f20 | 0xcc | `SetAlpha__9MenuModelFUc` | `MenuModel::SetAlpha(unsigned char)` |
| 0x00281ff0 | 0x88 | `SetAngle__9MenuModelFf` | `MenuModel::SetAngle(float)` |
| 0x00282080 | 0x1c0 | `SetSingleColor__9MenuModelFUcUcUc` | `MenuModel::SetSingleColor(unsigned char, unsigned char, unsigned char)` |
| 0x00282260 | 0x3c | `DeleteSetUp__9MenuModelFv` | `MenuModel::DeleteSetUp()` |
| 0x002822a0 | 0x4c | `TranseCallBack__9MenuModelFRC7FVector7FVector` | `MenuModel::TranseCallBack(const FVector&, FVector)` |
| 0x002822f0 | 0xb0 | `EventCallBack__9MenuModelFPCcPCciiUi` | `MenuModel::EventCallBack(const char*, const char*, int, int, unsigned int)` |
| 0x002823a0 | 0x58 | `MotionEndCallBack__9MenuModelFPCc` | `MenuModel::MotionEndCallBack(const char*)` |
| 0x00282400 | 0x38 | `getPacket__9MenuModelFv` | `MenuModel::getPacket()` |
| 0x00282440 | 0x138 | `GetPacket__9MenuModelFUc` | `MenuModel::GetPacket(unsigned char)` |
| 0x00282580 | 0x8 | `@20@__dt__9MenuModelFv` | `@20@__dt__9MenuModelFv` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuModel.c`
