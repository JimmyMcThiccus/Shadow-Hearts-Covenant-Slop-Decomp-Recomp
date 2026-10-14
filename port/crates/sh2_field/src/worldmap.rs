//! The world map / "area select" screen: `worldMap`, `worldMapThm`, `worldMapFade`, `worldMapLight`, `worldMapPoint`
//! (JP FIELD.BIN 0x00506be0 .. 0x0050d0d8; notes/G/worldMap.md, notes/integration/worldmap.md).
//!
//! This module is renderer independent: the table of selectable areas (`mTrialMapTbl`, `SUBMAP_DATA`), the per-world scroll limits
//! (`mWorldMapTbl`), the state machine of `worldMap::Polling` (JP 0x005071d0) and the scrolling / cursor logic
//! (`mCheckKey`, `mSearchNext/Prev`, `mSetWorldDest`, `mWorldScroll`).  The Bevy side is [`crate::worldmap_plugin`].
//!
//! Screen: 512x448.  The world picture (768x672 in `WORLDMAP/WMAPn.DAT` entry 4) scrolls so that the selected area sits at screen
//! position (0x170, 0xe0), clamped to the world's scroll limits; a 160 pixel wide panel on the left carries the thumbnail, name and hint of
//! the selected area, a five-row list sits at (0x34, 0x10c).  Circle confirms an area (`FieldMapJump(map, 1)` after `newGameInit`), cross
//! returns to the title (`opening()`).

use bevy::prelude::Resource;
use sh2_core::game::padbit;

/// `WORLDMAP_NAME`: the map name `CFieldSocket::fieldOverlay` compares against to hand over to `worldMap`.
pub const WORLDMAP_NAME: &str = sh2_core::game::FieldRequest::WORLDMAP_NAME;

/// Request for the next visit of the world map (`CFieldSocket::WorldMapJump(world, sub, extra)`; field script op 0x71 or the title's
/// new game).  `world < 0` re-opens the world / selection remembered in the save's `WM` chunk.
#[derive(Resource, Default, Debug, Clone, PartialEq)]
pub struct WorldMapRequest {
    pub world: i32,
    pub sub: i32,
    pub extra: u32,
    pub pending: bool,
    /// the visit starts a new game: confirming an area runs `newGameInit::initializeGameData`
    pub from_title: bool,
}

/// One selectable area (`worldMap::SUBMAP_DATA`, 0x50 bytes at JP `mTrialMapTbl` 0x00554e40).
#[derive(Debug, Clone, PartialEq)]
pub struct SubMap {
    /// +0x00 title (Shift-JIS)
    pub name: Vec<u8>,
    /// +0x20 reading / subtitle (Shift-JIS)
    pub hint: Vec<u8>,
    /// +0x40 field map name
    pub map: String,
    /// +0x48
    pub flag48: u8,
    /// +0x49 thumbnail index (`WMAPn.DAT` entry 10 + index)
    pub thumb: u8,
    /// +0x4a == 0xff: the area can be confirmed
    pub selectable: bool,
    /// +0x4b point id (selection id remembered in the save)
    pub id: i8,
    /// +0x4c / +0x4e position on the world picture
    pub x: i16,
    pub y: i16,
    /// per point state: 1 open, 2 newly unlocked (plays the unlock demo), 3 hidden
    pub state: u8,
    /// `FieldMapJump(map, entry)` entry id used when the area is confirmed (the demo always used 1; retail: the record's third field)
    pub entry: i32,
    /// retail: confirming this point opens world `portal` instead of a field map (list entry byte 1, `-1` = none)
    pub portal: i8,
}

/// Per-world data (`mWorldMapTbl`, 0x30 bytes per world at JP 0x00555580).
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct WorldInfo {
    /// retail: world links (`None` for the demo)
    pub links: Option<RetailLinks>,
    pub mask: u8,
    /// scroll limits: picture width/height minus the visible area
    pub max_scroll_x: i16,
    pub max_scroll_y: i16,
}

/// Retail world record links (`DAT_0060fe94..97`, +0x24..+0x27 of the 0x30 byte world record): `-1` = none.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RetailLinks {
    /// L1 / R1: the world to switch to (Europe <-> Japan)
    pub shoulder: i8,
    /// cross: the parent world (a city map returns to the country map)
    pub back: i8,
    /// the point selected in the parent world after cross
    pub back_point: i8,
    /// the point selected when this world is entered
    pub enter_point: i8,
}

/// The static data of the world map screen read from the JP `FIELD.BIN` overlay.
#[derive(Debug, Clone, Default)]
pub struct WorldMapTable {
    pub worlds: Vec<WorldInfo>,
    pub maps: Vec<SubMap>,
    /// `worldMap_trialNote_J`: one note per area
    pub notes: Vec<Vec<u8>>,
    /// main exe `mMapMenuTbl`: the two button hints ("decide", "back to title")
    pub menu_text: [Vec<u8>; 2],
}

const OVL_BASE: u32 = 0x0043_0a00;
pub const TRIAL_TBL: u32 = 0x0055_4e40;
pub const WORLD_TBL: u32 = 0x0055_5580;
pub const TRIAL_NOTES: u32 = 0x0055_5570;
/// `mMapMenuTbl` entries: "decide" and "back to title" button hints
pub const MENU_TEXT_DECIDE: u32 = 0x0055_ef90;
pub const MENU_TEXT_TITLE: u32 = 0x0055_efa0;

