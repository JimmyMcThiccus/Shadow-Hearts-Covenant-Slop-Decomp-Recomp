//! Reader for the static tables inside a JP `FIELD.BIN` overlay image (shop / Solomon / tailor / world-map message tables,
//! navi-map textures, layer programs, ...). Symbols: [`crate::overlay_data_syms::DATA_SYMS`].
//!
//! The overlay is an `MWo3` image: a 0x80-byte header followed by code+data loaded at `load_addr` (0x00430a00 in the JP demo);
//! pointers inside tables are absolute virtual addresses.

pub use crate::overlay_data_syms::{DataKind, DataSym, DATA_SYMS};

pub const JP_LOAD_ADDR: u32 = 0x0043_0a00;

pub struct OverlayImage {
    data: Vec<u8>,
    pub load_addr: u32,
}

impl OverlayImage {
    /// `bytes` = whole `FIELD.BIN` file; `load_addr` from the MWo3 header (+8).
    pub fn new(bytes: Vec<u8>) -> Result<Self, &'static str> {
        if bytes.len() < 0x80 || &bytes[0..4] != b"MWo3" {
            return Err("not an MWo3 overlay");
        }
        let load_addr = u32::from_le_bytes(bytes[8..12].try_into().unwrap());
        Ok(Self { data: bytes, load_addr })
    }

    pub fn contains(&self, va: u32) -> bool {
        va >= self.load_addr && ((va - self.load_addr) as usize) < self.data.len()
    }

    pub fn bytes_at(&self, va: u32, len: usize) -> Option<&[u8]> {
        if va < self.load_addr {
            return None;
        }
        let o = (va - self.load_addr) as usize;
        self.data.get(o..o + len)
    }

    pub fn u32_at(&self, va: u32) -> Option<u32> {
        self.bytes_at(va, 4).map(|b| u32::from_le_bytes(b.try_into().unwrap()))
    }

    /// NUL-terminated byte string (Shift-JIS) at `va`.
    pub fn cstr_at(&self, va: u32) -> Option<&[u8]> {
        if va < self.load_addr {
            return None;
        }
        let o = (va - self.load_addr) as usize;
        let s = self.data.get(o..)?;
        let n = s.iter().position(|&b| b == 0)?;
        Some(&s[..n])
    }

    pub fn sym(name: &str) -> Option<&'static DataSym> {
        DATA_SYMS.iter().find(|s| s.name == name)
    }

    /// Strings of a `StrPtrs` table such as `shopMess_mainMenu_J`.
    pub fn strings(&self, name: &str) -> Option<Vec<&[u8]>> {
        let s = Self::sym(name)?;
        if s.kind != DataKind::StrPtrs {
            return None;
        }
        (0..s.size / 4).map(|i| self.cstr_at(self.u32_at(s.addr + i * 4)?)).collect()
    }

    pub fn raw(&self, name: &str) -> Option<&[u8]> {
        let s = Self::sym(name)?;
        if s.kind == DataKind::Bss {
            return None;
        }
        self.bytes_at(s.addr, s.size as usize)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn real_overlay_tables_if_present() {
        let Some(dir) = std::env::var_os("SH2_DISC_DIR") else { return };
        let Ok(bytes) = sh2_core::fileio::read_disc_file(std::path::Path::new(&dir), "FIELD.BIN") else { return };
        let img = OverlayImage::new(bytes).unwrap();
        assert_eq!(img.load_addr, JP_LOAD_ADDR);
        let m = img.strings("shopMess_mainMenu_J").unwrap();
        assert_eq!(m.len(), 4);
        assert!(m.iter().all(|s| !s.is_empty()));
        let n = img.strings("shopMess_shopName_J").unwrap();
        assert_eq!(n.len(), 6);
        assert_eq!(img.raw("dirTbl").unwrap().len(), 16);
    }
}
