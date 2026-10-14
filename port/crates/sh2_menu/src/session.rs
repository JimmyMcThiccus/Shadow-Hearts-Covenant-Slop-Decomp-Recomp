//! The running game's persistent state (what the original keeps in `ourBtlSaveDat`, `CFieldSaveData`, `SaveMenuSection`) and the
//! file-backed save device.
//!
//! * [`GameSession`] owns a [`SaveFile`] (BTL0 + FLDa + MENU sections) as the single source of truth for party, cash and the script
//!   register file, plus runtime-only bits (current map, the saved character position used when returning from a battle).
//! * [`FileStorage`] implements [`SaveStorage`] on a directory in the user's data dir (`SH2_SAVE_DIR` overrides), using the same file
//!   names as the memory-card layout (`BISLPM-00000-SH2/SH2-000`).

use std::path::{Path, PathBuf};

use crate::btlsave::{LevelRow, LevelTable};
use crate::save::{folder_name, SaveFile, SystemFile, PC_COUNT, PC_REC_SIZE};
use crate::storage::{DeviceStatus, SaveManager, SaveStorage, StorageError};

/// `ChrPosSave` (JP FIELD.BIN `ChrPosSave*`, table of 8-byte saved positions): where the player stood when a battle started.
#[derive(Debug, Clone, PartialEq)]
pub struct ChrPos {
    pub map: String,
    pub pos: [f32; 3],
    /// heading in radians (game convention: 0 = +z, clockwise)
    pub yaw: f32,
}

/// Number of script registers kept in the `RG` chunk of the field save (`CScript` register file, 0x200 words).
pub const SCRIPT_REGS: usize = 0x200;

#[derive(bevy::prelude::Resource)]
pub struct GameSession {
    pub save: SaveFile,
    /// current field map (`GS+0x10`)
    pub map: String,
    pub chr_pos: Option<ChrPos>,
    /// script register file (persisted into `RG`)
    pub regs: Vec<u32>,
    pub play_ms: u64,
    /// `New Game` was chosen and the party has not been created yet (done by the battle plugin, which owns `SSHDAT`)
    pub needs_party_init: bool,
    /// a game is in progress (set when leaving the title)
    pub in_game: bool,
    /// one-line status shown by the overlay ("Saved to slot 0")
    pub toast: Option<(String, f32)>,
    /// cumulative field steps (units walked), used by tests/notes
    pub distance: f32,
    /// number of battles won (stat for the notes / autoplay)
    pub battles_won: u32,
    /// `SSHSys` bytes the field scripts read (retail `+0x54..+0x57`, JP `+0x50..+0x53`; added by round 5 FS): `[0]` how the map was
    /// entered (1 map jump, 2 back from a battle), `[1]` result of the last battle (1 won, 0 lost but the story goes on, 0xff escaped),
    /// `[2]` `SetFieldData(8)` "a defeat does not end the game" for the next battle
    pub ssh_sys: [u8; 4],
}

impl Default for GameSession {
    fn default() -> Self {
        GameSession {
            save: SaveFile::new_default(),
            map: String::new(),
            chr_pos: None,
            regs: vec![0; SCRIPT_REGS],
            play_ms: 0,
            needs_party_init: false,
            in_game: false,
            toast: None,
            distance: 0.0,
            battles_won: 0,
            ssh_sys: [0; 4],
        }
    }
}

impl GameSession {
    /// Title menu "start game": fresh save block, party creation deferred (`SaveMenuSection::SceneInit` + `BtlSaveSec::SetSceneInit`).
    pub fn new_game(&mut self, first_map: &str) {
        *self = GameSession { map: first_map.to_string(), needs_party_init: true, in_game: true, ..Default::default() };
        if self.save.build.is_retail() {
            // `SetSceneInit` rows the demo-shaped bag arrays cannot hold: key items, obtained bit sets, misc flag words
            for (kind, value, index) in retail_scene_rows(0) {
                if (5..=10).contains(&kind) {
                    self.save.btl.apply_scene_row(kind, index as usize, value);
                }
            }
        }
        // dev: start with story flags set (`SH2_STORY_FLAGS`, see `story_flags`)
        crate::story_flags::apply_env(&mut self.regs);
    }

