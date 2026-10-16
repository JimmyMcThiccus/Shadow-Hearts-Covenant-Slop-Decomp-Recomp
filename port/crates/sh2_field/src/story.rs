//! Headless story walker: plays the field side of the whole game without a renderer, the way a player would, to find where the
//! port's script engine stops the story.
//!
//! The walker owns a [`GameSession`] and a [`FieldRuntime`] and runs the real map scripts through [`FieldHost`] exactly like
//! `plugin::field_script_tick` / `field_logic_tick` do, with the services the Bevy layer would provide replaced by policies:
//!
//! * dialogue: circle every 12 ticks; selections take the choice of the current [`Policy`] (default 0);
//! * battles (`InvokeBattle*`, never random encounters): won at once, the map is re-entered with `FieldRequest::RESTORE` like `SSHSys`
//!   does after the result screen;
//! * map jumps: the register file is saved (`SaveScriptRegister`) and the next map is built;
//! * the world map: a point is chosen from the `WM` chunk (new points first, then the least visited open point);
//! * menus / shops / the save screen opened by a script are closed at once.
//!
//! When the player has control ("free control": no event job, no window, the control model is under pad control) the walker tries every
//! action a player could take on the map -- step into each enabled event box, examine each examinable box, talk to each displayed model
//! with a talk event, press circle on each look point -- each on a *copy* of the game, and keeps the one that changed the story most
//! (new script register values, new story flags, a scripted battle, a jump to a map not seen yet).  When no action makes progress it
//! takes the exit to the least visited map.  This is a novelty search: it does not know the story, it finds it.
//!
//! Story flags (debug-menu names, `notes/integration/debug_menu.md`): flag n = bit `n & 31` of register word `n >> 5`; 8.. first half
//! chapters, 0x3c.. second half, 0x64.. hidden dungeons.

use std::collections::{BTreeMap, BTreeSet, HashMap};
use std::sync::Arc;

use sh2_core::game::{padbit, FieldRequest};
use sh2_menu::session::{ChrPos, GameSession};
use sh2_script::cscript::PadState;

use crate::host::{BattleReq, FieldHost, FieldTables, MenuReq};
use crate::pkb_compat::PkbSet;
use crate::plugin::{read_field_t, FieldRuntime};
use crate::worldmap::{point_state, RetailWorldTable};

/// Copy of the session state the scripts can see (the session itself is a Bevy resource without `Clone`).
pub fn clone_session(s: &GameSession) -> GameSession {
    GameSession {
        save: s.save.clone(),
        map: s.map.clone(),
        chr_pos: s.chr_pos.clone(),
        regs: s.regs.clone(),
        play_ms: s.play_ms,
        needs_party_init: s.needs_party_init,
        in_game: s.in_game,
        toast: None,
        distance: s.distance,
        battles_won: s.battles_won,
        ssh_sys: s.ssh_sys,
    }
}

/// A walk checkpoint: everything needed to resume at a map entry (`--load`).
/// Format: `SH2WALK1`, then length-prefixed blobs: map name, entry (i32), registers, save file (`SaveFile::to_bytes`), the demo-shaped `BTL0` copy,
/// the `ssh_sys` bytes, the saved position (`map NUL` + 4 floats, or empty).
pub fn write_checkpoint(path: &std::path::Path, s: &GameSession, map: &str, entry: i32) -> std::io::Result<()> {
    let mut out = b"SH2WALK1".to_vec();
    let mut blob = |b: &[u8]| {
        out.extend_from_slice(&(b.len() as u32).to_le_bytes());
        out.extend_from_slice(b);
    };
    blob(map.as_bytes());
    blob(&entry.to_le_bytes());
    blob(&s.regs.iter().flat_map(|w| w.to_le_bytes()).collect::<Vec<u8>>());
    blob(&s.save.to_bytes());
    blob(&s.save.btl.data);
    blob(&s.ssh_sys);
    let cp = s.chr_pos.as_ref().map(|c| {
        let mut v = c.map.as_bytes().to_vec();
        v.push(0);
        for f in [c.pos[0], c.pos[1], c.pos[2], c.yaw] {
            v.extend_from_slice(&f.to_le_bytes());
        }
        v
    });
    blob(&cp.unwrap_or_default());
    std::fs::write(path, out)
}

pub fn read_checkpoint(path: &std::path::Path) -> Option<(GameSession, String, i32)> {
    let d = std::fs::read(path).ok()?;
    if !d.starts_with(b"SH2WALK1") {
        return None;
    }
    let mut p = 8usize;
    let mut next = || -> Option<Vec<u8>> {
        let n = u32::from_le_bytes(d.get(p..p + 4)?.try_into().ok()?) as usize;
        let b = d.get(p + 4..p + 4 + n)?.to_vec();
        p += 4 + n;
        Some(b)
    };
    let map = String::from_utf8(next()?).ok()?;
    let entry = i32::from_le_bytes(next()?.try_into().ok()?);
    let regs: Vec<u32> = next()?.chunks(4).map(|c| u32::from_le_bytes(c.try_into().unwrap())).collect();
    let mut s = GameSession::default();
    s.save = sh2_menu::save::SaveFile::parse(&next()?).ok()?;
    s.save.btl.data = next()?;
    let ss = next()?;
    s.ssh_sys.copy_from_slice(&ss[..4]);
    let cp = next()?;
    if let Some(z) = cp.iter().position(|&c| c == 0) {
        let f = |k: usize| f32::from_le_bytes(cp[z + 1 + k * 4..z + 5 + k * 4].try_into().unwrap());
        s.chr_pos = Some(ChrPos { map: String::from_utf8_lossy(&cp[..z]).to_string(), pos: [f(0), f(1), f(2)], yaw: f(3) });
    }
    s.regs = regs;
    s.in_game = true;
    s.map = map.clone();
    Some((s, map, entry))
}

/// Is story flag `n` set in a register file?
pub fn flag(regs: &[u32], n: u32) -> bool {
    regs.get((n >> 5) as usize).map(|w| (w >> (n & 31)) & 1 != 0).unwrap_or(false)
}

/// Debug-menu name of the scenario flags (first half page = 8 + row, second half = 0x3c + row, hidden = 0x64 + row).
pub fn story_flag_name(n: u32) -> Option<&'static str> {
    const FIRST: [&str; 34] = [
        "Opening", "Apoina part A", "Domremy", "Ardennes Forest", "Paris", "Louvre 1", "Wine cellar", "Louvre 2", "Southampton", "Ronda mine",
        "Wales 1", "Firenze 1", "Manmaria Island", "Firenze 2", "SG Italy branch", "Firenze 3", "Nemeton ruins", "Firenze 4", "Cannes",
        "Sainte-Marguerite", "Cannes 2", "Wales 2", "Hermitage 1", "Petrograd 1", "Hermitage 2", "Petrograd 2", "Goreme Valley", "Mirror castle",
        "Goreme Valley 2", "Corridor of the dead", "Hermitage 3", "Idar Flamme", "Apoina Tower 2", "Graveyard",
    ];
    const SECOND: [&str; 26] = [
        "2nd half opening", "Red-brick warehouse", "Yokohama 1", "Mikasa 1", "Todo lab 1", "Mikasa 2", "Yokohama 2", "Foreign cemetery 1",
        "The other world", "Muhyoan 1", "Nihonbashi 1", "Todo lab 2", "Muhyoan 2", "Nihonbashi 2", "Forest of wind 1", "Inugami village 1",
        "Mt. Fuji", "Graveyard 2", "Inugami village 2", "Foreign cemetery 2", "Azabu mansion", "Inugami village 3", "Queen's garden", "Wales 3",
        "Inugami village 4", "Last dungeon",
    ];
    const HIDDEN: [&str; 6] = ["Killing Stone", "Doll house", "Schwarzwald", "Wakuraba (cut)", "Nemeton depths", "Ring Tower"];
    match n {
        8..=0x29 => FIRST.get((n - 8) as usize).copied(),
        0x3c..=0x55 => SECOND.get((n - 0x3c) as usize).copied(),
        0x64..=0x69 => HIDDEN.get((n - 0x64) as usize).copied(),
        _ => None,
    }
}

/// The story flags (8..0x70) set in a register file.
pub fn story_flags(regs: &[u32]) -> Vec<u32> {
    (8..0x70).filter(|&n| flag(regs, n)).collect()
}

/// The area (map-name prefix) whose script sets a chapter flag with a constant argument (`flag_xref --set-only`), for the chapters the
/// walker has to reach through the world map.  A player learns where to go from the story; the walker takes it from here.
const CHAPTER_AREAS: [(u32, &str); 11] =
    [(0x18, "ND"), (0x1b, "SM"), (0x1c, "CA"), (0x4c, "FU"), (0x4e, "IN"), (0x4f, "GB"), (0x50, "KA"), (0x51, "IN"), (0x52, "QG"), (0x53, "WE"), (0x54, "IN")];

/// The area of the next chapter after the highest one reached (see [`CHAPTER_AREAS`]); `None` when it is not known.
pub fn next_chapter_area(regs: &[u32]) -> Option<&'static str> {
    let top = story_flags(regs).into_iter().filter(|&f| f < 0x64 && story_flag_name(f).is_some()).max()?;
    CHAPTER_AREAS.iter().find(|(f, _)| *f > top && !flag(regs, *f)).map(|x| x.1)
}

/// Disc data the walker needs.
pub struct Env {
    pub pkb: PkbSet,
    pub tables: Arc<FieldTables>,
    pub wm: Option<RetailWorldTable>,
    /// `SSHDAT` tables for the party changes (`SceneInit`, `PCAddInit`) and the new-game party
    pub battle: Option<Arc<sh2_battle::data::BattleData>>,
}

impl Env {
    pub fn open(dir: impl AsRef<std::path::Path>) -> Option<Env> {
        let pkb = PkbSet::open(dir.as_ref()).ok()?;
        let mut t = FieldTables::default();
        if let Some(d) = read_field_t(&pkb) {
            t.from_field_t(&d);
        }
        t.names = crate::plugin::name_lookup(&pkb);
        t.us_rd = crate::plugin::us_regdat(&pkb);
        let wm = std::fs::read(dir.as_ref().join("FIELD.BIN")).ok().and_then(|b| RetailWorldTable::from_field_bin(&b));
        let battle = sh2_battle::pkb_compat::PkbDisc::open(dir.as_ref()).ok().and_then(|d| sh2_battle::data::BattleData::load(&d).ok()).map(Arc::new);
        Some(Env { pkb, tables: Arc::new(t), wm, battle })
    }

