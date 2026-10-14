// `EffectBarin` (JP 0x00321e20.., `bng*` ids 2500-2508): the stored frame (snapshot, binding 3) is drawn as polygons that move / tumble / fly off over the live frame.
// Per polygon (5 vec4): [5k] = (vertex count, grey level, 0, 0); [5k + 1 + j] = (screen x, screen y, texel x, texel y) of vertex j, pixels of the 512 x 448 frame.
// Quads are GS triangle strips: triangles (0, 1, 2) and (1, 2, 3).  The polygon colour is the grey level (0.8 at rest, rgb and alpha); alpha above 1 is opaque.

#import bevy_core_pipeline::fullscreen_vertex_shader::FullscreenVertexOutput

@group(0) @binding(0) var screen_texture: texture_2d<f32>;
@group(0) @binding(1) var texture_sampler: sampler;
struct ShatterFx {
    head: vec4<f32>,                    // x = number of polygons
    polys: array<vec4<f32>, 320>,
};
@group(0) @binding(2) var<uniform> fx: ShatterFx;
@group(0) @binding(3) var snapshot: texture_2d<f32>;

const SCREEN: vec2<f32> = vec2<f32>(512.0, 448.0);

// copies the incoming frame into the snapshot
@fragment
fn capture(in: FullscreenVertexOutput) -> @location(0) vec4<f32> {
    return textureSampleLevel(screen_texture, texture_sampler, in.uv, 0.0);
}

struct Hit { inside: bool, tex: vec2<f32> };

fn tri(p: vec2<f32>, a: vec4<f32>, b: vec4<f32>, c: vec4<f32>) -> Hit {
    let v0 = b.xy - a.xy;
    let v1 = c.xy - a.xy;
    let v2 = p - a.xy;
    let den = v0.x * v1.y - v1.x * v0.y;
    if (abs(den) < 1e-6) {
        return Hit(false, vec2<f32>(0.0));
    }
    let u = (v2.x * v1.y - v1.x * v2.y) / den;
    let w = (v0.x * v2.y - v2.x * v0.y) / den;
    let t = 1.0 - u - w;
    if (u < 0.0 || w < 0.0 || t < 0.0) {
        return Hit(false, vec2<f32>(0.0));
    }
    return Hit(true, a.zw * t + b.zw * u + c.zw * w);
}

@fragment
fn fragment(in: FullscreenVertexOutput) -> @location(0) vec4<f32> {
    var c = textureSampleLevel(screen_texture, texture_sampler, in.uv, 0.0).rgb;
    let p = in.uv * SCREEN;
    let n = i32(fx.head.x);
    // topmost = drawn last
    for (var k = n - 1; k >= 0; k = k - 1) {
        let head = fx.polys[5 * k];
        let a = fx.polys[5 * k + 1];
        let b = fx.polys[5 * k + 2];
        let d = fx.polys[5 * k + 3];
        var h = tri(p, a, b, d);
        if (!h.inside && head.x > 3.5) {
            let e = fx.polys[5 * k + 4];
            h = tri(p, b, d, e);
        }
        if (h.inside) {
            let s = textureSampleLevel(snapshot, texture_sampler, h.tex / SCREEN, 0.0).rgb * head.y;
            c = mix(c, clamp(s, vec3<f32>(0.0), vec3<f32>(1.0)), clamp(head.y, 0.0, 1.0));
            break;
        }
    }
    return vec4<f32>(c, 1.0);
}
