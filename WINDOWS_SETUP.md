# Windows Setup for Shadow Hearts II Decomp

## Quick Start

### Prerequisites
1. **Rust** - Install from [rustup.rs](https://rustup.rs/)
2. **Game Discs** - Your own `.iso` images of the discs (any file names). Nothing needs extracting:
   - US Retail: Shadow Hearts: Covenant (USA) Disc 1 and Disc 2
   - JP Demo (optional, for `run-jp`): Shadow Hearts II (Japan) Furokuban demo

   Drag the `.iso` files into the `sh2-decomp` folder, next to `run-us.bat`. (A standalone `sh2_app.exe` also finds images placed next to itself.) Git ignores `*.iso`, so they never get committed.

### Running the Port

**For Japanese Demo:**
```batch
run-jp.bat --autoplay
```

**For US Retail:**
```batch
run-us.bat --autoplay --boost 80
```

**PowerShell alternatives:**
```powershell
.\run-jp.ps1 --autoplay
.\run-us.ps1 --us --autoplay
```

### Available Commands

| Script | Description |
|--------|-------------|
| `run-jp.bat --autoplay` | Run JP demo: title → map → battle → field |
| `run-us.bat --autoplay --boost 80` | Run US retail with boost (first encounter is hard) |
| `run-jp.bat --view-map <map_id>` | View a field map (e.g., `--view-map AP_00_U`) |
| `run-jp.bat --view-model <model_id>` | View a 3D model |
| `run-jp.bat --shots <dir>` | Take screenshots during autoplay |

## Configuration

The port finds each disc in this order:
1. The environment variable for that disc, if set: `SH2_DISC_DIR` (JP demo), `SH2_US_DISC_DIR` (US disc 1), `SH2_US_DISC2_DIR` (US disc 2). Each can name an `.iso` image or an extracted disc folder.
2. `.iso` images in the folder named by `SH2_DISCS` (the `run-*` scripts set it to their own folder, `sh2-decomp`).
3. `.iso` images next to `sh2_app.exe`.

Images are identified by their boot executable, so the file names don't matter: `SLPM_602.19` = JP demo, `SLUS_210.41` = US disc 1, `SLUS_210.44` = US disc 2. At startup the port prints a `disc: ...` line for each image it picked up.

Build Cache: `%USERPROFILE%\.cache\sh2-decomp-target`

To use other locations, set the environment variables before running:

**Batch:**
```batch
set SH2_DISCS=C:\Games\PS2
run-us.bat --autoplay
```

**PowerShell:**
```powershell
$env:SH2_US_DISC_DIR = "C:\Games\PS2\Shadow Hearts - Covenant (USA) (Disc 1).iso"
$env:SH2_US_DISC2_DIR = "C:\Games\PS2\Shadow Hearts - Covenant (USA) (Disc 2).iso"
.\run-us.ps1 --autoplay
```

## Troubleshooting

### "Disc not found" errors
Check the `disc: ...` lines the port prints at startup. If a disc is missing, make sure its `.iso` sits next to `run-us.bat` (or next to `sh2_app.exe` when you run the exe directly), or point that disc's variable straight at the image:
```
sh2-decomp\
  run-us.bat
  Shadow Hearts - Covenant (USA) (Disc 1).iso
  Shadow Hearts - Covenant (USA) (Disc 2).iso
```
Images must be plain 2048-byte-sector `.iso` files (the usual PS2 DVD dump format). Compressed formats such as `.chd` or `.cso` need converting to `.iso` first.

### Build errors
Clear and rebuild:
```batch
cd port
cargo clean
cargo build -p sh2_app
```

### Slow initial builds
This is normal. First build caches Bevy dependencies. Subsequent builds will be faster.

## Build Cache

The project uses an off-disk build cache by default to keep build artifacts separate from game data.

## Next Steps

1. **Run the game**: `run-jp.bat --autoplay`
2. **Check the docs**: See `docs/OUTLINE.md` for project architecture
3. **Contribute**: Review the decomp sections (A-H) in `notes/`
