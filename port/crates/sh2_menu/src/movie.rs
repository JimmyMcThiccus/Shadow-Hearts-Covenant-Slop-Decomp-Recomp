//! Full-screen MPEG-2 movie playback: `MovieServerHandler` (`MOVS` track) + `BGMServerHandler` (`PCMS` track) of an LSD stream
//! (`opening/demo.lsd`, `LSD/MOVIE_*.LSD`), JP 0x0038b9c0 / 0x00389830, notes `notes/E/lsd_format.md` §6.
//!
//! * [`MovieStream`] -- pure Rust: reads an LSD file from the disc, pulls the `MOVS` elementary stream and the `PCMS` audio out of it
//!   and decodes the video on a worker thread ([`sh2_gfx::ipu::mpeg2`]) into RGBA frames.  Usable without Bevy (tests, tools).
//! * [`MoviePlugin`] -- Bevy glue: insert a [`MovieRequest`] resource and the plugin shows the frames as a full-window image,
//!   plays the audio through `sh2_audio` ([`AudioRequest::PlayPcms`]) and reports progress in [`MovieStatus`].  O / START skips
//!   (when [`MovieRequest::skippable`]).  When the movie ends (all frames shown and the LSD duration elapsed) or is skipped,
//!   `MovieStatus::state` becomes [`MovieState::Finished`] / [`MovieState::Skipped`] and the request is removed.
//!
//! Title hook (`title.rs` / `plugin.rs` owner): `TitleCmd::PlayMovie(path)` -> `commands.insert_resource(MovieRequest::new(path))`, and
//! `TitleCmd::PauseExitMovie` / the title state machine's "movie done" test -> `MovieStatus::is_over()` (see `notes/integration/requests.md`).

use bevy::asset::RenderAssetUsages;
use bevy::prelude::*;
use bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};
use sh2_audio::{AudioRequest, AudioRuntime};
use sh2_core::game::{padbit, GamePad};
use sh2_gfx::ipu::mpeg2::Mpeg2Decoder;
use sh2_script::lsd::{LsdFile, TrackKind};
use std::path::PathBuf;
use std::sync::mpsc::{sync_channel, Receiver, TryRecvError};
use std::sync::Arc;

/// Everything the movie needs besides its video frames.
#[derive(Clone, Debug)]
pub struct MovieInfo {
    pub width: usize,
    pub height: usize,
    /// frame rate numerator / denominator (30000 / 1001 on the shipped movies)
    pub fps: (u32, u32),
    /// `PCMS` track header (for [`AudioRequest::PlayPcms`]) and the concatenated payload; `None` for silent movies
    pub pcm: Option<(Vec<u8>, Arc<Vec<u8>>)>,
    /// LSD duration (seconds): the movie ends then, even if the video stream is shorter
    pub duration_secs: f32,
}

pub enum MovieMsg {
    Info(MovieInfo),
    /// RGBA8, `width * height * 4`
    Frame(Vec<u8>),
    /// decoder finished: total number of frames
    End(usize),
    Error(String),
}

/// Handle of the decoding thread.
pub struct MovieStream {
    pub rx: std::sync::Mutex<Receiver<MovieMsg>>,
    handle: Option<std::thread::JoinHandle<()>>,
}

/// The `MOVS` elementary stream and `PCMS` audio of an LSD file held in memory.
pub fn split_lsd(bytes: &[u8]) -> Result<(Vec<u8>, MovieInfo), String> {
    let f = LsdFile::parse(bytes).map_err(|e| e.to_string())?;
    let movs = f.tracks.iter().position(|t| TrackKind::from_tag(&t.tag) == TrackKind::Movie).ok_or("no MOVS track")?;
    let pcms = f.tracks.iter().position(|t| &t.tag == b"PCMS");
    let mut es = Vec::with_capacity(f.tracks[movs].total_blocks as usize * 16);
    let mut pcm = Vec::new();
    for p in f.packets() {
        let i = p.track as usize;
        if i == movs {
            es.extend_from_slice(p.payload);
        } else if Some(i) == pcms {
            pcm.extend_from_slice(p.payload);
        }
    }
    let hdr = &f.tracks[movs].raw;
    let rd16 = |o: usize| hdr.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).unwrap_or(0);
    let info = MovieInfo {
        width: rd16(0x28),
        height: rd16(0x2a),
        fps: (30000, 1001),
        pcm: pcms.map(|i| (f.tracks[i].raw.clone(), Arc::new(pcm))),
        duration_secs: f.header.duration_ticks as f32 / f.header.ticks_per_sec.max(1) as f32,
    };
    Ok((es, info))
}

