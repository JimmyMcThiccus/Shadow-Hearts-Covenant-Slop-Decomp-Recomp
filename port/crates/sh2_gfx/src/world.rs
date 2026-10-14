//! `World` (ordering tables), `VIF1Prim`, `VIF1PrimChain` — JP libgsx.cpp 0x002257d0..0x00226520.
//!
//! The original keeps 16 sorted linked lists of `VIF1Prim*` ("layers").  Each frame `WorldGetPacket` asks every visible prim for its
//! packet (virtual `getPacket`) and writes `call` tags into a DMA buffer.  Here prims live in a [`PrimStore`] arena and the
//! result is a [`DrawList`].

use std::sync::Arc;

use crate::packet::{DrawEntry, DrawList, Packet};

pub const NUM_LAYERS: usize = 16;

/// Index of a prim inside the [`PrimStore`] (stands in for `VIF1Prim*`).
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct PrimId(pub u32);

/// `VIF1Prim::flags` (byte at +0x0c).
pub mod prim_flags {
    /// bit0: set by subclasses when active this frame; cleared by `changebActiveFlg`.
    pub const ACTIVE: u8 = 0x01;
    /// bits1-2: per-frame pass counter (0..3), cleared each frame, incremented by LayerGetPacket.
    pub const PASS_MASK: u8 = 0x06;
    /// bit3: hidden — skipped by LayerGetPacket.
    pub const HIDDEN: u8 = 0x08;
    /// bit4: z-volume locked — `changeZvolume` ignores the prim.
    pub const Z_LOCKED: u8 = 0x10;
}

/// The data members of the C++ base class `VIF1Prim` (size 0x14 with the vptr).
#[derive(Clone, Debug, Default)]
pub struct PrimBase {
    /// `pEnv` (+0x08): optional shared state packet. Emitted once when it differs from `World::last_env`.
    pub env: Option<Arc<Packet>>,
    /// +0x0c
    pub flags: u8,
    /// +0x0e — sort key inside a layer (descending: largest first).
    pub zvolume: i16,
}

/// Virtual interface of `VIF1Prim` (vtable slot 1 = `getPacket`).
pub trait Vif1Prim: Send + Sync {
    fn base(&self) -> &PrimBase;
    fn base_mut(&mut self) -> &mut PrimBase;
    /// JP: `getPacket()` — build/refresh this prim's packet for the frame and return it, or `None` to draw nothing.
    /// `env_parity` is `VIF1Prim::m_Env & 1`: subclasses double-buffer their packet memory with it.
    fn get_packet(&mut self, env_parity: u8) -> Option<Arc<Packet>>;
}

/// Arena of prims, addressed by [`PrimId`].
#[derive(Default)]
pub struct PrimStore {
    slots: Vec<Option<Box<dyn Vif1Prim>>>,
    free: Vec<u32>,
}

impl PrimStore {
    pub fn new() -> Self {
        Self::default()
    }
    pub fn insert(&mut self, p: Box<dyn Vif1Prim>) -> PrimId {
        if let Some(i) = self.free.pop() {
            self.slots[i as usize] = Some(p);
            PrimId(i)
        } else {
            self.slots.push(Some(p));
            PrimId(self.slots.len() as u32 - 1)
        }
    }
    pub fn remove(&mut self, id: PrimId) -> Option<Box<dyn Vif1Prim>> {
        let r = self.slots.get_mut(id.0 as usize)?.take();
        if r.is_some() {
            self.free.push(id.0);
        }
        r
    }
    pub fn get(&self, id: PrimId) -> Option<&dyn Vif1Prim> {
        self.slots.get(id.0 as usize)?.as_deref()
    }
    pub fn get_mut(&mut self, id: PrimId) -> Option<&mut (dyn Vif1Prim + 'static)> {
        self.slots.get_mut(id.0 as usize)?.as_deref_mut()
    }
    pub fn z(&self, id: PrimId) -> i16 {
        self.get(id).map(|p| p.base().zvolume).unwrap_or(0)
    }
}

