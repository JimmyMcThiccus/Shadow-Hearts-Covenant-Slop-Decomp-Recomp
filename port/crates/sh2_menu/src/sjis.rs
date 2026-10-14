//! Shift-JIS <-> Unicode for the game's strings (script messages, `SSHMES.JPN` names, menu `.MSD` texts).
//!
//! The renderer works on Unicode (system CJK font), the data is Shift-JIS; the table lives in [`crate::sjis_table`].
//! Game specific text codes (`$` newline, `%I n` icon, `%W n` wait, `%T n`, `%P n`, see `notes/B/Texture.md` section 5) are
//! removed by [`strip_codes`] / turned into layout by [`message_to_string`].

use crate::sjis_table::{LEADS, TABLE, TRAILS};

fn lead_index(b: u8) -> Option<usize> {
    match b {
        0x81..=0x9f => Some((b - 0x81) as usize),
        0xe0..=0xfc => Some((b - 0xe0) as usize + 31),
        _ => None,
    }
}

/// Decode Shift-JIS bytes (stops at the first NUL).  Unmapped double-byte codes become `?`.
pub fn decode(b: &[u8]) -> String {
    let mut s = String::new();
    let mut i = 0;
    while i < b.len() {
        let c = b[i];
        if c == 0 {
            break;
        }
        if c < 0x80 {
            s.push(c as char);
            i += 1;
        } else if (0xa1..=0xdf).contains(&c) {
            // half-width katakana U+FF61..U+FF9F
            s.push(char::from_u32(0xff61 + (c as u32 - 0xa1)).unwrap_or('?'));
            i += 1;
        } else if let (Some(li), Some(&t)) = (lead_index(c), b.get(i + 1)) {
            let u = if (0x40..=0xfc).contains(&t) && t != 0x7f { TABLE[li * TRAILS + (t - 0x40) as usize] } else { 0 };
            s.push(if u == 0 { '?' } else { char::from_u32(u as u32).unwrap_or('?') });
            i += 2;
        } else {
            s.push('?');
            i += 1;
        }
    }
    s
}

/// Encode a Unicode string as Shift-JIS (ASCII, half-width kana and the two-byte table; anything else becomes `?`).
pub fn encode(s: &str) -> Vec<u8> {
    let mut out = Vec::new();
    for ch in s.chars() {
        let u = ch as u32;
        if u < 0x80 {
            out.push(u as u8);
        } else if (0xff61..=0xff9f).contains(&u) {
            out.push((u - 0xff61 + 0xa1) as u8);
        } else if u <= 0xffff {
            match TABLE.iter().position(|&t| t as u32 == u) {
                Some(idx) => {
                    let (li, ti) = (idx / TRAILS, idx % TRAILS);
                    let lead = if li < 31 { 0x81 + li as u8 } else { 0xe0 + (li - 31) as u8 };
                    out.push(lead);
                    out.push(0x40 + ti as u8);
                }
                None => out.push(b'?'),
            }
        } else {
            out.push(b'?');
        }
    }
    out
}

/// Remove in-text control sequences and convert `$` to a newline: `%I n`, `%W n`, `%T n`, `%P n` take a decimal argument.
pub fn strip_codes(text: &str) -> String {
    let mut out = String::new();
    let cs: Vec<char> = text.chars().collect();
    let mut i = 0;
    while i < cs.len() {
        match cs[i] {
            '$' => {
                out.push('\n');
                i += 1;
            }
            '%' if i + 1 < cs.len() && matches!(cs[i + 1], 'I' | 'W' | 'T' | 'P') => {
                i += 2;
                while i < cs.len() && (cs[i] == ' ' || cs[i].is_ascii_digit()) {
                    i += 1;
                }
            }
            c if (c as u32) < 0x20 && c != '\n' => i += 1,
            c => {
                out.push(c);
                i += 1;
            }
        }
    }
    out
}

/// Decode + strip, for message-box text.
pub fn message_to_string(b: &[u8]) -> String {
    strip_codes(&decode(b))
}

#[allow(dead_code)]
const _ASSERT: () = {
    assert!(LEADS == 60);
};

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn roundtrip() {
        // "ゲームを始める" / "Item"
        let s = "ゲームを始める";
        let b = encode(s);
        assert_eq!(decode(&b), s);
        assert_eq!(decode(b"Item"), "Item");
        assert_eq!(&encode("あ")[..], &[0x82, 0xa0]);
        assert_eq!(decode(&[0x83, 0x41]), "ア");
    }

    #[test]
    fn codes() {
        assert_eq!(strip_codes("A$B%W 30C%I12D"), "A\nBCD");
    }
}
