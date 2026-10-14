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
        }
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
                        present: !x.removed,
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
            let bad = c.status.iter().any(|m| m.kind == 0x47 && (m.value & 0x24) != 0);
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
            k if k == EffectKind::Skill as i32 => {
                let r = t.groups.get(me.char_id.max(0) as usize).and_then(|g| g.get(cmd.p44.max(0) as usize))?;
                (t.skill_name(r.name_idx.max(0) as usize).to_string(), r.effect_id, r.is_offensive())
            }
            k if k == EffectKind::FusionSkill as i32 => {
                let r = t.mon_skills.get(cmd.p44.max(0) as usize)?;
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

    fn record(&self, actor: usize, cmd: &Command, me: &Fighter) -> Option<ActionRec> {
        let t = &self.tables;
        match cmd.p4c {
            0 => t.items.get(cmd.p44.max(0) as usize).cloned(),
            1 if me.is_enemy => t.items.get(cmd.p44.max(0) as usize).cloned(),
            1 => t.magic.get(cmd.p44.max(0) as usize).cloned(),
            2 => t.groups.get(me.char_id.max(0) as usize).and_then(|g| g.get(cmd.p44.max(0) as usize)).cloned(),
            3 => t.mon_skills.get(cmd.p44.max(0) as usize).cloned(),
            _ => {
                let _ = actor;
                None
            }
        }
    }
}

struct Rn<'a>(&'a mut BtlHost);
impl Rng for Rn<'_> {
    fn rand(&mut self) -> i32 {
        self.0.next()
    }
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
    fn friendship(&self, a: usize, b: usize) -> i32 {
        self.friend(a, b)
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
        let chrs = self.snapshot(f);
        let tables = self.tables.ai_tables();
        let (combo_pend, combo_cnt) = (self.combo_pend, self.combo_cnt);
        let combo_target = self.combo_target(actor, f);
        let bag = |_: usize| false;
        let mut rng = Rn(self);
        let decision = {
            // the brain lives in `self.brains`; split the borrow by taking it out for the call
            let mut brain = rng.0.brains.get_mut(actor).and_then(|b| b.take());
            let d = match brain.as_mut() {
                Some(b) => {
                    let mut env = AiEnv { chrs: &chrs, tables: &tables, rng: &mut rng, combo_pending: combo_pend || combo_cnt, turn_pend_mask: combo_pend, combo_count: combo_cnt, combo_target, bag: &bag };
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
                    AiDecision::Attack { target, shape } => MenuEvent::Attack { actor: me, target, kind: shape.clamp(0, 3), skill: -1 },
                    AiDecision::SkillAttack { target, skill } | AiDecision::MonsterSkill { skill, target } => MenuEvent::Special { a: skill, b: target, enemy_like: true },
                    AiDecision::Item { item, target } => MenuEvent::Item { item, target },
                    AiDecision::ItemAction { id, target, attack_kind: None } => MenuEvent::Magic { id, target },
                    AiDecision::ItemAction { target, attack_kind: Some(_), .. } => MenuEvent::Attack { actor: me, target, kind: 0, skill: -1 },
                    AiDecision::Move { .. } | AiDecision::Escape { .. } | AiDecision::Guard | AiDecision::LastBoss | AiDecision::Leave => MenuEvent::Guard { actor: me },
                    AiDecision::Nothing | AiDecision::PcSkill { .. } => unreachable!(),
                }
            }
        };
        if host.ai_log.len() < 64 {
            host.ai_log.push(format!("ai {actor}: {raw} -> {ev:?}"));
        }
        ev
    }

    fn resolve_effect(&mut self, actor: usize, cmd: &Command, fighters: &mut [Option<Fighter>]) -> Vec<(usize, i32)> {
        let Some(me) = fighters.get(actor).and_then(|x| x.clone()) else { return vec![] };
        let t = cmd.p48.max(0) as usize;
        self.last = self.describe(actor, cmd, fighters);
        // fusion: a timed attack boost / damage cut (the transformation model and the fusion monster tables are not ported)
        if cmd.p4c == 7 {
            if let Some(Some(f)) = fighters.get_mut(actor) {
                for (k, v) in [(rules::modkind::DEAL_PHYS, 150), (rules::modkind::DEAL_MAG, 150), (rules::modkind::TAKE_PHYS, 70), (rules::modkind::TAKE_MAG, 70)] {
                    f.status.push(StatMod { turns: 5, chance: 100, percent: true, kind: k, value: v });
                }
                f.sp = (f.sp - 2).max(0);
            }
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
            // damage skill / spell: `GetSkillPAtkDamage` (kind 1) or `GetSAtkDamage` (kind 2 and the HP-magic kinds)
            let physical = damage_recs.first().map(|r| r.kind == 1).unwrap_or(false);
            let element = damage_recs.first().map(|r| if r.element >= 6 { me.element } else { rules::Element(r.element) }).unwrap_or(me.element);
            let power = (rec.power as f32 / 100.0).clamp(0.5, 4.0);
            let (mut av, dv) = views(&me, &tgt);
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
            // status words of the same record
            let st: Vec<EffRec> = recs.iter().filter(|r| r.kind == 0x47 || r.kind == 0x48).copied().collect();
            if !st.is_empty() {
                if let Some(Some(f)) = fighters.get_mut(t) {
                    let mut rn = Rn(self);
                    apply_records(&st, f, &mut rn);
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
