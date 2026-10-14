//! Item / magic / skill records and their effect words (`SpecialEffectCode` JP 0x0032fb10, `EffectCodeFunc` JP 0x00331960).
//!
//! # Records (SSHDAT, JP demo layout)
//! | table | stride | fields used here |
//! |---|---|---|
//! | `ITEM` (sec 16, `GetRegDat(0x33)`) | 0x30 | `+0` id, `+4` u16 flags, `+8..0x18` four effect words, `+0x18` effect id (`EFFECT/%03d_00.EFD`, -1 = weapon-type attack), `+0x2c/+0x2e` menu order |
//! | `MAGI` (sec 21, `GetRegDat(0x38)`) | 0x44 | `+2` = 0xffff for an empty row, `+4` flags, `+8` effect words (or a float area parameter), `+0x18` effect id, `+0x1a` power %, `+0x1e` MP cost |
//! | `SKIL` (sec 19, `GetRegDat(0x36)`) | 24 groups `{u32 offset, u32 count}` (8-byte header each): group = party id (0x40 B records, same layout as `MAGI`), 0xc..0x15 fusion monsters, `0x16` monster skill sets (0x28 B: 20 x s16), `0x17` monster skills (0x20 B: `+2` name index, `+4` flags, `+8` words, `+0x18` effect id, `+0x1a` power %) |
//! | `MC_P` (sec 20, `GetRegDat(0x37)`) | 0x1c | crest ("紋章") records: `+6` flags, `+8/+0xa/+0xc/+0xe` four `MAGI` ids |
//!
//! `flags` (record +4): `(flags & 0x1f) >> 3` = where it can be used (0 never, 1 field, 2 battle+field, 3 key item); the target class is
//! `((flags & 0x7f) >> 5 == 0)` -> opponents, otherwise `(flags & 0x1ff) >> 7`: 0 self, 1 allies, 2 opponents, 3 everyone
//! ([`crate::ai::TargetClass::from_flags`]).
//!
//! # Effect words (`SpecialEffectCode`)
//! A record carries up to four little-endian 32 bit words, `-1` = empty.  `byte3` selects the class:
//!
//! | `byte3` | meaning | words |
//! |---|---|---|
//! | `0x00..0x0f` | damage skill: bit 3 = magical (kind 2) else physical (kind 1); `byte3 & 7` = element (7 = the caster's own); `i16` low = power | 1 |
//! | `0x10..0x1f` | **stat / HP-MP-SP change**: `kind = byte2 + 3`; bit 3 (0x08) = value is a percentage, bit 2 (0x04) = *set* instead of *add*; `i16` low = value; kinds 9/10 add `INT*2` (PC) or `SATK` (monsters), kind 0xb adds `INT/10` | 1 |
//! | `0x20..0x2f` | status 0x47 (bit field in the low 24 bits; bit 23 additionally emits a 0x48 record), second word: byte2 = turns, byte3 & 0x7f = chance % | 2 |
//! | `0x30..0x3f` | status-aux 0x48 | 2 |
//! | `0x40..0x4f` | packed modifier: `kind = ((w >> 21) & 0x7f) + 3`, signed 8 bit value, chance in the high bits | 1 |
//! | `0x50..0x5f` | packed modifier with a signed 13 bit value | 1 |
//!
//! `EffectCodeFunc` interprets the resulting 12 byte records per target.  Kinds seen in the data: `3/6/9` HP (6 = relative to the *real* max HP),
//! `4/7/10` MP, `5/8/11` SP, `0x0c..0x14` max HP/MP/SP, STR, VIT, INT, POW, AGL, LUC (timed), `0x17..0x22` attack/defence/turn/evasion/damage
//! modifiers (timed), `0x23` element override, `0x29/0x2a` guard, `0x2b` **revive**, `0x43` "has a beneficial effect" test, `0x47/0x48` status
//! bit fields (duration type `(flags & 0x1f) >> 2`: 0 inflict, 1 cure, 2 granted permanently).  Status bits (BtlMes_J order): 1 Poison, 2 D.Poison,
//! 4 Paralysis, 8 Seal, 0x10 Mental Break, 0x20 Panic (down), 0x40 Stone, 0x80 Death.
//!
//! [`apply_records`] implements the HP / MP / SP / revive / timed-stat / status subset used by items, magic and skills; the full `EffectCodeFunc`
//! (82 KB: protection flags, "dead reset" animation hooks, success-rate statistics for the AI) is documented but not ported.

use crate::ai::TargetClass;
use crate::data::{BattleData, SEC_ITEM, SEC_MAGIC, SEC_SKILL};
use crate::flow::Fighter;
use crate::rules::{Rng, StatMod};

/// `BattleData::name` returns double-byte Shift-JIS as `<XXXX>` escapes (no table in `data.rs`); turn them back into text.
pub fn unescape_sjis(s: &str) -> String {
    let b = s.as_bytes();
    let mut raw: Vec<u8> = Vec::with_capacity(b.len());
    let mut i = 0;
    while i < b.len() {
        if b[i] == b'<' && i + 6 <= b.len() && b[i + 5] == b'>' {
            if let (Ok(h), Ok(l)) = (u8::from_str_radix(&s[i + 1..i + 3], 16), u8::from_str_radix(&s[i + 3..i + 5], 16)) {
                raw.push(h);
                raw.push(l);
                i += 6;
                continue;
            }
        }
        // anything else: copy the UTF-8 bytes through a placeholder-free path (names are ASCII / half-width kana here)
        let ch = s[i..].chars().next().unwrap();
        let mut buf = [0u8; 4];
        let enc = ch.encode_utf8(&mut buf);
        if ch.is_ascii() {
            raw.push(ch as u8);
        } else {
            // already decoded text (half-width kana): keep as is
            let out = sh2_menu::sjis::decode(&raw);
            let mut out = out;
            out.push_str(enc);
            let rest = unescape_sjis(&s[i + enc.len()..]);
            out.push_str(&rest);
            return out;
        }
        i += 1;
    }
    sh2_menu::sjis::decode(&raw)
}

fn u16at(b: &[u8], o: usize) -> u16 {
    b.get(o..o + 2).map(|x| u16::from_le_bytes([x[0], x[1]])).unwrap_or(0)
}
fn i16at(b: &[u8], o: usize) -> i16 {
    u16at(b, o) as i16
}
fn u32at(b: &[u8], o: usize) -> u32 {
    b.get(o..o + 4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]])).unwrap_or(0)
}

/// One decoded effect record (the 12 byte `EFFTBL` entries written by `SpecialEffectCode`, retail SLUS 0x369330).
///
/// Record layout of the original: `+0` bits 0..5 source chr, bits 6..9 source type, bit 15..16 the "all bits" flag; `+1` bit 2 percent,
/// bits 3..5 duration type, bit 6 "permanent / unresistable"; `+4` kind; `+5` chance; `+6` bits 0..5 turns, bits 6..15 the record id.
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct EffRec {
    pub kind: u8,
    pub percent: bool,
    /// `(flags & 0x3f) >> 3`: 0 add / inflict, 1 set ("raise to") / cure, 2 protection (status words)
    pub dur: u8,
    pub chance: u8,
    pub turns: u8,
    pub value: i32,
    /// damage skills (kind 1/2): element 0..5 (7 = own)
    pub element: u8,
    /// flag byte bit 6: for the 0x00..0x1f word classes "permanent" (a stat word changes the base value of the party member, `0xc..0x15`), for a status word
    /// "unresistable" (protection is not rolled)
    pub perm: bool,
    /// word `+0` bits 15..16 (status words): the record applies to every bit (`0xff` / "cure all")
    pub all: u8,
    /// `SpecialEffectCode` param 2: 1 skill / spell / item (the default), 5 tarot, 6 tarot effect, 7 equipment
    pub src: u8,
}

/// `SpecialEffectCode` for `words` (caster INT / SATK passed in for the kind 9/10/0xb bonuses), source type 1 (skill / spell / item).
pub fn decode_effect_words(words: &[u32; 4], int_stat: i32, satk: i32, is_pc: bool) -> Vec<EffRec> {
    decode_effect_words_src(words, 1, int_stat, satk, is_pc, 0)
}

/// `SpecialEffectCode(chr, src, id, words, out, chr)` (retail SLUS 0x369330).  `fusion_bonus` = the fused character's level bonus (`FUSM`
/// growth row byte `+6 + id`, added to the magnitude of every non-damage value of a fusion skill, src 1).
pub fn decode_effect_words_src(words: &[u32; 4], src: u8, int_stat: i32, satk: i32, is_pc: bool, fusion_bonus: i32) -> Vec<EffRec> {
    let mut out = Vec::new();
    let bump = |v: i32| -> i32 {
        if v > 0 {
            v + fusion_bonus
        } else if v < 0 {
            v - fusion_bonus
        } else {
            v
        }
    };
    let int_bonus = |kind: u8, value: &mut i32, _percent: &mut bool| match kind {
        9 | 10 => *value += if is_pc { int_stat * 2 } else { satk },
        0xb if is_pc => *value += int_stat / 10,
        _ => {}
    };
    let mut i = 0;
    while i < 4 {
        let w = words[i];
        if w == 0xffff_ffff {
            i += 1;
            continue;
        }
        let b3 = (w >> 24) as u8;
        match b3 {
            0x00..=0x0f => {
                // damage word: kind 1 physical / 2 magical, element `b3 & 7` (7 = the caster's own), percent bit = word bit 23
                out.push(EffRec {
                    kind: if b3 & 8 != 0 { 2 } else { 1 },
                    percent: (w >> 23) & 1 != 0,
                    chance: 100,
                    value: (w & 0xffff) as u16 as i16 as i32,
                    element: b3 & 7,
                    perm: true,
                    src,
                    ..Default::default()
                });
                i += 1;
            }
            0x10..=0x1f => {
                let kind = ((w >> 16) & 0xff) as u8 + 3;
                let mut value = (w & 0xffff) as u16 as i16 as i32;
                let mut percent = b3 & 0x08 != 0;
                int_bonus(kind, &mut value, &mut percent);
                out.push(EffRec { kind, percent, dur: (b3 >> 2) & 1, chance: 100, value: bump(value), element: 7, perm: true, src, ..Default::default() });
                i += 1;
            }
            0x20..=0x2f => {
                let w2 = words[(i + 1).min(3)];
                let value = ((w << 8) as i32) >> 8;
                let turns = ((w2 >> 16) & 0x3f) as u8;
                let chance = ((w2 >> 24) & 0x7f) as u8;
                let dur = (b3 >> 2) & 3;
                let all = (b3 >> 1) & 1;
                out.push(EffRec { kind: crate::rules::modkind::STATUS, dur, chance, turns, value, element: 7, perm: b3 & 1 != 0, all, src, ..Default::default() });
                if w & 0x80_0000 != 0 {
                    out.push(EffRec { kind: crate::rules::modkind::STATUS_AUX, dur, chance, turns, value: 0, element: 7, perm: b3 & 1 != 0, all: 3, src, ..Default::default() });
                }
                i += 2;
            }
            0x30..=0x3f => {
                let w2 = words[(i + 1).min(3)];
                let value = ((w << 8) as i32) >> 8;
                out.push(EffRec {
                    kind: crate::rules::modkind::STATUS_AUX,
                    dur: (b3 >> 2) & 3,
                    chance: ((w2 >> 24) & 0x7f) as u8,
                    turns: ((w2 >> 16) & 0x3f) as u8,
                    value,
                    element: 7,
                    all: b3 & 3,
                    src,
                    ..Default::default()
                });
                i += 2;
            }
            0x40..=0x4f => {
                let kind = (((w >> 21) & 0x7f) as u8) + 3;
                let mut value = (w & 0xff) as u8 as i8 as i32;
                let mut percent = (w >> 8) & 1 != 0;
                int_bonus(kind, &mut value, &mut percent);
                out.push(EffRec {
                    kind,
                    percent,
                    chance: (((w << 11) >> 25) & 0x7f) as u8,
                    turns: ((w >> 9) & 0x1f) as u8,
                    value: bump(value),
                    element: 7,
                    src,
                    ..Default::default()
                });
                i += 1;
            }
            0x50..=0x5f => {
                let kind = (((w >> 21) & 0x7f) as u8) + 3;
                let raw = (w & 0x1fff) as i32;
                let mut value = if raw < 0x1000 { raw } else { raw - 0x2000 };
                let mut percent = (w >> 13) & 1 != 0;
                int_bonus(kind, &mut value, &mut percent);
                // `'?'` (HP drain) / `'='` (MP drain): a party member adds +-INT*2, a monster's value is a percentage
                if kind == crate::rules::modkind::HP_DRAIN || kind == crate::rules::modkind::MP_DRAIN {
                    if is_pc {
                        percent = false;
                        value += if value < 0 { -int_stat * 2 } else { int_stat * 2 };
                    } else {
                        percent = true;
                    }
                }
                out.push(EffRec { kind, percent, chance: (((w << 11) >> 25) & 0x7f) as u8, value: bump(value), element: 7, src, ..Default::default() });
                i += 1;
            }
            _ => {
                // not an effect word (e.g. a float area parameter in MAGI +8): skip
                i += 1;
            }
        }
    }
    out
}

/// A usable action record (item / magic / skill).
#[derive(Clone, Debug)]
pub struct ActionRec {
    pub id: i32,
    /// name index inside its SSHMES section (items: id, magic: id, PC skills and monster skills: the record's +2 column --
    /// `SetSkill1Menu`: `GetRegDat(9, rec+2)`)
    pub name_idx: i32,
    /// PC skills: the +0x3e column = index of the description (`sshmes` kind 0x1f); -1 elsewhere
    pub help_idx: i32,
    pub flags: u16,
    pub words: [u32; 4],
    /// `EFFECT/%03d_00.EFD`, -1 none
    pub effect_id: i32,
    /// +0x1a (percent)
    pub power: i32,
    pub mp: i32,
    pub empty: bool,
    /// usable in battle (`(flags & 0x1f) >> 3` is 1 or 2)
    pub battle_use: bool,
    pub revive: bool,
    /// Judgement Ring of the action (`CBattle::EffectFunc`, JP CBattle.c 0x4a6ee0 / retail `EffectFunc` 0x484650): skills and crest
    /// magic carry up to five `AddStepArea(start, width)` zones at `+0x20..+0x33` (the list stops at the first width <= 0) and one
    /// `AddModulateArea(start, width, min_pct, strike)` at `+0x34..+0x3b` (added when its width > 0); items one `AddStrikeArea(start,
    /// width, strike)` at `+0x1c..+0x21`.  Live: Cure = modulate (60, 60, 100, 15) only (`01l`), Crag = step (145, 50) + modulate
    /// (220, 100, 60, 10) (`09b`), Thera Leaf = strike (45, 120, 15).
    pub ring_steps: Vec<(i16, i16)>,
    pub ring_mod: Option<(i16, i16, i16, i16)>,
    pub ring_strike: Option<(i16, i16, i16)>,
    /// `+0x1c` of a skill / spell record: the flat bonus `EffectDamageSet` hands to `GetSAtkDamage` / `GetSkillPAtkDamage` (0 for items)
    pub flat: i16,
}

impl ActionRec {
    /// `rec+4 & 7`: the element of the damage (`EffectDamageSet` `bVar12`; 7 = the actor's own)
    pub fn element(&self) -> u8 {
        (self.flags & 7) as u8
    }
    /// `rec+5` bit 6: the damage uses `GetSAtkDamage` (magical) instead of `GetSkillPAtkDamage`
    pub fn magical(&self) -> bool {
        self.flags & 0x4000 != 0
    }
    /// `(rec+4 >> 7) & 3`: `GetTargetList` side class (0 self, 1 the actor's side, 2 the other side, 3 everybody)
    pub fn side_class(&self) -> u8 {
        ((self.flags >> 7) & 3) as u8
    }
    /// `(rec+5 & 0xf) >> 1`: the area shape (1 circle, 3 line, 4 line + circle, 5 everybody, else one target)
    pub fn shape(&self) -> u8 {
        ((self.flags >> 9) & 7) as u8
    }
    /// `(rec+5 & 0x3f) >> 4`: the area size (0..2)
    pub fn size(&self) -> u8 {
        ((self.flags >> 12) & 3) as u8
    }
    /// `+0x1a / 100`: the `TurnEnd` / `MakeTurnOrderTable` factor of the action (3.0 = an attack; 0 = not set)
    pub fn turn_factor(&self) -> f32 {
        self.power as f32 / 100.0
    }
    /// any damage word (`SpecialEffectCode` classes 0x00..0x0f -> kinds 1 / 2)
    pub fn deals_damage(&self) -> bool {
        self.words.iter().any(|&w| w != 0xffff_ffff && (w >> 24) < 0x10)
    }
    pub fn target_class(&self) -> TargetClass {
        TargetClass::from_flags(self.flags, self.revive)
    }
    pub fn is_offensive(&self) -> bool {
        matches!(self.target_class(), TargetClass::Opponent | TargetClass::OpponentsAlive)
    }
}

