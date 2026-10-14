//! sh2_gfx — graphics core (section B in docs/OUTLINE.md).
//!
//! Ports `libgsx.cpp` (Gsx, GsxCamera, GsxFrameBuf, World/VIF1Prim ordering tables), the GIF/GS/DMA packet formats the game's 2D layer
//! emits (P2*, prim*, ScreenBright, CineMask), texture container decoders, lights, and a Bevy-side renderer stub.
//!
//! Hardware is abstracted behind [`renderer::GfxBackend`]; PS2 DMA chains are modelled by [`packet`] and replayed with
//! [`gs::GsInterpreter`].  See `notes/B/pipeline.md` for the per-frame data flow.

pub mod camera;
pub mod dma;
pub mod gs;
pub mod ipu;
pub mod light;
pub mod packet;
pub mod psm;
pub mod renderer;
pub mod sprite;
pub mod texture;
pub mod world;
pub mod model;

/// Bevy rendering glue: textures -> Image, atomics -> Mesh, GS-style material, model/animation spawning, viewer helpers.
pub mod bevy;

/// Section D: effects (EffectCore/Effect/VSM, Puti/Fp particles, Judgement Ring).
pub mod effects;
