# Field script `WaitModel` held for 25 s (AP_02_U opening) -- fixed 2026-10-19

Symptom: after the free-control start of AP_02_U (Karin / Nicolai), the first dialogue only opened ~28 s later (tick 1690 instead of ~240).
Found with `SH2_FIELD_OPS=1` (new: logs every field sub-function call with args and tick, plus motion / WaitModel diagnostics): the start job calls
`SetMotion(1, 23, 0)`, `SetMotion(1, 24, 1)`, `SetMotion(1, 25, 1)` (Nicolai `lk_a` / `lk_b` / `lk_c`) then `WaitModel(1)` and sleeps.

Cause (`plugin.rs` "real motion lengths" stage): a finite script motion is held until the *model* reports it ended, with a 1500 tick safety cap.
Nicolai's model has only `lk_c`; the script-side chain therefore waited for a model motion that never played (or already had ended, its `finished` flag lasting
a single frame), so only the 25 s cap released it.

Fix: `CharacterModel::ended` remembers the name of the last motion that ended; the script motion is held only while the model plays that very motion
and is released when it ends; otherwise the script's own clock (`DEFAULT_MOTION_TICKS`) counts it down. A warning is logged if the 25 s cap is ever reached
(`field <map>: script motion ... still held after 25 s`) so other maps with the same problem show up in logs.
Result: the dialogue starts at tick 239.
