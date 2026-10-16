//! Widgets the retail (`--us`) command-menu pages share (round 5): the member card of the page scenes (`*.MSD` attach "card":
//! portrait medallion, `< Name >`, `LEVEL.`, coloured `HP. / MP. / SP.`), the page's own command column at (380, 25) (Equip Crests /
//! Recommended / ...), untextured GS polygons and the retail Yes / No query (`CMDMENU.MSD` attach 12).

use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextRun, TextureId};
use sh2_menu::msd::{PolygonRec, TextCommon};

use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

/// Lavender of the `LEVEL.` / banner labels (font 2, CLUT set 3; measured live) and the coloured `HP. / MP. / SP.` labels (sets 4 / 5 / 6).
pub const LAVENDER: (u8, u8, u8) = (0x49, 0x42, 0x5b);
pub const CARD_LABEL: [(u8, u8, u8); 3] = [(0x42, 0x4d, 0x6d), (0x4b, 0x23, 0x49), (0x4d, 0x1f, 0x22)];
/// Selected row text (white glyph x (0, 0x80, 0x80)).
pub const CYAN: (u8, u8, u8) = (0x00, 0x80, 0x80);
/// Red row text (a crest above the free DCP; live: (226, 30, 50) on the 8-bit frame).
pub const RED: (u8, u8, u8) = (0x76, 0x0f, 0x1a);

pub fn rgb(c: (u8, u8, u8), a: u8) -> Rgba {
    Rgba::new(c.0, c.1, c.2, a)
}

/// An untextured scene polygon: retail flat colours are GS values, halved for the canvas.
pub fn gs_poly(g: &mut dyn MenuGfx, p: &PolygonRec, ox: f32, oy: f32, a: u8) {
    let col = |k: usize| Rgba::new(p.rgba[k][0] / 2, p.rgba[k][1] / 2, p.rgba[k][2] / 2, ((p.rgba[k][3] as u32 * a as u32) / 0x80) as u8);
    g.draw(DrawCmd::Quad {
        tex: None,
        v: [vtx(ox + p.x[0], oy + p.y[0], 0.0, 0.0, col(0)), vtx(ox + p.x[1], oy + p.y[1], 0.0, 0.0, col(1)), vtx(ox + p.x[2], oy + p.y[2], 0.0, 0.0, col(2)), vtx(ox + p.x[3], oy + p.y[3], 0.0, 0.0, col(3))],
        blend: Blend::Alpha,
    });
}

/// An untextured scene sprite (flat GS colour, halved).
pub fn gs_rect(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, c: [u8; 4], a: u8) {
    fill(g, x, y, w, h, Rgba::new(c[0] / 2, c[1] / 2, c[2] / 2, ((c[3] as u32 * a as u32) / 0x80) as u8));
}

pub fn rec_at(t: &Option<TextCommon>, dx: f32, dy: f32) -> (f32, f32, f32) {
    t.as_ref().map(|t| (t.x, t.y, TextRun::hscale_of(t.flags))).unwrap_or((dx, dy, 0.8))
}

/// What the member card shows.
#[derive(Clone, Debug, Default)]
pub struct CardView {
    pub name: String,
    pub level: u8,
    pub hp: (u16, u16),
    pub mp: (u16, u16),
    pub sp: (u16, u16),
}

impl CardView {
    pub fn of(p: &PcView) -> Self {
        CardView { name: p.name.clone(), level: p.level, hp: (p.hp, p.hp_max), mp: (p.mp, p.mp_max), sp: (p.sp as u16, p.sp_max as u16) }
    }
}