fn rec_words(b: &[u8], o: usize) -> [u32; 4] {
    [u32at(b, o), u32at(b, o + 4), u32at(b, o + 8), u32at(b, o + 12)]
}

fn make_rec(b: &[u8], id: i32, words_off: usize, name_idx: i32, has_effect_id: bool) -> ActionRec {
    let flags = u16at(b, 4);
    let words = rec_words(b, words_off);
    let revive = {
        let w = words[0];
        (w >> 28) == 1 && (w >> 24) & 8 != 0 && ((w >> 16) & 0xff) as u8 == 0x28
    };
    ActionRec {
        id,
        name_idx,
        help_idx: -1,
        flags,
        words,
        effect_id: if has_effect_id { i16at(b, 0x18) as i32 } else { -1 },
        power: i16at(b, 0x1a) as i32,
        mp: u16at(b, 0x1e) as i32,
        empty: u16at(b, 2) == 0xffff,
        battle_use: matches!((flags & 0x1f) >> 3, 1 | 2),
        revive,
        ring_steps: vec![],
        ring_mod: None,
        ring_strike: None,
        flat: 0,
    }
}

/// The ring zones of a skill / magic record (`+0x20..+0x3b`, see [`ActionRec::ring_steps`]).
fn read_ring_zones(rec: &mut ActionRec, b: &[u8]) {
    if b.len() < 0x3c {
        return;
    }
    for k in 0..5 {
        let (s, w) = (i16at(b, 0x20 + k * 4), i16at(b, 0x22 + k * 4));
        if w <= 0 {
            break;
        }
        rec.ring_steps.push((s, w));
    }
    let w = i16at(b, 0x36);
    if w > 0 {
        rec.ring_mod = Some((i16at(b, 0x34), w, i16at(b, 0x38), i16at(b, 0x3a)));
    }
    rec.flat = i16at(b, 0x1c);
}

/// Crest record (`MC_P`).
#[derive(Clone, Debug)]
pub struct CrestRec {
    pub id: i32,
    pub flags: u8,
    pub magic: [i16; 4],
}

/// The battle action databases.
#[derive(Clone, Debug, Default)]
pub struct ActionTables {
    pub items: Vec<ActionRec>,
    pub magic: Vec<ActionRec>,
    /// SKIL groups 0..24: records of party members / fusion monsters
    pub groups: Vec<Vec<ActionRec>>,
    pub mon_skills: Vec<ActionRec>,
    pub mon_sets: Vec<[i16; 20]>,
    pub crests: Vec<CrestRec>,
    pub item_names: Vec<String>,
    pub magic_names: Vec<String>,
    pub skill_names: Vec<String>,
    /// item menu order by the `+0x2c` sort column (`SetItemMenu` sort mode 1)
    pub item_order: Vec<usize>,
    /// item menu order by the `+0x2e` sort column (sort mode 2); mode 0 lists the bag by id
    pub item_order2: Vec<usize>,
    /// `MAGI` sort columns `+0x3e / +0x40 / +0x42` (`SetMagicMenu` sort modes 1..3)
    pub magic_sort: Vec<[u16; 3]>,
    /// `FUSM` names (`GetRegDat(1, i)`) and the SP upkeep column `+5` of each fusion row (`SetFusionMenu`)
    pub fusion_names: Vec<String>,
    pub fusion_sp: Vec<u8>,
    /// `FUSM+2`: model / portrait number of the fusion monster
    pub fusion_models: Vec<u16>,
    /// `FUSM+0x1d`: the soul the fusion belongs to (its level is `BTL0+0xf24 + soul`)
    pub fusion_soul: Vec<u8>,
    /// `FUSM+8..+0x16`: up to seven `SKIL` record indices of the fusion's special skills (-1 empty) and `+0x16..+0x1d` the fusion level each
    /// one needs (`SetSkill1Menu`, fused path)
    pub fusion_skills: Vec<([i16; 7], [u8; 7])>,
    /// retail: aroma oil names (`GetRegDat(0xd, i)`) and the combination rows of `GetRegDat(0x43)`: `(first oil, second oil, MP)`
    pub aroma_names: Vec<String>,
    pub aroma_combos: Vec<(u8, u8, u16)>,
    /// retail: `GetRegDat(0xf, 0)` = `Snap Shot`
    pub snap_label: String,
    /// retail: tarot card names (`GetRegDat(0xe, i)`)
    pub tarot_names: Vec<String>,
    /// `COMB` (sec 22, `GetRegDat(0x3f)` retail): the combo magic records (0x40 B, one per element 0..6 plus 7 = the Ouka / Hien / Raiden trio),
    /// names `GetRegDat(0xc)` (demo section 20)
    pub combos: Vec<ActionRec>,
    pub combo_names: Vec<String>,
    /// retail: the aroma combination rows `(record, turns, chance)` (`AromaEffectFunc` / `AromaTurnReset`)
    pub aroma_rows: Vec<(ActionRec, u8, u8)>,
}

impl ActionTables {
    pub fn load(data: &BattleData) -> Self {
        let mut t = ActionTables::default();
        // items
        let isec = data.dat.section(SEC_ITEM);
        let n = isec.len() / 0x30;
        for i in 0..n {
            let r = &isec[i * 0x30..(i + 1) * 0x30];
            let mut rec = make_rec(r, i as i32, 8, i as i32, true);
            rec.mp = 0;
            if i16at(r, 0x1e) > 0 {
                rec.ring_strike = Some((i16at(r, 0x1c), i16at(r, 0x1e), i16at(r, 0x20)));
            }
            t.items.push(rec);
        }
        t.item_names = (0..n).map(|i| unescape_sjis(&data.name(12, i))).collect();
        // menu order: row `i` is shown at the position given by its +0x2c column
        let mut order: Vec<usize> = (0..n).collect();
        order.sort_by_key(|&i| u16at(&isec[i * 0x30..(i + 1) * 0x30], 0x2c));
        t.item_order = order;
        let mut order2: Vec<usize> = (0..n).collect();
        order2.sort_by_key(|&i| u16at(&isec[i * 0x30..(i + 1) * 0x30], 0x2e));
        t.item_order2 = order2;
        // magic
        let msec = data.dat.section(SEC_MAGIC);
        let n = msec.len() / 0x44;
        for i in 0..n {
            let r = &msec[i * 0x44..(i + 1) * 0x44];
            let mut rec = make_rec(r, i as i32, 8, i as i32, true);
            read_ring_zones(&mut rec, r);
            t.magic.push(rec);
            t.magic_sort.push([u16at(r, 0x3e), u16at(r, 0x40), u16at(r, 0x42)]);
        }
        t.magic_names = (0..n).map(|i| unescape_sjis(&data.name(17, i))).collect();
        // skills
        let ssec = data.dat.section(SEC_SKILL);
        let groups: Vec<(u32, u32)> = (0..24).map(|g| (u32at(ssec, g * 8), u32at(ssec, g * 8 + 4))).collect();
        // the retail `SKIL` has 24 groups of 0x40 B records (0..13 party members, 14..23 fusion monsters); the demo keeps its monster
        // skill sets / records in groups 0x16 / 0x17
        let retail_groups = data.raw_us.is_some();
        for (g, &(off, cnt)) in groups.iter().enumerate() {
            let mut v = Vec::new();
            if off != 0xffff_ffff && (g < 0x16 || retail_groups) {
                for i in 0..cnt as usize {
                    let o = off as usize + i * 0x40;
                    if let Some(r) = ssec.get(o..o + 0x40) {
                        // name = `GetRegDat(9, rec+2)` (both builds; the US group 11 reads Cure / Blessed Light / Divine Light), +0x3e = description row
                        let mut rec = make_rec(r, i as i32, 8, i16at(r, 2) as i32, true);
                        rec.help_idx = i16at(r, 0x3e) as i32;
                        read_ring_zones(&mut rec, r);
                        v.push(rec);
                    }
                }
            }
            t.groups.push(v);
        }
        // monster skill sets (0x28 B) / monster skills (0x20 B): demo groups 0x16 / 0x17, retail groups 0x18 / 0x19 (`GetRegDat(0x3c, 0x18 / 0x19)`
        // in the retail `AITurnFunc` / `AIIfFunc` / `EffectFunc`; groups 0x16 / 0x17 of the retail file are fusion skill groups) -- round 5 BE
        let (g_sets, g_skills) = if retail_groups { (0x18usize, 0x19usize) } else { (0x16, 0x17) };
        let groups: Vec<(u32, u32)> = (0..26).map(|g| (u32at(ssec, g * 8), u32at(ssec, g * 8 + 4))).collect();
        if let Some(&(off, cnt)) = groups.get(g_sets).filter(|g| g.0 != 0xffff_ffff) {
            for i in 0..cnt as usize {
                let o = off as usize + i * 0x28;
                let mut set = [-1i16; 20];
                for k in 0..20 {
                    set[k] = i16at(ssec, o + k * 2);
                }
                t.mon_sets.push(set);
            }
        }
        if let Some(&(off, cnt)) = groups.get(g_skills).filter(|g| g.0 != 0xffff_ffff) {
            for i in 0..cnt as usize {
                let o = off as usize + i * 0x20;
                if let Some(r) = ssec.get(o..o + 0x20) {
                    t.mon_skills.push(make_rec(r, i as i32, 8, i16at(r, 2) as i32, true));
                }
            }
        }
        t.skill_names = (0..data.mes.count(15, 18)).map(|i| unescape_sjis(&data.name(15, i))).collect();
        // fusions (`FUSM` of the first table, 0x20 B rows; names `SSHMES` section 4)
        let fsec = data.dat.section(crate::data::SEC_FUSION[0]);
        for i in 0..fsec.len() / 0x20 {
            let r = &fsec[i * 0x20..(i + 1) * 0x20];
            t.fusion_names.push(unescape_sjis(&data.name(4, i)));
            t.fusion_sp.push(r[5]);
            t.fusion_models.push(u16at(r, 2));
            t.fusion_soul.push(r[0x1d]);
            let mut ids = [-1i16; 7];
            let mut lv = [0u8; 7];
            for k in 0..7 {
                ids[k] = i16at(r, 8 + k * 2);
                lv[k] = r[0x16 + k];
            }
            t.fusion_skills.push((ids, lv));
        }
        if let Some(us) = data.us() {
            // aroma oils / combinations (Lucia), the Snap Shot label (Anastasia), the tarot cards
            let oils = us.count(0x42, 0).unwrap_or(0).min(64);
            t.aroma_names = (0..oils).map(|i| us.text(0xd, i, -1).unwrap_or_default()).collect();
            let combos = us.count(0x43, 0).unwrap_or(0).min(256);
            t.aroma_combos = (0..combos).filter_map(|i| us.record(0x43, i, -1).filter(|r| r.len() >= 0x20).map(|r| (r[0x1c], r[0x1d], u16at(r, 0x1e)))).collect();
            // the combination rows themselves (0x40 B, `GetRegDat(0x43)`): three effect words at +8, `+0x16` turns, `+0x17` chance, effect id
            // `+0x18`, `+0x1a` turn factor, ring zones `+0x20..`
            t.aroma_rows = (0..combos)
                .filter_map(|i| {
                    let r = us.record(0x43, i, -1).filter(|r| r.len() >= 0x40)?;
                    let mut rec = make_rec(r, i as i32, 8, i as i32, true);
                    rec.words[3] = 0xffff_ffff;
                    rec.mp = u16at(r, 0x1e) as i32;
                    read_ring_zones(&mut rec, r);
                    Some((rec, r[0x16], r[0x17]))
                })
                .collect();
            t.snap_label = us.text(0xf, 0, -1).unwrap_or_default();
            t.tarot_names = (0..22).map(|i| us.text(0xe, i, -1).unwrap_or_default()).collect();
        }
        // combo magic (`CheckComboSkill` 0x69abe0: row = the member's element)
        let csec_c = data.dat.section(crate::data::SEC_COMBO);
        for i in 0..csec_c.len() / 0x40 {
            let r = &csec_c[i * 0x40..(i + 1) * 0x40];
            let mut rec = make_rec(r, i as i32, 8, i as i32, true);
            read_ring_zones(&mut rec, r);
            t.combos.push(rec);
            let n = data.us().and_then(|us| us.text(0xc, i, -1)).unwrap_or_else(|| unescape_sjis(&data.name(20, i)));
            t.combo_names.push(n);
        }
        // crests
        let csec = data.dat.section(20);
        for i in 0..csec.len() / 0x1c {
            let r = &csec[i * 0x1c..(i + 1) * 0x1c];
            t.crests.push(CrestRec { id: i as i32, flags: r[6], magic: [i16at(r, 8), i16at(r, 10), i16at(r, 12), i16at(r, 14)] });
        }
        t
    }

    pub fn item_name(&self, id: usize) -> &str {
        self.item_names.get(id).map(|s| s.as_str()).unwrap_or("")
    }
    pub fn magic_name(&self, id: usize) -> &str {
        self.magic_names.get(id).map(|s| s.as_str()).unwrap_or("")
    }
    pub fn skill_name(&self, idx: usize) -> &str {
        self.skill_names.get(idx).map(|s| s.as_str()).unwrap_or("")
    }
    pub fn aroma_name(&self, idx: usize) -> &str {
        self.aroma_names.get(idx).map(|s| s.as_str()).unwrap_or("")
    }
    /// `SetSkill1Menu` (fused path): `SKIL` group of fusion `id` (0..2 -> 14, 3..5 -> 15, ... 0x12 / 0x13 -> 20, 0x14 -> 21, 0x15 -> 22, 0x16 -> 23).
    pub fn fusion_group(id: usize) -> usize {
        match id {
            0..=0x11 => 14 + id / 3,
            0x12 | 0x13 => 20,
            0x14 => 21,
            0x15 => 22,
            _ => 23,
        }
    }

    /// Magic ids a party member can cast: `PCParam+0x76..0x7d` (8 crest slots, -1 empty) -> `MC_P` -> up to four `MAGI` ids each;
    /// `learned(crest)` is the crest-learned bit (`BtlSave` +0xaae).
    pub fn crest_magic(&self, slots: &[i8], learned: &dyn Fn(usize) -> bool) -> Vec<usize> {
        let mut out: Vec<usize> = Vec::new();
        for &c in slots {
            if c < 0 {
                continue;
            }
            let Some(cr) = self.crests.get(c as usize) else { continue };
            for (k, &m) in cr.magic.iter().enumerate() {
                if m < 0 {
                    continue;
                }
                // flag bit k = "needs the learned bit"
                let need = cr.flags & (1 << k) != 0;
                if need && !learned(c as usize) {
                    continue;
                }
                if !out.contains(&(m as usize)) {
                    out.push(m as usize);
                }
            }
        }
        out.sort();
        out
    }

    /// The special-command list of a party member (`SKIL` group = party id).
    pub fn pc_skills(&self, pc: usize) -> Vec<&ActionRec> {
        self.groups.get(pc).map(|g| g.iter().filter(|r| !r.empty && r.battle_use).collect()).unwrap_or_default()
    }

    /// `AiTables` for the AI VM.
    pub fn ai_tables(&self) -> crate::ai::AiTables {
        crate::ai::AiTables {
            mon_sets: self.mon_sets.clone(),
            mon_skill_offensive: self.mon_skills.iter().map(|s| ((s.flags & 0x7f) >> 5) == 0).collect(),
            items: self
                .items
                .iter()
                .map(|r| {
                    crate::ai::ItemAi { flags: r.flags, w18: r.effect_id as i16, w8: r.words[0] as i32, wc: r.words[1] as i32 }
                })
                .collect(),
            magic_mp: self.magic.iter().map(|m| m.mp as u16).collect(),
            mon_skill_words: self.mon_skills.iter().map(|r| r.words).collect(),
            group_words: self.groups.iter().map(|g| g.iter().map(|r| r.words).collect()).collect(),
            mon_skill_b5_40: self.mon_skills.iter().map(|s| s.flags & 0x4000 != 0).collect(),
        }
    }
}

