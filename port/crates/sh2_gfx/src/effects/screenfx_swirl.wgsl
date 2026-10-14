// `EffectGunya` (JP 0x0031d760..0x0031ef80, `gny*` ids 2400-2403): the frame buffer is redrawn through a 6 ring x 36 spoke mesh.  Ring i (0 = outside) has the
// screen radius 340.16 * (1 - i / 6) clipped to the 512 x 448 box and texture coordinates = position / 513 rotated by `key * i` about the centre (then
// `ClumpSt` pulls coordinates that leave the texture back towards the centre); the 7th "ring" is the centre point.  The per pixel version below evaluates the
// same map continuously: find the ring interval around the pixel along its spoke and interpolate the rotation.

#import bevy_core_pipeline::fullscreen_vertex_shader::FullscreenVertexOutput

@group(0) @binding(0) var screen_texture: texture_2d<f32>;
@group(0) @binding(1) var texture_sampler: sampler;
struct SwirlFx {
    p: vec4<f32>,   // x = rotation key (radians per ring), y = enabled
};
@group(0) @binding(2) var<uniform> fx: SwirlFx;

const SCREEN: vec2<f32> = vec2<f32>(512.0, 448.0);
const CENTRE: vec2<f32> = vec2<f32>(256.0, 224.0);
const UV_CENTRE: vec2<f32> = vec2<f32>(255.5, 223.5);
const R0: f32 = 340.16467;

fn ring_radius(i: i32, dir: vec2<f32>) -> f32 {
    let base = R0 * (1.0 - f32(i) / 6.0);
    let cx = abs(dir.x);
    let cy = abs(dir.y);
    var lim = base;
    if (cx > 1e-6) { lim = min(lim, 256.0 / cx); }
    if (cy > 1e-6) { lim = min(lim, 224.0 / cy); }
    return select(0.0, lim, i < 6);
}

@fragment
fn fragment(in: FullscreenVertexOutput) -> @location(0) vec4<f32> {
    if (fx.p.y < 0.5) {
        return textureSampleLevel(screen_texture, texture_sampler, in.uv, 0.0);
    }
    let q = in.uv * SCREEN - CENTRE;
    let r = length(q);
    var dir = vec2<f32>(1.0, 0.0);
    if (r > 1e-4) { dir = q / r; }
    // ring interval along the spoke
    var t = 6.0;
    for (var i = 0; i < 6; i = i + 1) {
        let outer = ring_radius(i, dir);
        let inner = ring_radius(i + 1, dir);
        if (r >= inner) {
            let span = max(outer - inner, 1e-4);
            t = f32(i) + clamp((outer - r) / span, 0.0, 1.0);
            break;
        }
    }
    let ang = fx.p.x * t;
    let cs = cos(ang);
    let sn = sin(ang);
    let st = q * (512.0 / 513.0);
    var s = UV_CENTRE + vec2<f32>(st.x * cs - st.y * sn, st.x * sn + st.y * cs);
    // ClumpSt: back into [0, 512] x [0, 447] towards the centre
    let d = s - UV_CENTRE;
    var k = 1.0;
    if (abs(d.x) > 1e-4) { k = min(k, 255.5 / abs(d.x)); }
    if (abs(d.y) > 1e-4) { k = min(k, 223.5 / abs(d.y)); }
    s = UV_CENTRE + d * k;
    return textureSampleLevel(screen_texture, texture_sampler, s / SCREEN, 0.0);
}