impl MovieStream {
    pub fn try_recv(&self) -> Result<MovieMsg, TryRecvError> {
        self.rx.lock().unwrap_or_else(|e| e.into_inner()).try_recv()
    }
    pub fn recv(&self) -> Result<MovieMsg, std::sync::mpsc::RecvError> {
        self.rx.lock().unwrap_or_else(|e| e.into_inner()).recv()
    }
    /// Read `path` (e.g. `OPENING/DEMO.LSD`) from the disc folder `root` and start decoding.  Frames are queued through a small bounded
    /// channel (the thread blocks while it is full).
    pub fn open(root: PathBuf, path: String) -> MovieStream {
        let (tx, rx) = sync_channel::<MovieMsg>(8);
        let handle = std::thread::Builder::new()
            .name("movie-decoder".into())
            .spawn(move || {
                let run = || -> Result<(), String> {
                    let disc = sh2_core::fileio::Disc::open(&root).map_err(|e| e.to_string())?;
                    let bytes = disc.read(&path).map_err(|e| format!("{path}: {e}"))?;
                    let (es, mut info) = split_lsd(&bytes)?;
                    drop(bytes);
                    let mut dec = Mpeg2Decoder::new(&es);
                    // the sequence header gives the real size / rate
                    if let Some(s) = dec.peek_format() {
                        info.width = s.0;
                        info.height = s.1;
                        info.fps = (s.2, s.3);
                    }
                    let (w, h) = (info.width, info.height);
                    if tx.send(MovieMsg::Info(info)).is_err() {
                        return Ok(());
                    }
                    let mut n = 0usize;
                    let mut rgba = Vec::new();
                    loop {
                        match dec.next_frame() {
                            Ok(Some(f)) => {
                                f.to_rgba(&mut rgba);
                                debug_assert_eq!(rgba.len(), w * h * 4);
                                n += 1;
                                if tx.send(MovieMsg::Frame(std::mem::take(&mut rgba))).is_err() {
                                    return Ok(());
                                }
                            }
                            Ok(None) => break,
                            Err(e) => return Err(format!("frame {n}: {e}")),
                        }
                    }
                    let _ = tx.send(MovieMsg::End(n));
                    Ok(())
                };
                if let Err(e) = run() {
                    let _ = tx.send(MovieMsg::Error(e));
                }
            })
            .expect("spawn movie decoder");
        MovieStream { rx: std::sync::Mutex::new(rx), handle: Some(handle) }
    }

    /// Drain a stream completely (no pacing): returns `(frames, info)`.  For tests and tools.
    pub fn count_frames(root: PathBuf, path: String) -> Result<(usize, MovieInfo), String> {
        let s = MovieStream::open(root, path);
        let mut info = None;
        loop {
            match s.recv() {
                Ok(MovieMsg::Info(i)) => info = Some(i),
                Ok(MovieMsg::Frame(_)) => {}
                Ok(MovieMsg::End(n)) => return Ok((n, info.ok_or("no info")?)),
                Ok(MovieMsg::Error(e)) => return Err(e),
                Err(_) => return Err("decoder thread died".into()),
            }
        }
    }
}

