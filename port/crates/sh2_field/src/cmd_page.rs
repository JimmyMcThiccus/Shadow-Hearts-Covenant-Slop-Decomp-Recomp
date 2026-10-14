//! The `CmdMenu` page framework: [`Page`] trait, the shared environment ([`Env`]), the data bundles loaded from `MENU.PKB` /
//! `COMMON.PKB` ([`CmdCache`]) and the frame every page lives in ([`Frame`]: background, title log, note line, button hints).
//!
//! `CmdMenu` (JP 0x00435aa0) owns one page object per [`CmdPage`] and a few shared widgets (`CmdNote`, `CmdTitleLog`,
//! `CmdButtonReport`, `CmdCommon`); the same split is used here.

use std::collections::HashMap;
use std::sync::Arc;

use sh2_battle::actions::ActionTables;
use sh2_battle::data::BattleData;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::msd::{Msd, SpriteRec};
use sh2_menu::plugin::MenuAssets;
use sh2_menu::save::PC_COUNT;
use sh2_menu::session::{FileStorage, GameSession};

use crate::cmd::CmdPage;
use crate::cmd_ui::*;

// ----------------------------------------------------------------------------------------------------------------
// party view (`CmdParty` / `CmdPC`)
// ----------------------------------------------------------------------------------------------------------------

/// One party member as the menu shows it (`CmdPC`: name, level, current / maximum HP, MP, SP, face model).
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct PcView {
    pub id: u8,
    pub name: String,
    pub level: u8,
    pub hp: u16,
    pub hp_max: u16,
    pub mp: u16,
    pub mp_max: u16,
    pub sp: u8,
    pub sp_max: u8,
    /// `CmdPC+8`: model number used to pick the face strip (`FindAttachFile(face)`)
    pub face: u16,
}

/// The members of the current party set that really exist (`BtlSave` record present): the stand-in rows of the old overlay (an
/// empty "PC11 Lv 0") came from the default set naming a character that was never created.
pub fn party_view(session: &GameSession) -> Vec<PcView> {
    session
        .all_members()
        .into_iter()
        .filter(|&id| (id as usize) < PC_COUNT)
        .filter_map(|id| {
            let r = session.save.btl.pc(id as usize)?;
            if !r.present() || r.level == 0 {
                return None;
            }
            Some(PcView {
                id,
                name: session.pc_name(id),
                level: r.level,
                hp: r.hp,
                hp_max: r.hp_max,
                mp: r.mp,
                mp_max: r.mp_max,
                sp: r.sp,
                sp_max: r.sp_max,
                face: r.model_nums[2],
            })
        })
        .collect()
}

// ----------------------------------------------------------------------------------------------------------------
// data bundles
// ----------------------------------------------------------------------------------------------------------------

/// What `CmdMenu` keeps from `MENU/DAT/CMDMENU.MSD` (its 12 attach files, see `notes/integration/menu.md`).
pub struct CmdScenes {
    pub root: Msd,
    /// attach 8: the `CmdTop` scene (menu list, party panels, play info, face strips)
    pub top: SceneTex,
    /// attach 5: `CmdNote` (help line)
    pub note: SceneTex,
    /// attach 6: `CmdTitleLog` (page titles)
    pub title: SceneTex,
    /// attach 7: `CmdBackGround`
    pub bg: SceneTex,
    pub bg_tile: Option<TextureId>,
    /// attach 4: `CmdCommon`: page file table + cursor
    pub common: SceneTex,
    /// HP / MP / SP gauge texture (140x16)
    pub gauge: Option<TextureId>,
    /// attach 2 / 3: bitmap fonts
    pub font_small: BitmapFont,
    pub font_big: BitmapFont,
    pub font_italic: BitmapFont,
    /// MENU/MSD file of every page id (attach 4 resource table)
    pub page_files: Vec<String>,
    /// attach 11: the menu data tables (`MenuDataTable`, chunk-relative pointers): item / weapon / armor descriptions, help pages,
    /// character profiles, library entries, ring item texts ...
    pub mdt: Msd,
    /// retail attach 4: the 64 x 32 frame texture of the `CmdFence` list windows (the page scenes' fence records carry no texture)
    pub fence_tex: Option<TextureId>,
    /// retail `MENU/DAT/CMDMENUS.MSD`: page backdrops and the button report
    pub retail: Option<RetailFrame>,
    /// `COMMON/CMNMENU.DAT`
    pub cmn: CommonScene,
}

/// Which attach file of `CMDMENU.MSD` is what.  The retail file inserted a 64x32 texture at 4 and the Yes / No window at 12, so most
/// scenes moved up by one; the number fonts have wider cells (9 / 11 px instead of 8 / 10).
#[derive(Clone, Copy, Debug)]
pub struct AttachLayout {
    pub common: usize,
    pub note: usize,
    pub title: usize,
    pub bg: usize,
    pub top: usize,
    pub mdt: usize,
    pub small_cell: u16,
    pub big_cell: u16,
}

