# Round 6 FS2: story to the end, field scripts

## Paused (2026-10-14, coordinator: CPU budget, 2 agents at a time)

**Chapters reached so far:** the same as at the end of round 5. Nothing new has been reached yet in round 6.
- First half: 28 of 34 (0x08 and 0x18..0x1c missing).
- Second half: 14 of 26 (0x41, 0x4c..0x55 missing; 0x3f and 0x47 still come from the round-5 hand skips).
- Hidden: 0 of 6.

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

**Exact next steps:**
1. Rerun the Fuji search with a bigger budget, preferably from `cp42/03234_FU_06_U.walk` (it holds all 3 crystals at one point; check with `--regs 0x15f,0x160,0x161,0x162,0x163,0x164`), or from FU_00 with `--search 4000`. If the state count explodes, mask noise bytes in `state_key` (diff two sibling states to find them).
2. Mikasa: `story_walk --load <OLD>/cp34/00009_MI_02_U.walk --search 3000` (goal 0x3f).
3. Todo lab 2: `--load <OLD>/cp40/00240_TD_22_U.walk --search 3000` (goal 0x47).
4. Then a full second-half walk with `--search-on-stall 2000` from the Fuji result, then the first-half branch 0x18..0x1c (ND_14_U via Nemeton's stone-sled menu: the ND_06 / ND_07 Select loop).
5. GetFieldData(0x26), SetSceneInit 7 / 9..13 (`<OLD>/ssi_full.txt` has the MIPS), the shooting range presses, the coverage rerun.

**Paths:**
- `<OLD>` = `%TEMP%\claude\C--Users-jamie-Documents-SH2-Sh2-Decomp\cdb345cf-8b06-46bf-bd5a-4ebc033e3db5\scratchpad\fs`: the round-5 checkpoints cp8..cp42.
- New work: `...\scratchpad\fs2`.
  - `env.sh`: env + `CARGO_BUILD_JOBS=6`.
  - `sync.sh`: a private build copy of the tree, `git archive HEAD` + my crates. Used while sh2_battle did not compile; the main tree compiles again now.
  - `msc/`: dumped map scripts.
- Target dir: `%USERPROFILE%\.cache\sh2-r6-fs2` (release, for the walker).

No lock files held; Ghidra not switched (still SLUS_210.41).
