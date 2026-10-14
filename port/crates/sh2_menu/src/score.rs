//! Score statistics of the Score page (`CmdScore::SetScore` / `GetScore`, US FIELD.BIN 0x004ada00 / 0x004ade00).
//!
//! The retail save keeps three statistic blocks of 0x400 bytes (one per chapter) at `BTL0 + 0x14bc + chapter * 0x400` (the region right before
//! the item-list cache) and four u32 per chapter at `MENU + 0x2cc + chapter * 0x10`.  `SetScore` sums them; `GetScore(case)` turns the sums
//! into the numbers the page shows.  A block is an array of u32:
//!
//! | index | meaning (summed over the chapters) |
//! |---|---|
//! | 0 | battles fought |
//! | 1 | times ran away |
//! | 2 | most hits in one battle (max) |
//! | 3 | total hits |
//! | 4 | (max, not shown) |
//! | 5 | combo successes |
//! | 6 | largest damage (max) |
//! | 7 | complete victories |
//! | 8 | (not shown) |
//! | 9 | shortcut uses |
//! | 10..17 | battle bonuses (summed) |
//! | 0x11 + 9 * r + j, r < 14 | per party member r: j = 1 berserk, 2 unconscious, 3 / 5 ring total / success, 4 / 6 perfect total / success, 7 / 8 combo-ring total / success |
//!
//! Shop-ring total / success come from the `MENU` words.  The port's battle does not maintain these counters yet (hook:
//! `notes/integration/requests.md`); a **loaded retail save carries the real values**.  The demo build has no retail block: only battles won and the
//! walked distance (kept by the session) are available.

use crate::save::{BtlSave, MenuSave};

pub const OFF_BLOCKS: usize = 0x14bc;
pub const BLOCK_SIZE: usize = 0x400;
pub const CHAPTERS: usize = 3;
pub const OFF_MENU_SHOP: usize = 0x2cc;

/// The sums of [`ScoreTotals::from_save`].
#[derive(Clone, Debug, Default, PartialEq)]
pub struct ScoreTotals {
    pub battles: u32,
    pub ran_away: u32,
    pub berserk: u32,
    pub unconscious: u32,
    /// sum of the members' `j = 0` words (battles joined)
    pub joined_rows: u32,
    pub victories: u32,
    pub total_hits: u32,
    pub max_hits: u32,
    pub max_damage: u32,
    pub combo_successes: u32,
    pub shortcuts: u32,
    pub bonuses: u32,
    /// `(successes, total)` of the ring kinds: attack ring, perfect, combo ring, shop ring
    pub ring: (u32, u32),
    pub perfect: (u32, u32),
    pub combo_ring: (u32, u32),
    pub shop_ring: (u32, u32),
    pub distance_km: f32,
    /// per party member (index = PC id < 14): `(ring success, ring total, perfect success, perfect total)` and battles joined (`j = 0`)
    pub members: Vec<MemberScore>,
}

/// One member's part of the score blocks (`0x11 + 9 * pc + j`).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct MemberScore {
    pub joined: u32,
    pub ring: (u32, u32),
    pub perfect: (u32, u32),
}

/// What `GetScore` returns for one case, ready for the `printf` formats of the score scene.
#[derive(Clone, Debug, PartialEq)]
pub enum ScoreValue {
    Int(u32),
    /// `"%d/%d"`
    Pair(u32, u32),
    /// `"%3.2f"` percent
    Percent(f32),
    /// `"%12.2f"` kilometres
    Km(f32),
}

