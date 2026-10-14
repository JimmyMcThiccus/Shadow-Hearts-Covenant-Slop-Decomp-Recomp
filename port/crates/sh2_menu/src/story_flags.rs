//! Dev option `SH2_STORY_FLAGS`: start a new game with story / side-quest script flags already set, the way the retail debug map's
//! Flag management pages set them (`DB_00_U` event script; `notes/integration/debug_menu.md`).
//!
//! A script flag `n` is bit `n & 31` of register word `n >> 5` (`CScript` `setFlag` / `chkFlag`); the register file is
//! [`GameSession::regs`](crate::session::GameSession::regs), copied into every map's script VM on load.
//!
//! Syntax (comma separated, applied in order):
//! * `84`, `0x54` - set one flag; `-0x54` clears it
//! * `8-12`, `0x3c-0x40` - set a range (inclusive)
//! * `first:N`, `second:N`, `hidden:N`, `wolf:N`, `grave:N`, `appear:N` - the first `N` rows of that debug page (story order:
//!   `first:5` = Opening, Apoina A, Domremy, Ardennes, Paris cleared; `wolf:15` = every Wolfbout opponent beaten)
//! * `ringsoul=N`, `books=N` - the two counter bytes (Ring Soul visits, secret-art books)
//!
//! Example: `SH2_STORY_FLAGS=first:14,wolf:3,0x54` (whole first disc part, three Wolfbout wins, last dungeon open).

/// `(page name, first flag, rows)` of the debug map's Flag management pages.
pub const PAGES: &[(&str, u32, u32)] = &[
    ("first", 8, 34),
    ("second", 0x3c, 26),
    ("hidden", 0x64, 6),
    ("wolf", 0xa0, 15),
    ("appear", 0x29d0, 19),
    ("grave", 0x29e8, 18),
];

/// Byte offsets of the counters in the register file: Ring Soul visits (typed register 0x1539), secret-art books (reg8 0x18).
pub const RING_SOUL_BYTE: usize = 0x539;
pub const BOOKS_BYTE: usize = 0x18;

/// Set or clear flag `n` in a register file.
pub fn set_flag(regs: &mut [u32], n: u32, on: bool) {
    if let Some(w) = regs.get_mut((n >> 5) as usize) {
        if on {
            *w |= 1 << (n & 31);
        } else {
            *w &= !(1 << (n & 31));
        }
    }
}

pub fn flag(regs: &[u32], n: u32) -> bool {
    regs.get((n >> 5) as usize).map(|w| (w >> (n & 31)) & 1 != 0).unwrap_or(false)
}

fn set_byte(regs: &mut [u32], off: usize, v: u8) {
    if let Some(w) = regs.get_mut(off / 4) {
        let sh = (off % 4) * 8;
        *w = (*w & !(0xff << sh)) | ((v as u32) << sh);
    }
}

fn num(s: &str) -> Option<u32> {
    let s = s.trim();
    match s.strip_prefix("0x").or_else(|| s.strip_prefix("0X")) {
        Some(h) => u32::from_str_radix(h, 16).ok(),
        None => s.parse().ok(),
    }
}

/// Apply a `SH2_STORY_FLAGS` spec to a register file.  Unknown items are skipped (and returned so the caller can log them).
pub fn apply(regs: &mut [u32], spec: &str) -> Vec<String> {
    let mut bad = Vec::new();
    for item in spec.split(',').map(str::trim).filter(|s| !s.is_empty()) {
        let ok = if let Some((page, n)) = item.split_once(':') {
            match (PAGES.iter().find(|p| p.0 == page.trim()), num(n)) {
                (Some(&(_, first, rows)), Some(n)) => {
                    for i in 0..n.min(rows) {
                        set_flag(regs, first + i, true);
                    }
                    true
                }
                _ => false,
            }
        } else if let Some((key, v)) = item.split_once('=') {
            match (key.trim(), num(v)) {
                ("ringsoul", Some(v)) => {
                    set_byte(regs, RING_SOUL_BYTE, v.min(255) as u8);
                    true
                }
                ("books", Some(v)) => {
                    set_byte(regs, BOOKS_BYTE, v.min(255) as u8);
                    true
                }
                _ => false,
            }
        } else if let Some(n) = item.strip_prefix('-').and_then(num) {
            set_flag(regs, n, false);
            true
        } else if let Some((a, b)) = item.split_once('-') {
            match (num(a), num(b)) {
                (Some(a), Some(b)) if a <= b => {
                    for n in a..=b {
                        set_flag(regs, n, true);
                    }
                    true
                }
                _ => false,
            }
        } else if let Some(n) = num(item) {
            set_flag(regs, n, true);
            true
        } else {
            false
        };
        if !ok {
            bad.push(item.to_string());
        }
    }
    bad
}

/// `SH2_STORY_FLAGS` from the environment, applied to `regs` (new game).
pub fn apply_env(regs: &mut [u32]) {
    if let Ok(spec) = std::env::var("SH2_STORY_FLAGS") {
        let bad = apply(regs, &spec);
        log::info!("story flags: applied SH2_STORY_FLAGS={spec}");
        if !bad.is_empty() {
            log::warn!("story flags: ignored {bad:?}");
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pages_ranges_and_counters() {
        let mut r = vec![0u32; 0x200];
        let bad = apply(&mut r, "first:5, wolf:2, 0x54, 0x29e8-0x29e9, ringsoul=3, books=0x2, nope, -0x54");
        assert_eq!(bad, vec!["nope".to_string()]);
        // Opening (8) .. Paris (12)
        assert!((8..=12).all(|n| flag(&r, n)) && !flag(&r, 13) && !flag(&r, 7));
        assert!(flag(&r, 0xa0) && flag(&r, 0xa1) && !flag(&r, 0xa2));
        assert!(!flag(&r, 0x54), "cleared again by -0x54");
        assert!(flag(&r, 0x29e8) && flag(&r, 0x29e9));
        assert_eq!((r[RING_SOUL_BYTE / 4] >> ((RING_SOUL_BYTE % 4) * 8)) & 0xff, 3);
        assert_eq!(r[BOOKS_BYTE / 4] & 0xff, 2);
        // word layout: flag 8 is bit 8 of word 0, flag 0xa0 bit 0 of word 5 (as in the live register file)
        assert_eq!(r[0] & 0x1f00, 0x1f00);
        assert_eq!(r[5] & 3, 3);
    }

    #[test]
    fn page_counts_are_capped() {
        let mut r = vec![0u32; 0x200];
        apply(&mut r, "hidden:99");
        assert!((0x64..0x6a).all(|n| flag(&r, n)) && !flag(&r, 0x6a));
    }
}