    pub fn has_map(&self, map: &str) -> bool {
        self.pkb.read(&format!("FIELD/MPS/{map}.MPS")).is_some()
    }
}

/// How the walker answers prompts during one action.
#[derive(Debug, Clone, Default)]
pub struct Policy {
    /// choice for the k-th selection window of the action (missing = 0)
    pub choices: Vec<usize>,
    /// selections seen so far: number of items of each
    pub seen: Vec<usize>,
    /// result the field ring reports (`RingControl`), `None` = the host default (first area's colour)
    pub ring: Option<i32>,
    /// buttons pressed one by one (every 20 ticks) while no message / selection window is open -- a pad-driven gimmick inside an event
    /// (the Vessel's altar ring: left / right, then circle); the scripted presses replace the default circle presses until used up
    pub pads: Vec<u16>,
}

/// What ended a run of ticks.
#[derive(Debug, Clone, PartialEq)]
pub enum Stop {
    /// the player has control
    Free,
    Jump(String, i32),
    Battle(BattleReq),
    WorldMap(i32, i32, u32),
    GameOver,
    /// `SpecialMenu(7)`: the game is over and goes back to the title (the ending)
    Ending,
    /// the tick budget ran out (a wait the port never releases, or a very long scene)
    Timeout,
}

/// One playable game: session + the runtime of the current map.
#[derive(Clone)]
pub struct Game {
    pub rt: FieldRuntime,
    pub session: GameSessionBox,
    pub battle: Option<Arc<sh2_battle::data::BattleData>>,
    /// party changes applied so far (log)
    pub party_log: Vec<String>,
    /// ticks the current settle has been idle in free-control shape while the root job still runs
    idle_root: u32,
    /// ticks the script has been idle (for the empty-control-slot fallback)
    no_ctrl: u32,
    /// buttons pressed on the next tick (`Action::Pad`)
    pad: u16,
    /// ticks an event job has made no engine call (a script polling `get_pad` for a button other than circle, e.g. MI_02_U's ship
    /// map waits for cross) and the engine-call count of the last tick
    quiet: u32,
    last_calls: u64,
    /// last window text printed (`SH2_WALK_TEXT=MAP`)
    last_txt: String,
}

/// Button minigames the walker plays like a player who reads the screen.  TD_14_U (Todo lab shooting range, "destroy the 30 targets"):
/// targets rise in 8 lanes; the press handler (`0x79a7`) hits the nearest lane whose state (`bss+0x98 + 4i`) is 4 / 5 (up) and whose
/// button mask (`bss+0xf8 + 4i`, the symbol on the stand) matches the press.  A press with no such lane is a miss ("What do you think
/// you're aiming at?!"), so while the range runs nothing else is pressed.  The range runs while some lane state is non-zero (traced:
/// all lanes are 0 before the first target and after the last, at least one is non-zero in between).  `None` = not a minigame moment
/// (normal circle presses), `Some(0)` = hold still.
/// Maps with the Todo lab shooting gallery code (the same lane tables): the range TD_14_U and the corridor gallery of TD_02_U (event 6,
/// the walk-on box 6 of lab 1 -- it also clears the "wrong way" flag 0x1c2f that the lab-2 escape checks at TD_02_U's door).
pub const SHOOTING_MAPS: [&str; 2] = ["TD_14_U", "TD_02_U"];

pub fn minigame_press(rt: &FieldRuntime) -> Option<u16> {
    if !SHOOTING_MAPS.contains(&rt.map.as_str()) || rt.st.msg_active() || rt.st.ui.select.active {
        return None;
    }
    let r = |o: u32| rt.vm.mem.r32(sh2_script::memory::SEG_BSS + o).unwrap_or(0);
    // TD_02_U's gallery (event 6) shows its targets without the lane tables: hold still while it runs (a press is a miss)
    let gallery = rt.map == "TD_02_U" && rt.vm.top_event() == Some(6);
    if !gallery && (0..8).all(|i| r(0x98 + 4 * i) == 0) {
        return None;
    }
    for i in 0..8 {
        let (st, mask) = (r(0x98 + 4 * i), r(0xf8 + 4 * i));
        if (st == 4 || st == 5) && mask != 0 && mask <= 0xffff {
            return Some(mask as u16);
        }
    }
    Some(0)
}

/// `GameSession` wrapper with `Clone`.
pub struct GameSessionBox(pub GameSession);
impl Clone for GameSessionBox {
    fn clone(&self) -> Self {
        GameSessionBox(clone_session(&self.0))
    }
}

/// One thing the player can do at free control.
#[derive(Debug, Clone, PartialEq, Eq, Hash, PartialOrd, Ord)]
pub enum Action {
    /// step into event box `index` (event `id`, argument 1)
    Enter { index: usize, id: u32 },
    /// circle in front of box `index` (argument 4)
    Examine { index: usize, id: u32 },
    /// talk to the model in `slot` (its talk event, arguments `[4, slot]`)
    Talk { slot: usize, id: u32 },
    /// circle on a look point (arguments `[0, point id]`)
    Look { id: u32, point: i32 },
    /// press pad buttons in free control (a map script polling `get_pad` itself, e.g. Mikasa's square = "Switch Parties")
    Pad { bits: u16 },
}

impl Action {
    pub fn event(&self) -> u32 {
        match *self {
            Action::Enter { id, .. } | Action::Examine { id, .. } | Action::Talk { id, .. } | Action::Look { id, .. } => id,
            Action::Pad { .. } => 0,
        }
    }
}

impl std::fmt::Display for Action {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Action::Enter { index, id } => write!(f, "enter box {index} (ev {id})"),
            Action::Examine { index, id } => write!(f, "examine box {index} (ev {id})"),
            Action::Talk { slot, id } => write!(f, "talk slot {slot} (ev {id})"),
            Action::Look { id, point } => write!(f, "look {point:#x} (ev {id})"),
            Action::Pad { bits } => write!(f, "press pad {bits:#06x}"),
        }
    }
}

pub fn save_regs(rt: &FieldRuntime, session: &mut GameSession) {
    let n = rt.vm.n_regs.min(session.regs.len());
    for i in 0..n {
        session.regs[i] = u32::from_le_bytes(rt.vm.mem.regs[i * 4..i * 4 + 4].try_into().unwrap());
    }
}

pub fn regs_of(rt: &FieldRuntime) -> Vec<u32> {
    (0..rt.vm.n_regs).map(|i| u32::from_le_bytes(rt.vm.mem.regs[i * 4..i * 4 + 4].try_into().unwrap())).collect()
}

impl Game {
    /// New game at `map` (retail: `OP_00_U`, entry 0).
    pub fn new_game(env: &Env, map: &str, entry: i32) -> Option<Game> {
        let mut s = GameSession::default();
        s.new_game(map);
        if let Some(b) = env.battle.as_deref() {
            sh2_battle::bridge::init_new_game(b, &mut s);
        }
        Self::enter(env, s, map, entry)
    }

    pub fn enter(env: &Env, session: GameSession, map: &str, entry: i32) -> Option<Game> {
        Self::enter_carry(env, session, map, entry, None)
    }

    /// Enter `map` after a `MapJump` from a map whose models survive (`carry`).
    pub fn enter_carry(env: &Env, mut session: GameSession, map: &str, entry: i32, carry: Option<crate::script_actors::CarriedActors>) -> Option<Game> {
        let prev = std::mem::replace(&mut session.map, map.to_string());
        let mut rt = crate::plugin::build_runtime_carry(&env.pkb, None, Some(env.tables.clone()), map, entry, &session, carry)?;
        rt.st.prev_map = if prev != map { prev } else { session.chr_pos.as_ref().map(|_| String::new()).unwrap_or_default() };
        Some(Game { rt, session: GameSessionBox(session), battle: env.battle.clone(), party_log: vec![], idle_root: 0, no_ctrl: 0, pad: 0, quiet: 0, last_calls: 0, last_txt: String::new() })
    }

    /// Resume a walk checkpoint ([`read_checkpoint`]): the resumed map has no models from the previous one, so the player (slot 0 = the
    /// "controlled character" register byte 0) is carried in, shown.
    pub fn resume(env: &Env, path: &std::path::Path) -> Option<Game> {
        let (s, map, entry) = read_checkpoint(path)?;
        Self::resume_at(env, s, &map, entry)
    }

    pub fn resume_at(env: &Env, s: GameSession, map: &str, entry: i32) -> Option<Game> {
        let id = (s.regs.first().copied().unwrap_or(0) & 0xff) as i32;
        let mut t = crate::script_actors::ActorTable::default();
        t.load(0, &format!("{id:03}"), id, 0);
        let mut c = t.carry_over();
        c.ctrl_shown = true;
        Self::enter_carry(env, s, map, entry, Some(c))
    }

    pub fn map(&self) -> &str {
        &self.rt.map
    }

    pub fn regs(&self) -> Vec<u32> {
        regs_of(&self.rt)
    }

    fn ctrl_ready(&self) -> bool {
        let st = &self.rt.st;
        st.actors.get(st.actors.ctrl as i32).map(|a| a.manual && a.loaded && a.disp).unwrap_or(false)
    }

    /// Free control as `CField::Polling` sees it (see `plugin::field_logic_tick`'s `locked`).
    /// Only fully typed windows that wait for no key are open (a hint / status window the scene leaves up while the player moves, MI_02_U).
    fn msg_settled(st: &crate::host::ScriptState) -> bool {
        st.ui.windows.iter().all(|w| !w.is_open() || w.msg.is_none() || w.typed())
    }

    pub fn is_free(&self) -> bool {
        let st = &self.rt.st;
        (!st.msg_active() || (Self::msg_settled(st) && self.idle_root >= 900))
            && !st.ui.select.active
            && st.mces.state == 0
            && st.warp_fx.is_none()
            && !st.menu_wait
            && self.rt.vm.top_event().is_none()
            && st.event_queue.is_empty()
            && self.ctrl_ready()
            && (!self.rt.vm.is_running() || self.idle_root >= 900)
    }