impl AttachLayout {
    pub const DEMO: AttachLayout = AttachLayout { common: 4, note: 5, title: 6, bg: 7, top: 8, mdt: 11, small_cell: 8, big_cell: 10 };
    pub const RETAIL: AttachLayout = AttachLayout { common: 5, note: 6, title: 7, bg: 8, top: 9, mdt: 13, small_cell: 9, big_cell: 11 };
    pub fn current() -> AttachLayout {
        if sh2_core::boot::is_retail() { Self::RETAIL } else { Self::DEMO }
    }
}

impl CmdScenes {
    pub fn load(assets: &MenuAssets, reg: &mut TexReg) -> Option<Self> {
        use sh2_menu::disc::FileSource;
        let disc = assets.disc.as_ref()?;
        let lay = AttachLayout::current();
        let root = Msd::parse(disc.read("MENU/DAT/CMDMENU.MSD")?).ok()?;
        let top = SceneTex::new(root.attach_scene(lay.top)?, reg);
        let note = SceneTex::new(root.attach_scene(lay.note)?, reg);
        let title = SceneTex::new(root.attach_scene(lay.title)?, reg);
        let bg_scene = root.attach_scene(lay.bg)?;
        // background pattern tiles past the 32x32 texture: repeat addressing
        let mut bg = SceneTex::new(bg_scene.clone(), &mut TexReg::headless());
        let mut bg_tile = None;
        for i in 0..bg_scene.attach_files().len() {
            if let Some(img) = bg_scene.attach_data(i).and_then(decode_blob) {
                bg.size[i] = (img.width, img.height);
                if i == 0 {
                    bg_tile = reg.add_repeat(&img);
                    bg.tex[i] = bg_tile;
                } else {
                    bg.tex[i] = reg.add(&img);
                }
            }
        }
        let common = SceneTex::new(root.attach_scene(lay.common)?, reg);
        let gauge = common.t(0);
        let tex_of = |i: usize, reg: &mut TexReg| root.attach_data(i).and_then(decode_blob).and_then(|img| reg.add(&img));
        let font_small = if sh2_core::boot::is_retail() { BitmapFont::small_retail(tex_of(2, reg)) } else { BitmapFont::small(tex_of(2, reg), lay.small_cell) };
        let font_big = BitmapFont::big(tex_of(3, reg), lay.big_cell);
        let font_italic = BitmapFont::italic(top.t(3));
        let page_files = (0..common.msd.count(sh2_menu::msd::ChunkType::Resource)).map(|i| sj(common.msd.resource_bytes(i).unwrap_or(&[]))).collect();
        let cmn = CommonScene::load(disc, reg)?;
        let mut mdt = root.attach_scene(lay.mdt)?;
        if sh2_core::boot::is_retail() {
            mdt = mdt.with_mdt_map(sh2_menu::msd::us_mdt_type);
        }
        let (fence_tex, retail) = if sh2_core::boot::is_retail() {
            let frame = disc.read("MENU/DAT/CMDMENUS.MSD").and_then(|b| Msd::parse(b).ok()).and_then(|m| RetailFrame::new(&m, reg));
            (tex_of(4, reg), frame)
        } else {
            (None, None)
        };
        Some(CmdScenes { root, top, note, title, bg, bg_tile, common, gauge, font_small, font_big, font_italic, page_files, mdt, fence_tex, retail, cmn })
    }
}

/// What the retail menu adds in `MENU/DAT/CMDMENUS.MSD` (referenced by resource 1 of `CMDMENU.MSD`).
pub struct RetailFrame {
    /// attach 0: two 256 x 224 backdrops (0 = the vertical streaks of Items / Magic / ..., 1 = a top-lit fade) drawn by sprite 0 over the
    /// whole 512 x 448 screen in place of the captured field
    pub backdrop: SceneTex,
    /// attach 1: the button report (window (364, 334): one `icon : label` line per button, the last one at +66, earlier ones 20 px higher)
    pub report: SceneTex,
}

impl RetailFrame {
    fn new(m: &Msd, reg: &mut TexReg) -> Option<Self> {
        Some(RetailFrame { backdrop: SceneTex::new(m.attach_scene(0)?, reg), report: SceneTex::new(m.attach_scene(1)?, reg) })
    }
}