/// The retail member card (`CREST.MSD` attach 2, `EQUIP.MSD` attach 1, `SKILL.MSD` / `MAGIC.MSD` attach 1: window (10, 52)): the medallion
/// with the portrait (sprite 0), the name (record 4) with the lavender `<` `>` arrows while `arrows`, `LEVEL.` + value over the lavender rule
/// (polygons), `HP. / MP. / SP.` rows (records 1..3 labels, 6 values, 7 the slash column).
pub fn draw_pc_card(g: &mut dyn MenuGfx, sc: &CmdScenes, card: &SceneTex, face: Option<TextureId>, v: &CardView, arrows: bool, a: u8) {
    const SLASH_GAP: f32 = 8.0;
    let m = &card.msd;
    let (x, y) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((10.0, 52.0));
    face_frame(g, &sc.cmn, x, y, a);
    if let Some(s) = m.sprite(0) {
        blit(g, face, x + s.x, y + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(a));
    }
    for i in 0..m.count(sh2_menu::msd::ChunkType::Polygon) {
        if let Some(p) = m.polygon(i) {
            gs_poly(g, &p, x, y, a);
        }
    }
    let res = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
    let at = |k: usize| rec_at(&m.menu_text(k), 0.0, 0.0);
    let (nx, ny, nhs) = at(4);
    text_run_h(g, x + nx, y + ny, &v.name, 0, white(a), Some((1, 0)), nhs);
    if arrows {
        let tw = run_width(g, 0, &v.name, nhs, Some((1, 0))) / nhs.max(0.01);
        if let Some(t) = sc.cmn.s.t(4) {
            blit(g, Some(t), x + nx - 26.0, y + ny, 24.0, 22.0, (0.0, 2.0 * 22.0, 24.0, 3.0 * 22.0), white(a));
            blit(g, Some(t), x + nx + tw * nhs + 2.0, y + ny, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), white(a));
        }
    }
    let (lx, ly, lhs) = at(0);
    text_run_h(g, x + lx, y + ly, &res(0, "LEVEL."), 2, rgb(LAVENDER, a), None, lhs);
    let (vx, vy, vhs) = at(5);
    text_run_h(g, x + vx, y + vy, &cfmt(&res(4, "%2d"), &[(v.level as i32).into()]), 2, white(a), None, vhs);
    let rows = [v.hp, v.mp, v.sp];
    let (cx0, _, chs) = at(6);
    let (sx0, _, _) = at(7);
    for (k, (cur, max)) in rows.iter().enumerate() {
        let (hx, hy, hhs) = at(1 + k);
        text_run_h(g, x + hx, y + hy, &res(1 + k, ["HP.", "MP.", "SP."][k]), 2, rgb(CARD_LABEL[k], a), None, hhs);
        text_run_h(g, x + cx0, y + hy, &cfmt(&res(5, "%3d"), &[(*cur as i32).into()]), 0, white(a), None, chs);
        text_run_h(g, x + sx0, y + hy, &res(6, "/"), 0, white(a), None, chs);
        text_run_h(g, x + sx0 + SLASH_GAP, y + hy, &cfmt(&res(5, "%3d"), &[(*max as i32).into()]), 0, white(a), None, chs);
    }
}

/// A page's own command column (the scene's window at (380, 25), 20 px rows, record 0 for the font flags): `sel` cyan, `grey` rows at half alpha.
pub fn draw_menu_column(g: &mut dyn MenuGfx, origin: (f32, f32), rec: &Option<TextCommon>, labels: &[String], sel: Option<usize>, grey: &[usize], a: u8) {
    let (tx, ty, hs) = rec_at(rec, 0.0, 0.0);
    for (i, s) in labels.iter().enumerate() {
        let ra = if grey.contains(&i) { a / 2 } else { a };
        let c = if Some(i) == sel { rgb(CYAN, ra) } else { white(ra) };
        text_run_h(g, origin.0 + tx, origin.1 + ty + i as f32 * 20.0, s, 0, c, None, hs);
    }
}

/// Cursor tip for row `i` of a [`draw_menu_column`].
pub fn menu_column_tip(origin: (f32, f32), i: usize) -> (f32, f32) {
    (origin.0 - 5.0, origin.1 + i as f32 * 20.0 + 10.0)
}

/// The retail Yes / No query (`CMDMENU.MSD` attach 12: a 384 x 110 message window centred on (256, 128), the screen dimmed by a black
/// sprite of alpha 104, `Yes` / `No` at (175, 4) / (175, 25) under the message; the cursor starts on **No**).
pub struct RetailQuery {
    pub text: String,
    /// 0 = Yes, 1 = No
    pub sel: usize,
    pub t: f32,
}

