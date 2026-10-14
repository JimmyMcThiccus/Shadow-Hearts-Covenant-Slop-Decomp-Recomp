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

use std::sync::Arc;

use crate::actions::{ActionTables, FighterExt, Guard};
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
    /// 7 with the Defend page's choice (`SetGuardMenu`: 0 *Block*, 1 *Resist*); [`MenuEvent::Guard`] is *Block*
    Defend { actor: i32, resist: bool },
    /// retail phase 0x14 with `nCmdKind = 1` (AIS tokens 1 / 3): the unit only ends its turn (`flTurnPush = 3.0`, no guard)
    Wait { actor: i32 },
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
            Defend { actor, resist } => (Phase::Guard, 0, Command { p44: actor, p48: resist as i32, ..Default::default() }),
            Wait { actor } => (Phase::Guard, 0, Command { p44: actor, p48: -1, ..Default::default() }),
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
    /// Round 5 BE hook: elemental resist classes of fighter `t` against a physical (`true`) or magic hit -- monsters use `MONSTERParam+0x32`
    /// (`BtlHost::resist_of`); the default is "normal" for everyone.
    fn defender_resist(&self, _t: usize, _physical: bool) -> [rules::Resist; 6] {
        [rules::Resist::Normal; 6]
    }
    /// Round 5 BE hook: the soul reward of the monster in slot `k` (`MONSTERParam+0x2c`, summed by `AddTrophy` into the result's `Soul.` column).
    fn monster_soul(&self, _k: usize) -> u16 {
        0
    }
    /// BE request 8: the effect words of a monster skill attack (`PAtkEffectFunc` with the skill record, AIS 0x24 index 0 -> phase 5 with
    /// `cmd.p58 = skill`) on the struck target, after the physical hits landed.  Returns HP changes (damage > 0) like [`Host::resolve_effect`].
    fn attack_rider(&mut self, _actor: usize, _target: usize, _skill: i32, _fighters: &mut [Option<Fighter>]) -> Vec<(usize, i32)> {
        Vec::new()
    }
    /// Round 5 BE hook: fighter `chr` fused into `FUSM` row `id` (-1 = reverted); the host picks the fusion's skill group for its banner / effect.
    fn fusion_changed(&mut self, _chr: usize, _id: i32) {}
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
    /// party-side results of the round 5 engine (statuses, MP / SP changes, berserk, guard ...), see [`PartyEvent`]
    Party(PartyEvent),
}

/// What the party-side engine reports besides HP damage ([`BattleEvent::Party`]).  The plugin shows them as floating texts / messages
/// (`EffectMesCall`); headless runs read them for tests.
#[derive(Clone, Debug, PartialEq)]
pub enum PartyEvent {
    /// `EffectCodeFunc` result on one target: MP / SP change, status bits added / cured / resisted, buffs, "no effect"
    Effect { target: usize, mp: i32, sp: i32, added: u32, cured: u32, blocked: u32, buffs: Vec<u8>, failed: bool, revived: bool },
    /// `TurnBeforeFunc` step 0x39: `SetBtlMessage(0x73)` "%s is paralyzed!" -- the turn is lost
    Paralyzed { chr: usize },
    /// step 0x3d: `SetBtlMessage(0x71)` "%s has gone berserk!" (Sanity ran out, score counter +1) / 0x72 "%s is berserk!"
    Berserk { chr: usize, first: bool },
    /// a petrified unit's turn passes (it stays in the order but cannot act)
    Petrified { chr: usize },
    /// the MP an action cost (`DecMPp`)
    MpCost { chr: usize, mp: i32 },
    /// items / cash taken by *Pillage* / *Cash Steal* (the owner of the bag / cash adds them)
    Stolen { items: Vec<i32>, cash: i32 },
    /// the Defend stance of a party member (`Block` / `Resist`)
    Defend { chr: usize, resist: bool },
    /// a physical hit's ring item rider (`PAtkEffectFunc`: the `JRCI` effect words with the ring grade as power)
    RingItem { target: usize, added: u32 },
    /// `TurnBeforeFunc` step 0x37 / `SetBtlMessage(0x79)`: the aroma `id` is gone
    AromaGone { id: i32 },
    /// *Gathering*: `units` were moved next to unit `centre` (ring of radius [`GATHER_SPACING`]; the battle positions are already updated)
    Gather { centre: usize, units: Vec<usize> },
    /// Snap Shot: `SetBtlMessage(0x7a)` "You got the "%s" Album!" (album `index` = Anastasia's `SKIL` group 4 record)
    Album { index: u8, name: String },
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
    /// per fighter slot: the state the [`Fighter`] does not carry (guard stance, resists, immunities, raw stats, ...), see [`party_setup`]
    pub ext: Vec<FighterExt>,
    /// the action tables of the party-side engine ([`crate::actions::resolve_action`]); `None` = items / magic / skills go through
    /// [`Host::resolve_effect`] only (the headless tests of other modules)
    pub engine: Option<Arc<ActionTables>>,
    /// BE round 5: monster items / spells / skills are resolved by the same engine as the party's (`actions::resolve_action`: target lists / area shapes,
    /// `EffectDamageSet`, `EffectCodeFunc`) when `engine` is set; `false` = the older single-target `BtlHost::resolve_effect` path
    pub enemy_engine: bool,
    /// per fighter slot: floor positions (Bevy world, x / z) for the area shapes; empty = unknown (every area hits the chosen target only)
    pub positions: Vec<[f32; 3]>,
    /// the party's cash (Cash Steal by monsters)
    pub party_cash: i32,
    /// the crest columns learned (`MC_P+6` bits, `BtlSave+0xaae`): bit `k` of `crest_learned[crest]`
    pub crest_learned: Vec<u8>,
    /// statistics of this battle for the Score page ([`BattleStats`], written by [`write_score`])
    pub stats: BattleStats,
    /// Lucia's active aroma (`CBattle+0x4090..0x40a7`, [`AromaState`])
    pub aroma: Option<AromaState>,
    /// an action made the party leave (*Falling Leaves*): the battle ends as an escape after it
    pub escape_now: bool,
    /// Anastasia's albums already owned at the start (`BTL0+0xfc3` bits)
    pub albums_owned: Vec<u8>,
    /// the hit powers of the pending action's effect program (`actions::program_hits`, set by the presentation before the action
    /// resolves; cleared after it)
    pub hit_powers: Vec<i32>,
    pending: Option<MenuEvent>,
}

/// An aroma in the air (`CBattle+0x4090` row, `+0x4094` power, `+0x4098` three words, `+0x40a6` turns, `+0x40a7` chance).  `AromaEffectFunc`
/// (retail 0x69ccd0) re-applies the words to every unit of the aroma's side at the start of its turn (the previous application -- records of
/// source type 5 -- is removed first); the words with kinds 0x33 / 0x34 act on the enemies, the others on the party.  It lasts `turns` of Lucia's
/// turns and needs Lucia standing in the battle.
#[derive(Clone, Debug, PartialEq)]
pub struct AromaState {
    pub id: i32,
    pub words: [u32; 4],
    pub turns_left: u8,
    pub chance: u8,
    pub power: i32,
    pub lucia: usize,
}

/// Counters of one battle for the retail Score blocks (`BTL0+0x14bc + chapter * 0x400`, `sh2_menu::score`), written by [`write_score`].
#[derive(Clone, Debug, Default, PartialEq)]
pub struct BattleStats {
    /// most hits in one action / all hits of the battle
    pub max_hits: u32,
    pub total_hits: u32,
    /// the largest damage dealt by the party
    pub max_damage: u32,
    /// Link combos completed
    pub combos: u32,
    /// per PC id (0..14): went berserk, fell, attack rings (total / all areas hit), perfect rings (total / every hit a strike)
    pub berserk: [u32; 14],
    pub unconscious: [u32; 14],
    pub ring_total: [u32; 14],
    pub ring_ok: [u32; 14],
    pub perfect_total: [u32; 14],
    pub perfect_ok: [u32; 14],
    pub ran_away: bool,
    /// items taken from monsters by *Pillage* (party side, `ITEM` ids) and the cash change of *Cash Steal*
    pub stolen_items: Vec<i32>,
    pub cash_delta: i32,
    /// permanent base-stat changes of party members (the Seal items in battle): `(pc id, kind 0xc..0x15, delta)`
    pub permanent: Vec<(u8, u8, i32)>,
    /// Anastasia's albums gained by Snap Shot this battle (`SKIL` group 4 record = bit of `BTL0+0xfc3`)
    pub albums: Vec<u8>,
}

