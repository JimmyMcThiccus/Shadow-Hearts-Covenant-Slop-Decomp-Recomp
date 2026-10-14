//! The Data entry of the top menu (`CmdTopMenuData` -> `dataAccess`, JP 0x00392000): save / load slot list.
//!
//! Real flow on the real file layer: [`sh2_menu::session::save_session`] / [`load_session`] on the user-data directory
//! ([`sh2_menu::session::FileStorage`], `SaveManager` keeps the system file's slot table), slot summaries are the `SlotInfo` records
//! of the system file (leader, level, play time, cash, location).  Location names come from `MENU/DAT/SAVELIST.MDT`.  A successful
//! load asks the host to re-enter the field on the loaded map ([`HostReq::LoadedGame`]).

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba};
use sh2_menu::msd::Msd;
use sh2_menu::save::SLOT_COUNT;
use sh2_menu::session::{load_session, save_session};
use sh2_menu::storage::SaveManager;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const VISIBLE: usize = 5;
const ROW_H: f32 = 60.0;

#[derive(Clone, Debug, Default)]
struct SlotView {
    used: bool,
    leader: String,
    level: u8,
    location: String,
    time_ms: u32,
    cash: u32,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Slots,
    Confirm { yes: bool },
}

/// Demo / retail wording.
fn tr(jp: String, en: String) -> String {
    if sh2_core::boot::is_retail() { en } else { jp }
}
fn tr_s(jp: &'static str, en: &'static str) -> &'static str {
    if sh2_core::boot::is_retail() { en } else { jp }
}

pub struct DataPage {
    sc: std::sync::Arc<CmdScenes>,
    load: bool,
    slots: Vec<SlotView>,
    list: ListState,
    mode: Mode,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    msg: Option<(String, f32)>,
    note: String,
    /// location table of `SAVELIST.MDT`: id -> name
    places: Vec<(u32, String)>,
    /// where the player is now (`SAVELIST.MDT` name of `MENU+8`, else the map name)
    here: String,
}

/// `(location id, name)` rows of `MENU/DAT/SAVELIST.MDT`.
pub fn load_places(env: &Env) -> Vec<(u32, String)> {
    use sh2_menu::disc::FileSource;
    let Some(d) = env.assets.disc.as_ref() else { return vec![] };
    let Some(m) = d.read("MENU/DAT/SAVELIST.MDT").and_then(|b| Msd::parse(b).ok()) else { return vec![] };
    let ty = m.chunks.first().map(|c| c.raw_type).unwrap_or(45);
    (0..m.mdt_count(ty))
        .map(|i| {
            let id = m.mdt_data(ty, i).get(..4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]])).unwrap_or(0);
            (id, sj(m.mdt_str(ty, i, 0)))
        })
        .collect()
}

