# Round 6 FS2: story to the end, field scripts

## Status (2026-10-16, batch 3)

**Chapters reached (story flags set by walks, union with round 5):**
- First half: **29 of 34** (0x18 Nemeton ruins new in batch 3; still missing 0x08, 0x19, 0x1a (no constant setter), 0x1b
  Sainte-Marguerite, 0x1c Cannes 2).
- Second half: **23 of 26** (was 14; 0x47 now played): new this round 0x4c Mt. Fuji, 0x4e Inugami 2, 0x4f Foreign cemetery 2, 0x50 Azabu mansion,
  0x51 Inugami 3, 0x52 Queen's garden, 0x53 Wales 3, 0x54 Inugami 4 -- all played (Fuji by the puzzle search, the rest by the novelty
  walk with `--search-on-stall`), and the walk then enters the last dungeon (`AI_05_U` -> `AI_00_U` "Vessel"; its own search: 416
  states, closed, see below).  Missing: 0x41 Mikasa 2, 0x4d Graveyard 2, 0x55 Last dungeon -- **no script references these three flags
  at all** (`flag_xref --flags`: no set / clr / chk with a constant; the same holds for 0x08 and 0x19), so they are probably debug-menu
  chapter markers that the story never sets.  0x47 (Todo lab 2) is now played too (batch 2, below); 0x3f is played
  (Mikasa plan below, no more `--goto MI_16_U`).
- Second half after batch 3: still 23 of 26, but the walk now **plays the whole last dungeon and the ending**: from
  `fs2/chain/6_last_dungeon_AI_00_U.walk` with the Vessel plan, AI_00..03 rings -> AI_06_U (boss, monster set 217) -> GY_00_D ->
  AI_04_U -> ED_00_U (final boss 302) -> `SpecialMenu(7)` "THE END" in 41 steps / 17 s.  0x55 is never set by a script (see above).
- Hidden: 0 of 6.

**Second-half chain** (checkpoints in `fs2/chain/`, resume with `story_walk --load F [--goto MAP:ENTRY]`):
`1_post4e_00037_IN_04_U` (Fuji search result) -> `2_post4f_AP_02_A` (+ `--goto KA_09_U:0`) -> `3_post51_IN_02_U` (+ `--goto QG_14_U:0`)
-> `4_post53_WE_00_U` -> `5_post54_IN_00_U` -> `6_last_dungeon_AI_00_U`.  Logs: `fs2/fu5.err`, `w1.err`, `w2a.err`, `w3a.err`,
`w4a.err`, `w5.err`, `ai1.err`.

**Batch 3 (2026-10-16):**
- **Vessel ring solved.**  The ring registers are bytes **0x3a8..0x3ab** (one per floor, 0..3; the old notes watched 0x3ac..0x3b1).
  The altar (event 70, answer 0) runs AI_01_U func 0x42d0: `get_pad(0, 0)` (raw) each round, 0x80 (left) / 0x20 (right) turn the
  floor's ring, 0x2000 (circle) confirms, 0x4000 (cross) cancels; func 0x5acf compares the rings' colours (func 0x4c5b) and opens
  the elevators (bytes 0x38c / 0x38d).  The start job's loop at 0x347b (`get_pad & 0x1000` = triangle -> funcs 0x33fb / 0x337f) is
  only the ring camera.  Why the old pads did nothing: `Policy::pads` only pressed on the tick after a pad read, which never lined up
  with the loop's next read.  Now (`Game::tick`): while an **event job** read the pad within 30 ticks, the next scripted button is held
  until the script has read it once, then nothing for 20 ticks (`pad_age`, `pad_gap`).
  Plan `sh2_field/tests/walk/ai_00_u_vessel.plan` (8 steps, from lparchive update 135): floor 2 `L,L,L,O` (3), floor 3 `L,L,O` (2),
  floor 4 `L,O` (1) -> flash back to floor 1 -> `look 0x6 (ev 75)` "the light shines to the heavens" -> the ending (above).
  Test `retail_story::vessel_ring_plan_reaches_the_ending` (ignored, release, ~17 s; fixture `tests/walk/ai_00_u_vessel.walk`).
  Note for `sdis.py`-style disassemblers: expression op **0x79 is `&&`, 0x7a is `||`** (the scratch `sdis.py` had them swapped).
