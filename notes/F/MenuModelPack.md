# MenuModelPack

A model with its motion set and effect models; `SetMotion`, `SetAction`, `AddTime`, `BootEffect`, `FindMotion(MenuMotionConnect*, name)`.

## Virtual table (`__vt__MenuModelPack`)

| slot | function |
|---|---|
| 0x08 | `__dt__13MenuModelPackFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |

## Constructed by

`Reset__16MenuModelManegerFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0028f7d0 | 0x98 | `FindMotion__13MenuModelPackFP17MenuMotionConnectPCc` | `MenuModelPack::FindMotion(MenuMotionConnect*, const char*)` |
| 0x0028f870 | 0xfc | `__ct__13MenuModelPackFv` | `MenuModelPack::MenuModelPack()` |
| 0x0028f970 | 0x2a8 | `__dt__13MenuModelPackFv` | `MenuModelPack::~MenuModelPack()` |
| 0x0028fc20 | 0x9c | `Create__13MenuModelPackFP16MenuModelManeger` | `MenuModelPack::Create(MenuModelManeger*)` |
| 0x0028fcc0 | 0x170 | `Order__13MenuModelPackFv` | `MenuModelPack::Order()` |
| 0x0028fe30 | 0xe8 | `Standby__13MenuModelPackFv` | `MenuModelPack::Standby()` |
| 0x0028ff20 | 0x134 | `SafeDestroy__13MenuModelPackFv` | `MenuModelPack::SafeDestroy()` |
| 0x00290060 | 0x130 | `AddTime__13MenuModelPackFf` | `MenuModelPack::AddTime(float)` |
| 0x00290190 | 0x70 | `EnableAlpha__13MenuModelPackFv` | `MenuModelPack::EnableAlpha()` |
| 0x00290200 | 0x70 | `DisableAlpha__13MenuModelPackFv` | `MenuModelPack::DisableAlpha()` |
| 0x00290270 | 0x80 | `SetAlpha__13MenuModelPackFUc` | `MenuModelPack::SetAlpha(unsigned char)` |
| 0x002902f0 | 0xf8 | `SetMotion__13MenuModelPackFPCcUcUc` | `MenuModelPack::SetMotion(const char*, unsigned char, unsigned char)` |
| 0x002903f0 | 0xa8 | `SetMotion__13MenuModelPackFPCc` | `MenuModelPack::SetMotion(const char*)` |
| 0x002904a0 | 0x1b8 | `Event__13MenuModelPackFP9MenuModelPCcPCc` | `MenuModelPack::Event(MenuModel*, const char*, const char*)` |
| 0x00290660 | 0x194 | `FinishMotion__13MenuModelPackFP9MenuModelPCc` | `MenuModelPack::FinishMotion(MenuModel*, const char*)` |
| 0x00290800 | 0xf0 | `FinishEffect__13MenuModelPackFP15MenuEffectModelPCc` | `MenuModelPack::FinishEffect(MenuEffectModel*, const char*)` |
| 0x002908f0 | 0x1a4 | `SetAction__13MenuModelPackFv` | `MenuModelPack::SetAction()` |
| 0x00290aa0 | 0x1c0 | `BootEffect__13MenuModelPackFPCci` | `MenuModelPack::BootEffect(const char*, int)` |
| 0x00290c60 | 0x48 | `ResetEffect__13MenuModelPackFv` | `MenuModelPack::ResetEffect()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuModelPack.c`
