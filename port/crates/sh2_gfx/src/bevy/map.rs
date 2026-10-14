//! Field-map (BG) models: per-atomic GS state -> Bevy draws.
//!
//! Everything a `Pack1Atomic` tells the GS lives in two places (see `notes/integration/renderer.md`):
//!
//! * the atomic header `+0x10` u16 = the **PRIM register** of the strip (`Pack1Atomic::initPacket` writes it into the GIF tag with PRE=1):
//!   bit 4 TME, bit 5 FGE (fog), bit 6 ABE (alpha blend), bit 7 AA1; all shipped map atomics use `0x7c` (TRISTRIP | IIP | TME | FGE | ABE);
//! * the texture (`Texture::createRegsterPacket` / `CreateData`): `ALPHA_1` defaults to `0x44` (`(Cs-Cd)*As+Cd`) unless the TIHD
//!   carries its own bits, `TEST_1` defaults to `0x5370b` (ATE, GEQUAL, AREF 0x70, AFAIL = RGB_ONLY) unless the TIHD has a reference.
//!
//! Hence *every* map surface is alpha blended by its texture alpha; texels with `A >= 0x70` write colour and depth, texels below write only colour
//! (translucent shadows, window glass, foliage / lamp-halo cut-outs).  Bevy draws that as two entities per group ([`TestMode::CutIn`] in the
//! opaque phase, [`TestMode::Low`] in the blend phase) when the texture really contains both kinds of texels.
//!
//! Atomics of one model are merged by `(name, texture, PRIM bits)` so that a script/event that hides an atomic by name
//! (`Visible ` motion event) can toggle a whole [`BgAtomicGroup`] entity.  The `Pack1` vertex colours are passed through by the VU1
//! microcode unchanged (no light / colour inputs reach it), so map darkness is baked, not computed.

use ::bevy::prelude::*;
use sh2_formats::model::{AtomicDef, AtomicKind, Model, TexFormat, TextureDef};
use std::collections::BTreeMap;

use super::image::texture_def_image;
use super::material::{texture_blend, Sh2Blend, Sh2Material, TestMode, DEFAULT_ALPHA_REF};
use super::mesh::{atomics_mesh, drawable};
use super::model::GpuCtx;

/// Marker + identity of one merged group of atomics of a BG model.  Toggle `Visibility` on it (and its children) to hide an atomic by name.
#[derive(Component, Clone, Debug)]
pub struct BgAtomicGroup {
    pub model: String,
    pub atomic: String,
}

/// Which GS state the draw of a group uses (diagnostics / tests).
#[derive(Clone, Debug, PartialEq)]
pub struct DrawState {
    pub blend: Sh2Blend,
    pub test: TestMode,
    pub aref: f32,
    pub fog: bool,
    pub textured: bool,
}

/// What [`plan_draws`] decided for one `(atomic state, texture)` pair.
#[derive(Clone, Debug, PartialEq)]
pub struct DrawPlan {
    pub draws: Vec<DrawState>,
}

/// Texel alpha census of a texture (GS alpha units 0..0x80).
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub struct AlphaCensus {
    pub any_below: bool,
    pub any_at_or_above: bool,
}

pub fn alpha_census(rgba: &[u8], aref_gs: f32) -> AlphaCensus {
    let mut c = AlphaCensus::default();
    for px in rgba.chunks_exact(4) {
        // u8 alpha = min(a*2, 255) -> 0..0x80 units
        if (px[3] as f32) * 0.5 < aref_gs {
            c.any_below = true;
        } else {
            c.any_at_or_above = true;
        }
        if c.any_below && c.any_at_or_above {
            break;
        }
    }
    c
}

