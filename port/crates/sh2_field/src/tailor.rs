//! The tailor (`tailor`, JP FIELD.BIN 0x004eafe0 .. 0x004f20a0, US 0x00534370 ..): Cornelia's dress shop.
//!
//! Opened by `SpecialMenu(0x300)` (`CField::cbTailor`, `tailor::initialize(cb, field, mode 0)`).  The player pages through a sketch book of
//! dresses (`mMakeSketchBook`: the dress ids whose bit is set in the tailor flag word, default `0x3fe` = dresses 1..9), picks one
//! (circle), answers the designer's question (`mSetupYesNoWin`), then the order is carried out: `mSetCloth` stores the dress as the worn one
//! and as *used* (`BTL +0xda8` bit set, `BTL +0xdaa` = worn dress, `MENU +0x2fc` bit `id - 1`), the stage cut scene plays (stars, name roll
//! `dRoll`, the dress presentation text, the fitting-room magic) and the designer comments.  A dress already used cannot be ordered again
//! (buzzer).
//!
//! # What is real
//! the list rule, the state machine (JP `mTailorPolling` states 0..0x1a), the save flag changes, the texts (overlay tables `tailorMess_*_J` /
//! the `msg` entries of the US `TAILOR.DAT`), dress names (`CLOT` -> `SSHMES` table 14), the stage art, designer portrait, stars (`mMoveStars`
//! with the `mStarPos` table) and the blink sheet of `TAILOR.DAT`.
//!
//! # Not ported
//! the 3D sketch-book models (`primModel` pages, entries 14..25 of the bundle) and their page-turn motions: the page shows the stage with the
//! dress name and description instead; the fitting-room `.SSE` jingles.  The retail "Original Class changes" notes are shown, the class
//! change itself is not applied to the party (the demo has none).

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_gfx::texture::decode_menu_texture;
use sh2_menu::disc::FileSource;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};

use crate::cmd_page::{CmdScenes, Env};
use crate::cmd_ui::{blit, text_run};
use crate::fscreen::{coded_text, window, wrap_text, FieldScreen, ScreenFlow, ScreenIo, DT_MS};
use crate::overlay_data::OverlayImage;

/// Dress ids offered by default (`mMakeSketchBook`: `GetTailorFlagAddr() == 0` -> `0x3fe` = ids 1..=9).
pub const DEFAULT_MASK: u32 = 0x3fe;
pub const CLOTH_COUNT: usize = 11;
/// `BTL` offsets: used-dress bits (u16) and the worn dress (u8).
pub const OFF_USED: usize = 0xda8;
pub const OFF_WORN: usize = 0xdaa;
/// `MENU` offset of the dress collection bits (`0x1ff` mask).
pub const OFF_MENU_CLOTH: usize = 0x2fc;
/// `mStarPos` (JP FIELD.BIN 0x005542e0): the five star offsets.
pub const STAR_POS: u32 = 0x0055_42e0;

#[derive(Clone, Debug, Default)]
pub struct TailorText {
    pub select: String,
    pub select_cancel: String,
    pub cancel_q: String,
    pub confirm: String,
    pub working: String,
    pub presenting: String,
    pub titled: String,
    pub satisfied: String,
    pub menu_select: String,
    pub waiting: String,
    pub describe: String,
    pub reactions: Vec<String>,
    pub yes: String,
    pub no: String,
    /// per dress: `(class change note, reading, description)`
    pub cloth: Vec<(String, String, String)>,
    pub star_pos: [(u8, u8); 5],
}

fn fix(s: &str) -> String {
    s.replace('\\', "").replace('\u{ff8d}', "")
}