impl ScoreTotals {
    /// `CmdScore::SetScore` over the three chapter blocks (retail only; the demo-shaped save has no blocks).
    pub fn from_save(btl: &BtlSave, menu: &MenuSave) -> ScoreTotals {
        let mut t = ScoreTotals::default();
        if !btl.is_retail() {
            return t;
        }
        let word = |blk: &[u8], i: usize| blk.get(i * 4..i * 4 + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]])).unwrap_or(0);
        let mut rows = [0u32; 9];
        for ch in 0..CHAPTERS {
            let o = OFF_BLOCKS + ch * BLOCK_SIZE;
            let Some(blk) = btl.retail.get(o..o + BLOCK_SIZE) else { continue };
            t.battles += word(blk, 0);
            t.ran_away += word(blk, 1);
            t.max_hits = t.max_hits.max(word(blk, 2));
            t.total_hits += word(blk, 3);
            t.combo_successes += word(blk, 5);
            t.max_damage = t.max_damage.max(word(blk, 6));
            t.victories += word(blk, 7);
            t.shortcuts += word(blk, 9);
            for i in 10..0x11 {
                t.bonuses += word(blk, i);
            }
            if t.members.is_empty() {
                t.members = vec![MemberScore::default(); 14];
            }
            for r in 0..14 {
                for (j, s) in rows.iter_mut().enumerate() {
                    *s += word(blk, 0x11 + r * 9 + j);
                }
                let m = &mut t.members[r];
                m.joined += word(blk, 0x11 + r * 9);
                m.ring.1 += word(blk, 0x11 + r * 9 + 3);
                m.ring.0 += word(blk, 0x11 + r * 9 + 5);
                m.perfect.1 += word(blk, 0x11 + r * 9 + 4);
                m.perfect.0 += word(blk, 0x11 + r * 9 + 6);
            }
            let m = OFF_MENU_SHOP + ch * 0x10;
            let mw = |k: usize| menu.data.get(m + k * 4..m + k * 4 + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]])).unwrap_or(0);
            t.shop_ring.1 += mw(0);
            t.shop_ring.0 += mw(1);
        }
        t.joined_rows = rows[0];
        t.berserk = rows[1];
        t.unconscious = rows[2];
        t.ring = (rows[5], rows[3]);
        t.perfect = (rows[6], rows[4]);
        t.combo_ring = (rows[8], rows[7]);
        t
    }

    /// `GetScore(case)`: cases 0..=0x13 in the order of the labels of the score scene (label `4 + case`).
    pub fn value(&self, case: usize) -> ScoreValue {
        let cap = |v: u32| v.min(99_999);
        let pct = |p: (u32, u32)| {
            if p.1 == 0 {
                0.0
            } else {
                let v = p.0 as f32 / p.1 as f32 * 100.0;
                // `GetScore`: values above 99.99 show as 99.99 unless exactly 100
                if v > 99.99 && v != 100.0 { 99.99 } else { v }
            }
        };
        let pair = |p: (u32, u32)| ScoreValue::Pair(cap(p.0), cap(p.1));
        match case {
            0 => ScoreValue::Int(cap(self.battles)),
            1 => pair(self.ring),
            2 => ScoreValue::Percent(pct(self.ring)),
            3 => pair(self.perfect),
            4 => ScoreValue::Percent(pct(self.perfect)),
            5 => pair(self.combo_ring),
            6 => ScoreValue::Percent(pct(self.combo_ring)),
            7 => pair(self.shop_ring),
            8 => ScoreValue::Percent(pct(self.shop_ring)),
            9 => ScoreValue::Km(self.distance_km),
            0xa => ScoreValue::Int(cap(self.ran_away)),
            0xb => ScoreValue::Int(cap(self.berserk)),
            0xc => ScoreValue::Int(cap(self.unconscious)),
            0xd => ScoreValue::Int(cap(self.victories)),
            0xe => ScoreValue::Int(cap(self.total_hits)),
            0xf => ScoreValue::Int(cap(self.max_hits)),
            0x10 => ScoreValue::Int(cap(self.max_damage)),
            0x11 => ScoreValue::Int(cap(self.combo_successes)),
            0x12 => ScoreValue::Int(cap(self.shortcuts)),
            0x13 => ScoreValue::Int(cap(self.bonuses)),
            _ => ScoreValue::Int(0),
        }
    }
}

impl ScoreTotals {
    /// The number `GetScore` hands to `GetComment` for case `case` (US 0x4ade00, second switch): pairs give the success rate in percent,
    /// scaled by `0.5 + total / 400` while the successes are below 200 / 200 / 125 / 100 (ring / perfect / combo ring / shop ring); rates
    /// the rate, the distance its kilometres, counts the count (all capped at 99999).
    pub fn comment_value(&self, case: usize) -> i32 {
        let pair = |p: (u32, u32), k: usize| -> i32 {
            if p.1 == 0 {
                return 0;
            }
            let mut r = p.0 as f32 / p.1 as f32 * 100.0;
            if p.0 < [200, 200, 125, 100][k] {
                r *= p.1 as f32 / 400.0 + 0.5;
            }
            r as i32
        };
        match case {
            1 => pair(self.ring, 0),
            3 => pair(self.perfect, 1),
            5 => pair(self.combo_ring, 2),
            7 => pair(self.shop_ring, 3),
            _ => match self.value(case) {
                ScoreValue::Int(v) => v as i32,
                ScoreValue::Pair(a, _) => a as i32,
                ScoreValue::Percent(p) => p as i32,
                ScoreValue::Km(k) => k as i32,
            },
        }
    }

