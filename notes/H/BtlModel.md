# BtlModel

Battle model wrapper: skeleton/motion set, weapon models, bounding boxes (`BtlModel::EventCallBack/MotionEndCallBack` forward motion events to `CBattle::MotionEventCallBack`
(0x004a2bf0, 22 KB: damage frames, SE, effects) and `MotionEndCallBack`). 45 methods incl. alpha (`SetBtlModelAlpha`), attach points, weapon show/hide, colour tint. Uses `sh2_formats::{model,motion}` in the port.


## Methods (45)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00480ec0 |  | 0x20 | `BtlModel::GetPos()` |
| 0054b9c0 | 0057e6a0 | 0x210 | `BtlModel::__ct(short)` |
| 0054bbd0 | 0057e890 | 0x220 | `BtlModel::__dt()` |
| 0054bdf0 | 0057eab0 | 0x2b0 | `BtlModel::DeleteSetUp()` |
| 0054c0a0 | 0057ed60 | 0x240 | `BtlModel::Create(uchar *)` |
| 0054c2e0 | 0057efc0 | 0x50 | `BtlModel::CreateShadow(uchar *)` |
| 0054c330 | 0057f010 | 0x270 | `BtlModel::TranseCallBack(FVector *, FVector)` |
| 0054c5a0 | 0057f280 | 0x80 | `BtlModel::EventCallBack(char *, char *, int, int, uint)` |
| 0054c620 | 0057f310 | 0x1650 | `BtlModel::MotionEndCallBack(char *)` |
| 0054dc70 | 00580b80 | 0x700 | `BtlModel::addTime(float)` |
| 0054e370 | 00581280 | 0x190 | `BtlModel::calcMatrix(Matrix *)` |
| 0054e500 |  | 0x1a30 | `BtlModel::SetBtlMotion(int, float)` |
| 0054ff30 | 00581420 | 0x1a30 | `BtlModel::SetNextBtlMotion(int, float)` |
| 00551960 | 00585230 | 0x230 | `BtlModel::setMotion(char *)` |
| 00551b90 | 00585460 | 0x230 | `BtlModel::setNextMotion(char *)` |
| 00551dc0 | 00585690 | 0x1f0 | `BtlModel::OTEntry(int, int)` |
| 00551fb0 | 00585890 | 0x1b0 | `BtlModel::OTRelease()` |
| 00552160 | 00585a30 | 0x890 | `BtlModel::WeaponShow(int, bool)` |
| 005529f0 | 005862f0 | 0x90 | `BtlModel::SetPos(FVector *)` |
| 00552a80 | 00586380 | 0x130 | `BtlModel::SetAngle(FVector *)` |
| 00552bb0 | 005864b0 | 0x60 | `BtlModel::SetPosAngle(FVector *, FVector *)` |
| 00552c10 | 00586510 | 0x180 | `BtlModel::SetCameraAlpha(float, bool)` |
| 00552d90 | 00586690 | 0x2b0 | `BtlModel::SetModelColor(float, float, float)` |
| 00553040 | 00586900 | 0x2f0 | `BtlModel::CreateRightWeapon(uchar *)` |
| 00553330 | 00586c10 | 0x90 | `BtlModel::CreateRightWeaponShadow(uchar *)` |
| 005533c0 | 00586ca0 | 0x2f0 | `BtlModel::CreateLeftWeapon(uchar *)` |
| 005536b0 | 00586fb0 | 0x90 | `BtlModel::CreateLeftWeaponShadow(uchar *)` |
| 00553740 | 00587040 | 0x2f0 | `BtlModel::CreateCenterWeapon(uchar *)` |
| 00553a30 | 00587350 | 0x90 | `BtlModel::CreateCenterWeaponShadow(uchar *)` |
| 00553ac0 |  | 0x210 | `BtlModel::SetScale(float)` |
| 00553cd0 | 00587550 | 0x1e0 | `BtlModel::ShadowOn()` |
| 00553eb0 | 00587730 | 0x1d0 | `BtlModel::ShadowOff()` |
| 00554080 | 00587b20 | 0x1f0 | `BtlModel::searchBBoxIndex(char *, int)` |
| 00554270 | 00587d10 | 0x200 | `BtlModel::searchRWBBoxIndex(char *, int)` |
| 00554470 | 00587f10 | 0x200 | `BtlModel::searchLWBBoxIndex(char *, int)` |
| 00554670 | 00588110 | 0x4af0 | `BtlModel::ClutCtrl(float, float, float, float)` |
| 00559160 | 0058cc00 | 0xf0 | `BtlModel::SetCtrlMode(bool, bool)` |
| 00559250 | 0058ccf0 | 0x800 | `BtlModel::SetOpticalCamouflage(int, int)` |
| 00559a50 | 0058d4f0 | 0xbc0 | `BtlModel::SetBtlModelAlpha(int, int, int)` |
| 0055a610 | 0058e110 | 0x270 | `BtlModel::SetZWriteOff()` |
| 0055a880 |  | 0x6e0 | `BtlModel::AddModelEffect(int, int, char *)` |
| 0055af60 | 0058eef0 | 0x80 | `BtlModel::SetIdleCtrlFrame(int, FVector)` |
| 0055afe0 | 0058ef80 | 0x3c0 | `BtlModel::ReleaseWeapon(int)` |
| 0055b3a0 |  | 0x10 | `@20@__dt__8BtlModelFv` |
| 0057bf70 |  | 0x30 | `BtlModel::ModelEffectReset()` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 1 | @20@ |
| +0x10 | u32/int | 2 | Create, __dt__8BtlModelFv |
| +0x1c | u32 | 1 | __dt__8BtlModelFv |
| +0x30 | u32/int | 22 | CreateCenterWeapon, CreateLeftWeapon, CreateRightWeapon, ReleaseWeapon, SetAngle, SetPos… |
| +0x34 | u32 | 1 | MotionEndCallBack |
| +0x48 | int | 8 | SetBtlModelAlpha, SetOpticalCamouflage |
| +0x4c | int | 6 | Create, SetBtlModelAlpha, SetZWriteOff |
| +0x58 | int | 1 | searchBBoxIndex |
| +0x5c | int | 3 | SetBtlModelAlpha, SetOpticalCamouflage |
| +0x60 | int | 1 | searchBBoxIndex |
| +0x64 | int | 6 | Create, SetBtlModelAlpha, SetZWriteOff |
| +0x28c | int | 2 | SetBtlModelAlpha |
| +0x29c | int | 1 | SetBtlModelAlpha |
| +0x4b0 | byte | 137 | Create, CreateCenterWeapon, CreateCenterWeaponShadow, CreateLeftWeapon, CreateLeftWeaponShadow, CreateRightWeapon… |
| +0x4b1 | byte | 49 | AddModelEffect, DeleteSetUp, OTEntry, OTRelease, SetBtlModelAlpha, SetCtrlMode… |
| +0x4b2 | byte | 21 | OTEntry, WeaponShow |
| +0x4b4 | short | 2 | EventCallBack, MotionEndCallBack |
| +0x4c0 | int | 1 | SetPos |
| +0x4c4 | int | 1 | SetPos |
| +0x4c8 | u32 | 1 | SetPos |
| +0x4cc | u32 | 1 | SetPos |
| +0x4d0 | int/u32 | 2 | SetAngle |
| +0x4d4 | int/u32 | 2 | SetAngle |
| +0x4d8 | u32 | 2 | SetAngle |
| +0x4dc | u32 | 1 | SetAngle |
| +0x4e0 | float | 3 | SetAngle |
| +0x4e4 | float | 3 | OTEntry, SetOpticalCamouflage |
| +0x4ec | float | 3 | OTEntry, SetOpticalCamouflage |
| +0x4f0 | u16 | 39 | MotionEndCallBack, SetCtrlMode |
| +0x4f2 | u16/short | 46 | MotionEndCallBack, SetCtrlMode |
| +0x500 | u8 | 36 | MotionEndCallBack |
| +0x518 | u32/int | 32 | @20@, MotionEndCallBack |
| +0x51c | int | 2 | @20@ |
| +0x520 | int | 2 | @20@ |
| +0x52c | int/u32 | 77 | CreateRightWeapon, CreateRightWeaponShadow, DeleteSetUp, OTEntry, OTRelease, ReleaseWeapon… |
| +0x530 | int/u32 | 77 | CreateLeftWeapon, CreateLeftWeaponShadow, DeleteSetUp, OTEntry, OTRelease, ReleaseWeapon… |
| +0x534 | int/u32 | 74 | CreateCenterWeapon, CreateCenterWeaponShadow, DeleteSetUp, OTEntry, OTRelease, ReleaseWeapon… |
| +0x538 | int/u32 | 3 | CreateShadow, ShadowOff, ShadowOn |
| +0x53c | int/u32 | 6 | CreateRightWeaponShadow, ReleaseWeapon, ShadowOff, ShadowOn, WeaponShow |
| +0x540 | int/u32 | 6 | CreateLeftWeaponShadow, ReleaseWeapon, ShadowOff, ShadowOn, WeaponShow |
| +0x544 | int/u32 | 6 | CreateCenterWeaponShadow, ReleaseWeapon, ShadowOff, ShadowOn, WeaponShow |
| +0x548 | u32 | 1 | SetOpticalCamouflage |
| +0x54c | int | 3 | @20@ |
| +0x550 | int/float | 4 | @20@, DeleteSetUp |
| +0x554 | int/float | 4 | @20@, DeleteSetUp |
| +0x558 | int/float | 4 | @20@, DeleteSetUp |
| +0x560 | int/u32 | 10 | Create, __dt__8BtlModelFv |
| +0x564 | int/u32 | 14 | CreateRightWeapon, ReleaseWeapon, __dt__8BtlModelFv |
| +0x568 | int/u32 | 14 | CreateLeftWeapon, ReleaseWeapon, __dt__8BtlModelFv |
| +0x56c | int/u32 | 14 | CreateCenterWeapon, ReleaseWeapon, __dt__8BtlModelFv |
| +0x574 | u32 | 1 | DeleteSetUp |
| +0x578 | u32 | 1 | OTEntry |
| +0x584 | u32 | 1 | DeleteSetUp |
| +0x594 | u32 | 1 | DeleteSetUp |
| +0x5a4 | u32 | 1 | DeleteSetUp |
| +0x5b0 | int/u32 | 3 | SetIdleCtrlFrame, setMotion, setNextMotion |
| +0x5c0 | u32 | 1 | SetIdleCtrlFrame |
| +0x5c4 | u32 | 1 | SetIdleCtrlFrame |
| +0x5c8 | u32 | 1 | SetIdleCtrlFrame |
| +0x5cc | u32 | 1 | SetIdleCtrlFrame |
| +0x5d0 | int | 1 | SetIdleCtrlFrame |
| +0x5d4 | int | 1 | SetIdleCtrlFrame |
| +0x5d8 | u32 | 1 | SetIdleCtrlFrame |
| +0x5dc | u32 | 1 | SetIdleCtrlFrame |
| +0x5e0 | u32 | 4 | OTEntry, WeaponShow |
| +0x5e4 | u32 | 4 | OTEntry, WeaponShow |