impl TailorText {
    pub fn load(env: &Env) -> Option<Self> {
        let disc = env.assets.disc.as_ref()?;
        let retail = sh2_core::boot::is_retail();
        let root = std::env::var_os("SH2_DISC_DIR").map(std::path::PathBuf::from)?;
        if retail {
            let b = disc.read("SHOP/TAILOR.DAT")?;
            let n = u32::from_le_bytes(b.get(0..4)?.try_into().ok()?) as usize;
            let mut tabs = Vec::new();
            for k in 0..n {
                if b.get(8 + k * 8..11 + k * 8)? == b"msg" {
                    tabs.push(crate::worldmap::parse_msg_table(crate::worldmap::bundle_entry(&b, k)?));
                }
            }
            let (m, c) = (tabs.first()?, tabs.get(1)?);
            let s = |i: usize| fix(&sh2_menu::sjis::decode(m.get(i).map(|v| v.as_slice()).unwrap_or(&[])));
            let cl = |i: usize| fix(&sh2_menu::sjis::decode(c.get(i).map(|v| v.as_slice()).unwrap_or(&[])));
            let cloth = (0..CLOTH_COUNT).map(|i| (s(13 + i), cl(i * 2), cl(i * 2 + 1))).collect();
            Some(TailorText {
                select: s(0),
                select_cancel: s(1),
                cancel_q: s(2),
                yes: s(3),
                no: s(4),
                confirm: s(5),
                working: s(8),
                presenting: s(9),
                titled: s(10),
                satisfied: s(11),
                menu_select: s(24),
                waiting: s(25),
                describe: s(32),
                reactions: (26..32).map(s).collect(),
                cloth,
                star_pos: [(0, 0); 5],
            })
        } else {
            let img = OverlayImage::new(sh2_core::fileio::read_disc_file(&root, "FIELD.BIN").ok()?).ok()?;
            let dec = |b: &[u8]| sh2_menu::sjis::decode(b);
            let tbl = |n: &str| -> Option<Vec<String>> { Some(img.strings(n)?.iter().map(|b| dec(b)).collect()) };
            let mess = tbl("tailorMess_mess_J")?;
            let (note, ruby, desc) = (tbl("tailorMess_clothNote_J")?, tbl("tailorMess_clothRuby_J")?, tbl("tailorMess_clothMess_J")?);
            let g = |i: usize| mess.get(i).cloned().unwrap_or_default();
            let cloth = (0..CLOTH_COUNT).map(|i| (note.get(i).cloned().unwrap_or_default(), ruby.get(i).cloned().unwrap_or_default(), desc.get(i).cloned().unwrap_or_default())).collect();
            let mut star_pos = [(0u8, 0u8); 5];
            if let Some(b) = img.bytes_at(STAR_POS, 10) {
                for (i, p) in star_pos.iter_mut().enumerate() {
                    *p = (b[i * 2], b[i * 2 + 1]);
                }
            }
            Some(TailorText {
                select: g(0),
                select_cancel: g(0),
                cancel_q: g(1),
                confirm: g(2),
                working: g(3),
                presenting: g(4),
                titled: g(5),
                satisfied: g(6),
                menu_select: g(7),
                waiting: g(8),
                describe: g(9),
                reactions: (10..16).map(g).collect(),
                yes: "はい".to_string(),
                no: "いいえ".to_string(),
                cloth,
                star_pos,
            })
        }
    }
}

/// Dress ids offered by a flag word (`mMakeSketchBook`, shop mode).
pub fn sketch_book(mask: u32) -> Vec<usize> {
    let m = if mask == 0 { DEFAULT_MASK } else { mask };
    (0..CLOTH_COUNT).filter(|i| m & (1 << i) != 0).collect()
}

pub fn used_flags(env: &Env) -> u16 {
    let d = &env.session.save.btl.data;
    u16::from_le_bytes([d[OFF_USED], d[OFF_USED + 1]])
}

pub fn is_used(env: &Env, id: usize) -> bool {
    used_flags(env) & (1 << id) != 0
}

/// `mSetCloth` (shop mode): the dress becomes the worn one and is marked used.
pub fn set_cloth(env: &mut Env, id: usize) {
    let btl = &mut env.session.save.btl.data;
    btl[OFF_WORN] = id as u8;
    let used = u16::from_le_bytes([btl[OFF_USED], btl[OFF_USED + 1]]) | (1u16 << id) | 1;
    btl[OFF_USED..OFF_USED + 2].copy_from_slice(&used.to_le_bytes());
    // the collection bits of the Clothes menu: `(old | 1 << (id - 1)) & 0x1ff`
    let m = &mut env.session.save.menu.data;
    let cur = u32::from_le_bytes(m[OFF_MENU_CLOTH..OFF_MENU_CLOTH + 4].try_into().unwrap());
    let sh = (id as i32 - 1) & 0x1f;
    let new = (cur | (1u32 << sh)) & 0x1ff;
    m[OFF_MENU_CLOTH..OFF_MENU_CLOTH + 4].copy_from_slice(&new.to_le_bytes());
}