/// One layer = the `VIF1PrimChain` list.
#[derive(Clone, Debug, Default)]
struct Layer {
    nodes: Vec<PrimId>,
}

/// JP: class `World` (0x4120 bytes, single instance `CApp::m_World` @0x0042bf10).
pub struct World {
    /// `cam[2]` — opaque camera handles (`GsxCamera*`); index 0 is the active camera.
    pub cameras: [Option<crate::camera::CameraId>; 2],
    layers: [Layer; NUM_LAYERS],
    /// `layerCount[l]` (+0x40d0): prims counted per layer (layers with 0 are skipped).
    layer_count: [i32; NUM_LAYERS],
    /// `bufIdx` (+0x4110): which of the two DMA build buffers is being filled; flipped by `EndUpdate`.
    pub buf_idx: u8,
    /// `lastEnv` (+0x08) — NOT reset per frame in the original.
    last_env: Option<Arc<Packet>>,
    /// `VIF1Prim::m_Env` (static byte @0x0040abb0): toggled every frame by `changebActiveFlg`.
    pub m_env: u8,
}

impl Default for World {
    fn default() -> Self {
        World {
            cameras: [None, None],
            layers: Default::default(),
            layer_count: [0; NUM_LAYERS],
            buf_idx: 0,
            last_env: None,
            m_env: 0,
        }
    }
}

impl World {
    pub fn new() -> Self {
        Self::default()
    }

    /// JP 0x002258f0 `VIF1PrimChain::add` — insert before the first node with a strictly smaller z (stable for equal z).
    fn insert_sorted(&mut self, layer: usize, id: PrimId, store: &PrimStore) {
        let z = store.z(id);
        let nodes = &mut self.layers[layer].nodes;
        let pos = nodes.iter().position(|n| store.z(*n) < z).unwrap_or(nodes.len());
        nodes.insert(pos, id);
    }

    /// JP 0x002261d0 `AddOT(layer, prim)`.
    pub fn add_ot(&mut self, layer: i32, id: PrimId, store: &PrimStore) -> bool {
        if !(0..NUM_LAYERS as i32).contains(&layer) || store.get(id).is_none() {
            return false;
        }
        self.layer_count[layer as usize] += 1;
        self.insert_sorted(layer as usize, id, store);
        true
    }

    /// JP 0x00226160 `AddDoubleOT`.
    pub fn add_double_ot(&mut self, a: i32, b: i32, id: PrimId, store: &PrimStore) -> bool {
        let x = self.add_ot(a, id, store);
        let y = self.add_ot(b, id, store);
        x & y
    }

    /// JP 0x00226240 `AddOTBefor(ref, prim)`.
    pub fn add_ot_before(&mut self, reference: PrimId, id: PrimId) -> bool {
        self.add_relative(reference, id, 0)
    }

    /// JP 0x00226300 `AddOTAfter(ref, prim)`.
    pub fn add_ot_after(&mut self, reference: PrimId, id: PrimId) -> bool {
        self.add_relative(reference, id, 1)
    }

    fn add_relative(&mut self, reference: PrimId, id: PrimId, after: usize) -> bool {
        let Some(layer) = self.find_ot_index(reference) else { return false };
        self.layer_count[layer] += 1;
        let nodes = &mut self.layers[layer].nodes;
        let pos = nodes.iter().position(|n| *n == reference).unwrap();
        nodes.insert(pos + after, id);
        true
    }

    /// JP 0x00225fb0 `ReleaseOT` — removes *every* occurrence in *every* layer; true if anything was removed.
    pub fn release_ot(&mut self, id: PrimId) -> bool {
        let mut any = false;
        for l in 0..NUM_LAYERS {
            while let Some(p) = self.layers[l].nodes.iter().position(|n| *n == id) {
                self.layers[l].nodes.remove(p);
                self.layer_count[l] -= 1;
                any = true;
            }
        }
        any
    }

    /// JP 0x00226060 `FindOT`.
    pub fn find_ot(&self, id: PrimId) -> bool {
        self.find_ot_index(id).is_some()
    }

