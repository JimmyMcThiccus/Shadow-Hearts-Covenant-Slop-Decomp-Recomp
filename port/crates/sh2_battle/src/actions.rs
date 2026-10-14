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

/// One decoded effect record (the 12 byte `EFFTBL` entries).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct EffRec {
    pub kind: u8,
    pub percent: bool,
    /// `(flags & 0x1f) >> 2`: 0 add / inflict, 1 set / cure, 2 permanent
    pub dur: u8,
    pub chance: u8,
    pub turns: u8,
    pub value: i32,
    /// damage skills (kind 1/2): element 0..5 (7 = own)
    pub element: u8,
}

/// `SpecialEffectCode` for `words` (caster INT / SATK passed in for the kind 9/10/0xb bonuses).
pub fn decode_effect_words(words: &[u32; 4], int_stat: i32, satk: i32, is_pc: bool) -> Vec<EffRec> {
    let mut out = Vec::new();
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
                out.push(EffRec {
                    kind: if b3 & 8 != 0 { 2 } else { 1 },
                    percent: (w >> 23) & 1 != 0,
                    dur: if (b3 & 7) < 7 { 0 } else { 0 },
                    chance: 100,
                    turns: 0,
                    value: (w & 0xffff) as u16 as i16 as i32,
                    element: b3 & 7,
                });
                i += 1;
            }
            0x10..=0x1f => {
                let kind = ((w >> 16) & 0xff) as u8 + 3;
                let mut value = (w & 0xffff) as u16 as i16 as i32;
                if kind == 9 || kind == 10 {
                    value += if is_pc { int_stat * 2 } else { satk };
                } else if kind == 0xb && is_pc {
                    value += int_stat / 10;
                }
                out.push(EffRec { kind, percent: b3 & 0x08 != 0, dur: (b3 >> 2) & 1, chance: 100, turns: 0, value, element: 7 });
                i += 1;
            }
            0x20..=0x2f => {
                let w2 = words[(i + 1).min(3)];
                let value = ((w << 8) as i32) >> 8;
                let turns = ((w2 >> 16) & 0xff) as u8;
                let chance = ((w2 >> 24) & 0x7f) as u8;
                out.push(EffRec { kind: 0x47, percent: false, dur: (b3 >> 2) & 3, chance, turns, value, element: 7 });
                if w & 0x80_0000 != 0 {
                    out.push(EffRec { kind: 0x48, percent: false, dur: (b3 >> 2) & 3, chance, turns, value: 0, element: 7 });
                }
                i += 2;
            }
            0x30..=0x3f => {
                let w2 = words[(i + 1).min(3)];
                let value = ((w << 8) as i32) >> 8;
                out.push(EffRec { kind: 0x48, percent: false, dur: (b3 >> 2) & 3, chance: ((w2 >> 24) & 0x7f) as u8, turns: ((w2 >> 16) & 0xff) as u8, value, element: 7 });
                i += 2;
            }
            0x40..=0x4f => {
                let kind = (((w >> 21) & 0x7f) as u8) + 3;
                out.push(EffRec { kind, percent: (w >> 8) & 1 != 0, dur: 0, chance: (((w << 11) >> 25) & 0x7f) as u8, turns: ((w >> 9) & 0x1f) as u8, value: (w & 0xff) as u8 as i8 as i32, element: 7 });
                i += 1;
            }
            0x50..=0x5f => {
                let kind = (((w >> 21) & 0x7f) as u8) + 3;
                let raw = (w & 0x1fff) as i32;
                let value = if raw < 0x1000 { raw } else { raw - 0x2000 };
                out.push(EffRec { kind, percent: (w >> 9) & 1 != 0, dur: 0, chance: (((w << 11) >> 25) & 0x7f) as u8, turns: 0, value, element: 7 });
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
}

