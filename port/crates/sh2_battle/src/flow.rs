//! The `CBattle` phase state machine and the `BtlMenu` command protocol.
//!
//! The original is one gigantic polling function (`CBattle::Polling`, JP 0x004314a0, 105 KB)
//! that switches on `phase` (+0x28) and `step` (+0x2a), delegating the big phases to
//! `TurnBeforeFunc`, `BtlMenuFunc`, `AttackFunc`, `EffectFunc`, `TarotEffectFunc`,
//! `LastBossFunc`.  Presentation (models, camera, effects, windows) is behind [`Host`]; the
//! rules come from [`crate::rules`].
//!
//! What is faithfully ported here:
//! * the phase numbers / transitions ([`Phase`], [`MenuEvent::apply`]),
//! * the command protocol between the command UI and the battle (`BtlMenuCBFunc`),
//! * turn order handling (`TurnEnd`, `GetNextTurnChr2`), Sanity drain at turn start,
//! * win/lose detection and reward calculation,
//! * a simplified action resolver (basic attack → [`rules::physical_damage`]).
//!
//! What is *not* ported yet (needs the effect-code VM of the main executable, `EffectCodeFunc`
//! JP 0x00331960, and the AI script VM): item/magic/skill effect evaluation and enemy AI.  They
//! are stubbed behind [`Host::resolve_effect`] / [`Host::choose_ai_command`].

use crate::rules::{self, Ambush, GlobalMod, Lcg, Rng, StatMod, TurnSlot};

/// `CBattle+0x28`.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
#[repr(u16)]
pub enum Phase {
    /// Load models, place characters, build UI, "surrounded!" messages (`InitSequence`).
    Init = 1,
    /// Pick the next actor (`GetNextTurnChr`), open windows, set cameras.
    TurnSelect = 2,
    /// Turn start: status ticks (poison etc.), Sanity drain (`DecSP`), berserk check
    /// (`TurnBeforeFunc`).
    TurnBefore = 3,
    /// Command selection – PC through `BtlMenu`, enemy through AI (`BtlMenuFunc`).
    Command = 4,
    /// Physical attack execution: move, ring, hits, damage (`AttackFunc`).
    Attack = 5,
    /// Guard / wait (command 7).
    Guard = 6,
    /// Move next to an ally (link / combo preparation) (command 9).
    Link = 7,
    /// Escape attempt (`GetEscapeRate`, `SearchEscapePoint`).
    Escape = 8,
    /// Fusion transformation sequence.
    Fusion = 9,
    /// Item / magic / skill effect resolution (`EffectFunc`).
    Effect = 10,
    /// Judgement-ring skill (kind 4).
    RingSkill = 0xb,
    /// Aroma sequence with ring (`AromaEffectFunc`).
    Aroma = 0xc,
    /// Tarot (empty stub in the demo: `TarotEffectFunc` = 16 bytes).
    Tarot = 0xd,
    /// Final boss special (`LastBossFunc`).
    LastBoss = 0xe,
    /// Pre-end check after an action (fade, music) → Death.
    ActionDone = 0xf,
    /// Death handling, break effects, win/lose test → TurnSelect or Win/Lose.
    Death = 0x10,
    /// Victory (`SetWinCamera1`, result BGM, `MakeResultTrophy`).
    Win = 0x11,
    /// Defeat.
    Lose = 0x12,
    /// Fade out, `Destruct`, return to the field.
    End = 0x13,
}
impl Phase {
    pub fn from_u16(v: u16) -> Option<Self> {
        use Phase::*;
        Some(match v {
            1 => Init,
            2 => TurnSelect,
            3 => TurnBefore,
            4 => Command,
            5 => Attack,
            6 => Guard,
            7 => Link,
            8 => Escape,
            9 => Fusion,
            10 => Effect,
            0xb => RingSkill,
            0xc => Aroma,
            0xd => Tarot,
            0xe => LastBoss,
            0xf => ActionDone,
            0x10 => Death,
            0x11 => Win,
            0x12 => Lose,
            0x13 => End,
            _ => return None,
        })
    }
}

/// `CBattle+0x4c` while `phase == Effect` – what kind of effect is resolved.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
#[repr(i32)]
pub enum EffectKind {
    /// consumable item (`+0x44` = item id)
    Item = 0,
    /// Crest magic / "magic" entry (menu callback 6)
    Magic = 1,
    /// PC special command (menu callback 12 for PCs; `+0x44` = skill id)
    Skill = 2,
    /// Fusion monster ability
    FusionSkill = 3,
    /// judgement-ring skill (phase RingSkill)
    Ring = 4,
    /// menu callback 15 (aroma-like)
    Misc = 6,
    /// port convention: command 11 (fusion) -> phase 9; the effect hook evaluates it as a timed transformation boost
    Fusion = 7,
    /// port convention: Anastasia's `Snap Shot` (menu callback 12 with the camera skill; `+0x48` = target)
    Snap = 8,
}

/// A party member transformed by `Fusion` / `Demon Morph` (retail: `BtlChr+0xb1` bit 1 with the fusion id at `+0xba`): the fused name and
/// portrait replace the character's in the party panel and the Turn Priority cards, the special-command list comes from the fusion's
/// `FUSM` skills (`Battle::fused`), and the SP upkeep (`FUSM+5`) is paid every turn until the character reverts (`Cancel` on the Fusion page,
/// or SP 0).
#[derive(Clone, Debug, PartialEq)]
pub struct Fused {
    /// `FUSM` row
    pub id: i32,
    pub name: String,
    /// the character's own name, restored on revert
    pub orig_name: String,
    /// `FUSM+2`: `BTLDATA/CHR` model number of the fusion monster (also its `FI_%03d` portrait)
    pub model: u32,
    /// SP paid per turn
    pub sp_upkeep: i32,
}

/// Commands emitted by `BtlMenu` through `BtlMenuCallBack` (JP 0x00431150 → `BtlMenuCBFunc`
/// 0x004a93d0).  The numbers are the callback codes; arguments are `(a, b, c, d, e)`.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum MenuEvent {
    /// 0: cursor on character `chr` (focus camera, rebuild the timeline preview)
    FocusChr { chr: i32 },
    /// 1, 22: window sequence finished → advance `step`
    Advance,
    /// 2: step = 2, reset timer
    Reset,
    /// 3: focus camera on the current actor
    CameraActor,
    /// 4: basic / ring attack. `target`, `kind` (attack shape), `skill` (-1 none)
    Attack { actor: i32, target: i32, kind: i32, skill: i32 },
    /// 5: use item `item` on `target`
    Item { item: i32, target: i32 },
    /// 6: magic entry
    Magic { id: i32, target: i32 },
    /// 7: guard
    Guard { actor: i32 },
    /// 9: move/link towards ally
    Link { actor: i32, target: i32 },
    /// 10: run away
    Run,
    /// 11: fusion
    Fusion { id: i32 },
    /// 12: special command (PC → Effect/Skill, fusion monster → Attack or Effect/FusionSkill)
    Special { a: i32, b: i32, enemy_like: bool },
    /// 13: tarot
    Tarot,
    /// 14: aroma (`id` = `GetRegDat(0x43)` combination row of the two oils)
    Aroma { id: i32 },
    /// 17: ring skill
    RingSkill { id: i32, target: i32 },
    /// Anastasia's `Snap Shot` on an enemy (port: effect kind 8; the photo is recorded by the host)
    Snap { target: i32 },
}

