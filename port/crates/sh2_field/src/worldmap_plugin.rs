//! Bevy side of the world map (`worldMap` scene object, JP FIELD.BIN 0x00506be0): loads `WORLDMAP/WMAPn.DAT`, runs
//! [`crate::worldmap::WorldMap`] at 60 Hz, draws it through the UI canvas and hands the result to the scene manager.
//!
//! Entered exactly like the original does it: a field request for the map name `WORLDMAP` (`CFieldSocket::fieldOverlay` compares the
//! name against `WORLDMAP_NAME` and calls `WorldMapJumpA`) or a script's `WorldMapJump` (op 0x71).  Leaving: circle on an area
//! (`newGameInit::initializeGameData`, `SetSceneInit`, `FieldMapJump(map, 1)`), cross -> title (`opening()`).

use ::bevy::prelude::*;

use sh2_core::app::AppConfig;
use sh2_core::game::{FieldRequest, GamePad, GameSet, Scene};
use sh2_core::ssh_sys::{SshApi, SshSys};
use sh2_gfx::texture::{decode_menu_texture, Rgba8Image};
use sh2_menu::bevy_ui::{self, layer, UiCanvas, UiTextures};
use sh2_menu::gfx::{MenuSe, Rgba};
use sh2_menu::session::GameSession;
use sh2_menu::sjis;

use crate::host::FieldAudio;
use crate::plugin::{FieldAudioQueue, FieldData};
use crate::worldmap::{bundle_entry, parse_msg_table, RetailWorldTable, WmResult, WmSe, WmState, WorldMap, WorldMapRequest, WorldMapTable, WORLDMAP_NAME};

/// Texture ids of one `WMAPn.DAT` (entry numbers of the bundle).
#[derive(Default, Clone)]
pub struct WmTextures {
    /// 4: the world picture (768x672)
    pub map: Option<u32>,
    /// 1: spotlight vignette (216x216, black with alpha)
    pub spot: Option<u32>,
    /// 2: glow (64x64)
    pub glow: Option<u32>,
    /// 3 (left half): sun icon of the selected point; (right half): ring icon of the other points
    pub sun: Option<u32>,
    pub ring: Option<u32>,
    /// 10..: thumbnails 144x128
    pub thumbs: Vec<u32>,
    /// 8: "ふろく版" logo
    pub logo: Option<u32>,
}

#[derive(Resource)]
pub struct WorldMapRuntime {
    pub wm: WorldMap,
    pub tex: WmTextures,
    pub from_title: bool,
    /// tick of the scene (for the texture "read" delay and animations)
    pub ticks: u64,
    /// nothing to show (no table): continue to this map at once
    pub passthrough: Option<String>,
    pub handled: bool,
}

fn disc_root(cfg: Option<&AppConfig>) -> std::path::PathBuf {
    if let Some(d) = std::env::var_os("SH2_DISC_DIR") {
        return d.into();
    }
    cfg.map(|c| c.disc_dir.clone()).unwrap_or_else(|| ".".into())
}

fn crop(img: &Rgba8Image, x: u32, y: u32, w: u32, h: u32) -> Rgba8Image {
    let mut out = Rgba8Image::new(w, h);
    for yy in 0..h {
        for xx in 0..w {
            let p = img.px(x + xx, y + yy);
            let o = ((yy * w + xx) * 4) as usize;
            out.pixels[o..o + 4].copy_from_slice(&p);
        }
    }
    out
}

/// Additive sprites (`setBlendMode(1)`) carry no alpha: black is transparent.
fn black_to_alpha(img: &mut Rgba8Image) {
    for p in img.pixels.chunks_mut(4) {
        p[3] = p[0].max(p[1]).max(p[2]);
    }
}

fn load_bundle_entry(b: &[u8], k: usize) -> Option<Rgba8Image> {
    let o = 8 + k * 8;
    let off = u32::from_le_bytes(b.get(o + 4..o + 8)?.try_into().ok()?) as usize;
    decode_menu_texture(b, off).ok()
}

/// Decode and register the textures of `WMAPn.DAT`.
pub fn load_textures(bundle: &[u8], textures: &mut UiTextures, images: &mut Assets<Image>) -> WmTextures {
    load_textures_from(bundle, textures, images, 10)
}

