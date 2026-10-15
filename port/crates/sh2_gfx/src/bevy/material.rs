//! [`Sh2Material`]: the single material used for every PS2 model/map surface.
//!
//! GS state it reproduces (per `Texture::createRegsterPacket`, `changeGSAlpha`, `changeGSTest`, `Pack1Atomic::initPacket`):
//!
//! | GS | here |
//! |---|---|
//! | PRIM.ABE (atomic header `+0x10` bit 6) | [`Sh2Blend::Opaque`] when clear, otherwise the texture's ALPHA_1 below |
//! | `ALPHA_1 = 0x44` `(Cs-Cd)*As+Cd` (the register default of every model texture) | [`Sh2Blend::Normal`]  (SrcAlpha, OneMinusSrcAlpha) |
//! | `ALPHA_1 = 0x48` `Cs*As+Cd`      | [`Sh2Blend::Add`]     (SrcAlpha, One) |
//! | `ALPHA_1 = 0x42` `(0-Cs)*As+Cd`  | [`Sh2Blend::Sub`]     (ReverseSubtract: `Cd - Cs*As`) |
//! | `ALPHA_1` C = FIX                | `fix_alpha` |
//! | `TEST_1 = 0x5370b` (default): ATE, ATST = GEQUAL, AREF = 0x70, AFAIL = RGB_ONLY | [`TestMode::CutIn`] (`A >= 0x70`: writes depth) + [`TestMode::Low`] (`A < 0x70`: colour only, no depth write) |
//! | `TEST_1` from the TIHD (`changeGSTest(1, GEQUAL, ref, flags&3, ...)`) | [`Sh2Material::with_alpha_ref`] / [`TestMode`] |
//! | PRIM.FGE (atomic flag bit 5) | `fog_on`, fog constants from the `FOG` chunk ([`Sh2Fog`]) |
//! | TFX = MODULATE | shader (`tex * vtx`, vertex 0x80 = 1.0) |
//!
//! GS never culls, so the material is double sided.  Blended draws do not write depth (Bevy transparent pass).
//!
//! ## Colour space
//!
//! The GS blends *display-referred* values (gamma space).  In the default [`Sh2ColorSpace`] `gamma` mode (`SH2_LINEAR_BLEND=1` turns it off) the shader therefore
//! outputs the raw PS2 colour, the cameras render into an `Rgba16Float` (HDR) target, so blending happens on those raw values, and the
//! picture is decoded raw -> linear exactly once right before the sRGB surface encodes it again: by the last window camera's blit
//! (Bevy's `CompositingSpace::Srgb`, which also makes the 2D / UI layers blend raw values, see [`setup_gamma_cameras`]), or by a
//! full-screen pass ([`Sh2GammaDecode`], before tonemapping) on a camera that is alone on its target.
//! This makes additive glows (`Cs*As + Cd`) saturate exactly like the GS (clamp at the very end like the 8-bit frame buffer).

use ::bevy::asset::{load_internal_asset, uuid_handle};
use ::bevy::core_pipeline::fullscreen_material::{FullscreenMaterial, FullscreenMaterialPlugin};
use ::bevy::core_pipeline::tonemapping::Tonemapping;
use ::bevy::mesh::MeshVertexBufferLayoutRef;
use ::bevy::pbr::{MaterialPipeline, MaterialPipelineKey};
use ::bevy::prelude::*;
use ::bevy::reflect::TypePath;
use ::bevy::render::extract_component::ExtractComponent;
use ::bevy::render::render_resource::{
    AsBindGroup, BlendComponent, BlendFactor, BlendOperation, BlendState, RenderPipelineDescriptor, ShaderType,
    SpecializedMeshPipelineError,
};
use ::bevy::shader::{Shader, ShaderRef};

use crate::gs::{Alpha, BlendKind};

pub const SH2_SHADER: Handle<Shader> = uuid_handle!("5a3f6b0e-2d1c-4e7a-9f55-0b6c8d3e1a42");
pub const SH2_DECODE_SHADER: Handle<Shader> = uuid_handle!("7c1e44a0-96d2-4f3b-8a17-3d52c0e9b6f1");
/// Vertex stage of [`Sh2Material`] (`sh2_vertex.wgsl`: Bevy's mesh vertex shader + the PS2 one-matrix-per-vertex GPU skinning).
pub const SH2_VERTEX_SHADER: Handle<Shader> = uuid_handle!("b3f0c9e2-4d71-4a8e-9c06-2e5f7a1d8b34");