/// The command the battle will execute (CBattle+0x44..0x58).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Command {
    pub p44: i32,
    pub p48: i32,
    pub p4c: i32,
    pub p50: i32,
    pub p54: i32,
    pub p58: i32,
}

impl MenuEvent {
    /// Mirror of the `switch` in `BtlMenuCBFunc`: returns `(next phase, step, command)` or
    /// `None` for events that only affect the presentation.
    pub fn apply(&self, actor_is_enemy: bool) -> Option<(Phase, u16, Command)> {
        use MenuEvent::*;
        Some(match *self {
            Attack { actor, target, kind, skill } => {
                let mut c = Command { p44: actor, p48: target, p4c: kind, p50: 0, p54: 0, p58: -1 };
                if skill != -1 {
                    c.p54 = 3;
                    c.p58 = skill;
                }
                if actor_is_enemy {
                    // enemy attacks start at step 0x14 (AI path) with kind 1
                    c.p4c = 1;
                    (Phase::Attack, 0x14, c)
                } else {
                    (Phase::Attack, 0, c)
                }
            }
            Item { item, target } => (Phase::Effect, 0, Command { p44: item, p48: target, p4c: EffectKind::Item as i32, ..Default::default() }),
            Magic { id, target } => (Phase::Effect, 0, Command { p44: id, p48: target, p4c: EffectKind::Magic as i32, ..Default::default() }),
            Guard { actor } => (Phase::Guard, 0, Command { p44: actor, ..Default::default() }),
            Link { actor, target } => (Phase::Link, 0, Command { p44: actor, p48: target, ..Default::default() }),
            Run => (Phase::Escape, 0, Command::default()),
            Fusion { id } => (Phase::Fusion, 0, Command { p44: id, p4c: EffectKind::Fusion as i32, ..Default::default() }),
            Special { a, b, enemy_like } => {
                if !enemy_like {
                    (Phase::Effect, 0, Command { p44: a, p48: b, p4c: EffectKind::Skill as i32, ..Default::default() })
                } else {
                    (Phase::Effect, 0x14, Command { p44: a, p48: b, p4c: EffectKind::FusionSkill as i32, ..Default::default() })
                }
            }
            Tarot => (Phase::Tarot, 0, Command::default()),
            Aroma { id } => (Phase::Aroma, if actor_is_enemy { 0x14 } else { 0 }, Command { p44: id, p4c: EffectKind::Misc as i32, ..Default::default() }),
            Snap { target } => (Phase::Effect, 0, Command { p44: 0, p48: target, p4c: EffectKind::Snap as i32, ..Default::default() }),
            RingSkill { id, target } => (
                Phase::RingSkill,
                if actor_is_enemy { 0x14 } else { 0 },
                Command { p44: id, p48: target, p4c: EffectKind::Ring as i32, ..Default::default() },
            ),
            FocusChr { .. } | Advance | Reset | CameraActor => return None,
        })
    }
}

// ---------------------------------------------------------------------------------------
// Command menu (BtlMenu)
// ---------------------------------------------------------------------------------------

/// Entry indices of `BtlMenuItem_J` (JP .data 0x00651f20) – the labels shown in the command UI.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
#[repr(u8)]
pub enum MenuItem {
    Attack = 0,
    Standard = 1,
    HardHit = 2,
    HighAngle = 3,
    KnockDown = 4,
    ComboMagic = 5,
    CrestMagic = 6,
    Formation = 7,
    Item = 8,
    Guard = 9,
    Link = 10,
    Run = 11,
    Fusion = 12,
    Paranormal = 13,
    Marionette = 14,
    Tarot = 15,
    Aroma = 16,
    Snap = 17,
    Album = 18,
    SwordArt = 19,
    MuscleArts = 20,
    Incarnation = 21,
    Grenade = 22,
    WhiteMagic = 25,
    Special = 26,
}
impl MenuItem {
    /// Japanese labels (for reference / localisation tables).
    pub fn label_jp(self) -> &'static str {
        use MenuItem::*;
        match self {
            Attack => "攻撃",
            Standard => "スタンダード",
            HardHit => "ハードヒット",
            HighAngle => "ハイアングル",
            KnockDown => "ノックダウン",
            ComboMagic => "連携魔法",
            CrestMagic => "紋章魔法",
            Formation => "陣形",
            Item => "アイテム",
            Guard => "防御",
            Link => "連携",
            Run => "逃げる",
            Fusion => "フュージョン",
            Paranormal => "超常現象",
            Marionette => "マリオネット",
            Tarot => "タロット占い",
            Aroma => "アロマ",
            Snap => "スナップ",
            Album => "アルバム",
            SwordArt => "剣技",
            MuscleArts => "マッスルアーツ",
            Incarnation => "降魔化身術",
            Grenade => "手榴弾",
            WhiteMagic => "白魔法",
            Special => "特技",
        }
    }
}

/// What the player can currently do.
#[derive(Clone, Copy, Debug, Default)]
pub struct MenuContext {
    pub can_escape: bool,
    pub has_fusion: bool,
    pub combo_possible: bool,
    pub has_items: bool,
    /// per character special command (PC dependent: Paranormal, Marionette, Tarot, Aroma, Snap, ...)
    pub special: Option<MenuItem>,
}

/// Top-level entries shown for a PC (order of the original: attack row first).
pub fn main_menu(ctx: &MenuContext) -> Vec<MenuItem> {
    let mut v = vec![MenuItem::Attack];
    if let Some(s) = ctx.special {
        v.push(s);
    }
    if ctx.has_fusion {
        v.push(MenuItem::Fusion);
    }
    v.push(MenuItem::Item);
    v.push(MenuItem::Guard);
    if ctx.combo_possible {
        v.push(MenuItem::Link);
    }
    if ctx.can_escape {
        v.push(MenuItem::Run);
    }
    v
}

/// Sub-menu of the `Attack` entry: the four attack shapes (ST/HH/HA/KD, `BtlMes_J[2..5]`).
pub const ATTACK_SHAPES: [MenuItem; 4] =
    [MenuItem::Standard, MenuItem::HardHit, MenuItem::HighAngle, MenuItem::KnockDown];

