//! [`crate::flow::Host`] implementation for the playable battle: the enemy AI (AIS VM, [`crate::ai`]) and the evaluation of items, magic and skills
//! (`CBattle::EffectFunc` / `EffectDamageSet` / `EffectCodeFunc`, see [`crate::actions`]).
//!
//! Command semantics (`CBattle+0x44..0x58`, [`crate::flow::Command`]): `p4c` = effect kind (0 item, 1 magic, 2 PC skill, 3 monster skill, 7 fusion),
//! `p44` = id (item id / `MAGI` id / skill index / `SKIL` group 0x17 id), `p48` = target.  An enemy "magic" (kind 1) names an `ITEM` table entry (the AIS token
//! `0x26` uses the item table), a party "magic" a `MAGI` row.

use std::sync::Arc;

use crate::actions::{apply_records, decode_effect_words, ActionRec, ActionTables, EffRec};
use crate::ai::{AiBrain, AiChr, AiDecision, AiEnv, AiStatus};
use crate::flow::{Command, EffectKind, Fighter, Host, MenuEvent};
use crate::rules::{self, Rng, StatMod};

/// What the plugin shows / plays for the current action.
#[derive(Clone, Debug, Default)]
pub struct ActionInfo {
    pub actor: usize,
    pub kind: i32,
    pub id: i32,
    pub name: String,
    /// `EFFECT/%03d_00.EFD` or -1
    pub effect_id: i32,
    pub target: usize,
    pub offensive: bool,
}

pub struct BtlHost {
    pub rng: u32,
    pub tables: Arc<ActionTables>,
    /// per fighter slot (enemies only)
    pub brains: Vec<Option<AiBrain>>,
    /// per fighter slot: MONSTERParam +0x16 / +0x18
    pub skills: Vec<(i16, i16)>,
    /// per fighter slot: the monster has a physical attack (`PATK[atkTbl][1] != 0`)
    pub atk_flag: Vec<bool>,
    /// fighter positions (Bevy world) for the AI's cluster rules
    pub pos: Vec<[f32; 3]>,
    /// bag items consumed since the last drain
    pub used_items: Vec<i32>,
    /// `MONSTERParam` ids photographed by Snap Shot since the last drain (the owner of the save sets their library "snapped" bit,
    /// JP `BtlFree` command kind 6: `BtlSave+0xdcf`, retail `+0xf63`)
    pub snapped: Vec<u16>,
    pub last: Option<ActionInfo>,
    pub ai_log: Vec<String>,
    /// number of AI turns decided by a script / by the fallback
    pub ai_scripted: u32,
    pub ai_fallback: u32,
    /// `CBattle+0x32 != 0` (members still pending in a combo) / `+0x36 != 0` (a combo is running), refreshed by the plugin from `Battle::combo*`
    pub combo_pend: bool,
    pub combo_cnt: bool,
    /// per fighter slot: the PC id (`None` for monsters)
    pub pc_ids: Vec<Option<u8>>,
    /// per fighter slot: `PCParam+0x84` affinity table (friendship 0..10000 with each PC id), loaded from the save at battle start and written back at the end
    pub aff: Vec<[i16; 12]>,
    /// running Link combo (leader first)
    pub combo: Vec<usize>,
    /// `DecMPp` (0x6a57f4): the Tarot card *The Magician* scales every MP cost to `param` percent (100 = no card), see [`crate::tarot::TarotState::mp_cost`]
    pub mp_cost_pct: i32,
    /// the active Tarot card as the damage rules see it (`CBattle+0x407c..`, `GetSAtkDamage` / `GetSkillPAtkDamage` card 8), synced by the plugin from `Battle::gmod`
    pub gm: rules::GlobalMod,
    /// round 5 BE -- per fighter slot: the body CHR number (`BtlChr+0xec`, AI conditions 0x3c / 0x3f, `AIGetValue` 10)
    pub models: Vec<i32>,
    /// per fighter slot: status bits the unit is immune to (`MONSTERParam+0x32..0x34`, see [`monster_status_immunity`])
    pub immune: Vec<u32>,
    /// per fighter slot: `MONSTERParam+0x32` resist classes `(physical, magic)` (0 normal, 1 immune, 2 half, 3 absorb), enemies only
    pub resist: Vec<(u8, u8)>,
    /// the actor of the current / previous turn (`CBattle+0x3f82`, AI condition 0x3b)
    pub cur_actor: i32,
    pub prev_actor: i32,
    /// the AIS scripts and `GetTarget` follow the retail (US) rules
    pub us: bool,
    /// per fighter slot: soul reward `MONSTERParam+0x2c`
    pub souls: Vec<u16>,
    /// per fighter slot: the `FUSM` row of a fused party member (-1 = not fused), synced by the plugin from `Battle::fused` (banner / effect choice of fusion skills)
    pub fused: Vec<i32>,
    /// per fighter slot: the wave-bank id of its motion SE bank (`0x9000 | BCD(chr)`, 0 = none), filled by the plugin when the banks are loaded
    pub se_bank: Vec<u32>,
    /// per fighter slot: the boss death program `EFFECT/BD_%03d.EFD` of its CHR exists (retail phase 0x13, `DataReadEntry(0xc, 0xe, chr)`)
    pub bd_fx: Vec<bool>,
    /// engine-started effect programs requested by the battle (path, caster slot, target slot): `BD_%03d.EFD` when such a boss falls,
    /// `UNION.EFD` for the last boss's special turn (`LastBossFunc`); the plugin drains it into `effects_bridge::ExtraFx`
    pub engine_fx: Vec<(String, usize, usize)>,
    /// round 5b LV -- `LastBossSpecial` (live MONSET 302): the slots of the last boss's parts (CHR 500..502) while they are attached to
    /// the core (CHR 499).  Attached parts take no turns and cannot be targeted (live: the target list holds only Susano-o, only the core
    /// acts), but the AI still sees them (retail keeps them in the battle with `bState` 3, condition 0x3f).
    pub boss_parts: Vec<usize>,
    /// a `LastBoss` decision is waiting for [`Host::after_ai_command`]
    pub boss_toggle: bool,
    /// round 6 BT: the form change of this turn for [`Host::take_boss_form`] `(joined, core, parts)`
    pub boss_form: Option<(bool, usize, Vec<usize>)>,
    /// round 6 BT: core turns since the parts joined.  Live (r5_lv check 1, three joined periods): the core acts 4 times joined -- the
    /// script's union block M095_000 0xfda: skills 8 / 0xa / 9 / 0xb, one per part -- and its 5th turn is the separating `LastBossFunc`
    /// (phase 0xe, steps 10..13).  The script itself jumps back to its main block there (`9 4`), so the port starts the separation on
    /// that turn (where retail decides it is not traced: `AIIfFunc` 0x3f skips units with `+0xb2` bit 3, which the join sets).
    pub boss_joined_turns: u32,
}