    /// One 60 Hz tick (script + engine).  Returns a scene change when the script asked for one.
    pub fn tick(&mut self, policy: &mut Policy) -> Option<Stop> {
        let rt = &mut self.rt;
        let session = &mut self.session.0;
        let t = rt.st.ticks as u32;
        let mut press = if t % 12 == 0 { padbit::CIRCLE } else { 0 };
        // a selection is open: put the cursor on the policy's choice and confirm
        if rt.st.ui.select.active && !rt.st.ui.select.items.is_empty() && t % 12 == 0 {
            let k = policy.seen.len();
            let n = rt.st.ui.select.items.len();
            // beyond the policy: the first answer, but a prompt that keeps coming back (a menu-driven gimmick such as Nemeton's stone sled)
            // gets its last answer -- usually "quit" -- after 12 rounds
            let c = policy.choices.get(k).copied().unwrap_or(if k >= 12 { n - 1 } else { 0 }).min(n - 1);
            rt.st.ui.select.cursor = c;
            policy.seen.push(n);
            press = padbit::CIRCLE;
        } else if rt.st.ui.select.active {
            press = 0;
        }
        if self.pad != 0 {
            press |= self.pad;
            self.pad = 0;
        }
        // (a fully typed help window may stay up while the gimmick runs: the presses go on then)
        if !policy.pads.is_empty() && (!rt.st.msg_active() || Self::msg_settled(&rt.st)) && !rt.st.ui.select.active {
            press = if t % 20 == 0 { policy.pads.remove(0) } else { 0 };
        }
        if let Some(b) = minigame_press(rt) {
            press = if t % 12 == 0 { b } else { 0 };
        }
        // an event that makes no engine call for 5 s while no selection is open waits for another button: like a player, try cross,
        // triangle and square in turn (one press every 5 s)
        if rt.vm.top_event().is_some() && rt.st.calls == self.last_calls && !rt.st.ui.select.active {
            self.quiet += 1;
            if self.quiet % 300 == 0 {
                const OTHER: [u16; 3] = [padbit::CROSS, padbit::TRIANGLE, padbit::SQUARE];
                press = OTHER[((self.quiet / 300 - 1) % 3) as usize];
            }
        } else {
            self.quiet = 0;
        }
        self.last_calls = rt.st.calls;
        rt.st.press = press;
        crate::host::tick_state(&mut rt.st, &mut rt.sim);
        rt.sim.update_camera();
        for (id, args) in std::mem::take(&mut rt.st.event_queue) {
            if rt.vm.call_event(id, &args) {
                rt.st.event_running = true;
            }
        }
        rt.vm.set_pad(PadState { raw: press as u32, new_press: press as u32, repeat: 0, consumed: 0 });
        let idle = rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(session) });
        if idle {
            rt.st.event_running = false;
        }
        rt.st.faders.clear();
        rt.st.audio.clear();
        if !rt.st.party_ops.is_empty() {
            let ops = std::mem::take(&mut rt.st.party_ops);
            if let Some(b) = self.battle.as_deref() {
                self.party_log.extend(crate::party::apply_party_ops(b, session, ops));
            }
        }
        if let Ok(pat) = std::env::var("SH2_WALK_ACTOR") {
            // debugging: `MAP:slot` prints that actor every second
            // `MAP:a-b` every slot of the range every 10 ticks
            if let Some((m, s)) = pat.split_once(':') {
                let (lo, hi) = s.split_once('-').map(|(a, b)| (a.parse().unwrap_or(0), b.parse().unwrap_or(0))).unwrap_or((s.parse().unwrap_or(0), s.parse().unwrap_or(0)));
                let every = if lo == hi { 60 } else { 10 };
                if m == rt.map && rt.st.ticks % every == 0 {
                    for slot in lo..=hi {
                        if let Some(a) = rt.st.actors.get(slot) {
                            eprintln!("  [{m} t{}] actor {slot}: pos {:?} mv {:?} paused {} cmd {:?} manual {} disp {} motion {} attach {:#x} press {:?}", rt.st.ticks, a.pos, a.mv, a.paused_move, a.cmd, a.manual, a.disp, a.char_id, a.attach, minigame_press(rt));
                        }
                    }
                }
            }
        }
        if std::env::var_os("SH2_WALK_LANES").is_some() && SHOOTING_MAPS.contains(&rt.map.as_str()) && (rt.st.ticks % 6 == 0 || press != 0) {
            let r = |o: u32| rt.vm.mem.r32(sh2_script::memory::SEG_BSS + o).unwrap_or(0);
            eprintln!("  [{} t{}] press {press:#x} lanes {:?} masks {:x?}", rt.map, rt.st.ticks, (0..8).map(|i| r(0x98 + 4 * i)).collect::<Vec<_>>(), (0..8).map(|i| r(0xf8 + 4 * i)).collect::<Vec<_>>());
        }
        if std::env::var("SH2_WALK_TEXT").map(|m| m == rt.map).unwrap_or(false) {
            // debugging: the text of the open windows when it changes
            let txt: Vec<String> = rt.st.ui.windows.iter().filter(|w| w.is_open() && !w.raw.is_empty()).map(|w| String::from_utf8_lossy(&w.raw).replace('$', " / ")).collect();
            let txt = txt.join(" | ");
            if !txt.is_empty() && txt != self.last_txt {
                eprintln!("  [{} t{}] text: {txt}", rt.map, rt.st.ticks);
                self.last_txt = txt;
            }
        }
        if let Ok(pat) = std::env::var("SH2_WALK_GREP") {
            // debugging: print the engine calls of the map matching `MAP:substring`
            if let Some((m, s)) = pat.split_once(':') {
                if m == rt.map {
                    for l in rt.st.log.drain(..) {
                        if l.contains(s) {
                            eprintln!("  [{m} t{}] {l}", rt.st.ticks);
                        }
                    }
                }
            }
        }
        if rt.st.log.len() > 512 {
            let n = rt.st.log.len() - 256;
            rt.st.log.drain(..n);
        }
        // services of the Bevy layer
        if let Some(req) = rt.st.menu_req.take() {
            rt.st.menu_wait = false;
            if req == MenuReq::GameOver {
                return Some(Stop::GameOver);
            }
            if req == MenuReq::EndToTitle {
                return Some(Stop::Ending);
            }
        }
        rt.st.menu_wait = false;
        if let Some(b) = rt.st.battle.take() {
            return Some(Stop::Battle(b));
        }
        if let Some((w, s, e)) = rt.st.world_map_jump.take() {
            return Some(Stop::WorldMap(w, s, e));
        }
        if let Some((m, e)) = rt.st.pending_jump.take() {
            return Some(Stop::Jump(m, e));
        }
        // a scene that gave control to an empty control slot: load the controlled character (see `FieldHost::ensure_control_model`)
        if !rt.vm.is_running() && !rt.st.msg_active() && rt.st.mces.state == 0 && rt.st.event_queue.is_empty() {
            self.no_ctrl += 1;
            if self.no_ctrl == 120 {
                let id = rt.vm.mem.regs.first().copied().unwrap_or(0) as i32;
                if (FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(session) }).ensure_control_model(id) {
                    self.party_log.push(format!("FALLBACK: control slot empty, loaded character {id}"));
                }
            }
        } else {
            self.no_ctrl = 0;
        }
        if rt.vm.is_running() && rt.vm.top_event().is_none() && (!rt.st.msg_active() || Self::msg_settled(&rt.st)) && !rt.st.ui.select.active && rt.st.mces.state == 0 {
            self.idle_root += 1;
        } else {
            self.idle_root = 0;
        }
        None
    }

    /// Run until free control or a scene change (at most `budget` ticks).
    pub fn settle(&mut self, policy: &mut Policy, budget: u32) -> (Stop, u32) {
        for n in 0..budget {
            if let Some(s) = self.tick(policy) {
                return (s, n);
            }
            if n > 2 && policy.pads.is_empty() && self.is_free() {
                return (Stop::Free, n);
            }
        }
        (Stop::Timeout, budget)
    }

    /// Everything the player could do now.
    pub fn actions(&self) -> Vec<Action> {
        let rt = &self.rt;
        let mut out = BTreeSet::new();
        let mask = rt.sim.evt_mask;
        if let Some(ev) = rt.sim.field.event_boxes.as_ref() {
            for (i, b) in ev.boxes.iter().enumerate() {
                let fl = b.flags & 0xf;
                if b.id <= 0 {
                    continue;
                }
                let has = |id: u32| rt.vm.image.as_ref().map(|im| im.find_event(0, id).is_some()).unwrap_or(false);
                if !has(b.id as u32) {
                    continue;
                }
                if mask & !fl & 1 != 0 && (b.flags & 0x3f) >> 4 == 0 {
                    out.insert(Action::Enter { index: i, id: b.id as u32 });
                }
                if mask & fl & 4 != 0 {
                    out.insert(Action::Examine { index: i, id: b.id as u32 });
                }
            }
        }
        for (slot, a) in rt.st.actors.slots.iter().enumerate() {
            let Some(a) = a else { continue };
            if slot == rt.st.actors.ctrl || !a.loaded || !a.disp || a.event_id == 0 {
                continue;
            }
            out.insert(Action::Talk { slot, id: a.event_id });
        }
        for p in rt.st.look.slots.iter().flatten() {
            if p.event != 0 {
                out.insert(Action::Look { id: p.event, point: p.id });
            }
        }
        // buttons the map's own code tests: `get_pad(2)` `push16 mask` `and` (0xac 02 0c lo hi 76); circle is pressed anyway
        if let Some(im) = rt.vm.image.as_ref() {
            for w in im.code.windows(6) {
                if w[0] == 0xac && w[1] == 2 && w[2] == 0x0c && w[5] == 0x76 {
                    let bits = u16::from_le_bytes([w[3], w[4]]);
                    if bits != 0 && bits & padbit::CIRCLE == 0 {
                        out.insert(Action::Pad { bits });
                    }
                }
            }
        }
        out.into_iter().collect()
    }

    /// Start `a` (the player walks there: the control model is put on the spot first).
    pub fn start(&mut self, a: &Action) -> bool {
        if let Action::Pad { bits } = *a {
            self.pad = bits;
            self.idle_root = 0;
            self.no_ctrl = 0;
            return true;
        }
        let rt = &mut self.rt;
        let mut face: Option<f32> = None;
        let spot = match a {
            Action::Enter { index, .. } | Action::Examine { index, .. } => {
                rt.sim.field.event_boxes.as_ref().and_then(|e| e.boxes.get(*index)).map(|b| [b.center[0], b.center[1], b.center[2]])
            }
            // in front of the model, facing it (treasure chests test the player's direction against the chest's: `GetCharacterInfo(s, 1)`)
            Action::Talk { slot, .. } => rt.st.actors.slots.get(*slot).cloned().flatten().map(|x| {
                face = Some(x.yaw + std::f32::consts::PI);
                [x.pos[0] + 8.0 * x.yaw.sin(), x.pos[1], x.pos[2] + 8.0 * x.yaw.cos()]
            }),
            Action::Look { point, .. } => rt.st.look.slots.iter().flatten().find(|p| p.id == *point).map(|p| p.pos),
            Action::Pad { .. } => None,
        };
        if let Some(p) = spot {
            rt.sim.player.pos = p;
            let ctrl = rt.st.actors.ctrl as i32;
            if let Some(y) = face {
                rt.sim.player.yaw = y;
            }
            if let Some(c) = rt.st.actors.get_mut(ctrl) {
                c.pos = p;
                if let Some(y) = face {
                    c.yaw = y;
                }
            }
        }
        let ok = match *a {
            Action::Enter { id, .. } => rt.vm.call_event(id, &[1]),
            Action::Examine { id, .. } => rt.vm.call_event(id, &[4]),
            Action::Talk { id, slot } => rt.vm.call_event(id, &[4, slot as u32]),
            Action::Look { id, point } => rt.vm.call_event(id, &[0, point as u32]),
            Action::Pad { .. } => false,
        };
        if ok {
            rt.st.event_running = true;
        }
        self.idle_root = 0;
        self.no_ctrl = 0;
        ok
    }
}

