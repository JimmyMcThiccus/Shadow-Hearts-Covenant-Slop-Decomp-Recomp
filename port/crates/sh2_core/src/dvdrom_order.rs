//! DvdromOrder — the asynchronous "read file then call me back" queue (JP `dvdorder.cpp`, 0x0022e130..0x0022e9d0).
//!
//! Every loader in the game (models, textures, menus, field data, sound banks, overlays, scripts ...) calls
//! `DvdromOrder::Dvdromour->ReadOrder(path, cb, tag, user, flags)` and gets
//! `int cb(int tag, BufMemory* buf, int size, char* path, void* user)` when the file is in memory.
//!
//! # Layout
//! `DvdromOrder` (0x14c): `CPolObj` (0x18, lives in *FileIOLib's* poller at prio 0x80, so `Polling` runs on the
//! FileIO thread every 5 ms) + embedded `OrderPacket` list head `+0x18` (0x12c) + `+0x144` openInFlight + `+0x148` nextSlot.
//! Static pool `OrderPackets[100]` (0x12c each) at JP 0x004197d0 (0x7530 bytes).
//!
//! `OrderPacket` (0x12c): `+0 next`, `+4 cb`, `+8 tag`, `+0xc state`, `+0x10 id`, `+0x14 size`, `+0x18 flags (|1)`,
//! `+0x1c char path[0x100]`, `+0x11c user`, `+0x120 FIOHND*`, `+0x124 BufMemory*`, `+0x128`.
//!
//! # Packet states (`+0xc`)
//! `1` open -> `2` read -> `3` wait done -> `4` callback.  Packets are processed strictly in FIFO order: the scan stops at the
//! first packet that is still waiting on the IOP.  Completed packets (state 4) before it get their callback.
//! Callback return: `1` = DvdromOrder frees the buffer, `0` = the callback kept the buffer, any other value = *retry later*
//! (packet stays at state 4).

use crate::bufmem::BufMemory;

/// Result of a callback.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum CbRet {
    /// `return 0`: callback took ownership of the buffer (took it out of the Option)
    Keep,
    /// `return 1`: free the buffer
    Free,
    /// any other value: call again on the next poll
    Retry,
}

