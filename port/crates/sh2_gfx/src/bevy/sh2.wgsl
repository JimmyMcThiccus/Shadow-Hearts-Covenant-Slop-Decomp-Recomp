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
#import bevy_pbr::mesh_functions

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
    // x: test mode (0 plain discard below ref, 1 cut-in = keep A >= ref, 2 low = keep A < ref), y: gamma-space output,
    // z: shadow atlas tile + 1 (0 = off), w: atlas tiles per row
    extra: vec4<f32>,
};

@group(#{MATERIAL_BIND_GROUP}) @binding(0) var<uniform> material: Sh2Material;
@group(#{MATERIAL_BIND_GROUP}) @binding(1) var base_texture: texture_2d<f32>;
@group(#{MATERIAL_BIND_GROUP}) @binding(2) var base_sampler: sampler;
#ifdef SH2_DYN
// `Sh2Dyn` (material.rs): 9 vec4 per slot (tint, flags (x lights, y tint), ambient, light_dir, light_color, light_dir1, light_color1,
// light_dir2, light_color2); slot 0 = the scene light.  A draw's slot is its `MeshTag` (0 = none).
@group(#{MATERIAL_BIND_GROUP}) @binding(3) var<storage, read> sh2_dyn: array<vec4<f32>>;
#endif

fn srgb_to_linear(c: vec3<f32>) -> vec3<f32> {
    let lo = c / 12.92;
    let hi = pow((c + vec3<f32>(0.055)) / 1.055, vec3<f32>(2.4));
    return select(hi, lo, c <= vec3<f32>(0.04045));
}

@fragment
fn fragment(in: VertexOutput) -> @location(0) vec4<f32> {
    var uv = in.uv;
    if (material.extra.z > 0.5) {
        // shadow receivers: UV inside one tile of the silhouette atlas (`shadow.rs`), clamped half a texel inside it (the original clamps
        // its 128 x 128 silhouette texture, `CLAMP_2 = clamp`)
        let n = material.extra.w;
        let t = material.extra.z - 1.0;
        let tile = vec2<f32>(t - n * floor(t / n), floor(t / n));
        let h = 0.5 / 128.0;
        uv = (tile + clamp(uv, vec2<f32>(h), vec2<f32>(1.0 - h))) / n;
    }
    // per-frame values: the material uniforms, or the draw's `Sh2Dyn` slot / the scene light slot (same numbers, see material.rs)
    var tint = material.tint;
    var ambient = material.ambient;
    var ld0 = material.light_dir;
    var lc0 = material.light_color;
    var ld1 = material.light_dir1;
    var lc1 = material.light_color1;
    var ld2 = material.light_dir2;
    var lc2 = material.light_color2;
#ifdef SH2_DYN
    let tag = mesh_functions::get_tag(in.instance_index);
    var lb = 0u;
    var use_slot_light = material.ambient.w < 0.5;
    if (tag != 0u) {
        let b = tag * 9u;
        let flags = sh2_dyn[b + 1u];
        if (flags.y > 0.5) {
            tint = sh2_dyn[b];
        }
        if (flags.x > 0.5) {
            lb = b;
            use_slot_light = true;
        }
    }
    if (use_slot_light) {
        ambient = sh2_dyn[lb + 2u];
        ld0 = sh2_dyn[lb + 3u];
        lc0 = sh2_dyn[lb + 4u];
        ld1 = sh2_dyn[lb + 5u];
        lc1 = sh2_dyn[lb + 6u];
        ld2 = sh2_dyn[lb + 7u];
        lc2 = sh2_dyn[lb + 8u];
    }
#endif
    let tex = textureSample(base_texture, base_sampler, uv);
    var vtx = vec4<f32>(1.0);
#ifdef VERTEX_COLORS
    vtx = in.color;
#endif
    // alpha of the fragment as the GS sees it (TFX MODULATE, RGBA), 255 <-> 0x80
    let frag_a = tex.a * vtx.a * tint.a;
    if (material.params.x >= 0.0) {
        let below = frag_a * 127.5 < material.params.x;
        if (material.extra.x > 1.5) {
            if (!below) { discard; }
        } else if (below) {
            discard;
        }
    }
    var rgb = tex.rgb * vtx.rgb * tint.rgb;
    if (material.params.z > 0.5) {
        let n = normalize(in.world_normal);
        let d0 = max(dot(n, ld0.xyz), 0.0);
        let d1 = max(dot(n, ld1.xyz), 0.0);
        let d2 = max(dot(n, ld2.xyz), 0.0);
        rgb = rgb * (ambient.rgb + lc0.rgb * d0 + lc1.rgb * d1 + lc2.rgb * d2);
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