/// What one tried action did.
#[derive(Debug, Clone)]
pub struct Outcome {
    pub action: Action,
    pub stop: Stop,
    pub ticks: u32,
    /// register bytes whose new value was never seen before (globally)
    pub novel: usize,
    pub new_flags: Vec<u32>,
    pub changed_bytes: usize,
    pub save_changed: usize,
    /// a treasure was taken (field save flags and the bag both changed): key items such as Mikasa's security keys
    pub picked_up: bool,
    pub policy: Policy,
}

/// A log line of the walk.
#[derive(Debug, Clone)]
pub struct Step {
    pub map: String,
    pub what: String,
}

/// A place where the story did not go on: a timeout (a wait never released) or a dead end.
#[derive(Debug, Clone)]
pub struct Stuck {
    pub map: String,
    pub what: String,
    pub last_calls: Vec<String>,
}

/// The walker.
pub struct Walker<'e> {
    pub env: &'e Env,
    pub game: Game,
    /// every (register byte, value) the applied story has produced
    pub seen: HashSet2,
    pub visits: BTreeMap<String, u32>,
    pub steps: Vec<Step>,
    pub stuck: Vec<Stuck>,
    pub battles: Vec<(String, i32, bool)>,
    /// (map, state signature, action) already applied: never repeat the same action in the same state
    tried: HashMap<(String, u64), BTreeSet<Action>>,
    pub max_settle: u32,
    pub max_action: u32,
    pub verbose: bool,
    pub flags_at: Vec<(u32, String, usize)>,
    /// write a checkpoint at every map entry into this directory (`<n>_<MAP>.walk`)
    pub checkpoint_dir: Option<std::path::PathBuf>,
    /// wall time spent settling maps / trying actions (seconds), ticks simulated by the trials
    pub t_settle: f64,
    /// the walk reached the ending hand-over
    pub ended: bool,
    /// register states reached per map (puzzle wandering) and the wandering budget
    pub seen_states: std::collections::HashSet<(String, u64)>,
    pub puzzle_steps: u32,
    pub puzzle_budget: u32,
    /// world-map point bytes as the walker last saw them
    pub wm_seen: HashMap<u8, u8>,
    /// decisions since the last progress
    pub stagnant: u32,
    /// the game before the last applied action (map, action): a map whose start never gives control back (a minigame the walker cannot
    /// play, e.g. TD_14_U's shooting range) is undone and the action banned
    last_free: Option<(Game, String, String)>,
    pub banned: std::collections::HashSet<(String, u64, String)>,
    /// decisions where another action would also have made progress: (game before, map, action taken).  When the walk stagnates
    /// (a one-way pocket such as TD_16_U / TD_21_U before Todo lab's power is on) it goes back to the latest one and bans the action taken
    pub branches: Vec<(Game, String, String)>,
    pub backtracks: u32,
    last_timeout: bool,
    pub rollbacks: u32,
    /// actions whose trial never gave control back: (map, action) -> last engine calls
    pub stalls: BTreeMap<(String, String), String>,
    /// maps visited since the story last changed (the frontier is everything else)
    pub since_progress: BTreeSet<String>,
    /// exits learnt per map (destinations of trials that left it; "WORLDMAP" for the world map)
    pub exits: BTreeMap<String, BTreeSet<String>>,
    pub t_decide: f64,
    pub trial_ticks: u64,
    /// when the walk stagnates, run a breadth-first puzzle search ([`Walker::search`]) of at most this many states before backtracking
    /// (0 = off); searches from the same state are not repeated
    pub search_budget: usize,
    /// the search also takes the world map (every open point is a successor)
    pub search_world: bool,
    /// a scripted route (`MAP:text` steps, e.g. a walkthrough's puzzle solution): while the next step's map is the current one, the
    /// decision takes the first trial whose `"{action} {choices:?}"` contains `text` and the step is used up (`SH2_WALK_PLAN=a;b;..`)
    pub plan: std::collections::VecDeque<(String, String)>,
    searched: std::collections::HashSet<u64>,
}

pub type HashSet2 = std::collections::HashSet<(u16, u8)>;

fn sig(regs: &[u32]) -> u64 {
    let mut h: u64 = 0xcbf29ce484222325;
    for w in regs {
        h ^= *w as u64;
        h = h.wrapping_mul(0x100000001b3);
    }
    h
}

fn reg_bytes(regs: &[u32]) -> Vec<u8> {
    regs.iter().flat_map(|w| w.to_le_bytes()).collect()
}

impl<'e> Walker<'e> {
    pub fn new(env: &'e Env, game: Game) -> Self {
        let mut w = Walker {
            env,
            game,
            seen: Default::default(),
            visits: Default::default(),
            steps: vec![],
            stuck: vec![],
            battles: vec![],
            tried: Default::default(),
            max_settle: 40_000,
            max_action: 20_000,
            verbose: false,
            flags_at: vec![],
            checkpoint_dir: None,
            t_settle: 0.0,
            since_progress: Default::default(),
            stalls: Default::default(),
            ended: false,
            seen_states: Default::default(),
            puzzle_steps: 0,
            puzzle_budget: 400,
            wm_seen: Default::default(),
            stagnant: 0,
            last_free: None,
            banned: Default::default(),
            branches: vec![],
            backtracks: 0,
            last_timeout: false,
            rollbacks: 0,
            exits: Default::default(),
            t_decide: 0.0,
            trial_ticks: 0,
            search_budget: 0,
            search_world: true,
            plan: std::env::var("SH2_WALK_PLAN")
                .map(|v| v.split(';').filter_map(|p| p.split_once(':')).map(|(m, t)| (m.trim().to_string(), t.to_string())).collect())
                .unwrap_or_default(),
            searched: Default::default(),
        };
        let r = w.game.regs();
        w.mark_seen(&r);
        *w.visits.entry(w.game.map().to_string()).or_default() += 1;
        // the world-map points as they are now (a resumed walk: only what the story opens from here on counts as changed)
        if let Some(wm) = w.env.wm.as_ref() {
            let chunk = w.game.session.0.save.field.find(sh2_menu::save::FieldSave::TAG_WM).map(|c| c.payload.clone()).unwrap_or_default();
            for e in wm.worlds.iter().flat_map(|x| x.list.iter()) {
                w.wm_seen.insert(e.id, chunk.get(0xc + e.id as usize).copied().unwrap_or(0));
            }
        }
        w
    }

    fn mark_seen(&mut self, regs: &[u32]) {
        for (i, b) in reg_bytes(regs).into_iter().enumerate() {
            self.seen.insert((i as u16, b));
        }
    }

    fn log(&mut self, what: String) {
        if self.verbose {
            eprintln!("[{}] {what}", self.game.map());
        }
        self.steps.push(Step { map: self.game.map().to_string(), what });
    }

    fn flush_party(&mut self) {
        let mut l: Vec<String> = std::mem::take(&mut self.game.rt.st.party_log);
        l.extend(std::mem::take(&mut self.game.party_log));
        for x in l {
            self.log(format!("party: {x}"));
        }
    }

    fn note_flags(&mut self, before: &[u32]) {
        self.flush_party();
        let after = self.game.regs();
        for f in story_flags(&after) {
            if !flag(before, f) {
                let step = self.steps.len();
                self.flags_at.push((f, self.game.map().to_string(), step));
                self.log(format!("STORY FLAG {f:#x} {}", story_flag_name(f).unwrap_or("?")));
            }
        }
    }

