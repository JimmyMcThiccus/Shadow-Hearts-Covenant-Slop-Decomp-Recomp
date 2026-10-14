# PKFINFO.TBL / *.PKB archive format (decoded, verified on Furokuban disc)

Reader: `port/crates/sh2_core/src/fileio.rs`; `cargo run -p sh2_core --example pkb_list` (set `SH2_DISC_DIR`). Test `real_disc_archives_are_exact` passes: for each of the 11 archives `max(offset+size) == sizeof(PKB)`; 1734 files + 41 directory entries = 1775 table entries.

## Files
`\PKFINFO.TBL;1` on the disc root (28,416 B JP). Archives (plain concatenation, no per-file header, files 16-byte aligned, directories/files in practice 2048-aligned): BTLDATA, COMMON, EFFECT, MENU, FIELD, OPENING, SAVELOAD, WORLDMAP, SHOP, SOLOMON, LSD (`.PKB`). `FIELD.BIN` / `BATTLE.BIN` are plain disc files that also appear in the table (root, size only).

## Table
```
u16 count(1775) u16 entsize(0x10) u32 total_bytes(count*16) u8 pad[8]   ; header 0x10
PkbEntry[count] { u8 key[8]; u32 off16; u32 size_or_dir; }
```
* `off16`: offset in **16-byte units** from the parent list/archive start. Root entries store 0 in the file; `FileIOLib::InitPkb` overwrites it with the disc LBA of `\NAME.PKB;1` (dirs) or `\NAME;1` (plain files) using `sceCdLayerSearchFile` (strings `\`, `;1`, `.PKB;1` at 0x3fd940..).
* `size_or_dir`: bit31 clear = file size in bytes. bit31 set = directory; `low31/16` = distance (in entries) from the **start of the list containing the directory entry** to the first entry of its child list.
* Lists are stored depth-first (root list = idx 0..12: FIELD.BIN, BATTLE.BIN, then BTLDATA, COMMON, EFFECT, MENU, FIELD, OPENING, SAVELOAD, WORLDMAP, SHOP, SOLOMON, LSD; then BTLDATA's list 13.., its first subdir SOUND's list, ...). A child list's length is not stored; `searchInfo` scans from the list start to the end of the table (root: only up to `Dircount` = 13).
* File byte offset in archive = sum of `off16*16` over the path below the archive. Start LBA = `lba(PKB) + sum(off16 >> 7)` (`SearchFile` writes `_CDVDRINFO+0x10 = LBA`, `+0x18 = size`, `+0x14 = sum(off16)` unused).

## Name hash (`enCode`/`deCode`, JP 0x22cfb0/0x22ca90, US 0x22a5f0/0x229f60) -- reversible, no loss for <=12 chars
Alphabet (JP 0x3fda00): digit 0 = padding, 1 = `.`, 2..11 = `0..9`, 12..37 = `A..Z`, 38 = `_`. Name upper-cased, chars outside the alphabet skipped, first 12 chars.
For group g (4 digits a0..a3): `u_g = a0 + 40*a1 + 1600*a2 + 64000*a3` (22 bits). `hi_g = u_g>>16`, `lo_g = u_g & 0xffff`. Key = big-endian u16 `[hi0 + 40*hi1 + 1600*hi2, lo0, lo1, lo2]`.
Example `FIELD.BIN` -> `03 0e dd 31 d9 77 00 19`. Round trip verified on all 1775 entries.

## Path resolution (`SearchFile`, JP 0x22c7a0)
Split at `/` (leading `/` skipped), each component encoded and searched starting at the current list start; on a directory hit `list_start += low31/16`. Language variants: `SSHSys::GetFullPathName` tries the path, then `AddLocalPath` inserts `JPN/ USA/ GBR/ FRA/ GER/ ITA/ SPA/` before the file name.

## Archive contents (JP demo)
BTLDATA 259 (SOUND/BGM,SE,SYSTEM, BBG, AIS, CHR, WPN, BTL_00x.BIN), COMMON 14 (CMNEFF.DAT CMNMENU.DAT JRING.BIN SH2.ICO SPEC.TEX SSHDAT.JPN SSHMES.JPN SVP.BIN SYSREG.SSE WPA/WPC/WPF/WPJ/WPN.BIN), EFFECT 261 (*.EFD), MENU 581 (DAT, FACE, IMG/{AC,AM,AR,GO,HE,IT,KE,RI,SE,TA,WE}, MSD), FIELD 599 (EFF, IMG, MODEL, MPS, SOUND/{BGM,SE}), OPENING 3 (BGM803.SSV, DEMO.LSD 83 MB, OPENING.DAT), SAVELOAD 1, WORLDMAP 5, SHOP 2 (SHOP.DAT, TAILOR.DAT), SOLOMON 2 (COMP.DAT, SOLOMON.DAT), LSD 5 (N003..N007.LSD).

## IOP side
`FileIOLib` is an EE client of the custom IOP module `FIO.IRX` (SifCmd name "FIOIRX"). Commands: 1 open, 2 read, 3 close, 0x27 write, 0x1c re-open on error, replies 0x16 init, 0x17/0x18 done, 0x1b close done, 0x21/0x23/0x28/0x29/0x2c DMA bookkeeping (EE `DMASend` copies 0x19000-byte chunks with `sceSifSetDma`). FIOHND (0xc0): `+0 path[0x70], +0x70 device[0x14], +0x84 LBA, +0x88 mode(1 cdrom,4 pfs), +0x8c open flags, +0x90 size, +0x94 transferred, +0x98 open time, +0x9c req len, +0xa4 BufMemory*, +0xa8 queue next, +0xac status (0 idle,1 open req,2 read req,3 close req,0x27 write,0x2c dma,0xf001 busy,0xf002 inflight,0xf003 error,0xffff free), +0xb0 dst, +0xb4 self, +0xb8 layer`. 100 handles at 0x414ca0.
