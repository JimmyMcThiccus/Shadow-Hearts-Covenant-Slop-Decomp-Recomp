//! CList / CPolObj / CPoller (JP `app.cpp` region 0x003d6470..0x003d7144).
//!
//! `CPoller` is the engine's per-frame update list: an intrusive doubly linked list of `CPolObj`
//! sorted by an ascending `u16` priority.  `CApp` owns three of them:
//!
//! | CApp offset | role                                                    |
//! |-------------|---------------------------------------------------------|
//! | `+0x48`     | game poller A (scene objects; skipped while paused)     |
//! | `+0x54`     | game poller B (skipped while paused)                    |
//! | `+0x60`     | system poller (SSHSys prio 0x40, CPauser, CVibeMan ...) |
//!
//! C++ layout of `CPolObj` (0x18 bytes):
//! ```text
//! +0x00 CPoller* owner       +0x04 CPolObj* next      +0x08 CPolObj* prev
//! +0x0c u8 autoDelete        +0x0d u8 linked          +0x0e u8 killReq     +0x0f u8 (cleared on Remove)
//! +0x10 u16 priority (default 0x80)                  +0x14 vtable { +8 dtor(int del), +0xc bool Polling() }
//! ```
//! `Polling()` returns non-zero when the object is finished and must be removed.
//! `CPoller` (0xc bytes): `+0 head, +4 tail, +8 current`.

use std::any::Any;

/// Default priority of a `CPolObj` (`__ct__7CPolObjFv` stores 0x80).
pub const DEFAULT_PRIORITY: u16 = 0x80;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub struct PolHandle(pub u32);

/// Operations an object can request on its own poller while it is being polled.
/// (In C++ these are direct calls `Entry`/`Dispose` on `app->m_poller`; here they are queued and
/// applied right after the object's `polling()` returns, before the next object is visited.)
pub enum PollOp {
    Entry { obj: Box<dyn PolObj>, priority: u16, auto_delete: bool },
    Dispose(PolHandle),
}

#[derive(Default)]
pub struct PollCtl {
    ops: Vec<PollOp>,
}
impl PollCtl {
    pub fn entry(&mut self, obj: Box<dyn PolObj>, priority: u16, auto_delete: bool) {
        self.ops.push(PollOp::Entry { obj, priority, auto_delete });
    }
    pub fn dispose(&mut self, h: PolHandle) {
        self.ops.push(PollOp::Dispose(h));
    }
}

/// `CPolObj` virtual interface.
pub trait PolObj: Any {
    /// vtable `+0xc` — return `true` when finished (object is then removed, and dropped if auto-delete).
    fn polling(&mut self, ctl: &mut PollCtl) -> bool;
    fn as_any(&self) -> &dyn Any;
    fn as_any_mut(&mut self) -> &mut dyn Any;
}

struct Slot {
    id: PolHandle,
    priority: u16,
    auto_delete: bool,
    kill_req: bool,
    obj: Option<Box<dyn PolObj>>,
}

#[derive(Default)]
pub struct CPoller {
    slots: Vec<Slot>,
    next_id: u32,
    current: Option<PolHandle>,
    /// non-auto-delete objects that finished; caller owns them again (C++: they simply stay alive elsewhere)
    released: Vec<Box<dyn PolObj>>,
}

impl CPoller {
    pub fn new() -> Self {
        Self::default()
    }

    // JP: 0x003d6710 Entry__7CPollerFP7CPolObjib
    /// Insert sorted by priority (ascending; a new object goes *after* existing objects of equal priority).
    /// The C++ version prints a warning if the object is already linked.
    pub fn entry(&mut self, obj: Box<dyn PolObj>, priority: u16, auto_delete: bool) -> PolHandle {
        let id = PolHandle(self.next_id);
        self.next_id += 1;
        let pos = self.slots.iter().position(|s| (priority as i32) < s.priority as i32).unwrap_or(self.slots.len());
        self.slots.insert(pos, Slot { id, priority, auto_delete, kill_req: false, obj: Some(obj) });
        id
    }

    // JP: 0x003d6a70 Find__7CPollerCFPC7CPolObj
    pub fn find(&self, h: PolHandle) -> bool {
        self.slots.iter().any(|s| s.id == h)
    }

    pub fn len(&self) -> usize {
        self.slots.len()
    }
    pub fn is_empty(&self) -> bool {
        self.slots.is_empty()
    }

    pub fn get(&self, h: PolHandle) -> Option<&dyn PolObj> {
        self.slots.iter().find(|s| s.id == h).and_then(|s| s.obj.as_deref())
    }
    pub fn get_mut(&mut self, h: PolHandle) -> Option<&mut dyn PolObj> {
        match self.slots.iter_mut().find(|s| s.id == h) {
            Some(s) => match &mut s.obj {
                Some(b) => Some(b.as_mut()),
                None => None,
            },
            None => None,
        }
    }

    // JP: 0x003d6b30 Dispose__7CPollerFP7CPolObj  (+ 0x003d6550 Remove__7CPolObjFv)
    /// Unlink an object.  If it is the object currently being polled it is only *flagged*
    /// (`killReq`, `CPolObj+0xe`) and the poll loop finishes the removal; otherwise an auto-delete object is
    /// dropped immediately, a non-auto-delete one is handed back via [`CPoller::take_released`].
    pub fn dispose(&mut self, h: PolHandle) {
        if self.current == Some(h) {
            if let Some(s) = self.slots.iter_mut().find(|s| s.id == h) {
                s.kill_req = true;
            }
            return;
        }
        if let Some(pos) = self.slots.iter().position(|s| s.id == h) {
            let s = self.slots.remove(pos);
            if let Some(o) = s.obj {
                if !s.auto_delete {
                    self.released.push(o);
                }
            }
        }
    }