    /// Party of the current set in battle order: PC ids (`PartySet::members`, first `battle_count` entries).
    pub fn battle_party(&self) -> Vec<u8> {
        let Some(set) = self.save.menu.party_set(self.save.menu.current_set_index().min(4)) else { return vec![] };
        let n = (set.battle_count.max(0) as usize).min(4);
        set.members[..n].iter().copied().filter(|&m| (m as usize) < PC_COUNT).collect()
    }

    /// All party members (`member_count`).
    pub fn all_members(&self) -> Vec<u8> {
        let Some(set) = self.save.menu.party_set(self.save.menu.current_set_index().min(4)) else { return vec![] };
        set.members[..(set.member_count.max(0) as usize).min(8)].iter().copied().filter(|&m| (m as usize) < PC_COUNT).collect()
    }

    /// Display name of party member `id`: the saved name (Shift-JIS), else a stand-in (the demo's `SSHMES` only names PCs 0..2).
    pub fn pc_name(&self, id: u8) -> String {
        let n = self.save.btl.pc(id as usize).map(|r| crate::sjis::decode(&r.name)).unwrap_or_default();
        let n = n.trim().to_string();
        if !n.is_empty() {
            return n;
        }
        match id {
            5 => "Yuri".to_string(),
            _ => format!("PC{id}"),
        }
    }

    pub fn cash(&self) -> u32 {
        self.save.menu.cash(self.save.btl.scenario())
    }

    pub fn add_cash(&mut self, n: i32) {
        let sc = self.save.btl.scenario();
        let c = (self.save.menu.cash(sc) as i64 + n as i64).clamp(0, crate::save::MenuSave::MAX_CASH as i64) as u32;
        self.save.menu.set_cash(sc, c);
    }

    /// Flush runtime state into the save sections (what `SaveScriptRegister`, `GetFieldGS` and the play-time counter do before a save).
    pub fn sync_to_save(&mut self) {
        // play time
        let ms = self.play_ms.min(u32::MAX as u64) as u32;
        self.save.menu.data[crate::save::MenuSave::OFF_PLAYTIME_MS..crate::save::MenuSave::OFF_PLAYTIME_MS + 4].copy_from_slice(&ms.to_le_bytes());
        // GS: current map at +0x10, saved character position at +0x48
        if let Some(gs) = self.save.field.find_mut(crate::save::FieldSave::TAG_GS) {
            let p = &mut gs.payload;
            let name = self.map.as_bytes();
            let (o, n) = (0x10 - 4, 0x10);
            p[o..o + n].fill(0);
            let l = name.len().min(n - 1);
            p[o..o + l].copy_from_slice(&name[..l]);
            if let Some(cp) = &self.chr_pos {
                for (k, v) in cp.pos.iter().enumerate() {
                    p[0x48 - 4 + k * 2..0x48 - 4 + k * 2 + 2].copy_from_slice(&(*v as i16).to_le_bytes());
                }
                let facing = ((cp.yaw.to_degrees().rem_euclid(360.0)) / 360.0 * 256.0) as i16 + 1;
                p[0x4e - 4..0x4e - 4 + 2].copy_from_slice(&facing.to_le_bytes());
            }
        }
        // RG: script registers at +0x10
        if let Some(rg) = self.save.field.find_mut(crate::save::FieldSave::TAG_RG) {
            let base = 0x10 - 4;
            for (i, w) in self.regs.iter().enumerate() {
                let o = base + i * 4;
                if o + 4 > rg.payload.len() {
                    break;
                }
                rg.payload[o..o + 4].copy_from_slice(&w.to_le_bytes());
            }
        }
    }

    /// Inverse of [`sync_to_save`] after a load.
    pub fn sync_from_save(&mut self) {
        let regs = self.save.field.script_registers();
        if !regs.is_empty() {
            self.regs = regs;
            self.regs.resize(SCRIPT_REGS, 0);
        }
        self.map = self.save.field.current_map().unwrap_or_default();
        self.play_ms = self.save.menu.play_time_ms() as u64;
        self.chr_pos = None;
        self.needs_party_init = false;
        self.in_game = true;
    }

