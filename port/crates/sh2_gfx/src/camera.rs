//! `Gsx` (GS bring-up / vsync / flip state) and `GsxCamera` (render target + view parameters).
//! JP libgsx.cpp 0x002228c0..0x00223110 (Gsx), 0x00226b90..0x00227d54 (GsxCamera). See decomp/B/Gsx.c, GsxCamera.c.

use glam::Mat4;

use crate::gs::{ad, reg, GifFlg, GifTag, Qword};
use crate::psm::Psm;

/// Opaque handle of a camera inside whatever owns it (stands in for `GsxCamera*`).
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct CameraId(pub u32);

/// Video mode as stored by `Gsx::Open` (`vmode__3Gsx` @0x00412e10).
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct GsxVMode {
    pub mode: u8,
    pub inter: u8,
    pub ffmode: u8,
    pub fb_psm: u8,
    pub width: u16,
    pub height: u16,
    pub zbuf_en: u8,
    pub zbuf_psm: u8,
}

/// `Gsx::m_flags` bits.
pub mod gsx_flags {
    pub const OPEN: u32 = 0x01;
    pub const INTER30: u32 = 0x08;
    pub const FLIP_PENDING: u32 = 0x10;
    pub const FRAME_IN_FLIGHT: u32 = 0x20;
    pub const FF_MODE: u32 = 0x40;
    pub const FF_SUB: u32 = 0x80;
    pub const FORCE_FLIP: u32 = 0x100;
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum VsyncAction {
    None,
    /// `GsxCamera::Flip(cam, false, true)` must run in the vblank handler.
    Flip,
}

/// JP: static members of class `Gsx`.
#[derive(Clone, Debug)]
pub struct Gsx {
    pub vmode: GsxVMode,
    pub m_flags: u32,
    /// Minimum vblanks per frame (1 = 60 Hz, 2 = 30 Hz).
    pub sync_count: u16,
    pub vcount: u32,
}

impl Default for Gsx {
    fn default() -> Self {
        // Gsx::Initialize: m_syncCount = 1; m_flags = 0x101
        Gsx { vmode: GsxVMode::default(), m_flags: 0x101, sync_count: 1, vcount: 0 }
    }
}

impl Gsx {
    /// The game opens the GS with 512x448, 24-bit frame and 24-bit Z, mode 0x21 (`CApp::InitScreen`, JP 0x003d75a0).
    pub fn open_default() -> Gsx {
        let mut g = Gsx::default();
        g.open(512, 448, 24, 24, 0x21);
        g
    }

    /// JP 0x002229d0 `Gsx::Open`.
    pub fn open(&mut self, w: u16, h: u16, fb_bpp: u32, z_bpp: u32, mode: u32) {
        self.vmode = GsxVMode {
            mode: (mode & 0xf) as u8,
            inter: ((mode >> 4) & 0xf) as u8,
            ffmode: ((mode >> 8) & 0xf) as u8,
            fb_psm: Psm::from_bpp(fb_bpp, false).map(|p| p as u8).unwrap_or(0xff),
            width: w,
            height: h,
            zbuf_en: if z_bpp == 0 { 0 } else { 3 },
            zbuf_psm: Psm::from_bpp(z_bpp, true).map(|p| p as u8).unwrap_or(0xff),
        };
        self.m_flags = (self.m_flags & !gsx_flags::FF_MODE) | (((self.vmode.ffmode & 1) as u32) << 6);
    }

    /// JP 0x00223070 `SetInter30`, returns the old bit.
    pub fn set_inter30(&mut self, on: bool) -> bool {
        let old = self.m_flags & gsx_flags::INTER30 != 0;
        self.m_flags = (self.m_flags & !gsx_flags::INTER30) | ((on as u32) << 3);
        old
    }

