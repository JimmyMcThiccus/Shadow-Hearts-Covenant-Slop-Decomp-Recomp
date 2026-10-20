// `HitImpact::MakePacket` (JP 0x0051e090, US 0x005437f0): a 32 segment annulus around the hit, drawn as a triangle strip whose *texture coordinates are the screen
// positions of the unshrunk ring* and whose screen vertices are pulled towards the centre by `shrink` (0.7 -> 1.0): the strip shows the frame buffer (TEX0 = the
// current frame) so the band between the shrunk inner and outer circles displays the scene from `1 / shrink` further out -- a shock wave that squeezes the picture.
// The per pixel version: a pixel at distance `d` from the centre inside the displayed annulus `[shrink * inner, shrink * outer]` reads the frame at `centre + q / shrink`.
// Circles are in the 512 x 448 virtual frame; the y radius is `aspect` (7/6, the view matrix' 1120 / 960) times the x radius.

#import bevy_core_pipeline::fullscreen_vertex_shader::FullscreenVertexOutput

@group(0) @binding(0) var screen_texture: texture_2d<f32>;
@group(0) @binding(1) var texture_sampler: sampler;
struct RingFx {
    // [2k] = (centre x, centre y, outer radius, inner radius), [2k + 1] = (shrink, enabled, aspect, debug tint)
    rings: array<vec4<f32>, 4>,
};
@group(0) @binding(2) var<uniform> fx: RingFx;

const SCREEN: vec2<f32> = vec2<f32>(512.0, 448.0);

@fragment
fn fragment(in: FullscreenVertexOutput) -> @location(0) vec4<f32> {
    let px = in.uv * SCREEN;
    var src = px;
    var tint = vec3<f32>(1.0);
    for (var k = 0; k < 2; k = k + 1) {
        let a = fx.rings[2 * k];
        let b = fx.rings[2 * k + 1];
        if (b.y > 0.5) {
            let q = px - a.xy;
            let r = length(vec2<f32>(q.x, q.y / b.z));
            if (r >= b.x * a.w && r <= b.x * a.z) {
                src = a.xy + q / b.x;
                if (b.w > 0.5) {
                    tint = vec3<f32>(1.0, 0.35, 0.35);
                }
            }
        }
    }
    return vec4<f32>(textureSampleLevel(screen_texture, texture_sampler, src / SCREEN, 0.0).rgb * tint, 1.0);
}