/// Everything the pages load lazily and keep between menu openings.
#[derive(Default)]
pub struct CmdCache {
    pub scenes: Option<Arc<CmdScenes>>,
    /// loaded `MENU/MSD/*.MSD` page scenes by file name
    pub files: HashMap<String, Option<Arc<SceneTex>>>,
    /// `MENU/FACE/FI_nnn.TEX`
    pub faces: HashMap<u16, Option<TextureId>>,
    /// `MENU/IMG/<dir>/<XX>_nnn.TEX` item / weapon / ... pictures
    pub images: HashMap<String, Option<TextureId>>,
    /// `COMMON/JRING.BIN` textures for the retail item ring emblem (the battle's own copy lives in a battle-only resource)
    pub ring_art: Option<Arc<sh2_battle::hud_hits::HitArt>>,
    pub failed: bool,
    /// `CommandMenu(4, ChkSavePoint() >= 0)` -> `CmdMenu` flag 2: `Some(false)` = the main menu was opened off a save point, so the Save row of the Data
    /// entry is disabled (`CmdTopMenuData::CreateScene` 0x004c6950 calls the disable method on row 0 when the flag is clear); `None` = unrestricted (menus
    /// opened by scripts / the world map / the title).
    pub save_gate: Option<bool>,
}

/// Requests from a page to the host (`CmdMenu` owner callbacks and scene changes).
#[derive(Clone, Debug, PartialEq)]
pub enum HostReq {
    /// leave the field for the (re)loaded save: jump to the map in the session
    LoadedGame,
    /// a toast line ("Saved to slot 0")
    Toast(String),
    /// `FieldMapJump(map, entry)` out of the menu (`CmdMenu::MapJump` + `FieldMapJumpGY`: the Graveyard); closes the menu
    MapJump { map: String, entry: i32 },
    /// open a full field screen over the field (`CmdMenu` page 0x15: `solomon::initialize`); closes the menu
    Screen(crate::fscreen::ScreenReq),
}

/// The environment a page works in: game state, data tables, the texture registry, the audio request list.
pub struct Env<'a, 'b> {
    pub session: &'a mut GameSession,
    pub assets: &'a MenuAssets,
    pub db: Option<&'a BattleData>,
    pub tables: Option<&'a ActionTables>,
    pub reg: &'a mut TexReg<'b>,
    pub cache: &'a mut CmdCache,
    pub ses: &'a mut Vec<MenuSe>,
    pub dev: &'a mut FileStorage,
    pub req: &'a mut Vec<HostReq>,
    pub tick: u64,
}

impl Env<'_, '_> {
    /// May the Data page save (standing on a save point, or opened by a script / screen that always saves)?
    pub fn can_save(&self) -> bool {
        self.cache.save_gate.unwrap_or(true)
    }

    pub fn scenes(&mut self) -> Option<Arc<CmdScenes>> {
        if self.cache.scenes.is_none() && !self.cache.failed {
            match CmdScenes::load(self.assets, self.reg) {
                Some(s) => self.cache.scenes = Some(Arc::new(s)),
                None => {
                    log::warn!("cmd menu: cannot load MENU/DAT/CMDMENU.MSD");
                    self.cache.failed = true;
                }
            }
        }
        self.cache.scenes.clone()
    }

    /// A page scene file (`MENU/MSD/ITEM.MSD`) with its textures.
    pub fn file_scene(&mut self, path: &str) -> Option<Arc<SceneTex>> {
        if let Some(c) = self.cache.files.get(path) {
            return c.clone();
        }
        let disc = self.assets.disc.as_ref();
        let s = disc.and_then(|d| SceneTex::load(d, path, self.reg)).map(Arc::new);
        if s.is_none() {
            log::warn!("cmd menu: cannot load {path}");
        }
        self.cache.files.insert(path.to_string(), s.clone());
        s
    }

    /// Nested scene `idx` of a page file (e.g. the sort window of `ITEM.MSD`), cached.
    pub fn nested_scene(&mut self, path: &str, idx: usize) -> Option<Arc<SceneTex>> {
        let key = format!("{path}#{idx}");
        if let Some(c) = self.cache.files.get(&key) {
            return c.clone();
        }
        let parent = self.file_scene(path);
        let s = parent.and_then(|p| p.nested(idx, self.reg)).map(Arc::new);
        self.cache.files.insert(key, s.clone());
        s
    }

    /// Page file name of a page id (`CmdMenu+0x36c` table, JP `OrderFile`).
    pub fn page_scene(&mut self, page: CmdPage) -> Option<Arc<SceneTex>> {
        let sc = self.scenes()?;
        let name = sc.page_files.get(page as usize)?.clone();
        self.file_scene(&name)
    }

    /// Face strip texture of a character (`MENU/FACE/FI_nnn.TEX`).
    pub fn face(&mut self, face: u16) -> Option<TextureId> {
        if let Some(t) = self.cache.faces.get(&face) {
            return *t;
        }
        let t = self.load_tex(&format!("MENU/FACE/FI_{face:03}.TEX"));
        self.cache.faces.insert(face, t);
        t
    }

