//! Reads `match` arms out of other crates' sources (compiled in with `include_str!`), so that the harness's "which selectors / ops does the
//! port answer" lists follow the code instead of being copied by hand (round 6 QA2: the round-5 copies went stale within hours).
//!
//! `arms(src, anchor, head)`: from the first line containing `anchor`, the first later line containing `head` (a `match ... {` line) opens
//! the match; every line at the indentation of its first arm that contains `=>` starts an arm; the arm ends at the next such line or at a
//! line indented less (the closing brace).  Patterns are split on `|` (guards after `if` are dropped); integers (`0x1f`, `12`) and inclusive
//! ranges (`0x24..=0x38`) are understood, anything else is kept as text (`ScriptOut::Fader { .. }`).  First match wins, as in Rust.

pub const FIELD_HOST: &str = include_str!("../../../sh2_field/src/host.rs");
pub const CUTSCENE_PLUGIN: &str = include_str!("../../../sh2_field/src/cutscene_plugin.rs");

#[derive(Debug, Clone)]
pub enum Pat {
    Val(i64),
    Range(i64, i64),
    Wild,
    Text(String),
}

#[derive(Debug, Clone)]
pub struct Arm {
    pub pats: Vec<Pat>,
    pub body: String,
}

#[derive(Debug, Clone, Default)]
pub struct Arms(pub Vec<Arm>);

fn int(s: &str) -> Option<i64> {
    let s = s.trim();
    let (neg, s) = match s.strip_prefix('-') {
        Some(r) => (true, r.trim()),
        None => (false, s),
    };
    let s = s.replace('_', "");
    let v = if let Some(h) = s.strip_prefix("0x") { i64::from_str_radix(h, 16).ok()? } else { s.parse().ok()? };
    Some(if neg { -v } else { v })
}

fn pat(p: &str) -> Pat {
    let p = p.trim();
    if p == "_" {
        return Pat::Wild;
    }
    if let Some((a, b)) = p.split_once("..=") {
        if let (Some(a), Some(b)) = (int(a), int(b)) {
            return Pat::Range(a, b);
        }
    }
    match int(p) {
        Some(v) => Pat::Val(v),
        None => Pat::Text(p.to_string()),
    }
}

fn indent(l: &str) -> usize {
    l.len() - l.trim_start().len()
}

pub fn arms(src: &str, anchor: &str, head: &str) -> Arms {
    let lines: Vec<&str> = src.lines().collect();
    let Some(a) = lines.iter().position(|l| l.contains(anchor)) else { return Arms::default() };
    let Some(h) = lines[a..].iter().position(|l| l.contains(head)).map(|i| i + a) else { return Arms::default() };
    // the first arm: first non-blank, non-comment line after the head
    let Some(first) = lines[h + 1..].iter().position(|l| !l.trim().is_empty() && !l.trim_start().starts_with("//")).map(|i| i + h + 1) else {
        return Arms::default();
    };
    let ind = indent(lines[first]);
    let mut out: Vec<Arm> = vec![];
    for l in &lines[first..] {
        let t = l.trim();
        if t.is_empty() || t.starts_with("//") {
            if let Some(last) = out.last_mut() {
                last.body.push_str(t);
                last.body.push('\n');
            }
            continue;
        }
        let i = indent(l);
        if i < ind {
            break;
        }
        if i == ind && t.contains("=>") {
            let (p, body) = t.split_once("=>").unwrap();
            let p = p.split(" if ").next().unwrap_or(p);
            // `Some(a) => match what {`-style arms with a nested pattern containing `|` inside braces are rare; split on top-level `|` only
            let mut pats = vec![];
            let (mut depth, mut cur) = (0i32, String::new());
            for c in p.chars() {
                match c {
                    '(' | '{' | '[' => depth += 1,
                    ')' | '}' | ']' => depth -= 1,
                    _ => {}
                }
                if c == '|' && depth == 0 {
                    pats.push(pat(&cur));
                    cur.clear();
                } else {
                    cur.push(c);
                }
            }
            pats.push(pat(&cur));
            out.push(Arm { pats, body: format!("{}\n", body.trim()) });
        } else if let Some(last) = out.last_mut() {
            last.body.push_str(t);
            last.body.push('\n');
        }
    }
    Arms(out)
}

