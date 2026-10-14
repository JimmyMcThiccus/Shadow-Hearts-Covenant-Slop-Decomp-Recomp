# `.MSD` / `.MDT` menu scene files and the MENU.PKB directory (decoded)

## PKFINFO.TBL / PKB directory

`PKFINFO.TBL` (28,416 bytes JP demo): 0x10 byte header `{u32 0x1006ef, u32 table_bytes=0x6ef0, 0, 0}` followed by
1775 sixteen-byte entries `{u8 name[8], u32 offset16, u32 size_or_dir}`.

* `name` is an 8-byte packed identifier of one path component (<= 12 chars of `.0-9A-Z_`, 38-symbol alphabet, four
  characters per 16-bit-pair group, see `msd::pkf::{encode_name,decode_name}` = `FileIOLib::enCode/deCode`,
  0x0022cfb0 / 0x0022ca90). Upper-case only.
* Directory entries have bit31 set in `size_or_dir`; the low 31 bits are the byte offset (multiple of 16) of the
  child block **relative to the first index of the block that contains the directory entry**
  (`child_start = block_start + (v & 0x7fffffff)/16`; the root block starts at 0). A file entry's `size_or_dir` is its
  size in bytes. The block's end is implicit (the next sibling directory's start).
* `offset16` is the position in 16 byte units relative to the enclosing directory's base. A file's byte position
  inside its `.PKB` is `16 * sum(offset16 along the path)`. The root entries (`FIELD.BIN`, `BATTLE.BIN`, `BTLDATA`,
  `COMMON`, `EFFECT`, `MENU`, `FIELD`, `OPENING`, `SAVELOAD`, `WORLDMAP`, `SHOP`, `SOLOMON`, `LSD`) have offset 0
  and become the disc LBA of `<name>.PKB` at boot (`FileIOLib::InitPkb`, `sceCdLayerSearchFile`); `FIELD.BIN`/
  `BATTLE.BIN` are plain files (size in the second word).

`DiscDir` (`sh2_menu::disc`) implements this and reads `MENU/MSD/GAMEOVER.MSD` byte-exactly (test
`gameover_msd_from_disc`, set `SH2_DISC_DIR`).

### MENU.PKB (30,263,072 bytes)

| dir | entries | content |
|---|---|---|
| `MENU/DAT` | 24 | `000.MMD 001.MTD 002.MTD 077.MMD ... 099.MMD` (menu 3D models/textures), `CH_000.MED`, `LVUP_000..006.MED` (effect/motion data), `CMDMENU.MSD` (360 KB, 12 attach blobs), `MFIELD.MSD` (921 KB), `SAVELIST.MDT` (location name table) |
| `MENU/FACE` | 78 | `FI_000..FI_056.TEX` ... face portraits (0x3810 bytes each; texture format not yet decoded -- section B) |
| `MENU/IMG` | 11 subdirs, 456 TEX | `AC` 78 (actions/abilities), `AM` 43, `AR` 8, `GO` 1 (game over), `HE` 1 (help), `IT` 43 (items), `KE` 115 (key items), `RI` 55 (ring), `SE` 9, `TA` 23, `WE` 80 (weapons) — `XX_nnn.TEX` |
| `MENU/MSD` | 23 | `BACK BUTTON CBKEY CBMAGIC COMBO CREST ELEMENT EQUIP FORM GAMEOVER GRAVE HELP ITEM KEYCUS LIBRARY MAGIC NOTE OPTION PERSONAL PLIST RINGCTM SCORE SKILL` `.MSD` |

Other relevant archives: `COMMON.PKB` -> `CMNMENU.DAT` (common scene, 756 KB), `SH2.ICO` (memory-card icon), `SSHMES.JPN`
(system messages), `SSHDAT.JPN`; `SAVELOAD.PKB` -> `SAVELOAD.DAT` (153,072 byte texture bundle for the save UI, loaded by
`dataAccess::initialize` through `DVD_CBFunc` into a `primTex`); `OPENING.PKB` -> `BGM803.SSV` (title music),
`DEMO.LSD` (opening movie), `OPENING.DAT` (title textures); `LSD.PKB` -> `CM_A/CM_B/PV.LSD` commercials (`lsd/` dir).

## MSD / MDT chunk format

```
chunk: +0 u16 type, +2 u8 ptr_count, +3 u8 -, +4 u16 -, +6 u16 stride, +8 u32 count, +0xc u32 next (0 = last), +0x10 records
```
Pointers (the first `ptr_count` u32 of each record) are **file-relative offsets** in `.MSD` scene files
(`Convert(data, 0)`) and **chunk-relative** in `.MDT` data tables (`Convert(data, 1)`). Records are little endian.
Types: see `menu_toolkit.md` section 5 for the table; exact field offsets are in `sh2_menu::msd`.

Record layouts (record-relative):

* **Window (0x1c)**: `+0 u16 id, +2 i16 priority, +4 i16 x, +6 i16 y, +8 u16 w, +0xa u16 h, +0xc i16 cols, +0xe i16 rows,
  +0x10 u32 open_ticks, +0x14 u32 close_ticks, +0x18 u16 {bits0-2 open effect, 3-5 close effect, 6-8 style}, +0x19 bit1-2 clip
  mode, bit3 wrap-h, bit4 wrap-v, bit6 scroll enable, +0x1a u8 scroll-mark mask.`