/// Status bits a monster cannot receive: retail `AIIfFunc` case 0x3a / `GetTarget` criterion 130 decode `MONSTERParam+0x32..0x34` into the
/// status word (`+0x34` bits 0..5 -> 0x1 0x2 0x4 0x8 0x20 0x80, `+0x32` bits 4..7 -> 0x800..0x4000, `+0x33` bits 0..4 -> 0x8000..0x80000,
/// `+0x33` bit 5 -> 0x100).
pub fn monster_status_immunity(rec: &[u8]) -> u32 {
    let (b32, b33, b34) = (rec[0x32] as u32, rec[0x33] as u32, rec[0x34] as u32);
    let mut m = 0u32;
    for (bit, v) in [(0, 0x1), (1, 0x2), (2, 0x4), (3, 0x8), (4, 0x20), (5, 0x80)] {
        if b34 & (1 << bit) != 0 {
            m |= v;
        }
    }
    for (bit, v) in [(4, 0x800), (5, 0x1000), (6, 0x2000), (7, 0x4000)] {
        if b32 & (1 << bit) != 0 {
            m |= v;
        }
    }
    for (bit, v) in [(0, 0x8000), (1, 0x10000), (2, 0x20000), (3, 0x40000), (4, 0x80000), (5, 0x100)] {
        if b33 & (1 << bit) != 0 {
            m |= v;
        }
    }
    m
}

/// `PCParam+0x84` in the 0xc0 byte `BTL0` party record (PCParam is the record shifted by 0x3c, see `structs::pcparam::AFFINITY`).
pub const REC_AFFINITY: usize = 0x48;

impl BtlHost {
    /// Load the affinity tables of the party from the save (`pc_ids[i]` = PC id of fighter slot `i`).
    pub fn load_friendship(&mut self, pc_ids: &[Option<u8>], rec_raw: &dyn Fn(u8) -> Option<[u8; 0xc0]>) {
        self.pc_ids = pc_ids.to_vec();
        self.aff = vec![[0; 12]; pc_ids.len()];
        for (i, id) in pc_ids.iter().enumerate() {
            let Some(raw) = id.and_then(|id| rec_raw(id)) else { continue };
            for k in 0..12 {
                let o = REC_AFFINITY + k * 2;
                self.aff[i][k] = i16::from_le_bytes([raw[o], raw[o + 1]]).clamp(0, 10000);
            }
        }
    }

    /// `PCParam[a].affinity[pc id of b]`
    pub fn friend(&self, a: usize, b: usize) -> i32 {
        match (self.aff.get(a), self.pc_ids.get(b).copied().flatten()) {
            (Some(row), Some(pc)) if (pc as usize) < 12 => row[pc as usize] as i32,
            _ => 0,
        }
    }

    /// `BtlMenuFunc` step 0x28: using an item / skill on another party member grows the friendship of *both* by 100 (cap 10000).
    pub fn grow_friendship(&mut self, a: usize, b: usize) {
        if a == b {
            return;
        }
        let (Some(pa), Some(pb)) = (self.pc_ids.get(a).copied().flatten(), self.pc_ids.get(b).copied().flatten()) else { return };
        if pa as usize >= 12 || pb as usize >= 12 {
            return;
        }
        if let Some(r) = self.aff.get_mut(a) {
            r[pb as usize] = (r[pb as usize] + 100).min(10000);
        }
        if let Some(r) = self.aff.get_mut(b) {
            r[pa as usize] = (r[pa as usize] + 100).min(10000);
        }
    }

    pub fn new(seed: u32, tables: Arc<ActionTables>, slots: usize) -> Self {
        BtlHost {
            rng: seed | 1,
            tables,
            brains: vec![None; slots],
            skills: vec![(-1, -1); slots],
            atk_flag: vec![true; slots],
            pos: vec![[0.0; 3]; slots],
            used_items: vec![],
            snapped: vec![],
            last: None,
            ai_log: vec![],
            ai_scripted: 0,
            ai_fallback: 0,
            combo_pend: false,
            combo_cnt: false,
            pc_ids: vec![None; slots],
            aff: vec![[0; 12]; slots],
            combo: vec![],
            mp_cost_pct: 100,
            gm: rules::GlobalMod::default(),
            models: vec![0; slots],
            immune: vec![0; slots],
            resist: vec![(0, 0); slots],
            cur_actor: -1,
            prev_actor: -1,
            us: false,
            souls: vec![0; slots],
            fused: vec![-1; slots],
            se_bank: vec![0; slots],
            bd_fx: vec![false; slots],
            engine_fx: vec![],
            boss_parts: vec![],
            boss_toggle: false,
            boss_form: None,
            boss_joined_turns: 0,
        }
    }

    /// `MonsterInit` / `AIInit` for every monster slot of `setup`: skill ids (`+0x16 / +0x18`), the physical-attack flag, the body model, the
    /// status immunity and resist classes, and the AIS brain (`MONSTERParam+0x20` -> `BTLDATA/AIS/M%03d_%03d.AIS`, retail token dialect on the
    /// US data).  PCs get their model number from `pc_models`.  Returns the number of scripted monsters.
    pub fn setup_monsters(&mut self, data: &crate::data::BattleData, setup: &crate::bridge::BattleSetup, read: &dyn Fn(&str) -> Option<Vec<u8>>, pc_models: &dyn Fn(u8) -> i32) -> usize {
        self.us = data.raw_us.is_some();
        let dialect = if self.us { crate::ai::Dialect::Us } else { crate::ai::Dialect::Jp };
        let mut scripted = 0;
        for (i, f) in setup.fighters.iter().enumerate() {
            if !f.is_enemy {
                if let Some(Some(pc)) = setup.pc_ids.get(i) {
                    self.models[i] = pc_models(*pc);
                }
                continue;
            }
            let Some(rec) = data.dat.record(crate::data::SEC_MONSTER, f.char_id.max(0) as usize, 0x38) else { continue };
            let m = crate::data::MonsterParam::parse(rec);
            self.skills[i] = (i16::from_le_bytes([rec[0x16], rec[0x17]]), i16::from_le_bytes([rec[0x18], rec[0x19]]));
            self.atk_flag[i] = data.dat.record(crate::data::SEC_PATK, m.attack_table as usize, 0x18).map(|r| r[1] != 0).unwrap_or(true);
            self.models[i] = m.chr_model as i32;
            self.immune[i] = monster_status_immunity(rec);
            self.resist[i] = (m.phys_resist(), m.magic_resist());
            self.souls[i] = m.sp_reward;
            self.bd_fx[i] = read(&format!("EFFECT/BD_{:03}.EFD", m.chr_model)).is_some();
            let ai = i32::from_le_bytes([rec[0x20], rec[0x21], rec[0x22], rec[0x23]]);
            if let Some(b) = read(&crate::ai::ais_path(ai, false)) {
                self.brains[i] = crate::ai::AiScript::parse(&b, dialect).map(|s| AiBrain::new(Some(s)));
                if self.brains[i].is_some() {
                    scripted += 1;
                }
            }
        }
        scripted
    }

