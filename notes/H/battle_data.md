# Battle data — what the battle system loads and where it lives

Implemented in `port/crates/sh2_battle/src/{pkb_compat,data}.rs` (both validated against the real JP disc folder
`Shadow Hearts II (Japan) (Furokuban)/`; tests run when the folder exists or `$SH2_DISC_DIR` is set).

## 1. PKFINFO.TBL / *.PKB (decoded here because section A's reader did not exist yet — FLAGGED)

`PKFINFO.TBL` (28416 bytes) is the directory of every `*.PKB` archive (main exe: `FileIOLib::InitPkb` 0x0022ae70,
`SearchFile` 0x0022c7a0, `searchInfo` 0x0022c980, `gettokun` 0x0022c650, `enCode` 0x0022cfb0, `deCode` 0x0022ca90).

```
header (16 B): +2 u16 entry size (0x10), +4 u32 byte size of the entry area (=count*16); 1775 entries in the JP disc
entry  (16 B): +0  8 byte name code      (3 groups of 4 chars, alphabet ".0123456789A-Z_", base 40, big-endian pair)
               +8  u32 LE pos            (16-byte units; add up along the path)
               +12 u32 LE meta           bit31 set → directory: low 31 bits = byte delta (÷16 = entry delta) from the start
                                          of *this entry's list* to its child list; bit31 clear → file size in bytes
```
* Top-level list = 13 entries: `FIELD.BIN`, `BATTLE.BIN` (plain disc files, meta = size) and the PKB archives
  `BTLDATA COMMON EFFECT MENU FIELD OPENING SAVELOAD WORLDMAP SHOP SOLOMON LSD` (archive file = `<NAME>.PKB`).
* Child lists are laid out depth first (list, then the lists of its sub-directories in order); a list ends where its first
  sub-list begins.  File offset in the PKB = 16 × Σ pos along the path.  Verified: `COMMON/SSHDAT.JPN` at 0x100000 (70648 B) etc.
* Name code: `v = c0 + 40*c1 + 1600*c2 + 64000*c3` per 4-char group (digit = alphabet index + 1, 0 = pad);
  `A = ((hi0 + 40*hi1 + 1600*hi2) << 16) | lo0`, `B = (lo1 << 16) | lo2` with `hi = v >> 16, lo = v & 0xffff`.

## 2. BTLDATA.PKB (68 246 208 B) layout

```
BTLDATA/BTL_000.BIN BTL_001.BIN BTL_002.BIN    "tex" texture bundles (59 sections …) – battle effect textures
BTLDATA/SOUND/BGM/BGM401.SSQ …                 battle BGM sequences (+BGM801.SSE)
BTLDATA/SOUND/SE/nnnC.SSE nnnM.SSE nnnWnn.SSE  per character/monster/weapon SE banks (nnn = chr id, W = weapon variant)
BTLDATA/SOUND/SYSTEM/SYSBTL.SSE                system battle SE
BTLDATA/BBG/001.BBG … 077.BBG, nnn_nn.EFD      battle backgrounds ("DAT","mdl","mbs", SSH1.01 …) and effect data
BTLDATA/AIS/Mnnn_nnn.AIS, P000_000.AIS         AI scripts (9 in the Furokuban demo), tiny (276..1138 B) token streams
BTLDATA/CHR/nnn.ANM + nnn.BCM                  motions ("anm" sections) and model bundle ("mdl","sdw","dse","wse","mse","cse","bbx",…)
BTLDATA/WPN/nnn_nn.WPN, nnn_nnn.ANM            weapon models per character (rw/rws/lw/lws/ase …) + their motions
```
Every container (BTL, BBG, ANM, BCM, WPN, AIS-less) uses the same generic `u32 count, u32 size, {tag4, offset}…` header (same as
SSHDAT).  Character ids in file names: 000 Yuri? (000/001/002/005/006/007/018/035/082/088/122/123 are PCs & NPCs), 4xx = monsters.

## 3. COMMON/SSHDAT.JPN and SSHMES.JPN — the database behind `RegDatApi::GetRegDat`

Loaded at start-up by `RegDatApi::Initialize` (0x0037b430) from `common/sshmes.jpn` (tag `reg1`) and `common/sshdat.jpn`
(tag `reg2`); the blocks are found by walking the memory-block list at 0x108000 (`GetRegDat` 0x0037b6b0, 5 KB switch).  Section
indices below are SSHDAT sections (33 total); `GetRegDat(id, idx, sub)` = `section + idx*stride` (+ nested offset for ids marked N).

