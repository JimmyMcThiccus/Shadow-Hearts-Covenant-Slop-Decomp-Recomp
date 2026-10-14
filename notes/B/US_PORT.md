# JP -> US function name porting (Section B)

`bulk_fuzzy_match` in this MCP build ignores its `filter` argument and returns noisy matches for small functions, so it was NOT used as the source of truth.
Method instead (reproducible, scripts were in the session scratchpad):
1. `get_bulk_function_hashes` for both programs (position-independent instruction hash, `instruction_count`) + `list_functions` for the US program.
2. Unique-hash pairs, filtered with a longest-increasing-subsequence over US order, give anchors (~1500).
3. Between anchors: sequential alignment on (hash, instruction count): exact hash = score 1.0, equal instruction count = 0.9, within 8% = 0.8.
4. Validation: functions other agents had already named in the US program (ClutAdressControl, Clut, Texture, gTexture, TextureAnim, IPUTexture, ExpansionTexture, UpdatePolBreakState, ...)
   came back with identical names — and the two mismatches found (LightData ctor/dtor were really `List`/`OrderPacket` dtors) were reverted.
Caveat: tiny identical functions (trivial dtors/ctors) can alias; scores 1.0 on <12-instruction functions are order-based.
The retail code in `prim*`, `P2*`, `CScrCapture`, `CineMask`, `P2Filter`, `FontDraw` (parts) was recompiled differently (smaller), so ~48 % of Section B symbols remain unmatched there.
Result: 304 renames in SLUS_210.41 (see us_map.txt: `jp_addr us_addr name score`).
