//! Retail `CmdFormation` (page 8 "Party Members", US 0x4b6c10.., `Retail_CmdFormation_*`, `CmdFormationTeam`), checked against live
//! PCSX2 captures (`notes/integration/r5_mn.md`): the top-lit backdrop (CMDMENUS attach 0 image 1), the root list on the right, the member
//! rows of `FORM.MSD` window 0 (134, 45) in the root page's panel style (face strip with the battle marker, `LEVEL`, name, HP / MP with
//! their gauges, 44 px apart), the team box of window 1 (0, 147): the team name (cyan) over the four battle slots (`battle_max` of the
//! party set), and the report `circle : Edit Team / cross : Quit / triangle : Reset`.
//!
//! Flow: Edit Team picks a battle slot (the slot frame glows), then a member: the slot's own member is removed ("Remove %s."), a member of
//! another slot changes places with it, a waiting member takes the slot.  Reset puts the team back as it was when the page opened.  The
//! party set is `MENU+0x84 + set * 0x20` (`name[15]`, count `+0xf`, battle max `+0x10`, battle count `+0x11`, members `+0x12..`).

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
/// x pitch of the four slanted battle slots in the team box (live `pm_a`)
const SLOT_PITCH: f32 = 28.0;
const PATH: &str = "MENU/MSD/FORM.MSD";

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Menu,
    Slot,
    Member,
}

struct Row {
    pc: PcView,
    strip: Option<TextureId>,
    portrait: Option<TextureId>,
}

pub struct RetailFormPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    cms: Option<Arc<SceneTex>>,
    set_index: usize,
    /// party set name, members (ids), battle max, battle count
    name: String,
    members: Vec<u8>,
    battle_max: usize,
    battle_count: usize,
    original: Option<sh2_menu::save::PartySet>,
    rows: Vec<Row>,
    mode: Mode,
    slot: usize,
    list: ListState,
    cursor: CmdCursor,
    slide: Slide,
    blink: f32,
    title_img: Option<(TextureId, (u32, u32))>,
    /// square: the team name entry (`CmdMenu` page 18, [`crate::name_entry`], mode 0)
    entry: Option<crate::name_entry::NameEntry>,
}

