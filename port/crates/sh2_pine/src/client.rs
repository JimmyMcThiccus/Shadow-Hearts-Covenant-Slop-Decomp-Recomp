//! Minimal PINE client (PCSX2 IPC) over the Unix socket `$TMPDIR/pcsx2.sock.<slot>` (default slot 28011; the "armsx2" build used here
//! listens on 28013 — pass `SH2_PINE_SLOT` or let [`Pine::connect_auto`] scan the directory).
//!
//! Wire format (little endian): request `u32 total_len | { u8 opcode | args }...`, reply `u32 total_len | u8 status (0 ok, 0xFF fail) | data`.
//! Read/write opcodes 0..7 (8/16/32/64 bit), 8 version, 9 save state, 0xA load state, 0xB title, 0xC id, 0xD uuid, 0xE game version, 0xF status.
//!
//! PCSX2 drops replies when more than ~7 requests are in flight, so this client is strictly serial: one request, wait for its reply.

use std::io::{Read, Write};
#[cfg(unix)]
use std::os::unix::net::UnixStream;
use std::path::PathBuf;
use std::time::Duration;

#[derive(Debug, thiserror::Error)]
pub enum PineError {
    #[error("io: {0}")]
    Io(#[from] std::io::Error),
    #[error("PINE returned FAIL for the request (unmapped address?)")]
    Fail,
    #[error("malformed reply: {0}")]
    Protocol(&'static str),
    #[error("no pcsx2.sock.<slot> found in {0}")]
    NoSocket(String),
}

pub type Result<T> = std::result::Result<T, PineError>;

pub const OP_READ8: u8 = 0;
pub const OP_READ16: u8 = 1;
pub const OP_READ32: u8 = 2;
pub const OP_READ64: u8 = 3;
pub const OP_WRITE8: u8 = 4;
pub const OP_WRITE16: u8 = 5;
pub const OP_WRITE32: u8 = 6;
pub const OP_WRITE64: u8 = 7;
pub const OP_VERSION: u8 = 8;
pub const OP_SAVE_STATE: u8 = 9;
pub const OP_LOAD_STATE: u8 = 0xA;
pub const OP_TITLE: u8 = 0xB;
pub const OP_ID: u8 = 0xC;
pub const OP_UUID: u8 = 0xD;
pub const OP_GAME_VERSION: u8 = 0xE;
pub const OP_STATUS: u8 = 0xF;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum EmuStatus {
    Running,
    Paused,
    Shutdown,
    Unknown(u32),
}

/// Anything that can read emulated EE memory.  The typed readers in [`crate::game`] are generic over this so they can be unit-tested on
/// a plain byte image.
pub trait Mem {
    fn r8(&mut self, addr: u32) -> Result<u8>;
    fn r16(&mut self, addr: u32) -> Result<u16>;
    fn r32(&mut self, addr: u32) -> Result<u32>;
    fn r64(&mut self, addr: u32) -> Result<u64>;
    fn read_bytes(&mut self, addr: u32, len: usize) -> Result<Vec<u8>> {
        // largest aligned access at each step
        let mut out = Vec::with_capacity(len);
        let mut a = addr;
        let end = addr as u64 + len as u64;
        while (a as u64) < end {
            let left = end - a as u64;
            if a % 8 == 0 && left >= 8 {
                out.extend_from_slice(&self.r64(a)?.to_le_bytes());
                a += 8;
            } else if a % 4 == 0 && left >= 4 {
                out.extend_from_slice(&self.r32(a)?.to_le_bytes());
                a += 4;
            } else if a % 2 == 0 && left >= 2 {
                out.extend_from_slice(&self.r16(a)?.to_le_bytes());
                a += 2;
            } else {
                out.push(self.r8(a)?);
                a += 1;
            }
        }
        Ok(out)
    }
    fn f32(&mut self, addr: u32) -> Result<f32> {
        Ok(f32::from_bits(self.r32(addr)?))
    }
    fn vec4(&mut self, addr: u32) -> Result<[f32; 4]> {
        let b = self.read_bytes(addr, 16)?;
        let mut v = [0.0f32; 4];
        for (i, c) in b.chunks_exact(4).enumerate() {
            v[i] = f32::from_le_bytes([c[0], c[1], c[2], c[3]]);
        }
        Ok(v)
    }
    fn cstr(&mut self, addr: u32, max: usize) -> Result<String> {
        let b = self.read_bytes(addr, max)?;
        let n = b.iter().position(|&c| c == 0).unwrap_or(b.len());
        Ok(String::from_utf8_lossy(&b[..n]).into_owned())
    }
}

#[cfg(unix)]
type Stream = UnixStream;
/// On Windows PCSX2 serves PINE over TCP `127.0.0.1:<slot>` (default 28011) instead of a Unix socket.
#[cfg(not(unix))]
type Stream = std::net::TcpStream;

pub struct Pine {
    s: Stream,
}

impl Pine {
    #[cfg(not(unix))]
    pub fn connect_slot(slot: u16) -> Result<Self> {
        let s = std::net::TcpStream::connect(("127.0.0.1", slot))?;
        s.set_read_timeout(Some(Duration::from_secs(10)))?;
        s.set_write_timeout(Some(Duration::from_secs(10)))?;
        s.set_nodelay(true)?;
        Ok(Self { s })
    }

    #[cfg(not(unix))]
    pub fn connect_path(_p: PathBuf) -> Result<Self> {
        Err(PineError::Protocol("unix sockets are not available on this platform; use connect_slot (TCP)"))
    }

    #[cfg(unix)]
    pub fn connect_slot(slot: u16) -> Result<Self> {
        let dir = std::env::var("XDG_RUNTIME_DIR").ok().filter(|d| !d.is_empty()).or_else(|| std::env::var("TMPDIR").ok()).unwrap_or_else(|| "/tmp".into());
        Self::connect_path(PathBuf::from(dir).join(format!("pcsx2.sock.{slot}")))
    }

    #[cfg(unix)]
    pub fn connect_path(p: PathBuf) -> Result<Self> {
        let s = UnixStream::connect(p)?;
        s.set_read_timeout(Some(Duration::from_secs(10)))?;
        s.set_write_timeout(Some(Duration::from_secs(10)))?;
        Ok(Self { s })
    }

    /// `SH2_PINE_SLOT` if set, else the first `pcsx2.sock.*` in `$XDG_RUNTIME_DIR` / `$TMPDIR` that answers a version request.
    #[cfg(not(unix))]
    pub fn connect_auto() -> Result<Self> {
        let slot = std::env::var("SH2_PINE_SLOT").ok().and_then(|v| v.parse::<u16>().ok()).unwrap_or(28011);
        Self::connect_slot(slot)
    }

    #[cfg(unix)]
    pub fn connect_auto() -> Result<Self> {
        if let Ok(v) = std::env::var("SH2_PINE_SLOT") {
            if let Ok(slot) = v.parse::<u16>() {
                return Self::connect_slot(slot);
            }
        }
        let dir = std::env::var("XDG_RUNTIME_DIR").ok().filter(|d| !d.is_empty()).or_else(|| std::env::var("TMPDIR").ok()).unwrap_or_else(|| "/tmp".into());
        let mut socks: Vec<PathBuf> = std::fs::read_dir(&dir)?
            .flatten()
            .map(|e| e.path())
            .filter(|p| p.file_name().and_then(|n| n.to_str()).is_some_and(|n| n.starts_with("pcsx2.sock.")))
            .collect();
        socks.sort();
        for p in socks {
            if let Ok(mut c) = Self::connect_path(p) {
                if c.version().is_ok() {
                    return Ok(c);
                }
            }
        }
        Err(PineError::NoSocket(dir))
    }

    fn request(&mut self, op: u8, args: &[u8]) -> Result<Vec<u8>> {
        let total = 4 + 1 + args.len();
        let mut pkt = Vec::with_capacity(total);
        pkt.extend_from_slice(&(total as u32).to_le_bytes());
        pkt.push(op);
        pkt.extend_from_slice(args);
        self.s.write_all(&pkt)?;
        let mut len = [0u8; 4];
        self.s.read_exact(&mut len)?;
        let n = u32::from_le_bytes(len) as usize;
        if !(5..=1 << 20).contains(&n) {
            return Err(PineError::Protocol("bad reply length"));
        }
        let mut body = vec![0u8; n - 4];
        self.s.read_exact(&mut body)?;
        if body[0] == 0xFF {
            return Err(PineError::Fail);
        }
        body.remove(0);
        Ok(body)
    }

    fn string_op(&mut self, op: u8) -> Result<String> {
        let b = self.request(op, &[])?;
        if b.len() < 4 {
            return Err(PineError::Protocol("short string reply"));
        }
        let n = u32::from_le_bytes([b[0], b[1], b[2], b[3]]) as usize;
        let s = &b[4..(4 + n).min(b.len())];
        Ok(String::from_utf8_lossy(s).trim_end_matches('\0').to_string())
    }

    pub fn version(&mut self) -> Result<String> {
        self.string_op(OP_VERSION)
    }
    pub fn title(&mut self) -> Result<String> {
        self.string_op(OP_TITLE)
    }
    /// game serial, e.g. `SLUS-21041`
    pub fn game_id(&mut self) -> Result<String> {
        self.string_op(OP_ID)
    }
    pub fn uuid(&mut self) -> Result<String> {
        self.string_op(OP_UUID)
    }
    pub fn game_version(&mut self) -> Result<String> {
        self.string_op(OP_GAME_VERSION)
    }
    pub fn status(&mut self) -> Result<EmuStatus> {
        let b = self.request(OP_STATUS, &[])?;
        if b.len() < 4 {
            return Err(PineError::Protocol("short status"));
        }
        Ok(match u32::from_le_bytes([b[0], b[1], b[2], b[3]]) {
            0 => EmuStatus::Running,
            1 => EmuStatus::Paused,
            2 => EmuStatus::Shutdown,
            n => EmuStatus::Unknown(n),
        })
    }

    /// Save a state into slot `slot` (side effect on the emulator; only call when the user asked for it).
    pub fn save_state(&mut self, slot: u8) -> Result<()> {
        self.request(OP_SAVE_STATE, &[slot]).map(|_| ())
    }
    /// Load the state in slot `slot` (replaces the running game state!).
    pub fn load_state(&mut self, slot: u8) -> Result<()> {
        self.request(OP_LOAD_STATE, &[slot]).map(|_| ())
    }

    pub fn w8(&mut self, addr: u32, v: u8) -> Result<()> {
        let mut a = addr.to_le_bytes().to_vec();
        a.push(v);
        self.request(OP_WRITE8, &a).map(|_| ())
    }
    pub fn w16(&mut self, addr: u32, v: u16) -> Result<()> {
        let mut a = addr.to_le_bytes().to_vec();
        a.extend_from_slice(&v.to_le_bytes());
        self.request(OP_WRITE16, &a).map(|_| ())
    }
    pub fn w32(&mut self, addr: u32, v: u32) -> Result<()> {
        let mut a = addr.to_le_bytes().to_vec();
        a.extend_from_slice(&v.to_le_bytes());
        self.request(OP_WRITE32, &a).map(|_| ())
    }
    pub fn w64(&mut self, addr: u32, v: u64) -> Result<()> {
        let mut a = addr.to_le_bytes().to_vec();
        a.extend_from_slice(&v.to_le_bytes());
        self.request(OP_WRITE64, &a).map(|_| ())
    }

    fn rd(&mut self, op: u8, addr: u32, n: usize) -> Result<Vec<u8>> {
        let b = self.request(op, &addr.to_le_bytes())?;
        if b.len() < n {
            return Err(PineError::Protocol("short read reply"));
        }
        Ok(b)
    }
}

impl Mem for Pine {
    fn r8(&mut self, addr: u32) -> Result<u8> {
        Ok(self.rd(OP_READ8, addr, 1)?[0])
    }
    fn r16(&mut self, addr: u32) -> Result<u16> {
        let b = self.rd(OP_READ16, addr, 2)?;
        Ok(u16::from_le_bytes([b[0], b[1]]))
    }
    fn r32(&mut self, addr: u32) -> Result<u32> {
        let b = self.rd(OP_READ32, addr, 4)?;
        Ok(u32::from_le_bytes([b[0], b[1], b[2], b[3]]))
    }
    fn r64(&mut self, addr: u32) -> Result<u64> {
        let b = self.rd(OP_READ64, addr, 8)?;
        Ok(u64::from_le_bytes([b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]]))
    }
}

/// A plain byte image at a base address (tests, offline dumps).
pub struct Image {
    pub base: u32,
    pub data: Vec<u8>,
}

impl Image {
    fn slice(&self, addr: u32, n: usize) -> Result<&[u8]> {
        let o = addr.checked_sub(self.base).ok_or(PineError::Fail)? as usize;
        self.data.get(o..o + n).ok_or(PineError::Fail)
    }
}

impl Mem for Image {
    fn r8(&mut self, addr: u32) -> Result<u8> {
        Ok(self.slice(addr, 1)?[0])
    }
    fn r16(&mut self, addr: u32) -> Result<u16> {
        let b = self.slice(addr, 2)?;
        Ok(u16::from_le_bytes([b[0], b[1]]))
    }
    fn r32(&mut self, addr: u32) -> Result<u32> {
        let b = self.slice(addr, 4)?;
        Ok(u32::from_le_bytes([b[0], b[1], b[2], b[3]]))
    }
    fn r64(&mut self, addr: u32) -> Result<u64> {
        let b = self.slice(addr, 8)?;
        Ok(u64::from_le_bytes([b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]]))
    }
}

