//! Script-controlled UI objects of `CField`: message windows (`FieldMessage`, ops 0x30-0x37), name plates (0x39-0x3d), face images
//! (`FaceImage`, 0x40-0x46), the selection list (0x48-0x4b, `CField::Select`), the field timer (`FldTimer`, 0x4e/0x4f) and full-screen
//! images (`FldSprite`, 0x2c-0x2e).  This module is pure state (JP FIELD.BIN 0x004b5040.. `CField::CreateWindow` ... `Select`); the
//! Bevy glue draws it.
//!
//! Window ids: `CField` keeps eight message slots (`+0x60c + id*0x14`), eight name-plate slots (`+0x65c`) and four face slots (`+0x6b0`).
//! Ops 0x31 / 0x3a / 0x42 pick the *current* slot used by the following ops.

use sh2_menu::message::{Message, MsgState, TextSpeed};

pub const MAX_WINDOWS: usize = 8;
pub const MAX_FACES: usize = 4;
/// Pixel size of one character cell of the default field font (full-width glyph).
pub const CELL_W: f32 = 16.0;
pub const CELL_H: f32 = 22.0;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum WinPhase {
    /// no window object (`GetState` 0)
    Closed,
    /// open animation, ticks left
    Opening(u32),
    /// shown (`GetState` 1)
    Open,
    Closing(u32),
}

/// A message window or name plate (`FieldMessage`).
#[derive(Debug, Clone)]
pub struct FieldWindow {
    pub created: bool,
    /// `CreateWindow(id, kind, flags, max)`: frame style
    pub kind: u8,
    pub flags: u8,
    pub max_chars: u16,
    pub x: i32,
    pub y: i32,
    pub cols: u8,
    pub rows: u8,
    pub phase: WinPhase,
    pub msg: Option<Message>,
    /// everything appended with `OpenMessage` since the last `ClearMessage`
    pub raw: Vec<u8>,
    /// the window waits for the circle button before the script continues (set by `OpenMessage`, cleared by `KeyWait`)
    pub key_pending: bool,
    /// speaking actor slot (`OpenMessage` arg 2): its talk motion runs while the window types
    pub talker: i32,
}

impl Default for FieldWindow {
    fn default() -> Self {
        FieldWindow {
            created: false,
            kind: 0,
            flags: 0,
            max_chars: 0x100,
            x: 0,
            y: 0,
            cols: 30,
            rows: 3,
            phase: WinPhase::Closed,
            msg: None,
            raw: vec![],
            key_pending: false,
            talker: -1,
        }
    }
}

impl FieldWindow {
    pub fn is_open(&self) -> bool {
        matches!(self.phase, WinPhase::Open | WinPhase::Opening(_))
    }
    /// pixel size of the frame
    pub fn size_px(&self) -> (f32, f32) {
        (self.cols as f32 * CELL_W + 24.0, self.rows as f32 * CELL_H + 18.0)
    }
    /// `FieldMessage::GetState`: 0 closed, 1 shown and idle, 9 typing, 0xe waiting for the key
    pub fn state(&self) -> i16 {
        match self.phase {
            WinPhase::Closed => 0,
            WinPhase::Opening(_) => 3,
            WinPhase::Closing(_) => 4,
            WinPhase::Open => match &self.msg {
                Some(m) if m.state != MsgState::Done => 9,
                Some(_) if self.key_pending => 0xe,
                _ => 1,
            },
        }
    }
    pub fn open(&mut self, frames: i32) {
        if !self.created {
            self.created = true;
        }
        self.phase = if frames > 1 { WinPhase::Opening(frames.min(30) as u32) } else { WinPhase::Open };
    }
    pub fn close(&mut self, frames: i32) {
        self.phase = if frames > 1 { WinPhase::Closing(frames.min(30) as u32) } else { WinPhase::Closed };
        if self.phase == WinPhase::Closed {
            self.clear();
        }
    }
    /// JP: 0x004a1580 `FieldMessage::OpenMessage`: append the text and type the new part.
    pub fn append(&mut self, text: &[u8], speed: TextSpeed) {
        let prev = self.msg.as_ref().map(|m| m.glyphs.len()).unwrap_or(0);
        self.raw.extend_from_slice(&strip_text_codes(text));
        let mut m = Message::new(self.max_chars.max(0x100), speed);
        m.font_number = sh2_menu::bevy_ui::FIELD_FONT;
        m.set_text(&self.raw, vec![]);
        m.start();
        // the earlier pages are already on screen
        if let Some(old) = &self.msg {
            let keep = prev.min(m.glyphs.len());
            for g in m.glyphs.iter_mut().take(keep) {
                g.alpha = 0x80;
            }
            if keep > 0 && speed != TextSpeed::Instant {
                m.cur_glyph = keep as u16;
                m.fade_from = keep as u16;
                m.n_visible = old.n_visible;
            }
        }
        if speed == TextSpeed::Instant {
            m.finish();
        }
        self.msg = Some(m);
        self.key_pending = true;
        if self.phase == WinPhase::Closed {
            self.phase = WinPhase::Open;
        }
    }
    /// JP: 0x004a1740 `FieldMessage::ClearMessage`
    pub fn clear(&mut self) {
        self.raw.clear();
        self.msg = None;
        self.key_pending = false;
    }
    pub fn tick(&mut self) {
        match self.phase {
            WinPhase::Opening(n) => self.phase = if n <= 1 { WinPhase::Open } else { WinPhase::Opening(n - 1) },
            WinPhase::Closing(n) => {
                if n <= 1 {
                    self.phase = WinPhase::Closed;
                    self.clear();
                } else {
                    self.phase = WinPhase::Closing(n - 1);
                }
            }
            _ => {}
        }
        if let Some(m) = self.msg.as_mut() {
            m.poll(32);
        }
    }
    /// the message is completely typed
    pub fn typed(&self) -> bool {
        self.msg.as_ref().map(|m| m.state == MsgState::Done).unwrap_or(true)
    }
}

