//! Static (recursive-descent) scanner of event-script code: finds every `CScriptEx` call site (`0xbc..=0xff`, sub, nargs) together
//! with the constant arguments that are visible on a simulated operand stack.  Used by the corpus survey tools (see
//! `notes/integration/script_ops.md`); it follows the byte grammar of `CScript::GetParameter` / `Statement` (JP 0x00294620 / 0x00294130).

use crate::image::ScriptImage;
use std::collections::{BTreeSet, HashSet};

#[derive(Debug, Clone)]
pub struct CallSite {
    /// code offset of the first opcode byte of the call
    pub ip: u32,
    /// user function (entry offset) the site was reached from
    pub func: u32,
    /// first opcode byte: `0xc2` = CField, `0xc0` = LSDScrEx, `< 0xbc` = builtin (`ifc_*`)
    pub ex: u8,
    pub sub: u8,
    pub nargs: u8,
    /// constants visible for the arguments (`None` = computed at run time)
    pub args: Vec<Option<u32>>,
}

fn u16_at(c: &[u8], o: usize) -> Option<u32> {
    Some(u16::from_le_bytes([*c.get(o)?, *c.get(o + 1)?]) as u32)
}
fn u32_at(c: &[u8], o: usize) -> Option<u32> {
    Some(u32::from_le_bytes([*c.get(o)?, *c.get(o + 1)?, *c.get(o + 2)?, *c.get(o + 3)?]))
}