/// What one record application changed on one target (for messages and the floating numbers).
#[derive(Clone, Debug, Default, PartialEq)]
pub struct Applied {
    /// signed HP change (negative = damage)
    pub hp: i32,
    pub mp: i32,
    pub sp: i32,
    pub revived: bool,
    pub status_added: u32,
    pub status_cured: u32,
    pub buffs: Vec<u8>,
    /// `ECResult+0x58`: status bits / immunity bits the target resisted (protection / monster immunity)
    pub blocked: u32,
    /// `ECResult+0x46` bit 3: at least one record did nothing ("Miss" / no effect)
    pub failed: bool,
    /// `ECResult+0x46` bit 4: the target fell (HP drain / cut to 0, instant death, petrify)
    pub fell: bool,
    /// HP / MP taken by the drain kinds 0x3f / 0x3d (`CBattle+0x490c`, given to the caster)
    pub drained: i32,
    /// kind 0x4c: the `ITEM` id stolen from a monster
    pub stolen_item: Option<i32>,
    /// kind 0x4d: cash taken from a monster (positive) or from the party (negative)
    pub cash: i32,
    /// permanent changes of a party member's base values (`0xc..0x15` words with the permanent flag, Seal items): `(kind, delta)`
    pub permanent: Vec<(u8, i32)>,
}

/// Per-target inputs of `EffectCodeFunc` that the [`Fighter`] does not carry.
#[derive(Clone, Copy, Debug)]
pub struct EcEnv {
    /// `param_1 * 100`: the action's power percentage (100 = the record value as is)
    pub power: i32,
    /// `param_8` (`noRandom`): skip every chance roll (Tarot, AI dry runs)
    pub no_random: bool,
    /// monster immunity bits (`MONSTERParam+0x32..0x34`, see [`monster_immunity`]); 0 for party members
    pub immune: u32,
    /// PC id of the target (`BtlChr+0x120`), -1 for monsters: PCs 8 / 9 / 10 (Ouka / Hien / Raiden) have no Sanity
    pub pc: i32,
    /// `MONSTERParam` drop items `+0x1a / +0x1c` of a monster target (steal)
    pub drops: [i16; 2],
    /// `MONSTERParam+0x28`: the reward cash of a monster target (cash steal)
    pub mon_cash: i32,
    /// the party's cash (cash steal by a monster)
    pub party_cash: i32,
}

impl Default for EcEnv {
    fn default() -> Self {
        EcEnv { power: 100, no_random: false, immune: 0, pc: 0, drops: [-1, -1], mon_cash: 0, party_cash: 0 }
    }
}

/// Monster immunity mask of `EffectCodeFunc` (retail SLUS 0x36b410, the `uStack_680` set-up for `bFlagsB & 1` targets) from the bytes
/// `MONSTERParam+0x32 / +0x33 / +0x34`: status bits 1 / 2 / 4 / 8 / 0x20 / 0x80 (byte 0x34 bits 0..5), stat-down immunities 0x800 PATK,
/// 0x1000 PDEF, 0x2000 SATK, 0x4000 SDEF (byte 0x32 bits 4..7), 0x8000 AGL, 0x10000 LUC, 0x20000 delay, 0x40000 turn interval, 0x80000 evasion,
/// 0x100 HP cut (byte 0x33 bits 0..5).  Monsters are 100 % protected against the bits they have.
pub fn monster_immunity(b32: u8, b33: u8, b34: u8) -> u32 {
    let mut m = 0u32;
    for (bit, v) in [(0, 1u32), (1, 2), (2, 4), (3, 8), (4, 0x20), (5, 0x80)] {
        if b34 & (1 << bit) != 0 {
            m |= v;
        }
    }
    for (bit, v) in [(4, 0x800u32), (5, 0x1000), (6, 0x2000), (7, 0x4000)] {
        if b32 & (1 << bit) != 0 {
            m |= v;
        }
    }
    for (bit, v) in [(0, 0x8000u32), (1, 0x10000), (2, 0x20000), (3, 0x40000), (4, 0x80000), (5, 0x100)] {
        if b33 & (1 << bit) != 0 {
            m |= v;
        }
    }
    m
}

/// Stat-down immunity bit of a timed modifier kind (`EffectCodeFunc` cases 0x13 / 0x14 / 0x17..0x1c).
fn stat_immunity(kind: u8) -> u32 {
    match kind {
        0x13 => 0x8000,
        0x14 => 0x10000,
        0x17 => 0x800,
        0x18 => 0x2000,
        0x19 => 0x1000,
        0x1a => 0x4000,
        0x1b => 0x40000,
        0x1c => 0x80000,
        _ => 0,
    }
}

fn roll(rng: &mut dyn Rng, chance: u8) -> bool {
    (rng.rand() % 100) <= chance as i32
}

/// `(power * v +- 50) / 100`
fn by_power(power: i32, v: i32) -> i32 {
    if v < 0 {
        (power * v - 50) / 100
    } else {
        (power * v + 50) / 100
    }
}

/// `(power * base * v +- 5000) / 10000` (percent records)
fn pct_of(power: i32, base: i32, v: i32) -> i32 {
    let p = power as i64 * base as i64 * v as i64;
    (if v < 0 { (p - 5000) / 10000 } else { (p + 5000) / 10000 }) as i32
}

/// `EffectCodeFunc` value of an HP / MP / SP record: percent of `pct_base`, or the flat value scaled by the power; never 0 for a non-zero value.
/// `bump` = the MP / SP rule "a power above 100 % that leaves the value unchanged adds 1".
fn amount(r: &EffRec, power: i32, pct_base: i32, bump: bool) -> i32 {
    let mut a = if r.percent {
        pct_of(power, pct_base, r.value)
    } else {
        let a = by_power(power, r.value);
        if bump && power > 100 && a == r.value {
            a + r.value.signum()
        } else {
            a
        }
    };
    if a == 0 {
        a = r.value.signum();
    }
    a
}

/// Change `cur` (max `max`, min `lo`) by `a`: add (duration type 0) or "raise to" (type 1, never lowers).  Returns the applied delta.
fn change(cur: i32, max: i32, lo: i32, a: i32, raise: bool) -> i32 {
    if !raise {
        let mut d = a;
        if cur + d < lo {
            d = lo - cur;
        }
        if cur + d > max {
            d = max - cur;
        }
        d
    } else {
        let t = a.clamp(lo.min(0), max);
        (t - cur).max(0)
    }
}

/// Find the slot of a timed modifier the way `EffectCodeFunc` does: the first live record of the same kind with the same percent flag (and,
/// with `signed`, the same sign of the value).  `None` = a free slot is used (a new record).
fn find_slot(status: &[StatMod], kind: u8, percent: bool, value: i32, signed: bool) -> Option<usize> {
    status.iter().position(|m| {
        m.kind == kind && m.percent == percent && m.turns != 0 && (!signed || ((m.value >= 0 || value < 1) && (m.value < 1 || value >= 0)))
    })
}

/// Store a timed modifier: a new record, or a refresh of the found one (the duration only grows; `turns == 0` records are permanent).
/// `turns` already includes the `+1` of the original.
fn store_timed(status: &mut Vec<StatMod>, slot: Option<usize>, kind: u8, percent: bool, value: i32, turns: u8) {
    match slot {
        Some(i) => {
            let m = &mut status[i];
            if turns == 0 || m.turns < turns {
                m.turns = turns;
            }
            m.value = value;
        }
        None => status.push(StatMod { turns, chance: 100, percent, kind, value }),
    }
}

/// The retail `EffectCodeFunc` (SLUS 0x36b410, `param_7 != NULL` = a battle character) for one target: every record kind the retail
/// tables use.  `env.power` is `param_1 * 100`.  The fighter's `max_*` fields are the battle maxima (`BtlChr+0x12c / 0x134 / 0x138`), the
/// turn slot carries the timer of the delay kind.  Returns what changed (the `ECResult`).
pub fn effect_code(recs: &[EffRec], target: &mut Fighter, env: &EcEnv, rng: &mut dyn Rng) -> Applied {
    use crate::rules::modkind as mk;
    let mut a = Applied::default();
    let power = env.power;
    let no_sp = target.is_enemy || matches!(env.pc, 8..=10);
    // `uStack_670`: the target's current status (the dead bit 0x80 while HP < 1); `uStack_680` / `auStack_60`: protections
    let mut cur_status: u32 = crate::rules::status_of(&target.status) | if target.hp < 1 { 0x80 } else { 0 };
    let mut protect: u32 = env.immune;
    let mut protect_pct = [100u8; 24];
    if !target.is_enemy {
        protect_pct = [0; 24];
        for m in target.status.iter().chain(target.passives.iter()).filter(|m| m.kind == mk::STATUS_PROTECT) {
            let bits = m.value as u32;
            for (b, p) in protect_pct.iter_mut().enumerate() {
                if bits & (1 << b) != 0 {
                    protect |= 1 << b;
                    *p = (*p).max(m.chance);
                }
            }
        }
    }
    let mut revived_now = false;
    for r in recs {
        let rolls = !env.no_random;
        let k = r.kind;
        match k {
            // damage words are `EffectDamageSet`'s
            1 | 2 => {}
            3 | 6 | 9 => {
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                let base = if k == 6 { target.max_hp } else { target.hp };
                let am = amount(r, power, base, false);
                let d = if revived_now && r.dur == 0 {
                    // a revive followed by a heal: the HP becomes the healed value (`bVar5`)
                    let d = change(target.hp, target.max_hp, 0, am, false);
                    if d == 0 {
                        am.clamp(1, target.max_hp) - target.hp
                    } else {
                        d
                    }
                } else {
                    change(target.hp, target.max_hp, 0, am, r.dur != 0)
                };
                target.hp += d;
                a.hp += d;
                if d == 0 {
                    a.failed = true;
                }
            }
            4 | 7 | 10 => {
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                let max = target.max_mp.max(target.mp);
                let base = if k == 7 { max } else { target.mp };
                let am = amount(r, power, base, true);
                let d = change(target.mp, max, 0, am, r.dur != 0);
                target.mp += d;
                a.mp += d;
                if d == 0 {
                    a.failed = true;
                }
            }
            5 | 8 | 11 => {
                if no_sp || (rolls && !roll(rng, r.chance)) {
                    a.failed = true;
                    continue;
                }
                let base = if k == 8 { target.max_sp } else { target.sp };
                let am = amount(r, power, base, true);
                let d = change(target.sp, target.max_sp, -99, am, r.dur != 0);
                target.sp += d;
                a.sp += d;
                if d == 0 {
                    a.failed = true;
                }
            }
            0xc..=0x15 if r.perm => {
                // a permanent change of the party member's base value (Seal items): `PCParam` max HP / MP / SP, STR .. LUC, +0x2c
                if target.is_enemy || (rolls && !roll(rng, r.chance)) {
                    a.failed = true;
                    continue;
                }
                let am = if r.percent {
                    let base = match k {
                        0xc => target.max_hp,
                        0xd => target.max_mp,
                        0xe => target.max_sp,
                        _ => 0,
                    };
                    pct_of(power, base, r.value)
                } else {
                    let v = by_power(power, r.value);
                    if power > 100 && v == r.value {
                        v + r.value.signum()
                    } else {
                        v
                    }
                };
                let am = if am == 0 { r.value.signum() } else { am };
                match k {
                    0xc => {
                        let d = change(target.max_hp, 999, 1, am, false);
                        target.max_hp += d;
                        target.hp = target.hp.min(target.max_hp);
                        a.permanent.push((k, d));
                    }
                    0xd => {
                        let d = change(target.max_mp, 999, 0, am, false);
                        target.max_mp += d;
                        target.mp = target.mp.min(target.max_mp);
                        a.permanent.push((k, d));
                    }
                    0xe => {
                        let d = change(target.max_sp, 99, 1, am, false);
                        target.max_sp += d;
                        target.sp = target.sp.min(target.max_sp);
                        a.permanent.push((k, d));
                    }
                    0x13 => {
                        target.agl = (target.agl + am).clamp(1, 0x7fff);
                        a.permanent.push((k, am));
                    }
                    0x14 => {
                        target.luc = (target.luc + am).clamp(1, 0x7fff);
                        a.permanent.push((k, am));
                    }
                    _ => a.permanent.push((k, am)),
                }
            }
            0xc..=0x15 | 0x17..=0x1c | 0x30 | 0x31 => {
                // timed stat modifier (`'\x17'` style): same kind + percent + sign; stat-down immunity of monsters
                if k == 0x15 && (target.is_enemy || matches!(env.pc, 0 | 7..=10)) {
                    a.failed = true;
                    continue;
                }
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                if r.value < 0 && !env.no_random && env.immune & stat_immunity(k) != 0 {
                    a.blocked |= stat_immunity(k);
                    a.failed = true;
                    continue;
                }
                let slot = find_slot(&target.status, k, r.percent, r.value, true);
                let turns = if r.turns == 0 { 0 } else { r.turns.saturating_add(1) };
                store_timed(&mut target.status, slot, k, r.percent, by_power(power, r.value), turns);
                a.buffs.push(k);
                if k == 0xc {
                    target.hp = target.hp.min(target.max_hp);
                }
            }
            0x16 => {
                // turn delay: the timer grows by `interval * v %` or `v / 100`
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                if r.value >= 0 && !env.no_random && env.immune & 0x20000 != 0 {
                    a.blocked |= 0x20000;
                    a.failed = true;
                    continue;
                }
                let d = if r.percent {
                    target.turn.interval * (power * r.value) as f32 / 10000.0
                } else {
                    (power * r.value) as f32 / 10000.0
                };
                target.turn.timer = (target.turn.timer + d).max(0.0);
                a.buffs.push(k);
            }
            0x1d..=0x22 | 0x25..=0x28 | 0x32..=0x36 | 0x38..=0x3c | 0x3e | 0x29 | 0x2a | 0x4f | 0x50 | 0x51 | 0x52 => {
                // generic timed modifier: same kind + percent; exclusions of `EffectCodeFunc`
                if k == 0x1d && target.is_enemy {
                    a.failed = true;
                    continue;
                }
                if k == 0x38 && (target.is_enemy || !matches!(env.pc, 0 | 7)) {
                    a.failed = true;
                    continue;
                }
                if k == 0x1e && no_sp {
                    a.failed = true;
                    continue;
                }
                let skip_roll = env.no_random && k != 0x1e;
                if !skip_roll && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                let slot = find_slot(&target.status, k, r.percent, r.value, false);
                let turns = match k {
                    // the charges last until the target's next action (`+0x122 = 2`)
                    0x4f | 0x50 => 2,
                    _ if r.turns == 0 => 0,
                    _ if r.src == 5 => r.turns,
                    _ => r.turns.saturating_add(1),
                };
                store_timed(&mut target.status, slot, k, r.percent, by_power(power, r.value), turns);
                a.buffs.push(k);
            }
            0x23 => {
                // own element override (party members only): replaces the other element records; nothing if the same element is active
                if target.is_enemy || (rolls && !roll(rng, r.chance)) {
                    a.failed = true;
                    continue;
                }
                if target.status.iter().any(|m| m.kind == k && m.value == r.value) {
                    a.failed = true;
                    continue;
                }
                target.status.retain(|m| m.kind != k);
                let turns = if r.turns == 0 { 0 } else { ((power * (r.turns as i32 + 1) + 50) / 100).clamp(1, 63) as u8 };
                target.status.push(StatMod { turns, chance: 100, percent: false, kind: k, value: r.value });
                a.buffs.push(k);
            }
            0x24 | 0x37 => {
                // one record of the kind (element resistance / ...): the value is replaced, the duration grows
                if !env.no_random && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                let slot = target.status.iter().position(|m| m.kind == k);
                let turns = if r.turns == 0 { 0 } else { r.turns.saturating_add(1) };
                store_timed(&mut target.status, slot, k, r.percent, r.value, turns);
                a.buffs.push(k);
            }
            0x2b => {
                // revive: only a fallen target; HP 1, the death state is cleared
                if cur_status & 0x80 == 0 {
                    a.failed = true;
                    continue;
                }
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                target.hp = 1;
                target.removed = false;
                for m in target.status.iter_mut().filter(|m| mk::is_status(m.kind)) {
                    m.value &= !(0x80 | 0x20);
                }
                target.status.retain(|m| !(mk::is_status(m.kind) && m.value == 0));
                cur_status &= !0x80;
                a.status_cured |= 0x80;
                a.revived = true;
                a.hp += 1;
                revived_now = true;
            }
            0x2c..=0x2f => {
                // HP + MP + SP (0x2f: MP + SP) of the percent / flat value
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                if k != 0x2f {
                    let am = amount(r, power, target.max_hp, false);
                    let d = change(target.hp, target.max_hp, 0, am, r.dur != 0);
                    target.hp += d;
                    a.hp += d;
                }
                let max = target.max_mp.max(target.mp);
                let am = amount(r, power, max, true);
                let d = change(target.mp, max, 0, am, r.dur != 0);
                target.mp += d;
                a.mp += d;
                if !no_sp {
                    let am = amount(r, power, target.max_sp, true);
                    let d = change(target.sp, target.max_sp, -99, am, r.dur != 0);
                    target.sp += d;
                    a.sp += d;
                }
            }
            mk::MP_DRAIN | mk::HP_DRAIN => {
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                let (cur, max) = if k == mk::HP_DRAIN { (target.hp, target.max_hp) } else { (target.mp, target.max_mp.max(target.mp)) };
                let am = if r.percent { pct_of(power, max, r.value) } else { by_power(power, r.value) };
                let am = if am == 0 { r.value.signum() } else { am };
                let take = am.min(cur).max(0);
                if k == mk::HP_DRAIN {
                    target.hp -= take;
                    a.hp -= take;
                    if cur > 0 && target.hp < 1 {
                        a.fell = true;
                    }
                } else {
                    target.mp -= take;
                    a.mp -= take;
                }
                a.drained += take;
                if take == 0 {
                    a.failed = true;
                }
            }
            0x40..=0x4b => {
                // the "cut" families: 0x40 / 0x43 / 0x46 / 0x49 HP, 0x41 / 0x44 / 0x47 / 0x4a MP, 0x42 / 0x45 / 0x48 / 0x4b SP
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                let fam = (k - 0x40) % 3;
                let var = (k - 0x40) / 3;
                let (cur, max, imm) = match fam {
                    0 => (target.hp, target.max_hp, 0x100u32),
                    1 => (target.mp, target.max_mp.max(target.mp), 0x200),
                    _ => (target.sp, target.max_sp, 0x400),
                };
                let mut am = 0;
                if cur > 0 {
                    am = match var {
                        // % of the current value (rounded up) or flat
                        0 => {
                            if r.percent {
                                (cur * by_power(power, r.value) + 99) / 100
                            } else {
                                r.value
                            }
                        }
                        // % of the maximum or flat
                        1 => {
                            if r.percent {
                                (max * by_power(power, r.value) + 99) / 100
                            } else {
                                r.value
                            }
                        }
                        // % of the current, or "down to the value"
                        2 => {
                            if r.percent {
                                (cur * by_power(power, r.value) + 99) / 100
                            } else if r.value < cur {
                                cur - r.value
                            } else {
                                0
                            }
                        }
                        // % of the maximum (nothing if more than the current), or "down to the value"
                        _ => {
                            if r.percent {
                                let v = (max * by_power(power, r.value) + 99) / 100;
                                if cur < v {
                                    0
                                } else {
                                    v
                                }
                            } else if r.value < cur {
                                cur - r.value
                            } else {
                                0
                            }
                        }
                    };
                }
                if am <= 0 || (!env.no_random && env.immune & imm != 0 && r.src != 6) {
                    a.failed = true;
                    if am > 0 {
                        a.blocked |= imm;
                    }
                    continue;
                }
                let take = am.min(cur);
                match fam {
                    0 => {
                        target.hp -= take;
                        a.hp -= take;
                        if cur > 0 && target.hp < 1 {
                            a.fell = true;
                        }
                    }
                    1 => {
                        target.mp -= take;
                        a.mp -= take;
                    }
                    _ => {
                        target.sp -= take;
                        a.sp -= take;
                    }
                }
            }
            mk::STEAL => {
                // steal: a monster's drop item (`MONSTERParam+0x1a`, then `+0x1c`, success `rand() % 100 < power + value - 100`)
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                match env.drops.iter().copied().find(|&d| d >= 0) {
                    Some(id) if target.is_enemy => {
                        if !env.no_random && (rng.rand() % 100) >= power + r.value - 100 {
                            a.failed = true;
                            continue;
                        }
                        a.stolen_item = Some(id as i32);
                    }
                    _ => a.failed = true,
                }
            }
            mk::CASH_STEAL => {
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                let got = if target.is_enemy { pct_of(power, env.mon_cash, r.value).min(env.mon_cash) } else { -pct_of(power, env.party_cash, r.value).min(env.party_cash) };
                if got == 0 {
                    a.failed = true;
                }
                a.cash += got;
            }
            mk::REMOVE => {
                // remove every beneficial record (`EffectCodeFunc` case 0x4e, the same list as the AI's "has a beneficial effect")
                if rolls && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                let before = target.status.len();
                target.status.retain(|m| !is_beneficial(m));
                if target.status.len() == before {
                    a.failed = true;
                }
            }
            mk::STATUS => status_word(r, target, env, rng, &mut a, &mut cur_status, protect, &protect_pct),
            mk::STATUS_AUX => {
                // auxiliary word: protections (type 2) and cures (type 1) of the `'U'` bits; type 0 sets them
                if !env.no_random && !roll(rng, r.chance) {
                    a.failed = true;
                    continue;
                }
                match r.dur {
                    1 => {
                        let mask = if r.all != 0 { u32::MAX } else { r.value as u32 };
                        for m in target.status.iter_mut().filter(|m| m.kind == mk::STATUS_AUX) {
                            m.value &= !(mask as i32);
                        }
                        target.status.retain(|m| !(m.kind == mk::STATUS_AUX && m.value == 0));
                    }
                    d => {
                        let turns = if r.turns == 0 { 0 } else { r.turns.saturating_add(1) };
                        let kind = if d == 2 { mk::STATUS_AUX_PROTECT } else { k };
                        target.status.push(StatMod { turns, chance: r.chance, percent: false, kind, value: r.value });
                    }
                }
            }
            _ => {}
        }
    }
    a
}

