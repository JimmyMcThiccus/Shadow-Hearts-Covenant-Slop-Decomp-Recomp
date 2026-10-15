//! Bevy glue for the Shadow Hearts renderer.
//!
//! Layering (see `notes/integration/renderer.md`):
//!
//! | module | purpose |
//! |---|---|
//! | [`image`] | decoded PS2 textures -> `bevy::Image` (RGBA8 non-sRGB, nearest/repeat, alpha 0x80 = opaque) |
//! | [`mesh`] | `AtomicDef` triangle strips (ADC aware) -> `bevy::Mesh` triangle lists |
//! | [`material`] | [`material::Sh2Material`]: unlit / vertex-colour x texture "GS MODULATE" material with the three GS blend modes, alpha test split, fog, scene light, gamma-space blending |
//! | [`map`] | field-map (BG) models: per-atomic PRIM (ABE/FGE/TME) + texture ALPHA_1/TEST_1 state -> draws |
//! | [`model`] | spawning static models (field BG) and CPU-skinned, animated models |
//! | [`fly`], [`capture`] | free-fly debug camera and PNG screenshot helper used by the viewer |
//! | [`disc`] | shared handle to the opened disc image |
//!
//! Everything lives under a [`model::Ps2Root`] entity that rotates 180 degrees about X so that PS2 model space
//! (x right, y **down**, z into the screen; a right handed system) maps to Bevy's y-up world without mirroring.

pub mod bgmotion;
pub mod billboard;
pub mod capture;
pub mod character;
pub mod disc;
pub mod fxquad;
pub mod fly;
pub mod gfx2d;
pub mod image;
pub mod map;
pub mod material;
pub mod mesh;
pub mod mirror;
pub mod model;
pub mod perf;
pub mod screen;
pub mod shadow;
pub mod texanim;

pub use disc::Sh2Disc;
pub use image::TexFilter;
pub use material::{Sh2Blend, Sh2ColorSpace, Sh2Fog, Sh2Material, Sh2SceneLight, TestMode};