    /// JP 0x002230a0 `SetFFMode(ff, sub, syncCount)`.
    pub fn set_ff_mode(&mut self, ff: bool, sub: bool, sync_count: u16) {
        self.m_flags = (self.m_flags & 0x3f) | ((ff as u32) << 6) | ((sub as u32) << 7);
        self.sync_count = sync_count;
    }

    /// JP 0x00222ab0 `cbVSync` decision logic (the `TimerWatcherV` call is the timer subsystem's business).
    /// `active_cam_double_buffered` = `GsxCamera::m_pActiveCamera && (cam->flags & 1)`.
    pub fn cb_vsync(&mut self, active_cam_double_buffered: bool) -> VsyncAction {
        self.vcount += 1;
        if self.m_flags & gsx_flags::FRAME_IN_FLIGHT != 0 {
            return VsyncAction::None;
        }
        if !active_cam_double_buffered {
            self.m_flags &= !gsx_flags::FLIP_PENDING;
            return VsyncAction::None;
        }
        if self.m_flags & gsx_flags::FF_SUB == 0 || self.m_flags & gsx_flags::FLIP_PENDING != 0 {
            self.m_flags &= !gsx_flags::FLIP_PENDING;
            return VsyncAction::Flip;
        }
        VsyncAction::None
    }

    /// End-of-frame flag update from `CApp::Run` (before `DrawSync`).
    pub fn end_of_frame_flags(&mut self) {
        let mut f = self.m_flags & !gsx_flags::FRAME_IN_FLIGHT;
        if self.m_flags & gsx_flags::FORCE_FLIP != 0 {
            f = (self.m_flags & 0xcf) | gsx_flags::FLIP_PENDING;
        }
        self.m_flags = f;
    }

    /// Start-of-frame flag update from `CApp::Run`.
    pub fn begin_frame_flags(&mut self) {
        self.m_flags = (self.m_flags & !gsx_flags::FRAME_IN_FLIGHT) | gsx_flags::FRAME_IN_FLIGHT;
    }
}

/// `GsxCamera::flags` (byte +0x390).
pub mod cam_flags {
    /// Double buffered (frame raster allocated 2*height tall; `FlipBuffer` swaps FBP).
    pub const DOUBLE_BUFFER: u8 = 0x01;
    pub const HAS_ZBUF: u8 = 0x02;
    /// `World::BeginUpdate` calls `ClearRaster` every frame.
    pub const CLEAR_EACH_FRAME: u8 = 0x04;
    /// `FlipBuffer` syncs DMA and calls `sceGsPutDispEnv`.
    pub const SYNC_DISPLAY: u8 = 0x08;
    pub const FLIP_LATCH: u8 = 0x10;
    pub const CAPTURE: u8 = 0x20;
}

/// `sceGsDrawEnv1/2` — 8 A+D registers of one context.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct DrawEnv {
    pub frame: u64,
    pub zbuf: u64,
    pub xyoffset: u64,
    pub scissor: u64,
    pub prmodecont: u64,
    pub colclamp: u64,
    pub dthe: u64,
    pub test: u64,
}

impl DrawEnv {
    /// `sceGsSetDefDrawEnv(env, psm, w, h, ztest, zpsm)` (+ the game's post-fixups in `GsxCamera::Create`).
    pub fn default_for(psm: Psm, w: u32, h: u32, ztest: u32, zpsm: Option<Psm>) -> DrawEnv {
        let fbw = w / 64;
        DrawEnv {
            frame: (fbw as u64) << 16 | (psm as u64) << 24,
            zbuf: zpsm.map(|p| (p as u64 & 0xf) << 24).unwrap_or(0) | if zpsm.is_none() { 1 << 32 } else { 0 },
            xyoffset: ((2048 - w as u64 / 2) << 4) | (((2048 - h as u64 / 2) << 4) << 32),
            scissor: ((w as u64 - 1) << 16) | ((h as u64 - 1) << 48),
            prmodecont: 1,
            colclamp: 1,
            dthe: 0,
            test: 1 << 16 | (ztest as u64) << 17,
        }
    }

