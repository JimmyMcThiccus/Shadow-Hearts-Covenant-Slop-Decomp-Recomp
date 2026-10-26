# Windows Setup for Shadow Hearts II Decomp

## Quick Start

### Prerequisites
1. **Rust** - Install from [rustup.rs](https://rustup.rs/)
2. **Game Discs** - Extract PS2 disc data to folders:
   - JP Demo: `SH2JP` (Shadow Hearts II Japan demo)
   - US Retail: `SH2US` (Shadow Hearts Covenant USA)

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

By default the scripts look for the extracted discs next to the repo (in its parent folder):
- JP Disc: `..\SH2JP` (`SH2_DISC_DIR`)
- US Disc: `..\SH2US` (`SH2_US_DISC_DIR`)
- US Disc 2: `..\disk2extracted` (`SH2_US_DISC2_DIR`, US scripts only)
- Build Cache: `%USERPROFILE%\.cache\sh2-decomp-target`

To use other locations, set the environment variables before running:

**Batch:**
```batch
set SH2_DISC_DIR=C:\Games\SH2\JP
set SH2_US_DISC_DIR=C:\Games\SH2\US
run-jp.bat --autoplay
```

**PowerShell:**
```powershell
$env:SH2_DISC_DIR = "C:\Games\SH2\JP"
$env:SH2_US_DISC_DIR = "C:\Games\SH2\US"
.\run-jp.ps1 --autoplay
```

## Troubleshooting

### "Disc not found" errors
Ensure the folder structure matches (or point the variables above at your folders):
```
<parent folder>\
  sh2-decomp\        (this repo)
  SH2JP\
    SLPM_602.19
    SYSTEM.CNF
    *.PKB files
  SH2US\
    SLUS_210.41
    SYSTEM.CNF
    *.PKB files
```

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
