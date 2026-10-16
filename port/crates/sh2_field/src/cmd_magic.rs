//! `CmdMagic` (page 3, crest magic, JP 0x0047a210) and `CmdWhiteMagic` (page 2, a character's own field-usable skills):
//! pick a spell, pick a target, apply its effect words outside of battle.
//!
//! Data: the equipped crests of the character (`BTL0` crest slots -> `MC_P` records -> up to four `MAGI` ids each, filtered by the
//! crest's learned bits, see [`sh2_battle::actions::ActionTables::crest_magic`]); `MAGI` records (MP cost, effect words, usability
//! flags); names from `SSHMES`.  The effect is applied with the battle's own [`sh2_battle::actions::apply_records`] and the MP cost
//! is paid by the caster.  Layout: the character card and the 4-row list of `MENU/MSD/MAGIC.MSD`.
//!
//! **Retail White Magic** (US `CmdWhiteMagic` / `CmdTechniqueGoods` in `SH2US_FIELD.BIN`, checked against live PCSX2 captures): only
//! Nicolai (PC 0xb) can be picked (`CmdTopPC::SetTarget(0)`, US 0x486560); the list is his `SKIL` group in record order filtered by the
//! learned mask (`CreateScene` 0x487840 reads `CmdPC+0x38`, the battle's `SetSkill1Menu` mask = record `+0x6c`), names / Notes
//! `GetRegDat(9 / 0x1f, pc, i)`, cost `Retail_CmdPC_CalcMagicCostScaled` (+ the accessories' MP percentages), greyed (half alpha) when
//! battle-only (`(flags & 0x1f) >> 3 == 1`: Blessed Light) or above the current MP.  Scene `SKILL.MSD`: attach 1 the portrait card,
//! attach 2 the `Magic List` banner, attach 3 the `CmdSelectTarget` card, attach 4 the `Name / MP` fence.  The selected row's Judgement
//! Ring (step + modulate zones, `Retail_CmdPC_ApplyRingAreas`) is shown tilted next to the `CmdElement` stone (`ELEMENT.MSD`, element
//! `flags & 7`, `Retail_CmdElement_ChangeImage`); streak backdrop, root list on the right, no button report, no triangle view.
//! Confirm opens the target card (root list, ring and stone hidden); a successful cast stays on the card until the spell is no longer
//! affordable (`ExecSelectTarget` states 0xe / 0x10 / 0xd); cancel from the list returns to the root.

use std::sync::Arc;

use sh2_battle::actions::{apply_records, decode_effect_words, ActionRec};
use sh2_battle::hud_hits::HitArt;
use sh2_battle::rules::Lcg;
use sh2_core::game::padbit;
use sh2_gfx::effects::jring::JRing;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextRun, TextureId};
use sh2_menu::save::PcRec;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_item::{pc_fighter, store_fighter};
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 21.0;
const VISIBLE: usize = 4;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum Mode {
    List,
    Target,
    /// retail Crest Magic: the `CmdSort` window (square)
    Sort,
}

/// `MENU+0x28e`: the retail Crest Magic order (`CmdMagic::ExecSort` stores the `CmdSort` row: 0 Restore, 1 Attack, 2 Support, 3 By Alphabet).
const OFF_MAGIC_SORT: usize = 0x28e;

struct Entry {
    id: usize,
    name: String,
    mp: i32,
    usable: bool,
    /// retail: the Notes line (`GetRegDat(0x1f, pc, i)`)
    help: String,
    /// retail: element (`PCSKILL+4 & 7`: 0 Earth, 1 Water, 2 Fire, 3 Wind, 4 Light, 5 Dark, 6 None)
    element: u8,
    /// retail: the record's Judgement Ring zones (`+0x20..+0x3b`)
    ring_steps: Vec<(i16, i16)>,
    ring_mod: Option<(i16, i16, i16, i16)>,
    /// retail: target class `(flags >> 7) & 3` (3 = the whole party)
    target: u8,
}

impl Entry {
    fn plain() -> Self {
        Entry { id: 0, name: String::new(), mp: 0, usable: false, help: String::new(), element: 6, ring_steps: Vec::new(), ring_mod: None, target: 0 }
    }
}

/// Retail ring emblem centre (the same `JRing` placement as the item page, `CmdItem::GetReady`).
const RING_POS: (f32, f32) = (312.0, 300.0);
/// Retail colours of the `LEVEL.` / `HP.` / `MP.` / `SP.` labels (font 2, CLUT sets 3 / 4 / 5 / 6; live capture) and of the `Magic List`
/// banner text (set 3).
const LABEL_LEVEL: Rgba = Rgba::new(0x58, 0x48, 0x78, 0x80);
const LABEL_HMS: [Rgba; 3] = [Rgba::new(0x3c, 0x48, 0x78, 0x80), Rgba::new(0x58, 0x24, 0x5c, 0x80), Rgba::new(0x68, 0x1c, 0x1c, 0x80)];

/// `Retail_CmdPC_CalcMagicCostScaled` (US 0x46d200) + `Retail_CmdPC_ApplyCostModifiers` (0x46d2f0): the record's MP (`+0x1e`; effect 0x5f
/// costs a tenth of the maximum, at least 1), then every equipped accessory's MP percentage (menu data table 12 = demo 10, `+0xc`, s16)
/// compounds on it; rounded up, at least 1.
fn retail_cost(sc: &CmdScenes, rec: &ActionRec, r: &PcRec) -> i32 {
    let base = if rec.effect_id == 0x5f { ((r.mp_max as i32 + 5) / 10).max(1) } else { rec.mp };
    retail_cost_count(sc, base, 1, r)
}

/// `Retail_CmdPC_ApplyCostModifiers` (0x46d2f0): `cost * 100 / count` (count = equipped crests granting the spell, 1 for techniques), then
/// each equipped accessory's MP percentage compounds on it; rounded up, at least 1.
fn retail_cost_count(sc: &CmdScenes, base: i32, count: i32, r: &PcRec) -> i32 {
    let mut v = base * 100 / count.max(1);
    for &acc in r.accessories.iter().filter(|&&a| a >= 0) {
        let pct = sc.mdt.mdt_rec(10, acc as usize).and_then(|b| b.get(0xc..0xe)).map(|b| i16::from_le_bytes([b[0], b[1]]) as i32).unwrap_or(0);
        if pct != 0 {
            v += v * pct / 100;
        }
    }
    ((v + 99) / 100).max(1)
}

