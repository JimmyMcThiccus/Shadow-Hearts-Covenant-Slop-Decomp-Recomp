//! Retail Graveyard soul charge (`SCHARGE.MSD`): the screen of op 0x4d `InvokeCmdScene(a, b)` (only the Graveyard maps GY_08..13_U call it,
//! a = element stone 0..5).  Retail `CField::InvokeCmdScene` builds `CmdRetailSel01` -> `CmdRetailPage01` (US 0x4ddd80 `GetReady`,
//! 0x4def40 the charge handler, 0x4df450 the grade-up sequence, 0x4ded70 the exit, 0x4df950 the "No more Soul Energy." message).
//!
//! * The stone record is `SCHARGE.MSD` attach 1, MDT type 54 row `a`: `{char* name; u8 element; u8 grades (3); i16 need[grade]}`
//!   (40 / 60 / 80 for every stone).  Its state is `MENU + 0x380 + a * 0x10`: `[0]` grade (i8), `[2]` charged energy (i16, cumulative).
//! * The pool is the u16 at `BTL0 + 0` (`*ourBtlSaveDat`, gp-0x7c4c): the Soul Energy the battles brought in.
//! * `b != 0` (a first visit): the charge starts from 0 and the confirm button is held by the game itself (`+0x64` ors 0x2000 into the
//!   pad words); when the stone already had a grade nothing is written back (`+0x3302`).
//! * Holding confirm moves `need[grade] / 90` per frame (but never more than the pool) from the pool into the stone; reaching
//!   `base + need[grade]` clips the charge there, plays the grade-up (SE 0x3004, Yuri's `fac*` motions) and leaves with the grade
//!   one higher.  Cancel leaves; an empty pool on the idle state shows "No more Soul Energy." and leaves on a key.
//!
//! Layout (all absolute, `SCHARGE.MSD`): the stone name / `GRADE.` / `EXP.` / `Next.` block top left (mtext 0..6 + the four underline
//! polygons), the `Soul Energy` banner (attach 4, group at (0, 195)) with the pool, the gauge panel (attach 5 at (0, 222): frame, element
//! kanji cell of attach 3's sheet, rings, 104 x 8 gauge texture `1 + element`), the stone window (attach 3 at (387, 221)), the button
//! report (attach 2 = the common report: `: Charge` / `: Quit`) and the note line ("Press and hold the %i17 button ...").
//! **Not drawn**: the 3D Yuri (`SCCHAR.DAT`, motions `chs_*` / `chb_*` / `fac8..a`) and the 3D stone (`SCSTONE.DAT`, `SCLV_%03d.DAT`).

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba};
use sh2_menu::msd::{ChunkType, Msd};

use crate::cmd_common::{general_frame, white};
use crate::cmd_page::{draw_report, Button, CmdScenes, Env};
use crate::cmd_retail::{gs_poly, rgb, LAVENDER};
use crate::cmd_ui::{blit, draw_sprite_rec, fill, sj, text_run, text_run_h, SceneTex};
use crate::fscreen::{FieldScreen, ScreenFlow, ScreenIo, DT_MS};

const PATH: &str = "MENU/MSD/SCHARGE.MSD";
/// `MENU + 0x380 + stone * 0x10`: grade, +2 charged energy
pub const OFF_STONES: usize = 0x380;
/// frames a full grade takes (`need / 90.0` per frame)
const FRAMES_PER_GRADE: f32 = 90.0;

#[derive(Debug, Clone, Copy, PartialEq)]
enum Phase {
    Open,
    Idle,
    /// `chs_s` / `chb_s`: Yuri raises his hands (state 1)
    Windup(u32),
    Charge,
    /// `chs_e`: the release motion (states 3 / 4)
    Release(u32),
    /// "No more Soul Energy."
    Empty,
    /// the grade-up sequence (`0x4df450`, about 31 + 40 frames plus the windows)
    GradeUp(u32),
    Close,
}

/// One stone row of MDT 54.
#[derive(Debug, Clone, Default, PartialEq)]
pub struct Stone {
    pub name: String,
    pub element: u8,
    pub grades: u8,
    pub need: Vec<i32>,
}

