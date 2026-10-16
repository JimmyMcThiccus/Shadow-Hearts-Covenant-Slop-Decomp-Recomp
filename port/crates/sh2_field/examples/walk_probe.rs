//! Probe a walk state by hand: `walk_probe --load F [--goto MAP:ENTRY] [--regs 0x110,0x111] [--choices 1,0] [--pads R,R,O]`.
//! Follows `SH2_WALK_PLAN` (see `Walker::plan`) from the checkpoint until the plan is used up, then tries every action of the state
//! reached on its own copy and prints what it does: how it stops, the texts it shows and the register bytes it changes.
use sh2_field::story::{read_checkpoint, Game, Policy, Stop, Walker};

fn main() {
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let a: Vec<String> = std::env::args().skip(1).collect();
    let get = |k: &str| a.iter().position(|x| x == k).and_then(|i| a.get(i + 1)).cloned();
    let env = sh2_field::story::Env::open(std::env::var("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).expect("disc");
    let (s, mut map, mut entry) = read_checkpoint(std::path::Path::new(&get("--load").expect("--load"))).expect("checkpoint");
    if let Some(g) = get("--goto") {
        let (m, e) = g.split_once(':').unwrap_or((&g, "0"));
        map = m.to_string();
        entry = e.parse().unwrap_or(0);
    }
    let regs: Vec<usize> = get("--regs").map(|v| v.split(',').map(|t| usize::from_str_radix(t.trim_start_matches("0x"), 16).unwrap()).collect()).unwrap_or_default();
    let choices: Vec<usize> = get("--choices").map(|v| v.split(',').map(|t| t.parse().unwrap()).collect()).unwrap_or_default();
    let game = Game::resume_at(&env, s, &map, entry).expect("map");
    let mut w = Walker::new(&env, game);
    w.verbose = true;
    let mut n = 0;
    while !w.plan.is_empty() && n < 300 {
        if !w.game.is_free() && !w.settle() {
            break;
        }
        if !w.decide() {
            break;
        }
        n += 1;
    }
    for _ in 0..8 {
        if w.game.is_free() || !w.settle() {
            break;
        }
    }
    let bytes = |g: &Game| -> Vec<u8> { g.regs().iter().flat_map(|w| w.to_le_bytes()).collect() };
    let show = |b: &[u8]| regs.iter().map(|&r| format!("{r:#x}={:#x}", b.get(r).copied().unwrap_or(0))).collect::<Vec<_>>().join(" ");
    let b0 = bytes(&w.game);
    println!("== state: {} after {n} plan decisions ({} steps left), {}", w.game.map(), w.plan.len(), show(&b0));
    for act in w.game.actions() {
        let mut g = w.game.clone();
        // `SH2_PROBE_BRANCHES=text`: print the script branches taken by the actions whose name contains `text`
        let branches = std::env::var("SH2_PROBE_BRANCHES").ok().filter(|t| format!("{act}").contains(t.as_str())).is_some();
        if branches {
            g.rt.vm.branch_trace = Some(vec![]);
        }
        if !g.start(&act) {
            continue;
        }
        let mut pol = Policy { choices: choices.clone(), pads: sh2_field::story::parse_pads(&get("--pads").unwrap_or_default()), ..Default::default() };
        let mut texts: Vec<String> = vec![];
        let mut stop = Stop::Timeout;
        for _ in 0..6000 {
            if let Some(st) = g.tick(&mut pol) {
                stop = st;
                break;
            }
            for t in g.rt.st.ui.windows.iter().filter(|w| w.is_open() && !w.raw.is_empty()).map(|w| String::from_utf8_lossy(&w.raw).replace('$', " / ")) {
                if !texts.contains(&t) && !t.contains("Switch Parties") {
                    texts.push(t);
                }
            }
            if g.is_free() {
                stop = Stop::Free;
                break;
            }
        }
        let b1 = bytes(&g);
        let changed: Vec<String> = (0..b1.len()).filter(|&i| b0.get(i) != b1.get(i)).map(|i| format!("{i:#x}:{:#x}>{:#x}", b0.get(i).copied().unwrap_or(0), b1[i])).collect();
        if let Some(b) = g.rt.vm.branch_trace.take().filter(|_| branches) {
            // repeated decisions (wait loops) once, with a count
            let mut i = 0;
            while i < b.len() {
                let mut n = 1;
                while i + n < b.len() && b[i + n] == b[i] {
                    n += 1;
                }
                println!("    branch {}{}", b[i], if n > 1 { format!(" (x{n})") } else { String::new() });
                i += n;
            }
        }
        println!("{act} {:?}: {stop:?} | {} | regs {changed:?} | {}", pol.seen, texts.join(" // "), show(&b1));
    }
}
