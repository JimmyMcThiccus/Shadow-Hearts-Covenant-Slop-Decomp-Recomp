# dispSaveFile

One slot panel on the save list (3 visible): shows leader name, level, play time (`dispTime`), cash (`dispCash`), location, party faces (model numbers -> `FI_%03d` portraits); `setMove/move` animate the list scroll.

## Constructed by

`Polling__10dataAccessFv`, `mSetFileViewScroll__10dataAccessFi`, `mSetupSelectFile__10dataAccessFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003a4650 | 0xa4 | `__ct__12dispSaveFileFiiiQ210dataAccess10ACCESSMODEP7primTexPPc` | `dispSaveFile::dispSaveFile(int, int, int, dataAccess::ACCESSMODE, primTex*, char**)` |
| 0x003a4700 | 0xf0 | `__dt__12dispSaveFileFv` | `dispSaveFile::~dispSaveFile()` |
| 0x003a47f0 | 0xb0c | `mSetupDispFile__12dispSaveFileFv` | `dispSaveFile::mSetupDispFile()` |
| 0x003a5300 | 0x3d4 | `setMove__12dispSaveFileFi` | `dispSaveFile::setMove(int)` |
| 0x003a56e0 | 0x164 | `move__12dispSaveFileFiii` | `dispSaveFile::move(int, int, int)` |
| 0x003a5850 | 0x154 | `setDisp__12dispSaveFileFb` | `dispSaveFile::setDisp(bool)` |

## Open questions

- none recorded

Decompilation: `decomp/F/dispSaveFile.c`
