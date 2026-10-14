# BCursole

Menu cursor sprite (spelling 'Cursole' is original). Owned by `BtlMenu`; follows the selected row of a `BMesWin`.


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 005d7ad0 | 00622350 | 0x1d0 | `BCursole::__ct(int, int, uchar, uchar, uchar, uchar, uchar, FVector *)` |
| 005d7ca0 | 00622520 | 0x110 | `BCursole::__dt()` |
| 005d7db0 | 00622630 | 0xd0 | `BCursole::Destruct()` |
| 005d7e80 | 00622700 | 0xd70 | `BCursole::Polling()` |
| 005d8c10 |  | 0x10 | `@32@Polling__8BCursoleFv` |
| 005d8c20 |  | 0x10 | `@32@__dt__8BCursoleFv` |
| 005d8c30 |  | 0x10 | `@56@__dt__8BCursoleFv` |
| 005d8c40 |  | 0x10 | `@12@Polling__8BCursoleFv` |
| 005d8c50 |  | 0x10 | `@12@__dt__8BCursoleFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x7 | byte | 1 | @56@ |
| +0x8 | u32/int | 3 | Destruct, __dt__8BCursoleFv |
| +0x10 | u32 | 1 | @12@ |
| +0x14 | u32 | 1 | @32@ |
| +0x15 | byte/u16 | 3 | __ct__8BCursoleFiiUcUcUcUcUcP7FVector |
| +0x18 | u32 | 1 | @32@ |
| +0x1c | u32 | 1 | __dt__8BCursoleFv |
| +0x28 | u32 | 1 | @12@ |
| +0x2c | u32 | 1 | @12@ |
| +0x34 | byte/u32 | 3 | @32@, @32@Polling, __dt__8BCursoleFv |
| +0x38 | u32 | 1 | __dt__8BCursoleFv |
| +0x48 | byte | 2 | @12@, @12@Polling |
| +0x54 | byte | 5 | Destruct, Polling, __dt__8BCursoleFv |
| +0x55 | u8 | 1 | __ct__8BCursoleFiiUcUcUcUcUcP7FVector |
| +0x56 | u8 | 1 | __ct__8BCursoleFiiUcUcUcUcUcP7FVector |
