//! sh2_audio – the audio layer of the Shadow Hearts: Covenant port.  See notes/integration/audio.md.
//!
//! * [`adpcm`]  – SPU ADPCM decoder
//! * [`sdh`]    – `SDRH` bank parser (waves, programs, tones, timbres, SE map, sequences)
//! * [`spu`]    – SPU2 hardware pieces: driver pitch / pan math, ADSR, LFO, reverb with the LIBSD presets
//! * [`synth`]  – software SPU2 (voices, ADSR, reverb) + BGM / SE sequencers
//! * [`stream`] – `*.SSV` stream BGM and the EE-fed stream player
//! * [`engine`] – output backends (rodio device, null, WAV dump) and the `SoundBackend` implementation
//! * [`plugin`] – Bevy `AudioPlugin`, request queue and disc glue (feature `bevy`)
pub mod adpcm;
pub mod engine;
#[cfg(feature = "bevy")]
pub mod plugin;
pub mod runtime;
pub mod se_ids;
pub mod sdh;
pub mod spu;
pub mod stream;
pub mod synth;
pub mod validate;

pub use engine::{write_wav, AudioEngine, OutputKind};
#[cfg(feature = "bevy")]
pub use plugin::AudioPlugin;
pub use runtime::{drain, hooks, post, status, AudioRequest, AudioRuntime};
pub use sdh::Bank;
pub use synth::{Synth, SynthEvent, OUT_RATE};
