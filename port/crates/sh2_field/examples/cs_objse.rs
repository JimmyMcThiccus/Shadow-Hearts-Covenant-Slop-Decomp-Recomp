//! `cs_objse [--us] [MAP ...]` (round 5 CS): every map's `OBJSE` chunk through the audio runtime (null output): banks found, sounds that
//! resolve to an SE of the loaded banks, how many play with the listener at the map's entry point 0.
use sh2_audio::objse::{Listener, ObjSeChunk};
use sh2_audio::{AudioEngine, AudioRequest, AudioRuntime, OutputKind};
use sh2_field::mps::Mps;
use sh2_field::pkb_compat::PkbSet;

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|s| s == "--us");
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).expect("disc env");
    let set = PkbSet::open(&dir).unwrap();
    let names: Vec<String> = a.iter().filter(|s| !s.starts_with("--")).cloned().collect();
    let maps: Vec<String> = if names.is_empty() {
        set.list_dir_while("FIELD/MPS", |_| true).unwrap_or_default().into_iter().filter(|e| e.name.ends_with(".MPS")).map(|e| e.name.trim_end_matches(".MPS").to_string()).collect()
    } else {
        names
    };
    let (mut with, mut sounds, mut resolved, mut playing, mut missing_banks) = (0, 0, 0, 0, Vec::new());
    for m in &maps {
        let Some(raw) = set.read(&format!("FIELD/MPS/{m}.MPS")) else { continue };
        let Ok(mps) = Mps::parse(raw) else { continue };
        let Some(c) = mps.find(sh2_field::mps::tags::OBJSE) else { continue };
        let chunk = mps.data[c.data_start()..].to_vec();
        let parsed = ObjSeChunk::parse(&chunk);
        with += 1;
        sounds += parsed.records.len();
        let disc = sh2_core::fileio::Disc::open(&dir).ok();
        let mut rt = AudioRuntime::new(AudioEngine::new(OutputKind::Null), disc);
        rt.handle(&AudioRequest::MapObjSe { chunk: std::sync::Arc::new(chunk) });
        for b in &parsed.banks {
            if !set.disc().exists(&format!("FIELD/SOUND/SE/{b}.SSE")) {
                missing_banks.push(format!("{m}:{b}"));
            }
        }
        // which ids resolve (a 1-frame play of every record)
        let mut ok = 0;
        for r in &parsed.records {
            let h = sh2_script::audio::SoundBackend::play_se(&mut rt.engine, 0, r.id, &Default::default());
            if h == 0 {
                println!("  {m}: id {:#x} (kind {}, flags {:#x}) does not resolve", r.id, r.kind, r.flags);
            }
            if h != 0 {
                ok += 1;
                sh2_script::audio::SoundBackend::release_se(&mut rt.engine, h, 0);
            }
        }
        resolved += ok;
        let ep = mps.entry_points().ok().and_then(|e| e.first().map(|e| e.pos)).unwrap_or([0.0; 3]);
        rt.handle(&AudioRequest::SetListener { listener: Some(Listener { pos: [ep[0], ep[1] - 20.0, ep[2]], at: [0.0, 0.0, 1.0], scrz: 400.0 }) });
        rt.update(1.0 / 30.0);
        let n = rt.objse_count();
        playing += n;
        println!("{m}: banks {:?}, {} sounds, {} resolve, {} playing at entry 0, kinds {:?}", parsed.banks, parsed.records.len(), ok, n, parsed.records.iter().map(|r| r.kind).collect::<Vec<_>>());
    }
    println!("\n{} maps with OBJSE, {sounds} sounds, {resolved} resolve to a loaded SE, {playing} playing at entry 0; missing banks {:?}", with, missing_banks);
}