impl RetailFormPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let w = scene.msd.window(0);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let set_index = env.session.save.menu.current_set_index().min(sh2_menu::save::MenuSave::SET_COUNT - 1);
        let mut p = RetailFormPage {
            cms: env.file_scene("MENU/DAT/CMDMENUS.MSD"),
            sc,
            scene,
            set_index,
            name: String::new(),
            members: Vec::new(),
            battle_max: 4,
            battle_count: 0,
            original: env.session.save.menu.party_set(set_index),
            rows: Vec::new(),
            mode: Mode::Menu,
            slot: 0,
            list: ListState::new(VISIBLE, 0),
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(300), (236.0, 180.0)),
            blink: 0.0,
            title_img,
            entry: None,
        };
        p.refresh(env);
        p.place_cursor();
        p.cursor.snap();
        Some(p)
    }

    fn refresh(&mut self, env: &mut Env) {
        let Some(set) = env.session.save.menu.party_set(self.set_index) else { return };
        self.name = sj(&set.name);
        let n = (set.member_count.max(0) as usize).min(8);
        self.members = set.members[..n].to_vec();
        self.battle_max = (set.battle_max.max(1) as usize).min(4);
        self.battle_count = (set.battle_count.max(0) as usize).min(n).min(self.battle_max);
        let all = party_view(env.session);
        self.rows = self
            .members
            .iter()
            .filter_map(|&id| all.iter().find(|p| p.id == id).cloned())
            .map(|pc| Row { strip: self.sc.top.t_by_id(pc.face as i16), portrait: self.cms.as_ref().and_then(|c| c.t_by_id(pc.face as i16)), pc })
            .collect();
        self.list.set_len(self.rows.len());
    }

    fn store(&mut self, env: &mut Env) {
        let Some(mut set) = env.session.save.menu.party_set(self.set_index) else { return };
        for (i, m) in set.members.iter_mut().enumerate() {
            *m = self.members.get(i).copied().unwrap_or(0xff);
        }
        set.battle_count = self.battle_count as i8;
        env.session.save.menu.set_party_set(self.set_index, &set);
        self.refresh(env);
    }

    /// `CmdFormationMember` decide: put row `r` into battle slot `s`.
    fn place(&mut self, env: &mut Env, s: usize, r: usize) {
        let bc = self.battle_count;
        if r >= self.members.len() {
            return;
        }
        if s < bc && r == s {
            // "Remove %s.": the slot's own member leaves the battle team (one fighter always stays)
            if bc <= 1 {
                env.sound(MenuSe::Buzzer);
                return;
            }
            let m = self.members.remove(s);
            self.members.insert(bc - 1, m);
            self.battle_count -= 1;
        } else if r < bc && s < bc {
            self.members.swap(s, r);
        } else if s < bc {
            self.members.swap(s, r);
        } else {
            // an empty slot: the member joins the battle team after the others
            let m = self.members.remove(r);
            let at = bc.min(self.members.len());
            self.members.insert(at, m);
            self.battle_count = (bc + 1).min(self.battle_max);
        }
        env.sound(MenuSe::Decide);
        self.store(env);
    }

    fn reset(&mut self, env: &mut Env) {
        if let Some(o) = self.original.clone() {
            env.session.save.menu.set_party_set(self.set_index, &o);
            self.refresh(env);
        }
    }

    fn rows_origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((134.0, 45.0))
    }
    fn box_origin(&self) -> (f32, f32) {
        self.scene.msd.window(1).map(|w| (w.x, w.y)).unwrap_or((0.0, 147.0))
    }

    fn place_cursor(&mut self) {
        let (x, y) = match self.mode {
            // the menu mode has no cursor of its own (live `pm_a`): park it on the first row, hidden
            Mode::Menu | Mode::Member => {
                let (x, y) = self.rows_origin();
                (x - 8.0, y + self.list.slot() as f32 * ROW_H + 20.0)
            }
            Mode::Slot => {
                let (x, y) = self.box_origin();
                (x + 12.0 + self.slot as f32 * SLOT_PITCH, y + 56.0)
            }
        };
        self.cursor.set_target(x, y);
        self.cursor.visible = self.mode != Mode::Menu;
    }
}