/// Distance of the gathered units from the target of *Gathering* (world units; the retail placement is the effect program's -- not measured).
pub const GATHER_SPACING: f32 = 12.0;

/// `StatusRecovery` case 7 (Snap Shot, retail SH2US_BATTLE.BIN 0x626bf8): photographing these `MONSTERParam` ids gives album `k` (bit `k` of
/// `BTL0+0xfc3..0xfc4`, = Anastasia's `SKIL` group 4 record `k`: Aqua Raise, Direct Press, Cash Steal, Remove, Pillage Storm, Falling Leaves,
/// Power Cannon, Spirit Ward, Nightmare, Euthanasia).  Same ids as the JP demo's `BtlFree` case 6.
pub const ALBUM_MONSTERS: [u16; 10] = [0x3a, 0x4d, 0x26, 0x33, 0xcc, 0x6f, 0x7e, 0x82, 0x92, 0x9c];

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
            ext: vec![FighterExt::default(); rules::MAX_CHR],
            engine: None,
            enemy_engine: std::env::var("SH2_BATTLE_ENEMY_ENGINE").map(|v| v != "0").unwrap_or(true),
            positions: vec![],
            party_cash: 0,
            crest_learned: vec![],
            stats: BattleStats::default(),
            aroma: None,
            escape_now: false,
            albums_owned: vec![],
            hit_powers: vec![],
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
            if let Some(e) = self.ext.get_mut(i) {
                crate::actions::apply_fusion_stats(f, e, None);
            }
            self.host.fusion_changed(i, -1);
            return;
        }
        if let Some(e) = self.ext.get_mut(i) {
            crate::actions::apply_fusion_stats(f, e, Some(id));
        }
        let Some((name, model, sp_upkeep)) = self.host.fusion_info(id) else { return };
        let orig_name = self.fused.get(i).and_then(|s| s.as_ref()).map(|s| s.orig_name.clone()).unwrap_or_else(|| f.name.clone());
        f.name = name.clone();
        if let Some(slot) = self.fused.get_mut(i) {
            *slot = Some(Fused { id, name, orig_name, model, sp_upkeep });
        }
        self.host.fusion_changed(i, id);
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
                // a fallen party member has no turns until revived (BE item 9: `turn Karin(-402hp)`)
                Some(f) => TurnSlot { active: true, excluded: f.removed || f.hp <= 0, ..f.turn },
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
                    status_down: rules::status_of(&f.status) & rules::status_bits::DOWN != 0,
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
                // the stance of the previous turn ends; the getters see the expired records (`EffectEndFunc` -> `GetPAtk` ...)
                // (the aroma's records of the previous turn are removed and applied again below: `AromaEffectFunc`)
                if let Some(e) = self.ext.get_mut(i) {
                    e.guard = Guard::None;
                    crate::actions::refresh_stats(f, e);
                }
                // Poison (status 0x54 bit 0 / D.Poison bit 1): 5 % / 10 % of the max HP per turn (floor 1)
                let poison = rules::status_of(&f.status);
                if poison & 3 != 0 && f.hp > 1 {
                    let d = (f.max_hp * if poison & 2 != 0 { 10 } else { 5 } / 100).max(1);
                    f.hp = (f.hp - d).max(1);
                    let e = BattleEvent::Damage { target: i, amount: d, critical: false };
                    self.events.push(e);
                }
                // `TurnBeforeFunc` step 0x3d: Sanity drain for PCs (`DecSP(actor, -2)`: 1 SP per turn, the fusion's `FUSM+5` while fused, the 0x1e / 0x38
                // modifiers, x3 under Panic, The Temperance card); PCs 8..10 have no Sanity.  Running out of Sanity sends the character berserk
                // (`SetBtlMessage(0x71)`, `BtlChr+0xb6` bit 2, the score counter `BTL0+0x1504 + pc * 0x24`); a berserk character gets 0x72 each turn.
                let pc = self.ext.get(i).map(|e| e.pc).unwrap_or(f.char_id);
                let upkeep = self.fused.get(i).and_then(|s| s.as_ref()).map(|s| s.sp_upkeep);
                if !f.is_enemy && f.max_sp > 0 && !matches!(pc, 8..=10) {
                    let cost = rules::sp_cost_per_turn(upkeep, &f.status, &f.passives, upkeep.is_some(), &gm);
                    let (sp, frac, sane) = rules::dec_sp(f.sp, f.sp_frac, cost, false);
                    if sp != f.sp {
                        let e = BattleEvent::SanityDrop { chr: i, sp };
                        self.events.push(e);
                    }
                    f.sp = sp;
                    f.sp_frac = frac;
                    let was = self.ext.get(i).map(|e| e.berserk).unwrap_or(false);
                    if !sane {
                        if let Some(e) = self.ext.get_mut(i) {
                            e.berserk = true;
                        }
                        if !was {
                            if let Some(c) = self.stats.berserk.get_mut(pc.clamp(0, 13) as usize) {
                                *c += 1;
                            }
                        }
                        self.events.push(BattleEvent::Party(PartyEvent::Berserk { chr: i, first: !was }));
                    } else if let Some(e) = self.ext.get_mut(i) {
                        e.berserk = false;
                    }
                }
                // out of Sanity while fused: the fusion ends (`SetAutoFusionOff`)
                if upkeep.is_some() && self.fighters[i].as_ref().map(|f| f.sp < 1).unwrap_or(false) {
                    self.set_fused(i, -1);
                }
                self.aroma_turn(i);
                // a petrified unit (status 0x20) cannot act: its turn passes
                let st = self.fighters[i].as_ref().map(|f| rules::status_of(&f.status)).unwrap_or(0);
                if st & rules::status_bits::PETRIFY != 0 {
                    self.events.push(BattleEvent::Party(PartyEvent::Petrified { chr: i }));
                    self.finish_action(1.0);
                    return true;
                }
                // step 0x39: Paralysis (status 4) -- `SetBtlMessage(0x73)` "%s is paralyzed!", the turn is lost
                if st & rules::status_bits::PARALYSIS != 0 {
                    let e = BattleEvent::Party(PartyEvent::Paralyzed { chr: i });
                    self.host.event(&e);
                    self.events.push(e);
                    self.finish_action(1.0);
                    return true;
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
                let berserk = !enemy && self.ext.get(i).map(|e| e.berserk).unwrap_or(false);
                let ev = if enemy {
                    Some(self.host.choose_ai_command(i, &self.fighters))
                } else if berserk {
                    // `BerserkFunc` (retail 0x690270): no command menu; the port keeps its "attack somebody" branch (a random living enemy).  The
                    // item / crest-spell branches and the antics phases 0x0f..0x12 are not modelled.
                    self.pending = None;
                    Some(self.berserk_command(i))
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
                let leader_enemy = self.fighters.get(leader).and_then(|f| f.as_ref()).map(|f| f.is_enemy).unwrap_or(false);
                let ok = partner != leader && self.fighters.get(partner).and_then(|f| f.as_ref()).map(|f| f.is_enemy == leader_enemy && f.hp > 0 && !f.removed).unwrap_or(false);
                if ok && self.combo.is_empty() {
                    self.combo = vec![leader, partner];
                    self.host.combo_changed(&self.combo);
                    self.combo_queue = vec![leader];
                    self.actor = Some(partner);
                    let e = BattleEvent::ComboLink { leader, partner };
                    self.host.event(&e);
                    self.events.push(e);
                    self.goto(Phase::Command, 0);
                } else if ok && self.combo.contains(&leader) && !self.combo.contains(&partner) && self.combo.len() < 4 {
                    // round 5 BP: a combo member links a further ally (combos of up to four, the combo magic needs three): the new member acts
                    // next, the linking member after it, then the rest of the queue
                    self.combo.push(partner);
                    self.host.combo_changed(&self.combo);
                    self.combo_queue.insert(0, leader);
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
                // `BtlMenuFunc` step 0x32: the defender stands in `bState` 0x11 until its next turn; `CheckGuard` answers 1 (*Block*) or 2 (*Resist*,
                // `BtlChr+0xb5` bit 3).  `cmd.p48 == -1` is the AI's "end the turn" (no stance).
                let i = self.actor.unwrap();
                if self.cmd.p48 >= 0 {
                    let resist = self.cmd.p48 == 1;
                    if let Some(e) = self.ext.get_mut(i) {
                        e.guard = if resist { Guard::Resist } else { Guard::Block };
                    }
                    self.events.push(BattleEvent::Party(PartyEvent::Defend { chr: i, resist }));
                }
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
                    self.stats.ran_away = !me.is_enemy;
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
                let actor_pc = self.fighters[i].as_ref().map(|f| !f.is_enemy).unwrap_or(false);
                // Snap Shot of a monster that carries an album (`StatusRecovery` case 7): "You got the "%s" Album!" (0x7a) once per album
                if self.phase == Phase::Effect && actor_pc && self.cmd.p4c == EffectKind::Snap as i32 {
                    let t = self.cmd.p48.max(0) as usize;
                    if let Some(id) = self.fighters.get(t).and_then(|f| f.as_ref()).filter(|f| f.is_enemy).map(|f| f.char_id as u16) {
                        if let Some(k) = ALBUM_MONSTERS.iter().position(|&m| m == id) {
                            if !self.stats.albums.contains(&(k as u8)) && !self.albums_owned.contains(&(k as u8)) {
                                self.stats.albums.push(k as u8);
                                let name = self
                                    .engine
                                    .as_ref()
                                    .and_then(|t| t.groups.get(4).and_then(|g| g.get(k)).map(|r| t.skill_name(r.name_idx.max(0) as usize).to_string()))
                                    .unwrap_or_default();
                                self.events.push(BattleEvent::Party(PartyEvent::Album { index: k as u8, name }));
                            }
                        }
                    }
                }
                let mut factor = 1.0;
                // (a fused party member's skill may arrive as the monster-skill kind 3 (`Special { enemy_like: true }`, QA3): the engine looks it up in
                // the fusion's `SKIL` group)
                let engine_phase = self.phase == Phase::Effect && matches!(self.cmd.p4c, 0..=3) || self.phase == Phase::RingSkill && self.cmd.p4c == 4;
                if self.engine.is_some() && self.phase == Phase::Aroma && actor_pc {
                    factor = self.start_aroma(i);
                } else if self.engine.is_some() && engine_phase && (actor_pc || self.enemy_engine) {
                    factor = self.resolve_party_effect(i);
                } else if self.engine.is_some() && self.phase == Phase::Fusion {
                    // the fused form's stats come from `set_fused` (FUSM growth rows); the host only sees the command (banner / effect choice)
                    let mut scratch = self.fighters.clone();
                    let _ = self.host.resolve_effect(i, &self.cmd, &mut scratch);
                } else {
                    let hits = self.host.resolve_effect(i, &self.cmd, &mut self.fighters);
                    // the action's Judgement Ring (`GetJRingAreaResult` in `EffectDamageSet`): the grade scales every hit, a miss cancels the effect
                    let ring = self.ring;
                    for (t, amt) in hits {
                        self.apply_damage(t, scale_by_ring(amt, ring), false);
                    }
                }
                self.ring = 1.0;
                self.ring_hits.clear();
                if self.escape_now {
                    self.escape_now = false;
                    self.tarot.end_battle(&mut self.fighters);
                    self.gmod = rules::GlobalMod::default();
                    self.events.push(BattleEvent::Escaped);
                    self.goto(Phase::End, 0);
                    return true;
                }
                if self.phase == Phase::Fusion && self.fused.get(i).map(|s| s.is_some()).unwrap_or(false) {
                    // live `08h` / `17k`: the transformation costs no turn -- the fused character's own command menu opens at once
                    self.pending = None;
                    self.goto(Phase::Command, 0);
                } else {
                    self.finish_action(factor);
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
                    let soul = self.host.monster_soul(k);
                    self.trophy.add_monster(id, exp, cash, soul, &drops);
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
        // `CheckGuard`: the guard records first, then the Defend stance (`bState` 0x11: 1 Block, 2 Resist)
        let stance = self.ext.get(t).map(|e| e.guard.class()).unwrap_or(0);
        let mut guard = rules::check_guard(&guard_in, self.rng.as_mut());
        if guard == 0 {
            guard = stance;
        }
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
            resist: if def.is_enemy { self.host.defender_resist(t, true) } else { self.ext.get(t).map(|e| e.resist_p).unwrap_or([rules::Resist::Normal; 6]) },
            guard,
            ..Default::default()
        };
        let crit = rules::critical_rate(self.no_evade, att.luc, def.luc, &att.status, &att.passives, !att.is_enemy);
        let mut total = 0;
        let mut landed: Vec<(i32, bool)> = Vec::new();
        // `PAtkHitSet`: the target accumulates the float damage of the action (`BtlChr+0x530`) and takes the whole points (`+0x528`); a hit
        // that is not fully guarded away takes at least 1
        let mut acc_f = 0.0f32;
        let mut acc_i = 0i32;
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
            let factor = rules::guard_damage_factor(guard);
            let mut dmg = (acc_f + r.damage * factor) as i32 - acc_i;
            if factor != 0.0 && dmg == 0 {
                dmg = if r.damage > 0.0 { 1 } else if r.damage < 0.0 { -1 } else { 0 };
            }
            // The evasion roll happens only for an unguarded defender, or when the hit would kill a party member ("last chance" dodge, +10 %).
            let lethal = !def.is_enemy && dmg >= def.hp - total && def.hp - total > 0;
            if rules::evasion_roll_applies(guard, lethal) {
                let yoah = self.ext.get(t).and_then(|e| e.yoah).map(|y| y[3]);
                let mut ev = rules::evasion_rate(self.no_evade, def.agl, def.luc, att.agl, &def.status, &def.passives, !def.is_enemy, &self.gmod, yoah);
                if lethal {
                    ev += rules::LETHAL_EVADE_BONUS;
                }
                if rules::roll_percent(self.rng.as_mut(), ev) {
                    continue; // evaded
                }
            }
            acc_f += r.damage * factor;
            acc_i += dmg;
            landed.push((dmg, r.critical));
            total += dmg;
        }
        // ring statistics of a party member's attack (score page: attack rings total / every area hit, perfect = every hit a strike)
        if !att.is_enemy && !self.ring_hits.is_empty() {
            let pc = self.ext.get(a).map(|e| e.pc).unwrap_or(att.char_id).clamp(0, 13) as usize;
            self.stats.ring_total[pc] += 1;
            if self.ring_hits.iter().all(|&g| g > 0.0) {
                self.stats.ring_ok[pc] += 1;
            }
            self.stats.perfect_total[pc] += 1;
            if self.ring_hits.iter().all(|&g| g > 1.0) {
                self.stats.perfect_ok[pc] += 1;
            }
        }
        let grade = self.ring_hits.first().copied().unwrap_or(self.ring);
        self.ring = 1.0;
        self.ring_hits.clear();
        if !att.is_enemy {
            self.stats.max_hits = self.stats.max_hits.max(landed.len() as u32);
            self.stats.total_hits += landed.len() as u32;
            self.stats.max_damage = self.stats.max_damage.max(total.max(0) as u32);
        }
        // one result per landed hit (`EffectMesCall` per `PAtkHitSet`: the "N Hit" counter and the per-hit numbers); all hits evaded = a single miss
        let hit_any = !landed.is_empty();
        if landed.is_empty() {
            self.apply_damage(t, 0, false);
        } else {
            for (dmg, crit) in landed {
                self.apply_damage(t, dmg, crit);
            }
        }
        // BE request 8: a monster skill attack's rider (the skill record's effect words on the struck target)
        if hit_any && self.cmd.p58 >= 0 && att.is_enemy {
            let skill = self.cmd.p58;
            let hits = self.host.attack_rider(a, t, skill, &mut self.fighters);
            for (tt, amt) in hits {
                self.apply_damage(tt, amt, false);
            }
        }
        // `PAtkEffectFunc` (retail 0x6972a0 / 0x696ab0): the ring item of the attacker (`JRCI` row `PCParam+0x68`, effect words `+4`) acts on the
        // target with the ring grade as power (source type 0)
        if hit_any && !att.is_enemy {
            if let Some(words) = self.ext.get(a).and_then(|e| e.ring_item) {
                let recs = crate::actions::decode_effect_words_src(&words, 0, att.satk / 2, att.satk, true, 0);
                let tex = self.ext.get(t).cloned().unwrap_or_default();
                if let Some(Some(f)) = self.fighters.get_mut(t) {
                    if f.hp > 0 {
                        let env = crate::actions::EcEnv { power: (grade * 100.0).round() as i32, immune: tex.immune, pc: tex.pc, ..Default::default() };
                        let ap = crate::actions::effect_code(&recs, f, &env, self.rng.as_mut());
                        if ap.status_added != 0 {
                            self.events.push(BattleEvent::Party(PartyEvent::RingItem { target: t, added: ap.status_added }));
                        }
                    }
                }
            }
        }
        self.finish_action(1.0);
    }

    fn apply_damage(&mut self, t: usize, amount: i32, critical: bool) {
        if let Some(Some(f)) = self.fighters.get_mut(t) {
            let was = f.hp;
            f.hp = (f.hp - amount).clamp(0, f.max_hp);
            let fell = !f.is_enemy && was > 0 && f.hp <= 0;
            let e = BattleEvent::Damage { target: t, amount, critical };
            self.host.event(&e);
            self.events.push(e);
            if fell {
                self.note_fall(t);
            }
        }
    }

    /// Round 5 BP: the party-side additions to the command menu of `actor` (call after the lists are built, before `BtlMenu::new`): Seal greys the
    /// magic-like entries, the crest magic shows its `DecMPp` cost (crest count divisor, MP-cost modifiers, The Magician), a combo member may link
    /// one more ally (combos of up to four), and three or more combo members get the combo magic of their elements (`CheckComboSkill`).
    pub fn menu_extras(&self, actor: usize, b: &mut crate::ui::MenuBuild) {
        let Some(f) = self.fighters.get(actor).and_then(|f| f.as_ref()) else { return };
        let ext = self.ext.get(actor).cloned().unwrap_or_default();
        b.sealed = rules::status_of(&f.status) & rules::status_bits::SEAL != 0;
        if let Some(t) = self.engine.as_ref() {
            let bits = &self.crest_learned;
            let learned = |c: usize, k: usize| bits.get(c).map(|v| v & (1 << k) != 0).unwrap_or(false);
            for m in b.magic.iter_mut() {
                if let Some(rec) = t.magic.get(m.id.max(0) as usize) {
                    m.mp = crate::actions::mp_cost(t, rec, true, f, &ext, &self.gmod, &learned);
                }
            }
            // combo magic (`CheckComboSkill`): the members' elements -> `COMB` rows; Ouka / Hien / Raiden together -> row 7 (Lightning Flash)
            let members: Vec<usize> = if self.combo.contains(&actor) { self.combo.clone() } else { vec![] };
            let alive: Vec<usize> = members.iter().copied().filter(|&m| self.fighters.get(m).and_then(|x| x.as_ref()).map(|x| x.hp > 0 && !x.is_enemy).unwrap_or(false)).collect();
            let pcs: Vec<i32> = alive.iter().map(|&m| self.ext.get(m).map(|e| e.pc).unwrap_or(-1)).collect();
            let trio_ohr = [8, 9, 10].iter().all(|p| pcs.contains(p));
            let trio_nrv = [0xb, 0xc, 0xd].iter().all(|p| pcs.contains(p));
            let mut rows: Vec<usize> = vec![];
            if trio_ohr && alive.len() == 3 && self.combo.len() > 1 {
                rows.push(7);
            } else if self.combo.len() >= if trio_nrv { 2 } else { 3 } {
                for &m in &alive {
                    // `CheckComboSkill`: a fused member (`BtlChr+0xb1` bit 1) counts with the fusion's element (`FUSM+4 & 7`)
                    let fused_el = self.fused.get(m).and_then(|s| s.as_ref()).and_then(|s| self.ext.get(m).and_then(|e| e.fusions.iter().find(|x| x.id == s.id)).map(|x| x.element));
                    let el = fused_el.or_else(|| self.ext.get(m).map(|e| e.combo_element)).unwrap_or(7) as usize;
                    if el < 7 && !rows.contains(&el) {
                        rows.push(el);
                    }
                }
            }
            b.combo_magic = rows
                .into_iter()
                .filter_map(|r| {
                    let rec = t.combos.get(r)?;
                    let mp = crate::actions::mp_cost(t, rec, false, f, &ext, &self.gmod, &learned);
                    Some(crate::ui::MagicEntry { id: r as i32, name: t.combo_names.get(r).cloned().unwrap_or_default(), mp, class: rec.target_class(), area: crate::ui::Area::from_flags(rec.flags) })
                })
                .collect();
        }
        // a combo member may link one more ally
        if !self.combo.is_empty() && self.combo.contains(&actor) && self.combo.len() < 4 {
            b.can_link = b.allies.iter().any(|&a| a != actor && !self.combo.contains(&a));
        }
    }

    /// Lucia's *Aromatherapy* (phase 0xc): pay the combination's MP, put the aroma in the air ([`AromaState`]) and apply it to its side at once
    /// (the rows "only when used" have no turns and act this once).  Returns the turn factor.
    fn start_aroma(&mut self, i: usize) -> f32 {
        let mut scratch = self.fighters.clone();
        let _ = self.host.resolve_effect(i, &self.cmd, &mut scratch);
        let Some(t) = self.engine.clone() else { return 1.0 };
        let Some((rec, turns, chance)) = t.aroma_rows.get(self.cmd.p44.max(0) as usize).cloned() else { return 1.0 };
        let ext = self.ext.get(i).cloned().unwrap_or_default();
        if let Some(Some(f)) = self.fighters.get_mut(i) {
            let cost = crate::actions::mp_cost(&t, &rec, false, f, &ext, &self.gmod, &|_, _| true);
            f.mp = (f.mp - cost).max(0);
            self.events.push(BattleEvent::Party(PartyEvent::MpCost { chr: i, mp: cost }));
        }
        let power = (self.ring * 100.0).round() as i32;
        self.aroma = Some(AromaState { id: self.cmd.p44, words: rec.words, turns_left: turns, chance, power: power.max(1), lucia: i });
        let side_targets: Vec<usize> = (0..self.fighters.len()).collect();
        for k in side_targets {
            self.apply_aroma_to(k);
        }
        if turns == 0 {
            self.aroma = None;
        }
        if rec.power > 0 { rec.turn_factor() / 3.0 } else { 1.0 }
    }

    /// `AromaEffectFunc(chr)`: the aroma's records on one unit (source type 5 records of the last application are replaced).
    fn apply_aroma_to(&mut self, k: usize) {
        let Some(a) = self.aroma.clone() else { return };
        let lucia_ok = self.fighters.get(a.lucia).and_then(|f| f.as_ref()).map(|f| f.hp > 0 && !f.removed).unwrap_or(false);
        let Some(Some(f)) = self.fighters.get_mut(k) else { return };
        if !lucia_ok || f.hp <= 0 || f.removed {
            return;
        }
        // source type 5 (`SpecialEffectCode(.., 5, ..)`): turns are taken as they are; the aroma's chance / turns override the words'
        let mut recs = crate::actions::decode_effect_words_src(&a.words, 5, f.satk / 2, f.satk, true, 0);
        for r in recs.iter_mut() {
            if r.turns == 0 {
                r.turns = 1;
            }
            r.chance = a.chance.max(1);
        }
        let enemy_words = recs.first().map(|r| matches!(r.kind, 0x33 | 0x34)).unwrap_or(false);
        if f.is_enemy != enemy_words {
            return;
        }
        let tex = self.ext.get(k).cloned().unwrap_or_default();
        let env = crate::actions::EcEnv { power: a.power, immune: tex.immune, pc: tex.pc, ..Default::default() };
        let ap = crate::actions::effect_code(&recs, f, &env, self.rng.as_mut());
        if let Some(e) = self.ext.get(k) {
            crate::actions::refresh_stats(f, e);
        }
        if ap.hp != 0 {
            let e = BattleEvent::Damage { target: k, amount: -ap.hp, critical: false };
            self.host.event(&e);
            self.events.push(e);
        }
        if ap.mp != 0 || ap.sp != 0 || ap.status_added != 0 || ap.status_cured != 0 || !ap.buffs.is_empty() {
            self.events.push(BattleEvent::Party(PartyEvent::Effect { target: k, mp: ap.mp, sp: ap.sp, added: ap.status_added, cured: ap.status_cured, blocked: ap.blocked, buffs: ap.buffs, failed: false, revived: ap.revived }));
        }
    }

    /// Turn start of unit `i` with an aroma in the air: Lucia's turn counts the aroma down (`AromaTurnReset`, message 0x79 when it is gone),
    /// every other unit of the side gets the aroma again (`AromaEffectFunc`).
    fn aroma_turn(&mut self, i: usize) {
        let Some(a) = self.aroma.clone() else { return };
        if i == a.lucia {
            let left = a.turns_left.saturating_sub(1);
            if left == 0 {
                self.aroma = None;
                self.events.push(BattleEvent::Party(PartyEvent::AromaGone { id: a.id }));
                return;
            }
            if let Some(s) = self.aroma.as_mut() {
                s.turns_left = left;
            }
        }
        self.apply_aroma_to(i);
    }

    /// A party member fell (score counter "unconscious").
    fn note_fall(&mut self, t: usize) {
        let pc = self.ext.get(t).map(|e| e.pc).unwrap_or(0).clamp(0, 13) as usize;
        self.stats.unconscious[pc] += 1;
    }

    /// `BerserkFunc` (retail 0x690270): the berserk character's own choice.  Its per-PC jump table (0x6e6dd0) starts with the character's
    /// antics; ported: **Yuri** (0x690400) fuses at random -- 75 % of his turns (10 % when already fused; never twice in a row, `BtlChr+0x1c2 ==
    /// 12`, nor under Seal) into one of his fusions other than the current one, or back (`p44 = -1`).  Then the shared tail (0x694778, PCs 8..11
    /// directly): with a 20 % chance one of the equipped crests' learned spells whose class (`rec+4 & 0x1f >> 3`) is not 0 / 3 and which has a
    /// target -- the target is the caster for side 0, everybody for side 3 / shape 5, else a random unit the spell can reach (enemies *and*
    /// allies); otherwise a plain attack on a random living unit (live, pine_us_refinement 9.1: berserk PCs hit each other and the enemies).
    /// Not ported: the item branch (15 %, 50 % for PC 4: a random usable battle item of the bag), the other characters' antics blocks
    /// (Karin 0x691090, ... Kurando 0x694198).
    fn berserk_command(&mut self, i: usize) -> MenuEvent {
        let Some(me) = self.fighters.get(i).and_then(|f| f.clone()) else { return MenuEvent::Wait { actor: i as i32 } };
        let ext = self.ext.get(i).cloned().unwrap_or_default();
        let sealed = rules::status_of(&me.status) & rules::status_bits::SEAL != 0;
        let last = ext.berserk_last;
        let set_last = |b: &mut Self, v: u8| {
            if let Some(e) = b.ext.get_mut(i) {
                e.berserk_last = v;
            }
        };
        // Yuri's fusion antics
        if ext.pc == 0 && !sealed && last != 12 && !ext.fusions.is_empty() {
            let cur = self.fused.get(i).and_then(|s| s.as_ref()).map(|s| s.id);
            let chance = if cur.is_some() { 1000 } else { 7500 };
            let mut opts: Vec<i32> = ext.fusions.iter().map(|f| f.id).filter(|&id| Some(id) != cur).collect();
            if cur.is_some() {
                opts.push(-1);
            }
            if !opts.is_empty() && self.rng.rand() % 10000 <= chance {
                let id = opts[self.rng.rand() as usize % opts.len()];
                set_last(self, 12);
                return MenuEvent::Fusion { id };
            }
        }
        // the crest-spell branch
        if !sealed {
            if let Some(t) = self.engine.clone() {
                let mut spells: Vec<usize> = vec![];
                for &c in ext.crests.iter().filter(|&&c| c >= 0) {
                    let Some(cr) = t.crests.get(c as usize) else { continue };
                    for (k, &m) in cr.magic.iter().enumerate() {
                        let learned = self.crest_learned.get(c as usize).map(|b| b & (1 << k) != 0).unwrap_or(false);
                        if m >= 0 && learned && !spells.contains(&(m as usize)) {
                            spells.push(m as usize);
                        }
                    }
                }
                let radius: Vec<f32> = self.ext.iter().map(|e| e.radius).collect();
                let mut usable: Vec<(usize, Vec<usize>)> = vec![];
                for m in spells {
                    let Some(rec) = t.magic.get(m) else { continue };
                    let class = (rec.flags & 0x1f) >> 3;
                    if rec.empty || class == 0 || class == 3 {
                        continue;
                    }
                    let side = (rec.flags & 0x1ff) >> 7;
                    let reach: Vec<usize> = if side == 0 {
                        vec![i]
                    } else {
                        (0..self.fighters.len())
                            .filter(|&k| self.fighters[k].as_ref().map(|f| !f.removed && (f.hp > 0 || rec.revive)).unwrap_or(false))
                            .filter(|&k| !crate::actions::target_list(&self.fighters, &self.positions, &radius, i, k as i32, rec.side_class(), rec.shape(), rec.size(), rec.revive, true).is_empty())
                            .collect()
                    };
                    if !reach.is_empty() {
                        usable.push((m, reach));
                    }
                }
                if !usable.is_empty() && self.rng.rand() % 10000 <= 2000 {
                    let (m, reach) = usable[self.rng.rand() as usize % usable.len()].clone();
                    let rec = &t.magic[m];
                    let side = (rec.flags & 0x1ff) >> 7;
                    let target = if side == 0 {
                        i as i32
                    } else if side == 3 || rec.shape() == 5 {
                        -1
                    } else {
                        reach[self.rng.rand() as usize % reach.len()] as i32
                    };
                    set_last(self, 7);
                    return MenuEvent::Magic { id: m as i32, target };
                }
            }
        }
        set_last(self, 0);
        let any: Vec<usize> = (0..self.fighters.len()).filter(|&k| k != i && self.fighters[k].as_ref().map(|f| f.hp > 0 && !f.removed).unwrap_or(false)).collect();
        let t = if any.is_empty() { 0 } else { any[self.rng.rand() as usize % any.len()] };
        MenuEvent::Attack { actor: i as i32, target: t as i32, kind: 0, skill: -1 }
    }

    /// An item / crest spell / skill of a party member through the party-side engine ([`crate::actions::resolve_action`]).  The host still sees
    /// the command on a scratch copy of the fighters (its banner / effect id, the bag consumption, Snap Shot and friendship bookkeeping); the HP
    /// changes become [`BattleEvent::Damage`] events (applied already), everything else [`PartyEvent`]s.  Returns the `TurnEnd` factor.
    fn resolve_party_effect(&mut self, i: usize) -> f32 {
        let mut scratch = self.fighters.clone();
        let _ = self.host.resolve_effect(i, &self.cmd, &mut scratch);
        let Some(tables) = self.engine.clone() else { return 1.0 };
        let fused = self.fused.get(i).and_then(|s| s.as_ref()).map(|s| s.id);
        let combo = self.combo.clone();
        let learned_bits = self.crest_learned.clone();
        let learned = move |c: usize, k: usize| learned_bits.get(c).map(|b| b & (1 << k) != 0).unwrap_or(false);
        let radius: Vec<f32> = self.ext.iter().map(|e| e.radius).collect();
        let host = &self.host;
        let friendship = |a: usize, b: usize| host.friendship(a, b);
        let ctx = crate::actions::ResolveCtx {
            tables: &tables,
            pos: &self.positions,
            radius: &radius,
            gm: self.gmod,
            ring: self.ring,
            combo: &combo,
            friendship: &friendship,
            party_cash: self.party_cash,
            fused,
            learned: &learned,
            turn_no: self.turn_no,
            hit_powers: &self.hit_powers,
        };
        let mut cmd = self.cmd;
        let actor_pc = self.fighters.get(i).and_then(|f| f.as_ref()).map(|f| !f.is_enemy).unwrap_or(false);
        if cmd.p4c == 3 && actor_pc {
            cmd.p4c = 2;
        }
        let r = crate::actions::resolve_action(&ctx, i, &cmd, &mut self.fighters, &mut self.ext, self.rng.as_mut());
        self.hit_powers.clear();
        if r.mp_cost > 0 {
            self.events.push(BattleEvent::Party(PartyEvent::MpCost { chr: i, mp: r.mp_cost }));
        }
        let mut damage_total = 0;
        for h in &r.hits {
            let heal = h.applied.hp;
            if h.damage != 0 || h.missed || heal == 0 && h.applied.mp == 0 && h.applied.sp == 0 && h.applied.status_added == 0 && h.applied.status_cured == 0 && h.applied.buffs.is_empty() {
                // one damage event per program hit (the hit panel counts them: "7Hit 280Damage")
                let parts = if h.parts.len() > 1 { h.parts.clone() } else { vec![h.damage] };
                for d in parts {
                    let e = BattleEvent::Damage { target: h.target, amount: d, critical: h.critical };
                    self.host.event(&e);
                    self.events.push(e);
                }
                damage_total += h.damage.max(0);
            }
            if heal != 0 {
                let e = BattleEvent::Damage { target: h.target, amount: -heal, critical: false };
                self.host.event(&e);
                self.events.push(e);
            }
            let a = &h.applied;
            if a.mp != 0 || a.sp != 0 || a.status_added != 0 || a.status_cured != 0 || a.blocked != 0 || !a.buffs.is_empty() || a.revived || a.failed {
                self.events.push(BattleEvent::Party(PartyEvent::Effect {
                    target: h.target,
                    mp: a.mp,
                    sp: a.sp,
                    added: a.status_added,
                    cured: a.status_cured,
                    blocked: a.blocked,
                    buffs: a.buffs.clone(),
                    failed: a.failed,
                    revived: a.revived,
                }));
            }
            if let Some(pc) = self.ext.get(h.target).map(|e| e.pc).filter(|&p| p >= 0) {
                for &(k, dlt) in &a.permanent {
                    self.stats.permanent.push((pc as u8, k, dlt));
                }
            }
            let fell = self.fighters.get(h.target).and_then(|f| f.as_ref()).map(|f| !f.is_enemy && f.hp <= 0).unwrap_or(false);
            if fell && (h.damage > 0 || a.fell) {
                self.note_fall(h.target);
            }
        }
        self.stats.max_damage = self.stats.max_damage.max(damage_total as u32);
        // special effect ids of `EffectFunc` whose action is the effect program's (`rec+0x18 % 1000`): 0xe5 *Falling Leaves* -- the party runs
        // away (effect 0x105 = fails when the fight forbids it), 0xde *Spirit Ward* -- one enemy is driven away (0x104 = fails on bosses)
        let special = r.record.as_ref().map(|x| x.effect_id.rem_euclid(1000)).unwrap_or(-1);
        if special == 0xe5 && actor_pc && self.escape != rules::EscapeMode::Never {
            self.stats.ran_away = true;
            self.escape_now = true;
        }
        if special == 0xde && actor_pc && self.escape != rules::EscapeMode::Never {
            let t = self.cmd.p48.max(0) as usize;
            if let Some(Some(f)) = self.fighters.get_mut(t) {
                if f.is_enemy && f.hp > 0 {
                    f.removed = true;
                    let e = BattleEvent::Defeated { chr: t };
                    self.host.event(&e);
                    self.events.push(e);
                }
            }
        }
        // 0x50 *Gathering* ("Gathers enemies into one place."): the effect program pulls the living units of the target's side to the target;
        // `EffectFunc` (0x484650) also lets it continue a combo like a damage action.  The area shapes measure on the new places at once.
        if special == 0x50 {
            let t = self.cmd.p48.max(0) as usize;
            let side = self.fighters.get(t).and_then(|f| f.as_ref()).map(|f| f.is_enemy);
            if let (Some(side), Some(&c)) = (side, self.positions.get(t)) {
                let units: Vec<usize> =
                    (0..self.fighters.len()).filter(|&k| k != t && self.fighters[k].as_ref().map(|f| f.is_enemy == side && f.hp > 0 && !f.removed).unwrap_or(false)).collect();
                for (n, &k) in units.iter().enumerate() {
                    let a = n as f32 * std::f32::consts::TAU / units.len().max(1) as f32;
                    if let Some(p) = self.positions.get_mut(k) {
                        *p = [c[0] + GATHER_SPACING * a.cos(), c[1], c[2] + GATHER_SPACING * a.sin()];
                    }
                }
                if !units.is_empty() {
                    self.events.push(BattleEvent::Party(PartyEvent::Gather { centre: t, units }));
                }
            }
        }
        if !r.stolen.is_empty() || r.cash != 0 {
            self.events.push(BattleEvent::Party(PartyEvent::Stolen { items: r.stolen.clone(), cash: r.cash }));
            self.party_cash = (self.party_cash + r.cash).max(0);
            self.stats.stolen_items.extend(r.stolen.iter().copied());
            self.stats.cash_delta += r.cash;
        }
        r.turn_factor
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
            if self.combo.len() > 1 {
                self.stats.combos += 1;
            }
            self.combo.clear();
            self.host.combo_changed(&[]);
        }
        self.combo_queue.clear();
        self.goto(Phase::ActionDone, 0);
    }
}

