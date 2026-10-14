# Shadow Hearts: Covenant — save file format (JP demo SLPM_602.19, section F)

Recovered from `SaveData`, `SaveDataSection`, `BtlSaveSec`, `CFieldSaveData`, `SaveMenuSection`,
`SystemFile`, `SaveDevice{,MC,HDD}`, `dataAccess::Polling`. All integers little endian.
Rust parser: `port/crates/sh2_menu/src/save.rs`.

## 1. Memory-card layout

Folder on the card: `BISLPM-00000-SH2` (`SaveDevice::sm_folder`; the US build uses its own product code string — literal in .data, TODO confirm via the US map).
Files inside (names are `sprintf` templates in .data):

| file | content |
|---|---|
| `BISLPM-00000-SH2` | the **system file** (`SystemFile`, magic `SYSH`), 0x6c0 bytes; same name as the folder |
| `SH2-000` .. `SH2-014` | one **save file** per slot (`sm_slotName = "SH2-%03d"`), 15 slots (0..14) |
| `icon.sys` | PS2 memory-card icon.sys, 0x3c4 bytes (`SaveDevice::CreateIcon` builds it) |
| `SH2.ICO` | icon model, loaded from `COMMON/SH2.ICO` on the disc (`sm_iconFile`); copied from the DVD with `DvdromOrder::ReadOrder` |

On HDD (`SaveDeviceHDD`): partition `__common`, unit `hdd0:`, app pfs, same file names. HDD flavour is a
Japan-only product (PS2 HDD) — port can treat `SaveDeviceHDD` as a second directory.

`SaveDeviceMC::Sync` state machine (op byte at +6, step at +7): 1=Open (getinfo → chdir folder → read system
file), 2=Close, 3=CreateSystem (mkdir, write `icon.sys`, `SH2.ICO`, system file), 4=GetStatus, 5=Save slot
(StoreCommon → write system file then slot file), 6=Load slot (read slot → `SaveData::CreateSection` →
FlushCommon), 7=Delete slot (`sceMcDelete`, mark slot meta 0xff), 8=Format.

## 2. Checksum

`SaveData::SetCRC(buf, len)`: u32 at +0 = `sum of bytes [4 .. len)` (plain additive byte sum, wrapping u32).
`CheckCRC` is hard-wired to **return 1** (never verified) in the JP demo; the sum is only *written*.
For the save file `len = hdr.payload_size + hdr.hdr_size`; for the system file `len = 0x6c0`.

## 3. Save file (`SaveData` heap block)

The live save buffer is a fixed block at EE RAM `0x00100100` (`SaveData+0x1c`), the "common" block
(0x100 bytes of misc system state) at `0x00100000`.

```
0x00  u32  checksum (additive, see above)
0x04  [u8;8] magic "SSH_SAVE\0"   (rodata 0x003ff0e0)
0x0c  [u8;8] zero
0x14  u16  0
0x16  u16  header size = 0x20
0x18  u32  payload size = sum over sections of (0x10 + section size)
0x1c  u16  section count (3)
0x1e  u16  0
0x20  sections ...
```
File size actually written: `0x20 + payload` = **0x2bb4** (`0x20 + (0x10+0x1d44) + (0x10+0xa20) + (0x10+0x400)`).
The debug printfs in `dataAccess::Polling` print 0x1d44 / 0xa20 / 0x400 as the three section sizes.

### Section header (`_SaveDataSectionHdr`, 0x10 bytes)
```
0x00 [u8;4] name
0x04 u16 header size (0x10)
0x06 u16 version (0 for all three)
0x08 u32 data size
0x0c u32 aux (only `FLDa` uses it: chunk count)
```
Next section = `hdr + hdr_size + data_size`. On load `CreateSection` walks the list, finds the registered
`SaveDataSection` by name (`memcmp(name,4)`), calls virtual `CheckVersion(version)` (all must be true, else
load fails) and then `SetSection(hdr, data)` (virtual +0x10), which copies `min(file size, live size)` bytes
(BtlSaveSec copies exactly 0x1d44; CFieldSaveData also copies the header and recounts chunks).

Section order in the file = creation order: `BTL0`, `FLDa`, `MENU`
(`SSHSys::Initialize` → `new BtlSaveSec`; `InitFieldSaveData`; `MenuObj::Initialize` → `new SaveMenuSection`).

| name | class | size | notes |
|---|---|---|---|
| `BTL0` | `BtlSaveSec` | 0x1d44 | party / inventory / skills / battle state |
| `FLDa` | `CFieldSaveData` | 0xa20 (= 0xa2 × 16) | chunk-structured field state, see §5 |
| `MENU` | `SaveMenuSection` | 0x400 | menu state, party sets, cash, options, play time |

