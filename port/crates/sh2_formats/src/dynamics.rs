//! `DYNH` extension block: hair / cloth / tail chains (JP `DynamicsControl::Create` 0x00252f00,
//! `Dynamics::Create` 0x00253340).  See `notes/C/Dynamics.md`.

use crate::math::FVector;
use crate::model::ExtBlock;

#[derive(Clone, Debug)]
pub struct DynNode {
    /// Frame (bone) this node drives (`Frame::searchFrame(name)`).
    pub frame_name: String,
    /// +0x0c: 0.025 in the sample (mass / inertia).
    pub param_c: f32,
    /// +0x10: segment length / stiffness parameter.
    pub param_10: f32,
    /// +0x20: rest position (world, y-up authoring space like `FrameDef::translation`).
    pub rest_pos: FVector,
}

#[derive(Clone, Debug)]
pub struct DynChain {
    pub name: String,
    /// flags +0x0a: bit 3 = bending force; `flags >> 6` = damping in 1/100.
    pub flags: u16,
    /// +0x0c: gravity (s16, y = value * 0.01 * 9.8).
    pub gravity_raw: i16,
    /// +0x0e: air resistance * 100.
    pub air_resistance_raw: u16,
    pub nodes: Vec<DynNode>,
}

impl DynChain {
    pub fn gravity_y(&self) -> f32 {
        self.gravity_raw as f32 * 0.01 * 9.8
    }
    pub fn air_resistance(&self) -> f32 {
        self.air_resistance_raw as f32 * 0.01
    }
    pub fn damping(&self) -> f32 {
        (self.flags >> 6) as f32 * 0.01
    }
    pub fn bending_force(&self) -> bool {
        self.flags & 8 != 0
    }
}

fn cstr(b: &[u8]) -> String {
    b.iter().take_while(|&&c| c != 0).map(|&c| c as char).collect()
}

/// Parse the payload of a `DYNH` block.
pub fn parse_dynamics(block: &ExtBlock) -> Option<Vec<DynChain>> {
    if &block.tag != b"DYNH" {
        return None;
    }
    let d = &block.data;
    let mut p = 0usize;
    let mut chains = Vec::new();
    for _ in 0..block.count {
        let h = d.get(p..p + 0x10)?;
        let nn = u16::from_le_bytes([h[8], h[9]]) as usize;
        let mut chain = DynChain {
            name: cstr(&h[..8]),
            flags: u16::from_le_bytes([h[10], h[11]]),
            gravity_raw: i16::from_le_bytes([h[12], h[13]]),
            air_resistance_raw: u16::from_le_bytes([h[14], h[15]]),
            nodes: Vec::with_capacity(nn),
        };
        p += 0x10;
        for _ in 0..nn {
            let n = d.get(p..p + 0x30)?;
            chain.nodes.push(DynNode {
                frame_name: cstr(&n[..12]),
                param_c: f32::from_le_bytes([n[12], n[13], n[14], n[15]]),
                param_10: f32::from_le_bytes([n[16], n[17], n[18], n[19]]),
                rest_pos: FVector::read_le(&n[0x20..0x30]),
            });
            p += 0x30;
        }
        chains.push(chain);
    }
    Some(chains)
}