/// Set up the party-side engine of a battle (round 5 BP): the [`FighterExt`] of every fighter (PCs: the `PCInit` stat pipeline from the save
/// record incl. the accessory passives, resists, the weapon element and the crests, the ring item; monsters: `MONSTERParam` immunities,
/// resists, drops, raw stats), the action tables, the learned crest columns and the party's cash.  `pc_ids[i]` = the PC id of fighter `i`
/// (`None` for monsters, whose `char_id` is the `MONSTERParam` id).
pub fn party_setup<H: Host>(b: &mut Battle<H>, data: &crate::data::BattleData, tables: Arc<ActionTables>, session: &sh2_menu::session::GameSession, pc_ids: &[Option<u8>]) {
    b.engine = Some(tables);
    b.party_cash = session.cash() as i32;
    if session.save.btl.is_retail() {
        let r = &session.save.btl.retail;
        b.albums_owned = (0..10u8).filter(|&k| r.get(0xfc3 + (k as usize >> 3)).map(|v| v & (1 << (k & 7)) != 0).unwrap_or(false)).collect();
    }
    // `MC_P` learned columns: bit `k` of the crest's byte in the kind-5 bit set 2 of the active bag (`SetMagicMenu`: `bag + 0x16a`)
    let bag = session.save.btl.bag() as usize * sh2_menu::save::BtlSave::BAG_STRIDE;
    b.crest_learned = (0..0x60)
        .map(|c| {
            let learned = session.save.btl.data.get(sh2_menu::save::BtlSave::OFF_SKILL_BITS2 + bag + (c >> 3)).map(|v| v & (1 << (c & 7)) != 0).unwrap_or(false);
            if learned { 0xff } else { 0 }
        })
        .collect();
    for i in 0..b.fighters.len() {
        let Some(f) = b.fighters[i].as_mut() else { continue };
        let mut ext = FighterExt { radius: 3.0, ..Default::default() };
        match pc_ids.get(i).copied().flatten() {
            Some(pc) => {
                ext.pc = pc as i32;
                if let Some(rec) = session.save.btl.pc(pc as usize) {
                    let st = crate::actions::pc_stats(data, &rec, pc, None);
                    let (hp, mp, sp) = (f.hp, f.mp, f.sp);
                    crate::actions::apply_pc_stats(f, &mut ext, &st);
                    f.hp = hp.min(f.max_hp);
                    f.mp = mp.min(f.max_mp);
                    f.sp = sp.min(f.max_sp.max(sp));
                    for (k, c) in rec.skills.iter().enumerate().take(8) {
                        ext.crests[k] = *c;
                    }
                    // Yuri (0..0x14) / Kurando (0x15, 0x16): the fusion forms at the souls' levels (`BTL0+0xf24 + FUSM[0x1d]`)
                    let range: Vec<usize> = match pc {
                        0 => (0..0x15).collect(),
                        7 => (0x15..0x17).collect(),
                        _ => vec![],
                    };
                    if !range.is_empty() {
                        let lv = |soul: usize| if session.save.btl.is_retail() { session.save.btl.retail.get(0xf24 + soul).copied().unwrap_or(1) } else { 1 };
                        ext.fusions = crate::actions::fusion_forms(data, &range, &lv);
                    }
                    // the element the combo magic uses (`CheckComboSkill`: `PCParam+0` bits 2..4; Gepetto: Cornelia's dress, `CLOT` row `BTL0+0xf3e` byte 6)
                    ext.combo_element = (rec.raw[0] >> 2) & 7;
                    if pc == 2 && session.save.btl.is_retail() {
                        let dress = session.save.btl.retail.get(0xf3e).copied().unwrap_or(0) as usize;
                        if let Some(r) = data.dat.record(crate::data::SEC_CLOTH, dress, 0xc) {
                            ext.combo_element = r[6] & 7;
                            for (k, bit) in [(0, 0x08u8), (1, 0x10), (2, 0x20), (3, 0x40), (4, 0x80)] {
                                if r[6] & bit != 0 {
                                    ext.element_mask |= 1 << k;
                                }
                            }
                            for (k, bit) in [(5, 1u8), (6, 2)] {
                                if r[7] & bit != 0 {
                                    ext.element_mask |= 1 << k;
                                }
                            }
                        }
                    }
                    // Joachim's Yoahism row scales his max HP / PATK / SATK / evasion (`PCInit` also scales the current HP)
                    if pc == 6 {
                        let row = session.save.btl.yoahism() as usize;
                        if let Some(y) = data.dat.record(crate::data::SEC_YOAH, row, 0x10) {
                            ext.yoah = Some([y[10] as i32, y[11] as i32, y[12] as i32, y[13] as i32]);
                            let hp = f.hp;
                            crate::actions::refresh_stats(f, &ext);
                            f.hp = (hp * y[10] as i32 / 100).clamp(1, f.max_hp);
                        }
                    }
                    let ring = sh2_menu::ringcustom::ring_state(session, pc);
                    if ring.item >= 0 {
                        ext.ring_item = data.dat.record(crate::data::SEC_JRING, ring.item as usize, 0x20).map(|r| {
                            let w = |o: usize| u32::from_le_bytes([r[o], r[o + 1], r[o + 2], r[o + 3]]);
                            [w(4), w(8), w(0xc), w(0x10)]
                        });
                    }
                }
            }
            None => {
                if let Some(rec) = data.dat.record(crate::data::SEC_MONSTER, f.char_id.max(0) as usize, 0x38) {
                    ext = crate::actions::monster_ext(rec);
                }
            }
        }
        b.ext[i] = ext;
    }
}

