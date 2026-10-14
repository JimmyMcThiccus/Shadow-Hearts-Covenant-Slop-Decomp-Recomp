//! Judgement-Ring customisation: the party-record fields the `CmdRingCustom` page edits and the battle ring consumes.
//!
//! Recovered from `CmdPC::CustomJudgmentRing` (JP 0x0043c1b0), `CmdPC::CreateJudgmentRing` (0x0043bfe0), `CmdPC::GetExpansionRingItem`,
//! `CmdParty::GetRestRingItem` (0x0043d440), `CmdRingCustomHitArea::Custom` (0x0046c390), `CmdRingCustomAutoRing::Select`
//! (0x004a00d0) and the retail `PCInit` / `AddEquip`.  Fields of the 0xc0 byte party record (`BTL0`; the **retail record has four more bytes
//! at `+0x58`**, so every offset below is `+ 4` there, confirmed by the live save: Karin `+0x5c = 0x12`, `+0x68 = 0xff`):
//!
//! | demo | retail | meaning |
//! |---|---|---|
//! | `+0x58` bits 0-2 | `+0x5c` | base hit count (`PC_I[0x15] & 7`) |
//! | `+0x58` bits 3-5 | `+0x5c` | **chosen hit count** (areas of the attack ring; `GetExpansionRingItem` = chosen - base) |
//! | `+0x58` bits 6-7 | `+0x5c` | ring type (0 normal, 1 practice, 2 technical, 3 gamble) written into `JRing+0x41 bits 2-3` |
//! | `+0x59` bit 0 | `+0x5d` | auto ring (`CreateJudgmentRing`: one area, ring type 1) |
//! | `+0x5a..0x5f` | `+0x5e..0x63` | per hit: **zone expansion points** (each point widens the hit area by 2 degrees) |
//! | `+0x5f..0x64` | `+0x63..0x68` | per hit: **strike expansion points** (1 degree each) |
//! | `+0x64` | `+0x68` | ring item assigned to the character (-1 = none) |
//!
//! The points are paid from the party's stock of ring items: the key-item array of the active bag (`BTL0` bag `+0x174`, retail
//! `0xc30 + bag * 0x200`; slot 0 = extra hits, 1 = zone expansion items, 2 = strike expansion items, 3.. = ring-type items), the rest being
//! `stock - points placed on every party member` (`GetRestRingItem`).
//!
//! # Battle hook
//!
//! `sh2_battle` builds the attack ring from the `PC_J` areas of the character's hit count.  The customised ring is
//! [`battle_ring`]`(session, pc, weapon_ring_bytes)`: it returns the hit count to use (`CreateJudgmentRing`), the ring type, and the
//! 20 byte `JRCUSTOM` table for `JRing::custom_data` (`sh2_gfx::effects::jring::JrCustom { raw }` + `custom_convert`), where
//! `weapon_ring_bytes` = bytes `0x28..0x32` of the equipped weapon's `WPN_` record (the weapon's own narrowing per area).  See
//! `notes/integration/requests.md`.

use crate::session::GameSession;

/// Offsets inside the 0xc0 party record (demo; retail adds [`RETAIL_SHIFT`]).
pub const OFF_BITS: usize = 0x58;
pub const OFF_AUTO: usize = 0x59;
pub const OFF_ZONE: usize = 0x5a;
pub const OFF_STRIKE: usize = 0x5f;
pub const OFF_ITEM: usize = 0x64;
pub const RETAIL_SHIFT: usize = 4;
/// offset of the weapon's per-area narrowing bytes inside a `WPN_` record
pub const WEAPON_RING_OFF: usize = 0x28;
pub const WEAPON_RING_LEN: usize = 10;
/// most expansion points one area can take in the menu (the original is limited by `JRCustomCheck`: areas keep 5 degrees of gap)
pub const MAX_POINTS: u8 = 8;

/// Key-item slots of the ring stock.
pub const STOCK_HITS: usize = 0;
pub const STOCK_ZONE: usize = 1;
pub const STOCK_STRIKE: usize = 2;

fn shift(retail: bool) -> usize {
    if retail { RETAIL_SHIFT } else { 0 }
}

/// The customisation of one party member.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct RingState {
    /// bits 0-2: hits the character has by nature
    pub base_hits: u8,
    /// bits 3-5: hits of the attack ring (1..=5)
    pub hits: u8,
    /// bits 6-7
    pub ring_type: u8,
    pub auto: bool,
    pub zone: [u8; 5],
    pub strike: [u8; 5],
    /// assigned ring item (-1 none)
    pub item: i8,
}

