# PINE runtime validation (OUTLINE phase 6) -- first pass, 2026-10-09

Crate: `port/crates/sh2_pine` (no Bevy; client + typed readers + `dump` / `record` / `replay` examples + `tests/validate_jp.rs`).
Raw captures: `notes/integration/pine_dumps/*.txt` (hex dumps as printed by the MCP `pine_read_range`, decodable with `sh2_pine::client::Sparse`).

## 0. Environment and limits of this pass

* Emulator: "armsx2" (`PCSX2 8eada3b11a`), PINE slot 28013 (`$TMPDIR/pcsx2.sock.28013`).  `pine_get_info` times out (known), ping/status/read work.
* **PCSX2 serves exactly one PINE client.**  The MCP bridge keeps its connection open for the whole session (lsof: one accepted socket, owned by the
  `mcp-pine` node process), so the Rust client (`Pine::connect_auto`) connects but every request times out (EAGAIN) while an MCP bridge is attached.
  Consequences: (1) the Rust client is tested against a mock PINE server (`client::tests::client_against_mock_server`) and by decoding MCP dumps
  (`Sparse`), not live; (2) all live numbers below were read through the MCP tools (one call at a time, ~1 s each), i.e. only *static or very slow*
  quantities are measurable; per-frame time series need `examples/record` run with the MCP detached.
* Pad injection was not attempted: `CPad::Update` rebuilds `real/press` from the libpad buffer at the start of every frame (system poller), the game
  pollers consume it later in the same frame, so a PINE write lands in the vsync wait and is overwritten before use (success chance ~0).
* No memory was written, no state saved or loaded.
* Which game was running (it changed during the session): at the start the **US retail disc** (SLUS_210.41), sitting on the title/opening
  (`CDMYStage` current, no CField); later the **JP Furokuban demo** (SLPM_602.19) in field `AP_02_U` (entry 0), which stayed idle for 10+ minutes
  (player at (0.64, 0, 1.17), pad idle, a script camera active) -- no walking, no encounter, no ring was ever observed.  Identification: `u32@0x0021f6c0 /
  @0x00221ea0` = `0xfc640000 / 0x27bdffc0` (JP) or `0x27bdffc0 / 0x1460ffed` (US); the first words of the ELF image at 0x200000 are identical in both.

## 1. Addresses found (all verified live unless noted)

| thing | JP | US |
|---|---|---|
| `SSHSys::sys` (ptr) | 0x40ad60 | **0x43fdf8** (gp-0x7bf8, gp = 0x4479f0) |
| `CApp::app` (ptr) | 0x40adfc | **0x43fea0**; `m_scrw/h` +4/+6 = 0x200/0x1c0 ok |
| CApp counters | 0x40ae14.. | **0x43feb8..** (+0x350a4 vs JP; frame counter, GS ticks, ...) |
| `CField*` (`fld`) | 0x40ad94 | **0x43ff34** (`iGpffff8544`); `CFieldSocket*` 0x43fe2c |
| `Sys__7CBattle` (ptr) | 0x40af24 | **0x440000** (`new 0x4920`, ctor 0x45eb00) |
| `ourBtlSocket` | 0x40acac | 0x43fd5c |
| `CPad::m_pCoreArray` | 0x40ac00 | **0x43fca8** |
| libc `rand()` | 0x236220, reent ptr @0x3f8338 | 0x232cc8, reent ptr @0x42d248 (reent = 0x42cf58, state @ **0x42d000**) |
| SSHApi dtors (title/field/battle/gameover) | 0x3a7fa0 / 0x3bda80 / 0x32d860 / 0x3ac140 | 0x415dc0 / 0x3f5710 / 0x3652d0 / 0x3e3f10 |

Live checks: US `sys` -> 0x749500, `+0x28 current` -> CDMYStage (vtbl +8 = 0x415dc0), `+0x34..0x36` = 0, delta 33 ms, `app` -> 0x714640.
JP `sys` -> 0x6b80e0, current api = CFieldSocket (vtbl 0x407680), CField 0x6c3d40 (state +0x28 = 2, entry 0), CFieldCamera 0x6c66d0, ctrl model 0x13e3c70.

### JP layouts confirmed on live data (AP_02_U idle, `pine_dumps/jp_ap02u_idle.txt`)

* SSHSys: `+0x1c` timer ms, `+0x20` delta (16 ms while loading, **33 ms steady state** = the game runs at 30 fps), vtbl +0x14 = 0x407620, SysTool vtbl 0x404ad0 (all as in notes/A/SSHSys.md).
* CField: `+0x28` state = 2, `+0x2a` entry = 0, flag bytes `+0x18c..` = `14 10 0a 00 38 20 20 0f` (b2/b4 of 0x18c set = event mask 5, b4 of 0x18d displayed,
  `0x192` model_count = 0x20, `0x193` scr_camera_active = 0x0f -> script camera), `+0x1b8` floor, `+0x1bc` camera, `+0x1c0` models[0].
  `player_pos` (+0x1cf0) == ctrl model `pos` (+0x10) exactly: (0.6413665, 0, 1.1693826); model rotY (+0x24) = 3.1415927.
* CFieldCamera (0xd0): flags +6 = 5 (enabled|compose), view angle +0x1c/0x20/0x24 = 0.625, transition length +0x18 = 4.0 (set by script; 50 is only the ctor default),
  target +0x30, camera +0x40, blend-from +0x50/+0x60, composed +0x70/+0x80, pitch/yaw/roll +0xc0/0xc4/0xc8 = 354.032 / 359.963 / 0, +0xcc = 1.0 -- identical to notes/G/CFieldCamera.md.
  Note that `CField+0x1cd0 cam_pos` (-0.971,-72.581,-197.231) equals the camera's blend-from vector (+0x60), not the composed one: it is the last CAMEVENT goal,
  stale while the script camera drives the view.