/// Round 5 BP: what a finished battle leaves in the save besides the rewards -- the Score counters ([`write_score`], chapter = the save's
/// scenario), the items stolen with *Pillage* (into the active bag) and the cash of *Cash Steal*.  Call once when the battle ends (`won` =
/// victory).
pub fn apply_battle_end<H: Host>(b: &Battle<H>, session: &mut sh2_menu::session::GameSession, won: bool) {
    let chapter = session.save.btl.scenario() as usize;
    write_score(&b.stats, &mut session.save.btl, chapter, won);
    let bag = session.save.btl.bag() as usize * sh2_menu::save::BtlSave::BAG_STRIDE;
    for &item in &b.stats.stolen_items {
        if item >= 0 {
            if let Some(slot) = session.save.btl.data.get_mut(sh2_menu::save::BtlSave::OFF_ITEMS + bag + item as usize) {
                *slot = slot.saturating_add(1).min(99);
            }
        }
    }
    if b.stats.cash_delta != 0 {
        session.add_cash(b.stats.cash_delta);
    }
    // albums photographed by Anastasia
    if session.save.btl.is_retail() {
        for &k in &b.stats.albums {
            if let Some(v) = session.save.btl.retail.get_mut(0xfc3 + (k as usize >> 3)) {
                *v |= 1 << (k & 7);
            }
        }
    }
    // the Seal items used in battle change the record for good (`EffectCodeFunc` writes `PCParam` directly)
    for &(pc, kind, dlt) in &b.stats.permanent {
        let Some(mut r) = session.save.btl.pc(pc as usize) else { continue };
        let add8 = |v: u8| (v as i32 + dlt).clamp(0, 99) as u8;
        match kind {
            0xc => r.hp_max = (r.hp_max as i32 + dlt).clamp(1, 999) as u16,
            0xd => r.mp_max = (r.mp_max as i32 + dlt).clamp(0, 999) as u16,
            0xe => r.sp_max = (r.sp_max as i32 + dlt).clamp(1, 99) as u8,
            0xf => r.str_ = add8(r.str_),
            0x10 => r.vit = add8(r.vit),
            0x11 => r.int = add8(r.int),
            0x12 => r.pow = add8(r.pow),
            0x13 => r.agl = add8(r.agl),
            0x14 => r.luc = add8(r.luc),
            0x15 => r.stat_2c = add8(r.stat_2c),
            _ => continue,
        }
        session.save.btl.set_pc(pc as usize, &r);
    }
}

