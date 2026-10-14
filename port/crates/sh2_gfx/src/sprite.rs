//! Packet builders for the game's 2D drawables, byte-compatible with the originals:
//! `P2Sprite::UpdateObj` (JP 0x003c79a0), `ScreenBright::getPacket` (0x003d8920), `prim2D::getPacket` quad (0x0039b170),
//! `CineMask::MakePacket` (0x003cfb40) and `SetFullSprite*` (0x003d51a0).
//!
//! Screen coordinates are GS window coordinates: the 512x448 screen is centred at (2048,2048) in 12.4 fixed point, i.e. an
//! XYOFFSET of (1792, 1824) pixels is added by the originals ("+0x700 / +0x720").

use std::sync::Arc;

use crate::gs::{ad, reg, Alpha, GifFlg, GifTag, Qword};
use crate::packet::Packet;
use crate::world::{PrimBase, Vif1Prim};

pub const SCREEN_W: f32 = 512.0;
pub const SCREEN_H: f32 = 448.0;
/// GS window offset of the top-left screen pixel: 2048 - 256 and 2048 - 224.
pub const OFS_X: f32 = 1792.0;
pub const OFS_Y: f32 = 1824.0;

/// Blend modes of `prim2D::setBlendMode` / `primSprites`: value written to ALPHA_1.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BlendMode {
    Normal = 0,
    Add = 1,
    Sub = 2,
}
impl BlendMode {
    pub fn alpha_bits(self) -> u64 {
        match self {
            BlendMode::Normal => Alpha::NORMAL,
            BlendMode::Add => Alpha::ADD,
            BlendMode::Sub => Alpha::SUB,
        }
    }
}

fn fx4(v: f32) -> u16 {
    // original: (short)(int)(v * 16.0) with the >= 2^31 correction (irrelevant here)
    (v * 16.0) as i32 as u16
}

/// Mirror of `P2Sprite` (size 0x58) — fields that matter for the packet.
#[derive(Clone, Debug)]
pub struct P2Sprite {
    /// GS PRIM bits (SPRITE=6, TME=0x10, ABE=0x40, FST=0x100 ...)
    pub prim_bits: u16,
    pub fst: bool,
    pub ctx2: bool,
    pub centered_scale: bool,
    pub linear_tex1: bool,
    pub with_regs: bool,
    pub x: f32,
    pub y: f32,
    pub z: f32,
    pub rgba: u32,
    pub w: f32,
    pub h: f32,
    pub u: f32,
    pub v: f32,
    pub uw: f32,
    pub vh: f32,
    pub offx: f32,
    pub offy: f32,
    pub scale_x: f32,
    pub scale_y: f32,
    pub alpha: u64,
    pub test: u64,
    pub tex0: u64,
}

impl P2Sprite {
    /// JP 0x003c78b0 `Create(attr, tex)`.
    pub fn create(with_regs: bool) -> Self {
        P2Sprite {
            prim_bits: 6,
            fst: false,
            ctx2: false,
            centered_scale: false,
            linear_tex1: false,
            with_regs,
            x: 0.0,
            y: 0.0,
            z: 0.0,
            rgba: 0,
            w: 0.0,
            h: 0.0,
            u: 0.0,
            v: 0.0,
            uw: 0.0,
            vh: 0.0,
            offx: 0.0,
            offy: 0.0,
            scale_x: 1.0,
            scale_y: 1.0,
            alpha: 0,
            test: 0,
            tex0: 0,
        }
    }

    /// JP 0x003c7950 `GetPktSize`: 10 qwords with the register header, else 4.
    pub fn pkt_size(&self) -> usize {
        if self.with_regs {
            10
        } else {
            4
        }
    }