/// `thumb_base`: first thumbnail entry (demo bundles: 10, retail: 12 -- entries 10 / 11 are message tables there).
pub fn load_textures_from(bundle: &[u8], textures: &mut UiTextures, images: &mut Assets<Image>, thumb_base: usize) -> WmTextures {
    let mut t = WmTextures::default();
    let mut add = |img: Rgba8Image, tx: &mut UiTextures| tx.add(images, img.width, img.height, img.pixels);
    t.map = load_bundle_entry(bundle, 4).map(|i| add(i, textures));
    t.spot = load_bundle_entry(bundle, 1).map(|i| add(i, textures));
    // the ray sprite (64x64, bright corner at the bottom right) carries its own alpha channel
    t.glow = load_bundle_entry(bundle, 2).map(|i| add(i, textures));
    if let Some(mut icons) = load_bundle_entry(bundle, 3) {
        black_to_alpha(&mut icons);
        t.sun = Some(add(crop(&icons, 0, 0, 16, 16), textures));
        t.ring = Some(add(crop(&icons, 16, 0, 16, 16), textures));
    }
    t.logo = load_bundle_entry(bundle, 8).map(|i| add(i, textures));
    let n = u32::from_le_bytes(bundle.get(0..4).and_then(|x| x.try_into().ok()).unwrap_or([0; 4])) as usize;
    for k in thumb_base..n.min(thumb_base + 40) {
        match load_bundle_entry(bundle, k) {
            Some(i) => t.thumbs.push(add(i, textures)),
            None => break,
        }
    }
    t
}

#[allow(clippy::too_many_arguments)]
fn enter_worldmap(
    mut commands: Commands,
    req: Res<FieldRequest>,
    mut wm_req: ResMut<WorldMapRequest>,
    data: Option<Res<FieldData>>,
    cfg: Option<Res<AppConfig>>,
    session: Res<GameSession>,
    mut textures: Option<ResMut<UiTextures>>,
    mut images: Option<ResMut<Assets<Image>>>,
    mut audio: ResMut<FieldAudioQueue>,
    mut pad: ResMut<GamePad>,
) {
    if req.map != WORLDMAP_NAME {
        return;
    }
    pad.swallow();
    let from_title = wm_req.from_title || session.needs_party_init;
    // `WorldMapJumpA(-1)`: reopen with the world / selection remembered in the save (WM chunk: {s16 world, s16 sub, u32 extra})
    let (mut world, mut sub) = (wm_req.world, wm_req.sub);
    if !wm_req.pending || world < 0 {
        let (w, s) = session
            .save
            .field
            .find(sh2_menu::save::FieldSave::TAG_WM)
            .map(|c| (i16::from_le_bytes([c.payload[0], c.payload[1]]) as i32, i16::from_le_bytes([c.payload[2], c.payload[3]]) as i32))
            .unwrap_or((0, 0));
        world = w;
        sub = s;
    }
    let wm_req_extra = if wm_req.pending { wm_req.extra } else { 0 };
    *wm_req = WorldMapRequest::default();
    let root = disc_root(cfg.as_deref());
    if sh2_core::boot::is_retail() {
        let saved_extra = wm_chunk_extra(&session);
        let extra = if wm_req_extra != 0 { wm_req_extra } else { saved_extra };
        match build_retail(&root, world, sub, extra, &session, data.as_deref(), textures.as_deref_mut(), images.as_deref_mut(), &mut audio) {
            Some(rt) => {
                commands.insert_resource(rt);
                return;
            }
            None => log::warn!("world map: no retail point list available, continuing to {}", FieldRequest::FIRST_MAP),
        }
        commands.insert_resource(passthrough_runtime(false));
        return;
    }
    let table = std::fs::read(root.join("FIELD.BIN")).ok().and_then(|b| WorldMapTable::from_field_bin(&b)).filter(|_| std::env::var_os("SH2_SKIP_WORLDMAP").is_none());
    let Some(table) = table else {
        // no trial table: nothing to choose from, go to the first map
        log::warn!("world map: no area table in FIELD.BIN, continuing to {}", FieldRequest::FIRST_MAP);
        commands.insert_resource(passthrough_runtime(from_title));
        return;
    };
    let mut wm = WorldMap::new(&table, world, sub);
    if let Some(n) = std::env::var("SH2_WM_UNLOCK").ok().and_then(|v| v.parse::<usize>().ok()) {
        // dev: pretend point `n` was just unlocked by the story (plays `mNewPointDemo`)
        wm.force_new_point(n);
    }
    let mut tex = WmTextures::default();
    if let (Some(d), Some(tx), Some(im)) = (data.as_deref(), textures.as_deref_mut(), images.as_deref_mut()) {
        if let Some(b) = d.pkb.read(&format!("WORLDMAP/WMAP{}.DAT", wm.world)) {
            tex = load_textures(&b, tx, im);
        }
    }
    // `primMusic::play("BGM601.SSQ")`
    sh2_audio::post(sh2_audio::AudioRequest::LoadBgm { name: "BGM601".into() });
    sh2_audio::post(sh2_audio::AudioRequest::PlayBgm { index: 0, mode: 0 });
    audio.0.push(FieldAudio::LoadBgm("BGM601".into()));
    log::info!("world map: world {} selection {} ({} areas)", wm.world, wm.sel, wm.maps.len());
    commands.insert_resource(WorldMapRuntime { wm, tex, from_title, ticks: 0, passthrough: None, handled: false });
}