    /// Initialise party member `pc` from the `PC_I` record (`BtlSaveSec::InitPCParam(pc, difficulty)`, JP 0x0037f0b0):
    /// `pc_i` = 0x1c byte record of SSHDAT section 0..3, `name` = Shift-JIS name (SSHMES section 0..3, 18 bytes).
    pub fn init_pc(&mut self, pc: usize, pc_i: &[u8], name: &[u8], tbl: &dyn LevelTable) {
        if pc >= PC_COUNT || pc_i.len() < 0x1c {
            return;
        }
        let mut rec = [0u8; PC_REC_SIZE];
        rec[0] = 3; // present | joined (SetSceneInit sets both bits)
        rec[2] = pc_i[0];
        // model numbers: u16 at +4 copied to all three slots (+0x4/+0x6/+0x8 of the record)
        for k in 0..3 {
            rec[4 + k * 2] = pc_i[4];
            rec[5 + k * 2] = pc_i[5];
        }
        let n = name.iter().position(|&b| b == 0).unwrap_or(name.len()).min(0x11);
        rec[0x0a..0x0a + n].copy_from_slice(&name[..n]);
        // equipment / skills: PC_I[8..=0x14] -> record 0x2d..=0x39
        rec[0x2d..0x3a].copy_from_slice(&pc_i[8..0x15]);
        rec[0x3a..0x3c].copy_from_slice(&pc_i[0x18..0x1a]);
        if sh2_core::boot::is_retail() {
            self.retail_pc_fields(pc, pc_i, &mut rec);
        }
        let parsed = crate::save::PcRec::parse(&rec);
        self.save.btl.set_pc(pc, &parsed);
        self.save.btl.pc_level_init(pc, pc_i[6].max(1), tbl);
    }

    /// Retail `FUN_003bfbe0` (US `BtlSaveSec::PCInit`) record details that differ from the demo layout, verified against the live save of a new
    /// game (Karin `2b 00 05 01 ...` / Nicolai `33 00 0b 02 ...`, notes/integration/pine_us_refinement.md): the flag byte carries the class bits of
    /// `PC_I[7]` (bits 2-4 = `b7 & 7`, bits 5-7 = `(b7 >> 3) & 7`), `+0x3a` is empty, the `PC_I[0x18..0x1c]` word moves to `+0x6c`, `+0x5c` mirrors
    /// the low three bits of `PC_I[0x15]` twice, `+0x68` is -1 and a few characters start with growth caps in `+0x40..0x50`.
    fn retail_pc_fields(&mut self, pc: usize, pc_i: &[u8], rec: &mut [u8; PC_REC_SIZE]) {
        let b7 = pc_i[7];
        rec[0] = 3 | ((b7 & 7) << 2) | (((b7 >> 3) & 7) << 5);
        rec[0x3a] = 0;
        rec[0x3b] = 0;
        rec[0x6c..0x70].copy_from_slice(&pc_i[0x18..0x1c]);
        let t = pc_i[0x15] & 7;
        rec[0x5c] = t | (t << 3);
        rec[0x68] = 0xff;
        self.save.btl.init_pc_slots(pc);
        let mut put = |off: usize, v: u16| rec[off..off + 2].copy_from_slice(&v.to_le_bytes());
        match pc {
            0 => {
                put(0x4a, 1000);
                put(0x4e, 2000);
            }
            1 => put(0x48, 2000),
            4 => {
                put(0x42, 2000);
                put(0x4c, 2000);
                put(0x4e, 4000);
            }
            5 => put(0x40, 1000),
            6 => put(0x48, 2000),
            7 => {
                put(0x40, 2000);
                put(0x48, 4000);
            }
            _ => {}
        }
    }

