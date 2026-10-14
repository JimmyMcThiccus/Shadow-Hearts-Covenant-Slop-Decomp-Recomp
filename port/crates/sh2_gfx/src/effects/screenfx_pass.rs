//! Generic full-screen post pass for the effect VM's screen effects.
//!
//! Bevy 0.19's `FullscreenMaterial` keeps its pipeline id in a *single non-generic component*, so two such materials on the same camera (the gamma decode of
//! [`crate::bevy::material::Sh2GammaDecode`] and any effect) overwrite each other's pipeline.  [`ScreenFxPlugin<T>`] is the same pass (source texture + sampler + a
//! dynamic uniform of `T`, one full-screen triangle, `post_process_write` ping-pong) with per-type components, and optionally a persistent **snapshot** texture (binding 3):
//! when [`ScreenFx::capture_now`] is true the incoming frame is first copied into the snapshot through the shader's `capture` entry point (`EffectBarin` stores the
//! frame buffer once with `LocalHostImage::StoreImage` and re-uploads it every frame).

use std::marker::PhantomData;

use ::bevy::core_pipeline::schedule::Core3d;
use ::bevy::core_pipeline::{tonemapping::tonemapping, Core3dSystems, FullscreenShader};
use ::bevy::ecs::error::BevyError;
use ::bevy::ecs::schedule::{IntoScheduleConfigs, ScheduleConfigs};
use ::bevy::ecs::system::BoxedSystem;
use ::bevy::prelude::*;
use ::bevy::render::camera::ExtractedCamera;
use ::bevy::render::extract_component::{ComponentUniforms, DynamicUniformIndex, ExtractComponent, ExtractComponentPlugin, UniformComponentPlugin};
use ::bevy::render::render_resource::binding_types::{sampler, texture_2d, uniform_buffer};
use ::bevy::render::render_resource::encase::internal::WriteInto;
use ::bevy::render::render_resource::*;
use ::bevy::render::renderer::{RenderContext, RenderDevice, ViewQuery};
use ::bevy::render::view::{ExtractedView, ViewTarget};
use ::bevy::render::{Render, RenderApp, RenderStartup, RenderSystems};
use ::bevy::shader::ShaderRef;

use crate::bevy::material::Sh2GammaDecode;

pub trait ScreenFx: Component + ExtractComponent + Clone + Copy + ShaderType + WriteInto + Default {
    fn fragment_shader() -> ShaderRef;
    /// bind a persistent snapshot texture at binding 3 (and provide a `capture` fragment entry point)
    const SNAPSHOT: bool = false;
    /// copy the incoming frame into the snapshot before drawing (this frame only)
    fn capture_now(&self) -> bool {
        false
    }
}

#[derive(Resource)]
pub struct ScreenFxPipeline<T: ScreenFx> {
    layout: BindGroupLayoutDescriptor,
    sampler: Sampler,
    variants: Variants<RenderPipeline, Spec>,
    _m: PhantomData<T>,
}

struct Spec;

#[derive(PartialEq, Eq, Hash, Clone, Copy, SpecializerKey)]
struct Key {
    format: TextureFormat,
    capture: bool,
}

impl Specializer<RenderPipeline> for Spec {
    type Key = Key;
    fn specialize(&self, key: Self::Key, descriptor: &mut RenderPipelineDescriptor) -> Result<Canonical<Self::Key>, BevyError> {
        let fragment = descriptor.fragment_mut()?;
        fragment.set_target(0, ColorTargetState { format: key.format, blend: None, write_mask: ColorWrites::ALL });
        fragment.entry_point = Some(if key.capture { "capture" } else { "fragment" }.into());
        Ok(key)
    }
}