/// Name of dress `id` (`GetRegDat(0xb, id)`: `CLOT` record u16 +2 -> `SSHMES` table 14).
pub fn cloth_name(env: &Env, id: usize) -> String {
    let via = env.db.and_then(|d| d.dat.record(sh2_battle::data::SEC_CLOTH, id, 0xc)).and_then(|r| r.get(2..4)).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).unwrap_or(id);
    let n = env.name(14, via);
    if n.is_empty() {
        env.db.map(|d| d.name(14, via)).unwrap_or_default()
    } else {
        n
    }
}

#[derive(Clone, Debug, PartialEq)]
enum Phase {
    /// states 2..3: the selection message types out
    Intro,
    /// state 4: paging through the book
    Select,
    /// states 8..9: "can't order again" / the confirm question
    Ask,
    /// 0xb: yes / no
    YesNo,
    /// 0xc..0x11: the order is made, the name roll and the presentation
    Work,
    /// 0x12..0x15: the fitting-room magic and the designer's comment
    Magic,
    Comment,
    /// 0x18..0x1a: leave
    Leave,
}

/// A typed-out message (`MenuMessage`): the characters appear one by one, circle finishes it.
#[derive(Clone, Debug, Default)]
struct Msg {
    text: String,
    shown: f32,
}

impl Msg {
    fn set(&mut self, t: &str) {
        self.text = t.to_string();
        self.shown = 0.0;
    }
    fn len(&self) -> usize {
        self.text.chars().count()
    }
    fn done(&self) -> bool {
        self.shown as usize >= self.len()
    }
    fn tick(&mut self) {
        self.shown += DT_MS / 33.0;
    }
    fn finish(&mut self) {
        self.shown = self.len() as f32;
    }
    fn visible(&self) -> String {
        // codes (`%p7`, `$`) count as one step each in the typing but are never cut in half
        let mut out = String::new();
        let mut n = 0usize;
        let cs: Vec<char> = self.text.chars().collect();
        let mut i = 0;
        while i < cs.len() && (n as f32) < self.shown {
            if cs[i] == '%' && i + 2 < cs.len() && cs[i + 1] == 'p' {
                out.extend(&cs[i..i + 3]);
                i += 3;
                continue;
            }
            out.push(cs[i]);
            n += 1;
            i += 1;
        }
        out
    }
}

pub struct TailorScreen {
    t: TailorText,
    sc: Arc<CmdScenes>,
    tex: TailorTex,
    list: Vec<usize>,
    names: Vec<String>,
    used: Vec<bool>,
    page: usize,
    phase: Phase,
    timer: f32,
    msg: Msg,
    /// yes (0) / no (1)
    yn: usize,
    yn_cancel: bool,
    fade: f32,
    stars: [f32; 5],
    anim: f32,
    chosen: Option<usize>,
    /// first message shown (`SpecialMenu` always starts with the plain question)
    can_cancel: bool,
    reaction: usize,
    wait_ok: bool,
}

#[derive(Default, Clone)]
struct TailorTex {
    /// 1: the designer, 2: the old man (menu mode), 3: the stage frame, 4 / 5: lit / dark stage, 6: glow, 7: ring, 8: stamp, 9: stars sheet
    designer: Option<(TextureId, (u32, u32))>,
    frame: Option<(TextureId, (u32, u32))>,
    stage: Option<(TextureId, (u32, u32))>,
    stage_dark: Option<(TextureId, (u32, u32))>,
    glow: Option<(TextureId, (u32, u32))>,
    ring: Option<(TextureId, (u32, u32))>,
    stamp: Option<(TextureId, (u32, u32))>,
    stars: Option<(TextureId, (u32, u32))>,
}