    pub fn set_fbp(&mut self, fbp: u16) {
        self.frame = (self.frame & !0x1ff) | (fbp as u64 & 0x1ff);
    }
    pub fn set_zbp(&mut self, zbp: u16) {
        self.zbuf = (self.zbuf & !0x1ff) | (zbp as u64 & 0x1ff);
    }

    /// The eight A+D qwords for context `ctx` (0 or 1), in `sceGsDrawEnv` order.
    pub fn ad_qwords(&self, ctx: u8) -> [Qword; 8] {
        let c = ctx;
        [
            ad(reg::FRAME_1 + c, self.frame),
            ad(reg::ZBUF_1 + c, self.zbuf),
            ad(reg::XYOFFSET_1 + c, self.xyoffset),
            ad(reg::SCISSOR_1 + c, self.scissor),
            ad(reg::PRMODECONT, self.prmodecont),
            ad(reg::COLCLAMP, self.colclamp),
            ad(reg::DTHE, self.dthe),
            ad(reg::TEST_1 + c, self.test),
        ]
    }
}

/// JP class `GsxCamera` (0x398 bytes) — only the members relevant to rendering.
#[derive(Clone, Debug)]
pub struct GsxCamera {
    pub flags: u8,
    pub buf_idx: u8,
    pub field: u8,
    pub width: u16,
    pub height: u16,
    /// FBP (in 2 KiB units) of the two pages (`fbp[2]` @0x38c). Single-buffered cameras use `fbp[0]` for both.
    pub fbp: [u16; 2],
    pub zbp: u16,
    pub env1: DrawEnv,
    pub env2: DrawEnv,
    pub fogcol: u64,
    /// Background colour used by `ClearRaster` (RGBA, A=0x80 = 1.0).
    pub bgcolor: u32,
    /// Camera world matrix ("frame", +0x240) as 4 row vectors (X axis, Y axis, Z axis, position).
    pub frame: [[f32; 4]; 4],
    pub scrz: f32,
    pub aspx: f32,
    pub aspy: f32,
    pub near_z: f32,
    pub far_z: f32,
    pub zmax: f32,
    pub zmin: f32,
    pub fog_near: f32,
    pub fog_far: f32,
}

const IDENT: [[f32; 4]; 4] = [[1., 0., 0., 0.], [0., 1., 0., 0.], [0., 0., 1., 0.], [0., 0., 0., 1.]];

