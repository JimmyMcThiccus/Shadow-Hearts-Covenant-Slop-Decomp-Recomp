//! Hardware-independent packet / draw-list representation (what the PS2 code expressed as DMA chains).
//!
//! * [`Packet`] = a `VIF1Prim::getPacket()` result: a sub-chain that ends in a `ret` tag.  Items are GIF data blocks
//!   (the payload of a VIF `DIRECT`) or calls to other packets (e.g. the one-off texture upload chain, `call` tags in the original).
//! * [`DrawList`] = what `World::WorldGetPacket()` produced for one frame: per layer, in order, optional `Env` calls and prim packets.
//!
//! The renderer walks a [`DrawList`], feeds GIF items to [`crate::gs::GsInterpreter`] and replays the resulting
//! [`crate::gs::GsEvent`]s on a modern GPU.  Section C model packets are carried by `PacketItem::Model`.

use std::sync::Arc;

use crate::gs::{GsEvent, GsInterpreter, Qword};

/// Hook for packets whose payload is not GS-ready (VU1-transformed meshes).  Section C fills this.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ModelDrawRef {
    /// Opaque handle owned by the model system (`Model*` in the original).
    pub model: u64,
    /// Atomic / polygon-group index inside the model.
    pub part: u32,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub enum PacketItem {
    /// Raw GIF data (one or more GIFtag-led packets) — the payload of a VIF1 `DIRECT`/`DIRECTHL`.
    Gif(Vec<Qword>),
    /// `call` into another packet.
    Call(Arc<Packet>),
    /// Mesh draw request (Section C).
    Model(ModelDrawRef),
}

/// A sub-chain: list of items, implicitly terminated by `ret`.
#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct Packet {
    pub items: Vec<PacketItem>,
}

impl Packet {
    pub fn new() -> Self {
        Self::default()
    }
    pub fn gif(qws: Vec<Qword>) -> Self {
        Packet { items: vec![PacketItem::Gif(qws)] }
    }
    pub fn push_gif(&mut self, qws: Vec<Qword>) -> &mut Self {
        self.items.push(PacketItem::Gif(qws));
        self
    }
    pub fn push_call(&mut self, p: Arc<Packet>) -> &mut Self {
        self.items.push(PacketItem::Call(p));
        self
    }

    /// Visit all GIF blocks depth-first in execution order (call = recurse).
    pub fn for_each_gif<'a>(&'a self, f: &mut dyn FnMut(&'a [Qword])) {
        for it in &self.items {
            match it {
                PacketItem::Gif(v) => f(v),
                PacketItem::Call(p) => p.for_each_gif(f),
                PacketItem::Model(_) => {}
            }
        }
    }

    /// Run the whole packet through a GS interpreter and collect the events.
    pub fn execute(&self, gs: &mut GsInterpreter) -> Vec<GsEvent> {
        self.for_each_gif(&mut |q| gs.feed(q));
        gs.take_events()
    }

    /// Number of qwords a faithful DMA encoding would occupy (tag + vif + data per GIF block, plus ret) — informational.
    pub fn dma_qwords(&self) -> usize {
        let mut n = 1; // ret
        for it in &self.items {
            n += match it {
                PacketItem::Gif(v) => 1 + v.len(),
                PacketItem::Call(_) => 1,
                PacketItem::Model(_) => 1,
            };
        }
        n
    }
}

/// One entry of the per-frame draw list.
#[derive(Clone, Debug)]
pub enum DrawEntry {
    /// Shared state packet (`VIF1Prim::pEnv`), emitted only when it changes from the previous one.
    Env(Arc<Packet>),
    /// A primitive's own packet.
    Prim { id: crate::world::PrimId, layer: u8, packet: Arc<Packet> },
}

/// Output of `World::world_get_packet` (JP 0x00225d30) — the whole frame, layer 0..15 in order, END implied.
#[derive(Clone, Debug, Default)]
pub struct DrawList {
    pub entries: Vec<DrawEntry>,
}

impl DrawList {
    pub fn prim_count(&self) -> usize {
        self.entries.iter().filter(|e| matches!(e, DrawEntry::Prim { .. })).count()
    }

    /// Execute the entire frame on a software GS front end (for tests / offline replay).
    pub fn execute(&self, gs: &mut GsInterpreter) -> Vec<GsEvent> {
        for e in &self.entries {
            match e {
                DrawEntry::Env(p) => p.for_each_gif(&mut |q| gs.feed(q)),
                DrawEntry::Prim { packet, .. } => packet.for_each_gif(&mut |q| gs.feed(q)),
            }
        }
        gs.take_events()
    }
}
