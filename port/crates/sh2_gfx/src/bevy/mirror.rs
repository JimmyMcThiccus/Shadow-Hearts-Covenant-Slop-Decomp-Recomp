//! Planar mirrors (`MIRROR` chunk of 23 retail maps, `CFieldBG::CheckMirror` JP 0x004dafb0 / US 0x0051ed00, `MirrorModel` JP 0x0025bb00).
//!
//! The engine does not render the BG twice: a mirror record (three corner points of the plane, 0x30 bytes) is only used to decide whether the
//! camera currently *sees* the mirror (camera in front of the plane, `at . -normal >= -0.8`, inside the rectangle's extent +-10) and, if so,
//! `MirrorModel` draws a **reflected copy of every character model** (`Matrix` with one axis negated + `setOffset(plane position)`).
//! Here the reflection is exact for arbitrary planes: every [`AnimatedModel`] gets a sibling holder whose transform is `R * source` and whose
//! children share the source's `Mesh` / material handles, so CPU skinning updates both for free.  GPU-skinned parts also share the source's
//! `SkinnedMesh` (palette asset + identity joint, see `model.rs`): the palette is in model space, so the copy only differs in its transform.
//!
//! The reflection of the *background* is part of the map data (the mirror rooms contain a mirrored copy of the room), so nothing else is needed.

use ::bevy::mesh::skinning::SkinnedMesh;
use ::bevy::prelude::*;

use super::material::Sh2Material;
use super::model::{ps2_to_bevy, AnimatedModel};

/// `CheckMirrorNormal` (JP FIELD 0x004daec0): the dominant axis of the plane normal (0 = x, 1 = y, 2 = z).  The engine only supports
/// axis-aligned mirrors: the reflected copy is the model with that axis negated (`MirrorModel::setMirror(x, y, z)` + `setOffset`).
pub fn check_mirror_normal(n: Vec3) -> u8 {
    let (x, y, z) = (n.x.abs(), n.y.abs(), n.z.abs());
    let mut r = (x < y) as u8;
    if x.max(y) < z {
        r = 2;
    }
    r
}

/// One mirror plane in PS2 space (a `MIRROR` record: three corners of the rectangle).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct MirrorPlane {
    pub origin: Vec3,
    /// Unit normal, pointing towards the side from which the mirror is seen.
    pub normal: Vec3,
    /// [`check_mirror_normal`] of the normal.
    pub axis: u8,
    /// Per-axis minimum / maximum of the three corners.
    pub lo: Vec3,
    pub hi: Vec3,
}

/// `acosf` of a dot product, clamped (the original feeds unit vectors; rounding must not produce NaN).
fn angle(a: Vec3, b: Vec3) -> f32 {
    a.dot(b).clamp(-1.0, 1.0).acos()
}

impl MirrorPlane {
    /// From the three corner points of a `MIRROR` record (`n = (p2-p0) x (p1-p0)` of the *normalised* edges, as `CheckMirror` computes it).
    pub fn from_corners(c: [Vec3; 3]) -> Option<MirrorPlane> {
        let e1 = (c[1] - c[0]).normalize_or_zero();
        let e2 = (c[2] - c[0]).normalize_or_zero();
        let n = e2.cross(e1);
        if n.length_squared() < 1e-12 {
            return None;
        }
        let normal = n.normalize();
        Some(MirrorPlane {
            origin: c[0],
            normal,
            axis: check_mirror_normal(normal),
            lo: c[0].min(c[1]).min(c[2]),
            hi: c[0].max(c[1]).max(c[2]),
        })
    }

    /// Coordinate of the mirror plane along its axis (`(min + max) / 2` of the corners: `CheckMirror` returns `-(min + max)` as the offset).
    pub fn coord(&self) -> f32 {
        let a = self.axis as usize;
        (self.lo[a] + self.hi[a]) * 0.5
    }

    /// The reflection the engine draws: the dominant axis negated about the plane coordinate (axis aligned, like
    /// `MirrorModel::setMirror` + `setOffset`).
    pub fn reflection(&self) -> Mat4 {
        let a = self.axis as usize;
        let mut s = Vec3::ONE;
        s[a] = -1.0;
        let mut t = Vec3::ZERO;
        t[a] = 2.0 * self.coord();
        Mat4::from_translation(t) * Mat4::from_scale(s)
    }

    /// `CheckMirror`'s camera test: camera in front of the plane and not looking away from it.
    pub fn visible_from(&self, cam_pos: Vec3, cam_forward: Vec3) -> bool {
        let to_cam = (cam_pos - self.origin).normalize_or_zero();
        self.normal.dot(to_cam) >= 0.0 && cam_forward.normalize_or_zero().dot(-self.normal) >= -0.8
    }