| GetRegDat id | SSHDAT sec | tag | stride | content |
|---|---|---|---|---|
| 0x26 0x27 0x28 0x29 | 0 1 2 3 | PC_I | 0x1c | per-difficulty initial PC data (12 PCs) |
| 0x2a (N) | 4 | PC_L | 8 per PC → rows of 0x10 | level tables (see rules §9) |
| 0x2b (N) | 5 | PC_J | 0x20 | judgement ring data per PC/level |
| 0x2c | 6..9 | FUSM | 0x20 | fusion monsters, table chosen by `ourBtlSaveDat+4` (chapter 0..3); +5 SP cost, +0x1d equip type |
| 0x2d (N) | 10 | FUSM | 0x10 | fusion level growth rows: STR,VIT,AGL,INT,POW,LUC bonuses |
| 0x2e | 11 | MON_ | 0x38 | **MONSTERParam** (81 entries in the demo) |
| 0x2f | 12 | MON_ | 0x10 | **MONSETTbl** monster sets (32) |
| 0x30 | 13 | WPN_ | 0x34 | weapons (80) |
| 0x31 | 14 | ARM_ | 0x18 | armor (31) |
| 0x32 | 15 | ACS_ | 0x2c | accessories + abilities (77); +0x10 four 32-bit effect codes |
| 0x33 | 16 | ITEM | 0x30 | usable items (41) |
| 0x34 | 17 | KEYI | 0x08 | key items (255) |
| 0x35 | 18 | CLOT | 0x0c | costume data (11) |
| 0x36 (N) | 19 | SKIL | per-PC groups (24 groups, strides 0x40/0x28/0x20) | skills/special commands; group 0x16 = monster skill sets (0x28 per set, 20 × s16) |
| 0x37 | 20 | MC_P | 0x1c | |
| 0x38 | 21 | MAGI | 0x44 | magic (59) |
| 0x39 | 22 | COMB | 0x40 | combo skills (8) |
| 0x3a | 23 | PATK | 0x18 | weapon attack data (111); +0x16 = hits per swing |
| 0x3b | 24 | PATK | 0x48 | attack animation data (252) |
| 0x3c / 0x3d | 25 / 26 | AROM | 0x08 / 0x40 | aroma data (8 / 56) |
| 0x3e | 27 | JRCI | 0x20 | judgement ring areas (55) |
| 0x3f (N) | 28 | SCEN | | scenario |
| 0x40 | 29 | YOAH | 0x10 | Yoahism (difficulty) scaling rows (5) |
| 0x41-0x43 | 30-32 | DEMO | 0x1c | demo PC data |

SSHMES sections (44): 0..3 PC_N names, 4..7 FUSM names, 8 MON_ names (0x12 = 18-byte Shift-JIS strings), 9 WPN_, 10 ARM_,
11 ACS_, 12 ITEM, 13 KEYI, 14 CLOT, 15 SKIL, 16 MC_N, 17 MAGI, 18 COMB, 19 AROM, 20 JRCI, 21 YOAH, 22-24 DEMO, 25-40 the
80-byte descriptions of the same, 41-42 TUTO (tutorial), 43 PAUS.

### MONSETTbl (16 B)
`u16 formation; u16 monsters[6] (0xffff = none); u16 flags` — flags bits0-1 = escape mode (1 never / 2 always), bits2.. = battle type
(→ `CBattle+0x45c2`, 1 or 2 disable evade/crit unless the demo flag is set).  Formation → monster count: 0→1; 1,2,0xf,0x10→2;
3,4,5,0x11→3; 6..9→4; 10,0xb,0x12,0x13→5; otherwise 6 (`CBattle::MonsterEntry` 0x004635a0).  `BtlSocket::AddMonsterSet` copies up to 16 sets
into the socket; after each fight (`BtlSocket+0x34` index) the next set is started until `+0x58` sets are done (multi-wave battles).

### MONSTERParam (0x38 B, little endian)
```
+0x00 u16 id            +0x02 i16 (sequence number in the demo DB)   +0x04 u16 **CHR model number** (`BTLDATA/CHR/%03d.BCM/.ANM`: 418, 404, 35 ...; read as `chr+0xdc` by `DataReadEntry`; the old `u8 defensive element` here was the low byte of this number; the monster's element, used for defence and attack alike, is `+0x14 & 7`)
+0x06 u16 HP  +0x08 u16 MP  +0x0a u16 PATK  +0x0c u16 PDEF  +0x0e u16 SATK  +0x10 u16 SDEF
+0x12 u8 AGL  +0x13 u8 LUC  +0x14 u8 attack element (&7), bit7 → chr flag 0x10    +0x15 u8 size class (chr flagsA1 bits5-7)
+0x16 i16 skill id 0 / -1 → use skill set at +0x18    +0x18 i16 skill 1 or skill-set index
+0x1a i16 drop item 1  +0x1c i16 drop item 2   +0x1e u8 drop chance 1 (%)  +0x1f u8 drop chance 2 (%)
+0x24 i32 EXP  +0x28 i32 cash  +0x2c u16 SP reward  +0x2e u16 (→ chr+0x18e/0x190)  +0x30 u16 attack table index (PATK)
+0x32 u8 resist: bits0-1 physical class, bits2-3 magic class  (0 normal,1 immune,2 half,3 absorb)
```
(The JP Furokuban demo database only fills a handful of monsters: ids 0, 1, 2, 10, 20, 80 …; EXP/cash fields are mostly 0 there.)