impl WorldMapTable {
    /// Parse the tables out of a JP `FIELD.BIN` image (the file as stored on the disc).
    pub fn from_field_bin(bin: &[u8]) -> Option<Self> {
        if bin.len() < 0x80 || &bin[0..4] != b"MWo3" {
            return None;
        }
        let load = u32::from_le_bytes(bin[8..12].try_into().ok()?);
        if load != OVL_BASE {
            return None;
        }
        let at = |va: u32, n: usize| bin.get((va - load) as usize..(va - load) as usize + n);
        let cstr = |va: u32| -> Option<Vec<u8>> {
            let o = (va.checked_sub(load)?) as usize;
            let s = bin.get(o..)?;
            Some(s[..s.iter().position(|&b| b == 0)?].to_vec())
        };
        let mut t = WorldMapTable::default();
        // worlds
        for w in 0..5 {
            let r = at(WORLD_TBL + w * 0x30, 0x30)?;
            t.worlds.push(WorldInfo {
                links: None,
                mask: r[0x28],
                max_scroll_x: i16::from_le_bytes([r[0x2a], r[0x2b]]),
                max_scroll_y: i16::from_le_bytes([r[0x2c], r[0x2d]]),
            });
        }
        // areas: records until the first with an empty name
        for i in 0..23u32 {
            let r = at(TRIAL_TBL + i * 0x50, 0x50)?;
            if r[0] == 0 {
                break;
            }
            let z = |s: &[u8]| s.iter().position(|&b| b == 0).map(|n| s[..n].to_vec()).unwrap_or_else(|| s.to_vec());
            t.maps.push(SubMap {
                name: z(&r[0..0x20]),
                hint: z(&r[0x20..0x40]),
                map: String::from_utf8_lossy(&z(&r[0x40..0x48])).to_string(),
                flag48: r[0x48],
                thumb: r[0x49],
                selectable: r[0x4a] == 0xff,
                id: r[0x4b] as i8,
                x: i16::from_le_bytes([r[0x4c], r[0x4d]]),
                y: i16::from_le_bytes([r[0x4e], r[0x4f]]),
                state: 1,
                entry: 1,
                portal: -1,
            });
        }
        for i in 0..4u32 {
            let p = u32::from_le_bytes(at(TRIAL_NOTES + i * 4, 4)?.try_into().ok()?);
            t.notes.push(cstr(p).unwrap_or_default());
        }
        // `mMapMenuTbl` (main exe 0x003d8850) points at the two button hints stored in the overlay's string area
        t.menu_text = [cstr(MENU_TEXT_DECIDE).unwrap_or_default(), cstr(MENU_TEXT_TITLE).unwrap_or_default()];
        if t.maps.is_empty() {
            return None;
        }
        Some(t)
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum WmState {
    /// waiting for the texture read (`DVD_CBFunc`) - state 0
    Load,
    /// `worldMapFade::fadeIn(30)`, windows fading in - states 1/2
    FadeIn(u32),
    /// the unlock demo for newly opened points (`mNewPointDemo`, states 6/8): phase 0 pick the next point, 1 scroll to it, 3 the rays play (64 frames),
    /// 4 scroll back to the selection
    NewPoint(u32),
    /// retail states 10..0xd: the first-visit tutorial window (`mSetupTutorialWin`): phase 0 the screen darkens (40 frames), 1 the text is
    /// shown until circle, 2 the window closes (40 frames)
    Tutorial(u32),
    /// state 0x12: the selection loop
    Select,
    /// state 0x13: leaving, fading out
    FadeOut(u32),
    Done,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum WmResult {
    /// state 0x14 with a valid area: `initializeGameData`, `SetSceneInit(index)`, `FieldMapJump(map, entry)`
    Enter { map: String, index: usize, id: i32, entry: i32 },
    /// retail: switch to another world map (`point` = the point to select, `None` = that world's default entry point)
    World { world: i32, point: Option<i32> },
    /// cross: `opening()` (title)
    Title,
}

/// Scroll animation (`mSetWorldScroll`: 24 frames from the current to the destination offset).
#[derive(Debug, Clone, Copy, Default)]
pub struct Scroll {
    pub cur: (f32, f32),
    pub dest: (f32, f32),
    pub step: (f32, f32),
    pub left: u32,
}

#[derive(Debug, Clone)]
pub struct WorldMap {
    pub world: i32,
    pub info: WorldInfo,
    pub maps: Vec<SubMap>,
    pub notes: Vec<Vec<u8>>,
    pub menu_text: [Vec<u8>; 2],
    pub sel: usize,
    pub state: WmState,
    pub scroll: Scroll,
    pub tick: u64,
    /// thumbnail / name fade (0..=1); restarts after every scroll (`worldMapThm::fadeout` + `dispThm`)
    pub thm_alpha: f32,
    pub result: Option<WmResult>,
    /// frames until the next cursor SE etc. (host feedback)
    pub se: Vec<WmSe>,
    /// screen fade (0 = clear, 1 = black)
    pub fade: f32,
    /// the texture read finished
    pub tex_ready: bool,
    /// retail rules: cross / L1 / R1 follow the world links, cross never returns to the title
    pub retail: bool,
    /// `WorldMapJump` extra argument (`+0x18c`): the world links only work when `mask & extra != 0`
    pub extra: u32,
    /// `mNewPointDemo` bookkeeping
    pub demo: NewPointDemo,
    /// `worldMapLight` pulse: the counter (`+0x1c`) and the alpha it drives (`+0x58`)
    pub light_c: i32,
    pub light_a: i32,
    /// retail `+0x1c8`: tutorial text id (0 = the world map screen, first visit ever; 1 = "moving between Europe and Japan", the first time the
    /// jump carries extra bit 3), `None` = nothing to show.  Texts: `WMAPn.DAT` entry 10 strings 0 / 1.
    pub tutorial: Option<u8>,
    pub tutorial_texts: Vec<Vec<u8>>,
    /// frames in the current tutorial phase
    pub tut_t: u32,
}

/// State of the unlock demo (`worldMap +0x8cc` points waiting, `+0x8d4` current point, `+0x8e4` the selection to return to, `+0x5c` frame).
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct NewPointDemo {
    /// points still to be shown (state byte 2)
    pub queue: Vec<usize>,
    /// the point whose rays are playing
    pub point: usize,
    /// the selection before the demo
    pub back: usize,
    /// frame of the ray animation (0..64)
    pub t: u32,
    /// points opened by the demo (their `WM` chunk "new" bit is cleared by the host)
    pub unlocked: Vec<usize>,
}

impl NewPointDemo {
    /// Ray scale and rotation at frame `t` (`mNewPointDemo` state 3): grows 0.5 -> 1 with the rotation 0.01 -> 0.06 for 32 frames, then shrinks.
    pub fn ray(t: u32) -> (f32, f32) {
        if t < 32 {
            (t as f32 * 0.5 / 32.0 + 0.5, t as f32 * 0.05 / 32.0 + 0.01)
        } else {
            let k = (t - 32).min(32) as f32;
            (1.0 - k / 32.0, 0.06 - k * 0.05 / 32.0)
        }
    }
}

/// Sound effects `primSound::play(n)` of the world map: 0 cursor move, 2 decide, 3 cancel, 0x1007 new point.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum WmSe {
    Move,
    Decide,
    Cancel,
    NewPoint,
}

pub const SCREEN_W: f32 = 512.0;
pub const SCREEN_H: f32 = 448.0;
/// where the selected area is placed on screen (`mSetWorldDest`: 0x170, 0xe0)
pub const FOCUS: (f32, f32) = (368.0, 224.0);
pub const SCROLL_FRAMES: u32 = 24;
pub const FADE_FRAMES: u32 = 30;
/// frames of the tutorial veil fade (`+0x10c = 0x28`)
pub const TUTORIAL_FADE: u32 = 40;
/// the tutorial text types one character every this many frames (message window default speed)
pub const TUTORIAL_TYPE_RATE: u32 = 1;

impl WorldMap {
    /// `worldMap::initialize(world, sub, extra)` + `mScriptFilter`: `sub` selects the area whose point id matches (else the first).
    pub fn new(table: &WorldMapTable, world: i32, sub: i32) -> Self {
        let w = world.clamp(0, table.worlds.len().max(1) as i32 - 1);
        let info = table.worlds.get(w as usize).copied().unwrap_or_default();
        let maps = table.maps.clone();
        let sel = maps.iter().position(|m| m.id as i32 == sub).unwrap_or(0);
        let mut wm = WorldMap {
            world: w,
            info,
            maps,
            notes: table.notes.clone(),
            menu_text: table.menu_text.clone(),
            sel,
            state: WmState::Load,
            scroll: Scroll::default(),
            tick: 0,
            thm_alpha: 1.0,
            result: None,
            se: vec![],
            fade: 1.0,
            tex_ready: false,
            retail: info.links.is_some(),
            extra: 0,
            demo: NewPointDemo::default(),
            light_c: 0,
            light_a: 0,
            tutorial: None,
            tutorial_texts: vec![],
            tut_t: 0,
        };
        wm.demo.queue = wm.maps.iter().enumerate().filter(|(_, m)| m.state == 2).map(|(i, _)| i).collect();
        wm.demo.back = wm.sel;
        // mSetWorldPos: no animation for the first position
        let d = wm.world_dest(wm.sel);
        wm.scroll = Scroll { cur: d, dest: d, step: (0.0, 0.0), left: 0 };
        wm
    }

    /// `mSetWorldDest`: map offset that puts area `i` at the focus point, clamped to the world's limits.
    pub fn world_dest(&self, i: usize) -> (f32, f32) {
        let m = &self.maps[i.min(self.maps.len() - 1)];
        let x = (FOCUS.0 as i32 - m.x as i32).clamp(-(self.info.max_scroll_x as i32), 0xa0);
        let y = (FOCUS.1 as i32 - m.y as i32).clamp(-(self.info.max_scroll_y as i32), 0);
        (x as f32, y as f32)
    }

    /// `mSearchNext` / `mSearchPrev`: neighbouring area, skipping hidden points (state 3).
    pub fn search(&self, forward: bool) -> usize {
        let n = self.maps.len();
        let mut i = self.sel;
        for _ in 0..n {
            i = if forward { (i + 1) % n } else { (i + n - 1) % n };
            if self.maps[i].state != 3 {
                return i;
            }
        }
        self.sel
    }

    /// Dev / test hook: mark point `i` as newly unlocked so the `mNewPointDemo` plays when the screen opens.
    pub fn force_new_point(&mut self, i: usize) {
        if i < self.maps.len() {
            self.maps[i].state = 2;
            self.demo.queue = self.maps.iter().enumerate().filter(|(_, m)| m.state == 2).map(|(i, _)| i).collect();
            self.demo.back = self.sel;
        }
    }

    pub fn visible_count(&self) -> usize {
        self.maps.iter().filter(|m| m.state != 3).count()
    }

    fn start_scroll(&mut self) {
        let d = self.world_dest(self.sel);
        self.scroll.dest = d;
        self.scroll.step = ((d.0 - self.scroll.cur.0) / SCROLL_FRAMES as f32, (d.1 - self.scroll.cur.1) / SCROLL_FRAMES as f32);
        self.scroll.left = SCROLL_FRAMES;
        self.thm_alpha = 0.0;
        // `worldMapLight::setDest`: the light restarts its pulse at the new point
        self.light_c = 0;
        self.light_a = 0;
    }

    /// `worldMapLight::Polling` state 2: the glow alpha `+0x58` rises (counter 0..0x40 by 2, then 1 per frame), falls and cycles between 0x20 and 0x40.
    fn pulse_light(&mut self) {
        if self.light_c < 0x40 {
            self.light_c += 2;
            self.light_a += 1;
        } else if self.light_c < 0xc0 {
            self.light_c += 1;
            if self.light_c & 3 == 0 {
                self.light_a += 1;
            }
        } else if self.light_c < 0x140 {
            self.light_c += 1;
            if self.light_c & 3 == 0 {
                self.light_a -= 1;
            }
        } else {
            self.light_c = 0x40;
        }
    }

    pub fn scrolling(&self) -> bool {
        self.scroll.left > 0
    }

    /// Light (cursor sprite) position on screen.
    pub fn point_screen(&self, i: usize) -> (f32, f32) {
        let m = &self.maps[i];
        (m.x as f32 + self.scroll.cur.0, m.y as f32 + self.scroll.cur.1)
    }

    /// The texture read finished (`m_TexRead`): the screen starts fading in.
    pub fn set_ready(&mut self) {
        if self.state == WmState::Load {
            self.tex_ready = true;
            self.state = WmState::FadeIn(FADE_FRAMES);
        }
    }

    /// One 60 Hz tick of `worldMap::Polling` + `mWorldMapPolling`.  `press` = newly pressed pad bits.
    pub fn tick(&mut self, press: u16) {
        self.tick += 1;
        // mWorldScroll
        if self.scroll.left > 0 {
            self.scroll.left -= 1;
            if self.scroll.left == 0 {
                self.scroll.cur = self.scroll.dest;
            } else {
                self.scroll.cur.0 += self.scroll.step.0;
                self.scroll.cur.1 += self.scroll.step.1;
            }
        } else if self.thm_alpha < 1.0 {
            self.thm_alpha = (self.thm_alpha + 1.0 / 8.0).min(1.0);
        }
        match self.state {
            WmState::Load => {}
            WmState::FadeIn(n) => {
                self.fade = n as f32 / FADE_FRAMES as f32;
                if n <= 1 {
                    self.fade = 0.0;
                    self.state = if self.demo.queue.is_empty() { self.enter_select() } else { WmState::NewPoint(0) };
                } else {
                    self.state = WmState::FadeIn(n - 1);
                }
            }
            WmState::NewPoint(phase) => {
                if !self.scrolling() || phase == 3 {
                    self.pulse_light();
                }
                match phase {
                    // pick the next newly unlocked point (state byte 2 -> 1)
                    0 => match self.demo.queue.first().copied() {
                        None => self.state = WmState::NewPoint(4),
                        Some(p) => {
                            self.demo.queue.remove(0);
                            self.maps[p].state = 1;
                            self.demo.unlocked.push(p);
                            self.demo.point = p;
                            if self.sel == p {
                                self.se.push(WmSe::NewPoint);
                                self.demo.t = 0;
                                self.state = WmState::NewPoint(3);
                            } else {
                                self.sel = p;
                                self.start_scroll();
                                self.state = WmState::NewPoint(1);
                            }
                        }
                    },
                    1 => {
                        if !self.scrolling() {
                            self.se.push(WmSe::NewPoint);
                            self.demo.t = 0;
                            self.state = WmState::NewPoint(3);
                        }
                    }
                    3 => {
                        self.demo.t += 1;
                        if self.demo.t >= 64 {
                            self.state = if self.demo.queue.is_empty() { WmState::NewPoint(4) } else { WmState::NewPoint(0) };
                        }
                    }
                    _ => {
                        // back to the selection the player had
                        if self.demo.back != self.sel {
                            self.sel = self.demo.back;
                            self.start_scroll();
                            self.demo.back = self.sel;
                        } else if !self.scrolling() {
                            self.state = self.enter_select();
                        }
                        if !self.scrolling() && self.sel == self.demo.back {
                            self.state = self.enter_select();
                        }
                    }
                }
            }
            WmState::Tutorial(phase) => {
                self.pulse_light();
                self.tut_t += 1;
                match phase {
                    0 => {
                        if self.tut_t >= TUTORIAL_FADE {
                            self.tut_t = 0;
                            self.state = WmState::Tutorial(1);
                        }
                    }
                    1 => {
                        // circle: finish typing, then close (`+0xc` case: the window's line counter, circle)
                        let total = self.tutorial_text_len();
                        if press & padbit::CIRCLE != 0 {
                            if self.tut_t / TUTORIAL_TYPE_RATE < total {
                                self.tut_t = total * TUTORIAL_TYPE_RATE;
                            } else {
                                self.se.push(WmSe::Decide);
                                self.tut_t = 0;
                                self.state = WmState::Tutorial(2);
                            }
                        }
                    }
                    _ => {
                        if self.tut_t >= TUTORIAL_FADE {
                            // `+0x1c8 = -1`: shown once, then the selection loop (state 0x15)
                            self.tutorial = None;
                            self.tut_t = 0;
                            self.state = WmState::Select;
                        }
                    }
                }
            }
            WmState::Select => {
                self.pulse_light();
                if self.scrolling() {
                    // mCheckKey: no input while the map scrolls (`+0x88 != 0`)
                    // (the original still accepts the d-pad queue; one step at a time is enough)
                    return;
                }
                if press & padbit::CIRCLE != 0 {
                    self.se.push(WmSe::Decide);
                    if self.maps[self.sel].selectable && self.maps[self.sel].state != 3 {
                        let m = &self.maps[self.sel];
                        self.result = if m.portal >= 0 {
                            Some(WmResult::World { world: m.portal as i32, point: None })
                        } else {
                            Some(WmResult::Enter { map: m.map.clone(), index: self.sel, id: m.id as i32, entry: m.entry })
                        };
                        self.state = WmState::FadeOut(FADE_FRAMES);
                        return;
                    }
                } else if self.retail {
                    // retail `FUN_00558f80`: L1 / R1 swap the world, cross goes back to the parent world (only when `mask & extra`)
                    let links = self.info.links.unwrap_or(RetailLinks { shoulder: -1, back: -1, back_point: -1, enter_point: -1 });
                    let allowed = self.info.mask as u32 & self.extra != 0;
                    if press & (padbit::L1 | padbit::R1) != 0 && links.shoulder >= 0 && allowed {
                        self.se.push(WmSe::Decide);
                        self.result = Some(WmResult::World { world: links.shoulder as i32, point: None });
                        self.state = WmState::FadeOut(FADE_FRAMES);
                        return;
                    }
                    if press & padbit::CROSS != 0 && links.back >= 0 && allowed {
                        self.se.push(WmSe::Cancel);
                        self.result = Some(WmResult::World { world: links.back as i32, point: Some(links.back_point as i32) });
                        self.state = WmState::FadeOut(FADE_FRAMES);
                        return;
                    }
                } else if press & padbit::CROSS != 0 {
                    self.se.push(WmSe::Cancel);
                    self.result = Some(WmResult::Title);
                    self.state = WmState::FadeOut(FADE_FRAMES);
                    return;
                }
                if self.visible_count() > 1 {
                    if press & padbit::DOWN != 0 {
                        self.se.push(WmSe::Move);
                        self.sel = self.search(true);
                        self.start_scroll();
                    } else if press & padbit::UP != 0 {
                        self.se.push(WmSe::Move);
                        self.sel = self.search(false);
                        self.start_scroll();
                    }
                }
            }
            WmState::FadeOut(n) => {
                self.fade = 1.0 - n as f32 / FADE_FRAMES as f32;
                if n <= 1 {
                    self.fade = 1.0;
                    self.state = WmState::Done;
                } else {
                    self.state = WmState::FadeOut(n - 1);
                }
            }
            WmState::Done => {}
        }
    }

    pub fn done(&self) -> bool {
        self.state == WmState::Done
    }

    /// `Polling` case 10: a pending tutorial opens before the selection loop starts.
    fn enter_select(&mut self) -> WmState {
        if self.tutorial.is_some() && !self.tutorial_texts.is_empty() {
            self.tut_t = 0;
            WmState::Tutorial(0)
        } else {
            self.tutorial = None;
            WmState::Select
        }
    }

    /// number of characters of the tutorial text (typed one per `TUTORIAL_TYPE_RATE` frames)
    pub fn tutorial_text_len(&self) -> u32 {
        self.tutorial.and_then(|t| self.tutorial_texts.get(t as usize)).map(|t| t.len() as u32).unwrap_or(0)
    }
}

/// `worldMap::initialize`: which tutorial (if any) opens with the screen, from the saved flag bits (`WM` chunk word at payload +8, `>> 8`) and the
/// `WorldMapJump` extra argument.  Bit 0 = the screen tutorial was shown (id 0); bit 1 = the "moving between worlds" one (id 1, needs extra bit 3).
pub fn tutorial_for(flags: u8, extra: u32) -> Option<u8> {
    if flags & 1 == 0 {
        Some(0)
    } else if flags & 2 == 0 && extra & 8 != 0 {
        Some(1)
    } else {
        None
    }
}

/// Selection id to remember in the save's `WM` chunk (`GetWorldMapInfo`: `{s16 world, s16 sub, u32 extra}`).
pub fn wm_chunk_value(wm: &WorldMap) -> (i16, i16) {
    (wm.world as i16, wm.maps.get(wm.sel).map(|m| m.id as i16).unwrap_or(0))
}

// ====================================================================================================
// US retail world map (SLUS_210.41 + FIELD.BIN, `SH2US_FIELD.BIN` base 0x0045ea80)
// ====================================================================================================
//
// The retail `worldMap` (`initialize` 0x00557b50, `Polling` 0x00557f30, input 0x00558f80, list builder 0x0055aff0) is the demo's class
// with a progress dependent point list instead of `mTrialMapTbl`:
//
// * `point table`  0x0060ff60: 47 records of 14 bytes `{char map[8], s16 x, s16 y, s16 entry}` indexed by *point id* (record 0 is empty,
//   id 1 = `AP_00_U`, 2 = `DO_04_U` ...); confirming a point runs `FieldMapJump(map, entry as u8)` (0x003f4ea0).
// * `world table` 0x0060fe70: 5 records of 0x30 bytes: `char bgm[0x20]`, `+0x20` pointer to the world's point list, `+0x24 s8` L1/R1 target
//   world, `+0x25 s8` parent world (cross), `+0x26 s8` point selected in the parent, `+0x27 s8` point selected on entry, `+0x28 u8` mask,
//   `+0x2a s16` / `+0x2c s16` scroll limits.  World 0 = Europe, 1 = Japan, 2 = Paris, 3 = Yokohama / Tokyo area, 4 = Petrograd area.
// * point list: `{u8 thumbnail, s8 portal, u8 id, u8 0}` 4 byte entries ended by `id == 0`; `portal != -1` opens that world instead of a map.
// * availability: the save's `WM` chunk keeps one byte per point at payload `+0xc + id`: bit 2 = newly unlocked (plays `mNewPointDemo`),
//   `& 3 == 1` shown greyed (state 3), `& 3 == 2` open (state 1), else the point is not in the list at all.  Script op 0x70 writes it.
// * texts: `WORLDMAP/WMAPn.DAT` entry 11 = message table with `{name, hint}` pairs per point id (`2 * id`, `2 * id + 1`), entry 10 = the
//   screen's own strings (help text, ": Confirm", ": Menu", ": Move to Japan" ...), entries 12.. = 144x128 thumbnails.

pub const US_OVL_BASE: u32 = 0x0045_ea80;
pub const US_POINT_TBL: u32 = 0x0060_ff60;
pub const US_WORLD_TBL: u32 = 0x0060_fe70;
pub const US_POINT_COUNT: usize = 47;
pub const US_WORLD_COUNT: usize = 5;

/// One record of the point table.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RetailPoint {
    /// field map name (empty for the unused ids)
    pub map: String,
    pub x: i16,
    pub y: i16,
    /// `FieldMapJump` entry (low byte of the third field)
    pub entry: i16,
}

/// One entry of a world's point list.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RetailListEntry {
    pub thumb: u8,
    pub portal: i8,
    pub id: u8,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RetailWorld {
    pub bgm: String,
    pub list: Vec<RetailListEntry>,
    pub links: RetailLinks,
    pub mask: u8,
    pub max_scroll_x: i16,
    pub max_scroll_y: i16,
}

/// The retail static data (`FIELD.BIN` overlay).
#[derive(Debug, Clone, Default)]
pub struct RetailWorldTable {
    pub worlds: Vec<RetailWorld>,
    pub points: Vec<RetailPoint>,
}

/// A `msg` entry of a `WMAPn.DAT` bundle: `{u32 count, u16 end_offset[count - 1], strings...}`, strings NUL terminated.
pub fn parse_msg_table(b: &[u8]) -> Vec<Vec<u8>> {
    let Some(n) = b.get(0..4).map(|x| u32::from_le_bytes(x.try_into().unwrap()) as usize) else { return vec![] };
    if n == 0 || n > 4096 {
        return vec![];
    }
    let mut pos = 4 + (n - 1) * 2;
    let mut out = Vec::with_capacity(n);
    for _ in 0..n {
        let Some(rest) = b.get(pos..) else { break };
        let l = rest.iter().position(|&c| c == 0).unwrap_or(rest.len());
        out.push(rest[..l].to_vec());
        pos += l + 1;
    }
    out
}

/// Entry `k` of a `{u32 count, u32 total, {tag, off}[count]}` bundle (as `WMAPn.DAT` / `OPENING.DAT`).
pub fn bundle_entry(b: &[u8], k: usize) -> Option<&[u8]> {
    let n = u32::from_le_bytes(b.get(0..4)?.try_into().ok()?) as usize;
    if k >= n {
        return None;
    }
    let off = |i: usize| -> Option<usize> { Some(u32::from_le_bytes(b.get(12 + i * 8..16 + i * 8)?.try_into().ok()?) as usize) };
    let start = off(k)?;
    let end = if k + 1 < n { off(k + 1)? } else { b.len() };
    b.get(start..end)
}

/// Per point id: the state `worldMap::initialize` derives from the `WM` chunk byte (0 = not in the list, 1 open, 2 new, 3 greyed).
pub fn point_state(wm_byte: u8) -> u8 {
    if wm_byte & 4 != 0 {
        2
    } else if wm_byte & 3 == 1 {
        3
    } else if wm_byte & 3 == 2 {
        1
    } else {
        0
    }
}

impl RetailWorldTable {
    /// Parse the retail tables out of `FIELD.BIN` (load address 0x0045ea80).
    pub fn from_field_bin(bin: &[u8]) -> Option<Self> {
        if bin.len() < 0x80 || &bin[0..4] != b"MWo3" || u32::from_le_bytes(bin[8..12].try_into().ok()?) != US_OVL_BASE {
            return None;
        }
        let at = |va: u32, n: usize| bin.get((va.checked_sub(US_OVL_BASE)?) as usize..(va - US_OVL_BASE) as usize + n);
        let mut t = RetailWorldTable::default();
        for i in 0..US_POINT_COUNT as u32 {
            let r = at(US_POINT_TBL + i * 14, 14)?;
            let n = r[..8].iter().position(|&c| c == 0).unwrap_or(8);
            t.points.push(RetailPoint {
                map: String::from_utf8_lossy(&r[..n]).to_string(),
                x: i16::from_le_bytes([r[8], r[9]]),
                y: i16::from_le_bytes([r[10], r[11]]),
                entry: i16::from_le_bytes([r[12], r[13]]),
            });
        }
        for w in 0..US_WORLD_COUNT as u32 {
            let r = at(US_WORLD_TBL + w * 0x30, 0x30)?;
            let n = r[..0x20].iter().position(|&c| c == 0).unwrap_or(0x20);
            let list_va = u32::from_le_bytes(r[0x20..0x24].try_into().ok()?);
            let mut list = Vec::new();
            for k in 0..64u32 {
                let e = at(list_va + k * 4, 4)?;
                if e[2] == 0 {
                    break;
                }
                list.push(RetailListEntry { thumb: e[0], portal: e[1] as i8, id: e[2] });
            }
            t.worlds.push(RetailWorld {
                bgm: String::from_utf8_lossy(&r[..n]).to_string(),
                list,
                links: RetailLinks { shoulder: r[0x24] as i8, back: r[0x25] as i8, back_point: r[0x26] as i8, enter_point: r[0x27] as i8 },
                mask: r[0x28],
                max_scroll_x: i16::from_le_bytes([r[0x2a], r[0x2b]]),
                max_scroll_y: i16::from_le_bytes([r[0x2c], r[0x2d]]),
            });
        }
        Some(t)
    }