    /// Resist classes of fighter `t` against a hit (`physical` = `GetPAtkDamage` / `GetSkillPAtkDamage`, else `GetSAtkDamage`): monsters use
    /// `MONSTERParam+0x32` for every element (retail `GetPAtkDamage` 0x64e060: `*resist = pParam[0x32] & 3` for an enemy defender).
    pub fn resist_of(&self, t: usize, physical: bool) -> [rules::Resist; 6] {
        let cls = self.resist.get(t).map(|r| if physical { r.0 } else { r.1 }).unwrap_or(0);
        let r = match cls {
            1 => rules::Resist::Immune,
            2 => rules::Resist::Half,
            3 => rules::Resist::Absorb,
            _ => rules::Resist::Normal,
        };
        [r; 6]
    }

    fn next(&mut self) -> i32 {
        self.rng = self.rng.wrapping_mul(1664525).wrapping_add(1013904223);
        ((self.rng >> 1) & 0x7fff_ffff) as i32
    }

    fn snapshot(&self, f: &[Option<Fighter>]) -> Vec<AiChr> {
        (0..crate::ai::MAX_CHR)
            .map(|i| match f.get(i).and_then(|x| x.as_ref()) {
                Some(x) => {
                    let (s0, s1) = self.skills.get(i).copied().unwrap_or((-1, -1));
                    AiChr {
                        // attached last-boss parts stay visible to the core's script: its union block (M095_000 0xfda) plays one follow-up
                        // skill per living part on the next 4 turns from the bits it took before the join (see `boss_joined_turns`)
                        present: !x.removed || self.boss_parts.contains(&i),
                        enemy: x.is_enemy,
                        hp: x.hp,
                        max_hp: x.max_hp,
                        mp: x.mp,
                        max_mp: x.max_mp,
                        sp: x.sp,
                        max_sp: x.max_sp,
                        patk: x.patk,
                        satk: x.satk,
                        pdef: x.pdef,
                        sdef: x.sdef,
                        status: x.status.iter().filter(|m| m.kind != 0).map(|m| AiStatus { kind: m.kind, dur: 0, value: m.value, percent: m.percent }).collect(),
                        sub_id: x.char_id,
                        char_id: if x.is_enemy { -1 } else { x.char_id },
                        pos: self.pos.get(i).copied().unwrap_or([0.0; 3]),
                        radius: if x.is_enemy { 14.0 } else { 8.0 },
                        state: 7,
                        skill0: s0,
                        skill1: s1,
                        last_target: -1,
                        atk_flag: self.atk_flag.get(i).copied().unwrap_or(true),
                        flags_fe: 0,
                        model: self.models.get(i).copied().unwrap_or(0),
                        element: x.element.0,
                        guarding: x.status.iter().any(|m| m.kind == rules::modkind::GUARD_PART || m.kind == rules::modkind::GUARD_FULL),
                        immune: self.immune.get(i).copied().unwrap_or(0) | pc_immunity(&x.status, &x.passives),
                        // a timed record (buff / debuff with a duration) is what the retail dispel record 'N' removes
                        buffed: x.status.iter().any(|m| m.turns > 0 && m.kind != rules::modkind::STATUS),
                    }
                }
                None => AiChr::default(),
            })
            .collect()
    }

    /// `CBattle::GetComboTarget(actor, false)` (JP 0x0064f490), reduced to what the AI condition 0x26 reads: candidates are living units of the actor's side other
    /// than the actor (party members need SP >= 1 or be PC 8..10, and must not be paralysed / panicked: status 0x47 bits 0x24); a candidate whose turn comes
    /// within one interval of the actor's is a real partner (returned as is), otherwise the closest-timer unit is returned with the 0x80 "fallback" flag.
    pub fn combo_target(&self, actor: usize, f: &[Option<Fighter>]) -> i32 {
        let Some(me) = f.get(actor).and_then(|x| x.as_ref()) else { return -1 };
        let mut best: Option<(usize, f32)> = None;
        for (i, c) in f.iter().enumerate() {
            let Some(c) = c.as_ref() else { continue };
            if i == actor || c.is_enemy != me.is_enemy || c.hp <= 0 || c.removed {
                continue;
            }
            if !me.is_enemy && c.sp < 1 && !matches!(c.char_id, 8..=10) {
                continue;
            }
            let bad = c.status.iter().any(|m| m.kind == rules::modkind::STATUS && (m.value & 0x24) != 0);
            if bad {
                continue;
            }
            let d = (c.turn.timer - me.turn.timer).abs();
            if best.map(|b| d < b.1).unwrap_or(true) {
                best = Some((i, d));
            }
        }
        match best {
            None => -1,
            Some((i, d)) if d <= me.turn.interval.max(1.0) => i as i32,
            Some((i, _)) => i as i32 | 0x80,
        }
    }

