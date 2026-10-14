//! Hardware-independent model of the PS2 GIF/GS register interface, as used by every `VIF1Prim` packet in the game.
//!
//! The game's 2D packets (sprites, prim2D, fonts, fades, screen copies) are *already GS-ready*: they are GIF tags
//! followed by PACKED / REGLIST / A+D data.  [`GsInterpreter`] consumes those qwords exactly like the GS would and
//! emits [`GsEvent`]s (draw primitives with full state, image uploads, local copies, texture flushes) that a modern
//! renderer can replay.  Model packets (VU1 microprogram input) are NOT GS-ready and are handled in Section C.
//!
//! See notes/B/pipeline.md.

use std::fmt;

/// 128-bit quadword (the unit of every PS2 DMA / GIF transfer).
#[derive(Clone, Copy, Default, PartialEq, Eq, Hash)]
pub struct Qword {
    pub lo: u64,
    pub hi: u64,
}

impl fmt::Debug for Qword {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{:016x}_{:016x}", self.hi, self.lo)
    }
}

impl Qword {
    pub const ZERO: Qword = Qword { lo: 0, hi: 0 };
    pub const fn new(lo: u64, hi: u64) -> Self {
        Qword { lo, hi }
    }
    pub fn from_words(w: [u32; 4]) -> Self {
        Qword { lo: w[0] as u64 | (w[1] as u64) << 32, hi: w[2] as u64 | (w[3] as u64) << 32 }
    }
    pub fn words(&self) -> [u32; 4] {
        [self.lo as u32, (self.lo >> 32) as u32, self.hi as u32, (self.hi >> 32) as u32]
    }
    pub fn from_le_bytes(b: &[u8]) -> Self {
        let mut a = [0u8; 16];
        a[..b.len().min(16)].copy_from_slice(&b[..b.len().min(16)]);
        Qword { lo: u64::from_le_bytes(a[0..8].try_into().unwrap()), hi: u64::from_le_bytes(a[8..16].try_into().unwrap()) }
    }
}

/// GS register addresses (the `addr` half of an A+D qword).
pub mod reg {
    pub const PRIM: u8 = 0x00;
    pub const RGBAQ: u8 = 0x01;
    pub const ST: u8 = 0x02;
    pub const UV: u8 = 0x03;
    pub const XYZF2: u8 = 0x04;
    pub const XYZ2: u8 = 0x05;
    pub const TEX0_1: u8 = 0x06;
    pub const TEX0_2: u8 = 0x07;
    pub const CLAMP_1: u8 = 0x08;
    pub const CLAMP_2: u8 = 0x09;
    pub const FOG: u8 = 0x0a;
    pub const XYZF3: u8 = 0x0c;
    pub const XYZ3: u8 = 0x0d;
    pub const AD: u8 = 0x0e;
    pub const NOP: u8 = 0x0f;
    pub const TEX1_1: u8 = 0x14;
    pub const TEX1_2: u8 = 0x15;
    pub const TEX2_1: u8 = 0x16;
    pub const TEX2_2: u8 = 0x17;
    pub const XYOFFSET_1: u8 = 0x18;
    pub const XYOFFSET_2: u8 = 0x19;
    pub const PRMODECONT: u8 = 0x1a;
    pub const PRMODE: u8 = 0x1b;
    pub const TEXCLUT: u8 = 0x1c;
    pub const SCANMSK: u8 = 0x22;
    pub const MIPTBP1_1: u8 = 0x34;
    pub const MIPTBP1_2: u8 = 0x35;
    pub const MIPTBP2_1: u8 = 0x36;
    pub const MIPTBP2_2: u8 = 0x37;
    pub const TEXA: u8 = 0x3b;
    pub const FOGCOL: u8 = 0x3d;
    pub const TEXFLUSH: u8 = 0x3f;
    pub const SCISSOR_1: u8 = 0x40;
    pub const SCISSOR_2: u8 = 0x41;
    pub const ALPHA_1: u8 = 0x42;
    pub const ALPHA_2: u8 = 0x43;
    pub const DIMX: u8 = 0x44;
    pub const DTHE: u8 = 0x45;
    pub const COLCLAMP: u8 = 0x46;
    pub const TEST_1: u8 = 0x47;
    pub const TEST_2: u8 = 0x48;
    pub const PABE: u8 = 0x49;
    pub const FBA_1: u8 = 0x4a;
    pub const FBA_2: u8 = 0x4b;
    pub const FRAME_1: u8 = 0x4c;
    pub const FRAME_2: u8 = 0x4d;
    pub const ZBUF_1: u8 = 0x4e;
    pub const ZBUF_2: u8 = 0x4f;
    pub const BITBLTBUF: u8 = 0x50;
    pub const TRXPOS: u8 = 0x51;
    pub const TRXREG: u8 = 0x52;
    pub const TRXDIR: u8 = 0x53;
    pub const HWREG: u8 = 0x54;
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum GifFlg {
    Packed,
    RegList,
    Image,
    Disable,
}

/// A decoded GIFtag.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct GifTag {
    pub nloop: u16,
    pub eop: bool,
    pub pre: bool,
    pub prim: u16,
    pub flg: GifFlg,
    pub nreg: u8,
    pub regs: [u8; 16],
}

