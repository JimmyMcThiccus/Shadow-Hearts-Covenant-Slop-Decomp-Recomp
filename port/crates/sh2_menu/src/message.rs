//! `MenuMessage` — typewriter text box used by dialogue-style windows.
//!
//! JP: 0x0027d490..0x0027f4e8 (`Create`, `Start`, `Finish`, `SetOrderData`, `SetMacro`, `SetDefault`,
//! `Polling`, `Update`, `GetLastPosition`). The class derives from `PluralFontItem`, which keeps two
//! arrays of 0x30 byte entries in packet memory: per-glyph entries (alpha @+0x17, width @+0xc, fade
//! rate @+0x24) and "macro" entries (kind @+0x14, trigger glyph index @+0x16, argument @+0x24).
//! Glyph layout (`FontDraw::OrderMessage`) is the renderer's job in the port.

use crate::gfx::{DrawCmd, MenuGfx, Rgba, TextRun};
use glam::Vec2;

/// Text speed option stored in `MENU` section byte 0x274 bits 4-5 (`SaveMenuSection`).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum TextSpeed {
    /// setting 0: 200 ticks per character
    Slow,
    /// setting 1 (and 3? no): 100 ticks per character
    Normal,
    /// setting 2: 50 ticks per character
    Fast,
    /// setting 3: whole message appears at once
    Instant,
}

impl TextSpeed {
    pub fn from_option(v: u8) -> Self {
        match (v >> 4) & 3 {
            0 => TextSpeed::Slow,
            1 => TextSpeed::Normal,
            2 => TextSpeed::Fast,
            _ => TextSpeed::Instant,
        }
    }
    /// JP: 0x0027e200 MenuMessage::SetDefault
    pub fn interval(self) -> i16 {
        match self {
            TextSpeed::Slow => 200,
            TextSpeed::Fast => 50,
            _ => 100,
        }
    }
}

/// JP macro kinds (PluralFontItem second array, `+0x14`). Only 1,3,4,5,6 are interpreted by `SetMacro`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MacroOp {
    /// 6: restore the default speed and fade rate
    Default,
    /// 5: set the per-character interval (argument = ticks)
    Speed(i16),
    /// 1 / 3 / 4: stop typing for `ticks` (kinds differ by how the wait is ended in the host: 1 = key, 3/4 = timed)
    Wait { kind: u8, ticks: u32 },
}

#[derive(Clone, Copy, Debug)]
pub struct MacroEntry {
    /// glyph index at which the macro fires
    pub at_glyph: u16,
    pub op: MacroOp,
}

#[derive(Clone, Copy, Debug)]
pub struct Glyph {
    /// byte range inside [`Message::text`]
    pub start: u16,
    pub len: u8,
    /// 0 for control glyphs (newline), otherwise advance width in pixels (filled by the backend/layout)
    pub width: u8,
    /// 0..=0x80
    pub alpha: u8,
    /// per-glyph fade rate (JP +0x24)
    pub rate: u32,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MsgState {
    /// JP state 1: finished / idle
    Done,
    /// 9: typing
    Typing,
    /// 10: waiting on a macro
    Waiting,
}

#[derive(Clone, Debug)]
pub struct Message {
    pub text: Vec<u8>,
    pub glyphs: Vec<Glyph>,
    pub macros: Vec<MacroEntry>,
    pub state: MsgState,
    /// JP +0x7a — index of the next glyph to reveal
    pub cur_glyph: u16,
    /// JP +0x78 — number of printable glyphs revealed so far
    pub n_visible: u16,
    /// JP +0x80 — lowest glyph still fading in
    pub fade_from: u16,
    /// JP +0x8a — macro cursor
    pub cur_macro: u16,
    /// JP +0x8c — ticks per character
    pub interval: i16,
    /// JP +0x8e — accumulated ticks
    pub timer: i16,
    /// JP +0x90 — fade rate written into newly revealed glyphs (0x83126f)
    pub fade_rate: u32,
    pub speed: TextSpeed,
    /// pending wait (ticks) of the active wait macro
    wait_ticks: u32,
    pub font_number: u8,
    pub clut_set: u8,
    pub spacing: i8,
    pub max_chars: u16,
}

impl Message {
    pub const DEFAULT_FADE_RATE: u32 = 0x0083_126f;