    /// An image from `MENU/IMG` by archive path.
    pub fn image(&mut self, path: &str) -> Option<TextureId> {
        if let Some(t) = self.cache.images.get(path) {
            return *t;
        }
        let t = self.load_tex(path);
        self.cache.images.insert(path.to_string(), t);
        t
    }

    /// The Judgement Ring textures (`COMMON/JRING.BIN`: 0 hit words, 1 ring face, ...), loaded once.
    pub fn ring_art(&mut self) -> Option<Arc<sh2_battle::hud_hits::HitArt>> {
        use sh2_menu::disc::FileSource;
        if self.cache.ring_art.is_none() {
            let b = self.assets.disc.as_ref()?.read("COMMON/JRING.BIN")?;
            let mut art = sh2_battle::hud_hits::HitArt { retail: sh2_core::boot::is_retail(), loaded: true, ..Default::default() };
            for (kind, sec) in sh2_battle::stage::sections(&b) {
                if kind == "tex" {
                    let img = sh2_gfx::texture::decode_jrc(sec, 0, 0).ok();
                    art.ring.push(img.and_then(|i| Some((self.reg.add(&i)?, (i.width, i.height)))));
                }
            }
            self.cache.ring_art = Some(Arc::new(art));
        }
        self.cache.ring_art.clone()
    }

    fn load_tex(&mut self, path: &str) -> Option<TextureId> {
        use sh2_menu::disc::FileSource;
        let bytes = self.assets.disc.as_ref()?.read(path)?;
        let img = sh2_menu::plugin::decode_tex_file(&bytes)?;
        self.reg.add(&img)
    }

    /// Name of record `idx` of an `SSHMES` section (18 byte Shift-JIS strings): 9 weapons, 10 armor, 11 accessories, 12 items,
    /// 15 skills, 16 crests, 17 magic.
    pub fn name(&self, sec: usize, idx: usize) -> String {
        // retail: weapon / armour / accessory names (demo sections 9 / 10 / 11) come from the US text kinds 3 / 4 / 5; the shared name table is
        // demo-shaped there (accessory 0x2b read "Demon Earrings", live and the US data say "Small Jug")
        if sh2_core::boot::is_retail() && (9..=11).contains(&sec) {
            if let Some(n) = self.db.and_then(|d| d.us()).and_then(|u| u.text((sec - 6) as u8, idx, -1)) {
                return n;
            }
        }
        self.assets.names.as_ref().map(|n| n.name(sec, idx)).unwrap_or_default()
    }

    pub fn sound(&mut self, se: MenuSe) {
        self.ses.push(se);
    }
}

/// What a page asks of the menu after a tick.
pub enum Flow {
    Stay,
    /// open another page on top (`CmdMenu::Ready(page, a, b)` + `Active`)
    Open(Box<dyn Page>),
    /// leave this page (cancel)
    Back,
    /// close the whole menu (`CmdMenu` state 6)
    Close,
}

/// One `Cmd*` scene.
pub trait Page: Send + Sync {
    fn page(&self) -> CmdPage;
    /// index of the title string in the title-log scene (`CmdTitleLog::SetTitle`)
    fn title(&self) -> usize;
    /// the calligraphic title image of the page (texture, size), drawn left of the title text
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        None
    }
    /// help line shown in the note window (`CmdNote::SetExplanation`)
    fn note(&self) -> String {
        String::new()
    }
    /// button hints: `(button, label)` pairs for the bottom bar (`CmdButtonReport`)
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into())]
    }
    /// `Menu::Run` of the page: handle the key word, advance animations
    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow;
    fn draw(&self, g: &mut dyn MenuGfx);
    /// the page shows its own party panels / background (the top page draws the frame of the party column)
    fn wants_background(&self) -> bool {
        true
    }
    /// pages that were suspended by a child page being opened over them are notified when it closes
    fn resume(&mut self, _env: &mut Env) {}
    /// retail: the `CMDMENUS.MSD` backdrop drawn instead of the dimmed field (`None` = the field stays visible)
    fn backdrop(&self) -> Option<usize> {
        None
    }
    /// retail: the root command list stays on the right (selected entry cyan) while this page is open
    fn shows_root_list(&self) -> bool {
        false
    }
    /// the root page draws its command list for [`Page::shows_root_list`] pages
    fn draw_root_list(&self, _g: &mut dyn MenuGfx) {}
    /// retail button report (`CMDMENUS.MSD` attach 1): `(button, resource index)` per line, top to bottom; `Some` replaces the hint bar
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        None
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Button {
    Circle,
    Cross,
    Triangle,
    Square,
    L1,
    R1,
    L2,
    R2,
    /// the `[L2][R2]` pair of the retail report (`: Scroll`)
    L2R2,
    /// the right stick (`R`, retail Personal page: `: Rotate L/R`)
    RStick,
    Dpad,
    Start,
}

// ----------------------------------------------------------------------------------------------------------------
// animation helpers (`MenuWindow::Open/Close` effects)
// ----------------------------------------------------------------------------------------------------------------