    /// Put `ids` into party set 0 (`SaveMenuSection::JoinParty`) and make it current.
    pub fn set_party(&mut self, ids: &[u8]) {
        let mut set = self.save.menu.party_set(0).unwrap();
        set.member_count = 0;
        set.members = [0xff; 8];
        for &id in ids {
            set.join(id);
            if self.save.build.is_retail() {
                self.save.menu.set_joined(id); // `JoinParty` also sets the joined bit at MENU+0x82
            }
        }
        set.battle_count = ids.len().min(4) as i8;
        self.save.menu.set_party_set(0, &set);
        self.save.menu.data[crate::save::MenuSave::OFF_CUR_SET] = 0;
    }
}

/// `SCEN` rows `(kind, value, index)` of scene `scene` from the retail `sshdat.na` on the disc named by `SH2_DISC_DIR`
/// (`GetRegDat(0x47, scene)` = `SetSceneInit`'s start-of-chapter table).  Empty when the retail disc is not available.
pub fn retail_scene_rows(scene: usize) -> Vec<(u8, u8, u16)> {
    match std::env::var_os("SH2_DISC_DIR") {
        Some(dir) => retail_scene_rows_from(Path::new(&dir), scene),
        None => vec![],
    }
}

/// [`retail_scene_rows`] from an explicit disc folder.
pub fn retail_scene_rows_from(dir: &Path, scene: usize) -> Vec<(u8, u8, u16)> {
    use sh2_core::fileio::Disc;
    let Ok(disc) = Disc::open(dir) else { return vec![] };
    let (Some(dat), Some(mes)) = (disc.read_opt("common/sshdat.na"), disc.read_opt("common/sshmes.na")) else { return vec![] };
    let Some(db) = sh2_core::regdat::UsRegDat::new(&mes, &dat) else { return vec![] };
    let n = db.count(sh2_core::regdat::US_KIND_SCEN, scene).unwrap_or(0).min(256);
    (0..n)
        .filter_map(|i| db.record(sh2_core::regdat::US_KIND_SCEN, scene, i as i32 + 1))
        .map(|r| (r[0], r[1], u16::from_le_bytes([r[2], r[3]])))
        .collect()
}

/// A [`LevelTable`] backed by decoded `PC_L` rows (index = `pc`, then `level - 1`).
pub struct RowTable {
    pub rows: Vec<Vec<LevelRow>>,
}

impl LevelTable for RowTable {
    fn row(&self, pc: usize, level: u8) -> Option<LevelRow> {
        self.rows.get(pc)?.get(level.checked_sub(1)? as usize).copied()
    }
}

/// `SSHMES.JPN` ("reg1"): sections of 18-byte Shift-JIS names (`RegDatApi::GetRegDat` name tables).
/// Sections: 0..3 PC names per difficulty, 8 monsters, 9 weapons, 10 armor, 11 accessories, 12 items.
pub struct NameDb {
    raw: Vec<u8>,
    secs: Vec<(usize, usize)>,
}

impl NameDb {
    pub fn parse(raw: Vec<u8>) -> Result<Self, &'static str> {
        if raw.len() < 8 {
            return Err("short");
        }
        let count = u32::from_le_bytes(raw[0..4].try_into().unwrap()) as usize;
        let total = (u32::from_le_bytes(raw[4..8].try_into().unwrap()) as usize).min(raw.len());
        if raw.len() < 8 + count * 8 {
            return Err("short table");
        }
        let offs: Vec<usize> = (0..count).map(|i| u32::from_le_bytes(raw[8 + i * 8 + 4..8 + i * 8 + 8].try_into().unwrap()) as usize).collect();
        let mut secs = Vec::new();
        for i in 0..count {
            let end = offs.get(i + 1).copied().unwrap_or(total);
            if offs[i] > end || end > raw.len() {
                return Err("bad range");
            }
            secs.push((offs[i], end - offs[i]));
        }
        Ok(NameDb { raw, secs })
    }
    /// raw bytes of record `idx` of section `sec` (18 bytes)
    pub fn record(&self, sec: usize, idx: usize) -> Option<&[u8]> {
        let (o, l) = *self.secs.get(sec)?;
        if (idx + 1) * 18 > l {
            return None;
        }
        self.raw.get(o + idx * 18..o + (idx + 1) * 18)
    }
    pub fn name(&self, sec: usize, idx: usize) -> String {
        self.record(sec, idx).map(crate::sjis::decode).unwrap_or_default()
    }
    pub fn count(&self, sec: usize) -> usize {
        self.secs.get(sec).map(|s| s.1 / 18).unwrap_or(0)
    }
}