    /// JP: 0x0027d590 MenuMessage::Create
    pub fn new(max_chars: u16, speed: TextSpeed) -> Self {
        Message {
            text: Vec::new(),
            glyphs: Vec::new(),
            macros: Vec::new(),
            state: MsgState::Done,
            cur_glyph: 0,
            n_visible: 0,
            fade_from: 0,
            cur_macro: 0,
            interval: speed.interval(),
            timer: 0,
            fade_rate: Self::DEFAULT_FADE_RATE,
            speed,
            wait_ticks: 0,
            font_number: 0,
            clut_set: 0,
            spacing: 0,
            max_chars,
        }
    }

    /// Tokenise Shift-JIS bytes into glyph entries (lead bytes 0x81-0x9f / 0xe0-0xfc take two bytes).
    pub fn set_text(&mut self, bytes: &[u8], macros: Vec<MacroEntry>) {
        self.text = bytes.to_vec();
        self.glyphs.clear();
        let mut i = 0;
        while i < bytes.len() && self.glyphs.len() < self.max_chars as usize {
            let b = bytes[i];
            let two = (0x81..=0x9f).contains(&b) || (0xe0..=0xfc).contains(&b);
            let len = if two && i + 1 < bytes.len() { 2 } else { 1 };
            let ctrl = b == 0x0a || b == 0x0d;
            self.glyphs.push(Glyph { start: i as u16, len: len as u8, width: if ctrl { 0 } else { if len == 2 { 16 } else { 8 } }, alpha: 0, rate: 0 });
            i += len;
        }
        self.macros = macros;
        self.clear_message();
    }

    /// JP: 0x0027d680 ClearMessage
    pub fn clear_message(&mut self) {
        self.cur_glyph = 0;
        self.n_visible = 0;
        self.fade_from = 0;
        self.cur_macro = 0;
        self.timer = 0;
        for g in &mut self.glyphs {
            g.alpha = 0;
        }
        self.state = MsgState::Done;
    }

    /// JP: 0x0027d7b0 Start — begin typing (skipped when the option is "instant").
    pub fn start(&mut self) {
        if self.speed == TextSpeed::Instant {
            return;
        }
        self.cur_glyph = 0;
        self.n_visible = 0;
        self.fade_from = 0;
        self.timer = 0;
        self.cur_macro = 0;
        self.state = MsgState::Typing;
        self.set_macro(0);
    }

    /// JP: 0x0027d940 Finish — show everything immediately.
    pub fn finish(&mut self) {
        self.fade_from = self.glyphs.len() as u16;
        self.cur_glyph = self.glyphs.len() as u16;
        self.n_visible = self.glyphs.iter().filter(|g| g.width != 0).count() as u16;
        for g in &mut self.glyphs {
            g.alpha = 0x80;
        }
        self.cur_macro = self.macros.len() as u16;
        self.set_default();
        self.state = MsgState::Done;
    }

    /// JP: 0x0027e200 SetDefault
    pub fn set_default(&mut self) {
        self.interval = self.speed.interval();
        self.fade_rate = Self::DEFAULT_FADE_RATE;
    }

    /// JP: 0x0027df90 SetMacro — returns true when typing must pause.
    pub fn set_macro(&mut self, glyph: u16) -> bool {
        loop {
            let Some(m) = self.macros.get(self.cur_macro as usize) else { return false };
            if m.at_glyph != glyph {
                return false;
            }
            match m.op {
                MacroOp::Default => self.set_default(),
                MacroOp::Speed(v) => self.interval = v,
                MacroOp::Wait { ticks, .. } => {
                    // NB: the original does not advance `cur_macro` for wait macros (only one wait per
                    // message is ever processed); mirrored here.
                    self.state = MsgState::Waiting;
                    self.wait_ticks = ticks;
                    return true;
                }
            }
            self.cur_macro += 1;
        }
    }

    /// Host-driven wake up for key-wait macros (kind 1): the original polls the pad elsewhere.
    pub fn release_wait(&mut self) {
        if self.state == MsgState::Waiting {
            self.wait_ticks = 0;
        }
    }