impl GifTag {
    pub fn parse(q: Qword) -> GifTag {
        let nloop = (q.lo & 0x7fff) as u16;
        let eop = (q.lo >> 15) & 1 != 0;
        let pre = (q.lo >> 46) & 1 != 0;
        let prim = ((q.lo >> 47) & 0x7ff) as u16;
        let flg = match (q.lo >> 58) & 3 {
            0 => GifFlg::Packed,
            1 => GifFlg::RegList,
            2 => GifFlg::Image,
            _ => GifFlg::Disable,
        };
        let mut nreg = ((q.lo >> 60) & 0xf) as u8;
        if nreg == 0 {
            nreg = 16;
        }
        let mut regs = [0u8; 16];
        for (i, r) in regs.iter_mut().enumerate() {
            *r = ((q.hi >> (4 * i)) & 0xf) as u8;
        }
        GifTag { nloop, eop, pre, prim, flg, nreg, regs }
    }

    /// Build a tag (used by packet builders mirroring the original code).
    pub fn build(nloop: u16, eop: bool, pre: bool, prim: u16, flg: GifFlg, regs: &[u8]) -> Qword {
        let f = match flg {
            GifFlg::Packed => 0u64,
            GifFlg::RegList => 1,
            GifFlg::Image => 2,
            GifFlg::Disable => 3,
        };
        let nreg = if regs.len() == 16 { 0 } else { regs.len() as u64 };
        let lo = nloop as u64 | (eop as u64) << 15 | (pre as u64) << 46 | (prim as u64 & 0x7ff) << 47 | f << 58 | nreg << 60;
        let mut hi = 0u64;
        for (i, r) in regs.iter().enumerate() {
            hi |= (*r as u64 & 0xf) << (4 * i);
        }
        Qword { lo, hi }
    }
}

/// An `A+D` qword: `{data: u64, addr: u8}`.
pub fn ad(addr: u8, data: u64) -> Qword {
    Qword { lo: data, hi: addr as u64 }
}

/// A GIF packet: tag followed by its data qwords (nloop * nreg for PACKED, ceil(nloop*nreg/2) for REGLIST, nloop for IMAGE).
#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct GifPacket {
    pub qw: Vec<Qword>,
}

impl GifPacket {
    pub fn new() -> Self {
        Self::default()
    }
    pub fn push(&mut self, q: Qword) -> &mut Self {
        self.qw.push(q);
        self
    }
    /// Start an A+D block (`nloop` registers, EOP set) and return `self` for chaining `ad()` pushes.
    pub fn ad_block(&mut self, items: &[(u8, u64)]) -> &mut Self {
        self.qw.push(GifTag::build(items.len() as u16, true, false, 0, GifFlg::Packed, &[reg::AD]));
        for (a, d) in items {
            self.qw.push(ad(*a, *d));
        }
        self
    }
}

