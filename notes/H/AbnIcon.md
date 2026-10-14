# AbnIcon

Status-ailment icons above characters. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00500970 | 00523350 | 0x360 | `AbnIcon::__ct(int, int)` |
| 00500cd0 | 005236b0 | 0x160 | `AbnIcon::__dt()` |
| 00500e30 | 00523810 | 0xd0 | `AbnIcon::Destruct()` |
| 00500f00 | 005238e0 | 0x2d0 | `AbnIcon::Polling()` |
| 005011d0 | 00523b90 | 0xe00 | `AbnIcon::MakePacket()` |
| 0054b2b0 | 0057df50 | 0x10 | `AbnIcon::EndSet()` |
| 0054b4c0 |  | 0x10 | `@24@__dt__7AbnIconFv` |
| 0054b4d0 |  | 0x10 | `@44@__dt__7AbnIconFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 3 | __ct__7AbnIconFii, __dt__7AbnIconFv |
| +0x18 | u32/int | 3 | __ct__7AbnIconFii, __dt__7AbnIconFv |
| +0x1c | u32/int | 3 | __ct__7AbnIconFii, __dt__7AbnIconFv |
| +0x28 | u32 | 3 | __ct__7AbnIconFii, __dt__7AbnIconFv |
| +0x34 | u32/int | 6 | Destruct, Polling, __ct__7AbnIconFii, __dt__7AbnIconFv |
| +0x40 | byte/u32 | 14 | Destruct, MakePacket, Polling, __ct__7AbnIconFii |
| +0x44 | u32 | 1 | __ct__7AbnIconFii |
| +0x48 | int/u32 | 27 | Destruct, MakePacket, Polling, __ct__7AbnIconFii |
| +0x4c | u32 | 1 | __ct__7AbnIconFii |
| +0x54 | u32 | 1 | __ct__7AbnIconFii |
| +0x5c | u32/int | 6 | MakePacket, Polling, __ct__7AbnIconFii |
| +0x60 | u32 | 1 | __ct__7AbnIconFii |
| +0x64 | u32 | 1 | __ct__7AbnIconFii |
| +0x68 | float/u32 | 11 | MakePacket, Polling, __ct__7AbnIconFii |
| +0x6c | u16/short | 3 | MakePacket, __ct__7AbnIconFii |
| +0x6e | u16/short | 4 | MakePacket, __ct__7AbnIconFii |
| +0x70 | float/u32 | 8 | MakePacket, __ct__7AbnIconFii |
| +0x74 | float/u32 | 8 | MakePacket, Polling, __ct__7AbnIconFii |