impl RetailQuery {
    pub fn new(text: String) -> Self {
        RetailQuery { text, sel: 1, t: 0.0 }
    }
    /// `Some(true)` yes, `Some(false)` no / cancel.
    pub fn tick(&mut self, env: &mut Env, keys: u16) -> Option<bool> {
        use sh2_core::game::padbit;
        self.t += 1000.0 / 60.0;
        if keys & (padbit::UP | padbit::DOWN) != 0 {
            self.sel ^= 1;
            env.sound(sh2_menu::gfx::MenuSe::CursorMove);
        } else if keys & padbit::CIRCLE != 0 {
            env.sound(if self.sel == 0 { sh2_menu::gfx::MenuSe::Decide } else { sh2_menu::gfx::MenuSe::Cancel });
            return Some(self.sel == 0);
        } else if keys & padbit::CROSS != 0 {
            env.sound(sh2_menu::gfx::MenuSe::Cancel);
            return Some(false);
        }
        None
    }
    fn layout(&self) -> (f32, f32, f32, f32) {
        let (w, h) = (384.0, 110.0);
        (256.0 - w * 0.5, 128.0 - h * 0.5 + 40.0, w, h)
    }
    pub fn cursor_tip(&self) -> (f32, f32) {
        let (x, y, _, h) = self.layout();
        (x + 175.0 - 5.0, y + h - 52.0 + self.sel as f32 * 21.0 + 10.0)
    }
    pub fn draw(&self, g: &mut dyn MenuGfx, sc: &CmdScenes, a: u8) {
        fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, ((104u32 * a as u32) / 0x80) as u8));
        let (x, y, w, h) = self.layout();
        general_frame(g, &sc.cmn, x, y, w, h, a);
        for (i, l) in self.text.split(['$', '\n']).enumerate() {
            text_run_h(g, x + 24.0, y + 12.0 + i as f32 * 20.0, l, 0, white(a), None, 0.8);
        }
        let yes = ["Yes", "No"];
        for (i, s) in yes.iter().enumerate() {
            let c = if i == self.sel { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, x + 175.0, y + h - 52.0 + i as f32 * 21.0, s, 0, c, None, 0.8);
        }
    }
}

/// The DCP / crest-level gauge fill (live captures `cc_rec2`: purple -> orange -> pale yellow across the 156 px fill, flat for the last
/// fifth; colours corrected for the capture's 0.925 brightness): no texture of the scene holds it, so it is generated once.
pub fn dcp_gradient(env: &mut Env) -> Option<TextureId> {
    const KEY: &str = "retail:dcp_gradient";
    if let Some(t) = env.cache.images.get(KEY) {
        return *t;
    }
    const STOPS: [(f32, [f32; 3]); 7] = [
        (0.0, [100.0, 25.0, 235.0]),
        (0.12, [95.0, 33.0, 195.0]),
        (0.3, [150.0, 76.0, 148.0]),
        (0.47, [207.0, 124.0, 90.0]),
        (0.6, [248.0, 171.0, 76.0]),
        (0.8, [248.0, 240.0, 170.0]),
        (1.0, [248.0, 245.0, 178.0]),
    ];
    let (w, h) = (156u32, 4u32);
    let mut px = Vec::with_capacity((w * h * 4) as usize);
    for _ in 0..h {
        for x in 0..w {
            let t = x as f32 / (w - 1) as f32;
            let k = STOPS.windows(2).position(|s| t <= s[1].0).unwrap_or(STOPS.len() - 2);
            let (a, b) = (STOPS[k], STOPS[k + 1]);
            let f = ((t - a.0) / (b.0 - a.0)).clamp(0.0, 1.0);
            for c in 0..3 {
                px.push((a.1[c] + (b.1[c] - a.1[c]) * f).round().clamp(0.0, 255.0) as u8);
            }
            px.push(255);
        }
    }
    let t = env.reg.add(&sh2_gfx::texture::Rgba8Image { width: w, height: h, pixels: px });
    env.cache.images.insert(KEY.to_string(), t);
    t
}