impl GsxCamera {
    /// JP 0x00226e10 `GsxCamera::Create(w, h, fbBpp, zBpp, flags)`; `flags` as passed by callers
    /// (bit0 clear-each-frame, bit1 double buffer, bit3 sync display).  VRAM placement follows the game's first-fit result
    /// for a double-buffered 512x448 CT24 camera: frame0 0x0000, frame1 0x0e00, Z 0x1c00 (blocks), texture area from 0x2a00.
    pub fn create(gsx: &Gsx, w: u32, h: u32, fb_bpp: u32, z_bpp: u32, flags: u32) -> GsxCamera {
        let w = if w == 0 { gsx.vmode.width as u32 } else { w };
        let h = if h == 0 { gsx.vmode.height as u32 } else { h };
        let psm = if fb_bpp == 0 { Psm::from_code(gsx.vmode.fb_psm).unwrap_or(Psm::Ct24) } else { Psm::from_bpp(fb_bpp, false).unwrap() };
        let zpsm = if z_bpp != 0 { Psm::from_bpp(z_bpp, true) } else { None };
        let mut cf = 0u8;
        if z_bpp != 0 {
            cf |= cam_flags::HAS_ZBUF;
        }
        if flags & 1 != 0 {
            cf |= cam_flags::CLEAR_EACH_FRAME;
        }
        if flags & 2 != 0 {
            cf |= cam_flags::DOUBLE_BUFFER;
        }
        if flags & 8 != 0 {
            cf |= cam_flags::SYNC_DISPLAY;
        }
        let blocks_per_buf = (w * h * 4 / 256) as u16; // CT24 occupies 32-bit words
        let fb0 = 0u16;
        let fb1 = if cf & cam_flags::DOUBLE_BUFFER != 0 { blocks_per_buf } else { 0 };
        let zb = if cf & cam_flags::DOUBLE_BUFFER != 0 { 2 * blocks_per_buf } else { blocks_per_buf };
        let ztest = if z_bpp != 0 { 2 } else { 1 };
        let mut env1 = DrawEnv::default_for(psm, w, h, ztest, zpsm);
        let mut env2 = env1;
        env1.set_fbp(fb0 / 32);
        env2.set_fbp(fb0 / 32);
        if z_bpp != 0 {
            env1.set_zbp(zb / 32);
            env2.set_zbp(zb / 32);
        }
        GsxCamera {
            flags: cf,
            buf_idx: 0,
            field: 0,
            width: w as u16,
            height: h as u16,
            fbp: [fb0 / 32, fb1 / 32],
            zbp: zb / 32,
            env1,
            env2,
            fogcol: 0xffffff,
            bgcolor: 0,
            frame: IDENT,
            scrz: 0.0,
            aspx: 1.0,
            aspy: 1.0,
            near_z: 0.1,
            far_z: 30000.0,
            zmax: if z_bpp != 0 { ((1u64 << z_bpp) - 1) as f32 } else { 0.0 },
            zmin: 0.0,
            fog_near: 1.0,
            fog_far: 1000.0,
        }
    }

    /// JP 0x002278e0 `SetViewMatrix(scrz, ax, ay, nearz, farz)` — note the original's meaning of the last two args:
    /// `zmin = nearz`, `zmax = farz / 2` (they feed `sceVu0ViewScreenMatrix`'s Z-buffer range, the geometric near/far are
    /// the separate fields set directly by callers: 0.1 and 30000.0 in the game camera).
    pub fn set_view_matrix(&mut self, scrz: f32, ax: f32, ay: f32, nearz: f32, farz: f32) {
        self.scrz = scrz;
        self.aspx = ax;
        self.aspy = ay;
        if nearz >= 0.0 {
            self.zmin = nearz;
        }
        if farz >= 0.0 {
            self.zmax = farz / 2.0;
        }
    }

    /// JP 0x00300de0 `SetFogParam(near, far)`: returns the `fogParam` vector `(0, near, 256/(far-near), 255)`.
    pub fn set_fog_param(&mut self, near: f32, far: f32) -> [f32; 4] {
        self.fog_near = near;
        self.fog_far = far;
        [0.0, near, 256.0 / (far - near), 255.0]
    }

    /// JP 0x00227bd0 `ApplyFrame` — view matrix = inverse of the camera frame (row-vector convention).
    pub fn view_matrix(&self) -> Mat4 {
        // rows -> glam columns need a transpose; the original multiplies row vectors v*M, so M_glam = transpose(rows)
        let f = Mat4::from_cols_array_2d(&self.frame).transpose();
        f.inverse()
    }

    /// Half-extent tangents of the view frustum, *inferred*: `tan(half) = (size/2) / (scrz * asp)`.
    /// With the game camera (scrz 1200, ax 0.8, ay 0.9333, 512x448) this yields a 4:3 view (0.2667 : 0.2).
    pub fn tan_half_fov(&self) -> (f32, f32) {
        ((self.width as f32 / 2.0) / (self.scrz * self.aspx), (self.height as f32 / 2.0) / (self.scrz * self.aspy))
    }

    /// FBP of the page that is being drawn this frame (JP 0x00227420 `GetRenderTargPkt` page selection).
    pub fn draw_page_fbp(&self, gsx_inter30: bool) -> u16 {
        let mut page = 0usize;
        if self.flags & cam_flags::DOUBLE_BUFFER != 0 {
            page = ((self.buf_idx ^ 1) & 1) as usize;
            if gsx_inter30 {
                page ^= 1;
            }
        }
        self.fbp[page]
    }