fn load_tex(env: &mut Env) -> TailorTex {
    let mut t = TailorTex::default();
    let Some(b) = env.assets.disc.as_ref().and_then(|d| d.read("SHOP/TAILOR.DAT")) else { return t };
    let load = |env: &mut Env, k: usize| -> Option<(TextureId, (u32, u32))> {
        let off = u32::from_le_bytes(b.get(12 + k * 8..16 + k * 8)?.try_into().ok()?) as usize;
        let img = decode_menu_texture(&b, off).ok()?;
        let sz = (img.width, img.height);
        env.reg.add(&img).map(|id| (id, sz))
    };
    t.designer = load(env, 1);
    t.frame = load(env, 3);
    t.stage = load(env, 4);
    t.stage_dark = load(env, 5);
    t.glow = load(env, 6);
    t.ring = load(env, 7);
    t.stamp = load(env, 8);
    t.stars = load(env, 9);
    t
}

impl TailorScreen {
    pub fn new(env: &mut Env) -> Option<Self> {
        let t = TailorText::load(env)?;
        let sc = env.scenes()?;
        let tex = load_tex(env);
        let list = sketch_book(0);
        let names = list.iter().map(|&i| cloth_name(env, i)).collect();
        let used = list.iter().map(|&i| is_used(env, i)).collect();
        let mut s = TailorScreen {
            t,
            sc,
            tex,
            list,
            names,
            used,
            page: 0,
            phase: Phase::Intro,
            timer: 0.0,
            msg: Msg::default(),
            yn: 0,
            yn_cancel: false,
            fade: 0.0,
            stars: [0.0; 5],
            anim: 0.0,
            chosen: None,
            can_cancel: true,
            reaction: 0,
            wait_ok: false,
        };
        let first = s.t.select.clone();
        s.msg.set(&first);
        for (i, st) in s.stars.iter_mut().enumerate() {
            *st = (i as f32 * 53.0) % 255.0;
        }
        Some(s)
    }

    fn cur_id(&self) -> usize {
        self.list.get(self.page).copied().unwrap_or(0)
    }

    /// `mMoveStars`: five stars that cycle through their animation frames (the counter table of the original).
    fn move_stars(&mut self) {
        for st in self.stars.iter_mut() {
            *st += 1.0;
            if *st >= 255.0 {
                *st = 0.0;
            }
        }
    }
}