impl Drop for MovieStream {
    fn drop(&mut self) {
        // dropping the receiver makes the worker's next send fail and end the thread; do not join (it may be mid-decode)
        self.handle.take();
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------
// Bevy glue
// ----------------------------------------------------------------------------------------------------------------------------------

/// Insert to start a movie.  Ignored while another one is active.
#[derive(Resource, Clone, Debug)]
pub struct MovieRequest {
    /// disc path of the LSD file, e.g. `OPENING/DEMO.LSD` (case-insensitive, `opening/demo.lsd` works)
    pub path: String,
    /// O / START ends the movie early
    pub skippable: bool,
    /// audio gain (0..1)
    pub volume: f32,
}

impl MovieRequest {
    pub fn new(path: impl Into<String>) -> Self {
        MovieRequest { path: path.into(), skippable: true, volume: 1.0 }
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum MovieState {
    #[default]
    Idle,
    /// worker thread is reading / probing the file
    Loading,
    Playing,
    /// played to the end of the LSD stream
    Finished,
    /// cut short with O / START
    Skipped,
    Failed,
}

#[derive(Resource, Default, Debug)]
pub struct MovieStatus {
    pub state: MovieState,
    pub frames_decoded: usize,
    pub frames_shown: usize,
    /// set once the decoder reached the end of the elementary stream
    pub total_frames: Option<usize>,
    pub elapsed_secs: f32,
    pub width: usize,
    pub height: usize,
    pub error: Option<String>,
    /// number of movies started so far (lets a consumer tell "my movie" from an older result)
    pub generation: u32,
}

impl MovieStatus {
    /// Finished, skipped or failed (the movie is no longer on screen).
    pub fn is_over(&self) -> bool {
        matches!(self.state, MovieState::Finished | MovieState::Skipped | MovieState::Failed)
    }
    pub fn is_active(&self) -> bool {
        matches!(self.state, MovieState::Loading | MovieState::Playing)
    }
}

/// How a running movie / cut scene can be cut short.
///
/// * `Direct`: O / START ends it at once when [`MovieRequest::skippable`] (the demo title's convention; the retail title handles its own key).
/// * `StartThenTriangle`: the retail in-game rule (`CLSDPauser`, JP 0x003ca8b0): START pauses (everything freezes, the screen darkens and the
///   message "Triangle: Skip Movie / START: Cancel Pause" shows), then TRIANGLE leaves the movie (`FieldBreakMCES`) or START resumes.
///   The movie plugin resets the resource to `Direct` when the movie ends.
#[derive(Resource, Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum MovieSkipPolicy {
    #[default]
    Direct,
    StartThenTriangle,
}

/// The START-button pause overlay of `CLSDPauser`: a dark mask that fades to alpha 0x40 / 0x80 in steps of 8 per frame and the pause message.
#[derive(Default)]
pub struct PauseSkip {
    pub paused: bool,
    overlay: Option<Entity>,
    fade: f32,
    /// frames since the pause began (the original ignores TRIANGLE until the mask is fully faded in)
    age: u32,
}

#[derive(Component)]
pub struct PauseOverlay;

pub const PAUSE_MESSAGE: &str = "Triangle: Skip Movie\nSTART: Cancel Pause";

impl PauseSkip {
    /// One frame.  `press` = trigger word.  Returns true when the player chose to leave (TRIANGLE while paused).
    pub fn update<F: bevy::ecs::query::QueryFilter>(&mut self, press: u16, dt: f32, commands: &mut Commands, overlays: &mut Query<&mut BackgroundColor, F>) -> bool {
        if !self.paused {
            if press & padbit::START != 0 {
                self.paused = true;
                self.fade = 0.0;
                self.age = 0;
                let root = commands
                    .spawn((
                        PauseOverlay,
                        Node {
                            position_type: PositionType::Absolute,
                            left: Val::Px(0.0),
                            top: Val::Px(0.0),
                            width: Val::Percent(100.0),
                            height: Val::Percent(100.0),
                            align_items: AlignItems::Center,
                            justify_content: JustifyContent::Center,
                            ..default()
                        },
                        BackgroundColor(Color::srgba(0.0, 0.0, 0.0, 0.0)),
                        GlobalZIndex(20_000),
                        Name::new("pause"),
                    ))
                    .with_children(|p| {
                        p.spawn((
                            Text::new(PAUSE_MESSAGE),
                            TextFont { font_size: FontSize::Px(18.0), ..default() },
                            TextColor(Color::WHITE),
                            TextLayout::justify(Justify::Center),
                        ));
                    })
                    .id();
                self.overlay = Some(root);
            }
            return false;
        }
        self.age += 1;
        // `CLSDPauser`: +8 per console frame (30 / s)
        self.fade = (self.fade + 8.0 * 30.0 * dt).min(64.0);
        for mut bg in overlays.iter_mut() {
            bg.0 = Color::srgba(0.0, 0.0, 0.0, self.fade / 128.0);
        }
        if self.age > 2 && press & padbit::TRIANGLE != 0 {
            self.close(commands);
            return true;
        }
        if self.age > 2 && press & padbit::START != 0 {
            self.close(commands);
        }
        false
    }

    pub fn close(&mut self, commands: &mut Commands) {
        self.paused = false;
        if let Some(e) = self.overlay.take() {
            commands.entity(e).despawn();
        }
    }
}

/// Frame-time filter for the pictures of cut scenes / movies.  The render loop of the app delivers uneven frame deltas (7 / 25 ms alternating
/// with the pipelined renderer) although the frames are presented at regular intervals; stepping the scene by the raw delta makes every
/// moving thing judder.  The filter feeds the scene a smoothed delta and pays back the difference over the following frames, so the
/// total time is exact.
#[derive(Default, Clone, Debug)]
pub struct FrameClock {
    ema: f32,
    debt: f32,
}

impl FrameClock {
    pub fn smooth(&mut self, dt: f32) -> f32 {
        if self.ema <= 0.0 || dt > 0.12 {
            // first frame / hitch: take the raw delta
            self.ema = dt.min(0.05);
            self.debt = 0.0;
            return dt;
        }
        self.ema += (dt - self.ema) * 0.15;
        let pay = self.debt * 0.1;
        let used = (self.ema + pay).max(0.0);
        self.debt += dt - used;
        used
    }
}

/// Slaves a scene / picture clock to the audio stream position without ever running backwards and without trusting a bad audio clock.
///
/// * The stream position moves in buffer-sized steps: it is extrapolated with the wall clock between steps.
/// * The clock is steered by a gentle rate change (at most +-4 %); only an error above 0.3 s is re-synced once.
/// * Every second the audio rate is compared with the wall rate; a device whose reported position runs at a different speed
///   (> 10 % off: wrong sample-rate bookkeeping) is distrusted for good and the wall clock drives the scene.
#[derive(Default, Clone, Debug)]
pub struct AudioSlave {
    pub engaged: bool,
    pub bad: bool,
    last_pos: f32,
    last_pos_wall: f32,
    ref_wall: f32,
    ref_pos: f32,
}

impl AudioSlave {
    /// `pos` = stream position (s) now, `wall` = wall time (s) accumulated by the owner, `dt` = this frame's wall step, `clock` = the scene clock
    /// before the step, `t0` = scene time at which the stream started.  Returns the step to apply to the scene clock.
    pub fn steer(&mut self, pos: Option<f32>, wall: f32, dt: f32, clock: f32, t0: f32) -> f32 {
        let Some(pos) = pos.filter(|p| *p > 0.02 && !self.bad) else { return dt };
        if !self.engaged {
            self.engaged = true;
            self.last_pos = pos;
            self.last_pos_wall = wall;
            self.ref_wall = wall;
            self.ref_pos = pos;
        }
        if (pos - self.last_pos).abs() > 1e-6 {
            self.last_pos = pos;
            self.last_pos_wall = wall;
        }
        if wall - self.ref_wall >= 1.0 {
            let rate = (pos - self.ref_pos) / (wall - self.ref_wall);
            if (rate - 1.0).abs() > 0.1 && (rate - 1.0).abs() < 1.0e6 {
                self.bad = true;
                return dt;
            }
            self.ref_wall = wall;
            self.ref_pos = pos;
        }
        let est = pos + (wall - self.last_pos_wall).clamp(0.0, 0.1);
        let err = (t0 + est) - (clock + dt);
        if err.abs() > 0.3 {
            (t0 + est - clock).max(0.0)
        } else {
            dt * (1.0 + (err * 1.5).clamp(-0.04, 0.04))
        }
    }
}

#[cfg(test)]
mod clock_tests {
    use super::*;

    /// Step a scene clock with fake frame deltas for `secs` of wall time; the audio position (if any) is reported in `chunk`-second steps
    /// and runs at `audio_rate` x real time.  Returns the scene time reached.
    fn run(hz: f32, secs: f32, audio_rate: Option<f32>, chunk: f32, jitter: bool) -> f32 {
        let mut fc = FrameClock::default();
        let mut slave = AudioSlave::default();
        let (mut wall, mut clock, mut real) = (0.0f32, 0.0f32, 0.0f32);
        let mut n = 0u32;
        while real < secs {
            n += 1;
            // frame delta: regular, or alternating 7 / 25 ms like a pipelined renderer (the mean stays 1 / hz)
            let raw = if jitter { if n % 2 == 0 { 0.4 / hz } else { 1.6 / hz } } else { 1.0 / hz };
            real += raw;
            let dt = fc.smooth(raw);
            wall += dt;
            let pos = audio_rate.map(|r| ((real * r) / chunk).floor() * chunk);
            let step = slave.steer(pos, wall, dt, clock, 0.0);
            assert!(step >= 0.0);
            clock += step;
        }
        clock
    }

    #[test]
    fn scene_clock_keeps_real_time_at_any_frame_rate() {
        // N003 is 3421 ticks = 114.0 s, N004 603 ticks = 20.1 s
        for (secs, name) in [(114.0f32, "N003"), (20.1, "N004")] {
            for hz in [30.0f32, 60.0, 144.0, 1000.0] {
                for jitter in [false, true] {
                    let t = run(hz, secs, None, 0.0, jitter);
                    assert!((t - secs).abs() < 0.2, "{name} {hz} Hz jitter {jitter}: {t}");
                    let t = run(hz, secs, Some(1.0), 0.02, jitter);
                    assert!((t - secs).abs() < 0.2, "{name} {hz} Hz audio-slaved jitter {jitter}: {t}");
                }
            }
        }
    }

    #[test]
    fn a_bad_audio_clock_is_distrusted() {
        // the device reports its position at twice the speed (sample-rate bookkeeping): the scene must still run at real time
        let t = run(60.0, 30.0, Some(2.0), 0.02, false);
        assert!((t - 30.0).abs() < 1.5, "scene ran at {t} s for 30 s of wall time");
        let t = run(60.0, 30.0, Some(0.5), 0.02, false);
        assert!((t - 30.0).abs() < 1.5, "scene ran at {t} s for 30 s of wall time");
    }

    #[test]
    fn the_frame_filter_conserves_time() {
        let mut fc = FrameClock::default();
        let mut sum_raw = 0.0;
        let mut sum_used = 0.0;
        for i in 0..6000 {
            let raw = if i % 2 == 0 { 0.007 } else { 0.026 };
            sum_raw += raw;
            sum_used += fc.smooth(raw);
        }
        assert!((sum_raw - sum_used).abs() < 0.05, "{sum_raw} vs {sum_used}");
    }
}

#[derive(Component)]
struct MovieNode;

/// The 4:3 presentation rectangle of the window in logical pixels `(left, top, width, height)` (`sh2_gfx::bevy::screen::present_rect`): everything
/// full-screen (movie pictures, title art, fades) is stretched over it, like the console's video encoder stretched the 512 x 448 / 640 x 448 frame.
pub fn present_rect_logical(w: &Window) -> (f32, f32, f32, f32) {
    let (x, y, pw, ph) = sh2_gfx::bevy::screen::present_rect(w.physical_width(), w.physical_height(), false);
    let sf = w.scale_factor().max(0.01);
    (x as f32 / sf, y as f32 / sf, pw as f32 / sf, ph as f32 / sf)
}

/// Keep the movie picture on the 4:3 presentation rectangle (the picture is stretched to it whatever its stream size is).  Bevy UI lays a
/// root node out in the *viewport* of its camera, which `sh2_gfx::bevy::screen` already sets to the 4:3 rectangle: the node covers the whole
/// viewport (offsetting it by the window's letterbox bars, as this used to, pushed the picture out of the picture).
fn fit_movie_node(mut nodes: Query<&mut Node, With<MovieNode>>) {
    for mut n in &mut nodes {
        n.left = Val::Px(0.0);
        n.top = Val::Px(0.0);
        n.width = Val::Percent(100.0);
        n.height = Val::Percent(100.0);
    }
}

struct Active {
    stream: MovieStream,
    info: Option<MovieInfo>,
    image: Option<Handle<Image>>,
    node: Option<Entity>,
    /// seconds of playback so far
    clock: f32,
    started: bool,
    ended: Option<usize>,
    skippable: bool,
    volume: f32,
    pending: Option<Vec<u8>>,
    /// wall-clock seconds since the first frame (the fallback when no audio clock is running)
    wall: f32,
    /// last audio position seen and the wall time it changed at (the position moves in buffer-sized steps)
    slave: AudioSlave,
    warned_bad: bool,
    frame_clock: FrameClock,
    pause: PauseSkip,
}

#[derive(Resource, Default)]
struct MovieRuntime(Option<Active>);

fn movie_root() -> PathBuf {
    std::env::var_os("SH2_DISC_DIR").map(PathBuf::from).unwrap_or_else(|| ".".into())
}

fn start_movie(req: Option<Res<MovieRequest>>, mut rt: ResMut<MovieRuntime>, mut status: ResMut<MovieStatus>, cfg: Option<Res<sh2_core::app::AppConfig>>) {
    let Some(req) = req else { return };
    if rt.0.is_some() || !req.is_added() && !req.is_changed() {
        return;
    }
    let root = std::env::var_os("SH2_DISC_DIR").map(PathBuf::from).or_else(|| cfg.map(|c| c.disc_dir.clone())).unwrap_or_else(movie_root);
    info!("movie: starting {}", req.path);
    status.generation += 1;
    *status = MovieStatus { state: MovieState::Loading, generation: status.generation, ..Default::default() };
    rt.0 = Some(Active {
        stream: MovieStream::open(root, req.path.clone()),
        info: None,
        image: None,
        node: None,
        clock: 0.0,
        started: false,
        ended: None,
        skippable: req.skippable,
        volume: req.volume,
        pending: None,
        wall: 0.0,
        slave: AudioSlave::default(),
        warned_bad: false,
        frame_clock: FrameClock::default(),
        pause: PauseSkip::default(),
    });
}

fn finish(rt: &mut MovieRuntime, status: &mut MovieStatus, commands: &mut Commands, state: MovieState) {
    if let Some(mut a) = rt.0.take() {
        if let Some(n) = a.node {
            commands.entity(n).despawn();
        }
        a.pause.close(commands);
        sh2_audio::post(AudioRequest::StopPcms { fade_ms: 0 });
    }
    status.state = state;
    commands.remove_resource::<MovieRequest>();
    commands.insert_resource(MovieSkipPolicy::Direct);
}

#[allow(clippy::too_many_arguments)]
fn play_movie(
    mut commands: Commands,
    time: Res<Time>,
    pad: Option<Res<GamePad>>,
    mut rt: ResMut<MovieRuntime>,
    mut status: ResMut<MovieStatus>,
    mut images: ResMut<Assets<Image>>,
    req: Option<Res<MovieRequest>>,
    policy: Option<Res<MovieSkipPolicy>>,
    audio: Option<Res<AudioRuntime>>,
    mut overlays: Query<&mut BackgroundColor, With<PauseOverlay>>,
) {
    let Some(a) = rt.0.as_mut() else { return };
    // the owner removed the request (title: `PauseExitMovie`): stop
    if req.is_none() {
        info!("movie: request removed, stopping");
        finish(&mut rt, &mut status, &mut commands, MovieState::Skipped);
        return;
    }
    // drain the worker: info first, then as many frames as the clock asks for
    let mut failed = None;
    // 1. messages that are not frames (and the first frame)
    loop {
        // pick the next frame only when the clock wants it
        if a.pending.is_some() {
            break;
        }
        match a.stream.try_recv() {
            Ok(MovieMsg::Info(i)) => {
                status.width = i.width;
                status.height = i.height;
                let mut img = Image::new_fill(
                    Extent3d { width: i.width as u32, height: i.height as u32, depth_or_array_layers: 1 },
                    TextureDimension::D2,
                    &[0, 0, 0, 255],
                    TextureFormat::Rgba8UnormSrgb,
                    RenderAssetUsages::default(),
                );
                img.sampler = bevy::image::ImageSampler::linear();
                let h = images.add(img);
                let node = commands
                    .spawn((
                        Node { position_type: PositionType::Absolute, left: Val::Px(0.0), top: Val::Px(0.0), width: Val::Percent(100.0), height: Val::Percent(100.0), ..default() },
                        {
                            let mut n = ImageNode::new(h.clone());
                            n.image_mode = bevy::ui::widget::NodeImageMode::Stretch;
                            n
                        },
                        GlobalZIndex(10_000),
                        MovieNode,
                        Name::new("movie"),
                    ))
                    .id();
                a.image = Some(h);
                a.node = Some(node);
                a.info = Some(i);
            }
            Ok(MovieMsg::Frame(f)) => {
                a.pending = Some(f);
            }
            Ok(MovieMsg::End(n)) => a.ended = Some(n),
            Ok(MovieMsg::Error(e)) => {
                failed = Some(e);
                break;
            }
            Err(TryRecvError::Empty) => break,
            Err(TryRecvError::Disconnected) => {
                if a.ended.is_none() {
                    failed = Some("decoder thread ended unexpectedly".into());
                }
                break;
            }
        }
    }
    if let Some(e) = failed {
        error!("movie: {e}");
        status.error = Some(e);
        finish(&mut rt, &mut status, &mut commands, MovieState::Failed);
        return;
    }
    let Some(info) = a.info.clone() else { return };
    let in_game_pause = policy.map(|p| *p == MovieSkipPolicy::StartThenTriangle).unwrap_or(false);
    if !a.started {
        // the first frame is ready (or the stream is empty): start the clock and the audio together
        if a.pending.is_none() && a.ended.is_none() {
            return;
        }
        a.started = true;
        status.state = MovieState::Playing;
        if let Some((hdr, data)) = &info.pcm {
            sh2_audio::post(AudioRequest::PlayPcms { hdr: hdr.clone(), data: data.clone(), volume: a.volume });
        }
    } else {
        // START pause / TRIANGLE skip (`CLSDPauser`)
        if in_game_pause {
            if let Some(p) = &pad {
                let was = a.pause.paused;
                if a.pause.update(p.press(), time.delta_secs(), &mut commands, &mut overlays) {
                    info!("movie: skipped (START, TRIANGLE) at {:.1}s", a.clock);
                    finish(&mut rt, &mut status, &mut commands, MovieState::Skipped);
                    return;
                }
                if was != a.pause.paused {
                    sh2_audio::post(AudioRequest::PausePcms { paused: a.pause.paused });
                }
            }
        }
        if !a.pause.paused {
            let speed = std::env::var("SH2_CUTSCENE_SPEED").ok().and_then(|v| v.parse::<f32>().ok()).unwrap_or(1.0).clamp(0.1, 32.0);
            let dt = a.frame_clock.smooth(time.delta_secs().min(0.25)) * speed;
            a.wall += dt;
            // A/V sync: the PCMS stream position is the master clock (the decoder thread and the frame rate jitter, the sound card does not);
            // fall back to the wall clock when no audio is running (no device / muted / sped up for screenshots)
            let pos = if speed == 1.0 { audio.as_ref().and_then(|r| r.pcms_position()) } else { None };
            if let Some(p) = pos.filter(|p| *p > 0.02) {
                if !a.slave.engaged && !a.slave.bad {
                    info!("movie: A/V sync follows the audio clock (stream at {p:.2}s, picture clock {:.2}s)", a.clock);
                    a.clock = p; // the audio owns the clock from here on (the wall clock ran ahead while the device started)
                }
            }
            let step = if info.pcm.is_some() { a.slave.steer(pos, a.wall, dt, a.clock, 0.0) } else { dt };
            if a.slave.bad && !a.warned_bad {
                a.warned_bad = true;
                warn!("movie: the audio position runs at the wrong speed; the wall clock drives the movie");
            }
            a.clock += step;
        }
    }
    status.elapsed_secs = a.clock;
    // skip
    if a.skippable && !in_game_pause {
        if let Some(p) = &pad {
            if p.press() & (padbit::CIRCLE | padbit::START) != 0 && a.clock > 0.3 {
                info!("movie: skipped at {:.1}s", a.clock);
                finish(&mut rt, &mut status, &mut commands, MovieState::Skipped);
                return;
            }
        }
    }
    if a.pause.paused {
        return;
    }
    // show frames up to the clock (dropping late ones)
    let fps = info.fps.0 as f32 / info.fps.1.max(1) as f32;
    let target = (a.clock * fps).floor() as usize + 1;
    let mut latest: Option<Vec<u8>> = None;
    while status.frames_decoded < target {
        let frame = match a.pending.take() {
            Some(f) => f,
            None => match a.stream.try_recv() {
                Ok(MovieMsg::Frame(f)) => f,
                Ok(MovieMsg::End(n)) => {
                    a.ended = Some(n);
                    break;
                }
                Ok(MovieMsg::Error(e)) => {
                    error!("movie: {e}");
                    status.error = Some(e);
                    finish(&mut rt, &mut status, &mut commands, MovieState::Failed);
                    return;
                }
                Ok(MovieMsg::Info(_)) => continue,
                Err(_) => break,
            },
        };
        status.frames_decoded += 1;
        latest = Some(frame);
    }
    if let Some(f) = latest {
        if let Some(mut img) = a.image.as_ref().and_then(|h| images.get_mut(h)) {
            img.data = Some(f);
            status.frames_shown += 1;
        }
    }
    if let Some(n) = a.ended {
        status.total_frames = Some(n);
        // the elementary stream is exhausted: show black until the LSD duration (audio tail) has elapsed
        if status.frames_decoded >= n {
            if let Some(mut img) = a.image.as_ref().and_then(|h| images.get_mut(h)) {
                if a.clock * fps > n as f32 + 1.0 {
                    if let Some(d) = img.data.as_mut() {
                        d.chunks_exact_mut(4).for_each(|p| p[..3].fill(0));
                    }
                }
            }
            if a.clock >= info.duration_secs.max(n as f32 / fps) {
                info!("movie: finished, {} frames", status.frames_decoded);
                finish(&mut rt, &mut status, &mut commands, MovieState::Finished);
            }
        }
    }
}

/// `MoviePlugin`: add it once; then `commands.insert_resource(MovieRequest::new("opening/demo.lsd"))`.
pub struct MoviePlugin;

impl Plugin for MoviePlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<MovieRuntime>().init_resource::<MovieStatus>().init_resource::<MovieSkipPolicy>().add_systems(Update, (start_movie, play_movie, fit_movie_node).chain());
    }
}