/// A stack-of-windows command menu (BtlMenu::SetMainMenu/SetTargetMenu/...).
#[derive(Clone, Debug)]
pub enum MenuState {
    Closed,
    Main { cursor: usize, items: Vec<MenuItem> },
    AttackShape { cursor: usize },
    Target { cursor: usize, targets: Vec<usize>, then: PendingAction },
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum PendingAction {
    Attack { shape: i32 },
    Item { item: i32 },
    Magic { id: i32 },
    Special { id: i32 },
    Link,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Button {
    Up,
    Down,
    /// changes the attack shape next to `Attack` (`< Standard >`)
    Left,
    Right,
    Confirm,
    Cancel,
}

pub struct CommandMenu {
    pub state: MenuState,
    pub actor: usize,
    pub ctx: MenuContext,
    /// enemy / ally candidates for target selection
    pub enemies: Vec<usize>,
    pub allies: Vec<usize>,
    stack: Vec<MenuState>,
}

impl CommandMenu {
    pub fn open(actor: usize, ctx: MenuContext, enemies: Vec<usize>, allies: Vec<usize>) -> Self {
        let items = main_menu(&ctx);
        Self { state: MenuState::Main { cursor: 0, items }, actor, ctx, enemies, allies, stack: vec![] }
    }

    fn push(&mut self, s: MenuState) {
        let old = std::mem::replace(&mut self.state, s);
        self.stack.push(old);
    }

    /// Feed a button; returns a [`MenuEvent`] when the menu produced a command.
    pub fn press(&mut self, b: Button) -> Option<MenuEvent> {
        match (&mut self.state, b) {
            (MenuState::Closed, _) => None,
            (MenuState::Main { cursor, items }, Button::Down) => {
                *cursor = (*cursor + 1) % items.len();
                None
            }
            (MenuState::Main { cursor, items }, Button::Up) => {
                *cursor = (*cursor + items.len() - 1) % items.len();
                None
            }
            (MenuState::Main { cursor, items }, Button::Confirm) => {
                let it = items[*cursor];
                match it {
                    MenuItem::Attack => {
                        self.push(MenuState::AttackShape { cursor: 0 });
                        None
                    }
                    MenuItem::Guard => {
                        self.state = MenuState::Closed;
                        Some(MenuEvent::Guard { actor: self.actor as i32 })
                    }
                    MenuItem::Run => {
                        self.state = MenuState::Closed;
                        Some(MenuEvent::Run)
                    }
                    MenuItem::Fusion => {
                        self.state = MenuState::Closed;
                        Some(MenuEvent::Fusion { id: 0 })
                    }
                    MenuItem::Link => {
                        let t = self.allies.iter().copied().filter(|&a| a != self.actor).collect();
                        self.push(MenuState::Target { cursor: 0, targets: t, then: PendingAction::Link });
                        None
                    }
                    MenuItem::Item => {
                        let t = self.allies.clone();
                        self.push(MenuState::Target { cursor: 0, targets: t, then: PendingAction::Item { item: 0 } });
                        None
                    }
                    MenuItem::Tarot => {
                        self.state = MenuState::Closed;
                        Some(MenuEvent::Tarot)
                    }
                    _ => {
                        let t = self.enemies.clone();
                        self.push(MenuState::Target { cursor: 0, targets: t, then: PendingAction::Special { id: it as i32 } });
                        None
                    }
                }
            }
            (MenuState::Main { .. }, Button::Cancel) => None, // the root menu cannot be cancelled
            (_, Button::Left | Button::Right) => None,
            (MenuState::AttackShape { cursor }, Button::Down) => {
                *cursor = (*cursor + 1) % ATTACK_SHAPES.len();
                None
            }
            (MenuState::AttackShape { cursor }, Button::Up) => {
                *cursor = (*cursor + ATTACK_SHAPES.len() - 1) % ATTACK_SHAPES.len();
                None
            }
            (MenuState::AttackShape { cursor }, Button::Confirm) => {
                let shape = *cursor as i32;
                let t = self.enemies.clone();
                self.push(MenuState::Target { cursor: 0, targets: t, then: PendingAction::Attack { shape } });
                None
            }
            (MenuState::Target { cursor, targets, .. }, Button::Down) => {
                if !targets.is_empty() {
                    *cursor = (*cursor + 1) % targets.len();
                }
                None
            }
            (MenuState::Target { cursor, targets, .. }, Button::Up) => {
                if !targets.is_empty() {
                    *cursor = (*cursor + targets.len() - 1) % targets.len();
                }
                None
            }
            (MenuState::Target { cursor, targets, then }, Button::Confirm) => {
                let t = *targets.get(*cursor)? as i32;
                let a = self.actor as i32;
                let ev = match *then {
                    PendingAction::Attack { shape } => MenuEvent::Attack { actor: a, target: t, kind: shape, skill: -1 },
                    PendingAction::Item { item } => MenuEvent::Item { item, target: t },
                    PendingAction::Magic { id } => MenuEvent::Magic { id, target: t },
                    PendingAction::Special { id } => MenuEvent::Special { a: id, b: t, enemy_like: false },
                    PendingAction::Link => MenuEvent::Link { actor: a, target: t },
                };
                self.state = MenuState::Closed;
                Some(ev)
            }
            (_, Button::Cancel) => {
                if let Some(s) = self.stack.pop() {
                    self.state = s;
                }
                None
            }
        }
    }
}

// ---------------------------------------------------------------------------------------
// Battle simulation
// ---------------------------------------------------------------------------------------

/// Presentation + undecoded-VM hooks.
pub trait Host {
    /// Enemy decision (AI scripts `BTLDATA/AIS/Mnnn_nnn.AIS`, VM in `CBattle::AITurnFunc`).
    fn choose_ai_command(&mut self, actor: usize, fighters: &[Option<Fighter>]) -> MenuEvent;
    /// Evaluate an item/magic/skill effect (`EffectCodeFunc`).  Returns damage (+) / heal (-) per target.
    ///
    /// The hook may also change the fighters (MP / SP costs, status, revive); HP changes should be returned so that they produce
    /// [`BattleEvent::Damage`] events.
    fn resolve_effect(&mut self, actor: usize, cmd: &Command, fighters: &mut [Option<Fighter>]) -> Vec<(usize, i32)> {
        let _ = (actor, cmd, fighters);
        Vec::new()
    }
    /// Hook for presentation events (camera, SE, messages, ...).
    fn event(&mut self, _e: &BattleEvent) {}
    /// `PCParam[a].affinity[b]` (`PCParam+0x84 + id * 2`, 0..10000): the friendship that boosts damage while a Link combo runs
    /// (`GetPAtkDamage`: `mult += friendship(attacker, leader) * 0.2 / 10000`; `GetSAtkDamage`: `base += sum friendship / 200` over the other members).
    fn friendship(&self, _a: usize, _b: usize) -> i32 {
        0
    }
    /// The Link combo changed (`CBattle+0x36` members, leader first; empty = no combo).
    fn combo_changed(&mut self, _members: &[usize]) {}
    /// `FUSM` row `id`: `(name, model number, SP upkeep)` of a fusion monster, `None` when the tables are not available.
    fn fusion_info(&self, _id: i32) -> Option<(String, u32, i32)> {
        None
    }
}

/// Scale an effect hit (damage > 0 / heal < 0) by the Judgement Ring grade of the action: 1.0 = no ring or a clean lap, 0.0 = `Miss!!`
/// (the real game then applies nothing), 1.2 = strike.
pub fn scale_by_ring(amount: i32, ring: f32) -> i32 {
    if (ring - 1.0).abs() < 1e-6 {
        return amount;
    }
    (amount as f32 * ring).round() as i32
}

/// A combatant with the data the rules need.
#[derive(Clone, Debug)]
pub struct Fighter {
    pub is_enemy: bool,
    pub char_id: i32,
    pub name: String,
    pub hp: i32,
    pub max_hp: i32,
    pub mp: i32,
    pub max_mp: i32,
    pub sp: i32,
    pub max_sp: i32,
    pub agl: i32,
    pub luc: i32,
    pub patk: i32,
    pub pdef: i32,
    pub satk: i32,
    pub sdef: i32,
    pub element: rules::Element,
    pub variance: f32,
    pub status: Vec<StatMod>,
    pub passives: Vec<StatMod>,
    pub turn: TurnSlot,
    pub sp_frac: i32,
    pub hits_per_attack: i32,
    pub exp: i32,
    pub cash: i32,
    pub drops: [rules::DropSlot; 2],
    pub mon_id: u8,
    pub turns_taken: u32,
    pub removed: bool,
}
impl Fighter {
    pub fn alive(&self) -> bool {
        self.hp > 0 && !self.removed
    }
}

#[derive(Clone, Debug, PartialEq)]
pub enum BattleEvent {
    PhaseChanged(Phase),
    TurnStart { chr: usize },
    Damage { target: usize, amount: i32, critical: bool },
    Defeated { chr: usize },
    SanityDrop { chr: usize, sp: i32 },
    /// `Link`: `leader` hands the slot to `partner` (the partner chooses and acts first, then the leader acts; `CBattle+0x32 / 0x36`)
    ComboLink { leader: usize, partner: usize },
    Escaped,
    /// `GetEscapeRate` failed: the "Couldn't get away!" message (`SetBtlMessage(0x76)`)
    EscapeFailed,
    Victory(rules::BattleReward),
    Defeat,
    /// `TarotApplyCard` result for one target (HP / MP / SP change, Miss, knock-out), see [`crate::tarot`]
    TarotHit(crate::tarot::TarotHit),
    /// *The Tower*: the party's cash is scaled (`variant` 0 x2, 1 x4, 2 half, 3 quarter); the owner of the cash applies [`crate::tarot::cash_after`]
    TarotCash { variant: u8 },
    /// `TurnBeforeFunc` step 0x3b: the actor carries the "cannot act" status (Hanged Man) and loses its turn (`SetBtlMessage(0x78)`)
    CannotAct { chr: usize },
}

pub struct Battle<H: Host> {
    pub phase: Phase,
    pub step: u16,
    pub fighters: Vec<Option<Fighter>>,
    pub actor: Option<usize>,
    pub cmd: Command,
    pub turn_no: i32,
    pub ambush: Ambush,
    pub escape: rules::EscapeMode,
    pub no_evade: bool,
    pub gmod: GlobalMod,
    pub rng: Box<dyn Rng + Send + Sync>,
    pub host: H,
    pub events: Vec<BattleEvent>,
    pub reward: Option<rules::BattleReward>,
    pub trophy: rules::Trophy,
    /// judgement-ring result multiplier applied to the next player attack (`GetJRingAreaResult`); 1.0 = no ring.  Reset after use.
    pub ring: f32,
    /// per-hit ring multipliers (`GetJRingAreaResult(hit)` of the retail game: each hit has its own grade 1 / 2 / 3 -> x1.0 / ramp / x1.2 strike);
    /// empty = use [`Battle::ring`] for every hit.  Reset after use.
    pub ring_hits: Vec<f32>,
    /// combo (`Link`) members that have acted or are acting in this slot, in order (`CBattle+0x36` = len); empty = no combo
    pub combo: Vec<usize>,
    /// members still to act (`CBattle+0x32` pending mask)
    pub combo_queue: Vec<usize>,
    /// per fighter slot: the fusion the party member is transformed into (`Fusion` / `Demon Morph`), see [`Fused`]
    pub fused: Vec<Option<Fused>>,
    /// `CBattle+0x407c / 0x407e / 0x4080`: the active Tarot card ([`crate::tarot`])
    pub tarot: crate::tarot::TarotState,
    /// the Tarot draw in progress during [`Phase::Tarot`]
    pub tarot_run: Option<crate::tarot::TarotRun>,
    pending: Option<MenuEvent>,
}

impl<H: Host> Battle<H> {
    pub fn new(host: H, fighters: Vec<Fighter>, ambush: Ambush, escape: rules::EscapeMode, seed: u64) -> Self {
        let mut f: Vec<Option<Fighter>> = fighters.into_iter().map(Some).collect();
        f.resize(rules::MAX_CHR, None);
        Battle {
            phase: Phase::Init,
            step: 0,
            fighters: f,
            actor: None,
            cmd: Command::default(),
            turn_no: 0,
            ambush,
            escape,
            no_evade: false,
            gmod: GlobalMod::default(),
            rng: Box::new(Lcg(seed)),
            host,
            events: vec![],
            reward: None,
            trophy: rules::Trophy::default(),
            ring: 1.0,
            ring_hits: vec![],
            combo: vec![],
            combo_queue: vec![],
            fused: vec![None; rules::MAX_CHR],
            tarot: crate::tarot::TarotState::new([0; 3], false),
            tarot_run: None,
            pending: None,
        }
    }

    /// Transform fighter `i` into fusion `id` (`CBattle` phase 9 end: the fused name replaces the character's), or revert it (`id < 0`).
    pub fn set_fused(&mut self, i: usize, id: i32) {
        let Some(Some(f)) = self.fighters.get_mut(i) else { return };
        if id < 0 {
            if let Some(Some(prev)) = self.fused.get_mut(i).map(|s| s.take()) {
                f.name = prev.orig_name;
            }
            return;
        }
        let Some((name, model, sp_upkeep)) = self.host.fusion_info(id) else { return };
        let orig_name = self.fused.get(i).and_then(|s| s.as_ref()).map(|s| s.orig_name.clone()).unwrap_or_else(|| f.name.clone());
        f.name = name.clone();
        if let Some(slot) = self.fused.get_mut(i) {
            *slot = Some(Fused { id, name, orig_name, model, sp_upkeep });
        }
    }

    fn goto(&mut self, p: Phase, step: u16) {
        self.phase = p;
        self.step = step;
        let e = BattleEvent::PhaseChanged(p);
        self.host.event(&e);
        self.events.push(e);
    }

    fn slots(&self) -> Vec<TurnSlot> {
        self.fighters
            .iter()
            .map(|f| match f {
                Some(f) => TurnSlot { active: true, excluded: f.removed || f.hp <= 0 && !f.is_enemy && false, ..f.turn },
                None => TurnSlot::default(),
            })
            .collect()
    }

    fn sync_slots(&mut self, s: &[TurnSlot]) {
        for (f, s) in self.fighters.iter_mut().zip(s) {
            if let Some(f) = f {
                f.turn = *s;
            }
        }
    }

    /// `InitTurnTiming` for everybody.
    fn init_timers(&mut self) {
        let gm = self.gmod;
        for i in 0..self.fighters.len() {
            let Some(f) = self.fighters[i].as_mut() else { continue };
            let interval = rules::turn_interval(f.agl, f.luc, &f.status, &f.passives, &gm, !f.is_enemy);
            f.turn.active = true;
            f.turn.is_enemy = f.is_enemy;
            f.turn.interval = interval;
            f.turn.waited = 0.0;
            f.turn.timer = rules::initial_turn_timer(interval, f.agl, f.luc, f.is_enemy, self.ambush, self.rng.as_mut());
        }
    }

    pub fn outcome(&self) -> rules::BattleOutcome {
        let v: Vec<rules::EndView> = self
            .fighters
            .iter()
            .map(|f| match f {
                Some(f) => rules::EndView {
                    active: true,
                    in_battle: true,
                    excluded: false,
                    is_enemy: f.is_enemy,
                    hp: f.hp,
                    gone: f.removed,
                    status_down: f.status.iter().any(|m| m.kind == rules::modkind::STATUS && (m.value as u32 & rules::status_bits::DOWN) != 0),
                },
                None => rules::EndView::default(),
            })
            .collect();
        rules::battle_end_check(&v)
    }

    /// Provide the command for the current actor (what `BtlMenu` does via the callback).
    pub fn submit(&mut self, ev: MenuEvent) {
        self.pending = Some(ev);
    }

    /// Advance one tick of the state machine.  Returns `true` while the battle is running.
    pub fn poll(&mut self) -> bool {
        match self.phase {
            Phase::Init => {
                self.init_timers();
                self.goto(Phase::TurnSelect, 0);
            }
            Phase::TurnSelect => {
                match self.outcome() {
                    rules::BattleOutcome::Win => {
                        self.goto(Phase::Win, 0);
                        return true;
                    }
                    rules::BattleOutcome::Lose => {
                        self.goto(Phase::Lose, 0);
                        return true;
                    }
                    rules::BattleOutcome::Continue => {}
                }
                let slots = self.slots();
                if let Some(i) = rules::next_turn_chr(&slots) {
                    self.actor = Some(i);
                    let e = BattleEvent::TurnStart { chr: i };
                    self.host.event(&e);
                    self.events.push(e);
                    self.goto(Phase::TurnBefore, 0);
                } else {
                    self.goto(Phase::Lose, 0);
                }
            }
            Phase::TurnBefore => {
                let i = self.actor.unwrap();
                let gm = self.gmod;
                let f = self.fighters[i].as_mut().unwrap();
                // tick down timed status modifiers (MakeTurnOrderTable: duration byte)
                for m in f.status.iter_mut() {
                    if m.kind != 0 && m.turns != 0 {
                        m.turns -= 1;
                        if m.turns == 0 {
                            m.kind = 0;
                        }
                    }
                }
                f.status.retain(|m| m.kind != 0);
                // Poison (status 0x47 bit 0 / D.Poison bit 1): 5 % / 10 % of the max HP per turn (floor 1)
                let poison = f.status.iter().filter(|m| m.kind == rules::modkind::STATUS).fold(0, |a, m| a | m.value as u32);
                if poison & 3 != 0 && f.hp > 1 {
                    let d = (f.max_hp * if poison & 2 != 0 { 10 } else { 5 } / 100).max(1);
                    f.hp = (f.hp - d).max(1);
                    let e = BattleEvent::Damage { target: i, amount: d, critical: false };
                    self.events.push(e);
                }
                // Sanity drain for PCs (DecSP)
                if !f.is_enemy && f.max_sp > 0 {
                    let cost = rules::sp_cost_per_turn(None, &f.status, &f.passives, false, &gm);
                    let (sp, frac, _) = rules::dec_sp(f.sp, f.sp_frac, cost, false);
                    if sp != f.sp {
                        let e = BattleEvent::SanityDrop { chr: i, sp };
                        self.events.push(e);
                    }
                    f.sp = sp;
                    f.sp_frac = frac;
                }
                // a fused character pays the fusion's SP upkeep (`FUSM+5`) and reverts when it cannot
                let upkeep = self.fused.get(i).and_then(|s| s.as_ref()).map(|s| s.sp_upkeep).unwrap_or(0);
                if upkeep > 0 {
                    let f = self.fighters[i].as_mut().unwrap();
                    f.sp = (f.sp - upkeep).max(0);
                    let sp = f.sp;
                    self.events.push(BattleEvent::SanityDrop { chr: i, sp });
                    if sp == 0 {
                        // out of Sanity: the fusion ends (the real game's berserk is not modelled)
                        self.set_fused(i, -1);
                    }
                }
                // `TurnBeforeFunc` step 0x3b / `BtlMenuFunc`: a slot of kind 'Q' (the Hanged Man's tarot card) -- the turn is lost.  The slot count was
                // decremented above (n + 1 -> n), so a card that skips n turns removes itself at the start of turn n + 1.
                let skipped = self.fighters[i].as_ref().map(|f| f.status.iter().any(|m| m.kind == crate::tarot::KIND_SKIP_TURN)).unwrap_or(false);
                if skipped {
                    let e = BattleEvent::CannotAct { chr: i };
                    self.host.event(&e);
                    self.events.push(e);
                    self.finish_action(1.0);
                    return true;
                }
                // elapse: all other timers shrink by the actor's timer
                self.goto(Phase::Command, 0);
            }
            Phase::Command => {
                let i = self.actor.unwrap();
                let enemy = self.fighters[i].as_ref().unwrap().is_enemy;
                let ev = if enemy {
                    Some(self.host.choose_ai_command(i, &self.fighters))
                } else {
                    self.pending.take()
                };
                if let Some(ev) = ev {
                    if let Some((p, step, cmd)) = ev.apply(enemy) {
                        self.cmd = cmd;
                        self.goto(p, step);
                    }
                }
            }
            Phase::Attack => self.do_attack(),
            Phase::Link => {
                // `CBattle` phase 7: walk next to the partner; the partner chooses a command first (`SetNextComboChrMenu`), the leader acts afterwards
                let leader = self.actor.unwrap();
                let partner = self.cmd.p48.max(0) as usize;
                let ok = partner != leader && self.fighters.get(partner).and_then(|f| f.as_ref()).map(|f| !f.is_enemy && f.hp > 0 && !f.removed).unwrap_or(false);
                if ok && self.combo.is_empty() {
                    self.combo = vec![leader, partner];
                    self.host.combo_changed(&self.combo);
                    self.combo_queue = vec![leader];
                    self.actor = Some(partner);
                    let e = BattleEvent::ComboLink { leader, partner };
                    self.host.event(&e);
                    self.events.push(e);
                    self.goto(Phase::Command, 0);
                } else {
                    self.finish_action(1.0);
                }
            }
            Phase::Guard => {
                self.finish_action(1.0);
            }
            // `TarotEffectFunc`: the pick / effect steps are driven through `tarot_stop` / `tarot_apply` / `tarot_finish` (src/tarot.rs)
            Phase::Tarot => self.poll_tarot(),
            Phase::Escape => {
                let i = self.actor.unwrap();
                let foes: Vec<rules::EscapeFoe> = self
                    .fighters
                    .iter()
                    .flatten()
                    .filter(|f| f.is_enemy != self.fighters[i].as_ref().unwrap().is_enemy && f.hp > 0)
                    .map(|f| rules::EscapeFoe { agl: f.agl })
                    .collect();
                let me = self.fighters[i].as_ref().unwrap();
                let rate = rules::escape_rate(
                    self.escape,
                    self.ambush == Ambush::PcFirst && !me.is_enemy,
                    me.turns_taken as i32,
                    me.luc,
                    me.agl,
                    &foes,
                    &me.status,
                    &me.passives,
                    !me.is_enemy,
                );
                if rules::roll_percent(self.rng.as_mut(), rate) {
                    self.tarot.end_battle(&mut self.fighters);
                    self.gmod = rules::GlobalMod::default();
                    self.events.push(BattleEvent::Escaped);
                    self.goto(Phase::End, 0);
                } else {
                    self.events.push(BattleEvent::EscapeFailed);
                    self.finish_action(1.0);
                }
            }
            Phase::Fusion if self.cmd.p44 < 0 => {
                // `Cancel` on the Fusion page while fused: revert without an effect
                let i = self.actor.unwrap();
                self.set_fused(i, -1);
                self.finish_action(1.0);
            }
            Phase::Effect | Phase::RingSkill | Phase::Aroma | Phase::Fusion | Phase::LastBoss => {
                let i = self.actor.unwrap();
                if self.phase == Phase::Fusion {
                    // the transformation: the fused character gets its own command menu straight away (live `08h`: no turn passes)
                    let id = self.cmd.p44;
                    self.set_fused(i, id);
                }
                let hits = self.host.resolve_effect(i, &self.cmd, &mut self.fighters);
                // the action's Judgement Ring (`GetJRingAreaResult` in `EffectDamageSet`): the grade scales every hit, a miss cancels the effect
                let ring = self.ring;
                for (t, amt) in hits {
                    self.apply_damage(t, scale_by_ring(amt, ring), false);
                }
                self.ring = 1.0;
                self.ring_hits.clear();
                if self.phase == Phase::Fusion && self.fused.get(i).map(|s| s.is_some()).unwrap_or(false) {
                    // live `08h` / `17k`: the transformation costs no turn -- the fused character's own command menu opens at once
                    self.pending = None;
                    self.goto(Phase::Command, 0);
                } else {
                    self.finish_action(1.0);
                }
            }
            Phase::ActionDone => self.goto(Phase::Death, 0),
            Phase::Death => {
                let newly: Vec<usize> = (0..self.fighters.len())
                    .filter(|&k| self.fighters[k].as_ref().map(|f| f.hp <= 0 && !f.removed && f.is_enemy).unwrap_or(false))
                    .collect();
                for k in newly {
                    let f = self.fighters[k].as_mut().unwrap();
                    f.removed = true;
                    let (id, exp, cash, drops) = (f.mon_id, f.exp, f.cash, f.drops);
                    self.trophy.add_monster(id, exp, cash, 0, &drops);
                    let e = BattleEvent::Defeated { chr: k };
                    self.host.event(&e);
                    self.events.push(e);
                }
                match self.outcome() {
                    rules::BattleOutcome::Win => self.goto(Phase::Win, 0),
                    rules::BattleOutcome::Lose => self.goto(Phase::Lose, 0),
                    rules::BattleOutcome::Continue => self.goto(Phase::TurnSelect, 0),
                }
            }
            Phase::Win => {
                let mut shares = [0i32; 12];
                for (i, f) in self.fighters.iter().enumerate() {
                    if let Some(f) = f {
                        if !f.is_enemy {
                            let down = f.hp <= 0;
                            let sp_bad = f.sp < 1 && !matches!(f.char_id, 8 | 9 | 10);
                            shares[i] = rules::exp_share(false, true, down, sp_bad, 0);
                        }
                    }
                }
                let r = rules::make_result(&self.trophy, &rules::RewardMods::default(), &shares, &self.gmod, self.rng.as_mut());
                // `MakeResultTrophy` clears the Tarot card after the rewards were scaled and clamps HP / MP / SP to the real maxima
                self.tarot.end_battle(&mut self.fighters);
                self.gmod = rules::GlobalMod::default();
                self.reward = Some(r.clone());
                let e = BattleEvent::Victory(r);
                self.host.event(&e);
                self.events.push(e);
                self.goto(Phase::End, 0);
            }
            Phase::Lose => {
                self.tarot.end_battle(&mut self.fighters);
                self.gmod = rules::GlobalMod::default();
                self.events.push(BattleEvent::Defeat);
                self.goto(Phase::End, 0);
            }
            Phase::End => return false,
        }
        true
    }

    /// Basic attack of the current actor against `cmd.p48`.
    fn do_attack(&mut self) {
        let a = self.actor.unwrap();
        let t = self.cmd.p48.max(0) as usize;
        let (att, def) = match (self.fighters[a].clone(), self.fighters.get(t).cloned().flatten()) {
            (Some(a), Some(d)) => (a, d),
            _ => {
                self.finish_action(1.0);
                return;
            }
        };
        let hits = att.hits_per_attack.max(1);
        // Link combo: the friendship between the attacker and the leader boosts the damage (`friendship(A, leader) * 0.2 / 10000`)
        let combo_active = !self.combo.is_empty() && !att.is_enemy;
        let friendship = match self.combo.first() {
            Some(&leader) if combo_active && leader != a => self.host.friendship(a, leader),
            _ => 0,
        };
        let aview = rules::AttackerView {
            friendship_with_leader: friendship,
            combo_active,
            is_enemy: att.is_enemy,
            uses_sanity_bonus: !att.is_enemy && !matches!(att.char_id, 8 | 9 | 10),
            patk: att.patk,
            satk: att.satk,
            luc: att.luc,
            sp: att.sp,
            max_sp: att.max_sp,
            element: att.element,
            status: &att.status,
            passives: &att.passives,
            ..Default::default()
        };
        let guard_in = rules::GuardIn { free_to_guard: true, status: &def.status, passives: &def.passives, ..Default::default() };
        let guard = rules::check_guard(&guard_in, self.rng.as_mut());
        let dview = rules::DefenderView {
            is_enemy: def.is_enemy,
            pdef: def.pdef,
            sdef: def.sdef,
            luc: def.luc,
            hp: def.hp,
            element: def.element,
            variance: def.variance,
            status: &def.status,
            passives: &def.passives,
            resist: [rules::Resist::Normal; 6],
            guard,
            ..Default::default()
        };
        let crit = rules::critical_rate(self.no_evade, att.luc, def.luc, &att.status, &att.passives, !att.is_enemy);
        let mut total = 0;
        let mut landed: Vec<(i32, bool)> = Vec::new();
        for k in 0..hits {
            let h = rules::PhysHit {
                power: 1.0,
                hits_total: hits,
                hit_index: k,
                hits_per_swing: 1,
                ring: self.ring_hits.get(k as usize).copied().unwrap_or(self.ring),
                attack_element: att.element,
                turn_no: self.turn_no,
                combo_active,
                gm: self.gmod,
                crit_chance: crit,
            };
            // Retail order (`PAtkHitSet` -> `GetPAtkDamage`): the damage chain with its critical roll comes first, then the guard
            // factor, and only then the evasion roll.
            let r = rules::physical_damage(&aview, &dview, &h, self.rng.as_mut());
            let dmg = (r.damage * rules::guard_damage_factor(guard)) as i32;
            // The evasion roll happens only for an unguarded defender, or when the hit would kill a party member ("last chance" dodge, +10 %).
            let lethal = !def.is_enemy && dmg >= def.hp - total && def.hp - total > 0;
            if rules::evasion_roll_applies(guard, lethal) {
                let mut ev = rules::evasion_rate(self.no_evade, def.agl, def.luc, att.agl, &def.status, &def.passives, !def.is_enemy, &self.gmod, None);
                if lethal {
                    ev += rules::LETHAL_EVADE_BONUS;
                }
                if rules::roll_percent(self.rng.as_mut(), ev) {
                    continue; // evaded
                }
            }
            landed.push((dmg, r.critical));
            total += dmg;
        }
        self.ring = 1.0;
        self.ring_hits.clear();
        // one result per landed hit (`EffectMesCall` per `PAtkHitSet`: the "N Hit" counter and the per-hit numbers); all hits evaded = a single miss
        if landed.is_empty() {
            self.apply_damage(t, 0, false);
        } else {
            for (dmg, crit) in landed {
                self.apply_damage(t, dmg, crit);
            }
        }
        let _ = total;
        self.finish_action(1.0);
    }

    fn apply_damage(&mut self, t: usize, amount: i32, critical: bool) {
        if let Some(Some(f)) = self.fighters.get_mut(t) {
            f.hp = (f.hp - amount).clamp(-9999, f.max_hp);
            let e = BattleEvent::Damage { target: t, amount, critical };
            self.host.event(&e);
            self.events.push(e);
        }
    }

    /// `TarotEffectFunc` step 0x34: the turn ends (`TurnEnd`, same factor as every other action).
    pub(crate) fn tarot_finish_turn(&mut self) {
        self.finish_action(1.0);
    }

    /// `TurnEnd(factor, actor, mask)` then → ActionDone.
    fn finish_action(&mut self, factor: f32) {
        let a = self.actor.take().unwrap();
        let mut s = self.slots();
        let elapsed = s[a].timer;
        rules::end_turn(&mut s, 1 << a, factor, elapsed);
        self.sync_slots(&s);
        if let Some(f) = self.fighters[a].as_mut() {
            f.turns_taken += 1;
        }
        self.turn_no += 1;
        // a combo member is done: the next member acts inside the same slot, otherwise the combo ends
        if !self.combo_queue.is_empty() {
            let next = self.combo_queue.remove(0);
            if self.fighters.get(next).and_then(|f| f.as_ref()).map(|f| f.hp > 0 && !f.removed).unwrap_or(false) {
                self.actor = Some(next);
                self.goto(Phase::Command, 0);
                return;
            }
        }
        if !self.combo.is_empty() {
            self.combo.clear();
            self.host.combo_changed(&[]);
        }
        self.combo_queue.clear();
        self.goto(Phase::ActionDone, 0);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct Ai;
    impl Host for Ai {
        fn choose_ai_command(&mut self, actor: usize, f: &[Option<Fighter>]) -> MenuEvent {
            // attack the first living PC
            let t = f.iter().position(|x| x.as_ref().map(|x| !x.is_enemy && x.hp > 0).unwrap_or(false)).unwrap_or(0);
            MenuEvent::Attack { actor: actor as i32, target: t as i32, kind: 0, skill: -1 }
        }
    }

    fn fighter(enemy: bool, hp: i32, agl: i32, patk: i32) -> Fighter {
        Fighter {
            is_enemy: enemy,
            char_id: 0,
            name: String::new(),
            hp,
            max_hp: hp,
            mp: 0,
            max_mp: 0,
            sp: 50,
            max_sp: 50,
            agl,
            luc: 20,
            patk,
            pdef: 5,
            satk: 0,
            sdef: 0,
            element: rules::Element::NONE,
            variance: 1.0,
            status: vec![],
            passives: vec![],
            turn: TurnSlot::default(),
            sp_frac: 0,
            hits_per_attack: 1,
            exp: 30,
            cash: 10,
            drops: [rules::DropSlot { item: -1, chance: 0, rare: false }; 2],
            mon_id: 1,
            turns_taken: 0,
            removed: false,
        }
    }

    #[test]
    fn phase_roundtrip() {
        for v in 1..=0x13u16 {
            assert_eq!(Phase::from_u16(v).unwrap() as u16, v);
        }
        assert!(Phase::from_u16(0).is_none());
        assert!(Phase::from_u16(0x14).is_none());
    }

    #[test]
    fn menu_protocol_matches_btlmenucbfunc() {
        let (p, s, c) = MenuEvent::Attack { actor: 0, target: 3, kind: 1, skill: -1 }.apply(false).unwrap();
        assert_eq!((p, s, c.p44, c.p48, c.p4c, c.p54, c.p58), (Phase::Attack, 0, 0, 3, 1, 0, -1));
        let (p, s, c) = MenuEvent::Attack { actor: 7, target: 0, kind: 1, skill: 5 }.apply(true).unwrap();
        assert_eq!((p, s, c.p4c, c.p54, c.p58), (Phase::Attack, 0x14, 1, 3, 5));
        assert_eq!(MenuEvent::Item { item: 9, target: 2 }.apply(false).unwrap().0, Phase::Effect);
        assert_eq!(MenuEvent::Guard { actor: 1 }.apply(false).unwrap().0, Phase::Guard);
        assert_eq!(MenuEvent::Run.apply(false).unwrap().0, Phase::Escape);
        assert_eq!(MenuEvent::Fusion { id: 0 }.apply(false).unwrap().0, Phase::Fusion);
        assert_eq!(MenuEvent::Tarot.apply(false).unwrap().0, Phase::Tarot);
        assert!(MenuEvent::Advance.apply(false).is_none());
    }

    #[test]
    fn menu_navigation() {
        let ctx = MenuContext { can_escape: true, has_fusion: false, combo_possible: true, has_items: true, special: Some(MenuItem::Tarot) };
        let mut m = CommandMenu::open(0, ctx, vec![4, 5], vec![0, 1]);
        match &m.state {
            MenuState::Main { items, .. } => {
                assert_eq!(items[0], MenuItem::Attack);
                assert!(items.contains(&MenuItem::Run) && items.contains(&MenuItem::Link));
            }
            _ => panic!(),
        }
        // Attack -> shape -> target
        assert!(m.press(Button::Confirm).is_none());
        assert!(matches!(m.state, MenuState::AttackShape { .. }));
        m.press(Button::Down);
        assert!(m.press(Button::Confirm).is_none());
        m.press(Button::Down);
        let ev = m.press(Button::Confirm).unwrap();
        assert_eq!(ev, MenuEvent::Attack { actor: 0, target: 5, kind: 1, skill: -1 });
        // cancel returns one level
        let mut m = CommandMenu::open(0, ctx, vec![4], vec![0, 1]);
        m.press(Button::Confirm);
        m.press(Button::Cancel);
        assert!(matches!(m.state, MenuState::Main { .. }));
    }

    #[test]
    fn battle_runs_to_victory() {
        // one strong PC vs one weak enemy
        let pc = fighter(false, 200, 60, 200);
        let en = fighter(true, 30, 10, 20);
        let mut b = Battle::new(Ai, vec![pc, en], Ambush::None, rules::EscapeMode::Normal, 42);
        let mut ticks = 0;
        while b.poll() {
            ticks += 1;
            if b.phase == Phase::Command && b.actor == Some(0) {
                b.submit(MenuEvent::Attack { actor: 0, target: 1, kind: 0, skill: -1 });
            }
            assert!(ticks < 10_000, "no progress");
        }
        assert!(b.reward.is_some(), "events: {:?}", b.events);
        let r = b.reward.as_ref().unwrap();
        assert_eq!(r.exp_total, 30);
        assert_eq!(r.cash, 10);
        assert!(b.events.iter().any(|e| matches!(e, BattleEvent::Defeated { chr: 1 })));
    }

    #[test]
    fn battle_runs_to_defeat() {
        let pc = fighter(false, 10, 5, 1);
        let en = fighter(true, 5000, 90, 300);
        let mut b = Battle::new(Ai, vec![pc, en], Ambush::None, rules::EscapeMode::Never, 7);
        let mut ticks = 0;
        while b.poll() {
            ticks += 1;
            if b.phase == Phase::Command && b.actor == Some(0) {
                b.submit(MenuEvent::Guard { actor: 0 });
            }
            assert!(ticks < 10_000);
        }
        assert!(b.events.iter().any(|e| matches!(e, BattleEvent::Defeat)));
    }

    #[test]
    fn link_hands_the_slot_to_the_partner_and_back() {
        let mut f = vec![fighter(false, 100, 50, 30), fighter(false, 100, 40, 30), fighter(true, 400, 5, 10)];
        f[0].char_id = 0;
        f[1].char_id = 1;
        let mut b = Battle::new(Ai, f, Ambush::None, rules::EscapeMode::Never, 5);
        let mut order: Vec<usize> = vec![];
        let mut linked = false;
        for _ in 0..2000 {
            if !b.poll() {
                break;
            }
            if b.phase == Phase::Command {
                let a = b.actor.unwrap();
                if b.fighters[a].as_ref().unwrap().is_enemy {
                    continue;
                }
                if !linked && a == 0 {
                    linked = true;
                    b.submit(MenuEvent::Link { actor: 0, target: 1 });
                    continue;
                }
                if !linked {
                    b.submit(MenuEvent::Guard { actor: a as i32 });
                    continue;
                }
                if order.last() != Some(&a) || b.combo.is_empty() {
                    order.push(a);
                }
                b.submit(MenuEvent::Attack { actor: a as i32, target: 2, kind: 0, skill: -1 });
            }
            if linked && order.len() >= 2 {
                break;
            }
        }
        // the partner (1) chose first, then the leader (0), inside one slot
        assert_eq!(&order[..2], &[1, 0], "{order:?}");
        assert!(b.events.iter().any(|e| matches!(e, BattleEvent::ComboLink { leader: 0, partner: 1 })));
    }

    struct Friends(i32);
    impl Host for Friends {
        fn choose_ai_command(&mut self, actor: usize, _f: &[Option<Fighter>]) -> MenuEvent {
            MenuEvent::Guard { actor: actor as i32 }
        }
        fn friendship(&self, _a: usize, _b: usize) -> i32 {
            self.0
        }
    }

    /// The leader's / partner's blows inside a Link slot get `+friendship * 0.2 / 10000`; outside a combo friendship does nothing.
    #[test]
    fn friendship_boosts_only_combo_damage() {
        let run = |friend: i32, link: bool| -> i32 {
            let mut f = vec![fighter(false, 100, 50, 60), fighter(false, 100, 40, 60), fighter(true, 4000, 1, 10)];
            f[0].char_id = 0;
            f[1].char_id = 1;
            f[0].luc = 1;
            f[1].luc = 1;
            f[2].luc = 1;
            let mut b = Battle::new(Friends(friend), f, Ambush::None, rules::EscapeMode::Never, 5);
            let mut dmg = 0;
            let mut seen = 0;
            let mut linked = false;
            for _ in 0..3000 {
                if !b.poll() {
                    break;
                }
                if b.phase == Phase::Command {
                    let a = b.actor.unwrap();
                    if b.fighters[a].as_ref().unwrap().is_enemy {
                        b.submit(MenuEvent::Guard { actor: a as i32 });
                        continue;
                    }
                    if link && !linked && a == 0 {
                        linked = true;
                        b.submit(MenuEvent::Link { actor: 0, target: 1 });
                    } else if (!link || !b.combo.is_empty()) && a == 0 || a == 1 && !b.combo.is_empty() {
                        b.submit(MenuEvent::Attack { actor: a as i32, target: 2, kind: 0, skill: -1 });
                    } else {
                        b.submit(MenuEvent::Guard { actor: a as i32 });
                    }
                }
                for e in b.events[seen..].iter() {
                    if let BattleEvent::Damage { target: 2, amount, .. } = e {
                        dmg = *amount;
                    }
                }
                seen = b.events.len();
                if dmg > 0 {
                    break;
                }
            }
            dmg
        };
        let (plain, boosted) = (run(0, true), run(10000, true));
        assert!(boosted > plain, "link combo: {plain} -> {boosted}");
        assert_eq!(run(0, false), run(10000, false), "no combo, no friendship bonus");
    }

    #[test]
    fn effect_hits_follow_the_ring_grade() {
        assert_eq!(scale_by_ring(10, 1.0), 10);
        assert_eq!(scale_by_ring(10, 0.0), 0);
        assert_eq!(scale_by_ring(-16, 1.2), -19);
        assert_eq!(MenuEvent::Snap { target: 2 }.apply(false).unwrap().0, Phase::Effect);
        assert_eq!(MenuEvent::Aroma { id: 3 }.apply(false).unwrap().2.p4c, EffectKind::Misc as i32);
    }
}