impl Default for RingState {
    fn default() -> Self {
        RingState { base_hits: 2, hits: 2, ring_type: 0, auto: false, zone: [0; 5], strike: [0; 5], item: -1 }
    }
}

impl RingState {
    /// Decode from a party record (`retail` selects the +4 layout).
    pub fn from_record(rec: &[u8], retail: bool) -> RingState {
        let s = shift(retail);
        let Some(&b) = rec.get(OFF_BITS + s) else { return RingState::default() };
        let mut z = [0u8; 5];
        let mut k = [0u8; 5];
        for i in 0..5 {
            z[i] = rec.get(OFF_ZONE + s + i).copied().unwrap_or(0);
            k[i] = rec.get(OFF_STRIKE + s + i).copied().unwrap_or(0);
        }
        let hits = (b >> 3) & 7;
        RingState {
            base_hits: b & 7,
            hits: if (1..=5).contains(&hits) { hits } else { 2 },
            ring_type: b >> 6,
            auto: rec.get(OFF_AUTO + s).map(|v| v & 1 != 0).unwrap_or(false),
            zone: z,
            strike: k,
            item: rec.get(OFF_ITEM + s).copied().unwrap_or(0xff) as i8,
        }
    }

    /// Write the fields back (other bits of the record are untouched).
    pub fn write_record(&self, rec: &mut [u8], retail: bool) {
        let s = shift(retail);
        if rec.len() < OFF_ITEM + s + 1 {
            return;
        }
        rec[OFF_BITS + s] = (self.base_hits & 7) | ((self.hits & 7) << 3) | ((self.ring_type & 3) << 6);
        rec[OFF_AUTO + s] = (rec[OFF_AUTO + s] & !1) | self.auto as u8;
        rec[OFF_ZONE + s..OFF_ZONE + s + 5].copy_from_slice(&self.zone);
        rec[OFF_STRIKE + s..OFF_STRIKE + s + 5].copy_from_slice(&self.strike);
        rec[OFF_ITEM + s] = self.item as u8;
    }

    /// `CmdPC::GetExpansionRingItem`: hits bought on top of the natural count.
    pub fn extra_hits(&self) -> u8 {
        self.hits.saturating_sub(self.base_hits)
    }

    /// `CmdPC::IsExpandRing`: any point placed on the zones / strike areas.
    pub fn is_expanded(&self) -> bool {
        self.zone.iter().chain(self.strike.iter()).any(|&p| p != 0)
    }

    /// `ResetExpansion` of both tables (what the auto-ring reset does).
    pub fn reset_expansion(&mut self) {
        self.zone = [0; 5];
        self.strike = [0; 5];
    }

    /// The 20 byte `JRCUSTOM` table of `CmdPC::CustomJudgmentRing`: `widen[5]` (zone points * 2), `narrow[5]` (weapon bytes `0..`),
    /// `strike_widen[5]` (strike points), `strike_narrow[5]` (weapon bytes `hits..`), only the first `hits` entries filled.
    pub fn jr_custom(&self, weapon_ring: &[u8]) -> [u8; 20] {
        let mut raw = [0u8; 20];
        let hits = self.hits as usize;
        for i in 0..hits.min(5) {
            raw[i] = self.zone[i].wrapping_shl(1);
            raw[10 + i] = self.strike[i];
            if (1..=5).contains(&hits) {
                raw[5 + i] = weapon_ring.get(i).copied().unwrap_or(0);
                raw[15 + i] = weapon_ring.get(hits + i).copied().unwrap_or(0);
            }
        }
        raw
    }
}

pub fn ring_state(session: &GameSession, pc: u8) -> RingState {
    let retail = session.save.build.is_retail();
    session.save.btl.pc(pc as usize).map(|r| RingState::from_record(&r.raw, retail)).unwrap_or_default()
}

pub fn store_ring_state(session: &mut GameSession, pc: u8, st: &RingState) {
    let retail = session.save.build.is_retail();
    if let Some(mut r) = session.save.btl.pc(pc as usize) {
        st.write_record(&mut r.raw, retail);
        session.save.btl.set_pc(pc as usize, &r);
    }
}

/// Stock of ring items of `kind` ([`STOCK_HITS`] ..) in the active bag.
pub fn stock(session: &GameSession, kind: usize) -> u8 {
    session.save.btl.key_item(kind)
}

