# BtlCamera

Camera director. `CBattle` calls one of ~25 situation setters (`SetMoveCamera1`, `SetFusionCamera1`, `SetWinCamera1`, `SetLoseCamera1`, command/target cameras, per-character camera by `BtlChr+0x57a`).
Each interpolates position/look-at over time in `Polling`.


## Methods (31)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0055dbe0 | 00591d90 | 0x560 | `BtlCamera::__ct()` |
| 0055e140 | 005922f0 | 0xa0 | `BtlCamera::__dt()` |
| 0055e1e0 | 00592390 | 0x1dd90 | `BtlCamera::Polling()` |
| 0057c070 | 005a9050 | 0x1550 | `BtlCamera::UpdateCamera()` |
| 0057d5c0 | 005aa5a0 | 0x1f0 | `BtlCamera::CameraYPosCheck()` |
| 0057d7b0 | 005aa790 | 0x200 | `BtlCamera::SetFieldCamera(FVector, bool)` |
| 0057d9b0 | 005aa990 | 0x2a0 | `BtlCamera::SetNextComboCharacterCamera1(int, int, int, bool)` |
| 0057dc50 | 005aac30 | 0x250 | `BtlCamera::SetNextComboCharacterCamera2(FVector, int, int, bool)` |
| 0057dea0 | 005aae80 | 0x260 | `BtlCamera::SetHomeCharacterCamera1(int, bool)` |
| 0057e100 | 005ab0e0 | 0x250 | `BtlCamera::SetCharacterCamera1(int, bool)` |
| 0057e350 | 005ab590 | 0x250 | `BtlCamera::SetCharacterCamera2(int, bool)` |
| 0057e5a0 |  | 0x250 | `BtlCamera::SetCharacterCamera3(int, bool)` |
| 0057e7f0 | 005ab7e0 | 0x2b0 | `BtlCamera::SetSingleTargetCamera1(int, bool)` |
| 0057eaa0 | 005aba90 | 0x2f0 | `BtlCamera::SetSingleTargetCamera2(int, int, bool)` |
| 0057ed90 | 005abd80 | 0x340 | `BtlCamera::SetCircleTargetCamera1(int, int, int, int, ECCParam *, bool)` |
| 0057f0d0 | 005ac070 | 0x350 | `BtlCamera::SetStraightTargetCamera1(int, int, int, int, ECCParam *, bool)` |
| 0057f420 | 005ac3d0 | 0x350 | `BtlCamera::SetStraightEXTargetCamera1(int, int, int, int, ECCParam *, bool)` |
| 0057f770 | 005ac730 | 0x2f0 | `BtlCamera::SetAllTargetCamera1(int, int, int, ECCParam *, bool)` |
| 0057fa60 | 005aca20 | 0x230 | `BtlCamera::SetMoveTargetCamera1(FVector, int, bool)` |
| 0057fc90 | 005acc50 | 0x270 | `BtlCamera::SetJudgementRingCamera1(int, int, bool)` |
| 0057ff00 | 005acec0 | 0x270 | `BtlCamera::SetAttackMoveCamera1(int, int, bool)` |
| 00580170 | 005ad130 | 0x280 | `BtlCamera::SetAttackCamera1(int, int, int, bool)` |
| 005803f0 | 005c2890 | 0x250 | `BtlCamera::SetMoveCamera1(int, FVector, int, bool)` |
| 00580640 | 005c2ae0 | 0x2c0 | `BtlCamera::SetComboMemberCamera1(int, bool)` |
| 00580900 | 005c2da0 | 0x2e0 | `BtlCamera::SetComboMemberCamera2(int, int, bool)` |
| 00580be0 | 005c3c10 | 0x3b0 | `BtlCamera::SetWinCamera1(int, bool)` |
| 00580f90 | 005c40c0 | 0x330 | `BtlCamera::SetLoseCamera1(bool)` |
| 005812c0 | 005c43f0 | 0x280 | `BtlCamera::SetFusionCamera1(int, int, bool)` |
| 00581540 | 005c4670 | 0x760 | `BtlCamera::BtlCameraFunc()` |
| 00581ca0 | 005c5000 | 0x15d0 | `BtlCamera::BtlChrAlphaCtrl(FVector, FVector, bool)` |
| 00583270 | 005c65f0 | 0x4110 | `BtlCamera::BtlBGWallAlphaCtrl(FVector, FVector, float, bool)` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x14 | u32 | 1 | __dt__9BtlCameraFv |
| +0x18 | byte | 271 | SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3, SetComboMemberCamera1… |
| +0x19 | byte | 200 | SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3, SetComboMemberCamera1… |
| +0x1c | u16/short | 26 | SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3, SetComboMemberCamera1… |
| +0x1e | u16 | 19 | SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3, SetComboMemberCamera1… |
| +0x24 | float | 4 | UpdateCamera |
| +0x30 | int/u64 | 5 | UpdateCamera |
| +0x34 | int | 3 | UpdateCamera |
| +0x38 | u32/float | 4 | UpdateCamera |
| +0x3c | u32 | 4 | UpdateCamera |
| +0x40 | float/u32/int | 11 | UpdateCamera |
| +0x44 | float/u32/int | 11 | UpdateCamera |
| +0x48 | float/u32 | 11 | UpdateCamera |
| +0x4c | u32 | 1 | UpdateCamera |
| +0x50 | u64/float | 8 | CameraYPosCheck, UpdateCamera |
| +0x54 | float | 2 | CameraYPosCheck |
| +0x58 | u32/float | 5 | CameraYPosCheck, UpdateCamera |
| +0x5c | u32 | 3 | UpdateCamera |
| +0x60 | float/u64/u32 | 8 | SetFieldCamera, UpdateCamera |
| +0x64 | float/u32/int | 6 | SetFieldCamera, UpdateCamera |
| +0x68 | u32/float | 7 | SetFieldCamera, UpdateCamera |
| +0x6c | u32 | 2 | SetFieldCamera, UpdateCamera |
| +0x70 | int | 1 | SetWinCamera1 |
| +0x74 | int | 1 | SetWinCamera1 |
| +0x78 | u32 | 1 | SetWinCamera1 |
| +0x7c | u32 | 1 | SetWinCamera1 |
| +0x84 | u32 | 20 | SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3, SetComboMemberCamera1… |
| +0x88 | float/u32 | 7 | UpdateCamera |
| +0x8c | float/u32 | 12 | UpdateCamera |
| +0x90 | u32/float | 7 | UpdateCamera |
| +0xa0 | float/u32 | 9 | UpdateCamera |
| +0xa4 | float/u32 | 9 | UpdateCamera |
| +0xa8 | float/u32 | 9 | UpdateCamera |
| +0xb0 | float/u32 | 14 | UpdateCamera |
| +0xb4 | float/u32 | 14 | UpdateCamera |
| +0xb8 | float/u32 | 14 | UpdateCamera |
| +0xc0 | u32/float | 7 | UpdateCamera |
| +0xc4 | u32/float | 7 | UpdateCamera |
| +0xc8 | u32/float | 7 | UpdateCamera |
| +0xd0 | uint/int | 17 | SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3, SetComboMemberCamera1… |
| +0xd4 | uint/u32 | 7 | SetAttackCamera1, SetAttackMoveCamera1, SetComboMemberCamera2, SetJudgementRingCamera1, SetNextComboCharacterCamera1, SetNextComboCharacterCamera2… |
| +0xd8 | uint/u32 | 2 | SetAttackCamera1, SetNextComboCharacterCamera1 |
| +0xdc | u32 | 8 | SetComboMemberCamera1, SetComboMemberCamera2, SetFusionCamera1, SetHomeCharacterCamera1, SetMoveTargetCamera1, SetNextComboCharacterCamera1… |
| +0xe0 | u32 | 2 | SetFusionCamera1, SetHomeCharacterCamera1 |
| +0xec | float | 1 | SetWinCamera1 |
| +0x100 | int | 3 | SetMoveCamera1, SetMoveTargetCamera1, SetNextComboCharacterCamera2 |
| +0x104 | int | 3 | SetMoveCamera1, SetMoveTargetCamera1, SetNextComboCharacterCamera2 |
| +0x108 | u32 | 3 | SetMoveCamera1, SetMoveTargetCamera1, SetNextComboCharacterCamera2 |
| +0x10c | u32 | 3 | SetMoveCamera1, SetMoveTargetCamera1, SetNextComboCharacterCamera2 |
| +0x140 | int/uint/u32 | 32 | BtlChrAlphaCtrl, SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3… |
| +0x1e8 | float | 1 | UpdateCamera |
| +0x210 | u32/int | 67 | SetAllTargetCamera1, SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3… |
| +0x214 | u32 | 19 | SetAttackCamera1, SetAttackMoveCamera1, SetCharacterCamera1, SetCharacterCamera2, SetCharacterCamera3, SetComboMemberCamera1… |
