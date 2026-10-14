//! MPEG-2 video (ISO/IEC 13818-2, main profile, 4:2:0) elementary-stream decoder: I, P and B pictures, frame pictures with
//! frame / field motion and DCT, half-pel motion compensation.
//!
//! The game's movies (`MOVS` tracks of LSD files, `OPENING/DEMO.LSD`) are plain MPEG-2 elementary streams (TMPGEnc, 640x448, 29.97 fps,
//! I/P/B).  On the PS2 `sceMpeg` feeds them to the IPU (`FDEC`/`IDEC`/`BDEC`/`CSC`) and motion-compensates on the EE; this module does the
//! same job in software.  Decoding order -> display order is handled here (anchors are held back until the next anchor arrives).
//!
//! Not supported (returns [`Mpeg2Error::Unsupported`]): field pictures, dual-prime prediction, scalable extensions, 4:2:2 / 4:4:4.

use std::sync::{Arc, OnceLock};
use thiserror::Error;

#[derive(Debug, Error, Clone, PartialEq, Eq)]
pub enum Mpeg2Error {
    #[error("unsupported: {0}")]
    Unsupported(&'static str),
    #[error("invalid stream: {0}")]
    Invalid(&'static str),
    #[error("picture before any sequence header")]
    NoSequence,
}

/// One decoded picture (planar 4:2:0, `width`/`height` are the displayed size; planes are padded to whole macroblocks).
#[derive(Debug, Clone)]
pub struct Mpeg2Frame {
    pub width: usize,
    pub height: usize,
    /// luma stride = `mb_w * 16`
    pub stride: usize,
    pub y: Vec<u8>,
    pub cb: Vec<u8>,
    pub cr: Vec<u8>,
    pub temporal_reference: u16,
    /// 1 = I, 2 = P, 3 = B
    pub picture_type: u8,
    pub progressive: bool,
    pub top_field_first: bool,
    pub repeat_first_field: bool,
}

impl Mpeg2Frame {
    fn blank(width: usize, height: usize) -> Self {
        let mb_w = width.div_ceil(16);
        let mb_h = height.div_ceil(16);
        let stride = mb_w * 16;
        Mpeg2Frame {
            width,
            height,
            stride,
            y: vec![0; stride * mb_h * 16],
            cb: vec![128; stride / 2 * mb_h * 8],
            cr: vec![128; stride / 2 * mb_h * 8],
            temporal_reference: 0,
            picture_type: 0,
            progressive: true,
            top_field_first: false,
            repeat_first_field: false,
        }
    }

    /// BT.601 limited-range conversion (the IPU's CSC) to RGBA8, `width * height * 4` bytes.
    pub fn to_rgba(&self, out: &mut Vec<u8>) {
        out.clear();
        out.resize(self.width * self.height * 4, 255);
        let cs = self.stride / 2;
        for y in 0..self.height {
            for x in 0..self.width {
                let yy = self.y[y * self.stride + x] as i32 - 16;
                let cb = self.cb[(y / 2) * cs + x / 2] as i32 - 128;
                let cr = self.cr[(y / 2) * cs + x / 2] as i32 - 128;
                let c = |v: i32| ((v + 128) >> 8).clamp(0, 255) as u8;
                let o = (y * self.width + x) * 4;
                out[o] = c(298 * yy + 409 * cr);
                out[o + 1] = c(298 * yy - 100 * cb - 208 * cr);
                out[o + 2] = c(298 * yy + 516 * cb);
            }
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------
// bit reader
// ----------------------------------------------------------------------------------------------------------------------------------

struct Bits<'a> {
    d: &'a [u8],
    pos: usize,
}

impl<'a> Bits<'a> {
    fn new(d: &'a [u8], byte: usize) -> Self {
        Bits { d, pos: byte * 8 }
    }
    #[inline]
    fn peek(&self, n: u32) -> u32 {
        debug_assert!(n >= 1 && n <= 25);
        let byte = self.pos >> 3;
        let v = if byte + 8 <= self.d.len() {
            u64::from_be_bytes(self.d[byte..byte + 8].try_into().unwrap())
        } else {
            let mut b = [0u8; 8];
            for (i, s) in b.iter_mut().enumerate() {
                *s = self.d.get(byte + i).copied().unwrap_or(0);
            }
            u64::from_be_bytes(b)
        };
        ((v << (self.pos & 7)) >> (64 - n)) as u32
    }
    #[inline]
    fn skip(&mut self, n: u32) {
        self.pos += n as usize;
    }
    #[inline]
    fn read(&mut self, n: u32) -> u32 {
        if n == 0 {
            return 0;
        }
        let v = self.peek(n);
        self.pos += n as usize;
        v
    }
    #[inline]
    fn read1(&mut self) -> u32 {
        self.read(1)
    }
    fn eof(&self) -> bool {
        self.pos >= self.d.len() * 8
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------
// VLC tables
// ----------------------------------------------------------------------------------------------------------------------------------

/// Direct lookup table: `peek(bits)` -> `(value, length)`; length 0 = invalid code.
struct Vlc {
    bits: u32,
    tab: Vec<(i16, u8)>,
}

impl Vlc {
    /// `entries`: `(code, code length, value)`.
    fn new(entries: &[(u32, u8, i16)]) -> Vlc {
        let bits = entries.iter().map(|e| e.1 as u32).max().unwrap();
        let mut tab = vec![(0i16, 0u8); 1 << bits];
        for &(code, len, val) in entries {
            let shift = bits - len as u32;
            let base = (code << shift) as usize;
            for i in 0..(1usize << shift) {
                debug_assert_eq!(tab[base + i].1, 0, "VLC code overlaps");
                tab[base + i] = (val, len);
            }
        }
        Vlc { bits, tab }
    }
    #[inline]
    fn get(&self, br: &mut Bits) -> Option<i16> {
        let (v, l) = self.tab[br.peek(self.bits) as usize];
        if l == 0 {
            return None;
        }
        br.skip(l as u32);
        Some(v)
    }
}

/// B.1 macroblock_address_increment 1..=33 (value 34 = macroblock_escape).
const MBAI_CODES: [(u32, u8); 33] = [
    (0b1, 1),
    (0b011, 3),
    (0b010, 3),
    (0b0011, 4),
    (0b0010, 4),
    (0b00011, 5),
    (0b00010, 5),
    (0b0000111, 7),
    (0b0000110, 7),
    (0b00001011, 8),
    (0b00001010, 8),
    (0b00001001, 8),
    (0b00001000, 8),
    (0b00000111, 8),
    (0b00000110, 8),
    (0b0000010111, 10),
    (0b0000010110, 10),
    (0b0000010101, 10),
    (0b0000010100, 10),
    (0b0000010011, 10),
    (0b0000010010, 10),
    (0b00000100011, 11),
    (0b00000100010, 11),
    (0b00000100001, 11),
    (0b00000100000, 11),
    (0b00000011111, 11),
    (0b00000011110, 11),
    (0b00000011101, 11),
    (0b00000011100, 11),
    (0b00000011011, 11),
    (0b00000011010, 11),
    (0b00000011001, 11),
    (0b00000011000, 11),
];
const MBAI_ESCAPE: (u32, u8) = (0b00000001000, 11);

// macroblock type flags
const MB_QUANT: i16 = 1;
const MB_FWD: i16 = 2;
const MB_BWD: i16 = 4;
const MB_PATTERN: i16 = 8;
const MB_INTRA: i16 = 16;

/// B.2 (I), B.3 (P), B.4 (B)
const MBTYPE_I: [(u32, u8, i16); 2] = [(0b1, 1, MB_INTRA), (0b01, 2, MB_INTRA | MB_QUANT)];
const MBTYPE_P: [(u32, u8, i16); 7] = [
    (0b1, 1, MB_FWD | MB_PATTERN),
    (0b01, 2, MB_PATTERN),
    (0b001, 3, MB_FWD),
    (0b00011, 5, MB_INTRA),
    (0b00010, 5, MB_QUANT | MB_FWD | MB_PATTERN),
    (0b00001, 5, MB_QUANT | MB_PATTERN),
    (0b000001, 6, MB_QUANT | MB_INTRA),
];
const MBTYPE_B: [(u32, u8, i16); 11] = [
    (0b10, 2, MB_FWD | MB_BWD),
    (0b11, 2, MB_FWD | MB_BWD | MB_PATTERN),
    (0b010, 3, MB_BWD),
    (0b011, 3, MB_BWD | MB_PATTERN),
    (0b0010, 4, MB_FWD),
    (0b0011, 4, MB_FWD | MB_PATTERN),
    (0b00011, 5, MB_INTRA),
    (0b00010, 5, MB_QUANT | MB_FWD | MB_BWD | MB_PATTERN),
    (0b000011, 6, MB_QUANT | MB_FWD | MB_PATTERN),
    (0b000010, 6, MB_QUANT | MB_BWD | MB_PATTERN),
    (0b000001, 6, MB_QUANT | MB_INTRA),
];

/// B.9 coded_block_pattern (cbp, code, length)
const CBP_CODES: [(u8, u32, u8); 63] = [
    (60, 0b111, 3),
    (4, 0b1101, 4),
    (8, 0b1100, 4),
    (16, 0b1011, 4),
    (32, 0b1010, 4),
    (12, 0b10011, 5),
    (48, 0b10010, 5),
    (20, 0b10001, 5),
    (40, 0b10000, 5),
    (28, 0b01111, 5),
    (44, 0b01110, 5),
    (52, 0b01101, 5),
    (56, 0b01100, 5),
    (1, 0b01011, 5),
    (61, 0b01010, 5),
    (2, 0b01001, 5),
    (62, 0b01000, 5),
    (24, 0b001111, 6),
    (36, 0b001110, 6),
    (3, 0b001101, 6),
    (63, 0b001100, 6),
    (5, 0b0010111, 7),
    (9, 0b0010110, 7),
    (17, 0b0010101, 7),
    (33, 0b0010100, 7),
    (6, 0b0010011, 7),
    (10, 0b0010010, 7),
    (18, 0b0010001, 7),
    (34, 0b0010000, 7),
    (7, 0b00011111, 8),
    (11, 0b00011110, 8),
    (19, 0b00011101, 8),
    (35, 0b00011100, 8),
    (13, 0b00011011, 8),
    (49, 0b00011010, 8),
    (21, 0b00011001, 8),
    (41, 0b00011000, 8),
    (14, 0b00010111, 8),
    (50, 0b00010110, 8),
    (22, 0b00010101, 8),
    (42, 0b00010100, 8),
    (15, 0b00010011, 8),
    (51, 0b00010010, 8),
    (23, 0b00010001, 8),
    (43, 0b00010000, 8),
    (25, 0b00001111, 8),
    (37, 0b00001110, 8),
    (26, 0b00001101, 8),
    (38, 0b00001100, 8),
    (29, 0b00001011, 8),
    (45, 0b00001010, 8),
    (53, 0b00001001, 8),
    (57, 0b00001000, 8),
    (30, 0b00000111, 8),
    (46, 0b00000110, 8),
    (54, 0b00000101, 8),
    (58, 0b00000100, 8),
    (31, 0b000000111, 9),
    (47, 0b000000110, 9),
    (55, 0b000000101, 9),
    (59, 0b000000100, 9),
    (27, 0b000000011, 9),
    (39, 0b000000010, 9),
];

/// B.10 motion_code magnitude (without the sign bit)
const MOTION_CODES: [(u32, u8, i16); 17] = [
    (0b1, 1, 0),
    (0b01, 2, 1),
    (0b001, 3, 2),
    (0b0001, 4, 3),
    (0b000011, 6, 4),
    (0b0000101, 7, 5),
    (0b0000100, 7, 6),
    (0b0000011, 7, 7),
    (0b000001011, 9, 8),
    (0b000001010, 9, 9),
    (0b000001001, 9, 10),
    (0b0000010001, 10, 11),
    (0b0000010000, 10, 12),
    (0b0000001111, 10, 13),
    (0b0000001110, 10, 14),
    (0b0000001101, 10, 15),
    (0b0000001100, 10, 16),
];

struct Tables {
    mbai: Vlc,
    mbtype_i: Vlc,
    mbtype_p: Vlc,
    mbtype_b: Vlc,
    cbp: Vlc,
    motion: Vlc,
    dc_lum: Vlc,
    dc_chr: Vlc,
    coef0: Vlc,
    coef1: Vlc,
}

/// Run/level code lists shared with the `ipum` decoder (index = position in the table, `ESC` / `EOB` last).
fn coef_vlc(codes: &[(u16, u8); 113]) -> Vlc {
    let entries: Vec<(u32, u8, i16)> = codes.iter().enumerate().map(|(i, &(c, l))| (c as u32, l, i as i16)).collect();
    Vlc::new(&entries)
}

fn tables() -> &'static Tables {
    static T: OnceLock<Tables> = OnceLock::new();
    T.get_or_init(|| {
        let mut mbai: Vec<(u32, u8, i16)> = MBAI_CODES.iter().enumerate().map(|(i, &(c, l))| (c, l, i as i16 + 1)).collect();
        mbai.push((MBAI_ESCAPE.0, MBAI_ESCAPE.1, 34));
        let cbp: Vec<(u32, u8, i16)> = CBP_CODES.iter().map(|&(v, c, l)| (c, l, v as i16)).collect();
        let dc = |t: &[(u16, u8); 12]| Vlc::new(&t.iter().enumerate().map(|(i, &(c, l))| (c as u32, l, i as i16)).collect::<Vec<_>>());
        Tables {
            mbai: Vlc::new(&mbai),
            mbtype_i: Vlc::new(&MBTYPE_I),
            mbtype_p: Vlc::new(&MBTYPE_P),
            mbtype_b: Vlc::new(&MBTYPE_B),
            cbp: Vlc::new(&cbp),
            motion: Vlc::new(&MOTION_CODES),
            dc_lum: dc(&super::DC_LUM),
            dc_chr: dc(&super::DC_CHR),
            coef0: coef_vlc(&super::B14),
            coef1: coef_vlc(&super::B15),
        }
    })
}

/// Precomputed (run, level) for table indices 0..111.
fn run_level_table() -> &'static [(u8, u8); 111] {
    static T: OnceLock<[(u8, u8); 111]> = OnceLock::new();
    T.get_or_init(|| {
        let mut t = [(0u8, 0u8); 111];
        for (i, e) in t.iter_mut().enumerate() {
            let (r, l) = super::run_level(i);
            *e = (r, l as u8);
        }
        t
    })
}

// ----------------------------------------------------------------------------------------------------------------------------------
// scan / quantiser constants
// ----------------------------------------------------------------------------------------------------------------------------------

const ZIGZAG: [u8; 64] = super::ZIGZAG;
const ALT_SCAN: [u8; 64] = super::ALT_SCAN;
const QSCALE_NONLINEAR: [u8; 32] = super::QSCALE_NONLINEAR;

// ----------------------------------------------------------------------------------------------------------------------------------
// IDCT
// ----------------------------------------------------------------------------------------------------------------------------------

fn idct_matrix() -> &'static [[f32; 8]; 8] {
    static C: OnceLock<[[f32; 8]; 8]> = OnceLock::new();
    C.get_or_init(|| {
        let mut c = [[0f32; 8]; 8];
        for (x, row) in c.iter_mut().enumerate() {
            for (u, v) in row.iter_mut().enumerate() {
                let a = if u == 0 { (0.5f64).sqrt() } else { 1.0 };
                *v = (0.5 * a * (((2 * x + 1) as f64) * (u as f64) * std::f64::consts::PI / 16.0).cos()) as f32;
            }
        }
        c
    })
}

/// Separable IDCT of a dequantised block (raster order).  `last` = highest raster row/column index with a coefficient (speed only).
fn idct(f: &[i32; 64], out: &mut [i16; 64]) {
    let c = idct_matrix();
    let mut tmp = [0f32; 64];
    // rows: tmp[v][x] = sum_u c[x][u] * f[v][u]
    for v in 0..8 {
        let row = &f[v * 8..v * 8 + 8];
        let mut maxu = 0;
        for u in (0..8).rev() {
            if row[u] != 0 {
                maxu = u + 1;
                break;
            }
        }
        if maxu == 0 {
            continue;
        }
        for x in 0..8 {
            let mut s = 0.0;
            for u in 0..maxu {
                s += c[x][u] * row[u] as f32;
            }
            tmp[v * 8 + x] = s;
        }
    }
    for x in 0..8 {
        for y in 0..8 {
            let mut s = 0.0;
            for v in 0..8 {
                s += c[y][v] * tmp[v * 8 + x];
            }
            out[y * 8 + x] = s.round().clamp(-256.0, 255.0) as i16;
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------
// decoder
// ----------------------------------------------------------------------------------------------------------------------------------

#[derive(Clone)]
struct SeqState {
    width: usize,
    height: usize,
    mb_w: usize,
    mb_h: usize,
    frame_rate_code: u8,
    progressive_sequence: bool,
    intra_matrix: [u8; 64],
    non_intra_matrix: [u8; 64],
    valid: bool,
}

impl Default for SeqState {
    fn default() -> Self {
        SeqState { width: 0, height: 0, mb_w: 0, mb_h: 0, frame_rate_code: 0, progressive_sequence: false, intra_matrix: [0; 64], non_intra_matrix: [16; 64], valid: false }
    }
}

#[derive(Clone, Copy, Default)]
struct PicParams {
    coding_type: u8,
    temporal_reference: u16,
    f_code: [[u8; 2]; 2],
    intra_dc_precision: u32,
    picture_structure: u8,
    top_field_first: bool,
    frame_pred_frame_dct: bool,
    concealment_mv: bool,
    q_scale_type: bool,
    intra_vlc_format: bool,
    alternate_scan: bool,
    repeat_first_field: bool,
    progressive_frame: bool,
}

/// Streaming MPEG-2 decoder: feed it a whole elementary stream, pull frames in display order.
pub struct Mpeg2Decoder<'a> {
    data: &'a [u8],
    /// byte offset of the next unparsed start code
    pos: usize,
    seq: SeqState,
    pic: PicParams,
    past: Option<Arc<Mpeg2Frame>>,
    future: Option<Arc<Mpeg2Frame>>,
    out: std::collections::VecDeque<Arc<Mpeg2Frame>>,
    /// pictures decoded so far
    pub pictures: usize,
    /// slices that failed to decode (their macroblocks keep the previous content / stay grey)
    pub slice_errors: usize,
    done: bool,
}

fn find_start_code(d: &[u8], from: usize) -> Option<usize> {
    let mut i = from;
    while i + 3 < d.len() {
        if d[i + 2] > 1 {
            i += 3;
        } else if d[i] == 0 && d[i + 1] == 0 && d[i + 2] == 1 {
            return Some(i);
        } else {
            i += 1;
        }
    }
    None
}

impl<'a> Mpeg2Decoder<'a> {
    pub fn new(data: &'a [u8]) -> Self {
        let _ = tables();
        Mpeg2Decoder { data, pos: 0, seq: SeqState::default(), pic: PicParams::default(), past: None, future: None, out: Default::default(), pictures: 0, slice_errors: 0, done: false }
    }

    /// (width, height, frame rate numerator, denominator) once a sequence header was seen.
    pub fn format(&self) -> Option<(usize, usize, u32, u32)> {
        if !self.seq.valid {
            return None;
        }
        let (n, d) = match self.seq.frame_rate_code {
            1 => (24000, 1001),
            2 => (24, 1),
            3 => (25, 1),
            4 => (30000, 1001),
            5 => (30, 1),
            6 => (50, 1),
            7 => (60000, 1001),
            8 => (60, 1),
            _ => (30000, 1001),
        };
        Some((self.seq.width, self.seq.height, n, d))
    }

    /// Read the first sequence header without consuming anything: `(width, height, fps numerator, denominator)`.
    pub fn peek_format(&mut self) -> Option<(usize, usize, u32, u32)> {
        let sc = find_start_code(self.data, 0)?;
        let mut sc = sc;
        while self.data[sc + 3] != 0xb3 {
            sc = find_start_code(self.data, sc + 4)?;
        }
        self.parse_sequence_header(sc + 4).ok()?;
        self.format()
    }

    /// Parameters of the picture parsed last (diagnostics).
    pub fn debug_state(&self) -> String {
        let p = &self.pic;
        format!(
            "type {} tr {} fcode {:?} idp {} struct {} tff {} fpfd {} cmv {} qst {} ivf {} alt {} rff {} prog {}",
            p.coding_type, p.temporal_reference, p.f_code, p.intra_dc_precision, p.picture_structure, p.top_field_first, p.frame_pred_frame_dct, p.concealment_mv, p.q_scale_type, p.intra_vlc_format, p.alternate_scan, p.repeat_first_field, p.progressive_frame
        )
    }

    /// Next frame in display order; `None` at the end of the stream.
    pub fn next_frame(&mut self) -> Result<Option<Arc<Mpeg2Frame>>, Mpeg2Error> {
        loop {
            if let Some(f) = self.out.pop_front() {
                return Ok(Some(f));
            }
            if self.done {
                return Ok(None);
            }
            self.step()?;
        }
    }

    /// Parse until at least one frame was queued or the stream ended.
    fn step(&mut self) -> Result<(), Mpeg2Error> {
        let d = self.data;
        let Some(sc) = find_start_code(d, self.pos) else {
            self.flush();
            return Ok(());
        };
        let code = d[sc + 3];
        match code {
            0xb3 => {
                self.parse_sequence_header(sc + 4)?;
                self.pos = sc + 4;
            }
            0xb5 => {
                self.parse_extension(sc + 4)?;
                self.pos = sc + 4;
            }
            0x00 => {
                // picture: header + extension + all slices up to the next picture / sequence / GOP start
                let mut p = sc + 4;
                let mut br = Bits::new(d, p);
                self.pic = PicParams::default();
                self.pic.temporal_reference = br.read(10) as u16;
                self.pic.coding_type = br.read(3) as u8;
                br.read(16); // vbv_delay
                if self.pic.coding_type == 2 || self.pic.coding_type == 3 {
                    br.read1();
                    let f = br.read(3) as u8;
                    self.pic.f_code[0] = [f, f];
                    if self.pic.coding_type == 3 {
                        br.read1();
                        let f = br.read(3) as u8;
                        self.pic.f_code[1] = [f, f];
                    }
                }
                while br.read1() == 1 {
                    br.read(8);
                }
                p = (br.pos + 7) / 8;
                self.pic.picture_structure = 3;
                self.pic.progressive_frame = true;
                // extensions and user data, then slices
                let mut cur = p;
                let mut slices: Vec<(usize, u8)> = Vec::new();
                let mut have_ext = false;
                loop {
                    let Some(s) = find_start_code(d, cur) else {
                        cur = d.len();
                        break;
                    };
                    let c = d[s + 3];
                    match c {
                        0xb5 => {
                            self.parse_extension(s + 4)?;
                            have_ext = true;
                            cur = s + 4;
                        }
                        0xb2 => cur = s + 4,
                        0x01..=0xaf => {
                            slices.push((s + 4, c));
                            cur = s + 4;
                        }
                        _ => {
                            cur = s;
                            break;
                        }
                    }
                }
                self.pos = cur;
                if !have_ext {
                    return Err(Mpeg2Error::Unsupported("MPEG-1 picture (no picture_coding_extension)"));
                }
                self.decode_picture(&slices)?;
            }
            _ => {
                self.pos = sc + 4;
                if code == 0xb7 {
                    // sequence end
                }
            }
        }
        Ok(())
    }

    fn flush(&mut self) {
        self.done = true;
        if let Some(f) = self.future.take() {
            self.out.push_back(f);
        }
        self.past = None;
    }

    fn parse_sequence_header(&mut self, at: usize) -> Result<(), Mpeg2Error> {
        let mut br = Bits::new(self.data, at);
        let w = br.read(12) as usize;
        let h = br.read(12) as usize;
        br.read(4);
        let fr = br.read(4) as u8;
        br.read(18);
        br.read1();
        br.read(10);
        br.read1();
        let mut intra = [0u8; 64];
        let mut non = [16u8; 64];
        for i in 0..64 {
            intra[ZIGZAG[i] as usize] = super::INTRA_MATRIX[ZIGZAG[i] as usize];
        }
        if br.read1() == 1 {
            for i in 0..64 {
                intra[ZIGZAG[i] as usize] = br.read(8) as u8;
            }
        }
        if br.read1() == 1 {
            for i in 0..64 {
                non[ZIGZAG[i] as usize] = br.read(8) as u8;
            }
        }
        if w == 0 || h == 0 {
            return Err(Mpeg2Error::Invalid("zero picture size"));
        }
        self.seq = SeqState {
            width: w,
            height: h,
            mb_w: w.div_ceil(16),
            mb_h: h.div_ceil(16),
            frame_rate_code: fr,
            progressive_sequence: false,
            intra_matrix: intra,
            non_intra_matrix: non,
            valid: true,
        };
        Ok(())
    }

    fn parse_extension(&mut self, at: usize) -> Result<(), Mpeg2Error> {
        let mut br = Bits::new(self.data, at);
        let id = br.read(4);
        match id {
            1 => {
                // sequence extension
                br.read(8);
                self.seq.progressive_sequence = br.read1() == 1;
                let chroma = br.read(2);
                if chroma != 1 {
                    return Err(Mpeg2Error::Unsupported("chroma format other than 4:2:0"));
                }
                let hx = br.read(2) as usize;
                let vx = br.read(2) as usize;
                if hx != 0 || vx != 0 {
                    self.seq.width |= hx << 12;
                    self.seq.height |= vx << 12;
                    self.seq.mb_w = self.seq.width.div_ceil(16);
                    self.seq.mb_h = self.seq.height.div_ceil(16);
                }
            }
            3 => {
                // quantiser matrix extension
                if br.read1() == 1 {
                    for i in 0..64 {
                        self.seq.intra_matrix[ZIGZAG[i] as usize] = br.read(8) as u8;
                    }
                }
                if br.read1() == 1 {
                    for i in 0..64 {
                        self.seq.non_intra_matrix[ZIGZAG[i] as usize] = br.read(8) as u8;
                    }
                }
                // chroma matrices are not used in 4:2:0
            }
            8 => {
                let p = &mut self.pic;
                p.f_code[0][0] = br.read(4) as u8;
                p.f_code[0][1] = br.read(4) as u8;
                p.f_code[1][0] = br.read(4) as u8;
                p.f_code[1][1] = br.read(4) as u8;
                p.intra_dc_precision = br.read(2);
                p.picture_structure = br.read(2) as u8;
                p.top_field_first = br.read1() == 1;
                p.frame_pred_frame_dct = br.read1() == 1;
                p.concealment_mv = br.read1() == 1;
                p.q_scale_type = br.read1() == 1;
                p.intra_vlc_format = br.read1() == 1;
                p.alternate_scan = br.read1() == 1;
                p.repeat_first_field = br.read1() == 1;
                br.read1(); // chroma_420_type
                p.progressive_frame = br.read1() == 1;
            }
            _ => {}
        }
        Ok(())
    }

    fn decode_picture(&mut self, slices: &[(usize, u8)]) -> Result<(), Mpeg2Error> {
        if !self.seq.valid {
            return Err(Mpeg2Error::NoSequence);
        }
        if self.pic.picture_structure != 3 {
            return Err(Mpeg2Error::Unsupported("field pictures"));
        }
        let ct = self.pic.coding_type;
        if !(1..=3).contains(&ct) {
            return Err(Mpeg2Error::Invalid("picture_coding_type"));
        }
        let mut frame = Mpeg2Frame::blank(self.seq.width, self.seq.height);
        frame.temporal_reference = self.pic.temporal_reference;
        frame.picture_type = ct;
        frame.progressive = self.pic.progressive_frame;
        frame.top_field_first = self.pic.top_field_first;
        frame.repeat_first_field = self.pic.repeat_first_field;
        // references
        let (fwd, bwd) = match ct {
            1 => (None, None),
            2 => (self.future.clone(), None),
            _ => (self.past.clone().or_else(|| self.future.clone()), self.future.clone()),
        };
        if ct == 2 && fwd.is_none() {
            return Err(Mpeg2Error::Invalid("P picture without a reference"));
        }
        {
            let mut dec = PicDecoder { seq: &self.seq, pic: self.pic, frame: &mut frame, fwd: fwd.as_deref(), bwd: bwd.as_deref() };
            for &(at, code) in slices {
                // slice data ends at the next start code; a damaged slice only spoils its own macroblock row
                let end = find_start_code(self.data, at).unwrap_or(self.data.len());
                if let Err(e) = dec.slice(&self.data[..end], at, code as usize - 1) {
                    self.slice_errors += 1;
                    log::warn!("mpeg2: picture {} slice {}: {e}", self.pictures, code);
                }
            }
        }
        self.pictures += 1;
        let frame = Arc::new(frame);
        if ct == 3 {
            self.out.push_back(frame);
        } else {
            if let Some(old) = self.future.take() {
                self.out.push_back(old.clone());
                self.past = Some(old);
            }
            self.future = Some(frame);
        }
        Ok(())
    }
}

#[derive(Clone, Copy, Default)]
struct MbState {
    flags: i16,
    /// frame_motion_type: 1 field, 2 frame
    motion_type: u8,
    field_select: [[u8; 2]; 2],
    mv: [[[i32; 2]; 2]; 2],
}

struct PicDecoder<'a> {
    seq: &'a SeqState,
    pic: PicParams,
    frame: &'a mut Mpeg2Frame,
    fwd: Option<&'a Mpeg2Frame>,
    bwd: Option<&'a Mpeg2Frame>,
}

impl PicDecoder<'_> {
    fn slice(&mut self, d: &[u8], at: usize, row: usize) -> Result<(), Mpeg2Error> {
        let t = tables();
        let mut br = Bits::new(d, at);
        if row >= self.seq.mb_h {
            return Err(Mpeg2Error::Invalid("slice row"));
        }
        let mut qcode = br.read(5);
        if br.peek(1) == 1 {
            br.read(9);
            while br.peek(1) == 1 {
                br.read(9);
            }
        }
        br.read1();
        let mb_w = self.seq.mb_w;
        let idp = self.pic.intra_dc_precision;
        let dc_reset = 128i32 << idp;
        let mut dc_pred = [dc_reset; 3];
        // pmv[s][r][t]
        let mut pmv = [[[0i32; 2]; 2]; 2];
        let mut addr: i64 = (row * mb_w) as i64 - 1;
        let mut first = true;
        let mut prev = MbState::default();
        let ct = self.pic.coding_type;
        loop {
            // macroblock_address_increment
            let mut inc = 0i64;
            loop {
                match t.mbai.get(&mut br) {
                    Some(34) => inc += 33,
                    Some(v) => {
                        inc += v as i64;
                        break;
                    }
                    None => return Err(Mpeg2Error::Invalid("macroblock_address_increment")),
                }
            }
            if first {
                addr += inc;
                first = false;
            } else {
                // skipped macroblocks
                for _ in 1..inc {
                    addr += 1;
                    if addr as usize >= mb_w * self.seq.mb_h {
                        return Err(Mpeg2Error::Invalid("skipped macroblock beyond the picture"));
                    }
                    dc_pred = [dc_reset; 3];
                    let (mx, my) = (addr as usize % mb_w, addr as usize / mb_w);
                    if ct == 2 {
                        pmv = [[[0; 2]; 2]; 2];
                        let mut st = MbState { flags: MB_FWD, motion_type: 2, ..Default::default() };
                        st.mv = [[[0; 2]; 2]; 2];
                        self.predict(mx, my, &st)?;
                    } else {
                        // B: same prediction as the previous macroblock
                        self.predict(mx, my, &prev)?;
                    }
                }
                addr += 1;
            }
            if addr as usize >= mb_w * self.seq.mb_h {
                return Err(Mpeg2Error::Invalid("macroblock beyond the picture"));
            }
            let (mx, my) = (addr as usize % mb_w, addr as usize / mb_w);
            // macroblock_type
            let flags = match ct {
                1 => t.mbtype_i.get(&mut br),
                2 => t.mbtype_p.get(&mut br),
                _ => t.mbtype_b.get(&mut br),
            }
            .ok_or(Mpeg2Error::Invalid("macroblock_type"))?;
            let intra = flags & MB_INTRA != 0;
            let mut st = MbState { flags, motion_type: 2, ..Default::default() };
            let mut dct_field = false;
            if flags & (MB_FWD | MB_BWD) != 0 {
                if !self.pic.frame_pred_frame_dct {
                    st.motion_type = br.read(2) as u8;
                    if st.motion_type == 3 {
                        return Err(Mpeg2Error::Unsupported("dual-prime prediction"));
                    }
                    if st.motion_type == 0 {
                        return Err(Mpeg2Error::Invalid("frame_motion_type"));
                    }
                }
            }
            if !self.pic.frame_pred_frame_dct && (intra || flags & MB_PATTERN != 0) {
                dct_field = br.read1() == 1;
            }
            if flags & MB_QUANT != 0 {
                qcode = br.read(5);
            }
            // motion vectors
            let nvec = |m: u8| if m == 1 { 2 } else { 1 };
            let read_dir = |br: &mut Bits, s: usize, st: &mut MbState, pmv: &mut [[[i32; 2]; 2]; 2]| -> Result<(), Mpeg2Error> {
                let f = self.pic.f_code[s];
                if f[0] == 0 || f[0] > 9 || f[1] == 0 || f[1] > 9 {
                    return Err(Mpeg2Error::Invalid("f_code"));
                }
                if nvec(st.motion_type) == 1 {
                    let mx = decode_mv(br, f[0] as u32, pmv[s][0][0])?;
                    let my = decode_mv(br, f[1] as u32, pmv[s][0][1])?;
                    pmv[s][0] = [mx, my];
                    pmv[s][1] = [mx, my];
                    st.mv[s][0] = [mx, my];
                    st.mv[s][1] = [mx, my];
                } else {
                    for r in 0..2 {
                        st.field_select[s][r] = br.read1() as u8;
                        let mx = decode_mv(br, f[0] as u32, pmv[s][r][0])?;
                        let my = decode_mv(br, f[1] as u32, pmv[s][r][1] >> 1)?;
                        pmv[s][r] = [mx, my * 2];
                        st.mv[s][r] = [mx, my];
                    }
                }
                Ok(())
            };
            if flags & MB_FWD != 0 {
                read_dir(&mut br, 0, &mut st, &mut pmv)?;
            }
            if flags & MB_BWD != 0 {
                read_dir(&mut br, 1, &mut st, &mut pmv)?;
            }
            if intra && self.pic.concealment_mv {
                // concealment motion vectors are decoded and ignored
                let f = self.pic.f_code[0];
                decode_mv(&mut br, f[0] as u32, 0)?;
                decode_mv(&mut br, f[1] as u32, 0)?;
                br.read1();
            }
            let cbp = if flags & MB_PATTERN != 0 {
                t.cbp.get(&mut br).ok_or(Mpeg2Error::Invalid("coded_block_pattern"))? as u32
            } else if intra {
                63
            } else {
                0
            };
            // predictor resets
            if !intra {
                dc_pred = [dc_reset; 3];
            }
            if intra {
                pmv = [[[0; 2]; 2]; 2];
            } else if ct == 2 && flags & MB_FWD == 0 {
                pmv = [[[0; 2]; 2]; 2];
                st.flags |= MB_FWD;
                st.motion_type = 2;
            }
            // prediction
            if !intra {
                self.predict(mx, my, &st)?;
            }
            let qscale = if self.pic.q_scale_type { QSCALE_NONLINEAR[qcode as usize & 31] as i32 } else { (qcode as i32) * 2 };
            // blocks
            for b in 0..6usize {
                if cbp & (1 << (5 - b)) == 0 {
                    continue;
                }
                let mut coef = [0i32; 64];
                if intra {
                    self.decode_intra_block(&mut br, b, &mut dc_pred, qscale, &mut coef)?;
                } else {
                    self.decode_inter_block(&mut br, qscale, &mut coef)?;
                }
                let mut res = [0i16; 64];
                idct(&coef, &mut res);
                self.put_block(mx, my, b, &res, intra, dct_field);
            }
            prev = st;
            if br.eof() {
                break;
            }
            if br.peek(23) == 0 {
                break;
            }
        }
        Ok(())
    }

    fn decode_intra_block(&self, br: &mut Bits, b: usize, dc_pred: &mut [i32; 3], qscale: i32, coef: &mut [i32; 64]) -> Result<(), Mpeg2Error> {
        let t = tables();
        let comp = if b < 4 { 0 } else { b - 3 };
        let size = (if comp == 0 { &t.dc_lum } else { &t.dc_chr }).get(br).ok_or(Mpeg2Error::Invalid("dc size"))? as u32;
        let diff = if size == 0 {
            0
        } else {
            let bits = br.read(size) as i32;
            if bits < (1 << (size - 1)) {
                bits + 1 - (1 << size)
            } else {
                bits
            }
        };
        dc_pred[comp] += diff;
        coef[0] = dc_pred[comp] * (8 >> self.pic.intra_dc_precision);
        let vlc = if self.pic.intra_vlc_format { &t.coef1 } else { &t.coef0 };
        let scan = if self.pic.alternate_scan { &ALT_SCAN } else { &ZIGZAG };
        let rl = run_level_table();
        let mut i = 0usize;
        loop {
            let idx = vlc.get(br).ok_or(Mpeg2Error::Invalid("ac code"))? as usize;
            if idx == 112 {
                break;
            }
            let (run, level) = if idx == 111 {
                let run = br.read(6) as usize;
                let mut l = br.read(12) as i32;
                if l >= 2048 {
                    l -= 4096;
                }
                (run, l)
            } else {
                let (r, l) = rl[idx];
                let neg = br.read1() == 1;
                (r as usize, if neg { -(l as i32) } else { l as i32 })
            };
            i += run + 1;
            if i > 63 {
                return Err(Mpeg2Error::Invalid("coefficient index"));
            }
            let pos = scan[i] as usize;
            coef[pos] = ((level * self.seq.intra_matrix[pos] as i32 * qscale) / 16).clamp(-2048, 2047);
        }
        mismatch(coef);
        Ok(())
    }

    fn decode_inter_block(&self, br: &mut Bits, qscale: i32, coef: &mut [i32; 64]) -> Result<(), Mpeg2Error> {
        let t = tables();
        // intra_vlc_format only selects the table of intra blocks; non-intra blocks always use B.14
        let vlc = &t.coef0;
        let scan = if self.pic.alternate_scan { &ALT_SCAN } else { &ZIGZAG };
        let rl = run_level_table();
        let mut i: i32 = -1;
        let mut first = true;
        loop {
            let (run, level);
            if first && br.peek(1) == 1 {
                // first coefficient of a non-intra block: "1s" = run 0, level 1
                br.skip(1);
                let neg = br.read1() == 1;
                run = 0;
                level = if neg { -1 } else { 1 };
            } else {
                let idx = vlc.get(br).ok_or(Mpeg2Error::Invalid("ac code"))? as usize;
                if idx == 112 {
                    break;
                }
                if idx == 111 {
                    run = br.read(6) as usize;
                    let mut l = br.read(12) as i32;
                    if l >= 2048 {
                        l -= 4096;
                    }
                    level = l;
                } else {
                    let (r, l) = rl[idx];
                    let neg = br.read1() == 1;
                    run = r as usize;
                    level = if neg { -(l as i32) } else { l as i32 };
                }
            }
            first = false;
            i += run as i32 + 1;
            if i > 63 {
                return Err(Mpeg2Error::Invalid("coefficient index"));
            }
            let pos = scan[i as usize] as usize;
            let k = level.signum();
            coef[pos] = (((2 * level + k) * self.seq.non_intra_matrix[pos] as i32 * qscale) / 32).clamp(-2048, 2047);
        }
        mismatch(coef);
        Ok(())
    }

    /// Write (intra) or add (inter) a decoded block at its place in the macroblock.
    fn put_block(&mut self, mx: usize, my: usize, b: usize, res: &[i16; 64], intra: bool, dct_field: bool) {
        let stride = self.frame.stride;
        let (plane, pstride, x0, y0, row_step): (&mut Vec<u8>, usize, usize, usize, usize) = if b < 4 {
            let bx = (b & 1) * 8;
            if dct_field {
                (&mut self.frame.y, stride, mx * 16 + bx, my * 16 + (b >> 1), 2)
            } else {
                (&mut self.frame.y, stride, mx * 16 + bx, my * 16 + (b >> 1) * 8, 1)
            }
        } else if b == 4 {
            (&mut self.frame.cb, stride / 2, mx * 8, my * 8, 1)
        } else {
            (&mut self.frame.cr, stride / 2, mx * 8, my * 8, 1)
        };
        for r in 0..8 {
            let row = (y0 + r * row_step) * pstride + x0;
            let dst = &mut plane[row..row + 8];
            let src = &res[r * 8..r * 8 + 8];
            if intra {
                for (d, s) in dst.iter_mut().zip(src) {
                    *d = (*s).clamp(0, 255) as u8;
                }
            } else {
                for (d, s) in dst.iter_mut().zip(src) {
                    *d = (*d as i32 + *s as i32).clamp(0, 255) as u8;
                }
            }
        }
    }

    /// Motion-compensated prediction of macroblock (`mx`, `my`) into the current frame.
    fn predict(&mut self, mx: usize, my: usize, st: &MbState) -> Result<(), Mpeg2Error> {
        let fwd = st.flags & MB_FWD != 0;
        let bwd = st.flags & MB_BWD != 0;
        let mut first = true;
        for (s, on) in [(0usize, fwd), (1usize, bwd)] {
            if !on {
                continue;
            }
            let reference = if s == 0 { self.fwd } else { self.bwd }.ok_or(Mpeg2Error::Invalid("missing reference picture"))?;
            let avg = !first;
            first = false;
            if st.motion_type == 1 && !self.pic.frame_pred_frame_dct {
                // field prediction in a frame picture: two 16x8 blocks
                for r in 0..2usize {
                    let fs = st.field_select[s][r] as usize;
                    let [vx, vy] = st.mv[s][r];
                    mc_plane(&mut self.frame.y, &reference.y, reference.stride, reference.height.div_ceil(16) * 16, mx * 16, my * 8, 16, 8, vx, vy, Field { dst_parity: r, ref_parity: fs }, avg);
                    let (cvx, cvy) = (vx / 2, vy / 2);
                    let cs = reference.stride / 2;
                    mc_plane(&mut self.frame.cb, &reference.cb, cs, reference.height.div_ceil(16) * 8, mx * 8, my * 4, 8, 4, cvx, cvy, Field { dst_parity: r, ref_parity: fs }, avg);
                    mc_plane(&mut self.frame.cr, &reference.cr, cs, reference.height.div_ceil(16) * 8, mx * 8, my * 4, 8, 4, cvx, cvy, Field { dst_parity: r, ref_parity: fs }, avg);
                }
            } else {
                let [vx, vy] = st.mv[s][0];
                mc_plane(&mut self.frame.y, &reference.y, reference.stride, reference.height.div_ceil(16) * 16, mx * 16, my * 16, 16, 16, vx, vy, Field::FRAME, avg);
                let (cvx, cvy) = (vx / 2, vy / 2);
                let cs = reference.stride / 2;
                mc_plane(&mut self.frame.cb, &reference.cb, cs, reference.height.div_ceil(16) * 8, mx * 8, my * 8, 8, 8, cvx, cvy, Field::FRAME, avg);
                mc_plane(&mut self.frame.cr, &reference.cr, cs, reference.height.div_ceil(16) * 8, mx * 8, my * 8, 8, 8, cvx, cvy, Field::FRAME, avg);
            }
        }
        Ok(())
    }
}

fn mismatch(f: &mut [i32; 64]) {
    let sum: i32 = f.iter().sum();
    if sum & 1 == 0 {
        f[63] += if f[63] & 1 != 0 { -1 } else { 1 };
    }
}

/// Decode one motion vector component (`motion_code` + `motion_residual`) relative to the predictor.
fn decode_mv(br: &mut Bits, f_code: u32, pred: i32) -> Result<i32, Mpeg2Error> {
    let t = tables();
    let mag = t.motion.get(br).ok_or(Mpeg2Error::Invalid("motion_code"))? as i32;
    if mag == 0 {
        return Ok(pred);
    }
    let neg = br.read1() == 1;
    let shift = f_code - 1;
    let mut val = mag;
    if shift > 0 {
        val = ((val - 1) << shift) | br.read(shift) as i32;
        val += 1;
    }
    if neg {
        val = -val;
    }
    val += pred;
    // modulo wrap to [-16 << shift, (16 << shift) - 1]
    let bits = 5 + shift;
    let range = 1 << bits;
    let half = range >> 1;
    let mut v = val & (range - 1);
    if v >= half {
        v -= range;
    }
    Ok(v)
}

#[derive(Clone, Copy)]
struct Field {
    /// destination row parity (0 = every row; field prediction writes rows `2*r + parity`)
    dst_parity: usize,
    ref_parity: usize,
}
impl Field {
    const FRAME: Field = Field { dst_parity: usize::MAX, ref_parity: 0 };
    fn is_frame(&self) -> bool {
        self.dst_parity == usize::MAX
    }
}

/// Half-pel prediction of a `w x h` block.  `(bx, by)` is the block origin in the destination plane (for field prediction `by` is in
/// field rows), `(vx, vy)` the half-pel vector.  `ref_rows` = number of rows of the (frame) reference plane.
#[allow(clippy::too_many_arguments)]
fn mc_plane(dst: &mut [u8], refp: &[u8], stride: usize, ref_rows: usize, bx: usize, by: usize, w: usize, h: usize, vx: i32, vy: i32, field: Field, avg: bool) {
    let (rmul, roff, rrows) = if field.is_frame() { (1usize, 0usize, ref_rows) } else { (2usize, field.ref_parity, ref_rows / 2) };
    let ix = bx as i32 + (vx >> 1);
    let iy = by as i32 + (vy >> 1);
    let hx = (vx & 1) as i32;
    let hy = (vy & 1) as i32;
    let maxx = stride as i32 - 1;
    let maxy = rrows as i32 - 1;
    let fetch = |x: i32, y: i32| -> i32 {
        let xx = x.clamp(0, maxx) as usize;
        let yy = y.clamp(0, maxy) as usize;
        refp[(yy * rmul + roff) * stride + xx] as i32
    };
    for r in 0..h {
        let drow = if field.is_frame() { by + r } else { (by + r) * 2 + field.dst_parity };
        let dbase = drow * stride + bx;
        let y = iy + r as i32;
        // fast path: block fully inside
        for c in 0..w {
            let x = ix + c as i32;
            let p = match (hx, hy) {
                (0, 0) => fetch(x, y),
                (1, 0) => (fetch(x, y) + fetch(x + 1, y) + 1) >> 1,
                (0, 1) => (fetch(x, y) + fetch(x, y + 1) + 1) >> 1,
                _ => (fetch(x, y) + fetch(x + 1, y) + fetch(x, y + 1) + fetch(x + 1, y + 1) + 2) >> 2,
            };
            let d = &mut dst[dbase + c];
            *d = if avg { ((*d as i32 + p + 1) >> 1) as u8 } else { p as u8 };
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn kraft(entries: &[(u32, u8)]) -> f64 {
        let mut k = 0.0;
        for (i, &(c, l)) in entries.iter().enumerate() {
            assert!(c < (1 << l), "code {i} too long");
            k += 0.5f64.powi(l as i32);
            for (j, &(c2, l2)) in entries.iter().enumerate() {
                if i != j && l2 >= l {
                    assert_ne!(c2 >> (l2 - l), c, "code {i} is a prefix of {j}");
                }
            }
        }
        k
    }

    #[test]
    fn vlc_tables_are_prefix_free() {
        let mut e: Vec<(u32, u8)> = MBAI_CODES.to_vec();
        e.push(MBAI_ESCAPE);
        assert!(kraft(&e) <= 1.0);
        assert!(kraft(&CBP_CODES.iter().map(|&(_, c, l)| (c, l)).collect::<Vec<_>>()) <= 1.0);
        assert!(kraft(&MOTION_CODES.iter().map(|&(c, l, _)| (c, l)).collect::<Vec<_>>()) <= 1.0);
        for t in [&MBTYPE_I[..], &MBTYPE_P[..], &MBTYPE_B[..]] {
            let k = kraft(&t.iter().map(|&(c, l, _)| (c, l)).collect::<Vec<_>>());
            assert!(k <= 1.0);
        }
        // the cbp table has all 63 non-zero patterns exactly once
        let mut seen = [false; 64];
        for &(v, _, _) in &CBP_CODES {
            assert!(!seen[v as usize]);
            seen[v as usize] = true;
        }
        let _ = tables();
    }

    #[test]
    fn mv_wrap() {
        // motion_code 0 keeps the predictor
        let d = [0x80u8, 0, 0, 0];
        let mut br = Bits::new(&d, 0);
        assert_eq!(decode_mv(&mut br, 1, 5).unwrap(), 5);
    }

    #[test]
    fn idct_dc() {
        let mut f = [0i32; 64];
        f[0] = 80; // 80/8 = 10
        let mut o = [0i16; 64];
        idct(&f, &mut o);
        assert!(o.iter().all(|&v| v == 10));
    }
}