impl DataPage {
    pub fn new(env: &mut Env, load: bool) -> Option<Self> {
        let places = load_places(env);
        let sc = env.scenes()?;
        let mut p = DataPage {
            sc,
            load,
            slots: Vec::new(),
            list: ListState::new(VISIBLE, SLOT_COUNT),
            mode: Mode::Slots,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(0, 240, (420.0, 320.0)),
            time: 0.0,
            msg: None,
            note: String::new(),
            places,
            here: String::new(),
        };
        p.here = p.place_name(env);
        p.refresh(env);
        // start on the last used slot when saving
        if let Ok(m) = SaveManager::open(env.dev) {
            p.list.sel = (m.system.current_slot as usize).min(SLOT_COUNT - 1);
            p.list.set_len(SLOT_COUNT);
        }
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn refresh(&mut self, env: &mut Env) {
        self.slots = vec![SlotView::default(); SLOT_COUNT];
        if let Ok(m) = SaveManager::open(env.dev) {
            for (i, s) in m.slot_infos().iter().enumerate().take(SLOT_COUNT) {
                if !s.used {
                    continue;
                }
                let loc = sj(&s.location);
                self.slots[i] = SlotView { used: true, leader: sj(&s.leader_name), level: s.level, location: loc, time_ms: s.play_time_ms, cash: s.cash };
            }
        }
    }

    fn origin() -> (f32, f32) {
        (40.0, 70.0)
    }

    fn cursor_to_sel(&mut self) {
        let (x, y) = Self::origin();
        self.cursor.set_target(x - 6.0, y + self.list.slot() as f32 * ROW_H + 24.0);
    }

    fn place_name(&self, env: &Env) -> String {
        let id = env.session.save.menu.location_id();
        self.places.iter().find(|p| p.0 == id).map(|p| p.1.clone()).unwrap_or_else(|| env.session.map.clone())
    }

    fn do_it(&mut self, env: &mut Env) {
        let slot = self.list.sel as u8;
        if self.load {
            match load_session(env.dev, env.session, slot) {
                Ok(()) => {
                    env.req.push(HostReq::Toast(tr(format!("ロードしました（スロット{}）", slot + 1), format!("Loaded slot {}.", slot + 1))));
                    env.req.push(HostReq::LoadedGame);
                }
                Err(e) => self.msg = Some((tr(format!("ロードに失敗しました: {e}"), format!("Load failed: {e}")), 2500.0)),
            }
        } else {
            match save_session(env.dev, env.session, slot) {
                Ok(()) => {
                    env.sound(MenuSe::Other(0x1000));
                    self.msg = Some((tr(format!("セーブしました（スロット{}）", slot + 1), format!("Saved to slot {}.", slot + 1)), 2500.0));
                    self.refresh(env);
                }
                Err(e) => self.msg = Some((tr(format!("セーブに失敗しました: {e}"), format!("Save failed: {e}")), 2500.0)),
            }
        }
    }
}

impl Page for DataPage {
    fn page(&self) -> CmdPage {
        CmdPage::Top
    }
    fn title(&self) -> usize {
        10
    }
    fn note(&self) -> String {
        if let Some((m, _)) = &self.msg {
            return m.clone();
        }
        match self.mode {
            Mode::Slots => {
                if self.load {
                    tr("ロードするデータを選んでください。".to_string(), "Select the data to load.".to_string())
                } else {
                    tr("セーブするスロットを選んでください。".to_string(), "Select the slot to save to.".to_string())
                }
            }
            Mode::Confirm { .. } => {
                if self.load {
                    tr("このデータをロードしますか？".to_string(), "Load this data?".to_string())
                } else if self.slots.get(self.list.sel).map(|s| s.used).unwrap_or(false) {
                    tr("上書きしてセーブしますか？".to_string(), "Overwrite this data?".to_string())
                } else {
                    tr("このスロットにセーブしますか？".to_string(), "Save to this slot?".to_string())
                }
            }
        }
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        if let Some((_, t)) = self.msg.as_mut() {
            *t -= DT;
            if *t <= 0.0 {
                self.msg = None;
            }
        }
        match self.mode {
            Mode::Slots => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::CIRCLE != 0 {
                    let used = self.slots.get(self.list.sel).map(|s| s.used).unwrap_or(false);
                    if self.load && !used {
                        env.sound(MenuSe::Buzzer);
                    } else {
                        env.sound(MenuSe::Decide);
                        self.mode = Mode::Confirm { yes: true };
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Confirm { yes } => {
                if keys & (padbit::UP | padbit::DOWN | padbit::LEFT | padbit::RIGHT) != 0 {
                    self.mode = Mode::Confirm { yes: !yes };
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    if yes {
                        self.do_it(env);
                    } else {
                        env.sound(MenuSe::Cancel);
                    }
                    self.mode = Mode::Slots;
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Slots;
                }
            }
        }
        // keep the "current" game summary in step with the play time
        self.note = String::new();
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let dim = Rgba::new(0x70, 0x70, 0x80, a);
        let (x, y) = Self::origin();
        text_run(g, x + 120.0, y - 26.0, &self.here, 14, white, Some((1, 1)));
        text_run(g, x, y - 26.0, if self.load { tr_s("ロード", "Load") } else { tr_s("セーブ", "Save") }, 14, Rgba::new(0x80, 0xc0, 0xff, a), Some((1, 1)));
        for (slot, i) in (self.list.top..SLOT_COUNT).take(VISIBLE).enumerate() {
            let s = &self.slots[i];
            let ry = y + slot as f32 * ROW_H;
            let sel = i == self.list.sel;
            panel(g, x, ry, 420.0, ROW_H - 6.0, a);
            if sel {
                row_bar(g, x + 2.0, ry + 2.0, 416.0, ROW_H - 10.0, a);
            }
            text_run(g, x + 12.0, ry + 4.0, &format!("DATA {:02}", i + 1), 0, Rgba::new(0x80, 0xc0, 0xff, a), Some((1, 1)));
            if s.used {
                text_run(g, x + 100.0, ry + 4.0, &s.leader, 0, white, Some((1, 1)));
                text_run(g, x + 220.0, ry + 4.0, &format!("Lv.{}", s.level), 0, white, Some((1, 1)));
                text_run(g, x + 12.0, ry + 28.0, &s.location, 14, white, Some((1, 1)));
                let t = s.time_ms / 1000;
                text_run(g, x + 230.0, ry + 28.0, &format!("{}:{:02}:{:02}", t / 3600, (t / 60) % 60, t % 60), 14, dim, Some((1, 1)));
                text_run(g, x + 330.0, ry + 28.0, &format!("{} G", s.cash), 14, dim, Some((1, 1)));
            } else {
                text_run(g, x + 100.0, ry + 4.0, "-- NO DATA --", 0, dim, None);
            }
        }
        draw_scroll_marks(g, x + 210.0, y - 4.0, y + VISIBLE as f32 * ROW_H - 6.0, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        if let Mode::Confirm { yes } = self.mode {
            general_frame(g, &self.sc.cmn, 150.0, 160.0, 212.0, 100.0, a);
            text_run(g, 164.0, 170.0, &self.note(), 14, white, Some((1, 1)));
            for (k, (label, on)) in [("はい", yes), ("いいえ", !yes)].iter().enumerate() {
                text_run(g, 190.0, 200.0 + k as f32 * 24.0, label, 0, if *on { Rgba::new(0x80, 0x80, 0x30, a) } else { white }, Some((1, 1)));
            }
        } else {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}