/// Colour-space mode of the renderer (see the module docs).  `SH2_LINEAR_BLEND=1` in the environment starts with `gamma = false`.
#[derive(Resource, Clone, Copy, Debug, PartialEq, Eq)]
pub struct Sh2ColorSpace {
    /// Blend raw display values (like the GS) in an HDR target and decode once at the end.
    pub gamma: bool,
    /// With `gamma`: the 2D / UI cameras composite in gamma space too ([`setup_gamma_cameras`]); `SH2_UI_LINEAR_BLEND=1` restores the
    /// round 6 arrangement (decode on the 3D camera, UI blended in linear light) for A/B comparisons.
    pub ui_gamma: bool,
}

impl Default for Sh2ColorSpace {
    fn default() -> Self {
        Sh2ColorSpace { gamma: std::env::var_os("SH2_LINEAR_BLEND").is_none(), ui_gamma: std::env::var_os("SH2_UI_LINEAR_BLEND").is_none() }
    }
}

/// Default `TEST_1` of every model texture (`Texture::createRegsterPacket`: `0x5370b`): ATE=1, ATST=GEQUAL, AREF=0x70, AFAIL=RGB_ONLY.
pub const DEFAULT_ALPHA_REF: f32 = 112.0;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, Default)]
pub enum Sh2Blend {
    /// ABE off: alpha ignored.
    #[default]
    Opaque,
    /// `ALPHA_1 = 0x44`
    Normal,
    /// `ALPHA_1 = 0x48`
    Add,
    /// `ALPHA_1 = 0x42`
    Sub,
}

impl Sh2Blend {
    pub fn from_kind(k: BlendKind) -> Sh2Blend {
        match k {
            BlendKind::AlphaBlend => Sh2Blend::Normal,
            BlendKind::Additive => Sh2Blend::Add,
            BlendKind::Subtractive => Sh2Blend::Sub,
            _ => Sh2Blend::Normal,
        }
    }
}

/// How the GS alpha test (`TEST_1`) is split over the Bevy draws of one surface.
///
/// The default test `A >= 0x70, AFAIL = RGB_ONLY` fails for translucent texels but *still writes their colour* (without depth):
/// the classic "sorted translucency over opaque cut-out" trick.  It needs two draws: `CutIn` (opaque phase, writes depth)
/// and `Low` (blend phase, no depth write).
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, Default)]
pub enum TestMode {
    /// No alpha test (or the plain `ATE` discard stored in `params.x`, see [`Sh2Material::with_alpha_ref`]).
    #[default]
    Off,
    /// Texels with `A >= ref` only.
    CutIn,
    /// Texels with `A < ref` only (colour written, no depth).
    Low,
}

/// GS `ALPHA_1` fields as stored in a model texture header (`_ModelTextureHeader` +0x1c, see notes/B/Texture.md):
/// `A = v&2, B = (v&0xc)>>2, C = (v&0x20)>>4, D = (v&0xc0)>>6, FIX = v>>8`.  `0` means "register default" = `0x44`.
pub fn texture_blend(alpha_bits: u16) -> (Sh2Blend, Option<f32>) {
    if alpha_bits == 0 {
        return (Sh2Blend::Opaque, None);
    }
    let v = alpha_bits as u64;
    let a = Alpha { a: (v & 2) as u8, b: ((v & 0xc) >> 2) as u8, c: ((v & 0x20) >> 4) as u8, d: ((v & 0xc0) >> 6) as u8, fix: (v >> 8) as u8 };
    let fix = (a.c == 2).then(|| a.fix as f32 / 128.0);
    (Sh2Blend::from_kind(a.classify()), fix)
}

/// Fog state (`FOG` chunk -> `GsxCamera::SetFogParam/SetFogColor`): the VU1 program computes
/// `F = 255 - clamp((z - near) * 256 / (far - near), 0, 255)` and the GS blends `Cd = Cs*F/255 + FOGCOL*(255-F)/255`
/// for primitives with PRIM.FGE (atomic flag bit 5).
#[derive(Resource, Clone, Copy, Debug, PartialEq)]
pub struct Sh2Fog {
    pub enabled: bool,
    pub near: f32,
    pub far: f32,
    /// Raw display colour 0..1 (`FOGCOL` bytes / 255).
    pub color: Vec3,
}