* The port's floor accepts the real player position: `on_floor_chk` true, `on_floor_point` y = 0 (real y = 0), `circle_chk(4.0)` true.
* Pad core (0x6b8270): `assign` table at +0x48 is the identity, everything else 0 (idle).

## 2. Mismatches found

| # | what | real | port before | action |
|---|---|---|---|---|
| 1 | libc `rand()` | `s = s * 6364136223846793005 + 1; return (s >> 32) & 0x7fffffff` (disassembly of JP 0x236220 and US 0x232cc8: `daddiu v1,v0,1`, `dsrl32`, `and 0x7fffffff`); state is a u64 at `reent+0xa8`, `srand(s)` stores `s as u32` | `sh2_battle::rules::Lcg` used the MMIX increment 1442695040888963407 and `>> 33` -> different sequence for any seed | **fixed** in `rules.rs` (`Lcg` is now the game's generator; 68 battle tests green). Not fixed (other owners): `sh2_field::sim` / `host.rs` use their own 31-bit LCG (1103515245), `sh2_battle::host.rs` 1664525, `plugin.rs` ring seed uses MMIX -- they should call `Lcg` / `sh2_pine::game::rand_next`. Live confirmation of the sequence (two readings of the state a known number of `rand()` calls apart) is still open: the state did not change while the game idled (JP 0x2f50296d95d7bbd3 @0x3f80f0, US 0x735140310b709607 @0x42d000). |
| 2 | US `BtlChr` stride | **0x510** (CBattle ctor 0x45eb00 loops `+= 0x510` to 0x3d70; `GetTurnInterval` 0x4dfe80, `GetMaxHP` 0x636e90 index `idx*0x510 + 0xb0`); CBattle is 0x4920 bytes | JP 0x4f0 / 0x4660 | documented; `sh2_pine::addr::US_LAYOUT.b_chr_stride`. Inner US offsets (decompiler offsets): char id 0x120 (same), AGL cached **0x13c** (JP 0x12e), LUC **0x13e** (JP 0x130), turn interval **0x190** (JP 0x180), status records **0x1d0** (kind byte; JP 0x1b8+4), MONSTERParam ptr **0x150** (JP 0x148); HP/MP/SP/ATK/DEF block not located (somewhere inside the 0xe-byte shift between 0x122 and 0x13c). `sh2_battle::structs::chr` is JP-only; a retail battle bridge needs a US table. |
| 3 | US `CField` flag bytes | 0x178..0x18b (repacked; notes/G_retail/CField.md) | `sh2_pine::addr::US_LAYOUT` uses them | none needed |

## 3. Experiments: what could and could not be done

| experiment | status |
|---|---|
| (a) field movement / collision / speeds | **not measurable** (player never moved).  The port constants are already `WALK_SPEED = 0.30`, `RUN_SPEED = 0.83` per 60 Hz tick (= 18 / 50 units per second); `OUTLINE`/`final_status.md` still say 1.6/3.2 (stale).  Indirect evidence: one stale NPC model seen before the field reloaded had `last_trans` (+0x40) = (0, 0, -0.594) per game frame; at the steady-state 33 ms frame that is 18.0 units/s = exactly 0.30 x 60 (walk root track 16.8 units / 28 motion frames at 30 fps).  Caveat: the frame delta at that instant was not read (it is 16 ms while loading), so this is a plausibility check, not a measurement. |
| (b) camera vs `eval_camera` | **not comparable**: AP_02_U was under a script camera (`+0x193 != 0`).  Port rail camera for the real player position: pos (-0.59,-52.2,-140.7), real script camera pos (-0.575,-50.69,-112.456): same x/y family, 28 units apart in z, expected for a script override.  Needs a free-roaming sample (see below). |
| (c) battle (turn order, damage, HP deltas, MONSET roll) | **not observable** (no encounter; the demo was idle in a cutscene).  Readers exist (`read_battle`, JP layout; US partial). |
| (d) Judgement Ring | **not observable.**  `read_jring` (JP layout, `JRTop` 0x40ac8c) is ready; US `JRTop` not located yet. |

## 4. What the user needs to do for the real comparison

1. Detach the MCP PINE bridge (or run the tools from a session without it) so `sh2_pine` can own the socket, then
   `cargo run -p sh2_pine --example dump -- --watch` (live) or `--example record -- rec.csv --hz 60 --seconds 120` (time series).
2. JP demo: advance AP_02_U to free control (the cutscene must end; or load a save in a field), walk straight with the d-pad (walk, then run with X held),
   walk into a wall, cross a camera boundary.  Then `SH2_DISC_DIR=<JP> cargo run -p sh2_pine --example replay -- rec.csv AP_02_U` prints the per-sample position error
   of `FieldSim` fed the same d-pad input; the `trans` / `delta_ms` / `frames` columns give the true per-tick speed.
3. Trigger a random encounter or the tutorial battle with `--only battle,rand` running: gives HP deltas, turn timers (`+0x184` decompiler offsets) and consecutive
   `rand()` states (check them with `game::rand_steps`), then the ring (`--only jring`: period, area angles).
4. Same for the US disc (title is not enough: a field or battle must be live); `US_GLOBALS` / `US_LAYOUT` already cover sys, app, CField, camera, models, pad, rand.
