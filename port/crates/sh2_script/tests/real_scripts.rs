//! Smoke tests against retail data (skipped when the disc folder is not present).
use sh2_script::cscript::*;
use sh2_script::opcodes::{FIELD_SUBOPS, LSD_SUBOPS};
use std::io::{Read, Seek, SeekFrom};

fn disc_dir() -> Option<std::path::PathBuf> {
    let p = std::env::var("SH2_DISC_DIR")
        .unwrap_or_else(|_| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
    let p = std::path::PathBuf::from(p);
    p.join("FIELD.PKB").exists().then_some(p)
}

struct LogHost {
    calls: Vec<String>,
}
impl ScriptHost for LogHost {
    fn call_ex(&mut self, ctx: &mut ExCtx<'_>, ex: u8, sub: u8) -> ExResult {
        let name = match ex {
            0xc0 => LSD_SUBOPS.iter().find(|x| x.0 == sub).map(|x| x.1).unwrap_or("?"),
            0xc2 => FIELD_SUBOPS.iter().find(|x| x.0 == sub).map(|x| x.1).unwrap_or("?"),
            _ => "?",
        };
        let args: Vec<String> = (0..ctx.argc).map(|i| format!("{:#x}", ctx.arg(i))).collect();
        self.calls.push(format!("ex{ex:02x}.{sub:02x} {name}({})", args.join(",")));
        ExResult::Void
    }
}

#[test]
fn field_script_start_function_runs() {
    let Some(d) = disc_dir() else { return };
    let mut f = std::fs::File::open(d.join("FIELD.PKB")).unwrap();
    f.seek(SeekFrom::Start(0x21a8000)).unwrap();
    let mut buf = vec![0u8; 0x8000];
    f.read_exact(&mut buf).unwrap();
    let mut vm = CScript::new(64, 0x400, 4000);
    vm.init_script(Some("test"), &buf).expect("parse");
    let mut host = LogHost { calls: vec![] };
    vm.start_script();
    for _ in 0..4 {
        vm.poll(&mut host);
    }
    for c in &host.calls {
        println!("{c}");
    }
    // the start function ends with MapJump (field sub 0x20) in this script or loads flags; at least one host call must happen
    assert!(!host.calls.is_empty());
}

#[test]
fn lsd_script_track_events() {
    let Some(d) = disc_dir() else { return };
    let mut f = std::fs::File::open(d.join("LSD.PKB")).unwrap();
    f.seek(SeekFrom::Start(0x14f0 + 0x20)).unwrap();
    let mut buf = vec![0u8; 0x60];
    f.read_exact(&mut buf).unwrap();
    let mut vm = CScript::new(16, 0x200, 4000);
    vm.init_script(Some("lscr"), &buf).expect("parse");
    let mut host = LogHost { calls: vec![] };
    vm.start_script();
    assert!(vm.call_event_t(0));
    for _ in 0..4 {
        vm.poll(&mut host);
    }
    assert!(vm.call_event_t(0xccb));
    for _ in 0..4 {
        vm.poll(&mut host);
    }
    for c in &host.calls {
        println!("{c}");
    }
    assert_eq!(host.calls.len(), 3, "{:?}", host.calls); // CineMask(1), SetFader(0,2000), SetFader(1,2000)
}

/// Run every script in FIELD.PKB (start function and every by-id event) with a host that always
/// returns Void.  Must never panic or hang.
#[test]
fn all_field_scripts_run_without_panics() {
    let Some(d) = disc_dir() else { return };
    let data = std::fs::read(d.join("FIELD.PKB")).unwrap();
    let mut pos = 0usize;
    let mut n = 0;
    while let Some(i) = data[pos..].windows(4).position(|w| w == b"EVNT") {
        let at = pos + i;
        pos = at + 4;
        if at < 0x20 {
            continue;
        }
        let hdr = at - 0x20;
        if data[hdr + 2] != 1 || data[hdr + 1] != 2 {
            continue;
        }
        let img = &data[hdr..(hdr + 0x80000).min(data.len())];
        let Ok(parsed) = sh2_script::image::ScriptImage::parse(img) else { continue };
        let ids: Vec<u32> = parsed.events.iter().filter(|s| s.kind == 0).flat_map(|s| s.entries.iter().map(|e| e.id)).collect();
        let mut vm = CScript::new(0x400, 0x2000, 20000);
        vm.init_script(Some("t"), img).unwrap();
        let mut host = LogHost { calls: vec![] };
        vm.start_script();
        for _ in 0..50 {
            vm.poll(&mut host);
        }
        for id in ids {
            vm.call_event(id, &[1, 2, 3]);
            for _ in 0..50 {
                vm.poll(&mut host);
            }
        }
        n += 1;
        println!("script @{hdr:#x}: {} events, {} host calls", parsed.events.iter().map(|s| s.entries.len()).sum::<usize>(), host.calls.len());
    }
    assert!(n >= 30, "only {n} scripts parsed");
}