    /// The selectable list of `world` for the given per point `WM` chunk bytes (`wm_bytes[id]`), with the names of `msgs` (`WMAPn.DAT`
    /// entry 11) and the button hints of `ui` (entry 10), as the demo-shaped table [`WorldMap`] runs on.
    pub fn world_table(&self, world: usize, wm_bytes: &dyn Fn(usize) -> u8, msgs: &[Vec<u8>], ui: &[Vec<u8>]) -> Option<WorldMapTable> {
        let w = self.worlds.get(world)?;
        let mut maps = Vec::new();
        for e in &w.list {
            let st = point_state(wm_bytes(e.id as usize));
            if st == 0 {
                continue;
            }
            let p = self.points.get(e.id as usize)?;
            maps.push(SubMap {
                name: msgs.get(e.id as usize * 2).cloned().unwrap_or_default(),
                hint: msgs.get(e.id as usize * 2 + 1).cloned().unwrap_or_default(),
                map: p.map.clone(),
                flag48: 0,
                thumb: e.thumb,
                selectable: true,
                id: e.id as i8,
                x: p.x,
                y: p.y,
                state: st,
                entry: (p.entry & 0xff) as i32,
                portal: e.portal,
            });
        }
        let mut worlds = vec![WorldInfo::default(); self.worlds.len()];
        worlds[world] = WorldInfo { links: Some(w.links), mask: w.mask, max_scroll_x: w.max_scroll_x, max_scroll_y: w.max_scroll_y };
        let ui_str = |i: usize| ui.get(i).cloned().unwrap_or_default();
        let n = maps.len();
        Some(WorldMapTable { worlds, maps, notes: vec![vec![]; n], menu_text: [ui_str(2), ui_str(3)] })
    }
}

#[cfg(test)]
mod tests {
    /// `worldMap::initialize` (US 0x00557b50): the first world map ever shows tutorial 0; tutorial 1 (L1 / R1 between worlds) needs extra bit 3.
    #[test]
    fn tutorial_ids_follow_the_saved_flags() {
        assert_eq!(tutorial_for(0, 0), Some(0));
        assert_eq!(tutorial_for(1, 0), None);
        assert_eq!(tutorial_for(1, 8), Some(1));
        assert_eq!(tutorial_for(3, 8), None);
        assert_eq!(tutorial_for(0, 8), Some(0));
    }