/// Every call site reachable from the start / end functions, the event table and `callu` targets.
pub fn scan_calls(img: &ScriptImage) -> Vec<CallSite> {
    let code = &img.code;
    let mut funcs: BTreeSet<u32> = BTreeSet::new();
    funcs.insert(img.hdr.start_func as u32);
    if img.hdr.end_func != 0xffff {
        funcs.insert(img.hdr.end_func as u32);
    }
    for s in &img.events {
        for e in &s.entries {
            funcs.insert(e.func as u32);
        }
    }
    let mut done_funcs: HashSet<u32> = HashSet::new();
    let mut out: Vec<CallSite> = Vec::new();
    let mut seen_sites: HashSet<u32> = HashSet::new();
    while let Some(&f) = funcs.iter().find(|f| !done_funcs.contains(f)) {
        done_funcs.insert(f);
        let mut work = vec![f + 2];
        let mut visited: HashSet<u32> = HashSet::new();
        while let Some(mut ip) = work.pop() {
            let mut stack: Vec<Option<u32>> = Vec::new();
            let mut last_imm: Option<u32> = None;
            loop {
                if !visited.insert(ip) {
                    break;
                }
                let Some(&b) = code.get(ip as usize) else { break };
                let at = ip;
                ip += 1;
                macro_rules! pushc {
                    ($v:expr) => {{
                        let v: Option<u32> = $v;
                        last_imm = v;
                        stack.push(v);
                    }};
                }
                if b >= 0xa0 {
                    let mut sub = b;
                    if b > 0xbb {
                        sub = *code.get(ip as usize).unwrap_or(&0);
                        ip += 1;
                    }
                    let n = *code.get(ip as usize).unwrap_or(&0);
                    ip += 1;
                    let take = (n as usize).min(stack.len());
                    let args: Vec<Option<u32>> = stack[stack.len() - take..].to_vec();
                    stack.truncate(stack.len() - take);
                    if seen_sites.insert(at) {
                        out.push(CallSite { ip: at, func: f, ex: b, sub, nargs: n, args });
                    }
                    stack.push(None);
                    continue;
                }
                if b >= 0x90 {
                    // statements
                    stack.clear();
                    match b {
                        0x90 => {
                            if let Some(t) = u16_at(code, ip as usize) {
                                work.push(t);
                            }
                            break;
                        }
                        0x91 | 0x92 => {
                            if let Some(t) = u16_at(code, ip as usize) {
                                work.push(t);
                            }
                            ip += 2;
                        }
                        0x94 => {
                            let Some(tbl) = u16_at(code, ip as usize) else { break };
                            let mut p = tbl as usize;
                            let Some(h) = u16_at(code, p) else { break };
                            p += 2;
                            let kt = (h >> 12) & 7;
                            for _ in 0..(h & 0xfff) {
                                p += match kt {
                                    2 => 4,
                                    1 => 2,
                                    _ => 1,
                                };
                                if let Some(t) = u16_at(code, p) {
                                    work.push(t);
                                }
                                p += 2;
                            }
                            if h & 0x8000 != 0 {
                                if let Some(t) = u16_at(code, p) {
                                    work.push(t);
                                }
                                break;
                            }
                            ip = p as u32;
                        }
                        0x98 | 0x99 => break,
                        _ => {}
                    }
                    continue;
                }
                if b >= 0x20 {
                    // expression operators: stack effect + inline operands
                    match b {
                        0x8f | 0x8e => {
                            stack.pop();
                            stack.pop();
                            stack.pop();
                            stack.push(None);
                        }
                        0x8d => {
                            ip += 2;
                            stack.pop();
                        }
                        0x8c => {
                            let n = stack.pop().flatten().or(last_imm).unwrap_or(0);
                            ip += n.min(0x1000);
                        }
                        0x8b => {
                            ip += 1;
                            stack.pop();
                        }
                        0x8a => {
                            stack.pop();
                        }
                        0x80..=0x89 => {
                            let s = *code.get(ip as usize).unwrap_or(&0);
                            ip += 1;
                            if s & 0x80 != 0 && s & 0x40 != 0 {
                                ip += 1;
                            }
                            stack.pop();
                            stack.pop();
                            stack.push(None);
                        }
                        0x70..=0x7a | 0x67..=0x6d => {
                            let (a, bb) = (stack.pop().flatten(), stack.pop().flatten());
                            let r = match (a, bb, b) {
                                (Some(a), Some(c), 0x6a) => Some(a.wrapping_add(c)),
                                (Some(a), Some(c), 0x6b) => Some(c.wrapping_sub(a)),
                                (Some(a), Some(c), 0x67) => Some(c.wrapping_mul(a)),
                                _ => None,
                            };
                            stack.push(r);
                        }
                        0x60..=0x63 => {
                            let s = *code.get(ip as usize).unwrap_or(&0);
                            ip += 1;
                            if s & 0x80 != 0 && s & 0x40 != 0 {
                                ip += 1;
                            }
                            stack.pop();
                            stack.push(None);
                        }
                        0x66 => {
                            let v = stack.pop().flatten();
                            stack.push(v.map(|v| (v as i32).wrapping_neg() as u32));
                        }
                        _ => {
                            // unary: loads (0x20-0x28), segment adds, conversions, !, ~
                            stack.pop();
                            stack.push(None);
                        }
                    }
                    continue;
                }
                // pushes / low opcodes
                match b {
                    0x00 => break,
                    0x01 => stack.clear(),
                    0x04 => pushc!(None),
                    0x05 => pushc!(Some(u32::MAX)),
                    0x06 => pushc!(Some(0)),
                    0x07 => pushc!(Some(1)),
                    0x08 => pushc!(Some(2)),
                    0x09 => pushc!(Some(4)),
                    0x0a => {
                        pushc!(code.get(ip as usize).map(|&v| v as u32));
                        ip += 1;
                    }
                    0x0b => {
                        pushc!(code.get(ip as usize).map(|&v| v as u32 | 0xffff_ff00));
                        ip += 1;
                    }
                    0x0c => {
                        pushc!(u16_at(code, ip as usize));
                        ip += 2;
                    }
                    0x0d => {
                        pushc!(u16_at(code, ip as usize).map(|v| v | 0xffff_0000));
                        ip += 2;
                    }
                    0x0e | 0x0f => {
                        pushc!(u32_at(code, ip as usize));
                        ip += 4;
                    }
                    0x10..=0x13 => {
                        ip += 1;
                        stack.push(None);
                    }
                    0x14 | 0x16 | 0x18 => {
                        ip += 2;
                        stack.push(None);
                    }
                    0x15 => {
                        // data address: keep the offset so string arguments can be resolved
                        stack.push(u16_at(code, ip as usize).map(|v| v | crate::memory::SEG_DATA));
                        ip += 2;
                    }
                    0x19 => {
                        ip += 1;
                        stack.push(None);
                    }
                    0x1a => {
                        ip += 2;
                        stack.push(None);
                    }
                    0x1b => {
                        if let Some(t) = u16_at(code, ip as usize) {
                            funcs.insert(t);
                        }
                        let n = *code.get(ip as usize + 2).unwrap_or(&0) as usize;
                        ip += 3;
                        let take = n.min(stack.len());
                        stack.truncate(stack.len() - take);
                        stack.push(None);
                    }
                    _ => {}
                }
            }
        }
    }
    out.sort_by_key(|c| c.ip);
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn scans_real_field_script_if_present() {
        let Some(set) = crate::pkb_compat::PkbSet::from_env() else { return };
        let Ok(b) = set.read("FIELD/MPS/AP_02_U.MSC") else { return };
        let img = ScriptImage::parse(&b).unwrap();
        let calls = scan_calls(&img);
        assert!(calls.len() > 100);
        // every engine call is a CField (0xc2) command with a plausible id and argument count
        assert!(calls.iter().filter(|c| c.ex >= 0xbc).all(|c| c.ex == 0xc2 && c.sub < 0x90 && c.nargs < 16));
        // function 0 begins with SetMotion(0, 1, 0, 1) at code offset 0x0e (verified by hand against the byte stream)
        let first = calls.iter().find(|c| c.ip == 0x0e).unwrap();
        assert_eq!((first.sub, first.nargs), (0x10, 4));
        assert_eq!(first.args[..2], [Some(0), Some(1)]);
        assert!(calls.iter().any(|c| c.sub == 0x20 && c.ex == 0xc2), "map jump present");
    }
}
