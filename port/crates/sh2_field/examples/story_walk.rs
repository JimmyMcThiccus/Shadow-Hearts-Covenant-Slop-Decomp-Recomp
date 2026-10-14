//! Headless story walk of the US retail game (see `sh2_field::story`).
//! `cargo run --release -p sh2_field --example story_walk -- [--map OP_00_U] [--entry 0] [--decisions 400] [--flags 8,9,0x322=3] [-v]`
//! Prints the walk, the story flags reached, the scripted battles and where the story got stuck.
use sh2_field::story::{story_flag_name, story_flags, Env, Game, Walker};

fn main() {
    env_logger_init();
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let a: Vec<String> = std::env::args().skip(1).collect();
    let get = |k: &str| a.iter().position(|x| x == k).and_then(|i| a.get(i + 1)).cloned();
    let map = get("--map").unwrap_or_else(|| "OP_00_U".into());
    let entry: i32 = get("--entry").and_then(|v| v.parse().ok()).unwrap_or(0);
    let decisions: usize = get("--decisions").and_then(|v| v.parse().ok()).unwrap_or(400);
    let dir = std::env::var("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR");
    let env = Env::open(&dir).expect("disc");
    let mut s = sh2_menu::session::GameSession::default();
    s.new_game(&map);
    let mut map = map;
    let mut entry = entry;
    let mut loaded = false;
    if let Some(p) = get("--load") {
        let (ls, lm, le) = sh2_field::story::read_checkpoint(std::path::Path::new(&p)).expect("checkpoint");
        s = ls;
        map = lm;
        entry = le;
        loaded = true;
        // `--load F --goto MAP[:ENTRY]`: resume that state on another map (a world-map choice the walker did not make)
        if let Some(g) = get("--goto") {
            let (m, e) = g.split_once(':').unwrap_or((&g, "0"));
            map = m.to_string();
            entry = e.parse().unwrap_or(0);
        }
    }
    // --flags 8,9,0x10 (story flags) and byte=value pairs for register bytes
    if let Some(f) = get("--flags") {
        for t in f.split(',') {
            let p = |v: &str| if let Some(h) = v.strip_prefix("0x") { u32::from_str_radix(h, 16).unwrap() } else { v.parse().unwrap() };
            if let Some((k, v)) = t.split_once('=') {
                let (k, v) = (p(k) as usize, p(v) as u8);
                let mut b = s.regs[k / 4].to_le_bytes();
                b[k % 4] = v;
                s.regs[k / 4] = u32::from_le_bytes(b);
            } else {
                let n = p(t);
                s.regs[(n >> 5) as usize] |= 1 << (n & 31);
            }
        }
    }
    if !loaded {
        if let Some(b) = env.battle.as_deref() {
            sh2_battle::bridge::init_new_game(b, &mut s);
        }
    }
    // a resumed walk has no models from the previous map: give it the player (slot 0 = the "controlled character" register byte 0), shown
    let carry = loaded.then(|| {
        let id = (s.regs.first().copied().unwrap_or(0) & 0xff) as i32;
        let mut t = sh2_field::script_actors::ActorTable::default();
        t.load(0, &format!("{id:03}"), id, 0);
        let mut c = t.carry_over();
        c.ctrl_shown = true;
        c
    });
    let game = Game::enter_carry(&env, s, &map, entry, carry).expect("map");
    let mut w = Walker::new(&env, game);
    w.checkpoint_dir = get("--checkpoints").map(std::path::PathBuf::from);
    if let Some(d) = &w.checkpoint_dir {
        let _ = std::fs::create_dir_all(d);
    }
    w.verbose = a.iter().any(|x| x == "-v") || std::env::var_os("SH2_WALK_STREAM").is_some();
    let t0 = std::time::Instant::now();
    w.run(decisions);
    if !w.verbose {
        for s in &w.steps {
            println!("[{}] {}", s.map, s.what);
        }
    }
    println!("\n== {} steps in {:.1} s, {} maps visited, {} battles", w.steps.len(), t0.elapsed().as_secs_f32(), w.visits.len(), w.battles.len());
    let regs = w.game.regs();
    for f in story_flags(&regs) {
        println!("flag {f:#x} {}", story_flag_name(f).unwrap_or(""));
    }
    println!("maps: {}", w.visits.iter().map(|(m, n)| format!("{m}x{n}")).collect::<Vec<_>>().join(" "));
    // evidence for the coverage matrix (`tools/coverage/out/fs_story_walk.txt`, merged with what earlier walks found): `flag <hex> <map>` / `map <name>` / `end`
    if let Some(p) = get("--evidence") {
        let mut lines: std::collections::BTreeSet<String> = std::fs::read_to_string(&p).unwrap_or_default().lines().map(|l| l.to_string()).collect();
        for (f, m, _) in &w.flags_at {
            if !lines.iter().any(|l| l.starts_with(&format!("flag {f:#06x} "))) {
                lines.insert(format!("flag {f:#06x} {m}"));
            }
        }
        for m in w.visits.keys().filter(|m| *m != "WORLDMAP") {
            lines.insert(format!("map {m}"));
        }
        if w.ended {
            lines.insert("end ED_00_U".into());
        }
        let _ = std::fs::write(&p, lines.into_iter().collect::<Vec<_>>().join("
") + "
");
    }
    for ((m, a), calls) in &w.stalls {
        println!("STALL {m} {a}: {calls}");
    }
    for st in &w.stuck {
        println!("STUCK {} : {}", st.map, st.what);
        for c in st.last_calls.iter().rev() {
            println!("    {c}");
        }
    }
}

fn env_logger_init() {}
