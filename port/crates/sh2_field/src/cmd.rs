//! In-game menu system (`Cmd*`, ~140 classes in FIELD.BIN): shared structure.
//!
//! The menu toolkit (`Menu`, `MenuScene`, `MenuWindow`, `MenuText`, `MenuSprite`, ...) is section F; section G contributes the
//! application: one `CmdMenu` object (0x17f8 bytes, derived from `Menu`) that owns an array of *pages* (`MenuScene` subclasses created lazily
//! by `CmdMenu::Ready(page, a, b)`, JP 0x00436390) plus shared widgets (`CmdParty`, `CmdCommon`, `CmdNote`, `CmdTitleLog`,
//! `CmdButtonReport`, `CmdElement`). Class metadata: [`crate::classes_cmd::CMD_CLASSES`]. Doc: `notes/G/cmd_menu_system.md`.

pub use crate::classes_cmd::CMD_CLASSES;

/// Menu page ids accepted by `CmdMenu::Ready` / `CmdMenu::Initialize` (second constructor argument).
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[repr(u16)]
pub enum CmdPage {
    /// 0: top menu (`CmdTop`, 0x90 bytes) — also the page whose resources are embedded (`Initialize(sceneData)`).
    Top = 0,
    /// 1: items (`CmdItem`, 0xa0)
    Item = 1,
    /// 2: white magic (`CmdWhiteMagic`, 0x360)
    WhiteMagic = 2,
    /// 3: magic (`CmdMagic`, 0x368)
    Magic = 3,
    /// 4: crests (`CmdCrest`, 0x9c0)
    Crest = 4,
    /// 5: equipment (`CmdEquipment`, 0xd0)
    Equipment = 5,
    /// 6: ring customize (`CmdRingCustom`, 0x220)
    RingCustom = 6,
    /// 7: personal/status (`CmdPrivate`, 0x98)
    Private = 7,
    /// 8: formation (`CmdFormation`, 0xe58)
    Formation = 8,
    /// 9: graveyard (`CmdGraveyard`, 0x31c)
    Graveyard = 9,
    /// 10: combo keys (`CmdComboKey`, 0xcc0)
    ComboKey = 10,
    /// 11: combo magic (`CmdComboMagic`, 0x188)
    ComboMagic = 11,
    /// 12: help (`CmdHelp`, 0x2f0)
    Help = 12,
    /// 13: score (`CmdScore`, 0x2dc)
    Score = 13,
    /// 14: library (`CmdLibrary`, 0x208)
    Library = 14,
    /// 15: property list (`CmdPropertyList`, 0x16c)
    PropertyList = 15,
    /// 16: options (`CmdOption`, 0x2640)
    Option = 16,
    /// 17: key customize (`CmdKeyCustom`, 0x1c10)
    KeyCustom = 17,
    /// 19: retail character select (`CmdRetailPage06`, `SECHAR.MSD`): the member pick of the shop's Equip, then the Equipment page
    SelectChar = 19,
    /// 0x15: Solomon (the demon-fusing shop) launched from the menu (`solomon`, 0xbd0, see `crate::solomon`)
    Solomon = 0x15,
}

impl CmdPage {
    pub const ALL: [CmdPage; 19] = [
        Self::Top, Self::Item, Self::WhiteMagic, Self::Magic, Self::Crest, Self::Equipment, Self::RingCustom, Self::Private,
        Self::Formation, Self::Graveyard, Self::ComboKey, Self::ComboMagic, Self::Help, Self::Score, Self::Library,
        Self::PropertyList, Self::Option, Self::KeyCustom, Self::Solomon,
    ];

    pub fn from_u16(v: u16) -> Option<Self> {
        Self::ALL.into_iter().find(|p| *p as u16 == v)
    }

    /// JP class built for this page and its object size in bytes.
    pub fn class(self) -> (&'static str, u32) {
        match self {
            Self::Top => ("CmdTop", 0x90),
            Self::Item => ("CmdItem", 0xa0),
            Self::WhiteMagic => ("CmdWhiteMagic", 0x360),
            Self::Magic => ("CmdMagic", 0x368),
            Self::Crest => ("CmdCrest", 0x9c0),
            Self::Equipment => ("CmdEquipment", 0xd0),
            Self::RingCustom => ("CmdRingCustom", 0x220),
            Self::Private => ("CmdPrivate", 0x98),
            Self::Formation => ("CmdFormation", 0xe58),
            Self::Graveyard => ("CmdGraveyard", 0x31c),
            Self::ComboKey => ("CmdComboKey", 0xcc0),
            Self::ComboMagic => ("CmdComboMagic", 0x188),
            Self::Help => ("CmdHelp", 0x2f0),
            Self::Score => ("CmdScore", 0x2dc),
            Self::Library => ("CmdLibrary", 0x208),
            Self::PropertyList => ("CmdPropertyList", 0x16c),
            Self::Option => ("CmdOption", 0x2640),
            Self::KeyCustom => ("CmdKeyCustom", 0x1c10),
            Self::SelectChar => ("CmdRetailPage06", 0),
            Self::Solomon => ("solomon", 0xbd0),
        }
    }
}