    /// JP 0x003c79a0 `UpdateObj` — emits the qwords in the original order.
    pub fn build(&self) -> Vec<Qword> {
        let c = self.ctx2 as u8;
        let mut v = Vec::with_capacity(10);
        if self.with_regs {
            v.push(GifTag::build(5, true, false, 0, GifFlg::Packed, &[reg::AD]));
            v.push(ad(reg::TEXFLUSH, 0));
            v.push(ad(reg::ALPHA_1 + c, self.alpha));
            v.push(ad(reg::TEST_1 + c, self.test));
            v.push(ad(reg::TEX0_1 + c, self.tex0));
            v.push(ad(reg::TEX1_1 + c, if self.linear_tex1 { 0x60 } else { 0 }));
        }
        // quad GIF tag: NLOOP=1 EOP PRE=1 prim=? FLG=REGLIST NREG=6  (0x6400000000008001 has bit 58 and bits 60-62 only)
        let regs: [u8; 6] = if self.fst { [0, 1, 3, 4, 3, 4] } else { [0, 1, 2, 4, 2, 4] };
        v.push(GifTag::build(1, true, false, 0, GifFlg::RegList, &regs));
        // PRIM, RGBAQ
        v.push(Qword::new((self.prim_bits & 0x7ff) as u64, self.rgba as u64));
        let (z, _) = (self.z as u32 as u64, 0);
        let (x0, y0, x1, y1);
        if self.centered_scale {
            let hw = self.w * self.scale_x * 0.5;
            let hh = self.h * self.scale_y * 0.5;
            x0 = (self.x - hw) * 16.0;
            y0 = (self.y - hh) * 16.0;
            x1 = (self.x + hw) * 16.0;
            y1 = (self.y + hh) * 16.0;
        } else {
            x0 = (self.x - self.offx * self.scale_x) * 16.0;
            y0 = (self.y - self.offy * self.scale_y) * 16.0;
            x1 = (self.x + self.w * self.scale_x - self.offx * self.scale_x) * 16.0;
            y1 = (self.y + self.h * self.scale_y - self.offy * self.scale_y) * 16.0;
        }
        let p0 = (x0 as i32 as u16) as u64 | (y0 as i32 as u16 as u64) << 16 | (z & 0xff_ffff) << 32;
        let p1 = (x1 as i32 as u16) as u64 | (y1 as i32 as u16 as u64) << 16 | (z & 0xff_ffff) << 32;
        if self.fst {
            let u0 = fx4(self.u) as u64 | (fx4(self.v) as u64) << 16;
            let u1 = fx4(self.u + self.uw) as u64 | (fx4(self.v + self.vh) as u64) << 16;
            v.push(Qword::new(u0, p0));
            v.push(Qword::new(u1, p1));
        } else {
            v.push(Qword::new(self.u.to_bits() as u64 | (self.v.to_bits() as u64) << 32, p0));
            v.push(Qword::new((self.u + self.uw).to_bits() as u64 | ((self.v + self.vh).to_bits() as u64) << 32, p1));
        }
        v
    }
}

/// `ScreenBright` (JP 0x003d8770): full-screen alpha-blended black/colour sprite drawn after the world each frame.
/// The 7-qword template lives at 0x00403d50 (`pktData`); `getPacket` patches RGBAQ and the two XYZ words.
#[derive(Clone, Debug)]
pub struct ScreenBright {
    pub base: PrimBase,
    /// +0x28: alpha (0 = transparent / no draw). GS alpha 0x80 = opaque.
    pub level: u8,
    /// +0x34: 0x00BBGGRR colour of the overlay.
    pub rgb: u32,
}

impl ScreenBright {
    pub fn new() -> Self {
        ScreenBright { base: PrimBase::default(), level: 0, rgb: 0 }
    }