    /// Apply a scene change to the live game.  Returns false when the walk cannot go on.
    fn apply_stop(&mut self, stop: Stop) -> bool {
        match stop {
            Stop::Free => true,
            Stop::Timeout => {
                let last = self.game.rt.st.log.iter().rev().take(12).cloned().collect::<Vec<_>>();
                let st = &self.game.rt.st;
                let ctrl = st.actors.ctrl;
                let c = st.actors.get(ctrl as i32).map(|a| format!("manual {} loaded {} disp {}", a.manual, a.loaded, a.disp)).unwrap_or("none".into());
                let what = format!(
                    "timeout (event {:?}, ip {:?}, msg {}, select {}, mces {}, menu_wait {}, warp {}, ctrl slot {ctrl}: {c})",
                    self.game.rt.vm.top_event(),
                    self.game.rt.vm.top_ip(),
                    st.msg_active(),
                    st.ui.select.active,
                    st.mces.state,
                    st.menu_wait,
                    st.warp_fx.is_some()
                );
                // the open windows: phase, typing state, glyph / count (a message that never finishes typing holds `KeyWaitStat`)
                let wins: Vec<String> = st
                    .ui
                    .windows
                    .iter()
                    .enumerate()
                    .filter(|(_, w)| w.is_open())
                    .map(|(i, w)| match &w.msg {
                        Some(m) => format!("win {i}{}: {:?} {:?} {}/{} fade {} key {} {:?}", if i == st.ui.cur_win { "*" } else { "" }, w.phase, m.state, m.cur_glyph, m.glyphs.len(), m.fade_from, w.key_pending, String::from_utf8_lossy(&w.raw)) + &format!(" interval {} timer {} glyphs {:?}", m.interval, m.timer, m.glyphs.iter().skip(m.fade_from as usize).take(8).map(|g| (g.width, g.alpha, g.rate)).collect::<Vec<_>>()),
                        None => format!("win {i}: {:?} no message", w.phase),
                    })
                    .collect();
                let what = format!("{what} [{}]", wins.join("; "));
                self.log(what.clone());
                self.stuck.push(Stuck { map: self.game.map().to_string(), what, last_calls: last });
                self.last_timeout = true;
                false
            }
            Stop::GameOver => {
                self.log("game over".into());
                false
            }
            Stop::Ending => {
                self.log("THE END: SpecialMenu(7) hands over to the title".into());
                self.ended = true;
                false
            }
            Stop::Jump(map, entry) => self.goto(&map, entry),
            Stop::Battle(b) => {
                let map = self.game.map().to_string();
                self.log(format!("battle: monster set {} bg {} boss {}", b.monster_set, b.background, b.boss));
                self.battles.push((map.clone(), b.monster_set, b.boss));
                let mut s = clone_session(&self.game.session.0);
                save_regs(&self.game.rt, &mut s);
                s.chr_pos = Some(ChrPos { map: map.clone(), pos: self.game.rt.sim.player.pos, yaw: self.game.rt.sim.player.yaw });
                let map = self.game.rt.st.retail.socket_map.clone().unwrap_or(map);
                s.battles_won += 1;
                // `SSHSys::cbBattleA`: won, came back from a battle
                s.ssh_sys = [2, 1, 0, s.ssh_sys[3]];
                let old_prev = self.game.rt.st.prev_map.clone();
                match Game::enter(self.env, s, &map, FieldRequest::RESTORE) {
                    Some(g) => {
                        self.game = g;
                        if self.game.rt.st.prev_map.is_empty() {
                            self.game.rt.st.prev_map = old_prev;
                        }
                        *self.visits.entry(map.clone()).or_default() += 1;
                        if map != self.steps.last().map(|s| s.map.clone()).unwrap_or_default() {
                            self.log(format!("-> {map} (after the battle)"));
                        }
                        true
                    }
                    None => false,
                }
            }
            Stop::WorldMap(w, sub, extra) => {
                self.log(format!("world map ({w}, {sub}, {extra:#x})"));
                // remember the request in the WM chunk like `WorldMapJumpA`
                match self.pick_world_point(w) {
                    Some((map, entry)) => self.goto_ex(&map, entry, false),
                    None => {
                        let chunk = self.game.session.0.save.field.find(sh2_menu::save::FieldSave::TAG_WM).map(|c| c.payload.clone()).unwrap_or_default();
                        let nz: Vec<String> = chunk.iter().enumerate().skip(0xc).filter(|(_, b)| **b != 0).map(|(i, b)| format!("{}:{b:#x}", i - 0xc)).collect();
                        self.log(format!("world map: no open point (WM bytes {nz:?}, len {})", chunk.len()));
                        false
                    }
                }
            }
        }
    }

    fn goto(&mut self, map: &str, entry: i32) -> bool {
        self.goto_ex(map, entry, true)
    }

    fn goto_ex(&mut self, map: &str, entry: i32, keep_models: bool) -> bool {
        if map == crate::worldmap::WORLDMAP_NAME {
            return self.apply_stop(Stop::WorldMap(-1, 0, 0));
        }
        if !self.env.has_map(map) {
            self.log(format!("jump to {map}:{entry}: map not on the disc"));
            self.stuck.push(Stuck { map: self.game.map().to_string(), what: format!("jump to missing map {map}"), last_calls: vec![] });
            return false;
        }
        let mut s = clone_session(&self.game.session.0);
        save_regs(&self.game.rt, &mut s);
        self.log(format!("-> {map}:{entry}"));
        if let Some(dir) = &self.checkpoint_dir {
            let n = self.steps.len();
            let _ = write_checkpoint(&dir.join(format!("{n:05}_{map}.walk")), &s, map, entry);
        }
        let carry = keep_models.then(|| self.game.rt.st.actors.carry_over());
        match Game::enter_carry(self.env, s, map, entry, carry) {
            Some(g) => {
                self.game = g;
                *self.visits.entry(map.to_string()).or_default() += 1;
                self.since_progress.insert(map.to_string());
                true
            }
            None => false,
        }
    }

    /// Hops from each known map to the nearest frontier map (not visited since the last progress), over the learnt exits (reverse BFS).
    fn frontier_distances(&self) -> HashMap<String, u32> {
        let mut rev: HashMap<&str, Vec<&str>> = HashMap::new();
        for (a, ds) in &self.exits {
            for d in ds {
                rev.entry(d.as_str()).or_default().push(a.as_str());
            }
        }
        let mut dist: HashMap<String, u32> = HashMap::new();
        let mut q = std::collections::VecDeque::new();
        // frontier: every destination we know of that was not visited since the progress (world-map points count as frontier too)
        for ds in self.exits.values() {
            for d in ds {
                if !self.since_progress.contains(d) && !dist.contains_key(d) {
                    dist.insert(d.clone(), 0);
                    q.push_back(d.clone());
                }
            }
        }
        while let Some(m) = q.pop_front() {
            let dm = dist[&m];
            if let Some(srcs) = rev.get(m.as_str()) {
                for s in srcs {
                    if !dist.contains_key(*s) {
                        dist.insert(s.to_string(), dm + 1);
                        q.push_back(s.to_string());
                    }
                }
            }
        }
        dist
    }

    /// The world-map point the walker picks: a changed point, the next chapter's area, the current world, a "new" point, then the open point
    /// whose map was visited least.
    pub fn pick_world_point(&mut self, world: i32) -> Option<(String, i32)> {
        let wm = self.env.wm.as_ref()?;
        let chunk = self.game.session.0.save.field.find(sh2_menu::save::FieldSave::TAG_WM);
        let byte = |id: usize| chunk.and_then(|c| c.payload.get(0xc + id).copied()).unwrap_or(0);
        let mut best: Option<(i64, String, i32)> = None;
        let next_area = next_chapter_area(&self.game.regs());
        for (wi, w) in wm.worlds.iter().enumerate() {
            // a point the story opened / changed since the walker last looked comes first in every world (e.g. KA_09_U, opened in Japan
            // by the foreign cemetery 2 while the screen opens on Europe); then the next chapter's area; then the points of `world`, the one the screen opens on
            // (`WorldMapJump(world, ..)`; < 0 = the remembered one); then the "new" ones
            let here = world < 0 || wi as i32 == world;
            for e in &w.list {
                let st = point_state(byte(e.id as usize));
                if st == 0 || st == 3 || e.portal >= 0 {
                    continue;
                }
                let Some(p) = wm.points.get(e.id as usize) else { continue };
                if p.map.is_empty() {
                    continue;
                }
                let v = *self.visits.get(&p.map).unwrap_or(&0) as i64;
                // changed: the WM byte differs from the last look (or from the walk's start)
                let changed = self.wm_seen.get(&e.id).map(|b| *b != byte(e.id as usize)).unwrap_or(true);
                let goal = next_area.map(|a| p.map.starts_with(a)).unwrap_or(false);
                let score = if changed { 8_000_000 } else { 0 } + if goal { 4_000_000 } else { 0 } + if here { 2_000_000 } else { 0 } + if st == 2 { 1_000_000 } else { 0 } + if self.since_progress.contains(&p.map) { 0 } else { 1000 } - v * 10;
                if best.as_ref().map(|b| score > b.0).unwrap_or(true) {
                    best = Some((score, p.map.clone(), (p.entry & 0xff) as i32));
                }
            }
        }
        for w in &wm.worlds {
            for e in &w.list {
                self.wm_seen.insert(e.id, byte(e.id as usize));
            }
        }
        best.map(|b| (b.1, b.2))
    }

    /// Try `a` (with `policy`) on a copy of the game.
    pub fn try_action(&self, a: &Action, choices: Vec<usize>) -> (Outcome, Game) {
        self.try_action_ring(a, choices, None)
    }

    pub fn try_action_ring(&self, a: &Action, choices: Vec<usize>, ring: Option<i32>) -> (Outcome, Game) {
        self.try_action_pads(a, choices, ring, vec![])
    }

    /// [`Walker::try_action_ring`] with scripted button presses ([`Policy::pads`]).
    pub fn try_action_pads(&self, a: &Action, choices: Vec<usize>, ring: Option<i32>, pads: Vec<u16>) -> (Outcome, Game) {
        let mut g = self.game.clone();
        let before = g.regs();
        let save_before = g.session.0.save.btl.data.clone();
        let field_before = g.session.0.save.field.clone();
        let mut pol = Policy { choices, seen: vec![], ring, pads };
        g.rt.st.ring_override = ring;
        g.start(a);
        let (stop, ticks) = g.settle(&mut pol, self.max_action);
        let after = g.regs();
        let (bb, ab) = (reg_bytes(&before), reg_bytes(&after));
        let mut novel = 0;
        let mut changed = 0;
        for i in 0..ab.len() {
            if ab[i] != bb.get(i).copied().unwrap_or(0) {
                changed += 1;
                if !self.seen.contains(&(i as u16, ab[i])) {
                    novel += 1;
                }
            }
        }
        let new_flags = story_flags(&after).into_iter().filter(|&f| !flag(&before, f)).collect();
        let bag = g.session.0.save.btl.data.iter().zip(save_before.iter()).filter(|(a, b)| a != b).count();
        let field = g.session.0.save.field.chunks != field_before.chunks;
        let sd = bag + field as usize;
        let picked_up = bag > 0 && field;
        (Outcome { action: a.clone(), stop, ticks, novel, new_flags, changed_bytes: changed, save_changed: sd, picked_up, policy: pol }, g)
    }

