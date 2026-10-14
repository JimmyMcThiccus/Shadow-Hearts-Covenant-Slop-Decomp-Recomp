//! The **vibration option** (`MENU+0x274` bits 0-1, Option page / title Options: 0 off, 1 weak, 2 strong) and the port's force-feedback API.
//!
//! The original runs `CVibeMan::SetMode(mode)` (JP 0x002894b0 `SaveMenuSection::UpdateVibration`, retail `SaveMenuSection::Update`) whenever the setting changes and
//! every vibration source (`StartVib` of the LSD scripts, battle hits, the field) goes through `CVibeMan`, which scales / drops the pattern by the mode.
//! The port keeps the same split: [`VibrationSetting`] mirrors the option (written by [`crate::plugin::apply_system_options`]) and every source posts a
//! [`VibrationRequest`] (`strength` 0..1 of a full-strength DualShock pattern, `ms` duration); [`forward_vibration`] scales it by the mode ([`vibration_scale`]) and
//! forwards it to every connected gamepad as a Bevy [`GamepadRumbleRequest`].  Off = the request is dropped.

use bevy::input::gamepad::{Gamepad, GamepadRumbleIntensity, GamepadRumbleRequest};
use bevy::prelude::*;
use std::time::Duration;

/// Current vibration mode: 0 off, 1 weak, 2 strong (`MenuSave::vibration_mode`).
#[derive(Resource, Default, Clone, Copy, Debug, PartialEq, Eq)]
pub struct VibrationSetting {
    pub mode: u8,
}

/// A force-feedback pulse requested by the game.
#[derive(Message, Clone, Copy, Debug, PartialEq)]
pub struct VibrationRequest {
    /// 0..1 of a full-strength pattern
    pub strength: f32,
    pub ms: u32,
}

/// How much of a pattern the mode lets through: off 0, weak 0.5, strong 1.0 (anything above 2 = strong).
pub fn vibration_scale(mode: u8) -> f32 {
    match mode {
        0 => 0.0,
        1 => 0.5,
        _ => 1.0,
    }
}

/// The two motors of a pulse: the strong (big) motor carries the strength, the weak (small) motor is on for anything audible, like the DualShock's on / off motor.
pub fn motor_intensity(req: VibrationRequest, mode: u8) -> Option<GamepadRumbleIntensity> {
    let s = (req.strength.clamp(0.0, 1.0) * vibration_scale(mode)).clamp(0.0, 1.0);
    (s > 0.0 && req.ms > 0).then_some(GamepadRumbleIntensity { strong_motor: s, weak_motor: if s >= 0.25 { s.max(0.5) } else { 0.0 } })
}

/// Forward the requests to the connected gamepads.
pub fn forward_vibration(
    mut requests: MessageReader<VibrationRequest>,
    setting: Res<VibrationSetting>,
    pads: Query<Entity, With<Gamepad>>,
    mut out: MessageWriter<GamepadRumbleRequest>,
) {
    for r in requests.read() {
        let Some(intensity) = motor_intensity(*r, setting.mode) else { continue };
        for gamepad in &pads {
            out.write(GamepadRumbleRequest::Add { duration: Duration::from_millis(r.ms as u64), intensity, gamepad });
        }
    }
}

pub struct VibrationPlugin;

impl Plugin for VibrationPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<VibrationSetting>().add_message::<VibrationRequest>().add_message::<GamepadRumbleRequest>().add_systems(Update, forward_vibration);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn mode_scales_the_pattern() {
        let r = VibrationRequest { strength: 1.0, ms: 200 };
        assert_eq!(motor_intensity(r, 0), None, "off drops it");
        let w = motor_intensity(r, 1).unwrap();
        let s = motor_intensity(r, 2).unwrap();
        assert!(w.strong_motor < s.strong_motor && (w.strong_motor - 0.5).abs() < 1e-6 && s.strong_motor == 1.0);
        assert_eq!(motor_intensity(VibrationRequest { strength: 0.0, ms: 100 }, 2), None);
        assert_eq!(motor_intensity(VibrationRequest { strength: 1.0, ms: 0 }, 2), None);
        // a faint pulse only drives the big motor
        assert_eq!(motor_intensity(VibrationRequest { strength: 0.2, ms: 50 }, 2).unwrap().weak_motor, 0.0);
    }

    #[test]
    fn requests_reach_every_gamepad_only_when_enabled() {
        let mut app = App::new();
        app.add_plugins(VibrationPlugin);
        let a = app.world_mut().spawn(Gamepad::default()).id();
        let b = app.world_mut().spawn(Gamepad::default()).id();
        app.world_mut().resource_mut::<VibrationSetting>().mode = 2;
        app.world_mut().write_message(VibrationRequest { strength: 1.0, ms: 100 });
        app.update();
        let got: Vec<Entity> = app.world_mut().resource_mut::<Messages<GamepadRumbleRequest>>().drain().map(|r| r.gamepad()).collect();
        assert_eq!(got.len(), 2);
        assert!(got.contains(&a) && got.contains(&b));
        app.world_mut().resource_mut::<VibrationSetting>().mode = 0;
        app.world_mut().write_message(VibrationRequest { strength: 1.0, ms: 100 });
        app.update();
        assert_eq!(app.world_mut().resource_mut::<Messages<GamepadRumbleRequest>>().drain().count(), 0);
    }
}