impl Default for Sh2Fog {
    fn default() -> Self {
        Sh2Fog { enabled: false, near: 10.0, far: 16_777_000.0, color: Vec3::ZERO }
    }
}

/// Lights applied to materials with `lit = true` (skinned characters): the result of `LightControl::getLightMatrix`
/// (up to 3 directions *towards* the light with their colours, plus the ambient colour).
#[derive(Resource, Clone, Debug, PartialEq)]
pub struct Sh2SceneLight {
    pub ambient: Vec3,
    pub dirs: [Vec3; 3],
    pub colors: [Vec3; 3],
}

impl Default for Sh2SceneLight {
    fn default() -> Self {
        Sh2SceneLight {
            ambient: Vec3::splat(0.6),
            dirs: [Vec3::new(0.35, 0.8, 0.5).normalize(), Vec3::Y, Vec3::Y],
            colors: [Vec3::new(0.55, 0.55, 0.5), Vec3::ZERO, Vec3::ZERO],
        }
    }
}

#[derive(Asset, TypePath, AsBindGroup, Clone, Debug)]
#[bind_group_data(Sh2MaterialKey)]
pub struct Sh2Material {
    /// Multiplied into the result (rgb and alpha).
    #[uniform(0)]
    pub tint: Vec4,
    /// (alpha_ref, fix_alpha, lit, blended) - see `sh2.wgsl`.
    #[uniform(0)]
    pub params: Vec4,
    #[uniform(0)]
    pub ambient: Vec4,
    #[uniform(0)]
    pub light_dir: Vec4,
    #[uniform(0)]
    pub light_color: Vec4,
    #[uniform(0)]
    pub light_dir1: Vec4,
    #[uniform(0)]
    pub light_color1: Vec4,
    #[uniform(0)]
    pub light_dir2: Vec4,
    #[uniform(0)]
    pub light_color2: Vec4,
    /// (near, far, fog_on (PRIM.FGE), scene fog enabled)
    #[uniform(0)]
    pub fog: Vec4,
    #[uniform(0)]
    pub fog_color: Vec4,
    /// (test_mode 0/1/2, gamma_space, atlas tile + 1 (0 = off), atlas tiles per row): the shadow receivers sample one tile of the silhouette atlas
    #[uniform(0)]
    pub extra: Vec4,
    #[texture(1)]
    #[sampler(2)]
    pub texture: Option<Handle<Image>>,
    pub blend: Sh2Blend,
    /// Added to the view distance used to sort blended draws: keeps the submission order of the GS (`LayerGetPacket`)
    /// between translucent groups of the same model.
    pub sort_bias: f32,
    /// This material carries its own light (`ModelLightOverride`, per-fighter stage lighting): [`sync_material_globals`] leaves its light uniforms alone.
    pub own_light: bool,
    /// GS `TEST_1.ZTST = ALWAYS` (0x33001, `FpPrim::setZtest(0)`): the draw ignores the depth buffer (lens flares, screen overlays)
    pub ztest_off: bool,
}

impl Default for Sh2Material {
    fn default() -> Self {
        Self {
            tint: Vec4::ONE,
            params: Vec4::new(-1.0, -1.0, 0.0, 0.0),
            ambient: Vec4::new(0.6, 0.6, 0.6, 1.0),
            light_dir: Vec4::new(0.35, 0.8, 0.5, 0.0).normalize(),
            light_color: Vec4::new(0.55, 0.55, 0.5, 1.0),
            light_dir1: Vec4::new(0.0, 1.0, 0.0, 0.0),
            light_color1: Vec4::ZERO,
            light_dir2: Vec4::new(0.0, 1.0, 0.0, 0.0),
            light_color2: Vec4::ZERO,
            fog: Vec4::new(10.0, 16_777_000.0, 1.0, 0.0),
            fog_color: Vec4::ZERO,
            extra: Vec4::new(0.0, 1.0, 0.0, 0.0),
            texture: None,
            blend: Sh2Blend::Opaque,
            sort_bias: 0.0,
            own_light: false,
            ztest_off: false,
        }
    }
}

