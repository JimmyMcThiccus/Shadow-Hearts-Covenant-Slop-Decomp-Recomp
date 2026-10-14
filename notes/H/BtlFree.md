# BtlFree

Free functions in BATTLE.BIN (btlsub.cpp / btlapi.cpp): effect helpers (`EffectDamageSet`, `CharactorShow`, `WeaponShow`, `ComboStopOff`, `GetFusionCharactor`, `CharacterTargetMove`, `BeginMagicEffectClear`...). 


## Methods (30)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 005d8c60 | 006234e0 | 0x3a0 | `Get3DAngle(FVector)` |
| 005d9000 | 006238f0 | 0x380 | `Get3DAngleRad(FVector)` |
| 005d9380 | 00623ce0 | 0x890 | `Get3DAngle2(FVector)` |
| 005d9c10 | 00624dd0 | 0x1a0 | `GetPointToLineLength(FVector, FVector, FVector, FVector *)` |
| 005d9db0 |  | 0x690 | `IdelMotionReset(int)` |
| 005da440 |  | 0x13e0 | `StatusRecovery(int, int)` |
| 005dba20 | 00628560 | 0xf0 | `CameraControlStatus(bool)` |
| 005dbb10 | 00628670 | 0x130 | `BeginMagicEffectClear(int)` |
| 005dbc40 | 006287a0 | 0xb0 | `BeginMagicEffectClear2(int)` |
| 005dbcf0 |  | 0x60 | `MagicMotionEndSet(int)` |
| 005dbd50 | 006288d0 | 0x5730 | `EffectDamageSet(int, short, short, short, FVector, bool, int, int, int, int, int)` |
| 005e1480 |  | 0x10 | `GetBattleBgModel()` |
| 005e1490 |  | 0x60 | `ChangeFusionModel()` |
| 005e14f0 | 0062eb70 | 0x490 | `ComboStopOff(int)` |
| 005e1980 | 0062f0a0 | 0x230 | `GetFusionCharactor(int *, int *)` |
| 005e1bb0 |  | 0x30 | `CameraCutChange()` |
| 005e1be0 | 0062f2e0 | 0x860 | `CharactorShow(int, bool)` |
| 005e2440 | 0062fff0 | 0x80 | `WeaponShow(int, int, bool)` |
| 005e24c0 | 00630090 | 0x150 | `BattleBGShow(bool)` |
| 005e2610 | 006301f0 | 0x6e0 | `MagicStartEffectCall(int)` |
| 005e2cf0 | 006308d0 | 0x3d0 | `MagicStartEffectCall2(int, int, FVector *, float, float)` |
| 005e30c0 | 00630ca0 | 0x6c0 | `HitMarkEffectCall(int, FVector, FVector, float)` |
| 005e3780 | 00631360 | 0x70 | `BattleBGShowParts(uint, uint)` |
| 005e37f0 | 006313d0 | 0xb0 | `CharacterPushMode(int, bool)` |
| 005e38a0 |  | 0x3340 | `GetWarpPos(int, bool)` |
| 005e6be0 | 00632770 | 0x580 | `CharacterTargetMove(int, int, float, bool)` |
| 005e7160 |  | 0x2a0 | `SetForceDeath(int)` |
| 005e7400 | 00633530 | 0xc0 | `SetCharacterWallHitMode(int, bool)` |
| 005e74c0 |  | 0x30 | `BattleNext()` |
| 005e74f0 | 00633620 | 0x510 | `BattleCheck(int, int)` |
