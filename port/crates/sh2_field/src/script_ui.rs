//! Script-controlled UI objects of `CField`: message windows (`FieldMessage`, ops 0x30-0x37), name plates (0x39-0x3d), face images
//! (`FaceImage`, 0x40-0x46), the selection list (0x48-0x4b, `CField::Select`), the field timer (`FldTimer`, 0x4e/0x4f) and full-screen
//! images (`FldSprite`, 0x2c-0x2e).  This module is pure state (JP FIELD.BIN 0x004b5040.. `CField::CreateWindow` ... `Select`); the
//! Bevy glue draws it.
//!
//! Window ids: `CField` keeps eight message slots (`+0x60c + id*0x14`), eight name-plate slots (`+0x65c`) and four face slots (`+0x6b0`).
//! Ops 0x31 / 0x3a / 0x42 pick the *current* slot used by the following ops.

use sh2_menu::gfx::MenuSe;
use sh2_menu::message::{Message, MsgState, TextSpeed};
use sh2_menu::window::{Effect, WinState, Window};

pub const MAX_WINDOWS: usize = 8;
pub const MAX_FACES: usize = 4;
/// Pixel size of one character cell of the default field font (full-width glyph).
pub const CELL_W: f32 = 16.0;
pub const CELL_H: f32 = 22.0;

/// `FontItem::GetRealWidth` / `GetRealHeight` of the field windows' font item (US font 1 = `MFIELD.MSD` attach 0, cell 22 x 22): the width
/// is the cell width x 0.8 (the "narrow" flag `FontItem+0x58` bit 4, truncated to a byte), the height the cell height plus the item's shadow
/// y (`+0x5b` = 1, `FieldMessage::CreateWindow` writes the shadow (0, 1)).  `FieldMessage::SetSize(cols, rows)` makes the window
/// `cols * REAL_W` x `rows * REAL_H` pixels (US FIELD.BIN 0x004ee400 / JP 0x004a1c40).
pub const REAL_W: f32 = 17.0;
pub const REAL_H: f32 = 23.0;
/// One `FieldMessage` poll in `MenuObj::sm_iPassTime` units (`SysTool::GetTimer` ms) per 60 Hz logic tick: the accumulator in
/// [`UiState::tick`] hands out 16 / 17 ms so a second of ticks is a second of game time.
pub const TICK_MS: f32 = 1000.0 / 60.0;
/// `KeyWait` icon timer: `+0x1c` += pass time, wraps from 0x3c0 to -0x3c0 (KeyWait::Polling, JP 0x00280bf0).
pub const KEY_WRAP: i32 = 0x3c0;

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

/// CLUT row of the name plates (`MFIELD.MSD` font row 4 = 00 f8 c0: the teal name over US dialogue windows; row 0 = the cream body
/// text).  Applied when the plate is drawn (`plugin::draw_field_ui`).
pub const NAME_CLUT: u8 = 4;

/// Text style of the field windows (`FieldMessage::CreateWindow`, US FIELD.BIN 0x004ee180): the retail field serif (font 1, `MFIELD.MSD`),
/// laid out by `FontDraw::Order` with the `FontItem::Clear` defaults (`+0x58` = 0x18): proportional (each glyph advances by its width byte,
/// no lsb) and narrow (bit 4: glyph quads and pen steps x `FontDraw+0x40` = 0.8, set by `FontDraw::Clear` 0x0026d280).  The window sets
/// the item's shadow to (0, 1), so no extra pitch.  A US capture (LP archive Update 76) matches this within 2 % at the 4:3 frame scale.
pub fn field_text_style(m: &mut Message) {
    m.font_number = sh2_menu::bevy_ui::FIELD_FONT;
    m.hscale = sh2_menu::gfx::NARROW;
    m.proportional = true;
}

