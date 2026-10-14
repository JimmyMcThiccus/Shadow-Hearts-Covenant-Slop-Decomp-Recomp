//! Dbg — on-screen debug text console (JP `dbwin.cpp`, 0x003e16e0..0x003e2064; statics `m_stream` 0x004301a0 (0x400), `m_raster/m_palette`).
//!
//! `DBSTREAM` (as used by `PutStr`/`ScrollUp`): `+0 u16* cells, +8 ?, +0xa u8 cols, +0xb u8 rows, +0xc u8 cursor_x, +0xd u8 cursor_y,
//! +0xe u8 colour`.  Each cell is `u16 = (colour << 8) + (ch - 0x20)`; non-printable characters print as `?` (0x3f).
//! `Dbg::Printf(stream_id, fmt, ...)`: stream 0 (screen) or 1 (second, colour 0x3f) then sets `m_flags |= 4` (dirty).
//! `Dbg::m_dbgLev` (0x0040ae38) / `m_flags` (0x0040ae3c).
pub struct DbStream {
    pub cells: Vec<u16>,
    pub cols: u8,
    pub rows: u8,
    pub x: u8,
    pub y: u8,
    pub colour: u8,
}

impl DbStream {
    pub fn new(cols: u8, rows: u8, colour: u8) -> Self {
        DbStream { cells: vec![0; cols as usize * rows as usize], cols, rows, x: 0, y: 0, colour }
    }

    // JP: 0x003e18e0 ScrollUp__3DbgFP8DBSTREAM
    pub fn scroll_up(&mut self) {
        let c = self.cols as usize;
        let n = c * (self.rows as usize - 1);
        if self.rows > 1 {
            self.cells.copy_within(c..c + n, 0);
        }
        for v in &mut self.cells[n..n + c] {
            *v = 0;
        }
    }

    // JP: 0x003e1790 PutStr__3DbgFP8DBSTREAMRPc
    pub fn put_str(&mut self, s: &str) {
        for &b in s.as_bytes() {
            if b == 0 {
                break;
            }
            let idx = self.x as usize + self.y as usize * self.cols as usize;
            // original advances the cursor *before* storing, wrapping/scrolling first
            let prev_x = self.x;
            self.x = self.x.wrapping_add(1);
            let mut wrapped = false;
            if self.cols <= prev_x {
                self.x = 0;
                self.y += 1;
                wrapped = true;
            }
            let mut scrolled = false;
            if self.rows <= self.y {
                self.scroll_up();
                self.y = self.rows - 1;
                scrolled = true;
            }
            let idx = if wrapped || scrolled { self.x as usize + self.y as usize * self.cols as usize } else { idx };
            let ch = if (0x20..=0x7e).contains(&b) { b as u16 } else { 0x3f };
            if idx < self.cells.len() {
                self.cells[idx] = ch + ((self.colour as u16) << 8) - 0x20;
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn put_and_scroll() {
        let mut s = DbStream::new(4, 2, 1);
        s.put_str("ABCDE");
        // 'E' wrapped to the second row
        assert_eq!(s.cells[4], 0x100 + (b'E' as u16 - 0x20));
        s.put_str("FGHIJ");
        assert_eq!(s.y, 1);
    }
}