/// Add the counters of a finished battle to the retail Score block of `chapter` (`BTL0+0x14bc + chapter * 0x400`, u32 words, `sh2_menu::score`):
/// `[0]` battles, `[1]` ran away, `[2]` most hits (max), `[3]` total hits, `[5]` combos, `[6]` largest damage (max), `[7]` complete victories
/// (`won && nobody fell`), per PC `0x11 + 9 * pc + j`: 1 berserk, 2 unconscious, 3 / 5 ring total / success, 4 / 6 perfect total / success.
/// Nothing happens on a demo-shaped save (no retail block).
pub fn write_score(st: &BattleStats, btl: &mut sh2_menu::save::BtlSave, chapter: usize, won: bool) {
    let base = sh2_menu::score::OFF_BLOCKS + chapter.min(sh2_menu::score::CHAPTERS - 1) * sh2_menu::score::BLOCK_SIZE;
    if btl.retail.len() < base + sh2_menu::score::BLOCK_SIZE {
        return;
    }
    let mut word = |i: usize, f: &dyn Fn(u32) -> u32| {
        let o = base + i * 4;
        let v = u32::from_le_bytes([btl.retail[o], btl.retail[o + 1], btl.retail[o + 2], btl.retail[o + 3]]);
        btl.retail[o..o + 4].copy_from_slice(&f(v).to_le_bytes());
    };
    word(0, &|v| v.saturating_add(1));
    if st.ran_away {
        word(1, &|v| v.saturating_add(1));
    }
    word(2, &|v| v.max(st.max_hits));
    word(3, &|v| v.saturating_add(st.total_hits));
    word(5, &|v| v.saturating_add(st.combos));
    word(6, &|v| v.max(st.max_damage));
    if won && st.unconscious.iter().all(|&n| n == 0) {
        word(7, &|v| v.saturating_add(1));
    }
    for pc in 0..14 {
        let r = 0x11 + 9 * pc;
        for (j, n) in [(1, st.berserk[pc]), (2, st.unconscious[pc]), (3, st.ring_total[pc]), (5, st.ring_ok[pc]), (4, st.perfect_total[pc]), (6, st.perfect_ok[pc])] {
            if n > 0 {
                word(r + j, &|v| v.saturating_add(n));
            }
        }
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

/// Round 5 BP: the party-side engine inside `Battle` on the US tables (retail new game + Yuri); every test returns early without the disc.
#[cfg(test)]
mod bp_flow_tests {
    use super::*;
    use crate::data::BattleData;
    use crate::pkb_compat::PkbDisc;
    use sh2_menu::session::GameSession;

    fn us() -> Option<(BattleData, Arc<ActionTables>, GameSession)> {
        let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR")?).ok()?;
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
        let data = BattleData::load_us(&d).ok()?;
        let tables = Arc::new(ActionTables::load(&data));
        let mut s = GameSession::default();
        s.new_game("AP_03_U");
        crate::bridge::init_new_game_retail(&data, &mut s, 0);
        let tbl = crate::bridge::level_table(&data);
        crate::bridge::ensure_pc(&data, &mut s, 0, &tbl);
        eprintln!("bp_flow_tests: US disc loaded");
        Some((data, tables, s))
    }

    fn battle(data: &BattleData, tables: &Arc<ActionTables>, s: &GameSession, party: &[u8], set: usize) -> (Battle<crate::host::BtlHost>, crate::bridge::BattleSetup) {
        let mut n = 7u32;
        let mut rnd = || {
            n = n.wrapping_mul(1664525).wrapping_add(1013904223);
            n >> 8
        };
        let setup = crate::bridge::build_setup(data, s, party, set, &mut rnd).expect("setup");
        let host = crate::host::BtlHost::new(5, tables.clone(), setup.fighters.len());
        let mut b = Battle::new(host, setup.fighters.clone(), setup.ambush, setup.escape, 11);
        party_setup(&mut b, data, tables.clone(), s, &setup.pc_ids);
        (b, setup)
    }

    /// Run to the next command of party member `who`, answering every other party command with Defend.
    fn run_to(b: &mut Battle<crate::host::BtlHost>, who: usize) -> bool {
        for _ in 0..20000 {
            if b.phase == Phase::Command && b.actor == Some(who) {
                return true;
            }
            if b.phase == Phase::Command {
                let a = b.actor.unwrap();
                if !b.fighters[a].as_ref().unwrap().is_enemy {
                    b.submit(MenuEvent::Guard { actor: a as i32 });
                }
            }
            if !b.poll() {
                return false;
            }
        }
        false
    }

    #[test]
    fn retail_party_stats_and_white_magic() {
        let Some((data, tables, s)) = us() else { return };
        let (mut b, setup) = battle(&data, &tables, &s, &[5, 0xb], 2);
        // Karin's first-fight stats are the live cache values (pine_us_refinement 9.1)
        let k = b.fighters[0].as_ref().unwrap();
        assert_eq!((k.patk, k.satk, k.pdef, k.sdef), (17, 15, 16, 14));
        assert_eq!(b.ext[0].pc, 5);
        assert!(b.ext[2].pc < 0 && b.ext[2].mon.is_some());
        // Nicolai casts Cure (his SKIL group 11 record 0, 6 MP) on a hurt Karin
        b.fighters[0].as_mut().unwrap().hp = 5;
        assert!(run_to(&mut b, 1));
        let mp0 = b.fighters[1].as_ref().unwrap().mp;
        let ev0 = b.events.len();
        b.submit(MenuEvent::Special { a: 0, b: 0, enemy_like: false });
        while b.phase != Phase::ActionDone {
            b.poll();
        }
        let hp = b.fighters[0].as_ref().unwrap().hp;
        assert!(hp > 5, "Cure healed Karin: {hp}");
        assert_eq!(b.fighters[1].as_ref().unwrap().mp, mp0 - 6);
        assert!(b.events[ev0..].iter().any(|e| matches!(e, BattleEvent::Damage { target: 0, amount, .. } if *amount < 0)));
        assert!(b.events[ev0..].iter().any(|e| matches!(e, BattleEvent::Party(PartyEvent::MpCost { chr: 1, mp: 6 }))));
        let _ = setup;
    }

    #[test]
    fn defend_items_and_statuses() {
        let Some((data, tables, s)) = us() else { return };
        let (mut b, _setup) = battle(&data, &tables, &s, &[5, 0xb], 2);
        // Karin: Defend / Resist -> the stance lasts until her next turn
        assert!(run_to(&mut b, 0));
        b.submit(MenuEvent::Defend { actor: 0, resist: true });
        while b.phase != Phase::ActionDone {
            b.poll();
        }
        assert_eq!(b.ext[0].guard, Guard::Resist);
        assert!(run_to(&mut b, 0));
        assert_eq!(b.ext[0].guard, Guard::None, "the stance ends at the next turn");
        // Thera Leaf (ITEM 0) on Nicolai
        b.fighters[1].as_mut().unwrap().hp = 3;
        b.submit(MenuEvent::Item { item: 0, target: 1 });
        while b.phase != Phase::ActionDone {
            b.poll();
        }
        assert!(b.fighters[1].as_ref().unwrap().hp > 3);
        assert!(b.host.used_items.contains(&0), "the host consumed the leaf");
        // a paralysed character loses its turn
        b.fighters[1].as_mut().unwrap().status.push(StatMod { turns: 2, chance: 100, percent: false, kind: rules::modkind::STATUS, value: 4 });
        let ev0 = b.events.len();
        assert!(run_to(&mut b, 0));
        assert!(b.events[ev0..].iter().any(|e| matches!(e, BattleEvent::Party(PartyEvent::Paralyzed { chr: 1 }))) || b.fighters[1].as_ref().unwrap().hp <= 0);
    }

    #[test]
    fn sanity_out_goes_berserk_and_is_counted() {
        let Some((data, tables, s)) = us() else { return };
        let (mut b, _setup) = battle(&data, &tables, &s, &[5, 0xb], 2);
        b.fighters[0].as_mut().unwrap().sp = 1;
        assert!(run_to(&mut b, 0) || b.outcome() != rules::BattleOutcome::Continue);
        // Karin's turn started with SP 1 -> 0: berserk, the command is chosen for her
        assert!(b.ext[0].berserk || b.fighters[0].as_ref().unwrap().sp > 0);
        if b.ext[0].berserk {
            assert_eq!(b.stats.berserk[5], 1);
            assert!(b.events.iter().any(|e| matches!(e, BattleEvent::Party(PartyEvent::Berserk { chr: 0, first: true }))));
        }
    }

    #[test]
    fn yuri_fusion_uses_the_growth_rows() {
        let Some((data, tables, s)) = us() else { return };
        let (mut b, _setup) = battle(&data, &tables, &s, &[0, 5], 2);
        assert_eq!(b.ext[0].pc, 0);
        assert_eq!(b.ext[0].fusions.len(), 0x15);
        let before = b.fighters[0].as_ref().unwrap().clone();
        let form = b.ext[0].fusions[0];
        assert_eq!(form.growth, [6, 5, 4, 0, 3, 3], "FUSM 0 level 1 growth row");
        b.set_fused(0, 0);
        let f = b.fighters[0].as_ref().unwrap();
        assert_eq!(f.patk - before.patk, 6, "STR + 6 -> PATK + 6");
        assert_eq!(f.pdef - before.pdef, 5);
        assert_eq!(f.agl - before.agl, 4);
        b.set_fused(0, -1);
        let f = b.fighters[0].as_ref().unwrap();
        assert_eq!((f.patk, f.pdef, f.agl), (before.patk, before.pdef, before.agl));
    }

    #[test]
    fn lucia_aroma_heals_the_party_over_turns() {
        let Some((data, tables, mut s)) = us() else { return };
        let tbl = crate::bridge::level_table(&data);
        crate::bridge::ensure_pc(&data, &mut s, 3, &tbl);
        let (mut b, _setup) = battle(&data, &tables, &s, &[3, 5], 2);
        assert!(tables.aroma_rows.len() >= 8, "{}", tables.aroma_rows.len());
        let (row1, turns, chance) = tables.aroma_rows[1].clone();
        assert_eq!((row1.words[0], turns, chance), (0x1000_0032, 1, 100), "row 1: HP +50 for one turn");
        for k in [0, 1] {
            b.fighters[k].as_mut().unwrap().hp = 10;
        }
        assert!(run_to(&mut b, 0));
        b.submit(MenuEvent::Aroma { id: 1 });
        while b.phase != Phase::ActionDone {
            b.poll();
        }
        assert!(b.fighters[0].as_ref().unwrap().hp > 10 && b.fighters[1].as_ref().unwrap().hp > 10, "both healed at once");
        assert!(b.aroma.is_some(), "one more turn in the air");
        let karin_hp = b.fighters[1].as_ref().unwrap().hp;
        assert!(run_to(&mut b, 1) || b.fighters[1].as_ref().unwrap().hp <= 0);
        let _ = karin_hp;
    }

    #[test]
    fn score_block_gets_the_counters() {
        let Some((_data, _tables, mut s)) = us() else { return };
        if !s.save.btl.is_retail() {
            return;
        }
        let st = BattleStats { max_hits: 3, total_hits: 7, max_damage: 55, berserk: { let mut a = [0; 14]; a[5] = 1; a }, ..Default::default() };
        write_score(&st, &mut s.save.btl, 0, true);
        let t = sh2_menu::score::ScoreTotals::from_save(&s.save.btl, &s.save.menu);
        assert_eq!((t.battles, t.max_hits, t.total_hits, t.max_damage, t.berserk, t.victories), (1, 3, 7, 55, 1, 1));
    }

    /// `BerserkFunc`: berserk Yuri mostly fuses (75 %), never twice in a row; the others attack or cast a crest spell.
    #[test]
    fn berserk_yuri_fuses_at_random() {
        let Some((data, tables, s)) = us() else { return };
        let (mut b, _) = battle(&data, &tables, &s, &[0, 5], 2);
        if b.ext[0].fusions.is_empty() {
            let f = |id| crate::actions::FusionForm { id, growth: [0; 6], skill_flat: [0; 8], element: 0, level: 1 };
            b.ext[0].fusions = vec![f(0), f(1)];
        }
        let mut fusions = 0;
        let mut attacks = 0;
        for _ in 0..200 {
            b.ext[0].berserk_last = 0;
            match b.berserk_command(0) {
                MenuEvent::Fusion { .. } => {
                    fusions += 1;
                    // the next choice is never a fusion
                    assert!(!matches!(b.berserk_command(0), MenuEvent::Fusion { .. }));
                }
                MenuEvent::Attack { .. } => attacks += 1,
                _ => {}
            }
        }
        assert!(fusions > 120 && fusions < 180 && attacks > 0, "fusions {fusions} attacks {attacks}");
        // Karin never fuses
        for _ in 0..50 {
            assert!(!matches!(b.berserk_command(1), MenuEvent::Fusion { .. }));
        }
    }

    #[test]
    fn snap_shot_albums_reach_the_save() {
        let Some((data, tables, mut s)) = us() else { return };
        if !s.save.btl.is_retail() {
            return;
        }
        // the album records are Anastasia's SKIL group 4 (Aqua Raise first, Euthanasia tenth)
        let names: Vec<String> = (0..10).map(|k| tables.groups[4].get(k).map(|r| tables.skill_name(r.name_idx.max(0) as usize).to_string()).unwrap_or_default()).collect();
        eprintln!("albums: {names:?}");
        assert!(names.iter().all(|n| !n.is_empty()));
        let (mut b, _) = battle(&data, &tables, &s, &[5, 0xb], 2);
        b.stats.albums = vec![2, 8];
        apply_battle_end(&b, &mut s, true);
        assert_eq!(s.save.btl.retail[0xfc3] & 0x04, 0x04);
        assert_eq!(s.save.btl.retail[0xfc4] & 0x01, 0x01);
        // owned albums are read back at the next battle
        let (b2, _) = battle(&data, &tables, &s, &[5, 0xb], 2);
        assert!(b2.albums_owned.contains(&2) && b2.albums_owned.contains(&8));
    }
}