/// Combine PRIM bits, texture ALPHA_1/TEST_1 state and the texel census into Bevy draws (see the module docs).
pub fn plan_draws(prim_flags: u16, tex: Option<&TextureDef>, census: AlphaCensus) -> DrawPlan {
    let tme = prim_flags & 0x10 != 0 && tex.is_some();
    let fog = prim_flags & 0x20 != 0;
    let abe = prim_flags & 0x40 != 0;
    let mk = |blend, test, aref| DrawState { blend, test, aref, fog, textured: tme };
    if !abe {
        return DrawPlan { draws: vec![mk(Sh2Blend::Opaque, TestMode::Off, -1.0)] };
    }
    let Some(t) = tex.filter(|_| tme) else {
        // untextured, vertex alpha only (0x80 everywhere in shipped data)
        return DrawPlan { draws: vec![mk(Sh2Blend::Opaque, TestMode::Off, -1.0)] };
    };
    let (blend, _fix) = texture_blend(t.alpha_bits);
    if blend != Sh2Blend::Opaque {
        // the texture brought its own ALPHA_1 (additive glows, ...): one blended draw; a TIHD reference with AFAIL=KEEP also discards
        let (test, aref) = if t.alpha_ref != 0 && t.flags & 3 == 0 { (TestMode::CutIn, t.alpha_ref as f32) } else { (TestMode::Off, -1.0) };
        return DrawPlan { draws: vec![mk(blend, test, aref)] };
    }
    // register default ALPHA_1 = 0x44; TEST_1 default (AREF 0x70, RGB_ONLY) or from the header (GEQUAL ref, AFAIL = flags & 3)
    let (aref, afail) = if t.alpha_ref != 0 { (t.alpha_ref as f32, t.flags & 3) } else { (DEFAULT_ALPHA_REF, 3) };
    let mut draws = Vec::new();
    if census.any_at_or_above {
        // texels that pass: blended by their (high) alpha; with the default reference that is >= 0.875, i.e. opaque for our purposes
        let b = if aref >= DEFAULT_ALPHA_REF { Sh2Blend::Opaque } else { Sh2Blend::Normal };
        let test = if census.any_below { TestMode::CutIn } else { TestMode::Off };
        draws.push(mk(b, test, aref));
    }
    if census.any_below && (afail == 1 || afail == 3) {
        draws.push(mk(Sh2Blend::Normal, TestMode::Low, aref));
    }
    if draws.is_empty() {
        // every texel fails and nothing is written (AFAIL = KEEP / ZB_ONLY): nothing to draw
        draws.push(mk(Sh2Blend::Normal, TestMode::Low, aref));
    }
    DrawPlan { draws }
}

/// Textures of a model as Bevy images plus the per-texture alpha census.
pub struct MapTextures {
    pub images: Vec<Handle<Image>>,
    pub census: Vec<AlphaCensus>,
    /// `ipum` (MPEG-2 intra movie) textures: (texture index, image, decoded frames)
    pub ipu: Vec<(usize, Handle<Image>, std::sync::Arc<crate::ipu::IpuMovie>)>,
}

/// Plays a decoded `ipum` movie into an image (`IPUTexture::decodeFrame` runs once per displayed frame; the port steps at 30 fps and loops).
#[derive(Component)]
pub struct IpuTextureAnim {
    pub image: Handle<Image>,
    pub movie: std::sync::Arc<crate::ipu::IpuMovie>,
    pub time: f32,
    pub fps: f32,
    shown: usize,
}

pub fn ipu_texture_system(time: Res<Time>, mut q: Query<&mut IpuTextureAnim>, mut images: ResMut<Assets<Image>>) {
    for mut a in &mut q {
        a.time += time.delta_secs();
        let n = a.movie.frames.len().max(1);
        let k = ((a.time * a.fps) as usize) % n;
        if k != a.shown {
            a.shown = k;
            if let Some(mut img) = images.get_mut(&a.image) {
                if let Some(d) = img.data.as_mut() {
                    let f = &a.movie.frames[k];
                    if d.len() == f.len() {
                        d.copy_from_slice(f);
                    }
                }
            }
        }
    }
}

/// Spawn the animation drivers of the movie textures of `tex` (children of `parent`).
pub fn spawn_ipu_anims(commands: &mut Commands, parent: Entity, tex: &MapTextures) {
    for (_, h, movie) in &tex.ipu {
        let e = commands.spawn((Name::new("ipu_texture"), IpuTextureAnim { image: h.clone(), movie: movie.clone(), time: 0.0, fps: 30.0, shown: 0 })).id();
        commands.entity(parent).add_child(e);
    }
}

impl MapTextures {
    pub fn new(textures: &[TextureDef], gpu: &mut GpuCtx) -> Self {
        Self::with_animated(textures, gpu, &[])
    }

