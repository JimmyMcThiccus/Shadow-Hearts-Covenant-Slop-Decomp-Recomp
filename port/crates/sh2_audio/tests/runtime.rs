//! Runtime / plugin tests on real disc data (skipped without a disc): requests -> banks -> sound.

use sh2_audio::runtime::{drain, hooks, post, AudioRequest};
use sh2_audio::{AudioEngine, AudioRuntime, OutputKind};
use sh2_core::fileio::Disc;
use std::sync::Mutex;

const JP: &str = "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)";
// the request queue is process-global: serialise the tests that use it
static LOCK: Mutex<()> = Mutex::new(());

fn disc() -> Option<Disc> {
    Disc::open(std::env::var("SH2_DISC_DIR").unwrap_or_else(|_| JP.to_string())).ok()
}

fn energy(rt: &mut AudioRuntime, secs: f32) -> f32 {
    let mut buf = vec![0.0f32; (secs * 48000.0) as usize * 2];
    rt.engine.synth().render(&mut buf);
    (buf.iter().map(|s| s * s).sum::<f32>() / buf.len() as f32).sqrt()
}

#[test]
fn requests_play_real_banks() {
    let _g = LOCK.lock().unwrap_or_else(|e| e.into_inner());
    let Some(d) = disc() else { return };
    let mut rt = AudioRuntime::new(AudioEngine::new(OutputKind::Null), Some(d));
    // system SE (COMMON/SYSREG.SSE, wave bank 0)
    rt.handle(&AudioRequest::PlaySystemSe { id: 2 });
    assert!(energy(&mut rt, 0.3) > 0.001, "system SE is silent");
    // battle BGM by number -> BTLDATA/SOUND/BGM/BGM401.SSQ
    rt.handle(&AudioRequest::PlayBattleBgm { number: 0x191 });
    assert!(rt.bgm_playing());
    assert!(energy(&mut rt, 2.0) > 0.005, "battle BGM is silent");
    // a number without a file falls back to BGM401 instead of silence
    rt.handle(&AudioRequest::PlayBattleBgm { number: 0x2ff });
    assert!(rt.bgm_playing());
    // stopping fades out within the retail 500 ms
    rt.handle(&AudioRequest::StopBattleBgm);
    let _ = energy(&mut rt, 0.6);
    assert!(!rt.bgm_playing());
    let _ = energy(&mut rt, 2.5); // reverb tail
    assert!(energy(&mut rt, 0.2) < 1e-4, "fade-out should reach silence");
    // title stream
    rt.handle(&AudioRequest::PlayTitleBgm);
    assert!(rt.stream_playing());
    assert!(energy(&mut rt, 1.0) > 0.003);
    rt.handle(&AudioRequest::StopAll);
    assert!(energy(&mut rt, 0.2) < 1e-4, "StopAll silences the stream");
    assert!(rt.stats.missing_files.iter().all(|f| f.contains("BGM2FF") || f.contains("BGM767")), "{:?}", rt.stats.missing_files);
}

#[test]
fn field_script_ops_become_audio() {
    let _g = LOCK.lock().unwrap_or_else(|e| e.into_inner());
    let Some(d) = disc() else { return };
    drain();
    // LoadBgm("BGM601") ; PlayBgm(0, 0)   (script ops 0x50 / 0x51)
    assert!(hooks::field_script_op(0x50, 1, |_| 0, |_| "BGM601".to_string()));
    assert!(hooks::field_script_op(0x51, 2, |_| 0, |_| String::new()));
    // LoadSe("AP_00_U") ; PlaySe(0x20000000 | 1 ...)
    assert!(hooks::field_script_op(0x56, 1, |_| 0, |_| "AP_00_U".to_string()));
    assert!(hooks::field_script_op(0x58, 2, |i| if i == 0 { 0x2000_1001u32 as i32 } else { 100 }, |_| String::new()));
    assert!(!hooks::field_script_op(0x20, 2, |_| 0, |_| String::new()), "MapJump is not an audio op");
    let reqs = drain();
    assert_eq!(reqs.len(), 4, "{reqs:?}");
    let mut rt = AudioRuntime::new(AudioEngine::new(OutputKind::Null), Some(d));
    for r in &reqs {
        rt.handle(r);
    }
    assert!(rt.bgm_playing());
    assert!(energy(&mut rt, 3.0) > 0.005);
    assert!(rt.stats.banks_loaded >= 2);
    post(AudioRequest::StopAll);
    assert_eq!(drain(), vec![AudioRequest::StopAll]);
}

