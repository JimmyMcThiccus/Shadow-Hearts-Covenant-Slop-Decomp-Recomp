//! `cs_census [--us] [--efd] [names...]` : headless census of every LSD file of the disc (round 5 CS).  Per file: duration, track tags,
//! model / map / caption / lips / light / LGDT checks, the `LSCR` script dry-run (every `ex.sub` it calls, ticks 30 / s), unknown
//! control commands, and with `--efd` every `.EFD` track run on the effect VM.  One line per file + a summary; `--csv <file>` writes a table.
use sh2_field::cutscene::{CutsceneData, Playhead};
use sh2_field::cutscene_plugin::{LscrHost, ScriptOut};
use sh2_field::pkb_compat::PkbSet;
use sh2_script::cscript::CScript;
use sh2_script::lsd::{code, LgdtKind, TrackKind};
use std::collections::BTreeMap;

static VIBE_STATS: std::sync::Mutex<BTreeMap<&'static str, usize>> = std::sync::Mutex::new(BTreeMap::new());

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|s| s == "--us");
    let efd = a.iter().any(|s| s == "--efd");
    let csv = a.iter().position(|s| s == "--csv").and_then(|i| a.get(i + 1)).cloned();
    let names: Vec<String> = a.iter().filter(|s| !s.starts_with("--") && Some(*s) != csv.as_ref()).cloned().collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).expect("disc env");
    let set = PkbSet::open(&dir).unwrap();
    let files: Vec<String> = if names.is_empty() {
        let mut v: Vec<String> = set.list_dir_while("LSD", |e| e.name.to_uppercase().ends_with(".LSD")).unwrap_or_default().into_iter().map(|e| e.name.clone()).collect();
        // the other disc of a two-disc set (`SH2_US_DISC2_DIR`): its LSD scenes too
        if let Some(o) = set.disc().other() {
            for (_, files) in o.listing() {
                for (p, _) in files {
                    let up = p.to_uppercase();
                    if up.starts_with("LSD/") && up.ends_with(".LSD") && !v.iter().any(|n| n.eq_ignore_ascii_case(&p[4..])) {
                        v.push(p[4..].to_string());
                    }
                }
            }
        }
        v
    } else {
        names.iter().map(|n| if n.to_uppercase().ends_with(".LSD") { n.clone() } else { format!("{n}.LSD") }).collect()
    };
    let mut total = BTreeMap::<String, usize>::new();
    let mut ops_total = BTreeMap::<(u8, u8), usize>::new();
    let mut problems = Vec::new();
    let mut rows = Vec::new();
    for f in &files {
        let base = f.rsplit('/').next().unwrap().to_string();
        let path = if f.contains('/') { f.clone() } else { format!("LSD/{}", base) };
        let Some(bytes) = set.read(&path) else {
            problems.push(format!("{base}: missing"));
            continue;
        };
        let data = match CutsceneData::load(&path, &bytes) {
            Ok(d) => d,
            Err(e) => {
                problems.push(format!("{base}: load error {e}"));
                continue;
            }
        };
        let mut tags = BTreeMap::<String, usize>::new();
        for t in &data.content.tracks {
            *tags.entry(t.tag_str()).or_default() += 1;
            *total.entry(t.tag_str()).or_default() += 1;
        }
        let mut notes: Vec<String> = data.warnings.clone();
        // unknown control commands / tags
        for t in &data.content.tracks {
            if TrackKind::from_tag(&t.tag) == TrackKind::Unknown && &t.tag != b"SRDT" {
                notes.push(format!("unknown track tag {:?}", t.tag_str()));
            }
        }
        for e in &data.content.events {
            let c = e.command();
            if ![code::START, code::STOP, code::CONTINUE, code::END, code::PAUSE, code::RESUME].contains(&c) {
                notes.push(format!("event cmd {c:#x} on track {}", e.track));
            }
        }
        for (t, r) in &data.staff {
            println!("    staff roll track {t}: {} lines, {} pictures, start {:.1}s, {:.3} px / frame", r.lines.len(), r.images.len(), r.start, r.speed);
        }
        if data.content.tracks.iter().filter(|t| &t.tag == b"SRDT").count() != data.staff.len() {
            notes.push("SRDT track not parsed".into());
        }
        // ANMS without a model
        for (tr, name, _) in &data.bg_anims {
            // does the BG (map model) track move anything?  (bones whose keys change over the scene)
            let moving: Vec<String> = match data.content.data.get(*tr) {
                Some(sh2_script::lsd::TrackData::Anim(ad)) => ad
                    .bones
                    .iter()
                    .filter(|b| b.rot.windows(2).any(|w| w[0].v != w[1].v) || b.pos.windows(2).any(|w| w[0].v != w[1].v))
                    .map(|b| b.name.clone())
                    .collect(),
                _ => vec![],
            };
            *VIBE_STATS.lock().unwrap().entry(if moving.is_empty() { "bg anms static" } else { "bg anms moving" }).or_default() += 1;
            if let (true, Some(sh2_script::lsd::TrackData::Anim(ad))) = (std::env::var_os("CS_BG_KEYS").is_some(), data.content.data.get(*tr)) {
                for b in &ad.bones {
                    let ch: Vec<i32> = b.rot.windows(2).filter(|w| w[0].v != w[1].v).map(|w| w[1].t).chain(b.pos.windows(2).filter(|w| w[0].v != w[1].v).map(|w| w[1].t)).collect();
                    if let (Some(f), Some(l)) = (ch.iter().min(), ch.iter().max()) {
                        println!("  BG {name} bone {} moves t60 {f}..{l} (ticks {}..{})", b.name, f / 2, l / 2);
                    }
                }
            }
            if !moving.is_empty() {
                notes.push(format!("BG ANMS {name} moves {} bones: {:?}", moving.len(), moving.iter().take(6).collect::<Vec<_>>()));
            }
        }
        // lips channels
        for (_, l) in &data.lips {
            for ch in &l.channels {
                match data.models.iter().find(|m| m.name == ch.model) {
                    None => notes.push(format!("LIPS model {} missing", ch.model)),
                    Some(m) => {
                        if !m.model.frames.iter().any(|b| b.name == ch.bone) {
                            notes.push(format!("LIPS bone {}/{} missing", ch.model, ch.bone));
                        }
                    }
                }
            }
        }
        // captions
        let n_cap: usize = data.captions.iter().map(|(_, l)| l.len()).sum();
        for (t, font) in &data.caption_fonts {
            if font.is_none() {
                notes.push(format!("SBTD {t}: no pack font"));
            }
        }
        // maps
        for &t in &data.map_tracks {
            if let Some(raw) = data.content.raw(t) {
                if let Err(e) = sh2_field::mps::Mps::parse(raw.to_vec()) {
                    notes.push(format!("MPS {}: {e:?}", data.content.tracks[t].body_str(0)));
                }
            }
        }
        // LGDT
        let mut lg = BTreeMap::<String, usize>::new();
        for b in &data.lgdt {
            *lg.entry(format!("{:?}", b.kind)).or_default() += 1;
            match b.kind {
                LgdtKind::Image => {
                    if let Err(e) = sh2_gfx::texture::decode_p2_textex(&b.data, 0) {
                        notes.push(format!("LGDT image {}: {e:?}", b.name));
                    }
                }
                LgdtKind::Sound => {
                    if let Err(e) = sh2_audio::sdh::Bank::parse(&b.data) {
                        notes.push(format!("LGDT sound {}: {e:?}", b.name));
                    }
                }
                LgdtKind::Vibe => {
                    // every sequence of the blob through the `CVibe` port: must produce motor output and end (or loop) without running off the data
                    if let Some(vb) = sh2_audio::vibe::VibeBlob::parse(&b.data) {
                        for n in 0..vb.count() {
                            let Some(sq) = vb.sequence(n) else { notes.push(format!("VIBE {} seq {n}: bad offset", b.name)); continue };
                            let mut man = sh2_audio::vibe::VibeMan::default();
                            let mut v = sh2_audio::vibe::Vibe::start(sq, &mut man);
                            let (mut peak, mut end) = (0u8, None);
                            for f in 0..900 {
                                if v.poll(&mut man, 33) {
                                    end = Some(f);
                                    break;
                                }
                                peak = peak.max(v.out);
                            }
                            *VIBE_STATS.lock().unwrap().entry(if end.is_some() { "ends" } else { "runs > 30 s (loop)" }).or_default() += 1;
                            if peak == 0 {
                                notes.push(format!("VIBE {} seq {n}: no motor output (end {end:?})", b.name));
                            }
                        }
                    }
                    if std::env::var_os("CS_VIBE_DUMP").is_some() {
                        println!("VIBE {} {} B seqs {}: {:02x?}", b.name, b.data.len(), b.vibe_sequences(), &b.data[..b.data.len().min(96)]);
                    }
                }
                LgdtKind::Other => notes.push(format!("LGDT other {} ({} B, {:02x?})", b.name, b.data.len(), &b.data[..8.min(b.data.len())])),
            }
        }
        // face / visibility keys of the model ANMS tracks (round 6): target 1 = blend-shape sliders, target 8 = `Visible`, target 9 toggles
        for m in &data.models {
            let (mut sk, mut vk, mut tg, mut groups) = (0usize, 0usize, 0usize, std::collections::BTreeSet::new());
            for (tr, _) in &m.anims {
                if let Some(sh2_script::lsd::TrackData::Anim(ad)) = data.content.data.get(*tr) {
                    sk += ad.shape_keys.len();
                    vk += ad.vis_keys.len();
                    tg += ad.interp_toggles.len();
                    groups.extend(ad.shape_keys.iter().map(|k| k.group));
                }
            }
            let shapes: Vec<(String, u8, usize)> = m.model.blend_shapes.iter().map(|b| (b.name.clone(), b.group, b.targets.len())).collect();
            if sk + vk + tg > 0 || !shapes.is_empty() {
                let unmatched: Vec<u8> = groups.iter().copied().filter(|g| !shapes.iter().any(|s| s.1 == *g)).collect();
                notes.push(format!("ANMS {}: shape keys {sk} (groups {groups:?}, no shape for {unmatched:?}), visible keys {vk}, toggles {tg}, shapes {shapes:?}", m.name));
            }
        }
        // script dry run
        let mut ops = BTreeMap::<(u8, u8), usize>::new();
        let mut outs = Vec::<ScriptOut>::new();
        if let Some(img) = data.script_image() {
            match sh2_script::image::ScriptImage::parse(img) {
                Ok(parsed) => {
                    let mut vm = CScript::new(16, 0x200, 5);
                    if vm.init_script(Some("lscr"), img).is_ok() {
                        let mut timed: Vec<u32> = parsed.events.iter().filter(|s| s.kind == 1).flat_map(|s| s.entries.iter().map(|e| e.id)).collect();
                        timed.sort_unstable();
                        let mut head = Playhead::new(&data.content);
                        let script_tr = data.script_track.unwrap();
                        let mut next = 0;
                        let mut started = false;
                        let mut ended = false;
                        let mut host = LscrHost::default();
                        for _ in 0..(data.content.header.duration_ticks + 60) {
                            for ev in head.step(1.0 / 30.0) {
                                if ev.track as usize == script_tr {
                                    match ev.command() {
                                        code::START => {
                                            vm.start_script();
                                            started = true;
                                        }
                                        code::END => {
                                            vm.end_scene();
                                            ended = true;
                                        }
                                        _ => {}
                                    }
                                }
                            }
                            if started && !ended {
                                while let Some(&tick) = timed.get(next) {
                                    if head.ticks() >= tick as f32 {
                                        vm.call_event_t(tick);
                                        next += 1;
                                    } else {
                                        break;
                                    }
                                }
                            }
                            let before = host.out.len();
                            vm.poll(&mut host);
                            for o in &host.out[before..] {
                                if matches!(o, ScriptOut::BgEffectAlpha { .. } | ScriptOut::InvokeBattle | ScriptOut::NextBgm(_) | ScriptOut::FadeBgm(_)) {
                                    notes.push(format!("t {:.2} s: {o:?}", head.ticks() / 30.0));
                                }
                            }
                            if head.finished() {
                                break;
                            }
                        }
                        if next < timed.len() {
                            notes.push(format!("LSCR: {} timed events not reached", timed.len() - next));
                        }
                        for c in host.calls {
                            *ops.entry(c).or_default() += 1;
                            *ops_total.entry(c).or_default() += 1;
                        }
                        outs = host.out;
                    } else {
                        notes.push("LSCR: init failed".into());
                    }
                }
                Err(e) => notes.push(format!("LSCR parse: {e:?}")),
            }
        }
        for o in &outs {
            match o {
                ScriptOut::StartVib { name, .. } => {
                    if !data.lgdt.iter().any(|b| b.name.eq_ignore_ascii_case(name)) {
                        notes.push(format!("StartVib blob {name} missing"));
                    }
                }
                ScriptOut::DspImage { name, .. } => {
                    if !data.lgdt.iter().any(|b| b.name.eq_ignore_ascii_case(name)) {
                        notes.push(format!("DspImage {name} missing"));
                    }
                }
                ScriptOut::BgEffectAlpha { id, alpha, time } => {
                    // the elements it fades: EFFECT records of the scene's maps with `s16 +0 == id` (`CFieldBG::EffectAlpha`)
                    let mut hits = Vec::new();
                    for &t in &data.map_tracks {
                        if let Some(raw) = data.content.raw(t) {
                            let recs = sh2_gfx::effects::sbd::parse_sbd_full(raw).fx_records();
                            let n = recs.iter().filter(|r| r.slot as i32 == *id).count();
                            let fx = sh2_gfx::effects::bgfx::BgFx::new(&recs, 1);
                            hits.push(format!("{} {n} recs (kinds {:?}), unsupported here {:?}, {} elements in the map", data.content.tracks[t].body_str(0), recs.iter().filter(|r| r.slot as i32 == *id).map(|r| r.kind).collect::<Vec<_>>(), fx.unsupported.iter().filter(|u| u.0 as i32 == *id).collect::<Vec<_>>(), fx.len()));
                        }
                    }
                    notes.push(format!("BGEffectAlpha({id}, {alpha}, {time}): {hits:?}"));
                }
                ScriptOut::NextBgm(name) => {
                    if !data.lgdt.iter().any(|b| b.name.eq_ignore_ascii_case(name)) {
                        notes.push(format!("SetNextScript {name}: no LGDT blob"));
                    }
                }
                _ => {}
            }
        }
        // effects
        if efd {
            for &t in &data.efd_tracks {
                let Some(raw) = data.content.raw(t) else { continue };
                let th = &data.content.tracks[t];
                match sh2_battle::effects_bridge::FxProgram::new(t as i32, raw.to_vec(), sh2_battle::effects_bridge::FxContext { gen: vec![], targets: vec![], height: 30.0 }) {
                    Ok(mut p) => {
                        for _ in 0..(th.end_tick.saturating_sub(th.start_tick) + 5).min(900) {
                            p.step();
                            if p.finished {
                                break;
                            }
                        }
                        if !p.host.unknown.is_empty() {
                            notes.push(format!("EFD {t}: unknown {:?}", p.host.unknown));
                        }
                    }
                    Err(e) => notes.push(format!("EFD {t}: {e}")),
                }
            }
        }
        let opsum: Vec<String> = ops.iter().map(|((e, s), n)| format!("{e:02x}.{s:02x}x{n}")).collect();
        println!(
            "{base}: {:.1}s models {} caps {} pcms {} dlby {} movs {} efd {} lgdt {:?} tags {:?} ops [{}]{}",
            data.duration_secs(),
            data.models.len(),
            n_cap,
            data.pcms_track.is_some() as u8,
            data.dlby_track.is_some() as u8,
            tags.get("MOVS").copied().unwrap_or(0),
            data.efd_tracks.len(),
            lg,
            tags,
            opsum.join(" "),
            if notes.is_empty() { String::new() } else { format!("\n    ! {}", notes.join("\n    ! ")) }
        );
        rows.push(format!("{base},{:.1},{},{},{},{},{},{}", data.duration_secs(), data.models.len(), n_cap, data.pcms_track.is_some() as u8, data.dlby_track.is_some() as u8, data.efd_tracks.len(), notes.len()));
    }
    println!("\n{} files; track tags {:?}", files.len(), total);
    println!("VIBE sequences: {:?}", VIBE_STATS.lock().unwrap());
    println!("LSCR ops: {:?}", ops_total.iter().map(|((e, s), n)| format!("{e:02x}.{s:02x}x{n}")).collect::<Vec<_>>());
    for p in &problems {
        println!("PROBLEM {p}");
    }
    if let Some(c) = csv {
        let _ = std::fs::write(c, format!("name,secs,models,captions,pcms,dlby,efd,notes\n{}\n", rows.join("\n")));
    }
}
