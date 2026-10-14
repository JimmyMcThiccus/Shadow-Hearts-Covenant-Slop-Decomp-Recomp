//! Overlay loader (`Overlay` class, `mwOverlayInit`, `cbOverlayLoad`, `cbOverlayPreLoad`).
//! JP `SSHmain.cpp` 0x0023d150..0x0023d770, Metrowerks runtime 0x00384c60 / 0x00384780 / 0x0023d430.
//!
//! # MWo3 image format (FIELD.BIN, BATTLE.BIN, OPENING.BIN)
//! The whole file is DMA'd to a fixed EE address (`mwGetGroupAddress(group)`, JP 0x00430a00 / US 0x0045ea80) and the
//! code starts 0x80 bytes in.  Header (little endian):
//! ```text
//! +0x00 "MWo3"        magic ('M','W','o','3' = 0x336f574d)
//! +0x04 u32 id        overlay group number: 1 = FIELD, 2 = BATTLE, 3 = OPENING (US only)
//! +0x08 u32 load_addr 0x00430a00 (JP) / 0x0045ea80 (US); equals mwGetGroupAddress(id)
//! +0x0c u32 text_size  code size   (JP FIELD 0x0dc6c0, BATTLE 0x220340)
//! +0x10 u32 data_size  data+sdata size (JP FIELD 0x52080, BATTLE 0x6280);  text+data ~= file size - 0x40
//! +0x14 u32 bss_size   bytes to *zero after the loaded image* (JP FIELD 0x880, BATTLE 0x100)
//! +0x18 u32 ctor_begin absolute address of the static-constructor table `[begin, end)`
//! +0x1c u32 ctor_end   (begin==end: no ctors, e.g. FIELD.BIN JP; BATTLE.BIN JP has 5 entries at 0x00656fa0)
//! +0x20 char name[16]  "FIELD.BIN"
//! +0x30.. zero, padding to 0x80
//! ```
//! `mwOverlayInit(addr, loaded_size)` (JP 0x00384c60): `FlushCache(2)`, `memset(addr + loaded_size, 0, *(addr+0x14))`
//! (the bss), then `__initialize_cpp_rts(*(addr+0x18), *(addr+0x1c))` which simply calls every function pointer in
//! the ctor table.  After the overlay is loaded the main executable's `SSHApi` implementations (CFieldSocket /
//! BtlSocket) call into it by absolute address (symbols in the main `.syms` file whose address is >= 0x430a00
//! are overlay functions).
//!
//! # Overlay object (0x40 bytes, embedded in SSHSys at +0x68)
//! ```text
//! +0x00 i32 group        (Init(group) -> mwGetGroupAddress(group) must be != 0)
//! +0x04 u8* addr         overlay load address
//! +0x08 cb(int phase,bool ok,int a0,void* a1)   load/unload notification (phase 0 = loaded, 1 = unloaded)
//! +0x0c a0   +0x10 a1    +0x14 -
//! +0x18 BufMemory buf    (non-owning view of the load address)
//! +0x28 i32 loadedSize   (InitCashe)   +0x2c BufMemory* preBuf  +0x30 i32 preState (0 none,1 loading,2 done)
//! +0x34 i32 preSize      +0x38 u8 loadPending (Load() called while pre-load still running)
//! +0x3c vtable { +8 __dt }
//! ```
use crate::bufmem::BufMemory;