// ----------------------------------------------------------------------------------------------------------------
// file-backed save device
// ----------------------------------------------------------------------------------------------------------------

/// Env vars that mark a run as a development / unattended run (screenshots, scripted drivers, forced unlocks): such runs must not touch the player's
/// real save folder.
pub const DEV_ENV: &[&str] = &[
    "SH2_MENU_DEV",
    "SH2_DRIVE",
    "SH2_CUTSCENE_SHOTS",
    "SH2_AUTOPLAY_DEBUG",
    "SH2_THEATER_UNLOCK",
    "SH2_UI_PROBE",
    "SH2_DEV",
    "SH2_STORY_FLAGS",
];
/// Command line flags that mark a development run (`sh2_app --autoplay --shots dir`).
pub const DEV_ARGS: &[&str] = &["--autoplay", "--shots", "--dev"];

/// `true` for an unattended / development run: any of [`DEV_ENV`] set or any of [`DEV_ARGS`] on the command line.  `SH2_REAL_SAVES=1` overrides.
pub fn is_dev_run() -> bool {
    DEV_ENV.iter().any(|k| std::env::var_os(k).is_some()) || std::env::args().any(|a| DEV_ARGS.contains(&a.as_str()))
}

/// The player's real save directory: the platform user data dir (`~/Library/Application Support/sh2_port` on macOS, `$XDG_DATA_HOME` or
/// `~/.local/share` elsewhere, `%APPDATA%` on Windows).
pub fn real_save_dir() -> PathBuf {
    let home = std::env::var_os("HOME").map(PathBuf::from);
    let base = if cfg!(target_os = "macos") {
        home.map(|h| h.join("Library").join("Application Support"))
    } else if cfg!(target_os = "windows") {
        std::env::var_os("APPDATA").map(PathBuf::from)
    } else {
        std::env::var_os("XDG_DATA_HOME").map(PathBuf::from).or_else(|| home.map(|h| h.join(".local").join("share")))
    };
    base.unwrap_or_else(|| PathBuf::from(".")).join("sh2_port")
}

/// Throw-away save directory of development runs (`<tmp>/sh2_port_dev_saves`).
pub fn dev_save_dir() -> PathBuf {
    std::env::temp_dir().join("sh2_port_dev_saves")
}

/// Pure choice of the save directory (see [`default_save_dir`]).
pub fn choose_save_dir(explicit: Option<PathBuf>, real_saves: bool, dev: bool) -> PathBuf {
    if let Some(d) = explicit {
        return d;
    }
    if dev && !real_saves {
        dev_save_dir()
    } else {
        real_save_dir()
    }
}

/// Directory used for saves: `$SH2_SAVE_DIR` if set; otherwise the real user data dir ([`real_save_dir`]) for a normal run, but a throw-away directory
/// ([`dev_save_dir`]) for a development run ([`is_dev_run`]) unless `SH2_REAL_SAVES=1` asks for the real one.  (The dev tours used to write `SH2-00n`
/// into the player's real `BASLUS-21041-SH2` folder.)
pub fn default_save_dir() -> PathBuf {
    choose_save_dir(std::env::var_os("SH2_SAVE_DIR").map(PathBuf::from), std::env::var_os("SH2_REAL_SAVES").is_some_and(|v| v != "0"), is_dev_run())
}

