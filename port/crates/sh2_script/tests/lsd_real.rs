use sh2_script::lsd::*;
use sh2_script::pkb_compat::PkbSet;

#[test]
fn parse_all_lsd_files() {
    let Some(set) = PkbSet::from_env().or_else(|| PkbSet::open("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)").ok()) else { return };
    for n in ["N003", "N004", "N005", "N006", "N007"] {
        let d = set.read(&format!("LSD/{n}.LSD")).unwrap();
        let f = LsdFile::parse(&d).unwrap();
        assert_eq!(f.tracks[0].tag, *b"LSDC");
        let mut count = 0usize;
        let mut ctrl_events = 0usize;
        let mut last = 0;
        for p in f.packets() {
            count += 1;
            last = p.payload.as_ptr() as usize + p.payload.len() - d.as_ptr() as usize;
            if p.track == 0 {
                let cp = parse_control_packet(p.payload).expect("ctrl");
                ctrl_events += cp.events.len();
            }
        }
        println!("{n}: {} tracks, {} packets, {} events, dur {} ticks", f.tracks.len(), count, ctrl_events, f.header.duration_ticks);
        assert_eq!(last, d.len(), "packet walk must cover the file");
        assert!(ctrl_events > 0);
    }
}

struct Counter {
    reads: usize,
    events: Vec<(u16, f32)>,
}
struct F;
impl HandlerFactory for F {
    fn open(&mut self, _i: usize, _h: &TrackHeader) -> Option<Box<dyn TrackHandler>> {
        Some(Box::new(Counter { reads: 0, events: vec![] }))
    }
}
impl TrackHandler for Counter {
    fn read(&mut self, _h: &TrackHeader, _p: &[u8]) {
        self.reads += 1;
    }
    fn event(&mut self, _h: &TrackHeader, c: u16, t: f32, _dt: f32) {
        if c != code::UPDATE {
            self.events.push((c, t));
        }
    }
}

#[test]
fn play_n004_to_end() {
    let Some(set) = PkbSet::open("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)").ok() else { return };
    let d = set.read("LSD/N004.LSD").unwrap();
    let mut p = LsdPlayer::new(&d, &mut F).unwrap();
    let mut frames = 0;
    while p.state != PlayerState::Done && frames < 100_000 {
        p.poll();
        frames += 1;
    }
    println!("finished after {frames} frames, t={}", p.time);
    assert_eq!(p.state, PlayerState::Done);
    // 603 ticks @30 = ~20s = ~1206 frames at 60 fps
    assert!(frames > 1000 && frames < 1500, "{frames}");
}

#[test]
fn decode_n004_tracks() {
    let Some(set) = PkbSet::from_env().or_else(|| PkbSet::open("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)").ok()) else { return };
    let d = set.read("LSD/N004.LSD").unwrap();
    let c = LsdContent::load(&d, |_, _| true).unwrap();
    assert_eq!(c.tracks.len(), 17);
    // control events: START of the camera / music / script at 0, END of the control track last
    assert_eq!(c.events.last().map(|e| (e.command(), e.track)), Some((code::END, 0)));
    // ANMS 2 = Kalen_a_m: 46 bones with a key every 3 file ticks (2 x 82 rotation / translation keys on ROOT)
    let TrackData::Anim(a) = &c.data[2] else { panic!() };
    assert_eq!(a.model, "Kalen_a_m");
    assert_eq!(a.bones.len(), 46);
    assert_eq!(a.bones[0].name, "ROOT");
    assert_eq!(a.bones[0].rot.len(), 82);
    assert_eq!(a.bones[0].rot[0].t, 0);
    // identity quaternion = (0, 0, 0, 4096)
    assert_eq!(a.bones[0].rot[0].v, [0, 0, 0, 4096]);
    assert_eq!(a.interp_toggles, vec![170, 624]);
    // CAMS: unit quaternions, positions in model units, 183 keys
    let TrackData::Cam(k) = &c.data[4] else { panic!() };
    assert_eq!(k.len(), 183);
    for key in k.iter() {
        let l = key.quat.iter().map(|x| x * x).sum::<f32>().sqrt();
        assert!((l - 1.0).abs() < 0.01, "|q| = {l}");
    }
    assert!(k.windows(2).all(|w| w[0].t <= w[1].t));
    // LIPS / LGTS keep their packets
    assert_eq!(c.packets(13).map(|p| p.len()), Some(31));
    // MDLS payload is a complete model
    assert!(c.raw(1).map(|r| r.len()).unwrap_or(0) > 100_000);
}