/// Remove the colour / type / icon codes of the game text (`%t0`, `%p4`, `%i32`): the field window draws plain text (the palette switch of
/// `%pN` is not reproduced).  `$` (newline) and every other byte stay for the text layer.
pub fn strip_text_codes(raw: &[u8]) -> Vec<u8> {
    let mut out = Vec::with_capacity(raw.len());
    let mut i = 0;
    while i < raw.len() {
        let b = raw[i];
        // Shift-JIS lead byte: copy both bytes untouched
        if (0x81..=0x9f).contains(&b) || (0xe0..=0xfc).contains(&b) {
            out.push(b);
            if i + 1 < raw.len() {
                out.push(raw[i + 1]);
            }
            i += 2;
            continue;
        }
        if b == b'%' && i + 1 < raw.len() && matches!(raw[i + 1], b't' | b'p' | b'i') {
            let mut j = i + 2;
            while j < raw.len() && raw[j].is_ascii_digit() {
                j += 1;
            }
            if j > i + 2 {
                i = j;
                continue;
            }
        }
        out.push(b);
        i += 1;
    }
    out
}

/// `FaceImage`: a portrait loaded from `MENU/IMG/..` by face id.
#[derive(Debug, Clone, Default)]
pub struct FaceSlot {
    pub loaded: bool,
    pub face_id: i32,
    pub x: f32,
    pub y: f32,
    pub w: f32,
    pub h: f32,
    pub open: bool,
}

/// `CField::SelectInit/SelectAddItem/Select`.
#[derive(Debug, Clone, Default)]
pub struct Selection {
    pub active: bool,
    pub window: usize,
    pub mode: i32,
    pub cancel_ok: bool,
    pub items: Vec<Vec<u8>>,
    pub cursor: usize,
    pub result: Option<i32>,
}

/// `FldTimer`: counts in tenths of a second.
#[derive(Debug, Clone, Default)]
pub struct FldTimer {
    pub created: bool,
    pub x: i32,
    pub y: i32,
    /// tenths of seconds
    pub count: i32,
    pub limit: i32,
    pub kind: i32,
    pub running: bool,
    pub shown: bool,
    pub alarm_event: u32,
    pub alarm: bool,
    sub: u32,
}

impl FldTimer {
    pub fn create(&mut self, kind: i32, x: i32, y: i32, count: i32, limit: i32, event: u32) {
        *self = FldTimer { created: true, x, y, count, limit, kind, alarm_event: event, ..Default::default() };
    }
    /// 60 Hz tick; true when the alarm fires
    pub fn tick(&mut self) -> bool {
        if !self.created || !self.running {
            return false;
        }
        self.sub += 1;
        if self.sub < 6 {
            return false;
        }
        self.sub = 0;
        if self.limit > 0 {
            self.count += 1;
            if self.count >= self.limit {
                self.count = self.limit;
                self.running = false;
                self.alarm = true;
                return true;
            }
        } else {
            self.count -= 1;
            if self.count <= 0 {
                self.count = 0;
                self.running = false;
                self.alarm = true;
                return true;
            }
        }
        false
    }
}