/// `SaveDevice` of the port.  JP / tests: a plain directory (the "memory card folder" `BISLPM-00000-SH2` is a sub directory; the system file has the same name as
/// the folder, like on the card).  **Retail** ([`FileStorage::default_dir`]): the saves are written to a **PS2 memory-card image of the port's own**
/// (`<save dir>/mcd_sh2_port.ps2`, real card layout with FAT, directory entries and ECC, see [`crate::memcard`]) that PCSX2 / ARMSX2 can mount; the first write seeds its
/// `BASLUS-21041-SH2` folder with the slots the real game made on the emulator card.  Reads look in the port card, then the loose files of older port saves, then the
/// emulator card (read-only).
pub struct FileStorage {
    root: PathBuf,
    /// read-only fallback: a real PS2 memory-card image that holds this build's save folder (US retail only, see [`FileStorage::default_dir`])
    card: Option<crate::memcard::MemCardStorage>,
    /// the card image the port writes to (retail): its own `mcd_sh2_port.ps2`, or -- only with `SH2_MEMCARD_WRITE=1` -- the emulator's card itself
    port_card: Option<crate::memcard::MemCardStorage>,
}

impl FileStorage {
    pub fn new(root: impl Into<PathBuf>) -> Self {
        FileStorage { root: root.into(), card: None, port_card: None }
    }
    /// The save directory (see [`default_save_dir`]); on the retail build the saves go to the port's card image and a PS2 memory-card image with a
    /// `BASLUS-21041-SH2` save (`SH2_MEMCARD`, else the default ARMSX2 / PCSX2 card `Mcd001.ps2`) is attached as a read-only fallback, so **Continue loads a save made
    /// by the real game**.  Environment: `SH2_NO_MEMCARD=1` ignores the emulator card (development runs ignore it too unless `SH2_MEMCARD=<path>` is set), `SH2_SAVE_FILES=1` keeps the old loose-file layout, `SH2_MEMCARD_WRITE=1` writes into
    /// the emulator's own card image (do not do that while the emulator is running: it keeps the image in memory and would overwrite the changes).
    pub fn default_dir() -> Self {
        let mut s = Self::new(default_save_dir());
        if sh2_core::boot::is_retail() {
            // a development run is hermetic: it only looks at the emulator card when `SH2_MEMCARD` / `SH2_REAL_SAVES` ask for it
            let hermetic = is_dev_run() && std::env::var_os("SH2_MEMCARD").is_none() && std::env::var_os("SH2_REAL_SAVES").is_none();
            if std::env::var_os("SH2_NO_MEMCARD").is_none() && !hermetic {
                if let Some(card) = crate::memcard::MemCardStorage::find(folder_name()) {
                    log::info!("save: reading the memory card image {}", card.path.display());
                    s.card = Some(card);
                }
            }
            if std::env::var_os("SH2_SAVE_FILES").is_none() {
                let write_emulator = std::env::var_os("SH2_MEMCARD_WRITE").is_some_and(|v| v != "0");
                if let (true, Some(card)) = (write_emulator, s.card.as_ref()) {
                    s.port_card = crate::memcard::MemCardStorage::open_rw(card.path.clone(), folder_name());
                    log::warn!("save: WRITING into the emulator's memory card image {}", card.path.display());
                }
                if s.port_card.is_none() {
                    let p = s.root.join("mcd_sh2_port.ps2");
                    log::info!("save: port memory card image {}", p.display());
                    s.port_card = Some(crate::memcard::MemCardStorage::open_or_new(p, folder_name()));
                }
            }
        }
        s
    }
    /// Attach a memory-card image as the read-only fallback.
    pub fn with_card(mut self, card: crate::memcard::MemCardStorage) -> Self {
        self.card = Some(card);
        self
    }
    /// Write to this (writable) memory-card image instead of loose files.
    pub fn with_port_card(mut self, card: crate::memcard::MemCardStorage) -> Self {
        self.port_card = Some(card);
        self
    }
    pub fn card_path(&self) -> Option<&Path> {
        self.card.as_ref().map(|c| c.path.as_path())
    }
    /// Path of the card image the port writes to (retail), if any.
    pub fn port_card_path(&self) -> Option<&Path> {
        self.port_card.as_ref().map(|c| c.path.as_path())
    }
    pub fn root(&self) -> &Path {
        &self.root
    }
    fn folder(&self) -> PathBuf {
        self.root.join(folder_name())
    }
    fn io(e: std::io::Error) -> StorageError {
        if e.kind() == std::io::ErrorKind::NotFound {
            StorageError::NotFound
        } else {
            StorageError::Io(e.to_string())
        }
    }
    /// Make sure the port card has its save folder: seeded with the emulator card's files (the slots the real game made) or created with `icon.sys` / `SH2.ICO`.
    fn ensure_port_folder(&mut self) -> Result<(), StorageError> {
        let Some(pc) = self.port_card.as_mut() else { return Ok(()) };
        if pc.folder_exists() {
            return Ok(());
        }
        match self.card.as_mut() {
            Some(emu) if !std::ptr::eq(emu as *const _, pc as *const _) => {
                let n = pc.import_folder(emu)?;
                log::info!("save: seeded the port card with {n} files from {}", emu.path.display());
                Ok(())
            }
            _ => pc.create_system(),
        }
    }
}