fn init_pipeline<T: ScreenFx>(mut commands: Commands, render_device: Res<RenderDevice>, asset_server: Res<AssetServer>, fullscreen_shader: Res<FullscreenShader>) {
    let layout = if T::SNAPSHOT {
        BindGroupLayoutDescriptor::new(
            "screenfx_bind_group_layout",
            &BindGroupLayoutEntries::sequential(
                ShaderStages::FRAGMENT,
                (
                    texture_2d(TextureSampleType::Float { filterable: true }),
                    sampler(SamplerBindingType::Filtering),
                    uniform_buffer::<T>(true),
                    texture_2d(TextureSampleType::Float { filterable: true }),
                ),
            ),
        )
    } else {
        BindGroupLayoutDescriptor::new(
            "screenfx_bind_group_layout",
            &BindGroupLayoutEntries::sequential(
                ShaderStages::FRAGMENT,
                (texture_2d(TextureSampleType::Float { filterable: true }), sampler(SamplerBindingType::Filtering), uniform_buffer::<T>(true)),
            ),
        )
    };
    let sampler = render_device.create_sampler(&SamplerDescriptor { address_mode_u: AddressMode::ClampToEdge, address_mode_v: AddressMode::ClampToEdge, mag_filter: FilterMode::Linear, min_filter: FilterMode::Linear, ..default() });
    let shader = match T::fragment_shader() {
        ShaderRef::Handle(h) => h,
        ShaderRef::Path(p) => asset_server.load(p),
        ShaderRef::Default => unimplemented!("ScreenFx::fragment_shader must not be Default"),
    };
    let desc = RenderPipelineDescriptor {
        label: Some(format!("screenfx_pipeline<{}>", std::any::type_name::<T>()).into()),
        layout: vec![layout.clone()],
        vertex: fullscreen_shader.to_vertex_state(),
        fragment: Some(FragmentState {
            shader,
            targets: vec![Some(ColorTargetState { format: TextureFormat::Rgba8UnormSrgb, blend: None, write_mask: ColorWrites::ALL })],
            ..default()
        }),
        ..default()
    };
    commands.insert_resource(ScreenFxPipeline::<T> { layout, sampler, variants: Variants::new(Spec, desc), _m: PhantomData });
}

#[derive(Component)]
struct Pipelines<T: ScreenFx> {
    main: CachedRenderPipelineId,
    capture: Option<CachedRenderPipelineId>,
    _m: PhantomData<T>,
}

fn prepare_pipelines<T: ScreenFx>(
    mut commands: Commands,
    cache: Res<PipelineCache>,
    mut pipeline: ResMut<ScreenFxPipeline<T>>,
    views: Query<(Entity, &ExtractedView, Option<&T>), With<ExtractedCamera>>,
) -> Result<(), BevyError> {
    for (e, view, fx) in &views {
        if fx.is_none() {
            commands.entity(e).remove::<Pipelines<T>>();
            continue;
        }
        let main = pipeline.variants.specialize(&cache, Key { format: view.target_format, capture: false })?;
        let capture = if T::SNAPSHOT { Some(pipeline.variants.specialize(&cache, Key { format: view.target_format, capture: true })?) } else { None };
        commands.entity(e).insert(Pipelines::<T> { main, capture, _m: PhantomData });
    }
    Ok(())
}

/// The persistent snapshot of the frame (same size and format as the view target).
#[derive(Component)]
pub struct Snapshot<T: ScreenFx> {
    pub texture: Texture,
    pub view: TextureView,
    pub size: UVec2,
    pub format: TextureFormat,
    /// a snapshot has been captured at least once (the first frame of the effect stores the frame)
    pub filled: std::sync::Arc<std::sync::atomic::AtomicBool>,
    _m: PhantomData<T>,
}

fn prepare_snapshots<T: ScreenFx>(mut commands: Commands, device: Res<RenderDevice>, views: Query<(Entity, &ViewTarget, Option<&T>, Option<&Snapshot<T>>)>) {
    if !T::SNAPSHOT {
        return;
    }
    for (e, target, fx, snap) in &views {
        if fx.is_none() {
            if snap.is_some() {
                commands.entity(e).remove::<Snapshot<T>>();
            }
            continue;
        }
        let tex = target.main_texture();
        let size = UVec2::new(tex.width(), tex.height());
        let format = target.main_texture_format();
        if snap.map(|s| s.size == size && s.format == format).unwrap_or(false) {
            continue;
        }
        let texture = device.create_texture(&TextureDescriptor {
            label: Some("screenfx_snapshot"),
            size: Extent3d { width: size.x, height: size.y, depth_or_array_layers: 1 },
            mip_level_count: 1,
            sample_count: 1,
            dimension: TextureDimension::D2,
            format,
            usage: TextureUsages::RENDER_ATTACHMENT | TextureUsages::TEXTURE_BINDING,
            view_formats: &[],
        });
        let view = texture.create_view(&TextureViewDescriptor::default());
        commands.entity(e).insert(Snapshot::<T> { texture, view, size, format, filled: std::sync::Arc::new(std::sync::atomic::AtomicBool::new(false)), _m: PhantomData });
    }
}

