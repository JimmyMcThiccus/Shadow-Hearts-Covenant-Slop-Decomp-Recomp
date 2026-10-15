//! Decoded PS2 textures -> `bevy::Image`.
//!
//! * Pixels are RGBA8 with the GS alpha (0x80 = opaque) already expanded to 0..255 by the decoders
//!   (`sh2_formats::model::TextureDef::to_rgba8`, `sh2_gfx::texture`).
//! * The format is `Rgba8Unorm` (NOT sRGB): the GS works directly on display-referred values, so the
//!   material shader does the modulation in that space and converts to linear only at the very end.
//! * Addressing is `REPEAT` (`CLAMP_1 = 0` is what `Texture::createRegsterPacket` leaves in place).
//! * Filtering: the game's `TEX1_1` register is MMAG = MMIN = LINEAR for model textures, so the renderer default
//!   (`Sh2RenderSettings`) is [`TexFilter::Linear`]; `SH2_TEX_FILTER=nearest` selects [`TexFilter::Nearest`].

use ::bevy::asset::RenderAssetUsages;
use ::bevy::image::{ImageAddressMode, ImageFilterMode, ImageSampler, ImageSamplerDescriptor};
use ::bevy::prelude::*;
use ::bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};
use sh2_formats::model::TextureDef;

use crate::texture::Rgba8Image;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum TexFilter {
    #[default]
    Nearest,
    Linear,
}

pub fn sampler(filter: TexFilter) -> ImageSampler {
    let f = match filter {
        TexFilter::Nearest => ImageFilterMode::Nearest,
        TexFilter::Linear => ImageFilterMode::Linear,
    };
    ImageSampler::Descriptor(ImageSamplerDescriptor {
        address_mode_u: ImageAddressMode::Repeat,
        address_mode_v: ImageAddressMode::Repeat,
        address_mode_w: ImageAddressMode::Repeat,
        mag_filter: f,
        min_filter: f,
        mipmap_filter: f,
        ..default()
    })
}

/// RGBA8 pixel buffer (top row first) -> Bevy image.
pub fn rgba_image(width: u32, height: u32, rgba: Vec<u8>, filter: TexFilter) -> Image {
    let mut img = Image::new(
        Extent3d { width: width.max(1), height: height.max(1), depth_or_array_layers: 1 },
        TextureDimension::D2,
        rgba,
        TextureFormat::Rgba8Unorm,
        RenderAssetUsages::RENDER_WORLD,
    );
    img.sampler = sampler(filter);
    img
}

/// `TIHD` texture of a model/map (`TextureDef`) -> Bevy image.
pub fn texture_def_image(t: &TextureDef, filter: TexFilter) -> Image {
    rgba_image(t.width as u32, t.height as u32, t.to_rgba8(), filter)
}

/// Decoded `sh2_gfx::texture` image (menu textures, fonts, ...) -> Bevy image.
pub fn decoded_image(img: &Rgba8Image, filter: TexFilter) -> Image {
    rgba_image(img.width, img.height, img.pixels.clone(), filter)
}

/// Change the sampler of an already created image (viewer `--linear` switch).
pub fn set_filter(img: &mut Image, filter: TexFilter) {
    img.sampler = sampler(filter);
}