`SaveDataSection` virtuals (`__vt__15SaveDataSection` 0x00406c80): +0x08 dtor, +0x0c `SetDefault`,
+0x10 `SetSection`, +0x14 `CheckVersion`, +0x18 `FlushData` (called by `SaveData::Save` before writing).

## 4. `BTL0` — `BtlSaveSec` (0x1d44 bytes)

`ourBtlSaveDat__10BtlSaveSec` points at the data; `ourBtlSaveSec` at the section object. `SetDefault` zeroes
the block and (if RegDat loaded) runs `SetSceneInit(0, false)`.

| off | type | meaning |
|---|---|---|
| 0x000 | u16 | 0 at scene init (unused) |
| 0x002 | u8 | active bag index (item arrays are indexed `bag * 0x200`); 0 normally |
| 0x003 | u8 flags | bit0 combo-menu enabled, bit2 soul-system enabled (`SetComboMenuMode/SetSoulSystemMode`) |
| 0x004 | u32 | scenario / chapter selector 0..3 (also selects the RegDat table 0x26+n, 0x3f for starting inventory); doubles as index of the cash slot in MENU |
| 0x044 + i*0xc0 | PcRec[12] | 12 playable-character records (0xc0 bytes each), ends at 0x944 |
| 0x944 | u8[0x40] | consumable item counts (bag-relative) |
| 0x984 | u8[0x40] | item "seen/discovered" bitset |
| 0x9c4 | u8[0x60] | weapon counts (owned copies) |
| 0xa24 | u8[0x30] | armour counts |
| 0xa54 | u8[0x50] | accessory counts |
| 0xaa4 | u8[0x0a] | skill-learned bitset 1 (80 bits) |
| 0xaae | u8[0x0a] | skill bitset 2 (seen / equipped-ever) |
| 0xab8..0xaba | u8 x3 | misc stat-up counters (SP-up, etc.; incremented by `PCAddInit`) |
| 0xd48 | u8 | flags: bit2 Yoahism mode (`SetYoahismMode`), bit3 selects the alternate PC7 stat table (RegDat 0x2a/0xc) in `PCLevelInit` |
| 0xd4c | u32 | `ComboSkillFlag`-style bitfield written by `SetSceneInit` (0x802 / 0x800 / 2) |
| 0xd50 | u32[15] | Fusion-monster experience (`GetFusMonParam`: RegDat table 0x2d) |
| 0xd94 | u8[17] | fusion-monster level index, init 1 |
| 0xda8 | u16 | bitset (`SetSceneInit` item kind 7) |
| 0xdab | u8[]  | bitset (item kind 9) |
| 0xdae | u8 | bitset (item kind 8) |
| 0xe32 | u16 | PC5 (Yuri) "soul" unlock flags; 0xe34/35/36 derived tier bytes 0..2 |
| 0xe37 | u8 | PC6 mirror of rec.misc16 |
| 0xe38 | u32 | Yoahism counter (cycles, see `SetYoahism`/`GetYoahism`: wraps at 0x438) |
| 0xf44 | SkillSlot[?] | per-PC 0x10 bytes = 4 × {u8 kind, u8 idx, u16 id=0xffff} learned-ability slots; PC0 + extra rows 0xf44+0xc0.. , PC6 rows at 0x1114, PC7 rows at 0x1034 |
| ... | | remainder to 0x1d44: not touched by BtlSaveSec itself (battle/field systems write it) |

### PcRec (0xc0 bytes, record i at 0x44 + i*0xc0; PC ids 0..11)