impl Stone {
    pub fn from_mdt(m: &Msd, i: usize) -> Option<Stone> {
        if i >= m.mdt_count(54) {
            return None;
        }
        let d = m.mdt_data(54, i);
        let grades = *d.get(1)?;
        let need = (0..grades as usize).map(|k| d.get(2 + k * 2..4 + k * 2).map(|b| i16::from_le_bytes([b[0], b[1]]) as i32).unwrap_or(0)).collect();
        Some(Stone { name: sj(m.mdt_str(54, i, 0)), element: d[0], grades, need })
    }
    /// energy of the grades below `grade`
    pub fn base(&self, grade: usize) -> i32 {
        self.need.iter().take(grade).sum()
    }
}

/// The charge rule of `CmdRetailPage01` (state 2 of 0x4def40), one frame: returns (new charge, energy taken from the pool, grade reached).
pub fn charge_step(charge: f32, rate: f32, pool: u32, next: i32) -> (f32, u32, bool) {
    let inc = if (pool as f32) < rate { pool as f32 } else { rate };
    let before = charge as i32;
    let mut after = charge + inc;
    let mut took = (after as i32 - before).max(0);
    if after as i32 >= next {
        took -= after as i32 - next;
        after = next as f32;
        return (after, took.max(0) as u32, true);
    }
    (after, took as u32, false)
}

pub struct SoulChargeScreen {
    sc: Arc<CmdScenes>,
    top: Arc<SceneTex>,
    stone_win: Option<Arc<SceneTex>>,
    banner: Option<Arc<SceneTex>>,
    panel: Option<Arc<SceneTex>>,
    stone: Stone,
    idx: usize,
    auto: bool,
    no_write: bool,
    grade: usize,
    charge: f32,
    pool: u32,
    phase: Phase,
    fade: f32,
    t: f32,
    pulse: f32,
}

impl SoulChargeScreen {
    pub fn new(env: &mut Env, a: i32, b: i32) -> Option<Self> {
        let sc = env.scenes()?;
        let top = env.file_scene(PATH)?;
        let mdt = top.msd.attach_scene(1)?;
        let idx = a.clamp(0, 5) as usize;
        let stone = Stone::from_mdt(&mdt, idx)?;
        let o = OFF_STONES + idx * 0x10;
        let st = env.session.save.menu.data.get(o..o + 4).map(|s| (s[0] as i8, i16::from_le_bytes([s[2], s[3]]))).unwrap_or((0, 0));
        let auto = b != 0;
        let (grade, charge, no_write) = if auto { (0, 0.0, st.0 != 0) } else { (st.0.max(0) as usize, st.1.max(0) as f32, false) };
        let pool = soul_energy(env);
        log::info!("soul charge: stone {idx} ({}) grade {grade} charge {charge} pool {pool} auto {auto}", stone.name);
        Some(SoulChargeScreen {
            stone_win: env.nested_scene(PATH, 3),
            banner: env.nested_scene(PATH, 4),
            panel: env.nested_scene(PATH, 5),
            sc,
            top,
            stone,
            idx,
            auto,
            no_write,
            grade,
            charge,
            pool,
            phase: Phase::Open,
            fade: 0.0,
            t: 0.0,
            pulse: 0.0,
        })
    }

    fn maxed(&self) -> bool {
        self.grade >= self.stone.grades as usize
    }
    fn base(&self) -> i32 {
        self.stone.base(self.grade)
    }
    fn need(&self) -> i32 {
        self.stone.need.get(self.grade).copied().unwrap_or(0)
    }
    fn next(&self) -> i32 {
        self.base() + self.need()
    }

    /// `0x4ded70`: the charge (and on a grade-up the grade) goes back to `MENU + 0x380`, the pool to `BTL0 + 0`.
    fn write_back(&self, env: &mut Env) {
        let o = OFF_STONES + self.idx * 0x10;
        if !self.no_write {
            if let Some(s) = env.session.save.menu.data.get_mut(o..o + 4) {
                s[0] = self.grade as u8;
                s[2..4].copy_from_slice(&(self.charge as i32 as i16).to_le_bytes());
            }
        }
        set_soul_energy(env, self.pool);
    }
}

