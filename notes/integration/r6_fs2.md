# Round 6 FS2: story to the end, field scripts

## Status (2026-10-15, after the coordinator pause)

**Chapters reached (story flags set by walks, union with round 5):**
- First half: 28 of 34 (unchanged: 0x08 and 0x18..0x1c missing).
- Second half: **22 of 26** (was 14): new this round 0x4c Mt. Fuji, 0x4e Inugami 2, 0x4f Foreign cemetery 2, 0x50 Azabu mansion,
  0x51 Inugami 3, 0x52 Queen's garden, 0x53 Wales 3, 0x54 Inugami 4 -- all played (Fuji by the puzzle search, the rest by the novelty
  walk with `--search-on-stall`), and the walk then enters the last dungeon (`AI_05_U` -> `AI_00_U` "Vessel"; its own search: 416
  states, closed, see below).  Missing: 0x41 Mikasa 2, 0x4d Graveyard 2, 0x55 Last dungeon -- **no script references these three flags
  at all** (`flag_xref --flags`: no set / clr / chk with a constant; the same holds for 0x08 and 0x19), so they are probably debug-menu
  chapter markers that the story never sets.  0x47 (Todo lab 2) is set by hand (`--flags 0x47`) and not counted; 0x3f is now played
  (Mikasa plan below, no more `--goto MI_16_U`).
- Hidden: 0 of 6.

**Second-half chain** (checkpoints in `fs2/chain/`, resume with `story_walk --load F [--goto MAP:ENTRY]`):
`1_post4e_00037_IN_04_U` (Fuji search result) -> `2_post4f_AP_02_A` (+ `--goto KA_09_U:0`) -> `3_post51_IN_02_U` (+ `--goto QG_14_U:0`)
-> `4_post53_WE_00_U` -> `5_post54_IN_00_U` -> `6_last_dungeon_AI_00_U`.  Logs: `fs2/fu5.err`, `w1.err`, `w2a.err`, `w3a.err`,
`w4a.err`, `w5.err`, `ai1.err`.

**This session:**
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

**Open puzzles:**
- Todo lab 2 (0x47), from `fs2/chain/td_22_u_power.walk` (moved out of `tests/walk`, no test uses it yet): the search (world map off)
  closes after 419 states in 70 s.  Probed route (`walk_probe`, register byte 0x33b): TD_22_U examine box 5 (beat the guards, 1 -> 2),
  examine box 1 -> TD_00_U, enter box 8 ("You're Stag Team", 2 -> 3), examine box 1 -> TD_21_U (-> 4), examine box 1 -> TD_16_U (the
  experiment, -> 5, back in TD_21_U), the elevator (TD_21_U examine box 0) "power is off", examine box 2 -> TD_15_U (robot room: Evasion
  Down 3 / Thera Root; examine box 4 sets 0x325 bit 0x10), examine box 1 -> TD_02_U = "wrong way" dead end.  The walkthrough (lparchive
  update 91, "Escaping the Lab") goes TD_15 "exit on the lower level" -> Dragonsword chest room -> shooting range -> galleries -> Kato's
  lab -> stairs B7..1 -> lobby -> Hojo boss.  TD_15_U enter boxes 2 / 3 do nothing for the walker: probably the lower-level exit needs
  the player on the lower floor (height) -- check how `Action::Enter` places the player against the box's floor.
- Last dungeon (`AI_00_U` Vessel): the search from `6_last_dungeon_AI_00_U` without the world map closes after 416 states (AI_00 / 01 /
  05, GY_05_F).  Walkthrough (lparchive update 135, "Inside the Vessel"): each floor's altar has a **ring that is turned** to line up
  colours (floor 2: match the second ring with green in front; floor 3: yellow then green; floor 4: yellow -> blue, then green), which
  moves the light elevators; the Seventh Key / Crucifix chests, then the light elevator to Kato and the final question (top choice =
  good ending).  The walker tries only two answers of the first two prompts, so the ring turns (AI_01_U look 0x1 ev 70, 3 answers,
  probably repeated) need a `walk_probe` session and a plan like Mikasa's.  0x55 itself is never set by a script.

**Next steps:**
1. Todo lab 2: the TD_15_U lower exit (above), then a plan file like Mikasa's; drop the `--flags 0x47` skip.
2. Vessel ring puzzle with `walk_probe` + a plan (the route above), then ED_00_U from the walk.
3. First half 0x18..0x1c (ND_14_U via Nemeton's stone sled; the ND_07 / ND_09 search explodes with the world map on -- use
   `--search-world 0`, and the walkthrough for the sled).
4. `SetSceneInit` 10 (key items / skill bits of record 1, 0x003be870) and 11 (the stash list) on the retail-shaped save.

**Files (this session):** `sh2_field/src/story.rs` (plan, world-map choice, area hint, queue cap, `minigame_press`, `wm_seen` init),
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