/// `EffectCodeFunc` case 0x4e / the AI's `EffectCheck` 0x4e: is a status record a beneficial effect that *Remove* takes away?
pub fn is_beneficial(m: &StatMod) -> bool {
    use crate::rules::modkind as mk;
    let v = m.value;
    match m.kind {
        mk::SKIP_TURN => false,
        mk::STATUS_PROTECT | mk::STATUS_AUX_PROTECT => true,
        mk::STATUS_AUX => (v as u32 & 0x1f800) != 0,
        0x50 | 0x4f | 0x37 | 0x2a | 0x29 | 0x23 => true,
        0x3a => (m.percent && v < 100) || (!m.percent && v < 0),
        0x36 => v > 0x78,
        0x34 => v < 1,
        0x38 | 0x33 | 0x22 | 0x21 | 0x1e | 0x1d | 0x1b => v < 0,
        0x3e | 0x3c | 0x35 => (m.percent && v > 100) || (!m.percent && v > 0),
        0x20 | 0x1f | 0x39 | 0x32 | 0x28 | 0x27 | 0x26 | 0x25 | 0x1c | 0x31 | 0x30 | 0x1a | 0x18 | 0x19 | 0x17 | 0x14 | 0x13 | 0xe | 0xd | 0xc => v > 0,
        _ => false,
    }
}

/// `EffectCodeFunc` case 0x54 (`'T'`): inflict (type 0), cure (type 1) or grant a protection (type 2) of status bits.
#[allow(clippy::too_many_arguments)]
fn status_word(r: &EffRec, target: &mut Fighter, env: &EcEnv, rng: &mut dyn Rng, a: &mut Applied, cur: &mut u32, protect: u32, protect_pct: &[u8; 24]) {
    use crate::rules::modkind as mk;
    match r.dur {
        2 => {
            let bits = if r.all != 0 { 0xff } else { r.value as u32 };
            for m in target.status.iter_mut().filter(|m| m.kind == mk::STATUS_PROTECT) {
                m.value &= !(bits as i32);
            }
            target.status.retain(|m| !(m.kind == mk::STATUS_PROTECT && m.value == 0));
            let turns = if r.turns == 0 { 0 } else { r.turns.saturating_add(1) };
            target.status.push(StatMod { turns, chance: r.chance, percent: false, kind: mk::STATUS_PROTECT, value: bits as i32 });
            a.buffs.push(mk::STATUS);
        }
        1 => {
            let want: u32 = if r.all == 0 {
                let mut w = 0;
                for b in 0..23 {
                    if r.value as u32 & (1 << b) != 0 && (env.no_random || roll(rng, r.chance)) {
                        w |= 1 << b;
                    }
                }
                w
            } else if !env.no_random && !roll(rng, r.chance) {
                0
            } else {
                u32::MAX
            };
            if want == 0 {
                a.failed = true;
                return;
            }
            let mut cured = 0u32;
            for m in target.status.iter_mut().filter(|m| mk::is_status(m.kind)) {
                let had = m.value as u32 & want;
                cured |= had;
                m.value &= !(had as i32);
            }
            target.status.retain(|m| !(mk::is_status(m.kind) && m.value == 0));
            *cur &= !want;
            if cured == 0 {
                a.failed = true;
            }
            a.status_cured |= cured;
        }
        _ => {
            let mut bits = 0u32;
            for b in 0..23 {
                let req = r.value as u32 & (1 << b) != 0 || r.all != 0;
                if !req {
                    continue;
                }
                if !env.no_random && !roll(rng, r.chance) {
                    continue;
                }
                // protection: unresistable words and dry runs pass, otherwise a protected bit lands only when `rand() % 100 > protection %`
                let ok = r.perm || env.no_random || protect & (1 << b) == 0 || (rng.rand() % 100) > protect_pct[b] as i32;
                if ok {
                    bits |= 1 << b;
                } else {
                    a.blocked |= 1 << b;
                }
            }
            if bits == 0 {
                a.failed = true;
                return;
            }
            if bits & 0x80 != 0 && *cur & 0x80 == 0 {
                // instant death: `DeadReset`, HP 0
                target.hp = 0;
                *cur = 0x80;
                a.status_added |= 0x80;
                a.fell = true;
                return;
            }
            if bits & 0x20 != 0 && *cur & 0x80 == 0 {
                // petrify: `DeadReset`, the only remaining status record
                target.status.retain(|m| !mk::is_status(m.kind));
                target.status.push(StatMod { turns: 0, chance: 100, percent: false, kind: mk::STATUS, value: 0x20 });
                *cur = 0x20;
                a.status_added |= 0x20;
                a.fell = true;
                return;
            }
            if *cur & 0x80 != 0 {
                // nothing sticks on a fallen unit
                a.failed = true;
                return;
            }
            // poison on poison becomes Deadly Poison
            let poisoned = target.status.iter().any(|m| mk::is_status(m.kind) && m.value & 3 != 0);
            if poisoned && bits & 3 != 0 {
                for m in target.status.iter_mut().filter(|m| mk::is_status(m.kind)) {
                    m.value &= !3;
                }
                bits = (bits & !3) | 2;
            }
            for m in target.status.iter_mut().filter(|m| mk::is_status(m.kind)) {
                m.value &= !(bits as i32);
            }
            target.status.retain(|m| !(mk::is_status(m.kind) && m.value == 0));
            let turns = if r.turns == 0 { 0 } else { r.turns.saturating_add(1) };
            target.status.push(StatMod { turns, chance: r.chance, percent: false, kind: mk::STATUS, value: bits as i32 });
            *cur |= bits;
            a.status_added |= bits;
        }
    }
}

/// `EffectCodeFunc` with the defaults of an item / spell / skill used on a party member (power 100 %, source type 1): the entry point the
/// field menu (`sh2_field::cmd_item`) and the older host code use.
pub fn apply_records(recs: &[EffRec], target: &mut Fighter, rng: &mut dyn Rng) -> Applied {
    let env = EcEnv { pc: if target.is_enemy { -1 } else { target.char_id }, ..Default::default() };
    effect_code(recs, target, &env, rng)
}

// =====================================================================================================================================
// Party-side action engine (round 5 BP): PC battle stats (`PCInit` + the stat getters), the per-fighter extra state the `Fighter` does not
// carry, `GetTargetList`, `DecMPp`, and the resolution of items / crest magic / skills (`EffectFunc` -> `EffectDamageSet` -> `GetSAtkDamage`
// / `GetSkillPAtkDamage` + `EffectCodeFunc`).  Retail addresses: SH2US_BATTLE.BIN (load 0x45ea80) / SLUS_210.41.
// =====================================================================================================================================

use crate::rules::{GlobalMod, Resist};

/// The Defend stance chosen on the `Block` / `Resist` page (`SetGuardMenu` 0x603640: labels `GetRegDat(0x2a, 0x2a / 0x2b)`).  Retail
/// `BtlMenuFunc` step 0x32 puts the defender into `bState` 0x11 and `CheckGuard` (0x63f030) answers 1 (*Block*, damage x 0.25) or 2 when
/// `BtlChr+0xb5` bit 3 is set (*Resist*, damage x 0.5); the stance lasts until the character's next turn.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub enum Guard {
    #[default]
    None,
    Block,
    Resist,
}

impl Guard {
    /// `CheckGuard` class without guard records (1 block, 2 full guard).
    pub fn class(self) -> u8 {
        match self {
            Guard::None => 0,
            Guard::Block => 1,
            Guard::Resist => 2,
        }
    }
}

/// Per-fighter state of the battle that the shared [`Fighter`] has no field for (kept by `Battle::ext`, filled by `party_setup`).
#[derive(Clone, Debug, Default)]
pub struct FighterExt {
    /// PC id (`BtlChr+0x120`), -1 for monsters
    pub pc: i32,
    /// monster immunity bits ([`monster_immunity`]), 0 for party members
    pub immune: u32,
    /// `MONSTERParam` drop items / cash (steal, cash steal)
    pub drops: [i16; 2],
    pub mon_cash: i32,
    /// elemental resist classes against physical / magical damage: party members from the armour + accessories (`resist_bits`), monsters
    /// from `MONSTERParam+0x32` (the same class for every element: bits 0..1 physical, 2..3 magic)
    pub resist_p: [Resist; 6],
    pub resist_m: [Resist; 6],
    /// bounding radius (`BtlChr+0x354`) for the area shapes
    pub radius: f32,
    /// the Defend stance (until the next own turn)
    pub guard: Guard,
    /// the eight equipped crests (`PCParam+0x32..`, `DecMPp`)
    pub crests: [i8; 8],
    /// raw stats before modifiers: max HP / MP / SP, STR, VIT, INT, POW, AGL, LUC and the gear sums for PATK / SATK / PDEF / SDEF
    pub raw: Option<RawStats>,
    /// monster stats from `MONSTERParam` (the modifiers are applied on top)
    pub mon: Option<RawStats>,
    /// the cash of this monster was already taken by *Cash Steal* (`BtlChr+0xb6` bit 5) / an item was stolen
    pub cash_stolen: bool,
    pub item_stolen: bool,
    /// `BtlChr+0xb6` bit 2: the character went berserk (Sanity ran out) -- it acts by itself (`BerserkFunc`)
    pub berserk: bool,
    /// the `JRCI` ring item effect words of the character's ring (retail `PAtkEffectFunc`, `GetRegDat(0x46)` row `PCParam+0x68`), applied to
    /// every physical hit with the ring grade as power
    pub ring_item: Option<[u32; 4]>,
    /// the raw stats of the human form (restored when a fusion ends)
    pub base_raw: Option<RawStats>,
    /// the element of the character for the combo magic (`CheckComboSkill`), 7 = none
    pub combo_element: u8,
    /// Joachim: the Yoahism row (`GetRegDat(0x48)[BtlSocket+0x698]` = `BtlSave::yoahism()`): `+10` max HP %, `+0xb` PATK %, `+0xc` SATK %,
    /// `+0xd` evasion % (`GetMaxHP` / `GetPAtk` / `GetSAtk` / `GetEvasionRate` for `nCharId == 6`)
    pub yoah: Option<[i32; 4]>,
    /// Gepetto: the elements Cornelia's dress strengthens (`GetSAtkDamage`: `CLOT` row `BTL0+0xf3e` byte 6 bits 3..7 / byte 7 bits 0..1 ->
    /// +25 % for spells of that element)
    pub element_mask: u32,
    /// the element of the human form (weapon element, 6 = none)
    pub base_element: u8,
    /// Yuri / Kurando: per `FUSM` row the growth bonuses at the soul's current level (`GetRegDat(0x33, id)` row `BTL0+0xf24+FUSM[0x1d]` - 1)
    pub fusions: Vec<FusionForm>,
}

