//! Skinned model runtime (section C): `Model` / `Frame` / `SequenceControl` / `Atomic`.
//!
//! This is a CPU reference implementation of what the PS2 code does with VU0/VU1:
//! * [`skeleton::Skeleton`] mirrors `Frame::calcMatrix` (JP 0x00243fb0),
//! * [`instance::ModelInstance`] mirrors `Model::setMotion` / `Model::addTime`
//!   (JP 0x0023ffb0 / 0x002408c0) for the main motion slot,
//! * skinning follows the VU1 `SkinAtomicPack2` microcode: one palette matrix per vertex, no blending.
//!
//! The Bevy layer consumes [`instance::SkinnedAtomic`] (positions in model space,
//! `Y` down like the PS2 world) and the decoded textures.

pub mod blink;
pub mod brn;
pub mod dynamics;
pub mod instance;
pub mod lips;
pub mod path;
pub mod skeleton;
pub mod water;

pub use blink::Blink;
pub use instance::{ModelInstance, SkinnedAtomic};
pub use skeleton::Skeleton;

/// Abstraction of the PS2 GS/VU1 submission path (`VIF1Prim` / `World` packets).
/// The Bevy backend implements this to receive drawable meshes.
pub trait ModelSink {
    /// Called once per atomic per frame with already-skinned geometry.
    fn draw_atomic(&mut self, model_world: &sh2_formats::math::Matrix, atomic: &SkinnedAtomic, texture: Option<usize>);
}
