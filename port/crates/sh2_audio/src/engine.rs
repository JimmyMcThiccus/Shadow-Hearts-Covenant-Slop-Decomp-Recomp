//! Output backends and the [`SoundBackend`] implementation.
//!
//! * [`Output::Device`] – real-time playback through `rodio` (cpal / CoreAudio).  The stream lives on its own thread; the mixer source pulls
//!   from the shared [`Synth`].  Only with the `playback` feature.
//! * [`Output::Null`]   – no device (CI, headless, device open failed); [`AudioEngine::pump`] advances the synth with a virtual clock so
//!   that "is the SE still playing" / finished callbacks keep working.
//! * [`Output::Wav`]    – like `Null` but every pumped sample is also appended to a WAV file ([`WavWriter`]).

use crate::sdh::Bank;
use crate::stream::StreamPlayer;
use crate::synth::{PlayId, Synth, SynthEvent, OUT_RATE};
use sh2_script::audio::{BgmParam, SeParam, SoundBackend, SoundHandle, SoundMode};
use std::io::Write;
use std::path::{Path, PathBuf};
use std::sync::{Arc, Mutex, MutexGuard};

/// Where the rendered audio goes.
#[derive(Debug, Clone)]
pub enum OutputKind {
    /// try the default output device, fall back to [`OutputKind::Null`]
    Device,
    Null,
    Wav(PathBuf),
}

enum Output {
    Null,
    Wav(WavWriter),
    #[cfg(feature = "playback")]
    Device,
}

/// Minimal 16-bit stereo 48 kHz WAV writer.
pub struct WavWriter {
    file: std::io::BufWriter<std::fs::File>,
    frames: u64,
    done: bool,
}

impl WavWriter {
    pub fn create(path: &Path) -> std::io::Result<Self> {
        let mut f = std::io::BufWriter::new(std::fs::File::create(path)?);
        f.write_all(&[0u8; 44])?; // header patched in finish()
        Ok(WavWriter { file: f, frames: 0, done: false })
    }
    pub fn write(&mut self, interleaved: &[f32]) -> std::io::Result<()> {
        for s in interleaved {
            let v = (s.clamp(-1.0, 1.0) * 32767.0).round() as i16;
            self.file.write_all(&v.to_le_bytes())?;
        }
        self.frames += interleaved.len() as u64 / 2;
        Ok(())
    }
    /// Patch the RIFF header.  Also done on drop, so a `SH2_AUDIO=wav:<path>` run produces a valid file when the game exits.
    pub fn finish(mut self) -> std::io::Result<()> {
        self.finalize()
    }

    fn finalize(&mut self) -> std::io::Result<()> {
        use std::io::{Seek, SeekFrom};
        if self.done {
            return Ok(());
        }
        self.done = true;
        let data = (self.frames * 4) as u32;
        let mut h = Vec::with_capacity(44);
        h.extend_from_slice(b"RIFF");
        h.extend_from_slice(&(36 + data).to_le_bytes());
        h.extend_from_slice(b"WAVEfmt ");
        h.extend_from_slice(&16u32.to_le_bytes());
        h.extend_from_slice(&1u16.to_le_bytes());
        h.extend_from_slice(&2u16.to_le_bytes());
        h.extend_from_slice(&OUT_RATE.to_le_bytes());
        h.extend_from_slice(&(OUT_RATE * 4).to_le_bytes());
        h.extend_from_slice(&4u16.to_le_bytes());
        h.extend_from_slice(&16u16.to_le_bytes());
        h.extend_from_slice(b"data");
        h.extend_from_slice(&data.to_le_bytes());
        self.file.flush()?;
        let f = self.file.get_mut();
        f.seek(SeekFrom::Start(0))?;
        f.write_all(&h)?;
        f.flush()
    }
}

impl Drop for WavWriter {
    fn drop(&mut self) {
        let _ = self.finalize();
    }
}

/// Write interleaved stereo float samples to `path` as a 16-bit WAV.
pub fn write_wav(path: &Path, interleaved: &[f32], channels: u16, rate: u32) -> std::io::Result<()> {
    let mut f = std::io::BufWriter::new(std::fs::File::create(path)?);
    let data = interleaved.len() as u32 * 2;
    f.write_all(b"RIFF")?;
    f.write_all(&(36 + data).to_le_bytes())?;
    f.write_all(b"WAVEfmt ")?;
    f.write_all(&16u32.to_le_bytes())?;
    f.write_all(&1u16.to_le_bytes())?;
    f.write_all(&channels.to_le_bytes())?;
    f.write_all(&rate.to_le_bytes())?;
    f.write_all(&(rate * channels as u32 * 2).to_le_bytes())?;
    f.write_all(&(channels * 2).to_le_bytes())?;
    f.write_all(&16u16.to_le_bytes())?;
    f.write_all(b"data")?;
    f.write_all(&data.to_le_bytes())?;
    for s in interleaved {
        f.write_all(&((s.clamp(-1.0, 1.0) * 32767.0).round() as i16).to_le_bytes())?;
    }
    f.flush()
}

