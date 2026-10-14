//! BRN_LinkList — verlet-style rope/hair/cloth chain used by model effects (JP `BRN_calc_linklist.cpp`, 0x00249290..0x0024b4a0).
//! Only the data layout and the simple accessors are ported; the force/constraint solver (`applyForces` 0x67c bytes,
//! `applyConstraint` 0x898, `calcNextLinkList` 0x474, `sym_tridiag_solver`) is VU0-macro-code heavy and lives in the
//! documentation (`notes/A/BRN_LinkList.md`) until section C needs it.
//!
//! ```text
//! BRN_LinkList (0x5b0):
//! +0x000 i32 mode(2)   +0x004 i32 linkCount (<=5)  +0x008 f32 airResistance (50.0)  +0x010 f32 (0) +0x014 f32 (24.5) +0x018 f32 0 +0x01c f32 1.0
//! +0x020 BRN_inertia inertia (0x70)
//! +0x090 BRN_Link links[5]     (0x60 each: +0x10 pos, +0x20 vel, +0x30 force, +0x40 mass, +0xa0-0x90=+0x10 ... see decomp)
//! +0x270 BRN_Link prevLinks[5]
//! +0x450 bending work area   +0x4a0 FVector bendRest[5]   +0x4f0 BRN_Collision[5] (0x20 each: +0x10 radius?, +0x14 restitution, +0x18 ...)
//! +0x590 collision callback   +0x5a0 f32 damping (0.95)   +0x5a4 void* collision user data   +0x5a8 u8 bendingInit
//! ```
use glam::Vec4;

pub const MAX_LINKS: usize = 5;

#[derive(Debug, Clone, Copy, Default)]
pub struct BrnLink {
    pub pos: Vec4,
    pub vel: Vec4,
    pub force: Vec4,
    pub mass: f32,
    pub length: f32,
}

#[derive(Debug, Clone)]
pub struct BrnLinkList {
    pub links: [BrnLink; MAX_LINKS],
    pub prev: [BrnLink; MAX_LINKS],
    pub count: usize,
    pub air_resistance: f32,
    pub damping: f32,
    pub bending_init: bool,
}

impl BrnLinkList {
    // JP: 0x00249290 __ct__12BRN_LinkListFi
    pub fn new(count: usize) -> Self {
        BrnLinkList {
            links: [BrnLink { mass: 1.0, ..Default::default() }; MAX_LINKS],
            prev: [BrnLink::default(); MAX_LINKS],
            count: count.min(MAX_LINKS),
            air_resistance: 50.0,
            damping: 0.95,
            bending_init: false,
        }
    }
    // JP: 0x00249af0 clearForces__12BRN_LinkListFv
    pub fn clear_forces(&mut self) {
        for l in self.links.iter_mut().take(self.count) {
            l.force = Vec4::ZERO;
        }
    }
    // JP: 0x0024b230 setDampingMultiplier
    pub fn set_damping_multiplier(&mut self, v: f32) {
        self.damping = v;
    }
    // JP: 0x0024b460 setAirResistance
    pub fn set_air_resistance(&mut self, v: f32) {
        self.air_resistance = v;
    }
    // JP: 0x0024b300 setLinkPosition (also zeroes velocity)
    pub fn set_link_position(&mut self, i: usize, p: Vec4) {
        self.links[i].pos = p;
        self.links[i].vel = Vec4::ZERO;
    }
    // JP: 0x002495b0 getLinkGeometry — offset to previous link (or absolute for link 0)
    pub fn link_geometry(&self, i: usize) -> Vec4 {
        if i == 0 { self.links[0].pos } else { self.links[i].pos - self.links[i - 1].pos }
    }
    // JP: 0x0024a3b0 dissipateEnergy
    pub fn dissipate_energy(&mut self) {
        for l in self.links.iter_mut().take(self.count) {
            l.vel *= self.damping;
        }
    }
    // JP: 0x00249460 setLinkParams — rest position/ velocity and mass, then recompute segment lengths
    pub fn set_link_params(&mut self, i: usize, pos: Vec4, vel: Vec4, mass: f32) {
        self.links[i].pos = pos;
        self.links[i].vel = vel;
        self.links[i].mass = mass;
        self.links[0].length = self.links[0].pos.truncate().length();
        for k in 1..self.count {
            self.links[k].length = (self.links[k].pos - self.links[k - 1].pos).truncate().length();
        }
        self.prev = self.links;
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn lengths() {
        let mut l = BrnLinkList::new(3);
        l.set_link_params(0, Vec4::new(0.0, 0.0, 0.0, 1.0), Vec4::ZERO, 1.0);
        l.set_link_params(1, Vec4::new(3.0, 4.0, 0.0, 1.0), Vec4::ZERO, 1.0);
        assert_eq!(l.links[1].length, 5.0);
    }
}
