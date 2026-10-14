//! Screen space effects of the effect VM that read the frame buffer back: `blr*` (`EffectBlur`, the frame drawn over itself), `gny*` (`EffectGunya`, a
//! swirl / twist of the frame) and -- see [`Sh2ShatterFx`] -- `bng*` (`EffectBarin`, the screen breaking into shards).  Each one is a Bevy full-screen post
//! pass on the 3D camera (before the gamma decode, so it works on raw PS2 display values like the GS did); the effect scene
//! ([`super::scene::FxScene`]) owns the state and [`super::render`] copies it into these components every frame.

use ::bevy::asset::{load_internal_asset, uuid_handle};
use ::bevy::prelude::*;
use ::bevy::render::extract_component::ExtractComponent;
use ::bevy::render::render_resource::ShaderType;
use ::bevy::shader::{Shader, ShaderRef};

use super::screenfx_pass::{ScreenFx, ScreenFxPass};

pub const BLUR_SHADER: Handle<Shader> = uuid_handle!("a1b2c3d4-0001-4e5f-8a17-3d52c0e9b6f2");
pub const SWIRL_SHADER: Handle<Shader> = uuid_handle!("a1b2c3d4-0002-4e5f-8a17-3d52c0e9b6f3");
pub const SHATTER_SHADER: Handle<Shader> = uuid_handle!("a1b2c3d4-0003-4e5f-8a17-3d52c0e9b6f4");

/// `EffectBlur` layers (up to 4).  `layers[2k]` = vertex colour (r, g, b, a), GS 0..128 scale; `layers[2k + 1]` = texture window (u0, v0, u1, v1) in texels of the 512 x 448 frame.
#[derive(Component, ExtractComponent, Clone, Copy, ShaderType, Default, Debug, PartialEq)]
pub struct Sh2BlurFx {
    /// x = number of layers in use
    pub head: Vec4,
    pub layers: [Vec4; 8],
}

impl Sh2BlurFx {
    pub const MAX: usize = 4;
    pub fn push(&mut self, rgba: [f32; 4], uv: [f32; 4]) -> bool {
        let n = self.head.x as usize;
        if n >= Self::MAX {
            return false;
        }
        self.layers[2 * n] = Vec4::from_array(rgba);
        self.layers[2 * n + 1] = Vec4::from_array(uv);
        self.head.x += 1.0;
        true
    }
}

impl ScreenFx for Sh2BlurFx {
    fn fragment_shader() -> ShaderRef {
        ShaderRef::Handle(BLUR_SHADER)
    }
}

/// `EffectGunya` swirl: `p.x` = rotation (radians) added per ring (the ring index grows towards the centre), `p.y` = 1 when active.
#[derive(Component, ExtractComponent, Clone, Copy, ShaderType, Default, Debug, PartialEq)]
pub struct Sh2SwirlFx {
    pub p: Vec4,
}

impl ScreenFx for Sh2SwirlFx {
    fn fragment_shader() -> ShaderRef {
        ShaderRef::Handle(SWIRL_SHADER)
    }
}

/// Polygons the shatter pass can draw (`EffectBarin` pattern = 53, user polygons are few).
pub const SHATTER_MAX: usize = 64;

/// `EffectBarin` shards: `head.x` = polygon count, `polys[5k]` = (vertex count, grey level, 0, 0), `polys[5k + 1 + j]` = (screen x, screen y, texel x, texel y).
/// The first frame of the effect stores the incoming frame as the shards' texture ([`ScreenFx::SNAPSHOT`]).
#[derive(Component, ExtractComponent, Clone, Copy, ShaderType, Debug, PartialEq)]
pub struct Sh2ShatterFx {
    pub head: Vec4,
    pub polys: [Vec4; 320],
}

impl Default for Sh2ShatterFx {
    fn default() -> Self {
        Sh2ShatterFx { head: Vec4::ZERO, polys: [Vec4::ZERO; 320] }
    }
}

impl Sh2ShatterFx {
    /// Add one polygon (3 or 4 vertices of `(screen, texel)`), `shade` = grey level.
    pub fn push(&mut self, verts: &[([f32; 2], [f32; 2])], shade: f32) -> bool {
        let k = self.head.x as usize;
        if k >= SHATTER_MAX || verts.len() < 3 {
            return false;
        }
        self.polys[5 * k] = Vec4::new(verts.len().min(4) as f32, shade, 0.0, 0.0);
        for (j, (s, t)) in verts.iter().take(4).enumerate() {
            self.polys[5 * k + 1 + j] = Vec4::new(s[0], s[1], t[0], t[1]);
        }
        self.head.x += 1.0;
        true
    }
}

impl ScreenFx for Sh2ShatterFx {
    fn fragment_shader() -> ShaderRef {
        ShaderRef::Handle(SHATTER_SHADER)
    }
    const SNAPSHOT: bool = true;
}

/// Registers the shaders and the passes.
pub struct ScreenFxPlugin;

impl Plugin for ScreenFxPlugin {
    fn build(&self, app: &mut App) {
        load_internal_asset!(app, BLUR_SHADER, "screenfx_blur.wgsl", Shader::from_wgsl);
        load_internal_asset!(app, SWIRL_SHADER, "screenfx_swirl.wgsl", Shader::from_wgsl);
        load_internal_asset!(app, SHATTER_SHADER, "screenfx_shatter.wgsl", Shader::from_wgsl);
        app.add_plugins((ScreenFxPass::<Sh2BlurFx>::default(), ScreenFxPass::<Sh2SwirlFx>::default(), ScreenFxPass::<Sh2ShatterFx>::default()));
    }
}
