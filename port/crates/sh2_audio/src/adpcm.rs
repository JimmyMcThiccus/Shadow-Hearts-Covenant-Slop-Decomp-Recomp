//! PS2 SPU / PS1 SPU ADPCM ("VAG") decoder.
//!
//! A block is 16 bytes: `byte0 = (filter << 4) | shift`, `byte1 = flags`, then 14 bytes holding 28 four-bit samples
//! (low nibble first).  Flags: bit0 = loop end / stop, bit1 = repeat (jump to the loop-start address), bit2 = loop start.
//! This is what the SPU2 hardware decodes for the game's `WD` wave data and for the stream BGM (`*.SSV`) files.

/// Prediction filter coefficients `(f0, f1)` in 1/64 units.
pub const FILTER: [(i32, i32); 5] = [(0, 0), (60, 0), (115, -52), (98, -55), (122, -60)];

pub const BLOCK_BYTES: usize = 16;
pub const BLOCK_SAMPLES: usize = 28;

pub const FLAG_END: u8 = 1;
pub const FLAG_REPEAT: u8 = 2;
pub const FLAG_LOOP_START: u8 = 4;

/// Decoder history (the two previous output samples).
#[derive(Debug, Clone, Copy, Default, PartialEq, Eq)]
pub struct AdpcmState {
    pub s1: i32,
    pub s2: i32,
}

/// Decode one 16-byte block; returns the block's flag byte.
pub fn decode_block(block: &[u8], st: &mut AdpcmState, out: &mut [i16; BLOCK_SAMPLES]) -> u8 {
    let shift = {
        let s = (block[0] & 0xf) as u32;
        if s > 12 {
            9
        } else {
            s
        }
    };
    let filter = (((block[0] >> 4) & 7) as usize).min(4);
    let (f0, f1) = FILTER[filter];
    let mut n = 0;
    for j in 0..14 {
        let byte = block[2 + j];
        for nib in [byte & 0xf, byte >> 4] {
            // sign-extend the nibble into the top of an i16, then shift down
            let v = (((nib as i32) << 12) as i16 as i32) >> shift;
            let predicted = (st.s1 * f0 + st.s2 * f1 + 32) >> 6;
            let s = (v + predicted).clamp(-32768, 32767);
            st.s2 = st.s1;
            st.s1 = s;
            out[n] = s as i16;
            n += 1;
        }
    }
    block[1]
}

/// Result of decoding a self-contained sample (one `WV` wave).
#[derive(Debug, Clone, Default)]
pub struct Decoded {
    pub pcm: Vec<i16>,
    /// sample index the voice jumps to at the end of the sample (`Some` for looping samples)
    pub loop_start: Option<usize>,
    /// true when the final block carries the repeat flag (the sample loops until key-off)
    pub looping: bool,
}

/// Decode a single sample: stops after the first block carrying the end flag.  Samples without an end flag run to the end
/// of `data`.
pub fn decode_sample(data: &[u8]) -> Decoded {
    let mut st = AdpcmState::default();
    let mut pcm = Vec::with_capacity(data.len() / 16 * 28);
    let mut loop_start = None;
    let mut looping = false;
    let mut buf = [0i16; BLOCK_SAMPLES];
    for blk in data.chunks_exact(BLOCK_BYTES) {
        let flags = decode_block(blk, &mut st, &mut buf);
        if flags & FLAG_LOOP_START != 0 && loop_start.is_none() {
            loop_start = Some(pcm.len());
        }
        pcm.extend_from_slice(&buf);
        if flags & FLAG_END != 0 {
            if flags & FLAG_REPEAT != 0 {
                looping = true;
                if loop_start.is_none() {
                    loop_start = Some(0);
                }
            }
            break;
        }
    }
    if !looping {
        loop_start = None;
    }
    Decoded { pcm, loop_start, looping }
}