/// A message window or name plate (`FieldMessage`).
///
/// The script-visible record (`CField::_WndInfo`: kind, flags, size, position) is kept in `kind` .. `rows`; the live `MenuWindow` of the
/// `FieldMessageData` is [`FieldWindow::win`] (position, size, fade / slide animation, scroll).  `CField::OpenWindow` copies the record into
/// the live window (`SetSize` + `SetPosition`) and starts `MenuWindow::Open(effect, ms)`; `SetWindowPos` / `SetWindowSize` after that only
/// change the record (the next `OpenWindow` applies them).
#[derive(Debug, Clone)]
pub struct FieldWindow {
    pub created: bool,
    /// `CreateWindow(id, kind, flags, max)`: the `MenuWindow` decoration style (1 message, 2 face medallion, 3 note, 6 general ...)
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
    /// the live `MenuWindow`: position, size, alpha animation and scroll offset
    pub win: Window,
    /// creation order = draw order of windows of equal priority (`MenuObjTable`)
    pub seq: u32,
    /// byte offset into `raw` of the text of the last `OpenMessage` (note windows size and centre themselves on it)
    pub seg_start: usize,
    /// `KeyWait` icon timer (`KeyWait+0x1c`, ms, -0x3c0 ..= 0x3c0)
    pub key_t: i32,
    /// kind 3 (note): `OpenWindow` only remembers effect and time, the first `OpenMessage` opens the window
    pub deferred_open: Option<(u8, i32)>,
    /// the cursor of a selection moves the window scroll instead of the typing line
    pub selecting: bool,
}

fn closed_window() -> Window {
    let mut w = Window::default();
    w.render = false;
    w.state = WinState::Closed;
    w
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
            win: closed_window(),
            seq: 0,
            seg_start: 0,
            key_t: 0,
            deferred_open: None,
            selecting: false,
        }
    }
}