/// Open / close animation of a screen element: `effect` as in [`sh2_menu::window::Effect`], durations in milliseconds.
#[derive(Clone, Copy, Debug)]
pub struct Slide {
    pub effect: u8,
    pub t: f32,
    pub dur: f32,
    pub closing: bool,
    /// element size, for the off-screen start positions
    pub size: (f32, f32),
}

impl Slide {
    pub fn open(effect: u8, dur_ms: u32, size: (f32, f32)) -> Self {
        Slide { effect, t: 0.0, dur: dur_ms.max(1) as f32, closing: false, size }
    }
    pub fn done_open() -> Self {
        Slide { effect: 0, t: 1.0, dur: 1.0, closing: false, size: (0.0, 0.0) }
    }
    pub fn close(&mut self, effect: u8, dur_ms: u32) {
        self.effect = effect;
        self.dur = dur_ms.max(1) as f32;
        self.t = 0.0;
        self.closing = true;
    }
    pub fn tick(&mut self, dt_ms: f32) {
        self.t = (self.t + dt_ms).min(self.dur);
    }
    pub fn finished(&self) -> bool {
        self.t >= self.dur
    }
    pub fn hidden(&self) -> bool {
        self.closing && self.finished()
    }
    /// `(dx, dy, alpha 0..1)` to add to the element's rest position
    pub fn offset(&self, rest: (f32, f32)) -> (f32, f32, f32) {
        let p = (self.t / self.dur).clamp(0.0, 1.0);
        // opening: far -> rest, closing: rest -> far
        let k = if self.closing { p } else { 1.0 - p };
        let (w, h) = self.size;
        match self.effect {
            1 => (0.0, k * (-(h + 100.0) - rest.1), 1.0),
            2 => (0.0, k * (548.0 - rest.1), 1.0),
            3 => (k * (-(w + 100.0) - rest.0), 0.0, 1.0),
            4 => (k * (612.0 - rest.0), 0.0, 1.0),
            _ => (0.0, 0.0, 1.0 - k),
        }
    }
}

/// Alpha of a window in `0..=0x80` units from a [`Slide`].
pub fn slide_alpha(_s: &Slide, a: f32) -> u8 {
    (a * 128.0).clamp(0.0, 128.0) as u8
}

// ----------------------------------------------------------------------------------------------------------------
// the frame: background, title log, note, button report
// ----------------------------------------------------------------------------------------------------------------

/// `CmdBackGround` (attach 7 of CMDMENU): the field stays visible behind the menu (the original grabs the screen with `MenuCapture`
/// and draws it as sprite 0); on top come the vignette sprite and the scan-line tile.
pub fn draw_background(g: &mut dyn MenuGfx, sc: &CmdScenes, alpha: f32) {
    let a = |r: &SpriteRec| (r.rgba[3] as f32 * alpha) as u8;
    // dim the field a little (sprite 0 is the captured frame; the live field is behind us, so tint instead)
    fill(g, 0.0, 0.0, SCREEN_W, SCREEN_H, Rgba::new(0, 0, 0, (0x38 as f32 * alpha) as u8));
    if let Some(r) = sc.bg.msd.sprite(1) {
        let c = Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], a(&r));
        blit(g, sc.bg.t(1), r.x, r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), c);
    }
    if let Some(r) = sc.bg.msd.sprite(2) {
        let c = Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], a(&r));
        blit(g, sc.bg_tile, r.x, r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), c);
    }
}

/// Retail page backdrop `k` (`CMDMENUS.MSD` attach 0, sprite 0: 512 x 448, colour (90, 90, 90)).
pub fn draw_backdrop(g: &mut dyn MenuGfx, rf: &RetailFrame, k: usize, alpha: f32) {
    let s = &rf.backdrop;
    let Some(r) = s.msd.sprite(0) else { return };
    let a = (r.rgba[3] as f32 * alpha.clamp(0.0, 1.0)) as u8;
    blit(g, s.t(k), r.x, r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32 + 1.0, r.v1 as f32 + 1.0), Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], a));
}