    /// Describe the action of `cmd` for the banner / effect lookup (no state change).
    pub fn describe(&self, actor: usize, cmd: &Command, f: &[Option<Fighter>]) -> Option<ActionInfo> {
        let me = f.get(actor)?.as_ref()?;
        let t = &self.tables;
        let (name, effect_id, offensive) = match cmd.p4c {
            k if k == EffectKind::Item as i32 => {
                let r = t.items.get(cmd.p44.max(0) as usize)?;
                (t.item_name(r.id as usize).to_string(), r.effect_id, r.is_offensive())
            }
            k if k == EffectKind::Magic as i32 => {
                if me.is_enemy {
                    let r = t.items.get(cmd.p44.max(0) as usize)?;
                    (t.item_name(r.id as usize).to_string(), r.effect_id, r.is_offensive())
                } else {
                    let r = t.magic.get(cmd.p44.max(0) as usize)?;
                    (t.magic_name(r.id as usize).to_string(), r.effect_id, r.is_offensive())
                }
            }
            // PC skills and fusion skills: the character's `SKIL` group, the fusion's group while fused (`ActionTables::fusion_group`); monster skills: `SKIL` 0x19
            k if k == EffectKind::Skill as i32 || k == EffectKind::FusionSkill as i32 => {
                let r = self.record(actor, cmd, me)?;
                (t.skill_name(r.name_idx.max(0) as usize).to_string(), r.effect_id, r.is_offensive())
            }
            7 => (if cmd.p44 < 0 { "Cancel".to_string() } else { t.fusion_names.get(cmd.p44 as usize).cloned().unwrap_or_else(|| "Fusion".to_string()) }, -1, false),
            // aroma combination `GetRegDat(0x43, id)`: the name window shows `first × second` (live `10o`)
            6 => (t.aroma_combos.get(cmd.p44.max(0) as usize).map(|&(a, b, _)| format!("{} × {}", t.aroma_name(a as usize), t.aroma_name(b as usize))).unwrap_or_default(), -1, false),
            8 => (t.snap_label.clone(), -1, false),
            _ => return None,
        };
        // the demo disc's name tables are partly empty: fall back to a generic label so that the action banner is never blank
        let name = if name.trim().is_empty() {
            match cmd.p4c {
                k if k == EffectKind::Item as i32 => format!("Item {}", cmd.p44),
                k if k == EffectKind::Magic as i32 => format!("Magic {}", cmd.p44),
                _ => format!("Skill {}", cmd.p44),
            }
        } else {
            name
        };
        Some(ActionInfo { actor, kind: cmd.p4c, id: cmd.p44, name, effect_id, target: cmd.p48.max(0) as usize, offensive })
    }

    /// The `FUSM` row fighter `actor` is fused into: the `fusion_changed` / plugin-synced value, else recognised by the fused name `Battle::set_fused` gives
    /// the fighter (hosts driven without the hook).
    fn fused_id(&self, actor: usize, me: &Fighter) -> i32 {
        let id = self.fused.get(actor).copied().unwrap_or(-1);
        if id >= 0 || me.is_enemy {
            return id;
        }
        self.tables.fusion_names.iter().position(|n| !n.is_empty() && *n == me.name).map(|p| p as i32).unwrap_or(-1)
    }

    fn record(&self, actor: usize, cmd: &Command, me: &Fighter) -> Option<ActionRec> {
        let t = &self.tables;
        match cmd.p4c {
            0 => t.items.get(cmd.p44.max(0) as usize).cloned(),
            1 if me.is_enemy => t.items.get(cmd.p44.max(0) as usize).cloned(),
            1 => t.magic.get(cmd.p44.max(0) as usize).cloned(),
            2 | 3 if !me.is_enemy && self.fused_id(actor, me) >= 0 => {
                let g = ActionTables::fusion_group(self.fused_id(actor, me) as usize);
                t.groups.get(g).and_then(|g| g.get(cmd.p44.max(0) as usize)).cloned()
            }
            2 => t.groups.get(me.char_id.max(0) as usize).and_then(|g| g.get(cmd.p44.max(0) as usize)).cloned(),
            3 => t.mon_skills.get(cmd.p44.max(0) as usize).cloned(),
            _ => None,
        }
    }
}

struct Rn<'a>(&'a mut BtlHost);
impl Rng for Rn<'_> {
    fn rand(&mut self) -> i32 {
        self.0.next()
    }
}

/// Status bits a unit is protected against: the protection records (`'T'` duration type 2, port kind `modkind::STATUS_PROTECT`) of its
/// status list and of the passives of its accessories.
fn pc_immunity(status: &[StatMod], passives: &[StatMod]) -> u32 {
    status.iter().chain(passives).filter(|m| m.kind == rules::modkind::STATUS_PROTECT).fold(0, |a, m| a | m.value as u32)
}

fn views<'a>(a: &'a Fighter, d: &'a Fighter) -> (rules::AttackerView<'a>, rules::DefenderView<'a>) {
    let aview = rules::AttackerView {
        is_enemy: a.is_enemy,
        uses_sanity_bonus: !a.is_enemy && !matches!(a.char_id, 8 | 9 | 10),
        patk: a.patk,
        satk: a.satk,
        luc: a.luc,
        sp: a.sp,
        max_sp: a.max_sp,
        element: a.element,
        status: &a.status,
        passives: &a.passives,
        ..Default::default()
    };
    let dview = rules::DefenderView {
        is_enemy: d.is_enemy,
        pdef: d.pdef,
        sdef: d.sdef,
        luc: d.luc,
        hp: d.hp,
        element: d.element,
        variance: d.variance,
        status: &d.status,
        passives: &d.passives,
        resist: [rules::Resist::Normal; 6],
        ..Default::default()
    };
    (aview, dview)
}

impl Host for BtlHost {
    fn event(&mut self, e: &crate::flow::BattleEvent) {
        match e {
            crate::flow::BattleEvent::TurnStart { chr } => {
                self.prev_actor = self.cur_actor;
                self.cur_actor = *chr as i32;
            }
            // retail phase 0x13 (CBattle::Polling US 0x46d478): a fallen boss whose CHR has a `BD_%03d.EFD` plays it (SE 2000 first)
            crate::flow::BattleEvent::Defeated { chr } if self.bd_fx.get(*chr).copied().unwrap_or(false) => {
                let m = self.models.get(*chr).copied().unwrap_or(0);
                self.engine_fx.push((format!("EFFECT/BD_{m:03}.EFD"), *chr, *chr));
            }
            _ => {}
        }
    }

    fn friendship(&self, a: usize, b: usize) -> i32 {
        self.friend(a, b)
    }

    fn defender_resist(&self, t: usize, physical: bool) -> [rules::Resist; 6] {
        self.resist_of(t, physical)
    }

    fn fusion_changed(&mut self, chr: usize, id: i32) {
        if self.fused.len() <= chr {
            self.fused.resize(chr + 1, -1);
        }
        self.fused[chr] = id;
    }

    fn monster_soul(&self, k: usize) -> u16 {
        self.souls.get(k).copied().unwrap_or(0)
    }