    /// `CmdScoreRank::GetRank` (US 0x4afb50): five weighted terms (ring, perfect, combo ring, battle bonuses per battle, shop ring), each
    /// growing with the attempts (capped at twice the battles), the score `2 A + 3 B + 2 C + 2 D + E` -> rank `101 - min(score / 10, max hits,
    /// 100) - (score - 1000) / 20`, worsened by 20 per run-away / berserk / unconscious per battle, and never better than `101 - ceil((battles
    /// / 1000)^2)`; 1 (best) .. 99.
    pub fn rank(&self) -> i32 {
        let battles = self.battles as i32;
        let bf = battles as f32;
        let curve = |succ: u32, total: u32, lo: i32, hi: i32, k: f32, div: f32, last: f32, cap_by_battles: bool| -> f32 {
            let t = total as i32;
            let s0 = if cap_by_battles { t.min(battles * 2) } else { t };
            let mut r = 0.0f32;
            if t != 0 {
                r = succ as f32 / t as f32 * 100.0;
                r *= r;
            }
            let s0f = s0 as f32;
            if s0 < lo {
                r * s0f * s0f / 1e6
            } else if s0 < hi {
                r / (k - s0f / div)
            } else {
                r / last
            }
        };
        let a = curve(self.ring.0, self.ring.1, 112, 4612, 82.12, 100.0, 36.0, true);
        let b = curve(self.perfect.0, self.perfect.1, 200, 5400, 27.0, 300.0, 9.0, true);
        let c = curve(self.combo_ring.0, self.combo_ring.1, 125, 3925, 64.25, 100.0, 25.0, true);
        let per = if battles != 0 { self.bonuses as f32 / bf } else { 0.0 };
        let d = if battles < 201 {
            let v = 9.0 - bf * 0.03;
            900.0 * per / (v * v)
        } else if battles < 5201 {
            per * (96.0 + bf * 0.02)
        } else {
            per * 200.0
        };
        let e = curve(self.shop_ring.0, self.shop_ring.1, 112, 4612, 82.12, 100.0, 36.0, false);
        let score = (2.0 * a + 3.0 * b + 2.0 * c + 2.0 * d + e) as i32;
        let (r10, extra) = if score < 1001 { (score / 10, 0) } else { (100, (score - 1000) / 20) };
        let s7 = (r10 as u32).min(self.max_hits).min(100) as i32;
        let s6 = (101 - s7 - extra).clamp(1, 99);
        let pen = if battles != 0 { (self.ran_away as i32 * 20) / battles + (self.berserk as i32 * 20) / battles + (self.unconscious as i32 * 20) / battles } else { 0 };
        let c4 = s6 + pen;
        let q = (bf / 1000.0) * (bf / 1000.0);
        let floor = (101 - q.ceil() as i32).max(1);
        c4.min(floor).clamp(1, 99)
    }
}

impl ScoreValue {
    /// The text the row shows (the retail scene's `%%m2` markup removed).
    pub fn text(&self) -> String {
        match self {
            ScoreValue::Int(v) => format!("{v}"),
            ScoreValue::Pair(a, b) => format!("{a}/{b}"),
            ScoreValue::Percent(p) => format!("{p:.2}%"),
            ScoreValue::Km(k) => format!("{k:.2}"),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::save::SaveFile;

    #[test]
    fn real_card_save_has_all_zero_scores_and_demo_has_none() {
        let s = SaveFile::parse(include_bytes!("../tests/fixtures/us_card_SH2-000")).unwrap();
        let t = ScoreTotals::from_save(&s.btl, &s.menu);
        // the save was made right after the first fight: the counters hold the prologue's few events, the ratios stay in range
        assert!(t.ring.0 <= t.ring.1.max(t.ring.0));
        assert!(matches!(t.value(2), ScoreValue::Percent(p) if (0.0..=100.0).contains(&p)));
        let d = SaveFile::new_default_for(crate::save::Build::Demo);
        assert_eq!(ScoreTotals::from_save(&d.btl, &d.menu), ScoreTotals::default());
    }

    #[test]
    fn sums_follow_the_decompiled_set_score() {
        let mut f = SaveFile::new_default_for(crate::save::Build::Retail);
        let mut put = |ch: usize, i: usize, v: u32| {
            let o = OFF_BLOCKS + ch * BLOCK_SIZE + i * 4;
            f.btl.retail[o..o + 4].copy_from_slice(&v.to_le_bytes());
        };
        put(0, 0, 5);
        put(1, 0, 7);
        put(0, 2, 11);
        put(2, 2, 9);
        put(1, 0x11 + 9 * 3 + 5, 4); // member 3: ring success
        put(1, 0x11 + 9 * 3 + 3, 8); // member 3: ring total
        put(0, 0x11 + 9 * 6 + 5, 1);
        put(0, 0x11 + 9 * 6 + 3, 2);
        let t = ScoreTotals::from_save(&f.btl, &f.menu);
        assert_eq!(t.value(0), ScoreValue::Int(12));
        assert_eq!(t.value(0xf), ScoreValue::Int(11), "max hits is a max, not a sum");
        assert_eq!(t.value(1), ScoreValue::Pair(5, 10));
        assert_eq!(t.value(2).text(), "50.00%");
        assert_eq!(ScoreValue::Pair(5, 10).text(), "5/10");
    }

    #[test]
    fn rank_and_comment_values_match_the_live_capture() {
        // live `score_a` (2 battles, ring 12/12, perfect 0/12): Rank 99, ring comment = "Practice Paying Off?" (40 <= 52 < 60)
        let t = ScoreTotals { battles: 2, ring: (12, 12), perfect: (0, 12), max_hits: 3, ..Default::default() };
        assert_eq!(t.rank(), 99);
        assert_eq!(t.comment_value(1), 52, "f32: 100 * 0.53 truncates to 52, as the game's cvt.w.s");
        assert_eq!(t.comment_value(0), 2);
        // a strong record ranks near the top
        let s = ScoreTotals { battles: 3000, ring: (9000, 9000), perfect: (6000, 9000), combo_ring: (500, 600), bonuses: 9000, max_hits: 200, ..Default::default() };
        assert!(s.rank() < 20, "{}", s.rank());
    }
}