    /// JP 0x002260e0 `FindOTindex` (original returns -1 for not found).
    pub fn find_ot_index(&self, id: PrimId) -> Option<usize> {
        (0..NUM_LAYERS).find(|&l| self.layers[l].nodes.contains(&id))
    }

    /// JP 0x002263c0 `changeZvolume` — re-sorts a prim in every layer that holds it (no-op if `Z_LOCKED`).
    pub fn change_zvolume(&mut self, id: PrimId, store: &PrimStore) {
        let locked = store.get(id).map(|p| p.base().flags & prim_flags::Z_LOCKED != 0).unwrap_or(true);
        if locked {
            return;
        }
        for l in 0..NUM_LAYERS {
            if let Some(p) = self.layers[l].nodes.iter().position(|n| *n == id) {
                self.layers[l].nodes.remove(p);
                self.insert_sorted(l, id, store);
            }
        }
    }

    /// JP 0x00225860 `VIF1Prim::setZvolume` (+ `changeZvolume`).
    pub fn set_zvolume(&mut self, id: PrimId, z: i16, store: &mut PrimStore) {
        if let Some(p) = store.get_mut(id) {
            if p.base().zvolume == z {
                return;
            }
            p.base_mut().zvolume = z;
        }
        self.change_zvolume(id, store);
    }

    /// Count of prims in a layer (`layerCount[l]`).
    pub fn layer_len(&self, layer: usize) -> i32 {
        self.layer_count[layer]
    }
    pub fn layer_nodes(&self, layer: usize) -> &[PrimId] {
        &self.layers[layer].nodes
    }

    /// JP 0x00225db0 `changebActiveFlg()` — start-of-frame bookkeeping: clears ACTIVE and pass counters and toggles `m_Env`.
    pub fn change_active_flg(&mut self, store: &mut PrimStore) {
        for l in 0..NUM_LAYERS {
            for id in self.layers[l].nodes.clone() {
                if let Some(p) = store.get_mut(id) {
                    p.base_mut().flags &= !(prim_flags::ACTIVE | prim_flags::PASS_MASK);
                }
            }
        }
        self.m_env ^= 1;
    }

    /// JP 0x00226460 `BeginUpdate()`.  `clear_requested` = `camera->flags & 4`; the caller then issues `ClearRaster`.
    pub fn begin_update(&mut self, store: &mut PrimStore, clear_requested: bool) -> bool {
        self.change_active_flg(store);
        clear_requested
    }

    /// JP 0x002264b0 `EndUpdate()`.
    pub fn end_update(&mut self) {
        self.buf_idx ^= 1;
    }

    /// JP 0x002264c0 `SetCamera(idx<2, cam)` returns the previous camera.
    pub fn set_camera(&mut self, idx: usize, cam: Option<crate::camera::CameraId>) -> Option<crate::camera::CameraId> {
        if idx >= 2 {
            return None;
        }
        std::mem::replace(&mut self.cameras[idx], cam)
    }
    pub fn get_camera(&self, idx: usize) -> Option<crate::camera::CameraId> {
        self.cameras.get(idx).copied().flatten()
    }