/// What a fusion changes on the character (`FusMonInit` 0x49fb10 + the getters' fused branch).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct FusionForm {
    pub id: i32,
    /// STR, VIT, AGL, INT, POW, LUC bonuses of the growth row
    pub growth: [i32; 6],
    /// growth row bytes `+6..+0xd`: the flat damage bonus of the fusion's skill `k` (`GetSAtkDamage`: `row[cmd + 6]`)
    pub skill_flat: [i8; 8],
    /// `FUSM+4 & 7`: the element of the fused form (`SpecialEffectCode` element 7)
    pub element: u8,
    /// soul level (1..)
    pub level: u8,
}

/// The fusion forms of a character from the `FUSM` rows / growth table and the save's soul levels (`BTL0+0xf24 + FUSM[0x1d]`).
pub fn fusion_forms(data: &crate::data::BattleData, ids: &[usize], level_of: &dyn Fn(usize) -> u8) -> Vec<FusionForm> {
    let fsec = data.dat.section(crate::data::SEC_FUSION[0]);
    let gsec = data.dat.section(crate::data::SEC_FUSION_GROW);
    ids.iter()
        .filter_map(|&id| {
            let r = fsec.get(id * 0x20..id * 0x20 + 0x20)?;
            let level = level_of(r[0x1d] as usize).max(1);
            let growth = fusion_growth(data, id, level);
            let off = u32at(gsec, id * 8) as usize;
            let cnt = u32at(gsec, id * 8 + 4) as usize;
            let o = off + (level as usize - 1).min(cnt.saturating_sub(1)) * 0x10;
            let mut skill_flat = [0i8; 8];
            for (k, v) in skill_flat.iter_mut().enumerate() {
                *v = gsec.get(o + 6 + k).copied().unwrap_or(0) as i8;
            }
            Some(FusionForm { id: id as i32, growth, skill_flat, element: r[4] & 7, level })
        })
        .collect()
}

/// Switch a character's stats to fusion `id` (`None` = back to the human form): `FusMonInit` keeps the PC's own record and adds the growth row.
pub fn apply_fusion_stats(f: &mut Fighter, ext: &mut FighterExt, id: Option<i32>) {
    let Some(base) = ext.base_raw.or(ext.raw) else { return };
    ext.base_raw = Some(base);
    match id.and_then(|id| ext.fusions.iter().find(|x| x.id == id).copied()) {
        Some(form) => {
            let g = form.growth;
            ext.raw = Some(RawStats { str_: base.str_ + g[0], vit: base.vit + g[1], agl: base.agl + g[2], int: base.int + g[3], pow: base.pow + g[4], luc: base.luc + g[5], ..base });
            f.element = crate::rules::Element(form.element.min(6));
        }
        None => {
            ext.raw = Some(base);
            f.element = crate::rules::Element(if ext.base_element < 6 { ext.base_element } else { 6 });
        }
    }
    refresh_stats(f, ext);
}

/// The values the stat getters start from (see [`FighterExt::raw`]).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct RawStats {
    pub max_hp: i32,
    pub max_mp: i32,
    pub max_sp: i32,
    pub str_: i32,
    pub vit: i32,
    pub int: i32,
    pub pow: i32,
    pub agl: i32,
    pub luc: i32,
    /// weapon + accessory PATK, weapon + accessory SATK, armour + accessory PDEF / SDEF (`GetPAtk` 0x63a1b0 ... `GetSDef` 0x63b900)
    pub gear_patk: i32,
    pub gear_satk: i32,
    pub gear_pdef: i32,
    pub gear_sdef: i32,
}

/// `modded` with the getters' clamps.
fn getter(base: i32, status: &[StatMod], passives: &[StatMod], kinds: &[u8], lo: i32, hi: i32) -> i32 {
    crate::rules::modded(base, status, passives, kinds).clamp(lo, hi)
}

/// Recompute the cached battle stats of a fighter from its raw values and the current modifier lists (what the retail game does after every
/// stat record: `EffectCodeFunc` writes `GetPAtk(..)` to `BtlChr+0x140` etc.).  PCs: `GetMaxHP` (1..999), `GetStr` .. `GetLuc`, `GetPAtk` =
/// `GetStr + gear` with kinds 0x17 / 0x30 ...; monsters: the `MONSTERParam` value with the status modifiers only.
pub fn refresh_stats(f: &mut Fighter, ext: &FighterExt) {
    use crate::rules::modkind as mk;
    if let Some(r) = ext.raw.filter(|_| !f.is_enemy) {
        let (st, pa) = (f.status.as_slice(), f.passives.as_slice());
        f.max_hp = getter(r.max_hp, st, pa, &[mk::MAX_HP], 1, 999);
        f.max_mp = getter(r.max_mp, st, pa, &[mk::MAX_MP], 0, 999);
        if f.max_sp > 0 || r.max_sp > 0 {
            f.max_sp = getter(r.max_sp, st, pa, &[mk::MAX_SP], 1, 99);
        }
        let s = getter(r.str_, st, pa, &[mk::STR], 0, 0x7fff);
        let v = getter(r.vit, st, pa, &[mk::VIT], 0, 0x7fff);
        let i = getter(r.int, st, pa, &[mk::INT], 0, 0x7fff);
        let p = getter(r.pow, st, pa, &[mk::POW], 0, 0x7fff);
        f.agl = getter(r.agl, st, pa, &[mk::AGL], 1, 0x7fff);
        f.luc = getter(r.luc, st, pa, &[mk::LUC], 1, 0x7fff);
        f.patk = getter(s + r.gear_patk, st, pa, &[mk::PATK, mk::ATK_BOTH], 0, 0x7fff);
        f.satk = getter(i + r.gear_satk, st, pa, &[mk::SATK, mk::ATK_BOTH], 0, 0x7fff);
        f.pdef = getter(v + r.gear_pdef, st, pa, &[mk::PDEF, mk::DEF_BOTH], 0, 0x7fff);
        f.sdef = getter(p + r.gear_sdef, st, pa, &[mk::SDEF, mk::DEF_BOTH], 0, 0x7fff);
        if let Some(y) = ext.yoah {
            f.max_hp = ((f.max_hp * y[0] + 50) / 100).clamp(1, 999);
            f.patk = ((f.patk * y[1] + 50) / 100).clamp(0, 0x7fff);
            f.satk = ((f.satk * y[2] + 50) / 100).clamp(0, 0x7fff);
        }
    } else if let Some(r) = ext.mon {
        let st = f.status.as_slice();
        f.max_hp = getter(r.max_hp, st, &[], &[mk::MAX_HP], 1, 0x7fff);
        f.max_mp = getter(r.max_mp, st, &[], &[mk::MAX_MP], 0, 0x7fff);
        f.agl = getter(r.agl, st, &[], &[mk::AGL], 1, 0x7fff);
        f.luc = getter(r.luc, st, &[], &[mk::LUC], 1, 0x7fff);
        f.patk = getter(r.gear_patk, st, &[], &[mk::PATK, mk::ATK_BOTH], 0, 0x7fff);
        f.satk = getter(r.gear_satk, st, &[], &[mk::SATK, mk::ATK_BOTH], 0, 0x7fff);
        f.pdef = getter(r.gear_pdef, st, &[], &[mk::PDEF, mk::DEF_BOTH], 0, 0x7fff);
        f.sdef = getter(r.gear_sdef, st, &[], &[mk::SDEF, mk::DEF_BOTH], 0, 0x7fff);
    }
    f.hp = f.hp.min(f.max_hp);
    f.mp = f.mp.min(f.max_mp.max(0));
    if f.max_sp > 0 {
        f.sp = f.sp.min(f.max_sp);
    }
}

/// The battle stats of a party member the way `PCInit` (retail 0x49d180) and the getters compute them from the save record: base values
/// from the `PCParam` record, the weapon (`WPN_` +8 PATK / +0xa SATK), the armour (`ARM_` +6 PDEF / +8 SDEF, +0xa / +0xb resists), the three
/// accessories (`ACS_` +6 / +8 / +0xa / +0xc and their effect words, `SpecialEffectCode` source type 7 = the passives), and -- while fused --
/// the fusion growth row (`GetRegDat(0x33, fusion)` row `level - 1`: STR +0, VIT +1, AGL +2, INT +3, POW +4, LUC +5).
pub struct PcStats {
    pub raw: RawStats,
    pub passives: Vec<StatMod>,
    pub resist: [Resist; 6],
    /// the weapon's element (`WPN_+0x5 & 7`, 7 = none -> the attack is neutral)
    pub element: u8,
}

/// Fusion growth bonuses `[STR, VIT, AGL, INT, POW, LUC]` of fusion `id` at `level` (1..), from the `FUSION_GROW` table (`GetRegDat(0x33)` retail,
/// demo section 10: 0x10 byte rows per level, one block per fusion).
pub fn fusion_growth(data: &crate::data::BattleData, id: usize, level: u8) -> [i32; 6] {
    let sec = data.dat.section(crate::data::SEC_FUSION_GROW);
    let off = u32at(sec, id * 8) as usize;
    let cnt = u32at(sec, id * 8 + 4) as usize;
    let lv = (level.max(1) as usize - 1).min(cnt.saturating_sub(1));
    let o = off + lv * 0x10;
    if off == 0xffff_ffff || cnt == 0 || sec.len() < o + 6 {
        return [0; 6];
    }
    let b = |k: usize| sec[o + k] as i8 as i32;
    [b(0), b(1), b(2), b(3), b(4), b(5)]
}

pub fn pc_stats(data: &crate::data::BattleData, rec: &sh2_menu::save::PcRec, pc: u8, fusion: Option<[i32; 6]>) -> PcStats {
    let wpn = (rec.weapon >= 0).then(|| data.weapon(rec.weapon as usize)).flatten();
    let wraw = (rec.weapon >= 0).then(|| data.dat.record(crate::data::SEC_WEAPON, rec.weapon as usize, crate::data::WeaponRec::SIZE)).flatten();
    let arm = (rec.armor >= 0).then(|| data.armor(rec.armor as usize)).flatten();
    let accs: Vec<_> = rec.accessories.iter().filter(|&&a| a >= 0).filter_map(|&a| data.accessory(a as usize)).collect();
    let g = fusion.unwrap_or([0; 6]);
    let raw = RawStats {
        max_hp: rec.hp_max as i32,
        max_mp: rec.mp_max as i32,
        max_sp: rec.sp_max as i32,
        str_: rec.str_ as i32 + g[0],
        vit: rec.vit as i32 + g[1],
        agl: rec.agl as i32 + g[2],
        int: rec.int as i32 + g[3],
        pow: rec.pow as i32 + g[4],
        luc: rec.luc as i32 + g[5],
        gear_patk: wpn.map(|w| w.patk as i32).unwrap_or(0) + accs.iter().map(|a| a.patk as i16 as i32).sum::<i32>(),
        gear_satk: wpn.map(|w| w.satk as i32).unwrap_or(0) + accs.iter().map(|a| a.satk as i16 as i32).sum::<i32>(),
        gear_pdef: arm.map(|a| a.pdef as i32).unwrap_or(0) + accs.iter().map(|a| a.pdef as i16 as i32).sum::<i32>(),
        gear_sdef: arm.map(|a| a.sdef as i32).unwrap_or(0) + accs.iter().map(|a| a.sdef as i16 as i32).sum::<i32>(),
    };
    let mut passives = Vec::new();
    for a in &accs {
        for e in decode_effect_words_src(&a.effects, 7, rec.int as i32, 0, true, 0) {
            if matches!(e.kind, 1 | 2) {
                continue;
            }
            let kind = if crate::rules::modkind::is_status(e.kind) && e.dur == 2 { crate::rules::modkind::STATUS_PROTECT } else { e.kind };
            // the equipment records carry their chance in `+5` (guard records) and the protection percentage of the status words
            passives.push(StatMod { turns: 0, chance: e.chance, percent: e.percent, kind, value: e.value });
        }
    }
    let _ = pc;
    let mut resist = [Resist::Normal; 6];
    for (el, r) in resist.iter_mut().enumerate() {
        let base = arm.map(|a| Resist::from_bits(a.resist(el as u8) as u32)).unwrap_or(Resist::Normal);
        let others: Vec<Resist> = accs.iter().map(|a| Resist::from_bits(a.resist(el as u8) as u32)).collect();
        *r = crate::rules::merge_resist(base, &others);
    }
    let element = wraw.map(|w| w[5] & 7).unwrap_or(7);
    PcStats { raw, passives, resist, element }
}

/// Set up a party member's [`Fighter`] / [`FighterExt`] from its save record (the `PCInit` stat pipeline).  Keeps HP / MP / SP.
pub fn apply_pc_stats(f: &mut Fighter, ext: &mut FighterExt, st: &PcStats) {
    f.passives = st.passives.clone();
    ext.raw = Some(st.raw);
    ext.base_raw = Some(st.raw);
    ext.base_element = st.element.min(6);
    ext.resist_p = st.resist;
    ext.resist_m = st.resist;
    if st.element < 6 {
        f.element = crate::rules::Element(st.element);
    }
    refresh_stats(f, ext);
}

/// A monster's [`FighterExt`] from its `MONSTERParam` record (0x38 B): immunities `+0x32..0x34`, resist classes `+0x32` (bits 0..1 physical,
/// 2..3 magic, `GetPAtkDamage` / `GetSAtkDamage`), drops / cash for the steal kinds, the raw stats for [`refresh_stats`].
pub fn monster_ext(rec: &[u8]) -> FighterExt {
    let m = crate::data::MonsterParam::parse(rec);
    let rp = Resist::from_bits((rec[0x32] & 3) as u32);
    let rm = Resist::from_bits(((rec[0x32] >> 2) & 3) as u32);
    FighterExt {
        pc: -1,
        immune: monster_immunity(rec[0x32], rec[0x33], rec[0x34]),
        drops: m.item,
        mon_cash: m.cash,
        resist_p: [rp; 6],
        resist_m: [rm; 6],
        radius: 3.0,
        mon: Some(RawStats {
            max_hp: m.hp as i32,
            max_mp: m.mp as i32,
            agl: m.agl as i32,
            luc: m.luc as i32,
            gear_patk: m.patk as i32,
            gear_satk: m.satk as i32,
            gear_pdef: m.pdef as i32,
            gear_sdef: m.sdef as i32,
            ..Default::default()
        }),
        ..Default::default()
    }
}