- **Nemeton ruins (0x18) played.**  The round-5 walk had reached ND_08_U (the last block level) many times; the exit (event 2, walk-on
  box 1) only jumps while register byte 0x68 is 0, which event 4 (box 3, preloads ND_14_U) sets.  ND_14_U's start function: flag
  0x156 (the sentry fight, box 1 / event 2, monster set 74) and not 0x157 -> scene that sets 0x157 and goes through GY_04_U back into
  ND_14_U, where 0x157 and not 0x15c -> the Karin scene (func 0x2fa8) sets 0x18.  Plan `tests/walk/nd_08_u_exit.plan` (3 steps) on
  fixture `nd_08_u_exit.walk` (= round-5 `cp27/04343_ND_08_U.walk`); test `retail_story::nemeton_exit_plan_sets_the_chapter_flag`
  (ignored, release).
- **Cannes / Sainte-Marguerite (0x1b / 0x1c): reached SM_19_U, blocked on the Handmade Key.**  Fixes on the way:
  - `next_chapter_area`: the lowest chapter of `CHAPTER_AREAS` not reached **in the half of the highest flag** (a walk that took the
    other first-half branch had 0x1d..0x28 set and was sent to Mt. Fuji); `AREA_GATEWAYS` / `in_chapter_area`: SM is reached through
    CA (Nelson's boat, CA_02_U -> SM_00_U).
  - SM_05_U's dial lock = 8-6-4 (`examine box 1 (ev 2)|0,8,6,4`; register byte 0x128).
  - SM_07_U (Veronica's perfume scene) hung in `while (EffectControl(child, 0) != 2)`: **`EffectControl(h, 2, flags, gen*, tar*)`**
    creates an instance of a loaded effect (US FIELD.BIN 0x51dd70: a node under the parent with its own generating / target sets;
    `EffectSlot::child`, state 1 while it plays, 2 once ended), and **handles stay valid after `EffectControl(h, 1)`** (retail handles are
    node pointers; the port used to shift later handles down -- SM_07_U removes two effects and then instances a third).
  - SM_11..14 (Blanca's stealth section): **`WaitCharacterEx(slot, mode | 0x100)`** is a non-blocking poll returning 1 when the wait
    would be over (the start job's step machine runs `AutoMove` then `if (WaitCharacterEx(0, 0x100) == 1) step++`).  The walker
    also presses cross / triangle / square every 5 s when the start job polls the pad behind an open window (SM_11_U's "Hide / Move"
    tutorial waits for `get_pad(0) & cross`).
  - With these the walk plays the stealth section, Oscar and the reunion (SM_08..SM_17, SM_18 / 22 / 23) and reaches SM_19_U, whose
    door (event 2) to SM_20_U (sets 0x1b) needs flag 0x113 = Locke's **Handmade Key** (CA_01_U func 0x5b4d, Locke = slot 14, talk
    event 16; gives the key once register byte 0x208 counts the parts: Bent Wire, Adhesive, Fountain Pen).  Locke only stands in
    Cannes after flag 0x112 (PA_03_U event 28, Paris), which needs 0x111 (PE_00/01/02_N event 42, Petrograd).  So 0x1b / 0x1c need a
    world-map side trip (Petrograd -> Paris -> Cannes) plus the three parts: next step, as a plan (the LP's update 36 has the key).
  - Checkpoints: `fs2/chain/7_post18_CA_00_U.walk` (after 0x18), `8_sm_05_dial.walk`, `9_sm_17_veronica.walk`; `fs2/cpsm3/` has the
    stealth walk (`00319_SM_19_U.walk` at the locked door, `00375_CA_01_U.walk` back in Cannes).
- Ghidra: instance :8192 now has **FIELD.BIN** open (was SLUS_210.41); raw at 0, US address - 0x45ea80.

**Batch 1:**
- GPA review fixes: the GT_10_U test now checks the pit-fight table directly (`host::pit_fight_field`, `GetRegDat(0x53)` answers for
  every record; no talk on a fresh GT_10_U reaches `GetFieldData(0x26)` -- the old assertion could never match); `SH2_WALK_QUEUE`
  default 256 (~1.3 GB) and a dropped state is no longer marked seen; `minigame_press` only takes over TD_14_U while a lane is non-zero
  (traced: all 8 lane states are 0 before the first and after the last target); `merge_bag` adds the same 0x40 item slots case 10
  clears (doc no longer claims key items); `cmd.rs`, `cscript.rs`, `memory.rs` back to LF (their diffs are now just the real lines).
- World-map choice (`Walker::pick_world_point`): a point whose `WM` byte changed since the last look (initialised at the walk start,
  so a resumed walk does not count everything as changed) beats the next chapter's area (`next_chapter_area`, from the static setters:
  0x18 ND, 0x1b SM, 0x1c CA, 0x4c FU, 0x4e IN, 0x4f GB, 0x50 KA, 0x51 IN, 0x52 QG, 0x53 WE, 0x54 IN), which beats the world the screen
  opens on, which beats a "new" point.  Before, the walker toured Europe for hundreds of decisions after 0x4f / 0x53 (the screen opens
  on Europe).  Trial scores: outside the next chapter's area a jump into it +300, the world map +250 (WE_00_U's ev 7 used to win with
  its jump into Nemeton).
- `story_walk`: `--points` (open world points, `SH2_WALK_POINTS=1` adds the `WM` bytes), `--search-world 0`.
- `SetSceneInit` 7 / 9 / 10 / 12 / 13 in `party.rs` (10 partly, 11 only the party bit; see the code comments), `GetFieldData(0x26)`.

**Mikasa (0x3f) solved by a scripted route:** the route comes from **the user's reference** (lparchive.org, Shadow Hearts Covenant
Let's Play update 76, relayed by the coordinator), turned into 57 walker steps with the new `walk_probe` example (tries every action of a
state and prints texts / register changes) and stored as `sh2_field/tests/walk/mi_02_u_keys.plan`.  `Walker::plan` / `SH2_WALK_PLAN`
(`MAP:text;...`) take the first trial on that map whose `"{action} {choices:?}"` contains the text.  Findings: square (`press pad
0x8000`) switches parties; keyhole prompts are 4-item lists (`[0]` = the other keyhole / insert, `[1]` = take out / keyhole 2 when
inserting at MI_02_U); key values: 0x110 = 1 / 2 (MI_02_U holes 1 / 2), 3 (MI_06_U console); 0x111 = 1 / 2 (MI_09_U), 5 / 4 (MI_13_U
holes "1" / "4"); levers A (MI_17_U cabin, Cabin Key from MI_12_U), B (MI_07_U), C (MI_14_U); the parties meet in MI_14_U (talk slot 1),
MI_15_U examine box 1 -> MI_16_U boss -> 0x3f, and the walk goes on through Todo lab 1 (0x40).  Test
`retail_story::mikasa_security_keys_plan_reaches_the_boss` (ignored, release).  The blind search before it: 616 states in 2290 s, no
result.

**Batch 2 (2026-10-16):**
- **QA2's field blockers**: none is an engine wait that never ends.  Answers per map in `requests.md` "Round 6 FS2" (pad-polling altar
  loop in AI_01..03, debug pad loop DB_00, timed key hunt SM_15, bss dispatcher loops behind `WaitModel`, a `PathMove` patrol in CA_01,
  an absent NPC's talk event in PA_02_A, RU_04's message-typing wait needing circle presses).  The `--story` autopilot stall did not
  reproduce in a 300 s run.