    /// JP 0x003d8920 `getPacket`. Returns the 6 qwords of GIF payload (DIRECT 6).
    pub fn gif(&self, w: u16, h: u16) -> Vec<Qword> {
        let mut v = Vec::new();
        v.push(GifTag::build(2, false, false, 0, GifFlg::Packed, &[reg::AD]));
        v.push(ad(reg::TEST_1, 0x35302));
        v.push(ad(reg::ALPHA_1, Alpha::NORMAL));
        v.push(GifTag::build(1, true, false, 0, GifFlg::RegList, &[reg::PRIM, reg::RGBAQ, reg::XYZF2, reg::XYZF2]));
        let rgba = self.rgb as u64 + ((self.level as u64) << 24);
        v.push(Qword::new(0x46, rgba));
        let hx = (w as u32 >> 1) as i32;
        let hy = (h as u32 >> 1) as i32;
        let x0 = ((0x800 - hx) * 16) as u16 as u64;
        let y0 = ((0x800 - hy) * 16) as u16 as u64;
        let x1 = ((0x800 + hx) * 16) as u16 as u64;
        let y1 = ((0x800 + hy) * 16) as u16 as u64;
        v.push(Qword::new(x0 | y0 << 16, x1 | y1 << 16));
        v
    }
}

impl Vif1Prim for ScreenBright {
    fn base(&self) -> &PrimBase {
        &self.base
    }
    fn base_mut(&mut self) -> &mut PrimBase {
        &mut self.base
    }
    fn get_packet(&mut self, _parity: u8) -> Option<Arc<Packet>> {
        if self.level == 0 {
            return None;
        }
        Some(Arc::new(Packet::gif(self.gif(512, 448))))
    }
}

/// Quad of `prim2D` / `primSprites`: 4-vertex triangle strip, `PRIM=0x15c` (TRISTRIP|IIP|TME|ABE|FST), vertex order
/// top-left, bottom-left, top-right, bottom-right with UVs in 12.4 texels, Z = camera zmax.
#[derive(Clone, Copy, Debug)]
pub struct QuadVertex {
    pub x: f32,
    pub y: f32,
    pub u: f32,
    pub v: f32,
    pub rgba: [u8; 4],
}