/// `GetTargetList(actor, target, class, shape, size, words, &n, list)` (retail 0x688350).  `pos` / `radius` per fighter (any space whose
/// x / z axes are the floor; the shapes measure in the floor plane).  `revive` = the record's first word is a revive word (the list holds
/// fallen units only).  Returns the member list, the chosen target first.
#[allow(clippy::too_many_arguments)]
pub fn target_list(fighters: &[Option<Fighter>], pos: &[[f32; 3]], radius: &[f32], actor: usize, target: i32, class: u8, shape: u8, size: u8, revive: bool, berserk: bool) -> Vec<usize> {
    let valid = |i: usize| fighters.get(i).and_then(|f| f.as_ref()).map(|f| !f.removed).unwrap_or(false);
    let side_of = |i: usize| fighters.get(i).and_then(|f| f.as_ref()).map(|f| f.is_enemy).unwrap_or(false);
    let me_enemy = side_of(actor);
    // side filter: 0 = everybody, 1 = party side, 2 = enemy side (absolute, like the original's iVar17), 3 = mixed (berserk, invalid target)
    let side: u8 = if berserk && !me_enemy {
        if class == 3 {
            0
        } else if target < 0 || target as usize >= fighters.len() {
            3
        } else if !side_of(target as usize) {
            1
        } else {
            2
        }
    } else if class == 3 {
        0
    } else if class == 1 {
        if me_enemy { 2 } else { 1 }
    } else if me_enemy {
        1
    } else {
        2
    };
    let target = if class == 0 { actor as i32 } else { target };
    let hp_ok = |i: usize| {
        let hp = fighters[i].as_ref().map(|f| f.hp).unwrap_or(0);
        if revive {
            hp < 1
        } else {
            hp > 0
        }
    };
    let side_ok = |i: usize| match side {
        0 | 3 => true,
        1 => !side_of(i),
        _ => side_of(i),
    };
    let xz = |i: usize| pos.get(i).map(|p| (p[0], p[2])).unwrap_or((0.0, 0.0));
    let rad = |i: usize| radius.get(i).copied().unwrap_or(3.0);
    let n = fighters.len();
    let mut out: Vec<usize> = Vec::new();
    match shape {
        5 => {
            if target >= 0 && (target as usize) < n && valid(target as usize) {
                out.push(target as usize);
            }
            for i in 0..n {
                if !valid(i) || out.contains(&i) || (berserk && class == 2 && i == actor) {
                    continue;
                }
                if side_ok(i) && hp_ok(i) {
                    out.push(i);
                }
            }
        }
        1 | 3 | 4 if target >= 0 && (target as usize) < n => {
            let t = target as usize;
            out.push(t);
            let (cx, cz) = xz(t);
            let (ax, az) = xz(actor);
            let circle_r = [19.0, 29.0, 39.0][size.min(2) as usize];
            let line_w = if shape == 3 { [6.5, 11.5, 16.5][size.min(2) as usize] } else { 6.5 };
            // the line runs from the actor through the target (shape 3: 300 units long; shape 4: up to the target), units behind the actor are out
            let (dx, dz) = (cx - ax, cz - az);
            let len = (dx * dx + dz * dz).sqrt().max(1e-3);
            let (ux, uz) = (dx / len, dz / len);
            let seg = if shape == 3 { 300.0 } else { len };
            for i in 0..n {
                if i == t || !valid(i) || !side_ok(i) || !hp_ok(i) || (berserk && class == 2 && i == actor) {
                    continue;
                }
                let (px, pz) = xz(i);
                let mut inside = false;
                if shape == 1 || shape == 4 {
                    let d = ((px - cx).powi(2) + (pz - cz).powi(2)).sqrt();
                    inside |= d < circle_r + rad(i);
                }
                if shape == 3 || shape == 4 {
                    let (rx, rz) = (px - ax, pz - az);
                    let along = rx * ux + rz * uz;
                    if along > 0.0 {
                        let a = along.min(seg);
                        let (qx, qz) = (ax + ux * a, az + uz * a);
                        let d = ((px - qx).powi(2) + (pz - qz).powi(2)).sqrt();
                        inside |= d < line_w + rad(i);
                    }
                }
                if inside {
                    out.push(i);
                }
            }
        }
        _ => {
            if target >= 0 && (target as usize) < n && valid(target as usize) {
                out.push(target as usize);
            }
        }
    }
    out
}

/// `DecMPp(actor, kind, id, ..)` (retail 0x6a4de0): the MP an action costs.  Spells (`kind == 2`, party members) are divided by the number of
/// equipped crest slots that carry the spell (a column whose `MC_P+6` bit asks for the learned bit counts only once it is learned); MP-cost
/// modifiers (kind 0x1d, status + accessories) and The Magician (`GlobalMod` stat 1) scale it; the result is rounded up to whole points, at
/// least 1.  Special effect ids 0x4a / 0x5f cost 10 % of the maximum MP.
pub fn mp_cost(tables: &ActionTables, rec: &ActionRec, spell: bool, f: &Fighter, ext: &FighterExt, gm: &GlobalMod, learned: &dyn Fn(usize, usize) -> bool) -> i32 {
    if rec.mp <= 0 && !matches!(rec.effect_id % 1000, 0x4a | 0x5f) {
        return 0;
    }
    let mut c = if matches!(rec.effect_id.rem_euclid(1000), 0x4a | 0x5f) { (f.max_mp * 10 + 50) / 100 } else { rec.mp };
    c *= 100;
    if spell && !f.is_enemy {
        let mut n = 0;
        for &cr in ext.crests.iter().filter(|&&c| c >= 0) {
            let Some(crest) = tables.crests.get(cr as usize) else { continue };
            for (k, &m) in crest.magic.iter().enumerate() {
                if m as i32 == rec.id && (crest.flags & (1 << k) == 0 || learned(cr as usize, k)) {
                    n += 1;
                }
            }
        }
        if n > 0 {
            c /= n;
        }
    }
    for m in f.status.iter().chain(f.passives.iter()).filter(|m| m.kind == 0x1d) {
        if m.percent {
            c += c * m.value / 100;
        } else {
            c += m.value * 100;
        }
    }
    if gm.applies(1) {
        c = c * gm.value / 100;
    }
    c = (c + 99) - (c + 99) % 100;
    (c / 100).max(1)
}

/// R1: the Judgement Ring of a party member's attack as the Ring Customize page set it up (`CmdPC::CustomJudgmentRing` /
/// `CreateJudgmentRing`, `sh2_menu::ringcustom::battle_ring`): hit count, ring type (`JRing+0x41` bits 2..3: normal / practice / technical /
/// gamble, the auto ring = type 1 with one hit) and the `JRCUSTOM` widths built from the equipped weapon's per-area narrowing (`WPN_+0x28..0x32`).
pub fn attack_ring(data: &crate::data::BattleData, session: &sh2_menu::session::GameSession, pc: u8) -> sh2_menu::ringcustom::BattleRing {
    let weapon = session.save.btl.pc(pc as usize).map(|r| r.weapon).unwrap_or(-1);
    let wr: Vec<u8> = (weapon >= 0)
        .then(|| data.dat.record(crate::data::SEC_WEAPON, weapon as usize, crate::data::WeaponRec::SIZE))
        .flatten()
        .map(|r| r[0x28..0x32].to_vec())
        .unwrap_or_default();
    sh2_menu::ringcustom::battle_ring(session, pc, &wr)
}

/// Inputs of [`resolve_action`] besides the fighters.
pub struct ResolveCtx<'a> {
    pub tables: &'a ActionTables,
    /// per fighter: floor positions and radii for the area shapes ([`target_list`])
    pub pos: &'a [[f32; 3]],
    pub radius: &'a [f32],
    pub gm: GlobalMod,
    /// the Judgement Ring grade of the action (`GetJRingAreaResult(-1)`, 1.0 = clean, 0 = miss)
    pub ring: f32,
    /// running Link combo (leader first) and the friendship values (`PCParam+0x84`)
    pub combo: &'a [usize],
    pub friendship: &'a dyn Fn(usize, usize) -> i32,
    /// the party's cash (cash steal by monsters)
    pub party_cash: i32,
    /// the fusion the actor is transformed into (`BtlChr+0xba`), for the skill group of `cmd.p4c == 2`
    pub fused: Option<i32>,
    /// `crest_learned(crest, column)` (`DecMPp`)
    pub learned: &'a dyn Fn(usize, usize) -> bool,
    pub turn_no: i32,
}

/// One target of a resolved action.
#[derive(Clone, Debug, Default)]
pub struct Hit {
    pub target: usize,
    /// damage dealt (> 0; < 0 = absorbed / healed by the damage formula), 0 = no damage part
    pub damage: i32,
    pub critical: bool,
    /// the damage did nothing (`Miss`: ring miss, immune)
    pub missed: bool,
    /// the `EffectCodeFunc` part (HP heal is in `applied.hp`)
    pub applied: Applied,
    /// `CheckGuard` class of the defender (1 Block, 2 Resist)
    pub guard: u8,
}

#[derive(Clone, Debug, Default)]
pub struct Resolved {
    pub record: Option<ActionRec>,
    pub hits: Vec<Hit>,
    pub mp_cost: i32,
    /// `TurnEnd` factor relative to an attack (`rec+0x1a / 300`; 1.0 when the record has none)
    pub turn_factor: f32,
    /// HP / MP drained (given to the actor)
    pub drained: i32,
    pub stolen: Vec<i32>,
    pub cash: i32,
}

/// The record of command `cmd` (`EffectFunc`): kind 0 item, 1 crest magic (party) / `ITEM` "magic" (monsters, AIS token 0x26), 2 PC skill (the
/// character's `SKIL` group, the fusion's group while fused), 3 monster skill (`SKIL` 0x19 retail).
pub fn action_record(tables: &ActionTables, cmd: &crate::flow::Command, me: &Fighter, fused: Option<i32>) -> Option<ActionRec> {
    let id = cmd.p44.max(0) as usize;
    match cmd.p4c {
        0 => tables.items.get(id).cloned(),
        1 if me.is_enemy => tables.items.get(id).cloned(),
        1 => tables.magic.get(id).cloned(),
        2 => {
            let g = match fused {
                Some(fu) if fu >= 0 => ActionTables::fusion_group(fu as usize),
                _ => me.char_id.max(0) as usize,
            };
            tables.groups.get(g).and_then(|g| g.get(id)).cloned()
        }
        3 => tables.mon_skills.get(id).cloned(),
        // phase 0x0b ring skill = combo magic (`EffectDamageSet` kind 4: `GetRegDat(0x3f)` rows of 0x40 B)
        4 => tables.combos.get(id).cloned(),
        _ => None,
    }
}

/// Resolve an item / spell / skill (`EffectFunc` + `EffectDamageSet` + `EffectCodeFunc`) on the fighters.  Pays the MP, builds the target list,
/// rolls the damage of damage records (`GetSkillPAtkDamage` / `GetSAtkDamage` chosen by `rec+5` bit 6, element `rec+4 & 7`, flat `rec+0x1c`,
/// the defender's guard and resists, the ring grade) and applies the effect records with the ring grade as power.  HP changes are applied to the
/// fighters; the caller turns `hits` into events.
pub fn resolve_action(ctx: &ResolveCtx, actor: usize, cmd: &crate::flow::Command, fighters: &mut [Option<Fighter>], ext: &mut [FighterExt], rng: &mut dyn Rng) -> Resolved {
    let mut out = Resolved { turn_factor: 1.0, ..Default::default() };
    let Some(me) = fighters.get(actor).and_then(|f| f.clone()) else { return out };
    let Some(rec) = action_record(ctx.tables, cmd, &me, ctx.fused) else { return out };
    out.record = Some(rec.clone());
    if rec.power > 0 {
        out.turn_factor = rec.turn_factor() / 3.0;
    }
    // costs (`DecMPp`)
    let my_ext = ext.get(actor).cloned().unwrap_or_default();
    if cmd.p4c != 0 && !me.is_enemy {
        let cost = mp_cost(ctx.tables, &rec, cmd.p4c == 1, &me, &my_ext, &ctx.gm, ctx.learned);
        if let Some(Some(f)) = fighters.get_mut(actor) {
            f.mp = (f.mp - cost).max(0);
        }
        out.mp_cost = cost;
    } else if cmd.p4c == 1 && me.is_enemy {
        let cost = rec.mp.max(0);
        if let Some(Some(f)) = fighters.get_mut(actor) {
            f.mp = (f.mp - cost).max(0);
        }
        out.mp_cost = cost;
    }
    // targets (`GetTargetList`)
    let berserk = !me.is_enemy && !matches!(my_ext.pc, 8..=10) && me.max_sp > 0 && me.sp < 1;
    let radius: Vec<f32> = (0..fighters.len()).map(|i| ctx.radius.get(i).copied().or(ext.get(i).map(|e| e.radius)).unwrap_or(3.0)).collect();
    let list = target_list(fighters, ctx.pos, &radius, actor, cmd.p48, rec.side_class(), rec.shape(), rec.size(), rec.revive, berserk);
    // the actor's INT / SATK for the kind 9 / 10 / 11 bonuses: `GetInt` for party members, `GetSAtk` for monsters
    let int_stat = my_ext.raw.map(|r| crate::rules::modded(r.int, &me.status, &me.passives, &[crate::rules::modkind::INT])).unwrap_or(me.satk / 2);
    let recs = decode_effect_words_src(&rec.words, 1, int_stat, me.satk, !me.is_enemy, 0);
    let power = (ctx.ring * 100.0).round() as i32;
    let damage = rec.deals_damage();
    let combo_active = !ctx.combo.is_empty() && !me.is_enemy;
    for &t in &list {
        let Some(tgt) = fighters.get(t).and_then(|f| f.clone()) else { continue };
        let mut hit = Hit { target: t, ..Default::default() };
        let tex = ext.get(t).cloned().unwrap_or_default();
        if damage && tgt.hp > 0 && ctx.ring > 0.0 {
            // `EffectDamageSet`: element of the record (7 = the actor's own), `GetSkillPAtkDamage` / `GetSAtkDamage`, then the guard factor
            let element = match rec.element() {
                e if e < 6 => crate::rules::Element(e),
                _ => me.element,
            };
            let mut av = crate::rules::AttackerView {
                is_enemy: me.is_enemy,
                uses_sanity_bonus: !me.is_enemy && !matches!(my_ext.pc, 8..=10),
                patk: me.patk,
                satk: me.satk,
                luc: me.luc,
                sp: me.sp,
                max_sp: me.max_sp,
                element: me.element,
                element_bonus_mask: my_ext.element_mask,
                status: &me.status,
                passives: &me.passives,
                ..Default::default()
            };
            if combo_active {
                if let Some(&leader) = ctx.combo.first() {
                    if leader != actor {
                        av.friendship_with_leader = (ctx.friendship)(actor, leader);
                    }
                }
            }
            let guard = tex.guard.class();
            let dv = crate::rules::DefenderView {
                is_enemy: tgt.is_enemy,
                pdef: tgt.pdef,
                sdef: tgt.sdef,
                luc: tgt.luc,
                hp: tgt.hp,
                element: tgt.element,
                variance: tgt.variance,
                status: &tgt.status,
                passives: &tgt.passives,
                resist: if rec.magical() { tex.resist_m } else { tex.resist_p },
                guard,
                ..Default::default()
            };
            // the Link combo magic bonus (`GetSAtkDamage`: + friendship(actor, member) / 200 for every other combo member)
            let combo_friend_bonus = if combo_active && rec.magical() { ctx.combo.iter().filter(|&&m| m != actor).map(|&m| (ctx.friendship)(actor, m) / 200).sum() } else { 0 };
            let mh = crate::rules::MagicHit {
                power: ctx.ring,
                power2: 1.0,
                flat_bonus: rec.flat as i32,
                element,
                turn_no: ctx.turn_no,
                combo_active,
                combo_friend_bonus,
                // a fused character's skill gets the growth row's bonus for that skill (`GetSAtkDamage`: `row[cmd + 6]`)
                fusion_flat: match (ctx.fused, cmd.p4c) {
                    (Some(fu), 2) => my_ext.fusions.iter().find(|x| x.id == fu).and_then(|x| x.skill_flat.get(cmd.p44.max(0) as usize)).copied().unwrap_or(0) as i32,
                    _ => 0,
                },
                gm: ctx.gm,
            };
            let r = if rec.magical() { crate::rules::magic_damage(&av, &dv, &mh, rng) } else { crate::rules::skill_physical_damage(&av, &dv, &mh, rng) };
            // `EffectDamageSet`: the guard factor, at least 1 point unless the factor is 0
            let factor = crate::rules::guard_damage_factor(guard);
            let mut dmg = (r.damage * factor) as i32;
            if factor != 0.0 && dmg == 0 {
                dmg = if r.damage > 0.0 { 1 } else if r.damage < 0.0 { -1 } else { 0 };
            }
            hit.guard = guard;
            hit.damage = dmg;
            hit.missed = dmg == 0;
            if let Some(Some(f)) = fighters.get_mut(t) {
                f.hp = (f.hp - dmg).clamp(0, f.max_hp);
            }
        }
        if let Some(Some(f)) = fighters.get_mut(t) {
            let env = EcEnv {
                power: power.max(1),
                no_random: false,
                immune: tex.immune,
                pc: tex.pc,
                drops: if tex.item_stolen { [-1, -1] } else { tex.drops },
                mon_cash: if tex.cash_stolen { 0 } else { tex.mon_cash },
                party_cash: ctx.party_cash,
            };
            // the damage words are `EffectDamageSet`'s; a fallen target only takes the revive records
            let rs: Vec<EffRec> = recs.iter().copied().filter(|r| !matches!(r.kind, 1 | 2)).collect();
            if !rs.is_empty() && (f.hp > 0 || rec.revive || rs.iter().any(|r| r.kind == 0x2b)) && ctx.ring > 0.0 {
                hit.applied = effect_code(&rs, f, &env, rng);
            } else if !rs.is_empty() && ctx.ring <= 0.0 {
                hit.missed = true;
            }
            if let Some(e) = ext.get_mut(t) {
                if hit.applied.stolen_item.is_some() {
                    e.item_stolen = true;
                }
                if hit.applied.cash > 0 {
                    e.cash_stolen = true;
                }
                refresh_stats(f, e);
            }
            out.drained += hit.applied.drained;
            if let Some(id) = hit.applied.stolen_item {
                out.stolen.push(id);
            }
            out.cash += hit.applied.cash;
        }
        out.hits.push(hit);
    }
    // the drain pool goes to the actor (`CBattle+0x490c`)
    if out.drained > 0 {
        if let Some(Some(f)) = fighters.get_mut(actor) {
            let is_mp = recs.iter().any(|r| r.kind == crate::rules::modkind::MP_DRAIN);
            if is_mp {
                f.mp = (f.mp + out.drained).min(f.max_mp.max(f.mp));
            } else {
                f.hp = (f.hp + out.drained).min(f.max_hp);
            }
        }
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::rules::Lcg;

    fn disc() -> Option<crate::pkb_compat::PkbDisc> {
        let c = [
            std::env::var("SH2_DISC_DIR").ok(),
            Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string()),
        ];
        c.into_iter().flatten().find_map(|d| crate::pkb_compat::PkbDisc::open(d).ok())
    }

    fn fighter(hp: i32, max: i32) -> Fighter {
        crate::flow::Fighter {
            is_enemy: false,
            char_id: 0,
            name: String::new(),
            hp,
            max_hp: max,
            mp: 10,
            max_mp: 50,
            sp: 3,
            max_sp: 10,
            agl: 10,
            luc: 10,
            patk: 10,
            pdef: 10,
            satk: 10,
            sdef: 10,
            element: crate::rules::Element::NONE,
            variance: 1.0,
            status: vec![],
            passives: vec![],
            turn: Default::default(),
            sp_frac: 0,
            hits_per_attack: 1,
            exp: 0,
            cash: 0,
            drops: [crate::rules::DropSlot { item: -1, chance: 0, rare: false }; 2],
            mon_id: 0,
            turns_taken: 0,
            removed: false,
        }
    }

    #[test]
    fn decode_item_words() {
        // Medi-Leaf: +75 HP
        let r = decode_effect_words(&[0x1000_004b, !0, !0, !0], 10, 10, true);
        assert_eq!(r, vec![EffRec { kind: 3, percent: false, dur: 0, chance: 100, turns: 0, value: 75, element: 7, perm: true, src: 1, ..Default::default() }]);
        // Medi-Refine: set HP to 100 %
        let r = decode_effect_words(&[0x1c03_0064, !0, !0, !0], 10, 10, true);
        assert_eq!((r[0].kind, r[0].percent, r[0].dur, r[0].value), (6, true, 1, 100));
        // status cure all (word 0x26000000 + 0x64000000)
        let r = decode_effect_words(&[0x2600_0000, 0x6400_0000, !0, !0], 0, 0, true);
        assert_eq!((r[0].kind, r[0].dur, r[0].chance, r[0].all), (crate::rules::modkind::STATUS, 1, 100, 1));
        // magic-HP kind adds INT*2
        let r = decode_effect_words(&[0x1006_0032, !0, !0, !0], 20, 5, true);
        assert_eq!((r[0].kind, r[0].value), (9, 90));
    }

    #[test]
    fn apply_heal_set_and_revive() {
        let mut rng = Lcg(1);
        let mut f = fighter(10, 100);
        let a = apply_records(&decode_effect_words(&[0x1000_004b, !0, !0, !0], 0, 0, true), &mut f, &mut rng);
        assert_eq!((f.hp, a.hp), (85, 75));
        let a = apply_records(&decode_effect_words(&[0x1c03_0064, !0, !0, !0], 0, 0, true), &mut f, &mut rng);
        assert_eq!((f.hp, a.hp), (100, 15));
        // revive amulet: kind 0x2b + 20 % HP
        let mut dead = fighter(0, 100);
        let recs = decode_effect_words(&[0x1828_0064, 0x1803_0014, !0, !0], 0, 0, true);
        let a = apply_records(&recs, &mut dead, &mut rng);
        assert!(a.revived);
        assert!(dead.hp > 0);
    }

    #[test]
    fn real_tables() {
        let Some(d) = disc() else { return };
        let bd = BattleData::load(&d).unwrap();
        let t = ActionTables::load(&bd);
        assert!(t.items.len() >= 41 && t.items[0].battle_use);
        // Judgement Ring zones (live `01l` Cure one blue zone (60, 60, 15); Thera Leaf's strike area)
        if sh2_core::boot::is_retail() {
            assert_eq!(t.groups[11][0].ring_mod, Some((60, 60, 100, 15)));
            assert!(t.groups[11][0].ring_steps.is_empty());
            assert_eq!(t.magic[10].ring_steps, vec![(145, 50)]);
            assert_eq!(t.magic[10].ring_mod, Some((220, 110, 100, 11)));
            assert_eq!(t.items[0].ring_strike, Some((45, 120, 15)));
        }
        assert_eq!(t.items[0].effect_id, 3);
        assert!(!t.item_name(0).is_empty());
        // Medi-Leaf heals allies
        assert_eq!(t.items[0].target_class(), TargetClass::Ally { revive: false });
        // monster skills: skill 2 inflicts poison with a chance
        let r = decode_effect_words(&t.mon_skills[2].words, 0, 20, false);
        assert!(r.iter().any(|x| x.kind == crate::rules::modkind::STATUS), "{:?}", r);
        assert_eq!(t.mon_sets.len(), 3);
        // a damage skill decodes to kind 2 (magical)
        let r = decode_effect_words(&t.mon_skills[0].words, 0, 20, false);
        assert_eq!(r[0].kind, 2);
    }
}


