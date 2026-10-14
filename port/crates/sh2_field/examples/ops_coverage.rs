//! Which `ex 0xc2` sub-ops does `FieldHost` handle?  Calls every id 0..=0xff with a dummy argument block and reports the ones that fall
//! through to the "not implemented" arm.
use sh2_field::host::FieldHost;
use sh2_field::pkb_compat::PkbSet;
use sh2_field::plugin::build_runtime;
use sh2_menu::session::GameSession;
use sh2_script::cscript::{ExCtx, ScriptHost};
use sh2_script::memory::{Memory, SEG_STACK};

fn main() {
    let set = PkbSet::from_env().unwrap();
    let mut session = GameSession::default();
    let mut rt = build_runtime(&set, None, "AP_02_U", 0, &session).unwrap();
    let mut missing = vec![];
    for sub in 0..=0xffu8 {
        let mut mem = Memory::default();
        mem.stack = vec![0; 0x1000];
        mem.data = vec![0; 0x100];
        let mut ctx = ExCtx { mem: &mut mem, args: SEG_STACK + 0x100, argc: 4, nargs: 4, event_id: 0 };
        let before: u64 = rt.st.unimplemented.values().sum();
        let mut host = FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(&mut session) };
        host.call_ex(&mut ctx, 0xc2, sub);
        let after: u64 = rt.st.unimplemented.values().sum();
        if after > before {
            missing.push(sub);
        }
    }
    println!("not implemented: {:02x?}", missing);
}
