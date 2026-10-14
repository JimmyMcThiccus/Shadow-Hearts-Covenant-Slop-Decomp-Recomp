# CPad / CPadMan / CAnalogStick / CVibe / CVibeMan (JP 0x22fef0..0x231b20, 0x3b86e0..0x3bbcec; US 0x22c9a0.., 0x3f0100..)

See header comment of `port/crates/sh2_core/src/pad.rs` for the full layouts (structs CPad 0x18, CPadCore 0x98, CPadMan 0x1c8, CAnalogStick 0x10, CVibeMan 0x2bc created in Ghidra).
* `CPad::m_pCoreArray[2]` 0x40ac00; `CPad` handles are linked into the core's active list (`Enable/Disable`), `GetActive(port)` = list head.
* `CPad::Update` modes (`CPad+8`): 1 = if no d-pad bit pressed, stick direction sets d-pad bits else d-pad drives the stick; 2 = stick direction replaces d-pad bits, idle stick synthesised from d-pad.
* Dead zone: centre 0x80, threshold 0x30 (values `x-0xaf` / `-0x30-(x-0x80)`), gauge = |v|/80, angle via acos.
* Repeat: `delay=30`, `on=1`, `off=5` (CPad+0xc/+0x10/+0x14). Default assign table (identity) at 0x3fda90.
* `CPadMan` state machine (CLibpad): 1 disconnected -> 2 CheckVibration -> 3 InitVibration -> 4 wait -> 5 CheckActuator -> 6 InitActuator -> 7 wait -> 8 CheckPressMode -> 9 InitPressMode -> 10 wait -> 0xb stable. `Read` inverts button bytes (active low) and forces sticks to 0x80 unless term id 5/7.
* CVibeMan: see vibe.rs; flags +0x24 (mode b0-1, pause b2-3, registered b4, fading b5), strength = `(maxLevel*master)>>6` clamped 255, half mode `>>7`, mute count; output bytes `[small, large]` -> `CPad::SetActDirect(port)`.
* CVibe (0x44): sequencer (Polling 0xaec, key on/off envelopes, `CnvSeqData` text -> binary `_ActSeqHdr`).