#[test]
fn stop_se_wait_se_and_wait_bgm_follow_the_original_semantics() {
    use sh2_audio::{se_ids, status};
    let _g = LOCK.lock().unwrap_or_else(|e| e.into_inner());
    let Some(d) = disc() else { return };
    drain();
    let mut rt = AudioRuntime::new(AudioEngine::new(OutputKind::Null), Some(d));
    rt.handle(&AudioRequest::StopAll);
    // SYSREG 0x2000 is a looping sound: PlayGlobalSe loads the system bank on demand
    let gid = se_ids::global(se_ids::BANK_SYSREG, se_ids::LOOP_2000);
    assert!(status::wait_se(gid), "nothing playing yet");
    post(AudioRequest::PlayGlobalSe { id: gid });
    assert!(!status::wait_se(gid), "a posted PlaySe counts as started (WaitSe in the same frame must block)");
    for r in drain() {
        rt.handle(&r);
    }
    rt.update(0.5);
    assert!(!status::wait_se(gid), "looping SE still playing");
    // a second instance of the same id: StopSe releases only the first (SeFind2 -> SeRelease)
    rt.handle(&AudioRequest::PlayGlobalSe { id: gid });
    rt.handle(&AudioRequest::StopSe { id: gid });
    rt.update(1.0);
    assert!(!status::wait_se(gid), "the second instance keeps playing");
    rt.handle(&AudioRequest::StopSe { id: gid });
    rt.update(1.0);
    assert!(status::wait_se(gid), "both instances released");
    // WaitBgm: PlayBgm -> loaded, not finished; stop -> finished
    rt.handle(&AudioRequest::StopAll);
    rt.handle(&AudioRequest::LoadBgm { name: "BGM601".into() });
    post(AudioRequest::PlayBgm { index: 0, mode: 0 });
    assert!(!status::wait_bgm(1), "WaitBgm(1) blocks while the song plays / is queued");
    for r in drain() {
        rt.handle(&r);
    }
    assert!(status::wait_bgm(2) && !status::wait_bgm(1));
    post(AudioRequest::BgmFade { volume: 0, time: 3 });
    assert!(!status::wait_bgm(0), "fade pending");
    for r in drain() {
        rt.handle(&r);
    }
    assert!(!status::wait_bgm(0));
    rt.update(0.4); // 300 ms fade
    assert!(status::wait_bgm(0), "fade-done event reached WaitBgm(0)");
    rt.handle(&AudioRequest::StopBgm { fade_ms: 0 });
    assert!(status::wait_bgm(1));
    // the script-op helper mirrors CField::CallFunc
    use sh2_audio::hooks::field_wait_op;
    let op = field_wait_op(0x54, |_| 1).unwrap();
    assert!(op.done && op.blocking);
    let op = field_wait_op(0x5b, |i| if i == 0 { gid as i32 } else { 0x80 }).unwrap();
    assert!(op.done && !op.blocking);
    assert!(field_wait_op(0x58, |_| 0).is_none());
}

#[test]
fn battle_menu_ids_reach_sysreg_and_sysbtl() {
    use sh2_audio::se_ids;
    let _g = LOCK.lock().unwrap_or_else(|e| e.into_inner());
    let Some(d) = disc() else { return };
    let mut rt = AudioRuntime::new(AudioEngine::new(OutputKind::Null), Some(d));
    // BtlMenu: HNMSnd::PlaySE(2) = decide (SYSREG); CBattle: HNMSnd::PlaySE(0x02001000) = hit (SYSBTL local 0x1000)
    rt.handle(&AudioRequest::PlayBattleSe { id: se_ids::DECIDE });
    assert!(energy(&mut rt, 0.3) > 0.001);
    rt.handle(&AudioRequest::PlayBattleSe { id: se_ids::BTL_HIT });
    assert!(energy(&mut rt, 0.3) > 0.001);
    assert_eq!(se_ids::battle_global(se_ids::BTL_HIT), 0x0200_1000);
    assert_eq!(se_ids::battle_global(se_ids::CANCEL), 3);
}

