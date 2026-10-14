//! Battle result / message UI of the retail game (U2 pass, 2026-10-10): the battle message windows (`BMesWin`), the in-battle
//! `Battle Bonus / You Get!` panel (`BtlBonus`), the post-battle result screen with the EXP count-up and level-ups (`BtlResult`) and
//! the win / lose / escape sequencing of `CBattle` phases 0x15 / 0x16 / 8.
//!
//! Sources (all layout numbers are the real ones unless a doc comment says "approx"):
//! * `BtlBonus::MakePacket / WinCreate / Polling` of the retail main executable (`SLUS_210.41` 0x38f620 / 0x395230 / 0x38e800, decoded
//!   GIF packets: panel 427 x (193 + rows) centred on (256, 224), ornaments of `BTL_002` entry 3, titles entry 4, `Exp.Cash.Soul.Item.`
//!   strip + digits entry 5) -- `notes/integration/battle_ui_u2.md`.
//! * `BtlResult::WinCreate / Polling` (JP `decomp/H/BtlResult.c`, 0x15174 bytes; the retail copy is the same size and uses the same
//!   `BTL_002` art): full-screen magic-circle backdrop (entry 2), the `You Get!` totals window at the right, one 360 x 45 window per party
//!   member at `y = 42 + 44 k` with the wide portrait (entry 12 + pc id), `LEVEL / HP / MP / SP / NEXT` (entry 7), gauges (entry 9), the
//!   party cash with the `Cash` logo (entries 10 / 11), the flipping `Level Up!` title (entry 4, `cos` of a decaying 2 pi angle).
//! * `BMesWin::Create / Polling` (`decomp/H/BMesWin.c`): message kinds 0 centre, 1 top centre, 2 / 3 top right (3 = min 128 wide, centred
//!   text), 4 at (288, 312.8); 20 px rows; open / close 0x85 ms; close rules 1 any face button, 2 after 2 s, 3 either.  The retail
//!   `CBattle::SetBtlMessage` (`SH2US_BATTLE.BIN` 0x672080) maps its ids to `GetRegDat(0x2b, id)` strings and these kinds.
//! * Phase timings: `Retail_CBattle_Phase15_Win / Phase16_Lose` (`decomp/I/us_battle_phases.c`).
//!
//! Approximations (no live capture yet): the message window frame (`MenuWindowCompact`, CMNMENU attach 14) is a hand-drawn capsule;
//! the win pose length (3 s) stands in for the motion end; the result-window open / close effect is an alpha ramp.

use bevy::prelude::*;
use sh2_menu::gfx::{Blend, MenuGfx, Rgba};

use crate::hud::{grad, spr2, text, tex2, white, BtlHud};

/// `BTL_002` entries used here (retail numbering; see `hud::tex2` for the ones the HUD already uses).
pub mod art {
    /// 512 x 448 magic-circle backdrop of the result screen
    pub const BACKDROP: usize = 2;
    /// 96 x 112 black flourish: lines (1,70 38x7), verticals (0,78 14x24), swirl (0,0 88x29), corners (0,29 48x27) (0,56 26x14) (48,29 42x63)
    pub const ORNAMENT: usize = 3;
    /// `LEVEL HP MP SP NEXT -` (y 0..12) + small digits `/0123456789.,:` (y 12..27, 10 px cells)
    pub const STATS: usize = 7;
    /// 12 x 22 digits (level)
    pub const DIGITS12: usize = 8;
    /// gauges: tracks at y 8 (HP 1..61, MP 62..122, SP 123..146), fills at y 1
    pub const GAUGES: usize = 9;
    /// `Cash` logo 44 x 25
    pub const CASH: usize = 10;
    /// outlined digits 18 x 21 (party cash), comma at x 180
    pub const DIGITS18: usize = 11;
    /// wide portraits 96 x 36, entry `FACES + pc id`
    pub const FACES: usize = 12;
    /// 256 x 224 black overlay with the purple streaks (alpha map: dark at the edges), drawn 2x over the backdrop (`WinCreate` window 0)
    pub const STREAKS: usize = 6;
    /// 128 x 8 bar
    pub const BAR: usize = 31;
    /// 34 x 34 cursor arrow
    pub const CURSOR: usize = 32;
    /// button icons 144 x 40: circle, triangle, square, cross, L1, R1, L2, R2 (18 px cells) / start, R, L
    pub const BUTTONS: usize = 33;
    /// the `Battle Bonus / You Get! / Level Up!` titles recoloured to the purple script of the live game (`BTL_002` entry 4 has a
    /// single gold CLUT; the retail packet draws it purple -- the CLUT swap was not found, so [`load_art`] builds the purple copy
    /// from the gold one by luminance, matched to the capture colour (160,102,233)).  Stored in `BtlHud::tex2` under this key.
    pub const TITLES_PURPLE: usize = 1004;
    /// the item-kind icon sheet (`COMMON/CMNMENU.DAT` attach 5, 16 x 20 cells, 8 per row; `MenuIcon::Create(0x20 + n)` = cell `n`), stored in
    /// `BtlHud::tex2` under this key by [`load_art`]
    pub const ICONS: usize = 1005;
}

/// `Retail_GetItemKindTable(id, 0)` (SLUS 0x386130) minus 0x20: the cell of the item-kind icon of an item id (`BtlBonus::WinCreate` prints
/// `%i<kind>` before the name).  The weapon range (100..199) takes its kind from a table row (bit -> 0x20 + bit) that the port does not read here:
/// `None`.
pub fn item_icon_cell(id: i32) -> Option<usize> {
    Some(match id {
        i32::MIN..=-1 => return None,
        0..=99 => 12,
        100..=199 => return None,
        200..=299 => 15,
        300..=399 => 16,
        400..=499 => 21,
        500..=599 => 14,
        600..=699 => 18,
        700..=799 => 20,
        800..=899 => 19,
        0x41f..=0x428 => 17,
        0x430..=0x439 => 22,
        _ => 13,
    })
}

/// Build the purple title sheet once the HUD art is loaded (see [`art::TITLES_PURPLE`]).
pub fn load_art(mut hud: ResMut<BtlHud>, disc: Option<Res<sh2_gfx::bevy::Sh2Disc>>, mut textures: ResMut<sh2_menu::bevy_ui::UiTextures>, mut images: ResMut<Assets<Image>>) {
    let Some(disc) = disc else { return };
    if !hud.loaded || hud.tex2.contains_key(&art::TITLES_PURPLE) || !hud.tex2.contains_key(&tex2::TITLES) {
        return;
    }
    // the item-kind icon sheet of the common menu scene
    if let Ok(cmn) = disc.read("COMMON/CMNMENU.DAT") {
        if let Some(i) = sh2_menu::msd::Msd::parse(cmn).ok().and_then(|m| m.attach_data(5).and_then(|b| sh2_gfx::texture::decode_menu_texture(b, 0).ok())).filter(|i| i.width > 0 && i.width <= 1024 && i.height > 0 && i.height <= 1024) {
            let id = textures.add(&mut images, i.width, i.height, i.pixels);
            hud.tex2.insert(art::ICONS, (id, (i.width, i.height)));
        }
    }
    let Ok(b) = disc.read("BTLDATA/BTL_002.BIN") else { return };
    let Some((_, sec)) = crate::stage::sections(&b).into_iter().nth(tex2::TITLES) else { return };
    let Ok(mut img) = sh2_gfx::texture::decode_jrc(sec, 0, 0) else { return };
    recolour_purple(&mut img.pixels);
    let id = textures.add(&mut images, img.width, img.height, img.pixels);
    hud.tex2.insert(art::TITLES_PURPLE, (id, (img.width, img.height)));
}

/// Gold -> purple script: dark outline pixels stay, the gold body becomes (160,102,233), highlights a pale lavender.
pub fn recolour_purple(px: &mut [u8]) {
    for p in px.chunks_exact_mut(4) {
        if p[3] == 0 {
            continue;
        }
        let l = (p[0] as u32 * 299 + p[1] as u32 * 587 + p[2] as u32 * 114) / 1000;
        let (r, g, b) = if l < 70 {
            (p[0] / 2, p[1] / 2, (p[2] / 2).max(20))
        } else if l < 170 {
            (120, 60, 200)
        } else if l < 215 {
            (160, 102, 233)
        } else {
            (215, 190, 255)
        };
        p[0] = r;
        p[1] = g;
        p[2] = b;
    }
}


/// Retail `GetRegDat(0x2b, n)` message ids used by the sequences (`BtlText::word`), with the English text of the US disc as the
/// fallback for the demo disc.
pub mod msg {
    pub const CONFIRM: usize = 103;
    pub const END: usize = 104;
    pub const SKIP: usize = 105;
    pub const AMBUSH_PC: usize = 106;
    pub const AMBUSH_ENEMY: usize = 107;
    pub const COMBO_CHANCE: usize = 108;
    pub const RAN_AWAY_ONE: usize = 116;
    pub const RAN_AWAY: usize = 117;
    pub const CANT_GET_AWAY: usize = 118;
    pub const NO_ESCAPE: usize = 119;
    pub const NONE: &str = "None";

    pub fn fallback(id: usize) -> &'static str {
        match id {
            CONFIRM => "%i17:Confirm",
            END => "%i17:End",
            SKIP => "%i17:Skip",
            AMBUSH_PC => "You surrounded the enemy! Chance for a first-strike!",
            AMBUSH_ENEMY => "The enemy has surrounded you!",
            COMBO_CHANCE => "Your chance for a %s-person Combo!",
            RAN_AWAY_ONE => "%s ran away!",
            RAN_AWAY => "%s and the others ran away!",
            CANT_GET_AWAY => "Couldn't get away!",
            NO_ESCAPE => "You can't run away from this battle!",
            _ => "",
        }
    }
}

/// Message text `id` of the retail table, `%s` replaced by `arg`; the `%i17` button-icon escape and the full-width colon that follow it
/// in the prompts (`Skip` / `End` / `Confirm`) are stripped (the icon is drawn by [`MesWin`] instead).
pub fn message(text: &crate::ui::BtlText, id: usize, arg: &str) -> String {
    let raw = text.word(id);
    let raw = if raw.is_empty() { msg::fallback(id) } else { raw };
    let mut s = raw.replacen("%s", arg, 1);
    if let Some(rest) = s.strip_prefix("%i17") {
        // the full-width colon after the icon escape is drawn as `:` (live 03a: `[x]:Skip`)
        s = format!(":{}", rest.trim_start_matches(['\u{81}', 'F', '：', ':']));
    }
    s
}

/// Pixel width of `s` in the battle font (`FontItem` spacing -1 like [`crate::hud::text`]).
fn text_w(g: &dyn MenuGfx, s: &str) -> f32 {
    let n = s.chars().count() as f32;
    (g.measure_text(0, &sh2_menu::sjis::encode(s)).0 - (n - 1.0).max(0.0)).max(0.0)
}

fn digit_of(v: i64, pow: u32) -> Option<usize> {
    let p = 10i64.pow(pow);
    if pow > 0 && v < p {
        None
    } else {
        Some(((v / p) % 10) as usize)
    }
}

// ------------------------------------------------------------------------------------------------------------------
// battle message windows (BMesWin)
// ------------------------------------------------------------------------------------------------------------------

