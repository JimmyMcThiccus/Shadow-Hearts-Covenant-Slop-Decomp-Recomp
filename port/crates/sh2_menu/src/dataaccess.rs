//! `dataAccess` — the Save / Load / device-check screen state machine (and `deviceChecker`).
//!
//! JP: `dataAccess::Polling` 0x003922d0 (states 0..0x1d), `mInitialDeviceCheck` 0x003976a0 (boot-time
//! device check, states 0..0x16), `deviceChecker` 0x003990f0..0x00399d60.
//!
//! The original draws with `primWin`/`primCursor` (section B) and talks to `SaveData` asynchronously.
//! The port keeps the *state numbers and transitions* (so notes/F/dataAccess.md cross references stay
//! valid) but performs device I/O synchronously through [`SaveStorage`] and reports UI work to the host
//! as [`UiCmd`]s.

use crate::save::{SaveFile, SlotInfo, SLOT_COUNT};
use crate::storage::{DeviceKind, DeviceStatus, SaveManager, SaveStorage, StorageError};

/// `dataAccess::ACCESSMODE`
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum AccessMode {
    Save = 0,
    Load = 1,
    /// boot-time check of the memory cards / HDD (`mInitialDeviceCheck`)
    InitialCheck = 2,
}

/// Callback event code (`dataAccess+0x180`, passed to the creator's callback with its user arg).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Event {
    /// 0: background texture arrived, scene is being built
    BackgroundReady = 0,
    /// 1: first fade-in finished, input is live
    Shown = 1,
    /// 2: initial check: nothing usable / user dismissed
    NoSaveDevice = 2,
    /// 3: initial check: a device with save data was found; also "game saved" for mode Save
    SaveFound = 3,
    /// 4: screen finished; the object can be destroyed
    Finished = 4,
    /// 5: a slot was loaded (`SaveData` now holds it)
    Loaded = 5,
    /// 6: initial check needs the UI (switches the display mode in `openingMessage`)
    NeedUi = 6,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct Input {
    pub ok: bool,
    pub cancel: bool,
    pub up: bool,
    pub down: bool,
    pub left: bool,
    pub right: bool,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub enum Warning {
    /// `dataMess_deviceWarning_J`: could not use the device
    Device(DeviceKind),
    /// nothing is inserted in that slot (`initialMess_noDevice`: "No memory card (8MB) ... in MEMORY CARD slot 2.")
    NoDevice(DeviceKind),
    /// `SaveData::Save / Load` failed (`dataMess_saveFailed / overwriteFailed / loadFailed`)
    OpFailed { save: bool, overwrite: bool, kind: DeviceKind },
    /// `dataMess_systemWarning_J`: system file bad
    System(DeviceKind),
    /// `dataMess_deviceUnformat_J`
    Unformatted(DeviceKind),
    /// `dataMess_deviceNoSaveData_J` (load with nothing saved)
    NoSaveData(DeviceKind),
    /// `initialMess_deviceExistSaveData_J`: save data folder already exists while creating the system file
    SaveDataExists(DeviceKind),
    /// `dataMess_saveWarning_J`: not enough free space (< 99 KB)
    NotEnoughSpace,
    FormatFailed,
}

/// Work for the host UI layer (replaces the `primWin`/`primCursor` calls of the original).
#[derive(Clone, Debug, PartialEq)]
pub enum UiCmd {
    ShowBackground,
    HideAll,
    ShowDeviceSelect { choices: Vec<DeviceKind>, selected: usize },
    ShowFileList { slots: Vec<SlotInfo>, empty_greyed: Vec<bool>, selected: usize },
    ScrollFileList { up: bool, selected: usize },
    ShowQuery { save: bool, slot: usize },
    ShowProgress { percent: u32 },
    ShowWarning(Warning),
    ShowDone { save: bool },
    ShowFormatQuery,
    /// `mSetupQuit` (state 0x1a): "Go back without saving / loading?" Yes / No
    ShowQuit { save: bool },
    Se(SeKind),
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum SeKind {
    Move = 0,
    Decide = 2,
    Cancel = 3,
    Buzzer = 4,
    Complete = 0x1000,
}

/// What the screen needs from the game.
pub trait DataAccessHost {
    fn device(&mut self, kind: DeviceKind) -> Option<&mut dyn SaveStorage>;
    fn ui(&mut self, cmd: UiCmd);
    /// current game state (mode Save)
    fn current_save(&mut self) -> SaveFile;
    fn location_name(&self) -> Vec<u8>;
    fn common_block(&self) -> [u8; 0x100];
    /// a slot was loaded (mode Load): replace the live `BtlSaveSec`/`CFieldSaveData`/`SaveMenuSection`
    fn apply_loaded(&mut self, file: SaveFile, system_common: [u8; 0x100]);
    fn event(&mut self, e: Event);
}

/// `deviceChecker` result for one device.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct DeviceReport {
    pub kind: DeviceKind,
    pub status: DeviceStatus,
    pub has_save: bool,
    pub free_kb: u32,
}

/// JP: `deviceChecker::mCheckAll` — poll all devices once.
pub fn check_all(host: &mut dyn DataAccessHost) -> Vec<DeviceReport> {
    let mut out = Vec::new();
    for kind in [DeviceKind::Mc1, DeviceKind::Mc2, DeviceKind::Hdd] {
        if let Some(d) = host.device(kind) {
            let status = d.status();
            let has_save = status == DeviceStatus::Formatted && d.has_folder() && SaveManager::open(d).map(|m| m.system.first_used_slot().is_some()).unwrap_or(false);
            out.push(DeviceReport { kind, status, has_save, free_kb: d.free_kb() });
        }
    }
    out
}

impl DeviceReport {
    pub fn active(&self) -> bool {
        self.status != DeviceStatus::NoDevice
    }
}

/// Minimum free space for a new save (JP: `mCheckFreeArea` -> `free > 0x62` KB).
pub const MIN_FREE_KB: u32 = 0x63;

pub struct DataAccess {
    pub mode: AccessMode,
    /// JP +0x160
    pub state: u32,
    /// JP +0x164
    pub next_state: u32,
    /// JP `mInitialDeviceCheck` state (+0x150)
    pub check_state: u32,
    /// +0x80: selected device / menu row
    pub device_sel: usize,
    pub dev_kind: DeviceKind,
    pub cur_slot: usize,
    /// slots greyed out because they're empty (+0xac)
    pub slot_empty: [bool; SLOT_COUNT],
    pub retry: u32,
    pub progress: u32,
    /// answer cursor in the Yes/No query (0 = yes)
    pub query_sel: usize,
    /// frames the progress bar runs before the (synchronous) save / load is performed: the original shows `mGrowProgress` while the card works
    /// (`mSetupProgressSaveLoad` speeds 0.25 .. 2.0 px per frame); the screen sets it, the tests leave it 0
    pub min_progress: u32,
    /// number of device rows of the device select window (JP demo 3: MC1, MC2, HDD; the US retail game has no HDD support: 2)
    pub device_rows: usize,
    mgr: Option<SaveManager>,
    reports: Vec<DeviceReport>,
    /// result of the check: 0 no device, 1 cards but none usable, 2 only HDD, 3 free card available
    pub check_result: u32,
    loaded: Option<SaveFile>,
}

impl DataAccess {
    /// JP: 0x00392050 initialize
    pub fn new(mode: AccessMode) -> Self {
        DataAccess {
            mode,
            state: if mode == AccessMode::InitialCheck { 0 } else { 1 },
            next_state: 0,
            check_state: 0,
            device_sel: 0,
            dev_kind: DeviceKind::Mc1,
            cur_slot: 0,
            slot_empty: [true; SLOT_COUNT],
            retry: 0,
            progress: 0,
            query_sel: 0,
            device_rows: 3,
            min_progress: 0,
            mgr: None,
            reports: Vec::new(),
            check_result: 0,
            loaded: None,
        }
    }

    /// JP: 0x00392210 start — begins the interactive part after the background loaded
    /// (`m_TexRead && start-flag` in state 1).
    pub fn is_finished(&self) -> bool {
        self.state >= 0x1d
    }

    /// One frame. `bg_ready` = the DVD callback delivered the SAVELOAD texture (`m_TexRead`).
    pub fn poll(&mut self, input: Input, bg_ready: bool, host: &mut dyn DataAccessHost) {
        if self.mode == AccessMode::InitialCheck {
            self.poll_initial(input, bg_ready, host);
            return;
        }
        match self.state {
            // 1: wait for the background resource, build the scene
            1 if bg_ready => {
                host.event(Event::BackgroundReady);
                host.ui(UiCmd::ShowBackground);
                self.state = 2;
            }
            // 2: fade done -> input live, go to device selection
            2 => {
                host.event(Event::Shown);
                self.state = 5;
                self.show_device_select(host);
            }
            // 3/4: (re)select device
            3 => {
                host.ui(UiCmd::HideAll);
                self.state = 4;
            }
            4 => {
                self.show_device_select(host);
                self.state = 5;
            }
            // 5: device select
            5 => {
                if input.ok {
                    host.ui(UiCmd::Se(SeKind::Decide));
                    self.retry = 0;
                    self.open_device(host);
                } else if input.cancel {
                    host.ui(UiCmd::Se(SeKind::Cancel));
                    self.state = 0x19;
                } else if input.up || input.down {
                    let n = self.device_rows.max(1);
                    self.device_sel = if input.down { (self.device_sel + 1) % n } else { (self.device_sel + n - 1) % n };
                    host.ui(UiCmd::Se(SeKind::Move));
                    self.show_device_select(host);
                }
            }
            // 7: warning popup acknowledged -> next_state
            7 => {
                if input.ok || input.cancel {
                    host.ui(UiCmd::HideAll);
                    self.state = self.next_state;
                }
            }
            // 8: re-open after a failed read (up to 3 tries)
            8 => self.open_device(host),
            // 9/10: unformatted device: offer format
            9 => {
                host.ui(UiCmd::ShowFormatQuery);
                self.state = 10;
            }
            10 => {
                if input.cancel {
                    host.ui(UiCmd::Se(SeKind::Cancel));
                    self.state = 0x19;
                } else if input.ok {
                    host.ui(UiCmd::Se(SeKind::Decide));
                    if self.device_sel == 0 {
                        // format
                        let kind = self.dev_kind;
                        let r = host.device(kind).map(|d| d.format());
                        match r {
                            Some(Ok(())) => {
                                self.state = 0xd; // JP 0xb..: "formatted" done -> done window
                                host.ui(UiCmd::ShowProgress { percent: 100 });
                                self.state = 0xd;
                            }
                            _ => {
                                host.ui(UiCmd::ShowWarning(Warning::FormatFailed));
                                self.state = 7;
                                self.next_state = 0x19;
                            }
                        }
                    } else {
                        self.state = 0x19;
                    }
                }
            }
            // 0xd: format finished window
            0xd => {
                if input.ok {
                    host.ui(UiCmd::Se(SeKind::Decide));
                    self.state = if self.mode == AccessMode::Load { 0x19 } else { 0xe };
                }
            }
            // 0xe: build file list
            0xe => {
                host.ui(UiCmd::ShowFileList { slots: self.slot_infos(), empty_greyed: self.slot_empty.to_vec(), selected: self.cur_slot });
                self.state = 0xf;
            }
            // 0xf: file select
            0xf => self.poll_file_select(input, host),
            // 0x10/0x11: list scroll animation (12 ticks), then back to 0xf
            0x10 | 0x11 => {
                self.progress += 1;
                if self.progress >= 12 {
                    self.progress = 0;
                    self.state = 0xf;
                }
            }
            // 0x12: wait for save-time info (Save) then show the query
            0x12 => {
                host.ui(UiCmd::ShowQuery { save: self.mode == AccessMode::Save, slot: self.cur_slot });
                // `mSetupQuerySaveLoad`: the cursor starts on the second row ("No")
                self.query_sel = 1;
                self.state = 0x13;
            }
            // 0x13: Yes/No
            0x13 => {
                if input.up || input.down {
                    self.query_sel ^= 1;
                    host.ui(UiCmd::Se(SeKind::Move));
                } else if input.ok && self.query_sel == 0 {
                    host.ui(UiCmd::Se(SeKind::Decide));
                    self.state = 0x14;
                    self.next_state = 0x15;
                    self.progress = 0;
                } else if input.ok || input.cancel {
                    host.ui(UiCmd::Se(if input.ok { SeKind::Decide } else { SeKind::Cancel }));
                    self.state = 0xe;
                }
            }
            // 0x14: fade the query away, then run the operation (0x15)
            0x14 => {
                host.ui(UiCmd::ShowProgress { percent: 0 });
                self.state = self.next_state;
            }
            // 0x15: execute the save/load (after the progress bar has run for `min_progress` frames)
            0x15 => {
                if self.progress < self.min_progress {
                    self.progress += 1;
                    host.ui(UiCmd::ShowProgress { percent: self.progress * 100 / self.min_progress.max(1) });
                } else {
                    self.run_operation(host);
                }
            }
            // 0x16/0x17: warning then back
            0x16 | 0x17 => {
                if input.ok || input.cancel {
                    host.ui(UiCmd::HideAll);
                    self.state = self.next_state;
                }
            }
            // 0x18: "done" window; OK -> fire Saved(3)/Loaded(5)
            0x18 => {
                if input.ok {
                    host.ui(UiCmd::Se(SeKind::Decide));
                    if self.mode == AccessMode::Load {
                        if let Some(f) = self.loaded.take() {
                            let common = self.mgr.as_ref().map(|m| m.system.common).unwrap_or([0; 0x100]);
                            host.apply_loaded(f, common);
                        }
                        host.event(Event::Loaded);
                    } else {
                        host.event(Event::SaveFound);
                    }
                    self.state = 0x1c;
                }
            }
            // 0x19/0x1a/0x1b: quit confirmation ("quit?" -> fade -> callback 3)
            0x19 => {
                host.ui(UiCmd::HideAll);
                self.state = 0x1a;
            }
            0x1a => {
                // `mSetupQuit`: the cursor starts on "No"
                self.query_sel = 1;
                host.ui(UiCmd::ShowQuit { save: self.mode == AccessMode::Save });
                self.state = 0x1b;
            }
            0x1b => {
                if input.up || input.down {
                    self.query_sel ^= 1;
                    host.ui(UiCmd::Se(SeKind::Move));
                } else if input.ok && self.query_sel == 0 {
                    host.ui(UiCmd::Se(SeKind::Decide));
                    host.event(Event::SaveFound);
                    self.state = 0x1c;
                } else if input.ok || input.cancel {
                    host.ui(UiCmd::Se(if input.ok { SeKind::Decide } else { SeKind::Cancel }));
                    self.state = 3;
                }
            }
            // 0x1c: fade out -> release -> 0x1d
            0x1c => {
                host.ui(UiCmd::HideAll);
                self.state = 0x1d;
            }
            // 0x1d: final
            0x1d => {
                host.event(Event::Finished);
                self.state = 0x1e;
            }
            _ => {}
        }
    }

    fn show_device_select(&mut self, host: &mut dyn DataAccessHost) {
        let _ = &host;
        let choices: Vec<DeviceKind> = [DeviceKind::Mc1, DeviceKind::Mc2, DeviceKind::Hdd].into_iter().take(self.device_rows.clamp(1, 3)).collect();
        host.ui(UiCmd::ShowDeviceSelect { choices, selected: self.device_sel });
    }

    fn slot_infos(&self) -> Vec<SlotInfo> {
        self.mgr.as_ref().map(|m| m.system.slots.clone()).unwrap_or_default()
    }

    /// JP: state 6 — open device & system file.
    fn open_device(&mut self, host: &mut dyn DataAccessHost) {
        self.dev_kind = [DeviceKind::Mc1, DeviceKind::Mc2, DeviceKind::Hdd][self.device_sel.min(2)];
        let kind = self.dev_kind;
        let Some(dev) = host.device(kind) else {
            host.ui(UiCmd::ShowWarning(Warning::NoDevice(kind)));
            self.state = 7;
            self.next_state = 0x19;
            return;
        };
        match SaveManager::open(dev) {
            Ok(m) => {
                self.slot_empty = std::array::from_fn(|i| !m.system.slots.get(i).map(|s| s.used).unwrap_or(false));
                let any = self.slot_empty.iter().any(|e| !e);
                self.cur_slot = m.system.slots.iter().position(|s| s.used).unwrap_or(0);
                self.mgr = Some(m);
                if self.mode == AccessMode::Load && !any {
                    host.ui(UiCmd::ShowWarning(Warning::NoSaveData(kind)));
                    self.state = 7;
                    self.next_state = 0x19;
                } else {
                    self.state = 0xe;
                }
            }
            Err(StorageError::Unformatted) => {
                self.retry += 1;
                if self.retry < 3 {
                    self.state = 8;
                } else {
                    host.ui(UiCmd::ShowWarning(Warning::Unformatted(kind)));
                    self.state = 7;
                    if kind != DeviceKind::Hdd {
                        self.next_state = 9;
                    } else {
                        self.next_state = 0x19;
                    }
                }
            }
            Err(_) => {
                host.ui(UiCmd::ShowWarning(Warning::Device(kind)));
                self.state = 7;
                self.next_state = 0x19;
            }
        }
    }

    /// Is slot `i` used (so that saving over it is an overwrite)?
    pub fn slot_used(&self, i: usize) -> bool {
        self.slot_empty.get(i).map(|e| !*e).unwrap_or(false)
    }

    fn poll_file_select(&mut self, input: Input, host: &mut dyn DataAccessHost) {
        if input.cancel {
            host.ui(UiCmd::Se(SeKind::Cancel));
            self.state = 0x19;
        } else if input.ok {
            let empty = self.slot_empty.get(self.cur_slot).copied().unwrap_or(true);
            if self.mode == AccessMode::Load && empty {
                host.ui(UiCmd::Se(SeKind::Buzzer));
            } else if self.mode == AccessMode::Save && host.device(self.dev_kind).map(|d| d.free_kb() < MIN_FREE_KB && empty).unwrap_or(true) {
                host.ui(UiCmd::Se(SeKind::Decide));
                host.ui(UiCmd::ShowWarning(Warning::NotEnoughSpace));
                self.state = 0x16;
                self.next_state = 0x19;
            } else {
                host.ui(UiCmd::Se(SeKind::Decide));
                self.state = 0x12;
            }
        } else if input.down && self.cur_slot + 1 < SLOT_COUNT {
            host.ui(UiCmd::Se(SeKind::Move));
            self.cur_slot += 1;
            host.ui(UiCmd::ScrollFileList { up: false, selected: self.cur_slot });
            self.state = 0x10;
            self.progress = 0;
        } else if input.up && self.cur_slot > 0 {
            host.ui(UiCmd::Se(SeKind::Move));
            self.cur_slot -= 1;
            host.ui(UiCmd::ScrollFileList { up: true, selected: self.cur_slot });
            self.state = 0x11;
            self.progress = 0;
        }
    }

    /// JP: state 0x15 — the `SaveData::Save/Load` call and its completion/failure handling.
    fn run_operation(&mut self, host: &mut dyn DataAccessHost) {
        let kind = self.dev_kind;
        let slot = self.cur_slot as u8;
        let result = (|| -> Result<(), StorageError> {
            let mgr = self.mgr.as_mut().ok_or(StorageError::NoDevice)?;
            match self.mode {
                AccessMode::Save => {
                    let file = host.current_save();
                    let name = host.location_name();
                    let common = host.common_block();
                    let dev = host.device(kind).ok_or(StorageError::NoDevice)?;
                    mgr.save(dev, slot, &file, &name, &common)
                }
                _ => {
                    let dev = host.device(kind).ok_or(StorageError::NoDevice)?;
                    self.loaded = Some(mgr.load(dev, slot)?);
                    Ok(())
                }
            }
        })();
        match result {
            Ok(()) => {
                host.ui(UiCmd::ShowProgress { percent: 100 });
                host.ui(UiCmd::Se(SeKind::Complete));
                host.ui(UiCmd::ShowDone { save: self.mode == AccessMode::Save });
                self.state = 0x18;
            }
            Err(_) => {
                host.ui(UiCmd::ShowWarning(Warning::OpFailed { save: self.mode == AccessMode::Save, overwrite: self.slot_used(self.cur_slot), kind }));
                self.state = 0x17;
                self.next_state = 0x19;
            }
        }
    }

    // ------------------------------------------------------------ initial check

    /// JP: 0x003976a0 mInitialDeviceCheck
    fn poll_initial(&mut self, input: Input, bg_ready: bool, host: &mut dyn DataAccessHost) {
        match self.check_state {
            0 | 2 => {
                // JP case 0 -> checkDeviceAll(); case 2: wait for the poll (synchronous here)
                self.reports = check_all(host);
                let active = self.reports.iter().filter(|r| r.active()).count();
                let saved = self.reports.iter().filter(|r| r.has_save).count();
                let free = self.reports.iter().filter(|r| r.active() && !r.has_save && r.status == DeviceStatus::Formatted).count();
                let only_hdd = self.reports.iter().filter(|r| r.active()).all(|r| r.kind == DeviceKind::Hdd);
                if active == 0 {
                    self.check_result = 0;
                    self.check_state = 5;
                } else if saved != 0 {
                    // 3: a save exists
                    self.check_state = 3;
                } else if free == 0 {
                    self.check_result = if only_hdd { 2 } else { 1 };
                    self.check_state = 5;
                } else {
                    self.check_result = 3;
                    self.check_state = 5;
                }
            }
            3 => {
                host.event(Event::SaveFound);
                self.check_state = 4;
            }
            4 | 7 => {
                self.state = 0x1d; // finished
            }
            5 => {
                if bg_ready {
                    host.event(Event::NeedUi);
                    host.ui(UiCmd::ShowBackground);
                    self.check_state = 6;
                }
            }
            6 => {
                // device-status screen: OK/cancel leave (result 3 = offer to create system file)
                if input.ok || input.cancel {
                    host.ui(UiCmd::Se(if input.ok { SeKind::Decide } else { SeKind::Cancel }));
                    host.event(Event::NoSaveDevice);
                    self.check_state = 7;
                }
            }
            _ => {}
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::storage::MemoryStorage;

    struct Host {
        mc1: MemoryStorage,
        events: Vec<Event>,
        uis: Vec<UiCmd>,
        loaded: Option<SaveFile>,
    }
    impl DataAccessHost for Host {
        fn device(&mut self, k: DeviceKind) -> Option<&mut dyn SaveStorage> {
            (k == DeviceKind::Mc1).then_some(&mut self.mc1 as &mut dyn SaveStorage)
        }
        fn ui(&mut self, c: UiCmd) {
            self.uis.push(c);
        }
        fn current_save(&mut self) -> SaveFile {
            let mut f = SaveFile::new_default();
            f.menu.set_cash(0, 4242);
            f
        }
        fn location_name(&self) -> Vec<u8> {
            b"Tokyo".to_vec()
        }
        fn common_block(&self) -> [u8; 0x100] {
            [1; 0x100]
        }
        fn apply_loaded(&mut self, f: SaveFile, _c: [u8; 0x100]) {
            self.loaded = Some(f);
        }
        fn event(&mut self, e: Event) {
            self.events.push(e);
        }
    }

    fn run(da: &mut DataAccess, host: &mut Host, script: &[Input]) {
        for i in script {
            da.poll(*i, true, host);
            for _ in 0..20 {
                da.poll(Input::default(), true, host);
            }
        }
    }
    fn ok() -> Input {
        Input { ok: true, ..Default::default() }
    }
    fn up() -> Input {
        Input { up: true, ..Default::default() }
    }

    /// The Yes / No query starts on "No": a plain confirm goes back to the file list; "Yes" needs a move first.  Cancelling the screen asks "go back?"
    /// first (default No); only Yes leaves.
    #[test]
    fn queries_default_to_no() {
        let mut host = Host { mc1: MemoryStorage::new(DeviceStatus::Formatted), events: vec![], uis: vec![], loaded: None };
        let mut da = DataAccess::new(AccessMode::Save);
        run(&mut da, &mut host, &[Input::default(), Input::default(), ok(), ok(), ok()]);
        assert_eq!(da.state, 0xf, "OK on the default \"No\" returns to the file list");
        assert!(!host.events.contains(&Event::SaveFound));
        // cancel -> quit query (default No) -> OK = No -> back to the device select
        run(&mut da, &mut host, &[Input { cancel: true, ..Default::default() }]);
        assert_eq!(da.state, 0x1b);
        assert!(host.uis.contains(&UiCmd::ShowQuit { save: true }));
        run(&mut da, &mut host, &[ok()]);
        assert_eq!(da.state, 5, "No goes back to the device select");
        run(&mut da, &mut host, &[Input { cancel: true, ..Default::default() }, up(), ok()]);
        assert!(host.events.contains(&Event::SaveFound), "Yes leaves the screen (callback 3)");
    }

    #[test]
    fn save_then_load() {
        let mut host = Host { mc1: MemoryStorage::new(DeviceStatus::Formatted), events: vec![], uis: vec![], loaded: None };
        let mut da = DataAccess::new(AccessMode::Save);
        // bg, shown, device select ok, (open), file ok, query yes, ... done ok
        run(&mut da, &mut host, &[Input::default(), Input::default(), ok(), ok(), up(), ok(), ok(), ok()]);
        assert!(host.events.contains(&Event::SaveFound), "{:?} state {:#x}", host.events, da.state);
        assert!(host.events.contains(&Event::Finished));

        let mut da = DataAccess::new(AccessMode::Load);
        run(&mut da, &mut host, &[Input::default(), Input::default(), ok(), ok(), up(), ok(), ok(), ok()]);
        assert!(host.events.contains(&Event::Loaded), "{:?} state {:#x}", host.events, da.state);
        assert_eq!(host.loaded.as_ref().unwrap().menu.cash(0), 4242);
    }

    #[test]
    fn initial_check_no_device() {
        let mut host = Host { mc1: MemoryStorage::new(DeviceStatus::NoDevice), events: vec![], uis: vec![], loaded: None };
        let mut da = DataAccess::new(AccessMode::InitialCheck);
        for _ in 0..5 {
            da.poll(Input::default(), true, &mut host);
        }
        assert!(host.events.contains(&Event::NeedUi));
        da.poll(ok(), true, &mut host);
        assert!(host.events.contains(&Event::NoSaveDevice));
    }
}