impl FieldWindow {
    pub fn is_open(&self) -> bool {
        matches!(self.phase, WinPhase::Open | WinPhase::Opening(_))
    }
    /// pixel size of the window (`FieldMessage::SetSize(cols, rows)`)
    pub fn size_px(&self) -> (f32, f32) {
        (self.cols as f32 * REAL_W, self.rows as f32 * REAL_H)
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
    /// `FieldMessage` state 3 / 4 ends with the window animation (`+0xb8` = 1 or 0, `MenuWindow` state idle / closed).
    fn sync_phase(&mut self) {
        let w = &self.win;
        self.phase = if !w.render {
            WinPhase::Closed
        } else if w.closing {
            WinPhase::Closing(1)
        } else if w.state != WinState::Open {
            WinPhase::Opening(1)
        } else {
            WinPhase::Open
        };
    }
    /// The record -> the live window (`CField::OpenWindow`: `FieldMessage::SetSize` + `SetPosition`).
    fn apply_record(&mut self) {
        let (w, h) = self.size_px();
        self.win.size = glam::Vec2::new(w, h);
        // `FieldMessage::SetPosition` of a note window keeps the x (the first `OpenMessage` centres it on the screen)
        let x = if self.kind == 3 { self.win.pos.x } else { self.x as f32 };
        self.win.pos = glam::Vec2::new(x, self.y as f32);
        // `ScrollData` of `FieldMessage::SetSize`: one column as wide as the window, rows of `REAL_H`, `rows` visible
        self.win.set_scroll_cells(1, self.rows as i16, w, REAL_H, 0);
    }
    fn open_now(&mut self, effect: u8, ms: i32) {
        self.created = true;
        self.apply_record();
        self.win.open(Effect::from_code(effect), ms);
        self.sync_phase();
    }
    /// `CField::OpenWindow(effect, ms)` -> `FieldMessage::OpenWindow` -> `MenuWindow::Open`.
    pub fn open_fx(&mut self, effect: u8, ms: i32) {
        self.created = true;
        if self.kind == 3 && self.msg.is_none() && !self.win.render {
            // JP 0x004a1390: a note window only stores the effect (`+0xc0` bits 0-2) and the time (`+0xa4`); `OpenMessage` opens it
            self.deferred_open = Some((effect, ms));
            return;
        }
        self.open_now(effect, ms);
    }
    /// Frames / ms of the old port API: a fade of `ms` milliseconds.
    pub fn open(&mut self, ms: i32) {
        self.open_fx(0, ms);
    }
    /// `CField::CloseWindow(effect, ms)` -> `MenuWindow::Close`; the text goes with the window.
    pub fn close_fx(&mut self, effect: u8, ms: i32) {
        self.deferred_open = None;
        if !self.win.render {
            self.phase = WinPhase::Closed;
            return;
        }
        self.win.close(Effect::from_code(effect), ms);
        if ms <= 0 {
            self.win.finish();
        }
        self.sync_phase();
        if self.phase == WinPhase::Closed {
            self.clear();
        }
    }
    pub fn close(&mut self, ms: i32) {
        self.close_fx(0, ms);
    }
    /// JP: 0x004a1580 `FieldMessage::OpenMessage`: append the text and type the new part.
    pub fn append(&mut self, text: &[u8], speed: TextSpeed) {
        let prev = self.msg.as_ref().map(|m| m.glyphs.len()).unwrap_or(0);
        self.seg_start = self.raw.len();
        self.raw.extend_from_slice(&strip_text_codes(text));
        let mut m = Message::new(self.max_chars.max(0x100), speed);
        field_text_style(&mut m);
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
        if !self.win.render {
            match self.deferred_open.take() {
                // the note window opens with its first message
                Some((e, ms)) => self.open_now(e, ms),
                // a message for a window that was never opened: shown at once (the port's tolerance; the retail window stays hidden)
                None => {
                    self.apply_record();
                    self.win.open(Effect::Fade, 0);
                    self.sync_phase();
                }
            }
        }
    }
    /// JP: 0x004a1740 `FieldMessage::ClearMessage`
    pub fn clear(&mut self) {
        self.raw.clear();
        self.msg = None;
        self.key_pending = false;
        self.seg_start = 0;
        self.selecting = false;
        self.win.set_scroll_cell(0, 0);
    }
    /// Line (0-based, `$` / newline separated) of glyph `g` of the current message.
    pub fn line_of_glyph(&self, g: usize) -> usize {
        let Some(m) = &self.msg else { return 0 };
        m.glyphs.iter().take(g).filter(|x| x.width == 0 || m.text.get(x.start as usize) == Some(&b'$')).count()
    }
    /// One `FieldMessage::Polling` step: `dt` = `MenuObj::sm_iPassTime` (ms).
    pub fn tick(&mut self, dt: i32) {
        let was_closing = self.phase != WinPhase::Closed && self.win.closing;
        if self.win.render {
            self.win.poll(dt);
            self.sync_phase();
        }
        if was_closing && self.phase == WinPhase::Closed {
            self.clear();
        }
        // the typing starts when the window animation is over (state 3 -> 9)
        if !matches!(self.phase, WinPhase::Opening(_)) {
            if let Some(m) = self.msg.as_mut() {
                m.poll(dt);
            }
        }
        self.key_t += dt;
        if self.key_t > KEY_WRAP {
            self.key_t -= KEY_WRAP * 2;
        }
        // state 9: keep the line being typed inside the visible rows (`Scroll(0, row)`)
        if self.phase == WinPhase::Open && !self.selecting {
            if let Some(m) = &self.msg {
                let g = (m.cur_glyph as usize).min(m.glyphs.len());
                let cur = if g == 0 { 0 } else { self.line_of_glyph(g - 1) as i32 };
                let rows = (self.rows as i32).max(1);
                let top = self.scroll_row();
                if cur < top + rows {
                    if cur < top {
                        self.win.scroll_to_cell(0, cur as i16);
                    }
                } else {
                    self.win.scroll_to_cell(0, (cur - (rows - 1)) as i16);
                }
            }
        }
    }
    /// Row at the top of the window (the scroll target).
    pub fn scroll_row(&self) -> i32 {
        let t = self.win.target_offset();
        (-t.y / REAL_H).round() as i32
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

/// `FaceImage` (JP 0x004a0440, 0x1c bytes + `FaceImageData` 0x184): a portrait `MENU/FACE/FI_%03d.TEX` (104 x 128, `FileManeger::GetHandle(id)`
/// of the `sm_pFace` manager) on a `MenuPolygon` with UV (0, 0) .. (0x66, 0x80) inside its own plain `MenuWindow` of priority 0x10 (above
/// every message window).  `LoadFace` sets the size 96 x 96 (retail; `SetFaceSize` changes it), `OpenFace` / `CloseFace` are
/// `MenuWindow::Open` / `Close` (a fade for effect 0).
#[derive(Debug, Clone)]
pub struct FaceSlot {
    pub loaded: bool,
    pub face_id: i32,
    pub x: f32,
    pub y: f32,
    pub w: f32,
    pub h: f32,
    /// `OpenFace` was called and `CloseFace` was not
    pub open: bool,
    /// the window of the polygon: alpha fade
    pub win: Window,
}

impl Default for FaceSlot {
    fn default() -> Self {
        FaceSlot { loaded: false, face_id: 0, x: 0.0, y: 0.0, w: 0.0, h: 0.0, open: false, win: closed_window() }
    }
}

/// `FaceImage` portrait polygon: UV rectangle in texels.
pub const FACE_UV: (f32, f32) = (102.0, 128.0);

impl FaceSlot {
    /// `FaceImage::Open(effect, ms)`: nothing happens before `LoadFace`.
    pub fn open_fx(&mut self, effect: u8, ms: i32) {
        if !self.loaded {
            return;
        }
        self.open = true;
        self.win.size = glam::Vec2::new(self.w, self.h);
        self.win.open(Effect::from_code(effect), ms);
    }
    pub fn close_fx(&mut self, effect: u8, ms: i32) {
        if !self.loaded || !self.win.render {
            return;
        }
        self.open = false;
        self.win.close(Effect::from_code(effect), ms);
        if ms <= 0 {
            self.win.finish();
        }
    }
    /// shown (opening, open or fading out)
    pub fn visible(&self) -> bool {
        self.loaded && self.win.render
    }
    pub fn tick(&mut self, dt: i32) {
        if self.win.render {
            self.win.poll(dt);
        }
    }
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
    /// next creation number (`FieldWindow::seq`)
    pub seq: u32,
    /// sound effects the windows asked for (`FieldMessage::Polling`: `MenuSound::PlaySE` 0 cursor, 2 confirm, 3 cancel); the drawing system
    /// hands them to the menu sound player
    pub ses: Vec<MenuSe>,
    /// logic ticks since the last reset (cursor spin)
    pub ticks: u32,
    tick_acc: f32,
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
            seq: 0,
            ses: Vec::new(),
            ticks: 0,
            tick_acc: 0.0,
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
    /// `CField::CreateWindow(id, kind, flags, max)`: a new `FieldMessage` in slot `id` (the old one is destroyed with its text).
    pub fn create_window(&mut self, id: usize, kind: u8, flags: u8, max: u16) {
        let id = id.min(MAX_WINDOWS - 1);
        self.seq += 1;
        let (cols, rows) = (30, 3);
        self.windows[id] = FieldWindow { created: true, kind, flags, max_chars: max.max(0x40), cols, rows, seq: self.seq, ..Default::default() };
        self.cur_win = id;
    }
    /// `CField::CreateName(id, kind, flags, max)`: a name plate is a window of 16 x 1 cells (`SetSize(0x10, 1)`).
    pub fn create_name(&mut self, id: usize, kind: u8, flags: u8) {
        let id = id.min(MAX_WINDOWS - 1);
        self.seq += 1;
        self.names[id] = FieldWindow { created: true, kind, flags, cols: 16, rows: 1, seq: self.seq, ..Default::default() };
        self.cur_name = id;
    }
    /// One 60 Hz logic tick: `FieldMessage::Polling` / `FaceImage::Polling` with the pass time of the tick (ms).
    pub fn tick(&mut self) {
        self.ticks = self.ticks.wrapping_add(1);
        self.tick_acc += TICK_MS;
        let dt = self.tick_acc as i32;
        self.tick_acc -= dt as f32;
        // `FieldMessage::SetCursor` -> `MenuWindow::Scroll(rect)`: a vertical list scrolls to keep the cursor row inside the window
        if self.select.active && self.select.mode & 1 == 0 {
            let (cur, w) = (self.select.cursor as i32, &mut self.windows[self.select.window.min(MAX_WINDOWS - 1)]);
            let rows = (w.rows as i32).max(1);
            let top = w.scroll_row();
            if cur < top {
                w.win.scroll_to_cell(0, cur as i16);
            } else if cur >= top + rows {
                w.win.scroll_to_cell(0, (cur - rows + 1) as i16);
            }
        }
        for w in self.windows.iter_mut().chain(self.names.iter_mut()) {
            w.tick(dt);
        }
        for f in self.faces.iter_mut() {
            f.tick(dt);
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
                w.tick(17);
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
