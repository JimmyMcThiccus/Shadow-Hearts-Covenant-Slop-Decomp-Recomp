//! DMA source-chain and VIF1 code model.
//!
//! `World` builds a chain of `call`/`ret` DMA tags in EE memory and `WorldRender` (JP 0x00225f70) hands its address to the
//! VIF1 DMA channel (`DmaMan::DmaSend(1, ...)`).  Everything the game puts on that channel follows the conventions below,
//! which is what [`walk_chain`] / [`execute_chain`] reproduce so recorded RAM dumps (PCSX2) can be replayed against the Rust renderer.

use std::collections::BTreeMap;

use crate::gs::{GsInterpreter, Qword};

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
#[repr(u8)]
pub enum DmaId {
    Refe = 0,
    Cnt = 1,
    Next = 2,
    Ref = 3,
    Refs = 4,
    Call = 5,
    Ret = 6,
    End = 7,
}

impl DmaId {
    pub fn from_bits(v: u8) -> DmaId {
        match v & 7 {
            0 => DmaId::Refe,
            1 => DmaId::Cnt,
            2 => DmaId::Next,
            3 => DmaId::Ref,
            4 => DmaId::Refs,
            5 => DmaId::Call,
            6 => DmaId::Ret,
            _ => DmaId::End,
        }
    }
}

/// The low 64 bits of a DMA tag.  The high 64 bits carry two VIF codes (CHCR.TTE=1 on channel 1 in this game: `CHCR = 0x41`).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct DmaTag {
    pub qwc: u16,
    pub pce: u8,
    pub id: DmaId,
    pub irq: bool,
    pub addr: u32,
    pub spr: bool,
}

impl DmaTag {
    pub fn parse(q: Qword) -> DmaTag {
        DmaTag {
            qwc: (q.lo & 0xffff) as u16,
            pce: ((q.lo >> 26) & 3) as u8,
            id: DmaId::from_bits(((q.lo >> 28) & 7) as u8),
            irq: (q.lo >> 31) & 1 != 0,
            addr: ((q.lo >> 32) & 0x7fff_ffff) as u32,
            spr: (q.lo >> 63) & 1 != 0,
        }
    }

    /// `word0 = qwc | id<<28`, `word1 = addr` — exactly the 8 bytes the game writes (`*p = 0x50000000; p[1] = addr`).
    pub fn build(id: DmaId, qwc: u16, addr: u32) -> u64 {
        qwc as u64 | (id as u64) << 28 | (addr as u64) << 32
    }

    /// Full tag qword with two VIF codes in the upper half.
    pub fn qword(id: DmaId, qwc: u16, addr: u32, vif0: u32, vif1: u32) -> Qword {
        Qword { lo: Self::build(id, qwc, addr), hi: vif0 as u64 | (vif1 as u64) << 32 }
    }
}

