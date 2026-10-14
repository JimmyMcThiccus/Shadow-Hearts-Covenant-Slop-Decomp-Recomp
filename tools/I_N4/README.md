# tools/I_N4 -- naming pass N4 for SLUS_210.41 (scripts as run; paths assume a scratch dir with usdec/, jpdec/, us_now.txt, jp_main.pkl)
Pipeline: `iter.py` (refresh function list -> `setup.py` -> `gaps.py` anchors/gaps -> `fetch3.py` decompiles via GhidraMCP HTTP -> `real2.py` gap DP `gapmatch.py`/`match.py`
+ evidence `metrics.py` + order-bracket stage `stage2.py`) -> `final.py --apply` (rename) -> `stage3.py` + `gapply.py` (caller-name evidence) -> `sig.py`/`sigapply.py`
(relocation-masked machine-code identity) -> `vecapply.py` (VEC FuncTbl id table). `holdout.py`/`diag.py`/`evalstage2.py` hide every 6th anchor and re-find it (precision test).
Needs: JP symbols (`symbols/SLPM_602.19.syms` -> `jp_main.pkl`), Ghidra HTTP API on 127.0.0.1:8089 with programs SLUS_210.41 / SLPM_602.19.