/// `{s16 world, s16 sub, u32 extra}` of the `WM` chunk: the `extra` word.
fn wm_chunk_extra(session: &GameSession) -> u32 {
    session.save.field.find(sh2_menu::save::FieldSave::TAG_WM).and_then(|c| c.payload.get(4..8)).map(|b| u32::from_le_bytes(b.try_into().unwrap())).unwrap_or(0)
}

fn passthrough_runtime(from_title: bool) -> WorldMapRuntime {
    WorldMapRuntime {
        wm: WorldMap::new(
            &WorldMapTable {
                worlds: vec![Default::default()],
                maps: vec![crate::worldmap::SubMap { name: vec![], hint: vec![], map: FieldRequest::FIRST_MAP.into(), flag48: 0, thumb: 0, selectable: true, id: 0, x: 0, y: 0, state: 1, entry: 1, portal: -1 }],
                notes: vec![],
                menu_text: [vec![], vec![]],
            },
            0,
            0,
        ),
        tex: WmTextures::default(),
        from_title,
        ticks: 0,
        passthrough: Some(FieldRequest::FIRST_MAP.to_string()),
        handled: false,
    }
}

/// The retail screen for `world` / `sub` (= point id): point list, availability and names from the overlay, `WM` chunk and `WMAPn.DAT`.
/// A world without any unlocked point falls back to the first world that has one.
#[allow(clippy::too_many_arguments)]
pub fn build_retail(
    root: &std::path::Path,
    world: i32,
    sub: i32,
    extra: u32,
    session: &GameSession,
    data: Option<&FieldData>,
    textures: Option<&mut UiTextures>,
    images: Option<&mut Assets<Image>>,
    audio: &mut FieldAudioQueue,
) -> Option<WorldMapRuntime> {
    let bin = std::fs::read(root.join("FIELD.BIN")).ok()?;
    let rt = RetailWorldTable::from_field_bin(&bin)?;
    let wm_chunk = session.save.field.find(sh2_menu::save::FieldSave::TAG_WM);
    let byte = |id: usize| wm_chunk.and_then(|c| c.payload.get(0xc + id).copied()).unwrap_or(0);
    let data = data?;
    let order: Vec<usize> = std::iter::once(world.clamp(0, 4) as usize).chain(0..5).collect();
    for w in order {
        let bundle = data.pkb.read(&format!("WORLDMAP/WMAP{w}.DAT"))?;
        let msgs = bundle_entry(&bundle, 11).map(parse_msg_table).unwrap_or_default();
        let ui = bundle_entry(&bundle, 10).map(parse_msg_table).unwrap_or_default();
        let Some(table) = rt.world_table(w, &byte, &msgs, &ui) else { continue };
        if table.maps.is_empty() {
            continue;
        }
        let mut wm = WorldMap::new(&table, w as i32, sub);
        wm.extra = extra;
        // `worldMap::initialize`: the tutorial flags live in the `WM` chunk word at payload +8 (`flags << 8`)
        let flags = wm_chunk.and_then(|c| c.payload.get(9).copied()).unwrap_or(0);
        wm.tutorial = crate::worldmap::tutorial_for(flags, extra);
        wm.tutorial_texts = ui.iter().take(2).cloned().collect();
        // points whose state byte is 2 ("new") play the unlock demo `mNewPointDemo` (`WorldMap::new` queues them); `SH2_WM_UNLOCK=<index>` forces one
        if let Some(n) = std::env::var("SH2_WM_UNLOCK").ok().and_then(|v| v.parse::<usize>().ok()) {
            wm.force_new_point(n);
        }
        let mut tex = WmTextures::default();
        if let (Some(tx), Some(im)) = (textures, images) {
            tex = load_textures_from(&bundle, tx, im, 12);
        }
        let bgm = rt.worlds[w].bgm.split('.').next().unwrap_or("BGM601").to_string();
        sh2_audio::post(sh2_audio::AudioRequest::LoadBgm { name: bgm.clone() });
        sh2_audio::post(sh2_audio::AudioRequest::PlayBgm { index: 0, mode: 0 });
        audio.0.push(FieldAudio::LoadBgm(bgm));
        log::info!("world map (retail): world {} selection {} ({} points, extra {extra:#x})", wm.world, wm.sel, wm.maps.len());
        return Some(WorldMapRuntime { wm, tex, from_title: false, ticks: 0, passthrough: None, handled: false });
    }
    None
}