    pub fn take_released(&mut self) -> Vec<Box<dyn PolObj>> {
        std::mem::take(&mut self.released)
    }

    // JP: 0x003d6c90 Polling__7CPollerFv
    pub fn polling(&mut self) {
        let mut idx = 0;
        while idx < self.slots.len() {
            let id = self.slots[idx].id;
            self.current = Some(id);
            let mut obj = self.slots[idx].obj.take().expect("object being polled twice");
            let mut ctl = PollCtl::default();
            let done = obj.polling(&mut ctl);
            // put it back (the slot may have moved if ops were applied; find by id)
            let mut pos = self.slots.iter().position(|s| s.id == id).unwrap_or(idx);
            self.slots[pos].obj = Some(obj);
            // apply queued ops in order
            for op in ctl.ops {
                match op {
                    PollOp::Entry { obj, priority, auto_delete } => {
                        self.entry(obj, priority, auto_delete);
                    }
                    PollOp::Dispose(h) => self.dispose(h),
                }
            }
            pos = self.slots.iter().position(|s| s.id == id).unwrap_or(pos);
            let kill = self.slots[pos].kill_req;
            self.current = None;
            if done || kill {
                let s = self.slots.remove(pos);
                if let (Some(o), false) = (s.obj, s.auto_delete) {
                    self.released.push(o);
                }
                idx = pos; // next element slid into this index
            } else {
                idx = pos + 1;
            }
        }
    }
}

/// `CList` (JP 0x003d6d90..0x003d7144, 8 bytes: `next`, `prev`).  Used for `DelayDeleteObject` and a few
/// misc queues.  Note the (confusing) naming in the original: `GetHead` follows `prev` links to the first
/// element, `GetTail` follows `next` links to the last.  This arena version keeps the same semantics.
#[derive(Debug, Default, Clone)]
pub struct CList<T> {
    items: std::collections::VecDeque<T>,
}
impl<T> CList<T> {
    pub fn new() -> Self {
        Self { items: Default::default() }
    }
    /// `AddTail` / `InsertAfter(tail)`
    pub fn add_tail(&mut self, v: T) {
        self.items.push_back(v);
    }
    /// `InsertBefore(head)`
    pub fn add_head(&mut self, v: T) {
        self.items.push_front(v);
    }
    /// `RemoveHead`
    pub fn remove_head(&mut self) -> Option<T> {
        self.items.pop_front()
    }
    pub fn len(&self) -> usize {
        self.items.len()
    }
    pub fn is_empty(&self) -> bool {
        self.items.is_empty()
    }
    pub fn drain(&mut self) -> impl Iterator<Item = T> + '_ {
        self.items.drain(..)
    }
    pub fn iter(&self) -> impl Iterator<Item = &T> {
        self.items.iter()
    }
}

/// `DelayDeleteObject` (JP 0x00222150 ctor, vtable 0x004049f0: `+8` dtor, `+0xc` DelayDelete).
/// Objects that cannot be destroyed in the middle of a frame call `DelayDelete()`, which appends the
/// embedded `CList` node to `app->m_delayDelete` (CApp+0x6c) unless it is already queued.
/// `CApp::Run` pops the queue after `sceGsSyncPath` and calls each node's virtual destructor.
#[derive(Default)]
pub struct DelayDeleteQueue {
    q: Vec<Box<dyn Any + Send>>,
}
impl DelayDeleteQueue {
    // JP: 0x00226520 DelayDelete__17DelayDeleteObjectFv
    pub fn delay_delete(&mut self, obj: Box<dyn Any + Send>) {
        self.q.push(obj);
    }
    /// flush at the end of the frame (drops everything queued)
    pub fn flush(&mut self) -> usize {
        let n = self.q.len();
        self.q.clear();
        n
    }
    pub fn len(&self) -> usize {
        self.q.len()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct Counter {
        n: u32,
        limit: u32,
        tag: &'static str,
        log: std::sync::Arc<std::sync::Mutex<Vec<&'static str>>>,
    }
    impl PolObj for Counter {
        fn polling(&mut self, _: &mut PollCtl) -> bool {
            self.n += 1;
            self.log.lock().unwrap().push(self.tag);
            self.n >= self.limit
        }
        fn as_any(&self) -> &dyn Any {
            self
        }
        fn as_any_mut(&mut self) -> &mut dyn Any {
            self
        }
    }

    #[test]
    fn priority_order_and_completion() {
        let log = std::sync::Arc::new(std::sync::Mutex::new(vec![]));
        let mut p = CPoller::new();
        p.entry(Box::new(Counter { n: 0, limit: 2, tag: "b", log: log.clone() }), 0x80, true);
        p.entry(Box::new(Counter { n: 0, limit: 1, tag: "a", log: log.clone() }), 0x40, true);
        p.entry(Box::new(Counter { n: 0, limit: 9, tag: "c", log: log.clone() }), 0x80, true);
        p.polling();
        assert_eq!(*log.lock().unwrap(), vec!["a", "b", "c"]);
        assert_eq!(p.len(), 2); // "a" finished
        p.polling();
        assert_eq!(p.len(), 1); // "b" finished
    }
}
