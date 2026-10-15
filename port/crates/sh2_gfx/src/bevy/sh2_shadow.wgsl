// Silhouette pass of the drop shadows (`shadow.rs`): every caster atomic has a twin draw on the shadow layer that the atlas camera renders.
// Position = the same (GPU-skinned) world position as `sh2_vertex.wgsl`, projected by the caster's own clip matrix into its atlas tile (the camera's
// view-projection is not used); output = coverage (alpha 1) on the transparent-black atlas.

#import bevy_pbr::{
    mesh_functions,
    skinning,
    forward_io::{Vertex, VertexOutput},
}

struct ShadowIndex {
    // x: atlas tile of the caster
    index: vec4<f32>,
};

@group(#{MATERIAL_BIND_GROUP}) @binding(0) var<uniform> caster: ShadowIndex;
@group(#{MATERIAL_BIND_GROUP}) @binding(1) var<storage, read> clips: array<mat4x4<f32>>;

@vertex
fn vertex(vertex: Vertex) -> VertexOutput {
    var out: VertexOutput;
    let world_from_local = mesh_functions::get_world_from_local(vertex.instance_index);
    var local = vec4<f32>(vertex.position, 1.0);
#ifdef SKINNED
    let palette = skinning::skin_model(vertex.joint_indices, vertex.joint_weights, vertex.instance_index);
    local = vec4<f32>((palette * local).xyz, 1.0);
#endif
    out.world_position = mesh_functions::mesh_position_local_to_world(world_from_local, local);
    out.position = clips[u32(caster.index.x + 0.5)] * vec4<f32>(out.world_position.xyz, 1.0);
    out.world_normal = vec3<f32>(0.0, 1.0, 0.0);
#ifdef VERTEX_UVS_A
    out.uv = vec2<f32>(0.0);
#endif
#ifdef VERTEX_UVS_B
    out.uv_b = vec2<f32>(0.0);
#endif
#ifdef VERTEX_TANGENTS
    out.world_tangent = vec4<f32>(1.0, 0.0, 0.0, 1.0);
#endif
#ifdef VERTEX_COLORS
    out.color = vec4<f32>(1.0);
#endif
#ifdef VERTEX_OUTPUT_INSTANCE_INDEX
    out.instance_index = vertex.instance_index;
#endif
#ifdef VISIBILITY_RANGE_DITHER
    out.visibility_range_dither = 0;
#endif
    return out;
}

@fragment
fn fragment(in: VertexOutput) -> @location(0) vec4<f32> {
    return vec4<f32>(0.0, 0.0, 0.0, 1.0);
}