### Equipment records
* `WPN_` (0x34): +6 u16 equip mask (bit = PC id), +8 PATK, +10 SATK.
* `ARM_` (0x18): +4 equip mask, +6 PDEF, +8 SDEF, +10/+11 resist bits (2 bits per element, elements 0..3 in +10, 4..5 in +11).
* `ACS_` (0x2c): +4 equip mask, +6 PATK, +8 SATK, +10 PDEF, +12 SDEF, +14/+15 resist bits, +0x10 four effect codes (`-1` empty).
  Effect codes feed `SpecialEffectCode` (0x0032fb10): byte3 class 0x00-0x0f → plain value; 0x10-0x1f → stat modifier `kind = hi16 + 3`
  with percent bit 28 / chance; 0x20-0x2f → status bit-field record (kind 0x47 [+0x48]); 0x30-0x3f → two-word record (kind 0x48); 0x40-0x4f/0x50-0x5f →
  packed modifiers (`kind = (w>>9 & 0x7f) + 3`, value 13-bit signed in the 0x5x class, duration in bits 4..8).  Kinds 9/10 (heal/damage) are
  scaled by INT×2 (PCs) or SATK (monsters); kind 0x0b by INT/10.

## 4. AIS (enemy AI scripts) — `BTLDATA/AIS/Mnnn_nnn.AIS`
Streams of little-endian `s16` tokens interpreted by `CBattle::AITurnFunc/AIIfFunc/AICalcFunc/AIGetValue` (JP 0x006433e0…).  Operand tokens:
`0x15 imm16` (immediate follows), `0x16` own monster id, `0x17` own turn count, `0x19` number of living units on the own side
(`CBattle+0x3e94/96`), `0x1a..0x21` eight per-character script registers (`chr+0x19c..0x1aa`), `0x22` none, `0x2c` function call
`AIGetValue(kind, a, b…)`; arithmetic tokens `0x0b` end, `0x0c` set, `0x11 +`, `0x12 −`, `0x13 ×`, `0x14 ÷`.  Conditions (`AIIfFunc`) select a test by number:
0 random%, 1 ==, 2 !=, 3 ≥, 4 >, 5 ≤, 6 <, 7/8 own HP ≤/≥ x%, 9/10 MP, 0xb/0xc SP, 0xd/0xe any ally HP ≤/≥ x% …
`AIGetValue` kinds: 0 ally with highest HP, 1 count of own skills (excluding one), 2 count of usable skills, 3/4 n-th (usable) skill index, 5 random in [a,b).
A fully decoded VM is future work (`notes/H/CBattle.md` open questions).

## 5. Names of the code-side tables (overlay .data, JP)
`BtlMenuItem_J` 0x651f20 (27 command labels), `BtlMenuNote_J` 0x651f90 (help texts), `BtlMes_J` 0x651de0 (60 battle strings: "Guard",
"Critical", "Miss", status names Poison, D.Poison, Paralysis, Seal, Mental Break, Panic, Stone, Death, Violently …),
`IconDataTbl` 0x650d80, `SwordDataTbl` 0x651180 (+`PCnn_SwordData`: sword-trail anchors), `MuzzlePosDataTbl` 0x651b70,
`AttrCol` 0x652b60 / `HitAttrCol` 0x654ea0 (element colours), `TurnPCFace` 0x652bb0, `AromaColorData` 0x657000.


## 6. Battle model files (verified 2026-10-09, Rust: `sh2_battle::models`)
`CBattle::DataReadEntry(chr, type, id)` formats (BATTLE.BIN 0x655640..): 1 `BTLDATA/BTL_%03d.BIN`, **2 `BTLDATA/CHR/%03d.BCM`** (model bundle), **3 `BTLDATA/CHR/%03d.ANM`**
(motions), 4 `BTLDATA/BBG/%03d.BBG`, 5/6 `BTLDATA/WPN/%03d_%02d.WPN/.ANM`, 7/8 the 3-digit-variant WPN files, 9.. `AIS`, `EFFECT/%03d_00.EFD`...
* BCM = package `mdl` (+`sdw` shadow, `dse`/`wse`/`mse`/`cse`/`ase` sound-effect banks, `bbx` boxes) + the first motions (`app`, `idla`, `idlb`, `idlc`; monsters `idla`, `idlb`).
* ANM = the rest: `dsh def defa defb esc crvd blwd blwi flyi lad dwn dwni wup mags magi mage uitm atck can1..can4 rdy koda blwa flya win key2..key4 ...`
  (monster CHR 418, the demo's most common enemy, has no `atck`).  `BtlModel::SetBtlMotion(id)` (0x0054e500) maps engine ids to these names
  (1 idle, 3 app, 4 dsh, 5 atck, 6..9 can1..4, 16 blwa, 17 flya, 18 koda, 25 def, 26/27 defa/defb, 28 esc, 35 dwn, 36 dwni, 37 wup, 38 uitm, 39..41 mags/magi/mage,
  42 win, 43..46 fusa/fuea/fusb/fueb, 47..78 `sp0`..`sp31`).
* Attack motions carry `MosEvent` event keys (u16 time, first = the hit frame, e.g. frame 10 of the PC `atck`) and `MosCncel` (combo cancel window); the ROOT track of `atck`/`dsh`
  carries the lunge (34 / 47 units): the battle code moves the model by it (`BtlModel::TranseCallBack`).