#[allow(clippy::type_complexity)]
fn screenfx_system<T: ScreenFx>(
    view: ViewQuery<(&ViewTarget, &T, &DynamicUniformIndex<T>, &Pipelines<T>, Option<&Snapshot<T>>)>,
    cache: Res<PipelineCache>,
    pipeline: Res<ScreenFxPipeline<T>>,
    uniforms: Res<ComponentUniforms<T>>,
    mut ctx: RenderContext,
) {
    let (target, fx, index, pipes, snap) = view.into_inner();
    let Some(binding) = uniforms.uniforms().binding() else { return };
    let Some(main) = cache.get_render_pipeline(pipes.main) else { return };
    let layout = cache.get_bind_group_layout(&pipeline.layout);
    let pp = target.post_process_write();
    let (source, destination) = (pp.source, pp.destination);

    let make_bind_group = |ctx: &RenderContext, tex: &TextureView, snapshot: Option<&TextureView>| {
        if T::SNAPSHOT {
            ctx.render_device().create_bind_group("screenfx_bind_group", &layout, &BindGroupEntries::sequential((tex, &pipeline.sampler, binding.clone(), snapshot.unwrap_or(tex))))
        } else {
            ctx.render_device().create_bind_group("screenfx_bind_group", &layout, &BindGroupEntries::sequential((tex, &pipeline.sampler, binding.clone())))
        }
    };

    // capture: source -> snapshot
    let first = snap.map(|s| !s.filled.load(std::sync::atomic::Ordering::Relaxed)).unwrap_or(false);
    if T::SNAPSHOT && (fx.capture_now() || first) {
        if let (Some(snap), Some(cap_id)) = (snap, pipes.capture) {
            snap.filled.store(true, std::sync::atomic::Ordering::Relaxed);
            if let Some(cap) = cache.get_render_pipeline(cap_id) {
                let bg = make_bind_group(&ctx, source, None);
                let pass = RenderPassDescriptor {
                    label: Some("screenfx_capture"),
                    color_attachments: &[Some(RenderPassColorAttachment { view: &snap.view, depth_slice: None, resolve_target: None, ops: Operations::default() })],
                    depth_stencil_attachment: None,
                    timestamp_writes: None,
                    occlusion_query_set: None,
                    multiview_mask: None,
                };
                let mut rp = ctx.command_encoder().begin_render_pass(&pass);
                rp.set_pipeline(cap);
                rp.set_bind_group(0, &bg, &[index.index()]);
                rp.draw(0..3, 0..1);
            }
        }
    }

    let bg = make_bind_group(&ctx, source, snap.map(|s| &s.view));
    let pass = RenderPassDescriptor {
        label: Some("screenfx_pass"),
        color_attachments: &[Some(RenderPassColorAttachment { view: destination, depth_slice: None, resolve_target: None, ops: Operations::default() })],
        depth_stencil_attachment: None,
        timestamp_writes: None,
        occlusion_query_set: None,
        multiview_mask: None,
    };
    let mut rp = ctx.command_encoder().begin_render_pass(&pass);
    rp.set_pipeline(main);
    rp.set_bind_group(0, &bg, &[index.index()]);
    rp.draw(0..3, 0..1);
}

/// Order of the pass: after the 3D scene, before tonemapping and before the gamma decode of the raw display values.
pub fn order(system: ScheduleConfigs<BoxedSystem>) -> ScheduleConfigs<BoxedSystem> {
    system.in_set(Core3dSystems::PostProcess).before(tonemapping).before(::bevy::core_pipeline::fullscreen_material::fullscreen_material_system::<Sh2GammaDecode>)
}

pub struct ScreenFxPass<T: ScreenFx>(PhantomData<T>);

impl<T: ScreenFx> Default for ScreenFxPass<T> {
    fn default() -> Self {
        ScreenFxPass(PhantomData)
    }
}

impl<T: ScreenFx> Plugin for ScreenFxPass<T> {
    fn build(&self, app: &mut App) {
        app.add_plugins((ExtractComponentPlugin::<T>::default(), UniformComponentPlugin::<T>::default()));
        let Some(render_app) = app.get_sub_app_mut(RenderApp) else { return };
        render_app
            .add_systems(RenderStartup, init_pipeline::<T>)
            .add_systems(Render, (prepare_pipelines::<T>.in_set(RenderSystems::Prepare), prepare_snapshots::<T>.in_set(RenderSystems::PrepareResources)))
            .add_systems(Core3d, order(screenfx_system::<T>.into_configs()));
    }
}