    fn score(&self, o: &Outcome) -> i64 {
        let mut s = o.new_flags.len() as i64 * 1000 + o.novel as i64 * 20 + (o.save_changed.min(20) as i64) * 2 + o.picked_up as i64 * 400;
        match &o.stop {
            Stop::Battle(_) => s += 300,
            Stop::Jump(m, _) => {
                let v = *self.visits.get(m).unwrap_or(&0) as i64;
                s += if v == 0 && self.env.has_map(m) { 200 } else { -v.min(50) };
                if !self.env.has_map(m) {
                    s -= 10_000;
                }
            }
            Stop::WorldMap(..) => s -= 5,
            Stop::GameOver => s -= 100_000,
            Stop::Ending => s += 1_000_000,
            Stop::Timeout => s -= 50_000,
            Stop::Free => {}
        }
        // a walk-on box whose event changes the state (a flag) before the walker leaves the room: in the game the player walks through
        // it on the way (TD_02_U box 6, event 6, lab 1: sets 0x1c2e and clears the "wrong way" flag 0x1c2f that the lab-2 escape checks);
        // the walker teleports, so it has to take such boxes on purpose -- ahead of a jump into a new map
        if matches!(o.action, Action::Enter { .. }) && o.stop == Stop::Free && o.novel > 0 {
            s += 250;
        }
        // the next chapter is in another area: head for it (a jump into that area; else the world map beats a jump into a new map)
        if let Some(area) = next_chapter_area(&self.game.regs()) {
            if !self.game.map().starts_with(area) {
                match &o.stop {
                    Stop::Jump(m, _) if m.starts_with(area) => s += 300,
                    Stop::WorldMap(..) => s += 250,
                    _ => {}
                }
            }
        }
        s
    }

    /// One decision at free control.  Returns false when the walk ends.
    pub fn decide(&mut self) -> bool {
        let regs = self.game.regs();
        let key = (self.game.map().to_string(), sig(&regs));
        let tried = self.tried.get(&key).cloned().unwrap_or_default();
        let acts = self.game.actions();
        if acts.is_empty() {
            self.log("free control, no action on this map".into());
            self.stuck.push(Stuck { map: self.game.map().to_string(), what: "no action at free control".into(), last_calls: vec![] });
            return false;
        }
        // every action (with the other answers of its first two prompts) on its own copy of the game, in parallel
        let this = &*self;
        let per_action: Vec<Vec<(Outcome, Game)>> = par_map(&acts, |a| {
                    {
                        let (o, g) = this.try_action(a, vec![]);
                        let seen = o.policy.seen.clone();
                        // a field ring was played: also try every other colour it could stop on
                        let ring_cols: Vec<i32> = g.rt.st.ring.as_ref().map(crate::field_ring::possible_results).unwrap_or_default(); // RG: results by ring kind
                        let mut variants = vec![(o, g)];
                        let mut tried_cols = std::collections::BTreeSet::new();
                        for c in ring_cols.iter().skip(1) {
                            if tried_cols.insert(*c) && Some(c) != ring_cols.first() {
                                variants.push(this.try_action_ring(a, vec![], Some(*c)));
                            }
                        }
                        for k in 0..seen.len().min(2) {
                            for c in 1..seen[k].min(4) {
                                let mut ch = vec![0; k];
                                ch.push(c);
                                variants.push(this.try_action(a, ch));
                            }
                        }
                        // a prompt asked again and again: also try the same answer every time (2..4)
                        if seen.len() > 4 {
                            for c in 1..seen[0].min(5) {
                                variants.push(this.try_action(a, vec![c; 12]));
                            }
                        }
                        variants
                    }
        });
        let mut outs: Vec<(i64, Outcome, Game)> = vec![];
        let here = self.game.map().to_string();
        for (a, variants) in acts.iter().zip(per_action) {
            if self.banned.contains(&(here.clone(), sig(&regs), a.to_string())) {
                continue;
            }
            for (o, g) in variants {
                if o.stop == Stop::Timeout {
                    // an action whose script never gives control back: a wait the port does not release (or a very long scene)
                    let key = (self.game.map().to_string(), o.action.to_string());
                    if !self.stalls.contains_key(&key) {
                        let tail: Vec<String> = g.rt.st.log.iter().rev().take(6).cloned().collect();
                        self.stalls.insert(key, tail.join(" | "));
                    }
                }
                self.trial_ticks += o.ticks as u64;
                let mut sc = self.score(&o);
                if tried.contains(a) {
                    sc -= 400;
                }
                outs.push((sc, o, g));
            }
        }
        outs.sort_by(|a, b| b.0.cmp(&a.0));
        if std::env::var_os("SH2_WALK_TRIALS").is_some() {
            for (sc, o, _) in &outs {
                eprintln!("    trial {} {:?}{}: {:?} after {} ticks score {sc} novel {} flags {:?}", o.action, o.policy.choices, o.policy.ring.map(|r| format!(" ring {r}")).unwrap_or_default(), o.stop, o.ticks, o.novel, o.new_flags);
            }
        }
        let progress = outs.first().map(|o| o.0 > 0).unwrap_or(false);
        // debugging: `SH2_WALK_FORCE=MAP:text[;MAP:text..]` takes the first trial on MAP whose action (+ choices) contains `text`
        let forced = std::env::var("SH2_WALK_FORCE").ok().and_then(|v| {
            v.split(';').find_map(|p| {
                let (m, t) = p.split_once(':')?;
                if m != self.game.map() {
                    return None;
                }
                outs.iter().position(|(_, o, _)| format!("{} {:?}", o.action, o.policy.choices).contains(t))
            })
        });
        // the scripted route: the next step on this map.  `text|c1,c2|pads` = the action whose name contains `text`, played with those
        // answers and the buttons `pads` (L R U D, O = circle, X = cross, T = triangle, S = square; see `Policy::pads`)
        let mut scripted: Option<usize> = None;
        if let Some((m, t)) = self.plan.front().cloned().filter(|(m, t)| m == self.game.map() && t.contains('|')) {
            let mut parts = t.split('|');
            let name = parts.next().unwrap_or("").trim().to_string();
            let choices: Vec<usize> = parts.next().unwrap_or("").split(',').filter_map(|c| c.trim().parse().ok()).collect();
            let pads = parse_pads(parts.next().unwrap_or(""));
            // `press pad 0x20|..`: any button, also one the map's code does not test with the pattern `Game::actions` looks for
            let synth = name.strip_prefix("press pad 0x").and_then(|h| u16::from_str_radix(h, 16).ok()).map(|bits| Action::Pad { bits });
            if let Some(a) = acts.iter().find(|a| a.to_string().contains(&name)).cloned().or(synth) {
                let (o, g) = self.try_action_pads(&a, choices, None, pads);
                self.trial_ticks += o.ticks as u64;
                let sc = self.score(&o);
                outs.push((sc, o, g));
                scripted = Some(outs.len() - 1);
            } else {
                self.log(format!("plan step {m}:{t}: no action {name:?} here"));
            }
        }
        let planned = if scripted.is_some() { scripted } else { match self.plan.front() {
            Some((m, t)) if m == self.game.map() => {
                let i = outs.iter().position(|(_, o, _)| format!("{} {:?}", o.action, o.policy.choices).contains(t.as_str()));
                if i.is_none() {
                    let have: Vec<String> = outs.iter().map(|(_, o, _)| format!("{} {:?}", o.action, o.policy.choices)).collect();
                    self.log(format!("plan step {m}:{t} has no trial here ({have:?})"));
                }
                i
            }
            _ => None,
        } };
        if planned.is_some() {
            let (m, t) = self.plan.pop_front().unwrap();
            self.log(format!("plan step {m}:{t} ({} left)", self.plan.len()));
        }
        let pick = if let Some(i) = planned.or(forced) {
            i
        } else if progress {
            0
        } else {
            // nothing new here: head for the frontier -- a map not visited since the story last moved.  Direct exits to such a map first,
            // else the first hop of the shortest path (over the exits learnt so far) to one; ties go to the map visited least overall.
            let here = self.game.map().to_string();
            let fresh = |m: &str| !self.since_progress.contains(m);
            let dist = self.frontier_distances();
            let mut best: Option<(i64, usize)> = None;
            for (i, (_, o, _)) in outs.iter().enumerate() {
                let sc = match &o.stop {
                    Stop::Jump(m, _) if self.env.has_map(m) && *m != here => {
                        let d = if fresh(m) { 0 } else { dist.get(m.as_str()).copied().unwrap_or(1000) as i64 + 1 };
                        -d * 1000 - (*self.visits.get(m).unwrap_or(&0) as i64) * 10 - tried.contains(&o.action) as i64 * 5
                    }
                    Stop::WorldMap(..) => {
                        let d = dist.get("WORLDMAP").copied().unwrap_or(1000) as i64 + 1;
                        -d * 1000 - (self.visits.get("WORLDMAP").copied().unwrap_or(0) as i64) * 10 - 3
                    }
                    Stop::Battle(_) => -10_000_000,
                    _ => continue,
                };
                if best.map(|b| sc > b.0).unwrap_or(true) {
                    best = Some((sc, i));
                }
            }
            // stagnation (no progress for a long time although exits exist): the way on is probably a state puzzle on one of the maps -- reach
            // register states never seen before on the map before taking an exit again
            if self.stagnant > 150 {
                for (i, (_, o, g)) in outs.iter().enumerate() {
                    if matches!(o.stop, Stop::Free) && o.changed_bytes > 0 && !self.seen_states.contains(&(self.game.map().to_string(), sig(&g.regs()))) {
                        best = Some((1, i));
                        break;
                    }
                }
            }
            // no way out: a state puzzle (switches, panels).  Wander the map's state space: prefer an action whose resulting register state was
            // never reached, else any action that changes something (rotating through them), for at most `puzzle_budget` decisions per map
            if best.is_none() && self.puzzle_steps < self.puzzle_budget {
                self.puzzle_steps += 1;
                let mut pick_new: Option<usize> = None;
                let mut pick_any: Vec<usize> = vec![];
                for (i, (_, o, g)) in outs.iter().enumerate() {
                    if !matches!(o.stop, Stop::Free) || o.changed_bytes == 0 {
                        continue;
                    }
                    let s = (self.game.map().to_string(), sig(&g.regs()));
                    if !self.seen_states.contains(&s) && pick_new.is_none() {
                        pick_new = Some(i);
                    }
                    pick_any.push(i);
                }
                if let Some(i) = pick_new.or_else(|| (!pick_any.is_empty()).then(|| pick_any[self.puzzle_steps as usize % pick_any.len()])) {
                    best = Some((0, i));
                }
            }
            match best {
                Some((_, i)) => i,
                None => {
                    self.log(format!("dead end: {} actions, none changes anything or leaves", acts.len()));
                    self.stuck.push(Stuck { map: self.game.map().to_string(), what: format!("dead end ({} actions tried)", acts.len()), last_calls: vec![] });
                    return false;
                }
            }
        };
        // learn the exits of this map (every trial that left it)
        for (_, o, _) in &outs {
            if let Stop::Jump(m, _) = &o.stop {
                self.exits.entry(self.game.map().to_string()).or_default().insert(m.clone());
            }
            if let Stop::WorldMap(..) = &o.stop {
                self.exits.entry(self.game.map().to_string()).or_default().insert("WORLDMAP".into());
            }
        }
        // another progressing action exists: remember the way back
        if progress && outs.iter().enumerate().any(|(i, x)| i != pick && x.0 > 0 && x.1.action != outs[pick].1.action) {
            if self.branches.len() >= 24 {
                self.branches.remove(0);
            }
            self.branches.push((self.game.clone(), self.game.map().to_string(), outs[pick].1.action.to_string()));
        }
        let (sc, o, g) = outs.swap_remove(pick);
        self.seen_states.insert((self.game.map().to_string(), sig(&g.regs())));
        if o.novel > 0 || !matches!(o.stop, Stop::Free) {
            self.puzzle_steps = 0;
        }
        if o.novel > 0 || !o.new_flags.is_empty() || matches!(o.stop, Stop::Battle(_)) {
            self.stagnant = 0;
        } else {
            self.stagnant += 1;
        }
        if o.novel > 0 || !o.new_flags.is_empty() || matches!(o.stop, Stop::Battle(_)) {
            self.since_progress.clear();
        }
        self.tried.entry(key).or_default().insert(o.action.clone());
        let before = self.game.regs();
        if !matches!(o.stop, Stop::Free) {
            self.last_free = Some((self.game.clone(), self.game.map().to_string(), o.action.to_string()));
        }
        self.game = g;
        let after = self.game.regs();
        self.mark_seen(&after);
        let ch = if o.policy.seen.is_empty() { String::new() } else { format!(" choices {:?} of {:?}", o.policy.choices, o.policy.seen) };
        self.log(format!("{}{ch}: {:?} after {} ticks (score {sc}, novel {}, regs {})", o.action, o.stop, o.ticks, o.novel, o.changed_bytes));
        self.note_flags(&before);
        if matches!(o.stop, Stop::WorldMap(..)) {
            *self.visits.entry("WORLDMAP".into()).or_default() += 1;
        }
        self.apply_stop(o.stop)
    }