    /// `Polling` cases 10 - 0xd (US 0x00557f30): after the fade-in the tutorial window opens (veil, text, circle), closes, then the selection loop runs.
    #[test]
    fn tutorial_opens_before_the_selection_loop() {
        let t = table();
        let mut wm = WorldMap::new(&t, 0, 0);
        wm.tutorial = Some(0);
        wm.tutorial_texts = vec![b"Tutorial".to_vec()];
        wm.set_ready();
        let mut seen_tutorial = false;
        for _ in 0..200 {
            wm.tick(0);
            seen_tutorial |= matches!(wm.state, WmState::Tutorial(_));
            if matches!(wm.state, WmState::Tutorial(1)) {
                break;
            }
        }
        assert!(seen_tutorial && wm.state == WmState::Tutorial(1));
        // cursor keys do nothing while it is up; circle first completes the typing, then closes the window
        wm.tick(padbit::DOWN);
        assert_eq!(wm.sel, 0);
        wm.tick(padbit::CIRCLE);
        assert!(wm.tut_t >= wm.tutorial_text_len());
        wm.tick(padbit::CIRCLE);
        assert_eq!(wm.state, WmState::Tutorial(2));
        for _ in 0..TUTORIAL_FADE + 2 {
            wm.tick(0);
        }
        assert_eq!(wm.state, WmState::Select);
        assert_eq!(wm.tutorial, None, "shown once");
    }

