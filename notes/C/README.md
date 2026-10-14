# Section C notes — models / animation / math

* `model_format.md` — `SSH1.01a` model file (header, frames, atomics, vertex layouts, chunks, textures, bboxes, extension blocks)
* `motion_format.md` — `SQHD` motion file (bone tracks, SVector, event tracks, event names, playback rules)
* `Model.md`, `Frame.md`, `Atomic.md`, `Dynamics.md`, `Math.md`, `Misc.md` — class notes and struct layouts
* `us_map.txt` — JP -> US (SLUS_210.41) function address map
* code: `decomp/C/*.c`; Rust: `port/crates/sh2_formats/src/{math,model,motion,dynamics,pkb}.rs`, `port/crates/sh2_gfx/src/model/*`
* reproduction tools: `tools/C/*.py` (python reference parser + software renderer used to verify the format; point `D` in `ex.py` at the disc folder)
