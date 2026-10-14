# BtlMenu

Command UI. Mostly static (`uGpffff86ec/86e8` hold the callback + user pointer; `iGpffff86f0` is the linked list of live `BMesWin` windows).
Menu builders: `SetMainMenu` (0x005adc70, 54 KB), `SetTargetMenu`, `SetMagicMenu`, `SetItemMenu`, `SetSkill1Menu`, `SetComboSkillMenu`, `SetBaseAromaMenu/SetAddAromaMenu`,
`SetComboShortCutMenu`, `SetFusionMenu`, `SetGuardMenu`, `SetMoveMenu`, `SetTutorialMenu`. Each constructs `BMesWin` windows + one `BCursole` and reports through the callback
(codes 0-23, table in `battle_flow.md` section 3, reproduced in Rust as `flow::MenuEvent`). `MakeMesWin(x,y,text,w)` picks the first free window id by walking the list and `new BMesWin(0x138)`.
Menu item labels (27) are `flow::MenuItem`.


## Methods (50)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0058bba0 | 005cf620 | 0x30 | `BtlMenu::SetCallBack(void *, void *)` |
| 0058bbd0 | 005cf650 | 0x100 | `BtlMenu::MakeMesWin(int, int, char *, int)` |
| 0058bcd0 | 005cf750 | 0x70 | `BtlMenu::BMesWinEntry(BMesWin *)` |
| 0058bd40 | 005cf7c0 | 0xb0 | `BtlMenu::BMesWinRelease(BMesWin *)` |
| 0058bdf0 | 005cf870 | 0x60 | `BtlMenu::AllMesWinDestruct()` |
| 0058be50 | 005cf8d0 | 0x60 | `BtlMenu::FindMesWin(int)` |
| 0058beb0 | 005cf930 | 0x50 | `BtlMenu::SetMesWinClose(int)` |
| 0058bf00 | 005cf980 | 0x250 | `BtlMenu::MakeCursole(int, uchar, uchar, uchar, uchar, uchar, FVector *, int)` |
| 0058c150 | 005cfbd0 | 0x70 | `BtlMenu::BCurEntry(BCursole *)` |
| 0058c1c0 | 005cfc40 | 0xb0 | `BtlMenu::BCurRelease(BCursole *)` |
| 0058c270 | 005cfcf0 | 0x60 | `BtlMenu::AllBCurDestruct()` |
| 0058c2d0 | 005cfd50 | 0x60 | `BtlMenu::FindBCursole(int)` |
| 0058c330 | 005cfdb0 | 0x3f0 | `BtlMenu::__ct(int, bool)` |
| 0058c7e0 | 005d02d0 | 0x4a0 | `BtlMenu::__dt()` |
| 0058cc80 | 005d0860 | 0x380 | `BtlMenu::Destruct()` |
| 0058d000 |  | 0x15020 | `BtlMenu::Polling()` |
| 005a2020 |  | 0x3570 | `BtlMenu::MainMenuFunc()` |
| 005a5590 | 005e7130 | 0x350 | `BtlMenu::DelaySelectFunc(int, int, int, EFCTCOMParam *)` |
| 005a58e0 | 005e7480 | 0xb70 | `BtlMenu::SelectFunc(int, int, int, EFCTCOMParam *)` |
| 005a6450 | 005e8080 | 0x280 | `BtlMenu::AllWindowClose()` |
| 005a66d0 |  | 0x4700 | `BtlMenu::WinSequence()` |
| 005aadd0 | 005edf00 | 0x90 | `BtlMenu::SetMode(int, bool)` |
| 005aae60 | 005edf90 | 0x180 | `BtlMenu::IsReady()` |
| 005aafe0 | 005ee140 | 0x2d0 | `BtlMenu::AutoMenuFunc(int, int, int, int, int)` |
| 005ab2b0 |  | 0xa50 | `BtlMenu::SetWindowMove(int, int)` |
| 005abd00 | 005ef260 | 0x230 | `BtlMenu::SetWindowClose(int, int)` |
| 005abf30 | 005ef530 | 0x2e0 | `BtlMenu::SetNoteWindow(char *)` |
| 005ac210 | 005ef7f0 | 0x90 | `BtlMenu::SetNoteWindowClose()` |
| 005ac2a0 | 005ef880 | 0x170 | `BtlMenu::CreateCursole()` |
| 005ac410 | 005ef9f0 | 0x590 | `BtlMenu::SetNextComboChrTitle(int)` |
| 005ac9a0 | 005f00a0 | 0x240 | `BtlMenu::SetNextComboChrMenu(int, int)` |
| 005acbe0 |  | 0xf00 | `BtlMenu::SetTargetMenu(int, int, int, EFCTCOMParam *, int, int)` |
| 005adae0 | 005f1f30 | 0x190 | `BtlMenu::SetDamageTypeMenu(int, int, int)` |
| 005adc70 |  | 0xd470 | `BtlMenu::SetMainMenu(int, int, int, int)` |
| 005bb180 | 00602510 | 0xcf0 | `BtlMenu::SetMagicMenu(int, int, int)` |
| 005bbe70 | 00603210 | 0x430 | `BtlMenu::SetItemMenu(int, int, int)` |
| 005bc2a0 | 00603640 | 0xe0 | `BtlMenu::SetGuardMenu(int, int)` |
| 005bc380 | 00603720 | 0x4b0 | `BtlMenu::SetMoveMenu(int, int, int)` |
| 005bc830 | 00603bd0 | 0xe0 | `BtlMenu::SetMoveAfterMenu(int, int)` |
| 005bc910 | 00603cb0 | 0x5b0 | `BtlMenu::SetFusionMenu(int, int, int)` |
| 005bcec0 |  | 0x8a0 | `BtlMenu::SetSkill1Menu(int, int, int)` |
| 005bd760 | 006051d0 | 0x270 | `BtlMenu::SetComboSkillMenu(int, int, int)` |
| 005bd9d0 | 00605450 | 0x260 | `BtlMenu::SetBaseAromaMenu(int, int, int)` |
| 005bdc30 | 006056c0 | 0x2b0 | `BtlMenu::SetAddAromaMenu(int, int, int)` |
| 005bdee0 |  | 0x9d20 | `BtlMenu::SetComboShortCutMenu(int, int, int)` |
| 005c7c00 |  | 0x7620 | `BtlMenu::SetComboShortCutSettingMenu(int, int, int)` |
| 005cf220 |  | 0x24f0 | `BtlMenu::SetTutorialMenu(int, int)` |
| 005d1710 |  | 0x2700 | `BtlMenu::CreateMenu1(int, int, int, int, short *, char *, char *, bool, bool)` |
| 005d3e10 |  | 0x2c00 | `BtlMenu::CreateMenu2(int, int, int, int, short *, char *, short *, char *, bool, bool)` |
| 005d8bf0 |  | 0x10 | `@24@__dt__7BtlMenuFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @24@ |
| +0xc | byte | 2 | @24@ |
| +0xd | byte | 1 | @24@ |
| +0x14 | u32 | 2 | __ct__7BtlMenuFib, __dt__7BtlMenuFv |
| +0x18 | u32 | 1 | __ct__7BtlMenuFib |
| +0x1c | u32 | 1 | __ct__7BtlMenuFib |
| +0x20 | u32/int | 5 | Destruct, __ct__7BtlMenuFib, __dt__7BtlMenuFv |
| +0x24 | byte/u32/int | 60 | BMesWinEntry, BMesWinRelease, CreateCursole, Destruct, MainMenuFunc, SetMode… |
| +0x25 | byte | 64 | CreateMenu1, Destruct, MainMenuFunc, SetNoteWindow, WinSequence, __dt__7BtlMenuFv |
| +0x28 | u16/u32/int | 24 | BMesWinEntry, BMesWinRelease, MainMenuFunc, SetMode, __ct__7BtlMenuFib |
| +0x2a | u16/short | 21 | MainMenuFunc, SetMode, __ct__7BtlMenuFib |
| +0x32 | short | 5 | MainMenuFunc, WinSequence |
| +0x48 | u32/int | 8 | BCurEntry, BCurRelease |
| +0x4c | u32/int | 6 | BCurEntry, BCurRelease |
| +0x130 | int | 3 | MainMenuFunc |
| +0x140 | u32/int | 31 | MainMenuFunc |
| +0x150 | u32 | 2 | WinSequence |
| +0x154 | u32 | 2 | WinSequence |
| +0x158 | int | 5 | MainMenuFunc |
| +0x164 | u32 | 2 | MainMenuFunc |
| +0x168 | int/u32 | 8 | MainMenuFunc |
| +0x16c | int/u32 | 20 | MainMenuFunc |
| +0x170 | int | 7 | MainMenuFunc |
| +0x174 | int/u32 | 9 | MainMenuFunc |
| +0x74e | short | 5 | MainMenuFunc |
| +0x8b8 | short/u16 | 15 | AllWindowClose, IsReady, SetNoteWindow, SetNoteWindowClose, WinSequence, __ct__7BtlMenuFib |
| +0x8ba | u16/short | 9 | AllWindowClose, SetNoteWindow, SetNoteWindowClose, WinSequence, __ct__7BtlMenuFib |
| +0x8d0 | u16 | 1 | SetNoteWindow |
| +0x910 | u16 | 1 | SetNoteWindow |
| +0x938 | int | 3 | SetNoteWindow |
| +0x9a4 | char | 2 | WinSequence |
| +0x9b8 | int | 1 | SetNoteWindow |
| +0x9cc | u16 | 1 | SetNoteWindow |
| +0x9ce | u16 | 1 | SetNoteWindow |
| +0xa0a | u8 | 1 | SetNoteWindow |
| +0xa0b | u8 | 1 | SetNoteWindow |
| +0xa30 | u16/short | 7 | AllWindowClose, CreateCursole, IsReady, WinSequence, __ct__7BtlMenuFib |
| +0xa32 | u16/short | 13 | AllWindowClose, CreateMenu1, SetTutorialMenu, WinSequence, __ct__7BtlMenuFib |
| +0xa46 | byte | 2 | CreateCursole |
| +0xa48 | u16 | 1 | CreateCursole |
| +0xae4 | byte | 2 | CreateCursole |
| +0xae5 | byte/char | 2 | CreateCursole |
| +0xae6 | ushort | 2 | CreateCursole |
| +0xb18 | int | 2 | @24@ |
| +0xb20 | int | 20 | MainMenuFunc, SetWindowMove |
| +0xb30 | u32/int | 21 | CreateMenu1, Destruct, WinSequence, __ct__7BtlMenuFib, __dt__7BtlMenuFv |
| +0xb34 | u32/uint | 4 | SetMode, SetNextComboChrMenu, __ct__7BtlMenuFib |
| +0xb38 | int/u32 | 5 | Destruct, __ct__7BtlMenuFib |
| +0xb3c | int/u32 | 9 | AllWindowClose, Destruct, __ct__7BtlMenuFib |
| +0xb40 | ushort | 2 | MainMenuFunc |
| +0xb42 | char | 2 | MainMenuFunc |
| +0xb43 | char/u8 | 14 | MainMenuFunc |
| +0xb44 | u16/short | 24 | MainMenuFunc, __ct__7BtlMenuFib |
| +0xb46 | u16/short | 36 | MainMenuFunc, WinSequence, __ct__7BtlMenuFib |
| +0xb48 | u32/float | 55 | MainMenuFunc |
| +0xb4c | u16 | 1 | MainMenuFunc |
| +0xb4e | u16 | 1 | MainMenuFunc |
| +0xb50 | u16 | 1 | MainMenuFunc |
| +0xb52 | u16 | 1 | MainMenuFunc |
| +0xb54 | u8 | 1 | MainMenuFunc |
| +0xb55 | u8 | 4 | MainMenuFunc |
| +0xb56 | u16 | 1 | MainMenuFunc |
| +0xb58 | short/u16 | 25 | MainMenuFunc, __ct__7BtlMenuFib |
| +0xb5a | u16 | 13 | MainMenuFunc, __ct__7BtlMenuFib |
| +0xb5c | u16 | 13 | MainMenuFunc, __ct__7BtlMenuFib |
| +0xb5e | u16 | 13 | MainMenuFunc, __ct__7BtlMenuFib |