- **Todo lab 2 (0x47) is now played.**  The dead end was a walker artifact from lab 1, not the lab-2 route: TD_06_U's look point
  (event 16) sets flag 0x1c2f, which TD_02_U's door (event 1) reads as "you're going the wrong way".  In lab 1 the player walks through
  TD_02_U's walk-on box 6 (event 6, enabled while reg 0x338 = 0xd): a shooting gallery that sets 0x1c2e and clears 0x1c2f.  The walker
  teleported past it.  Fixes in `story.rs`:
  - `Walker::score`: a walk-on box that changes the state (`Enter`, Free, novel > 0) gets +250, so it beats a jump into a new map.
  - `minigame_press`: TD_02_U's gallery holds still while event 6 runs (it shows no lane tables; a press is a miss), see
    `SHOOTING_MAPS`.
  - Test `td_02_u_lab1_gallery_clears_the_wrong_way_flag` (fixture `tests/walk/td_02_u_lab1.walk`, from the Mikasa plan run).
  - From `fs2/chain/td_22_u_power.walk`, with the lab-1 flags as the gallery leaves them (`--flags 0x385=0x40`), the novelty walk
    plays the whole escape: TD_15 -> TD_02 -> TD_01 -> TD_14 range -> TD_03..05 -> TD_20 -> TD_06 -> TD_17 -> TD_07..13 stairs -> TD_00
    lobby -> boss (monster set 164) -> **0x47**.  No hand-set 0x47 any more.  The fixture itself was made before the fix and still has
    0x1c2f set.
- **Plans can press buttons**: a plan step `text|c1,c2|pads` plays the action whose name contains `text` with those answers and the
  buttons `pads` (`L,R,U,D,O,X,T,S`; `Policy::pads`, pressed every 20 ticks while no window is waiting, or while only a fully typed
  window is open).  `press pad 0x20||` synthesises any button.  `walk_probe --pads R,R,O` tries them.
