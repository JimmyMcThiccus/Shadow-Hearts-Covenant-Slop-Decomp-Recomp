// Vertex stage of `Sh2FxMaterial` (`fxquad.rs`): expands effect quads / ribbon points from the record buffer.  The template mesh carries
// `uv = (slot, corner)`; corners and triangles follow the CPU meshes (`0 1 2`, `1 3 2` per slot).  Unused slots collapse to a zero-area triangle.
// The fragment stage is `sh2.wgsl`.

#import bevy_pbr::{
    mesh_functions,
    forward_io::VertexOutput,
    view_transformations::position_world_to_clip,
}

// header: [0] camera right.xyz, count  [1] camera up.xyz  [2] camera position (group local).xyz  [3] camera forward.xyz; then the records
@group(#{MATERIAL_BIND_GROUP}) @binding(3) var<storage, read> records: array<vec4<f32>>;

struct FxVertex {
    @builtin(instance_index) instance_index: u32,
    @location(0) position: vec3<f32>,
    @location(2) slot_corner: vec2<f32>,
};

fn normalize_or_zero(v: vec3<f32>) -> vec3<f32> {
    let l = length(v);
    if (l > 0.0) {
        return v / l;
    }
    return vec3<f32>(0.0);
}

fn pick2(a: vec4<f32>, b: vec4<f32>, k: u32) -> vec2<f32> {
    switch k {
        case 0u: { return a.xy; }
        case 1u: { return a.zw; }
        case 2u: { return b.xy; }
        default: { return b.zw; }
    }
}

@vertex
fn vertex(v: FxVertex) -> VertexOutput {
    var out: VertexOutput;
    let slot = u32(v.slot_corner.x + 0.5);
    let k = u32(v.slot_corner.y + 0.5);
    let count = u32(records[0].w + 0.5);
    let right = records[0].xyz;
    let up = records[1].xyz;
    let cam = records[2].xyz;
    let fwd = records[3].xyz;
    var p = vec3<f32>(0.0);
    var uv = vec2<f32>(0.0);
    var color = vec4<f32>(0.0);
    var valid = false;
#ifdef SH2_FX_RIBBON
    if (slot + 1u < count) {
        valid = true;
        let i = slot + (k >> 1u);
        let base = 4u + i * 4u;
        let pos = records[base].xyz;
        let dir = records[base + 1u].xyz;
        color = records[base + 2u];
        let st = records[base + 3u];
        var t = 0.0;
        if (count > 1u) {
            t = f32(i) / f32(count - 1u);
        }
        let vv = st.y + (st.w - st.y) * t;
        if ((k & 1u) == 0u) {
            p = pos - dir;
            uv = vec2<f32>(st.x, vv);
        } else {
            p = pos + dir;
            uv = vec2<f32>(1.0 - st.z, vv);
        }
    }
#else
    if (slot < count) {
        valid = true;
        let base = 4u + slot * 11u;
        let r0 = records[base];
        let r1 = records[base + 1u];
        let r2 = records[base + 2u];
        let o = pick2(records[base + 3u], records[base + 4u], k);
        uv = pick2(records[base + 5u], records[base + 6u], k);
        color = records[base + 7u + k];
        let mode = u32(r0.w + 0.5);
        if (mode == 2u) {
            // screen space: r1 = (kx, ky, depth)
            let c = cam + fwd * r1.z + right * (r0.x * r1.x) - up * (r0.y * r1.y);
            p = c + right * (o.x * r1.x) - up * (o.y * r1.y);
        } else {
            var c = r0.xyz;
            if (r1.w != 0.0) {
                c = c + normalize_or_zero(cam - c) * r1.w;
            }
            if (mode == 0u) {
                p = c + r1.xyz * o.x + r2.xyz * o.y;
            } else {
                p = c + right * o.x - up * o.y;
            }
        }
    }
#endif
    let world_from_local = mesh_functions::get_world_from_local(v.instance_index);
    out.world_position = mesh_functions::mesh_position_local_to_world(world_from_local, vec4<f32>(p, 1.0));
    out.position = position_world_to_clip(out.world_position.xyz);
    if (!valid) {
        // zero-area triangle outside the clip volume
        out.position = vec4<f32>(2.0, 2.0, 2.0, 1.0);
    }
    out.world_normal = vec3<f32>(0.0, 1.0, 0.0);
#ifdef VERTEX_UVS_A
    out.uv = uv;
#endif
#ifdef VERTEX_COLORS
    out.color = color;
#endif
    return out;
}
