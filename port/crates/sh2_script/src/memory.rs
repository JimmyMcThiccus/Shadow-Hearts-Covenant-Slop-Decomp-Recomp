//! Segmented virtual memory used by the script VMs.
//!
//! The PS2 VM works with raw EE pointers: the stack holds addresses of registers, data-segment
//! items, strings and locals.  To keep scripts bit-identical we model the same address space with
//! a 4-bit segment tag in the top nibble of a `u32` "pointer".

pub const SEG_SHIFT: u32 = 28;
pub const SEG_CONST: u32 = 0x0000_0000; // address 0 = "" (empty NUL string)
pub const SEG_CODE: u32 = 0x1000_0000;
pub const SEG_DATA: u32 = 0x2000_0000;
pub const SEG_BSS: u32 = 0x3000_0000;
pub const SEG_REGS: u32 = 0x4000_0000; // "flag"/register file (CScript+0x40 table)
pub const SEG_STACK: u32 = 0x5000_0000;
pub const SEG_HOST: u32 = 0x6000_0000; // scratch owned by the embedding game (strings returned to scripts, etc.)

#[derive(Debug, Default, Clone)]
pub struct Memory {
    pub code: Vec<u8>,
    pub data: Vec<u8>,
    pub bss: Vec<u8>,
    pub regs: Vec<u8>,
    pub stack: Vec<u8>,
    pub host: Vec<u8>,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct BadAddr(pub u32);

impl Memory {
    fn seg(&self, addr: u32) -> Option<(&[u8], usize)> {
        let off = (addr & 0x0fff_ffff) as usize;
        let s: &[u8] = match addr & 0xf000_0000 {
            SEG_CONST => &[0u8; 1][..],
            SEG_CODE => &self.code,
            SEG_DATA => &self.data,
            SEG_BSS => &self.bss,
            SEG_REGS => &self.regs,
            SEG_STACK => &self.stack,
            SEG_HOST => &self.host,
            _ => return None,
        };
        Some((s, off))
    }
    fn seg_mut(&mut self, addr: u32) -> Option<(&mut [u8], usize)> {
        let off = (addr & 0x0fff_ffff) as usize;
        let s: &mut [u8] = match addr & 0xf000_0000 {
            SEG_CODE => &mut self.code,
            SEG_DATA => &mut self.data,
            SEG_BSS => &mut self.bss,
            SEG_REGS => &mut self.regs,
            SEG_STACK => &mut self.stack,
            SEG_HOST => &mut self.host,
            _ => return None,
        };
        Some((s, off))
    }
    pub fn read(&self, addr: u32, out: &mut [u8]) -> Result<(), BadAddr> {
        let (s, off) = self.seg(addr).ok_or(BadAddr(addr))?;
        let end = off.checked_add(out.len()).ok_or(BadAddr(addr))?;
        if end > s.len() {
            return Err(BadAddr(addr));
        }
        out.copy_from_slice(&s[off..end]);
        Ok(())
    }
    pub fn write(&mut self, addr: u32, src: &[u8]) -> Result<(), BadAddr> {
        let (s, off) = self.seg_mut(addr).ok_or(BadAddr(addr))?;
        let end = off.checked_add(src.len()).ok_or(BadAddr(addr))?;
        if end > s.len() {
            return Err(BadAddr(addr));
        }
        s[off..end].copy_from_slice(src);
        Ok(())
    }
    pub fn r8(&self, a: u32) -> Result<u8, BadAddr> {
        let mut b = [0u8; 1];
        self.read(a, &mut b)?;
        Ok(b[0])
    }
    pub fn r16(&self, a: u32) -> Result<u16, BadAddr> {
        let mut b = [0u8; 2];
        self.read(a, &mut b)?;
        Ok(u16::from_le_bytes(b))
    }
    pub fn r32(&self, a: u32) -> Result<u32, BadAddr> {
        let mut b = [0u8; 4];
        self.read(a, &mut b)?;
        Ok(u32::from_le_bytes(b))
    }
    pub fn w8(&mut self, a: u32, v: u8) -> Result<(), BadAddr> {
        self.write(a, &[v])
    }
    pub fn w16(&mut self, a: u32, v: u16) -> Result<(), BadAddr> {
        self.write(a, &v.to_le_bytes())
    }
    pub fn w32(&mut self, a: u32, v: u32) -> Result<(), BadAddr> {
        self.write(a, &v.to_le_bytes())
    }
    /// Read a NUL-terminated string (Shift-JIS bytes are returned as-is, lossy UTF-8 for ASCII names).
    pub fn cstr(&self, a: u32) -> Result<String, BadAddr> {
        let mut v = Vec::new();
        let mut p = a;
        loop {
            let c = self.r8(p)?;
            if c == 0 {
                break;
            }
            v.push(c);
            p += 1;
            if v.len() > 4096 {
                return Err(BadAddr(a));
            }
        }
        Ok(String::from_utf8_lossy(&v).into_owned())
    }
    /// Raw bytes of the NUL-terminated string at `a` (Shift-JIS text must not go through UTF-8).
    pub fn cstr_bytes(&self, a: u32) -> Result<Vec<u8>, BadAddr> {
        let mut v = Vec::new();
        let mut p = a;
        loop {
            let c = self.r8(p)?;
            if c == 0 {
                break;
            }
            v.push(c);
            p += 1;
            if v.len() > 4096 {
                return Err(BadAddr(a));
            }
        }
        Ok(v)
    }
    /// Allocate a NUL-terminated string in host scratch and return its pointer.
    pub fn host_str(&mut self, s: &str) -> u32 {
        let p = SEG_HOST + self.host.len() as u32;
        self.host.extend_from_slice(s.as_bytes());
        self.host.push(0);
        p
    }
}
