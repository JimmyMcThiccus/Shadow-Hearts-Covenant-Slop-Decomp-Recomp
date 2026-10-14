//! Retail Wolf Bout stamp card (`WSTAMP.MSD`): `SpecialMenu(0x600, bout)` (16 maps) builds `CmdRetailSel02` -> `CmdRetailPage03`
//! (US 0x4e3c00 `GetReady`, 0x4e3eb0 the stamp sequence, windows `CmdRetailWin06` = the card, `CmdRetailWin07` = the message).
//!
//! * `CmdRetailSel02` (0x4e39d0): `BTL0[0xfd8 + count] = bout`, then `BTL0[0xfd7]` (the stamp count) + 1.  The count is what Blanca's
//!   wolf skills read (Soul Comet's power, 0x46b088 / 0x4bd77c).
//! * The card: `count < 13` the open box (attach 1, 232 x 232, stamps 1..12 = sprites 2..13 on the paw sheet attach 3), else the second
//!   box (attach 2, 216 x 216, stamps 13..15 = sprites 14..16 on attach 4), window 0 at (124, 64).  The new stamp fades in (+4 alpha per
//!   frame, SE 0x3003 when the card is up, SE 0x1003 with the message), then the message window (window 1: (94, 300) 324 x 44, style 6)
//!   says MDT 53 row `count - 1` ("You learned %p9Soul Comet%p0!", "... has powered up!", ...); a key closes it.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba};

use crate::cmd_common::{message_frame, white};
use crate::cmd_page::{CmdScenes, Env};
use crate::cmd_ui::{draw_sprite_rec, fill, sj, SceneTex};
use crate::fscreen::{coded_text, FieldScreen, ScreenFlow, ScreenIo, DT_MS};

const PATH: &str = "MENU/MSD/WSTAMP.MSD";
/// `BTL0 + 0xfd7`: stamps so far; `+0xfd8..`: the bout of each stamp
pub const OFF_STAMP_COUNT: usize = 0xfd7;
pub const OFF_STAMP_BOUTS: usize = 0xfd8;
pub const STAMP_MAX: usize = 15;

#[derive(Debug, Clone, Copy, PartialEq)]
enum Phase {
    Open,
    Stamp(u32),
    Message,
    Close,
}

pub struct WolfStampScreen {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    count: usize,
    text: String,
    phase: Phase,
    fade: f32,
    stamp_a: u32,
}

/// `CmdRetailSel02`'s bookkeeping: records the bout and returns the new stamp count.
pub fn add_stamp(btl: &mut [u8], bout: i32) -> usize {
    let n = btl.get(OFF_STAMP_COUNT).copied().unwrap_or(0) as usize;
    if n < STAMP_MAX {
        if let Some(b) = btl.get_mut(OFF_STAMP_BOUTS + n) {
            *b = bout as u8;
        }
        if let Some(b) = btl.get_mut(OFF_STAMP_COUNT) {
            *b = (n + 1) as u8;
        }
    }
    (n + 1).min(STAMP_MAX)
}

impl WolfStampScreen {
    pub fn new(env: &mut Env, bout: i32) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let count = add_stamp(&mut env.session.save.btl.data, bout);
        let text = scene.msd.attach_scene(0).map(|m| sj(m.mdt_str(53, count - 1, 0))).unwrap_or_default();
        log::info!("wolf stamp: bout {bout} -> stamp {count}: {text:?}");
        Some(WolfStampScreen { sc, scene, count, text, phase: Phase::Open, fade: 0.0, stamp_a: 0 })
    }
}

impl FieldScreen for WolfStampScreen {
    fn name(&self) -> &'static str {
        "wolfstamp"
    }
    fn state(&self) -> String {
        match self.phase {
            Phase::Open => "open",
            Phase::Stamp(_) => "stamp",
            Phase::Message => "message",
            Phase::Close => "close",
        }
        .into()
    }
    fn tick(&mut self, env: &mut Env, _keys: u16, press: u16, _io: &mut ScreenIo) -> ScreenFlow {
        match self.phase {
            Phase::Open => {
                self.fade = (self.fade + DT_MS / 240.0).min(1.0);
                if self.fade >= 1.0 {
                    env.sound(MenuSe::Other(0x3003));
                    self.phase = Phase::Stamp(0);
                }
            }
            Phase::Stamp(n) => {
                self.stamp_a = (self.stamp_a + 4).min(128);
                if self.stamp_a >= 128 {
                    env.sound(MenuSe::Other(0x1003));
                    self.phase = Phase::Message;
                } else {
                    self.phase = Phase::Stamp(n + 1);
                }
            }
            Phase::Message => {
                if press & (padbit::CIRCLE | padbit::CROSS) != 0 {
                    env.sound(MenuSe::Decide);
                    self.phase = Phase::Close;
                }
            }
            Phase::Close => {
                self.fade = (self.fade - DT_MS / 300.0).max(0.0);
                if self.fade <= 0.0 {
                    return ScreenFlow::Done;
                }
            }
        }
        ScreenFlow::Stay
    }
    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = (self.fade * 128.0) as u8;
        if a == 0 {
            return;
        }
        let m = &self.scene.msd;
        fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, (a as u32 * 0x40 / 0x80) as u8));
        let (ox, oy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((124.0, 64.0));
        let second = self.count > 12;
        // the card, then stamps 1..count (the newest fading in)
        let (card, tex, first, last) = if second { (1usize, 2usize, 13usize, 15usize) } else { (0, 1, 1, 12) };
        if let Some(s) = m.sprite(card) {
            draw_sprite_rec(g, &s, self.scene.t(tex), ox, oy, a);
        }
        for k in first..=last.min(self.count) {
            let Some(s) = m.sprite(k + 1) else { continue };
            let sa = if k == self.count { ((self.stamp_a * a as u32) / 0x80) as u8 } else { a };
            draw_sprite_rec(g, &s, self.scene.t(if second { 4 } else { 3 }), ox, oy, sa);
        }
        if matches!(self.phase, Phase::Message | Phase::Close) {
            let (wx, wy, ww, wh) = m.window(1).map(|w| (w.x, w.y, w.w, w.h)).unwrap_or((94.0, 300.0, 324.0, 44.0));
            message_frame(g, &self.sc.cmn, wx, wy, ww, a);
            let lines = self.text.split('$').count() as f32;
            coded_text(g, wx + 16.0, wy + wh * 0.5 - lines * 10.0 - 2.0, &self.text, 0, white(a), 20.0, true);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn stamps_record_the_bout_and_stop_at_fifteen() {
        let mut b = vec![0u8; 0x1000];
        assert_eq!(add_stamp(&mut b, 7), 1);
        assert_eq!((b[OFF_STAMP_COUNT], b[OFF_STAMP_BOUTS]), (1, 7));
        for i in 1..20 {
            add_stamp(&mut b, i);
        }
        assert_eq!(b[OFF_STAMP_COUNT] as usize, STAMP_MAX);
        assert_eq!(b[OFF_STAMP_BOUTS + 14], 14);
    }
}
