//! BufMemory (JP `dvdorder.cpp`/`FileIOLib`, ctor 0x0022dc70/0x0022dcb0, dtor 0x0022ddb0).
//!
//! 16-byte handle that owns (or merely points at) a block of EE memory and is the standard "I read a file into
//! this" currency: `DvdromOrder` callbacks all receive a `BufMemory*` (`int cb(int tag, BufMemory*, int size, char* path, void* user)`).
//! ```text
//! +0x00 u8*  alloc    raw `new[]` pointer (0 for SetBuffer'd views => dtor does not free)
//! +0x04 u8*  buffer   `alloc` rounded up to `align` (0x80 for disc reads, so the IOP can DMA sector aligned)
//! +0x08 u64  size     size + align (accounted in `BufMemory::NowByte` 0x0040abf0)
//! ```
//! ctor(size, align): `size64 = size + align; NowByte += size64; alloc = new u8[size64];
//! buffer = alloc % align == 0 ? alloc : alloc + (align - alloc % align)`.
//! `SetBuffer(size, ptr)` just stores `buffer = ptr; size = size` (no ownership) — used by `Overlay::Load` to point the
//! DVD read at the fixed overlay load address.
//!
//! The Rust version owns a `Vec<u8>`; alignment is not reproducible with the global allocator so `buffer()`
//! returns the whole usable slice (exactly `size` bytes requested).

use std::sync::atomic::{AtomicU64, Ordering};

/// `BufMemory::NowByte` — total bytes currently held by BufMemory objects (debug HUD).
pub static NOW_BYTE: AtomicU64 = AtomicU64::new(0);

#[derive(Debug)]
pub struct BufMemory {
    data: Vec<u8>,
    /// requested usable size
    size: usize,
    align: usize,
    owned: bool,
    /// non-owning view installed with `set_buffer` (counts as "has a buffer")
    view: bool,
    accounted: u64,
}

impl BufMemory {
    // JP: 0x0022dc40 __ct__9BufMemoryFv
    pub fn empty() -> Self {
        BufMemory { data: Vec::new(), size: 0, align: 0, owned: false, view: false, accounted: 0 }
    }
    // JP: 0x0022dcb0 __ct__9BufMemoryFUlUi
    pub fn new(size: usize, align: usize) -> Self {
        let accounted = (size + align) as u64;
        NOW_BYTE.fetch_add(accounted, Ordering::Relaxed);
        BufMemory { data: vec![0; size], size, align, owned: true, view: false, accounted }
    }
    /// wrap bytes that were produced elsewhere (host file read)
    pub fn from_vec(v: Vec<u8>, align: usize) -> Self {
        let accounted = (v.len() + align) as u64;
        NOW_BYTE.fetch_add(accounted, Ordering::Relaxed);
        let size = v.len();
        BufMemory { data: v, size, align, owned: true, view: false, accounted }
    }
    // JP: 0x0022dc70 SetBuffer__9BufMemoryFUlPUc — non-owning view; in Rust a "view" is just a size marker
    pub fn set_buffer(&mut self, size: usize) {
        self.size = size;
        self.owned = false;
        self.view = true;
        self.data.clear();
    }
    // JP: 0x0022b650 getBuffer__9BufMemoryFv
    pub fn get_buffer(&self) -> &[u8] {
        &self.data[..self.size.min(self.data.len())]
    }
    pub fn get_buffer_mut(&mut self) -> &mut [u8] {
        let n = self.size.min(self.data.len());
        &mut self.data[..n]
    }
    pub fn size(&self) -> usize {
        self.size
    }
    pub fn align(&self) -> usize {
        self.align
    }
    pub fn is_owned(&self) -> bool {
        self.owned
    }
    pub fn is_set(&self) -> bool {
        self.view || self.owned
    }
}

impl Drop for BufMemory {
    // JP: 0x0022ddb0 __dt__9BufMemoryFv
    fn drop(&mut self) {
        if self.accounted != 0 {
            NOW_BYTE.fetch_sub(self.accounted, Ordering::Relaxed);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn accounting() {
        let b = BufMemory::new(100, 0x80);
        assert_eq!(b.get_buffer().len(), 100);
        assert!(NOW_BYTE.load(Ordering::Relaxed) >= 228);
        let mut v = BufMemory::empty();
        assert!(!v.is_set());
        v.set_buffer(0);
        assert!(v.is_set());
    }
}
