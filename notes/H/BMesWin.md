# BMesWin

Message/menu window object (0x138 bytes). Linked list node: `+0x28` next, `+0x2c` id. Created by `BtlMenu::MakeMesWin`; draws the frame via `BtlWin`, text via the main-exe text printer.


## Methods (7)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 005d6a10 | 0061fe40 | 0x120 | `BMesWin::__ct(int, int, int, char *, int)` |
| 005d6b30 |  | 0x1a0 | `BMesWin::__dt()` |
| 005d6cd0 |  | 0xe0 | `BMesWin::Destruct()` |
| 005d6db0 |  | 0x370 | `BMesWin::Polling()` |
| 005d7120 |  | 0x950 | `BMesWin::Create(int, int, char *, int)` |
| 005d7a70 | 006222f0 | 0x60 | `BMesWin::SetClose()` |
| 005d8c00 |  | 0x10 | `@24@__dt__7BMesWinFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @24@ |
| +0x14 | u32 | 3 | @24@, __ct__7BMesWinFiiiPci, __dt__7BMesWinFv |
| +0x18 | byte/u32/ushort | 4 | @24@, __ct__7BMesWinFiiiPci |
| +0x1c | u32 | 1 | __ct__7BMesWinFiiiPci |
| +0x20 | u32/int | 6 | Destruct, Polling, __ct__7BMesWinFiiiPci, __dt__7BMesWinFv |
| +0x2c | u32 | 2 | __ct__7BMesWinFiiiPci, __dt__7BMesWinFv |
| +0x30 | byte/ushort/u16 | 25 | Create, Destruct, Polling, __ct__7BMesWinFiiiPci, __dt__7BMesWinFv |
| +0x32 | u16/short | 6 | Create, Polling, SetClose, __ct__7BMesWinFiiiPci |
| +0x34 | u16 | 4 | Create, Polling, SetClose, __ct__7BMesWinFiiiPci |
| +0x36 | u16 | 1 | Create |
| +0x38 | float/u32 | 8 | Create, Polling |
| +0x3c | short/u16 | 2 | Create, Polling |
| +0x3e | u16/short | 3 | Create |
| +0x94 | u16 | 1 | Create |
| +0xbc | int | 3 | Create |
| +0x11c | u32 | 1 | @24@ |
| +0x128 | char | 2 | Polling |
| +0x134 | u32/int | 5 | Create, __ct__7BMesWinFiiiPci, __dt__7BMesWinFv |
