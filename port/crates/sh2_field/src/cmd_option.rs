//! `CmdOption` (page 16, JP 0x00446be0): system settings, stored in the `MENU` save block.
//!
//! Rows and option texts come from `MENU/MSD/OPTION.MSD` (text table entries 0..9 = row labels, 10..29 = option texts with the
//! explanation line in the alternate string).  What each row writes:
//!
//! | row | `MENU` byte | meaning |
//! |---|---|---|
//! | vibration | `0x274` bits 0-1 | 0 off, 1 weak, 2 strong (`CVibeMan::SetMode`) |
//! | sound | `0x274` bits 2-3 | 0 stereo, 1 mono, 2 5.1 (`UpdateSoundOut`, `Sdrv::SetMode`) |
//! | brightness | `0x278` | 1..10, `CApp::SetBright(v * 0.03 + 0.7)` |
//! | message speed | `0x274` bits 4-5 | slow / normal / fast / instant (`MenuMessage`) |
//! | battle cursor | `0x274` bit 6 | remember the last battle command |
//! | subtitles / navi map / shortcuts | `0x275` bits 0-1 / 2-3 / 4-5 | 2-bit fields (`CmdOption` JP 0x446be0 rows 6 / 7 / 8, retail `CField::Update` reads `(0x275 & 0xf) >> 2 == 0` = map shown); shortcuts also write `0x276` bits 0-1 = `value ^ 1` |

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::save::MenuSave;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 24.0;

struct Row {
    label: usize,
    /// option text entries and their stored values
    opts: &'static [(usize, u8)],
}

const ROWS: [Row; 9] = [
    Row { label: 0, opts: &[] },
    Row { label: 1, opts: &[(10, 2), (11, 1), (12, 0)] },
    Row { label: 2, opts: &[(13, 0), (14, 1), (15, 2)] },
    Row { label: 3, opts: &[] },
    Row { label: 4, opts: &[(16, 0), (17, 1), (18, 2), (19, 3)] },
    Row { label: 5, opts: &[(20, 1), (21, 0)] },
    Row { label: 6, opts: &[(22, 0), (23, 1)] },
    Row { label: 7, opts: &[(24, 0), (25, 1)] },
    Row { label: 8, opts: &[(26, 1), (27, 0)] },
];

/// The retail option scene: no "Shortcuts" row (the combo switch moved into the command menu), options renumbered (`Loading` is a hardware choice
/// and not listed).
const ROWS_RETAIL: [Row; 8] = [
    Row { label: 0, opts: &[] },
    Row { label: 1, opts: &[(9, 2), (10, 1), (11, 0)] },
    Row { label: 2, opts: &[(12, 0), (13, 1), (14, 2)] },
    Row { label: 3, opts: &[] },
    Row { label: 4, opts: &[(15, 0), (16, 1), (17, 2), (18, 3)] },
    Row { label: 5, opts: &[(19, 1), (20, 0)] },
    Row { label: 6, opts: &[(21, 0), (22, 1)] },
    Row { label: 7, opts: &[(23, 0), (24, 1)] },
];

fn rows() -> &'static [Row] {
    if sh2_core::boot::is_retail() { &ROWS_RETAIL } else { &ROWS }
}

/// Current stored value of option row `row`.
pub fn get_value(menu: &MenuSave, row: usize) -> u8 {
    let o0 = menu.data[MenuSave::OFF_OPT0];
    let o1 = menu.data[MenuSave::OFF_OPT1];
    match row {
        1 => o0 & 3,
        2 => (o0 >> 2) & 3,
        3 => menu.data[MenuSave::OFF_BRIGHT].clamp(1, 10),
        4 => (o0 >> 4) & 3,
        5 => (o0 >> 6) & 1,
        6 => o1 & 1,
        7 => (o1 >> 2) & 3,
        8 => (o1 >> 4) & 1,
        _ => 0,
    }
}

pub fn set_value(menu: &mut MenuSave, row: usize, v: u8) {
    let o0 = &mut menu.data[MenuSave::OFF_OPT0];
    match row {
        1 => *o0 = (*o0 & !3) | (v & 3),
        2 => *o0 = (*o0 & !0xc) | ((v & 3) << 2),
        4 => *o0 = (*o0 & !0x30) | ((v & 3) << 4),
        5 => *o0 = (*o0 & !0x40) | ((v & 1) << 6),
        3 => menu.data[MenuSave::OFF_BRIGHT] = v.clamp(1, 10),
        6 => menu.data[MenuSave::OFF_OPT1] = (menu.data[MenuSave::OFF_OPT1] & !1) | (v & 1),
        7 => menu.data[MenuSave::OFF_OPT1] = (menu.data[MenuSave::OFF_OPT1] & !0xc) | ((v & 3) << 2),
        8 => menu.data[MenuSave::OFF_OPT1] = (menu.data[MenuSave::OFF_OPT1] & !0x10) | ((v & 1) << 4),
        _ => {}
    }
}