    /// The full `CFieldBG::CheckMirror` test for one plane (JP FIELD 0x004dafb0): the camera test, then the *angular extent* test: the model
    /// at `p` must lie inside the wedge in which the camera sees the mirror rectangle (extended by 10 units along the mirror).
    pub fn check(&self, cam_pos: Vec3, cam_forward: Vec3, p: Vec3) -> bool {
        if !self.visible_from(cam_pos, cam_forward) {
            return false;
        }
        let axis = self.axis;
        // lo / hi corners of the rectangle in the two axes the test uses (`(x, z)` for walls, `(x, y)` for horizontal planes)
        let (mut lo, mut hi) = if axis & 1 == 0 {
            (Vec3::new(self.lo.x, 0.0, self.lo.z), Vec3::new(self.hi.x, 0.0, self.hi.z))
        } else {
            (Vec3::new(self.lo.x, self.lo.y, 0.0), Vec3::new(self.hi.x, self.hi.y, 0.0))
        };
        match axis {
            0 => {
                lo.z -= 10.0;
                hi.z += 10.0;
            }
            _ => {
                lo.x -= 10.0;
                hi.x += 10.0;
            }
        }
        let flat = |mut v: Vec3| {
            if axis & 1 == 0 {
                v.y = 0.0;
            } else {
                v.z = 0.0;
            }
            v
        };
        let e = flat(p - lo).normalize_or_zero();
        let f = flat(p - hi).normalize_or_zero();
        let mut c = flat(cam_pos - lo);
        let mut d = flat(cam_pos - hi);
        // the horizontal component along the mirror is negated (axis 0: z, axis 2: x, axis 1: x)
        if axis == 0 {
            c.z = -c.z;
            d.z = -d.z;
        } else {
            c.x = -c.x;
            d.x = -d.x;
        }
        let mut b = (d - c).normalize_or_zero();
        let (c, d) = (c.normalize_or_zero(), d.normalize_or_zero());
        if angle(b, e) > angle(b, c) {
            return false;
        }
        b = -b;
        angle(b, f) <= angle(b, d)
    }
}

/// Mirrors of the current map (PS2 space).  Filled by the map loader.
#[derive(Resource, Default, Clone, Debug)]
pub struct Sh2Mirrors {
    pub planes: Vec<MirrorPlane>,
    /// Draw the reflected characters even when `CheckMirror` would not (debugging).
    pub always: bool,
}

/// Holder of a reflected copy of `source`.
#[derive(Component)]
pub struct MirrorCopy {
    pub source: Entity,
}

/// A part of a [`MirrorCopy`]: the source part it mirrors (its `SkinnedMesh` is shared once the source has one).
#[derive(Component)]
pub struct MirrorPart {
    pub source: Entity,
}

/// Marker on a source model whose copy already exists.
#[derive(Component)]
pub struct HasMirror;

/// Create the mirrored copies of newly spawned animated models (one per mirror plane in use: the first plane is used).
pub fn spawn_mirror_copies(
    mut commands: Commands,
    mirrors: Res<Sh2Mirrors>,
    sources: Query<(Entity, &ChildOf, &Children), (With<AnimatedModel>, Without<HasMirror>)>,
    parts: Query<(&Mesh3d, &MeshMaterial3d<Sh2Material>)>,
) {
    if mirrors.planes.is_empty() {
        return;
    }
    for (src, parent, children) in &sources {
        let holder = commands.spawn((Name::new("mirror_copy"), MirrorCopy { source: src }, Transform::default(), Visibility::Hidden)).id();
        commands.entity(parent.parent()).add_child(holder);
        for c in children.iter() {
            if let Ok((m, mat)) = parts.get(c) {
                let child = commands
                    .spawn((m.clone(), mat.clone(), MirrorPart { source: c }, Transform::default(), Visibility::default(), ::bevy::camera::visibility::NoFrustumCulling))
                    .id();
                commands.entity(holder).add_child(child);
            }
        }
        commands.entity(src).insert(HasMirror);
    }
}

/// Keep copies in sync with their source (`R * source`).  Like `CField::CheckMirror`, every model asks for *its own* mirror: the first plane
/// of the map for which the camera test and the extent test pass (at the model's position) selects the reflection; none = no copy.
pub fn update_mirror_copies(
    mirrors: Res<Sh2Mirrors>,
    cams: Query<&GlobalTransform, (With<Camera3d>, Without<super::shadow::ShadowCamera>)>,
    sources: Query<(&Transform, &GlobalTransform), Without<MirrorCopy>>,
    mut copies: Query<(&MirrorCopy, &mut Transform, &mut Visibility)>,
    mut commands: Commands,
) {
    if mirrors.planes.is_empty() {
        for (c, ..) in &copies {
            commands.entity(c.source).remove::<HasMirror>();
        }
        return;
    }
    let cam = cams.iter().next();
    // camera in PS2 space (the Ps2Root rotation is its own inverse)
    let cam_ps2 = cam.map(|g| (ps2_to_bevy(g.translation()), ps2_to_bevy(g.forward().as_vec3())));
    for (c, mut t, mut v) in &mut copies {
        let Ok((src, gsrc)) = sources.get(c.source) else { continue };
        let p = ps2_to_bevy(gsrc.translation());
        let chosen = mirrors.planes.iter().find(|pl| mirrors.always || cam_ps2.map(|(cp, cf)| pl.check(cp, cf, p)).unwrap_or(true)).or_else(|| mirrors.always.then(|| mirrors.planes.first()).flatten());
        let want = match chosen {
            Some(pl) => {
                *t = Transform::from_matrix(pl.reflection() * src.to_matrix());
                Visibility::Inherited
            }
            None => Visibility::Hidden,
        };
        if *v != want {
            *v = want;
        }
    }
}