/// One status slot as `EffectCheck` reads it (`aStatus[i]`: `bKind`, percent bit of `bFlags`, `nValue`).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct CheckStatus {
    pub kind: u8,
    pub percent: bool,
    pub value: i32,
}

/// `CBattle::EffectCheck` (JP 0x00650080): would the effect `recs` (decoded from a skill record) still do something to a unit with `hp` and `status`?
/// `false` as soon as one record is redundant (the same timed modifier of the same sign is already active, the unit is alive for a revive, nothing to cure for
/// "cure all", every requested status bit is already set).  Used by the AI condition 0x1b.
pub fn effect_check(recs: &[EffRec], hp: i32, status: &[CheckStatus]) -> bool {
    for r in recs {
        match r.kind {
            0xc | 0xd | 0xe | 0x13 | 0x14 | 0x17..=0x22 | 0x25..=0x28 | 0x30..=0x36 | 0x38..=0x3c => {
                if status.iter().any(|s| s.kind == r.kind && s.percent == r.percent && (s.value < 1 || r.value >= 0) && (s.value >= 0 || r.value < 1)) {
                    return false;
                }
            }
            0x23 => {
                if status.iter().any(|s| s.kind == r.kind && s.value == r.value) {
                    return false;
                }
            }
            0x29 | 0x2a => {
                if status.iter().any(|s| s.kind == r.kind && s.percent == r.percent) {
                    return false;
                }
            }
            0x2b => {
                if hp > 0 {
                    return false;
                }
            }
            crate::rules::modkind::REMOVE => {
                // retail `EffectCheck` 0x4e (JP 0x43): *Remove* needs a beneficial record to take away
                let n = status.iter().filter(|s| is_beneficial(&StatMod { kind: s.kind, percent: s.percent, value: s.value, ..Default::default() })).count();
                if n == 0 {
                    return false;
                }
            }
            crate::rules::modkind::STATUS | crate::rules::modkind::STATUS_AUX if r.dur == 0 => {
                let mut left = r.value as u32;
                for s in status.iter().filter(|s| s.kind == r.kind) {
                    left -= (s.value as u32) & left;
                }
                if left == 0 {
                    return false;
                }
            }
            _ => {}
        }
    }
    true
}

#[cfg(test)]
mod effect_check_tests {
    use super::*;

    fn rec(kind: u8, value: i32) -> EffRec {
        EffRec { kind, chance: 100, value, element: 7, ..Default::default() }
    }

    #[test]
    fn redundant_effects_are_rejected() {
        // revive on a living unit, cure-all with nothing to cure, a status that is already set
        assert!(!effect_check(&[rec(0x2b, 0)], 10, &[]));
        assert!(effect_check(&[rec(0x2b, 0)], 0, &[]));
        assert!(!effect_check(&[rec(crate::rules::modkind::REMOVE, 0)], 10, &[]));
        assert!(effect_check(&[rec(crate::rules::modkind::REMOVE, 0)], 10, &[CheckStatus { kind: 0x17, percent: false, value: 1 }]));
        assert!(!effect_check(&[rec(crate::rules::modkind::STATUS, 0x4)], 10, &[CheckStatus { kind: crate::rules::modkind::STATUS, percent: false, value: 0x6 }]));
        assert!(effect_check(&[rec(crate::rules::modkind::STATUS, 0x8)], 10, &[CheckStatus { kind: crate::rules::modkind::STATUS, percent: false, value: 0x6 }]));
        // an attack buff already active
        assert!(!effect_check(&[rec(0x17, 20)], 10, &[CheckStatus { kind: 0x17, percent: false, value: 10 }]));
        assert!(effect_check(&[rec(0x17, 20)], 10, &[CheckStatus { kind: 0x17, percent: false, value: -10 }]));
    }
}

/// Round 5 BP: the retail effect engine against the US tables (`SH2_US_DISC_DIR`; every test returns early without the disc).
#[cfg(test)]
mod bp_tests {
    use super::*;
    use crate::flow::{Command, Fighter};
    use crate::rules::{modkind as mk, status_bits as sb, Lcg};

    fn us() -> Option<(crate::data::BattleData, ActionTables)> {
        let dir = std::env::var_os("SH2_US_DISC_DIR")?;
        let d = crate::pkb_compat::PkbDisc::open(dir).ok()?;
        let data = crate::data::BattleData::load_us(&d).ok()?;
        let t = ActionTables::load(&data);
        Some((data, t))
    }

    fn unit(enemy: bool, hp: i32) -> Fighter {
        Fighter {
            is_enemy: enemy,
            char_id: if enemy { 0 } else { 0xb },
            name: String::new(),
            hp,
            max_hp: 200,
            mp: 40,
            max_mp: 60,
            sp: 8,
            max_sp: 10,
            agl: 10,
            luc: 10,
            patk: 30,
            pdef: 10,
            satk: 30,
            sdef: 10,
            element: crate::rules::Element::NONE,
            variance: 1.0,
            status: vec![],
            passives: vec![],
            turn: crate::rules::TurnSlot { interval: 10.0, timer: 5.0, ..Default::default() },
            sp_frac: 0,
            hits_per_attack: 2,
            exp: 0,
            cash: 0,
            drops: [crate::rules::DropSlot { item: -1, chance: 0, rare: false }; 2],
            mon_id: 0,
            turns_taken: 0,
            removed: false,
        }
    }

    /// Always-succeeding rolls (`rand() % 100 == 0`).
    struct Zero;
    impl Rng for Zero {
        fn rand(&mut self) -> i32 {
            0
        }
    }

    #[test]
    fn retail_words_decode_to_retail_kinds() {
        // Rage (MAGI 8): 0x42990b1e = kind 0x17 (PATK), +30 %, 5 turns, chance 100
        let r = decode_effect_words(&[0x4299_0b1e, !0, !0, !0], 0, 0, true);
        assert_eq!((r[0].kind, r[0].percent, r[0].value, r[0].turns, r[0].chance), (0x17, true, 30, 5, 100));
        // Heal (MAGI 6): cure every status bit (`'T'` type 1, all) and every aux bit
        let r = decode_effect_words(&[0x2600_0000, 0x6400_0000, 0x3700_0000, 0x6400_0000], 0, 0, true);
        assert_eq!((r[0].kind, r[0].dur, r[0].all), (mk::STATUS, 1, 1));
        assert_eq!((r[1].kind, r[1].dur, r[1].all), (mk::STATUS_AUX, 1, 3));
        // Entrance (MAGI 32): 0x59b9207d = kind 0x50 (magic charge) +125 %
        let r = decode_effect_words(&[0x59b9_207d, !0, !0, !0], 0, 0, true);
        assert_eq!((r[0].kind, r[0].value, r[0].percent), (mk::SATK_CHARGE, 125, true));
        // Gale (MAGI 16): delay -25 % then turn interval -25 % for 5 turns
        let r = decode_effect_words(&[0x5279_3fe7, 0x4319_0be7, !0, !0], 0, 0, true);
        assert_eq!((r[0].kind, r[0].value, r[0].percent), (0x16, -25, true));
        assert_eq!((r[1].kind, r[1].value, r[1].turns), (0x1b, -25, 5));
    }

    #[test]
    fn statuses_follow_the_retail_rules() {
        let mut rng = Zero;
        let mut f = unit(false, 100);
        let poison = EffRec { kind: mk::STATUS, chance: 100, turns: 3, value: 1, ..Default::default() };
        let a = effect_code(&[poison], &mut f, &EcEnv::default(), &mut rng);
        assert_eq!(a.status_added, sb::POISON);
        // poison on poison becomes Deadly Poison (one record, bit 2)
        let a = effect_code(&[poison], &mut f, &EcEnv::default(), &mut rng);
        assert_eq!(a.status_added, sb::D_POISON);
        assert_eq!(crate::rules::status_of(&f.status), sb::D_POISON);
        // the duration is the record's + 1 (`(+6 & 0x3f) + 1`)
        assert_eq!(f.status.iter().find(|m| m.kind == mk::STATUS).unwrap().turns, 4);
        // a 100 % protection (accessory, duration type 2) stops Seal
        f.passives.push(StatMod { turns: 0, chance: 100, percent: false, kind: mk::STATUS_PROTECT, value: sb::SEAL as i32 });
        let seal = EffRec { kind: mk::STATUS, chance: 100, value: sb::SEAL as i32, ..Default::default() };
        let mut rng2 = Lcg(7);
        let a = effect_code(&[seal], &mut f, &EcEnv::default(), &mut rng2);
        assert_eq!((a.status_added, a.blocked), (0, sb::SEAL));
        // ... unless the word is unresistable
        let a = effect_code(&[EffRec { perm: true, ..seal }], &mut f, &EcEnv::default(), &mut rng2);
        assert_eq!(a.status_added, sb::SEAL);
        // cure all
        let cure = EffRec { kind: mk::STATUS, dur: 1, chance: 100, all: 1, ..Default::default() };
        let a = effect_code(&[cure], &mut f, &EcEnv::default(), &mut rng);
        assert_eq!(a.status_cured, sb::D_POISON | sb::SEAL);
        assert_eq!(crate::rules::status_of(&f.status), 0);
        // a monster immune to Poison (`MONSTERParam+0x34` bit 0) never gets it
        let mut m = unit(true, 100);
        let env = EcEnv { immune: monster_immunity(0, 0, 1), ..Default::default() };
        let a = effect_code(&[poison], &mut m, &env, &mut rng2);
        assert_eq!((a.status_added, a.blocked), (0, sb::POISON));
        // instant death and petrify take the unit out
        let a = effect_code(&[EffRec { value: sb::DEATH as i32, ..poison }], &mut m, &EcEnv::default(), &mut rng);
        assert!(a.fell && m.hp == 0);
        let mut p = unit(false, 50);
        let a = effect_code(&[EffRec { value: sb::PETRIFY as i32, ..poison }], &mut p, &EcEnv::default(), &mut rng);
        assert!(a.fell && crate::rules::status_of(&p.status) == sb::PETRIFY);
    }