/// Retail button report (`CMDMENUS.MSD` attach 1): bottom right, one line per button (icon sprite 0 at (18, 69), `: Label` text record 0
/// at (32, 66)), the last line lowest and the others stacked 20 px above it.
pub fn draw_report(g: &mut dyn MenuGfx, rf: &RetailFrame, cmn: &CommonScene, lines: &[(Button, usize)], alpha: u8) {
    let m = &rf.report.msd;
    let Some(w) = m.window(0) else { return };
    let Some(t) = m.menu_text(0) else { return };
    let icon = m.sprite(0);
    let hs = sh2_menu::gfx::TextRun::hscale_of(t.flags);
    let shadow = (t.shadow[0] != 0 || t.shadow[1] != 0).then_some((t.shadow[0], t.shadow[1]));
    let n = lines.len();
    for (k, (b, res)) in lines.iter().enumerate() {
        let dy = (n - 1 - k) as f32 * 20.0;
        let label = m.resource_bytes(*res).map(sj).unwrap_or_default();
        // a pair (`[L2][R2]`) puts the first icon 16 px left of the usual spot (sprite 1 of the record, x 2)
        let cells: Vec<((usize, usize), f32)> = match b {
            Button::L2R2 => vec![((0, 1), -16.0), ((1, 1), 0.0)],
            b => icon_cell(icon_button(*b)).map(|c| vec![(c, 0.0)]).unwrap_or_default(),
        };
        if let Some(s) = &icon {
            for (cell, ox) in cells {
                blit(g, cmn.s.t(6), w.x + s.x + ox, w.y + s.y - 5.0 - dy, s.w, s.h, ((cell.0 * 16) as f32, (cell.1 * 20) as f32, (cell.0 * 16 + 16) as f32, (cell.1 * 20 + 20) as f32), Rgba::new(0x80, 0x80, 0x80, alpha));
            }
        }
        text_run_h(g, w.x + t.x, w.y + t.y - 5.0 - dy, &label, 0, Rgba::new(0x80, 0x80, 0x80, alpha), shadow, hs);
    }
}

/// Cell of a pad icon in the 16 x 20 icon sheet of the common scene (attach 6).
fn icon_cell(b: Button) -> Option<(usize, usize)> {
    match b {
        Button::Triangle => Some((4, 1)),
        Button::Circle => Some((5, 1)),
        Button::Cross => Some((6, 1)),
        Button::Square => Some((7, 1)),
        Button::L2 => Some((0, 1)),
        Button::R2 => Some((1, 1)),
        Button::L2R2 => Some((0, 1)),
        Button::RStick => Some((2, 0)),
        Button::L1 => Some((2, 1)),
        Button::R1 => Some((3, 1)),
        Button::Start => Some((3, 0)),
        Button::Dpad => Some((4, 0)),
    }
}

/// Title log (`CmdTitleLog::SetTitle` + `Open`): the page's title image followed by the title string.
pub struct TitleLog {
    pub slide: Slide,
    pub text: String,
    pub image: Option<(TextureId, (u32, u32))>,
}

impl TitleLog {
    pub fn new(sc: &CmdScenes, index: usize, image: Option<(TextureId, (u32, u32))>) -> Self {
        // the retail title-log file still carries the demo's Japanese strings (the calligraphic title image says it all): not shown there
        let text = if sh2_core::boot::is_retail() { String::new() } else { sc.title.msd.resource_bytes(index).map(sj).unwrap_or_default() };
        let rec = sc.title.msd.window(0);
        let dur = rec.as_ref().map(|r| r.open_time).unwrap_or(120);
        let eff = rec.as_ref().map(|r| r.open_effect).unwrap_or(3);
        TitleLog { slide: Slide::open(eff, dur, (250.0, 32.0)), text, image }
    }
    pub fn draw(&self, g: &mut dyn MenuGfx, sc: &CmdScenes) {
        let Some(w) = sc.title.msd.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let (x, y) = (w.x + dx, w.y + dy);
        let mut tx = x;
        if let Some((t, (iw, ih))) = self.image {
            blit(g, Some(t), x, y, iw as f32, ih as f32, (0.0, 0.0, iw as f32, ih as f32), Rgba::new(0x80, 0x80, 0x80, a));
            tx = x + iw as f32 + 2.0;
        }
        // title text: MenuText record 0 (font 3 = the italic title font), drop shadow (0, 1)
        let r = sc.title.msd.menu_text(0);
        let ty = y + r.as_ref().map(|r| r.y).unwrap_or(10.0) - 6.0;
        text_run(g, tx, ty, &self.text, 3, Rgba::new(0x80, 0x80, 0x80, a), Some((0, 1)));
    }
}

/// Note window (`CmdNote`): label sprite and one explanation line.
pub struct Note {
    pub slide: Slide,
    pub text: String,
}