impl SaveStorage for FileStorage {
    fn status(&self) -> DeviceStatus {
        DeviceStatus::Formatted
    }
    fn free_kb(&self) -> u32 {
        match &self.port_card {
            Some(c) => c.free_kb(),
            None => 1024 * 1024,
        }
    }
    fn format(&mut self) -> Result<(), StorageError> {
        let _ = std::fs::remove_dir_all(self.folder());
        match self.port_card.as_mut() {
            Some(c) => c.format(),
            None => Ok(()),
        }
    }
    fn create_system(&mut self) -> Result<(), StorageError> {
        if self.port_card.is_some() {
            return self.ensure_port_folder();
        }
        std::fs::create_dir_all(self.folder()).map_err(Self::io)?;
        std::fs::write(self.folder().join(folder_name()), SystemFile::new_empty().to_bytes()).map_err(Self::io)?;
        std::fs::write(self.folder().join("icon.sys"), crate::memcard::RETAIL_ICON_SYS).map_err(Self::io)
    }
    fn has_folder(&self) -> bool {
        self.port_card.as_ref().is_some_and(|c| c.folder_exists()) || self.folder().join(folder_name()).is_file() || self.card.is_some()
    }
    fn read(&mut self, name: &str) -> Result<Vec<u8>, StorageError> {
        if let Some(pc) = self.port_card.as_mut() {
            if let Ok(d) = pc.read(name) {
                return Ok(d);
            }
        }
        match std::fs::read(self.folder().join(name)) {
            Err(e) if e.kind() == std::io::ErrorKind::NotFound => match self.card.as_mut() {
                Some(c) => c.read(name),
                None => Err(StorageError::NotFound),
            },
            r => r.map_err(Self::io),
        }
    }
    fn write(&mut self, name: &str, data: &[u8]) -> Result<(), StorageError> {
        if self.port_card.is_some() {
            self.ensure_port_folder()?;
            return self.port_card.as_mut().unwrap().write(name, data);
        }
        std::fs::create_dir_all(self.folder()).map_err(Self::io)?;
        // write-then-rename so a crash never leaves a half written slot
        let tmp = self.folder().join(format!("{name}.tmp"));
        std::fs::write(&tmp, data).map_err(Self::io)?;
        std::fs::rename(&tmp, self.folder().join(name)).map_err(Self::io)
    }
    fn delete(&mut self, name: &str) -> Result<(), StorageError> {
        if let Some(pc) = self.port_card.as_mut() {
            if pc.read(name).is_ok() {
                return pc.delete(name);
            }
        }
        std::fs::remove_file(self.folder().join(name)).map_err(Self::io)
    }
}

/// Save the session to `slot` on `dev` (`SaveData::Save`).
pub fn save_session(dev: &mut dyn SaveStorage, session: &mut GameSession, slot: u8) -> Result<(), StorageError> {
    session.sync_to_save();
    let mut mgr = SaveManager::open(dev)?;
    let loc = session.map.as_bytes().to_vec();
    let common = mgr.system.common;
    mgr.save(dev, slot, &session.save, &loc, &common)
}