    use super::*;

    fn table() -> WorldMapTable {
        let mk = |name: &str, map: &str, id: i8, x: i16, y: i16| SubMap {
            name: name.as_bytes().to_vec(),
            hint: vec![],
            map: map.into(),
            flag48: 1,
            thumb: id as u8,
            selectable: true,
            id,
            x,
            y,
            state: 1,
            entry: 1,
            portal: -1,
        };
        WorldMapTable {
            worlds: vec![WorldInfo { mask: 8, max_scroll_x: 256, max_scroll_y: 224, links: None }],
            maps: vec![mk("a", "AP_00_U", 0, 391, 518), mk("b", "AR_00_S", 1, 323, 325), mk("c", "PA_00_S", 2, 289, 351)],
            notes: vec![vec![]; 3],
            menu_text: [vec![], vec![]],
        }
    }

    fn run(wm: &mut WorldMap, n: u32) {
        for _ in 0..n {
            wm.tick(0);
        }
    }

    #[test]
    fn dest_is_clamped_to_the_world_limits() {
        let t = table();
        let wm = WorldMap::new(&t, 0, 0);
        // x: 0x170 - 391 = -23 (inside), y: 0xe0 - 518 = -294 -> clamped to -224
        assert_eq!(wm.world_dest(0), (-23.0, -224.0));
        // y: 224 - 325 = -101
        assert_eq!(wm.world_dest(1), (45.0, -101.0));
    }

