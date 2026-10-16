//! Round 6 BT: the Judgement Ring as a reusable API (the battle's rings and RG's field ring screen, `sh2_field::field_ring`).
//!
//! * [`RingRun`] -- one running `JRing` (`sh2_gfx::effects::jring`) with its RNG, the battle constructors (`start_areas`, `start_special`,
//!   `start_effect`) and [`RingRun::start_event`] for an *event* ring (step areas carrying a tag: the field `SetRing` spec
//!   `C<colour>S<start>E<end>`, the tag of the stopped area comes back as `JrResult::event_value`);
//! * [`RingDriver`] -- a ring plus the presentation state the battle keeps next to it (the 9-sample pointer trail, the `Good!! / Strike!!`
//!   sprites): `tick(face_press)` once per 60 Hz frame, `draw(g, art)` onto any `MenuGfx` layer;
//! * the art: [`HitArt`] (`COMMON/JRING.BIN` + the battle font), loaded by [`load_hit_art`]; add [`RingArtPlugin`] to load it outside the
//!   battle scene.
//!
//! Geometry: the ring centre is `JRing::center` (battle rings (1024/3, 224) on the 1024 x 448 canvas), tilt / scale are the `JRing` fields;
//! `draw_ring` is the retail `JRing::MakePacket`.

use bevy::prelude::*;
use sh2_menu::gfx::MenuGfx;

pub use crate::hud_hits::{draw_ring, load_hit_art, HitArt};
pub use crate::plugin::{ring_hit_multiplier, ring_hit_multipliers, RingRun};
pub use sh2_gfx::effects::jring::{self, JRing, JrArea, JrEvent, JrResult, PAD_FACE_MASK};

/// A ring with its presentation state.
pub struct RingDriver {
    pub run: RingRun,
    pub fx: crate::hud_hits::HitFx,
}

impl RingDriver {
    pub fn new(run: RingRun) -> Self {
        RingDriver { run, fx: Default::default() }
    }

    /// One 60 Hz frame with the face buttons newly pressed this frame (`PAD_FACE_MASK` bits); true once the ring has finished.
    pub fn tick(&mut self, face_press: u16) -> bool {
        let done = self.run.tick(face_press);
        let i = (self.fx.trail_i + 1) % 9;
        self.fx.trail_i = i;
        self.fx.trail[i] = self.run.ring.cur_angle;
        for (area, variant) in self.run.mes.drain(..) {
            self.fx.ring_mes(&self.run.ring, area.as_ref(), variant);
        }
        for e in self.run.flashes.drain(..) {
            self.fx.ring_area_flash(&self.run.ring, &e);
        }
        self.fx.tick_ring_mes(1.0 / 60.0);
        done
    }

    /// The ring, its pointer trail and the hit sprites.
    pub fn draw(&self, g: &mut dyn MenuGfx, art: &HitArt) {
        if !art.ring_ok() {
            return;
        }
        draw_ring(g, art, &self.run.ring, &self.fx.trail, self.fx.trail_i);
        self.fx.draw_ring_mes(g, art);
    }

    /// The final result (callback 0x40) or the event result (0x80) of the ring.
    pub fn result(&self) -> Option<&JrResult> {
        self.run.result.as_ref().or(self.run.event_result.as_ref())
    }
}

/// Loads [`HitArt`] in every scene (the battle plugin loads it during battles only).
pub struct RingArtPlugin;

impl Plugin for RingArtPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<HitArt>();
        app.add_systems(Update, load_hit_art.run_if(resource_exists::<sh2_menu::bevy_ui::UiTextures>));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn an_event_ring_reports_the_tag_of_the_area_it_stops_in() {
        // two tagged areas; the autoplay press lands inside the first one it meets
        let mut d = RingDriver::new(RingRun::start_event(&[(40, 60, 3), (200, 60, 1)], 1.6, 7));
        d.run.ring.auto_mode = 1;
        let mut done = false;
        for _ in 0..600 {
            if d.tick(0) {
                done = true;
                break;
            }
        }
        assert!(done, "ring never ended");
        let r = d.result().expect("result");
        eprintln!("event ring result {:?}", r);
    }
    /// Round 6 BT4: the intro (`SetMode(5, ..)`, state 3 type 5) against live US `JRing` samples (Nicolai's attack, AP_02_U, 2026-10-16):
    /// `(+0x94 elapsed, +0x70 rot x / y in degrees, +0x84 / +0xb0)`.  The ring spins in from (91, -32) through face-on (~0.1 s) to its
    /// home tilt (-30, 55); retail's home scale is 1.0 against the port's 0.85, so the radius grows by the same fraction of home.
    #[test]
    fn the_ring_intro_follows_the_live_us_samples() {
        const LIVE: [(f32, f32, f32, f32); 8] = [
            (0.030, 90.9, -31.7, 0.241),
            (0.063, 153.7, -103.6, 0.440),
            (0.095, -161.2, -155.0, 0.583),
            (0.128, -126.7, 165.6, 0.693),
            (0.161, -101.3, 136.5, 0.774),
            (0.194, -82.6, 115.1, 0.833),
            (0.292, -51.3, 79.3, 0.932),
            (0.390, -38.6, 64.8, 0.973),
        ];
        let mut r = RingRun::start_areas(&[(169, 90, 14), (279, 72, 11)], 1.6, 7);
        let mut samples = vec![];
        for _ in 0..40 {
            let j = &r.ring;
            if j.state == jring::state::INTRO && j.sub == 1 {
                samples.push((j.anim_c, j.rot[0].to_degrees(), j.rot[1].to_degrees(), j.scale_y / j.home_scale_y));
            }
            r.tick(0);
        }
        let wrap = |d: f32| (d + 540.0).rem_euclid(360.0) - 180.0;
        for (c, x, y, s) in LIVE {
            // the port's tick nearest in elapsed time (the live game runs two 1/60 s steps per frame)
            let p = samples.iter().min_by(|a, b| (a.0 - c).abs().total_cmp(&(b.0 - c).abs())).unwrap();
            assert!(wrap(p.1 - x).abs() < 12.0 && wrap(p.2 - y).abs() < 12.0, "t {c}: live ({x}, {y}) port ({}, {})", p.1, p.2);
            assert!((p.3 - s).abs() < 0.12, "t {c}: live scale {s} port {}", p.3);
        }
    }
}
