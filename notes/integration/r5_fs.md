# Round 5 FS: field scripts, maps, story progression (whole US game)

Owner: FS (`sh2_script/**`, `sh2_field/src/` minus the MN / CS files).  Status at the end of round 5 is in section 5; the walk results in section 3.

## 1. The harness: a headless story walker (`sh2_field::story`, `examples/story_walk.rs`)

Plays the field side of the retail game with no renderer, from `OP_00_U` (new game) on, through the real `FieldHost` / `CScript`:

* dialogue: circle every 12 ticks; selection windows answered by a per-action policy (choice 0; the walker also tries the other answers of the first two
  prompts of every action); field rings (`SetRing` / `RingControl`) answered with each colour of the ring's areas;
* scripted battles (`InvokeBattle` / `InvokeBattleTbl`): won at once; the map is re-entered with `RESTORE` like `SSHSys` after the result screen
  (`ssh_sys = [2, 1, ..]`: back from a battle, won; a `SetLocationName(2, ..)` socket rename sends it to that map instead);
* map jumps: register file saved (`SaveScriptRegister`), the loaded models carried over (`CarriedActors`), the next map built; the world map: new points
  first, then frontier / least visited open points;
* menus / shops / the save screen opened by a script are closed at once; party changes that need `SSHDAT` (`SceneInit`, `PCAddInit`) are applied with the battle
  crate's data (`sh2_field::party`); `SpecialMenu(7)` = the end of the game (`Stop::Ending`).

At free control (no event job, no window, the control model under pad control) it tries every action a player has -- step into each enabled kind-0 event box,
examine each examinable box, talk to each displayed model with a talk event, circle on each look point -- each on a **clone of the whole game**, all actions in
parallel threads, and keeps the one that changed the story most (new story flags x1000, never-seen register byte values x20, a scripted battle, a map not
visited yet).  With no progress it heads for the frontier: the nearest map (over the exits learnt so far) not visited since the story last moved.

```
cargo run --release -p sh2_field --example story_walk -- [--map M] [--entry N] [--decisions N] [--flags 8,9,0x322=3] [--checkpoints DIR] [--load FILE] [-v]
SH2_WALK_STREAM=1   print the walk live          SH2_WALK_TRIALS=1  print every trial of every decision
SH2_WALK_TRACE=MAP  engine calls + branch decisions of that map's start function     SH2_WALK_GREP=MAP:substring  engine calls of that map
```

`--checkpoints` writes the session at every map entry (`story::write_checkpoint`: map, entry, registers, save file, BTL0 copy, `ssh_sys`, position);
`--load` resumes there.  Trials that never give control back are listed as `STALL` at the end (map, action, last engine calls).

Other new tools: `examples/op_args_census.rs` (static selector census of the multi-purpose ops over all scripts), `msc_hdr.rs`, `gs_dump.rs` (read-only GS /
story flags of the saves on a memory card), `map_trace --us` / `script_corpus --us` now set the retail region.  `tools/live/msc_list.py`: comparison /
bitwise op names fixed (0x70 lt, 0x71 gt, 0x72 le, 0x73 ge, 0x74 eq, 0x75 ne, 0x77 xor, 0x78 or).  Retail FIELD.BIN / SLUS code was read with a small MIPS
disassembler (no Ghidra needed; FIELD.BIN raw at 0x45ea80, SLUS file offset = address - 0x1fff00).

## 2. What the walk found and what was fixed