impl FieldScreen for TailorScreen {
    fn name(&self) -> &'static str {
        "tailor"
    }

    fn state(&self) -> String {
        format!("{:?}", self.phase).to_lowercase()
    }

    fn tick(&mut self, env: &mut Env, keys: u16, press: u16, _io: &mut ScreenIo) -> ScreenFlow {
        self.anim += DT_MS;
        self.timer += DT_MS;
        self.msg.tick();
        self.move_stars();
        self.fade = if self.phase == Phase::Leave { (self.fade - DT_MS / 400.0).max(0.0) } else { (self.fade + DT_MS / 400.0).min(1.0) };
        if press & padbit::CIRCLE != 0 && !self.msg.done() {
            self.msg.finish();
        }
        let ok = press & padbit::CIRCLE != 0;
        match self.phase.clone() {
            Phase::Intro => {
                if self.msg.done() && self.timer > 1000.0 {
                    self.phase = Phase::Select;
                    self.timer = 0.0;
                }
            }
            Phase::Select => {
                if keys & padbit::RIGHT != 0 && self.page + 1 < self.list.len() {
                    self.page += 1;
                    env.sound(MenuSe::Other(0x300_0004));
                } else if keys & padbit::LEFT != 0 && self.page > 0 {
                    self.page -= 1;
                    env.sound(MenuSe::Other(0x300_0004));
                } else if ok {
                    if self.used[self.page] {
                        // already ordered once: buzzer (`play(4)`)
                        env.sound(MenuSe::Buzzer);
                    } else {
                        env.sound(MenuSe::Decide);
                        let c = self.t.confirm.clone();
                        self.msg.set(&c);
                        self.phase = Phase::Ask;
                        self.timer = 0.0;
                    }
                } else if press & padbit::CROSS != 0 && self.can_cancel {
                    env.sound(MenuSe::Decide);
                    let c = self.t.cancel_q.clone();
                    self.msg.set(&c);
                    self.yn_cancel = true;
                    self.phase = Phase::Ask;
                    self.timer = 0.0;
                }
            }
            Phase::Ask => {
                if self.msg.done() && ok && self.timer > 200.0 {
                    self.yn = 0;
                    self.phase = Phase::YesNo;
                }
            }
            Phase::YesNo => {
                if keys & (padbit::UP | padbit::DOWN) != 0 {
                    self.yn = 1 - self.yn;
                    env.sound(MenuSe::CursorMove);
                } else if press & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.back_to_select();
                } else if ok {
                    env.sound(MenuSe::Decide);
                    if self.yn == 0 {
                        if self.yn_cancel {
                            self.phase = Phase::Leave;
                            self.timer = 0.0;
                        } else {
                            let id = self.cur_id();
                            set_cloth(env, id);
                            self.chosen = Some(id);
                            self.used[self.page] = true;
                            let w = self.t.working.clone();
                            self.msg.set(&w);
                            self.phase = Phase::Work;
                            self.timer = 0.0;
                        }
                    } else {
                        self.back_to_select();
                    }
                }
            }
            Phase::Work => {
                // presentation: the working line, then the title of the dress (`mSetupMess(4)`, `(5)` with `%s`)
                if self.timer > 2500.0 && self.msg.done() && !self.wait_ok {
                    let id = self.chosen.unwrap_or(0);
                    let name = self.names.get(self.page).cloned().unwrap_or_default();
                    let _ = id;
                    let m = format!("{}$$ {}", self.t.presenting, self.t.titled.replace("%s", &name));
                    self.msg.set(&m);
                    self.wait_ok = true;
                }
                if self.wait_ok && self.msg.done() && self.timer > 6000.0 && ok {
                    self.wait_ok = false;
                    // the class change note of the dress (retail) / the fitting magic line
                    let n = self.t.cloth.get(self.chosen.unwrap_or(0)).map(|c| c.0.clone()).unwrap_or_default();
                    self.msg.set(&n);
                    self.phase = Phase::Magic;
                    self.timer = 0.0;
                }
            }
            Phase::Magic => {
                if self.msg.done() && ok && self.timer > 600.0 {
                    let s = self.t.satisfied.clone();
                    self.msg.set(&s);
                    self.phase = Phase::Comment;
                    self.timer = 0.0;
                }
            }
            Phase::Comment => {
                if self.msg.done() && ok && self.timer > 600.0 {
                    env.sound(MenuSe::Decide);
                    self.phase = Phase::Leave;
                    self.timer = 0.0;
                }
            }
            Phase::Leave => {
                if self.fade <= 0.0 {
                    let _ = self.reaction;
                    return ScreenFlow::Done;
                }
            }
        }
        ScreenFlow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = self.fade;
        let white = Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8);
        // stage backdrop
        crate::cmd_ui::fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0x08, 0x08, 0x10, (0x80 as f32 * a) as u8));
        if let Some((t, (w, h))) = self.tex.frame {
            blit(g, Some(t), 0.0, 0.0, 512.0, 448.0, (0.0, 0.0, w as f32, h as f32), white);
        }
        let lit = matches!(self.phase, Phase::Work | Phase::Magic | Phase::Comment);
        let stage = if lit || self.phase == Phase::Select { self.tex.stage } else { self.tex.stage_dark };
        if let Some((t, (w, h))) = stage {
            blit(g, Some(t), 108.0, 66.0, 218.0, 206.0, (0.0, 0.0, w as f32, h as f32), white);
        }
        // the dress on the stage: its name large, the used stamp
        let id = self.cur_id();
        let name = self.names.get(self.page).cloned().unwrap_or_default();
        coded_text(g, 124.0, 150.0, &name, 0, white, 18.0, true);
        if self.used.get(self.page).copied().unwrap_or(false) {
            if let Some((t, (w, h))) = self.tex.stamp {
                blit(g, Some(t), 140.0, 190.0, w as f32 * 0.9, h as f32 * 0.9, (0.0, 0.0, w as f32, h as f32), white);
            }
        }
        // page turn arrows and counter
        if self.phase == Phase::Select {
            let c = Rgba::new(0xff, 0xe0, 0x60, (128.0 * a) as u8);
            if self.page > 0 {
                text_run(g, 90.0, 160.0, "<", 0, c, Some((1, 1)));
            }
            if self.page + 1 < self.list.len() {
                text_run(g, 330.0, 160.0, ">", 0, c, Some((1, 1)));
            }
            text_run(g, 190.0, 276.0, &format!("{} / {}", self.page + 1, self.list.len()), 14, white, Some((1, 1)));
        }
        // description note window (right)
        window(g, 276.0, 32.0, 220.0, 224.0, a);
        let (note, ruby, desc) = self.t.cloth.get(id).cloned().unwrap_or_default();
        text_run(g, 284.0, 38.0, &name, 14, white, Some((1, 1)));
        text_run(g, 284.0, 56.0, &sh2_menu::sjis::strip_codes(&ruby), 14, Rgba::new(0x70, 0xc0, 0xff, (128.0 * a) as u8), Some((1, 1)));
        coded_text(g, 284.0, 82.0, &wrap_text(&desc, 26), 14, white, 16.0, true);
        if !note.trim().is_empty() {
            coded_text(g, 284.0, 196.0, &wrap_text(&note, 26), 14, Rgba::new(0xff, 0xe0, 0x60, (128.0 * a) as u8), 15.0, true);
        }
        // the designer and the message window
        if let Some((t, (w, h))) = self.tex.designer {
            blit(g, Some(t), 16.0, 292.0, w as f32 * 0.9, h as f32 * 0.9, (0.0, 0.0, w as f32, h as f32), white);
        }
        window(g, 120.0, 340.0, 376.0, 92.0, a);
        coded_text(g, 132.0, 346.0, &wrap_text(&self.msg.visible(), 44), 14, white, 20.0, true);
        if self.msg.done() && matches!(self.phase, Phase::Ask | Phase::Work | Phase::Magic | Phase::Comment) {
            let blink = ((self.anim / 300.0) as i32) % 2 == 0;
            if blink {
                text_run(g, 472.0, 410.0, "v", 14, Rgba::new(0xff, 0xe0, 0x60, 0x80), Some((1, 1)));
            }
        }
        // yes / no
        if self.phase == Phase::YesNo {
            window(g, 380.0, 250.0, 100.0, 66.0, 1.0);
            for (i, s) in [&self.t.yes, &self.t.no].iter().enumerate() {
                let y = 258.0 + 26.0 * i as f32;
                if i == self.yn {
                    crate::cmd_ui::fill(g, 384.0, y - 2.0, 92.0, 24.0, Rgba::new(0x50, 0x70, 0xc0, 0x50));
                }
                text_run(g, 396.0, y, s, 0, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
            }
        }
        // the stars (`mMoveStars`: five sprites of the star sheet, frame by counter)
        if matches!(self.phase, Phase::Work | Phase::Magic) {
            if let Some((t, (w, h))) = self.tex.stars {
                for (i, c) in self.stars.iter().enumerate() {
                    let fr = if *c < 23.0 { 0 } else if *c < 46.0 { 1 } else if *c < 69.0 { 2 } else { 0 };
                    let (px, py) = (self.t.star_pos[i].0 as f32, self.t.star_pos[i].1 as f32);
                    blit(g, Some(t), 130.0 + px, 80.0 + py, 32.0, 40.0, ((fr * 32 + 1) as f32, (i * 40 + 1) as f32, (fr * 32 + 33) as f32, (i * 40 + 41) as f32), white);
                    let _ = (w, h);
                }
            }
        }
        let _ = &self.sc;
    }
}

impl TailorScreen {
    fn back_to_select(&mut self) {
        let m = if self.can_cancel { self.t.select_cancel.clone() } else { self.t.select.clone() };
        self.msg.set(&m);
        self.yn_cancel = false;
        self.phase = Phase::Select;
        self.timer = 0.0;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn default_book_offers_dresses_one_to_nine() {
        // `0x3fe`: dress 0 (the rags she starts in) and dress 10 are not for order
        assert_eq!(sketch_book(0), (1..=9).collect::<Vec<_>>());
        assert_eq!(sketch_book(0b101), vec![0, 2]);
    }

    #[test]
    fn typed_message_never_cuts_a_colour_code() {
        let mut m = Msg::default();
        m.set("%p7ab%p0cd");
        m.shown = 1.0;
        assert_eq!(m.visible(), "%p7a");
        m.finish();
        assert!(m.done());
    }
}