    /// `PAtkEffectFunc` (US 0x696ab0) with a monster skill attack's record (AIS 0x24 index 0): the skill's effect words act on the struck target
    /// (Paralysis, SP Lowering, Dying ...) through `EffectCodeFunc`, the monster immunity mask applied.
    fn attack_rider(&mut self, actor: usize, target: usize, skill: i32, fighters: &mut [Option<Fighter>]) -> Vec<(usize, i32)> {
        let Some(rec) = self.tables.mon_skills.get(skill.max(0) as usize).cloned() else { return vec![] };
        let Some(me) = fighters.get(actor).and_then(|x| x.clone()) else { return vec![] };
        let Some(tgt) = fighters.get(target).and_then(|x| x.clone()) else { return vec![] };
        if tgt.hp <= 0 {
            return vec![];
        }
        let recs: Vec<EffRec> = decode_effect_words(&rec.words, me.satk / 2, me.satk, !me.is_enemy).into_iter().filter(|r| r.kind != 1 && r.kind != 2).collect();
        if recs.is_empty() {
            return vec![];
        }
        let imm = if tgt.is_enemy { self.immune.get(target).copied().unwrap_or(0) } else { 0 };
        let env = crate::actions::EcEnv { immune: imm, pc: if tgt.is_enemy { -1 } else { tgt.char_id }, ..Default::default() };
        let mut copy = tgt.clone();
        let mut rn = Rn(self);
        let ap = crate::actions::effect_code(&recs, &mut copy, &env, &mut rn);
        if let Some(Some(f)) = fighters.get_mut(target) {
            f.mp = copy.mp;
            f.sp = copy.sp;
            f.status = copy.status.clone();
        }
        let dhp = if ap.fell && copy.hp <= 0 { tgt.hp } else { -ap.hp };
        if dhp != 0 {
            vec![(target, dhp)]
        } else {
            vec![]
        }
    }

    fn fusion_info(&self, id: i32) -> Option<(String, u32, i32)> {
        let t = &self.tables;
        let name = t.fusion_names.get(id.max(0) as usize)?.clone();
        if name.is_empty() {
            return None;
        }
        Some((name, t.fusion_models.get(id as usize).copied().unwrap_or(0) as u32, t.fusion_sp.get(id as usize).copied().unwrap_or(0) as i32))
    }

    fn combo_changed(&mut self, members: &[usize]) {
        self.combo = members.to_vec();
    }

    fn choose_ai_command(&mut self, actor: usize, f: &[Option<Fighter>]) -> MenuEvent {
        if !self.boss_parts.is_empty() && self.models.get(actor) == Some(&499) {
            self.boss_joined_turns += 1;
            if self.boss_joined_turns > 4 {
                self.boss_joined_turns = 0;
                self.boss_toggle = true;
                if self.ai_log.len() < 64 {
                    self.ai_log.push(format!("ai {actor}: LastBoss (separate after 4 joined turns)"));
                }
                return MenuEvent::Wait { actor: actor as i32 };
            }
        }
        let chrs = self.snapshot(f);
        let tables = self.tables.ai_tables();
        let (combo_pend, combo_cnt) = (self.combo_pend, self.combo_cnt);
        let combo_target = self.combo_target(actor, f);
        let (prev_actor, combo_n, us) = (self.prev_actor, self.combo.len() as i16, self.us);
        let bag = |_: usize| false;
        let mut rng = Rn(self);
        let decision = {
            // the brain lives in `self.brains`; split the borrow by taking it out for the call
            let mut brain = rng.0.brains.get_mut(actor).and_then(|b| b.take());
            let d = match brain.as_mut() {
                Some(b) => {
                    let mut env = AiEnv {
                        chrs: &chrs,
                        tables: &tables,
                        rng: &mut rng,
                        combo_pending: combo_pend || combo_cnt,
                        turn_pend_mask: combo_pend,
                        combo_count: combo_cnt,
                        combo_target,
                        bag: &bag,
                        prev_actor,
                        combo_n,
                        us,
                    };
                    Some(b.decide(&mut env, actor))
                }
                None => None,
            };
            if let Some(b) = brain.as_mut() {
                b.state.turn_count = b.state.turn_count.wrapping_add(1);
            }
            if let Some(slot) = rng.0.brains.get_mut(actor) {
                *slot = brain;
            }
            d
        };
        let host = rng.0;
        let me = actor as i32;
        let living: Vec<usize> = f.iter().enumerate().filter(|(_, x)| x.as_ref().map(|x| !x.is_enemy && x.hp > 0).unwrap_or(false)).map(|(i, _)| i).collect();
        let fallback = |host: &mut BtlHost| {
            host.ai_fallback += 1;
            let t = living.get(host.next() as usize % living.len().max(1)).copied().unwrap_or(0);
            MenuEvent::Attack { actor: me, target: t as i32, kind: 0, skill: -1 }
        };
        let raw = format!("{decision:?}");
        let ev = match decision {
            None | Some(AiDecision::Nothing) | Some(AiDecision::PcSkill { .. }) => fallback(host),
            Some(d) => {
                host.ai_scripted += 1;
                match d {
                    AiDecision::Attack { target, shape } => MenuEvent::Attack { actor: me, target, kind: if (0..=3).contains(&shape) { shape } else { 0 }, skill: -1 },
                    // AIS 0x24 index 0: a physical attack carrying the skill record (phase 5, `+0x54 = 1`, `+0x58 = skill`; the rider acts in `attack_rider`)
                    AiDecision::SkillAttack { target, skill } => MenuEvent::Attack { actor: me, target, kind: 0, skill },
                    AiDecision::MonsterSkill { skill, target } => MenuEvent::Special { a: skill, b: target, enemy_like: true },
                    AiDecision::Item { item, target } => MenuEvent::Item { item, target },
                    AiDecision::ItemAction { id, target, attack_kind: None } => MenuEvent::Magic { id, target },
                    AiDecision::ItemAction { target, attack_kind: Some(_), .. } => MenuEvent::Attack { actor: me, target, kind: 0, skill: -1 },
                    // AIS 0x27: Link with an ally (`GetMoveTarget`), phase 7 -- the flow's Link phase forms the combo
                    AiDecision::Move { target, .. } if target >= 0 && (target as usize) < f.len() && target != me => MenuEvent::Link { actor: me, target },
                    // AIS 0x2a: `LastBossFunc` -- `EFFECT/UNION.EFD` with the core and its parts, then `LastBossSpecial` re-arranges them; the turn ends
                    AiDecision::LastBoss => {
                        host.engine_fx.push(("EFFECT/UNION.EFD".to_string(), actor, actor));
                        host.boss_toggle = true;
                        MenuEvent::Wait { actor: me }
                    }
                    // AIS 1 / 3: retail phase 0x14 with `nCmdKind = 1`, `flTurnPush = 3.0` -- the unit ends its turn (no guard stance, it stays in the battle)
                    AiDecision::Leave => MenuEvent::Wait { actor: me },
                    AiDecision::Move { .. } | AiDecision::Escape { .. } | AiDecision::Guard => MenuEvent::Guard { actor: me },
                    AiDecision::Nothing | AiDecision::PcSkill { .. } => unreachable!(),
                }
            }
        };
        if host.ai_log.len() < 64 {
            host.ai_log.push(format!("ai {actor}: {raw} -> {ev:?}"));
        }
        ev
    }