    /// JP 0x00227420 `GetRenderTargPkt`: the 17-qword A+D block (preceded by its GIFtag) that switches the draw environment.
    pub fn render_target_packet(&self, gsx_inter30: bool) -> Vec<Qword> {
        let fbp = self.draw_page_fbp(gsx_inter30);
        let mut e1 = self.env1;
        let mut e2 = self.env2;
        e1.set_fbp(fbp);
        e2.set_fbp(fbp);
        let mut v = Vec::with_capacity(18);
        v.push(GifTag::build(0x11, true, false, 0, GifFlg::Packed, &[reg::AD]));
        v.extend_from_slice(&e1.ad_qwords(0));
        v.extend_from_slice(&e2.ad_qwords(1));
        v.push(ad(reg::FOGCOL, self.fogcol));
        v
    }

    /// JP 0x00227650 `FlipBuffer`: toggles `buf_idx` and swaps the draw env pages (returns the page now displayed).
    pub fn flip_buffer(&mut self) -> Option<u16> {
        self.buf_idx = (self.buf_idx + 1) & 1;
        if self.flags & cam_flags::DOUBLE_BUFFER != 0 {
            let show = self.fbp[(self.buf_idx ^ 1) as usize];
            let draw = self.fbp[self.buf_idx as usize];
            self.env1.set_fbp(draw);
            self.env2.set_fbp(draw);
            Some(show)
        } else {
            None
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::gs::GifTag;

    #[test]
    fn game_camera_layout() {
        let g = Gsx::open_default();
        assert_eq!((g.vmode.width, g.vmode.height), (512, 448));
        assert_eq!(g.vmode.fb_psm, Psm::Ct24 as u8);
        assert_eq!(g.vmode.zbuf_psm, Psm::Z24 as u8);
        let c = GsxCamera::create(&g, 0, 0, 0, 24, 2);
        assert_eq!(c.flags & cam_flags::DOUBLE_BUFFER, 1);
        assert_eq!(c.fbp, [0, 0x0e00 / 32]);
        assert_eq!(c.zbp, 0x1c00 / 32);
        assert_eq!(c.zmax, 16777215.0);
    }

    #[test]
    fn render_target_packet_shape() {
        let g = Gsx::open_default();
        let c = GsxCamera::create(&g, 0, 0, 0, 24, 2);
        let p = c.render_target_packet(false);
        assert_eq!(p.len(), 18);
        let t = GifTag::parse(p[0]);
        assert_eq!(t.nloop, 17);
        assert_eq!(p[17].hi as u8, reg::FOGCOL);
    }

    #[test]
    fn flip_swaps_pages() {
        let g = Gsx::open_default();
        let mut c = GsxCamera::create(&g, 0, 0, 0, 24, 2);
        let d0 = c.draw_page_fbp(false);
        c.flip_buffer();
        let d1 = c.draw_page_fbp(false);
        assert_ne!(d0, d1);
    }

    #[test]
    fn vsync_logic() {
        let mut g = Gsx::default();
        assert_eq!(g.cb_vsync(true), VsyncAction::Flip); // m_flags=0x101: bit7 clear -> flip
        g.m_flags |= gsx_flags::FRAME_IN_FLIGHT;
        assert_eq!(g.cb_vsync(true), VsyncAction::None);
        assert_eq!(g.vcount, 2);
    }

    #[test]
    fn game_view_is_4_3() {
        let g = Gsx::open_default();
        let mut c = GsxCamera::create(&g, 0, 0, 0, 24, 2);
        c.set_view_matrix(1200.0, 0.8, 0.93333334, 1.0, 1.6777e7);
        let (tx, ty) = c.tan_half_fov();
        assert!(((tx / ty) - 4.0 / 3.0).abs() < 0.01);
    }
}