impl Sh2Material {
    pub fn textured(texture: Option<Handle<Image>>) -> Self {
        Self { texture, ..default() }
    }
    pub fn with_blend(mut self, blend: Sh2Blend, fix_alpha: Option<f32>) -> Self {
        self.blend = blend;
        self.params.w = if blend == Sh2Blend::Opaque { 0.0 } else { 1.0 };
        self.params.y = fix_alpha.unwrap_or(-1.0);
        self
    }
    /// GS alpha test (`ATST = GEQUAL`, reference in 0..0x80 units): texels below the reference are discarded.
    pub fn with_alpha_ref(mut self, aref: Option<f32>) -> Self {
        self.params.x = aref.unwrap_or(-1.0);
        self
    }
    /// Split of the default `TEST_1` (see [`TestMode`]); `aref` in 0..0x80 units.
    pub fn with_test(mut self, mode: TestMode, aref: f32) -> Self {
        self.params.x = aref;
        self.extra.x = match mode {
            TestMode::Off => 0.0,
            TestMode::CutIn => 1.0,
            TestMode::Low => 2.0,
        };
        self
    }
    pub fn with_lit(mut self, lit: bool) -> Self {
        self.params.z = if lit { 1.0 } else { 0.0 };
        self
    }
    /// PRIM.FGE: apply the scene fog (colour is blended before ABE like the GS does).
    pub fn with_fog(mut self, on: bool) -> Self {
        self.fog.z = if on { 1.0 } else { 0.0 };
        self
    }
    pub fn with_ztest_off(mut self, off: bool) -> Self {
        self.ztest_off = off;
        self
    }
    pub fn with_sort_bias(mut self, bias: f32) -> Self {
        self.sort_bias = bias;
        self
    }
    pub fn test_mode(&self) -> TestMode {
        match self.extra.x as i32 {
            1 => TestMode::CutIn,
            2 => TestMode::Low,
            _ => TestMode::Off,
        }
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Hash)]
pub struct Sh2MaterialKey {
    pub blend: Sh2Blend,
    pub ztest_off: bool,
    /// material-type specific variant (`Sh2Material`: 0, 2 = shadow receiver (`extra.z` = atlas tile); `Sh2FxMaterial`: 1 = ribbon)
    pub variant: u8,
}

impl From<&Sh2Material> for Sh2MaterialKey {
    fn from(m: &Sh2Material) -> Self {
        Sh2MaterialKey { blend: m.blend, ztest_off: m.ztest_off, variant: if m.extra.z > 0.5 { 2 } else { 0 } }
    }
}

/// The GS state of [`Sh2Material`] (and `Sh2FxMaterial`): no culling, `ZTST = ALWAYS`, the three `ALPHA_1` blend equations.
pub fn sh2_specialize(descriptor: &mut RenderPipelineDescriptor, key: Sh2MaterialKey) {
    descriptor.primitive.cull_mode = None;
    if key.ztest_off {
        if let Some(ds) = descriptor.depth_stencil.as_mut() {
            ds.depth_compare = Some(::bevy::render::render_resource::CompareFunction::Always);
        }
    }
    let color = match key.blend {
        Sh2Blend::Opaque => None,
        Sh2Blend::Normal => Some(BlendComponent { src_factor: BlendFactor::SrcAlpha, dst_factor: BlendFactor::OneMinusSrcAlpha, operation: BlendOperation::Add }),
        Sh2Blend::Add => Some(BlendComponent { src_factor: BlendFactor::SrcAlpha, dst_factor: BlendFactor::One, operation: BlendOperation::Add }),
        // wgpu ReverseSubtract: dst*dst_factor - src*src_factor
        Sh2Blend::Sub => Some(BlendComponent { src_factor: BlendFactor::SrcAlpha, dst_factor: BlendFactor::One, operation: BlendOperation::ReverseSubtract }),
    };
    if let Some(fragment) = descriptor.fragment.as_mut() {
        for target in fragment.targets.iter_mut().flatten() {
            target.blend = color.map(|c| BlendState { color: c, alpha: BlendComponent::OVER });
        }
    }
}

impl Material for Sh2Material {
    fn vertex_shader() -> ShaderRef {
        ShaderRef::Handle(SH2_VERTEX_SHADER)
    }

    fn fragment_shader() -> ShaderRef {
        ShaderRef::Handle(SH2_SHADER)
    }

    fn alpha_mode(&self) -> AlphaMode {
        match self.blend {
            Sh2Blend::Opaque => AlphaMode::Opaque,
            _ => AlphaMode::Blend,
        }
    }

    fn depth_bias(&self) -> f32 {
        self.sort_bias
    }

    fn enable_prepass() -> bool {
        false
    }

    fn enable_shadows() -> bool {
        false
    }

