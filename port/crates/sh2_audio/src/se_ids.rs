//! Sound-effect ids of the game's UI layers, identified from the decompiled call sites (decomp/F, G, H: `MenuSound::PlaySE`,
//! `primSound::play`, `HNMSnd::PlaySE`) and from the contents of the system banks (see notes/integration/audio.md section 7a).
//!
//! An SE id passed to `MenuSound::PlaySE` / `HNMSnd::PlaySE` is a *global* id: `(wave bank id << 16) | local id`.  The two system banks are
//! always resident: `COMMON/SYSREG.SSE` has wave-bank id 0 and `BTLDATA/SOUND/SYSTEM/SYSBTL.SSE` has wave-bank id 0x0200.  Every id below is
//! the *local* id inside its bank; `AudioRequest::PlaySystemSe` takes SYSREG ids, `PlayBattleSe` takes SYSREG ids below 0x1000 and SYSBTL ids
//! from 0x1000 up, `PlayGlobalSe` takes the full global id.

/// wave-bank id of `COMMON/SYSREG.SSE`
pub const BANK_SYSREG: u16 = 0x0000;
/// wave-bank id of `BTLDATA/SOUND/SYSTEM/SYSBTL.SSE`
pub const BANK_SYSBTL: u16 = 0x0200;

/// Combine a bank and a local id into a global SE id.
pub const fn global(bank: u16, local: u16) -> u32 {
    ((bank as u32) << 16) | local as u32
}

// ----- SYSREG (menus, field UI, and the battle command menu `BtlMenu`) ------------------------------------------------------------------
/// cursor move (`Cursor::SetTarget`, every list window, battle command menu up/down): 28 `MenuSound` call sites + 8 in `BtlMenu`
pub const CURSOR: u16 = 0;
/// value adjust / option tick (`CmdOption` left-right, shop quantity, ring-custom): 6 call sites
pub const ADJUST: u16 = 1;
/// decide / confirm (47 call sites; `BtlMenu` command accepted)
pub const DECIDE: u16 = 2;
/// cancel / back (30 call sites; `BtlMenu` pad bit 0x4000)
pub const CANCEL: u16 = 3;
/// buzzer / not allowed (11 call sites; `dataAccess` `SeKind::Buzzer = 4`; `BtlMenu` rejected command)
pub const BUZZER: u16 = 4;
/// `sm_pSound` id 5 (one call site in the field menu)
pub const MENU_5: u16 = 5;
/// `BtlMenu` R1/R2 page forward (pad mask 0xa00)
pub const PAGE_NEXT: u16 = 6;
/// `BtlMenu` L1/L2 page back (pad mask 0x500)
pub const PAGE_PREV: u16 = 7;
/// 0x1000: save / load finished (`dataAccess` progress bar complete); 0x1002: battle shortcut target changed (`CBattle`);
/// 0x1007: world-map "new point" jingle.  0x1001, 0x1003..0x1006 are event jingles used by field scripts.
pub const SAVE_DONE: u16 = 0x1000;
pub const SHORTCUT_TARGET: u16 = 0x1002;
pub const WORLD_NEW_POINT: u16 = 0x1007;
/// looping sounds of SYSREG (ids 0x2000, 0x2001, 0x3000, 0x3001 sustain until released)
pub const LOOP_2000: u16 = 0x2000;

// ----- SYSBTL (battle system sounds, `CBattle` / `HNMSnd::PlaySE(0x0200_xxxx)`) -------------------------------------------------------
/// generic physical hit (`0x02001000`)
pub const BTL_HIT: u16 = 0x1000;
/// wall hit damage (`0x02001002`)
pub const BTL_WALL_HIT: u16 = 0x1002;
/// hit of an element type 2 / 5 attack (`0x02001005`)
pub const BTL_HIT_ELEMENT: u16 = 0x1005;
/// formation / entry effect (`0x02002005`)
pub const BTL_FORMATION: u16 = 0x2005;

/// Split a battle-menu SE id as posted by `AudioRequest::PlayBattleSe`: SYSREG below 0x1000, SYSBTL from 0x1000.
pub const fn battle_global(id: u16) -> u32 {
    if id < 0x1000 {
        global(BANK_SYSREG, id)
    } else {
        global(BANK_SYSBTL, id)
    }
}