pub const MWO3_MAGIC: &[u8; 4] = b"MWo3";
pub const HEADER_SIZE: usize = 0x80;
/// JP demo / US retail load addresses
pub const LOAD_ADDR_JP: u32 = 0x0043_0a00;
pub const LOAD_ADDR_US: u32 = 0x0045_ea80;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum OverlayId {
    Field = 1,
    Battle = 2,
    Opening = 3,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct OverlayHeader {
    pub id: u32,
    pub load_addr: u32,
    pub text_size: u32,
    pub data_size: u32,
    pub bss_size: u32,
    pub ctor_begin: u32,
    pub ctor_end: u32,
    pub name: String,
}

#[derive(Debug, thiserror::Error, PartialEq, Eq)]
pub enum OverlayError {
    #[error("not an MWo3 image")]
    BadMagic,
    #[error("image shorter than its header")]
    Truncated,
    #[error("ctor table outside the image")]
    BadCtorTable,
}

impl OverlayHeader {
    pub fn parse(img: &[u8]) -> Result<Self, OverlayError> {
        if img.len() < HEADER_SIZE {
            return Err(OverlayError::Truncated);
        }
        if &img[..4] != MWO3_MAGIC {
            return Err(OverlayError::BadMagic);
        }
        let u = |o: usize| u32::from_le_bytes(img[o..o + 4].try_into().unwrap());
        let name_end = img[0x20..0x30].iter().position(|&b| b == 0).unwrap_or(16);
        Ok(OverlayHeader {
            id: u(4),
            load_addr: u(8),
            text_size: u(0xc),
            data_size: u(0x10),
            bss_size: u(0x14),
            ctor_begin: u(0x18),
            ctor_end: u(0x1c),
            name: String::from_utf8_lossy(&img[0x20..0x20 + name_end]).into_owned(),
        })
    }

    /// Static constructor addresses (`__initialize_cpp_rts` input): u32 pointers in `[ctor_begin, ctor_end)`.
    pub fn ctors(&self, img: &[u8]) -> Result<Vec<u32>, OverlayError> {
        if self.ctor_end < self.ctor_begin {
            return Err(OverlayError::BadCtorTable);
        }
        let off = |a: u32| a.checked_sub(self.load_addr).map(|v| v as usize);
        let (b, e) = (off(self.ctor_begin).ok_or(OverlayError::BadCtorTable)?, off(self.ctor_end).ok_or(OverlayError::BadCtorTable)?);
        if e > img.len() {
            return Err(OverlayError::BadCtorTable);
        }
        Ok(img[b..e].chunks_exact(4).map(|c| u32::from_le_bytes(c.try_into().unwrap())).collect())
    }

    /// file offset of code (header is 0x80 bytes)
    pub fn code_offset(&self) -> usize {
        HEADER_SIZE
    }
}

/// `mwOverlayInit` on a byte image: returns the image extended by the zeroed bss and the constructor list.
// JP: 0x00384c60 mwOverlayInit
pub fn mw_overlay_init(img: &[u8]) -> Result<(Vec<u8>, Vec<u32>), OverlayError> {
    let h = OverlayHeader::parse(img)?;
    let mut mem = img.to_vec();
    mem.resize(img.len() + h.bss_size as usize, 0);
    let ctors = h.ctors(img)?;
    Ok((mem, ctors))
}

/// vtable callback `void (*)(int phase, bool ok, int a0, void* a1)`
pub type OverlayCb = Box<dyn FnMut(i32, bool) + Send>;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PreState {
    None = 0,
    Loading = 1,
    Done = 2,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LoadResult {
    /// 0: read queued, `cbOverlayLoad` fires when the DVD read completes
    Pending = 0,
    /// 2: a buffer is already set — overlay resident
    AlreadyLoaded = 2,
    /// 3: pre-load had finished — copied from the pre-buffer and initialised immediately
    FromPreload = 3,
}

/// `Overlay` object.
pub struct Overlay {
    pub group: i32,
    pub addr: u32,
    cb: Option<OverlayCb>,
    pub buf: BufMemory,
    pub loaded_size: i32,
    pub pre_buf: Option<BufMemory>,
    pub pre_state: PreState,
    pub pre_size: i32,
    pub load_pending: bool,
    /// set by `Load` when it needs the host to read `path` into the overlay region
    pub requested_path: Option<String>,
    pub initialised: Vec<u32>,
}

impl Overlay {
    // JP: 0x0023d1e0 __ct__7OverlayFv
    pub fn new() -> Self {
        Overlay {
            group: -1,
            addr: 0,
            cb: None,
            buf: BufMemory::empty(),
            loaded_size: 0,
            pre_buf: None,
            pre_state: PreState::None,
            pre_size: 0,
            load_pending: false,
            requested_path: None,
            initialised: vec![],
        }
    }

    // JP: 0x0023d3d0 Init__7OverlayFUi   `addr = mwGetGroupAddress(group)`
    pub fn init(&mut self, group: i32, group_addr: u32) -> bool {
        self.group = group;
        self.addr = group_addr;
        self.group != 0
    }

    /// `Load(path, cb)`; JP: 0x0023d460 Load__7OverlayFPCcPFibiPv_viPv
    pub fn load(&mut self, path: &str, cb: Option<OverlayCb>, img_size_hint: usize) -> LoadResult {
        if self.buf.is_set() {
            return LoadResult::AlreadyLoaded;
        }
        self.loaded_size = 0;
        self.cb = cb;
        self.buf.set_buffer(img_size_hint);
        match self.pre_state {
            PreState::Done => {
                // CopyFromPrebuffer + cbOverlayLoad(size = preSize)
                let sz = self.pre_size;
                self.copy_from_prebuffer();
                self.init_cashe(sz);
                LoadResult::FromPreload
            }
            PreState::Loading => {
                self.load_pending = true;
                LoadResult::Pending
            }
            PreState::None => {
                self.requested_path = Some(path.to_string());
                LoadResult::Pending
            }
        }
    }

    /// JP: 0x0023d5c0 PreLoad__7OverlayFP9BufMemoryPCcPFibiPv_viPv — read the overlay into a scratch buffer early.
    pub fn pre_load(&mut self, scratch: BufMemory, path: &str, cb: Option<OverlayCb>) {
        self.pre_state = PreState::Loading;
        self.pre_buf = Some(scratch);
        self.loaded_size = 0;
        self.cb = cb;
        self.requested_path = Some(path.to_string());
    }

    /// `cbOverlayPreLoad` -> JP: 0x0023d2f0 PreloadDone__7OverlayFP9BufMemoryi
    pub fn preload_done(&mut self, size: i32) {
        self.pre_state = PreState::Done;
        self.pre_size = size;
        if self.load_pending {
            self.copy_from_prebuffer();
            self.init_cashe(size);
        }
    }

    // JP: 0x0023d370 CopyFromPrebuffer__7OverlayFv  (memcpy to the load address, FlushCache(0))
    fn copy_from_prebuffer(&mut self) {
        if let Some(p) = self.pre_buf.as_ref() {
            let n = (self.pre_size as usize).min(p.get_buffer().len());
            let data = p.get_buffer()[..n].to_vec();
            self.buf = BufMemory::from_vec(data, 0);
        }
    }

    /// `cbOverlayLoad` -> JP: 0x0023d6d0 InitCashe__7OverlayFi:
    /// `loadedSize = size; mwOverlayInit(addr, size); cb(0, true, a0, a1); preBuf = 0; preState = 0; preSize = 0; pending = 0`
    pub fn init_cashe(&mut self, size: i32) {
        self.loaded_size = size;
        if let Ok((_mem, ctors)) = mw_overlay_init(self.buf.get_buffer()) {
            self.initialised = ctors;
        }
        if let Some(cb) = self.cb.as_mut() {
            cb(0, true);
        }
        self.pre_buf = None;
        self.pre_state = PreState::None;
        self.pre_size = 0;
        self.load_pending = false;
    }

    /// host completion for a normal `Load` read
    pub fn on_read_complete(&mut self, data: Vec<u8>) {
        let sz = data.len() as i32;
        self.buf = BufMemory::from_vec(data, 0);
        self.requested_path = None;
        self.init_cashe(sz);
    }

    // JP: 0x0023d660 Unload__7OverlayFPFibiPv_v — drop the buffer and tell the owner (phase 1)
    pub fn unload(&mut self, cb: Option<&mut OverlayCb>) -> bool {
        self.buf = BufMemory::empty();
        if let Some(c) = cb {
            c(1, true);
        }
        true
    }
}

impl Default for Overlay {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn fake_image() -> Vec<u8> {
        let mut v = vec![0u8; 0x100];
        v[..4].copy_from_slice(b"MWo3");
        v[4..8].copy_from_slice(&2u32.to_le_bytes());
        v[8..12].copy_from_slice(&LOAD_ADDR_JP.to_le_bytes());
        v[0x14..0x18].copy_from_slice(&0x40u32.to_le_bytes());
        v[0x18..0x1c].copy_from_slice(&(LOAD_ADDR_JP + 0xf0).to_le_bytes());
        v[0x1c..0x20].copy_from_slice(&(LOAD_ADDR_JP + 0xf8).to_le_bytes());
        v[0x20..0x2a].copy_from_slice(b"BATTLE.BIN");
        v[0xf0..0xf4].copy_from_slice(&0x0043_1000u32.to_le_bytes());
        v[0xf4..0xf8].copy_from_slice(&0x0043_2000u32.to_le_bytes());
        v
    }

    #[test]
    fn header_and_ctors() {
        let img = fake_image();
        let h = OverlayHeader::parse(&img).unwrap();
        assert_eq!(h.id, 2);
        assert_eq!(h.name, "BATTLE.BIN");
        assert_eq!(h.ctors(&img).unwrap(), vec![0x0043_1000, 0x0043_2000]);
        let (mem, c) = mw_overlay_init(&img).unwrap();
        assert_eq!(mem.len(), 0x140);
        assert_eq!(c.len(), 2);
        assert!(OverlayHeader::parse(&img[..16]).is_err());
    }

    #[test]
    fn load_callback() {
        let mut o = Overlay::new();
        o.init(2, LOAD_ADDR_JP);
        let flag = std::sync::Arc::new(std::sync::atomic::AtomicBool::new(false));
        let f2 = flag.clone();
        assert_eq!(o.load("BATTLE.BIN", Some(Box::new(move |ph, ok| f2.store(ph == 0 && ok, std::sync::atomic::Ordering::SeqCst))), 0), LoadResult::Pending);
        assert_eq!(o.requested_path.as_deref(), Some("BATTLE.BIN"));
        o.on_read_complete(fake_image());
        assert!(flag.load(std::sync::atomic::Ordering::SeqCst));
        assert_eq!(o.initialised.len(), 2);
    }
}