/// Sparse memory image built from text dumps in the format the MCP `pine_read_range` tool prints
/// (`0x006C3D40 [64 bytes]:` followed by space separated hex bytes) or `pine_read32/64` one-liners (`0x0040AD94: 7093568 (0x6C3D40)` —
/// those are ignored).  Lets the typed readers decode dumps captured through another PINE client.
#[derive(Default)]
pub struct Sparse {
    pub chunks: std::collections::BTreeMap<u32, Vec<u8>>,
}

impl Sparse {
    pub fn parse(text: &str) -> Self {
        let mut s = Sparse::default();
        let mut cur: Option<(u32, Vec<u8>)> = None;
        for line in text.lines() {
            let t = line.trim();
            if let Some(rest) = t.strip_prefix("0x") {
                if let Some(idx) = rest.find(" [") {
                    if let Some(c) = cur.take() {
                        s.chunks.insert(c.0, c.1);
                    }
                    if let Ok(a) = u32::from_str_radix(&rest[..idx], 16) {
                        cur = Some((a, Vec::new()));
                    }
                    continue;
                }
            }
            if let Some((_, v)) = cur.as_mut() {
                for tok in t.split_whitespace() {
                    if tok.len() == 2 {
                        if let Ok(b) = u8::from_str_radix(tok, 16) {
                            v.push(b);
                        }
                    }
                }
            }
        }
        if let Some(c) = cur.take() {
            s.chunks.insert(c.0, c.1);
        }
        s
    }