impl Note {
    pub fn new(sc: &CmdScenes) -> Self {
        let rec = sc.note.msd.window(0);
        let dur = rec.as_ref().map(|r| r.open_time).unwrap_or(120);
        Note { slide: Slide::open(0, dur, (512.0, 58.0)), text: String::new() }
    }
    pub fn draw(&self, g: &mut dyn MenuGfx, sc: &CmdScenes) {
        let Some(w) = sc.note.msd.window(0) else { return };
        let (_, _, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        if sh2_core::boot::is_retail() {
            // retail (live capture): a flat translucent black band along the bottom edge, no blue frame
            fill(g, 0.0, 418.0, SCREEN_W, SCREEN_H - 418.0, Rgba::new(0, 0, 0, (a as u32 * 0x48 / 0x80) as u8));
        } else {
            // dark band behind the help line (the original's `Note` window frame comes from the common scene)
            fill_v(g, 0.0, w.y - 2.0, SCREEN_W, 58.0, Rgba::new(0x10, 0x10, 0x20, (a as u32 * 0x70 / 0x80) as u8), Rgba::new(0x00, 0x00, 0x08, (a as u32 * 0x70 / 0x80) as u8));
            fill(g, 0.0, w.y - 2.0, SCREEN_W, 1.0, Rgba::new(0x60, 0x70, 0xa0, (a as u32 * 0x60 / 0x80) as u8));
        }
        if let Some(r) = sc.note.msd.sprite(0) {
            draw_sprite_rec(g, &r, sc.note.t(0), 0.0, w.y, a);
        }
        let m = sc.note.msd.message(0);
        let hs = m.as_ref().map(|m| sh2_menu::gfx::TextRun::hscale_of(m.common.flags)).unwrap_or(1.0);
        let (mx, my) = m.map(|m| (m.common.x, m.common.y)).unwrap_or((20.0, 26.0));
        let mut lines: Vec<String> = self.text.split('\n').map(str::to_string).collect();
        let c = Rgba::new(0x80, 0x80, 0x80, a);
        // a long one line explanation (the retail strings are English and longer) is word wrapped into the multi-line layout instead of running off the screen
        if lines.len() <= 1 {
            let avail = SCREEN_W - (w.x + mx) - 10.0;
            let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&self.text));
            if tw > avail {
                lines = wrap_words(g, &self.text, 14, SCREEN_W - 62.0 - 10.0);
            }
        }
        if lines.len() <= 1 {
            // retail: live captures put the line 6 px lower than the demo's `my - 6`
            let dy = if sh2_core::boot::is_retail() { 0.0 } else { -6.0 };
            text_run_h(g, w.x + mx, w.y + my + dy, &self.text, 0, c, Some((1, 1)), hs);
        } else {
            // multi-line explanations (`$` line breaks of the data tables): smaller type, from the right of the label
            for (i, l) in lines.iter().take(3).enumerate() {
                text_run(g, 62.0, w.y + 2.0 + i as f32 * 17.0, l, 14, c, Some((1, 1)));
            }
        }
    }
}

/// Greedy word wrap with the metrics of font `font` (`g.measure_text`), at most `max_w` pixels per line.
pub fn wrap_words(g: &dyn MenuGfx, text: &str, font: u8, max_w: f32) -> Vec<String> {
    let mut out: Vec<String> = Vec::new();
    let mut line = String::new();
    for word in text.split(' ') {
        let cand = if line.is_empty() { word.to_string() } else { format!("{line} {word}") };
        let (w, _) = g.measure_text(font, &sh2_menu::sjis::encode(&cand));
        if !line.is_empty() && w > max_w {
            out.push(std::mem::take(&mut line));
            line = word.to_string();
        } else {
            line = cand;
        }
    }
    out.push(line);
    out
}

/// English wording of the button hints for the retail build (the pages are written with the demo's labels): the strings of `BUTTON.MSD` where one
/// exists (": Confirm", ": Go Back One", ": Sort", ": Scroll", ": Info"), else the obvious translation.
pub fn hint_label(label: &str) -> String {
    if !sh2_core::boot::is_retail() {
        return label.to_string();
    }
    match label {
        "決定" => "Confirm",
        "戻る" => "Back",
        "閉じる" => "Close",
        "選択" => "Select",
        "キャラ切替" => "Change Character",
        "おすすめ" => "Auto Equip",
        "使用" => "Use",
        "並べ替え" => "Sort",
        "ページ" => "Page",
        "入れ替え" => "Swap",
        other => other,
    }
    .to_string()
}

/// The pad icon a *logical* button is shown with: the retail default swaps confirm / cancel (`SaveMenuSection::SetDefaultButton`
/// `c e d f`: the physical cross is the logical circle), so "Confirm" carries the cross icon there.
fn icon_button(b: Button) -> Button {
    let e = sh2_core::game::default_buttons();
    let phys = |k: usize| match e[k] {
        0xc => Button::Triangle,
        0xd => Button::Circle,
        0xe => Button::Cross,
        _ => Button::Square,
    };
    match b {
        Button::Triangle => phys(0),
        Button::Circle => phys(1),
        Button::Cross => phys(2),
        Button::Square => phys(3),
        o => o,
    }
}

