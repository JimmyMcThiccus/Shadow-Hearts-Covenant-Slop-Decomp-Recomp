# Overlay / MWo3 / DvdromOrder / BufMemory / RingBuffer

## MWo3 header (decoded from FIELD.BIN, BATTLE.BIN JP + FIELD/BATTLE/OPENING US; code starts +0x80)
```
+0x00 "MWo3"  +0x04 u32 group (1 FIELD, 2 BATTLE, 3 OPENING[US])  +0x08 u32 load addr (JP 0x430a00, US 0x45ea80)
+0x0c u32 text size  +0x10 u32 data size (text+data ~ file size - 0x40)  +0x14 u32 bss bytes zeroed after the image
+0x18 u32 ctor_begin  +0x1c u32 ctor_end  (absolute, point into the image tail: BATTLE JP 0x656fa0..0x656fb4 = 5 ctors; FIELD JP empty)
+0x20 char name[16]
```
`mwOverlayInit(addr, loaded)` (JP 0x384c60, US 0x3c58b0): `FlushCache(2); memset(addr+loaded, 0, hdr.bss); __initialize_cpp_rts(ctor_begin, ctor_end)` which calls each function pointer (US 0x3c57f0). Load address array: `mwGetGroupAddress(i) = (&__exception_table_end__)[i]` (JP 0x23d430, US 0x239d70).
The `Overlay` object (0x40, embedded in SSHSys+0x68): `+0 group, +4 addr, +8 cb(phase 0 load/1 unload, ok, a0, a1), +0xc a0, +0x10 a1, +0x18 BufMemory view of the load address, +0x28 loaded size, +0x2c BufMemory* prebuffer, +0x30 preState(0/1 loading/2 done), +0x34 preSize, +0x38 loadPending, +0x3c vtbl`.
`Load(path, cb, a0, a1)`: if buffer already set returns 2; else sets buffer = group address, and: preState 2 -> copy from prebuffer + `cbOverlayLoad` (returns 3); preState 1 -> loadPending (0); else `ReadOrder(path, cbOverlayLoad, 0, &buf, this)` (0). `cbOverlayLoad` -> `InitCashe(size)` -> `mwOverlayInit` + user cb(0,1). `PreLoad` reads into a scratch BufMemory early (`cbOverlayPreLoad` -> `PreloadDone`).
Callers: `CFieldSocket::PreloadOverlay/fieldOverlay` ("FIELD.BIN"), BtlSocket ("BATTLE.BIN"), US CDMYStage::preLoad ("OPENING.BIN").

## DvdromOrder (0x14c, global `Dvdromour` 0x40abf8) -- see port dvdrom_order.rs
`ReadOrder(path, cb, tag, [BufMemory*], user, flags)`: ring of 100 packets (`OrderPackets` 0x4197d0, 0x12c each), FIFO. cb `int(int tag, BufMemory*, int size, char* path, void* user)`: 1 = free buffer, 0 = kept, else retry. `deleteOrder(id)` cancels.

## BufMemory (0x10) `{u8* alloc; u8* buf; u64 size}`; `NowByte` 0x40abf0 accounting; `SetBuffer(size, ptr)` creates a non-owning view.
## RingBuffer (0x2c): `{rd, base, cap, wr, used, BufMemory*, trackSectors, sectorTbl[1000]x12B, sectorCnt, -, vtbl}`; used by LSD streaming handlers (`Open/Read(.., RingBuffer*)`).
