//! Bevy glue: [`AudioPlugin`] owns an [`AudioRuntime`] resource, drains the global request queue every frame and plays the scene music.
//!
//! Registered in `sh2_app/src/main.rs`.  Without any hook in the field / battle crates it already plays:
//! * the title jingle (`Scene::Title`, `OPENING/BGM803.SSV`),
//! * the battle BGM of the requested battle (`BattleRequest.param.bgm`, `BTLDATA/SOUND/BGM/BGM%03d.SSQ`) and the result fanfare
//!   (`BattleReport.pending`), faded out on leaving the battle;
//! and everything the scripts / menus [`post`](crate::post) (see notes/integration/audio.md for the one-line hooks).

use crate::engine::AudioEngine;
use crate::runtime::{drain, output_from_env, AudioRequest, AudioRuntime};
use bevy::prelude::*;
use sh2_core::app::AppConfig;
use sh2_core::fileio::Disc;
use sh2_core::game::{BattleOutcome, BattleReport, BattleRequest, Scene};

#[derive(Default)]
pub struct AudioPlugin {
    /// override the output (default: `SH2_AUDIO` environment variable, else the default device)
    pub output: Option<crate::engine::OutputKind>,
}

impl Plugin for AudioPlugin {
    fn build(&self, app: &mut App) {
        let kind = self.output.clone().unwrap_or_else(output_from_env);
        let dir = app.world().get_resource::<AppConfig>().map(|c| c.disc_dir.clone()).or_else(|| std::env::var_os("SH2_DISC_DIR").map(Into::into));
        let disc = dir.and_then(|d| match Disc::open(&d) {
            Ok(d) => Some(d),
            Err(e) => {
                warn!("audio: cannot open disc {}: {e}", d.display());
                None
            }
        });
        let engine = AudioEngine::new(kind);
        info!("audio: output backend '{}'{}", engine.name, if disc.is_some() { "" } else { " (no disc: silent)" });
        app.insert_resource(AudioRuntime::new(engine, disc));
        app.add_systems(Update, (audio_drain, audio_battle_result, audio_update).chain());
        app.add_systems(OnEnter(Scene::Title), on_enter_title);
        app.add_systems(OnEnter(Scene::Battle), on_enter_battle);
        app.add_systems(OnExit(Scene::Battle), on_exit_battle);
        app.add_systems(OnEnter(Scene::GameOver), on_enter_game_over);
    }
}

fn audio_drain(mut rt: ResMut<AudioRuntime>) {
    for r in drain() {
        rt.handle(&r);
    }
}

fn audio_update(mut rt: ResMut<AudioRuntime>, time: Res<Time>) {
    rt.update(time.delta_secs());
}

fn on_enter_title(mut rt: ResMut<AudioRuntime>) {
    rt.handle(&AudioRequest::StopAll);
    rt.handle(&AudioRequest::PlayTitleBgm);
}

fn on_enter_battle(mut rt: ResMut<AudioRuntime>, req: Option<Res<BattleRequest>>) {
    // SSHSys: BtlSocket::SetBtlBGMNumber(param.bgm); the default battle BGM number is 0x191 (BGM401)
    let n = req.map(|r| r.param.bgm).filter(|&b| b != 0).unwrap_or(0x191);
    rt.handle(&AudioRequest::PlayBattleBgm { number: n });
}

fn on_exit_battle(mut rt: ResMut<AudioRuntime>) {
    rt.handle(&AudioRequest::StopBattleBgm);
}

fn on_enter_game_over(mut rt: ResMut<AudioRuntime>) {
    rt.handle(&AudioRequest::StopAll);
}

fn audio_battle_result(mut rt: ResMut<AudioRuntime>, report: Option<Res<BattleReport>>, mut was_pending: Local<bool>) {
    let Some(r) = report else { return };
    if r.pending && !*was_pending && r.outcome == BattleOutcome::Win {
        rt.handle(&AudioRequest::PlayBattleResultBgm);
    }
    *was_pending = r.pending;
}
