// Shadow Hearts GS-style material.
//
//   out.rgb = clamp(tex.rgb * vtx.rgb)           (GS TFX = MODULATE; vertex colour 0x80 == 1.0, brighter allowed)
//   out.a   = tex.a * vtx.a   or FIX              (only meaningful when a blend mode is selected)
//   alpha test: GEQUAL against the 0..0x80 texture alpha (TEST_1 ATST = 5); mode 2 keeps the *failing* texels
//               (the AFAIL = RGB_ONLY half of the default test, drawn without depth write)
//   fog (PRIM.FGE): F = 255 - clamp((z - near) * 256 / (far - near), 0, 255); Cs = Cs*F/255 + FOGCOL*(1 - F/255)  (before ABE)
//   optional Lambert light (skinned characters have normals instead of vertex colours): ambient + sum of 3 directional lights
//
// Colour space: in "gamma" mode (extra.y > 0.5) the raw display value is written to an HDR target and blended there
// like the GS does; `Sh2GammaDecode` converts it to linear before the sRGB surface re-encodes it.  In legacy mode the
// value is converted here.

#import bevy_pbr::forward_io::VertexOutput

struct Sh2Material {
    tint: vec4<f32>,
    // x: alpha test reference in GS units (0..128), < 0 = test off
    // y: constant alpha (GS FIX/128), < 0 = use texture*vertex alpha
    // z: 1.0 = apply the light below, 0.0 = unlit
    // w: 1.0 = blended (use alpha), 0.0 = alpha ignored (ABE off)
    params: vec4<f32>,
    ambient: vec4<f32>,
    light_dir: vec4<f32>,   // direction *towards* the light, world space
    light_color: vec4<f32>,
    light_dir1: vec4<f32>,
    light_color1: vec4<f32>,
    light_dir2: vec4<f32>,
    light_color2: vec4<f32>,
    // x near, y far, z = PRIM.FGE of this surface, w = scene fog enabled
    fog: vec4<f32>,
    fog_color: vec4<f32>,
    // x: test mode (0 plain discard below ref, 1 cut-in = keep A >= ref, 2 low = keep A < ref), y: gamma-space output
    extra: vec4<f32>,
};

@group(#{MATERIAL_BIND_GROUP}) @binding(0) var<uniform> material: Sh2Material;
@group(#{MATERIAL_BIND_GROUP}) @binding(1) var base_texture: texture_2d<f32>;
@group(#{MATERIAL_BIND_GROUP}) @binding(2) var base_sampler: sampler;

fn srgb_to_linear(c: vec3<f32>) -> vec3<f32> {
    let lo = c / 12.92;
    let hi = pow((c + vec3<f32>(0.055)) / 1.055, vec3<f32>(2.4));
    return select(hi, lo, c <= vec3<f32>(0.04045));
}

@fragment
fn fragment(in: VertexOutput) -> @location(0) vec4<f32> {
    let tex = textureSample(base_texture, base_sampler, in.uv);
    var vtx = vec4<f32>(1.0);
#ifdef VERTEX_COLORS
    vtx = in.color;
#endif
    // alpha of the fragment as the GS sees it (TFX MODULATE, RGBA), 255 <-> 0x80
    let frag_a = tex.a * vtx.a * material.tint.a;
    if (material.params.x >= 0.0) {
        let below = frag_a * 127.5 < material.params.x;
        if (material.extra.x > 1.5) {
            if (!below) { discard; }
        } else if (below) {
            discard;
        }
    }
    var rgb = tex.rgb * vtx.rgb * material.tint.rgb;
    if (material.params.z > 0.5) {
        let n = normalize(in.world_normal);
        let d0 = max(dot(n, material.light_dir.xyz), 0.0);
        let d1 = max(dot(n, material.light_dir1.xyz), 0.0);
        let d2 = max(dot(n, material.light_dir2.xyz), 0.0);
        rgb = rgb * (material.ambient.rgb + material.light_color.rgb * d0 + material.light_color1.rgb * d1 + material.light_color2.rgb * d2);
    }
    rgb = clamp(rgb, vec3<f32>(0.0), vec3<f32>(1.0));
    if (material.fog.z > 0.5 && material.fog.w > 0.5) {
        // in.position.w = 1 / w_clip; w_clip is the view-space depth (the VU1 uses the same value)
        let z = 1.0 / max(in.position.w, 1e-6);
        let f = 1.0 - clamp((z - material.fog.x) * 256.0 / (material.fog.y - material.fog.x), 0.0, 255.0) / 255.0;
        rgb = rgb * f + material.fog_color.rgb * (1.0 - f);
    }
    var a = 1.0;
    if (material.params.w > 0.5) {
        a = frag_a;
        if (material.params.y >= 0.0) {
            a = material.params.y;
        }
    }
    if (material.extra.y > 0.5) {
        return vec4<f32>(rgb, clamp(a, 0.0, 1.0));
    }
    return vec4<f32>(srgb_to_linear(rgb), clamp(a, 0.0, 1.0));
}