- **Vessel ring: not solved in batch 2 (solved in batch 3, above).**  Floor 1: `look 0x1 (ev 15)` (switch) then `look 0x3 (ev 72)` -> AI_01_U (floor 2).  The altar,
  `look 0x1 (ev 70)` answer 0, explains the control ("rotate with left / right, circle to confirm, cross to cancel").  Then the event
  ends and the start job's loop at 0x3495 polls the pad (`get_pad & 0x1000` -> func 0x33fb, func 0x337f each round).  These all left
  regs 0x3ac..0x3b1 unchanged:
  - Left / right / circle / triangle sequences sent through the event's pads.
  - The same presses as separate free-control pad steps.

  Next: read funcs 0x337f / 0x33fb (which pad mode / bits they test, where the ring angle lives -- probably bss).
- Not reached this batch: the second-half rerun after the Vessel; the first half 0x18..0x1c.

**Open puzzles:**
- First half 0x1b / 0x1c: Locke's Handmade Key (batch 3 above): flags 0x111 (Petrograd ev 42) -> 0x112 (Paris PA_03_U ev 28) ->
  Locke in CA_01_U (slot 14, ev 16) with the three parts -> 0x113 -> SM_19_U door -> SM_20_U (0x1b) -> CA_03_U (0x1c).
- The Vessel's optional chests (Seventh Key, Crucifix) and the good-ending question are not in the plan (it takes the shortest way).
- `SetSceneInit` 10 / 11 remainders.

**Files (batch 3):** `sh2_field/src/story.rs` (scripted pads held until read, `pad_age` / `pad_gap`, help-window presses,
`next_chapter_area` per half, `AREA_GATEWAYS`, lone CR fixed), `host.rs` (`EffectControl` mode 2 + stable handles, `WaitCharacterEx`
0x100), `plugin.rs` (child effect states), `sh2_script/src/cscript.rs` (`pad_reads`), `examples/walk_probe.rs` (branch runs),
`tests/retail_story.rs` (Vessel + Nemeton plan tests), `tests/walk/ai_00_u_vessel.{plan,walk}`, `tests/walk/nd_08_u_exit.{plan,walk}`.

**Files (batch 1):** `sh2_field/src/story.rs` (plan, world-map choice, area hint, queue cap, `minigame_press`, `wm_seen` init),
`host.rs` (`pit_fight_field`), `party.rs` (`merge_bag`), `examples/story_walk.rs` (`--points`, `--search-world`), new
`examples/walk_probe.rs`, `tests/retail_story.rs` (GT_10 table test, Mikasa plan test), `tests/walk/mi_02_u_keys.plan`;
`cmd.rs` / `cscript.rs` / `memory.rs` line endings only.

## Earlier (round 6 before the pause)

**What is done (compiles: `cargo check -p sh2_field -p sh2_script --examples` is clean):**
- `sh2_field/src/host.rs` op 0x64 `RingControl`: a ring-screen hook for RG.
  - New state fields: `st.ring_screen` (the plugin sets it), `st.ring_wait` (the screen is shown) and `st.ring_answer` (the screen posts the colour code here).
  - The instant fallback stays for the headless runs. RG has already adopted it: `field_ring::instant_result` / `possible_results`.
- `sh2_field/src/story.rs`:
  - `Walker::search(max_nodes)`: a breadth-first puzzle search. It expands every free-control state with every action and the prompt / ring variants, and follows jumps and battles but not the world map. The state key `state_key()` is the map + registers + the TR / WM chunks + BTL0. It stops when a new story flag is set.
  - `Walker.search_budget`: runs the search when the walk stagnates (more than 80 decisions without progress), before it backtracks.
  - The `quiet` press: an event that makes no engine call for 5 s gets cross, then triangle, then square. Example: MI_02_U's "View map of ship" (callu 0x5aa9) waits for cross. That timed out before; verified fixed.
  - `SH2_WALK_FORCE=MAP:text` forces a trial (debugging).
- `examples/story_walk.rs`: new options `--search N` (search first), `--search-on-stall N` and `--regs 0x15f,..` (print register bytes at the start and the end).
- New `examples/flag_xref.rs`: a static cross-reference.
  - `--flags` / `--set-only`: setFlag, clrFlag and chkFlag call sites with a constant argument.
  - `--regs 0x115f`: typed register byte accesses. regT v: type `v>>12`, byte index `v&0xfff`, so regT 0x115f = register byte 0x15f.
  - Output of the full run: `scratchpad/fs2/flags_set.txt`.