fn lock(m: &Mutex<Synth>) -> MutexGuard<'_, Synth> {
    m.lock().unwrap_or_else(|e| e.into_inner())
}

/// The game-facing audio engine: owns the [`Synth`] and its output.
pub struct AudioEngine {
    synth: Arc<Mutex<Synth>>,
    output: Output,
    /// SE handles handed out (play id -> bank handle) for `set_se_param`
    mode: SoundMode,
    /// stream handles opened through the EE-fed stream API but not started yet
    pending_streams: Vec<PlayId>,
    pub name: &'static str,
}

impl AudioEngine {
    pub fn new(kind: OutputKind) -> Self {
        let synth = Arc::new(Mutex::new(Synth::new()));
        let (output, name) = match kind {
            OutputKind::Null => (Output::Null, "null"),
            OutputKind::Wav(p) => match WavWriter::create(&p) {
                Ok(w) => (Output::Wav(w), "wav"),
                Err(e) => {
                    log::warn!("audio: cannot create {}: {e}; using the null backend", p.display());
                    (Output::Null, "null")
                }
            },
            #[cfg(feature = "playback")]
            OutputKind::Device => match device::spawn(synth.clone()) {
                Ok(()) => (Output::Device, "rodio"),
                Err(e) => {
                    log::warn!("audio: no output device ({e}); using the null backend");
                    (Output::Null, "null")
                }
            },
            #[cfg(not(feature = "playback"))]
            OutputKind::Device => (Output::Null, "null"),
        };
        AudioEngine { synth, output, mode: SoundMode(0), pending_streams: Vec::new(), name }
    }

    pub fn null() -> Self {
        Self::new(OutputKind::Null)
    }

    /// Direct access to the synth (tests, tools, the Bevy plugin).
    pub fn synth(&self) -> MutexGuard<'_, Synth> {
        lock(&self.synth)
    }

    pub fn shared(&self) -> Arc<Mutex<Synth>> {
        self.synth.clone()
    }

    pub fn has_device(&self) -> bool {
        #[cfg(feature = "playback")]
        {
            matches!(self.output, Output::Device)
        }
        #[cfg(not(feature = "playback"))]
        {
            false
        }
    }

    /// Advance the synth by `dt` seconds when there is no real-time consumer (Null / Wav outputs).  No-op for the device output.
    pub fn pump(&mut self, dt: f32) {
        let frames = (dt.clamp(0.0, 0.5) * OUT_RATE as f32) as usize;
        match &mut self.output {
            #[cfg(feature = "playback")]
            Output::Device => {}
            Output::Null => {
                let mut buf = vec![0.0f32; frames * 2];
                lock(&self.synth).render(&mut buf);
            }
            Output::Wav(w) => {
                let mut buf = vec![0.0f32; frames * 2];
                lock(&self.synth).render(&mut buf);
                let _ = w.write(&buf);
            }
        }
    }

    /// Finish a WAV output (writes the header).
    pub fn finish(self) {
        if let Output::Wav(w) = self.output {
            let _ = w.finish();
        }
    }

    pub fn take_events(&self) -> Vec<SynthEvent> {
        std::mem::take(&mut lock(&self.synth).events)
    }

    // ----- convenience API used by the Bevy plugin ------------------------------------------------------------------------

    pub fn load_bank(&self, bytes: &[u8]) -> Option<u32> {
        match Bank::parse(bytes) {
            Ok(b) => Some(lock(&self.synth).add_bank(b)),
            Err(e) => {
                log::warn!("audio: bad SDH bank: {e}");
                None
            }
        }
    }

    pub fn play_stream_file(&self, ssv: &[u8], volume: f32) -> Option<PlayId> {
        let mut p = match StreamPlayer::from_ssv(ssv) {
            Ok(p) => p,
            Err(e) => {
                log::warn!("audio: bad stream BGM: {e}");
                return None;
            }
        };
        p.set_volume(volume);
        Some(lock(&self.synth).add_stream(p))
    }
}

