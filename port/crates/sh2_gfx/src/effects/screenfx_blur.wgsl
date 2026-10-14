// `EffectBlur` (JP 0x0031a970..0x0031b260, `blr*` ids 2100-2106): the frame buffer is drawn over itself as one screen sized sprite with the texture
// window (u0, v0)-(u1, v1) (texels of the 512 x 448 frame), vertex colour (r, g, b, a) on the GS 0..128 scale and ALPHA = (Cs - Cd) * As + Cd.
// Up to four blur objects are applied in order.

#import bevy_core_pipeline::fullscreen_vertex_shader::FullscreenVertexOutput

@group(0) @binding(0) var screen_texture: texture_2d<f32>;
@group(0) @binding(1) var texture_sampler: sampler;
struct BlurFx {
    head: vec4<f32>,                  // x = number of layers
    layers: array<vec4<f32>, 8>,      // [2k] = (r, g, b, a) 0..128, [2k+1] = (u0, v0, u1, v1) texels
};
@group(0) @binding(2) var<uniform> fx: BlurFx;

const SCREEN: vec2<f32> = vec2<f32>(512.0, 448.0);

@fragment
fn fragment(in: FullscreenVertexOutput) -> @location(0) vec4<f32> {
    var c = textureSampleLevel(screen_texture, texture_sampler, in.uv, 0.0).rgb;
    let n = i32(fx.head.x);
    let p = in.uv * SCREEN;
    for (var i = 0; i < 4; i = i + 1) {
        if (i >= n) {
            break;
        }
        let col = fx.layers[2 * i];
        let w = fx.layers[2 * i + 1];
        // the sprite spans (0, 0)-(511, 447); the texture window maps linearly onto it
        let t = w.xy + (p / vec2<f32>(511.0, 447.0)) * (w.zw - w.xy);
        let s = textureSampleLevel(screen_texture, texture_sampler, t / SCREEN, 0.0).rgb;
        let a = clamp(col.w / 128.0, 0.0, 1.0);
        let src = clamp(s * col.xyz / 128.0, vec3<f32>(0.0), vec3<f32>(1.0));
        c = mix(c, src, a);
    }
    return vec4<f32>(c, 1.0);
}
