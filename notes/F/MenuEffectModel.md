# MenuEffectModel

Effect model instance used by `MenuModelPack` (`Order`, `Release`, `SetTest`).

## Virtual table (`__vt__MenuEffectModel`)

| slot | function |
|---|---|
| 0x08 | `__dt__15MenuEffectModelFv` |
| 0x0c | `getPacket__7ExModelFv` |
| 0x18 | `@20@__dt__15MenuEffectModelFv` |
| 0x1c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x20 | `create__7ExModelFP9BufMemory` |
| 0x24 | `create__7ExModelFPUc` |
| 0x28 | `calcMatrix__7ExModelFP6Matrix` |
| 0x2c | `addTime__5ModelFf` |
| 0x30 | `TranseCallBack__7ExModelFRC7FVector7FVector` |
| 0x34 | `EventCallBack__7ExModelFPCcPCciiUi` |
| 0x38 | `MotionEndCallBack__15MenuEffectModelFPCc` |
| 0x3c | `setAtomic__7ExModelFP16_ModelFileHeaderP20_ModelTriangleHeader` |
| 0x40 | `DeleteSetUp__15MenuEffectModelFv` |
| 0x44 | `ShadowProcess__5ModelFv` |

## Constructed by

`ReadFile__16MenuModelManegerFiP9BufMemory`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00291780 | 0x5c | `__ct__15MenuEffectModelFv` | `MenuEffectModel::MenuEffectModel()` |
| 0x002917e0 | 0x84 | `__dt__15MenuEffectModelFv` | `MenuEffectModel::~MenuEffectModel()` |
| 0x00291870 | 0x58 | `Order__15MenuEffectModelFv` | `MenuEffectModel::Order()` |
| 0x002918d0 | 0x60 | `Release__15MenuEffectModelFv` | `MenuEffectModel::Release()` |
| 0x00291930 | 0xac | `SetTest__15MenuEffectModelFi` | `MenuEffectModel::SetTest(int)` |
| 0x002919e0 | 0x3c | `DeleteSetUp__15MenuEffectModelFv` | `MenuEffectModel::DeleteSetUp()` |
| 0x00291a20 | 0x58 | `MotionEndCallBack__15MenuEffectModelFPCc` | `MenuEffectModel::MotionEndCallBack(const char*)` |
| 0x00291a80 | 0x8 | `@20@__dt__15MenuEffectModelFv` | `@20@__dt__15MenuEffectModelFv` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuEffectModel.c`
