//! The common window frame and cursor of `COMMON/CMNMENU.DAT` for screens that live in this crate (the Game Over question): a small copy of
//! `sh2_field::cmd_common::general_frame` (`MenuWindowGeneral::Update`, JP 0x0028def0: sprites 8..17 of the common scene on its 88 x 120 texture
//! + polygon 1 as the fill) and of `CmdCursor::draw` (`Cursor` kind 0: the silver arrow of attach 2 spinning about its vertical axis, the flare of attach 3).

use crate::bevy_ui::UiTextures;
use crate::disc::FileSource;
use crate::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextureId, Vertex};
use crate::msd::Msd;
use bevy::prelude::*;
use glam::Vec2;

pub struct CmnArt {
    msd: Msd,
    frame: Option<TextureId>,
    arrow: Option<TextureId>,
    flare: Option<TextureId>,
    /// round 6 MN3: attach 6, the pad icon sheet (8 x 2 cells of 16 x 20; row 1 = pad bits 8..15)
    icons: Option<TextureId>,
}

fn blit(g: &mut dyn MenuGfx, tex: Option<TextureId>, x: f32, y: f32, w: f32, h: f32, uv: (f32, f32, f32, f32), c: Rgba) {
    let (u0, v0, u1, v1) = uv;
    let v = |px: f32, py: f32, u: f32, vv: f32| Vertex { pos: Vec2::new(px, py), uv: Vec2::new(u, vv), color: c };
    g.draw(DrawCmd::Quad { tex, v: [v(x, y, u0, v0), v(x, y + h, u0, v1), v(x + w, y, u1, v0), v(x + w, y + h, u1, v1)], blend: Blend::Alpha });
}

impl CmnArt {
    pub fn load(disc: &dyn FileSource, textures: &mut UiTextures, images: &mut Assets<Image>) -> Option<CmnArt> {
        let msd = Msd::parse(disc.read("COMMON/CMNMENU.DAT")?).ok()?;
        let mut tex = |i: usize| -> Option<TextureId> {
            let img = sh2_gfx::texture::decode_menu_texture(msd.attach_data(i)?, 0).ok()?;
            Some(textures.add(images, img.width, img.height, img.pixels))
        };
        let (frame, arrow, flare, icons) = (tex(8), tex(2), tex(3), tex(6));
        Some(CmnArt { msd, frame, arrow, flare, icons })
    }

    /// Round 6 MN3: the 16 x 20 icon of pad bit `bit` (8..15: L2 R2 L1 R1 triangle circle cross square) with its top left at `(x, y)`.
    pub fn pad_icon(&self, g: &mut dyn MenuGfx, bit: u16, x: f32, y: f32, alpha: u8) {
        let c = (bit.clamp(8, 15) - 8) as f32 * 16.0;
        blit(g, self.icons, x, y, 16.0, 20.0, (c, 20.0, c + 16.0, 40.0), Rgba::new(0x80, 0x80, 0x80, alpha));
    }

    /// `MenuWindowGeneral`: `(x, y, w, h)` is the outer rectangle (see `sh2_field::cmd_common::general_frame`).
    pub fn general_frame(&self, g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, alpha: u8) {
        let m = &self.msd;
        let (wp, hp) = ((w - 49.0).max(0.0), (h - 73.0).max(0.0));
        let (ox, oy) = (x + 19.0, y + 7.0);
        if let Some(p) = m.polygon(1) {
            let col = |k: usize| Rgba::new(p.rgba[k][0], p.rgba[k][1], p.rgba[k][2], ((p.rgba[k][3] as u32 * alpha as u32) / 0x80) as u8);
            let (x0, y0, x1, y1) = (ox - 19.0, oy - 7.0, ox - 19.0 + 49.0 + wp, oy - 7.0 + 61.0 + hp + 12.0);
            let v = |px: f32, py: f32, c: Rgba| Vertex { pos: Vec2::new(px, py), uv: Vec2::ZERO, color: c };
            g.draw(DrawCmd::Quad { tex: None, v: [v(x0, y0, col(0)), v(x0, y1, col(1)), v(x1, y0, col(2)), v(x1, y1, col(3))], blend: Blend::Alpha });
        }
        let spr = |g: &mut dyn MenuGfx, i: usize, px: f32, py: f32, sw: Option<f32>, sh: Option<f32>| {
            if let Some(r) = m.sprite(i) {
                let c = Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], ((r.rgba[3] as u32 * alpha as u32) / 0x80) as u8);
                blit(g, self.frame, ox + px, oy + py, sw.unwrap_or(r.w), sh.unwrap_or(r.h), (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), c);
            }
        };
        let rec = |i: usize| m.sprite(i).map(|r| (r.x, r.y)).unwrap_or((0.0, 0.0));
        let (x14, y14) = rec(14);
        spr(g, 14, x14, y14, Some(wp), None);
        let (x15, y15) = rec(15);
        spr(g, 15, x15, hp + y15, Some(wp), None);
        let (x16, y16) = rec(16);
        spr(g, 16, x16, y16, None, Some(hp));
        let (x17, y17) = rec(17);
        spr(g, 17, wp + x17, y17, None, Some(hp));
        let (x13, y13) = rec(13);
        spr(g, 13, x13, y13, None, None);
        let (x12, y12) = rec(12);
        spr(g, 12, x12, y12, None, None);
        let (x11, y11) = rec(11);
        spr(g, 11, x11, hp + y11, None, None);
        let (x8, y8) = rec(8);
        spr(g, 8, wp + x8, y8, None, None);
        let (x9, y9) = rec(9);
        spr(g, 9, wp + x9, hp + y9, None, None);
        let (x10, y10) = rec(10);
        spr(g, 10, wp + x10, hp + y10, None, None);
    }

    /// The selection cursor with its tip at `(x, y)` (arrow on the left pointing right), `angle` in degrees (spin).
    pub fn cursor(&self, g: &mut dyn MenuGfx, x: f32, y: f32, angle: f32, alpha: u8) {
        if let Some(t) = self.flare {
            blit(g, Some(t), x - 30.0, y - 20.0, 40.0, 40.0, (0.0, 0.0, 40.0, 40.0), Rgba::new(0x60, 0x80, 0x80, (alpha as u32 * 0x50 / 0x80) as u8));
        }
        let k = angle.to_radians().cos().abs().max(0.35);
        if let Some(t) = self.arrow {
            blit(g, Some(t), x - 20.0, y - 10.0 * k, 20.0, 20.0 * k, (0.0, 0.0, 20.0, 20.0), Rgba::new(0x80, 0x80, 0x80, alpha));
        }
    }
}
