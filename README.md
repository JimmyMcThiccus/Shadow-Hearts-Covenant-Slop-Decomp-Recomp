# Shadow Hearts: Covenant (SH2) decompilation and Rust/Bevy port

A decompilation of *Shadow Hearts II* / *Shadow Hearts: Covenant* (PS2) and a native Rust/Bevy reimplementation built from it.

The Japanese demo executable `SLPM_602.19` ships with a full symbol table. It is the main source for names, class layouts and the call graph, and those names are carried over to the stripped US retail build `SLUS_210.41`, which is what the port targets.

**This repository contains no game data.** You need your own copy of the game. Extract the disc contents to folders on disk (see [WINDOWS_SETUP.md](WINDOWS_SETUP.md)).

## Layout

| Path | Contents |
|---|---|
| `docs/` | [OUTLINE.md](docs/OUTLINE.md) (architecture and project plan), [AGENT_BRIEF.md](docs/AGENT_BRIEF.md) (per-section workflow), [SDK_MAP.md](docs/SDK_MAP.md) |
| `decomp/<section>/` | Cleaned-up Ghidra output, one file per class / source file (sections A–I, `G_retail`) |
| `notes/<section>/` | Per-class notes: struct layouts, state machines, JP→US address maps |
| `notes/integration/` | Cross-section port status, coverage ledger, live-vs-port comparisons |
| `symbols/` | Symbol dumps and module maps for the JP demo builds |
| `port/` | Cargo workspace: `sh2_core`, `sh2_formats`, `sh2_gfx`, `sh2_script`, `sh2_menu`, `sh2_field`, `sh2_battle`, `sh2_audio`, `sh2_app`, `sh2_pine` |
| `tools/` | Python helpers for Ghidra matching, decomp generation, coverage and driving PCSX2 live |

## Running the port

Install Rust, extract the discs next to this repo (`../SH2JP`, `../SH2US`, `../disk2extracted`) or set `SH2_DISC_DIR` / `SH2_US_DISC_DIR` / `SH2_US_DISC2_DIR`, then run:

```bat
run-us.bat --autoplay --boost 80
```

`run-us.ps1` and `run-us.sh` do the same on PowerShell and macOS/Linux; the `run-jp.*` scripts launch the Japanese demo. [WINDOWS_SETUP.md](WINDOWS_SETUP.md) lists the options and troubleshooting steps.

## License

Licensed under either of [Apache License, Version 2.0](LICENSE-APACHE) or [MIT license](LICENSE-MIT) at your option, matching `license = "MIT OR Apache-2.0"` in `port/Cargo.toml`.

*Shadow Hearts* and its code, text, graphics and audio belong to their respective rights holders. This license covers the project's own work and grants no rights to the original game.