**Findings:**
- Static setters of the chapter flags:
  - 0x18 ND_14_U, 0x1b SM_20_U, 0x1c CA_03_U.
  - 0x4c FU_18_U (func 0x401a), 0x4e IN_06_U, 0x4f GB_00_U, 0x50 KA_01_U, 0x51 IN_02_U, 0x52 QG_12_U, 0x53 WE_04_U, 0x54 IN_03_U.
  - No constant setter for 0x08, 0x19, 0x1a, 0x41, 0x4d or 0x55 (computed argument or engine side).
- Mt. Fuji is a crystal routing puzzle:
  - The crystals are register byte 0x15f bits 1 / 2 / 4. They come from treasures: FU_01_U (bit 1), FU_02_U ev 6 (treasure 0x1bc + flag 0x951, bit 2) and FU_04_U (bit 4).
  - Each gate pedestal byte 0x160..0x164 holds the crystal inserted there. `callu 0x3f56` jumps by value: 1 → first destination, 2 → second, 4 → third.
  - The way on is FU_06_U → FU_12_U → FU_15 → FU_16 → FU_17 → FU_18_U. It needs crystal 4 in FU_06_U's gate (byte 0x163): event 13 jumps to FU_12_U.
  - The novelty walk (800 decisions from `cp42/00493_FU_00_U.walk`) did not solve it.
- Mikasa keys:
  - Bytes 0x110 (party A's key: keyhole 1 / 2 in MI_02_U ev 3) and 0x111 (party B's key: MI_09_U / MI_13_U).
  - The doors open from the key positions.
- Todo lab 2: byte 0x33b is written in TD_00 / 16 / 21 / 22.
- `GetFieldData(0x26, a)` (FIELD.BIN 0x4fc418):
  - mode = a & 0xff, b = (a >> 8) & 0xff, field = (a >> 16) & 0xff.
  - mode 0: `0x3ba9e0(0x53, -1)` (count of RegDat table 0x53). mode 1: `0x3b9540(0x2d, b, -1)`. mode 2: record `0x3b9540(0x53, b, -1)` → field by the jump table at 0x610b70.
  - The fields: 0 = +6 & 7, 1 = u16 +0x10, 2 = s16 +0x12, 3 = s8 +0x16, 4 = s16 +0x14, 5 = u32 +8, 6 = u32 +0xc, 7 = s8 +0x17, 8 = u32 +0x18. Check the order against the table before implementing.
  - Not implemented yet.

**In progress when paused:** the first `--search 1500` from `cp42/00493_FU_00_U.walk` (Mt. Fuji). It had expanded 280 states (397 distinct, about 1 s per state, about 340 MB) and found nothing yet when it was stopped.

**Exact next steps (as of the pause; superseded by Status):**
1. Rerun the Fuji search with a bigger budget, preferably from `cp42/03234_FU_06_U.walk` (it holds all 3 crystals at one point; check with `--regs 0x15f,0x160,0x161,0x162,0x163,0x164`), or from FU_00 with `--search 4000`. If the state count explodes, mask noise bytes in `state_key` (diff two sibling states to find them).
2. Mikasa: `story_walk --load <OLD>/cp34/00009_MI_02_U.walk --search 3000` (goal 0x3f).
3. Todo lab 2: `--load <OLD>/cp40/00240_TD_22_U.walk --search 3000` (goal 0x47).
4. Then a full second-half walk with `--search-on-stall 2000` from the Fuji result, then the first-half branch 0x18..0x1c (ND_14_U via Nemeton's stone-sled menu: the ND_06 / ND_07 Select loop).
5. GetFieldData(0x26), SetSceneInit 7 / 9..13 (`<OLD>/ssi_full.txt` has the MIPS), the shooting range presses, the coverage rerun.

**Paths:**
- `<OLD>` = `%TEMP%\claude\C--Users-jamie-Documents-SH2-Sh2-Decomp\cdb345cf-8b06-46bf-bd5a-4ebc033e3db5\scratchpad\fs`: the round-5 checkpoints cp8..cp42.
- New work: `...\scratchpad\fs2`.
  - `env.sh`: env + `CARGO_BUILD_JOBS=10`.
  - `chain/`: the second-half checkpoints (see Status) and `td_22_u_power.walk`; `mi_plan*.txt`, `td_plan.txt`: probe plans.
  - `sync.sh`: a private build copy of the tree, `git archive HEAD` + my crates. Used while sh2_battle did not compile; the main tree compiles again now.
  - `msc/`: dumped map scripts.
- Target dir: `%USERPROFILE%\.cache\sh2-r6-fs2` (release, for the walker).

No lock files held; Ghidra not switched (still SLUS_210.41).
