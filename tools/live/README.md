# Live PCSX2 capture tools (Windows)

Written 2026-10-13 against the PCSX2 build with the DebugServer (port 21512, newline-delimited JSON) and PINE (28011).

* `dbg.py`  - second DebugServer client (the pcsx2 MCP keeps PINE, but the DebugServer accepts extra clients): `Dbg().mem(addr, n)` ~0.08 ms per read, so a whole `BtlChr` (0x510 bytes) can be sampled several times per 30 Hz game frame.
* `keys.py` - posts WM_KEYDOWN/UP to the PCSX2 window (works unfocused). Pad = keyboard: K cross, L circle, I triangle, J square, Return start, WASD left stick, arrows d-pad. **Hold >= 0.12 s**: the game reads the pad once per 30 Hz frame and a 60 ms tap is missed.
* `grab.py` - PrintWindow screenshot of the emulator window (25 ms per frame after the first). Needs per-process DPI awareness (`SetProcessDpiAwarenessContext(-4)`) or only the upper-left corner is captured.
* `rec3.py` - example recorder: loads nothing, taps Attack/target, then a Judgement Ring bot reads the live pointer angle and presses Cross inside each area, sampling `CBattle`, `BtlChr` 1 and 2, the ring and the game timer into a pickle (+ frames). Addresses are for save slot 7 of the 2026-10-13 session (CBattle 0xAFFA20, ring 0x11718b0); re-derive them after any other state.
* `fight.py <seconds>` - plays a whole battle: taps Attack + target at each command menu, finds the ring through `[CBattle+0x45d0]` and presses inside every area, clicks through the result screens (`CBattle*` is read from `[0x440000]`).  Does not answer tutorial prompts ("Battle Basics", "Combos": Down + Cross = Skip).
* `watch.py <seconds>` - passive: logs `SSHSys` request / next-map / monset changes with a screenshot (a field door does not touch them).
* `snapmem.py` - whole-RAM dump helper for diffing while walking.
* `sheet.py` - contact sheet of the grabbed frames with the battle phase burnt in.
* `cap.ps1` - one-shot window capture.

Do NOT set EE breakpoints / watchpoints while driving the game: setting one (recompiler reset) and then pressing a key froze the VM once (PC stuck at one instruction, state loads ignored until PCSX2 was restarted). Sampling memory with `Dbg` never needed a pause.