/// The picture, spotlight, points and rays go to a *sprite* layer: only those are meshes with real UVs / rotations (the spotlight quarters are
/// mirrored copies of one texture, the rays are rotated), the Bevy UI layers can only draw axis-aligned unflipped images.  The windows and texts (layer
/// `FIELD`, a UI layer) stay above it.
const WM_SCENE: u8 = layer::SPRITE_BASE + 2;

fn exit_worldmap(mut commands: Commands, mut canvas: ResMut<UiCanvas>) {
    commands.remove_resource::<WorldMapRuntime>();
    for l in [WM_SCENE, layer::SCENE, layer::FIELD, layer::FADER] {
        canvas.clear(l);
    }
}

fn sj(b: &[u8]) -> String {
    sjis::decode(b)
}

/// One mirrored quarter of the spotlight vignette (`flip_u` / `flip_v` mirror the 216 x 216 texture).
fn spot_quarter(g: &mut dyn sh2_menu::gfx::MenuGfx, tex: sh2_menu::gfx::TextureId, x: f32, y: f32, flip_u: bool, flip_v: bool, alpha: u8) {
    use sh2_menu::gfx::{Blend, DrawCmd, Vertex};
    let c = Rgba::new(0x80, 0x80, 0x80, alpha);
    let (u0, u1) = if flip_u { (1.0, 0.0) } else { (0.0, 1.0) };
    let (v0, v1) = if flip_v { (1.0, 0.0) } else { (0.0, 1.0) };
    let v = |px: f32, py: f32, u: f32, vv: f32| Vertex { pos: glam::Vec2::new(px, py), uv: glam::Vec2::new(u, vv), color: c };
    g.draw(DrawCmd::Quad { tex: Some(tex), v: [v(x, y, u0, v0), v(x, y + 216.0, u0, v1), v(x + 216.0, y, u1, v0), v(x + 216.0, y + 216.0, u1, v1)], blend: Blend::Alpha });
}

/// A square sprite of side `size` whose bottom-right corner is the pivot `(px, py)`, turned by `angle` radians around it.
fn ray_sprite(g: &mut dyn sh2_menu::gfx::MenuGfx, tex: sh2_menu::gfx::TextureId, px: f32, py: f32, size: f32, angle: f32) {
    use sh2_menu::gfx::{Blend, DrawCmd, Vertex};
    let c = Rgba::new(0x80, 0x80, 0x80, 0x80);
    let (sn, cs) = angle.sin_cos();
    let rot = |lx: f32, ly: f32| glam::Vec2::new(px + lx * cs - ly * sn, py + lx * sn + ly * cs);
    let v = |lx: f32, ly: f32, u: f32, vv: f32| Vertex { pos: rot(lx, ly), uv: glam::Vec2::new(u, vv), color: c };
    g.draw(DrawCmd::Quad { tex: Some(tex), v: [v(-size, -size, 0.0, 0.0), v(-size, 0.0, 0.0, 1.0), v(0.0, -size, 1.0, 0.0), v(0.0, 0.0, 1.0, 1.0)], blend: Blend::Alpha });
}