/// Load `slot` into the session (`SaveData::Load`).
pub fn load_session(dev: &mut dyn SaveStorage, session: &mut GameSession, slot: u8) -> Result<(), StorageError> {
    let mut mgr = SaveManager::open(dev)?;
    let file = mgr.load(dev, slot)?;
    session.save = file;
    session.sync_from_save();
    Ok(())
}

/// Is slot `slot` used on `dev`?
pub fn slot_used(dev: &mut dyn SaveStorage, slot: u8) -> bool {
    SaveManager::open(dev).map(|m| m.system.slots.get(slot as usize).map(|s| s.used).unwrap_or(false)).unwrap_or(false)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn tmpdir(tag: &str) -> PathBuf {
        let d = std::env::temp_dir().join(format!("sh2_port_test_{tag}_{}", std::process::id()));
        let _ = std::fs::remove_dir_all(&d);
        d
    }

    #[test]
    fn dev_runs_do_not_use_the_real_save_dir() {
        let explicit = Some(PathBuf::from("/x/y"));
        assert_eq!(choose_save_dir(explicit.clone(), false, true), PathBuf::from("/x/y"), "SH2_SAVE_DIR always wins");
        assert_eq!(choose_save_dir(None, false, true), dev_save_dir(), "a development run gets the throw-away directory");
        assert_eq!(choose_save_dir(None, true, true), real_save_dir(), "SH2_REAL_SAVES=1 asks for the real one");
        assert_eq!(choose_save_dir(None, false, false), real_save_dir(), "a normal run keeps the real directory");
        assert_ne!(dev_save_dir(), real_save_dir());
    }

    #[test]
    fn file_storage_roundtrip() {
        let dir = tmpdir("save");
        let mut dev = FileStorage::new(&dir);
        let mut s = GameSession::default();
        s.new_game("AP_00_U");
        s.needs_party_init = false;
        s.add_cash(1234);
        s.regs[7] = 0xdead;
        s.map = "AP_02_U".into();
        s.play_ms = 61_000;
        assert!(!slot_used(&mut dev, 0));
        save_session(&mut dev, &mut s, 0).unwrap();
        assert!(slot_used(&mut dev, 0));
        let mut t = GameSession::default();
        load_session(&mut dev, &mut t, 0).unwrap();
        assert_eq!(t.cash(), 1234);
        assert_eq!(t.regs[7], 0xdead);
        assert_eq!(t.map, "AP_02_U");
        assert_eq!(t.play_ms, 61_000);
        let _ = std::fs::remove_dir_all(&dir);
    }

    /// The retail new game (`SetSceneInit(0)`) reproduces the key items and starting bag of a real save, byte for byte where modelled.
    #[test]
    fn retail_new_game_matches_real_save() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let rows = retail_scene_rows_from(Path::new(&dir), 0);
        assert!(!rows.is_empty());
        let mut f = SaveFile::new_default_for(crate::save::Build::Retail);
        for (kind, value, index) in rows {
            f.btl.apply_scene_row(kind, index as usize, value);
        }
        let real = SaveFile::parse(include_bytes!("../tests/fixtures/us_card_SH2-000")).unwrap();
        for k in 0..0x40 {
            assert_eq!(f.btl.key_item(k), real.btl.key_item(k), "key item {k}");
        }
        assert_eq!(f.btl.bag(), real.btl.bag());
    }

    #[test]
    fn party_set_and_pc_init() {
        let mut s = GameSession::default();
        s.new_game("AP_00_U");
        // default party of MenuSave::new_default is {0xb, 5}
        assert_eq!(s.battle_party(), vec![0xb, 5]);
        s.set_party(&[5, 0]);
        assert_eq!(s.battle_party(), vec![5, 0]);
        let tbl = RowTable { rows: vec![vec![]; 12] };
        let mut pc_i = [0u8; 0x1c];
        pc_i[0] = 1;
        pc_i[6] = 1;
        pc_i[8] = 4;
        s.init_pc(5, &pc_i, b"Yuri\0", &tbl);
        let p = s.save.btl.pc(5).unwrap();
        assert!(p.present() && p.joined());
        assert_eq!(p.name_lossy(), "Yuri");
        assert_eq!(p.weapon, 4);
    }
}
