//! Save device abstraction (`SaveDevice` / `SaveDeviceMC` / `SaveDeviceHDD` / `SaveData` operations).
//!
//! The PS2 code runs a tiny asynchronous state machine over `sceMc*` (see `SaveDeviceMC::Sync` in
//! notes/F/save_format.md). The port exposes a *synchronous* trait; hosts can implement it on top of a
//! directory of files (the layout is `SAVE_FOLDER/<file>`), a memory-card image or cloud storage.

use crate::save::{folder_name, SaveFile, SlotInfo, SystemFile, SLOT_COUNT};
use std::collections::HashMap;

/// Device kinds (`SaveData::Open(short)`): 0 = memory card slot 1, 1 = slot 2, 2 = PS2 HDD.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub enum DeviceKind {
    Mc1,
    Mc2,
    Hdd,
}

impl DeviceKind {
    pub fn from_code(c: i16) -> Option<Self> {
        match c {
            0 => Some(Self::Mc1),
            1 => Some(Self::Mc2),
            2 => Some(Self::Hdd),
            _ => None,
        }
    }
    pub fn code(self) -> i16 {
        match self {
            Self::Mc1 => 0,
            Self::Mc2 => 1,
            Self::Hdd => 2,
        }
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum DeviceStatus {
    /// nothing inserted
    NoDevice,
    /// inserted but not formatted (`SaveDevice+0xc == 0` after `sceMcGetInfo`)
    Unformatted,
    Formatted,
}

/// Name of the file for slot `n` ("SH2-007").
pub fn slot_file_name(n: u8) -> String {
    format!("SH2-{:03}", n)
}

#[derive(Debug, thiserror::Error)]
pub enum StorageError {
    #[error("no device")]
    NoDevice,
    #[error("not formatted")]
    Unformatted,
    #[error("no such file")]
    NotFound,
    #[error("not enough space")]
    Full,
    #[error("io error: {0}")]
    Io(String),
}

/// One opened save device (what `SaveDevice` offers after `Open`).
pub trait SaveStorage {
    fn status(&self) -> DeviceStatus;
    /// Free space in kilobytes (`sceMcGetInfo` free clusters; the UI requires > 0x62 = 98 KB to save).
    fn free_kb(&self) -> u32;
    /// `SaveDeviceMC::Format`
    fn format(&mut self) -> Result<(), StorageError>;
    /// `SaveDevice::CreateSystem` — mkdir + icon.sys + SH2.ICO + empty system file
    fn create_system(&mut self) -> Result<(), StorageError>;
    fn has_folder(&self) -> bool;
    /// whole file inside the save folder (`"BISLPM-00000-SH2"`, `"SH2-003"`, `"icon.sys"`)
    fn read(&mut self, name: &str) -> Result<Vec<u8>, StorageError>;
    fn write(&mut self, name: &str, data: &[u8]) -> Result<(), StorageError>;
    fn delete(&mut self, name: &str) -> Result<(), StorageError>;
}

/// In-memory device for tests and as a reference implementation.
#[derive(Debug, Clone)]
pub struct MemoryStorage {
    pub state: DeviceStatus,
    pub folder: bool,
    pub files: HashMap<String, Vec<u8>>,
    pub capacity_kb: u32,
}

impl MemoryStorage {
    pub fn new(state: DeviceStatus) -> Self {
        MemoryStorage { state, folder: false, files: HashMap::new(), capacity_kb: 8 * 1024 }
    }
}

impl SaveStorage for MemoryStorage {
    fn status(&self) -> DeviceStatus {
        self.state
    }
    fn free_kb(&self) -> u32 {
        let used: usize = self.files.values().map(|v| (v.len() + 1023) / 1024).sum();
        self.capacity_kb.saturating_sub(used as u32)
    }
    fn format(&mut self) -> Result<(), StorageError> {
        self.files.clear();
        self.folder = false;
        self.state = DeviceStatus::Formatted;
        Ok(())
    }
    fn create_system(&mut self) -> Result<(), StorageError> {
        if self.state != DeviceStatus::Formatted {
            return Err(StorageError::Unformatted);
        }
        self.folder = true;
        self.files.insert(folder_name().to_string(), SystemFile::new_empty().to_bytes());
        self.files.insert("icon.sys".to_string(), vec![0; 0x3c4]);
        Ok(())
    }
    fn has_folder(&self) -> bool {
        self.folder
    }
    fn read(&mut self, name: &str) -> Result<Vec<u8>, StorageError> {
        self.files.get(name).cloned().ok_or(StorageError::NotFound)
    }
    fn write(&mut self, name: &str, data: &[u8]) -> Result<(), StorageError> {
        if self.state != DeviceStatus::Formatted || !self.folder {
            return Err(StorageError::NoDevice);
        }
        self.files.insert(name.to_string(), data.to_vec());
        Ok(())
    }
    fn delete(&mut self, name: &str) -> Result<(), StorageError> {
        self.files.remove(name).map(|_| ()).ok_or(StorageError::NotFound)
    }
}

/// `SaveData` front end: save/load/delete a slot and keep the system file's slot table in sync
/// (JP: `SaveData::Save/Load`, `SaveDevice::Save/Load`, `SaveDeviceMC::Sync` op 5/6/7).
pub struct SaveManager {
    pub system: SystemFile,
}

impl SaveManager {
    /// Open a device and read its system file (JP: `SaveDeviceMC::Open` -> op 1 chain).
    pub fn open(dev: &mut dyn SaveStorage) -> Result<Self, StorageError> {
        match dev.status() {
            DeviceStatus::NoDevice => return Err(StorageError::NoDevice),
            DeviceStatus::Unformatted => return Err(StorageError::Unformatted),
            DeviceStatus::Formatted => {}
        }
        if !dev.has_folder() {
            return Ok(SaveManager { system: SystemFile::new_empty() });
        }
        let sys = SystemFile::parse(&dev.read(folder_name())?).map_err(|e| StorageError::Io(e.to_string()))?;
        Ok(SaveManager { system: sys })
    }

    /// JP: `SaveData::Save(slot)` — write the slot file, then the system file with the new `SlotInfo`.
    pub fn save(&mut self, dev: &mut dyn SaveStorage, slot: u8, file: &SaveFile, location_name: &[u8], common: &[u8; 0x100]) -> Result<(), StorageError> {
        if !dev.has_folder() {
            dev.create_system()?;
        }
        let bytes = file.to_bytes();
        dev.write(&slot_file_name(slot), &bytes)?;
        if (slot as usize) < SLOT_COUNT {
            self.system.slots[slot as usize] = SystemFile::build_slot_info(file, location_name);
        }
        self.system.current_slot = slot;
        self.system.common = *common; // StoreCommon
        dev.write(folder_name(), &self.system.to_bytes())
    }

    /// JP: `SaveData::Load(slot)`
    pub fn load(&mut self, dev: &mut dyn SaveStorage, slot: u8) -> Result<SaveFile, StorageError> {
        let d = dev.read(&slot_file_name(slot))?;
        SaveFile::parse(&d).map_err(|e| StorageError::Io(e.to_string()))
    }

    /// JP: `SaveDeviceMC::Delete` — remove the file and mark the slot empty (first byte 0xff).
    pub fn delete(&mut self, dev: &mut dyn SaveStorage, slot: u8) -> Result<(), StorageError> {
        dev.delete(&slot_file_name(slot))?;
        let mut empty = SystemFile::new_empty().slots[0].clone();
        empty.used = false;
        self.system.slots[slot as usize] = empty;
        if slot == self.system.current_slot {
            self.system.current_slot = self.system.first_used_slot().unwrap_or(0);
        }
        dev.write(folder_name(), &self.system.to_bytes())
    }

    pub fn slot_infos(&self) -> &[SlotInfo] {
        &self.system.slots
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn save_load_delete() {
        let mut dev = MemoryStorage::new(DeviceStatus::Formatted);
        let mut mgr = SaveManager::open(&mut dev).unwrap();
        let mut f = SaveFile::new_default();
        f.menu.set_cash(0, 777);
        mgr.save(&mut dev, 2, &f, b"Tokyo", &[7u8; 0x100]).unwrap();
        let mgr2 = SaveManager::open(&mut dev).unwrap();
        assert!(mgr2.system.slots[2].used);
        assert_eq!(mgr2.system.slots[2].cash, 777);
        assert_eq!(mgr2.system.common[0], 7);
        let g = mgr.load(&mut dev, 2).unwrap();
        assert_eq!(g.menu.cash(0), 777);
        mgr.delete(&mut dev, 2).unwrap();
        assert!(!SaveManager::open(&mut dev).unwrap().system.slots[2].used);
    }

    #[test]
    fn unformatted() {
        let mut dev = MemoryStorage::new(DeviceStatus::Unformatted);
        assert!(matches!(SaveManager::open(&mut dev), Err(StorageError::Unformatted)));
        dev.format().unwrap();
        assert!(SaveManager::open(&mut dev).is_ok());
    }
}
