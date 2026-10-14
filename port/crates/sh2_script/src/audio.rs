//! Audio protocol layer: `Sdrv` ↔ `SDRV_IOP.IRX` command words, SDH sound banks, stream header.
//!
//! The PS2 build talks to the IOP sound driver ("Nautilus" sdrv) through SIF commands.  A port does not need the IOP;
//! it needs (a) the *data formats* (SDH banks, stream files) and (b) the *semantic API* the game code uses (`SoundBackend`),
//! which a rodio/kira based backend can implement.  The constants below document the wire protocol (JP `SdrvEE`).

// ---------------------------------------------------------------------------------------------------------------------
// Wire protocol
// ---------------------------------------------------------------------------------------------------------------------

/// Low byte of the SIF command word (`pkt+0x0c`) – IRX `sdrv_drvCall` jump table, JP `SdrvEE::Cmd*`.
pub mod major {
    pub const STATUS: u8 = 0;
    pub const INIT: u8 = 1;
    pub const LOAD_SDH_ALLOC: u8 = 2;
    pub const LOAD_SDH_DATA: u8 = 3;
    pub const RELEASE_SDH: u8 = 4;
    pub const WAVE_INFO: u8 = 5;
    pub const TRANS_WAVE: u8 = 6;
    pub const EE_STREAM: u8 = 7;
    pub const SET_MODE: u8 = 8;
    pub const SE: u8 = 9;
    pub const BGM: u8 = 10;
    pub const PAUSE: u8 = 11;
    pub const RESET: u8 = 12;
    pub const REPORT: u8 = 14;
    pub const TEST: u8 = 15;
}
/// `sub` byte (bits 8-15) for [`major::SE`].
pub mod se_sub {
    pub const PLAY: u8 = 0;
    pub const PARAM: u8 = 1;
    pub const STAT: u8 = 2;
    pub const RELEASE: u8 = 3;
}
/// `sub` byte for [`major::BGM`].
pub mod bgm_sub {
    pub const PLAY: u8 = 0;
    pub const PARAM: u8 = 2;
    pub const STAT: u8 = 3;
    pub const STOP: u8 = 4;
    pub const RELEASE: u8 = 5;
}
/// `sub` byte for [`major::EE_STREAM`] (`sdrv_eeStreamSub`).
pub mod stream_sub {
    pub const CREATE_CHANNEL: u8 = 0x02;
    pub const SET_PARAM: u8 = 0x03;
    pub const GET_STAT: u8 = 0x04;
    pub const START: u8 = 0x09;
    pub const PAUSE: u8 = 0x0b;
    pub const GET_WRITE_STAT: u8 = 0x10;
    pub const WRITE_DATA: u8 = 0x11;
    pub const AUTO_START: u8 = 0x12;
    pub const STOP_END: u8 = 0x13;
    pub const STOP: u8 = 0x14;
    pub const RELEASE_CHANNEL: u8 = 0x15;
}
/// IOP → EE reply codes (`SdrvEE::Receive`, low byte of the reply command word).
pub mod reply {
    pub const RESULT_SHORT: u8 = 0;
    pub const RESULT_WORDS: u8 = 1;
    pub const LOAD_SDH: u8 = 2;
    pub const RELEASE_OR_TRANS: u8 = 4;
    pub const DMA_BUFFERS: u8 = 0x10;
    pub const WAVE_BUF_FREE: u8 = 0x11;
    pub const SE_FINISHED: u8 = 0x12;
    pub const BGM_FINISHED: u8 = 0x13;
    pub const CALLBACK: u8 = 0x14;
    pub const LOG: u8 = 0x17;
}

pub const fn cmd_word(major: u8, sub: u8, arg16: u16) -> u32 {
    (major as u32) | ((sub as u32) << 8) | ((arg16 as u32) << 16)
}

/// `Sdrv::SetMode` mode bits (`SdrvEE::SetMode` JP 0x003747b0).  `mode & 0xf` = output (2 = Dolby/Pro-Logic?), bit4 = …, bit5 = …;
/// bits 12-15 select which groups of the word are valid (`&1` output, `&2` bit4, `&4` low nibble of byte 1, `&8` bit5).
#[derive(Debug, Clone, Copy, Default, PartialEq, Eq)]
pub struct SoundMode(pub u32);

