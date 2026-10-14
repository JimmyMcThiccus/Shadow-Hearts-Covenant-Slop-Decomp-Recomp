# Round 5 BE -- battle, enemy side (every MONSET / boss / AI / stage)

Owner files: every `port/crates/sh2_battle/src/*.rs` except BP's `{actions,flow,rules,tarot,ui,menu_data,hud,hud_hits,hud_result}.rs`.
Tools: `tools/be/mipsdis.py` (R5900 disassembler for retail overlay code Ghidra has not disassembled: `python tools/be/mipsdis.py ../SH2US/BATTLE.BIN 45ea80 START END
--clean`, `--table ADDR N` dumps a jump table; `mipsdis.grep_all(file, base, regex)` scans the whole overlay).  Ghidra's `BATTLE.BIN` (raw at 0) decompiles
switch-free functions; every big switch (`AIIfFunc`, `AIGetValue`, `GetTarget`, `EffectCheckCore`) fails there because its jump tables hold absolute addresses.

Examples (all `SH2_US_DISC_DIR`): `be_tables` (MONSET / BTL_ / PIT_ / MON_ rows), `be_ais_scan` (static scan of the 116 retail AIS scripts), `be_skil` (SKIL
groups), `be_every_battle` (headless matrix, below).

## 1. Retail battle tables (US `sshdat.na`)

* **MONSET** (file 6, 327 rows of 0x14 B `{u16 id, u16 formation, u16 monsters[6], u32 flags}`).  `flags`: bits 0..1 escape rule (1 = impossible: every boss /
  event fight), bits 2.. = battle type (retail `MonsterSet` 0x4a1280 copies the row to `CBattle+0x4644` and stores `flags >> 2` at `CBattle+0x4866`):
  1 = "Battle Basics" tutorial (MONSET 4), 2 = "Combos" tutorial (5), 3 = no ambush (306), 4 = enemies cannot ambush (115-117, 136: Mother Filaria waves),
  5 = forced enemy ambush (173 Lion Dogs, 309).  101 rows have the escape bit (bosses / event fights).
* **PIT_** (file 36, 18 rows of 0x3c B): pit-fight rounds; `+0x1c..` = up to 16 u16 **MONSET ids** fought in a row (pit 0 = 49, 75, 73, 65, 84 ...).  So pit fights
  are ordinary MONSET battles.
* **BTL_** file 35 (0x24 B per monster id): `{u16 id, u16 n, n x {u8 kind, u8 sub, u16 id, u32 value}}` -- per-monster info lists (library / Snap Shot data,
  not used in battle logic); BTL_ file 34 (8 B): monster -> name / description index map.
* **MON_** (file 5, 0x38 B): `+4` CHR model, `+0x16 / +0x18` skill 0 / skill 1 (or `+0x16 = -1`: `+0x18` = skill **set** index), `+0x20` AIS id,
  `+0x30` PATK row, `+0x32` resist classes (bits 0..1 physical, 2..3 magic: 0 normal 1 immune 2 half 3 absorb) + status immunity bits 4..7,
  `+0x33` bits 0..5 / `+0x34` bits 0..5 status immunity (decoded by `host::monster_status_immunity`).