/// `FldSprite` (full-screen / HUD image).
#[derive(Debug, Clone, Default)]
pub struct ImageSlot {
    pub name: String,
    pub shown: bool,
    pub x: i32,
    pub y: i32,
    pub a: i32,
    pub b: i32,
    pub fade_in: i32,
}

#[derive(Debug, Clone)]
pub struct UiState {
    pub windows: Vec<FieldWindow>,
    pub names: Vec<FieldWindow>,
    pub faces: Vec<FaceSlot>,
    pub images: Vec<ImageSlot>,
    pub cur_win: usize,
    pub cur_name: usize,
    pub cur_face: usize,
    pub select: Selection,
    pub timer: FldTimer,
    pub speed: TextSpeed,
}

impl Default for UiState {
    fn default() -> Self {
        UiState {
            windows: (0..MAX_WINDOWS).map(|_| FieldWindow::default()).collect(),
            names: (0..MAX_WINDOWS).map(|_| FieldWindow { cols: 16, rows: 1, ..Default::default() }).collect(),
            faces: vec![FaceSlot::default(); MAX_FACES],
            images: vec![ImageSlot::default(); 8],
            cur_win: 0,
            cur_name: 0,
            cur_face: 0,
            select: Selection::default(),
            timer: FldTimer::default(),
            speed: TextSpeed::Fast,
        }
    }
}

impl UiState {
    pub fn win(&mut self) -> &mut FieldWindow {
        let i = self.cur_win.min(MAX_WINDOWS - 1);
        &mut self.windows[i]
    }
    pub fn name(&mut self) -> &mut FieldWindow {
        let i = self.cur_name.min(MAX_WINDOWS - 1);
        &mut self.names[i]
    }
    pub fn face(&mut self) -> &mut FaceSlot {
        let i = self.cur_face.min(MAX_FACES - 1);
        &mut self.faces[i]
    }
    /// a message window is visible (used by the player-lock logic and the autopilot)
    pub fn msg_active(&self) -> bool {
        self.windows.iter().any(|w| w.is_open() && w.msg.is_some())
    }
    pub fn any_window_open(&self) -> bool {
        self.windows.iter().any(|w| w.is_open())
    }
    pub fn tick(&mut self) {
        for w in self.windows.iter_mut().chain(self.names.iter_mut()) {
            w.tick();
        }
    }
    pub fn reset(&mut self) {
        let speed = self.speed;
        *self = UiState { speed, ..Default::default() };
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn append_keeps_earlier_text_visible() {
        let mut w = FieldWindow::default();
        w.open(0);
        w.append(b"abc", TextSpeed::Fast);
        w.msg.as_mut().unwrap().finish();
        w.append(b"def", TextSpeed::Fast);
        let m = w.msg.as_ref().unwrap();
        assert_eq!(m.glyphs.len(), 6);
        assert_eq!(m.cur_glyph, 3);
        assert!(m.glyphs[..3].iter().all(|g| g.alpha == 0x80));
        assert_eq!(w.state(), 9);
    }

    /// TD_14_U's orders (three `$` lines in a 20 x 3 window) type to the end.
    #[test]
    fn long_message_finishes_typing() {
        for speed in [TextSpeed::Slow, TextSpeed::Normal, TextSpeed::Fast] {
            let mut w = FieldWindow::default();
            w.cols = 0x14;
            w.rows = 3;
            w.open(0xf);
            w.append(b"What do you think you're aiming at?! How$could you miss such a big target?!", speed);
            let mut n = 0;
            while !w.typed() && n < 5000 {
                w.tick();
                n += 1;
            }
            let m = w.msg.as_ref().unwrap();
            assert!(w.typed(), "{speed:?}: state {:?} glyph {} / {} fade {} macro {:?}", m.state, m.cur_glyph, m.glyphs.len(), m.fade_from, m.macros.get(m.cur_macro as usize).map(|x| format!("{x:?}")));
        }
    }

    #[test]
    fn text_codes_are_stripped() {
        assert_eq!(strip_text_codes(b"%t0%p4Nicole%p0 a%d"), b"Nicole a%d");
        assert_eq!(strip_text_codes(&[0x83, 0x70, b'%', b'p', b'1', b'x']), vec![0x83, 0x70, b'x']);
    }

    #[test]
    fn timer_counts_down_in_tenths() {
        let mut t = FldTimer::default();
        t.create(0, 0, 0, 5, 0, 7);
        t.running = true;
        let mut fired = 0;
        for _ in 0..60 {
            if t.tick() {
                fired += 1;
            }
        }
        assert_eq!(t.count, 0);
        assert_eq!(fired, 1, "5 tenths take 30 ticks, the alarm fires once");
    }
}
