//! Game-over screen: `GameOver` (a `Menu`) + `GameOverScene` + `GameOverSelect`/`GameOverRealize`.
//!
//! JP: 0x003abe10 `GameOver::ReceiveEvent`, 0x003abea0 ctor, 0x003ac270.. `GameOverScene`.
//! Scene data: `MENU/MSD/GAMEOVER.MSD` (resource 0 = `"MENU/IMG/GO/GO_%03d.TEX"`, three text strings
//! `"Load?"`, `"Yes"`, `"No"`, window 0 = full-screen image window, window 1 = the 240x80 question box,
//! cursor 0). The scene's `Run` is a pointer-to-member state machine (`__ptmf` at +0x58):
//! `GetReady -> ReadData -> Realize -> ExitRealize -> SelectLoad -> ExitSelectLoad`.

use crate::dataaccess::Event as DaEvent;

/// Which illustration to show: JP `MENU` section short at 0x29c; negative = random among the
/// bits of the u16 at 0x29e.
pub fn pick_image(chosen: i16, unlocked_mask: u16, rand: u32) -> i16 {
    if chosen >= 0 {
        return chosen;
    }
    let set: Vec<i16> = (0..16).filter(|b| unlocked_mask & (1 << b) != 0).collect();
    if set.is_empty() {
        0
    } else {
        set[(rand as usize) % set.len()]
    }
}

/// JP `GameOverScene` states (function pointer in `+0x58`).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum State {
    /// 0x003ac340 GetReady: allocate the realize object, pick image, order the texture file
    GetReady,
    /// 0x003ac640 ReadData: wait until the texture is loaded (`+0xfa & 1`), build sprite+window, open
    ReadData,
    /// 0x003ac7c0 Realize: window is open; wait for OK (once fully open) or 5000 ticks
    Realize,
    /// 0x003ac930 ExitRealize: wait close; then title or the load question
    ExitRealize,
    /// 0x003acd00 SelectLoad: cursor over Yes/No
    SelectLoad,
    /// 0x003acf60 ExitSelectLoad
    ExitSelectLoad,
    /// the state function was set to `__ptmf_null` (waiting on the load screen)
    WaitLoad,
    Done,
}

#[derive(Clone, Debug, PartialEq)]
pub enum Cmd {
    /// order the illustration texture
    LoadTexture(String),
    /// build the full screen sprite + window 0 and open it (effect from the record flags)
    OpenImageWindow,
    CloseImageWindow,
    /// destroy the realize objects
    ReleaseImage,
    /// build window 1 with texts 0..3 and the cursor on the first answer; open it
    OpenQuestion,
    CloseQuestion,
    MoveCursor { down: bool },
    /// leave the cursor and start the `dataAccess` load screen at the cursor position
    StartLoadScreen,
    /// `opening()` — recreate the title (`CDMYStage` / `openingMessage`)
    ShiftTitle,
    /// destroy the GameOver menu object
    Destroy,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct Inputs {
    pub ok: bool,
    pub up: bool,
    pub down: bool,
    /// texture finished loading
    pub texture_ready: bool,
    /// the window object reports "fully open or fully closed" (JP state byte 0/1)
    pub window_settled: bool,
    /// MENU byte 0x308 != 0: show the Load? question instead of going straight to the title
    pub offer_load: bool,
    /// which answer is under the cursor: id 0 = Yes
    pub cursor_on_yes: bool,
    pub dt: i32,
}

pub struct GameOverScene {
    pub state: State,
    pub image_no: i16,
    /// ticks the image has been shown (`GameOverRealize+0xba`)
    pub shown: i32,
    load_screen: bool,
    texture_fmt: String,
}

impl GameOverScene {
    /// `texture_fmt` is the scene's resource 0 string.
    pub fn new(texture_fmt: impl Into<String>) -> Self {
        GameOverScene { state: State::GetReady, image_no: 0, shown: 0, load_screen: false, texture_fmt: texture_fmt.into() }
    }