* **Sprite (0x20)**: `+0 id, +2 prio, +4 x, +6 y, +8 w, +0xa h, +0xc col, +0xe row, +0x10 label, +0x12 flags (bit0 uv, bit1
  single packet, bit2 alpha-relative, bit3), +0x14 r,g,b,a, +0x18 u0, +0x1a u1, +0x1c v0, +0x1e v1` (u/v in texels; u0>u1 or
  v0>v1 mirror the image — used by corner pieces).
* **Polygon (0x3c)**: `+0 id, +2 prio, +4 col, +6 row, +8 label, +0xa flags, +0xc x[4], +0x14 y[4], +0x1c r[4], +0x20 g[4],
  +0x24 b[4], +0x28 a[4], +0x2c u[4], +0x34 v[4]` (strip order TL,BL,TR,BR).
* **Text (0x1c)** / **Message (0x20)**: `+0 id, +2 prio, +4 x, +6 y, +8 col, +0xa row, +0xc text id (index into the type-1 table),
  +0x10 rgba, +0x14 font number, +0x16 csa<<4 | spacing(signed nibble), +0x18/0x19 shadow x/y, +0x1a flags, +0x1b flags
  (+0x1c u16 max chars, +0x1e u16 ? for Message)`.
* **Group (0x18)**: `+0 id, +2 prio, +4 x, +6 y, +8 col, +0xa row, +0xc w, +0xe h, +0x10 label, +0x12 u16 alpha (0x8000), +0x14 selectable,
  +0x15 has-size`.
* **Cursor (0xc)**: `+0 id, +2 prio, +4 i16 w, +6 i16 h, +8 u8 {kind 0-2, shadow 3-4, rotate 5}, +9 u8 {skip mode 2-5, back object 6}`
  and direction in `u16@+8 >> 6 & 0xf`.
* **FontDraw (0x10)**: `+0 id, +2 prio, +4 psm (0x2c), +6 flags, +8 w, +0xa h, +0xc clut ptr`.

### Scenes in the demo

| file | size | chunks |
|---|---|---|
| BACK | 116912 | win 1, spr 1, att 2 |
| BUTTON | 564 | res 18, fdraw 1, win 1, spr 2, text 1 |
| CBKEY | 17336 | res 1, txt 7, fdraw 4, win 4, grp 3, spr 6, text 5, att 6 |
| CBMAGIC | 7728 | res 4, txt 2, fdraw 1, win 1, grp 1, text 2, att 3 |
| COMBO | 5936 | res 1, txt 2, fdraw 1, win 1, grp 1, text 3, att 2 |
| CREST | 14912 | res 6, txt 5, fdraw 3, win 2, spr 15, poly 3, text 8, att 8 |
| ELEMENT | 148064 | win 1, spr 3, att 9 |
| EQUIP | 15232 | res 15, txt 7, fdraw 4, win 3, grp 2, spr 2, text 11, att 6 |
| FORM | 34316 | res 12, fdraw 2, win 2, grp 3, spr 9, poly 20, text 2, font 6, att 19 |
| GAMEOVER | 412 | res 1, txt 3, fdraw 1, cur 1, win 2, spr 1, text 3 |
| GRAVE | 4432 | txt 3, fdraw 1, win 1, text 2, att 1 |
| HELP | 4320 | res 1, txt 3, fdraw 4, win 3, grp 1, spr 2, text 3, msg 1, att 2 |
| ITEM | 87360 | res 2, txt 1, fdraw 2, win 2, grp 1, spr 1, text 2, msg 1, att 5 |
| KEYCUS | 23696 | txt 7, fdraw 2, cur 1, win 2, grp 8, spr 7, poly 8, text 5, att 4 |
| LIBRARY | 15648 | res 42, txt 3, fdraw 4, win 2, grp 1, spr 4, text 19, msg 1, att 5 |
| MAGIC | 96432 | res 1, fdraw 1, win 1, grp 1, text 2, att 6 |
| NOTE | 2400 | fdraw 1, win 1, spr 1, msg 1, att 1 |
| OPTION | 9328 | txt 30, fdraw 2, cur 1, win 2, spr 9, text 2, att 4 |
| PERSONAL | 340016 | res 8, txt 18, fdraw 5, win 3, spr 1, poly 2, text 17, att 24 |
| PLIST | 9548 | res 8, txt 14, fdraw 1, win 1, grp 1, spr 1, text 2, att 7 |
| RINGCTM | 21112 | res 13, txt 25, fdraw 6, win 6, grp 3, spr 12, poly 1, text 14, att 12 |
| SCORE | 6016 | txt 33, fdraw 4, win 5, grp 2, spr 1, text 11, att 2 |
| SKILL | 96032 | res 1, fdraw 1, win 1, grp 1, text 2, att 5 |
| DAT/CMDMENU | 359928 | att 12 (field command menu: nested tables) |
| DAT/MFIELD | 921392 | att 1 |
| COMMON/CMNMENU | 756272 | res 3, spr 33, poly 2, att 15 |

### `SAVELIST.MDT`
One chunk of type 45 (0x2d), 50 rows `{ptr name (Shift-JIS), u32 location id}`: ids 0-39 field maps (アポイナの塔１ ...
イーダルフラーム３), 257-263 and 513-515 chapter/ending titles. `SaveMenuSection::GetSaveDataSlot` matches `MENU+8` against
the ids to fill `SlotInfo.location`.

### GAMEOVER.MSD example (412 bytes)
`res0 = "MENU/IMG/GO/GO_%03d.TEX"`, texts = ["ロード しますか？", "はい", "いいえ"], FontDraw 204x240, one Cursor, windows
{id -1 prio 10 800/800-tick open+close} and {120,120,240x80}, one full-screen sprite (0,0,512,448), three MenuText.