impl Page for RetailFormPage {
    fn page(&self) -> CmdPage {
        CmdPage::Formation
    }
    fn title(&self) -> usize {
        2
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn backdrop(&self) -> Option<usize> {
        Some(1)
    }
    fn shows_root_list(&self) -> bool {
        true
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        Some(match self.mode {
            Mode::Menu => vec![(Button::Circle, 0), (Button::Cross, 3), (Button::Triangle, 5)],
            Mode::Slot => vec![(Button::Triangle, 5)],
            Mode::Member => Vec::new(),
        })
    }
    fn note(&self) -> String {
        let res = |i: usize| self.scene.msd.resource_bytes(i).map(sj).unwrap_or_default();
        match self.mode {
            Mode::Menu => cfmt(&res(6), &[self.name.as_str().into()]),
            Mode::Slot => res(7),
            Mode::Member => {
                if self.slot < self.battle_count && self.list.sel == self.slot {
                    cfmt(&res(12), &[self.rows.get(self.slot).map(|r| r.pc.name.as_str()).unwrap_or("").into()])
                } else {
                    res(8)
                }
            }
        }
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.blink += DT;
        if let Some(e) = self.entry.as_mut() {
            e.tick(env, keys);
            if let Some(r) = e.result() {
                if let (Some(name), Some(mut set)) = (r, env.session.save.menu.party_set(self.set_index)) {
                    set.name = sh2_menu::sjis::encode(&name);
                    env.session.save.menu.set_party_set(self.set_index, &set);
                }
                self.entry = None;
                self.refresh(env);
            }
            return Flow::Stay;
        }
        match self.mode {
            Mode::Menu => {
                if keys & padbit::SQUARE != 0 {
                    // the `Team Name` line of the common report (resource 10)
                    env.sound(MenuSe::Decide);
                    self.entry = crate::name_entry::NameEntry::new(env, 0, &self.name);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Slot;
                    self.slot = 0;
                } else if keys & padbit::TRIANGLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.reset(env);
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Slot => {
                let n = self.battle_max.max(1);
                if keys & (padbit::LEFT | padbit::UP) != 0 {
                    self.slot = (self.slot + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::RIGHT | padbit::DOWN) != 0 {
                    self.slot = (self.slot + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Member;
                    self.list.sel = if self.slot < self.battle_count { self.slot } else { self.battle_count.min(self.rows.len().saturating_sub(1)) };
                    self.list.set_len(self.rows.len());
                } else if keys & padbit::TRIANGLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.reset(env);
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
            Mode::Member => {
                if self.list.key(keys & (padbit::UP | padbit::DOWN)) {
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    self.place(env, self.slot, self.list.sel);
                    self.mode = Mode::Slot;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Slot;
                }
            }
        }
        self.place_cursor();
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let m = &self.scene.msd;
        let Some(w) = m.window(0) else { return };
        let (_, _, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let (ox, oy) = self.rows_origin();
        // the dark plate behind the rows (polygon 19 of each row: -4..240 x -4..44, they join into one panel)
        if let Some(p) = m.polygon(19) {
            for k in 0..self.rows.len().min(VISIBLE) {
                gs_poly(g, &p, ox, oy + k as f32 * ROW_H, a);
            }
        }
        for (k, row) in self.rows.iter().enumerate().skip(self.list.top).take(VISIBLE) {
            let sel = self.mode == Mode::Member && k == self.list.sel;
            self.draw_row(g, row, ox, oy + (k - self.list.top) as f32 * ROW_H, k < self.battle_count, sel, a);
        }
        self.draw_box(g, a);
        self.cursor.draw(g, &self.sc.cmn, a);
        if let Some(e) = &self.entry {
            e.draw(g, a);
        }
    }
}

impl RetailFormPage {
    /// One member row (`FORM.MSD` group 0, 236 x 44): stepped grey plate (polygons 0..3; 4..7 = the cyan glow of the chosen row), face
    /// strip (sprite 0) with the battle marker (the root page's triangle), `LEVEL` + big level, name (record 0), HP / MP values and gauges.
    #[allow(clippy::too_many_arguments)]
    fn draw_row(&self, g: &mut dyn MenuGfx, row: &Row, ox: f32, oy: f32, in_battle: bool, selected: bool, a: u8) {
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
        if in_battle {
            if let (Some(r), Some(top_marker)) = (m.sprite(1), sc.top.msd.sprite(9)) {
                blit(g, sc.top.t(4), ox + r.x, oy + r.y, r.w, r.h, (top_marker.u0 as f32, top_marker.v0 as f32, top_marker.u1 as f32, top_marker.v1 as f32), white(a));
            }
        }
        let name_c = if selected { rgb(CYAN, a) } else { white(a) };
        if let Some(t) = m.menu_text(0) {
            text_run_h(g, ox + t.x, oy + t.y - 2.0, &row.pc.name, 0, name_c, Some((1, 1)), TextRun::hscale_of(t.flags));
        }
        let fp = |i: usize| m.font_pos(i).unwrap_or((0.0, 0.0));
        let level_c = Rgba::new(0x46, 0x3e, 0x4e, a);
        let (x, y) = fp(0);
        sc.font_small.draw(g, ox + x, oy + y, "LEVEL", level_c);
        let (x, y) = fp(3);
        sc.font_big.draw(g, ox + x, oy + y, &format!("{:>2}", row.pc.level), white(a));
        let vals = [(1usize, 4usize, "HP", row.pc.hp as i32, row.pc.hp_max as i32, 2usize), (2, 5, "MP", row.pc.mp as i32, row.pc.mp_max as i32, 3)];
        for (lab, val, label, cur, max, spr) in vals {
            let (x, y) = fp(lab);
            sc.font_small.draw(g, ox + x, oy + y, label, white(a));
            let frac = if max > 0 { cur as f32 / max as f32 } else { 0.0 };
            let vc = if label == "HP" && frac < 0.25 {
                Rgba::new(0xc4, 0x00, 0x00, a)
            } else if label == "HP" && (frac < 0.5 || frac > 1.0) {
                Rgba::new(0xc4, 0xc4, 0x00, a)
            } else {
                white(a)
            };
            let (x, y) = fp(val);
            sc.font_small.draw(g, ox + x, oy + y, &cfmt("%3d/%3d", &[cur.into(), max.into()]), vc);
            if let (Some(back), Some(fill_r)) = (m.sprite(spr), m.sprite(spr + 2)) {
                draw_sprite_rec(g, &back, sc.gauge, ox, oy, a);
                let wf = (fill_r.w * frac.clamp(0.0, 1.0)).round();
                if wf > 0.0 {
                    blit(g, sc.gauge, ox + fill_r.x, oy + fill_r.y, wf, fill_r.h, (fill_r.u0 as f32, fill_r.v0 as f32, fill_r.u0 as f32 + wf, fill_r.v1 as f32), white(a));
                }
            }
        }
    }

    /// Window 1 (0, 147, 128 x 81): gradient plate (polygon 18) with the lavender rules (polygons 20 / 21 and 10..), the team name (record 1,
    /// cyan) and the four slanted battle slots (sprite 6 = the empty slot of attach 1, the member's portrait inside).
    fn draw_box(&self, g: &mut dyn MenuGfx, a: u8) {
        let m = &self.scene.msd;
        let (bx, by) = self.box_origin();
        if let Some(p) = m.polygon(18) {
            gs_poly(g, &p, bx, by, a);
        }
        // the lavender rules: top (10 / 11), under the name (8 / 9), bottom (20 / 21)
        for i in [8usize, 9, 10, 11, 20, 21] {
            if let Some(p) = m.polygon(i) {
                gs_poly(g, &p, bx, by, a);
            }
        }
        if let Some(t) = m.menu_text(1) {
            text_run_h(g, bx + t.x, by + t.y - 2.0, &self.name, 0, rgb(CYAN, a), Some((1, 0)), TextRun::hscale_of(t.flags));
        }
        for s in 0..self.battle_max {
            let sx = bx + s as f32 * SLOT_PITCH;
            let Some(r) = m.sprite(6) else { continue };
            let (x, y) = (sx + r.x, by + r.y);
            let glow = self.mode != Mode::Menu && s == self.slot;
            let filled = s < self.battle_count;
            if filled {
                if let Some(row) = self.rows.get(s) {
                    // the face of the 104 x 128 portrait in a slot leaning like the tile ("/"): top edge 9 px further right than the bottom
                    let c = white(a);
                    let (u0, v0, u1, v1) = (30.0, 14.0, 78.0, 84.0);
                    g.draw(sh2_menu::gfx::DrawCmd::Quad {
                        tex: row.portrait,
                        v: [vtx(x + 10.0, y + 1.0, u0, v0, c), vtx(x + 1.0, y + r.h - 1.0, u0, v1, c), vtx(x + r.w - 1.0, y + 1.0, u1, v0, c), vtx(x + r.w - 10.0, y + r.h - 1.0, u1, v1, c)],
                        blend: sh2_menu::gfx::Blend::Alpha,
                    });
                }
            } else {
                blit(g, self.scene.t(1), x, y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), white(a));
            }
            if glow {
                blit(g, self.scene.t(1), x, y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), Rgba::new(0x20, 0x80, 0x80, a / 2));
            }
        }
    }
}