/// `CmdMenu+0x3e` — state of `CmdMenu::Polling` (JP 0x00435aa0).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(u16)]
pub enum CmdMenuState {
    /// 0: wait until the current page (`+0x40`) is loaded and the owner callback(6) allows opening; then
    /// `CPause::DisablePause`, capture the field behind the menu (state 2) or go straight on (1).
    WaitScene = 0,
    /// 1: wait for the background flag (`+0x3d`), `CreateBackGround(7|8)`, callback(0), -> 3
    WaitBackground = 1,
    /// 2: wait for `MenuCapture` (screen grab 0x200x0xe0 PSM 0xd) -> 1
    Capturing = 2,
    /// 3: page ready: callback(1), set GS FF mode, (Solomon page: lights + projection), open the title window, menu SE 5 -> 4
    Open = 3,
    /// 4: `Menu::Run` — the page logic runs
    Run = 4,
    /// 5: final: destroy background, `MenuRender::Dispose`, `EnablePause`, callback(3), delete self (returns 1)
    Closing = 5,
    /// 6: close requested: callback(2) may veto; layer change; close window -> 5
    CloseRequest = 6,
    /// 7: launch Solomon (`start__7solomon`) -> 8
    LaunchSolomon = 7,
    /// 9: re-create scenes after returning from Solomon -> 10 -> `CreateScene`, page 0, background 7 -> 4
    Recreate = 9,
    /// 0xb: first-time font/texture/data-table creation (`CreateFont`, `MenuTexture::Create`, `MenuDataTable::Create`) -> 0
    InitResources = 0xb,
    Other(u16),
}

impl From<u16> for CmdMenuState {
    fn from(v: u16) -> Self {
        match v {
            0 => Self::WaitScene,
            1 => Self::WaitBackground,
            2 => Self::Capturing,
            3 => Self::Open,
            4 => Self::Run,
            5 => Self::Closing,
            6 => Self::CloseRequest,
            7 => Self::LaunchSolomon,
            9 | 10 => Self::Recreate,
            0xb => Self::InitResources,
            x => Self::Other(x),
        }
    }
}

/// Event codes passed to the owner callback `int cb(int event, void* user, CmdMenu*)` supplied to `CmdMenu::CmdMenu(page, cb, user)`.
/// `CFieldSocket::cbMenu` (JP 0x003bf740) is the field's implementation.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(i32)]
pub enum CmdMenuEvent {
    /// background created: field timer masked, "menu open" flag set on CField (+0x191 b6)
    BackgroundReady = 0,
    /// before the first page opens: `CField::Clr()` (hide the field)
    PageReady = 1,
    /// menu asks to close (return 0 to veto): `CField::Dsp()`, un-pause flags
    Closing = 2,
    /// menu closed: `CField::Pause(1)`
    Closed = 3,
    /// 5: clear "menu requested" flag (CField+0x18d b5)
    Ack = 5,
    /// 6: allowed to open: `CField::Pause(0)`; sets `CmdMenu+0x3d = 0x11`
    MayOpen = 6,
}

/// Events sent to `CmdMenu::DataEvent` (JP 0x00435610) by the save/load screen (`dataAccess`) launched from the top menu.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum DataEvent {
    /// 1: remove the window from the `MenuObjTable`
    RemoveObj = 1,
    /// 3: add it back (priority order)
    AddPriority = 3,
    /// 4: tell `CmdTop::DataAccessEvent` the save/load finished
    Finished = 4,
    /// 5: load completed -> `CmdMenu::MapJump(0)` then request page 0x17
    Loaded = 5,
}

pub fn class_info(name: &str) -> Option<&'static crate::registry::ClassInfo> {
    crate::registry::find(CMD_CLASSES, name)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn page_classes_exist_in_registry() {
        for p in CmdPage::ALL {
            let (name, size) = p.class();
            if p == CmdPage::Solomon {
                continue;
            }
            let ci = class_info(name).unwrap_or_else(|| panic!("{name}"));
            // CmdRingCustom also shows up with other `operator new` sizes (nested uses); the page factory size is authoritative
            if ci.size != 0 && name != "CmdRingCustom" {
                assert_eq!(ci.size, size, "{name}");
            }
        }
    }

    #[test]
    fn roundtrip_pages() {
        for p in CmdPage::ALL {
            assert_eq!(CmdPage::from_u16(p as u16), Some(p));
        }
        assert_eq!(CmdPage::from_u16(18), None);
    }
}