pub struct OrderDone<'a> {
    pub tag: i32,
    pub buf: &'a mut Option<BufMemory>,
    pub size: usize,
    pub path: &'a str,
}
pub type OrderCb = Box<dyn FnMut(OrderDone<'_>) -> CbRet + Send>;

/// The part of `FileIOLib` the queue uses (`open`, `getStatus`, `read`, `getBuffer`, `getSize`, `close`).
pub trait DiscIo {
    type Handle: Copy;
    /// `FileIOLib::open(path, flags, true)`; None when the file does not exist / the IOP is busy
    fn open(&mut self, path: &str, flags: u32) -> Option<Self::Handle>;
    /// `getStatus`: 0 = idle (previous command finished)
    fn status(&mut self, h: Self::Handle) -> i32;
    fn size(&mut self, h: Self::Handle) -> usize;
    /// `read(h, buf, len)`: start the read; `preset` is a caller supplied BufMemory (else FileIOLib allocates `len` bytes, align 0x80).  true = accepted.
    fn read(&mut self, h: Self::Handle, preset: Option<BufMemory>, len: usize) -> bool;
    /// `getBuffer(h)`: the filled buffer
    fn take_buffer(&mut self, h: Self::Handle) -> Option<BufMemory>;
    fn close(&mut self, h: Self::Handle);
}

struct Order<H> {
    cb: Option<OrderCb>,
    tag: i32,
    state: u8,
    id: usize,
    size: usize,
    flags: u32,
    path: String,
    handle: Option<H>,
    buf: Option<BufMemory>,
}

pub const NUM_PACKETS: usize = 100;

pub struct DvdromOrder<H: Copy> {
    queue: std::collections::VecDeque<Order<H>>,
    used: [bool; NUM_PACKETS],
    next_slot: usize,
    /// `+0x144`: set by FileIOLib::open, cleared by close (HDD/disc "busy opening" flag read by the UI)
    pub open_in_flight: bool,
}

impl<H: Copy> Default for DvdromOrder<H> {
    fn default() -> Self {
        DvdromOrder { queue: Default::default(), used: [false; NUM_PACKETS], next_slot: 0, open_in_flight: false }
    }
}

impl<H: Copy> DvdromOrder<H> {
    pub fn new() -> Self {
        Self::default()
    }

    /// JP: 0x0022e6d0 / 0x0022e850 ReadOrder  — returns the packet id (0..99).
    /// `buf`: optional pre-allocated destination (the first overload `ReadOrder(path, cb, tag, BufMemory*, user, flags)`).
    pub fn read_order(&mut self, path: &str, cb: Option<OrderCb>, tag: i32, buf: Option<BufMemory>, flags: u32) -> usize {
        if self.used[self.next_slot] {
            // first free slot (the original scans 0..100 and keeps the last index if all are used)
            let mut i = 0;
            while i < NUM_PACKETS && self.used[i] {
                i += 1;
            }
            self.next_slot = i.min(NUM_PACKETS - 1);
        }
        let id = self.next_slot;
        self.next_slot += 1;
        if self.next_slot > NUM_PACKETS {
            self.next_slot = 0; // original: `> 100` => 0 (then id was forced to 0)
        }
        self.used[id] = true;
        self.queue.push_back(Order { cb, tag, state: 1, id, size: 0, flags: flags | 1, path: path.to_string(), handle: None, buf });
        id
    }

    /// JP: 0x0022e5c0 deleteOrder__11DvdromOrderFi  — cancel by id
    pub fn delete_order<D: DiscIo<Handle = H>>(&mut self, io: &mut D, id: usize) -> bool {
        if let Some(pos) = self.queue.iter().position(|o| o.id == id) {
            let o = self.queue.remove(pos).unwrap();
            if let Some(h) = o.handle {
                io.close(h);
            }
            self.used[id] = false;
            true
        } else {
            false
        }
    }

    pub fn pending(&self) -> usize {
        self.queue.len()
    }

    /// JP: 0x0022e320 Polling__11DvdromOrderFv
    pub fn polling<D: DiscIo<Handle = H>>(&mut self, io: &mut D) {
        let mut passes = 1;
        while passes > 0 {
            passes -= 1;
            let mut i = 0;
            let mut stop = false;
            while i < self.queue.len() && !stop {
                match self.queue[i].state {
                    4 => {
                        let o = &mut self.queue[i];
                        let mut cb = o.cb.take();
                        let ret = match cb.as_mut() {
                            Some(f) => f(OrderDone { tag: o.tag, buf: &mut o.buf, size: o.size, path: &o.path }),
                            None => CbRet::Free,
                        };
                        match ret {
                            CbRet::Retry => {
                                self.queue[i].cb = cb;
                                i += 1;
                            }
                            r => {
                                if r == CbRet::Free {
                                    self.queue[i].buf = None;
                                }
                                let o = self.queue.remove(i).unwrap();
                                self.used[o.id] = false;
                                stop = true; // list changed: rescan next poll
                            }
                        }
                    }
                    s @ (1 | 2 | 3) => {
                        let mut s = s;
                        // 1: open
                        if s == 1 {
                            let (path, flags) = (self.queue[i].path.clone(), self.queue[i].flags);
                            match io.open(&path, flags) {
                                Some(h) => {
                                    self.queue[i].handle = Some(h);
                                    self.queue[i].state = 2;
                                    s = 2;
                                }
                                None => {
                                    stop = true;
                                    continue;
                                }
                            }
                        }
                        // 2: start read when the open finished
                        if s == 2 {
                            let h = self.queue[i].handle.unwrap();
                            if io.status(h) == 0 {
                                let len = io.size(h);
                                let preset = self.queue[i].buf.take();
                                if io.read(h, preset, len) {
                                    self.queue[i].state = 3;
                                    s = 3;
                                } else {
                                    stop = true;
                                    continue;
                                }
                            } else {
                                stop = true;
                                continue;
                            }
                        }
                        // 3: wait for completion
                        if s == 3 {
                            let h = self.queue[i].handle.unwrap();
                            if io.status(h) == 0 {
                                self.queue[i].buf = io.take_buffer(h);
                                self.queue[i].size = io.size(h);
                                self.queue[i].state = 4;
                                io.close(h);
                                self.queue[i].handle = None;
                                if i + 1 < self.queue.len() {
                                    passes += 1; // `if (*piVar4 != 0) iVar6++`
                                }
                                i += 1;
                            } else {
                                stop = true;
                            }
                        }
                    }
                    _ => i += 1,
                }
            }
        }
    }
}

/// Synchronous host implementation of [`DiscIo`] over [`crate::fileio::Disc`] — every read completes immediately.
pub struct SyncDisc<'a> {
    pub disc: &'a crate::fileio::Disc,
    files: Vec<Option<(Vec<u8>, Option<BufMemory>)>>,
}
impl<'a> SyncDisc<'a> {
    pub fn new(disc: &'a crate::fileio::Disc) -> Self {
        SyncDisc { disc, files: vec![] }
    }
}
impl<'a> DiscIo for SyncDisc<'a> {
    type Handle = usize;
    fn open(&mut self, path: &str, _flags: u32) -> Option<usize> {
        let data = self.disc.read(path).ok()?;
        self.files.push(Some((data, None)));
        Some(self.files.len() - 1)
    }
    fn status(&mut self, _h: usize) -> i32 {
        0
    }
    fn size(&mut self, h: usize) -> usize {
        self.files[h].as_ref().map(|f| f.0.len()).unwrap_or(0)
    }
    fn read(&mut self, h: usize, _preset: Option<BufMemory>, _len: usize) -> bool {
        if let Some(f) = self.files[h].as_mut() {
            f.1 = Some(BufMemory::from_vec(std::mem::take(&mut f.0), 0x80));
            true
        } else {
            false
        }
    }
    fn take_buffer(&mut self, h: usize) -> Option<BufMemory> {
        self.files[h].as_mut().and_then(|f| f.1.take())
    }
    fn close(&mut self, h: usize) {
        self.files[h] = None;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct Mem {
        files: Vec<(String, Vec<u8>)>,
        open: Vec<Option<(usize, bool)>>,
        busy: i32,
    }
    impl DiscIo for Mem {
        type Handle = usize;
        fn open(&mut self, path: &str, _: u32) -> Option<usize> {
            let i = self.files.iter().position(|f| f.0 == path)?;
            self.open.push(Some((i, false)));
            Some(self.open.len() - 1)
        }
        fn status(&mut self, _: usize) -> i32 {
            if self.busy > 0 {
                self.busy -= 1;
                1
            } else {
                0
            }
        }
        fn size(&mut self, h: usize) -> usize {
            self.files[self.open[h].unwrap().0].1.len()
        }
        fn read(&mut self, h: usize, _: Option<BufMemory>, _: usize) -> bool {
            self.open[h].as_mut().unwrap().1 = true;
            self.busy = 1;
            true
        }
        fn take_buffer(&mut self, h: usize) -> Option<BufMemory> {
            Some(BufMemory::from_vec(self.files[self.open[h].unwrap().0].1.clone(), 0x80))
        }
        fn close(&mut self, h: usize) {
            self.open[h] = None;
        }
    }

    #[test]
    fn fifo_and_callback() {
        let mut io = Mem { files: vec![("a".into(), vec![1, 2, 3]), ("b".into(), vec![9])], open: vec![], busy: 0 };
        let mut q: DvdromOrder<usize> = DvdromOrder::new();
        let got = std::sync::Arc::new(std::sync::Mutex::new(vec![]));
        for (name, tag) in [("a", 10), ("b", 20)] {
            let g = got.clone();
            q.read_order(name, Some(Box::new(move |d| {
                g.lock().unwrap().push((d.tag, d.size));
                CbRet::Free
            })), tag, None, 0);
        }
        for _ in 0..10 {
            q.polling(&mut io);
        }
        assert_eq!(*got.lock().unwrap(), vec![(10, 3), (20, 1)]);
        assert_eq!(q.pending(), 0);
    }

    #[test]
    fn retry_keeps_packet() {
        let mut io = Mem { files: vec![("a".into(), vec![1])], open: vec![], busy: 0 };
        let mut q: DvdromOrder<usize> = DvdromOrder::new();
        let mut n = 0;
        q.read_order("a", Some(Box::new(move |_| { n += 1; if n < 3 { CbRet::Retry } else { CbRet::Keep } })), 0, None, 0);
        for _ in 0..10 {
            q.polling(&mut io);
        }
        assert_eq!(q.pending(), 0);
    }
}
