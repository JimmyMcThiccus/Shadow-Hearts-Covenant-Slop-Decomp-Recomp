# BtlBG

Battle background manager (`SetBtlBG(id)` from `BtlSocket`, `BtlBGSequence` per frame). Loads the BG model/texture set from BTLDATA.PKB.


## Methods (12)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0055b3b0 | 0058f550 | 0x100 | `BtlBG::__ct(int, int)` |
| 0055b4b0 | 0058f650 | 0xa0 | `BtlBG::__dt()` |
| 0055b550 | 0058f6f0 | 0x90 | `BtlBG::DeleteSetUp()` |
| 0055b5e0 | 0058f780 | 0x30 | `BtlBG::TranseCallBack(FVector *, FVector)` |
| 0055b610 | 0058f7b0 | 0x50 | `BtlBG::EventCallBack(char *, char *, int, int, uint)` |
| 0055b660 | 0058f800 | 0x10 | `BtlBG::MotionEndCallBack(char *)` |
| 0055b670 | 0058f810 | 0x590 | `BtlBG::BtlBGInit(uchar *)` |
| 0055bc00 | 0058fdb0 | 0xe0 | `BtlBG::OTEntry(int, int)` |
| 0055bce0 | 0058fe90 | 0xf0 | `BtlBG::OTRelease()` |
| 0055bdd0 | 0058ff80 | 0x1c70 | `BtlBG::SetAlpha(int, uchar, bool)` |
| 0055da40 | 00591bf0 | 0x190 | `BtlBG::SetBtlBGEffectAlpha(int, int, float)` |
| 0055dbd0 |  | 0x10 | `@20@__dt__5BtlBGFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 1 | @20@ |
| +0x10 | int/u32 | 20 | SetAlpha, __ct__5BtlBGFii, __dt__5BtlBGFv |
| +0x1c | u32 | 2 | __ct__5BtlBGFii, __dt__5BtlBGFv |
| +0x48 | int | 62 | SetAlpha |
| +0x5c | int | 1 | SetAlpha |
| +0x4b0 | byte/u32 | 9 | DeleteSetUp, OTEntry, OTRelease, __ct__5BtlBGFii |
| +0x4b4 | u16 | 1 | __ct__5BtlBGFii |
| +0x4b6 | u16/short | 2 | SetAlpha, __ct__5BtlBGFii |
| +0x752 | short | 4 | OTEntry, OTRelease |
| +0x760 | u32 | 1 | __ct__5BtlBGFii |
| +0x764 | u32 | 1 | __ct__5BtlBGFii |