    pub fn put(&mut self, addr: u32, data: Vec<u8>) {
        self.chunks.insert(addr, data);
    }

    fn get(&self, addr: u32, n: usize) -> Result<Vec<u8>> {
        for (&base, d) in self.chunks.range(..=addr).rev().take(1) {
            let o = (addr - base) as usize;
            if o + n <= d.len() {
                return Ok(d[o..o + n].to_vec());
            }
        }
        Err(PineError::Fail)
    }
}

impl Mem for Sparse {
    fn r8(&mut self, addr: u32) -> Result<u8> {
        Ok(self.get(addr, 1)?[0])
    }
    fn r16(&mut self, addr: u32) -> Result<u16> {
        let b = self.get(addr, 2)?;
        Ok(u16::from_le_bytes([b[0], b[1]]))
    }
    fn r32(&mut self, addr: u32) -> Result<u32> {
        let b = self.get(addr, 4)?;
        Ok(u32::from_le_bytes([b[0], b[1], b[2], b[3]]))
    }
    fn r64(&mut self, addr: u32) -> Result<u64> {
        let b = self.get(addr, 8)?;
        Ok(u64::from_le_bytes(b.try_into().unwrap()))
    }
}

#[cfg(all(test, unix))]
mod tests {
    use super::*;
    use std::os::unix::net::UnixListener;