    /// `LastBossSpecial` (live MONSET 302, round 5b LV): the first special of the core combines -- the living parts (CHR 500..502) leave the
    /// turn order and the target lists (retail `bState` 3, flagsA |= 0x180000, flagsB |= 0x100, `CBattle+0x26` |= 8) -- the next one
    /// separates them again (they act and can be targeted; retail places them on an arc in front of the core at R_core + R_part + 12).
    fn after_ai_command(&mut self, actor: usize, fighters: &mut [Option<Fighter>]) {
        if !std::mem::take(&mut self.boss_toggle) {
            return;
        }
        // `LastBossSpecial` finds the core and the parts among the living units in the battle; without the core it only clears the flag
        let core = (0..fighters.len()).find(|&i| self.models.get(i) == Some(&499) && fighters[i].as_ref().is_some_and(|f| f.hp > 0)).unwrap_or(actor);
        if self.boss_parts.is_empty() {
            for (i, f) in fighters.iter_mut().enumerate() {
                let part = matches!(self.models.get(i), Some(500..=502));
                if let Some(f) = f.as_mut().filter(|f| part && f.is_enemy && f.hp > 0 && !f.removed) {
                    f.removed = true;
                    self.boss_parts.push(i);
                }
            }
            if !self.boss_parts.is_empty() {
                self.boss_joined_turns = 0;
                self.boss_form = Some((true, core, self.boss_parts.clone()));
            }
        } else {
            let mut freed = vec![];
            for i in std::mem::take(&mut self.boss_parts) {
                if let Some(Some(f)) = fighters.get_mut(i) {
                    if f.hp > 0 {
                        f.removed = false;
                        freed.push(i);
                    }
                }
            }
            self.boss_form = Some((false, core, freed));
        }
    }

    fn chr_model(&self, k: usize) -> u32 {
        self.models.get(k).copied().unwrap_or(0).max(0) as u32
    }

    fn take_boss_form(&mut self) -> Option<(bool, usize, Vec<usize>)> {
        self.boss_form.take()
    }

    fn resolve_effect(&mut self, actor: usize, cmd: &Command, fighters: &mut [Option<Fighter>]) -> Vec<(usize, i32)> {
        let Some(me) = fighters.get(actor).and_then(|x| x.clone()) else { return vec![] };
        let t = cmd.p48.max(0) as usize;
        self.last = self.describe(actor, cmd, fighters);
        // Fusion: the transformation (fused stats from the `FUSM` growth rows, SP upkeep) is applied by `Battle` (`actions::apply_fusion_stats`); nothing here
        if cmd.p4c == 7 {
            return vec![];
        }
        // Snap Shot: only a monster target is recorded (JP `BtlFree` kind 6 returns early unless the target's `bFlagsB & 1`)
        if cmd.p4c == EffectKind::Snap as i32 {
            if let Some(Some(tgt)) = fighters.get(t) {
                if tgt.is_enemy && tgt.char_id >= 0 {
                    self.snapped.push(tgt.char_id as u16);
                }
            }
            return vec![];
        }
        let Some(rec) = self.record(actor, cmd, &me) else { return vec![] };
        // friendship: an item / spell / skill on another party member grows it for both
        if !me.is_enemy && t != actor && fighters.get(t).and_then(|x| x.as_ref()).map(|x| !x.is_enemy).unwrap_or(false) {
            self.grow_friendship(actor, t);
        }
        // costs
        if let Some(Some(f)) = fighters.get_mut(actor) {
            if !f.is_enemy {
                // `DecMPp`: ceil(cost * pct / 100), at least 1 while a Magician card is active
                let cost = if self.mp_cost_pct == 100 || rec.mp <= 0 { rec.mp } else { ((rec.mp * self.mp_cost_pct + 99) / 100).max(1) };
                f.mp = (f.mp - cost).max(0);
                if cmd.p4c == EffectKind::Item as i32 {
                    self.used_items.push(cmd.p44);
                }
            }
        }
        let Some(tgt) = fighters.get(t).and_then(|x| x.clone()) else { return vec![] };
        let recs: Vec<EffRec> = decode_effect_words(&rec.words, me.satk / 2, me.satk, !me.is_enemy);
        let mut out = vec![];
        let offensive = rec.is_offensive();
        let damage_recs: Vec<&EffRec> = recs.iter().filter(|r| r.kind == 1 || r.kind == 2).collect();
        if offensive && tgt.hp > 0 {
            // damage skill / spell: `GetSkillPAtkDamage` (kind 1) or `GetSAtkDamage` (kind 2); a record without damage words (Instant Death, status /
            // debuff skills) deals no damage -- retail `EffectDamageSet` only runs the damage functions for kinds 1 / 2
            if !damage_recs.is_empty() {
                let physical = damage_recs.first().map(|r| r.kind == 1).unwrap_or(false);
                let element = damage_recs.first().map(|r| if r.element >= 6 { me.element } else { rules::Element(r.element) }).unwrap_or(me.element);
                let power = (rec.power as f32 / 100.0).clamp(0.5, 4.0);
                let (mut av, mut dv) = views(&me, &tgt);
                if tgt.is_enemy {
                    // monster resist classes `MONSTERParam+0x32` (retail `GetSAtkDamage` / `GetSkillPAtkDamage`), then the flow-side 0x24 fold
                    dv.resist = self.resist_of(t, physical);
                }
                // a spell cast inside a Link combo gets the friendship boost (`GetSAtkDamage`: `mult += friendship(attacker, leader) * 0.2 / 10000`)
                let combo_active = !self.combo.is_empty() && !me.is_enemy;
                if combo_active {
                    if let Some(&leader) = self.combo.first() {
                        if leader != actor {
                            av.friendship_with_leader = self.friend(actor, leader);
                        }
                    }
                }
                let gm = self.gm;
                let mut rn = Rn(self);
                let hit = rules::MagicHit { power, power2: 1.0, flat_bonus: 0, element, turn_no: 0, combo_active, combo_friend_bonus: 0, fusion_flat: 0, gm };
                let r = if physical { rules::skill_physical_damage(&av, &dv, &hit, &mut rn) } else { rules::magic_damage(&av, &dv, &hit, &mut rn) };
                out.push((t, r.damage.round() as i32));
            }
            // the other records of the same skill (statuses, debuffs, instant death, cuts, drains ...) through `EffectCodeFunc`; monsters are immune to the
            // bits of `MONSTERParam+0x32..0x34`
            let rest: Vec<EffRec> = recs.iter().filter(|r| r.kind != 1 && r.kind != 2).copied().collect();
            if !rest.is_empty() {
                let imm = if tgt.is_enemy { self.immune.get(t).copied().unwrap_or(0) } else { 0 };
                let env = crate::actions::EcEnv { immune: imm, pc: if tgt.is_enemy { -1 } else { tgt.char_id }, ..Default::default() };
                if let Some(Some(f)) = fighters.get(t).cloned().map(|x| x) {
                    let mut copy = f.clone();
                    let mut rn = Rn(self);
                    let ap = crate::actions::effect_code(&rest, &mut copy, &env, &mut rn);
                    if let Some(Some(f)) = fighters.get_mut(t) {
                        f.mp = copy.mp;
                        f.sp = copy.sp;
                        f.status = copy.status.clone();
                    }
                    // HP changes of these records (instant death, cuts, drains) go through the flow as damage
                    let dhp = if ap.fell && copy.hp <= 0 { tgt.hp } else { -ap.hp };
                    if dhp != 0 {
                        out.push((t, dhp));
                    }
                }
            }
        } else if !offensive || tgt.hp <= 0 {
            // support: apply on a copy so that the HP change goes through the flow (damage numbers / events)
            let mut copy = tgt.clone();
            let mut rn = Rn(self);
            let ap = apply_records(&recs, &mut copy, &mut rn);
            if let Some(Some(f)) = fighters.get_mut(t) {
                f.mp = copy.mp;
                f.sp = copy.sp;
                f.status = copy.status.clone();
                f.removed = copy.removed;
                if ap.revived {
                    f.hp = 0;
                }
            }
            if ap.hp != 0 {
                out.push((t, -ap.hp));
            }
        }
        out
    }
}