pub struct OptionPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    /// indices into the row table that are listed (all of them in the game; the title's `OptionMenu` lists four, item mask 0x4e)
    visible: Vec<usize>,
    /// position in `visible`
    sel: usize,
    /// current values per row
    vals: [u8; 9],
    cursor: CmdCursor,
    slide: Slide,
    title_img: Option<(TextureId, (u32, u32))>,
}

impl OptionPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/OPTION.MSD")?;
        let w = scene.msd.window(0);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = OptionPage {
            sc,
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(240), (300.0, 230.0)),
            scene,
            visible: (0..rows().len()).collect(),
            sel: 0,
            vals: [0; 9],
            cursor: CmdCursor::new(0.0, 0.0),
            title_img,
        };
        p.load(env);
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    /// The title's Options scene (`OptionMenu`, OPENING.BIN 0x468e80): the same `OPTION.MSD` scene with only four items, vibration / sound / brightness / subtitles
    /// (item mask 0x4e = label texts 1, 2, 3, 6).  Retail only; the demo title has no such screen.
    pub fn new_title(env: &mut Env) -> Option<Self> {
        let mut p = Self::new(env)?;
        p.visible = vec![1, 2, 3, 6];
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    /// Row id (index into the row table) under the cursor.
    fn row_id(&self) -> usize {
        self.visible.get(self.sel).copied().unwrap_or(0)
    }

    fn load(&mut self, env: &Env) {
        for r in 0..9 {
            self.vals[r] = get_value(&env.session.save.menu, r);
        }
    }

    fn origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((38.0, 66.0))
    }

    fn cursor_to_sel(&mut self) {
        let (x, y) = self.origin();
        // round 6 MN3: the title's four-item page draws its labels on the retail rows too (the cursor stayed on Vibration there)
        if sh2_core::boot::is_retail() {
            self.cursor.set_target(x - 4.0, Self::retail_row_y(self.row_id()) + 10.0);
            return;
        }
        self.cursor.set_target(x - 4.0, y + self.sel as f32 * ROW_H + 11.0);
    }

    fn title_mode(&self) -> bool {
        self.visible.len() != rows().len()
    }

    /// Retail label row tops (live `cs_sub`: `Button Customization` 74, then 30 px apart; `Sound` has the two-line box and sits 18 lower).
    fn retail_row_y(row: usize) -> f32 {
        const Y: [f32; 8] = [65.0, 95.0, 143.0, 185.0, 215.0, 245.0, 276.0, 306.0];
        Y.get(row).copied().unwrap_or(306.0 + (row as f32 - 7.0) * 30.0)
    }

    /// Retail `CmdOption` (`OPTION.MSD`): labels at x 38, the choices in framed boxes from x 170 (fence-texture 3-slices: three 67 px boxes for
    /// Vibration, the 206 x 58 two-line Sound box, four 50 px Message Speed boxes, two 102 px boxes for Cursor / Subtitles / Navi Map), the
    /// chosen value cyan, the brightness bar of ten segments; the row under the cursor has a cyan label.
    fn draw_retail(&self, g: &mut dyn MenuGfx) {
        let m = &self.scene.msd;
        let Some(w0) = m.window(0) else { return };
        let (_, _, al) = self.slide.offset((w0.x, w0.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let cyan = Rgba::new(0x00, 0x80, 0x80, a);
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let hs = 0.8;
        let bx = m.window(1).map(|w| w.x).unwrap_or(170.0);
        let tex = self.sc.fence_tex;
        let boxed = |g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32| {
            let c = Rgba::new(0x80, 0x80, 0x80, a);
            fill(g, x + 2.0, y + 2.0, w - 4.0, h - 4.0, Rgba::new(0x0a, 0x08, 0x10, (a as u32 * 0x60 / 0x80) as u8));
            blit(g, tex, x, y, 4.0, h, (0.0, 0.0, 4.0, 28.0), c);
            blit(g, tex, x + 4.0, y, w - 8.0, h, (4.0, 0.0, 60.0, 28.0), c);
            blit(g, tex, x + w - 4.0, y, 4.0, h, (60.0, 0.0, 64.0, 28.0), c);
        };
        let centered = |g: &mut dyn MenuGfx, x: f32, w: f32, y: f32, s: &str, c: Rgba| {
            let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(s));
            text_run_h(g, x + (w - tw * hs) * 0.5, y, s, 0, c, None, hs);
        };
        for (k, &i) in self.visible.iter().enumerate() {
            let row = &rows()[i];
            let y = Self::retail_row_y(i);
            let sel = k == self.sel;
            text_run_h(g, w0.x, y, &m.text(row.label).map(sj).unwrap_or_default(), 0, if sel { cyan } else { white }, None, hs);
            let cur = self.cur_opt_index(i);
            let name = |t: usize| m.text(t).map(sj).unwrap_or_default();
            match i {
                3 => {
                    // brightness: a 200 x 8 bar of ten segments (live: dark blue -> cyan across the lit part, the rest dark), thin frame
                    let by = y + 8.0;
                    fill(g, bx, by - 1.0, 202.0, 10.0, Rgba::new(0x30, 0x30, 0x38, a));
                    for s in 0..10u8 {
                        let sx = bx + 1.0 + s as f32 * 20.0;
                        if s < self.vals[3] {
                            let k = s as f32 / 9.0;
                            let c = |l: f32, r: f32| (l + (r - l) * k) as u8;
                            fill(g, sx, by, 19.0, 8.0, Rgba::new(c(12.0, 16.0), c(28.0, 92.0), c(92.0, 104.0), a));
                        } else {
                            fill(g, sx, by, 19.0, 8.0, Rgba::new(0x08, 0x08, 0x0c, a));
                        }
                    }
                }
                2 => {
                    // two-line Sound box: Stereo / Mono on top, Dolby Digital 5.1 below.  Round 6 MN3: 6 px lower (was y - 29): live
                    // `menu5/cmp_opt.png` has the Stereo row 31 px and the Dolby row 58 px under the Vibration label (port 25 / 51), the Sound
                    // label half way between them
                    let top = y - 23.0;
                    for (j, (bxo, bw, byo)) in [(4.0, 98.0, 4.0), (104.0, 98.0, 4.0), (4.0, 198.0, 30.0)].iter().enumerate() {
                        boxed(g, bx + bxo, top + byo, *bw, 24.0);
                        if let Some(&(t, _)) = row.opts.get(j) {
                            centered(g, bx + bxo, *bw, top + byo + 2.0, &name(t), if j == cur { cyan } else { white });
                        }
                    }
                }
                0 => {}
                _ => {
                    let n = row.opts.len().max(1);
                    let (w, gap) = match n {
                        3 => (67.0, 2.0),
                        4 => (50.0, 2.0),
                        _ => (102.0, 2.0),
                    };
                    for (j, &(t, _)) in row.opts.iter().enumerate() {
                        let x = bx + j as f32 * (w + gap);
                        boxed(g, x, y - 4.0, w, 28.0);
                        centered(g, x, w, y, &name(t), if j == cur { cyan } else { white });
                    }
                }
            }
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }

    fn cur_opt_index(&self, row: usize) -> usize {
        rows()[row].opts.iter().position(|o| o.1 == self.vals[row]).unwrap_or(0)
    }
}

impl Page for OptionPage {
    fn page(&self) -> CmdPage {
        CmdPage::Option
    }
    fn title(&self) -> usize {
        8
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        let row = self.row_id();
        let r = &rows()[row];
        if r.opts.is_empty() {
            return self.scene.msd.text_entry(r.label).map(|e| sj(e.1)).unwrap_or_default();
        }
        let i = self.cur_opt_index(row);
        self.scene.msd.text_entry(r.opts[i].0).map(|e| sj(e.1)).unwrap_or_default()
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Dpad, "選択".into()), (Button::Cross, "戻る".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        let nv = self.visible.len();
        if keys & padbit::UP != 0 {
            self.sel = (self.sel + nv - 1) % nv;
            env.sound(MenuSe::CursorMove);
            self.cursor_to_sel();
        } else if keys & padbit::DOWN != 0 {
            self.sel = (self.sel + 1) % nv;
            env.sound(MenuSe::CursorMove);
            self.cursor_to_sel();
        } else if keys & (padbit::LEFT | padbit::RIGHT) != 0 {
            let d: i32 = if keys & padbit::RIGHT != 0 { 1 } else { -1 };
            let row = self.row_id();
            if row == 3 {
                // brightness bar
                let v = (self.vals[3] as i32 + d).clamp(1, 10) as u8;
                if v != self.vals[3] {
                    set_value(&mut env.session.save.menu, 3, v);
                    self.vals[3] = v;
                    env.sound(MenuSe::Other(1));
                }
            } else if !rows()[row].opts.is_empty() {
                let n = rows()[row].opts.len() as i32;
                let cur = self.cur_opt_index(row) as i32;
                let new = (cur + d).clamp(0, n - 1);
                if new != cur {
                    let v = rows()[row].opts[new as usize].1;
                    set_value(&mut env.session.save.menu, row, v);
                    self.vals[row] = v;
                    env.sound(MenuSe::Other(1));
                }
            }
        } else if keys & padbit::CIRCLE != 0 && self.row_id() == 0 {
            env.sound(MenuSe::Decide);
            if let Some(p) = crate::cmd_pages::make_page(env, CmdPage::KeyCustom, None) {
                return Flow::Open(p);
            }
        } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
            env.sound(MenuSe::Cancel);
            return Flow::Back;
        }
        Flow::Stay
    }

    fn backdrop(&self) -> Option<usize> {
        (sh2_core::boot::is_retail() && !self.title_mode()).then_some(1)
    }
    fn shows_root_list(&self) -> bool {
        sh2_core::boot::is_retail() && !self.title_mode()
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        sh2_core::boot::is_retail().then(Vec::new)
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        if sh2_core::boot::is_retail() {
            self.draw_retail(g);
            return;
        }
        let m = &self.scene.msd;
        let Some(w0) = m.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w0.x, w0.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let dim = Rgba::new(0x70, 0x70, 0x80, a);
        let hi = Rgba::new(0x80, 0x80, 0x30, a);
        general_frame(g, &self.sc.cmn, w0.x + dx - 14.0, w0.y + dy - 10.0, 332.0, self.visible.len() as f32 * ROW_H + 14.0, a);
        let vx = m.window(1).map(|w| w.x).unwrap_or(170.0);
        for (k, &i) in self.visible.iter().enumerate() {
            let row = &rows()[i];
            let y = w0.y + dy + k as f32 * ROW_H;
            let sel = k == self.sel;
            if sel {
                row_bar(g, w0.x + dx - 8.0, y - 1.0, 318.0, ROW_H - 2.0, a);
            }
            text_run(g, w0.x + dx, y, &m.text(row.label).map(sj).unwrap_or_default(), 0, if sel { white } else { dim }, Some((1, 1)));
            if i == 3 {
                // brightness: ten segments
                for s in 0..10 {
                    let on = (s as u8) < self.vals[3];
                    fill(g, vx + dx + s as f32 * 17.0, y + 3.0, 14.0, 12.0, if on { Rgba::new(0x60, 0xa0, 0xf0, a) } else { Rgba::new(0x30, 0x30, 0x40, a) });
                }
                continue;
            }
            let mut x = vx + dx;
            for (k, &(t, _)) in row.opts.iter().enumerate() {
                let name = m.text(t).map(sj).unwrap_or_default();
                let on = k == self.cur_opt_index(i);
                let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&name));
                text_run(g, x, y, &name, 0, if on { hi } else { dim }, Some((1, 1)));
                x += tw + 18.0;
            }
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn option_bits_roundtrip() {
        let mut m = MenuSave::new_default();
        // defaults of `SaveMenuSection::SetDefault`: weak vibration, stereo, normal speed, remember cursor
        assert_eq!(get_value(&m, 1), 1);
        assert_eq!(get_value(&m, 2), 0);
        assert_eq!(get_value(&m, 4), 1);
        assert_eq!(get_value(&m, 5), 1);
        for row in [1usize, 2, 4, 5, 6, 7, 8] {
            for v in 0..2u8 {
                set_value(&mut m, row, v);
                assert_eq!(get_value(&m, row), v, "row {row}");
            }
        }
        set_value(&mut m, 4, 3);
        assert_eq!(get_value(&m, 4), 3);
        assert_eq!(m.vibration_mode(), 1);
        set_value(&mut m, 3, 12);
        assert_eq!(get_value(&m, 3), 10);
    }
}