fn draw(rt: &WorldMapRuntime, canvas: &mut UiCanvas) {
    let wm = &rt.wm;
    let t = &rt.tex;
    {
        // layer SCENE: the picture, the spotlight, the points
        let mut g = canvas.begin(WM_SCENE);
        bevy_ui::rect(&mut g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, 0x80));
        if let Some(m) = t.map {
            bevy_ui::image(&mut g, m, wm.scroll.cur.0, wm.scroll.cur.1, 768.0, 672.0, 0x80);
        }
        let (lx, ly) = if wm.maps.is_empty() { (0.0, 0.0) } else { wm.point_screen(wm.sel) };
        // spotlight vignette around the selected point: four mirrored 216x216 quarters + four black fillers (`worldMapLight`)
        // the pulse of `worldMapLight::Polling`: the black fillers have alpha 0x80 - a, the glow a * 2 (a cycles between 0x20 and 0x40)
        let a = (0x80 - wm.light_a).clamp(0, 0x80) as u8;
        let glow = (wm.light_a * 2).clamp(0, 0x80) as u8;
        // four black fillers outside the 432 x 432 square around the point (`worldMapLight::setPos`)
        let black = Rgba::new(0, 0, 0, a);
        bevy_ui::rect(&mut g, 0.0, ly - 216.0 - 256.0, 512.0, 256.0, black);
        bevy_ui::rect(&mut g, 0.0, ly + 216.0, 512.0, 256.0, black);
        bevy_ui::rect(&mut g, lx - 216.0 - 256.0, ly - 216.0, 256.0, 432.0, black);
        bevy_ui::rect(&mut g, lx + 216.0, ly - 216.0, 256.0, 432.0, black);
        if let Some(s) = t.spot {
            // the 216 x 216 texture is one quarter of the vignette (opaque black at the top left, clear at the bottom right); the four sprites of
            // `worldMapLight::select` mirror it (`setUV(0xd7, 1, 0, 0xd8)` ...) around the point
            spot_quarter(&mut g, s, lx - 216.0, ly - 216.0, false, false, a);
            spot_quarter(&mut g, s, lx, ly - 216.0, true, false, a);
            spot_quarter(&mut g, s, lx - 216.0, ly, false, true, a);
            spot_quarter(&mut g, s, lx, ly, true, true, a);
        }
        // points
        let pulse = 0.5 + 0.5 * (wm.tick as f32 * 0.12).sin();
        for (i, m) in wm.maps.iter().enumerate() {
            if m.state == 3 {
                continue;
            }
            let (px, py) = wm.point_screen(i);
            if i == wm.sel {
                if let Some(sun) = t.sun {
                    // soft halo (the glow of `worldMapLight`): the sun icon enlarged and faint, then the icon itself
                    let s = 26.0 + 8.0 * pulse;
                    bevy_ui::image(&mut g, sun, px - s / 2.0, py - s / 2.0, s, s, glow / 2);
                    bevy_ui::image(&mut g, sun, px - 8.0, py - 8.0, 16.0, 16.0, 0x80);
                } else {
                    bevy_ui::rect(&mut g, px - 4.0, py - 4.0, 8.0, 8.0, Rgba::new(0xff, 0xd0, 0x40, 0x80));
                }
            } else if let Some(r) = t.ring {
                bevy_ui::image(&mut g, r, px - 8.0, py - 8.0, 16.0, 16.0, 0x60);
            } else {
                bevy_ui::rect(&mut g, px - 3.0, py - 3.0, 6.0, 6.0, Rgba::new(0xd0, 0x40, 0x40, 0x70));
            }
        }
        // `mNewPointDemo`: four prim2D copies of the ray sprite (64x64, bright corner anchored on the point, `setCenterMode(4)`), copy i rotated by
        // i * pi / 2 plus the small animated angle, scale 0.5 -> 1 -> 0 (`rot` 0.01 -> 0.06 -> 0.01) over 64 frames
        if wm.state == WmState::NewPoint(3) {
            let (scale, rot) = crate::worldmap::NewPointDemo::ray(wm.demo.t);
            let (px, py) = wm.point_screen(wm.demo.point);
            if let Some(gl) = t.glow {
                for i in 0..4 {
                    ray_sprite(&mut g, gl, px, py, 64.0 * scale, i as f32 * std::f32::consts::FRAC_PI_2 + rot);
                }
            }
        }
        // left panel (160 px, dark) with a soft edge
        bevy_ui::rect(&mut g, 0.0, 0.0, 160.0, 448.0, Rgba::new(0, 0, 0, 0x80));
        for k in 0..20 {
            let a = (0x80 as f32 * (1.0 - k as f32 / 20.0)) as u8;
            bevy_ui::rect(&mut g, 160.0 + k as f32 * 4.0, 0.0, 4.0, 448.0, Rgba::new(0, 0, 0, a));
        }
    }
    let mut g = canvas.begin(layer::FIELD);
    if wm.maps.is_empty() {
        return;
    }
    let alpha = (wm.thm_alpha.clamp(0.0, 1.0) * 128.0) as u8;
    // thumbnail (`worldMapThm`): entry 10 + thumb index at (56, 53)
    let cur = &wm.maps[wm.sel];
    if let Some(&th) = t.thumbs.get(cur.thumb as usize) {
        bevy_ui::image(&mut g, th, 20.0, 40.0, 144.0, 128.0, alpha);
    }
    // name / hint centred at x = 128 (rows 208 / 230)
    let nm = sj(&cur.name);
    let hint = sj(&cur.hint);
    let ncol = Rgba::new(0x80, 0x90, 0xc0, alpha);
    bevy_ui::text(&mut g, 80.0 - nm.chars().count() as f32 * 6.5, 176.0, &nm, 0, ncol, true);
    bevy_ui::text(&mut g, 80.0 - hint.chars().count() as f32 * 4.0, 198.0, &hint, 1, Rgba::new(0x80, 0x80, 0x80, alpha), true);
    // list window (`mSetupSelectWin`): five rows of 22 px at (52, 268), scrolled so the selection stays visible
    let first = wm.sel.saturating_sub(4).min(wm.maps.len().saturating_sub(5));
    bevy_ui::panel(&mut g, 36.0, 260.0, 270.0, 124.0, 0x60);
    for (row, i) in (first..wm.maps.len().min(first + 5)).enumerate() {
        let m = &wm.maps[i];
        let y = 270.0 + row as f32 * 22.0;
        let sel = i == wm.sel;
        if sel {
            bevy_ui::rect(&mut g, 44.0, y - 2.0, 254.0, 22.0, Rgba::new(0x50, 0x50, 0xa0, 0x50));
        }
        let c = if m.state == 3 {
            Rgba::new(0x40, 0x40, 0x40, 0x60)
        } else if sel {
            Rgba::new(0x80, 0x80, 0x30, 0x80)
        } else {
            Rgba::NEUTRAL
        };
        bevy_ui::text(&mut g, 52.0, y, &sj(&m.name), 0, c, true);
        if sel {
            bevy_ui::text(&mut g, 36.0, y, ">", 0, c, false);
        }
    }
    // note of the area and the button hints (bottom bar)
    bevy_ui::rect(&mut g, 0.0, 414.0, 512.0, 34.0, Rgba::new(0, 0, 0, 0x50));
    if let Some(n) = wm.notes.get(wm.sel) {
        bevy_ui::text(&mut g, 16.0, 420.0, &sj(n), 1, Rgba::NEUTRAL, true);
    }
    bevy_ui::text(&mut g, 380.0, 370.0, &format!("\u{25cb}{}", sj(&wm.menu_text[0])), 1, Rgba::NEUTRAL, true);
    bevy_ui::text(&mut g, 380.0, 392.0, &format!("{}{}", if wm.retail { "\u{25b3}" } else { "\u{00d7}" }, sj(&wm.menu_text[1])), 1, Rgba::NEUTRAL, true);
    if let Some(l) = t.logo {
        bevy_ui::image(&mut g, l, 360.0, 6.0, 136.0, 48.0, 0x60);
    }
    drop(g);
    if let WmState::Tutorial(phase) = wm.state {
        // `mSetupTutorialWin`: a full-screen veil (alpha 0x40 over the map) and a window at (0x60, 0x9b) 0x140 x 0x8a with the text
        let k = match phase {
            0 => wm.tut_t as f32 / crate::worldmap::TUTORIAL_FADE as f32,
            1 => 1.0,
            _ => 1.0 - wm.tut_t as f32 / crate::worldmap::TUTORIAL_FADE as f32,
        }
        .clamp(0.0, 1.0);
        let mut g = canvas.begin(layer::FIELD);
        bevy_ui::rect(&mut g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, (0x40 as f32 * k) as u8));
        if phase >= 1 {
            let a = if phase == 1 { 1.0 } else { k };
            crate::fscreen::window(&mut g, 96.0, 155.0, 320.0, 138.0, a);
            if let Some(t) = wm.tutorial.and_then(|t| wm.tutorial_texts.get(t as usize)) {
                // `%i16` is the triangle button icon
                let txt = sj(t).replace("%i16", "\u{25b3}");
                let shown: String = if phase == 1 { txt.chars().take((wm.tut_t / crate::worldmap::TUTORIAL_TYPE_RATE) as usize + 12).collect() } else { txt };
                let wrapped = crate::fscreen::wrap_text(&shown, 38);
                crate::fscreen::coded_text(&mut g, 106.0, 163.0, &wrapped, 1, Rgba::new(255 as u8, 255, 255, (255.0 * a) as u8), 16.0, true);
            }
        }
        drop(g);
    }
    let mut f = canvas.begin(layer::FADER);
    if wm.fade > 0.001 {
        bevy_ui::rect(&mut f, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, (wm.fade * 128.0) as u8));
    }
}