/// `BMesWin::Create` placement kinds (`BtlMenu::MakeMesWin` last argument).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MesKind {
    /// centred on (256, 224): ambush, run-away, status messages
    Center = 0,
    /// top centre (y 16)
    TopCenter = 1,
    /// top right (x = 512 - (w + 20.8), y 16): combo chance
    TopRight = 2,
    /// top right, at least 128 wide, text centred: the action name (`SetBtlMessage(0x146, name)`)
    TopRightWide = 3,
    /// the `Skip` / `End` prompts: bottom right, `x = 512 - (w + 12.8)`, y 392 (live capture 03a/03d; the JP build had (288, 312.8))
    Prompt = 4,
    /// retail kind 8: the ornate result window at the bottom (`SetBtlMessage(0xde)` = the Tarot card effect text from `GetRegDat(0x2c,
    /// 0xde + card)`, `0xa6` raw strings): dark panel x 48..465, y 320..398 with the entry-3 corner pieces, text at (66, 343), the
    /// confirm icon bottom right (live 10k); close rule 1 (any face button).  Snap Shot posts nothing (live 11k).
    Ornate = 8,
}

/// `BMesWin` close rule (`MakeMesWin` first argument).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MesClose {
    /// stays until the owner closes it (`SetMesWinClose`)
    Owner = 0,
    /// any face button
    Button = 1,
    /// 2 s after the window has opened
    Timed = 2,
    /// 2 s or any face button
    TimedOrButton = 3,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum MesState {
    Opening,
    Open,
    Closing,
    Done,
}

/// One message window.  `alpha` follows the 0x85 ms open / close transition of `MenuWindow::Open(0, 0x85)`.
#[derive(Clone, Debug)]
pub struct MesWin {
    pub id: u32,
    pub kind: MesKind,
    pub close: MesClose,
    pub rows: Vec<String>,
    /// draw a button icon in front of the first row (the `%i17` escape of the prompts)
    pub icon: bool,
    state: MesState,
    alpha: f32,
    /// seconds since the window finished opening
    shown: f32,
}

/// Open / close transition of a message window (`Open(0, 0x85)`: 133 ms).
pub const MES_FADE: f32 = 0.133;
/// `BMesWin::Polling` auto-close delay for close rules 2 / 3.
pub const MES_HOLD: f32 = 2.0;
/// row pitch of a message window
pub const MES_ROW: f32 = 20.0;

impl MesWin {
    /// Position and inner size `(x, y, w, h)` of the window (`BMesWin::Create` switch on the kind).
    pub fn rect(&self, g: &dyn MenuGfx) -> (f32, f32, f32, f32) {
        let mut w = self.rows.iter().map(|r| text_w(g, r)).fold(0.0f32, f32::max);
        if self.icon {
            w += 20.0;
        }
        if self.kind == MesKind::Center {
            // the centred windows carry the confirm icon after the text (live 05a)
            w += 20.0;
        }
        let h = (self.rows.len().max(1) as f32 * MES_ROW).max(if self.rows.len() >= 2 && self.kind == MesKind::Center { 60.0 } else { 0.0 });
        match self.kind {
            MesKind::Center => (256.0 - w / 2.0, 224.0 - h / 2.0, w, h),
            MesKind::TopCenter => (256.0 - w / 2.0, 16.0, w, h),
            MesKind::TopRight => (512.0 - (w + 12.8 + 8.0), 16.0, w, h),
            MesKind::TopRightWide => {
                let w = w.max(128.0);
                (512.0 - (w + 12.8 + 8.0), 16.0, w, h)
            }
            MesKind::Prompt => (512.0 - (w + 12.8), 392.0, w, h),
            MesKind::Ornate => (66.0, 343.0, 380.0, h),
        }
    }

    pub fn is_done(&self) -> bool {
        self.state == MesState::Done
    }

    /// Start the close transition (`BMesWin::SetClose`).
    pub fn set_close(&mut self) {
        if !matches!(self.state, MesState::Closing | MesState::Done) {
            self.state = MesState::Closing;
        }
    }

    /// `BMesWin::Polling`: `face_press` = a face button went down this tick.
    pub fn tick(&mut self, dt: f32, face_press: bool) {
        match self.state {
            MesState::Opening => {
                self.alpha = (self.alpha + dt / MES_FADE).min(1.0);
                if self.alpha >= 1.0 {
                    self.state = MesState::Open;
                    self.shown = 0.0;
                }
            }
            MesState::Open => {
                self.shown += dt;
                let timed = matches!(self.close, MesClose::Timed | MesClose::TimedOrButton) && self.shown >= MES_HOLD;
                let button = matches!(self.close, MesClose::Button | MesClose::TimedOrButton) && face_press;
                if timed || button {
                    self.set_close();
                }
            }
            MesState::Closing => {
                self.alpha = (self.alpha - dt / MES_FADE).max(0.0);
                if self.alpha <= 0.0 {
                    self.state = MesState::Done;
                }
            }
            MesState::Done => {}
        }
    }

    /// Draw the window.  Live captures 05a / 05c: a near-opaque black capsule (fill ~0.9) 14 px wider than the text on each side,
    /// 27 px tall around the 20 px row, with a 2 px grey-blue rim and pointed ends (`MenuWindowCompact`, CMNMENU attach 14 --
    /// the rim pieces are approximated with quads).  Kind 3 centres every row; the prompts carry the confirm icon in front, the
    /// centred messages after the text.
    pub fn draw(&self, g: &mut dyn MenuGfx, hud: &BtlHud, retail: bool) {
        if self.alpha <= 0.0 {
            return;
        }
        let a = (self.alpha * 128.0) as u8;
        let (x, y, w, h) = self.rect(g);
        let cell = if retail { 3.0 } else { 0.0 };
        // one 18 px cell of the button sheet, trimmed to the round icon (live: ~14 px)
        let icon = |g: &mut dyn MenuGfx, ix: f32, iy: f32| spr2(g, hud, art::BUTTONS, (cell * 18.0 + 2.0, 1.0, 14.0, 18.0), (ix + 1.0, iy + 1.0, 14.0, 18.0), Rgba::new(0x80, 0x80, 0x80, a));
        let col = Rgba::new(0x80, 0x80, 0x80, a);
        if self.kind == MesKind::Ornate {
            // dark panel with the corner flourishes of `BTL_002` entry 3 (approx: the retail frame art was not decoded)
            let (px, py, pw, ph) = (48.0, 320.0, 418.0, h + 56.0);
            let fill = Rgba::new(0x22, 0x1e, 0x26, (a as u32 * 0x70 / 0x80) as u8);
            let rail = Rgba::new(0x58, 0x58, 0x66, (a as u32 * 0x70 / 0x80) as u8);
            grad(g, px, py, pw, ph, fill, fill, fill, fill);
            grad(g, px, py, pw, 2.0, rail, rail, rail, rail);
            grad(g, px, py + ph - 2.0, pw, 2.0, rail, rail, rail, rail);
            grad(g, px, py, 2.0, ph, rail, rail, rail, rail);
            grad(g, px + pw - 2.0, py, 2.0, ph, rail, rail, rail, rail);
            let orn = |g: &mut dyn MenuGfx, src: (f32, f32, f32, f32), dst: (f32, f32, f32, f32)| spr2(g, hud, art::ORNAMENT, src, dst, Rgba::new(0x80, 0x80, 0x80, a));
            orn(g, (0.0, 56.0, 26.0, 14.0), (px - 6.0, py - 4.0, 26.0, 14.0));
            orn(g, (26.0, 56.0, -26.0, 14.0), (px + pw - 20.0, py - 4.0, 26.0, 14.0));
            orn(g, (0.0, 56.0, 26.0, 14.0), (px - 6.0, py + ph - 10.0, 26.0, 14.0));
            orn(g, (26.0, 56.0, -26.0, 14.0), (px + pw - 20.0, py + ph - 10.0, 26.0, 14.0));
            for (i, r) in self.rows.iter().enumerate() {
                text(g, x, y + i as f32 * MES_ROW, r, col);
            }
            icon(g, px + pw - 26.0, py + ph - 24.0);
            return;
        }
        if self.kind == MesKind::Prompt {
            // no frame: `[x]:Skip` straight on the scene
            let mut tx = x;
            if self.icon {
                icon(g, tx - 2.0, y - 2.0);
                tx += 20.0;
            }
            if let Some(r) = self.rows.first() {
                text(g, tx, y, r, col);
            }
            return;
        }
        // live 05c: frame 348..507 / 13..40 around the 128 px row at 363 / 16 -> 15 px beyond the row on each side incl. the
        // pointed ends, 3 px above / below
        let (px, py, pw, ph) = (x - 8.0, y - 3.0, w + 16.0, h + 6.0);
        let fill = Rgba::new(0, 0, 0, (a as u32 * 0x74 / 0x80) as u8);
        let rim = Rgba::new(0x52, 0x52, 0x60, (a as u32 * 0x6c / 0x80) as u8);
        let rim2 = Rgba::new(0x30, 0x30, 0x3a, (a as u32 * 0x6c / 0x80) as u8);
        grad(g, px, py, pw, ph, fill, fill, fill, fill);
        // rim: top / bottom rails and the pointed ends
        grad(g, px, py, pw, 2.0, rim, rim, rim, rim);
        grad(g, px, py + ph - 2.0, pw, 2.0, rim, rim, rim, rim);
        let v = |q: (f32, f32), c: Rgba| sh2_menu::gfx::Vertex { pos: glam_vec(q.0, q.1), uv: glam_vec(0.0, 0.0), color: c };
        let cy = py + ph / 2.0;
        for (sx, dir) in [(px, -1.0f32), (px + pw, 1.0)] {
            g.draw(sh2_menu::gfx::DrawCmd::Quad { tex: None, v: [v((sx, py), rim), v((sx, py + ph), rim), v((sx + dir * 7.0, cy), rim), v((sx + dir * 7.0, cy), rim)], blend: Blend::Alpha });
            g.draw(sh2_menu::gfx::DrawCmd::Quad { tex: None, v: [v((sx, py + 2.0), rim2), v((sx, py + ph - 2.0), rim2), v((sx + dir * 4.0, cy), rim2), v((sx + dir * 4.0, cy), rim2)], blend: Blend::Alpha });
            g.draw(sh2_menu::gfx::DrawCmd::Quad { tex: None, v: [v((sx, py + 3.0), fill), v((sx, py + ph - 3.0), fill), v((sx + dir * 2.0, cy), fill), v((sx + dir * 2.0, cy), fill)], blend: Blend::Alpha });
        }
        for (i, r) in self.rows.iter().enumerate() {
            let tw = text_w(g, r);
            let mut tx = if self.kind == MesKind::TopRightWide { x + (w - tw) / 2.0 } else { x };
            let ty = y + i as f32 * MES_ROW;
            if self.icon && i == 0 {
                icon(g, tx, ty);
                tx += 20.0;
            }
            text(g, tx, ty, r, col);
            if self.kind == MesKind::Center && i == self.rows.len() - 1 {
                icon(g, tx + tw + 4.0, ty);
            }
        }
    }
}

/// The message windows of the battle (`BtlMenu`'s `BMesWin` list).  Handles are `BtlMenu::MakeMesWin` ids.
#[derive(Default, Debug)]
pub struct MesQueue {
    pub wins: Vec<MesWin>,
    next_id: u32,
}

impl MesQueue {
    /// `BtlMenu::MakeMesWin(close, rows, text, kind)`; `text` holds one row per line.
    pub fn post(&mut self, kind: MesKind, close: MesClose, text: &str) -> u32 {
        self.post_icon(kind, close, text, false)
    }

    pub fn post_icon(&mut self, kind: MesKind, close: MesClose, text: &str, icon: bool) -> u32 {
        let id = self.next_id;
        self.next_id += 1;
        let rows: Vec<String> = text.lines().map(|l| l.to_string()).filter(|l| !l.is_empty()).collect();
        self.wins.push(MesWin { id, kind, close, rows, icon, state: MesState::Opening, alpha: 0.0, shown: 0.0 });
        id
    }

    /// `BtlMenu::SetMesWinClose(id)`.
    pub fn close(&mut self, id: u32) {
        if let Some(w) = self.wins.iter_mut().find(|w| w.id == id) {
            w.set_close();
        }
    }

