# BtlSocket (main executable, SLPM_602.19 0x0032d610 .. 0x0032f720) and the battle glue on the main side

Decompilation: `decomp/H/BtlSocket.c`, `BtlBonus.c`, `BtlResult.c`, `BtlFader.c`, `BtlIn.c`, `BtlInBoss.c`, `SSHSys_battle.c` (tidied Ghidra output from the main exe).

BtlSocket is the host object between the field/scene layer and the BATTLE.BIN overlay: it loads the overlay, instantiates `CBattle`, feeds it the party and
the monster set(s), collects the per-fight result records and plays the victory/defeat screens. Full description and the state machine: `battle_flow.md` section 1.

## Layout (object size 0x69c, allocated by `InitBtlSocket` 0x0032d4c0)

| off | meaning |
|---|---|
| +0x20 | flags |
| +0x24 | overlay load state (0 idle, 1 loading, 2 loaded) |
| +0x28 | **state** (0..8): 1 create CBattle / 2 wait / 3 BattleEnd requested / 4 finished / 5 BtlBonus / 6 BtlResult / 7 fade BGM / 8 release |
| +0x34 | current monster-set index; +0x58 number of sets; +0x5c + i*0x10 copies of `MONSETTbl` |
| +0x47 | roster count (<=8); +0x49 PCs in this fight; +0x4a.. PC ids (<=4 front, 4 reserve) |
| +0x15c | background id; +0x168 demo flag; +0x16c result (bits0-1 outcome, bits2-6 fights won) |
| +0x160/+0x164 | result callback + arg (`SSHSys::cbBattle`) |
| +0x170.. | consolidated drops: item ids, +0x230 counts, +0x290/294/298 exp/cash/sp, +0x29c pcExp[12], kills +0x2cc/+0x44c, trophy keys +0x526/+0x540/+0x5a0 |
| +0x68c/+0x690 | `SmoothFilter` / `BlurFilter` |
| +0x694 | battle BGM number; +0x698 Yoahism level |

## `_SysBtlParam` / `StartBattle`
`SSHSys::StartBattle(_SysBtlParam*, const char* returnPath)` (0x003b6c20) copies the param block to `SSHSys+0x40..0x4f`, the path to `SSHSys+0x54`, and sets
`SSHSys.+0x36 = 0x20` (battle request). `cbBattleA(code, ...)` decides the next scene from `BtlSocket+0x16c & 3`.

## Result record, BtlBonus, BtlFader, BtlIn/BtlInBoss
See `battle_flow.md` (result record layout, BtlBonus 0x0034c810, BtlFader 0x00371870, BtlIn 0x003ad2c0 / BtlInBoss 0x003b2770).

## Open items
* Exact `_SysBtlParam` field names (only the sizes/uses are known); `BtlResult` internals; BtlIn polygon-group geometry (`BI_PolGrp`).
* Not ported to Rust beyond the state machine in `sh2_battle::flow`.