/// `_SeParam` (12 bytes, `Sdrv::InitSeParam` JP 0x00372940).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct SeParam {
    pub volume: u8, // 0x7f
    pub pan: u8,    // 0x40 = centre
    pub resv: u16,
    pub pitch: u16, // 1000 = 1.0
    /// bits 0-2: extra 32-bit word present (sent in `pkt+0x20`)
    pub flags: u16,
    pub user: u32,
}
impl Default for SeParam {
    fn default() -> Self {
        SeParam { volume: 0x7f, pan: 0x40, resv: 0, pitch: 1000, flags: 0, user: 0 }
    }
}
impl SeParam {
    pub fn to_bytes(&self) -> [u8; 12] {
        let mut b = [0u8; 12];
        b[0] = self.volume;
        b[1] = self.pan;
        b[2..4].copy_from_slice(&self.resv.to_le_bytes());
        b[4..6].copy_from_slice(&self.pitch.to_le_bytes());
        b[6..8].copy_from_slice(&self.flags.to_le_bytes());
        b[8..12].copy_from_slice(&self.user.to_le_bytes());
        b
    }
}
/// `_BgmParam` (16 bytes, `Sdrv::InitBgmParam` JP 0x00373110): like `SeParam` + `extra` word.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct BgmParam {
    pub base: SeParam,
    pub extra: u32,
}
impl Default for BgmParam {
    fn default() -> Self {
        BgmParam { base: SeParam::default(), extra: 0 }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// SDH ("SDRH") sound banks
// ---------------------------------------------------------------------------------------------------------------------

#[derive(Debug, Clone)]
pub struct SdhBlock<'a> {
    pub tag: [u8; 2],
    pub kind: u16,
    pub offset: usize,
    pub size_units: u16,
    pub bytes: &'a [u8],
}

#[derive(Debug, thiserror::Error, PartialEq, Eq)]
pub enum SdhError {
    #[error("not an SDRH file")]
    BadMagic,
    #[error("truncated / corrupt block chain at 0x{0:x}")]
    Corrupt(usize),
}

/// A parsed SDH container: blocks `WV FT PG SS FE FQ SG WD` (see notes/E/audio.md §4 and notes/integration/audio.md; the full bank
/// parser, ADPCM decoder and synth live in the `sh2_audio` crate).
#[derive(Debug, Clone)]
pub struct Sdh<'a> {
    pub version: u32,
    pub total_len: usize,
    pub blocks: Vec<SdhBlock<'a>>,
}

impl<'a> Sdh<'a> {
    // JP: SdhFindBlock / SdhNextBlock, SdrvEE::LoadSDH 0x00373f30
    pub fn parse(d: &'a [u8]) -> Result<Self, SdhError> {
        if d.get(0..4) != Some(b"SDRH") {
            return Err(SdhError::BadMagic);
        }
        let ver = u32::from_le_bytes(d[4..8].try_into().unwrap());
        let w = u32::from_le_bytes(d[8..12].try_into().unwrap());
        let start = (w & 0xff) as usize * 16;
        let total = (w >> 8) as usize * 16;
        let end = total.min(d.len());
        let mut p = start;
        let mut blocks = Vec::new();
        while p + 8 <= end {
            // sdrv_NextBlock: the `WD` wave-data block stores its length as u32 units, every other block as u16
            let units = if &d[p..p + 2] == b"WD" { u32::from_le_bytes([d[p + 4], d[p + 5], d[p + 6], d[p + 7]]) as usize } else { u16::from_le_bytes([d[p + 4], d[p + 5]]) as usize };
            if units == 0 {
                return Err(SdhError::Corrupt(p));
            }
            let len = units * 16;
            let blk_end = (p + len).min(end);
            blocks.push(SdhBlock {
                tag: [d[p], d[p + 1]],
                kind: u16::from_le_bytes([d[p + 2], d[p + 3]]),
                offset: p,
                size_units: units.min(u16::MAX as usize) as u16,
                bytes: &d[p..blk_end],
            });
            p += len;
        }
        Ok(Sdh { version: ver, total_len: total, blocks })
    }
    pub fn find(&self, tag: &[u8; 2]) -> Option<&SdhBlock<'a>> {
        self.blocks.iter().find(|b| &b.tag == tag)
    }
}