    /// JP: 0x0027e2a0 Polling. `dt` = `MenuObj::sm_iPassTime`.
    pub fn poll(&mut self, dt: i32) {
        match self.state {
            MsgState::Waiting => {
                self.timer = self.timer.wrapping_add(dt as i16);
                if self.wait_ticks as i64 <= self.timer as i64 {
                    self.state = MsgState::Typing;
                    self.timer = (self.timer as i64 - self.wait_ticks as i64) as i16;
                    self.cur_glyph += 1;
                    self.set_macro(self.cur_glyph);
                }
            }
            MsgState::Typing if (self.cur_glyph as usize) < self.glyphs.len() => {
                self.timer = self.timer.wrapping_add(dt as i16);
                while self.interval <= self.timer {
                    let rate = self.fade_rate;
                    let g = &mut self.glyphs[self.cur_glyph as usize];
                    g.alpha = 0;
                    g.rate = rate;
                    let printable = g.width != 0;
                    self.cur_glyph += 1;
                    self.timer -= self.interval;
                    if printable {
                        self.n_visible += 1;
                    }
                    if self.set_macro(self.cur_glyph) || self.cur_glyph as usize >= self.glyphs.len() {
                        break;
                    }
                }
            }
            _ => {}
        }
        // fade-in of revealed glyphs
        if self.fade_from < self.cur_glyph {
            let mut lowest = self.cur_glyph;
            for i in self.fade_from..self.cur_glyph {
                let g = &mut self.glyphs[i as usize];
                g.alpha = g.alpha.wrapping_add((g.rate.wrapping_mul(dt as u32) >> 24) as u8);
                if g.alpha < 0x80 {
                    lowest = lowest.min(i);
                } else {
                    g.alpha = 0x80;
                }
            }
            self.fade_from = lowest;
        }
        if self.state == MsgState::Typing && self.cur_glyph as usize >= self.glyphs.len() && self.fade_from >= self.cur_glyph {
            self.state = MsgState::Done;
        }
    }

    /// JP: 0x0027f3d0 GetLastPosition — pixel position just after the last revealed glyph.
    pub fn last_position(&self, origin: Vec2, line_height: f32) -> Vec2 {
        let mut x = 0.0;
        let mut y = 0.0;
        for g in self.glyphs.iter().take(self.cur_glyph as usize) {
            if g.width == 0 {
                x = 0.0;
                y += line_height;
            } else {
                x += g.width as f32 + self.spacing as f32;
            }
        }
        origin + Vec2::new(x, y)
    }

    pub fn draw(&self, gfx: &mut dyn MenuGfx, x: f32, y: f32, color: Rgba) {
        gfx.draw(DrawCmd::Text(TextRun {
            pos: Vec2::new(x, y),
            text: self.text.clone(),
            font_number: self.font_number,
            clut_set: self.clut_set,
            spacing: self.spacing,
            color,
            shadow: None,
            glyph_alpha: self.glyphs.iter().map(|g| g.alpha).collect(),
            visible: if self.state == MsgState::Done && self.cur_glyph == 0 && self.speed == TextSpeed::Instant { usize::MAX } else { self.cur_glyph as usize },
            hscale: 1.0,
        }));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn types_out_over_time() {
        let mut m = Message::new(32, TextSpeed::Normal);
        m.set_text(b"abc", vec![]);
        m.start();
        for _ in 0..10 {
            m.poll(16);
        }
        assert_eq!(m.cur_glyph, 1); // 160 ticks / 100 -> one char so far
        for _ in 0..40 {
            m.poll(16);
        }
        assert_eq!(m.cur_glyph, 3);
        assert_eq!(m.state, MsgState::Done);
        assert!(m.glyphs.iter().all(|g| g.alpha == 0x80));
    }

    #[test]
    fn wait_macro_pauses() {
        let mut m = Message::new(32, TextSpeed::Fast);
        m.set_text(b"ab", vec![MacroEntry { at_glyph: 1, op: MacroOp::Wait { kind: 3, ticks: 500 } }]);
        m.start();
        for _ in 0..10 {
            m.poll(16);
        }
        assert_eq!(m.state, MsgState::Waiting);
    }
}
