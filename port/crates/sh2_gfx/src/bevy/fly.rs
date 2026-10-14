//! Free-fly debug camera: WASD/QE move, Shift run, right mouse (or arrow keys) look, wheel changes speed.

use ::bevy::input::mouse::{AccumulatedMouseMotion, AccumulatedMouseScroll};
use ::bevy::prelude::*;

#[derive(Component, Clone, Debug)]
pub struct FlyCamera {
    pub speed: f32,
    pub sensitivity: f32,
    pub yaw: f32,
    pub pitch: f32,
}

impl Default for FlyCamera {
    fn default() -> Self {
        Self { speed: 60.0, sensitivity: 0.003, yaw: 0.0, pitch: 0.0 }
    }
}

impl FlyCamera {
    /// Place `transform` at `eye` looking at `target` and sync yaw/pitch.
    pub fn look_at(&mut self, transform: &mut Transform, eye: Vec3, target: Vec3) {
        *transform = Transform::from_translation(eye).looking_at(target, Vec3::Y);
        let (y, p, _) = transform.rotation.to_euler(EulerRot::YXZ);
        self.yaw = y;
        self.pitch = p;
    }
}

pub fn fly_camera_system(
    time: Res<Time>,
    keys: Res<ButtonInput<KeyCode>>,
    buttons: Res<ButtonInput<MouseButton>>,
    motion: Res<AccumulatedMouseMotion>,
    scroll: Res<AccumulatedMouseScroll>,
    mut q: Query<(&mut Transform, &mut FlyCamera)>,
) {
    let dt = time.delta_secs();
    for (mut t, mut fly) in &mut q {
        if scroll.delta.y != 0.0 {
            fly.speed = (fly.speed * (1.0 + 0.1 * scroll.delta.y)).clamp(1.0, 5000.0);
        }
        if buttons.pressed(MouseButton::Right) {
            fly.yaw -= motion.delta.x * fly.sensitivity;
            fly.pitch = (fly.pitch - motion.delta.y * fly.sensitivity).clamp(-1.55, 1.55);
        }
        let rot = 1.5 * dt;
        if keys.pressed(KeyCode::ArrowLeft) {
            fly.yaw += rot;
        }
        if keys.pressed(KeyCode::ArrowRight) {
            fly.yaw -= rot;
        }
        if keys.pressed(KeyCode::ArrowUp) {
            fly.pitch = (fly.pitch + rot).min(1.55);
        }
        if keys.pressed(KeyCode::ArrowDown) {
            fly.pitch = (fly.pitch - rot).max(-1.55);
        }
        t.rotation = Quat::from_euler(EulerRot::YXZ, fly.yaw, fly.pitch, 0.0);
        let mut d = Vec3::ZERO;
        let fwd = t.forward().as_vec3();
        let right = t.right().as_vec3();
        if keys.pressed(KeyCode::KeyW) {
            d += fwd;
        }
        if keys.pressed(KeyCode::KeyS) {
            d -= fwd;
        }
        if keys.pressed(KeyCode::KeyD) {
            d += right;
        }
        if keys.pressed(KeyCode::KeyA) {
            d -= right;
        }
        if keys.pressed(KeyCode::KeyE) {
            d += Vec3::Y;
        }
        if keys.pressed(KeyCode::KeyQ) {
            d -= Vec3::Y;
        }
        let run = if keys.pressed(KeyCode::ShiftLeft) { 4.0 } else { 1.0 };
        t.translation += d.normalize_or_zero() * fly.speed * run * dt;
    }
}

pub struct FlyCameraPlugin;
impl Plugin for FlyCameraPlugin {
    fn build(&self, app: &mut App) {
        app.add_systems(Update, fly_camera_system);
    }
}