* **SKIL** retail: 26 groups; **monster skill sets = group 0x18 (85 x 0x28 B), monster skills = group 0x19 (524 x 0x20 B)** (`GetRegDat(0x3c, 0x18/0x19)`).
  The loader read groups 0x16 / 0x17 (retail fusion groups) -- **every monster skill on the US disc was wrong**; fixed in `actions.rs` (BP's file, hook logged).

## 2. AI (AIS VM) -- retail semantics

Scan of all 116 US scripts (`be_ais_scan`): no unknown tokens.  Used: IF conditions 0,1,2,3,4,5,7,0xd,0x17,0x1b,0x1e,0x21,0x22,0x25,0x26,0x27,0x2a,0x30,0x32,0x33,
0x35,0x37..0x3b,0x3d..0x44; actions 0x23 attack (216), 0x24 skill (634), 0x26 item entry (3), 0x27 Link (40), 0x28 guard (3), 0x2a last boss (1);
`AIGetValue` 0..10; `GetTarget` criteria 0..117 (formula), 120..124, 127..135.

Retail functions read with `tools/be/mipsdis.py` (US addresses; file offset = addr - 0x45ea80):
| function | US | notes |
|---|---|---|
| `AITurnFunc` | 0x6cf200 | decompiles; tokens as the port's `Dialect::Us` (group 0x2c, skip 0x2e, call 0x2d), 0x28 guard `(c, a)`, 0x2a last boss, 0x27 Link via `GetMoveTarget` |
| `AIIfFunc` | 0x6d0d30, table 0x6e73f0 (69 cases) | cases 0..0x35 = demo; new 0x36..0x44, 0x1e/0x40 skill-block records, 0x22/0x23 refuse when sealed |
| `AICalcFunc` | 0x6d6200 | first term token 0x16 = the unit *index* (later terms `nSubId`) |
| `AIGetValue` | 0x6d7410, table 0x6e7640 (11 fns) | new 6 combo members, 7 able allies, 8 `GetTarget` pick, 9 element of unit, 10 first CHR-74 enemy |
| `GetTarget` | 0x6d9450, table 0x6e7790 (136) | opponent candidates compare **absolute** HP/MP/SP (flag `sp+0xe0`), allies the ratio; specials 120..135 |
| `GetMoveTarget` | 0x6defb0 | a = 0: `GetComboTarget(chr, c) & 0xff`, a = 1: unit b |
| `EffectCheckCore` | 0x6e0320, table 0x6e7b10 | kind 'N' 0x4e = dispel test over the target's timed records |

New conditions (port `ai::ai_if_us`): 0x36 opponent down, 0x37 ally down, 0x38 no pending combo member, 0x39 an opponent has a dispellable effect, 0x3a an
opponent is not immune to status `v2`, 0x3b previous actor is an ally, 0x3c own body is CHR `v2`, 0x3d ally in bState 0x11..0x13, 0x3e own `'P'` (SATK charge)
record, 0x3f a living last-boss part CHR 500+v2, 0x41 / 0x42 bit `v3` of `v2` set / clear, 0x43 an ally has an offensive skill with record byte 5 bit 6,
0x44 an opponent has MP.  Criteria: 120 Nicolai 70 %, 123 `p3 < 0` = self (demo: `< 1`), 124 skill-block holders (none modelled), 125 none, 127 healthiest
50 % else weakest, 128 dispellable, 129 Yuri 70 %, 130 not immune to `p3`, 131 PCs with dispellable effects, 132 guarding units 50 %, 133-135 PC 11/12/13 50 %.

Monster data now fed to the AI per slot (`BtlHost::setup_monsters`): skills, PATK flag, **body model**, status immunity, resist classes, retail dialect.
`host.rs` maps AIS 0x27 to `MenuEvent::Link` (BP request: accept enemy partners).

## 3. Battle start rules
* **First strike / ambush** (`CheckGambit`, retail 0x4df640, integer form): ported as `bridge::check_gambit` (battle types 4 / 5, accessory 73 blocks enemy ambush,
  `500 + 600 * avgLUC / 99 + rand % 400` per 10000, faster side (avg AGL) rolled first, a side needs 2 members).  `BattleSetup::ambush` was always `None`.
  `SH2_BATTLE_NO_AMBUSH=1` turns it off.
* Escape rule: MONSET bits 0..1 (already).

## 4. Monster resistances / immunity
* Resist classes `MONSTERParam+0x32` now reach the damage code: physical (`flow::do_attack` through the new `Host::defender_resist` hook) and magic / skills
  (`host.rs`).  Before, every monster took normal damage from everything.
* Status immunity: the status records of skills / spells cast on a monster drop the immune bits (unless the record is "unresistable").

## 5. Last boss
`LastBossFunc` (phase 0xe, US 0x492200) plays effect `DataReadEntry(0xc, 0xd)`, then `LastBossSpecial` (JP 0x640840) re-arranges the core (CHR 499) and parts
(500..502: motions / positions, a mode flag `CBattle+0x26` bit 2); the turn ends with all parts in the command mask.  Port: AIS 0x2a -> a guard turn (no damage
in the retail either); the part rearrangement is not ported.

## 6. Headless every-battle matrix (`examples/be_every_battle.rs`, test `headless::tests::every_us_monster_set_runs`)
`headless::run_set` builds a battle exactly like the plugin (`build_setup` + `BtlHost::setup_monsters`), plays it through `flow::Battle` with a sturdy harness
party (30000 HP, x6 PATK, death / stone protection, refilled at its turns, attacks the first living enemy) while every monster runs its retail AIS script.
`BE_TRACE=1 cargo run --release -p sh2_battle --example be_every_battle -- FIRST LAST` prints the turns, AI decisions and damage.

Run 2026-10-14 ~04:20 (all 327 MONSETs): **316 won, 7 lost, 4 endless (400-turn cap)**; 6527 AI turns, **all decided by the scripts (0 fallback)**:
Attack 1489, SkillAttack 1714, MonsterSkill 2465, Link 668, Guard 185, LastBoss 5, ItemAction 1.  Every monster has its CHR model + motion file + AIS script and
every effect its skills name exists (`EFFECT/%03d_00.EFD` after the retail `raw >= 1000 -> raw - 1000` rule).
* lost (legitimate against the dumb policy): 159 / 160 (Hien + Armored Fighters), 218 (6 x Orobas: *Nightmare* HP -> 1 then a combo hit in the same slot), 232
  (Svarozic: *Dying* HP -> 1 rider + follow-up), 302 (last boss), 312, 319;
* endless: 174 / 175 (Blooming Phoenix x5 / x6 revive each other), 225 (Torso), 309 (MON 214, 30000 HP hidden boss) -- the harness party is too weak / too dumb.
Fixed through this harness: the retail monster skill groups (above), instant-death / status skills dealt damage (a record without damage words now only applies
its effect records, `host.rs`), enemy Link combos (AIS 0x27 -> `MenuEvent::Link`, combo flags refreshed), monster attack shapes > 3 = Standard (retail
`AttackFunc`), the retail effect id rule in the plugin (`effects_bridge::retail_effect_id`: effects 1000+ never played).

## 7. Field-side coverage (`sh2_field/examples/be_encounters.rs`, read-only)
559 maps, 274 with random encounters (1274 table rows), 152 `BBTL` rows (46 with the boss flag); all background ids exist on the disc (88 distinct), all MONSET ids
are in range; 300 of the 327 MONSETs are reachable from these tables (27 others: pit fights `PIT_`, literal `InvokeBattle`, debug).  Every BBG loads
(`stage::tests::every_us_bbg_loads`: model, `DAT`, `LIGHT`, `EFFECT` records -> background effects).

## 8. Visual checks (dev drive, `notes/integration/screens/r5_be/`)
`SH2_BATTLE_DEMO=232 SH2_BATTLE_BG=68` (Svarozic, BBTL 75): stage, boss model, retail skill name *Euthanasia* in the action window; `SH2_BATTLE_DEMO=302
SH2_BATTLE_BG=62` (last boss: Gaap CHR 499 + Aerolite 500 / Talos 501 / Onlooker 502 in formation 9).  `SH2_BATTLE_DEMO` now takes any set id (was `u8`);
`SH2_BATTLE_MAX_TICKS` (default 30000) is a hard exit for every dev-drive run.

## 9. Engine-started programs (FX X4 / X5)
`BtlHost::engine_fx` queues `EFFECT/BD_%03d.EFD` when a boss whose CHR has one falls (retail phase 0x13, `CBattle::Polling` 0x46d478 -> `DataReadEntry(0xc, 0xe, chr)`,
SE 2000 first; 29 BD files) and `EFFECT/UNION.EFD` on the last boss's AIS 0x2a turn; `plugin::start_engine_fx` hands them to `effects_bridge::ExtraFx`.
**Opt-in (`SH2_BATTLE_ENGINE_FX=1`)** until FX fixes the program camera (BD_420 leaves the view on the floor, `screens/r5_be/b007_bd` vs `b007_nobd`).  Effect stream
music (`sbgCreate`) is faded when the program ends.

## 10. Souls
`AddTrophy` (US 0x660ed0) sums `MONSTERParam+0x2c` into `CBattle+0x48bc` (EXP `+0x48b4`, cash `+0x48b8`); `MakeResultTrophy` scales it (0x661e68) into the result
(`Soul.` column).  The port now carries it to the result screen (`Host::monster_soul`); where the save stores the soul energy afterwards (`BtlResult` / `BtlSocket`
path) is **not identified**, so nothing is written back yet.

## Open (priority order)
1. BP: monster skill-attack riders (request 8: `Host::attack_rider` in `do_attack`; until then AIS skill-0 attacks resolve as an effect without the physical hit),
   dead PCs keeping turns (request 9), `MenuEvent::Wait` for AIS 1 / 3 (accepted), the tutorial fights' turn seeding / pages (battle types 1 / 2).
2. FX: `parse_package` drops the last-boss motion sets `a2` / `a3` (request 12); BD / UNION program camera (13).  Then `LastBossSpecial` (JP 0x640840: the core /
   part re-arrangement and the motion-set switch) can be ported on top.
3. Soul energy write-back (above); the knowledge array `+0xf83` (MN).
4. AI pieces not modelled: skill-block records (conditions 0x1e / 0x40, criterion 124: always "not blocked"), the `'N'` dispel test (approximated by "has a timed
   record"), condition 0x43's byte-5-bit-6 meaning, `GetTarget`'s Joachim filter (YOAH row flag), `CBattle+0x463c` target mask, the `bState` the AI sees (always 7).
5. Live verification not done this round: the direct battle start (`SSHSys+0x44` / request 0x21) leaves the field black afterwards and agents cannot reload states --
   needs the user (formations 3 / 9 / 0x11 and the last boss's part layout against `formation.rs`).
6. FS: `SetSceneInit` for scenes > 0 (US 0x3bc710, 0x2150 B) was asked of BE / BP; it is save / party logic (`BtlSaveSec`) and not done here.