    fn specialize(
        _pipeline: &MaterialPipeline,
        descriptor: &mut RenderPipelineDescriptor,
        layout: &MeshVertexBufferLayoutRef,
        key: MaterialPipelineKey<Self>,
    ) -> Result<(), SpecializedMeshPipelineError> {
        sh2_specialize(descriptor, key.bind_group_data);
        // GPU billboards (`billboard.rs`): skinned meshes with a corner offset in `UV_1`
        if layout.0.contains(Mesh::ATTRIBUTE_UV_1) && layout.0.contains(Mesh::ATTRIBUTE_JOINT_INDEX) {
            descriptor.vertex.shader_defs.push("SH2_BILLBOARD".into());
        }
        // GPU shadow receivers (`shadow.rs`): the skin palette is the light-plane UV matrix, the positions are not skinned
        if key.bind_group_data.variant == 2 {
            descriptor.vertex.shader_defs.push("SH2_SHADOW_RECEIVER".into());
        }
        Ok(())
    }
}

/// Final full-screen pass of the gamma-space pipeline: raw PS2 display value -> linear (clamped like the 8-bit frame buffer).
#[derive(Component, ExtractComponent, Clone, Copy, ShaderType, Default)]
pub struct Sh2GammaDecode {
    /// 1.0 = decode.
    pub enabled: f32,
    pub _pad: Vec3,
}

impl FullscreenMaterial for Sh2GammaDecode {
    fn fragment_shader() -> ShaderRef {
        ShaderRef::Handle(SH2_DECODE_SHADER)
    }
}

/// `true` while the window cameras composite in gamma space ([`setup_gamma_cameras`]: two or more cameras on the window, the last one's
/// blit decodes).  The 2D / UI draws then blend raw display values like the GS, so per-draw compensations for linear blending (the
/// menu text `gamma_alpha` of `sh2_menu::bevy_ui`) must be off.
#[derive(Resource, Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Sh2GammaCompositing(pub bool);