impl Arms {
    /// the arm a value takes (first match)
    pub fn find(&self, v: i64) -> Option<&Arm> {
        self.0.iter().find(|a| {
            a.pats.iter().any(|p| match p {
                Pat::Val(x) => *x == v,
                Pat::Range(x, y) => (*x..=*y).contains(&v),
                Pat::Wild => true,
                Pat::Text(_) => false,
            })
        })
    }
    /// the value has an arm of its own (not the `_` fall-through)
    pub fn answers(&self, v: i64) -> bool {
        self.find(v).map(|a| !a.pats.iter().any(|p| matches!(p, Pat::Wild))).unwrap_or(false)
    }
    /// the arm whose text pattern starts with `prefix` (e.g. `ScriptOut::Fader`)
    pub fn find_text(&self, prefix: &str) -> Option<&Arm> {
        self.0.iter().find(|a| a.pats.iter().any(|p| matches!(p, Pat::Text(t) if t.starts_with(prefix) && t[prefix.len()..].chars().next().map(|c| !c.is_alphanumeric()).unwrap_or(true))))
    }
}

/// An arm body that does nothing: `{}`, only comments, or only records the call (`field_data_ex.insert`, a `debug!` saying "not applied").
pub fn body_is_noop(body: &str) -> bool {
    let code: Vec<&str> = body.lines().map(|l| l.split("//").next().unwrap_or("").trim()).filter(|l| !l.is_empty()).collect();
    if body.contains("not applied") {
        return true;
    }
    code.iter().all(|l| matches!(*l, "{}" | "{}," | "{" | "}" | "}," | "()" | "()," ) || l.contains("field_data_ex.insert"))
}

/// The field host's selector tables (sh2_field/src/host.rs), read once.
pub struct FieldTables {
    pub get_char: Arms,
    pub get_char_bg: Arms,
    pub set_char: Arms,
    pub get_field: Arms,
    pub set_field: Arms,
    /// the `c2.sub` dispatcher (`fn op`)
    pub ops: Arms,
}

pub fn field_tables() -> &'static FieldTables {
    static T: std::sync::OnceLock<FieldTables> = std::sync::OnceLock::new();
    T.get_or_init(|| {
        let t = FieldTables {
            get_char: arms(FIELD_HOST, "0x00 GetCharacterInfo", "Some(a) => match what {"),
            get_char_bg: arms(FIELD_HOST, "0x00 GetCharacterInfo", "Some(b) => match what {"),
            set_char: arms(FIELD_HOST, "0x01 SetCharacterInfo", "match what {"),
            get_field: arms(FIELD_HOST, "fn get_field_data(", "match sel {"),
            set_field: arms(FIELD_HOST, "fn set_field_data(", "match sel {"),
            ops: arms(FIELD_HOST, "fn op(&mut self, ctx: &mut ExCtx", "match sub {"),
        };
        for (n, a) in [("GetCharacterInfo", &t.get_char), ("GetCharacterInfo(BG)", &t.get_char_bg), ("SetCharacterInfo", &t.set_char), ("GetFieldData", &t.get_field), ("SetFieldData", &t.set_field), ("op dispatcher", &t.ops)] {
            if a.0.len() < 2 {
                eprintln!("coverage: srcscan could not read the {n} arms from sh2_field/src/host.rs (the code moved?): the audit of it is off");
            }
        }
        t
    })
}

/// The cut-scene `LSCR` host (sh2_field/src/cutscene_plugin.rs): per `c0.sub`, `None` = no arm (unknown op), `Some(true)` = accepted but
/// the `ScriptOut` it produces is not applied by `apply_script_out`, `Some(false)` = handled.
pub fn lscr_op_state(sub: u8) -> Option<bool> {
    static T: std::sync::OnceLock<(Arms, Arms)> = std::sync::OnceLock::new();
    let (ops, apply) = T.get_or_init(|| (arms(CUTSCENE_PLUGIN, "impl ScriptHost for LscrHost", "match sub {"), arms(CUTSCENE_PLUGIN, "fn apply_script_out(", "match o {")));
    let arm = ops.find(sub as i64)?;
    if arm.pats.iter().any(|p| matches!(p, Pat::Wild)) {
        return None;
    }
    // the ScriptOut variant the op pushes
    let Some(i) = arm.body.find("ScriptOut::") else { return Some(body_is_noop(&arm.body)) };
    let name: String = arm.body[i..].chars().take_while(|c| c.is_alphanumeric() || *c == '_' || *c == ':').collect();
    match apply.find_text(&name) {
        Some(a) => Some(body_is_noop(&a.body)),
        None => Some(true),
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn reads_host_tables() {
        let t = field_tables();
        assert!(t.get_field.answers(0x29) && !t.get_field.answers(0x7f));
        assert!(t.get_char.answers(0xd));
        assert_eq!(lscr_op_state(0x0f), Some(false));
        assert_eq!(lscr_op_state(0x40), None);
    }
}
