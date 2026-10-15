// Vertex stage of `Sh2Material`.
//
// Unskinned meshes: exactly Bevy's `bevy_pbr::mesh` vertex shader (minus morph targets, which no SH2 mesh uses).
// GPU-skinned atomics (`SKINNED`, see `model.rs` "Skinning decision"): the joint "matrix" Bevy hands us is the PS2 palette matrix itself (the joint
// entity is the identity), one per vertex like the VU1 `SkinAtomicPack2` microcode (weight 1 on joint 0).  The vertex is skinned in *model space*
// and then placed by the mesh entity's own transform, exactly like the CPU path (`skin()` + the re-uploaded mesh):
//   local  = P * v
//   normal = mesh_normal_local_to_world(normalize(P * n))
// `BAtomic` billboards (`SH2_BILLBOARD`: skinned + `UV_1`, see `billboard.rs`): position = element centre, `uv_b` = corner offset; joint 0 / 1
// = bone (without / with the first element's offset), joint 2 = the camera-facing corner basis (columns 0 / 1, model space) and the first
// element's colour factor (column 2):
//   local = P * centre + B[0] * corner.x + B[1] * corner.y

#import bevy_pbr::{
    mesh_functions,
    skinning,
    forward_io::{Vertex, VertexOutput},
    view_transformations::position_world_to_clip,
}

@vertex
fn vertex(vertex: Vertex) -> VertexOutput {
    var out: VertexOutput;
    let world_from_local = mesh_functions::get_world_from_local(vertex.instance_index);

#ifdef SKINNED
    let palette = skinning::skin_model(vertex.joint_indices, vertex.joint_weights, vertex.instance_index);
#ifdef SH2_BILLBOARD
    let bb = skinning::skin_model(vec4<u32>(2u, 0u, 0u, 0u), vec4<f32>(1.0, 0.0, 0.0, 0.0), vertex.instance_index);
#endif
#endif

#ifdef VERTEX_NORMALS
    var n = vertex.normal;
#ifdef SKINNED
    let pn = (palette * vec4<f32>(n, 0.0)).xyz;
    n = pn / max(length(pn), 1e-6);
#endif
    out.world_normal = mesh_functions::mesh_normal_local_to_world(n, vertex.instance_index);
#endif

#ifdef VERTEX_POSITIONS
    var local = vec4<f32>(vertex.position, 1.0);
#ifdef SKINNED
    local = vec4<f32>((palette * local).xyz, 1.0);
#ifdef SH2_BILLBOARD
    local = vec4<f32>(local.xyz + bb[0].xyz * vertex.uv_b.x + bb[1].xyz * vertex.uv_b.y, 1.0);
#endif
#endif
    out.world_position = mesh_functions::mesh_position_local_to_world(world_from_local, local);
    out.position = position_world_to_clip(out.world_position.xyz);
#endif

#ifdef VERTEX_UVS_A
    out.uv = vertex.uv;
#endif
#ifdef VERTEX_UVS_B
    out.uv_b = vertex.uv_b;
#endif

#ifdef VERTEX_TANGENTS
    out.world_tangent = mesh_functions::mesh_tangent_local_to_world(world_from_local, vertex.tangent, vertex.instance_index);
#endif

#ifdef VERTEX_COLORS
    out.color = vertex.color;
#ifdef SH2_BILLBOARD
    if vertex.joint_indices.x == 1u {
        out.color = vec4<f32>(vertex.color.rgb * bb[2].xyz, vertex.color.a);
    }
#endif
#endif

#ifdef VERTEX_OUTPUT_INSTANCE_INDEX
    out.instance_index = vertex.instance_index;
#endif

#ifdef VISIBILITY_RANGE_DITHER
    out.visibility_range_dither = mesh_functions::get_visibility_range_dither_level(vertex.instance_index, world_from_local[3]);
#endif

    return out;
}
