//! Retail `CmdMenu` page 19 = `CmdRetailPage06` (`MENU/MSD/SECHAR.MSD`, "Equip Weapons, Armor and Accessories."): the member pick of the
//! shop's Equip.  The members as the root page / Party Members show them (window (134, 45), 44 px rows: stepped plate, face strip, `LEVEL`
//! + level, name, HP / MP with gauges; the picked row glows cyan); confirm opens the Equipment page for that member, cancel leaves.
//!
//! The scene's records are those of the Party Members rows (`FORM.MSD` group 0): polygons 0..3 the plate, 4..7 the glow, 8 the dark panel,
//! sprite 0 the strip, 2 / 3 the gauge backs and 4 / 5 their fills, font records 0 `LEVEL`, 1 / 2 `HP` / `MP`, 3 the level, 4 / 5 the values.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextRun, TextureId};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_retail::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 44.0;
const VISIBLE: usize = 4;
const PATH: &str = "MENU/MSD/SECHAR.MSD";

struct Row {
    pc: PcView,
    strip: Option<TextureId>,
}

pub struct SelectCharPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    rows: Vec<Row>,
    list: ListState,
    cursor: CmdCursor,
    slide: Slide,
    note: String,
}

impl SelectCharPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let rows: Vec<Row> = party_view(env.session).into_iter().map(|pc| Row { strip: sc.top.t_by_id(pc.face as i16), pc }).collect();
        if rows.is_empty() {
            return None;
        }
        let note = scene.msd.resource_bytes(6).map(sj).unwrap_or_default();
        let w = scene.msd.window(0);
        let mut p = SelectCharPage {
            sc,
            list: ListState::new(VISIBLE, rows.len()),
            rows,
            scene,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(300), (236.0, 180.0)),
            note,
        };
        p.place_cursor();
        p.cursor.snap();
        Some(p)
    }

    fn origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((134.0, 45.0))
    }

    fn place_cursor(&mut self) {
        let (x, y) = self.origin();
        self.cursor.set_target(x - 12.0, y + self.list.slot() as f32 * ROW_H + 18.0);
    }

    #[allow(clippy::too_many_arguments)]
    fn draw_row(&self, g: &mut dyn MenuGfx, row: &Row, ox: f32, oy: f32, selected: bool, a: u8) {
        let m = &self.scene.msd;
        let sc = &*self.sc;
        let range = if selected { 4..8 } else { 0..4 };
        for i in range {
            if let Some(p) = m.polygon(i) {
                gs_poly(g, &p, ox, oy, a);
            }
        }
        if let Some(r) = m.sprite(0) {
            blit(g, row.strip, ox + r.x, oy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), white(a));
        }
        let name_c = if selected { rgb(CYAN, a) } else { white(a) };
        if let Some(t) = m.menu_text(0) {
            text_run_h(g, ox + t.x, oy + t.y - 2.0, &row.pc.name, 0, name_c, Some((1, 1)), TextRun::hscale_of(t.flags));
        }
        let fp = |i: usize| m.font_pos(i).unwrap_or((0.0, 0.0));
        let (x, y) = fp(0);
        sc.font_small.draw(g, ox + x, oy + y, "LEVEL", Rgba::new(0x46, 0x3e, 0x4e, a));
        let (x, y) = fp(3);
        sc.font_big.draw(g, ox + x, oy + y, &format!("{:>2}", row.pc.level), white(a));
        let vals = [(1usize, 4usize, "HP", row.pc.hp as i32, row.pc.hp_max as i32, 2usize), (2, 5, "MP", row.pc.mp as i32, row.pc.mp_max as i32, 3)];
        for (lab, val, label, cur, max, spr) in vals {
            let (x, y) = fp(lab);
            sc.font_small.draw(g, ox + x, oy + y, label, white(a));
            let frac = if max > 0 { cur as f32 / max as f32 } else { 0.0 };
            let (x, y) = fp(val);
            sc.font_small.draw(g, ox + x, oy + y, &cfmt("%3d/%3d", &[cur.into(), max.into()]), white(a));
            if let (Some(back), Some(fill_r)) = (m.sprite(spr), m.sprite(spr + 2)) {
                draw_sprite_rec(g, &back, sc.gauge, ox, oy, a);
                let wf = (fill_r.w * frac.clamp(0.0, 1.0)).round();
                if wf > 0.0 {
                    blit(g, sc.gauge, ox + fill_r.x, oy + fill_r.y, wf, fill_r.h, (fill_r.u0 as f32, fill_r.v0 as f32, fill_r.u0 as f32 + wf, fill_r.v1 as f32), white(a));
                }
            }
        }
    }
}

impl Page for SelectCharPage {
    fn backdrop(&self) -> Option<usize> {
        Some(1)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        Some(Vec::new())
    }
    fn page(&self) -> CmdPage {
        CmdPage::SelectChar
    }
    fn title(&self) -> usize {
        crate::cmd_pages::title_index(CmdPage::Equipment)
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.scene.t(0).map(|t| (t, self.scene.tex_size(0)))
    }
    fn note(&self) -> String {
        self.note.clone()
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        Vec::new()
    }
    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        if self.list.key(keys) {
            env.sound(MenuSe::CursorMove);
        } else if keys & padbit::CIRCLE != 0 {
            let pc = self.rows[self.list.sel].pc.id;
            match crate::cmd_pages::make_page(env, CmdPage::Equipment, Some(pc)) {
                Some(p) => {
                    env.sound(MenuSe::Decide);
                    return Flow::Open(p);
                }
                None => env.sound(MenuSe::Buzzer),
            }
        } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
            env.sound(MenuSe::Cancel);
            return Flow::Close;
        }
        self.place_cursor();
        Flow::Stay
    }
    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        let (ox, oy) = self.origin();
        if let Some(p) = self.scene.msd.polygon(8) {
            for k in 0..self.rows.len().min(VISIBLE) {
                gs_poly(g, &p, ox, oy + k as f32 * ROW_H, a);
            }
        }
        for (k, row) in self.rows.iter().enumerate().skip(self.list.top).take(VISIBLE) {
            self.draw_row(g, row, ox, oy + (k - self.list.top) as f32 * ROW_H, k == self.list.sel, a);
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}