    /// `animated`: texture indices whose pixels are rewritten at run time (TXAH): their images keep a CPU copy.
    pub fn with_animated(textures: &[TextureDef], gpu: &mut GpuCtx, animated: &[usize]) -> Self {
        let mut images = Vec::new();
        let mut census = Vec::new();
        let mut ipu = Vec::new();
        for (ti, t) in textures.iter().enumerate() {
            let mut movie = None;
            let rgba = if matches!(t.format, TexFormat::Ipu) {
                match crate::ipu::decode_ipum(&t.data) {
                    Ok(m) if m.width == t.width as usize && m.height == t.height as usize && !m.frames.is_empty() => {
                        let f = m.frames[0].clone();
                        movie = Some(std::sync::Arc::new(m));
                        f
                    }
                    Ok(_) => t.to_rgba8(),
                    Err(e) => {
                        warn!("IPU texture {ti}: {e}");
                        t.to_rgba8()
                    }
                }
            } else {
                t.to_rgba8()
            };
            let aref = if t.alpha_ref != 0 { t.alpha_ref as f32 } else { DEFAULT_ALPHA_REF };
            census.push(if matches!(t.format, TexFormat::Ipu) { AlphaCensus { any_below: false, any_at_or_above: true } } else { alpha_census(&rgba, aref) });
            let mut img = super::image::rgba_image(t.width as u32, t.height as u32, rgba, gpu.filter);
            if animated.contains(&ti) || movie.is_some() {
                img.asset_usage = ::bevy::asset::RenderAssetUsages::default();
            }
            let h = gpu.images.add(img);
            if let Some(m) = movie {
                ipu.push((ti, h.clone(), m));
            }
            images.push(h);
        }
        let _ = texture_def_image; // keep the public helper linked for other callers
        MapTextures { images, census, ipu }
    }
}

/// Summary of one spawned model.
#[derive(Clone, Debug, Default)]
pub struct MapModelStats {
    pub atomics: usize,
    pub groups: usize,
    pub draws: usize,
    pub two_pass_groups: usize,
    pub skipped_billboards: usize,
}


/// One spawned draw (entity + its material) of an atomic group; kept so events can change visibility / alpha later.
#[derive(Clone, Debug)]
pub struct DrawHandle {
    pub entity: Entity,
    pub material: Handle<Sh2Material>,
    /// Blend mode of the draw before any model/atomic alpha fade was applied.
    pub base_blend: Sh2Blend,
}

/// Spawn the draws of `plan` for `mesh` as children of `parent`.  `first` (index of the first atomic of the group) orders translucent draws.
#[allow(clippy::too_many_arguments)]
pub fn spawn_draws(commands: &mut Commands, parent: Entity, gpu: &mut GpuCtx, mesh: &Handle<Mesh>, plan: &DrawPlan, t: Option<&TextureDef>, img: Option<Handle<Image>>, first: usize) -> Vec<DrawHandle> {
    let mut out = Vec::new();
    for d in &plan.draws {
        let (blend, fix) = match t.map(|t| texture_blend(t.alpha_bits)) {
            Some((b, f)) if d.blend != Sh2Blend::Opaque && b != Sh2Blend::Opaque => (b, f),
            _ => (d.blend, None),
        };
        let mut m = Sh2Material::textured(img.clone()).with_blend(blend, fix).with_fog(d.fog);
        m = match d.test {
            TestMode::Off => m.with_alpha_ref(None),
            mode => m.with_test(mode, d.aref),
        };
        if blend != Sh2Blend::Opaque {
            // keep the GS submission order between translucent groups of one model
            m = m.with_sort_bias(first as f32 * 0.002);
        }
        let handle = gpu.materials.add(m);
        let child = commands.spawn((Mesh3d(mesh.clone()), MeshMaterial3d(handle.clone()), Transform::default(), Visibility::default())).id();
        commands.entity(parent).add_child(child);
        out.push(DrawHandle { entity: child, material: handle, base_blend: blend });
    }
    out
}

type GroupKey = (String, u8, u16);