/// The Soul Energy pool (`BTL0 + 0`, u16).
pub fn soul_energy(env: &Env) -> u32 {
    let o = sh2_menu::save::retail_btl::OFF_SOUL;
    env.session.save.btl.data.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as u32).unwrap_or(0)
}

pub fn set_soul_energy(env: &mut Env, v: u32) {
    let o = sh2_menu::save::retail_btl::OFF_SOUL;
    if let Some(b) = env.session.save.btl.data.get_mut(o..o + 2) {
        b.copy_from_slice(&(v.min(9999) as u16).to_le_bytes());
    }
}

impl FieldScreen for SoulChargeScreen {
    fn name(&self) -> &'static str {
        "soulcharge"
    }

    fn state(&self) -> String {
        match self.phase {
            Phase::Open => "open",
            Phase::Idle => "idle",
            Phase::Windup(_) => "windup",
            Phase::Charge => "charge",
            Phase::Release(_) => "release",
            Phase::Empty => "empty",
            Phase::GradeUp(_) => "gradeup",
            Phase::Close => "close",
        }
        .into()
    }

    fn tick(&mut self, env: &mut Env, keys: u16, press: u16, io: &mut ScreenIo) -> ScreenFlow {
        self.t += DT_MS;
        let ok_held = self.auto || io.held & padbit::CIRCLE != 0;
        let ok_press = self.auto || press & padbit::CIRCLE != 0;
        let _ = keys;
        if self.phase == Phase::Charge {
            self.pulse += DT_MS;
        }
        match self.phase {
            Phase::Open => {
                self.fade = (self.fade + DT_MS / 300.0).min(1.0);
                if self.fade >= 1.0 {
                    self.phase = Phase::Idle;
                }
            }
            Phase::Idle => {
                if self.pool == 0 {
                    // `Sub4de840(-1)`: the message window, any key leaves
                    self.phase = Phase::Empty;
                } else if ok_press && !self.maxed() {
                    env.sound(MenuSe::Other(0x3001));
                    self.phase = Phase::Windup(0);
                } else if ok_press {
                    env.sound(MenuSe::Buzzer);
                } else if press & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.phase = Phase::Close;
                }
            }
            Phase::Windup(n) => {
                self.phase = if n >= 20 { Phase::Charge } else { Phase::Windup(n + 1) };
            }
            Phase::Charge => {
                if ok_held && self.pool > 0 {
                    let rate = self.need() as f32 / FRAMES_PER_GRADE;
                    let (c, took, up) = charge_step(self.charge, rate, self.pool, self.next());
                    self.charge = c;
                    self.pool = self.pool.saturating_sub(took);
                    if up {
                        env.sound(MenuSe::Other(0x3004));
                        self.phase = Phase::GradeUp(0);
                    }
                } else {
                    self.phase = Phase::Release(0);
                }
            }
            Phase::Release(n) => {
                self.phase = if n >= 20 { Phase::Idle } else { Phase::Release(n + 1) };
            }
            Phase::Empty => {
                if !self.auto && press & (padbit::CIRCLE | padbit::CROSS) != 0 || self.auto && self.t > 2000.0 {
                    env.sound(MenuSe::Decide);
                    self.phase = Phase::Close;
                }
            }
            Phase::GradeUp(n) => {
                if n >= 31 + 40 + 20 {
                    if !self.no_write {
                        self.grade += 1;
                    }
                    self.phase = Phase::Close;
                } else {
                    self.phase = Phase::GradeUp(n + 1);
                }
            }
            Phase::Close => {
                self.fade = (self.fade - DT_MS / 300.0).max(0.0);
                if self.fade <= 0.0 {
                    self.write_back(env);
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
        let m = &self.top.msd;
        // the graveyard stays visible: only a light veil
        fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, (a as u32 * 0x30 / 0x80) as u8));
        // name / GRADE. / EXP. / Next. block
        for i in 0..m.count(ChunkType::Polygon) {
            if let Some(p) = m.polygon(i) {
                gs_poly(g, &p, 0.0, 0.0, a);
            }
        }
        let res = |i: usize| m.resource_bytes(i).map(sj).unwrap_or_default();
        let at = |i: usize| m.menu_text(i).map(|t| (t.x, t.y)).unwrap_or((0.0, 0.0));
        let (x, y) = at(3);
        text_run(g, x, y - 4.0, &self.stone.name, 0, white(a), Some((1, 1)));
        for k in 0..3 {
            let (x, y) = at(k);
            text_run_h(g, x, y - 3.0, &res(k), 2, rgb(LAVENDER, a), Some((1, 0)), 0.8);
        }
        let shown_grade = if self.maxed() { self.stone.grades as usize } else { self.grade + 1 };
        let (x, y) = at(4);
        self.sc.font_big.draw(g, x, y - 6.0, &format!("{shown_grade}"), white(a));
        let exp = self.charge as i32;
        let rest = if self.maxed() { 0 } else { (self.next() - exp).max(0) };
        let (x, y) = at(5);
        text_run(g, x, y - 4.0, &format!("{exp:>3}"), 0, white(a), Some((1, 1)));
        let (x, y) = at(6);
        text_run(g, x, y - 4.0, &format!("{rest:>3}"), 0, white(a), Some((1, 1)));

        // `Soul Energy` banner + the pool
        if let Some(b) = &self.banner {
            let bm = &b.msd;
            if let Some(gr) = bm.group(0) {
                for i in 0..bm.count(ChunkType::Sprite) {
                    if let Some(sp) = bm.sprite(i) {
                        draw_sprite_rec(g, &sp, b.t(0), gr.x, gr.y, a);
                    }
                }
                if let Some(t) = bm.menu_text(0) {
                    let s = bm.resource_bytes(0).map(sj).unwrap_or_default();
                    text_run_h(g, gr.x + t.x, gr.y + t.y - 3.0, &s, 2, rgb(LAVENDER, a), Some((1, 0)), 0.8);
                }
                let s = format!("{}", self.pool);
                let (w, _) = g.measure_text(0, &sh2_menu::sjis::encode(&s));
                text_run(g, gr.x + 164.0 - w, gr.y + 2.0, &s, 0, white(a), Some((1, 1)));
            }
        }
        let kanji = self.stone_win.as_ref().and_then(|s| s.t(7));
        let rings = self.stone_win.as_ref().and_then(|s| s.t(8));
        let el = self.stone.element.min(6) as f32;
        let glow = if self.phase == Phase::Charge || matches!(self.phase, Phase::GradeUp(_)) { 0.5 + 0.5 * (self.pulse / 160.0).sin() } else { 0.0 };
        // gauge panel
        if let Some(p) = &self.panel {
            let pm = &p.msd;
            let (ox, oy) = pm.window(0).map(|w| (w.x, w.y)).unwrap_or((0.0, 222.0));
            if let Some(s) = pm.sprite(0) {
                draw_sprite_rec(g, &s, p.t(0), ox, oy, a);
            }
            if let Some(s) = pm.sprite(2) {
                draw_sprite_rec(g, &s, rings, ox, oy, a);
            }
            if let Some(s) = pm.sprite(3) {
                let ga = (a as f32 * glow) as u8;
                if ga > 0 {
                    blit(g, rings, ox + s.x, oy + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), Rgba::new(s.rgba[0], s.rgba[1], s.rgba[2], ga));
                }
            }
            if let Some(s) = pm.sprite(1) {
                blit(g, kanji, ox + s.x, oy + s.y, s.w, s.h, (el * 20.0, 0.0, el * 20.0 + 20.0, 23.0), white(a));
            }
            if let Some(s) = pm.sprite(4) {
                let frac = if self.maxed() { 1.0 } else if self.need() > 0 { ((self.charge - self.base() as f32) / self.need() as f32).clamp(0.0, 1.0) } else { 0.0 };
                let w = s.w * frac;
                if w > 0.0 {
                    blit(g, p.t(1 + self.stone.element.min(6) as usize), ox + s.x, oy + s.y, w, s.h, (0.0, 0.0, 104.0 * frac, 8.0), white(a));
                }
            }
        }
        // the stone window (the 3D stone is not drawn: its ring and kanji)
        if let Some(sw) = &self.stone_win {
            let wm = &sw.msd;
            let (ox, oy) = wm.window(0).map(|w| (w.x, w.y)).unwrap_or((387.0, 221.0));
            for i in [1usize, 2] {
                if let Some(s) = wm.sprite(i) {
                    draw_sprite_rec(g, &s, rings, ox, oy, a);
                }
            }
            if let Some(s) = wm.sprite(0) {
                blit(g, kanji, ox + s.x, oy + s.y, s.w, s.h, (el * 20.0, 0.0, el * 20.0 + 20.0, 23.0), white(a));
            }
        }
        // button report + note
        if let Some(rf) = &self.sc.retail {
            draw_report(g, rf, &self.sc.cmn, &[(Button::Circle, 2), (Button::Cross, 3)], 0.0, a);
        }
        fill(g, 0.0, 418.0, 512.0, 30.0, Rgba::new(0, 0, 0, (a as u32 * 0x48 / 0x80) as u8));
        let note = res(5);
        let mut x = 30.0;
        for (k, part) in note.split("%i17").enumerate() {
            if k > 0 {
                x += crate::cmd_help_retail::draw_inline_icon(g, &self.sc, 17, x, 422.0, a);
            }
            text_run(g, x, 424.0, part, 0, white(a), Some((1, 1)));
            let (w, _) = g.measure_text(0, &sh2_menu::sjis::encode(part));
            x += w;
        }
        match self.phase {
            Phase::Empty => {
                let s = res(6);
                let (w, _) = g.measure_text(0, &sh2_menu::sjis::encode(&s));
                general_frame(g, &self.sc.cmn, 256.0 - w * 0.5 - 24.0, 196.0, w + 48.0, 52.0, a);
                text_run(g, 256.0 - w * 0.5, 212.0, &s, 0, white(a), Some((1, 1)));
            }
            Phase::GradeUp(n) => {
                // the flare (`MenuEffectModel`) and the grade-up window of the original: a white flash and the new grade
                let f = if n < 16 { n as f32 / 16.0 } else { (1.0 - (n as f32 - 16.0) / 30.0).max(0.0) };
                fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0x80, 0x80, 0x80, (a as f32 * 0.5 * f) as u8));
                if n > 31 {
                    let s = format!("{} {}", res(0).trim_end_matches('.'), self.grade + 2);
                    let (w, _) = g.measure_text(0, &sh2_menu::sjis::encode(&s));
                    general_frame(g, &self.sc.cmn, 256.0 - w * 0.5 - 24.0, 196.0, w + 48.0, 52.0, a);
                    text_run(g, 256.0 - w * 0.5, 212.0, &s, 0, white(a), Some((1, 1)));
                }
            }
            _ => {}
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn charge_clips_at_the_grade_and_never_overdraws_the_pool() {
        // 40 energy / 90 frames from a full pool: 90 frames reach the grade exactly
        let (mut c, mut pool, mut up) = (0.0f32, 500u32, false);
        let mut frames = 0;
        while !up {
            let (n, took, u) = charge_step(c, 40.0 / 90.0, pool, 40);
            c = n;
            pool -= took;
            up = u;
            frames += 1;
            assert!(frames < 200);
        }
        assert_eq!(c as i32, 40);
        assert_eq!(pool, 460);
        assert!((89..=91).contains(&frames));
        // a pool of 3 runs dry at 3
        let (mut c, mut pool) = (0.0f32, 3u32);
        for _ in 0..50 {
            let (n, took, _) = charge_step(c, 40.0 / 90.0, pool, 40);
            c = n;
            pool -= took;
        }
        assert_eq!(pool, 0);
        assert_eq!(c as i32, 3);
    }

    #[test]
    fn stone_bases_are_cumulative() {
        let s = Stone { name: "Earth Stone".into(), element: 0, grades: 3, need: vec![40, 60, 80] };
        assert_eq!((s.base(0), s.base(1), s.base(2), s.base(3)), (0, 40, 100, 180));
    }
}