    #[test]
    fn select_scrolls_and_confirms() {
        let t = table();
        let mut wm = WorldMap::new(&t, 0, 0);
        wm.set_ready();
        run(&mut wm, FADE_FRAMES + 2);
        assert_eq!(wm.state, WmState::Select);
        wm.tick(padbit::DOWN);
        assert_eq!(wm.sel, 1);
        assert!(wm.scrolling());
        run(&mut wm, SCROLL_FRAMES + 1);
        assert_eq!(wm.scroll.cur, wm.world_dest(1));
        wm.tick(padbit::CIRCLE);
        assert!(matches!(wm.state, WmState::FadeOut(_)));
        run(&mut wm, FADE_FRAMES + 1);
        assert!(wm.done());
        assert_eq!(wm.result, Some(WmResult::Enter { map: "AR_00_S".into(), index: 1, id: 1, entry: 1 }));
    }

    #[test]
    fn cross_returns_to_the_title() {
        let t = table();
        let mut wm = WorldMap::new(&t, 0, 2);
        assert_eq!(wm.sel, 2);
        wm.set_ready();
        run(&mut wm, FADE_FRAMES + 2);
        wm.tick(padbit::CROSS);
        run(&mut wm, FADE_FRAMES + 1);
        assert_eq!(wm.result, Some(WmResult::Title));
    }

    #[test]
    fn hidden_points_are_skipped() {
        let mut t = table();
        t.maps[1].state = 3;
        let wm = WorldMap::new(&t, 0, 0);
        assert_eq!(wm.search(true), 2);
        assert_eq!(wm.search(false), 2);
    }

    #[test]
    fn real_jp_tables_if_present() {
        let Some(dir) = std::env::var_os("SH2_DISC_DIR") else { return };
        let Ok(bytes) = std::fs::read(std::path::Path::new(&dir).join("FIELD.BIN")) else { return };
        let t = WorldMapTable::from_field_bin(&bytes).expect("tables");
        assert_eq!(t.maps.len(), 4);
        assert_eq!(t.maps[0].map, "AP_00_U");
        assert_eq!((t.maps[0].x, t.maps[0].y), (391, 518));
        assert_eq!(t.maps[3].map, "SM_07_U");
        assert!(t.maps.iter().all(|m| m.selectable));
        assert_eq!(t.worlds[0].max_scroll_x, 256);
        assert_eq!(t.worlds[0].max_scroll_y, 224);
    }
}