/// Entry of the `WV` wave table (6 bytes): `{u24 offset, u8 flags, u16 sample_rate}` (offset into the `WD` data, which starts 0x10 bytes
/// into the `WD` block).  Corrected from the first pass, which read the table 3 bytes late; see `SetWaveInfo` in SDRV_IOP.IRX.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct WaveEntry {
    pub flags: u8,
    pub sample_rate: u16,
    pub offset: u32,
}
/// Decode the wave table of a `WV` block (header: `u16 hdr_units` at +2 (= 2, table at +0x20), `u16 count` at +8).
pub fn wave_table(wv: &SdhBlock<'_>) -> Vec<WaveEntry> {
    let b = wv.bytes;
    let count = if b.len() >= 10 { u16::from_le_bytes([b[8], b[9]]) as usize } else { 0 };
    let mut v = Vec::new();
    let start = (wv.kind as usize * 16).min(b.len());
    for i in 0..count {
        let o = start + i * 6;
        if o + 6 > b.len() {
            break;
        }
        v.push(WaveEntry { offset: u32::from_le_bytes([b[o], b[o + 1], b[o + 2], 0]), flags: b[o + 3], sample_rate: u16::from_le_bytes([b[o + 4], b[o + 5]]) });
    }
    v
}

// ---------------------------------------------------------------------------------------------------------------------
// Streams
// ---------------------------------------------------------------------------------------------------------------------

/// LSD `PCMS` / `DLBY` track header body (`BGMServerHandler::Open`, JP 0x00389880): offsets in the 0x40-byte header.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct PcmsHeader {
    /// +0x20 low nibble: 0 → type 2, ≠0 → type 3
    pub kind: u8,
    pub bits: u16,
    pub channels: u16,
    pub sample_rate: u16,
}
impl PcmsHeader {
    pub fn parse(hdr: &[u8]) -> Option<Self> {
        let b = hdr.get(0x20..0x28)?;
        Some(PcmsHeader { kind: b[0], bits: u16::from_le_bytes([b[2], b[3]]), channels: u16::from_le_bytes([b[4], b[5]]), sample_rate: u16::from_le_bytes([b[6], b[7]]) })
    }
}