/// Reward fields of the retail (US) `MONSTERParam` table, keyed by monster id.
///
/// The JP Furokuban demo database leaves EXP / cash at zero for most monsters; the retail tables (`COMMON/SSHDAT.NA`, section `MON_` at index 5 with the same
/// 0x38 byte records) carry the real values.  A record is used only when its id **and its model number (`+4`)** match the JP record, i.e. when the layouts
/// really describe the same monster.
#[derive(Clone, Debug, Default)]
pub struct UsRewards {
    pub map: std::collections::HashMap<u16, UsReward>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct UsReward {
    pub exp: i32,
    pub cash: i32,
    pub sp: u16,
    pub item: [i16; 2],
    pub rate: [u8; 2],
}

impl UsRewards {
    pub fn load(us: &crate::pkb_compat::PkbDisc, jp: &crate::data::BattleData) -> Option<Self> {
        let raw = us.read("COMMON/SSHDAT.NA").ok()?;
        let c = crate::data::Container::parse(raw).ok()?;
        let mon_sec = c.sections.iter().position(|s| &s.tag == b"MON_")?;
        let sec = c.section(mon_sec);
        let jsec = jp.dat.section(crate::data::SEC_MONSTER);
        let mut map = std::collections::HashMap::new();
        for i in 0..sec.len() / 0x38 {
            let r = &sec[i * 0x38..(i + 1) * 0x38];
            let id = u16::from_le_bytes([r[0], r[1]]);
            let Some(j) = jsec.get(id as usize * 0x38..(id as usize + 1) * 0x38) else { continue };
            if u16::from_le_bytes([j[0], j[1]]) != id || j[4..6] != r[4..6] || j[2..4] == [0xff, 0xff] {
                continue;
            }
            let i32at = |o: usize| i32::from_le_bytes([r[o], r[o + 1], r[o + 2], r[o + 3]]);
            map.insert(
                id,
                UsReward {
                    exp: i32at(0x24),
                    cash: i32at(0x28),
                    sp: u16::from_le_bytes([r[0x2c], r[0x2d]]),
                    item: [i16::from_le_bytes([r[0x1a], r[0x1b]]), i16::from_le_bytes([r[0x1c], r[0x1d]])],
                    rate: [r[0x1e], r[0x1f]],
                },
            );
        }
        Some(UsRewards { map })
    }

    /// Patch a monster fighter whose JP record has no EXP / cash (`jp_empty`).  Returns `true` when the US values were applied.
    pub fn apply(&self, f: &mut Fighter, jp_empty: bool) -> bool {
        if !f.is_enemy || !jp_empty {
            return false;
        }
        let Some(r) = self.map.get(&(f.char_id as u16)) else { return false };
        f.exp = r.exp;
        f.cash = r.cash;
        for k in 0..2 {
            f.drops[k] = rules::DropSlot { item: r.item[k], chance: r.rate[k], rare: k == 1 };
        }
        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::bridge;
    use crate::data::BattleData;
    use crate::flow::{Battle, Phase};
    use crate::pkb_compat::PkbDisc;
    use sh2_menu::session::GameSession;

    fn disc() -> Option<PkbDisc> {
        let c = [
            std::env::var("SH2_DISC_DIR").ok(),
            Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string()),
        ];
        c.into_iter().flatten().find_map(|d| PkbDisc::open(d).ok())
    }