/// Put the cameras into the gamma-space pipeline (or take them out again).
///
/// **Window cameras (round 6 GPA): one gamma-space texture, decoded by the last blit.**  Bevy gives each distinct (target, format,
/// MSAA) its own main texture; cameras that share the key share the texture and draw on top of each other, and every camera ends with
/// an *upscaling blit* of the texture onto the window (blending off, so the last camera's blit is what the window shows).  All window
/// cameras are HDR (`Rgba16Float`, one shared texture holding raw PS2 display values) and, from the second one on, carry Bevy's
/// [`CompositingSpace::Srgb`]: their 2D meshes / sprites / text output sRGB-encoded (= raw) values (`SRGB_OUTPUT`), and their blit
/// decodes raw -> linear (`SRGB_TO_LINEAR`) for the sRGB surface.  So the 3D scene, the backdrop clear colour, the canvas sprite
/// layers, the effect 2D layers and -- through [`patch_ui_shaders`] -- Bevy UI nodes (fader, title, HUD rects / text) all blend in
/// gamma space like the GS frame buffer, and are decoded exactly once.  The first (clearing) camera keeps no compositing space so the
/// clear colour keeps the `Color::linear_rgb(raw)` convention of the field / battle / cut scene `ClearColor`.
///
/// A camera alone on its target (tools / viewers without the UI cameras, the menu model view rendering into an image) keeps the old
/// arrangement: HDR + a [`Sh2GammaDecode`] pass at the end of its 3D post-processing.  [`NativeTarget`](super::screen::NativeTarget)
/// cameras render raw values straight into the 8-bit virtual frame buffer (no HDR, no decode; the presenter draws it on the window).
#[allow(clippy::type_complexity)]
pub fn setup_gamma_cameras(
    settings: Res<Sh2ColorSpace>,
    mut compositing: ResMut<Sh2GammaCompositing>,
    mut last_window: Local<Vec<(isize, Entity)>>,
    mut commands: Commands,
    cams: Query<
        (
            Entity,
            &Camera,
            Option<&::bevy::camera::RenderTarget>,
            Option<&Sh2GammaDecode>,
            Option<&::bevy::camera::CompositingSpace>,
            Has<Camera3d>,
            Has<::bevy::camera::Hdr>,
            Has<super::screen::NativeTarget>,
            Option<&Tonemapping>,
            Option<&Name>,
        ),
        Without<super::shadow::ShadowCamera>,
    >,
) {
    use ::bevy::camera::{CompositingSpace, Hdr, RenderTarget};
    let on_window = |t: Option<&RenderTarget>| t.is_none_or(|t| matches!(t, RenderTarget::Window(_)));
    // window cameras in render order: the first one clears, the last one's blit is the picture
    let mut window: Vec<(isize, Entity)> =
        cams.iter().filter(|c| c.1.is_active && !c.7 && on_window(c.2)).map(|c| (c.1.order, c.0)).collect();
    window.sort();
    let shared = settings.gamma && settings.ui_gamma && window.len() >= 2;
    if compositing.0 != shared {
        compositing.0 = shared;
    }
    if *last_window != window {
        let names: Vec<String> = window.iter().map(|&(o, e)| format!("{o}:{}", cams.get(e).ok().and_then(|c| c.9).map(|n| n.as_str().to_string()).unwrap_or_else(|| format!("{e}")))).collect();
        log::info!("gamma: window cameras {names:?}, gamma compositing {shared}");
        *last_window = window.clone();
    }
    for (e, _, _, decode, space, is_3d, hdr, native, tonemapping, _) in &cams {
        let mut ec = commands.entity(e);
        if native && settings.gamma {
            // renders raw display values into the virtual 512 x 448 UNORM target (clamped per blend): no HDR, no decode (the presenter's camera decodes)
            if decode.is_some() || hdr || space.is_some() {
                ec.remove::<(Hdr, Sh2GammaDecode, CompositingSpace)>();
            }
            continue;
        }
        if !settings.gamma {
            if is_3d && decode.is_some() {
                ec.remove::<(Hdr, Sh2GammaDecode)>();
            }
            if space.is_some() {
                ec.remove::<CompositingSpace>();
            }
            continue;
        }
        if !hdr {
            ec.insert(Hdr);
        }
        if is_3d && tonemapping != Some(&Tonemapping::None) {
            // raw display values must reach the decode untouched
            ec.insert(Tonemapping::None);
        }
        let pos = window.iter().position(|&(_, w)| w == e);
        let (want_decode, want_space) = match pos {
            Some(i) if shared => (false, (i > 0).then_some(CompositingSpace::Srgb)),
            _ => (is_3d, None),
        };
        match (want_decode, decode.is_some()) {
            (true, false) => {
                ec.insert(Sh2GammaDecode { enabled: 1.0, ..default() });
            }
            (false, true) => {
                ec.remove::<Sh2GammaDecode>();
            }
            _ => {}
        }
        if space.copied() != want_space {
            match want_space {
                Some(s) => {
                    ec.insert(s);
                }
                None => {
                    ec.remove::<CompositingSpace>();
                }
            }
        }
    }
}

/// Bevy UI fragment shaders (`bevy_ui_render`, embedded assets) whose output [`patch_ui_shaders`] encodes for gamma-space compositing.
pub const UI_SHADER_PATHS: [&str; 4] = [
    "embedded://bevy_ui_render/ui.wgsl",
    "embedded://bevy_ui_render/ui_texture_slice.wgsl",
    "embedded://bevy_ui_render/box_shadow.wgsl",
    "embedded://bevy_ui_render/gradient.wgsl",
];
const UI_PATCH_MARK: &str = "sh2_linear_fragment";

/// Rewrite a WGSL source so its `@fragment fn fragment(..) -> @location(0) vec4<f32>` returns sRGB-encoded rgb: the original entry point
/// becomes the plain function `sh2_linear_fragment` and a new `fragment` wraps it.  `None` when the shape is not the expected one.
pub fn encode_fragment_output(src: &str) -> Option<String> {
    if src.contains(UI_PATCH_MARK) {
        return None;
    }
    let f = src.find("fn fragment(")?;
    let head = src[..f].trim_end();
    let attr = head.strip_suffix("@fragment")?.len();
    let open = f + "fn fragment(".len();
    let close = open + src[open..].find(')')?;
    let params = src[open..close].trim().trim_end_matches(',').to_string();
    if !src[close + 1..].trim_start().starts_with("-> @location(0) vec4<f32>") {
        return None;
    }
    let args: Vec<&str> = params.split(',').map(|p| p.split(':').next().unwrap_or("").trim()).filter(|a| !a.is_empty()).collect();
    if args.iter().any(|a| a.starts_with('@')) {
        return None;
    }
    // a plain function may not carry `@location` on its return type
    let rest = src[open..].replacen("-> @location(0) vec4<f32>", "-> vec4<f32>", 1);
    Some(format!(
        "{}fn {UI_PATCH_MARK}({}\n\n\
         // sh2 (sh2_gfx::bevy::material::patch_ui_shaders): gamma-space compositing, the target holds raw (sRGB-encoded) display values\n\
         fn sh2_encode(c: f32) -> f32 {{\n    if c <= 0.0031308 {{ return max(c, 0.0) * 12.92; }}\n    return 1.055 * pow(c, 1.0 / 2.4) - 0.055;\n}}\n\n\
         @fragment\nfn fragment({params}) -> @location(0) vec4<f32> {{\n    let c = {UI_PATCH_MARK}({});\n    return vec4<f32>(sh2_encode(c.r), sh2_encode(c.g), sh2_encode(c.b), c.a);\n}}\n",
        &src[..attr],
        rest,
        args.join(", ")
    ))
}