| off | type | meaning |
|---|---|---|
| +0x00 | u8 flags | bit0 present, bit1 joined/available; bits2-4 and 5-7 from RegDat byte 7 (class/element) |
| +0x02 | u8 | character kind (RegDat byte 0) |
| +0x03 | u8 | **level** |
| +0x04/+0x06/+0x08 | u16 x3 | model numbers (`SetPCModelNum` writes all three) |
| +0x0a | char[0x12] | **name** (shift-JIS, NUL terminated; shown in save list) |
| +0x1c | u16 | HP max (base, before equipment) |
| +0x1e | u16 | HP current |
| +0x20 | u16 | MP max |
| +0x22 | u16 | MP current |
| +0x24 | u8 | SP max |
| +0x25 | u8 | SP current |
| +0x26 | u8 | STR |
| +0x27 | u8 | VIT |
| +0x28 | u8 | INT |
| +0x29 | u8 | POW |
| +0x2a | u8 | AGL |
| +0x2b | u8 | LUC |
| +0x2c | u8 | 0..99 secondary stat (clamped like the others; "MAG"/soul stat) |
| +0x2d | i8 | weapon item index (-1 none) |
| +0x2e | i8 | armour item index |
| +0x2f | i8[3] | accessory item indices |
| +0x32 | i8[8] | learned/equipped skill ids (bit index into 0xaa4 bitsets) |
| +0x3a | u16 | misc16 (PC5: unlock flags; PC6: byte mirror) |
| +0x3c | u32 | **EXP** (total); level derives from table RegDat 0x2a (16-byte rows: hp,mp,sp,str,vit,agl?,..,u32 exp-to-next @+0xc) |
| +0x40..+0x58 | 24 bytes | zeroed at init; u16 values written by `SetSceneInit` at +0x40/+0x42/+0x4a/+0x4c (combo / equipment-skill packed words, unresolved) |
| +0x58 | u8 | bitfield: low3 / bits3-5 = tool slots |
| +0x5a.. | u8 | counters |
| +0x64 | i8 | 0xff init (selected-ability) |

`GetPCParam(pc, kind)` / `SetPCParam` / `AddPCParam` (kind 0..0x12): 0 level, 1 HPmax, 2 HP, 3 MPmax, 4 MP,
5 SPmax, 6 SP, 7 STR, 8 VIT, 9 INT, 10 POW, 11 AGL, 12 LUC, 13 +0x2c stat, 14 physical attack (derived),
15 spiritual attack, 16 physical defence, 17 spiritual defence, 18 EXP. Level change recomputes stats from
the RegDat 0x2a rows (`PCLevelSet2` applies the row delta, clamps 1..999 for HP/MP, 1..99 for the rest).
`GetNextExp` iterates 99 rows summing `row.exp`.

## 5. `FLDa` — `CFieldSaveData` (0xa20 bytes = 0xa2 sixteen-byte units)

Section header aux (+0xc) = chunk count. Chunks are packed back to back, each a multiple of 16 bytes:

```
[+0 u8[2] tag][+2 u8 size_in_16B_units][+3 u8 flag][+4.. payload]
```
`SetDefault` order and sizes: `GS` 8 units (0x80 B), `RG` 0x81 units (2064 B), `TR` 0x10 units (256 B),
`WM` 5 units (80 B), `NP` 4 units (64 B). Total 0xa2 units = full section; `AddChunk` refuses to overflow.
`FindChunk(tag)` walks by size.

| tag | users | content |
|---|---|---|
| `GS` (field game-state) | `GetFieldGS`, `SaveScriptRegister`, `SceneInit`, `GetSavedMpsName`, `GetSavedChrPos` | +4/+8/+0xc/+0x54/+0x58 ints (target-map ids, entry pt); +0x10 char[16] current MPS (field map) name; +0x20 char[16] previous map name; +0x48 3×i16 packed position (`SetShortPos`), +0x4e i16 facing+1 |
| `RG` (script registers) | `CFieldSocket::{Load,Save}ScriptRegister` | +0x10: up to 0x200 u32 script registers (`CScript` register file, copied as `count<<2` bytes) |
| `TR` (treasure) | `SetTreasureFlag`, `RestoreTreasureFlag` | bitset starting at +8 (bit n = chest n opened) |
| `WM` (world map) | `GetWorldMapInfo` | payload at +4 (world-map position / flags, 76 B) |
| `NP` (npc library) | `FieldNpcLibrary(idx, minlevel)` | nibble array at +4: `nib[idx] = max(nib[idx], val)` (4-bit NPC "encounter" level) |

## 6. `MENU` — `SaveMenuSection` (0x400 bytes)

`sm_pSubstance__15SaveMenuSection` = object; object+0xc = pointer to data (section+0x10); object+0x10 =
`MenuDataTable` (loaded location-name table from MENU.PKB, key 0x2d).