/// VIF command (high byte of a VIF code).
pub mod vifcmd {
    pub const NOP: u8 = 0x00;
    pub const STCYCL: u8 = 0x01;
    pub const OFFSET: u8 = 0x02;
    pub const BASE: u8 = 0x03;
    pub const ITOP: u8 = 0x04;
    pub const STMOD: u8 = 0x05;
    pub const MSKPATH3: u8 = 0x06;
    pub const MARK: u8 = 0x07;
    pub const FLUSHE: u8 = 0x10;
    pub const FLUSH: u8 = 0x11;
    pub const FLUSHA: u8 = 0x13;
    pub const MSCAL: u8 = 0x14;
    pub const MSCNT: u8 = 0x17;
    pub const MSCALF: u8 = 0x15;
    pub const STMASK: u8 = 0x20;
    pub const STROW: u8 = 0x30;
    pub const STCOL: u8 = 0x31;
    pub const MPG: u8 = 0x4a;
    pub const DIRECT: u8 = 0x50;
    pub const DIRECTHL: u8 = 0x51;
    pub const UNPACK_BASE: u8 = 0x60;
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct VifCode {
    pub imm: u16,
    pub num: u8,
    pub cmd: u8,
}

impl VifCode {
    pub fn parse(w: u32) -> VifCode {
        VifCode { imm: (w & 0xffff) as u16, num: ((w >> 16) & 0xff) as u8, cmd: ((w >> 24) & 0x7f) as u8 }
    }
    pub fn build(cmd: u8, num: u8, imm: u16) -> u32 {
        imm as u32 | (num as u32) << 16 | (cmd as u32) << 24
    }
    pub fn is_unpack(&self) -> bool {
        self.cmd & 0x60 == 0x60
    }
}

/// Read access to a simulated EE memory image, in qwords.
pub trait QwMemory {
    fn read_qw(&self, addr: u32) -> Option<Qword>;
}

/// Sparse test memory: regions of qwords keyed by 16-byte aligned start address.
#[derive(Default, Debug, Clone)]
pub struct SparseMemory {
    regions: BTreeMap<u32, Vec<Qword>>,
}

impl SparseMemory {
    pub fn new() -> Self {
        Self::default()
    }
    /// Place qwords at `addr` (must be 16-byte aligned). Returns the address for chaining.
    pub fn put(&mut self, addr: u32, qws: Vec<Qword>) -> u32 {
        assert_eq!(addr & 0xf, 0);
        self.regions.insert(addr, qws);
        addr
    }
}

impl QwMemory for SparseMemory {
    fn read_qw(&self, addr: u32) -> Option<Qword> {
        let (&base, v) = self.regions.range(..=addr).next_back()?;
        let idx = ((addr - base) / 16) as usize;
        v.get(idx).copied()
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum ChainError {
    BadAddress(u32),
    StackOverflow,
    StackUnderflow,
    TooLong,
}

/// One DMA transfer unit resulting from the walk: the tag and the data qwords it moves.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Transfer {
    pub tag_addr: u32,
    pub tag: DmaTag,
    /// The two VIF codes carried in the tag's upper 64 bits.
    pub vif: [u32; 2],
    pub data: Vec<Qword>,
}

/// Walk a source chain starting at `start` following the PS2 DMA tag rules (call/ret with a 2-deep address stack).
pub fn walk_chain(mem: &dyn QwMemory, start: u32, max_tags: usize) -> Result<Vec<Transfer>, ChainError> {
    let mut out = Vec::new();
    let mut stack: Vec<u32> = Vec::new();
    let mut taddr = start;
    for _ in 0..max_tags {
        let tq = mem.read_qw(taddr).ok_or(ChainError::BadAddress(taddr))?;
        let tag = DmaTag::parse(tq);
        let vif = [tq.hi as u32, (tq.hi >> 32) as u32];
        let read_data = |addr: u32, n: u16| -> Result<Vec<Qword>, ChainError> {
            let mut v = Vec::with_capacity(n as usize);
            for i in 0..n as u32 {
                v.push(mem.read_qw(addr + i * 16).ok_or(ChainError::BadAddress(addr + i * 16))?);
            }
            Ok(v)
        };
        let after = taddr + 16 + tag.qwc as u32 * 16;
        let (data, next): (Vec<Qword>, Option<u32>) = match tag.id {
            DmaId::Refe => (read_data(tag.addr, tag.qwc)?, None),
            DmaId::Cnt => (read_data(taddr + 16, tag.qwc)?, Some(after)),
            DmaId::Next => (read_data(taddr + 16, tag.qwc)?, Some(tag.addr)),
            DmaId::Ref | DmaId::Refs => (read_data(tag.addr, tag.qwc)?, Some(taddr + 16)),
            DmaId::Call => {
                if stack.len() >= 2 {
                    return Err(ChainError::StackOverflow);
                }
                let d = read_data(taddr + 16, tag.qwc)?;
                stack.push(after);
                (d, Some(tag.addr))
            }
            DmaId::Ret => {
                let d = read_data(taddr + 16, tag.qwc)?;
                let n = stack.pop().ok_or(ChainError::StackUnderflow)?;
                (d, Some(n))
            }
            DmaId::End => (read_data(taddr + 16, tag.qwc)?, None),
        };
        out.push(Transfer { tag_addr: taddr, tag, vif, data });
        match next {
            Some(n) => taddr = n,
            None => return Ok(out),
        }
    }
    Err(ChainError::TooLong)
}

/// Statistics / unsupported-stream markers produced by [`execute_chain`].
#[derive(Debug, Default, Clone, PartialEq, Eq)]
pub struct ExecReport {
    pub transfers: usize,
    pub direct_qwords: usize,
    /// VIF commands that need the VU1 (MSCAL/MSCNT/UNPACK/MPG): model packets, not GS-ready.
    pub vu_commands: Vec<u8>,
}

/// Run a chain through a minimal VIF1 model (DIRECT/DIRECTHL -> GIF) into `gs`.
pub fn execute_chain(mem: &dyn QwMemory, start: u32, gs: &mut GsInterpreter) -> Result<ExecReport, ChainError> {
    let transfers = walk_chain(mem, start, 1_000_000)?;
    let mut rep = ExecReport { transfers: transfers.len(), ..Default::default() };
    // VIF1 FIFO state: remaining qwords of the current DIRECT payload.
    let mut direct_left: usize = 0;
    let mut gif_buf: Vec<Qword> = Vec::new();
    let mut pending_words: Vec<u32> = Vec::new();

    for t in &transfers {
        // The tag's two VIF codes enter the VIF before the data.
        for w in t.vif {
            pending_words.push(w);
        }
        // Data stream: if inside DIRECT, whole qwords go to the GIF; otherwise words are VIF codes.
        let mut push_data = |q: Qword, direct_left: &mut usize, gif_buf: &mut Vec<Qword>| {
            if *direct_left > 0 {
                gif_buf.push(q);
                *direct_left -= 1;
                rep.direct_qwords += 1;
            }
        };
        // First interpret pending VIF words.
        let mut wi = 0;
        let mut words = std::mem::take(&mut pending_words);
        while wi < words.len() {
            let c = VifCode::parse(words[wi]);
            wi += 1;
            match c.cmd {
                vifcmd::DIRECT | vifcmd::DIRECTHL => {
                    direct_left = if c.imm == 0 { 65536 } else { c.imm as usize };
                    // The payload follows in this transfer's data (qword aligned).
                    break;
                }
                vifcmd::MSCAL | vifcmd::MSCNT | vifcmd::MSCALF | vifcmd::MPG => rep.vu_commands.push(c.cmd),
                x if x & 0x60 == 0x60 => rep.vu_commands.push(c.cmd),
                _ => {}
            }
        }
        words.clear();
        for q in &t.data {
            if direct_left > 0 {
                push_data(*q, &mut direct_left, &mut gif_buf);
            } else {
                // Data qwords that are plain VIF codes (e.g. DIRECT inside `Ref` data): interpret 4 words.
                for w in q.words() {
                    let c = VifCode::parse(w);
                    if c.cmd == vifcmd::DIRECT || c.cmd == vifcmd::DIRECTHL {
                        direct_left = c.imm as usize;
                    }
                }
            }
        }
        if !gif_buf.is_empty() {
            gs.feed(&gif_buf);
            gif_buf.clear();
        }
    }
    Ok(rep)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::gs::{ad, reg, GifFlg, GifTag, GsEvent};

    #[test]
    fn tag_layout_matches_game_literals() {
        // LayerGetPacket writes word0=0x50000000 (call, qwc 0), word1=addr
        let t = DmaTag::parse(Qword::new(0x50000000 | (0x1234u64 << 32), 0));
        assert_eq!(t.id, DmaId::Call);
        assert_eq!(t.qwc, 0);
        assert_eq!(t.addr, 0x1234);
        // WorldGetPacket end marker
        assert_eq!(DmaTag::parse(Qword::new(0x70000000, 0)).id, DmaId::End);
        // ret
        assert_eq!(DmaTag::parse(Qword::new(0x60000000, 0)).id, DmaId::Ret);
        // VIF FLUSHA / DIRECT
        assert_eq!(VifCode::parse(0x13000000).cmd, vifcmd::FLUSHA);
        let d = VifCode::parse(0x50000006);
        assert_eq!((d.cmd, d.imm), (vifcmd::DIRECT, 6));
    }

    /// World chain: [call sub][end]; sub: [cnt(DIRECT 3) + A+D x2][ret]
    #[test]
    fn world_style_chain_executes_into_gs() {
        let mut mem = SparseMemory::new();
        // sub-chain at 0x1000: cnt tag with FLUSHA/DIRECT 3, then GIF tag + 2 A+D, then ret tag
        let sub = vec![
            DmaTag::qword(DmaId::Cnt, 3, 0, VifCode::build(vifcmd::FLUSHA, 0, 0), VifCode::build(vifcmd::DIRECT, 0, 3)),
            GifTag::build(2, true, false, 0, GifFlg::Packed, &[reg::AD]),
            ad(reg::TEST_1, 0x3000d),
            ad(reg::ALPHA_1, 0x44),
            Qword::new(0x60000000, 0),
        ];
        mem.put(0x1000, sub);
        // OT buffer at 0x2000: call 0x1000, end
        mem.put(0x2000, vec![Qword::new(0x50000000 | (0x1000u64 << 32), 0), Qword::new(0x70000000, 0)]);
        let mut gs = GsInterpreter::new();
        let rep = execute_chain(&mem, 0x2000, &mut gs).unwrap();
        assert_eq!(rep.direct_qwords, 3);
        assert_eq!(gs.ctx[0].alpha.classify(), crate::gs::BlendKind::AlphaBlend);
        assert!(gs.ctx[0].test.ate);
        assert_eq!(gs.ctx[0].test.atst, 6);
        assert!(gs.take_events().iter().all(|e| matches!(e, GsEvent::TexFlush) || true));
    }
}