/// Bevy UI has no notion of [`CompositingSpace`](::bevy::camera::CompositingSpace): its shaders always output linear colour.  While
/// [`Sh2GammaCompositing`] is on, the UI camera composites into the raw (gamma) texture, so the UI fragment shaders are patched to
/// output sRGB-encoded values ([`encode_fragment_output`]); `Color`s / sRGB textures of the nodes keep their meaning (`encode(c * t)`
/// is `raw(c) * raw(t)` up to the sRGB curve's linear toe), only the blend now happens on display values like the GS.  The original
/// sources are restored when the compositing turns off again.
pub fn patch_ui_shaders(
    on: Res<Sh2GammaCompositing>,
    server: Res<AssetServer>,
    mut shaders: ResMut<Assets<Shader>>,
    mut state: Local<Vec<(Handle<Shader>, Option<::bevy::shader::Source>, bool)>>,
) {
    if state.is_empty() {
        if !on.0 {
            return;
        }
        *state = UI_SHADER_PATHS.iter().map(|p| (server.load::<Shader>(*p), None, false)).collect();
    }
    for (h, original, patched) in state.iter_mut() {
        if *patched == on.0 {
            continue;
        }
        let Some(sh) = shaders.get(&*h) else { continue };
        if on.0 {
            let ::bevy::shader::Source::Wgsl(src) = &sh.source else {
                *patched = true;
                continue;
            };
            match encode_fragment_output(src) {
                Some(new_src) => {
                    *original = Some(sh.source.clone());
                    if let Some(mut sh) = shaders.get_mut(&*h) {
                        sh.source = ::bevy::shader::Source::Wgsl(new_src.into());
                    }
                }
                None => log::warn!("gamma UI: could not patch {:?}; Bevy UI there blends in linear light", sh.path),
            }
            *patched = true;
        } else {
            if let Some(src) = original.take() {
                if let Some(mut sh) = shaders.get_mut(&*h) {
                    sh.source = src;
                }
            }
            *patched = false;
        }
    }
}

/// Push fog, scene lights and the colour-space switch into every material (only when something changed).
#[allow(clippy::too_many_arguments)]
pub fn sync_material_globals(
    fog: Res<Sh2Fog>,
    light: Res<Sh2SceneLight>,
    settings: Res<Sh2ColorSpace>,
    mut materials: ResMut<Assets<Sh2Material>>,
    mut last_count: Local<usize>,
    mut last_state: Local<Option<(Sh2Fog, Sh2SceneLight, bool)>>,
) {
    let count = materials.len();
    let state = (*fog, light.clone(), settings.gamma);
    if *last_count == count && last_state.as_ref() == Some(&state) {
        return;
    }
    *last_count = count;
    *last_state = Some(state);
    let fogv = Vec4::new(fog.near, fog.far, 0.0, 0.0);
    let fogc = fog.color.extend(1.0);
    let gamma = if settings.gamma { 1.0 } else { 0.0 };
    let amb = light.ambient.extend(1.0);
    let l = |i: usize| (light.dirs[i].normalize_or_zero().extend(0.0), light.colors[i].extend(1.0));
    let (d0, c0) = l(0);
    let (d1, c1) = l(1);
    let (d2, c2) = l(2);
    let fog_w = if fog.enabled { 1.0 } else { 0.0 };
    let lit = (amb, d0, c0, d1, c1, d2, c2);
    let apply = |m: &mut Sh2Material| {
        m.fog.x = fogv.x;
        m.fog.y = fogv.y;
        m.fog.w = fog_w;
        m.fog_color = fogc;
        m.extra.y = gamma;
        if m.params.z > 0.5 && !m.own_light {
            (m.ambient, m.light_dir, m.light_color, m.light_dir1, m.light_color1, m.light_dir2, m.light_color2) = lit;
        }
    };
    // only the materials that differ are written: `iter_mut` / `get_mut` mark an asset modified, and every modified material is re-prepared
    // (new bind group) and its entities re-specialised in the render world -- writing all of them whenever one material was added (effects,
    // per-instance copies) re-uploaded hundreds of materials in one frame
    let stale: Vec<AssetId<Sh2Material>> = materials
        .iter()
        .filter(|(_, m)| {
            let mut c = (*m).clone();
            apply(&mut c);
            c.fog != m.fog || c.fog_color != m.fog_color || c.extra != m.extra || c.ambient != m.ambient || c.light_dir != m.light_dir
                || c.light_color != m.light_color || c.light_dir1 != m.light_dir1 || c.light_color1 != m.light_color1 || c.light_dir2 != m.light_dir2
                || c.light_color2 != m.light_color2
        })
        .map(|(id, _)| id)
        .collect();
    for id in stale {
        if let Some(mut m) = materials.get_mut(id) {
            apply(&mut *m);
        }
    }
}

