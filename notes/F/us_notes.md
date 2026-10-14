# US (SLUS_210.41) porting notes, section F

Method (the plugin's `bulk_fuzzy_match` ignores `filter` and gives false positives, so it was only used as a hint):
1. opcode/register signature of every JP function (immediates, jal targets masked) vs every US function (`tools/F` scratch,
   see `us_map.txt` header);
2. unique long signatures give 2,018 monotonic anchors across the exe; a function is accepted only when its signature is
   identical **and** its US address equals JP + the delta of the neighbouring anchors;
3. 8 more by SequenceMatcher >= 0.85 at the interpolated address.
Result: **474 / 825** section-F functions matched, **441 renamed** in SLUS_210.41 (33 were already named identically by other
sections -- a cross-check). Matched: the whole widget toolkit (MenuObj..MenuWindow*, Cursor, MenuGroup, ScrollMark, MenuFlare, ...).
**Not matched (changed in retail)**: `dataAccess`, `deviceChecker`, `dispSaveFile/Time/Cash`, `openingMessage/openingBattleDemo`
(retail moves the title into the new `OPENING.BIN` overlay), `SaveDeviceHDD` (no HDD in the US build), `CFieldSaveData`,
most of `BtlSaveSec` (retail rebalancing), `MenuModelManeger`, parts of `MenuSound/MenuModelPack/SaveMenuSection`.
Positions are in `notes/F/us_map.txt` (`jp us name score`).