    /// Settle the current map (start function, post-battle scene ...).
    pub fn settle(&mut self) -> bool {
        let before = self.game.regs();
        let mut pol = Policy::default();
        let trace = std::env::var("SH2_WALK_TRACE").map(|m| m == self.game.map()).unwrap_or(false);
        if trace {
            self.game.rt.vm.branch_trace = Some(vec![]);
            self.game.rt.st.log.clear();
        }
        let (stop, n) = self.game.settle(&mut pol, self.max_settle);
        if trace {
            eprintln!("== trace {} entry {}: {stop:?}", self.game.map(), self.game.rt.st.map_entry);
            for l in &self.game.rt.st.log {
                eprintln!("  {l}");
            }
            for l in self.game.rt.vm.branch_trace.take().unwrap_or_default() {
                eprintln!("  br {l}");
            }
        }
        let r = self.game.regs();
        self.mark_seen(&r);
        if !matches!(stop, Stop::Free) || self.verbose {
            self.log(format!("settled: {stop:?} after {n} ticks"));
        }
        self.note_flags(&before);
        self.apply_stop(stop)
    }

    /// Walk for at most `decisions` free-control decisions.
    pub fn run(&mut self, decisions: usize) {
        let mut d = 0;
        loop {
            if !self.game.is_free() {
                let t0 = std::time::Instant::now();
                let ok = self.settle();
                self.t_settle += t0.elapsed().as_secs_f64();
                if !ok {
                    // a map that never gives control back: undo the action that led there and never take it again
                    if self.last_timeout && self.rollbacks < 20 {
                        if let Some((g, map, action)) = self.last_free.take() {
                            self.last_timeout = false;
                            self.rollbacks += 1;
                            self.log(format!("rollback: back to {map} before \"{action}\" (banned)"));
                            self.banned.insert((map, sig(&g.regs()), action));
                            self.game = g;
                            continue;
                        }
                    }
                    return;
                }
                continue;
            }
            if d >= decisions {
                self.log("decision budget used up".into());
                return;
            }
            d += 1;
            // stagnation: a breadth-first search for the next story flag from here (state puzzles), then back to the latest decision that
            // had another way on
            if self.stagnant > 80 && self.search_budget > 0 && self.searched.insert(state_key(&self.game)) {
                self.log(format!("search: no progress for {} decisions, breadth-first search (budget {})", self.stagnant, self.search_budget));
                if self.search(self.search_budget) {
                    continue;
                }
                if self.ended {
                    return;
                }
            }
            if self.stagnant > 80 && self.backtracks < 40 {
                if let Some((g, map, action)) = self.branches.pop() {
                    self.backtracks += 1;
                    self.stagnant = 0;
                    self.log(format!("backtrack: no progress for 80 decisions, back to {map} before \"{action}\" (banned)"));
                    self.banned.insert((map, sig(&g.regs()), action));
                    self.game = g;
                    continue;
                }
            }
            let t0 = std::time::Instant::now();
            let ok = self.decide();
            self.t_decide += t0.elapsed().as_secs_f64();
            if !ok {
                return;
            }
        }
    }
}

/// FNV-1a over bytes.
fn fnv(h: &mut u64, b: &[u8]) {
    for &x in b {
        *h ^= x as u64;
        *h = h.wrapping_mul(0x100000001b3);
    }
}

/// What makes two free-control states the same for the puzzle search: map, register file, treasure / world-map chunks and which
/// items the bag holds (key items).  The position on the map is not part of it (every action puts the player on its spot).
pub fn state_key(g: &Game) -> u64 {
    let mut h: u64 = 0xcbf29ce484222325;
    fnv(&mut h, g.map().as_bytes());
    fnv(&mut h, &reg_bytes(&g.regs()));
    let f = &g.session.0.save.field;
    for t in [sh2_menu::save::FieldSave::TAG_TR, sh2_menu::save::FieldSave::TAG_WM] {
        if let Some(c) = f.find(t) {
            fnv(&mut h, &c.payload);
        }
    }
    // the bag as "has / has not" per item (counts, HP / MP and the skill bits change with repeatable events and would make every state new)
    let d = &g.session.0.save.btl.data;
    let bag = d.get(sh2_menu::save::BtlSave::OFF_BAG).copied().unwrap_or(0) as usize * sh2_menu::save::BtlSave::BAG_STRIDE;
    let have: Vec<u8> = (sh2_menu::save::BtlSave::OFF_ITEMS..sh2_menu::save::BtlSave::OFF_SKILL_BITS)
        .filter(|o| !(sh2_menu::save::BtlSave::OFF_ITEM_SEEN..sh2_menu::save::BtlSave::OFF_WEAPONS).contains(o))
        .map(|o| (d.get(bag + o).copied().unwrap_or(0) != 0) as u8)
        .collect();
    fnv(&mut h, &have);
    h
}

/// A node of the puzzle search.
struct SearchNode {
    game: Game,
    /// what led here from the search root
    path: Vec<String>,
}

impl<'e> Walker<'e> {
    /// The world-map points the player could pick in `g` (open, not a portal, with a map): `(map, entry)`.
    pub fn open_world_points(&self, g: &Game) -> Vec<(String, i32)> {
        let Some(wm) = self.env.wm.as_ref() else { return vec![] };
        let chunk = g.session.0.save.field.find(sh2_menu::save::FieldSave::TAG_WM);
        let byte = |id: usize| chunk.and_then(|c| c.payload.get(0xc + id).copied()).unwrap_or(0);
        let mut out: Vec<(String, i32)> = vec![];
        for w in &wm.worlds {
            for e in &w.list {
                let st = point_state(byte(e.id as usize));
                if st == 0 || st == 3 || e.portal >= 0 {
                    continue;
                }
                let Some(p) = wm.points.get(e.id as usize) else { continue };
                let v = (p.map.clone(), (p.entry & 0xff) as i32);
                if std::env::var_os("SH2_WALK_POINTS").is_some() {
                    eprintln!("  point {} id {} WM byte {:#x}", p.map, e.id, byte(e.id as usize));
                }
                if !p.map.is_empty() && self.env.has_map(&p.map) && !out.contains(&v) {
                    out.push(v);
                }
            }
        }
        out
    }

