//! Retail `CmdScore` (page 13 "Score", US `SetScore` 0x4ada00, `GetScore` 0x4ade00, `GetComment` 0x4ae290, `CmdScoreRank::GetRank`
//! 0x4afb50), checked against the live PCSX2 capture `score_a` (`notes/integration/r5_mn.md`).
//!
//! Top-lit backdrop; one framed panel (window 2: (20, 58) 472 x 332) titled `< Grand Total >` (left / right change the category: Grand
//! Total, Battle Data, Ring Data, Battles Joined = text entries 0..3); `Current Score` / `Current Rating` headers; one row per statistic
//! (Grand Total = `GetScore` cases 0..9, Battle Data = 10..19: label right-aligned at x 196, value right-aligned at x 306, the rating comment
//! at x 327 = `GetComment(table, value)`: the comment tables are chunks 29.. of `SCORE.MSD` attach 0, `{text, u32 limit}` rows, the first
//! limit above the value (or negative) wins; the table of a row is the low word of its text entry's tag, 0 = no comment).  Grand Total ends
//! with the `Rank` box: the rank (`GetRank`) and its title (chunk 45: rank `n` = row `n - 1`), the next better rank dimmed above it.
//! Ring Data lists every member's ring / perfect success rate, Battles Joined their rounds.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::msd::Msd;
use sh2_menu::score::{ScoreTotals, ScoreValue};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const PATH: &str = "MENU/MSD/SCORE.MSD";
/// row tops (live `score_a`: first row centre 101.5, 22.2 px apart)
const ROW0: f32 = 77.0;
const PITCH: f32 = 22.2;

pub struct RetailScorePage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    mdt: Option<Msd>,
    totals: ScoreTotals,
    members: Vec<(String, u8)>,
    cat: usize,
    slide: Slide,
    title_img: Option<(TextureId, (u32, u32))>,
}

impl RetailScorePage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let mdt = scene.msd.attach_scene(0);
        let mut totals = ScoreTotals::from_save(&env.session.save.btl, &env.session.save.menu);
        totals.distance_km = env.session.distance / 1000.0;
        let members = party_view(env.session).into_iter().map(|p| (p.name, p.id)).collect();
        let title_img = scene.t(1).map(|t| (t, scene.tex_size(1)));
        Some(RetailScorePage { sc, scene, mdt, totals, members, cat: 0, slide: Slide::open(0, 240, (472.0, 332.0)), title_img })
    }

    fn comment(&self, table: u16, value: i32) -> String {
        let Some(m) = &self.mdt else { return String::new() };
        for i in 0..m.mdt_count(table) {
            let lim = m.mdt_data(table, i).get(0..4).map(|b| i32::from_le_bytes([b[0], b[1], b[2], b[3]])).unwrap_or(-1);
            if lim < 0 || value < lim {
                return sj(m.mdt_str(table, i, 0));
            }
        }
        String::new()
    }

    fn rank_title(&self, rank: i32) -> String {
        self.mdt.as_ref().map(|m| sj(m.mdt_str(45, (rank - 1).max(0) as usize, 0))).unwrap_or_default()
    }
}

