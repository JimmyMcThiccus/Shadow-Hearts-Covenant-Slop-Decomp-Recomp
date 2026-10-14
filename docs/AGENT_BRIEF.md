# Agent brief — shared instructions for every decompilation section

Read `docs/OUTLINE.md` first. You are decompiling ONE section (given in your task) of Shadow Hearts: Covenant (PS2, Metrowerks C++), using the Japanese demo `SLPM_602.19` which has full symbols, and producing (1) cleaned C, (2) notes, (3) a Rust port into the named crate, (4) name propagation to the stripped US build `SLUS_210.41`.

## Inputs
- `symbols/SLPM_602.19.syms` — `addr size type bind section name`. Grep it for your classes.
- `symbols/classes_by_section.txt`, `symbols/SLPM_602.19_module_map.txt` — address-ordered layout (Metrowerks links each .cpp contiguously, so neighbours in the map are usually the same source file).
- Ghidra MCP tools (`mcp__ghidra__*`). Programs: `SLPM_602.19` (JP main), `SH2JP_FIELD.BIN`, `SH2JP_BATTLE.BIN`, `SLUS_210.41` (US). ALWAYS pass `program=`. Scripting (`run_script_inline`) is disabled — use the regular tools.
- Overlay programs are raw imports rebased to 0x00430A00; code starts 0x80 in. Calls into the main executable show as bare addresses — look them up in the `.syms` file (main section) and create a label with `create_label` so the decompiler shows names.

## Required outputs (write as you go, not at the end)
1. `decomp/<section>/<Class>.c` — Ghidra output cleaned up: real types, struct field names, demangled names in comments, one file per class / source file.
2. `notes/<section>/<Class>.md` — what the class does, struct layout table (offset, type, name), key state machines, which functions call it, open questions.
3. `port/crates/<crate>/src/<module>.rs` — idiomatic Rust translation (not a transliteration): structs with the same fields, free functions → methods, callbacks → trait objects or closures, PS2 hardware calls → a clearly named abstraction (`gfx::`, `io::`, `audio::`) so the Bevy layer can implement them. Each fn gets `// JP: 0x<addr> <mangled>`. Add `pub mod` lines to the crate's `lib.rs`. It must `cargo check` (run `cargo check -p <crate>` from `port/`).
4. Ghidra: create structs for your classes (`create_struct`/`add_struct_field`), apply them to `this` (`set_function_this_type` / `set_function_prototype`), set comments. Then port names to the US build: `bulk_fuzzy_match(source_program="SLPM_602.19", target_program="SLUS_210.41", filter="<class or prefix>", threshold=0.7)` and `rename_function_by_address` on confident matches (score ≥ 0.8, or lower when the neighbourhood ordering confirms it). Record the JP→US address pairs in `notes/<section>/us_map.txt` as `jp_addr us_addr name score`.
5. End your report with: classes done / partially done / untouched, struct layouts recovered, format findings (file formats you decoded), US match count, and blockers.

## Rules
- Work class by class in address order. Decompile with `batch_decompile` (comma-separated names) to save round trips; big functions one at a time.
- Prefer the symbol table's truth over guesses; if a name conflicts with behaviour, keep the name and note it.
- Don't touch other sections' classes except to read them. Shared primitives (FVector, Matrix, BufMemory, CPolObj) belong to section C/A; if you need them before they exist, write a minimal stub in your crate's `compat.rs` and say so.
- `sce*`, libc, libm functions are SDK — do not decompile; map to Rust equivalents in notes.
- Save the Ghidra program (`save_program`) every ~30 renames.
- Do not spawn sub-agents.