    /// JP 0x00225e40 `LayerGetPacket` + 0x00225d30 `WorldGetPacket`: build the frame's draw list.
    pub fn world_get_packet(&mut self, store: &mut PrimStore) -> DrawList {
        let mut out = DrawList::default();
        for layer in 0..NUM_LAYERS {
            if self.layer_count[layer] == 0 {
                continue;
            }
            for id in self.layers[layer].nodes.clone() {
                let parity = self.m_env & 1;
                let Some(prim) = store.get_mut(id) else { continue };
                if prim.base().flags & prim_flags::HIDDEN != 0 {
                    continue;
                }
                let pkt = prim.get_packet(parity);
                let b = prim.base_mut();
                let pass = ((b.flags & prim_flags::PASS_MASK) >> 1).wrapping_add(1) & 3;
                b.flags = (b.flags & !prim_flags::PASS_MASK) | (pass << 1);
                let Some(pkt) = pkt else { continue };
                if let Some(env) = prim.base().env.clone() {
                    let changed = match &self.last_env {
                        Some(last) => !Arc::ptr_eq(last, &env),
                        None => true,
                    };
                    if changed {
                        out.entries.push(DrawEntry::Env(env.clone()));
                        self.last_env = Some(env);
                    }
                }
                out.entries.push(DrawEntry::Prim { id, layer: layer as u8, packet: pkt });
            }
        }
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct Dummy {
        base: PrimBase,
        pkt: Arc<Packet>,
        calls: u32,
    }
    impl Dummy {
        fn boxed(z: i16) -> Box<dyn Vif1Prim> {
            Box::new(Dummy { base: PrimBase { zvolume: z, ..Default::default() }, pkt: Arc::new(Packet::new()), calls: 0 })
        }
    }
    impl Vif1Prim for Dummy {
        fn base(&self) -> &PrimBase {
            &self.base
        }
        fn base_mut(&mut self) -> &mut PrimBase {
            &mut self.base
        }
        fn get_packet(&mut self, _p: u8) -> Option<Arc<Packet>> {
            self.calls += 1;
            Some(self.pkt.clone())
        }
    }

    #[test]
    fn sorted_descending_stable() {
        let mut store = PrimStore::new();
        let mut w = World::new();
        let a = store.insert(Dummy::boxed(5));
        let b = store.insert(Dummy::boxed(9));
        let c = store.insert(Dummy::boxed(5));
        let d = store.insert(Dummy::boxed(1));
        for id in [a, b, c, d] {
            assert!(w.add_ot(3, id, &store));
        }
        assert_eq!(w.layer_nodes(3), &[b, a, c, d]);
        assert_eq!(w.layer_len(3), 4);
        // re-sort after z change
        w.set_zvolume(d, 100, &mut store);
        assert_eq!(w.layer_nodes(3)[0], d);
        assert!(w.release_ot(d));
        assert_eq!(w.layer_len(3), 3);
        assert!(!w.add_ot(16, a, &store));
        assert!(!w.add_ot(-1, a, &store));
    }

    #[test]
    fn env_elision_and_hidden() {
        let mut store = PrimStore::new();
        let mut w = World::new();
        let env = Arc::new(Packet::gif(vec![crate::gs::Qword::new(1, 2)]));
        let mk = |z: i16, env: Option<Arc<Packet>>, store: &mut PrimStore| {
            let id = store.insert(Dummy::boxed(z));
            store.get_mut(id).unwrap().base_mut().env = env;
            id
        };
        let p1 = mk(3, Some(env.clone()), &mut store);
        let p2 = mk(2, Some(env.clone()), &mut store);
        let p3 = mk(1, None, &mut store);
        let hidden = mk(0, Some(env.clone()), &mut store);
        store.get_mut(hidden).unwrap().base_mut().flags |= prim_flags::HIDDEN;
        for id in [p1, p2, p3, hidden] {
            w.add_ot(0, id, &store);
        }
        let dl = w.world_get_packet(&mut store);
        let envs = dl.entries.iter().filter(|e| matches!(e, DrawEntry::Env(_))).count();
        assert_eq!(envs, 1);
        assert_eq!(dl.prim_count(), 3);
        // pass counter incremented once for visible prims
        assert_eq!(store.get(p1).unwrap().base().flags & prim_flags::PASS_MASK, 1 << 1);
        w.change_active_flg(&mut store);
        assert_eq!(store.get(p1).unwrap().base().flags & prim_flags::PASS_MASK, 0);
        assert_eq!(w.m_env, 1);
    }

    #[test]
    fn before_after() {
        let mut store = PrimStore::new();
        let mut w = World::new();
        let a = store.insert(Dummy::boxed(0));
        let b = store.insert(Dummy::boxed(0));
        let c = store.insert(Dummy::boxed(0));
        w.add_ot(7, a, &store);
        assert!(w.add_ot_before(a, b));
        assert!(w.add_ot_after(a, c));
        assert_eq!(w.layer_nodes(7), &[b, a, c]);
        assert_eq!(w.find_ot_index(c), Some(7));
    }
}