/// `StreamBGM` file header (first 0x20 bytes), JP `StreamBGM::PollingStream` 0x003ceaa0.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct StreamBgmHeader {
    pub data_start_units: u16,
    pub flags: u8,
    pub channels: u8,
    pub loop_end: u32,
    pub raw_0x10: u32,
}
impl StreamBgmHeader {
    pub fn parse(b: &[u8]) -> Option<Self> {
        if b.len() < 0x20 {
            return None;
        }
        Some(StreamBgmHeader {
            data_start_units: u16::from_le_bytes([b[2], b[3]]),
            flags: b[8],
            channels: b[9],
            loop_end: u32::from_le_bytes(b[0xc..0x10].try_into().ok()?),
            raw_0x10: u32::from_le_bytes(b[0x10..0x14].try_into().ok()?),
        })
    }
    /// codec nibble `(flags & 0xf) >> 2`.  Verified on the shipped `*.SSV` files: 2 = stereo SPU ADPCM interleaved in `channels * 0x200`
    /// byte chunks (the earlier guess "PCM16" was wrong).  Full decoder: `sh2_audio::stream`.
    pub fn codec(&self) -> u8 {
        (self.flags & 0xf) >> 2
    }
    /// byte `+9` is the interleave chunk in units of 0x200 bytes (4 => 0x800), not a channel count.
    pub fn interleave_bytes(&self) -> usize {
        self.channels as usize * 0x200
    }
    pub fn looped(&self) -> bool {
        self.flags & 0x10 != 0
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Backend abstraction for the port
// ---------------------------------------------------------------------------------------------------------------------

/// Handle returned by [`SoundBackend`] (mirrors the `Sdrv` request handle).
pub type SoundHandle = u32;

/// What the game's `Sdrv` facade offers; a Bevy/rodio layer implements it.
pub trait SoundBackend {
    fn load_sdh(&mut self, sdh: &[u8]) -> SoundHandle; // Sdrv::AutoLoad + LoadSDH
    fn release_sdh(&mut self, h: SoundHandle);
    fn play_se(&mut self, sdh: SoundHandle, se_id: u32, p: &SeParam) -> SoundHandle;
    fn set_se_param(&mut self, se: SoundHandle, p: &SeParam);
    fn release_se(&mut self, se: SoundHandle, fade: i32);
    fn is_se_playing(&self, se: SoundHandle) -> bool;
    fn play_bgm(&mut self, sdh: SoundHandle, bgm_id: u32, mode: u32, p: &BgmParam) -> SoundHandle;
    fn stop_bgm(&mut self, bgm: SoundHandle, fade_mode: u32);
    fn set_bgm_param(&mut self, bgm: SoundHandle, p: &BgmParam);
    fn pause(&mut self, on: bool);
    fn set_mode(&mut self, mode: SoundMode);
    // EE-fed streams (LSD PCMS, StreamBGM)
    fn stream_open(&mut self) -> SoundHandle;
    fn stream_create(&mut self, h: SoundHandle, codec: u8, channels: u8);
    fn stream_set_param(&mut self, h: SoundHandle, vol_lr: u32, pitch: u32);
    fn stream_write(&mut self, h: SoundHandle, data: &[u8]);
    fn stream_buffered(&self, h: SoundHandle) -> usize;
    fn stream_start(&mut self, h: SoundHandle);
    fn stream_stop(&mut self, h: SoundHandle, fade: bool);
    fn stream_pause(&mut self, h: SoundHandle, resume: bool);
    fn stream_close(&mut self, h: SoundHandle);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn cmd_words_match_ee_code() {
        // CmdSeParam: (flags << 16) | 0x109 ; CmdBgmParam: (flags<<16)|0x20a ; stream auto-start 0x1207 ; pause 0xb07
        assert_eq!(cmd_word(major::SE, se_sub::PARAM, 0), 0x109);
        assert_eq!(cmd_word(major::SE, se_sub::STAT, 0), 0x209);
        assert_eq!(cmd_word(major::SE, se_sub::RELEASE, 0), 0x309);
        assert_eq!(cmd_word(major::BGM, bgm_sub::PARAM, 0), 0x20a);
        assert_eq!(cmd_word(major::EE_STREAM, stream_sub::AUTO_START, 0), 0x1207);
        assert_eq!(cmd_word(major::EE_STREAM, stream_sub::STOP_END, 0), 0x1307);
        assert_eq!(cmd_word(major::EE_STREAM, stream_sub::STOP, 0), 0x1407);
        assert_eq!(cmd_word(major::EE_STREAM, stream_sub::PAUSE, 0), 0xb07);
        assert_eq!(cmd_word(major::EE_STREAM, stream_sub::RELEASE_CHANNEL, 0), 0x1507);
    }

    #[test]
    fn sdh_real_if_present() {
        let p = "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)/COMMON.PKB";
        let Ok(d) = std::fs::read(p) else { return };
        let sdh = Sdh::parse(&d[0x12f000..]).unwrap();
        let tags: Vec<String> = sdh.blocks.iter().map(|b| String::from_utf8_lossy(&b.tag).into_owned()).collect();
        assert_eq!(tags, ["WV", "FT", "PG", "SS", "FE", "FQ", "SG", "WD"]);
        assert_eq!(sdh.total_len, 0x300f0);
        let wt = wave_table(sdh.find(b"WV").unwrap());
        assert_eq!(wt.len(), 22);
        assert_eq!((wt[0].offset, wt[0].flags, wt[0].sample_rate), (0, 1, 48000));
        assert_eq!((wt[1].offset, wt[1].sample_rate), (0x1be0, 48000));
        assert!(wt.windows(2).all(|w| w[1].offset > w[0].offset));
    }
}