    /// Follow a scene change of a trial game to the next free control (map jumps, scripted battles, the world map: one successor per
    /// open point; at most 8 hops).  Stops the walk cannot go on from give no successor.
    fn follow(&self, g: Game, stop: Stop, path: Vec<String>, hops: u32) -> Vec<(Game, Stop, Vec<String>)> {
        let mut path = path;
        let next = match stop {
            Stop::Free | Stop::Ending => return vec![(g, stop, path)],
            _ if hops >= 8 => return vec![],
            Stop::Jump(map, entry) => {
                if map == crate::worldmap::WORLDMAP_NAME {
                    return self.follow(g, Stop::WorldMap(-1, 0, 0), path, hops + 1);
                }
                if !self.env.has_map(&map) {
                    return vec![];
                }
                let mut s = clone_session(&g.session.0);
                save_regs(&g.rt, &mut s);
                let carry = g.rt.st.actors.carry_over();
                path.push(format!("-> {map}:{entry}"));
                match Game::enter_carry(self.env, s, &map, entry, Some(carry)) {
                    Some(n) => n,
                    None => return vec![],
                }
            }
            Stop::Battle(b) => {
                let map = g.map().to_string();
                let mut s = clone_session(&g.session.0);
                save_regs(&g.rt, &mut s);
                s.chr_pos = Some(ChrPos { map: map.clone(), pos: g.rt.sim.player.pos, yaw: g.rt.sim.player.yaw });
                let map = g.rt.st.retail.socket_map.clone().unwrap_or(map);
                s.battles_won += 1;
                s.ssh_sys = [2, 1, 0, s.ssh_sys[3]];
                let prev = g.rt.st.prev_map.clone();
                path.push(format!("battle: monster set {} -> {map}", b.monster_set));
                match Game::enter(self.env, s, &map, FieldRequest::RESTORE) {
                    Some(mut n) => {
                        if n.rt.st.prev_map.is_empty() {
                            n.rt.st.prev_map = prev;
                        }
                        n
                    }
                    None => return vec![],
                }
            }
            Stop::WorldMap(..) => {
                let mut s = clone_session(&g.session.0);
                save_regs(&g.rt, &mut s);
                let mut out = vec![];
                for (map, entry) in self.open_world_points(&g) {
                    let Some(mut n) = Game::enter(self.env, clone_session(&s), &map, entry) else { continue };
                    let mut p = path.clone();
                    p.push(format!("world map -> {map}:{entry}"));
                    let mut pol = Policy::default();
                    let (st, _) = n.settle(&mut pol, self.max_settle);
                    out.extend(self.follow(n, st, p, hops + 1));
                }
                return out;
            }
            _ => return vec![],
        };
        let mut g = next;
        let mut pol = Policy::default();
        let (st, _) = g.settle(&mut pol, self.max_settle);
        self.follow(g, st, path, hops + 1)
    }

    /// Breadth-first search over the free-control states reachable from the current one (world map included unless `search_world` is
    /// off), until one sets a story
    /// flag that is not set now (or ends the game).  For the state puzzles the novelty walk gets lost in (Mikasa's two-party security keys,
    /// Mt. Fuji's crystal gates, Todo lab 2's power relay): every state is expanded with every action and the other answers of its first
    /// two prompts.  On success the walk continues from the state found and the path is logged; `max_nodes` bounds the expansions.
    pub fn search(&mut self, max_nodes: usize) -> bool {
        // start from free control (a resumed walk is at a map entry)
        for _ in 0..8 {
            if self.game.is_free() {
                break;
            }
            if !self.settle() {
                return false;
            }
        }
        let root_regs = self.game.regs();
        let root_map = self.game.map().to_string();
        let mut seen: std::collections::HashSet<u64> = std::collections::HashSet::new();
        seen.insert(state_key(&self.game));
        let mut queue: std::collections::VecDeque<SearchNode> = std::collections::VecDeque::new();
        queue.push_back(SearchNode { game: self.game.clone(), path: vec![] });
        let mut expanded = 0usize;
        let max_queue: usize = std::env::var("SH2_WALK_QUEUE").ok().and_then(|v| v.parse().ok()).unwrap_or(256);
        let t0 = std::time::Instant::now();
        let goal = |g: &Game, st: &Stop| -> bool { *st == Stop::Ending || story_flags(&g.regs()).iter().any(|&f| !flag(&root_regs, f) && story_flag_name(f).is_some()) };
        while let Some(node) = queue.pop_front() {
            if expanded >= max_nodes {
                break;
            }
            expanded += 1;
            let acts = node.game.actions();
            let w = WalkerView { max_action: self.max_action };
            let wr = &w;
            let ng = &node.game;
            // every action and its prompt variants on a copy, in parallel
            let results: Vec<Vec<(Outcome, Game)>> = par_map(&acts, |a| {
                        {
                            let (o, g) = wr.trial(ng, a, vec![], None);
                            let seen = o.policy.seen.clone();
                            let ring_cols: Vec<i32> = g.rt.st.ring.as_ref().map(crate::field_ring::possible_results).unwrap_or_default();
                            let mut v = vec![(o, g)];
                            for c in ring_cols.iter().skip(1) {
                                v.push(wr.trial(ng, a, vec![], Some(*c)));
                            }
                            for k in 0..seen.len().min(2) {
                                for c in 1..seen[k].min(5) {
                                    let mut ch = vec![0; k];
                                    ch.push(c);
                                    v.push(wr.trial(ng, a, ch, None));
                                }
                            }
                            v
                        }
            });
            for variants in results {
                for (o, g) in variants {
                    self.trial_ticks += o.ticks as u64;
                    if matches!(o.stop, Stop::Timeout | Stop::GameOver) || (matches!(o.stop, Stop::WorldMap(..)) && !self.search_world) {
                        continue;
                    }
                    let mut path = node.path.clone();
                    let ch = if o.policy.choices.is_empty() { String::new() } else { format!(" choices {:?}", o.policy.choices) };
                    path.push(format!("[{}] {}{ch}{}", ng.map(), o.action, o.policy.ring.map(|r| format!(" ring {r}")).unwrap_or_default()));
                    for (g2, stop, path) in self.follow(g, o.stop.clone(), path, 0) {
                    if goal(&g2, &stop) {
                        self.log(format!("search: found after {expanded} states ({:.0} s) from {root_map}, {} steps:", t0.elapsed().as_secs_f64(), path.len()));
                        for p in &path {
                            self.log(format!("  search path: {p}"));
                        }
                        let before = self.game.regs();
                        self.game = g2;
                        *self.visits.entry(self.game.map().to_string()).or_default() += 1;
                        let r = self.game.regs();
                        self.mark_seen(&r);
                        self.note_flags(&before);
                        self.stagnant = 0;
                        self.since_progress.clear();
                        if stop == Stop::Ending {
                            return self.apply_stop(Stop::Ending);
                        }
                        return true;
                    }
                    if !matches!(stop, Stop::Free) {
                        continue;
                    }
                    // the queue holds whole games (~5 MB each): bounded (`SH2_WALK_QUEUE`, default 256, ~1.3 GB)
                    if std::env::var_os("SH2_WALK_KEYDIFF").is_some() {
                        // debugging the state key: register bytes that differ from the parent state
                        let (pb, cb) = (reg_bytes(&ng.regs()), reg_bytes(&g2.regs()));
                        let d: Vec<String> = (0..cb.len()).filter(|&i| pb.get(i) != cb.get(i)).map(|i| format!("{i:#x}:{:#x}>{:#x}", pb.get(i).copied().unwrap_or(0), cb[i])).collect();
                        let bag = ng.session.0.save.btl.data.iter().zip(&g2.session.0.save.btl.data).enumerate().filter(|(_, (a, b))| a != b).map(|(i, _)| format!("{i:#x}")).collect::<Vec<_>>();
                        eprintln!("    keydiff {} -> {} {}: regs {d:?} btl {bag:?}", ng.map(), g2.map(), o.action);
                    }
                    if queue.len() < max_queue && seen.insert(state_key(&g2)) {
                        queue.push_back(SearchNode { game: g2, path });
                    }
                    }
                }
            }
            if self.verbose && expanded % 20 == 0 {
                eprintln!("  search: {expanded} expanded, {} queued, {} states, {:.0} s", queue.len(), seen.len(), t0.elapsed().as_secs_f64());
            }
        }
        self.log(format!("search: nothing after {expanded} states ({} distinct, {:.0} s) from {root_map}", seen.len(), t0.elapsed().as_secs_f64()));
        false
    }
}

/// The parts of the walker a trial needs (shared by the search threads).
struct WalkerView {
    max_action: u32,
}

impl WalkerView {
    fn trial(&self, game: &Game, a: &Action, choices: Vec<usize>, ring: Option<i32>) -> (Outcome, Game) {
        let mut g = game.clone();
        let mut pol = Policy { choices, seen: vec![], ring, pads: vec![] };
        g.rt.st.ring_override = ring;
        g.start(a);
        let (stop, ticks) = g.settle(&mut pol, self.max_action);
        (Outcome { action: a.clone(), stop, ticks, novel: 0, new_flags: vec![], changed_bytes: 0, save_changed: 0, picked_up: false, policy: pol }, g)
    }
}

/// Button names of a plan step / `walk_probe --pads`: `L,R,U,D` (d-pad), `O` circle, `X` cross, `T` triangle, `S` square.
pub fn parse_pads(s: &str) -> Vec<u16> {
    s.split(',')
        .filter_map(|c| match c.trim() {
            "L" => Some(padbit::LEFT),
            "R" => Some(padbit::RIGHT),
            "U" => Some(padbit::UP),
            "D" => Some(padbit::DOWN),
            "O" => Some(padbit::CIRCLE),
            "X" => Some(padbit::CROSS),
            "T" => Some(padbit::TRIANGLE),
            "S" => Some(padbit::SQUARE),
            _ => None,
        })
        .collect()
}

/// `f` over `items` on at most `SH2_WALK_THREADS` (default 8) worker threads, results in order.
pub fn par_map<T: Sync, R: Send>(items: &[T], f: impl Fn(&T) -> R + Sync) -> Vec<R> {
    let n = std::env::var("SH2_WALK_THREADS").ok().and_then(|v| v.parse().ok()).unwrap_or(8usize).max(1).min(items.len().max(1));
    let next = std::sync::atomic::AtomicUsize::new(0);
    let out: Vec<std::sync::Mutex<Option<R>>> = items.iter().map(|_| std::sync::Mutex::new(None)).collect();
    std::thread::scope(|sc| {
        for _ in 0..n {
            sc.spawn(|| loop {
                let i = next.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                let Some(x) = items.get(i) else { break };
                let r = f(x);
                *out[i].lock().unwrap() = Some(r);
            });
        }
    });
    out.into_iter().map(|m| m.into_inner().unwrap().expect("par_map result")).collect()
}
