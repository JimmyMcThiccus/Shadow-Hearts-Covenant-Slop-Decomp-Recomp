# US (retail) port status for FIELD.BIN

* `SH2US_FIELD.BIN`: imported (raw, `r5900:LE:32:default`), image base 0x0045ea80 (code from +0x80), analysed: 2180 functions found.
* Method: Ghidra `bulk_fuzzy_match` ignores its `filter` argument and walks the program in address order, so a stand-alone matcher was used instead
  (Python, over the two overlay images + JP symbol table): (A) unique exact match of the register/offset-normalised instruction sequence, (B) global 5-gram Jaccard
  similarity of the opcode skeleton with an inverted index, one-to-one greedy assignment, (C) locality interpolation between confident anchors, (D) call-graph propagation.
* Verification (per coordinator guidance, `bulk_fuzzy_match` is NOT trusted): every candidate pair is checked by (1) JP vs US function body size (Ghidra body sizes), (2) address-order consistency with surrounding exact anchors, (3) for 0.8-0.9 scores or size mismatches a comparison of the decompiled numeric-constant multisets and call counts.
* Result: 852 candidate pairs, **583 verified and renamed** in `SH2US_FIELD.BIN` (the first 583 lines of `us_map.txt`; unverified candidates are listed after the `# CANDIDATES` marker and are not renamed; 48 names that failed verification were reverted to `FUN_xxxxxxxx`).
* Where it works: all menu pages (`Cmd*`), `shop`, `solomon*`, `worldMap*`, `tailor`, `WarpPoint`, `SavePoint`, `FieldMessage`/`FaceImage`, `FVector`/`Matrix` helpers, `CBalIcon`, `FldTimer`...
  The US layout is the JP layout shifted by +0x2e080 (start) growing to +0x52000 (end) in address order; a few classes are moved (e.g. `CmdTop` ctor at 0x470fe0).
* Where it does **not** work: the field core — `CField` (1/201), `CFieldModel` (0/111), `CNaviMap` (0/32), `CFieldBG` (0/24), `CFieldCamera` (0/15), `CFloorMan` (0/9) — the best opcode-skeleton similarity of those functions in the retail binary is below 0.3, i.e. the retail
  build **rewrote** the field engine (and, in the main exe, `CFieldSocket`, `CSTGDB`, `CSndBufCache`, `LayerMan_*`, `ChrPosSave*` — best similarity < 0.3; only `MPSServerHandler`/`MPSModel` match: renamed in `SLUS_210.41`, see end of `us_map.txt`).
  Data formats are however unchanged (SBD 0.11 container, same chunk tags; +`MIRROR`, +`BGCOLOR`; 559 retail maps parse and their floors validate with the JP-derived `FloorMan`).
  Porting the retail field logic therefore needs the retail code decompiled on its own (start from `CField::InitSDB`'s consumers by searching the retail overlay for the 64-bit chunk tag constants, e.g. `0x534f505952544e45` "ENTRYPOS").
* Retail PKB layout is identical to the JP demo's (same PKFINFO.TBL codec; retail `FIELD/MPS` holds 559 `.MPS` + 546 `.MSC` files, FIELD.PKB is 820 MB, `LSD.PKB` 2.3 GB).


## Update (retail pass)
The statement above that the retail build *rewrote* CField/CFieldModel/CNaviMap/CFieldBG/CFieldCamera/CFloorMan/CFieldSocket is superseded: the sources are the same, the JP demo was compiled unoptimised. See `notes/G_retail/README.md` and `notes/G_retail/us_map.txt` for the function map and the genuine differences.