    /// Full headless battle: the real MONSET 0 against the demo party; the party attacks, uses a Medi-Leaf and defends; the enemies run their AIS scripts.
    #[test]
    fn scripted_enemies_fight_and_items_heal() {
        let Some(d) = disc() else { return };
        let data = BattleData::load(&d).unwrap();
        let tables = Arc::new(ActionTables::load(&data));
        let mut s = GameSession::default();
        s.new_game("AP_00_U");
        bridge::init_new_game(&data, &mut s);
        let party = s.battle_party();
        let mut n = 0u32;
        let mut rnd = || {
            n += 29;
            n
        };
        // the AP_03_U monster set of the autoplay
        let setup = bridge::build_setup(&data, &s, &party, 2, &mut rnd).expect("set 2");
        let mut host = BtlHost::new(7, tables.clone(), setup.fighters.len());
        for (i, f) in setup.fighters.iter().enumerate() {
            if f.is_enemy {
                let rec = data.dat.record(crate::data::SEC_MONSTER, f.char_id as usize, 0x38).unwrap();
                let ai = i32::from_le_bytes([rec[0x20], rec[0x21], rec[0x22], rec[0x23]]);
                host.skills[i] = (i16::from_le_bytes([rec[0x16], rec[0x17]]), i16::from_le_bytes([rec[0x18], rec[0x19]]));
                host.atk_flag[i] = data.dat.record(23, u16::from_le_bytes([rec[0x30], rec[0x31]]) as usize, 0x18).map(|r| r[1] != 0).unwrap_or(true);
                if let Ok(b) = d.read(&crate::ai::ais_path(ai, false)) {
                    host.brains[i] = crate::ai::AiScript::parse(&b, crate::ai::Dialect::Jp).map(|s| AiBrain::new(Some(s)));
                }
            }
        }
        let scripted = host.brains.iter().filter(|b| b.is_some()).count();
        let mut b = Battle::new(host, setup.fighters.clone(), setup.ambush, setup.escape, 11);
        let enemies: Vec<usize> = setup.fighters.iter().enumerate().filter(|(_, f)| f.is_enemy).map(|(i, _)| i).collect();
        let mut healed = false;
        let mut guard = 0;
        while b.poll() {
            guard += 1;
            assert!(guard < 50_000, "no progress");
            if b.phase == Phase::Command {
                if let Some(a) = b.actor {
                    if !b.fighters[a].as_ref().unwrap().is_enemy {
                        let hurt = b.fighters.iter().position(|f| f.as_ref().map(|f| !f.is_enemy && f.hp > 0 && f.hp * 2 < f.max_hp).unwrap_or(false));
                        let ev = if b.host.ai_scripted + b.host.ai_fallback < 4 {
                            // let the enemies act a few times first
                            MenuEvent::Guard { actor: a as i32 }
                        } else if let (Some(h), false) = (hurt, healed) {
                            healed = true;
                            MenuEvent::Item { item: 0, target: h as i32 }
                        } else {
                            let t = enemies.iter().copied().find(|&e| b.fighters[e].as_ref().map(|f| f.hp > 0).unwrap_or(false)).unwrap_or(enemies[0]);
                            MenuEvent::Attack { actor: a as i32, target: t as i32, kind: 0, skill: -1 }
                        };
                        b.submit(ev);
                    }
                }
            }
        }
        assert!(b.reward.is_some() || b.events.iter().any(|e| matches!(e, crate::flow::BattleEvent::Defeat)), "battle did not end");
        eprintln!("scripted brains {scripted}, ai scripted {} fallback {}; log {:?}", b.host.ai_scripted, b.host.ai_fallback, &b.host.ai_log[..b.host.ai_log.len().min(6)]);
        if scripted > 0 {
            assert!(b.host.ai_scripted > 0, "no AIS decision was used");
        }
    }

    /// Soul Comet lv 2 (`SKIL` group 1 #2, effect 202): live US 57 / 85 / 143 per hit = 20 / 30 / 50 % (round 5b LV); the three
    /// `btlEffectDamageSet` calls are each preceded by `hitResetHitMark`.
    #[test]
    fn soul_comet_has_three_hits_like_the_live_game() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = sh2_core::fileio::Disc::open(dir) else { return };
        let Ok(bytes) = d.read(&crate::effects_bridge::efd_path(202)) else { return };
        let p: Vec<i32> = crate::actions::program_hits(202, &bytes).iter().map(|h| h.1).collect();
        assert_eq!(p, vec![20, 30, 50]);
    }

    /// Snap Shot (JP `BtlFree` command kind 6): a monster target is recorded for the library "snapped" bit, an ally target is not.
    #[test]
    fn snap_shot_records_the_monster() {
        let Some(d) = disc() else { return };
        let data = BattleData::load(&d).unwrap();
        let tables = Arc::new(ActionTables::load(&data));
        let mut s = GameSession::default();
        s.new_game("AP_00_U");
        bridge::init_new_game(&data, &mut s);
        let party = s.battle_party();
        let mut n = 0u32;
        let mut rnd = || {
            n += 3;
            n
        };
        let setup = bridge::build_setup(&data, &s, &party, 2, &mut rnd).unwrap();
        let mut f: Vec<Option<Fighter>> = setup.fighters.iter().cloned().map(Some).collect();
        let enemy = f.iter().position(|x| x.as_ref().is_some_and(|x| x.is_enemy)).unwrap();
        let mon = f[enemy].as_ref().unwrap().char_id as u16;
        let mut host = BtlHost::new(1, tables, f.len());
        let snap = |t: usize| Command { p48: t as i32, p4c: EffectKind::Snap as i32, ..Default::default() };
        assert!(host.resolve_effect(0, &snap(0), &mut f).is_empty());
        assert!(host.snapped.is_empty());
        assert!(host.resolve_effect(0, &snap(enemy), &mut f).is_empty());
        assert_eq!(host.snapped, vec![mon]);
    }

    #[test]
    fn medi_leaf_heals_and_consumes() {
        let Some(d) = disc() else { return };
        let data = BattleData::load(&d).unwrap();
        let tables = Arc::new(ActionTables::load(&data));
        let mut s = GameSession::default();
        s.new_game("AP_00_U");
        bridge::init_new_game(&data, &mut s);
        let party = s.battle_party();
        let mut n = 0u32;
        let mut rnd = || {
            n += 3;
            n
        };
        let setup = bridge::build_setup(&data, &s, &party, 2, &mut rnd).unwrap();
        let mut f: Vec<Option<Fighter>> = setup.fighters.iter().cloned().map(Some).collect();
        f[0].as_mut().unwrap().hp = 10;
        let mut host = BtlHost::new(1, tables, f.len());
        let cmd = Command { p44: 0, p48: 0, p4c: EffectKind::Item as i32, ..Default::default() };
        let r = host.resolve_effect(1, &cmd, &mut f);
        assert_eq!(r, vec![(0, -75)]);
        assert_eq!(host.used_items, vec![0]);
        assert_eq!(host.last.as_ref().unwrap().effect_id, 3);
    }
}
