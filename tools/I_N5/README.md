# tools/I_N5 -- naming pass N5 (retail-new Fp*/Puti* classes, menu scene classes, overlays, Sdrv, SDK leftovers)
Scratch layout used (not committed): `w/` with `dec/{main,jmain,field,jfield,battle_all,jbattle}/<addr>.c` (Ghidra decompiles via GhidraMCP HTTP 127.0.0.1:8089),
`fn_<program>.txt` (list_functions), `ovl_{field,battle,main}/` (copies of the gap-DP scripts of tools/I_N4 + the files below).
* `fetch.py <prog> <addr list> <outdir>`  bulk decompile.   `prep_ovl.py` build us_main.pkl/jp_main.pkl + substitute `func_0xADDR` by main-exe names in overlay decompiles.
* Gap DP (reused from I_N4 `match.py/metrics.py/feat2.py/gapmatch.py`): `gaps.py` (anchors + gaps), `step2.py` (DP pairs, THETA env = acceptance floor 0.3),
  `select_.py` (rules C1/C2/C3/L1/L2), `step3.py` (sandwich: equal-count gaps <=4 between confirmed anchors), `callerev.py` (caller-name overlap, tier G), `apply_.py`, `iterate.sh` (loop until stable).
  Hold-out test `ho.py <K> <R> <noise>`: hides R of every K anchors (and optionally drops JP counterparts) and re-finds them: 613/613 correct pairs on main, 405/408 on FIELD with 50 % of the anchors hidden;
  sandwich rule 85/89; lowering the DP floor to 0.3 with the callee rule keeps 430/433.
* Vtable tools (new): `vtmatch2.py` (JP `__vt__X` <-> US vtable by agreeing named slots, then name the unnamed slot functions; base-class slots only when the US function sits in >=2 vtables),
  `vtover.py` (derived-class overrides get `Method__<DerivedClass>`), `vtthunks.py` (create/name the undefined 8-byte `@N@` this-adjust thunks that sit in secondary vtables),
  `vtscan.py`/`clsgrp.py`/`fieldblock.py` (find retail-new classes by vtable stores; name `ct/dt/CreateScene/UpdateScene/GetReady/Run...` from vtable slots; classes `CmdRetailWinNN/PageNN/SelNN`),
  `fp_spec.py` (the hand-verified spec of the 32 Fp classes), `applyl.py` (rename list applier: skips already-named, duplicate names, conflicts).
* Data scans: `pkb.py` (PKFINFO.TBL name codec/tree), `sbdscan.py` (EFFECT chunk of every SBD in the PKBs: which BG effect types exist where).
* `cov.py` coverage numbers (notes/I/us_coverage.md), `maskid.py`/`audit_sdk.py` relocation-masked machine-code identity checks, `brief.py` compact decompile viewer.
