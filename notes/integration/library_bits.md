# Monster library bits (US decompile, 2026-10-14)

Three bit arrays in the battle save block (`BTL0`): demo / retail offsets.

| array | demo | retail | meaning |
|---|---|---|---|
| defeated | `+0xdaf` | `+0xf43` | monster id seen in a **won** battle |
| snapped | `+0xdcf` | `+0xf63` | photographed with Anastasia's Snap Shot |
| knowledge | `+0xdef` | `+0xf83` | 2 bits per monster (drops / weaknesses shown) |

Evidence
* `+0xf43` writers: US main `FUN_00396fa0` = `BtlResult::Polling` (0x396fa0, state 2 step 1 -> 3: loop over the result list `obj2+0x176`, count `+0x1a3`) and `FUN_003657b0` = `BtlSocket::Polling` (0x3657b0, three loops over `+0x316` / `+0x1a3` in the result-state-0x28 path, the "battle chained / no result screen" path and the normal exit).  Both skip a monster whose `MONSTERParam+0x14` bit 6 is set (`(rec[0x14] >> 6) & 1`, `GetRegDat(0x34/0x2e)` rows of 0x38 bytes).  The `BtlSocket` path with `(+0x1a0 & 3) == 0` runs when the battle ends without the result screen.
* `+0xf63` writer: JP `StatusRecovery__Fii` (`decomp/H/BtlFree.c` ~1040, actually the command-kind switch; case 6 = Snap Shot) sets `+0xdcf` for the target's `nSubId` (+ the album bytes `+0xe2f / +0xe30` for 11 special monsters); retail readers: BATTLE `FUN_000c68d0` (`TargetInfo`) at 0xc6990 reads `+0xf63` for `BtlChr+0xba` of the target and then looks for a live party slot 4 (Anastasia) to choose the large plate (height 0xa8 / 0x60 px).
* `CmdLibrary` (`decomp/G/CmdLibrary.c` ~495-545) lists a monster when the *defeated* bit (`+0xdaf`) is set, and the second mode needs `+0xdcf`.

Port: `sh2_menu::save::BtlSave::{monster_defeated, set_monster_defeated, monster_snapped, set_monster_snapped, monster_knowledge}`; `sh2_battle::bridge::BattleSetup::library_ids` (monsters without the no-library flag) applied by `apply_end` on victory; `BtlHost::snapped` drained in `plugin.rs` after each action; `HudTargetPlate::snapped` filled from the fighter's MP / element.
Not identified: the source list of the knowledge array writes (`BtlSocket+0x58a` ids, `+0x64a` flags -> bit `1 << ((id & 3) * 2)`, doubled when the flag is set).