#[allow(clippy::too_many_arguments)]
fn worldmap_tick(
    pad: Res<GamePad>,
    rt: Option<ResMut<WorldMapRuntime>>,
    mut canvas: ResMut<UiCanvas>,
    mut session: ResMut<GameSession>,
    mut sys: ResMut<SshSys>,
    mut field_req: ResMut<FieldRequest>,
    mut commands: Commands,
    data: Option<Res<FieldData>>,
    cfg: Option<Res<AppConfig>>,
    mut textures: Option<ResMut<UiTextures>>,
    mut images: Option<ResMut<Assets<Image>>>,
    mut audio: ResMut<FieldAudioQueue>,
    mut menu: ResMut<crate::menu_overlay::InGameMenu>,
) {
    let Some(mut rt) = rt else { return };
    let rt = &mut *rt;
    // the command menu opened with triangle (state 0xc: `CmdMenu` page 0 over the map, `worldMap::CMN` callback): the map waits
    if menu.open || menu.request {
        return;
    }
    rt.ticks += 1;
    if rt.ticks == 1 {
        if let Some(id) = rt.wm.tutorial.filter(|_| rt.wm.retail) {
            // the flag is set when the screen opens, so the tutorial is shown once (`initialize`: `flags |= 1` / `flags |= 2`)
            if let Some(c) = session.save.field.find_mut(sh2_menu::save::FieldSave::TAG_WM) {
                if let Some(b) = c.payload.get_mut(9) {
                    *b |= 1 | ((id & 1) << 1);
                }
            }
        }
    }
    // the texture read of `mReadDataRequest` completes after a couple of frames
    if rt.ticks == 2 {
        rt.wm.set_ready();
    }
    if let Some(map) = rt.passthrough.clone() {
        if !rt.handled {
            rt.handled = true;
            leave_to(&map, 0, rt.from_title, &mut session, &mut sys, &mut field_req);
        }
        return;
    }
    // triangle in the selection loop: `mCheckKey` returns 0xc -> `new CmdMenu(0, CMN, this)` (the party exists once the game has started)
    if rt.wm.state == WmState::Select && !rt.wm.scrolling() && pad.press() & sh2_core::game::padbit::TRIANGLE != 0 && !session.needs_party_init && !rt.from_title {
        canvas.ses.push(MenuSe::Decide);
        menu.request = true;
        return;
    }
    rt.wm.tick(pad.press());
    // the unlock demo opened these points: the "new" bit of their `WM` chunk byte is cleared (`+0x129 = 1`)
    for p in std::mem::take(&mut rt.wm.demo.unlocked) {
        let id = rt.wm.maps.get(p).map(|m| m.id).unwrap_or(-1);
        if id >= 0 {
            if let Some(c) = session.save.field.find_mut(sh2_menu::save::FieldSave::TAG_WM) {
                if let Some(b) = c.payload.get_mut(0xc + id as usize) {
                    *b &= !4;
                }
            }
        }
    }
    for se in std::mem::take(&mut rt.wm.se) {
        canvas.ses.push(match se {
            WmSe::Move => MenuSe::CursorMove,
            WmSe::Decide => MenuSe::Decide,
            WmSe::Cancel => MenuSe::Cancel,
            WmSe::NewPoint => MenuSe::Other(0x1007),
        });
    }
    draw(rt, &mut canvas);
    if rt.wm.state == WmState::Done && !rt.handled {
        rt.handled = true;
        // remember the selection in the save's WM chunk (`GetWorldMapInfo`)
        let (w, s) = crate::worldmap::wm_chunk_value(&rt.wm);
        if let Some(c) = session.save.field.find_mut(sh2_menu::save::FieldSave::TAG_WM) {
            c.payload[0..2].copy_from_slice(&w.to_le_bytes());
            c.payload[2..4].copy_from_slice(&s.to_le_bytes());
        }
        match rt.wm.result.clone() {
            Some(WmResult::Enter { map, index, id, entry }) => {
                log::info!("world map: area {index} (point {id}) -> {map} (entry {entry})");
                leave_to(&map, entry, rt.from_title, &mut session, &mut sys, &mut field_req);
            }
            Some(WmResult::World { world, point }) => {
                // retail: another world map (portal / L1 / R1 / cross)
                let root = disc_root(cfg.as_deref());
                let extra = rt.wm.extra;
                let sub = point.unwrap_or_else(|| retail_enter_point(&root, world));
                match build_retail(&root, world, sub, extra, &session, data.as_deref(), textures.as_deref_mut(), images.as_deref_mut(), &mut audio) {
                    Some(next) if next.wm.world == world => {
                        log::info!("world map: -> world {world} point {sub}");
                        commands.insert_resource(next);
                        return;
                    }
                    _ => {
                        // that world has nothing unlocked yet: stay where we are
                        log::info!("world map: world {world} is empty, staying");
                        rt.wm.result = None;
                        rt.wm.state = WmState::Select;
                        rt.wm.fade = 0.0;
                        rt.handled = false;
                    }
                }
            }
            Some(WmResult::Title) | None => {
                log::info!("world map: back to the title");
                sys.set_api(SshApi::DummyStage);
            }
        }
    }
}

