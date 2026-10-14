# US retail save format (`SLUS_210.41`) -- validated against a real memory-card save

Status 2026-10-10.  Code: `port/crates/sh2_menu/src/{save,memcard,storage,session,ringcustom,score}.rs`.  Ground truth: the user's emulator card
`~/Library/Application Support/ARMSX2/memcards/Mcd001.ps2` holds a **real save made by the retail game**: folder `BASLUS-21041-SH2` with
`BASLUS-21041-SH2` (system file, 1728 B), `SH2-000` (12332 B), `icon.sys` (964 B), `SH2.ICO` (39320 B).  Copies of the two data files are the test fixtures
`port/crates/sh2_menu/tests/fixtures/us_card_SH2-000` / `us_card_system`.  The same blocks were cross-checked against the live `SaveData` heap of the PINE
save states (`SaveData` = EE `0x00100100`, "common" block `0x00100000`).

## Identical to the demo (notes/F/save_format.md)

Container (`SSH_SAVE`, header 0x20, sections `{name, hdr 0x10, version, size, aux}`), **additive byte-sum checksum over `[4..len)` -- now really verified**
(`SaveData::CheckCRC` = `FUN_0035fcf0`, the demo's was a stub returning 1; the real file's 0x81ab matches), system file `SYSH` (0x6c0, 15 slot infos of 0x60 B,
common block copy), slot file names `SH2-%03d`, `icon.sys`, `SH2.ICO`, MENU party-set record, FLDa chunk list (`GS 8`, `RG 0x81`, `TR 0x10`, `WM 5`, `NP 4` units).
Differences are the names and sizes below.

## What changed

| item | demo | retail |
|---|---|---|
| folder + system file name | `BISLPM-00000-SH2` | **`BASLUS-21041-SH2`** (rodata 0x00434050; `SaveDevice::sm_folder`) |
| file size | 0x2bb4 | **0x302c** (`0x20 + 3*0x10 + 0x21bc + 0xa20 + 0x400`) |
| `BTL0` | version 0, 0x1d44 B | **version 4, 0x21bc B** (`BtlSaveSec::SetSection` copies 0x21bc for v4; v3 files are converted: records get 4 bytes inserted at +0x58) |
| `FLDa` header aux | chunk count | the game never clears it: `SetDefault` runs twice at boot, real files say **10** for 5 chunks (`SetSection` walks `aux` headers, the spare ones have size 0).  The Rust reader stops at the first empty header and keeps the value for byte-exact re-saving. |
| `MENU` | 5 party sets | **7 party sets** at `+0x84 + k*0x20` (set 6 = Yuri alone), joined-PC mask u16 at `+0x82`, location id at **`+0x10`** (demo `+0x08`), cash at **`+4 + bag*4`** (bag = `BTL0+2`), best-progress u32 `+0x14`, language u32 `+0x18`, cached quick-slot summary `+0x40..0x64`, defaults: brightness 7, pad entries `c e d f` |
| `GS` chunk | | `+0x64` u16 = saved disc number (`Retail_SetSavedDiscNo`), `"CLEAR"` map name + `+0x58` for the New-Game-Plus reset (`Retail_CFieldSaveData_ResetClearChunk`) |

## Retail `BTL0` (0x21bc)  (`sh2_menu::save::retail_btl`)