/// Retail `CmdElement` (`MENU/MSD/ELEMENT.MSD`, window (387, 221)): per element (attach 0..6, each a pack of four textures: the stone,
/// its shadow, the glyph and the name plate) and the emblem icons (attach 7 = the seven kanji, one 16-colour CLUT per element; attach 8
/// = the dark disc / the dashed ring).
/// Colour of the dashed ring per element (0 Earth, 1 Water, 2 Fire, 3 Wind, 4 Light, 5 Dark, 6 none), measured on the live Graveyard
/// / Library captures (`gy_c`, `lchar_b`; capture RGB halved to the 0x80 scale).
const ELEMENT_RING: [(u8, u8, u8); 7] = [(0x1e, 0x6a, 0x6a), (0x2a, 0x5a, 0x5e), (0x72, 0x1e, 0x30), (0x74, 0x70, 0x10), (0x80, 0x80, 0x80), (0x78, 0x78, 0x7c), (0x80, 0x80, 0x80)];

pub(crate) struct ElemArt {
    scene: Arc<SceneTex>,
    /// `(stone, stone size, name plate)` per element
    stones: Vec<(Option<TextureId>, (f32, f32), Option<TextureId>)>,
    /// the kanji strip in each element's CLUT
    glyphs: Vec<Option<TextureId>>,
}

impl ElemArt {
    pub(crate) fn load(env: &mut Env) -> Option<Self> {
        use sh2_menu::disc::FileSource;
        const PATH: &str = "MENU/MSD/ELEMENT.MSD";
        let scene = env.file_scene(PATH)?;
        let data = env.assets.disc.as_ref()?.read(PATH)?;
        let m = sh2_menu::msd::Msd::parse(data).ok()?;
        let mut stones = Vec::new();
        let mut glyphs = Vec::new();
        for k in 0..7 {
            let b = m.attach_data(k).unwrap_or(&[]);
            // `{u32 count; u32 size; {"tex\0", u32 offset} x count}`
            let off = |i: usize| -> Option<usize> {
                if b.get(8..12)? != b"tex\0" {
                    return None;
                }
                Some(u32::from_le_bytes(b.get(12 + i * 8..16 + i * 8)?.try_into().ok()?) as usize)
            };
            let size = off(0).and_then(|o| sh2_gfx::texture::MenuTexHeader::parse(b, o).ok()).map(|h| (h.width as f32, h.height as f32)).unwrap_or((96.0, 116.0));
            let cached = |env: &mut Env, name: &str, img: &dyn Fn() -> Option<sh2_gfx::texture::Rgba8Image>| -> Option<TextureId> {
                let key = format!("{PATH}#{k}{name}");
                if let Some(t) = env.cache.images.get(&key) {
                    return *t;
                }
                let t = img().and_then(|i| env.reg.add(&i));
                env.cache.images.insert(key, t);
                t
            };
            let stone = cached(env, "s", &|| sh2_gfx::texture::decode_menu_texture(b, off(0)?).ok());
            let plate = cached(env, "p", &|| sh2_gfx::texture::decode_menu_texture(b, off(3)?).ok());
            // the kanji strip with CLUT k (4 bit, 16 CLUTs in CSM1 order)
            let glyph = cached(env, "g", &|| {
                let b = m.attach_data(7)?;
                let h = sh2_gfx::texture::MenuTexHeader::parse(b, 0).ok()?;
                let all = sh2_gfx::texture::read_palette(b, h.clut_off as usize, 256, true).ok()?;
                let n = (h.width as usize * h.height as usize + 1) / 2;
                let po = h.pix_off as usize;
                sh2_gfx::texture::decode_indexed(b.get(po..po + n)?, h.width as u32, h.height as u32, 4, &all[k * 16..k * 16 + 16]).ok()
            });
            stones.push((stone, size, plate));
            glyphs.push(glyph);
        }
        Some(ElemArt { scene, stones, glyphs })
    }

    /// The element display at the scene window: the stone, the name plate (sprite 3), the dark disc and the dashed ring (sprites 1 / 2 on
    /// attach 8) and the element's kanji (sprite 0, cell `k` of attach 7).
    pub(crate) fn draw(&self, g: &mut dyn MenuGfx, k: u8, a: u8) {
        let Some(w) = self.scene.msd.window(0) else { return };
        self.draw_at(g, k, w.x, w.y, a);
    }

    /// [`Self::draw`] with the stone's top left at `(ox, oy)` (the Graveyard shows six of them).
    pub(crate) fn draw_at(&self, g: &mut dyn MenuGfx, k: u8, ox: f32, oy: f32, a: u8) {
        let k = (k as usize).min(6);
        let m = &self.scene.msd;
        let c = Rgba::new(0x80, 0x80, 0x80, a);
        let (stone, (sw, sh), plate) = self.stones[k];
        blit(g, stone, ox, oy, sw, sh, (0.0, 0.0, sw, sh), c);
        if let Some(r) = m.sprite(3) {
            blit(g, plate, ox + r.x, oy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), c);
        }
        for i in [1usize, 2] {
            if let Some(r) = m.sprite(i) {
                // the dashed ring takes the element's colour (live: Fire red, Earth / Water teal, Wind yellow, Light / Dark white)
                let tint = if i == 2 { ELEMENT_RING[k] } else { (0x80, 0x80, 0x80) };
                blit(g, self.scene.t(8), ox + r.x, oy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), Rgba::new(tint.0, tint.1, tint.2, a));
            }
        }
        if let Some(r) = m.sprite(0) {
            let cell = 144.0 / 7.0;
            let u0 = (k as f32 * cell).round();
            blit(g, self.glyphs[k], ox + r.x, oy + r.y, r.w, r.h, (u0, r.v0 as f32, u0 + r.w, r.v1 as f32), c);
        }
    }
}

