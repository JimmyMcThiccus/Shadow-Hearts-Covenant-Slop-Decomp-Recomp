//! Real-data tests: every SDH bank of both discs must parse, decode and run through the sequence grammar; the stream BGM files must
//! decode.  Skipped (with a message) when the disc folders are not available.

use sh2_audio::stream::{SsvHeader, StreamPlayer};
use sh2_audio::synth::{validate_se_stream, validate_sequence};
use sh2_audio::Bank;
use sh2_core::fileio::Disc;

const JP: &str = "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)";
const US: &str = "/Volumes/work/Sh2 Decomp/Shadow Hearts - Covenant (USA) (Disc 1)-1";

fn disc(var: &str, fallback: &str) -> Option<Disc> {
    let dir = std::env::var(var).unwrap_or_else(|_| fallback.to_string());
    match Disc::open(&dir) {
        Ok(d) => Some(d),
        Err(e) => {
            eprintln!("skipping: {var} ({dir}) not available: {e}");
            None
        }
    }
}

#[derive(Default, Debug)]
struct Totals {
    files: usize,
    embedded: usize,
    raw_wd: usize,
    banks: usize,
    waves: usize,
    samples: usize,
    programs: usize,
    tones: usize,
    sequences: usize,
    se_streams: usize,
    se_ids: usize,
    seq_events: usize,
    /// SE map entries whose FQ record / variant / sequence does not exist (the driver would fail to start them)
    dangling_se: usize,
}

fn check_bank(name: &str, bytes: &[u8], t: &mut Totals) {
    let b = Bank::parse(bytes).unwrap_or_else(|e| panic!("{name}: {e}"));
    t.banks += 1;
    t.waves += b.waves.len();
    t.programs += b.programs.len();
    t.tones += b.tones.len();
    assert!(b.has(b"WV") && b.has(b"WD"), "{name}: bank without wave table/data: {:?}", b.tags);
    for (i, w) in b.waves.iter().enumerate() {
        assert!(w.rate >= 4000 && w.rate <= 96000, "{name}: wave {i} rate {}", w.rate);
        t.samples += w.pcm.len();
    }
    // every tone must reference an existing wave, every split an existing sample set, every set existing tones
    for (pi, p) in b.programs.iter().enumerate() {
        for s in &p.splits {
            assert!((s.sample_set as usize) < b.sample_sets.len(), "{name}: prog {pi} split -> set {}", s.sample_set);
        }
    }
    for set in &b.sample_sets {
        for &ti in &set.tones {
            assert!((ti as usize) < b.tones.len(), "{name}: tone {ti}/{}", b.tones.len());
        }
    }
    for (i, tn) in b.tones.iter().enumerate() {
        if tn.vol() != 0 {
            assert!((tn.wave() as usize) < b.waves.len(), "{name}: tone {i} wave {}/{}", tn.wave(), b.waves.len());
        }
    }
    for (i, sq) in b.sequences.iter().enumerate() {
        let r = validate_sequence(sq).unwrap_or_else(|e| panic!("{name}: sequence {i}: {e}"));
        t.sequences += 1;
        t.seq_events += r.events;
    }
    for r in b.se_records.iter().flatten() {
        for (vi, st) in r.streams.iter().enumerate() {
            if st.events.is_empty() {
                continue;
            }
            validate_se_stream(&st.events).unwrap_or_else(|e| panic!("{name}: SE stream {vi}: {e}"));
            t.se_streams += 1;
        }
    }
    for &(id, _) in &b.se_map {
        t.se_ids += 1;
        let ok = match b.se_target(id) {
            Some(sh2_audio::sdh::SeTarget::Sequence(n)) => (n as usize) < b.sequences.len(),
            Some(sh2_audio::sdh::SeTarget::Record { record, variant }) => {
                b.se_records.get(record as usize).and_then(|r| r.as_ref()).map(|r| (variant as usize) < r.streams.len()).unwrap_or(false)
            }
            None => false,
        };
        if !ok {
            t.dangling_se += 1;
            eprintln!("{name}: SE {id:#x} has no target (data issue, the driver rejects it too)");
        }
    }
}

fn scan_disc(d: &Disc, label: &str) -> Totals {
    let mut t = Totals::default();
    for (_c, files) in d.listing() {
        for (path, _loc) in files {
            let up = path.to_uppercase();
            let is_snd = up.ends_with(".SSE") || up.ends_with(".SSQ");
            let is_efd = up.ends_with(".EFD");
            if !is_snd && !is_efd {
                continue;
            }
            let bytes = d.read(&path).unwrap();
            if is_snd {
                t.files += 1;
                if bytes.starts_with(b"SDRH") {
                    check_bank(&path, &bytes, &mut t);
                } else if bytes.starts_with(b"WD") {
                    t.raw_wd += 1; // headerless extra wave data (AutoLoad's second argument)
                } else {
                    panic!("{label}: {path}: unknown sound file head {:02x?}", &bytes[..8]);
                }
            } else {
                // effect packages carry embedded SDH banks at 16-byte aligned offsets
                let mut o = 0;
                while o + 4 <= bytes.len() {
                    if &bytes[o..o + 4] == b"SDRH" {
                        if let Ok(b) = Bank::parse_opts(&bytes[o..], false) {
                            let _ = b;
                            check_bank(&format!("{path}+{o:#x}"), &bytes[o..], &mut t);
                            t.embedded += 1;
                        }
                    }
                    o += 16;
                }
            }
        }
    }
    eprintln!("{label}: {t:?}");
    t
}