/// Registers the shader and the material.
pub struct Sh2MaterialPlugin;

impl Plugin for Sh2MaterialPlugin {
    fn build(&self, app: &mut App) {
        load_internal_asset!(app, SH2_SHADER, "sh2.wgsl", Shader::from_wgsl);
        load_internal_asset!(app, SH2_DECODE_SHADER, "sh2_decode.wgsl", Shader::from_wgsl);
        load_internal_asset!(app, SH2_VERTEX_SHADER, "sh2_vertex.wgsl", Shader::from_wgsl);
        app.init_resource::<Sh2Fog>()
            .init_resource::<Sh2SceneLight>()
            .init_resource::<Sh2ColorSpace>()
            .init_resource::<Sh2GammaCompositing>()
            .add_plugins(MaterialPlugin::<Sh2Material>::default())
            .add_plugins(FullscreenMaterialPlugin::<Sh2GammaDecode>::default())
            .add_systems(PostUpdate, ((setup_gamma_cameras, patch_ui_shaders).chain(), sync_material_globals))
            .add_systems(Startup, super::model::spawn_skin_joint)
            .add_systems(Update, super::model::drop_unwanted_shadows.before(super::model::animate_models))
            .add_plugins((super::fxquad::Sh2FxQuadPlugin, super::perf::Sh2PerfPlugin, super::shadow::Sh2ShadowPlugin));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn texture_alpha_bits_map_to_gs_modes() {
        assert_eq!(texture_blend(0).0, Sh2Blend::Opaque);
        assert_eq!(texture_blend(0x44).0, Sh2Blend::Normal);
        assert_eq!(texture_blend(0x48).0, Sh2Blend::Add);
        assert_eq!(texture_blend(0x42).0, Sh2Blend::Sub);
        assert_eq!(texture_blend(0x2064).1, Some(0x20 as f32 / 128.0));
        assert_eq!(texture_blend(0x44).1, None);
    }

    #[test]
    fn ui_fragment_gets_encoded() {
        let src = "#import x
fn helper() {}
@fragment
fn fragment(
    in: VertexOutput,
) -> @location(0) vec4<f32> {
    return in.color;
}
";
        let out = encode_fragment_output(src).expect("patch");
        assert!(out.contains("fn sh2_linear_fragment(
    in: VertexOutput,
) -> vec4<f32> {
    return in.color;"));
        assert_eq!(out.matches("@fragment").count(), 1);
        assert!(out.contains("fn fragment(in: VertexOutput) -> @location(0) vec4<f32> {
    let c = sh2_linear_fragment(in);"));
        // idempotent, and unknown shapes are left alone
        assert!(encode_fragment_output(&out).is_none());
        assert!(encode_fragment_output("fn fragment(in: V) -> vec4<f32> { }").is_none());
    }

    #[test]
    fn test_modes_roundtrip() {
        let m = Sh2Material::default().with_test(TestMode::Low, DEFAULT_ALPHA_REF);
        assert_eq!(m.test_mode(), TestMode::Low);
        assert_eq!(Sh2Material::default().with_test(TestMode::CutIn, 1.0).test_mode(), TestMode::CutIn);
        assert_eq!(Sh2Material::default().test_mode(), TestMode::Off);
    }
}