#[cfg(feature = "bevy")]
#[test]
fn bevy_plugin_plays_scene_music() {
    use bevy::prelude::*;
    use bevy::state::app::StatesPlugin;
    use sh2_audio::AudioPlugin;
    use sh2_core::game::Scene;
    let _g = LOCK.lock().unwrap_or_else(|e| e.into_inner());
    if disc().is_none() {
        return;
    }
    drain();
    std::env::set_var("SH2_DISC_DIR", std::env::var("SH2_DISC_DIR").unwrap_or_else(|_| JP.to_string()));
    let mut app = App::new();
    app.add_plugins((MinimalPlugins, StatesPlugin)).init_state::<Scene>().add_plugins(AudioPlugin { output: Some(OutputKind::Null) });
    app.update();
    app.world_mut().resource_mut::<NextState<Scene>>().set(Scene::Title);
    app.update();
    app.update();
    assert!(app.world().resource::<AudioRuntime>().stream_playing(), "title jingle");
    // a queued request is drained by the plugin
    post(AudioRequest::PlaySystemSe { id: 1 });
    app.update();
    assert!(app.world().resource::<AudioRuntime>().stats.requests >= 3);
    app.world_mut().resource_mut::<NextState<Scene>>().set(Scene::Battle);
    app.update();
    app.update();
    assert!(app.world().resource::<AudioRuntime>().bgm_playing(), "battle BGM");
    app.world_mut().resource_mut::<NextState<Scene>>().set(Scene::GameOver);
    app.update();
    app.update();
    assert!(!app.world().resource::<AudioRuntime>().bgm_playing());
}

/// Round 5: `PlaySeR` (op 0x5f) plays / fades, the map object sounds start for a listener and stop for the battle, battle banks load by number.
#[test]
fn play_se_r_objse_and_battle_banks() {
    let _g = LOCK.lock().unwrap_or_else(|e| e.into_inner());
    let Some(d) = disc() else { return };
    drain();
    // PlaySeR(0, id, 0x60, 0) ; PlaySeR(4, id, 0, 300) ; PlaySeR(1, ..) is a host query
    assert!(hooks::field_script_op(0x5f, 4, |i| [0, 0x2000_1001u32 as i32, 0x60, 0][i], |_| String::new()));
    assert!(hooks::field_script_op(0x5f, 4, |i| [4, 0x2000_1001u32 as i32, 0, 300][i], |_| String::new()));
    assert!(hooks::field_script_op(0x5f, 4, |i| [1, 0x2000_1001u32 as i32, 0, 0][i], |_| String::new()));
    let reqs = drain();
    assert_eq!(reqs, vec![AudioRequest::PlaySe { id: 0x2000_1001, volume: 0x60 }, AudioRequest::FadeSe { id: 0x2000_1001, volume: 0, time: 300 }]);
    let mut rt = AudioRuntime::new(AudioEngine::new(OutputKind::Null), Some(d));
    rt.handle(&AudioRequest::LoadSe { name: "AP_00_U".into(), slot: 1 });
    rt.handle(&reqs[0]);
    assert!(energy(&mut rt, 0.2) > 1e-4);
    rt.handle(&reqs[1]);
    let _ = energy(&mut rt, 0.5);
    // an object sound: non-positional, play bits set
    let rec = sh2_audio::objse::ObjSeRec { id: 0x2000_1001, kind: 0, flags: 1, points: vec![], extra: [0; 4] };
    rt.handle(&AudioRequest::SetObjSe { slot: 3, rec: Some(rec), one_shot: false });
    rt.update(1.0 / 30.0);
    assert_eq!(rt.objse_count(), 1);
    rt.handle(&AudioRequest::PlayBattleBgm { number: 0x191 });
    rt.update(1.0 / 30.0);
    assert_eq!(rt.objse_count(), 0, "the battle releases the field's object sounds");
    rt.handle(&AudioRequest::LoadBattleBanks { chrs: vec![0, 401], weapons: vec![(0, 0)], voices: vec![0] });
    rt.handle(&AudioRequest::UnloadBattleBanks);
    drain();
}