impl ActionRec {
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
        if let Some(&(off, cnt)) = groups.get(0x16) {
            for i in 0..cnt as usize {
                let o = off as usize + i * 0x28;
                let mut set = [-1i16; 20];
                for k in 0..20 {
                    set[k] = i16at(ssec, o + k * 2);
                }
                t.mon_sets.push(set);
            }
        }
        if let Some(&(off, cnt)) = groups.get(0x17) {
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
            t.snap_label = us.text(0xf, 0, -1).unwrap_or_default();
            t.tarot_names = (0..22).map(|i| us.text(0xe, i, -1).unwrap_or_default()).collect();
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
}

/// Apply decoded records to `target` (`EffectCodeFunc` for the supported kinds).
pub fn apply_records(recs: &[EffRec], target: &mut Fighter, rng: &mut dyn Rng) -> Applied {
    let mut a = Applied::default();
    let revive = recs.iter().any(|r| r.kind == 0x2b);
    if revive && target.hp <= 0 {
        target.hp = 0;
        target.removed = false;
        a.revived = true;
        // death status goes away
        target.status.retain(|m| !(m.kind == crate::rules::modkind::STATUS && (m.value as u32 & 0xa0) != 0));
    }
    for r in recs {
        match r.kind {
            3 | 6 | 9 => {
                if target.hp <= 0 && !a.revived {
                    continue;
                }
                let max = target.max_hp;
                let amount = scaled(r, max);
                let new = if r.dur != 0 { amount.clamp(0, max) } else { (target.hp + amount).clamp(if a.revived && amount <= 0 { 1 } else { 0 }, max) };
                a.hp += new - target.hp;
                target.hp = new;
            }
            4 | 7 | 10 => {
                let max = max_mp(target);
                let amount = scaled(r, max);
                let new = if r.dur != 0 { amount.clamp(0, max) } else { (target.mp + amount).clamp(0, max) };
                a.mp += new - target.mp;
                target.mp = new;
            }
            5 | 8 | 11 => {
                if target.max_sp <= 0 {
                    continue;
                }
                let amount = scaled(r, target.max_sp);
                let new = if r.dur != 0 { amount.clamp(0, target.max_sp) } else { (target.sp + amount).clamp(0, target.max_sp) };
                a.sp += new - target.sp;
                target.sp = new;
            }
            0x2b => {
                if a.revived && !recs.iter().any(|x| matches!(x.kind, 3 | 6 | 9)) {
                    target.hp = 1.max(target.hp);
                    a.hp += target.hp;
                }
            }
            0x47 => {
                let bits = r.value as u32 & 0x7f_ffff;
                if r.dur == 1 {
                    // cure
                    let mask = if bits == 0 { 0x7f_ffff & !0x80 } else { bits };
                    for m in target.status.iter_mut().filter(|m| m.kind == crate::rules::modkind::STATUS) {
                        let had = m.value as u32 & mask;
                        a.status_cured |= had;
                        m.value &= !(mask as i32);
                    }
                    target.status.retain(|m| !(m.kind == crate::rules::modkind::STATUS && m.value == 0));
                } else if bits != 0 && (rng.rand() % 100) as u8 <= r.chance.max(1) {
                    a.status_added |= bits;
                    target.status.push(StatMod { turns: r.turns, chance: r.chance, percent: false, kind: crate::rules::modkind::STATUS, value: bits as i32 });
                    if bits & 0x80 != 0 {
                        target.hp = 0;
                    }
                }
            }
            0x0c..=0x14 | 0x17..=0x22 => {
                // timed stat modifiers
                if r.turns > 0 || r.dur == 0 {
                    target.status.push(StatMod { turns: r.turns.max(1), chance: 100, percent: r.percent, kind: r.kind, value: r.value });
                    a.buffs.push(r.kind);
                }
            }
            _ => {}
        }
    }
    a
}

fn max_mp(f: &Fighter) -> i32 {
    f.max_mp.max(f.mp)
}

fn scaled(r: &EffRec, max: i32) -> i32 {
    let mut amount = if r.percent {
        if r.value > 0 {
            (max * r.value + 50) / 100
        } else if r.value < 0 {
            (max * r.value - 50) / 100
        } else {
            0
        }
    } else {
        r.value
    };
    if amount == 0 && r.value > 0 {
        amount = 1;
    } else if amount == 0 && r.value < 0 {
        amount = -1;
    }
    amount
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
        assert_eq!(r, vec![EffRec { kind: 3, percent: false, dur: 0, chance: 100, turns: 0, value: 75, element: 7 }]);
        // Medi-Refine: set HP to 100 %
        let r = decode_effect_words(&[0x1c03_0064, !0, !0, !0], 10, 10, true);
        assert_eq!((r[0].kind, r[0].percent, r[0].dur, r[0].value), (6, true, 1, 100));
        // status cure all (word 0x26000000 + 0x64000000)
        let r = decode_effect_words(&[0x2600_0000, 0x6400_0000, !0, !0], 0, 0, true);
        assert_eq!((r[0].kind, r[0].dur, r[0].chance), (0x47, 1, 100));
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
        assert!(r.iter().any(|x| x.kind == 0x47), "{:?}", r);
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
            0x43 => {
                let mut n = 0;
                for s in status {
                    let pos = s.value > 0;
                    match s.kind {
                        0x48 if s.value & 0x1f800 != 0 => n += 1,
                        0x47 => {}
                        0x45 | 0x44 | 0x37 | 0x2a | 0x29 | 0x23 => n += 1,
                        0x3a => {
                            if (s.percent && s.value < 100) || (!s.percent && s.value < 0) {
                                n += 1;
                            }
                        }
                        0x36 if s.value > 0x78 => n += 1,
                        0x34 if s.value < 1 => n += 1,
                        0x38 | 0x33 | 0x22 | 0x21 | 0x1e | 0x1d | 0x1b if s.value < 0 => n += 1,
                        0x3e | 0x3c | 0x35 | 0x20 | 0x1f => {
                            if (s.percent && s.value > 100) || (!s.percent && s.value > 0) {
                                n += 1;
                            }
                        }
                        0x39 | 0x32 | 0x28 | 0x27 | 0x26 | 0x25 | 0x1c | 0x31 | 0x30 | 0x1a | 0x18 | 0x19 | 0x17 | 0x14 | 0x13 | 0xe | 0xd | 0xc if pos => n += 1,
                        _ => {}
                    }
                }
                if n == 0 {
                    return false;
                }
            }
            0x47 | 0x48 => {
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
        EffRec { kind, percent: false, dur: 0, chance: 100, turns: 0, value, element: 7 }
    }

    #[test]
    fn redundant_effects_are_rejected() {
        // revive on a living unit, cure-all with nothing to cure, a status that is already set
        assert!(!effect_check(&[rec(0x2b, 0)], 10, &[]));
        assert!(effect_check(&[rec(0x2b, 0)], 0, &[]));
        assert!(!effect_check(&[rec(0x43, 0)], 10, &[]));
        assert!(effect_check(&[rec(0x43, 0)], 10, &[CheckStatus { kind: 0x45, percent: false, value: 1 }]));
        assert!(!effect_check(&[rec(0x47, 0x4)], 10, &[CheckStatus { kind: 0x47, percent: false, value: 0x6 }]));
        assert!(effect_check(&[rec(0x47, 0x8)], 10, &[CheckStatus { kind: 0x47, percent: false, value: 0x6 }]));
        // an attack buff already active
        assert!(!effect_check(&[rec(0x17, 20)], 10, &[CheckStatus { kind: 0x17, percent: false, value: 10 }]));
        assert!(effect_check(&[rec(0x17, 20)], 10, &[CheckStatus { kind: 0x17, percent: false, value: -10 }]));
    }
}
