# FieldFree (free functions of the overlay)

| JP addr | size | method |
|---|---|---|
| `0x00430a80` | 0x40 | `cbSvpCallback(int, BufMemory*, int, char*, void*)` |
| `0x00430ac0` | 0x34 | `CbOn(char*, void*)` |
| `0x00430b00` | 0x34 | `CbOff_1(char*, void*)` |
| `0x00430b40` | 0x34 | `CbOff_2(char*, void*)` |
| `0x00430c30` | 0x1c | `Init__Q29SavePoint18@class$2151SVP_cppFv` |
| `0x004329f0` | 0x40 | `cbWpCallback(int, BufMemory*, int, char*, void*)` |
| `0x00432bb0` | 0x1c | `Init__Q29WarpPoint17@class$2141WP_cppFv` |
| `0x00432bd0` | 0x3c | `__ct__Q29WarpPoint17@class$2140WP_cppFv` |
| `0x004a2a30` | 0x1c | `GetDTCExSize(_DTCINFO*)` |
| `0x004a2a50` | 0xa4 | `clipRadian(float&)` |
| `0x004a3f90` | 0x144 | `FldInitLSDPlayer()` |
| `0x004a4fe0` | 0x38 | `FieldBreakMCES()` |
| `0x004a5020` | 0xa0 | `FieldExitPauseMCES()` |
| `0x004a5250` | 0xec | `MCESInvokeBattle()` |
| `0x004a59f0` | 0x48 | `_toUpper(int)` |
| `0x004a5a40` | 0x98 | `_stricmp(const char*, const char*)` |
| `0x004a5f20` | 0x1ec | `MakeMoveControl(float&, float&, CPad*)` |
| `0x004b0c50` | 0x88 | `GetNumber(const char&*)` |
| `0x004b1590` | 0x5bc | `VectorOperation(int, _ParStack*)` |
| `0x004b2b10` | 0x38 | `cbLoadMotion(unsigned int, unsigned int, void*)` |
| `0x004b3d40` | 0x90 | `FindFrame(CFieldModel*, const char*)` |
| `0x004b4020` | 0x108 | `CalcStandParent(FVector&, CFieldModel*, float)` |
| `0x004b64c0` | 0x3c | `GetImgName(char*, const char*)` |
| `0x004b7110` | 0xb0 | `CreateSavePoint(_SavPoint*, Model*)` |
| `0x004b79c0` | 0xbc | `CreateWarpPoint(_WapPoint*, int)` |
| `0x004b9f50` | 0x1270 | `GetNearestPath(SDB::tagFCAMERA*, FVector, int&)` |
| `0x004bc080` | 0x1c | `Clear__Q29FldSpline6_flagsFv` |
| `0x004be430` | 0x1c | `clear__Q212CFieldCamera6_flagsFv` |
| `0x004bf920` | 0xa4 | `EncodeChar(int)` |
| `0x004bff50` | 0x170 | `EncodeMotionName(const char*)` |
| `0x004c00c0` | 0x1a8 | `DecodeMotionName(char*, unsigned int)` |
| `0x004c0270` | 0x60 | `GetMotionName(unsigned int)` |
| `0x004c02d0` | 0xc | `InitFieldModel()` |
| `0x004c02e0` | 0xc | `GetModelReadCt()` |
| `0x004c02f0` | 0x78 | `mdlReadCB(int, BufMemory*, int, char*, void*)` |
| `0x004c0370` | 0x6c | `mdlReadMotionCB(int, BufMemory*, int, char*, void*)` |
| `0x004c0770` | 0x30 | `__ct__Q211CFieldModel7_memberFv` |
| `0x004c1940` | 0x1c | `clear__Q311CFieldModel7_member6_flagsFv` |
| `0x004c1960` | 0x1c | `clear__Q311CFieldModel7_member8_evflagsFv` |
| `0x004c4020` | 0x120 | `InterPolPitch(float, float, float)` |
| `0x004c4e10` | 0x19c | `GetSmoothVelocity(float, float, float, float, float)` |
| `0x004c6bf0` | 0x180 | `ClipRadian(float)` |
| `0x004c6fa0` | 0xb8 | `GetRotAngle(int)` |
| `0x004c7e40` | 0xcc | `checkKind(const char*)` |
| `0x004ca4f0` | 0x3c | `GetRand(int)` |
| `0x004ca530` | 0x2a8 | `CalcModelBBox(Model*, float*)` |
| `0x004cc820` | 0x1c | `clear__Q28CBalIcon6_flagsFv` |
| `0x004cdcc0` | 0x1b4 | `CnvY(unsigned int)` |
| `0x004cde80` | 0xfc | `CnvModelGray(Model*)` |
| `0x004cf0f0` | 0xa8 | `CreateFldBGEffect(int, void*)` |
| `0x004d0560` | 0x144 | `GetColVector(FVector*, unsigned int)` |
| `0x004d36b0` | 0x40 | `HalfCol(unsigned int)` |
| `0x004d4130` | 0x84 | `GetRotMatrix(Matrix&, int)` |
| `0x004d5600` | 0x3c | `GetBgmFileName(char*, const char*)` |
| `0x004d5640` | 0x3c | `GetSeFileName(char*, const char*)` |
| `0x004d5680` | 0x28 | `cbReadBGM(int, BufMemory*, int, char*, void*)` |
| `0x004d5730` | 0x88 | `GetObjSeSize(SDB::tagFOBJSE*)` |
| `0x004d60e0` | 0x500 | `Exp3DVolume(FVector, FVector, FVector, int&, int&, int)` |
| `0x004d65e0` | 0xc70 | `Calc3DPosition(FVector*, FVector*, _ObjSE*)` |
| `0x004d7250` | 0x130 | `Exp3DVolumeC(FVector&, FVector&, FVector&, float)` |
| `0x004da260` | 0x2c | `cbReplace(Effect*, void*, int)` |
| `0x004daec0` | 0xec | `CheckMirrorNormal(FVector&)` |

Decompiled source: `decomp/G/FieldFree.c`.