// -------------------------------------------------------------------------------------------------
// Register field decoders
// -------------------------------------------------------------------------------------------------

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Prim {
    pub kind: u8,
    pub iip: bool,
    pub tme: bool,
    pub fge: bool,
    pub abe: bool,
    pub aa1: bool,
    pub fst: bool,
    pub ctxt: bool,
    pub fix: bool,
}
impl Prim {
    pub fn from_bits(v: u64) -> Prim {
        Prim {
            kind: (v & 7) as u8,
            iip: v & 0x8 != 0,
            tme: v & 0x10 != 0,
            fge: v & 0x20 != 0,
            abe: v & 0x40 != 0,
            aa1: v & 0x80 != 0,
            fst: v & 0x100 != 0,
            ctxt: v & 0x200 != 0,
            fix: v & 0x400 != 0,
        }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Tex0 {
    pub tbp0: u16,
    pub tbw: u8,
    pub psm: u8,
    pub tw: u8,
    pub th: u8,
    pub tcc_rgba: bool,
    pub tfx: u8,
    pub cbp: u16,
    pub cpsm: u8,
    pub csm2: bool,
    pub csa: u8,
    pub cld: u8,
}
impl Tex0 {
    pub fn from_bits(v: u64) -> Tex0 {
        Tex0 {
            tbp0: (v & 0x3fff) as u16,
            tbw: ((v >> 14) & 0x3f) as u8,
            psm: ((v >> 20) & 0x3f) as u8,
            tw: ((v >> 26) & 0xf) as u8,
            th: ((v >> 30) & 0xf) as u8,
            tcc_rgba: (v >> 34) & 1 != 0,
            tfx: ((v >> 35) & 3) as u8,
            cbp: ((v >> 37) & 0x3fff) as u16,
            cpsm: ((v >> 51) & 0xf) as u8,
            csm2: (v >> 55) & 1 != 0,
            csa: ((v >> 56) & 0x1f) as u8,
            cld: ((v >> 61) & 7) as u8,
        }
    }
    pub fn width(&self) -> u32 {
        1 << self.tw
    }
    pub fn height(&self) -> u32 {
        1 << self.th
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Tex1 {
    pub lcm: bool,
    pub mxl: u8,
    pub mmag_linear: bool,
    pub mmin: u8,
}
impl Tex1 {
    pub fn from_bits(v: u64) -> Tex1 {
        Tex1 { lcm: v & 1 != 0, mxl: ((v >> 2) & 7) as u8, mmag_linear: (v >> 5) & 1 != 0, mmin: ((v >> 6) & 7) as u8 }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Clamp {
    pub wms: u8,
    pub wmt: u8,
    pub minu: u16,
    pub maxu: u16,
    pub minv: u16,
    pub maxv: u16,
}
impl Clamp {
    pub fn from_bits(v: u64) -> Clamp {
        Clamp {
            wms: (v & 3) as u8,
            wmt: ((v >> 2) & 3) as u8,
            minu: ((v >> 4) & 0x3ff) as u16,
            maxu: ((v >> 14) & 0x3ff) as u16,
            minv: ((v >> 24) & 0x3ff) as u16,
            maxv: ((v >> 34) & 0x3ff) as u16,
        }
    }
}

/// `ALPHA`: out = (A - B) * C >> 7 + D  with A,B,D in {0:Cs 1:Cd 2:0}, C in {0:As 1:Ad 2:FIX}.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Alpha {
    pub a: u8,
    pub b: u8,
    pub c: u8,
    pub d: u8,
    pub fix: u8,
}
impl Alpha {
    pub fn from_bits(v: u64) -> Alpha {
        Alpha { a: (v & 3) as u8, b: ((v >> 2) & 3) as u8, c: ((v >> 4) & 3) as u8, d: ((v >> 6) & 3) as u8, fix: ((v >> 32) & 0xff) as u8 }
    }
    /// The three blend modes the 2D layer uses (see `prim2D::setBlendMode`): 0 normal, 1 additive, 2 subtractive.
    pub const NORMAL: u64 = 0x44; // (Cs-Cd)*As+Cd
    pub const ADD: u64 = 0x48; // Cs*As+Cd
    pub const SUB: u64 = 0x42; // (0-Cs)*As+Cd
    pub fn classify(&self) -> BlendKind {
        match (self.a, self.b, self.c, self.d) {
            (0, 1, 0, 1) => BlendKind::AlphaBlend,
            (0, 2, 0, 1) => BlendKind::Additive,
            (2, 0, 0, 1) => BlendKind::Subtractive,
            _ => BlendKind::Other,
        }
    }
}
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BlendKind {
    AlphaBlend,
    Additive,
    Subtractive,
    Other,
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Test {
    pub ate: bool,
    pub atst: u8,
    pub aref: u8,
    pub afail: u8,
    pub date: bool,
    pub datm: bool,
    pub zte: bool,
    pub ztst: u8,
}
impl Test {
    pub fn from_bits(v: u64) -> Test {
        Test {
            ate: v & 1 != 0,
            atst: ((v >> 1) & 7) as u8,
            aref: ((v >> 4) & 0xff) as u8,
            afail: ((v >> 12) & 3) as u8,
            date: (v >> 14) & 1 != 0,
            datm: (v >> 15) & 1 != 0,
            zte: (v >> 16) & 1 != 0,
            ztst: ((v >> 17) & 3) as u8,
        }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Frame {
    /// Frame base in GS blocks (FBP*32).
    pub block: u32,
    pub fbw: u8,
    pub psm: u8,
    pub fbmsk: u32,
}
impl Frame {
    pub fn from_bits(v: u64) -> Frame {
        Frame { block: ((v & 0x1ff) as u32) * 32, fbw: ((v >> 16) & 0x3f) as u8, psm: ((v >> 24) & 0x3f) as u8, fbmsk: (v >> 32) as u32 }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct ZBuf {
    pub block: u32,
    pub psm: u8,
    pub zmsk: bool,
}
impl ZBuf {
    pub fn from_bits(v: u64) -> ZBuf {
        ZBuf { block: ((v & 0x1ff) as u32) * 32, psm: 0x30 | ((v >> 24) & 0xf) as u8, zmsk: (v >> 32) & 1 != 0 }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Scissor {
    pub x0: u16,
    pub x1: u16,
    pub y0: u16,
    pub y1: u16,
}
impl Scissor {
    pub fn from_bits(v: u64) -> Scissor {
        Scissor { x0: (v & 0x7ff) as u16, x1: ((v >> 16) & 0x7ff) as u16, y0: ((v >> 32) & 0x7ff) as u16, y1: ((v >> 48) & 0x7ff) as u16 }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Context {
    pub tex0: Tex0,
    pub tex1: Tex1,
    pub clamp: Clamp,
    pub alpha: Alpha,
    pub test: Test,
    pub frame: Frame,
    pub zbuf: ZBuf,
    pub scissor: Scissor,
    /// XYOFFSET in 12.4 fixed point.
    pub ofs_x: i32,
    pub ofs_y: i32,
    pub miptbp1: u64,
    pub miptbp2: u64,
}

#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Vertex {
    /// Screen position in pixels (after XYOFFSET), plus raw 24/32-bit Z.
    pub x: f32,
    pub y: f32,
    pub z: u32,
    pub rgba: [u8; 4],
    /// Texel coordinates when `Prim::fst`, else s/q and t/q (normalised) — see `Vertex::q`.
    pub u: f32,
    pub v: f32,
    pub q: f32,
    pub fog: u8,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum PrimKind {
    Point,
    Line,
    LineStrip,
    Triangle,
    TriStrip,
    TriFan,
    Sprite,
}
impl PrimKind {
    pub fn from_code(c: u8) -> Option<Self> {
        Some(match c {
            0 => Self::Point,
            1 => Self::Line,
            2 => Self::LineStrip,
            3 => Self::Triangle,
            4 => Self::TriStrip,
            5 => Self::TriFan,
            6 => Self::Sprite,
            _ => return None,
        })
    }
    fn verts_needed(self) -> usize {
        match self {
            Self::Point => 1,
            Self::Line | Self::LineStrip | Self::Sprite => 2,
            _ => 3,
        }
    }
}

/// A single primitive (point/line/triangle/sprite) with the full GS state that applies to it.
#[derive(Clone, Debug, PartialEq)]
pub struct DrawPrim {
    pub kind: PrimKind,
    pub attr: Prim,
    pub ctx: Context,
    pub texa: u64,
    pub fogcol: u32,
    pub pabe: bool,
    pub colclamp: bool,
    pub dthe: bool,
    pub verts: Vec<Vertex>,
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct BitBltBuf {
    pub sbp: u16,
    pub sbw: u8,
    pub spsm: u8,
    pub dbp: u16,
    pub dbw: u8,
    pub dpsm: u8,
}
impl BitBltBuf {
    pub fn from_bits(v: u64) -> Self {
        BitBltBuf {
            sbp: (v & 0x3fff) as u16,
            sbw: ((v >> 16) & 0x3f) as u8,
            spsm: ((v >> 24) & 0x3f) as u8,
            dbp: ((v >> 32) & 0x3fff) as u16,
            dbw: ((v >> 48) & 0x3f) as u8,
            dpsm: ((v >> 56) & 0x3f) as u8,
        }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct TrxPos {
    pub ssax: u16,
    pub ssay: u16,
    pub dsax: u16,
    pub dsay: u16,
    pub dir: u8,
}
impl TrxPos {
    pub fn from_bits(v: u64) -> Self {
        TrxPos {
            ssax: (v & 0x7ff) as u16,
            ssay: ((v >> 16) & 0x7ff) as u16,
            dsax: ((v >> 32) & 0x7ff) as u16,
            dsay: ((v >> 48) & 0x7ff) as u16,
            dir: ((v >> 59) & 3) as u8,
        }
    }
}

/// A host->local upload (TRXDIR=0): raw bytes in transfer order; the receiver decodes by `bitbltbuf.dpsm`.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ImageUpload {
    pub bitbltbuf: BitBltBuf,
    pub pos: TrxPos,
    pub rrw: u16,
    pub rrh: u16,
    pub data: Vec<u8>,
}

/// A local->local copy (TRXDIR=2): used by frame-buffer read-back effects.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct LocalCopy {
    pub bitbltbuf: BitBltBuf,
    pub pos: TrxPos,
    pub rrw: u16,
    pub rrh: u16,
}

#[derive(Clone, Debug, PartialEq)]
pub enum GsEvent {
    Draw(DrawPrim),
    Upload(ImageUpload),
    LocalCopy(LocalCopy),
    /// Local->host transfer request (CScrCapture / GsxFrameBuf::StoreImage use DMA instead; kept for completeness).
    Download(LocalCopy),
    TexFlush,
}

/// Software GIF + GS front end.
#[derive(Clone, Debug)]
pub struct GsInterpreter {
    pub ctx: [Context; 2],
    pub prim: Prim,
    pub rgbaq: [u8; 4],
    pub q: f32,
    pub st: (f32, f32),
    pub uv: (u16, u16),
    pub fog: u8,
    pub texa: u64,
    pub fogcol: u32,
    pub pabe: bool,
    pub colclamp: bool,
    pub dthe: bool,
    pub bitbltbuf: BitBltBuf,
    pub trxpos: TrxPos,
    pub trxreg: (u16, u16),
    pub trxdir: u8,
    queue: Vec<Vertex>,
    strip_flip: bool,
    image: Vec<u8>,
    image_expected: usize,
    pub events: Vec<GsEvent>,
}

impl Default for GsInterpreter {
    fn default() -> Self {
        GsInterpreter {
            ctx: [Context::default(); 2],
            prim: Prim::default(),
            rgbaq: [0x80; 4],
            q: 1.0,
            st: (0.0, 0.0),
            uv: (0, 0),
            fog: 0,
            texa: 0,
            fogcol: 0,
            pabe: false,
            colclamp: true,
            dthe: false,
            bitbltbuf: BitBltBuf::default(),
            trxpos: TrxPos::default(),
            trxreg: (0, 0),
            trxdir: 3,
            queue: Vec::new(),
            strip_flip: false,
            image: Vec::new(),
            image_expected: 0,
            events: Vec::new(),
        }
    }
}

impl GsInterpreter {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn take_events(&mut self) -> Vec<GsEvent> {
        std::mem::take(&mut self.events)
    }

    /// Feed a sequence of GIF packets back to back (as a VIF1 DIRECT / DIRECTHL stream delivers them).
    pub fn feed(&mut self, qws: &[Qword]) {
        let mut i = 0;
        while i < qws.len() {
            let tag = GifTag::parse(qws[i]);
            i += 1;
            if tag.prim != 0 || tag.pre {
                if tag.pre {
                    self.write_prim(tag.prim as u64);
                }
            }
            match tag.flg {
                GifFlg::Packed => {
                    for _ in 0..tag.nloop {
                        for r in 0..tag.nreg as usize {
                            if i >= qws.len() {
                                return;
                            }
                            self.packed(tag.regs[r], qws[i]);
                            i += 1;
                        }
                    }
                }
                GifFlg::RegList => {
                    let total = tag.nloop as usize * tag.nreg as usize;
                    let mut n = 0;
                    while n < total {
                        if i >= qws.len() {
                            return;
                        }
                        let q = qws[i];
                        i += 1;
                        for half in 0..2 {
                            if n >= total {
                                break;
                            }
                            let data = if half == 0 { q.lo } else { q.hi };
                            let r = tag.regs[n % tag.nreg as usize];
                            self.reglist(r, data);
                            n += 1;
                        }
                    }
                }
                GifFlg::Image => {
                    let n = tag.nloop as usize;
                    let end = (i + n).min(qws.len());
                    for q in &qws[i..end] {
                        self.image_qw(*q);
                    }
                    i = end;
                }
                GifFlg::Disable => {
                    i += tag.nloop as usize;
                }
            }
        }
    }

    fn packed(&mut self, r: u8, q: Qword) {
        match r {
            reg::PRIM => self.write_prim(q.lo & 0x7ff),
            reg::RGBAQ => {
                self.rgbaq = [q.lo as u8, (q.lo >> 32) as u8, q.hi as u8, (q.hi >> 32) as u8];
            }
            reg::ST => {
                self.st = (f32::from_bits(q.lo as u32), f32::from_bits((q.lo >> 32) as u32));
                self.q = f32::from_bits(q.hi as u32);
            }
            reg::UV => self.uv = ((q.lo & 0x3fff) as u16, ((q.lo >> 32) & 0x3fff) as u16),
            reg::XYZF2 | reg::XYZF3 => {
                let adc = (q.hi >> 47) & 1 != 0; // bit 111
                let x = (q.lo & 0xffff) as u16;
                let y = ((q.lo >> 32) & 0xffff) as u16;
                let z = ((q.hi >> 4) & 0xff_ffff) as u32; // bits 68..91
                self.fog = ((q.hi >> 36) & 0xff) as u8; // bits 100..107
                self.vertex(x, y, z, r == reg::XYZF2 && !adc);
            }
            reg::XYZ2 | reg::XYZ3 => {
                let adc = (q.hi >> 47) & 1 != 0;
                let x = (q.lo & 0xffff) as u16;
                let y = ((q.lo >> 32) & 0xffff) as u16;
                let z = q.hi as u32;
                self.vertex(x, y, z, r == reg::XYZ2 && !adc);
            }
            reg::FOG => self.fog = ((q.hi >> 36) & 0xff) as u8,
            reg::AD => self.write_reg((q.hi & 0xff) as u8, q.lo),
            _ => {}
        }
    }

    fn reglist(&mut self, r: u8, d: u64) {
        match r {
            reg::PRIM => self.write_prim(d & 0x7ff),
            reg::RGBAQ => {
                self.rgbaq = [d as u8, (d >> 8) as u8, (d >> 16) as u8, (d >> 24) as u8];
                self.q = f32::from_bits((d >> 32) as u32);
            }
            reg::ST => self.st = (f32::from_bits(d as u32), f32::from_bits((d >> 32) as u32)),
            reg::UV => self.uv = ((d & 0x3fff) as u16, ((d >> 16) & 0x3fff) as u16),
            reg::XYZF2 | reg::XYZF3 => {
                let x = (d & 0xffff) as u16;
                let y = ((d >> 16) & 0xffff) as u16;
                let z = ((d >> 32) & 0xff_ffff) as u32;
                self.fog = (d >> 56) as u8;
                self.vertex(x, y, z, r == reg::XYZF2);
            }
            reg::XYZ2 | reg::XYZ3 => {
                let x = (d & 0xffff) as u16;
                let y = ((d >> 16) & 0xffff) as u16;
                let z = (d >> 32) as u32;
                self.vertex(x, y, z, r == reg::XYZ2);
            }
            reg::FOG => self.fog = (d >> 56) as u8,
            reg::NOP | reg::AD => {}
            other => self.write_reg(other, d),
        }
    }

    fn write_prim(&mut self, v: u64) {
        self.prim = Prim::from_bits(v);
        self.queue.clear();
        self.strip_flip = false;
    }

    /// Write one GS register (A+D semantics).
    pub fn write_reg(&mut self, addr: u8, d: u64) {
        match addr {
            reg::PRIM => self.write_prim(d & 0x7ff),
            reg::RGBAQ => {
                self.rgbaq = [d as u8, (d >> 8) as u8, (d >> 16) as u8, (d >> 24) as u8];
                self.q = f32::from_bits((d >> 32) as u32);
            }
            reg::ST => self.st = (f32::from_bits(d as u32), f32::from_bits((d >> 32) as u32)),
            reg::UV => self.uv = ((d & 0x3fff) as u16, ((d >> 16) & 0x3fff) as u16),
            reg::XYZF2 => self.vertex((d & 0xffff) as u16, ((d >> 16) & 0xffff) as u16, ((d >> 32) & 0xff_ffff) as u32, true),
            reg::XYZ2 => self.vertex((d & 0xffff) as u16, ((d >> 16) & 0xffff) as u16, (d >> 32) as u32, true),
            reg::XYZF3 => self.vertex((d & 0xffff) as u16, ((d >> 16) & 0xffff) as u16, ((d >> 32) & 0xff_ffff) as u32, false),
            reg::XYZ3 => self.vertex((d & 0xffff) as u16, ((d >> 16) & 0xffff) as u16, (d >> 32) as u32, false),
            reg::TEX0_1 => self.ctx[0].tex0 = Tex0::from_bits(d),
            reg::TEX0_2 => self.ctx[1].tex0 = Tex0::from_bits(d),
            reg::CLAMP_1 => self.ctx[0].clamp = Clamp::from_bits(d),
            reg::CLAMP_2 => self.ctx[1].clamp = Clamp::from_bits(d),
            reg::TEX1_1 => self.ctx[0].tex1 = Tex1::from_bits(d),
            reg::TEX1_2 => self.ctx[1].tex1 = Tex1::from_bits(d),
            reg::XYOFFSET_1 => {
                self.ctx[0].ofs_x = (d & 0xffff) as i32;
                self.ctx[0].ofs_y = ((d >> 32) & 0xffff) as i32;
            }
            reg::XYOFFSET_2 => {
                self.ctx[1].ofs_x = (d & 0xffff) as i32;
                self.ctx[1].ofs_y = ((d >> 32) & 0xffff) as i32;
            }
            reg::MIPTBP1_1 => self.ctx[0].miptbp1 = d,
            reg::MIPTBP1_2 => self.ctx[1].miptbp1 = d,
            reg::MIPTBP2_1 => self.ctx[0].miptbp2 = d,
            reg::MIPTBP2_2 => self.ctx[1].miptbp2 = d,
            reg::TEXA => self.texa = d,
            reg::FOGCOL => self.fogcol = d as u32 & 0xff_ffff,
            reg::TEXFLUSH => self.events.push(GsEvent::TexFlush),
            reg::SCISSOR_1 => self.ctx[0].scissor = Scissor::from_bits(d),
            reg::SCISSOR_2 => self.ctx[1].scissor = Scissor::from_bits(d),
            reg::ALPHA_1 => self.ctx[0].alpha = Alpha::from_bits(d),
            reg::ALPHA_2 => self.ctx[1].alpha = Alpha::from_bits(d),
            reg::DTHE => self.dthe = d & 1 != 0,
            reg::COLCLAMP => self.colclamp = d & 1 != 0,
            reg::TEST_1 => self.ctx[0].test = Test::from_bits(d),
            reg::TEST_2 => self.ctx[1].test = Test::from_bits(d),
            reg::PABE => self.pabe = d & 1 != 0,
            reg::FRAME_1 => self.ctx[0].frame = Frame::from_bits(d),
            reg::FRAME_2 => self.ctx[1].frame = Frame::from_bits(d),
            reg::ZBUF_1 => self.ctx[0].zbuf = ZBuf::from_bits(d),
            reg::ZBUF_2 => self.ctx[1].zbuf = ZBuf::from_bits(d),
            reg::BITBLTBUF => self.bitbltbuf = BitBltBuf::from_bits(d),
            reg::TRXPOS => self.trxpos = TrxPos::from_bits(d),
            reg::TRXREG => self.trxreg = ((d & 0xfff) as u16, ((d >> 32) & 0xfff) as u16),
            reg::TRXDIR => {
                self.trxdir = (d & 3) as u8;
                match self.trxdir {
                    0 => self.begin_upload(),
                    2 => self.events.push(GsEvent::LocalCopy(LocalCopy {
                        bitbltbuf: self.bitbltbuf,
                        pos: self.trxpos,
                        rrw: self.trxreg.0,
                        rrh: self.trxreg.1,
                    })),
                    1 => self.events.push(GsEvent::Download(LocalCopy {
                        bitbltbuf: self.bitbltbuf,
                        pos: self.trxpos,
                        rrw: self.trxreg.0,
                        rrh: self.trxreg.1,
                    })),
                    _ => {}
                }
            }
            reg::HWREG => {
                for b in d.to_le_bytes() {
                    self.image.push(b);
                }
                self.finish_upload_if_complete();
            }
            _ => {}
        }
    }

    fn begin_upload(&mut self) {
        let bpp = crate::psm::Psm::from_code(self.bitbltbuf.dpsm).map(|p| p.bpp()).unwrap_or(32) as usize;
        self.image.clear();
        self.image_expected = ((self.trxreg.0 as usize * self.trxreg.1 as usize * bpp) + 7) / 8;
    }

    fn image_qw(&mut self, q: Qword) {
        self.image.extend_from_slice(&q.lo.to_le_bytes());
        self.image.extend_from_slice(&q.hi.to_le_bytes());
        self.finish_upload_if_complete();
    }

    fn finish_upload_if_complete(&mut self) {
        if self.image_expected != 0 && self.image.len() >= self.image_expected {
            let mut data = std::mem::take(&mut self.image);
            data.truncate(self.image_expected);
            self.image_expected = 0;
            self.events.push(GsEvent::Upload(ImageUpload {
                bitbltbuf: self.bitbltbuf,
                pos: self.trxpos,
                rrw: self.trxreg.0,
                rrh: self.trxreg.1,
                data,
            }));
        }
    }

    fn vertex(&mut self, x: u16, y: u16, z: u32, kick: bool) {
        let c = &self.ctx[self.prim.ctxt as usize];
        let vx = (x as i32 - c.ofs_x) as f32 / 16.0;
        let vy = (y as i32 - c.ofs_y) as f32 / 16.0;
        let (u, v, q) = if self.prim.fst {
            (self.uv.0 as f32 / 16.0, self.uv.1 as f32 / 16.0, 1.0)
        } else {
            (self.st.0, self.st.1, self.q)
        };
        let vert = Vertex { x: vx, y: vy, z, rgba: self.rgbaq, u, v, q, fog: self.fog };
        self.queue.push(vert);
        if !kick {
            // XYZ3/XYZF3 or ADC: vertex queued but no draw; the queue is capped to the primitive size.
            self.trim_queue_no_kick();
            return;
        }
        let Some(kind) = PrimKind::from_code(self.prim.kind) else { return };
        let need = kind.verts_needed();
        match kind {
            PrimKind::Point | PrimKind::Line | PrimKind::Triangle | PrimKind::Sprite => {
                if self.queue.len() >= need {
                    let vs: Vec<Vertex> = self.queue[self.queue.len() - need..].to_vec();
                    self.emit(kind, vs);
                    self.queue.clear();
                }
            }
            PrimKind::LineStrip => {
                if self.queue.len() >= 2 {
                    let vs = self.queue[self.queue.len() - 2..].to_vec();
                    self.emit(PrimKind::Line, vs);
                    let last = *self.queue.last().unwrap();
                    self.queue.clear();
                    self.queue.push(last);
                }
            }
            PrimKind::TriStrip => {
                if self.queue.len() >= 3 {
                    let n = self.queue.len();
                    let mut vs = vec![self.queue[n - 3], self.queue[n - 2], self.queue[n - 1]];
                    if self.strip_flip {
                        vs.swap(0, 1);
                    }
                    self.strip_flip = !self.strip_flip;
                    self.emit(PrimKind::Triangle, vs);
                    self.queue.remove(0);
                }
            }
            PrimKind::TriFan => {
                if self.queue.len() >= 3 {
                    let vs = self.queue.clone();
                    self.emit(PrimKind::Triangle, vs);
                    self.queue.remove(1);
                }
            }
        }
    }

    fn trim_queue_no_kick(&mut self) {
        let max = 3;
        if self.queue.len() > max {
            self.queue.remove(0);
        }
    }

    fn emit(&mut self, kind: PrimKind, verts: Vec<Vertex>) {
        let ctx = self.ctx[self.prim.ctxt as usize];
        self.events.push(GsEvent::Draw(DrawPrim {
            kind,
            attr: self.prim,
            ctx,
            texa: self.texa,
            fogcol: self.fogcol,
            pabe: self.pabe,
            colclamp: self.colclamp,
            dthe: self.dthe,
            verts,
        }));
    }
}

/// Convert a GS alpha byte (0x80 = 1.0) to a conventional 0..255 alpha.
pub fn gs_alpha_to_u8(a: u8) -> u8 {
    a.saturating_mul(2)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn gif_tag_roundtrip() {
        let q = GifTag::build(5, true, false, 0, GifFlg::Packed, &[reg::AD]);
        let t = GifTag::parse(q);
        assert_eq!(t.nloop, 5);
        assert!(t.eop);
        assert_eq!(t.flg, GifFlg::Packed);
        assert_eq!(t.nreg, 1);
        assert_eq!(t.regs[0], reg::AD);
        // the literal used by Texture::createRegsterPacket / P2Sprite::UpdateObj
        let t2 = GifTag::parse(Qword::new(0x1000000000008005, 0xe));
        assert_eq!((t2.nloop, t2.eop, t2.nreg, t2.regs[0]), (5, true, 1, reg::AD));
    }

    /// The reglist tag used by P2Sprite / SetFullSprite: 0x6400000000008001 + regs 0x434310.
    #[test]
    fn sprite_reglist_tag() {
        let t = GifTag::parse(Qword::new(0x6400000000008001, 0x434310));
        assert_eq!(t.flg, GifFlg::RegList);
        assert_eq!(t.nreg, 6);
        assert_eq!(&t.regs[..6], &[0, 1, 3, 4, 3, 4]);
    }

    #[test]
    fn alpha_blend_modes() {
        assert_eq!(Alpha::from_bits(Alpha::NORMAL).classify(), BlendKind::AlphaBlend);
        assert_eq!(Alpha::from_bits(Alpha::ADD).classify(), BlendKind::Additive);
        assert_eq!(Alpha::from_bits(Alpha::SUB).classify(), BlendKind::Subtractive);
    }
}