/// `DAT_0060fe97[world * 0x30]`: the point selected when a world is entered through a portal / L1 / R1.
fn retail_enter_point(root: &std::path::Path, world: i32) -> i32 {
    std::fs::read(root.join("FIELD.BIN"))
        .ok()
        .and_then(|b| RetailWorldTable::from_field_bin(&b))
        .and_then(|t| t.worlds.get(world.max(0) as usize).map(|w| w.links.enter_point as i32))
        .unwrap_or(0)
}

/// State 0x14 of `worldMap::Polling`: `newGameInit::initializeGameData`, `SetSceneInit(index)`, `FieldMapJump(map, entry)`.
fn leave_to(map: &str, entry: i32, from_title: bool, session: &mut GameSession, sys: &mut SshSys, field_req: &mut FieldRequest) {
    if from_title {
        // initializeGameData: a fresh save block; the starting party is created by the battle side (`SetSceneInit`)
        session.new_game(map);
    }
    session.map = map.to_string();
    field_req.map = map.to_string();
    field_req.entry = entry;
    sys.set_api(SshApi::FieldSocket);
}

pub struct WorldMapPlugin;

impl Plugin for WorldMapPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<WorldMapRequest>()
            .add_systems(OnEnter(Scene::Field), enter_worldmap)
            .add_systems(OnExit(Scene::Field), exit_worldmap)
            .add_systems(FixedUpdate, worldmap_tick.in_set(GameSet::Logic).run_if(in_state(Scene::Field)));
    }
}