impl Page for RetailScorePage {
    fn page(&self) -> CmdPage {
        CmdPage::Score
    }
    fn title(&self) -> usize {
        6
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn backdrop(&self) -> Option<usize> {
        Some(1)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        Some(Vec::new())
    }
    fn note(&self) -> String {
        let alt = self.scene.msd.text_entry(self.cat).map(|e| sj(e.1)).unwrap_or_default();
        if self.cat == 0 {
            let r = self.totals.rank();
            return cfmt(&alt, &[r.into(), self.rank_title(r).as_str().into()]);
        }
        alt
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        if keys & padbit::LEFT != 0 {
            self.cat = (self.cat + 3) % 4;
            env.sound(MenuSe::CursorMove);
        } else if keys & padbit::RIGHT != 0 {
            self.cat = (self.cat + 1) % 4;
            env.sound(MenuSe::CursorMove);
        } else if keys & (padbit::CROSS | padbit::CIRCLE) != 0 {
            env.sound(MenuSe::Cancel);
            return Flow::Back;
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let m = &self.scene.msd;
        let (px, py, pw, ph) = m.window(2).map(|w| (w.x, w.y, w.w, w.h)).unwrap_or((20.0, 58.0, 472.0, 332.0));
        general_frame(g, &self.sc.cmn, px - 14.0, py - 16.0, pw + 28.0, ph + 12.0, a);
        // the live panel is dark inside (style 6 window)
        fill(g, px, py - 6.0, pw, ph - 12.0, Rgba::new(0x08, 0x08, 0x0c, (a as u32 * 0x50 / 0x80) as u8));
        let hs = 0.8;
        let txt = |i: usize| m.text(i).map(sj).unwrap_or_default();
        let res = |i: usize| m.resource_bytes(i).map(sj).unwrap_or_default();
        // `< Category >`
        let title = txt(self.cat);
        let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&title));
        let cx = 280.0;
        text_run_h(g, cx - tw * hs * 0.5, 18.0, &title, 0, white(a), None, hs);
        if let Some(t) = self.sc.cmn.s.t(4) {
            blit(g, Some(t), cx - tw * hs * 0.5 - 26.0, 18.0, 24.0, 22.0, (0.0, 2.0 * 22.0, 24.0, 3.0 * 22.0), white(a));
            blit(g, Some(t), cx + tw * hs * 0.5 + 2.0, 18.0, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), white(a));
        }
        let right = |g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, c: Rgba| {
            let (w, _) = g.measure_text(0, &sh2_menu::sjis::encode(s));
            text_run_h(g, x - w * hs, y, s, 0, c, None, hs);
        };
        let center = |g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, c: Rgba| {
            let (w, _) = g.measure_text(0, &sh2_menu::sjis::encode(s));
            text_run_h(g, x - w * hs * 0.5, y, s, 0, c, None, hs);
        };
        match self.cat {
            0 | 1 => {
                center(g, 262.0, 52.0, &res(0), white(a));
                center(g, 405.0, 52.0, &res(1), white(a));
                let cases: Vec<usize> = if self.cat == 0 { (0..10).collect() } else { (10..20).collect() };
                for (k, &case) in cases.iter().enumerate() {
                    let y = ROW0 + k as f32 * PITCH;
                    let e = m.text_entry(4 + case);
                    right(g, 196.0, y, &txt(4 + case), white(a));
                    let v = self.totals.value(case);
                    let s = match v {
                        ScoreValue::Km(km) => format!("{km:.2}KM"),
                        ScoreValue::Int(n) if case == 0xf => format!("{n}HIT"),
                        _ => v.text(),
                    };
                    right(g, 294.0, y, &s, white(a));
                    let table = e.map(|e| (e.2 & 0xffff) as u16).unwrap_or(0);
                    if table != 0 {
                        text_run_h(g, 327.0, y, &self.comment(table, self.totals.comment_value(case)), 0, white(a), None, hs);
                    }
                }
                if self.cat == 0 {
                    self.draw_rank(g, a);
                }
            }
            2 => {
                center(g, 262.0, 52.0, &res(6), white(a));
                center(g, 405.0, 52.0, &res(7), white(a));
                for (k, (name, id)) in self.members.iter().enumerate().take(12) {
                    let y = ROW0 + k as f32 * PITCH;
                    let ms = self.totals.members.get(*id as usize).copied().unwrap_or_default();
                    let pct = |p: (u32, u32)| if p.1 == 0 { 0.0 } else { p.0 as f32 / p.1 as f32 * 100.0 };
                    right(g, 196.0, y, name, white(a));
                    right(g, 294.0, y, &format!("{:.2}%", pct(ms.ring)), white(a));
                    right(g, 446.0, y, &format!("{:.2}%", pct(ms.perfect)), white(a));
                }
            }
            _ => {
                for (k, (name, id)) in self.members.iter().enumerate().take(12) {
                    let y = ROW0 + k as f32 * PITCH;
                    let ms = self.totals.members.get(*id as usize).copied().unwrap_or_default();
                    right(g, 196.0, y, name, white(a));
                    right(g, 294.0, y, &cfmt(&res(11), &[(ms.joined as i32).into()]), white(a));
                }
            }
        }
    }
}

impl RetailScorePage {
    /// `Rank` at (102, 352), the box (165..382, 348..373) with the rank and its title, the next better rank dimmed above it.
    fn draw_rank(&self, g: &mut dyn MenuGfx, a: u8) {
        let hs = 0.8;
        let r = self.totals.rank();
        let label = self.scene.msd.text(24).map(sj).unwrap_or_else(|| "Rank".into());
        text_run_h(g, 102.0, 337.0, &label, 0, white(a), None, hs);
        fill(g, 166.0, 334.0, 216.0, 24.0, Rgba::new(0x10, 0x10, 0x18, (a as u32 * 0x60 / 0x80) as u8));
        let frame = Rgba::new(0x50, 0x50, 0x5c, a);
        fill(g, 165.0, 333.0, 218.0, 1.0, frame);
        fill(g, 165.0, 358.0, 218.0, 1.0, frame);
        fill(g, 165.0, 333.0, 1.0, 26.0, frame);
        fill(g, 382.0, 333.0, 1.0, 26.0, frame);
        let center = |g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, c: Rgba| {
            let (w, _) = g.measure_text(0, &sh2_menu::sjis::encode(s));
            text_run_h(g, x - w * hs * 0.5, y, s, 0, c, None, hs);
        };
        center(g, 196.0, 337.0, &format!("{r}"), white(a));
        center(g, 303.0, 337.0, &self.rank_title(r), white(a));
        if r > 1 {
            let dim = Rgba::new(0x80, 0x80, 0x80, a / 3);
            center(g, 196.0, 308.0, &format!("{}", r - 1), dim);
            center(g, 303.0, 308.0, &self.rank_title(r - 1), dim);
        }
    }
}