impl SoundBackend for AudioEngine {
    fn load_sdh(&mut self, sdh: &[u8]) -> SoundHandle {
        self.load_bank(sdh).unwrap_or(0)
    }
    fn release_sdh(&mut self, h: SoundHandle) {
        lock(&self.synth).remove_bank(h);
    }
    fn play_se(&mut self, sdh: SoundHandle, se_id: u32, p: &SeParam) -> SoundHandle {
        let mut s = lock(&self.synth);
        // a global id carries the wave-bank number in its high half (FindSE); a bank handle selects the bank directly
        let (bank, local) = if sdh != 0 {
            (Some(sdh), (se_id & 0xffff) as u16)
        } else {
            (s.find_bank_by_id((se_id >> 16) as u16), (se_id & 0xffff) as u16)
        };
        bank.and_then(|b| s.play_se(b, local, p)).unwrap_or(0)
    }
    fn set_se_param(&mut self, se: SoundHandle, p: &SeParam) {
        let mut s = lock(&self.synth);
        s.set_volume(se, p.volume as f32 / 127.0);
        s.set_pan(se, p.pan);
    }
    fn release_se(&mut self, se: SoundHandle, fade: i32) {
        lock(&self.synth).stop(se, fade.max(0) as u32);
    }
    fn is_se_playing(&self, se: SoundHandle) -> bool {
        lock(&self.synth).is_playing(se)
    }
    fn play_bgm(&mut self, sdh: SoundHandle, bgm_id: u32, _mode: u32, p: &BgmParam) -> SoundHandle {
        lock(&self.synth).play_bgm(sdh, (bgm_id & 0xffff) as usize, p).unwrap_or(0)
    }
    fn stop_bgm(&mut self, bgm: SoundHandle, fade_mode: u32) {
        // `fade_mode` is the fade time in milliseconds
        lock(&self.synth).stop(bgm, fade_mode);
    }
    fn set_bgm_param(&mut self, bgm: SoundHandle, p: &BgmParam) {
        let mut s = lock(&self.synth);
        s.set_volume(bgm, p.base.volume as f32 / 127.0);
        s.set_pan(bgm, p.base.pan);
    }
    fn pause(&mut self, on: bool) {
        lock(&self.synth).set_paused(on);
    }
    fn set_mode(&mut self, mode: SoundMode) {
        self.mode = mode;
    }
    fn stream_open(&mut self) -> SoundHandle {
        let id = lock(&self.synth).add_stream(StreamPlayer::fed(2, 0x800, false, 48000));
        self.pending_streams.push(id);
        id
    }
    fn stream_create(&mut self, h: SoundHandle, codec: u8, channels: u8) {
        let mut s = lock(&self.synth);
        if let Some(st) = s.stream_mut(h) {
            let ch = channels.max(1) as usize;
            let rate = st.rate;
            let id = st.id;
            *st = StreamPlayer::fed(ch, 0x800, codec == 0 || codec == 3, rate);
            st.id = id;
        }
    }
    fn stream_set_param(&mut self, h: SoundHandle, vol_lr: u32, pitch: u32) {
        let mut s = lock(&self.synth);
        if let Some(st) = s.stream_mut(h) {
            st.set_volume(((vol_lr & 0xffff) as f32 / 0x3fff as f32).min(1.0));
            // pitch = rate / 48000 * 4096
            if pitch != 0 {
                st.rate = (pitch as u64 * 48000 / 4096) as u32;
            }
        }
    }
    fn stream_write(&mut self, h: SoundHandle, data: &[u8]) {
        if let Some(st) = lock(&self.synth).stream_mut(h) {
            st.feed(data);
        }
    }
    fn stream_buffered(&self, h: SoundHandle) -> usize {
        lock(&self.synth).stream_mut(h).map(|s| s.buffered_frames() * 2).unwrap_or(0)
    }
    fn stream_start(&mut self, h: SoundHandle) {
        if let Some(st) = lock(&self.synth).stream_mut(h) {
            st.start();
        }
    }
    fn stream_stop(&mut self, h: SoundHandle, fade: bool) {
        let mut s = lock(&self.synth);
        if fade {
            s.fade(h, 0.0, 500, true); // StepStreamFade: the retail 500 ms fade-out
        } else if let Some(st) = s.stream_mut(h) {
            st.stop();
        }
    }
    fn stream_pause(&mut self, h: SoundHandle, resume: bool) {
        if let Some(st) = lock(&self.synth).stream_mut(h) {
            st.pause(!resume);
        }
    }
    fn stream_close(&mut self, h: SoundHandle) {
        lock(&self.synth).remove_stream(h);
        self.pending_streams.retain(|&x| x != h);
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// rodio device output
// ---------------------------------------------------------------------------------------------------------------------

#[cfg(feature = "playback")]
mod device {
    use super::*;
    use rodio::{ChannelCount, Sample, SampleRate, Source};
    use std::num::NonZero;
    use std::time::Duration;

    /// Endless stereo source pulling from the synth in 1024-frame blocks.
    pub struct SynthSource {
        synth: Arc<Mutex<Synth>>,
        buf: Vec<f32>,
        idx: usize,
    }

    impl Iterator for SynthSource {
        type Item = Sample;
        fn next(&mut self) -> Option<Sample> {
            if self.idx >= self.buf.len() {
                lock(&self.synth).render(&mut self.buf);
                self.idx = 0;
            }
            let s = self.buf[self.idx];
            self.idx += 1;
            Some(s as Sample)
        }
    }

    impl Source for SynthSource {
        fn current_span_len(&self) -> Option<usize> {
            None
        }
        fn channels(&self) -> ChannelCount {
            NonZero::new(2).unwrap()
        }
        fn sample_rate(&self) -> SampleRate {
            NonZero::new(OUT_RATE).unwrap()
        }
        fn total_duration(&self) -> Option<Duration> {
            None
        }
    }

    /// Open the default device on a dedicated thread (the cpal stream is not `Send`) and keep it alive forever.
    pub fn spawn(synth: Arc<Mutex<Synth>>) -> Result<(), String> {
        let (tx, rx) = std::sync::mpsc::channel::<Result<(), String>>();
        std::thread::Builder::new()
            .name("sh2-audio".into())
            .spawn(move || match rodio::DeviceSinkBuilder::open_default_sink() {
                Ok(mut sink) => {
                    sink.log_on_drop(false);
                    sink.mixer().add(SynthSource { synth, buf: vec![0.0; 2048], idx: 2048 });
                    let _ = tx.send(Ok(()));
                    loop {
                        std::thread::park();
                    }
                }
                Err(e) => {
                    let _ = tx.send(Err(e.to_string()));
                }
            })
            .map_err(|e| e.to_string())?;
        match rx.recv_timeout(Duration::from_secs(3)) {
            Ok(r) => r,
            Err(_) => Err("timed out opening the output device".into()),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn sound_backend_trait_plays_and_streams() {
        use crate::synth::testbank::mini_bank;
        let ev = [0x00, 0xC0, 0x00, 0x00, 0x90, 60, 100, 0x72, 0xFF, 0xFF];
        let bytes = mini_bank(&ev, &[(5, 0x1000)]);
        let mut e = AudioEngine::null();
        let h = e.load_sdh(&bytes);
        assert_ne!(h, 0);
        assert_eq!(e.load_sdh(b"garbage"), 0);
        // global id: bank id 0x1234 in the high half, no explicit bank handle
        let se = e.play_se(0, (0x1234 << 16) | 5, &SeParam::default());
        assert_ne!(se, 0);
        assert!(e.is_se_playing(se));
        e.pump(0.1);
        assert!(e.is_se_playing(se));
        e.release_se(se, 0);
        e.pump(0.3);
        assert!(!e.is_se_playing(se));
        assert_eq!(e.play_se(h, 99, &SeParam::default()), 0, "unknown id");
        let bgm = e.play_bgm(h, 0, 0, &BgmParam::default());
        assert_ne!(bgm, 0);
        e.stop_bgm(bgm, 0);
        e.pump(0.3);
        assert!(!e.synth().is_playing(bgm));
        // EE-fed stream: two stereo chunks of 0x800 bytes of silence blocks
        let st = e.stream_open();
        e.stream_create(st, 2, 2);
        e.stream_write(st, &vec![0u8; 0x1000]);
        assert!(e.stream_buffered(st) > 0);
        e.stream_start(st);
        e.pump(0.01);
        e.stream_pause(st, false);
        e.stream_stop(st, true);
        e.stream_close(st);
        e.pause(true);
        e.set_mode(SoundMode(0x2000));
        e.pause(false);
    }

    #[test]
    fn wav_header_is_valid() {
        let dir = std::env::temp_dir().join("sh2_audio_wav_test.wav");
        let mut w = WavWriter::create(&dir).unwrap();
        w.write(&[0.5, -0.5, 0.25, -0.25]).unwrap();
        w.finish().unwrap();
        let b = std::fs::read(&dir).unwrap();
        assert_eq!(&b[0..4], b"RIFF");
        assert_eq!(&b[8..12], b"WAVE");
        assert_eq!(u32::from_le_bytes([b[40], b[41], b[42], b[43]]), 8);
        assert_eq!(b.len(), 44 + 8);
        assert_eq!(i16::from_le_bytes([b[44], b[45]]), 16384);
        let _ = std::fs::remove_file(dir);
    }
}