```
0x000 u16 0      0x002 u8 bag (active bag; the retail "scenario": also selects the cash slot; a new game is bag 1)   0x003 u8 flags (bit0 combo shortcuts on)
0x03c 12 party records of 0xc0 B (record = demo record layout up to +0x58; `+0x5c` base/chosen hits/ring type, `+0x5d` auto ring, `+0x5e..0x68` ring points,
      `+0x68` ring item (-1), `+0x6c` u32 from PC_I[0x18..]; `+0x40 + 2*pc` u16 friendship values)
0xabc two bags of 0x200 B (bag b at +b*0x200):
        +0x000 u8[0x30] consumables       +0x030 u8[0x20] item-obtained set 1 (`SCEN` kind 10)   +0x050 u8[0x20] set 2
        +0x070 u8[0x60] weapons           +0x0d0 u8[0x30] armour                                  +0x100 u8[0x60] accessories
        +0x160 u8[0xa] skill/crest bits (kind 5)           +0x16a u8[0xa] second set               +0x174 u8[0x40] KEY ITEMS (kind 6; [0..3] ring-stock counters)
0xec0 u8 flags (bit2 soul system, bit3 alternate PC7 table)   0xebc u32 combo-known bits   0xec8 u32[23] fusion exp   0xf24 u8[23] fusion level
0xf3c u16 kind-7 flag word   0xf3f u8[3] kind-9 bits   0xf42 u8 kind-8 bits   0xf43 u8[0x20] monster MET bits   0xf63 u8[0x20] monster DEFEATED   0xf83 2-bit knowledge/monster
0xfc6.. soul unlock words (PC5)   0xfcc u32 3 after a new game
0x10bc 12 x 0x10 ability / combo-shortcut slots `{u8 kind, u8 button, u16 id}` x 4   (0x11ec / 0x130c: PC0 / PC6 / PC7 larger tables)
0x14bc 3 x 0x400 score blocks (see `score.rs`)       0x20bc 0x40 x {s16 id, u16 count} sorted item-list cache (rebuilt by `FUN_003bf2d0`)
```

`SetSceneInit` (`FUN_003bc710`) rows `{u8 kind, u8 value, u16 index}` of `SCEN` (`GetRegDat(0x47, scene)`): 1/2/3/4 bag arrays, 5 skill bit, **6 key item**, 7 / 8 / 9
flag words, 10 obtained bit.  The retail start gives key items `[1] = 3, [2] = 3, [0x33] = 1` (reproduced; the real save has exactly these) next to 8 Thera / Mana / Pure Leaf,
3 Talisman of Luck, 3 Tent.  `retail_new_game_matches_real_save` tests this against the card.

## The port's two views

`BtlSave { data: demo-shaped working copy (0x1d44), retail: authoritative 0x21bc block }`.  Load (`from_retail_section`) maps the shared fields (party records,
bag arrays, skill bits, `+0xab8` counters = key items 0..3, flags, fusion exp / level) into `data`; save (`sync_to_retail`) maps them back over the raw block; everything
else (key items >= 3, flag words, library / score / combo state, ability slots) is read and written through accessors on the raw block.
`parse -> to_bytes` of the real card file and of the real system file are **byte identical** (tests `real_retail_card_save_roundtrips_byte_for_byte`,
`real_retail_system_file`).

## Memory-card reader (`memcard.rs`)

`MemCard` parses a PS2 card image (superblock, indirect FAT -> FAT, 512 B directory entries, with or without the 16 B ECC spare per page; flags `0x20` directory /
`0x10` file).  `MemCardStorage` serves one save folder read-only as a `SaveStorage`.  `FileStorage::default_dir()` (used by every title / menu path through the
`SaveDevice` resource) attaches it on the retail build: `SH2_MEMCARD=<path>` or the default ARMSX2 / PCSX2 `Mcd001.ps2`, disabled by `SH2_NO_MEMCARD=1`.  **Continue loads the
real card save**; the port's own saves go to `$SH2_SAVE_DIR/BASLUS-21041-SH2/` and shadow the card's files (the first port save copies the card's system file, so
slots made by the real game stay listed).  The card image itself is never written.

## Writing (round 4, `notes/integration/menu_m1.md` section 3)

`sh2_menu::memcard` now writes card images (FAT, directory entries, ECC verified against this card; `format_new`, `mkdir`, `write_file`, `delete_file`); retail saves go to the port's own `mcd_sh2_port.ps2`
(seeded from the emulator card's folder on the first save, `icon.sys` / `SH2.ICO` included), reads fall back to loose files and then to the emulator card.  The real card image is only written with `SH2_MEMCARD_WRITE=1`.

## Not done / open

* Slot-info location names: the screen shows the `SlotInfo` location string (the real card holds "Apoina Tower/1F Hallway"); the port writes the `SAVELIST.MDT` place name of `MENU+0x10` when it exists, else the map id.
* v3 files (older retail builds) load through the 0x3c-byte-prefix conversion that `BtlSaveSec::SetSection` implements -- not ported.
* A card image written by the port was not mounted in the emulator to see whether the real game accepts it (needs the emulator).