/// Decode a continuous ADPCM stream (flags ignored) with a running history; used for the interleaved stream BGM.
pub fn decode_stream(data: &[u8], st: &mut AdpcmState, out: &mut Vec<i16>) {
    let mut buf = [0i16; BLOCK_SAMPLES];
    for blk in data.chunks_exact(BLOCK_BYTES) {
        decode_block(blk, st, &mut buf);
        out.extend_from_slice(&buf);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn block(filter: u8, shift: u8, flags: u8, nibbles: &[u8; 28]) -> [u8; 16] {
        let mut b = [0u8; 16];
        b[0] = (filter << 4) | shift;
        b[1] = flags;
        for j in 0..14 {
            b[2 + j] = (nibbles[2 * j] & 0xf) | (nibbles[2 * j + 1] << 4);
        }
        b
    }

    #[test]
    fn silent_block_is_silent() {
        let mut st = AdpcmState::default();
        let mut out = [1i16; 28];
        let f = decode_block(&[0u8; 16], &mut st, &mut out);
        assert_eq!(f, 0);
        assert!(out.iter().all(|&s| s == 0));
    }

    #[test]
    fn filter0_shift12_returns_the_signed_nibbles() {
        // filter 0, shift 12: sample = (nibble << 12) >> 12 = signed nibble
        let mut nib = [0u8; 28];
        for (i, n) in nib.iter_mut().enumerate() {
            *n = (i % 16) as u8;
        }
        let b = block(0, 12, 0, &nib);
        let mut st = AdpcmState::default();
        let mut out = [0i16; 28];
        decode_block(&b, &mut st, &mut out);
        let expect: Vec<i16> = (0..28).map(|i| { let n = (i % 16) as i16; if n >= 8 { n - 16 } else { n } }).collect();
        assert_eq!(&out[..], &expect[..]);
        assert_eq!(st.s1, expect[27] as i32);
        assert_eq!(st.s2, expect[26] as i32);
    }

    #[test]
    fn shift0_scales_to_full_range_and_filter1_predicts() {
        // shift 0: sample = nibble << 12 (sign extended) -> 0x7000 for nibble 7, -0x8000 for nibble 8
        let mut nib = [0u8; 28];
        nib[0] = 7;
        nib[1] = 8;
        nib[2] = 0xf;
        let b = block(0, 0, 0, &nib);
        let mut st = AdpcmState::default();
        let mut out = [0i16; 28];
        decode_block(&b, &mut st, &mut out);
        assert_eq!(&out[..4], &[0x7000, -0x8000, -0x1000, 0]);

        // filter 1 (f0 = 60/64): after a sample of 1000, a zero nibble decays by 60/64 (rounded: (1000*60+32)>>6 = 938)
        let mut st = AdpcmState { s1: 1000, s2: 0 };
        let b = block(1, 12, 0, &[0u8; 28]);
        decode_block(&b, &mut st, &mut out);
        assert_eq!(out[0], 938);
        assert_eq!(out[1], ((938 * 60 + 32) >> 6) as i16);
        // filter 2 uses both history taps: (115*s1 - 52*s2 + 32) >> 6
        let mut st = AdpcmState { s1: 640, s2: 128 };
        let b = block(2, 12, 0, &[0u8; 28]);
        decode_block(&b, &mut st, &mut out);
        assert_eq!(out[0] as i32, (640 * 115 - 128 * 52 + 32) >> 6);
    }

    #[test]
    fn output_is_clamped() {
        let mut st = AdpcmState { s1: 32767, s2: 0 };
        let mut nib = [0u8; 28];
        nib[0] = 7;
        let b = block(1, 0, 0, &nib);
        let mut out = [0i16; 28];
        decode_block(&b, &mut st, &mut out);
        assert_eq!(out[0], 32767);
    }

    #[test]
    fn sample_decoding_honours_loop_flags() {
        let z = [0u8; 28];
        let mut data = Vec::new();
        data.extend_from_slice(&block(0, 12, 0, &z));
        data.extend_from_slice(&block(0, 12, FLAG_LOOP_START | FLAG_REPEAT, &z)); // loop start: sample 56
        data.extend_from_slice(&block(0, 12, FLAG_END | FLAG_REPEAT, &z)); // end + repeat
        data.extend_from_slice(&block(0, 12, 0, &z)); // never decoded
        let d = decode_sample(&data);
        assert_eq!(d.pcm.len(), 3 * 28 - 28 + 28); // 3 blocks
        assert_eq!(d.pcm.len(), 84);
        assert!(d.looping);
        assert_eq!(d.loop_start, Some(28));

        let mut one = Vec::new();
        one.extend_from_slice(&block(0, 12, 0, &z));
        one.extend_from_slice(&block(0, 12, FLAG_END, &z));
        let d = decode_sample(&one);
        assert!(!d.looping);
        assert_eq!(d.loop_start, None);
        assert_eq!(d.pcm.len(), 56);
    }
}