    /// A mock PCSX2 PINE server: serves reads from a byte image, handles version/status, and replies FAIL for out-of-range reads.
    fn serve(listener: UnixListener, ram: Vec<u8>, base: u32) {
        let (mut s, _) = listener.accept().unwrap();
        loop {
            let mut len = [0u8; 4];
            if s.read_exact(&mut len).is_err() {
                return;
            }
            let n = u32::from_le_bytes(len) as usize;
            let mut body = vec![0u8; n - 4];
            s.read_exact(&mut body).unwrap();
            let op = body[0];
            let mut reply = vec![0u8; 5];
            let rd = |addr: u32, k: usize| -> Option<&[u8]> { ram.get(addr.checked_sub(base)? as usize..)?.get(..k) };
            match op {
                OP_READ8 | OP_READ16 | OP_READ32 | OP_READ64 => {
                    let k = 1usize << op;
                    let addr = u32::from_le_bytes(body[1..5].try_into().unwrap());
                    match rd(addr, k) {
                        Some(d) => reply.extend_from_slice(d),
                        None => reply[4] = 0xFF,
                    }
                }
                OP_VERSION => {
                    let v = b"PCSX2 mock\0";
                    reply.extend_from_slice(&(v.len() as u32).to_le_bytes());
                    reply.extend_from_slice(v);
                }
                OP_STATUS => reply.extend_from_slice(&0u32.to_le_bytes()),
                _ => reply[4] = 0xFF,
            }
            let total = (reply.len() - 0) as u32;
            reply[..4].copy_from_slice(&total.to_le_bytes());
            s.write_all(&reply).unwrap();
        }
    }