    #[test]
    fn timed_modifiers_refresh_like_the_original() {
        let mut rng = Zero;
        let mut f = unit(false, 100);
        let rage = decode_effect_words(&[0x4299_0b1e, !0, !0, !0], 0, 0, true);
        effect_code(&rage, &mut f, &EcEnv { power: 120, ..Default::default() }, &mut rng);
        // value scaled by the power (ring grade 1.2): (120 * 30 + 50) / 100 = 36, 6 turns
        let m = f.status.iter().find(|m| m.kind == 0x17).copied().unwrap();
        assert_eq!((m.value, m.turns, m.percent), (36, 6, true));
        // the same buff again: one record, the value replaced, the duration kept
        effect_code(&rage, &mut f, &EcEnv::default(), &mut rng);
        assert_eq!(f.status.iter().filter(|m| m.kind == 0x17).count(), 1);
        assert_eq!(f.status.iter().find(|m| m.kind == 0x17).unwrap().value, 30);
        // a debuff of the same kind is a separate record (the sign differs); a monster immune to PATK down rejects it
        let down = EffRec { kind: 0x17, percent: true, chance: 100, turns: 5, value: -30, ..Default::default() };
        effect_code(&[down], &mut f, &EcEnv::default(), &mut rng);
        assert_eq!(f.status.iter().filter(|m| m.kind == 0x17).count(), 2);
        let mut m = unit(true, 100);
        let a = effect_code(&[down], &mut m, &EcEnv { immune: monster_immunity(0x10, 0, 0), ..Default::default() }, &mut rng);
        assert!(a.failed && a.blocked == 0x800 && m.status.is_empty());
        // Gale's delay on a monster: -25 % of the interval now
        let gale = decode_effect_words(&[0x5279_3fe7, 0x4319_0be7, !0, !0], 0, 0, true);
        let mut e = unit(true, 100);
        effect_code(&gale, &mut e, &EcEnv::default(), &mut rng);
        assert!((e.turn.timer - 2.5).abs() < 1e-4, "{}", e.turn.timer);
    }

    #[test]
    fn revive_heal_drain_and_cut() {
        let mut rng = Zero;
        // Raise Up (MAGI 4): revive + 20 % HP + 50 % SP
        let raise = decode_effect_words(&[0x1828_0064, 0x1803_0014, 0x1805_0032, !0], 0, 0, true);
        let mut dead = unit(false, 0);
        dead.sp = 0;
        let a = effect_code(&raise, &mut dead, &EcEnv::default(), &mut rng);
        assert!(a.revived);
        assert_eq!(dead.hp, 1 + 40);
        assert_eq!(dead.sp, 5);
        // a heal on a living unit does nothing to the revive record
        let mut alive = unit(false, 150);
        let a = effect_code(&raise, &mut alive, &EcEnv::default(), &mut rng);
        assert!(!a.revived && alive.hp == 190);
        // HP drain `'?'` 10 % of the max HP of a monster
        let mut m = unit(true, 100);
        let a = effect_code(&[EffRec { kind: mk::HP_DRAIN, percent: true, chance: 100, value: 10, ..Default::default() }], &mut m, &EcEnv::default(), &mut rng);
        assert_eq!((a.drained, m.hp), (20, 80));
        // `0x46` "HP down to the value": 1 HP left
        let a = effect_code(&[EffRec { kind: 0x46, chance: 100, value: 1, ..Default::default() }], &mut m, &EcEnv::default(), &mut rng);
        assert_eq!((m.hp, a.hp), (1, -79));
    }

    #[test]
    fn us_spells_resolve_with_targets_costs_and_damage() {
        let Some((_data, t)) = us() else { return };
        let mut fighters: Vec<Option<Fighter>> = vec![Some(unit(false, 60)), Some(unit(false, 100)), Some(unit(true, 300)), Some(unit(true, 300))];
        fighters.resize(12, None);
        let mut ext = vec![FighterExt { radius: 3.0, ..Default::default() }; 12];
        ext[0].pc = 0xb;
        ext[1].pc = 5;
        // Nicolai knows Cure through no crest: the plain MP cost
        let learned = |_: usize, _: usize| true;
        let fr = |_: usize, _: usize| 0;
        let pos = [[0.0, 0.0, 0.0]; 12];
        let ctx = ResolveCtx { tables: &t, pos: &pos, radius: &[], gm: GlobalMod::default(), ring: 1.0, combo: &[], friendship: &fr, party_cash: 0, fused: None, learned: &learned, turn_no: 0 };
        let mut rng = Lcg(3);
        // Arc Cure (MAGI 1): area 5 = every living ally, 16 MP, heals 50 + INT * 2 (INT = SATK / 2 without raw stats)
        let cmd = Command { p44: 1, p48: 0, p4c: 1, ..Default::default() };
        let r = resolve_action(&ctx, 0, &cmd, &mut fighters, &mut ext, &mut rng);
        assert_eq!(r.mp_cost, 16);
        assert_eq!(r.hits.len(), 2, "{:?}", r.hits);
        assert_eq!(fighters[0].as_ref().unwrap().hp, 60 + 50 + 30);
        assert_eq!(fighters[1].as_ref().unwrap().hp, 180);
        assert!((r.turn_factor - 1.0).abs() < 1e-6, "Arc Cure +0x1a = 300 = an attack's 3.0");
        // Rock Rot (MAGI 34): magical earth damage on one enemy (area 1/0 but no positions given -> only the chosen target is inside 19 units? all at 0,0: both)
        let cmd = Command { p44: 34, p48: 2, p4c: 1, ..Default::default() };
        let before = fighters[2].as_ref().unwrap().hp;
        let r = resolve_action(&ctx, 0, &cmd, &mut fighters, &mut ext, &mut rng);
        assert!(r.record.as_ref().unwrap().magical());
        assert_eq!(r.record.as_ref().unwrap().element(), 0);
        assert!(r.hits.iter().all(|h| h.damage > 0), "{:?}", r.hits);
        assert!(fighters[2].as_ref().unwrap().hp < before);
        // a Resist stance halves the damage, Block quarters it
        ext[3].guard = Guard::Block;
        let r = resolve_action(&ctx, 0, &Command { p44: 34, p48: 3, p4c: 1, ..Default::default() }, &mut fighters, &mut ext, &mut rng);
        let h = r.hits.iter().find(|h| h.target == 3).unwrap();
        assert_eq!(h.guard, 1);
    }

    /// Live US check (2026-10-14, first fight, Nicolai INT 9, max HP forced to 999 at 10 HP): Cure (White Magic, `SKIL` group 11 record 0)
    /// with a "Good" ring (grade 1) healed exactly **68** = 50 + 2 * INT -- the effect power is the ring grade, not `rec+0x1a`.
    #[test]
    fn cure_heals_like_the_live_game() {
        let Some((_data, t)) = us() else { return };
        let mut n = unit(false, 10);
        n.max_hp = 999;
        n.char_id = 0xb;
        let mut fighters: Vec<Option<Fighter>> = vec![Some(n), Some(unit(true, 50))];
        fighters.resize(12, None);
        let mut ext = vec![FighterExt::default(); 12];
        ext[0].pc = 0xb;
        ext[0].raw = Some(RawStats { int: 9, max_hp: 999, max_mp: 60, max_sp: 10, ..Default::default() });
        let learned = |_: usize, _: usize| true;
        let fr = |_: usize, _: usize| 0;
        let ctx = ResolveCtx { tables: &t, pos: &[], radius: &[], gm: GlobalMod::default(), ring: 1.0, combo: &[], friendship: &fr, party_cash: 0, fused: None, learned: &learned, turn_no: 0 };
        let r = resolve_action(&ctx, 0, &Command { p44: 0, p48: 0, p4c: 2, ..Default::default() }, &mut fighters, &mut ext, &mut Lcg(1));
        assert_eq!(r.hits[0].applied.hp, 68);
        assert_eq!(r.mp_cost, 6);
    }

    #[test]
    fn target_list_shapes() {
        let mut fighters: Vec<Option<Fighter>> = (0..5).map(|i| Some(unit(i >= 2, 50))).collect();
        fighters.resize(12, None);
        let mut pos = vec![[0.0f32; 3]; 12];
        pos[0] = [0.0, 0.0, -30.0];
        pos[1] = [10.0, 0.0, -30.0];
        pos[2] = [0.0, 0.0, 20.0];
        pos[3] = [15.0, 0.0, 20.0];
        pos[4] = [60.0, 0.0, 20.0];
        let rad = vec![3.0f32; 12];
        // circle size 0 (19 + radius) around enemy 2: enemy 3 (15 away) in, enemy 4 (60 away) out
        assert_eq!(target_list(&fighters, &pos, &rad, 0, 2, 2, 1, 0, false, false), vec![2, 3]);
        // every enemy
        assert_eq!(target_list(&fighters, &pos, &rad, 0, 2, 2, 5, 0, false, false), vec![2, 3, 4]);
        // every ally (class 1) from the party side
        assert_eq!(target_list(&fighters, &pos, &rad, 0, 1, 1, 5, 0, false, false), vec![1, 0]);
        // self only (class 0)
        assert_eq!(target_list(&fighters, &pos, &rad, 1, 3, 0, 0, 0, false, false), vec![1]);
        // a line from the caster through enemy 2 (width 6.5 + radius): enemy 3 is 15 to the side -> out
        assert_eq!(target_list(&fighters, &pos, &rad, 0, 2, 2, 3, 0, false, false), vec![2]);
        // revive items list fallen allies only
        fighters[1].as_mut().unwrap().hp = 0;
        assert_eq!(target_list(&fighters, &pos, &rad, 0, 1, 1, 5, 0, true, false), vec![1]);
    }

    #[test]
    fn pc_stats_match_the_live_first_encounter() {
        // Live slot-8 capture (notes/integration/pine_us_refinement.md 9.1): Karin STR / VIT / INT / POW 6, weapon 0x22, armour 1 ->
        // PATK 17, SATK 15, PDEF 16, SDEF 14
        let Some((data, _t)) = us() else { return };
        let mut raw = [0u8; sh2_menu::save::PC_REC_SIZE];
        raw[0] = 3;
        let mut rec = sh2_menu::save::PcRec::parse(&raw);
        rec.hp_max = 25;
        rec.mp_max = 15;
        rec.sp_max = 4;
        rec.str_ = 6;
        rec.vit = 6;
        rec.int = 6;
        rec.pow = 6;
        rec.agl = 7;
        rec.luc = 4;
        rec.weapon = 0x22;
        rec.armor = 1;
        rec.accessories = [-1; 3];
        let st = pc_stats(&data, &rec, 5, None);
        let mut f = unit(false, 25);
        let mut ext = FighterExt::default();
        apply_pc_stats(&mut f, &mut ext, &st);
        assert_eq!((f.patk, f.satk, f.pdef, f.sdef, f.max_hp, f.agl, f.luc), (17, 15, 16, 14, 25, 7, 4));
    }
}

/// Round 5 BP: every party-side record of the US tables (PC skill groups, fusion skills, crest magic, battle items, combo magic) goes through
/// the engine and does something (damage, a change, or the "no effect" of a redundant record).  Prints the records that do nothing.
#[cfg(test)]
mod bp_coverage {
    use super::*;
    use crate::flow::{Command, Fighter};

    fn unit(enemy: bool) -> Fighter {
        Fighter {
            is_enemy: enemy,
            char_id: if enemy { 0 } else { 0 },
            name: String::new(),
            hp: 100,
            max_hp: 300,
            mp: 200,
            max_mp: 300,
            sp: 5,
            max_sp: 20,
            agl: 20,
            luc: 20,
            patk: 80,
            pdef: 10,
            satk: 80,
            sdef: 10,
            element: crate::rules::Element::NONE,
            variance: 1.0,
            status: vec![StatMod { turns: 3, chance: 100, percent: false, kind: crate::rules::modkind::STATUS, value: 1 }],
            passives: vec![],
            turn: crate::rules::TurnSlot { interval: 10.0, timer: 5.0, ..Default::default() },
            sp_frac: 0,
            hits_per_attack: 1,
            exp: 0,
            cash: 0,
            drops: [crate::rules::DropSlot { item: -1, chance: 0, rare: false }; 2],
            mon_id: 0,
            turns_taken: 0,
            removed: false,
        }
    }

    #[test]
    fn every_party_record_resolves() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = crate::pkb_compat::PkbDisc::open(dir) else { return };
        let data = crate::data::BattleData::load_us(&d).unwrap();
        let t = ActionTables::load(&data);
        let mut cases: Vec<(String, Command, i32)> = vec![];
        for g in 0..t.groups.len().min(24) {
            for (i, r) in t.groups[g].iter().enumerate() {
                if r.empty || !r.battle_use {
                    continue;
                }
                let fused = if g >= 14 { Some((0..0x17).find(|&f| ActionTables::fusion_group(f) == g).unwrap_or(0) as i32) } else { None };
                cases.push((format!("skil g{g} #{i} {}", t.skill_name(r.name_idx.max(0) as usize)), Command { p44: i as i32, p4c: 2, p50: g as i32, ..Default::default() }, fused.unwrap_or(-1)));
            }
        }
        for (i, r) in t.magic.iter().enumerate() {
            if !r.empty {
                cases.push((format!("magi {} {}", i, t.magic_name(i)), Command { p44: i as i32, p4c: 1, ..Default::default() }, -1));
            }
        }
        for (i, r) in t.items.iter().enumerate() {
            if r.battle_use && !t.item_name(i).is_empty() {
                cases.push((format!("item {} {}", i, t.item_name(i)), Command { p44: i as i32, p4c: 0, ..Default::default() }, -1));
            }
        }
        for i in 0..t.combos.len() {
            cases.push((format!("comb {} {}", i, t.combo_names.get(i).cloned().unwrap_or_default()), Command { p44: i as i32, p4c: 4, ..Default::default() }, -1));
        }
        let mut idle = vec![];
        let learned = |_: usize, _: usize| true;
        let fr = |_: usize, _: usize| 5000;
        let pos = [[0.0f32; 3]; 12];
        for (name, mut cmd, fused) in cases.clone() {
            let mut fighters: Vec<Option<Fighter>> = vec![Some(unit(false)), Some(unit(false)), Some(unit(true)), Some(unit(true))];
            fighters[1].as_mut().unwrap().hp = 0; // a fallen ally for the revive records
            fighters.resize(12, None);
            if cmd.p4c == 2 && fused < 0 {
                fighters[0].as_mut().unwrap().char_id = cmd.p50;
            }
            let mut ext = vec![FighterExt { radius: 3.0, pc: 0, ..Default::default() }; 12];
            ext[2] = FighterExt { radius: 3.0, pc: -1, drops: [0, 1], mon_cash: 100, ..Default::default() };
            ext[3] = ext[2].clone();
            let rec = action_record(&t, &cmd, fighters[0].as_ref().unwrap(), if fused >= 0 { Some(fused) } else { None }).expect(&name);
            cmd.p48 = match rec.side_class() {
                0 => 0,
                1 if rec.revive => 1,
                1 => 0,
                _ if rec.target_class() == crate::ai::TargetClass::Opponent || rec.target_class() == crate::ai::TargetClass::OpponentsAlive => 2,
                _ => 2,
            };
            let ctx = ResolveCtx { tables: &t, pos: &pos, radius: &[], gm: GlobalMod::default(), ring: 1.0, combo: &[0, 1], friendship: &fr, party_cash: 1000, fused: if fused >= 0 { Some(fused) } else { None }, learned: &learned, turn_no: 0 };
            let mut rng = crate::rules::Lcg(9);
            let r = resolve_action(&ctx, 0, &cmd, &mut fighters, &mut ext, &mut rng);
            let did = r.hits.iter().any(|h| h.damage != 0 || h.applied != Applied::default());
            if !did {
                idle.push(name);
            }
        }
        eprintln!("bp_coverage: {} records, {} without an effect:\n  {}", cases.len(), idle.len(), idle.join("\n  "));
        assert!(idle.len() * 10 < cases.len(), "too many records without an effect");
    }
}
