// Last step of the gamma-space pipeline: the HDR target holds raw PS2 display values (blended like the GS did);
// clamp like the 8-bit frame buffer and convert to linear so the sRGB surface encodes them back unchanged.

#import bevy_core_pipeline::fullscreen_vertex_shader::FullscreenVertexOutput

@group(0) @binding(0) var screen_texture: texture_2d<f32>;
@group(0) @binding(1) var texture_sampler: sampler;
struct Decode {
    enabled: f32,
    pad: vec3<f32>,
};
@group(0) @binding(2) var<uniform> settings: Decode;

fn srgb_to_linear(c: vec3<f32>) -> vec3<f32> {
    let lo = c / 12.92;
    let hi = pow((c + vec3<f32>(0.055)) / 1.055, vec3<f32>(2.4));
    return select(hi, lo, c <= vec3<f32>(0.04045));
}

@fragment
fn fragment(in: FullscreenVertexOutput) -> @location(0) vec4<f32> {
    let c = textureSample(screen_texture, texture_sampler, in.uv);
    if (settings.enabled < 0.5) {
        return c;
    }
    // alpha passes through (an opaque window ignores it; the menu model view, `sh2_field::menu_model`, renders into an image over the
    // menu backdrop and needs its cleared background to stay transparent; round 6 MN2)
    return vec4<f32>(srgb_to_linear(clamp(c.rgb, vec3<f32>(0.0), vec3<f32>(1.0))), clamp(c.a, 0.0, 1.0));
}