    #[test]
    fn client_against_mock_server() {
        let dir = std::env::temp_dir().join(format!("sh2_pine_test_{}", std::process::id()));
        std::fs::create_dir_all(&dir).unwrap();
        let path = dir.join("pcsx2.sock.1");
        let _ = std::fs::remove_file(&path);
        let l = UnixListener::bind(&path).unwrap();
        let ram: Vec<u8> = (0..=255u8).cycle().take(0x1000).collect();
        let base = 0x0040_0000;
        let ram2 = ram.clone();
        let h = std::thread::spawn(move || serve(l, ram2, base));
        let mut p = Pine::connect_path(path.clone()).unwrap();
        assert_eq!(p.version().unwrap(), "PCSX2 mock");
        assert_eq!(p.status().unwrap(), EmuStatus::Running);
        assert_eq!(p.r8(base + 5).unwrap(), 5);
        assert_eq!(p.r16(base + 2).unwrap(), 0x0302);
        assert_eq!(p.r32(base + 4).unwrap(), 0x07060504);
        assert_eq!(p.r64(base + 8).unwrap(), 0x0f0e0d0c0b0a0908);
        // unaligned range read assembled from mixed widths
        assert_eq!(p.read_bytes(base + 3, 13).unwrap(), ram[3..16].to_vec());
        assert!(matches!(p.r32(0x1000), Err(PineError::Fail)));
        drop(p);
        h.join().unwrap();
        let _ = std::fs::remove_dir_all(&dir);
    }

    #[test]
    fn parse_mcp_dump() {
        let t = "0x006C3D40 [8 bytes]:\n08 33 68 00 50 AD 6E 00\n0x0040AD94: 7093568 (0x6C3D40)\n0x00100000 [4 bytes]:\n01 02 03 04";
        let mut s = Sparse::parse(t);
        assert_eq!(s.r32(0x6C3D40).unwrap(), 0x00683308);
        assert_eq!(s.r32(0x6C3D44).unwrap(), 0x006EAD50);
        assert_eq!(s.r8(0x100003).unwrap(), 4);
        assert!(s.r8(0x100004).is_err());
    }
}