/// Give mirror parts the GPU skin of their source part (the source gets it on its first animated frame, possibly after the copy was made).
pub fn sync_mirror_skins(
    mut commands: Commands,
    mut parts: Query<(Entity, &MirrorPart, Option<&SkinnedMesh>, &mut Transform)>,
    sources: Query<(&SkinnedMesh, &Transform), Without<MirrorPart>>,
) {
    for (e, mp, have, mut tf) in &mut parts {
        let Ok((src, stf)) = sources.get(mp.source) else { continue };
        // GPU skins offset the draw entity (sort key, see `model.rs`): the copy follows
        if *tf != *stf {
            *tf = *stf;
        }
        if have.map(|h| h.inverse_bindposes != src.inverse_bindposes || h.joints != src.joints).unwrap_or(true) {
            commands.entity(e).try_insert(src.clone());
        }
    }
}

pub struct MirrorPlugin;

impl Plugin for MirrorPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<Sh2Mirrors>().add_systems(PostUpdate, (spawn_mirror_copies, update_mirror_copies, sync_mirror_skins).chain().before(TransformSystems::Propagate));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn wall_x() -> MirrorPlane {
        // MS_01_U-like: plane x = 170 spanning z 364..386, 100 high (y down)
        MirrorPlane::from_corners([Vec3::new(170.0, -100.0, 364.0), Vec3::new(170.0, 0.0, 364.0), Vec3::new(170.0, -100.0, 386.0)]).unwrap()
    }

    #[test]
    fn reflection_mirrors_points_across_the_plane() {
        let p = MirrorPlane::from_corners([Vec3::new(10.0, 0.0, 0.0), Vec3::new(10.0, 1.0, 0.0), Vec3::new(10.0, 0.0, 1.0)]).unwrap();
        assert_eq!(p.axis, 0);
        let r = p.reflection();
        let q = r.transform_point3(Vec3::new(7.0, 3.0, 2.0));
        assert!((q - Vec3::new(13.0, 3.0, 2.0)).length() < 1e-5);
        assert!((r * r).abs_diff_eq(Mat4::IDENTITY, 1e-5));
        assert!(r.determinant() < 0.0);
        let t = Transform::from_matrix(r);
        assert!((t.to_matrix().transform_point3(Vec3::new(7.0, 3.0, 2.0)) - q).length() < 1e-4);
    }

    #[test]
    fn axis_is_the_dominant_normal_component() {
        assert_eq!(check_mirror_normal(Vec3::new(0.9, 0.1, 0.2)), 0);
        assert_eq!(check_mirror_normal(Vec3::new(0.1, -0.9, 0.2)), 1);
        assert_eq!(check_mirror_normal(Vec3::new(0.1, 0.2, -0.9)), 2);
        let wz = MirrorPlane::from_corners([Vec3::new(0.0, 0.0, 50.0), Vec3::new(1.0, 0.0, 50.0), Vec3::new(0.0, 1.0, 50.0)]).unwrap();
        assert_eq!(wz.axis, 2);
        assert!((wz.coord() - 50.0).abs() < 1e-6);
    }

    #[test]
    fn visibility_test_matches_check_mirror() {
        let p = MirrorPlane { origin: Vec3::ZERO, normal: Vec3::Z, axis: 2, lo: Vec3::ZERO, hi: Vec3::ZERO };
        assert!(p.visible_from(Vec3::new(0.0, 0.0, 5.0), Vec3::NEG_Z));
        assert!(!p.visible_from(Vec3::new(0.0, 0.0, -5.0), Vec3::Z));
        assert!(!p.visible_from(Vec3::new(0.0, 0.0, 5.0), Vec3::Z));
    }

    #[test]
    fn extent_test_requires_the_model_in_the_mirror_wedge() {
        let m = wall_x();
        // which side the camera sees the mirror from is given by the normal
        let side = if m.normal.x > 0.0 { 1.0 } else { -1.0 };
        let cam = Vec3::new(170.0 + side * 150.0, -60.0, 375.0);
        let fwd = Vec3::new(-side, 0.0, 0.0);
        // a model in front of the mirror, in line with the camera: reflected
        assert!(m.check(cam, fwd, Vec3::new(170.0 + side * 60.0, 0.0, 375.0)));
        // the same model far along the wall (outside the +-10 extended rectangle as seen from the camera): not reflected
        assert!(!m.check(cam, fwd, Vec3::new(170.0 + side * 60.0, 0.0, 700.0)));
        assert!(!m.check(cam, fwd, Vec3::new(170.0 + side * 60.0, 0.0, 40.0)));
        // camera behind the wall: nothing
        assert!(!m.check(Vec3::new(170.0 - side * 150.0, -60.0, 375.0), -fwd, Vec3::new(170.0 + side * 60.0, 0.0, 375.0)));
    }
}
