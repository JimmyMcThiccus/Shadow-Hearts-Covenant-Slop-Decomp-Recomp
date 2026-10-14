# FileIOLib (JP 0x22a910..0x22df18; US 0x228450..0x22b3a0)

Ghidra struct `FileIOLib` (0x13ae8 JP; US 0x13ac8: the US struct is 0x20 smaller and `+0x13a5c` is the device string -- offsets after the entry table shift by -4/-0x20).

| off | meaning |
|---|---|
| 0x00 | CPolObj (vtbl 0x404a00 `{+8 __dt, +0xc Polling}`) |
| 0x18 | CThread (prio 1/2? `CreateThread(1,2,0x10000)`), `Run` loops `Wait(5ms); Polling(); poller.Polling()` while `+0x13920` |
| 0x60 | PKFINFO header copy: u16 count, u16 entsize@0x62, u32 bytes@0x64 |
| 0x70 | PkbEntry[5000] |
| 0x13918 | SifCmd handle (CheckID "FIOIRX"), 0x1391c recv cmd id (handler `Command_Process`) |
| 0x13920 | run flag; 0x13928 inhibit; 0x13934 diskState (2 = swap pending, 1 = verifying); 0x13938 diskResult (-1 wrong disc); 0x1393c disc no; 0x13940 layer (-1 unknown); 0x13944 volume label[0x15] ("DEFAULT") |
| 0x1395c | CPoller (runs DvdromOrder + other IO objects on the IO thread) |
| 0x13968/0x13984 | two semaphores (0x13980 CdSync, 0x1399c queue lock) |
| 0x13a7c | device name; 0x13ae0 u64 entry count |

`InitPkb` (0x7dc): checks disc ready, verifies volume label (sector 0x10) for disc swaps, `sceCdLayerSearchFile("\PKFINFO.TBL;1")`, reads it into a 0x80-aligned BufMemory, copies header+entries (<5000), then resolves every root entry's LBA. `Initialize`: Sif init, CheckID("FIOIRX"), `sceSifAddCmdHandler`, create 2 semaphores, `fioCmdCall(0x16)` init, mark 100 handles free, `sceCdDiskReady`, `InitPkb`.
`open(path, flags)` -> getFileHand (first of 100 with status 0xffff), `makeHandler` (mode 1: `SearchFile` -> LBA/size), status 0xf001, `fioCmdCall(1, 0xc0)`; `read(h, buf?, len)` allocates `BufMemory(len, 0x80)` when `buf==0`, status 2, queued on `DAT_00414c88`; `Polling` pops the queue one at a time (myFp) and sends the command. `ResetSystem` clears run flag and waits for `myFp==0`. US `ResetSystem` additionally powers off HDD (devctl 0x5003).
Globals: ourFio 0x40abd4, myFp 0x40abd8, useHDDDrive 0x40abdc, state 0x40abe4, Dircount, FileHand[100] 0x414ca0, Root 0x414be0.