pub fn prim2d_quad_gif(verts: &[QuadVertex; 4], z: u32, blend: BlendMode, tex0: u64, tex0_extra: u64) -> Vec<Qword> {
    let mut q = Vec::new();
    // cnt(3): A+D x2 : TEXFLUSH, TEX0_1
    q.push(GifTag::build(2, false, false, 0, GifFlg::Packed, &[reg::AD]));
    q.push(ad(reg::TEXFLUSH, 0));
    q.push(ad(reg::TEX0_1, tex0));
    // cnt(0xc): A+D x3 : TEST_1, ALPHA_1, TEX0_1 (+extra)
    q.push(GifTag::build(3, false, false, 0, GifFlg::Packed, &[reg::AD]));
    q.push(ad(reg::TEST_1, 0x3000d));
    q.push(ad(reg::ALPHA_1, blend.alpha_bits()));
    q.push(ad(reg::TEX0_1, tex0.wrapping_add(tex0_extra)));
    // REGLIST tag 0xe400000000008001, regs 0x431431c31c31f0: PRIM, NOP, then {RGBAQ,UV,XYZF3|2} x4 (3rd and 4th kick)
    q.push(GifTag::build(
        1,
        true,
        false,
        0,
        GifFlg::RegList,
        &[reg::PRIM, reg::NOP, reg::RGBAQ, reg::UV, reg::XYZF3, reg::RGBAQ, reg::UV, reg::XYZF3, reg::RGBAQ, reg::UV, reg::XYZF2, reg::RGBAQ, reg::UV, reg::XYZF2],
    ));
    let mut halves: Vec<u64> = vec![0x15c, 0];
    for v in verts {
        let rgba = v.rgba[0] as u64 | (v.rgba[1] as u64) << 8 | (v.rgba[2] as u64) << 16 | (v.rgba[3] as u64) << 24 | 0x1_0000_0000;
        let uv = (v.u as u32 as u64 & 0x3fff) | ((v.v as u32 as u64 & 0x3fff) << 16);
        let xy = fx4(v.x) as u64 | (fx4(v.y) as u64) << 16 | (z as u64) << 32;
        halves.push(rgba);
        halves.push(uv);
        halves.push(xy);
    }
    // 14 values were laid out as [prim,nop, (rgba,uv,xyz)*4] = 14: pack pairwise
    for c in halves.chunks(2) {
        q.push(Qword::new(c[0], c[1]));
    }
    q
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::gs::{BlendKind, GsEvent, GsInterpreter, PrimKind};

    #[test]
    fn screen_bright_draws_fullscreen_alpha_quad() {
        let sb = ScreenBright { base: PrimBase::default(), level: 0x40, rgb: 0 };
        let mut gs = GsInterpreter::new();
        // game camera uses XYOFFSET (2048-256, 2048-224)<<4
        gs.write_reg(reg::XYOFFSET_1, ((1792u64 + 0) << 4) | ((1824u64 << 4) << 32));
        gs.feed(&sb.gif(512, 448));
        let ev = gs.take_events();
        let d = ev
            .iter()
            .find_map(|e| if let GsEvent::Draw(d) = e { Some(d) } else { None })
            .expect("draw");
        assert_eq!(d.kind, PrimKind::Sprite);
        assert!(d.attr.abe);
        assert_eq!(d.ctx.alpha.classify(), BlendKind::AlphaBlend);
        assert_eq!(d.verts[0].rgba[3], 0x40);
        // 0x800-256 and 0x800+256 minus the 1792 offset -> hmm: offset is 1792 px, vertices are at (0x800-256)=1792 px
        assert_eq!((d.verts[0].x, d.verts[0].y), (0.0, 0.0));
        assert_eq!((d.verts[1].x, d.verts[1].y), (512.0, 448.0));
    }

    #[test]
    fn p2sprite_fst_packet_roundtrip() {
        let mut s = P2Sprite::create(true);
        s.prim_bits = 0x156 | 0x100; // SPRITE|TME|ABE|FST
        s.fst = true;
        s.x = 10.0 + 1792.0;
        s.y = 20.0 + 1824.0;
        s.w = 64.0;
        s.h = 32.0;
        s.u = 0.0;
        s.v = 0.0;
        s.uw = 64.0;
        s.vh = 32.0;
        s.rgba = 0x80808080;
        s.alpha = Alpha::NORMAL;
        s.test = 0x3000d;
        assert_eq!(s.build().len(), s.pkt_size());
        let mut gs = GsInterpreter::new();
        gs.write_reg(reg::XYOFFSET_1, (1792u64 << 4) | ((1824u64 << 4) << 32));
        gs.feed(&s.build());
        let ev = gs.take_events();
        let d = ev.iter().find_map(|e| if let GsEvent::Draw(d) = e { Some(d) } else { None }).unwrap();
        assert_eq!(d.verts.len(), 2);
        assert_eq!((d.verts[0].x, d.verts[0].y), (10.0, 20.0));
        assert_eq!((d.verts[1].x, d.verts[1].y), (74.0, 52.0));
        assert_eq!((d.verts[1].u, d.verts[1].v), (64.0, 32.0));
        assert!(d.ctx.test.ate);
    }

    #[test]
    fn prim2d_strip_yields_two_triangles() {
        let v = |x, y| QuadVertex { x, y, u: 0.0, v: 0.0, rgba: [0x7f; 4] };
        let quad = [v(0.0, 0.0), v(0.0, 8.0), v(8.0, 0.0), v(8.0, 8.0)];
        let mut gs = GsInterpreter::new();
        gs.feed(&prim2d_quad_gif(&quad, 0x7fffff, BlendMode::Add, 0, 0));
        let ev = gs.take_events();
        let tris = ev.iter().filter(|e| matches!(e, GsEvent::Draw(d) if d.kind == PrimKind::Triangle)).count();
        assert_eq!(tris, 2);
        let d = ev.iter().find_map(|e| if let GsEvent::Draw(d) = e { Some(d) } else { None }).unwrap();
        assert_eq!(d.ctx.alpha.classify(), BlendKind::Additive);
        assert!(d.attr.fst && d.attr.tme);
    }
}