/// Spawn the drawable atomics of a map model under `parent` at `local`.  Returns the holder entity.
pub fn spawn_map_model(commands: &mut Commands, parent: Entity, model: &Model, gpu: &mut GpuCtx, local: Transform, name: &str) -> (Entity, MapModelStats) {
    let tex = MapTextures::new(&model.textures, gpu);
    let mut stats = MapModelStats::default();
    let holder = commands.spawn((Name::new(name.to_owned()), local, Visibility::default())).id();
    commands.entity(parent).add_child(holder);
    spawn_ipu_anims(commands, holder, &tex);

    let mut groups: BTreeMap<GroupKey, (usize, Vec<&AtomicDef>)> = BTreeMap::new();
    for (i, a) in model.atomics.iter().enumerate() {
        if matches!(a.kind, AtomicKind::Billboard) {
            stats.skipped_billboards += 1;
        }
        if !drawable(a) {
            continue;
        }
        stats.atomics += 1;
        // PRIM bits 4..7 matter for state; the low bits (strip type) are fixed by the loader
        let e = groups.entry((a.name.clone(), a.texture, a.flags & 0xf0)).or_insert_with(|| (i, Vec::new()));
        e.0 = e.0.min(i);
        e.1.push(a);
    }

    for ((aname, tex_idx, prim), (first, atoms)) in groups {
        let t = model.textures.get(tex_idx as usize);
        let census = tex.census.get(tex_idx as usize).copied().unwrap_or(AlphaCensus { any_below: false, any_at_or_above: true });
        let plan = plan_draws(prim, t, census);
        let mesh = gpu.meshes.add(atomics_mesh(&atoms));
        let img = tex.images.get(tex_idx as usize).cloned().filter(|_| prim & 0x10 != 0);
        let group_e = commands
            .spawn((Name::new(format!("{aname}#{first}")), BgAtomicGroup { model: name.to_owned(), atomic: aname.clone() }, Transform::default(), Visibility::default()))
            .id();
        commands.entity(holder).add_child(group_e);
        stats.groups += 1;
        if plan.draws.len() > 1 {
            stats.two_pass_groups += 1;
        }
        let handles = spawn_draws(commands, group_e, gpu, &mesh, &plan, t, img.clone(), first);
        stats.draws += handles.len();
    }
    (holder, stats)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn tex(alpha_bits: u16, aref: u8, flags: u8) -> TextureDef {
        TextureDef {
            width: 4,
            height: 4,
            format: TexFormat::Psmt8,
            raw_format: 8,
            mip_levels: 0,
            palette: vec![],
            data: vec![],
            alpha_bits,
            alpha_ref: aref,
            flags,
            file_offset: 0,
        }
    }

    #[test]
    fn default_state_splits_translucent_texels() {
        let t = tex(0, 0, 0);
        let both = AlphaCensus { any_below: true, any_at_or_above: true };
        let p = plan_draws(0x7c, Some(&t), both);
        assert_eq!(p.draws.len(), 2);
        assert_eq!(p.draws[0].test, TestMode::CutIn);
        assert_eq!(p.draws[0].blend, Sh2Blend::Opaque);
        assert_eq!(p.draws[1].test, TestMode::Low);
        assert_eq!(p.draws[1].blend, Sh2Blend::Normal);
        assert!(p.draws[0].fog);
        // fully opaque texture: one opaque draw
        let p = plan_draws(0x7c, Some(&t), AlphaCensus { any_below: false, any_at_or_above: true });
        assert_eq!(p.draws.len(), 1);
        assert_eq!(p.draws[0].test, TestMode::Off);
    }

    #[test]
    fn abe_off_and_additive() {
        let t = tex(0x48, 0, 0);
        let c = AlphaCensus { any_below: true, any_at_or_above: true };
        assert_eq!(plan_draws(0x3c, Some(&t), c).draws[0].blend, Sh2Blend::Opaque);
        assert_eq!(plan_draws(0x7c, Some(&t), c).draws[0].blend, Sh2Blend::Add);
    }

    #[test]
    fn header_reference_with_keep_is_a_cutout() {
        let t = tex(0, 0x40, 0);
        let c = AlphaCensus { any_below: true, any_at_or_above: true };
        let p = plan_draws(0x7c, Some(&t), c);
        assert_eq!(p.draws.len(), 1, "AFAIL=KEEP discards failing texels completely");
        assert_eq!(p.draws[0].test, TestMode::CutIn);
        assert_eq!(p.draws[0].blend, Sh2Blend::Normal, "reference below 0x70: passing texels are still blended");
    }

    #[test]
    fn census_counts_gs_units() {
        // u8 alpha 224 == 0x70 GS units
        assert_eq!(alpha_census(&[0, 0, 0, 224], 112.0), AlphaCensus { any_below: false, any_at_or_above: true });
        assert_eq!(alpha_census(&[0, 0, 0, 222], 112.0), AlphaCensus { any_below: true, any_at_or_above: false });
    }
}
