//! VSM system-call table (`FuncTbl` at 0x003f89b0, 269 entries of {id, fn, kind}).
//!
//! The table has a single source of truth: [`sh2_script::opcodes::VEC_FUNC_TABLE`] (section E, generated from the
//! executable; it also records each handler's JP address).  This module re-exports it under the names section D used
//! (`SYSCALLS`, `SysEntry`, `SysCtx`) so the effect code and the script VM can never disagree about an id.
//!
//! `kind` (3rd field): `SysCtx::Core` = handler gets the `EffectCore` as context, `Thread` = the calling `VEC` thread,
//! `None` = no context.  The JP handler symbol is `<name>__FiiPPcPv`  (`int id, int argc, char **args, void *ctx`),
//! see [`jp_sym`].

pub use sh2_script::opcodes::{SysCtx, SysFunc as SysEntry, VEC_FUNC_TABLE as SYSCALLS};

pub fn lookup(id: u16) -> Option<&'static SysEntry> {
    SYSCALLS.iter().find(|e| e.id == id as i32)
}

/// Mangled JP symbol of a handler (`mdlCreate` -> `mdlCreate__FiiPPcPv`).
pub fn jp_sym(e: &SysEntry) -> String {
    format!("{}__FiiPPcPv", e.name)
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn table() {
        assert_eq!(SYSCALLS.len(), 269);
        assert_eq!(lookup(200).unwrap().name, "sysWaitSystem");
        assert_eq!(lookup(900).unwrap().name, "mdlCreate");
        assert!(lookup(1).is_some() && lookup(32000).is_some());
        assert_eq!(jp_sym(lookup(900).unwrap()), "mdlCreate__FiiPPcPv");
        assert_eq!(lookup(900).unwrap().ctx, SysCtx::Thread);
    }
}