pub struct MagicPage {
    white: bool,
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    card: Option<Arc<SceneTex>>,
    tgt_card: Option<Arc<SceneTex>>,
    pcs: Vec<PcView>,
    pc: usize,
    entries: Vec<Entry>,
    list: ListState,
    mode: Mode,
    tgt: usize,
    all: bool,
    face: Option<TextureId>,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    msg: Option<(String, f32)>,
    title_img: Option<(TextureId, (u32, u32))>,
    caster_mp: (u16, u16),
    retail: bool,
    /// retail `SKILL.MSD` attach 4 (`Name / MP` fence), attach 2 (`Magic List` banner)
    fence: Option<Arc<SceneTex>>,
    banner: Option<Arc<SceneTex>>,
    /// retail: the selected technique's Judgement Ring and its textures
    ring: Option<JRing>,
    ring_art: Option<Arc<HitArt>>,
    /// retail `CmdElement` (`MENU/MSD/ELEMENT.MSD`)
    elem: Option<ElemArt>,
    /// retail Crest Magic: `MAGIC.MSD` attach 4 (`CmdSort`: Restore / Attack / Support / By Alphabet) and its cursor row
    sort_scene: Option<Arc<SceneTex>>,
    sort_sel: usize,
}

impl MagicPage {
    pub fn new(env: &mut Env, white: bool, pc: Option<u8>) -> Option<Self> {
        let sc = env.scenes()?;
        let file = if white { "MENU/MSD/SKILL.MSD" } else { "MENU/MSD/MAGIC.MSD" };
        let scene = env.file_scene(file)?;
        let card = env.nested_scene(file, 1);
        let retail = sh2_core::boot::is_retail();
        // retail: the target card is attach 3 of `SKILL.MSD` / `MAGIC.MSD` (the same `CmdSelectTarget` scene as `ITEM.MSD` attach 2); the
        // `Name / MP` fence is attach 4 of `SKILL.MSD`, attach 5 of `MAGIC.MSD` (whose attach 4 is the `CmdSort` window)
        let tgt_card = if retail { env.nested_scene(file, 3) } else { env.nested_scene("MENU/MSD/ITEM.MSD", 2) };
        let fence = if retail { env.nested_scene(file, if white { 4 } else { 5 }) } else { None };
        let sort_scene = if retail && !white { env.nested_scene(file, 4) } else { None };
        let banner = if retail { env.nested_scene(file, 2) } else { None };
        let ring_art = if retail { env.ring_art() } else { None };
        let elem = if retail { ElemArt::load(env) } else { None };
        if retail {
            dev_hp_override(env);
        }
        let pcs = party_view(env.session);
        if pcs.is_empty() {
            return None;
        }
        let pci = pc.and_then(|id| pcs.iter().position(|p| p.id == id)).unwrap_or(0);
        let w = scene.msd.window(0);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let mut p = MagicPage {
            white,
            sc,
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(240), (200.0, 100.0)),
            scene,
            card,
            tgt_card,
            pcs,
            pc: pci,
            entries: Vec::new(),
            list: ListState::new(VISIBLE, 0),
            mode: Mode::List,
            tgt: 0,
            all: false,
            face: None,
            cursor: CmdCursor::new(0.0, 0.0),
            time: 0.0,
            msg: None,
            title_img,
            caster_mp: (0, 0),
            retail,
            fence,
            banner,
            ring: None,
            ring_art,
            elem,
            sort_scene,
            sort_sel: 0,
        };
        p.rebuild(env);
        p.cursor_to_sel();
        p.cursor.snap();
        p.update_ring();
        Some(p)
    }

    fn pc_id(&self) -> u8 {
        self.pcs[self.pc].id
    }

    fn rebuild(&mut self, env: &mut Env) {
        self.face = env.face(self.pcs[self.pc].face);
        let pc = self.pc_id();
        let mut entries = Vec::new();
        if let (Some(t), Some(r)) = (env.tables, env.session.save.btl.pc(pc as usize)) {
            self.caster_mp = (r.mp, r.mp_max);
            if self.retail && self.white {
                entries = self.retail_entries(env, t, pc);
            } else if self.retail {
                entries = self.retail_crest_entries(env, t, pc);
            } else if self.white {
                for (i, rec) in t.groups.get(pc as usize).map(|g| g.iter().enumerate().collect::<Vec<_>>()).unwrap_or_default() {
                    let v = (rec.flags & 0x1f) >> 3;
                    if rec.empty || !(v == 2 || v == 1) {
                        continue;
                    }
                    entries.push(Entry { id: i, name: { let n = env.name(15, rec.name_idx.max(0) as usize); if n.trim().is_empty() { format!("技{}", i + 1) } else { n } }, mp: rec.mp, usable: v == 2, ..Entry::plain() });
                }
            } else {
                let learned = |c: usize| env.session.save.btl.skill_learned(c);
                for id in t.crest_magic(&r.skills, &learned) {
                    let Some(rec) = t.magic.get(id) else { continue };
                    let v = (rec.flags & 0x1f) >> 3;
                    entries.push(Entry { id, name: { let n = env.name(17, id); if n.trim().is_empty() { format!("魔法{}", id + 1) } else { n } }, mp: rec.mp, usable: v == 2 || v == 0 && !rec.is_offensive(), ..Entry::plain() });
                }
            }
        }
        self.entries = entries;
        self.list.set_len(self.entries.len());
    }

    /// Retail `CmdTechniqueGoods::CreateScene` (US 0x487840): the character's `SKIL` group (`GetRegDat(0x3c, pc)`) in record order, only
    /// the records whose bit is set in the learned mask (`CmdPC+0x38`, the battle's `SetSkill1Menu` mask: Nicolai = save record `+0x6c`);
    /// name `GetRegDat(9, pc, i)`, cost `Retail_CmdPC_CalcMagicCostScaled`; a row is greyed (half alpha, not selectable) when it is a
    /// battle-only technique (`(flags & 0x1f) >> 3 == 1`) or costs more than the current MP.
    fn retail_entries(&self, env: &Env, t: &sh2_battle::actions::ActionTables, pc: u8) -> Vec<Entry> {
        let Some(group) = t.groups.get(pc as usize) else { return Vec::new() };
        let Some(r) = env.session.save.btl.pc(pc as usize) else { return Vec::new() };
        let src = sh2_battle::menu_data::MenuSource { btl: &env.session.save.btl, menu: &env.session.save.menu, pc: pc as usize, retail: true };
        let mask = src.skill_mask(group.len());
        let us = env.db.and_then(|d| d.us());
        let mut v = Vec::new();
        for (i, rec) in group.iter().enumerate().take(64) {
            if mask & (1u64 << i) == 0 {
                continue;
            }
            let name = us.as_ref().and_then(|u| u.text(9, pc as usize, i as i32)).filter(|n| !n.trim().is_empty()).unwrap_or_else(|| env.name(15, rec.name_idx.max(0) as usize));
            let help = us.as_ref().and_then(|u| u.text(0x1f, pc as usize, i as i32)).unwrap_or_default();
            let mp = retail_cost(&self.sc, rec, &r);
            let battle_only = (rec.flags & 0x1f) >> 3 == 1;
            v.push(Entry {
                id: i,
                name,
                mp,
                usable: !battle_only && mp <= r.mp as i32,
                help,
                element: (rec.flags & 7) as u8,
                ring_steps: rec.ring_steps.clone(),
                ring_mod: rec.ring_mod,
                target: ((rec.flags >> 7) & 3) as u8,
            });
        }
        v
    }

    /// Retail `CmdMagicGoods::UpdateScene` (US 0x4c9b60): the rows follow the magic order table (menu data table, retail key 14 = demo 12:
    /// one record per spell, `+0xc + sort * 2` = the spell at that place for the order `MENU+0x28e`); a spell is listed when the character's
    /// `CmdPC::CreateMagic` count (0x46c200: per equipped crest of record `+0x32..`, each `MC_P` spell whose flag bit asks for the crest's
    /// learned bit only when it is set; the count is how many equipped crests grant it) is non-zero.  Cost `Retail_CmdPC_CalcMagicCost`
    /// (0x46d0c0): `MAGI+0x1e` (effect 0x4a: a tenth of the maximum MP), divided by the count, then the accessories' percentages; greyed when
    /// battle-only (`(flags & 0x1f) >> 3 == 1`) or above the current MP.  Name `GetRegDat(0xb)`, Notes = magic description kind 0x21.
    fn retail_crest_entries(&self, env: &Env, t: &sh2_battle::actions::ActionTables, pc: u8) -> Vec<Entry> {
        let Some(r) = env.session.save.btl.pc(pc as usize) else { return Vec::new() };
        let src = sh2_battle::menu_data::MenuSource { btl: &env.session.save.btl, menu: &env.session.save.menu, pc: pc as usize, retail: true };
        let mut count = vec![0u8; t.magic.len().max(1)];
        for &c in r.skills.iter().filter(|&&c| c >= 0) {
            let Some(cr) = t.crests.get(c as usize) else { continue };
            for (k, &m) in cr.magic.iter().enumerate() {
                if m < 0 || (cr.flags & (1 << k) != 0 && !src.crest_learned(c as usize)) {
                    continue;
                }
                if let Some(n) = count.get_mut(m as usize) {
                    *n = n.saturating_add(1);
                }
            }
        }
        let mode = env.session.save.menu.data.get(OFF_MAGIC_SORT).copied().unwrap_or(0).min(3) as usize;
        let us = env.db.and_then(|d| d.us());
        let mut order: Vec<usize> = (0..self.sc.mdt.mdt_count(12))
            .filter_map(|k| {
                let b = self.sc.mdt.mdt_rec(12, k)?;
                let o = 0xc + mode * 2;
                let id = i16::from_le_bytes([*b.get(o)?, *b.get(o + 1)?]);
                (id >= 0).then_some(id as usize)
            })
            .collect();
        if order.is_empty() {
            order = (0..t.magic.len()).collect();
        }
        let mut v = Vec::new();
        for id in order {
            let n = count.get(id).copied().unwrap_or(0);
            let Some(rec) = t.magic.get(id).filter(|_| n > 0) else { continue };
            let base = if rec.effect_id == 0x4a { ((r.mp_max as i32 + 5) / 10).max(1) } else { rec.mp };
            let mp = retail_cost_count(&self.sc, base, n as i32, &r);
            let battle_only = (rec.flags & 0x1f) >> 3 == 1;
            log::debug!("crest magic row {id}: flags {:#x} count {n} mp {mp} battle_only {battle_only}", rec.flags);
            let name = Some(t.magic_name(id).to_string()).filter(|n| !n.trim().is_empty()).unwrap_or_else(|| format!("Magic {id}"));
            v.push(Entry {
                id,
                name,
                mp,
                usable: !battle_only && mp <= r.mp as i32,
                help: us.as_ref().and_then(|u| u.text(0x21, id, -1)).unwrap_or_default(),
                element: (rec.flags & 7) as u8,
                ring_steps: rec.ring_steps.clone(),
                ring_mod: rec.ring_mod,
                target: ((rec.flags >> 7) & 3) as u8,
            });
        }
        v
    }

    /// Retail: the selected technique's ring (`Retail_CmdPC_ApplyRingAreas`: the record's step zones and modulate zone) at the item page's
    /// emblem place, home tilt, no pointer.
    fn update_ring(&mut self) {
        if !self.retail {
            return;
        }
        self.ring = self.entries.get(self.list.sel).and_then(|e| {
            if e.ring_steps.is_empty() && e.ring_mod.is_none() {
                return None;
            }
            let mut j = JRing::new(0);
            j.center = RING_POS;
            j.rot = j.home_rot;
            j.scale_x = j.home_scale_x;
            j.scale_y = 1.0;
            j.ring_visible = true;
            j.pointer_visible = false;
            for &(s, w) in &e.ring_steps {
                j.add_step_area(s.rem_euclid(360), w, None, 0);
            }
            if let Some((s, w, pct, strike)) = e.ring_mod {
                j.add_modulate_area(s.rem_euclid(360), w, pct, strike, None, None, None);
            }
            for a in j.areas.iter_mut().filter(|a| a.kind.is_some()) {
                a.visible = true;
            }
            Some(j)
        });
    }

    fn list_origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((42.0, 280.0))
    }

    fn cursor_to_sel(&mut self) {
        let (x, y) = self.list_origin();
        self.cursor.set_target(x - 4.0, y + self.list.slot() as f32 * ROW_H + 10.0);
    }

    fn cast(&mut self, env: &mut Env) {
        let Some(e) = self.entries.get(self.list.sel) else { return };
        let Some(rec) = env.tables.and_then(|t| if self.white { t.groups.get(self.pc_id() as usize).and_then(|g| g.get(e.id)) } else { t.magic.get(e.id) }).cloned() else { return };
        let caster = self.pc_id();
        let Some(mut cf) = pc_fighter(env, caster) else { return };
        let cost = if self.retail { e.mp } else { rec.mp };
        if cf.mp < cost {
            env.sound(MenuSe::Buzzer);
            return;
        }
        let targets: Vec<u8> = if self.all { self.pcs.iter().map(|p| p.id).collect() } else { vec![self.pcs[self.tgt].id] };
        let mut rng = Lcg(env.tick.wrapping_mul(0x9e37_79b9) ^ e.id as u64);
        let mut changed = false;
        let satk = cf.satk;
        for t in targets {
            let Some(mut f) = pc_fighter(env, t) else { continue };
            let recs = decode_effect_words(&rec.words, cf.satk, satk, true);
            let a = apply_records(&recs, &mut f, &mut rng);
            if a.hp != 0 || a.mp != 0 || a.sp != 0 || a.revived || a.status_cured != 0 {
                changed = true;
                store_fighter(env, t, &f);
            }
        }
        if !changed {
            env.sound(MenuSe::Buzzer);
            return;
        }
        // the caster pays (re-read: the caster may also have been a target)
        if let Some(mut c) = pc_fighter(env, caster) {
            c.mp = (c.mp - cost).max(0);
            store_fighter(env, caster, &c);
        }
        cf.mp = 0;
        env.sound(MenuSe::Decide);
        self.pcs = party_view(env.session);
        self.rebuild(env);
        // retail `CmdWhiteMagic::ExecSelectTarget`: the target card stays up (state 0xe -> 0x10) until the technique is no longer affordable
        // (`CmdTechniqueGoods::UpdateScene` greys it -> state 0xd)
        if !self.retail || !self.entries.get(self.list.sel).map(|e| e.usable).unwrap_or(false) {
            self.mode = Mode::List;
        }
    }
}

