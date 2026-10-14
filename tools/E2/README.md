# tools/E2 (effects, round 4)

* `mipsemu.py` -- a tiny straight-line MIPS (R5900 subset) emulator over an EE ELF (`SLUS_210.41`): `lui/ori/addiu/lw/sw/lq/sq/lwc1/swc1/mtc1/...`, branches with delay slots, `jal` handled by a hook.
  Written because the Ghidra decompiler times out on huge compiler-unrolled functions (`FpRetailMote207::CreateObjects` is 0x84dc bytes).
* `extract_mote207.py` -- runs `CreateObjects(variant)` of US 0x002cfbe0 for variants 0..5, hooks `FVector` copy-ctor 0x00222f00 / `__nw` / the object ctor 0x002d8120 / `SetData` 0x002d8290 and prints the 69 volumes
  (`corner, range, velmax, count`); the output is `sh2_gfx/src/effects/mote207.rs` tables `V0..V5`.  `SH2_US_DISC_DIR` must point at the US disc; run from this directory (`python3 extract_mote207.py`, writes `mote207.json`).