/// Button hint bar (`CmdButtonReport`, scene `BUTTON.MSD` + the button icons of the common scene).
pub fn draw_buttons(g: &mut dyn MenuGfx, cmn: &CommonScene, buttons: &[(Button, String)], y: f32, alpha: u8) {
    let buttons: Vec<(Button, String)> = buttons.iter().map(|(b, l)| (icon_button(*b), hint_label(l))).collect();
    let buttons = &buttons[..];
    // total width, so the bar can be right aligned
    let mut total = 0.0;
    for (_, label) in buttons {
        let (w, _) = g.measure_text(14, &sh2_menu::sjis::encode(label));
        total += 18.0 + w + 12.0;
    }
    // icons of attach 7 of CMNMENU (80x20 sheet is the dpad; 7 = `SELECT L R START | pad | L2 R2 L1 R1 | tri circle cross square`)
    let mut x = (SCREEN_W - 8.0 - total).max(8.0);
    for (b, label) in buttons {
        if let (Some((cx, cy)), Some(tex)) = (icon_cell(*b), cmn.s.t(6)) {
            blit(g, Some(tex), x, y - 3.0, 16.0, 20.0, ((cx * 16) as f32, (cy * 20) as f32, (cx * 16 + 16) as f32, (cy * 20 + 20) as f32), Rgba::new(0x80, 0x80, 0x80, alpha));
            x += 18.0;
        }
        text_run(g, x, y - 1.0, label, 14, Rgba::new(0x80, 0x80, 0x80, alpha), Some((1, 1)));
        let (w, _) = g.measure_text(14, &sh2_menu::sjis::encode(label));
        x += w + 12.0;
    }
}

/// The selection cursor (`Cursor`, kind 0: the silver arrow of the common scene plus the cyan flare).
#[derive(Clone, Copy, Debug)]
pub struct CmdCursor {
    pub pos: (f32, f32),
    pub target: (f32, f32),
    pub angle: f32,
    pub visible: bool,
}

impl CmdCursor {
    pub fn new(x: f32, y: f32) -> Self {
        CmdCursor { pos: (x, y), target: (x, y), angle: 0.0, visible: true }
    }
    pub fn set_target(&mut self, x: f32, y: f32) {
        self.target = (x, y);
    }
    pub fn snap(&mut self) {
        self.pos = self.target;
    }
    /// JP `Cursor::Polling`: `pos += (target - pos) * dt * 0.01`, snap below one pixel.
    pub fn tick(&mut self, dt_ms: f32) {
        let (dx, dy) = (self.target.0 - self.pos.0, self.target.1 - self.pos.1);
        if dx.abs() < 1.0 && dy.abs() < 1.0 {
            self.pos = self.target;
        } else {
            self.pos.0 += dx * dt_ms * 0.01;
            self.pos.1 += dy * dt_ms * 0.01;
        }
        // JP `Cursor::Polling`: `angle += passTime * 0.5` (degrees, about the horizontal axis); the retail menu was measured live at about half that rate
        // (the arrow's height goes from full to a line in 0.36 s: 250 degrees per second)
        let rate = if sh2_core::boot::is_retail() { 0.25 } else { 0.5 };
        self.angle = (self.angle + dt_ms * rate) % 360.0;
    }
    /// Draw with its tip at the current position, image on the left pointing right (`Cursor` direction 8).
    pub fn draw(&self, g: &mut dyn MenuGfx, cmn: &CommonScene, alpha: u8) {
        if !self.visible {
            return;
        }
        let (x, y) = self.pos;
        if sh2_core::boot::is_retail() {
            // retail: a navy 32 x 18 arrow (attach 1 of the common scene, live capture) spinning about its horizontal axis inside the full strength cyan flare
            if let Some(t) = cmn.s.t(3) {
                blit(g, Some(t), x - 34.0, y - 20.0, 40.0, 40.0, (0.0, 0.0, 40.0, 40.0), Rgba::new(0x80, 0x80, 0x80, alpha));
            }
            let k = self.angle.to_radians().cos().abs().max(0.04);
            let (w, h) = (32.0, 18.0);
            if let Some(t) = cmn.s.t(1) {
                blit(g, Some(t), x - w, y - h * 0.5 * k, w, h * k, (0.0, 0.0, 32.0, 18.0), Rgba::new(0x80, 0x80, 0x80, alpha));
            }
            return;
        }
        // flare: additive glow behind the arrow
        if let Some(t) = cmn.s.t(3) {
            blit(g, Some(t), x - 30.0, y - 20.0, 40.0, 40.0, (0.0, 0.0, 40.0, 40.0), Rgba::new(0x60, 0x80, 0x80, (alpha as u32 * 0x50 / 0x80) as u8));
        }
        // arrow, spun about its vertical axis like the original (`rotate`)
        let k = self.angle.to_radians().cos().abs().max(0.35);
        let (w, h) = (20.0, 20.0);
        if let Some(t) = cmn.s.t(2) {
            blit(g, Some(t), x - w, y - h * 0.5 * k, w, h * k, (0.0, 0.0, 20.0, 20.0), Rgba::new(0x80, 0x80, 0x80, alpha));
        }
    }
}