| off | type | meaning |
|---|---|---|
| 0x000 | u16 | slot-info word 0 (copied to `_SaveDataInfo+2`) |
| 0x004 | u32[4] | cash per scenario index (`cash[BTL0.u32@4]`), clamp 99,999,999 (`SetCurrentCash`) |
| 0x008 | u32 | current location id (matched against MenuDataTable 0x2d rows to get the place name) |
| 0x00c | u32 | **play time in milliseconds** (`dispTime::Polling` adds 16 per frame; displayed `HHHH:MM:SS`) |
| 0x080 | i8 | current party-set index (0..4) |
| 0x081 | u8 | party-set lock (when !=0 `ChengePartySet` does not move) |
| 0x084 + k*0x20 | PartySet[5] | up to 5 named party sets, 0x84..0x124 |
| 0x180 | 0xa0 B | scene-init scratch (cleared by `SceneInit`) |
| 0x220 | 0x4c B | scratch cleared by `SceneInit` |
| 0x26c | u16[4] | pad button assignment (CPad assign slots 0xc..0xf; defaults 0xc,0xd,0xe,0xf) |
| 0x274 | u8 | options: bits0-1 vibration mode (`CVibeMan::SetMode`), bits2-3 sound out (0 stereo→0x1001, 1 mono→0x1000, 2 surround→0x1002; `Sdrv::SetMode`), bits4-5, bits6-7 further options (default 1 / 1) |
| 0x275 | u8 | options (bits4-5 = 1 default) |
| 0x278 | u8 | screen brightness 0..: applied as `CApp::SetBright(v*0.03 + 0.7)`, default 8 |
| 0x2ac,0x2ae,0x2b0 | u16 | 0xffff (last-used command cursor memory) |
| 0x2bc,0x2cc | 0x10 B | scratch cleared by SceneInit |
| 0x2fc | u32 | 0 at scene init |
| 0x300,0x312 | u8 | 2 (defaults) |

### PartySet (0x20 bytes at 0x84 + k*0x20)
| off | type | meaning |
|---|---|---|
| +0x00 | char[0xf] | set name (default names are Shift-JIS strings in .rodata) |
| +0x0f | i8 | member count (max 8) |
| +0x10 | i8 | max battle-team size (default 4) |
| +0x11 | i8 | current battle-team size (first N members are the team) |
| +0x12 | i8[8] | member PC ids, 0xff = empty; default `[0xb, 5, ff..]` in the demo |
| +0x1a | u16 | bitmask of forced/pinned members |

Ops: `JoinParty/LeaveParty(pc, set|-1=all)`, `JoinBattle(pc,set,pin)` moves a member to the front of the
battle team, `ClearBattleTeam`, `SetBattleCount`, `ChengePartySet(±1)` skips empty sets (+0x15 byte = member 3 id... sets with no members are skipped).

## 7. System file `SYSH` (`SystemFile`, 0x6c0 bytes)

```
0x00 u32 checksum   0x04 "SYSH"   0x08 u32 size = 0x6a0   0x0c u8 current slot   0x0d u8 slot count = 15
0x0e u16 header size 0x20   0x10 u16 common size 0x100   0x14 u32 common offset 0x20
0x18 u16 slot record size 0x60   0x1c u32 slot table offset 0x120
0x20 [u8;0x100]  common block (copy of EE RAM 0x100000; StoreCommon / FlushCommon)
0x120 SlotInfo[15] (0x60 B each, ends 0x6c0)
```
`SlotInfo` (`_SaveDataInfo`, filled by `SaveMenuSection::GetSaveDataSlot` when saving; byte 0 == 0xff means empty;
`SetCurrentSlot` picks the first non-empty slot):

| off | type | meaning |
|---|---|---|
| 0x00 | u8 | 0xff = empty slot, else used |
| 0x01 | u8 | leader level (PC `party.leader` rec +3) |
| 0x02 | u16 | MENU word 0 |
| 0x04 | u32 | play time ms |
| 0x08 | u32 | cash |
| 0x0c | u16 | bitmask of PCs in the party set |
| 0x0e | u16[4] | model numbers of the battle team (0xffff = none) |
| 0x16 | char[0x12] | leader name |
| 0x28 | char[0x10] | party-set name |
| 0x38 | char[0x28] | location name (from MenuDataTable 0x2d) |

The save-slot list UI (`dispSaveFile::mSetupDispFile`) reads these without opening the slot files.

## 8. Slot / device operations seen by `dataAccess`

`dataAccess::Polling` (state at +0x160) — see `notes/F/dataAccess.md`.

Save sequence for slot n: `SaveData::Save(n)` → every section `FlushData()` → device op 5: `StoreCommon`
(copies EE 0x100000..+0x100 into SYSH), writes system file (`GetHeap` recomputes checksum), writes `SH2-%03d`
with `SaveData::GetHeap()` (checksum recomputed over payload). Load: read slot file → verify header magic
(`SSH_SAVE\0`) → `CreateSection` → `FlushCommon` copies SYSH common back to EE 0x100000.