/// `CmdParty::GetRestRingItem(kind)`: stock minus what the members already use (kind 0 extra hits, 1 zone points, 2 strike points).
pub fn rest(session: &GameSession, kind: usize) -> i32 {
    let used: i32 = session
        .all_members()
        .into_iter()
        .map(|id| {
            let st = ring_state(session, id);
            match kind {
                STOCK_HITS => st.extra_hits() as i32,
                STOCK_ZONE => st.zone.iter().map(|&p| p as i32).sum(),
                STOCK_STRIKE => st.strike.iter().map(|&p| p as i32).sum(),
                _ => (st.item as i32 == kind as i32) as i32,
            }
        })
        .sum();
    stock(session, kind) as i32 - used
}

/// What the attack ring of party member `pc` looks like (`CmdPC::CreateJudgmentRing` + `CustomJudgmentRing`).
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct BattleRing {
    /// number of hit areas (`PC_J` row); the auto ring has exactly one
    pub hits: u8,
    /// `JRing+0x41` ring type (the auto ring is type 1)
    pub ring_type: u8,
    pub auto: bool,
    /// `JRCUSTOM` for `JRing::custom_data`, `None` when no expansion point is placed
    pub custom: Option<[u8; 20]>,
}

/// The ring settings battle must use for `pc`; `weapon_ring` = bytes `0x28..0x32` of the equipped weapon's `WPN_` record (pass `&[]` when unknown).
pub fn battle_ring(session: &GameSession, pc: u8, weapon_ring: &[u8]) -> BattleRing {
    let st = ring_state(session, pc);
    if st.auto {
        return BattleRing { hits: 1, ring_type: 1, auto: true, custom: None };
    }
    let custom = st.is_expanded().then(|| st.jr_custom(weapon_ring));
    BattleRing { hits: st.hits, ring_type: st.ring_type, auto: false, custom }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn retail_record_layout_matches_the_live_save() {
        // Karin of a real retail save: +0x5c = 0x12 (base 2, chosen 2, normal ring), +0x68 = 0xff (no ring item)
        let s = crate::save::SaveFile::parse(include_bytes!("../tests/fixtures/us_card_SH2-000")).unwrap();
        let rec = s.btl.pc(5).unwrap();
        let st = RingState::from_record(&rec.raw, true);
        assert_eq!((st.base_hits, st.hits, st.ring_type, st.auto, st.item), (2, 2, 0, false, -1));
        assert_eq!(st.zone, [0; 5]);
        // writing the same state back changes nothing
        let mut raw = rec.raw;
        st.write_record(&mut raw, true);
        assert_eq!(raw, rec.raw);
    }

    #[test]
    fn points_pay_from_the_stock_and_make_the_jrcustom_table() {
        let s = crate::save::SaveFile::parse(include_bytes!("../tests/fixtures/us_card_SH2-000")).unwrap();
        let mut g = GameSession { save: s, ..Default::default() };
        g.sync_from_save();
        // the new game stock: three zone and three strike expansion items
        assert_eq!((stock(&g, STOCK_ZONE), stock(&g, STOCK_STRIKE)), (3, 3));
        assert_eq!(rest(&g, STOCK_ZONE), 3);
        let mut st = ring_state(&g, 5);
        st.zone[0] = 2;
        st.strike[1] = 1;
        store_ring_state(&mut g, 5, &st);
        assert_eq!((rest(&g, STOCK_ZONE), rest(&g, STOCK_STRIKE)), (1, 2));
        let b = battle_ring(&g, 5, &[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
        assert_eq!((b.hits, b.ring_type, b.auto), (2, 0, false));
        let c = b.custom.unwrap();
        assert_eq!(&c[0..5], &[4, 0, 0, 0, 0], "zone points are doubled");
        assert_eq!(&c[5..10], &[1, 2, 0, 0, 0], "weapon narrowing of areas 0..hits");
        assert_eq!(&c[10..15], &[0, 1, 0, 0, 0]);
        assert_eq!(&c[15..20], &[3, 4, 0, 0, 0], "strike narrowing starts hits bytes into the weapon table");
        // auto ring: one area, practice type, no custom table
        let mut st = ring_state(&g, 5);
        st.auto = true;
        store_ring_state(&mut g, 5, &st);
        assert_eq!(battle_ring(&g, 5, &[]), BattleRing { hits: 1, ring_type: 1, auto: true, custom: None });
    }
}