    pub fn start(&mut self, chosen: i16, mask: u16, rand: u32) -> Vec<Cmd> {
        self.image_no = pick_image(chosen, mask, rand);
        let path = self.texture_fmt.replacen("%03d", &format!("{:03}", self.image_no), 1);
        self.state = State::ReadData;
        vec![Cmd::LoadTexture(path)]
    }

    pub fn poll(&mut self, i: Inputs) -> Vec<Cmd> {
        let mut out = Vec::new();
        match self.state {
            State::ReadData if i.texture_ready => {
                out.push(Cmd::OpenImageWindow);
                self.shown = 0;
                self.state = State::Realize;
            }
            State::Realize => {
                self.shown += i.dt;
                if (i.window_settled && i.ok) || self.shown > 5000 {
                    out.push(Cmd::CloseImageWindow);
                    self.state = State::ExitRealize;
                }
            }
            State::ExitRealize if i.window_settled => {
                out.push(Cmd::ReleaseImage);
                if !i.offer_load {
                    out.push(Cmd::ShiftTitle);
                    out.push(Cmd::Destroy);
                    self.state = State::Done;
                } else {
                    out.push(Cmd::OpenQuestion);
                    self.state = State::SelectLoad;
                }
            }
            State::SelectLoad if i.window_settled => {
                if i.ok {
                    self.load_screen = i.cursor_on_yes;
                    out.push(Cmd::CloseQuestion);
                    self.state = State::ExitSelectLoad;
                } else if i.up {
                    out.push(Cmd::MoveCursor { down: false });
                } else if i.down {
                    out.push(Cmd::MoveCursor { down: true });
                }
            }
            State::ExitSelectLoad if i.window_settled => {
                if !self.load_screen {
                    out.push(Cmd::ShiftTitle);
                    out.push(Cmd::Destroy);
                    self.state = State::Done;
                } else {
                    out.push(Cmd::StartLoadScreen);
                    self.state = State::WaitLoad;
                }
            }
            _ => {}
        }
        out
    }

    /// JP: 0x003abe10 `GameOver::ReceiveEvent(event, menu)` — events from the `dataAccess` load screen.
    pub fn receive_event(&mut self, e: DaEvent) -> Vec<Cmd> {
        match e {
            DaEvent::Loaded => {
                self.state = State::Done;
                vec![Cmd::Destroy]
            }
            DaEvent::Finished => {
                self.state = State::Done;
                vec![Cmd::ShiftTitle, Cmd::Destroy]
            }
            _ => vec![],
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn flow_to_title() {
        let mut g = GameOverScene::new("MENU/IMG/GO/GO_%03d.TEX");
        let c = g.start(-1, 0b100, 7);
        assert_eq!(c, vec![Cmd::LoadTexture("MENU/IMG/GO/GO_002.TEX".into())]);
        let base = Inputs { window_settled: true, dt: 16, ..Default::default() };
        assert_eq!(g.poll(Inputs { texture_ready: true, ..base }), vec![Cmd::OpenImageWindow]);
        assert!(g.poll(base).is_empty());
        assert_eq!(g.poll(Inputs { ok: true, ..base }), vec![Cmd::CloseImageWindow]);
        let c = g.poll(base);
        assert_eq!(c, vec![Cmd::ReleaseImage, Cmd::ShiftTitle, Cmd::Destroy]);
    }

    #[test]
    fn flow_to_load() {
        let mut g = GameOverScene::new("x%03d");
        g.start(1, 0, 0);
        let b = Inputs { window_settled: true, offer_load: true, dt: 16, ..Default::default() };
        g.poll(Inputs { texture_ready: true, ..b });
        g.poll(Inputs { dt: 6000, ..b });
        assert_eq!(g.state, State::ExitRealize);
        assert_eq!(g.poll(b), vec![Cmd::ReleaseImage, Cmd::OpenQuestion]);
        assert_eq!(g.poll(Inputs { ok: true, cursor_on_yes: true, ..b }), vec![Cmd::CloseQuestion]);
        assert_eq!(g.poll(b), vec![Cmd::StartLoadScreen]);
        assert_eq!(g.receive_event(DaEvent::Loaded), vec![Cmd::Destroy]);
    }
}