#[test]
fn every_sdh_bank_on_the_jp_disc_parses() {
    let Some(d) = disc("SH2_DISC_DIR", JP) else { return };
    let t = scan_disc(&d, "JP");
    assert!(t.banks > 300, "{t:?}");
    assert!(t.embedded >= 100, "EFFECT.PKB carries 104 embedded banks: {t:?}");
    assert!(t.sequences > 100 && t.se_ids > 100);
    assert!(t.dangling_se * 100 < t.se_ids, "{t:?}");
}

#[test]
fn every_sdh_bank_on_the_us_disc_parses() {
    let Some(d) = disc("SH2_US_DISC_DIR", US) else { return };
    let t = scan_disc(&d, "US");
    assert!(t.banks > 100, "{t:?}");
    assert!(t.dangling_se * 100 < t.se_ids, "{t:?}");
}

#[test]
fn stream_bgm_files_decode() {
    for (var, fallback) in [("SH2_DISC_DIR", JP), ("SH2_US_DISC_DIR", US)] {
        let Some(d) = disc(var, fallback) else { continue };
        let mut n = 0;
        for (_c, files) in d.listing() {
            for (path, _) in files {
                if !path.to_uppercase().ends_with(".SSV") {
                    continue;
                }
                let bytes = d.read(&path).unwrap();
                let h = SsvHeader::parse(&bytes).unwrap_or_else(|e| panic!("{path}: {e}"));
                assert_eq!(h.sample_rate, 48000, "{path}");
                assert_eq!(h.channels(), 2, "{path}");
                assert_eq!(h.interleave, 0x800, "{path}");
                assert_eq!(h.file_size, bytes.len(), "{path}: header size field");
                let p = StreamPlayer::from_ssv(&bytes).unwrap();
                // decoded frames: whole 0x800 rounds of both channels
                let rounds = (bytes.len() - 0x20) / (2 * 0x800);
                assert_eq!(p.dec.frames(), rounds * 3584, "{path}");
                assert!(p.end.unwrap() <= p.dec.frames());
                // not silent
                let peak = p.dec.pcm.iter().step_by(97).map(|s| s.unsigned_abs()).max().unwrap();
                assert!(peak > 1000, "{path}: peak {peak}");
                n += 1;
            }
        }
        eprintln!("{var}: {n} stream BGM files");
        assert!(n >= 1);
    }
}

/// LSD `PCMS` tracks (cutscene audio) are the same interleaved SPU ADPCM as the stream BGM: check that the 0x800 interleave gives a
/// continuous waveform across the chunk joins.
#[test]
fn lsd_pcms_tracks_decode() {
    use sh2_script::lsd::LsdFile;
    for (var, fallback) in [("SH2_DISC_DIR", JP), ("SH2_US_DISC_DIR", US)] {
        let Some(d) = disc(var, fallback) else { continue };
        let mut tracks = 0;
        let mut corr_sum = 0f64;
        for (_c, files) in d.listing() {
            for (path, loc) in files {
                if !path.to_uppercase().ends_with(".LSD") || loc.size > 40_000_000 {
                    continue;
                }
                let bytes = d.read(&path).unwrap();
                let lsd = LsdFile::parse(&bytes).unwrap();
                for (ti, t) in lsd.tracks.iter().enumerate() {
                    if &t.tag != b"PCMS" {
                        continue;
                    }
                    let mut data = Vec::new();
                    for p in lsd.packets().filter(|p| p.track as usize == ti) {
                        data.extend_from_slice(p.payload);
                        if data.len() > 4_000_000 {
                            break;
                        }
                    }
                    let p = StreamPlayer::from_pcms(&t.raw, &data).unwrap();
                    assert_eq!(p.rate, 48000, "{path}");
                    let frames = p.dec.frames();
                    assert!(frames > 100_000, "{path}: {frames}");
                    // with the right interleave the two channels of a stereo mix are strongly correlated (wrong chunk sizes give ~0)
                    let pcm = &p.dec.pcm;
                    let (mut sab, mut saa, mut sbb) = (0f64, 0f64, 0f64);
                    for f in 0..frames {
                        let (l, r) = (pcm[f * 2] as f64, pcm[f * 2 + 1] as f64);
                        sab += l * r;
                        saa += l * l;
                        sbb += r * r;
                    }
                    let corr = sab / (saa * sbb).sqrt().max(1.0);
                    let peak = pcm.iter().step_by(31).map(|s| s.unsigned_abs()).max().unwrap();
                    eprintln!("{path} track {ti}: {frames} frames, L/R correlation {corr:.2}, peak {peak}");
                    assert!(peak > 500, "{path}: silent PCMS");
                    assert!(corr > 0.0, "{path}: L/R correlation {corr} - wrong interleave?");
                    corr_sum += corr;
                    tracks += 1;
                }
            }
        }
        eprintln!("{var}: {tracks} PCMS tracks, mean L/R correlation {:.2}", corr_sum / tracks.max(1) as f64);
        assert!(tracks >= 1);
        assert!(corr_sum / tracks as f64 > 0.5, "the 0x800 interleave must be right on average");
    }
}