    /// Close every owner-managed window (end of an action / of the battle).
    pub fn close_owned(&mut self) {
        for w in self.wins.iter_mut().filter(|w| w.close == MesClose::Owner) {
            w.set_close();
        }
    }

    pub fn close_all(&mut self) {
        for w in self.wins.iter_mut() {
            w.set_close();
        }
    }

    /// `BtlMenu::FindMesWin(id)`: still alive?
    pub fn alive(&self, id: u32) -> bool {
        self.wins.iter().any(|w| w.id == id && !w.is_done())
    }

    pub fn is_empty(&self) -> bool {
        self.wins.is_empty()
    }

    pub fn tick(&mut self, dt: f32, face_press: bool) {
        for w in self.wins.iter_mut() {
            w.tick(dt, face_press);
        }
        self.wins.retain(|w| !w.is_done());
    }

    pub fn draw(&self, g: &mut dyn MenuGfx, hud: &BtlHud, retail: bool) {
        for w in &self.wins {
            w.draw(g, hud, retail);
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// Battle Bonus / You Get! panel (BtlBonus)
// ------------------------------------------------------------------------------------------------------------------

/// One row of the `Battle Bonus` section (retail `BtlBonus` ctor: `Max Hit Number: %s Hits`, `No-Damage Victory`, ... with the bonus
/// `Exp.+n` / item in the value column).  Normal fights have none (Pit Fight conditions).
#[derive(Clone, Debug, Default, PartialEq)]
pub struct BonusRow {
    pub name: String,
    pub value: String,
}

/// What the panel shows (`BtlSocket+0x290..` totals, `+0x1a2` items, `+0x556` bonus rows).
#[derive(Clone, Debug, Default)]
pub struct BonusData {
    pub exp: i64,
    pub cash: i64,
    pub soul: i64,
    /// `BtlSaveDat+3 & 4`: the Soul counter is unlocked (otherwise the `Exp.` / `Cash.` columns move 64 px right)
    pub show_soul: bool,
    /// `(name, count)`
    pub items: Vec<(String, u8)>,
    /// item ids parallel to `items` (the kind icon before the name); may be shorter
    pub item_ids: Vec<i32>,
    pub rows: Vec<BonusRow>,
    /// outcome bits != 0 (escape / lose): the magic-circle backdrop is drawn behind the panel and the `End` prompt at the bottom right
    pub escaped: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BonusPhase {
    /// alpha 0 -> 1 at 2 / s
    FadeIn,
    /// one bonus row every 0.25 s (SE 0x3002); a single 0.25 s step when there is none
    Rows,
    /// 10 s or the confirm button
    Hold,
    /// alpha 1 -> 0 at 2 / s while `BtlFader::SetMode(1.0, 3, 0)` darkens the screen
    FadeOut,
    Done,
}

/// `BtlBonus`: the panel drawn over the win pose (`CBattle` phase 0x15, `nCmd0 == 1`) and after a successful escape (phase 8 step 0x23).
#[derive(Clone, Debug)]
pub struct BonusPanel {
    /// the skip flag of `BtlBonus` (`+0x38` bit 2, set by the confirm button): every phase passes at once -- set when the win pose was skipped (retail
    /// `Phase15_Win` step 5 sets it on the freshly built panel when the button ended the pose)
    pub skip: bool,
    pub data: BonusData,
    pub phase: BonusPhase,
    pub alpha: f32,
    t: f32,
    pub shown_rows: usize,
    /// SYSREG sound ids requested this tick (0x3002 per revealed row)
    pub ses: Vec<u16>,
    /// `BtlFader::SetMode(1.0, 3, 0)` was issued: the host fades the screen to black
    pub fade_screen: bool,
}

/// panel centre
pub const BONUS_CX: f32 = 256.0;
pub const BONUS_CY: f32 = 224.0;
/// panel x range (retail: GS 0x72b0 .. 0x8d60 at 12.4 bits, offset 1792)
pub const BONUS_LEFT: f32 = 43.0;
pub const BONUS_RIGHT: f32 = 470.0;
pub const BONUS_ROW_PITCH: f32 = 24.0;
/// `BtlBonus::Polling` phase 3 holds the panel `10.0 <= timer` seconds (retail; the JP demo's 4 s was wrong -- live capture: the panel stays up ~10 s)
pub const BONUS_HOLD: f32 = 10.0;

impl BonusPanel {
    pub fn new(data: BonusData) -> Self {
        BonusPanel { skip: false, data, phase: BonusPhase::FadeIn, alpha: 0.0, t: 0.0, shown_rows: 0, ses: Vec::new(), fade_screen: false }
    }

    /// Height of the bonus-row section (`n * 24 + 37`), 0 without rows.
    pub fn rows_height(&self) -> f32 {
        let n = self.data.rows.len() as f32;
        if n > 0.0 {
            n * BONUS_ROW_PITCH + 37.0
        } else {
            0.0
        }
    }

    /// `(top, bottom)` of the panel: `top = 224 - ((h + 194) >> 1)`, `bottom = top + 1 + (h + 193)`.
    pub fn vertical(&self) -> (f32, f32) {
        let h = self.rows_height() as i32;
        let top = 224 - ((h + 194) >> 1);
        (top as f32, (top + 1 + h + 193) as f32)
    }

    /// y of the `You Get!` title: `top + h + 16`.
    pub fn you_get_y(&self) -> f32 {
        self.vertical().0 + self.rows_height() + 16.0
    }

    pub fn is_done(&self) -> bool {
        self.phase == BonusPhase::Done
    }

    /// `BtlBonus::Polling`; `press` = confirm went down this tick.
    pub fn tick(&mut self, dt: f32, press: bool) {
        self.ses.clear();
        let press = press || self.skip;
        match self.phase {
            BonusPhase::FadeIn => {
                self.alpha = (self.alpha + dt * 2.0).min(1.0);
                if self.alpha >= 1.0 || press {
                    self.alpha = 1.0;
                    self.phase = BonusPhase::Rows;
                    self.t = 0.25;
                }
            }
            BonusPhase::Rows => {
                if self.t > 0.0 && !press {
                    self.t -= dt;
                    if self.t > 0.0 {
                        return;
                    }
                }
                self.t = 0.0;
                if self.shown_rows < self.data.rows.len() {
                    self.shown_rows += 1;
                    self.t = 0.25;
                    if !press {
                        self.ses.push(0x3002);
                    }
                } else if self.shown_rows == 0 && self.data.rows.is_empty() && self.t == 0.0 && !self.hold_started() {
                    // the empty list still spends one 0.25 s step
                    self.t = 0.25;
                    self.shown_rows = usize::MAX;
                } else {
                    self.phase = BonusPhase::Hold;
                    self.t = 0.0;
                }
            }
            BonusPhase::Hold => {
                self.t += dt;
                if self.t >= BONUS_HOLD || press {
                    self.phase = BonusPhase::FadeOut;
                    self.fade_screen = true;
                }
            }
            BonusPhase::FadeOut => {
                self.alpha = (self.alpha - dt * 2.0).max(0.0);
                if self.alpha <= 0.0 {
                    self.phase = BonusPhase::Done;
                }
            }
            BonusPhase::Done => {}
        }
    }

    fn hold_started(&self) -> bool {
        self.shown_rows == usize::MAX
    }

    /// `BtlBonus::MakePacket` + `WinCreate`.
    pub fn draw(&self, g: &mut dyn MenuGfx, hud: &BtlHud, text_tbl: &crate::ui::BtlText, retail: bool) {
        if self.alpha <= 0.0 {
            return;
        }
        let a = (self.alpha * 128.0) as u8;
        let af = |k: f32| Rgba::new(0x80, 0x80, 0x80, (self.alpha * 128.0 * k) as u8);
        let (top, bottom) = self.vertical();
        let hh = bottom - top; // 1 + (h + 193)
        let yg = self.you_get_y();
        if self.data.escaped {
            spr2(g, hud, art::BACKDROP, (0.0, 0.0, 512.0, 448.0), (0.0, 0.0, 512.0, 448.0), af(1.0));
        }
        // panel: vertex-coloured quad (0x41,0x41,0x4e) -> (0x0a,0x08,0x0a), alpha 0.6
        let pa = (self.alpha * 76.8) as u8;
        // (flat GS colours are used as they are: 0x80 = 1.0 here, so halve)
        grad(g, BONUS_LEFT, top, BONUS_RIGHT - BONUS_LEFT, hh, Rgba::new(0x20, 0x20, 0x27, pa), Rgba::new(0x05, 0x04, 0x05, pa), Rgba::new(0x20, 0x20, 0x27, pa), Rgba::new(0x05, 0x04, 0x05, pa));
        // ornaments (entry 3)
        let orn = |g: &mut dyn MenuGfx, src: (f32, f32, f32, f32), dst: (f32, f32, f32, f32)| spr2(g, hud, art::ORNAMENT, src, dst, af(1.0));
        let line = (1.0, 70.0, 38.0, 7.0);
        orn(g, line, (70.0, top - 5.0, 101.0, 7.0));
        orn(g, line, (343.0, top - 5.0, 101.0, 7.0));
        orn(g, line, (71.0, bottom - 3.0, 372.0, 7.0));
        // live 03d: the rails run from just under the top line to 24 px above the bottom line
        orn(g, (0.0, 78.0, 14.0, 24.0), (31.0, top + 4.0, 14.0, hh - 28.0));
        orn(g, (14.0, 78.0, -14.0, 24.0), (467.0, top + 4.0, 14.0, hh - 28.0));
        orn(g, (0.0, 0.0, 88.0, 29.0), (169.0, top - 17.0, 88.0, 29.0));
        orn(g, (88.0, 0.0, -88.0, 29.0), (255.0, top - 17.0, 88.0, 29.0));
        orn(g, (0.0, 29.0, 48.0, 27.0), (22.0, top - 12.0, 48.0, 27.0));
        orn(g, (0.0, 56.0, 26.0, 14.0), (22.0, top + 13.0, 26.0, 14.0));
        orn(g, (48.0, 29.0, -48.0, 27.0), (442.0, top - 12.0, 48.0, 27.0));
        orn(g, (26.0, 56.0, -26.0, 14.0), (464.0, top + 13.0, 26.0, 14.0));
        orn(g, (48.0, 29.0, 42.0, 63.0), (29.0, bottom - 52.0, 42.0, 63.0));
        orn(g, (90.0, 29.0, -42.0, 63.0), (441.0, bottom - 52.0, 42.0, 63.0));
        // titles (entry 4)
        let titles = if hud.tex2.contains_key(&art::TITLES_PURPLE) { art::TITLES_PURPLE } else { tex2::TITLES };
        if !self.data.rows.is_empty() {
            spr2(g, hud, titles, (0.0, 0.0, 142.0, 23.0), (185.0, top + 16.0, 142.0, 23.0), af(1.0));
        }
        spr2(g, hud, titles, (0.0, 24.0, 93.0, 23.0), (209.0, yg, 93.0, 23.0), af(1.0));
        // separator lines: light purple (0x82,0x7d,0x96) bright in the middle, transparent at both ends
        let sep = |g: &mut dyn MenuGfx, y: f32, h: f32| {
            let c = Rgba::new(0x41, 0x3e, 0x4b, a);
            let z = Rgba::new(0x41, 0x3e, 0x4b, 0);
            grad(g, 71.0, y, 68.0, h, z, z, c, c);
            grad(g, 139.0, y, 234.0, h, c, c, c, c);
            grad(g, 373.0, y, 68.0, h, c, c, z, z);
        };
        let shown = if self.shown_rows == usize::MAX { 0 } else { self.shown_rows };
        for (i, row) in self.data.rows.iter().enumerate().take(shown) {
            let yr = top + 44.0 + i as f32 * BONUS_ROW_PITCH;
            sep(g, yr, if i == 0 { 4.0 } else { 2.0 });
            let ty = top + 49.0 + i as f32 * BONUS_ROW_PITCH;
            text(g, 71.0, ty, &row.name, white(a));
            let vw = text_w(g, &row.value);
            text(g, 441.0 - vw, ty, &row.value, white(a));
        }
        sep(g, yg + 27.0, 4.0);
        // labels (entry 5, vertex colour 0x41,0x3f,0x4b) and the big digits (0x55 grey)
        let lab = Rgba::new(0x41, 0x3f, 0x4b, a);
        let dig = Rgba::new(0x55, 0x55, 0x55, a);
        let shift = if self.data.show_soul { 0.0 } else { 64.0 };
        spr2(g, hud, tex2::LABELS, (0.0, 0.0, 41.0, 25.0), (64.0 + shift, yg + 37.0, 41.0, 25.0), lab);
        spr2(g, hud, tex2::LABELS, (41.0, 0.0, 52.0, 22.0), (192.0 + shift, yg + 37.0, 52.0, 22.0), lab);
        if self.data.show_soul {
            spr2(g, hud, tex2::LABELS, (93.0, 0.0, 48.0, 22.0), (331.0, yg + 37.0, 48.0, 22.0), lab);
        }
        spr2(g, hud, tex2::LABELS, (141.0, 0.0, 47.0, 22.0), (54.0, yg + 59.0, 47.0, 22.0), lab);
        let digits = |g: &mut dyn MenuGfx, v: i64, x0: f32, slots: u32| {
            for k in 0..slots {
                let pow = slots - 1 - k;
                if let Some(d) = digit_of(v.max(0).min(999_999), pow) {
                    spr2(g, hud, tex2::LABELS, (d as f32 * 13.0, 25.0, 13.0, 22.0), (x0 + k as f32 * 11.0, yg + 37.0, 13.0, 22.0), dig);
                }
            }
        };
        digits(g, self.data.exp, 113.0 + shift, 6);
        digits(g, self.data.cash, 252.0 + shift, 6);
        if self.data.show_soul {
            digits(g, self.data.soul, 371.0, 6);
        }
        // items: two columns, 22 px rows; `%2d` counts right-aligned
        if self.data.items.is_empty() {
            text(g, 103.0, yg + 61.0, msg::NONE, white(a));
        }
        for (i, (name, n)) in self.data.items.iter().enumerate().take(10) {
            let (col, row) = (i % 2, i / 2);
            let x = if col == 0 { 103.0 } else { 288.0 };
            let y = yg + 61.0 + row as f32 * 22.0;
            // the `%i<kind>` item-kind icon occupies 16 px before the name (live 03d: icon at 107, name at 120)
            if let Some(cell) = self.data.item_ids.get(i).and_then(|&id| item_icon_cell(id)) {
                spr2(g, hud, art::ICONS, ((cell % 8) as f32 * 16.0, (cell / 8) as f32 * 20.0, 16.0, 20.0), (x, y + 1.0, 16.0, 20.0), Rgba::new(0x80, 0x80, 0x80, a));
            }
            text(g, x + 16.0, y, name, white(a));
            let q = format!("{n:2}");
            let qw = text_w(g, &q);
            text(g, (if col == 0 { 271.0 } else { 456.0 }) - qw, y, &q, white(a));
        }
        if self.data.escaped {
            let s = message(text_tbl, msg::END, "");
            let w = text_w(g, &s) + 20.0;
            let x = 512.0 - (w + 12.8);
            let cell = if retail { 3.0 } else { 0.0 };
            spr2(g, hud, art::BUTTONS, (cell * 18.0 + 2.0, 1.0, 14.0, 18.0), (x + 1.0, 395.0, 14.0, 18.0), af(1.0));
            text(g, x + 20.0, 394.0, &s, white(a));
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// result screen (BtlResult)
// ------------------------------------------------------------------------------------------------------------------

/// One party member on the result screen.
#[derive(Clone, Debug, Default)]
pub struct ResultPc {
    pub pc: u8,
    /// model number of the character (`PCRec+4`); `None` = derived from the pc id ([`model_of_pc`])
    pub model: Option<u16>,
    pub name: String,
    /// EXP before the battle
    pub exp_start: u32,
    pub exp_gain: u32,
    /// level table rows of this PC (`exp_next` per level) for `level_for_exp` / `next_exp`
    pub rows: Vec<sh2_menu::btlsave::LevelRow>,
    pub hp: i32,
    pub hp_max: i32,
    pub mp: i32,
    pub mp_max: i32,
    pub sp: i32,
    pub sp_max: i32,
    // ---- animation
    pub exp_shown: u32,
    pub rate: u32,
    pub level: u32,
    /// `Level Up!` flip angle (2 pi, decays by a quarter per tick)
    pub up_theta: f32,
    pub levelled: bool,
}

/// Retail PC id -> model number (`PCRec+4`, live `battle_live/INDEX.md`): 0 Yuri 0, 1 Blanca 1, 2 Gepetto 2, 3 Lucia 3, 4 Anastasia 4, 5 Karin 6,
/// 6 Joachim 7, 7 Kurando 0xa, 0xb Nicolai 0x12, 0xc 0x13, 0xd 0x15.
pub fn model_of_pc(pc: u8) -> u16 {
    match pc {
        0..=4 => pc as u16,
        5 => 6,
        6 => 7,
        7 => 0xa,
        8 => 0xb,
        9 => 0xc,
        10 => 0xd,
        0xb => 0x12,
        0xc => 0x13,
        0xd => 0x15,
        _ => 0,
    }
}

/// `BtlResult::WinCreate` (retail 0x399900): `BTL_002` entry of the wide portrait of a model, from the byte table at SLUS `0x42eb20`
/// (255 = no portrait).
pub fn face_entry(model: u16) -> Option<usize> {
    const T: [u8; 22] = [12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 255, 255, 23, 24, 25, 255, 255, 26, 27, 255, 28];
    T.get(model as usize).copied().filter(|&e| e != 255).map(|e| e as usize)
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ResultPhase {
    /// windows 0, 1 and the first PC window open at once, the next PC windows one per tick (open 333 ms)
    Opening,
    /// 0.5 s (or confirm) before the counters run
    Wait,
    /// counters: every tick `rate = max(13, total / 60)`; confirm jumps to the end
    Count,
    /// everything counted: the screen stays (`[x]:End`) until the confirm button is pressed (`Polling` phase 3 step 0)
    WaitEnd,
    /// windows close (333 ms), BGM fade
    Closing,
    Done,
}

/// `BtlResult`: the post-battle screen over the magic-circle backdrop.
#[derive(Clone, Debug)]
pub struct ResultScreen {
    pub pcs: Vec<ResultPc>,
    /// `You Get!` totals.  **They do not count down in the retail game** (`Polling` phase 2 step 0 zeroes the three rates `+0xdd8 / +0xde0 /
    /// +0xde8`; live capture: `Exp. 901` / `Cash. 2010` stay up while the character EXP and the party cash climb) -- the JP demo does count down.
    pub exp: i64,
    pub cash: i64,
    pub soul: i64,
    pub show_soul: bool,
    /// party cash (counts up)
    pub cash_total: i64,
    cash_target: i64,
    cash_rate: i64,
    soul_rate: i64,
    /// Soul energy counted so far (`CmdSoulEnergy` meter)
    pub soul_shown: i64,
    pub phase: ResultPhase,
    /// window alpha (open / close transition)
    pub alpha: f32,
    pub t: f32,
    pub ticks: u32,
    /// frames until the next `Level Up` sound may play (`Polling +0xe0c`, 8)
    se_wait: u32,
    /// SYSREG sound ids requested this tick (0x3000 counter start, 0x1003 level up)
    pub ses: Vec<u16>,
    /// looping sounds to release this tick: 0x3000 when the count is finished (`BtlResult::Polling` stops it once neither the cash nor an
    /// EXP counter moved, and the screen never leaves the count phase without it)
    pub stop_ses: Vec<u16>,
    /// the count-up loop 0x3000 is running
    counting_se: bool,
    /// the latched skip flag (`BtlResult+0x24` bit 1: set by the confirm button while counting)
    skip: bool,
}

/// `MenuWindow::Open(.., 0x14d)`: 333 ms.
pub const RESULT_FADE: f32 = 0.333;

impl ResultScreen {
    pub fn new(pcs: Vec<ResultPc>, exp: i64, cash: i64, soul: i64, show_soul: bool, cash_before: i64) -> Self {
        let mut s = ResultScreen {
            pcs,
            exp,
            cash,
            soul,
            show_soul,
            cash_total: cash_before,
            cash_target: cash_before + cash,
            cash_rate: 0,
            soul_rate: 0,
            soul_shown: 0,
            phase: ResultPhase::Opening,
            alpha: 0.0,
            t: 0.0,
            ticks: 0,
            se_wait: 0,
            ses: Vec::new(),
            stop_ses: Vec::new(),
            counting_se: false,
            skip: false,
        };
        for p in s.pcs.iter_mut() {
            p.exp_shown = p.exp_start;
            p.level = sh2_menu::btlsave::level_for_exp(&p.rows, p.exp_start).max(1);
        }
        s
    }

    pub fn is_done(&self) -> bool {
        self.phase == ResultPhase::Done
    }

    /// `BtlResult::Polling` phase 2 step 0: the per-tick increments (`total / 60`, at least 13).
    pub fn rate_of(total: i64) -> i64 {
        if total <= 0 {
            0
        } else {
            (total / 60).max(13)
        }
    }

    pub fn tick(&mut self, dt: f32, press: bool) {
        self.ses.clear();
        self.stop_ses.clear();
        self.ticks += 1;
        self.se_wait = self.se_wait.saturating_sub(1);
        match self.phase {
            ResultPhase::Opening => {
                self.alpha = (self.alpha + dt / RESULT_FADE).min(1.0);
                if self.alpha >= 1.0 {
                    self.phase = ResultPhase::Wait;
                    self.t = 0.0;
                }
            }
            ResultPhase::Wait => {
                self.t += dt;
                if self.t >= 0.5 || press {
                    self.cash_rate = Self::rate_of(self.cash);
                    self.soul_rate = if self.show_soul { Self::rate_of(self.soul) } else { 0 };
                    let mut any = self.cash_rate > 0;
                    for p in self.pcs.iter_mut() {
                        p.rate = Self::rate_of(p.exp_gain as i64) as u32;
                        if sh2_menu::btlsave::next_exp(&p.rows, p.exp_start) < 1 {
                            p.rate = 0;
                        }
                        any |= p.rate > 0;
                    }
                    if any {
                        self.ses.push(0x3000);
                        self.counting_se = true;
                    }
                    self.phase = ResultPhase::Count;
                }
            }
            ResultPhase::Count => {
                if press {
                    self.skip = true;
                }
                let press = self.skip;
                let mut busy = false;
                // the party cash counts up, capped at the target (`Polling` 0xdc4 / 0xdc8)
                if self.cash_rate > 0 {
                    let step = if press { self.cash_target - self.cash_total } else { self.cash_rate.min(self.cash_target - self.cash_total) };
                    self.cash_total += step;
                    if self.cash_total >= self.cash_target {
                        self.cash_rate = 0;
                    }
                    if self.cash_total > 99_999_999 {
                        self.cash_total = 99_999_999;
                        self.cash_rate = 0;
                    }
                    busy = true;
                }
                if self.soul_rate > 0 {
                    let step = if press { self.soul - self.soul_shown } else { self.soul_rate.min(self.soul - self.soul_shown) };
                    self.soul_shown += step;
                    if self.soul_shown >= self.soul {
                        self.soul_rate = 0;
                    }
                    busy = true;
                }
                for p in self.pcs.iter_mut() {
                    if p.up_theta > 0.0 {
                        p.up_theta -= p.up_theta / 4.0;
                        if p.up_theta < 0.01 {
                            p.up_theta = 0.0;
                        }
                    }
                    if p.rate == 0 {
                        continue;
                    }
                    // this tick's EXP: `min(rate, remaining)`, never past the next level (`GetNextExp`), so a level up lands on its own tick
                    let end = p.exp_start + p.exp_gain;
                    let remaining = (end - p.exp_shown) as i64;
                    let mut step = if press { remaining } else { (p.rate as i64).min(remaining) };
                    let next = sh2_menu::btlsave::next_exp(&p.rows, p.exp_shown);
                    if next >= 1 && next < step {
                        step = next;
                    }
                    p.exp_shown += step.max(0) as u32;
                    let lv = sh2_menu::btlsave::level_for_exp(&p.rows, p.exp_shown).max(1);
                    if lv > p.level {
                        p.level = lv;
                        p.levelled = true;
                        p.up_theta = std::f32::consts::TAU;
                        if self.se_wait == 0 {
                            self.ses.push(0x1003);
                            self.se_wait = 8;
                        }
                    }
                    if p.exp_shown >= end || sh2_menu::btlsave::next_exp(&p.rows, p.exp_shown) < 1 {
                        p.rate = 0;
                    }
                    busy = true;
                }
                // the counters stopped: release the count-up loop (the original keys it off on the first tick without movement)
                if !busy && self.counting_se {
                    self.counting_se = false;
                    self.stop_ses.push(0x3000);
                }
                // the `Level Up!` flips finish before the windows close
                if !busy && self.pcs.iter().all(|p| p.up_theta == 0.0) {
                    // the flag is cleared on the way to phase 3: the screen needs a fresh press to close
                    self.skip = false;
                    self.phase = ResultPhase::WaitEnd;
                }
            }
            ResultPhase::WaitEnd => {
                for p in self.pcs.iter_mut() {
                    if p.up_theta > 0.0 {
                        p.up_theta = (p.up_theta - p.up_theta / 4.0).max(0.0);
                    }
                }
                if press {
                    self.phase = ResultPhase::Closing;
                }
            }
            ResultPhase::Closing => {
                if self.counting_se {
                    self.counting_se = false;
                    self.stop_ses.push(0x3000);
                }
                self.alpha = (self.alpha - dt / RESULT_FADE).max(0.0);
                if self.alpha <= 0.0 {
                    self.phase = ResultPhase::Done;
                }
            }
            ResultPhase::Done => {}
        }
    }

    /// `BtlResult::WinCreate` (retail 0x399900, decoded `MenuSprite` / `MenuPolygon` records): window 0 = backdrop (`BTL_002` entry 2,
    /// 513 x 449) + the dark streak overlay (entry 6 at 2x) + the `End` prompt; window 1 = the `You Get!` totals (ornaments of entry 3,
    /// body polygon (361, 54)-(492, 196), title (376, 63), labels / digits of entry 5, the `Cash` logo (348, 369) and the party cash digits of
    /// entry 11); windows 2.. = one 360 x 45 window per party member at `y = 42 + 44 k` that slides in from the left.  Flat polygon colours
    /// are the GS ones (no modulate doubling), so they are halved for the port's 0x80 = 1.0 convention.
    pub fn draw(&self, g: &mut dyn MenuGfx, hud: &BtlHud, text_tbl: &crate::ui::BtlText, retail: bool) {
        let a = (self.alpha * 128.0) as u8;
        let wa = Rgba::new(0x80, 0x80, 0x80, a);
        let titles = if hud.tex2.contains_key(&art::TITLES_PURPLE) { art::TITLES_PURPLE } else { tex2::TITLES };
        // window 0: backdrop, streaks, prompt
        spr2(g, hud, art::BACKDROP, (0.0, 0.0, 512.0, 448.0), (0.0, 0.0, 513.0, 449.0), wa);
        spr2(g, hud, art::STREAKS, (0.0, 0.0, 256.0, 224.0), (0.0, 0.0, 514.0, 450.0), wa);
        {
            let s = message(text_tbl, msg::END, "");
            let cell = if retail { 3.0 } else { 0.0 };
            spr2(g, hud, art::BUTTONS, (cell * 18.0 + 2.0, 1.0, 14.0, 18.0), (461.0, 395.0, 14.0, 18.0), wa);
            text(g, 480.0, 394.0, &s, white(a));
        }
        // window 1: totals
        let pa = (self.alpha * 76.0) as u8;
        let half = |r: u8, gg: u8, b: u8, al: u8| Rgba::new(((r as u16 * 128) / 255) as u8, ((gg as u16 * 128) / 255) as u8, ((b as u16 * 128) / 255) as u8, al);
        grad(g, 361.0, 54.0, 131.0, 142.0, half(0x41, 0x41, 0x4e, pa), half(0x0a, 0x08, 0x0a, pa), half(0x41, 0x41, 0x4e, pa), half(0x0a, 0x08, 0x0a, pa));
        let orn = |g: &mut dyn MenuGfx, src: (f32, f32, f32, f32), dst: (f32, f32, f32, f32)| spr2(g, hud, art::ORNAMENT, src, dst, wa);
        orn(g, (2.0, 70.0, 36.0, 7.0), (387.0, 49.0, 81.0, 7.0));
        orn(g, (38.0, 77.0, -36.0, -7.0), (388.0, 194.0, 79.0, 7.0));
        orn(g, (0.0, 79.0, 14.0, 22.0), (349.0, 80.0, 14.0, 67.0));
        orn(g, (14.0, 101.0, -14.0, -22.0), (490.0, 106.0, 14.0, 65.0));
        orn(g, (0.0, 29.0, 48.0, 27.0), (340.0, 42.0, 48.0, 27.0));
        orn(g, (0.0, 56.0, 26.0, 14.0), (340.0, 67.0, 26.0, 14.0));
        orn(g, (48.0, 29.0, 42.0, 63.0), (347.0, 146.0, 42.0, 63.0));
        orn(g, (92.0, 90.0, -44.0, -61.0), (464.0, 43.0, 42.0, 63.0));
        orn(g, (26.0, 70.0, -26.0, -14.0), (487.0, 169.0, 26.0, 14.0));
        orn(g, (48.0, 56.0, -48.0, -27.0), (465.0, 181.0, 48.0, 27.0));
        spr2(g, hud, art::BAR, (0.0, 0.0, 123.0, 6.0), (365.0, 92.0, 123.0, 6.0), wa);
        spr2(g, hud, titles, (0.0, 24.0, 93.0, 23.0), (376.0, 63.0, 93.0, 23.0), wa);
        let lab = Rgba::new(0x41, 0x3f, 0x4b, a);
        let dig = Rgba::new(0x58, 0x58, 0x58, a);
        let ry = if self.show_soul { 106.0 } else { 119.0 };
        spr2(g, hud, tex2::LABELS, (0.0, 0.0, 41.0, 25.0), (379.0, ry, 41.0, 25.0), lab);
        spr2(g, hud, tex2::LABELS, (41.0, 0.0, 52.0, 22.0), (368.0, ry + 27.0, 52.0, 22.0), lab);
        if self.show_soul {
            spr2(g, hud, tex2::LABELS, (93.0, 0.0, 48.0, 22.0), (372.0, 159.0, 48.0, 22.0), lab);
        }
        let big = |g: &mut dyn MenuGfx, v: i64, x0: f32, y: f32, slots: u32| {
            for k in 0..slots {
                let pow = slots - 1 - k;
                if let Some(d) = digit_of(v.max(0), pow) {
                    spr2(g, hud, tex2::LABELS, (d as f32 * 13.0, 25.0, 13.0, 22.0), (x0 + k as f32 * 11.0, y, 13.0, 22.0), dig);
                }
            }
        };
        big(g, self.exp, 420.0, ry, 6);
        big(g, self.cash, 420.0, ry + 27.0, 6);
        if self.show_soul {
            big(g, self.soul_shown.max(0), 442.0, 159.0, 4);
        }
        // party cash: `Cash` logo + outlined digits (8 slots, a separator glyph before the thousands and millions groups)
        spr2(g, hud, art::CASH, (0.0, 0.0, 44.0, 25.0), (348.0, 369.0, 44.0, 25.0), wa);
        {
            let v = self.cash_total.clamp(0, 99_999_999);
            let xs = [391.0, 401.0, 416.0, 426.0, 436.0, 451.0, 461.0, 471.0];
            for (k, x) in xs.iter().enumerate() {
                let pow = 7 - k as u32;
                if let Some(d) = digit_of(v, pow) {
                    spr2(g, hud, art::DIGITS18, (d as f32 * 18.0, 0.0, 18.0, 21.0), (*x, 370.0, 18.0, 21.0), wa);
                }
            }
            for (min, x) in [(1_000_000, 406.0), (1_000, 441.0)] {
                if v >= min {
                    spr2(g, hud, art::DIGITS18, (180.0, 0.0, 18.0, 21.0), (x, 370.0, 18.0, 21.0), wa);
                }
            }
        }
        // windows 2..: one per party member, sliding in from the left (`MenuWindow::Open` style 3)
        let slide = -(360.0 + 100.0) * (1.0 - self.alpha);
        for (k, p) in self.pcs.iter().enumerate().take(8) {
            self.draw_pc(g, hud, p, slide, 42.0 + 44.0 * k as f32, 128);
        }
    }

    fn draw_pc(&self, g: &mut dyn MenuGfx, hud: &BtlHud, p: &ResultPc, wx: f32, wy: f32, a: u8) {
        let wa = Rgba::new(0x80, 0x80, 0x80, a);
        let v = |x: f32, y: f32, c: u8| sh2_menu::gfx::Vertex { pos: glam_vec(wx + x, wy + y), uv: glam_vec(0.0, 0.0), color: Rgba::new(c / 2, c / 2, c / 2, a) };
        let quad = |g: &mut dyn MenuGfx, q: [(f32, f32, u8); 4]| {
            g.draw(sh2_menu::gfx::DrawCmd::Quad { tex: None, v: [v(q[0].0, q[0].1, q[0].2), v(q[1].0, q[1].1, q[1].2), v(q[2].0, q[2].1, q[2].2), v(q[3].0, q[3].1, q[3].2)], blend: Blend::Alpha })
        };
        // the grey band (`MenuPolygon`s, y 2..38, colours 0x28 -> 0x5a): two flat strips, a diagonally split quad, and the triangle that
        // cuts the right end from (202, 2) down to (317, 38)
        quad(g, [(0.0, 2.0, 0x28), (0.0, 38.0, 0x28), (70.0, 2.0, 0x32), (70.0, 38.0, 0x32)]);
        quad(g, [(70.0, 2.0, 0x32), (70.0, 38.0, 0x32), (185.0, 2.0, 0x3c), (185.0, 2.0, 0x3c)]);
        quad(g, [(70.0, 38.0, 0x3c), (185.0, 2.0, 0x46), (185.0, 38.0, 0x46), (185.0, 38.0, 0x46)]);
        quad(g, [(185.0, 2.0, 0x46), (185.0, 38.0, 0x46), (202.0, 2.0, 0x4b), (202.0, 38.0, 0x4b)]);
        quad(g, [(202.0, 2.0, 0x4b), (202.0, 38.0, 0x4b), (317.0, 38.0, 0x5a), (317.0, 38.0, 0x5a)]);
        // the soft highlight behind NEXT (alpha 0 -> 0x20 -> 0, light blue (0xc0, 0xe0, 0xff) over dark blue (0x10, 4, 0x80))
        let hv = |x: f32, y: f32, light: bool| {
            let (r, gg, b, al) = if light { (0xc0u16, 0xe0u16, 0xffu16, 0x20u8) } else { (0x10, 0x04, 0x80, 0) };
            sh2_menu::gfx::Vertex { pos: glam_vec(wx + x, wy + y), uv: glam_vec(0.0, 0.0), color: Rgba::new((r * 128 / 255) as u8, (gg * 128 / 255) as u8, (b * 128 / 255) as u8, al) }
        };
        for (x0, l0, x1, l1) in [(262.0, false, 278.0, true), (278.0, true, 308.0, true), (308.0, true, 348.0, false)] {
            g.draw(sh2_menu::gfx::DrawCmd::Quad { tex: None, v: [hv(x0, 9.0, l0), hv(x0, 19.0, l0), hv(x1, 9.0, l1), hv(x1, 19.0, l1)], blend: Blend::Alpha });
        }
        // portrait (96 x 36 at (6, 2)), arrow (-1, 7), name (128, 2)
        let model = p.model.unwrap_or_else(|| model_of_pc(p.pc));
        if let Some(e) = face_entry(model) {
            spr2(g, hud, e, (0.0, 0.0, 96.0, 36.0), (wx + 6.0, wy + 2.0, 96.0, 36.0), wa);
        }
        spr2(g, hud, art::CURSOR, (0.0, 0.0, 34.0, 34.0), (wx - 1.0, wy + 7.0, 34.0, 34.0), wa);
        text(g, wx + 128.0, wy + 2.0, &p.name, white(a));
        // labels (entry 7), tinted like the capture: LEVEL / NEXT lavender, HP blue, MP magenta, SP red
        let lbl = |g: &mut dyn MenuGfx, src: (f32, f32, f32, f32), x: f32, y: f32, c: (u8, u8, u8)| spr2(g, hud, art::STATS, src, (wx + x, wy + y, src.2, src.3), Rgba::new(c.0, c.1, c.2, a));
        lbl(g, (0.0, 0.0, 37.0, 12.0), 86.0, 3.0, (0x41, 0x3f, 0x4c));
        lbl(g, (37.0, 0.0, 16.0, 12.0), 125.0, 21.0, (0x34, 0x47, 0x65));
        lbl(g, (53.0, 0.0, 16.0, 12.0), 204.0, 21.0, (0x55, 0x26, 0x4c));
        lbl(g, (69.0, 0.0, 16.0, 12.0), 283.0, 21.0, (0x5a, 0x24, 0x24));
        lbl(g, (85.0, 0.0, 30.0, 12.0), 269.0, 3.0, (0x41, 0x3f, 0x4c));
        // level: 12 x 22 digits (entry 8), the tens hidden below 10
        let dig12 = |g: &mut dyn MenuGfx, d: usize, x: f32| spr2(g, hud, art::DIGITS12, (d as f32 * 12.0, 0.0, 12.0, 22.0), (wx + x, wy + 15.0, 12.0, 22.0), Rgba::new(0x58, 0x58, 0x58, a));
        let lv = p.level.min(99) as usize;
        if lv >= 10 {
            dig12(g, lv / 10, 99.0);
        }
        dig12(g, lv % 10, 109.0);
        // HP / MP / SP numbers: 10 x 15 cells (entry 7 row 12), 8 px pitch; current values take the HP colour thresholds
        let small = |g: &mut dyn MenuGfx, v: i64, x0: f32, y: f32, slots: u32, col: (u8, u8, u8)| {
            for k in 0..slots {
                let pow = slots - 1 - k;
                if let Some(d) = digit_of(v.max(0), pow) {
                    spr2(g, hud, art::STATS, ((d as f32 + 1.0) * 10.0, 12.0, 10.0, 15.0), (wx + x0 + k as f32 * 8.0, wy + y, 10.0, 15.0), Rgba::new(col.0, col.1, col.2, a));
                }
            }
        };
        let thresh = |cur: i32, max: i32| {
            let mut half = max >> 1;
            if half < 2 && max > 2 {
                half = 2;
            }
            let mut quarter = max >> 2;
            if quarter < 1 && max > 1 {
                quarter = 1;
            }
            if cur > half {
                (0x58u8, 0x58u8, 0x58u8)
            } else if cur > quarter {
                (0x58, 0x58, 0)
            } else {
                (0x58, 0, 0)
            }
        };
        let white58 = (0x58u8, 0x58u8, 0x58u8);
        let slash = |g: &mut dyn MenuGfx, x: f32| spr2(g, hud, art::STATS, (0.0, 12.0, 10.0, 15.0), (wx + x, wy + 21.0, 10.0, 15.0), Rgba::new(0x58, 0x58, 0x58, a));
        small(g, p.hp as i64, 141.0, 21.0, 3, thresh(p.hp, p.hp_max));
        slash(g, 165.0);
        small(g, p.hp_max as i64, 173.0, 21.0, 3, white58);
        small(g, p.mp as i64, 220.0, 21.0, 3, thresh(p.mp, p.mp_max));
        slash(g, 244.0);
        small(g, p.mp_max as i64, 252.0, 21.0, 3, white58);
        small(g, p.sp as i64, 299.0, 21.0, 2, white58);
        // NEXT: five cells from x 299 at y 3, dashes at the level cap
        let next = sh2_menu::btlsave::next_exp(&p.rows, p.exp_shown);
        if next < 1 {
            for k in 0..5 {
                spr2(g, hud, art::STATS, (115.0, 0.0, 10.0, 15.0), (wx + 299.0 + k as f32 * 8.0, wy + 3.0, 10.0, 15.0), Rgba::new(0x58, 0x58, 0x58, a));
            }
        } else {
            small(g, next, 299.0, 3.0, 5, white58);
        }
        // gauges (entry 9): tracks (140 / 219 / 298, 32), fills 2 px inside, lengths hp * 55 / max, mp * 55 / max, sp * 18 / max
        let track = |g: &mut dyn MenuGfx, src: (f32, f32, f32, f32), x: f32| spr2(g, hud, art::GAUGES, src, (wx + x, wy + 32.0, src.2, src.3), wa);
        track(g, (1.0, 8.0, 60.0, 8.0), 140.0);
        track(g, (62.0, 8.0, 60.0, 8.0), 219.0);
        track(g, (123.0, 8.0, 23.0, 8.0), 298.0);
        let fill = |g: &mut dyn MenuGfx, u: f32, x: f32, len: i32| {
            if len > 0 {
                spr2(g, hud, art::GAUGES, (u, 1.0, len as f32, 6.0), (wx + x, wy + 32.0, len as f32, 6.0), wa);
            }
        };
        let frac = |cur: i32, max: i32, n: i32| if max <= 0 { 0 } else { (cur.max(0) * n / max).min(n) };
        fill(g, 3.0, 142.0, frac(p.hp, p.hp_max, 55));
        fill(g, 64.0, 221.0, frac(p.mp, p.mp_max, 55));
        fill(g, 125.0, 300.0, frac(p.sp, p.sp_max, 18));
        // Level Up! (entry 4 (0, 48, 104, 25), flips around x 55 while the angle decays, rests at (3, 20))
        if p.levelled {
            // the gold sheet as it is (live: `Level Up!` is gold; only the `You Get!` packet swaps the CLUT to purple)
            let w = p.up_theta.cos() * 104.0;
            let src = if w >= 0.0 { (0.0, 48.0, 104.0, 25.0) } else { (104.0, 48.0, -104.0, 25.0) };
            spr2(g, hud, tex2::TITLES, src, (wx + 55.0 - w.abs() / 2.0, wy + 20.0, w.abs().max(1.0), 25.0), wa);
        }
    }
}

fn glam_vec(x: f32, y: f32) -> bevy::math::Vec2 {
    bevy::math::Vec2::new(x, y)
}

// ------------------------------------------------------------------------------------------------------------------
// win / lose / escape sequencing
// ------------------------------------------------------------------------------------------------------------------

/// What the host (`plugin::battle_tick`) has to do for a sequence this tick.
#[derive(Clone, Debug, PartialEq)]
pub enum SeqEvent {
    /// close the party panel / turn strip
    HideHud,
    /// `SetWinCamera1` / `SetLoseCamera1`
    Camera,
    /// post a message window
    Message { kind: MesKind, close: MesClose, text: String, icon: bool, tag: u32 },
    /// close the message posted with `tag`
    CloseMessage(u32),
    /// play the win pose motion
    WinPose,
    /// play a SYSREG sound
    Se(u16),
    /// release a looping SYSREG sound (`HNMSnd::StopSE`): the result screen's count-up loop 0x3000
    StopSe(u16),
    /// fade the screen to black over `frames`
    FadeOut(u32),
    /// drop the cover at once (`BtlFader::SetMode(0, 0, 0)`)
    Uncover,
    /// the sequence is over: hand the outcome to `SSHSys`
    Finish,
}

/// message tag of the `Skip` prompt
pub const TAG_SKIP: u32 = 1;
/// message tag of the run-away message
pub const TAG_ESCAPE: u32 = 2;

/// Timings of `Retail_CBattle_Phase15_Win` (seconds after the last enemy fell).
pub mod win_t {
    /// step 3: formation, result BGM, win camera, HUD close, `Skip` prompt
    pub const CAMERA: f32 = 0.5;
    /// step 5: win pose motion 0x33 + voice, 0.2 s after the camera
    pub const POSE: f32 = 0.7;
    /// stand-in for the pose motion's end when the models report none
    pub const POSE_LEN: f32 = 3.0;
    /// safety cap while the motion reports `Playing`
    pub const POSE_MAX: f32 = 30.0;
}

/// What the models side reports about the victory motion (`pModel + 0x510` of the winners: 1 playing, 2 ended).
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub enum WinMotion {
    /// no model has a victory motion (or it has not started yet)
    #[default]
    Unknown,
    /// the victory motion (0x33) is playing
    Playing,
    /// it has played to its end
    Done,
}

#[derive(Clone, Debug)]
pub enum WinState {
    Pose,
    Bonus(BonusPanel),
    /// black screen between the battle overlay and the result screen (`BtlSocket` states 4 -> 6)
    Black,
    Screen(ResultScreen),
    Done,
}

/// The whole victory flow: win pose with the `Skip` prompt, `Battle Bonus / You Get!` panel, fade to black, result screen, field.
#[derive(Clone, Debug)]
pub struct WinSequence {
    pub state: WinState,
    pub t: f32,
    pub bonus: BonusData,
    pub screen: Option<ResultScreen>,
    hud_hidden: bool,
    camera: bool,
    posed: bool,
    skip_text: String,
}

impl WinSequence {
    pub fn new(bonus: BonusData, screen: ResultScreen, skip_text: String) -> Self {
        WinSequence { state: WinState::Pose, t: 0.0, bonus, screen: Some(screen), hud_hidden: false, camera: false, posed: false, skip_text }
    }

    pub fn hud_hidden(&self) -> bool {
        self.hud_hidden
    }
    pub fn camera_ready(&self) -> bool {
        self.camera
    }
    pub fn is_done(&self) -> bool {
        matches!(self.state, WinState::Done)
    }

    pub fn tick(&mut self, dt: f32, press: bool) -> Vec<SeqEvent> {
        self.tick_with(dt, press, WinMotion::Unknown)
    }

    /// One tick with the state of the victory motion.  `Retail_CBattle_Phase15_Win` step 5: the `Battle Bonus / You Get!` panel is built only when
    /// the winner's motion 0x33 has *ended* (`pModel+0x510 == 2` after the motion was started) or the confirm button is pressed (then the panel gets
    /// its skip flag); until then the win scene (camera, poses, `Skip` prompt) simply goes on.  Without a motion signal ([`WinMotion::Unknown`],
    /// e.g. a disc whose party models have no victory motion) the stand-in length [`win_t::POSE_LEN`] applies.
    pub fn tick_with(&mut self, dt: f32, press: bool, motion: WinMotion) -> Vec<SeqEvent> {
        let mut ev = Vec::new();
        self.t += dt;
        match &mut self.state {
            WinState::Pose => {
                if !self.camera && self.t >= win_t::CAMERA {
                    self.camera = true;
                    self.hud_hidden = true;
                    ev.push(SeqEvent::Camera);
                    ev.push(SeqEvent::HideHud);
                    ev.push(SeqEvent::Message { kind: MesKind::Prompt, close: MesClose::Owner, text: self.skip_text.clone(), icon: true, tag: TAG_SKIP });
                }
                if !self.posed && self.t >= win_t::POSE {
                    self.posed = true;
                    ev.push(SeqEvent::WinPose);
                }
                let over = match motion {
                    WinMotion::Done => true,
                    // still playing: the scene goes on (a long safety cap in case the motion never reports its end)
                    WinMotion::Playing => self.t >= win_t::POSE + win_t::POSE_MAX,
                    WinMotion::Unknown => self.t >= win_t::POSE + win_t::POSE_LEN,
                };
                // the button ends the pose at once (`uVar1 & 0x2000`, the button must be seen after the camera step)
                if self.posed && (over || press) {
                    let mut panel = BonusPanel::new(self.bonus.clone());
                    panel.skip = press && !over;
                    self.state = WinState::Bonus(panel);
                }
            }
            WinState::Bonus(p) => {
                let was_fading = p.fade_screen;
                p.tick(dt, press);
                for &s in &p.ses {
                    ev.push(SeqEvent::Se(s));
                }
                if p.fade_screen && !was_fading {
                    ev.push(SeqEvent::CloseMessage(TAG_SKIP));
                    ev.push(SeqEvent::FadeOut(30));
                }
                if p.is_done() {
                    self.state = WinState::Black;
                    self.t = 0.0;
                }
            }
            WinState::Black => {
                if self.t >= 0.3 {
                    ev.push(SeqEvent::Uncover);
                    self.state = match self.screen.take() {
                        Some(s) => WinState::Screen(s),
                        None => WinState::Done,
                    };
                }
            }
            WinState::Screen(s) => {
                s.tick(dt, press);
                for &se in &s.ses {
                    ev.push(SeqEvent::Se(se));
                }
                for &se in &s.stop_ses {
                    ev.push(SeqEvent::StopSe(se));
                }
                if s.is_done() {
                    ev.push(SeqEvent::FadeOut(1));
                    ev.push(SeqEvent::Finish);
                    self.state = WinState::Done;
                }
            }
            WinState::Done => {}
        }
        ev
    }

    pub fn draw(&self, g: &mut dyn MenuGfx, hud: &BtlHud, text_tbl: &crate::ui::BtlText, retail: bool) {
        match &self.state {
            WinState::Bonus(p) => p.draw(g, hud, text_tbl, retail),
            WinState::Screen(s) => s.draw(g, hud, text_tbl, retail),
            _ => {}
        }
    }
}

/// `Retail_CBattle_Phase16_Lose`: lose camera and HUD close after 0.5 s, 3 s hold, `BtlFader::SetHoldFade(1.0, 3)`, then the
/// `GameOver` scene (`SSHSys` request 0x30 through `cbBattleA`).
#[derive(Clone, Debug, Default)]
pub struct LoseSequence {
    pub t: f32,
    camera: bool,
    faded: bool,
    done: bool,
}

pub mod lose_t {
    pub const CAMERA: f32 = 0.5;
    pub const FADE: f32 = 3.5;
    pub const END: f32 = 4.1;
}

impl LoseSequence {
    pub fn hud_hidden(&self) -> bool {
        self.camera
    }
    pub fn camera_ready(&self) -> bool {
        self.camera
    }
    pub fn tick(&mut self, dt: f32) -> Vec<SeqEvent> {
        let mut ev = Vec::new();
        self.t += dt;
        if !self.camera && self.t >= lose_t::CAMERA {
            self.camera = true;
            ev.push(SeqEvent::Camera);
            ev.push(SeqEvent::HideHud);
        }
        if !self.faded && self.t >= lose_t::FADE {
            self.faded = true;
            ev.push(SeqEvent::FadeOut(30));
        }
        if !self.done && self.t >= lose_t::END {
            self.done = true;
            ev.push(SeqEvent::Finish);
        }
        ev
    }
}

/// `CBattle` phase 8 after `GetEscapeRate` succeeded: the run-away message (kind 0, owner-closed, 2 s), then the `You Get!` panel with
/// the backdrop and the `End` prompt (`BtlBonus` with outcome bits set), then the field.
#[derive(Clone, Debug)]
pub struct EscapeSequence {
    pub t: f32,
    pub panel: Option<BonusPanel>,
    bonus: BonusData,
    text: String,
    posted: bool,
    faded: bool,
    closed: bool,
    done: bool,
}

/// live 05a/05b: the message is up, the scene fades to black under it, then the panel comes over the backdrop
pub mod escape_t {
    pub const FADE: f32 = 1.0;
    pub const PANEL: f32 = 2.2;
}

impl EscapeSequence {
    pub fn new(bonus: BonusData, text: String) -> Self {
        EscapeSequence { t: 0.0, panel: None, bonus, text, posted: false, faded: false, closed: false, done: false }
    }
    pub fn hud_hidden(&self) -> bool {
        self.panel.is_some()
    }
    pub fn tick(&mut self, dt: f32, press: bool) -> Vec<SeqEvent> {
        let mut ev = Vec::new();
        self.t += dt;
        if !self.posted {
            self.posted = true;
            ev.push(SeqEvent::Message { kind: MesKind::Center, close: MesClose::Owner, text: self.text.clone(), icon: false, tag: TAG_ESCAPE });
        }
        if !self.faded && self.t >= escape_t::FADE {
            self.faded = true;
            ev.push(SeqEvent::FadeOut(40));
        }
        if !self.closed && self.t >= escape_t::PANEL {
            self.closed = true;
            ev.push(SeqEvent::CloseMessage(TAG_ESCAPE));
            ev.push(SeqEvent::HideHud);
            ev.push(SeqEvent::Uncover);
            self.panel = Some(BonusPanel::new(BonusData { escaped: true, ..self.bonus.clone() }));
        }
        if let Some(p) = self.panel.as_mut() {
            let was = p.fade_screen;
            p.tick(dt, press);
            for &s in &p.ses {
                ev.push(SeqEvent::Se(s));
            }
            if p.fade_screen && !was {
                ev.push(SeqEvent::FadeOut(30));
            }
            if p.is_done() && !self.done {
                self.done = true;
                ev.push(SeqEvent::Finish);
            }
        }
        ev
    }
    pub fn draw(&self, g: &mut dyn MenuGfx, hud: &BtlHud, text_tbl: &crate::ui::BtlText, retail: bool) {
        if let Some(p) = &self.panel {
            p.draw(g, hud, text_tbl, retail);
        }
    }
}

/// Combo-chance message text: `Your chance for a %s-person Combo!` with the count as a full-width digit (`CBattle::SetBtlMessage`
/// builds `0x82 0x4f + n`).
pub fn combo_chance_text(text: &crate::ui::BtlText, persons: usize) -> String {
    let d: String = persons.to_string().chars().map(|c| char::from_u32(0xff10 + (c as u32 - '0' as u32)).unwrap_or(c)).collect();
    message(text, msg::COMBO_CHANCE, &d)
}

// ------------------------------------------------------------------------------------------------------------------
// tests
// ------------------------------------------------------------------------------------------------------------------

#[cfg(test)]
mod tests {
    use super::*;

    fn data() -> BonusData {
        BonusData { exp: 5, cash: 40, soul: 0, show_soul: false, items: vec![("Thera Leaf".into(), 1)], item_ids: vec![0], rows: vec![], escaped: false }
    }

    #[test]
    fn bonus_panel_geometry_matches_the_retail_packet() {
        // no bonus rows: h = 0, top = 224 - 97 = 127, bottom = 127 + 194 = 321, You Get! at top + 16
        let p = BonusPanel::new(data());
        assert_eq!(p.rows_height(), 0.0);
        assert_eq!(p.vertical(), (127.0, 321.0));
        assert_eq!(p.you_get_y(), 143.0);
        // two rows: h = 85, top = 224 - ((85 + 194) >> 1) = 224 - 139 = 85
        let mut d = data();
        d.rows = vec![BonusRow { name: "No-Damage Victory".into(), value: "Exp.+10".into() }, BonusRow::default()];
        let p = BonusPanel::new(d);
        assert_eq!(p.rows_height(), 85.0);
        assert_eq!(p.vertical(), (85.0, 364.0));
        assert_eq!(p.you_get_y(), 186.0);
    }

    #[test]
    fn bonus_panel_timing() {
        let mut p = BonusPanel::new(data());
        let dt = 1.0 / 60.0;
        let mut t = 0.0;
        while p.phase == BonusPhase::FadeIn {
            p.tick(dt, false);
            t += dt;
        }
        assert!((t - 0.5).abs() < 0.03, "fade in {t}");
        while p.phase == BonusPhase::Rows {
            p.tick(dt, false);
            t += dt;
        }
        // the empty list still spends the 0.25 s step of phase 1 plus its own 0.25 s step
        assert!((t - 1.0).abs() < 0.05, "rows {t}");
        while p.phase == BonusPhase::Hold {
            p.tick(dt, false);
            t += dt;
        }
        assert!((t - 11.0).abs() < 0.1, "hold {t}");
        assert!(p.fade_screen);
        while !p.is_done() {
            p.tick(dt, false);
            t += dt;
        }
        assert!((t - 11.5).abs() < 0.1, "fade out {t}");
    }

    #[test]
    fn bonus_rows_reveal_with_a_sound() {
        let mut d = data();
        d.rows = vec![BonusRow::default(); 3];
        let mut p = BonusPanel::new(d);
        p.tick(1.0, false);
        assert_eq!(p.phase, BonusPhase::Rows);
        let mut sounds = 0;
        let mut t: f32 = 0.0;
        while p.phase == BonusPhase::Rows {
            p.tick(1.0 / 60.0, false);
            sounds += p.ses.len();
            t += 1.0 / 60.0;
        }
        assert_eq!(sounds, 3);
        assert_eq!(p.shown_rows, 3);
        assert!((t - 1.0).abs() < 0.1, "{t}");
    }

    #[test]
    fn confirm_skips_the_hold() {
        let mut p = BonusPanel::new(data());
        p.tick(1.0, false);
        p.tick(1.0, false);
        p.tick(1.0, false);
        assert_eq!(p.phase, BonusPhase::Hold);
        p.tick(0.1, true);
        assert_eq!(p.phase, BonusPhase::FadeOut);
    }

    #[test]
    fn count_rates_follow_polling() {
        assert_eq!(ResultScreen::rate_of(0), 0);
        assert_eq!(ResultScreen::rate_of(5), 13);
        assert_eq!(ResultScreen::rate_of(6000), 100);
    }

    fn rows() -> Vec<sh2_menu::btlsave::LevelRow> {
        (1..=99u16).map(|l| sh2_menu::btlsave::LevelRow { exp_next: 100 * l as u32, ..Default::default() }).collect()
    }

    #[test]
    fn result_screen_counts_and_levels_up() {
        let pc = ResultPc { pc: 5, name: "Karin".into(), exp_start: 90, exp_gain: 50, rows: rows(), hp: 30, hp_max: 40, mp: 10, mp_max: 20, sp: 5, sp_max: 7, ..Default::default() };
        let mut s = ResultScreen::new(vec![pc], 50, 40, 0, false, 300);
        assert_eq!(s.pcs[0].level, 1);
        let dt = 1.0 / 60.0;
        while s.phase != ResultPhase::Count {
            s.tick(dt, false);
        }
        assert_eq!(s.ses, vec![0x3000]);
        let mut level_up = false;
        while s.phase == ResultPhase::Count {
            s.tick(dt, false);
            level_up |= s.ses.contains(&0x1003);
        }
        assert!(level_up);
        assert_eq!(s.pcs[0].level, 2);
        assert_eq!(s.pcs[0].exp_shown, 140);
        // the retail `You Get!` totals stay up (live: `Exp. 901` / `Cash. 2010` while the party cash and character EXP climb)
        assert_eq!(s.exp, 50);
        assert_eq!(s.cash, 40);
        assert_eq!(s.cash_total, 340);
        // the screen stays up until the button is pressed (live: the result screen sat there for 30 s)
        assert_eq!(s.phase, ResultPhase::WaitEnd);
        for _ in 0..600 {
            s.tick(dt, false);
        }
        assert_eq!(s.phase, ResultPhase::WaitEnd);
        s.tick(dt, true);
        assert_eq!(s.phase, ResultPhase::Closing);
        while !s.is_done() {
            s.tick(dt, false);
        }
    }

    /// `BtlResult::WinCreate` (0x399900): the wide portrait entry comes from the byte table at 0x42eb20 indexed by the model number
    /// (live: Nicolai, model 0x12, shows the entry-26 face; the old `12 + pc id` mapping drew another character).
    /// `Retail_GetItemKindTable` (SLUS 0x386130): consumables -> icon 0x2c (cell 12 of the common icon sheet, the pouch of live `03d`), armour 0x2f, ...
    #[test]
    fn item_kind_icons_follow_the_retail_table() {
        assert_eq!(item_icon_cell(0), Some(12));
        assert_eq!(item_icon_cell(99), Some(12));
        assert_eq!(item_icon_cell(250), Some(15));
        assert_eq!(item_icon_cell(450), Some(21));
        assert_eq!(item_icon_cell(950), Some(13));
        assert_eq!(item_icon_cell(0x41f), Some(17));
        assert_eq!(item_icon_cell(150), None);
        assert_eq!(item_icon_cell(-1), None);
    }

    #[test]
    fn portrait_entries_follow_the_model_table() {
        assert_eq!(face_entry(0), Some(12));
        assert_eq!(face_entry(model_of_pc(5)), Some(18)); // Karin (model 6)
        assert_eq!(face_entry(model_of_pc(0xb)), Some(26)); // Nicolai (model 0x12)
        assert_eq!(face_entry(model_of_pc(7)), Some(22)); // Kurando (model 0xa)
        assert_eq!(face_entry(11), None);
        assert_eq!(face_entry(99), None);
    }

    /// `Polling` phase 2: each tick adds `min(rate, remaining)` EXP but never past the next level (`GetNextExp`), so a big gain climbs one
    /// level per tick and every level plays its own flip (live: Nicolai Lv 2 -> 8 on 900 EXP).
    #[test]
    fn exp_never_crosses_two_levels_in_one_tick() {
        let pc = ResultPc { pc: 0xb, rows: rows(), exp_start: 0, exp_gain: 900, hp_max: 1, mp_max: 1, sp_max: 1, ..Default::default() };
        let mut s = ResultScreen::new(vec![pc], 900, 0, 0, false, 0);
        let dt = 1.0 / 60.0;
        while s.phase != ResultPhase::Count {
            s.tick(dt, false);
        }
        let mut last = s.pcs[0].level;
        let mut ups = 0;
        while s.phase == ResultPhase::Count {
            s.tick(dt, false);
            let l = s.pcs[0].level;
            assert!(l <= last + 1, "two levels in one tick");
            if l > last {
                ups += 1;
            }
            last = l;
        }
        // rows: level l needs 100 l more EXP (acc 100, 300, 600, 1000): 900 EXP = level 4
        assert_eq!(s.pcs[0].level, 4);
        assert_eq!(ups, 3);
        assert_eq!(s.pcs[0].exp_shown, 900);
    }

    #[test]
    fn message_windows_time_out_and_close_on_buttons() {
        let mut q = MesQueue::default();
        let a = q.post(MesKind::Center, MesClose::Timed, "Couldn't get away!");
        let b = q.post(MesKind::TopRightWide, MesClose::Owner, "Blessed Light");
        let dt = 1.0 / 60.0;
        let mut t = 0.0;
        while q.alive(a) {
            q.tick(dt, false);
            t += dt;
        }
        assert!((t - (MES_HOLD + 2.0 * MES_FADE)).abs() < 0.05, "{t}");
        assert!(q.alive(b));
        q.close_owned();
        for _ in 0..20 {
            q.tick(dt, false);
        }
        assert!(!q.alive(b));
        let c = q.post(MesKind::Center, MesClose::Button, "x");
        for _ in 0..10 {
            q.tick(dt, false);
        }
        q.tick(dt, true);
        for _ in 0..10 {
            q.tick(dt, false);
        }
        assert!(!q.alive(c));
    }

    #[test]
    fn message_placement() {
        let g = sh2_menu::gfx::CommandBuffer::default();
        let w = MesWin { id: 0, kind: MesKind::TopRightWide, close: MesClose::Owner, rows: vec!["Cure".into()], icon: false, state: MesState::Open, alpha: 1.0, shown: 0.0 };
        let (x, y, ww, h) = w.rect(&g);
        assert_eq!((ww, h), (128.0, 20.0));
        assert!((x - (512.0 - 148.8)).abs() < 0.01);
        assert_eq!(y, 16.0);
        let w = MesWin { kind: MesKind::Prompt, ..w };
        let (px, py, _, _) = w.rect(&g);
        assert_eq!(py, 392.0);
        assert!(px < 512.0 - 12.8);
        let w = MesWin { kind: MesKind::Ornate, rows: vec!["All ally MP restored by 50%.".into()], ..w };
        assert_eq!(w.rect(&g), (66.0, 343.0, 380.0, 20.0));
    }

    #[test]
    fn win_sequence_order() {
        let pc = ResultPc { pc: 5, rows: rows(), hp_max: 1, mp_max: 1, sp_max: 1, ..Default::default() };
        let mut w = WinSequence::new(data(), ResultScreen::new(vec![pc], 5, 40, 0, false, 0), "Skip".into());
        let dt = 1.0 / 60.0;
        let mut log = Vec::new();
        let mut t: f32 = 0.0;
        while !w.is_done() && t < 30.0 {
            // the result screen waits for the button
            let press = matches!(&w.state, WinState::Screen(s) if s.phase == ResultPhase::WaitEnd);
            for e in w.tick(dt, press) {
                log.push((t, e));
            }
            t += dt;
        }
        assert!(w.is_done());
        let at = |pred: &dyn Fn(&SeqEvent) -> bool| log.iter().find(|(_, e)| pred(e)).map(|(t, _)| *t).expect("event");
        let cam = at(&|e| *e == SeqEvent::Camera);
        let pose = at(&|e| *e == SeqEvent::WinPose);
        let skip = at(&|e| matches!(e, SeqEvent::Message { tag: TAG_SKIP, .. }));
        let fade = at(&|e| matches!(e, SeqEvent::FadeOut(30)));
        let fin = at(&|e| *e == SeqEvent::Finish);
        assert!((cam - 0.5).abs() < 0.02 && (skip - 0.5).abs() < 0.02 && (pose - 0.7).abs() < 0.02, "{cam} {skip} {pose}");
        // panel: starts at 3.7, 0.5 fade + 0.25 step + 10 hold -> fade at ~14.5
        assert!((fade - 14.5).abs() < 0.3, "{fade}");
        assert!(fin > fade + 0.5 + 0.3 + 0.333 + 0.5);
    }

    /// `Retail_CBattle_Phase15_Win` step 5: the panel waits for the end of the victory motion (however long), a button press skips it with the
    /// panel's skip flag set.
    #[test]
    fn win_scene_lasts_as_long_as_the_victory_motion() {
        let pc = ResultPc { pc: 5, rows: rows(), hp_max: 1, mp_max: 1, sp_max: 1, ..Default::default() };
        let mk = || WinSequence::new(data(), ResultScreen::new(vec![pc.clone()], 5, 40, 0, false, 0), "Skip".into());
        let dt = 1.0 / 60.0;
        // the motion keeps playing for 9 s: the pose scene does not end at the 3.7 s stand-in
        let mut w = mk();
        for _ in 0..(9.0 / dt) as usize {
            w.tick_with(dt, false, WinMotion::Playing);
        }
        assert!(matches!(w.state, WinState::Pose), "{:?}", w.state);
        // it ends -> the panel is built, without the skip flag
        w.tick_with(dt, false, WinMotion::Done);
        match &w.state {
            WinState::Bonus(p) => assert!(!p.skip),
            s => panic!("{s:?}"),
        }
        // a button during the pose skips straight through the panel
        let mut w = mk();
        for _ in 0..(1.0 / dt) as usize {
            w.tick_with(dt, false, WinMotion::Playing);
        }
        w.tick_with(dt, true, WinMotion::Playing);
        match &mut w.state {
            WinState::Bonus(p) => {
                assert!(p.skip);
                let mut n = 0;
                while !p.is_done() && n < 600 {
                    p.tick(dt, false);
                    n += 1;
                }
                assert!(n < 120, "the skipped panel passes in {n} ticks");
            }
            s => panic!("{s:?}"),
        }
    }

    #[test]
    fn message_text_strips_the_icon_escape() {
        let t = crate::ui::BtlText { words: vec![], ..Default::default() };
        assert_eq!(message(&t, msg::SKIP, ""), ":Skip");
        let mut t2 = t;
        t2.words = vec![String::new(); 110];
        t2.words[105] = "%i17\u{81}FSkip".into();
        t2.words[108] = "Your chance for a %s-person Combo!".into();
        assert_eq!(message(&t2, msg::SKIP, ""), ":Skip");
        assert_eq!(combo_chance_text(&t2, 2), "Your chance for a ２-person Combo!");
    }
}

#[cfg(test)]
mod tally_sound_tests {
    use super::*;

    /// The count-up loop 0x3000 starts with the count and is released as soon as the counters stop (it used to play on into the field).
    #[test]
    fn the_tally_loop_is_released_when_counting_ends() {
        let mut s = ResultScreen::new(vec![], 0, 500, 0, false, 0);
        let (mut started, mut stopped_at, mut started_at) = (false, None, None);
        for n in 0..1200 {
            s.tick(1.0 / 60.0, false);
            if s.ses.contains(&0x3000) {
                started = true;
                started_at = Some(n);
            }
            if s.stop_ses.contains(&0x3000) {
                stopped_at = Some(n);
                break;
            }
        }
        assert!(started, "the count never started its loop");
        assert!(stopped_at.unwrap() > started_at.unwrap(), "the loop was never released");
        assert!(s.cash_total >= s.cash_target || s.phase != ResultPhase::Count);
    }

    /// Closing the screen while the loop still runs (skip / leave) also releases it.
    #[test]
    fn skipping_the_count_releases_the_loop() {
        let mut s = ResultScreen::new(vec![], 0, 90_000_000, 0, false, 0);
        let mut stops = 0;
        for n in 0..2000 {
            s.tick(1.0 / 60.0, n > 100 && n < 104);
            stops += s.stop_ses.iter().filter(|&&i| i == 0x3000).count();
        }
        assert_eq!(stops, 1, "released exactly once");
    }
}