| # | symptom | cause | fix |
|---|---|---|---|
| 1 | party never changed (Yuri's party never formed) | `SetFieldData` 0x0a / 0x0b / 0x13 / 0x20 no-ops, 0x14..0x16 partial | retail `SetFieldData` (US 0x004fb8c0, table 0x00610a70) decoded: 0x08 no-game-over flag, 0x0a ClearBattleTeam, 0x0b JoinBattle, 0x12 GraveYardEnable, 0x13 SceneInit, 0x14 / 0x15 join / leave (+ record "in party" bit), 0x16 current set / battle count / lock, 0x17 GS flag, 0x1f / 0x25 / 0x38 MENU words, 0x20 PCAddInit, 0x2d record name, 0x2e GS word +0x46, 0x31, 0x34 |
| 2 | scripts read -1 for the current party set; wrong battle members | `GetFieldData` 0x16 missing, 0x21 compared with the member count | retail `GetFieldData` (US 0x004fc170): 9 battle result, 0xd how the map was entered, 0x16, 0x1f, 0x21 (battle count), 0x25, 0x29 member position, 0x2a image object state, 0x2e, 0x36, 0x37 WM bits, 0x38 |
| 3 | after the Ardennes boss the world map had no open point | the post-boss scene renames the socket's map (`SetLocationName(2, ..)` = `strcpy(CFieldSocket+0x64)`): the battle returns to `HUB_NA`, which opens Paris | `RetailState::socket_map`; battle hand-over and walker return there; sub 1 = team name of a party set |
| 4 | doors could not be examined (BO_03_U) | examine probe tested kind != 0 boxes; JP / retail `Polling` test every box (`HitCheck` mode 1) | `sim.rs` examine -> `HitMode::All` |
| 5 | scripted defeats always ended in a game over (BE 10) | `SetFieldData(8)` | `GameSession::ssh_sys` mirror <-> `SshSys::btl_result` |
| 6 | field rings always "missed" | the result is the colour code of the area the pointer stops in (`cbRing` 0x004faf20) | `FieldRing { colours }`, host answers the first area's colour, walker tries every colour; ring screen requested from MN |
| 7 | story equipment changes were only logged | `CharacterEquip` stub | US 0x003f4aa0: kinds 2 / 3 / 4 / 5, mode 0 strip, mode 1 give + equip |
| 8 | IF_11_U start scene hung (QA's IF_11_U failure) | `GetCharacterInfo(s, 0xd)` = index in the 54-name standard motion table (US 0x00509c40), and a one-shot motion falls back to `fidl` | `standard_motion_index`; idle fallback after a one-shot motion (not looping, so a queued motion still replaces it) |
| 9 | the player vanished after scenes (RU_00_U, WI_04_U ...) | the port rebuilt the model table per map; `CField` is reused across `MapJump` and `InitSDB` (US 0x004f7210) only hides the models (corridor maps never load the player) | `CarriedActors` / `build_runtime_carry` / `FieldCarry`; the shown control model goes to the entry point with pad control; same-model `LoadCharacter` resets like `CFieldModel::Reset`; walker safety net `ensure_control_model` (no longer fires) |
| 10 | `MapJump(1, n)` went to map "" (QA1, 33 exits) | pointer 1 = `GetSavedMpsName(1)` (US 0x003f7c40) | GS +0x20 of the save, else the map this one was entered from (an empty name string -- a jump wrapper called without one -- is resolved the same way, logged) |
| 11 | arguments shifted, stack leak in every `&&` / `||` / `|` (QA2) | **VM bug**: ops 0x76..0x7a did not pop their second operand | `cscript::expression` (JP 0x00295840) |
| 12 | Ring Soul scenes loaded all models into the player's slot | **VM bug**: bss sized by the header, accesses past it dropped (SU_04_U: 10 bytes declared, state at +0x84..) | bss >= 64 KiB |
| 13 | HE_24_N / GT_10_U waited for effects for ever | retail `EffectControl(h, 0)` = node+0x14 & 7; scripts wait for 3 | effects report 1 loading, 3 running, 0 ended |
| 14 | the ending did nothing | `SpecialMenu` kind 7 = `CField+0x178` delete reason 2 -> scene 0x40 (title) | `MenuReq::EndToTitle` -> `SshSys::request_title()`; walker `Stop::Ending` |
| 15 | the typed name never reached the dialogue (MN 1) | `SpecialMenu(k < 0)` returns `CField+0x2170` | `ScriptState::name_buffer` (filled from `FieldScreens::name_result`) |
| 16 | field vibration ops were state only (CS4) | | ops 0x69..0x6e drive `sh2_audio::vibe` sequences from the map's GENERIC "VIBRATION" block, forwarded as `VibrationRequest` |
| 17 | field effects were 180-tick placeholders (FX X2) | | `StartEffect` gen / target sets decoded; `drive_field_effects` runs them on `FxRunner` (drawn, sounds forwarded), the script sees the program state |

Walker-side (the harness, not the engine) -- what a player does that the first walker did not:

| # | where | what the player does | walker |
|---|---|---|---|
| 18 | MI_02_U (Mikasa) | a persistent "Switch Parties" window (`OpenMessage(.., 0x2710, -1)`) stays open during free control | free control = no event job and every open window fully typed |
| 19 | MI_02_U / MI_09..11_U | square switches between the two parties (the start function polls `get_pad(2)` itself) | `Action::Pad`: every button mask a map's code tests with `get_pad(2) push16 mask and` (circle excepted) |
| 20 | treasure chests (MI_02_U, TD_04_U ...) | open them from the front (`GetCharacterInfo(s, 1)` of player and chest compared) | talk actions stand in front of the model, facing it |
| 21 | Mikasa security keys | take the key items | +400 for a trial that changes both the treasure flags and the bag |
| 22 | TD_14_U (Todo lab shooting range) | press the button of the target symbol that rises (models 292..295 = circle / square / triangle / cross) | `story::minigame_press` |
| 23 | one-way pockets (TD_16_U / TD_21_U before the power is on; Mt. Fuji) | come back and take the other way | decisions with a second progressing action are remembered; after 80 decisions without progress the walk goes back to the latest one and bans the action it took (per state); a map whose start never gives control back is undone (`rollback`) |

Also: QA's `SetSceneInit` question -- `party::scene_init` reproduces cases 1, 2, 3, 4, 5, 6, 8, 14 (bag, records, SCEN group); 7, 9..13 are record / bag moves
not reproduced.  The dev map-name label is hidden during cut scenes and the stale "MCES not played" log line is gone (CS3).

## 3. Coverage of the walk

The walk is a chain of runs resumed from its own checkpoints (`--load`: the state it wrote at a map entry), from `OP_00_U` (new game):

* **First half, played**: Apoina, Domremy, Ardennes Forest (boss), Graveyard, Paris, Louvre 1 / 2, Wine cellar, Southampton, Ronda mine, Wales 1 / 2,
  Hermitage 1-3, Petrograd 1-2, Goreme Valley 1-2, Mirror castle, Manmaria Island, Corridor of the dead, Firenze 1-3, SG Italy branch, Idar Flamme,
  Apoina Tower 2 -> `DC_01_U` (disc change, seamless) -> `OP_01_U`.  Not reached: 0x08 Opening (set outside the map scripts), Nemeton ruins / Firenze 4 /
  Cannes 1-2 / Sainte-Marguerite (0x18..0x1c: the walk took the other branch; Nemeton's stone-sled menu loops).
* **Second half, played**: 2nd half opening, Red-brick warehouse, Yokohama 1, into Mikasa.
* **Skipped by hand twice** (the walker cannot solve these yet; the engine runs them): the Mikasa two-party security-key puzzle (`--goto MI_16_U`, the
  boss and flag 0x3f follow) and Todo lab 2's power-relay chain (reg byte 0x33b 1..10 across TD_22 / TD_00 / TD_21 / TD_16 / TD_00; `--flags 0x47`).
* **After the skips, played**: Mikasa 1 boss, Todo lab 1 (incl. the shooting range), Yokohama 2, Foreign cemetery 1, The other world, Muhyoan 1,
  Nihonbashi 1, Muhyoan 2, Nihonbashi 2, Forest of wind 1, Inugami village 1; the walk then searches Mt. Fuji (0x4c).
* **Ending**: `ED_00_U` played on its own (`retail_story::ed_00_u_ends_the_game`): final boss (monster set 302), films, clear save, `SpecialMenu(7)` -> title.

Story flags reached by walks: 28 of the 34 first-half chapter flags, 14 of 26 second-half (0x3c..0x4b except 0x41 Mikasa 2 and the forced 0x47), 0 of 6
hidden.  Evidence for the coverage matrix: `tools/coverage/out/fs_story_walk.txt` (`flag`, `map` lines; a flag's map names the chain it came from).

Coverage rerun (`tools/coverage/run_all.sh all --fresh`, 2026-10-14 evening, FS target dir): **3793 items, 3543 ok, 97 stub, 3 fails, 150 untested**
(before this round's last fixes: 3449 ok / 39 fails / 221 untested).  Field maps 559 = 495 ok / 64 stub; story 1673 = 1510 ok / 21 stub / 3 fails
(debug maps / maps not on the disc); chapter rows 52 ok / 17 untested.  The 13 new "jump MAP -> MAP:n entry not in MAP" stubs are the headless
runs' `MapJump` with an empty name (no previous map in a single-map run -> this map).  Field ops: 137 of 141 ids handled (0x13, 0x3e, 0x3f, 0x47 not).

## 4. Open, in priority order

0. Walk the rest of the second half (Mt. Fuji 0x4c .. Last dungeon 0x55) from `cp42`-style checkpoints, and teach the walker the two skipped puzzles
   (Mikasa keys: two parties, two keyholes, reg 0x1110 / 0x1111; Todo lab power: reg 0x33b).  The shooting range is passed by reaching its end; the
   walker's presses still score misses (lane state / timing of `0x79a7` not matched yet).
1. Stalls the walker found (optional content): AD_02_U doll-house panels (examine boxes open a cursor-driven window), GT_10_U pit-fight arena loop,
   WI_13_U talk loop -- these wait for pad input other than circle / the selection cursor.
2. Field ring screen (MN), `fldAttachBG2` named BG models for SM_07_U (FX X2 remainder), `GetFieldData(0x26)` pit-fight info (DB_00_U / GT_10_U / GI_02_N).
3. `SetSceneInit` cases 7, 9..13; retail BTL0 has 14 party records (the demo-shaped copy 12).
4. `MapJump(1)`: who writes GS +0x20 on the console is not found (the port falls back to the map the player came from).