impl MagicPage {
    /// Retail target card origin (`SKILL.MSD` attach 3, window 0).
    fn card_origin(&self) -> (f32, f32) {
        self.tgt_card.as_ref().and_then(|c| c.msd.window(0)).map(|w| (w.x, w.y)).unwrap_or((256.0, 42.0))
    }

    /// Retail `CmdWhiteMagic::SelectGoods` / `ExecSelectTarget` (US 0x4d27d0 / 0x4d2c50): up / down move (wrapping), confirm on a usable row
    /// opens `CmdSelectTarget` (class `(flags >> 7) & 3`, 3 = everyone), a greyed row buzzes, cancel leaves the page; no character switch
    /// (only Nicolai has the page).  In the target card left / right pick the member, confirm casts, cancel returns to the list.
    fn tick_retail(&mut self, env: &mut Env, keys: u16) -> Flow {
        match self.mode {
            Mode::List => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                    self.update_ring();
                } else if keys & padbit::CIRCLE != 0 {
                    match self.entries.get(self.list.sel) {
                        Some(e) if e.usable && !self.pcs.is_empty() => {
                            env.sound(MenuSe::Decide);
                            self.all = e.target == 3;
                            self.mode = Mode::Target;
                            self.tgt = 0;
                        }
                        Some(_) => env.sound(MenuSe::Buzzer),
                        None => {}
                    }
                } else if keys & padbit::SQUARE != 0 && self.sort_scene.is_some() {
                    // `CmdMagic::Enter` -> `CmdSort` (the window opens on the current order)
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Sort;
                    self.sort_sel = env.session.save.menu.data.get(OFF_MAGIC_SORT).copied().unwrap_or(0).min(3) as usize;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Sort => {
                let n = self.sort_rows();
                if keys & padbit::UP != 0 {
                    self.sort_sel = (self.sort_sel + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.sort_sel = (self.sort_sel + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    // `CmdMagic::ExecSort`: `MENU+0x28e = row`, the list is rebuilt in that order and the cursor goes back to the top row
                    env.sound(MenuSe::Decide);
                    if let Some(b) = env.session.save.menu.data.get_mut(OFF_MAGIC_SORT) {
                        *b = self.sort_sel as u8;
                    }
                    self.list = ListState::new(VISIBLE, 0);
                    self.rebuild(env);
                    self.update_ring();
                    self.mode = Mode::List;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                }
            }
            Mode::Target => {
                let n = self.pcs.len().max(1);
                if keys & padbit::LEFT != 0 && !self.all {
                    self.tgt = (self.tgt + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::RIGHT != 0 && !self.all {
                    self.tgt = (self.tgt + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    self.cast(env);
                    self.update_ring();
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                }
            }
        }
        match self.mode {
            Mode::Target => {
                let (x, y) = self.card_origin();
                self.cursor.set_target(x + 22.0, y + 54.0);
            }
            Mode::Sort => {
                let (x, y) = self.sort_origin();
                self.cursor.set_target(x - 6.0, y + self.sort_sel as f32 * 20.0 + 10.0);
            }
            Mode::List => self.cursor_to_sel(),
        }
        Flow::Stay
    }

    fn sort_rows(&self) -> usize {
        self.sort_scene.as_ref().map(|s| s.msd.count(sh2_menu::msd::ChunkType::Text)).unwrap_or(4).clamp(1, 4)
    }

    fn sort_origin(&self) -> (f32, f32) {
        self.sort_scene.as_ref().and_then(|s| s.msd.window(0)).map(|w| (w.x, w.y)).unwrap_or((260.0, 92.0))
    }

    /// Retail `CmdSort` (`MAGIC.MSD` attach 4, window (260, 92)): the `Name` fence of the list scene with the four orders, the selected one cyan
    /// (the same window as the item page's, one row taller).
    fn draw_sort_retail(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(s) = &self.sort_scene else { return };
        let (sx, sy) = self.sort_origin();
        let n = self.sort_rows();
        let (bx, by, bw) = (sx - 6.0, sy - 31.0, 113.0);
        let back = self.fence.as_ref().and_then(|f| f.msd.polygon(0));
        fence_box(g, back.as_ref(), self.sc.fence_tex, bx, by, bw, 41.0 + n as f32 * 20.0, a);
        if let Some(f) = &self.fence {
            if let (Some(t), Some(b)) = (f.msd.menu_text(0), f.msd.resource_bytes(0)) {
                let hs = TextRun::hscale_of(t.flags);
                let label = sj(b);
                let tw = run_width(g, 0, &label, hs, Some((1, 1)));
                text_run_h(g, bx + (bw - tw) * 0.5, by + t.y - 1.0, &label, 0, white(a), Some((1, 1)), hs);
            }
        }
        let hs = s.msd.menu_text(0).map(|t| TextRun::hscale_of(t.flags)).unwrap_or(1.0);
        for i in 0..n {
            let t = s.msd.text(i).map(sj).unwrap_or_default();
            let c = if i == self.sort_sel { Rgba::new(0x00, 0x80, 0x80, a) } else { white(a) };
            text_run_h(g, sx, sy + i as f32 * 20.0, &t, 0, c, None, hs);
        }
    }

    fn draw_retail(&self, g: &mut dyn MenuGfx) {
        let Some(w) = self.scene.msd.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        self.draw_card_retail(g, a);
        self.draw_banner(g, a);
        self.draw_list_retail(g, w.x + dx, w.y + dy, a);
        if self.mode == Mode::Sort {
            self.draw_sort_retail(g, a);
        }
        if self.mode == Mode::Target {
            self.draw_target_retail(g, a);
        } else {
            if let (Some(r), Some(art)) = (&self.ring, &self.ring_art) {
                sh2_battle::hud_hits::draw_ring(g, art, r, &[0.0; 9], 0);
            }
            if let (Some(el), Some(e)) = (&self.elem, self.entries.get(self.list.sel)) {
                el.draw(g, e.element, a);
            }
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }

    /// `SKILL.MSD` attach 1 (window (10, 52)): the portrait medallion, the name, `LEVEL.` + level over the lavender rule (polygons 0 / 1),
    /// the coloured `HP. / MP. / SP.` labels with `cur/ max`.
    fn draw_card_retail(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(card) = &self.card else { return };
        let pc = &self.pcs[self.pc];
        let m = &card.msd;
        let (cx, cy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((10.0, 52.0));
        face_frame(g, &self.sc.cmn, cx, cy, a);
        if let Some(r) = m.sprite(0) {
            blit(g, self.face, cx + r.x, cy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), white(a));
        }
        for i in 0..2 {
            if let Some(p) = m.polygon(i) {
                // untextured: GS colours, halved for the canvas
                let col = |k: usize| Rgba::new(p.rgba[k][0] / 2, p.rgba[k][1] / 2, p.rgba[k][2] / 2, ((p.rgba[k][3] as u32 * a as u32) / 0x80) as u8);
                g.draw(sh2_menu::gfx::DrawCmd::Quad {
                    tex: None,
                    v: [vtx(cx + p.x[0], cy + p.y[0], 0.0, 0.0, col(0)), vtx(cx + p.x[1], cy + p.y[1], 0.0, 0.0, col(1)), vtx(cx + p.x[2], cy + p.y[2], 0.0, 0.0, col(2)), vtx(cx + p.x[3], cy + p.y[3], 0.0, 0.0, col(3))],
                    blend: sh2_menu::gfx::Blend::Alpha,
                });
            }
        }
        let res = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        let tint = |c: Rgba| Rgba::new(c.r, c.g, c.b, a);
        if let Some(t) = m.menu_text(4) {
            text_run_h(g, cx + t.x, cy + t.y, &pc.name, 0, white(a), Some((1, 1)), TextRun::hscale_of(t.flags));
        }
        if let Some(t) = m.menu_text(0) {
            text_run_h(g, cx + t.x, cy + t.y - 3.0, &res(0, "LEVEL."), 2, tint(LABEL_LEVEL), None, TextRun::hscale_of(t.flags));
        }
        if let Some(t) = m.menu_text(5) {
            text_run_h(g, cx + t.x, cy + t.y - 3.0, &cfmt(&res(4, "%2d"), &[(pc.level as i32).into()]), 2, white(a), None, 1.0);
        }
        let rows = [(pc.hp as i32, pc.hp_max as i32), (self.caster_mp.0 as i32, self.caster_mp.1 as i32), (pc.sp as i32, pc.sp_max as i32)];
        let (vx, sx) = (m.menu_text(6).map(|t| t.x).unwrap_or(126.0), m.menu_text(7).map(|t| t.x).unwrap_or(151.0));
        let hs = m.menu_text(6).map(|t| TextRun::hscale_of(t.flags)).unwrap_or(0.8);
        for (k, (cur, max)) in rows.iter().enumerate() {
            let Some(t) = m.menu_text(1 + k) else { continue };
            text_run_h(g, cx + t.x, cy + t.y - 3.0, &res(1 + k, ["HP.", "MP.", "SP."][k]), 2, tint(LABEL_HMS[k]), None, TextRun::hscale_of(t.flags));
            let fmt = res(5, "%3d");
            text_run_h(g, cx + vx, cy + t.y - 1.0, &cfmt(&fmt, &[(*cur).into()]), 0, white(a), Some((1, 1)), hs);
            text_run_h(g, cx + sx, cy + t.y - 1.0, &format!("{}{}", res(6, "/"), cfmt(&fmt, &[(*max).into()])), 0, white(a), Some((1, 1)), hs);
        }
    }

    /// `SKILL.MSD` attach 2: the `Magic List` banner (three sprites of its 192 x 28 texture at group (0, 195)) and its lavender title.
    fn draw_banner(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(b) = &self.banner else { return };
        let m = &b.msd;
        let (ox, oy) = m.group(0).map(|gr| (gr.x, gr.y)).unwrap_or((0.0, 195.0));
        for i in 0..3 {
            if let Some(r) = m.sprite(i) {
                draw_sprite_rec(g, &r, b.t(0), ox, oy, a);
            }
        }
        if let (Some(t), Some(s)) = (m.menu_text(0), m.resource_bytes(0)) {
            text_run_h(g, ox + t.x, oy + t.y - 3.0, &sj(s), 2, Rgba::new(LABEL_LEVEL.r, LABEL_LEVEL.g, LABEL_LEVEL.b, a), Some((1, 0)), TextRun::hscale_of(t.flags));
        }
    }

    /// The `Name / MP` fence (attach 4) and the rows (window (42, 280), 4 visible): name + `%3d` cost, selected cyan, greyed rows at half alpha.
    fn draw_list_retail(&self, g: &mut dyn MenuGfx, ox: f32, oy: f32, a: u8) {
        let (lx, ly) = self.list_origin();
        if let Some(f) = &self.fence {
            if let Some(fw) = f.msd.window(0) {
                draw_fence_tex(g, f, self.sc.fence_tex, fw.x + ox - lx, fw.y + oy - ly, a, true);
            }
        }
        let m = &self.scene.msd;
        let (name_r, mp_r) = (m.menu_text(0), m.menu_text(1));
        let hs = name_r.as_ref().map(|r| TextRun::hscale_of(r.flags)).unwrap_or(0.8);
        let name_x = name_r.as_ref().map(|r| r.x).unwrap_or(2.0);
        let mp_x = mp_r.as_ref().map(|r| r.x).unwrap_or(148.0);
        let fmt = m.resource_bytes(8).map(sj).filter(|f| !f.is_empty()).unwrap_or_else(|| "%3d".into());
        for (slot, e) in self.entries.iter().skip(self.list.top).take(VISIBLE).enumerate() {
            let y = oy + slot as f32 * ROW_H;
            let ra = if e.usable { a } else { a / 2 };
            let c = if self.list.top + slot == self.list.sel { Rgba::new(0x00, 0x80, 0x80, ra) } else { white(ra) };
            text_run_h(g, ox + name_x, y - 1.0, &e.name, 0, c, None, hs);
            text_run_h(g, ox + mp_x, y - 1.0, &cfmt(&fmt, &[e.mp.into()]), 0, c, None, hs);
        }
        draw_scroll_marks(g, ox + 90.0, oy, oy + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
    }

    /// Retail `CmdSelectTarget` (`SKILL.MSD` attach 3): portrait ring + face, coloured `HP. / MP. / SP.`, the numbers and `< Name >`.
    fn draw_target_retail(&self, g: &mut dyn MenuGfx, a: u8) {
        let (Some(card), Some(pc)) = (&self.tgt_card, self.pcs.get(self.tgt)) else { return };
        let (x, y) = self.card_origin();
        let m = &card.msd;
        if let Some(r) = m.sprite(0) {
            draw_sprite_rec(g, &r, card.t(0), x, y, a);
        }
        if let Some(r) = m.sprite(1) {
            draw_sprite_rec(g, &r, card.t_by_id(pc.face as i16), x, y, a);
        }
        let rows = [(pc.hp as i32, pc.hp_max as i32), (pc.mp as i32, pc.mp_max as i32), (pc.sp as i32, pc.sp_max as i32)];
        let fmt = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        for (k, (cur, max)) in rows.iter().enumerate() {
            if let Some(t) = m.menu_text(2 + k) {
                let c = LABEL_HMS[k];
                text_run_h(g, x + t.x, y + t.y - 3.0, &fmt(k, ["HP.", "MP.", "SP."][k]), 2, Rgba::new(c.r, c.g, c.b, a), None, TextRun::hscale_of(t.flags));
            }
            if let Some(t) = m.menu_text(6 + k) {
                text_run_h(g, x + t.x, y + t.y - 1.0, &cfmt(&fmt(3, "%3d"), &[(*cur).into()]), 0, white(a), None, TextRun::hscale_of(t.flags));
            }
            if let Some(t) = m.menu_text(10 + k) {
                text_run_h(g, x + t.x, y + t.y - 1.0, &cfmt(&fmt(4, "/%3d"), &[(*max).into()]), 0, white(a), None, TextRun::hscale_of(t.flags));
            }
        }
        let name = if self.all { m.text(0).map(sj).unwrap_or_default() } else { pc.name.clone() };
        let t0 = m.menu_text(0);
        let hs = t0.as_ref().map(|t| TextRun::hscale_of(t.flags)).unwrap_or(1.0);
        let ny = y + t0.as_ref().map(|t| t.y).unwrap_or(94.0);
        let tw = run_width(g, 0, &name, hs, Some((1, 1)));
        let cx = x + 96.0;
        text_run_h(g, cx - tw * 0.5, ny, &name, 0, white(a), Some((1, 1)), hs);
        if !self.all && self.pcs.len() > 1 {
            if let Some(t) = self.sc.cmn.s.t(4) {
                blit(g, Some(t), cx - tw * 0.5 - 26.0, ny, 24.0, 22.0, (0.0, 2.0 * 22.0, 24.0, 3.0 * 22.0), white(a));
                blit(g, Some(t), cx + tw * 0.5 + 2.0, ny, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), white(a));
            }
        }
    }
}

impl Page for MagicPage {
    fn page(&self) -> CmdPage {
        if self.white {
            CmdPage::WhiteMagic
        } else {
            CmdPage::Magic
        }
    }
    fn title(&self) -> usize {
        if self.white {
            28
        } else {
            13
        }
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        if let Some((m, _)) = &self.msg {
            return m.clone();
        }
        if self.retail && self.mode == Mode::Sort {
            return self.sort_scene.as_ref().and_then(|s| s.msd.text_entry(self.sort_sel)).map(|e| sj(e.1)).unwrap_or_default();
        }
        if self.retail {
            // `CmdTechniqueGoods::Select`: `GetRegDat(0x1f, pc, i)` of the selected row, also while the target card is up
            return self.entries.get(self.list.sel).map(|e| strip_icon_codes(&e.help)).unwrap_or_default();
        }
        String::new()
    }
    fn backdrop(&self) -> Option<usize> {
        self.retail.then_some(0)
    }
    fn shows_root_list(&self) -> bool {
        self.retail && self.mode != Mode::Target
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        // live: the White Magic page shows no button report, Crest Magic `square : Sort` (`CMDMENUS.MSD` attach 1 resource 6) on its list
        self.retail.then(|| if !self.white && self.mode == Mode::List { vec![(Button::Square, 6)] } else { Vec::new() })
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "使用".into()), (Button::Cross, "戻る".into()), (Button::L1, "キャラ切替".into())]
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
        if self.retail {
            return self.tick_retail(env, keys);
        }
        match self.mode {
            Mode::List => {
                if keys & (padbit::L1 | padbit::R1 | padbit::LEFT | padbit::RIGHT) != 0 && self.pcs.len() > 1 {
                    let d = if keys & (padbit::L1 | padbit::LEFT) != 0 { self.pcs.len() - 1 } else { 1 };
                    self.pc = (self.pc + d) % self.pcs.len();
                    env.sound(MenuSe::CursorMove);
                    self.list = ListState::new(VISIBLE, 0);
                    self.rebuild(env);
                    self.cursor_to_sel();
                } else if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::CIRCLE != 0 {
                    match self.entries.get(self.list.sel) {
                        Some(e) if e.usable && e.mp <= self.caster_mp.0 as i32 => {
                            env.sound(MenuSe::Decide);
                            self.mode = Mode::Target;
                            self.tgt = self.pc;
                            self.all = false;
                        }
                        Some(_) => env.sound(MenuSe::Buzzer),
                        None => {}
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Target => {
                let n = self.pcs.len();
                if keys & padbit::UP != 0 {
                    self.tgt = (self.tgt + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.tgt = (self.tgt + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::LEFT | padbit::RIGHT) != 0 {
                    self.all = !self.all;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    self.cast(env);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                }
            }
            Mode::Sort => self.mode = Mode::List,
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        if self.retail {
            self.draw_retail(g);
            return;
        }
        let Some(w) = self.scene.msd.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let blue = Rgba::new(0x70, 0xc0, 0xff, a);
        // character card (nested scene 1)
        if let Some(card) = &self.card {
            let pc = &self.pcs[self.pc];
            let cw = card.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((10.0, 52.0));
            let (cx, cy) = (cw.0 + dx, cw.1 + dy);
            face_card_back(g, &self.sc.cmn, &card.msd, self.face, cx, cy, a);
            let t = |k: usize| card.msd.menu_text(k).map(|t| (t.x, t.y)).unwrap_or((0.0, 0.0));
            let (x, y) = t(4);
            text_run(g, cx + x, cy + y - 2.0, &pc.name, 0, white, Some((1, 0)));
            let (x, y) = t(0);
            self.sc.font_small.draw(g, cx + x, cy + y, "LEVEL", blue);
            let (x, y) = t(5);
            self.sc.font_big.draw(g, cx + x - 20.0, cy + y - 4.0, &format!("{:>2}", pc.level), white);
            for (k, (label, cur, max)) in [("HP", pc.hp as i32, pc.hp_max as i32), ("MP", self.caster_mp.0 as i32, self.caster_mp.1 as i32), ("SP", pc.sp as i32, pc.sp_max as i32)].iter().enumerate() {
                let (x, y) = t(1 + k);
                self.sc.font_small.draw(g, cx + x, cy + y, label, blue);
                self.sc.font_small.draw(g, cx + x + 26.0, cy + y, &cfmt("%3d/%3d", &[(*cur).into(), (*max).into()]), white);
            }
        }
        // spell list
        let (lx, ly) = (w.x + dx, w.y + dy);
        general_frame(g, &self.sc.cmn, lx - 10.0, ly - 8.0, 214.0, VISIBLE as f32 * ROW_H + 14.0, a);
        if self.entries.is_empty() {
            text_run(g, lx, ly, "--", 0, Rgba::new(0x70, 0x70, 0x78, a), None);
        }
        for (slot, e) in self.entries.iter().skip(self.list.top).take(VISIBLE).enumerate() {
            let y = ly + slot as f32 * ROW_H;
            let sel = self.list.top + slot == self.list.sel;
            if sel && self.mode == Mode::List {
                row_bar(g, lx - 4.0, y, 196.0, ROW_H - 1.0, a);
            }
            let c = if !e.usable || e.mp > self.caster_mp.0 as i32 {
                Rgba::new(0x58, 0x58, 0x60, a)
            } else if sel {
                Rgba::new(0x80, 0x80, 0x30, a)
            } else {
                white
            };
            text_run(g, lx + 2.0, y + 1.0, &e.name, 0, c, Some((1, 1)));
            text_run(g, lx + 148.0, y + 1.0, &cfmt("%3d", &[e.mp.into()]), 0, c, Some((1, 1)));
        }
        draw_scroll_marks(g, lx + 90.0, ly - 2.0, ly + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        if self.mode == Mode::Target {
            if let (Some(card), Some(pc)) = (&self.tgt_card, self.pcs.get(self.tgt)) {
                let cw = (250.0 + dx, 50.0 + dy);
                general_frame(g, &self.sc.cmn, cw.0 - 8.0, cw.1 - 6.0, 238.0, 134.0, a);
                TargetCard { scene: card }.draw(g, pc, cw.0, cw.1, a);
                if self.all {
                    text_run(g, cw.0 + 100.0, cw.1 - 2.0, &card.msd.text(0).map(sj).unwrap_or_default(), 0, Rgba::new(0x80, 0x80, 0x30, a), Some((1, 1)));
                }
            }
        } else {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}

/// The Notes line without its inline icon codes (`%iNN`: the retail help of an attack technique ends in `/%i86`, drawn live as a yellow
/// down arrow; the shared Notes band has no inline icons yet).
fn strip_icon_codes(s: &str) -> String {
    let mut out = String::with_capacity(s.len());
    let mut it = s.chars().peekable();
    while let Some(c) = it.next() {
        if c == '%' && it.peek() == Some(&'i') {
            it.next();
            while it.peek().is_some_and(|d| d.is_ascii_digit()) {
                it.next();
            }
            continue;
        }
        out.push(c);
    }
    out
}

/// Dev aid for port captures (`SH2_MENU_DEV_HP=5:7,11:20` = party member id : HP): wounds members so the heal path can be exercised.
fn dev_hp_override(env: &mut Env) {
    let Ok(v) = std::env::var("SH2_MENU_DEV_HP") else { return };
    for (id, hp) in v.split(',').filter_map(|e| e.split_once(':')).filter_map(|(a, b)| Some((a.trim().parse::<usize>().ok()?, b.trim().parse::<u16>().ok()?))) {
        if let Some(mut r) = env.session.save.btl.pc(id) {
            r.hp = hp.min(r.hp_max);
            env.session.save.btl.set_pc(id, &r);
        }
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn notes_drop_inline_icon_codes() {
        assert_eq!(super::strip_icon_codes("Circular, small/1 hit/%i86"), "Circular, small/1 hit/");
        assert_eq!(super::strip_icon_codes("Restores 50% HP."), "Restores 50% HP.");
    }
}
