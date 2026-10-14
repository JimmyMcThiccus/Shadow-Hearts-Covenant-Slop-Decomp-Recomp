//! Opcode tables for the two script VMs of Shadow Hearts: Covenant.
//!
//! 1. **CScript** event-script VM (`CScript::JobExec/GetParameter/Expression/Statement`, JP 0x00291ba0..0x00298b80).
//!    Byte-coded RPN stack machine.  Used by field events (FIELD.PKB `.scr` images) and cutscene
//!    `LSCR` tracks inside LSD.PKB.  Opcode groups:
//!    * `0x00..=0x1f` operand pushes (see [`push`])
//!    * `0x20..=0x8f` expression operators (see [`expr`])
//!    * `0x90..=0x9f` statements / control flow (see [`stmt`])
//!    * `0xa0..=0xaf` built-in `ifc_*` functions (see [`ifc`])
//!    * `0xb0..=0xbb` unassigned (ExecFunc returns 0x10 = error)
//!    * `0xbc..=0xff` extension calls: *first byte* selects a `CScriptEx` object by id ([`ex`]),
//!      the *second byte* is the sub-function number, third byte is `nargs`.
//! 2. **VEC / VSM** effect-script VM (`VEC::DecodeVSM`, JP 0x002fc400).  Fixed 8-byte instructions
//!    `[op u8][fp_rel u8][pad u16][operand u32]`; opcodes in [`vsm`]; 269 system calls in [`VEC_FUNC_TABLE`].

// JP: 0x00294620 GetParameter__7CScriptFRPUc
/// Operand pushes.  The VM keeps a type shift-register (`type_bits`): bit0 = "top of stack is float".
pub mod push {
    pub const END_OF_PROGRAM: u8 = 0x00; // JobExec: script finished
    pub const STACK_RESET: u8 = 0x01; // sp = frame base (also used as an explicit NOP statement)
    pub const STR_EMPTY: u8 = 0x04; // push pointer to "" (NUL string)
    pub const IMM_M1: u8 = 0x05;
    pub const IMM_0: u8 = 0x06;
    pub const IMM_1: u8 = 0x07;
    pub const IMM_2: u8 = 0x08;
    pub const IMM_4: u8 = 0x09;
    pub const IMM_U8: u8 = 0x0a; // u8
    pub const IMM_NEG8: u8 = 0x0b; // u8 | 0xffffff00
    pub const IMM_U16: u8 = 0x0c; // u16
    pub const IMM_NEG16: u8 = 0x0d; // u16 | 0xffff0000
    pub const IMM_I32: u8 = 0x0e; // u32
    pub const IMM_F32: u8 = 0x0f; // u32 bits, marks top as float
    pub const REG8: u8 = 0x10; // u8 idx   -> push &regs8[idx]       (SafeGetFlagAddr type 0)
    pub const REG16: u8 = 0x11; // u8 idx   -> push &regs16[idx]      (type 2)
    pub const REG32: u8 = 0x12; // u8 idx   -> push &regs32[idx]      (type 4)
    pub const REGF32: u8 = 0x13; // u8 idx   -> as 0x12 but marks float
    pub const REGX: u8 = 0x14; // u16: type=hi4 (0/1:8bit 2/3:16bit 4/5:32bit), idx=lo12
    pub const ADDR_DATA: u8 = 0x15; // u16 off -> push data_base + off
    pub const ADDR_CODE: u8 = 0x16; // u16 off -> push code_base + off
    pub const ADDR_BSS: u8 = 0x18; // u16 off -> push bss_base + off
    pub const ADDR_LOCAL8: u8 = 0x19; // u8 byte offset into current arg/local block
    pub const ADDR_LOCAL32: u8 = 0x1a; // u16 word index into current arg/local block
    pub const CALL_USER: u8 = 0x1b; // u16 func code offset, u8 nargs  (EnterUFunc; function starts with u16 locals-size)
    pub const END_EXPR: u8 = 0x4f; // GetParameter returns -1 (end script)
}

// JP: 0x00295840 Expression__7CScriptFUiRPUc
/// Expression operators.  Binary ops pop 2 and push 1; "size ops" carry a `GetSize` operand
/// (1 byte, or 2 bytes when bit6 set): `b&0x80==0` -> size=1<<(b>>5), step=1; else size=4(ptr/float marker 8), step=(b&0x3f)[<<8|next].
pub mod expr {
    pub const LD_S8: u8 = 0x20;
    pub const LD_U8: u8 = 0x21;
    pub const LD_S16: u8 = 0x22;
    pub const LD_U16: u8 = 0x23;
    pub const LD_I32: u8 = 0x24;
    pub const LD_F32: u8 = 0x25; // marks float
    pub const ST_8: u8 = 0x26; // *(sp-2)=top ; result = value
    pub const ST_16: u8 = 0x27;
    pub const ST_32: u8 = 0x28;
    pub const ADR_CODE: u8 = 0x29; // top += code_base
    pub const ADR_DATA: u8 = 0x2a; // top += data_base
    pub const ADR_REG8: u8 = 0x2b; // top += regs
    pub const ADR_REG16: u8 = 0x2c; // regs + top*2
    pub const ADR_REG32: u8 = 0x2d; // regs + top*4
    pub const ADR_REG32B: u8 = 0x2e; // same as 0x2d
    pub const ADR_LOCAL: u8 = 0x2f; // top += local block base
    pub const SEXT8: u8 = 0x40;
    pub const ZEXT8: u8 = 0x41;
    pub const SEXT16: u8 = 0x42;
    pub const ZEXT16: u8 = 0x43;
    pub const F2I: u8 = 0x44;
    pub const I2F: u8 = 0x45; // top int->float, marks float
    pub const I2F_SECOND: u8 = 0x46; // element below top int->float (type bit1)
    pub const MARK_FLOAT: u8 = 0x47; // set float bit without converting
    pub const NOP: u8 = 0x48;
    pub const PRE_INC: u8 = 0x60; // [size op] *p += step ; result = new value
    pub const PRE_DEC: u8 = 0x61;
    pub const POST_INC: u8 = 0x62; // result = old value
    pub const POST_DEC: u8 = 0x63;
    pub const LNOT: u8 = 0x64;
    pub const BNOT: u8 = 0x65;
    pub const NEG: u8 = 0x66; // float aware
    pub const MUL: u8 = 0x67; // 0x67..=0x6b float aware via type bits
    pub const DIV: u8 = 0x68;
    pub const MOD: u8 = 0x69;
    pub const ADD: u8 = 0x6a;
    pub const SUB: u8 = 0x6b;
    pub const SHL: u8 = 0x6c;
    pub const SHR: u8 = 0x6d; // arithmetic
    pub const LT: u8 = 0x70;
    pub const GT: u8 = 0x71;
    pub const LE: u8 = 0x72;
    pub const GE: u8 = 0x73;
    pub const EQ: u8 = 0x74;
    pub const NE: u8 = 0x75;
    pub const AND: u8 = 0x76;
    pub const XOR: u8 = 0x77;
    pub const OR: u8 = 0x78;
    pub const LAND: u8 = 0x79;
    pub const LOR: u8 = 0x7a;
    // op-assign family: [size op]  *p = *p OP top; (size==8 selects float).  NOTE: the int path of 0x80 adds
    // (a + b*step) in the shipped code (apparent codegen quirk) while float path multiplies.
    pub const MUL_SET: u8 = 0x80;
    pub const DIV_SET: u8 = 0x81;
    pub const MOD_SET: u8 = 0x82;
    pub const ADD_SET: u8 = 0x83;
    pub const SUB_SET: u8 = 0x84;
    pub const SHL_SET: u8 = 0x85;
    pub const SHR_SET: u8 = 0x86;
    pub const AND_SET: u8 = 0x87;
    pub const XOR_SET: u8 = 0x88;
    pub const OR_SET: u8 = 0x89;
    // string/output builder
    pub const OUT_SET: u8 = 0x8a; // out_cursor = top
    pub const OUT_PUT: u8 = 0x8b; // u8 n: n<0x80 -> write n low bytes of top ; n>=0x80 -> memcpy (n&0x7f) bytes from *top
    pub const OUT_INLINE: u8 = 0x8c; // top = n bytes of inline data follow in the code stream (copied, ip += n)
    pub const OUT_SKIP: u8 = 0x8d; // u16: out_cursor += u16
    pub const INDEX_A: u8 = 0x8e; // pushes sp[-2] + sp[-3]*top
    pub const INDEX_B: u8 = 0x8f; // pushes sp[-3] + sp[-2]*top
}

// JP: 0x00294130 Statement__7CScriptFiRPUc
pub mod stmt {
    pub const JMP: u8 = 0x90; // u16 code offset
    pub const JZ: u8 = 0x91; // u16 target, pops cond, jumps if == 0
    pub const JNZ: u8 = 0x92; // u16 target, jumps if != 0
    /// u16 -> address of a switch table: `u16 hdr` (count=hdr&0xfff, key type=(hdr>>12)&7: 0=u8 1=u16 2=u32,
    /// 0x8000 = has default), then count x (key, u16 target), then optional u16 default target.
    pub const SWITCH: u8 = 0x94;
    pub const RET_VALUE: u8 = 0x98; // pop v; LeaveUFunc; push v
    pub const RET: u8 = 0x99; // LeaveUFunc (push 0 if returning from root frame)
}

// JP: 0x00297610 ExecFunc__7CScriptFiii
/// Built-in interface functions `ifc_*` (statement-visible calls).  Return conventions:
/// 0 = void (clear temporaries), 1 = int result in args[0], 2 = float result, 7 = restart at new ip (callEvent),
/// 0x10 = error, negative = suspend; the VM re-issues the call next tick with `nargs` = that negative token.
pub mod ifc {
    pub const CHAIN: u8 = 0xa0; // chain("next.scr") -> ends scene, schedules load of another script   JP 0x00297890
    pub const CALL_EVENT: u8 = 0xa1; // callEvent(id, args..) spawn event job in the same image           JP 0x00297930
    pub const CALL_EVENT_DLY: u8 = 0xa2; // callEventDly(delay_ms?, id, args..) queue delayed event      JP 0x002979f0
    pub const GET_SYS_INFO: u8 = 0xa3; // getSysInfo(n) -> 0 (stub)                                       JP 0x00297aa0
    pub const SET_FLAG: u8 = 0xa4; // setFlag(bit)                                                        JP 0x00297b00
    pub const CLR_FLAG: u8 = 0xa5; // clrFlag(bit)                                                        JP 0x00297ba0
    pub const CHK_FLAG: u8 = 0xa6; // chkFlag(bit) -> 0/1                                                 JP 0x00297c40
    pub const REG_CLR: u8 = 0xa7; // reg_clr(first, last, value)                                         JP 0x00297ce0
    pub const WAIT: u8 = 0xaa; // wait(frames) ; negative = -(units of 1/1000 frame-time)               JP 0x00297e10
    pub const SPRINTF: u8 = 0xab; // sprintf(dst, fmt, args..)                                          JP 0x00298170
    pub const GET_PAD: u8 = 0xac; // get_pad(mode, mask): 1=new press 2=repeat 3/4=consume else raw     JP 0x00297fc0
    pub const RANDOMIZE: u8 = 0xad; //                                                                   JP 0x002980a0
    pub const RND: u8 = 0xae; // rnd(n) -> 0..n-1 (n==0: raw)                                           JP 0x002980d0
    pub const DPRINTF: u8 = 0xaf; // debug print (stub in retail)                                       JP 0x00298150
}

/// `CScriptEx` ids == first opcode byte of an extension call.
pub mod ex {
    /// `LSDScrEx` (cutscene helper: fader, cine mask, vibration, images, BG motion).  JP LSDScrEx::CallFunc 0x003cd310
    pub const LSD: u8 = 0xc0;
    /// Unknown / battle script ex (id 0xc1 is not linked anywhere in main or FIELD.BIN).
    pub const BATTLE_RESERVED: u8 = 0xc1;
    /// `CField` (field engine: characters, camera, windows, BGM/SE, battles ...).  JP FIELD.BIN CField::CallFunc 0x004ac950
    pub const FIELD: u8 = 0xc2;
}

/// LSDScrEx sub-functions (`call ex=0xc0 sub=N`).  JP 0x003cd310.
pub const LSD_SUBOPS: &[(u8, &str, &str)] = &[
    (0x00, "SetFader", "(mode, time) -> CFieldSocket::SetFader(1, mode|.., time); mode bit0/2 select fade-in/out"),
    (0x01, "Nop1", ""),
    (0x02, "Nop2", ""),
    (0x03, "SetNextScript", "(char* name) store LSD chain name at +0x5c, flag +0x5a=1"),
    (0x04, "FadeBGM", "(time) CMusic::FadeBGM(0,time)"),
    (0x05, "CineMask", "(on) show/clear letterbox CineMask"),
    (0x06, "StartVib", "(id, char* name, flags) LSDScrEx::StartVib"),
    (0x07, "StopVib", "(id, flags)"),
    (0x08, "FadeVib", "(id, power, time)"),
    (0x09, "DspImage", "(id, char* name, x, y)"),
    (0x0a, "ClrImage", "(id, flags)"),
    (0x0b, "SetBGMotion", "(id, char* motion)"),
    (0x0c, "SetBGMotionI", "(id, char*, char*)"),
    (0x0d, "InvokeBattle", "MCESInvokeBattle()"),
    (0x0e, "BGEffectAlpha", "(id, alpha, time) CFieldBG::EffectAlpha"),
    (0x0f, "ExitLSD", "LSDPlayer::Pause(); LSDPlayer::Exit()"),
];

/// CField sub-functions (`call ex=0xc2 sub=N`, JP FIELD.BIN 0x004ac950).  Documented from the decompile;
/// owner of the semantics is section G.  `0x80..=0x8c` are vector-math ops (`VectorOperation`, 0x004b1590).
pub const FIELD_SUBOPS: &[(u8, &str)] = &[
    // names confirmed against `CField::CallFunc` (JP FIELD.BIN 0x004ac950, US 0x004f7fb0) and the handlers it calls; see
    // notes/integration/script_ops.md.  `// R` = retail (US) only.
    (0x00, "GetCharacterInfo"), (0x01, "SetCharacterInfo"), (0x02, "CharAddItem"), (0x03, "CharRemoveItem"),
    (0x04, "CharAddItemEx"), (0x05, "AttachFrame"), (0x06, "BgFog"), (0x07, "LoadCharacterByName"), (0x08, "LoadCharacter"),
    (0x09, "UnloadCharacter"), (0x0a, "DispCharacter"), (0x0b, "DispCharacterEP"), (0x0c, "ClrCharacter"),
    (0x0d, "SetMoveMotion"), (0x0e, "LoadMotion"), (0x0f, "UnloadMotion"), (0x10, "SetMotion"),
    (0x11, "SetMotionByName"), (0x12, "DispCharacterEPByName"), (0x14, "WaitModel"), (0x15, "SetMotionSpeed"),
    (0x16, "SetCharacterDir"), (0x17, "GetPos"), (0x18, "AutoMove"), (0x19, "PathMove"),
    (0x1a, "WaitCharacterEx"), (0x1b, "SetNpcSight"), (0x1c, "SetManual"), (0x1d, "SetViewPoint"), (0x1e, "SetViewPointEP"),
    (0x1f, "ClrViewPoint"), (0x20, "MapJump"), (0x21, "SetMapString"), (0x22, "AddLight"),
    (0x23, "SetFieldData"), (0x24, "GetFieldData"), (0x25, "SetBGMotion"), (0x26, "GetFramePos"),
    (0x27, "GetEntryPoint"), (0x28, "SetFader1"), (0x29, "SetFader0"), (0x2a, "SetBGMotionSpeed"), (0x2b, "SetLocationName"),
    (0x2c, "LoadImage"), (0x2d, "DspImage"), (0x2e, "ClrImage"), (0x2f, "EffectCmd"),
    (0x30, "CreateWindow"), (0x31, "SetActiveWindow"), (0x32, "SetWindowPos"), (0x33, "SetWindowSize"),
    (0x34, "OpenWindow"), (0x35, "CloseWindow"), (0x36, "OpenMessage"), (0x37, "ClearMessage"),
    (0x38, "KeyWait"), (0x39, "CreateName"), (0x3a, "SetActiveName"), (0x3b, "SetNamePos"),
    (0x3c, "OpenName"), (0x3d, "CloseName"),
    (0x40, "LoadFace"), (0x41, "ReleaseFace"), (0x42, "SetActiveFace"), (0x43, "SetFacePos"),
    (0x44, "SetFaceSize"), (0x45, "OpenFace"), (0x46, "CloseFace"),
    (0x48, "Select"), (0x49, "SelectInit"), (0x4a, "SelectAddItem"), (0x4b, "SelectWait"), (0x4c, "SelectInit2"), (0x4d, "InvokeCmdScene"),
    (0x4e, "TimerCreate"), (0x4f, "TimerControl"),
    (0x50, "LoadBgm"), (0x51, "PlayBgm"), (0x52, "BgmFade"), (0x53, "SetBgmVolume"), (0x54, "WaitBgm"),
    (0x55, "SetBattleBgm"), (0x56, "LoadSe"), (0x57, "UnloadSe"), (0x58, "PlaySe"), (0x59, "SetSeVolume"),
    (0x5a, "StopSe"), (0x5b, "WaitSe"), (0x5c, "SetObjSE"), (0x5d, "SetSoundData"), (0x5e, "PlayStreamBgm"),
    (0x5f, "PlaySeR"),
    (0x60, "StartEffect"), (0x61, "EffectControl"), (0x62, "MCES"), (0x63, "SetRing"), (0x64, "RingControl"),
    (0x65, "WarpPoint"), (0x66, "InventoryChange"), (0x67, "NaviItem"), (0x68, "CharacterEquip"), (0x69, "StartVib"),
    (0x6a, "StartVibSeq"), (0x6b, "VibStop"), (0x6c, "VibFade"), (0x6d, "VibRelease"), (0x6e, "VibQuery"),
    (0x6f, "DiskChange"),
    (0x70, "SetWorldMapPoint"), (0x71, "WorldMapJump"), (0x72, "InvokeBattle"), (0x73, "InvokeBattleTbl"),
    (0x74, "SetCameraA"), (0x75, "SetCameraB"), (0x76, "SetCameraC"), (0x77, "CamBlurFx"), (0x78, "RestoreCamera"),
    (0x79, "TreasureControl"), (0x7a, "SetLookPoint"), (0x7b, "ClrLookPoint"), (0x7c, "DspIcon"),
    (0x7d, "ParamChange"), (0x7e, "SavePoint"), (0x7f, "SpecialMenu"),
    (0x80, "vZero"), (0x81, "vCopy"), (0x82, "vNormalize"), (0x83, "vLength"), (0x84, "vAdd"), (0x85, "vSub"),
    (0x86, "vMul"), (0x87, "vScale"), (0x88, "vDivScale"), (0x89, "vDot"), (0x8a, "vCross"), (0x8b, "vRotY"),
    (0x8c, "vSet"),
];

/// VSM instruction opcodes (byte 0 of the 8-byte instruction), JP `VEC::DecodeVSM` 0x002fc400.
/// `byte1 != 0` => operand is frame-pointer relative (`operand += fp`).  Operand stack: array of 100 u32 at VEC+0x78, `sp` at +0x10.
pub mod vsm {
    pub const NOP: u8 = 0x00;
    pub const STB: u8 = 0x01; // dseg8[stk[sp-1]] = stk[sp]; sp-=1      (store through pointer)
    pub const STW: u8 = 0x02; // dseg32
    pub const STF: u8 = 0x03; // dseg32 (float)
    pub const ADD: u8 = 0x04;
    pub const ADDF: u8 = 0x05;
    pub const ADDI: u8 = 0x06; // stk[sp] += operand
    pub const SUB: u8 = 0x07;
    pub const SUBF: u8 = 0x08;
    pub const SUBI: u8 = 0x09;
    pub const MUL: u8 = 0x0a;
    pub const MULF: u8 = 0x0b;
    pub const MULI: u8 = 0x0c;
    pub const DIV: u8 = 0x0d; // error if divisor == 0 (prints, kills thread)
    pub const DIVF: u8 = 0x0e;
    pub const DIVI: u8 = 0x0f;
    pub const MOD: u8 = 0x10;
    pub const MODI: u8 = 0x12;
    pub const NEG: u8 = 0x13;
    pub const NEGF: u8 = 0x14;
    pub const CMP: u8 = 0x15; // stk[sp-1] = sign(stk[sp-1] - stk[sp]) as -1/0/1 ; sp-=1
    pub const CMPF: u8 = 0x16;
    pub const CMPI: u8 = 0x17; // stk[sp] = sign(stk[sp] vs operand)
    pub const DUP: u8 = 0x18;
    pub const LDB: u8 = 0x19; // push (i8)dseg[operand]
    pub const LDW: u8 = 0x1a; // push dseg32[operand]
    pub const LDF: u8 = 0x1b;
    pub const PUSHI: u8 = 0x1c; // push operand
    pub const LDB_IND: u8 = 0x1d; // stk[sp] = (i8)dseg[stk[sp]]
    pub const LDW_IND: u8 = 0x1e;
    pub const LDF_IND: u8 = 0x1f;
    pub const POP: u8 = 0x20;
    pub const STB_ABS: u8 = 0x21; // dseg8[operand] = stk[sp]; sp-=1
    pub const STW_ABS: u8 = 0x22;
    pub const STF_ABS: u8 = 0x23;
    pub const SETFP: u8 = 0x24; // fp = operand
    pub const ADDFP: u8 = 0x25; // fp += operand (error if > 40000)   (function prologue)
    pub const SUBFP: u8 = 0x26; // fp -= operand                       (epilogue)
    pub const I2F: u8 = 0x27;
    pub const F2I: u8 = 0x28;
    pub const JMP: u8 = 0x29;
    pub const JLT0: u8 = 0x2a; // pop; jump if < 0
    pub const JLE0: u8 = 0x2b;
    pub const JEQ0: u8 = 0x2c;
    pub const JNE0: u8 = 0x2d;
    pub const JGE0: u8 = 0x2e;
    pub const JGT0: u8 = 0x2f;
    pub const CALL: u8 = 0x30; // push ip; ip = operand
    pub const RET: u8 = 0x31; // ip = pop
    pub const END: u8 = 0x32; // thread state = 3 (done)
    pub const MEMCPY: u8 = 0x33; // pops (n, dst, src) byte copy within dseg
    pub const ALLOC: u8 = 0x34; // stk[sp] = new[](stk[sp]) - dseg_base
    pub const FREE: u8 = 0x35;
    pub const SCANF: u8 = 0x36;
    pub const POP2: u8 = 0x37;
    pub const POP1: u8 = 0x38;
    pub const SYSCALL: u8 = 0x39; // operand = (func_id << 16) | argc ; args set by SETARG
    pub const SETARG: u8 = 0x3a; // arg[operand] = dseg + stk[sp]; sp-=1   (operand<=20)
    pub const SPAWN: u8 = 0x3b; // operand = entry ip ; next instruction's operand = thread id/tag
    pub const EXIT: u8 = 0x3c; // RemoveThread()
    pub const WAIT_THREADS: u8 = 0x3d; // operand = tag ; yield until no thread with that tag
    pub const KILL_THREADS: u8 = 0x3e; // EffectCore::KillThread(operand)
}

/// Where a VEC system call gets its fourth argument from.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SysCtx {
    /// kind 0: the owning `EffectCore*` (VEC+0x230)
    Core,
    /// kind 1: the calling `VEC*` thread
    Thread,
    /// kind 2: null
    None,
}

/// One entry of the VEC (effect script) system-call registry `FuncTbl` (JP 0x003f89b0, 269 * 12 bytes).
/// Entry layout in the executable: `{ id: i32, handler: fn(i32 id, i32 argc, *mut *mut u8 args, *mut c_void ctx), ctx_kind: u8 }`.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct SysFunc { pub id: i32, pub name: &'static str, pub ctx: SysCtx, pub jp_addr: u32 }

pub static VEC_FUNC_TABLE: [SysFunc; 269] = [
    SysFunc { id: 0, name: "vecZeroVector", ctx: SysCtx::None, jp_addr: 0x003101d0 },
    SysFunc { id: 1, name: "vecNormalize", ctx: SysCtx::None, jp_addr: 0x00310220 },
    SysFunc { id: 2, name: "vecOuterProduct", ctx: SysCtx::None, jp_addr: 0x00310280 },
    SysFunc { id: 3, name: "vecInnerProduct", ctx: SysCtx::None, jp_addr: 0x00310300 },
    SysFunc { id: 4, name: "vecLength", ctx: SysCtx::None, jp_addr: 0x00310370 },
    SysFunc { id: 100, name: "matUnitMatrix", ctx: SysCtx::None, jp_addr: 0x003106b0 },
    SysFunc { id: 101, name: "matApplyMatrix", ctx: SysCtx::None, jp_addr: 0x003106f0 },
    SysFunc { id: 102, name: "matMulMatrix", ctx: SysCtx::None, jp_addr: 0x00310770 },
    SysFunc { id: 103, name: "matTransMatrix", ctx: SysCtx::None, jp_addr: 0x003107f0 },
    SysFunc { id: 104, name: "matRotXMatrix", ctx: SysCtx::None, jp_addr: 0x00310840 },
    SysFunc { id: 105, name: "matRotYMatrix", ctx: SysCtx::None, jp_addr: 0x00310890 },
    SysFunc { id: 106, name: "matRotZMatrix", ctx: SysCtx::None, jp_addr: 0x003108e0 },
    SysFunc { id: 107, name: "matRotMatrix", ctx: SysCtx::None, jp_addr: 0x00310930 },
    SysFunc { id: 108, name: "matTranspose", ctx: SysCtx::None, jp_addr: 0x00310980 },
    SysFunc { id: 109, name: "matInvers", ctx: SysCtx::None, jp_addr: 0x00310a10 },
    SysFunc { id: 110, name: "matGetAngle", ctx: SysCtx::None, jp_addr: 0x00310a70 },
    SysFunc { id: 200, name: "sysWaitSystem", ctx: SysCtx::Thread, jp_addr: 0x00310bd0 },
    SysFunc { id: 201, name: "sysGetTime", ctx: SysCtx::None, jp_addr: 0x00310c10 },
    SysFunc { id: 202, name: "sysSetTick", ctx: SysCtx::Thread, jp_addr: 0x00310c50 },
    SysFunc { id: 203, name: "sysGetTick", ctx: SysCtx::Thread, jp_addr: 0x00310c90 },
    SysFunc { id: 204, name: "sysSetAddTime", ctx: SysCtx::Thread, jp_addr: 0x00310cf0 },
    SysFunc { id: 205, name: "sysGetAddTime", ctx: SysCtx::Core, jp_addr: 0x00310d60 },
    SysFunc { id: 206, name: "sysCreateEffect", ctx: SysCtx::Thread, jp_addr: 0x00310dd0 },
    SysFunc { id: 207, name: "sysSetHandle", ctx: SysCtx::Core, jp_addr: 0x00310e60 },
    SysFunc { id: 208, name: "sysGetHandle", ctx: SysCtx::Core, jp_addr: 0x00310ef0 },
    SysFunc { id: 209, name: "sysWaitCreateEffect", ctx: SysCtx::Thread, jp_addr: 0x00310fe0 },
    SysFunc { id: 210, name: "sysStartEffect", ctx: SysCtx::Core, jp_addr: 0x00311020 },
    SysFunc { id: 211, name: "sysGetHandleCount", ctx: SysCtx::Core, jp_addr: 0x00310f70 },
    SysFunc { id: 250, name: "calRand", ctx: SysCtx::None, jp_addr: 0x003110d0 },
    SysFunc { id: 251, name: "calFRand", ctx: SysCtx::None, jp_addr: 0x00311140 },
    SysFunc { id: 252, name: "calSin", ctx: SysCtx::None, jp_addr: 0x003111b0 },
    SysFunc { id: 253, name: "calCos", ctx: SysCtx::None, jp_addr: 0x00311210 },
    SysFunc { id: 254, name: "calTan", ctx: SysCtx::None, jp_addr: 0x00311270 },
    SysFunc { id: 255, name: "calAsin", ctx: SysCtx::None, jp_addr: 0x003112d0 },
    SysFunc { id: 256, name: "calAcos", ctx: SysCtx::None, jp_addr: 0x00311320 },
    SysFunc { id: 257, name: "calAtan", ctx: SysCtx::None, jp_addr: 0x00311370 },
    SysFunc { id: 258, name: "calRad", ctx: SysCtx::None, jp_addr: 0x003113c0 },
    SysFunc { id: 259, name: "calSqrt", ctx: SysCtx::None, jp_addr: 0x00311410 },
    SysFunc { id: 300, name: "pgrCreate", ctx: SysCtx::Thread, jp_addr: 0x00317a50 },
    SysFunc { id: 301, name: "pgrSetTrans", ctx: SysCtx::Thread, jp_addr: 0x00317b10 },
    SysFunc { id: 302, name: "pgrSetRot", ctx: SysCtx::Thread, jp_addr: 0x00317bb0 },
    SysFunc { id: 303, name: "pgrSetMatrix", ctx: SysCtx::Thread, jp_addr: 0x00317c50 },
    SysFunc { id: 304, name: "pgrSetTexture", ctx: SysCtx::Thread, jp_addr: 0x00317cb0 },
    SysFunc { id: 305, name: "pgrSetTestReg", ctx: SysCtx::Thread, jp_addr: 0x00317d10 },
    SysFunc { id: 306, name: "pgrSetAlphaReg", ctx: SysCtx::Thread, jp_addr: 0x00317e10 },
    SysFunc { id: 307, name: "pgrShow", ctx: SysCtx::Thread, jp_addr: 0x00317ed0 },
    SysFunc { id: 308, name: "pgrSetLayer", ctx: SysCtx::Core, jp_addr: 0x00317f60 },
    SysFunc { id: 309, name: "pgrSetClampReg", ctx: SysCtx::Thread, jp_addr: 0x00317fd0 },
    SysFunc { id: 400, name: "polCreate3D", ctx: SysCtx::Thread, jp_addr: 0x00318fa0 },
    SysFunc { id: 401, name: "polCreateBB", ctx: SysCtx::Thread, jp_addr: 0x00319040 },
    SysFunc { id: 402, name: "polSetRot", ctx: SysCtx::Thread, jp_addr: 0x00319180 },
    SysFunc { id: 403, name: "polSetCenter", ctx: SysCtx::Thread, jp_addr: 0x00319210 },
    SysFunc { id: 404, name: "polSetVertex", ctx: SysCtx::Thread, jp_addr: 0x003192a0 },
    SysFunc { id: 405, name: "polSetSt", ctx: SysCtx::Thread, jp_addr: 0x00319310 },
    SysFunc { id: 406, name: "polSetColor", ctx: SysCtx::Thread, jp_addr: 0x003193a0 },
    SysFunc { id: 407, name: "polCreateDirect", ctx: SysCtx::Thread, jp_addr: 0x003190e0 },
    SysFunc { id: 408, name: "polDelete", ctx: SysCtx::Core, jp_addr: 0x00319450 },
    SysFunc { id: 900, name: "mdlCreate", ctx: SysCtx::Thread, jp_addr: 0x0030c480 },
    SysFunc { id: 901, name: "mdlShow", ctx: SysCtx::Thread, jp_addr: 0x0030c550 },
    SysFunc { id: 902, name: "mdlSetMotion", ctx: SysCtx::Thread, jp_addr: 0x0030c630 },
    SysFunc { id: 903, name: "mdlSetTrans", ctx: SysCtx::Thread, jp_addr: 0x0030c6f0 },
    SysFunc { id: 904, name: "mdlSetRot", ctx: SysCtx::Thread, jp_addr: 0x0030c7a0 },
    SysFunc { id: 905, name: "mdlSetScale", ctx: SysCtx::Thread, jp_addr: 0x0030c8b0 },
    SysFunc { id: 906, name: "mdlDelete", ctx: SysCtx::Thread, jp_addr: 0x0030c980 },
    SysFunc { id: 907, name: "mdlAttach", ctx: SysCtx::Thread, jp_addr: 0x0030ca20 },
    SysFunc { id: 908, name: "mdlDetach", ctx: SysCtx::Thread, jp_addr: 0x0030cb70 },
    SysFunc { id: 909, name: "mdlSetTestReg", ctx: SysCtx::Thread, jp_addr: 0x0030d220 },
    SysFunc { id: 910, name: "mdlClone", ctx: SysCtx::Thread, jp_addr: 0x0030d390 },
    SysFunc { id: 911, name: "mdlSetAlphaWeight", ctx: SysCtx::Thread, jp_addr: 0x0030d420 },
    SysFunc { id: 912, name: "mdlSetDrawLayer", ctx: SysCtx::Thread, jp_addr: 0x0030d540 },
    SysFunc { id: 913, name: "mdlSetOffsetRotTrans", ctx: SysCtx::Thread, jp_addr: 0x0030d640 },
    SysFunc { id: 914, name: "mdlSetAutoDelete", ctx: SysCtx::Thread, jp_addr: 0x0030d970 },
    SysFunc { id: 915, name: "mdlWaitMotion", ctx: SysCtx::Thread, jp_addr: 0x0030da00 },
    SysFunc { id: 916, name: "mdlManyDelete", ctx: SysCtx::Thread, jp_addr: 0x0030db80 },
    SysFunc { id: 917, name: "mdlWaitMotionFrame", ctx: SysCtx::Thread, jp_addr: 0x0030da80 },
    SysFunc { id: 918, name: "mdlCreateMemory", ctx: SysCtx::Thread, jp_addr: 0x0030dbf0 },
    SysFunc { id: 919, name: "mdlCreateMotion", ctx: SysCtx::Core, jp_addr: 0x0030ddf0 },
    SysFunc { id: 920, name: "mdlSetTransCallbackMode", ctx: SysCtx::Core, jp_addr: 0x0030deb0 },
    SysFunc { id: 921, name: "mdlAttach2", ctx: SysCtx::Core, jp_addr: 0x0030cbe0 },
    SysFunc { id: 922, name: "mdlDetach2", ctx: SysCtx::Core, jp_addr: 0x0030cd10 },
    SysFunc { id: 923, name: "mdlAttach3", ctx: SysCtx::Core, jp_addr: 0x0030cd80 },
    SysFunc { id: 924, name: "mdlDetach3", ctx: SysCtx::Core, jp_addr: 0x0030cf30 },
    SysFunc { id: 925, name: "mdlCreateShadow", ctx: SysCtx::Core, jp_addr: 0x0030df40 },
    SysFunc { id: 926, name: "mdlAttach4", ctx: SysCtx::Core, jp_addr: 0x0030d010 },
    SysFunc { id: 927, name: "mdlDetach4", ctx: SysCtx::Core, jp_addr: 0x0030d1b0 },
    SysFunc { id: 928, name: "mdlSetDrawLayerDirect", ctx: SysCtx::Core, jp_addr: 0x0030e000 },
    SysFunc { id: 1000, name: "cusCreate", ctx: SysCtx::Thread, jp_addr: 0x00311460 },
    SysFunc { id: 1001, name: "cusShow", ctx: SysCtx::Thread, jp_addr: 0x00311550 },
    SysFunc { id: 1100, name: "btlStatusRecovery", ctx: SysCtx::Thread, jp_addr: 0x00311610 },
    SysFunc { id: 1101, name: "btlIdelMotionReset", ctx: SysCtx::Thread, jp_addr: 0x00311740 },
    SysFunc { id: 1102, name: "btlCameraControlStatus", ctx: SysCtx::Core, jp_addr: 0x003117d0 },
    SysFunc { id: 1103, name: "btlGetCharno", ctx: SysCtx::Thread, jp_addr: 0x00311850 },
    SysFunc { id: 1104, name: "btlBeginMagicEffectClear", ctx: SysCtx::Thread, jp_addr: 0x003118f0 },
    SysFunc { id: 1105, name: "btlMagicMotionEndSet", ctx: SysCtx::Thread, jp_addr: 0x00311980 },
    SysFunc { id: 1106, name: "btlEffectDamageSet", ctx: SysCtx::Thread, jp_addr: 0x00311a10 },
    SysFunc { id: 1107, name: "btlGetCharBBoxSize", ctx: SysCtx::Thread, jp_addr: 0x00311bb0 },
    SysFunc { id: 1108, name: "btlChangeBattleBG", ctx: SysCtx::Thread, jp_addr: 0x00311d20 },
    SysFunc { id: 1109, name: "btlChangeFusionModel", ctx: SysCtx::None, jp_addr: 0x00311e20 },
    SysFunc { id: 1110, name: "btlComboStopOff", ctx: SysCtx::Core, jp_addr: 0x00311e80 },
    SysFunc { id: 1111, name: "btlCharactorShow", ctx: SysCtx::Core, jp_addr: 0x00311f20 },
    SysFunc { id: 1112, name: "btlGetFusionCharactor", ctx: SysCtx::None, jp_addr: 0x00312020 },
    SysFunc { id: 1113, name: "btlMagicStartEffectCall", ctx: SysCtx::Thread, jp_addr: 0x00312070 },
    SysFunc { id: 1114, name: "btlBattleBGShow", ctx: SysCtx::Thread, jp_addr: 0x00312100 },
    SysFunc { id: 1115, name: "btlHitMarkEffectCall", ctx: SysCtx::Thread, jp_addr: 0x00312160 },
    SysFunc { id: 1116, name: "btlBGShowParts", ctx: SysCtx::Core, jp_addr: 0x00312210 },
    SysFunc { id: 1117, name: "btlCharacterPushMode", ctx: SysCtx::Core, jp_addr: 0x00312280 },
    SysFunc { id: 1118, name: "btlGetWarpPos", ctx: SysCtx::Core, jp_addr: 0x00312330 },
    SysFunc { id: 1119, name: "btlCharacterTargetMove", ctx: SysCtx::Core, jp_addr: 0x00312400 },
    SysFunc { id: 1120, name: "btlGetWeponWorldPos", ctx: SysCtx::Core, jp_addr: 0x00312520 },
    SysFunc { id: 1121, name: "btlGetWeponWorldRot", ctx: SysCtx::Core, jp_addr: 0x003126f0 },
    SysFunc { id: 1122, name: "btlSetForceDeath", ctx: SysCtx::Core, jp_addr: 0x003128c0 },
    SysFunc { id: 1123, name: "btlSetCharacterWallHitMode", ctx: SysCtx::Core, jp_addr: 0x00312950 },
    SysFunc { id: 1124, name: "btlMagicStartEffectCall2", ctx: SysCtx::None, jp_addr: 0x00312a20 },
    SysFunc { id: 1125, name: "btlBeginMagicEffectClear2", ctx: SysCtx::None, jp_addr: 0x00312ac0 },
    SysFunc { id: 1126, name: "btlSetWait", ctx: SysCtx::Thread, jp_addr: 0x00312b00 },
    SysFunc { id: 1127, name: "btlGetWait", ctx: SysCtx::Thread, jp_addr: 0x00312b40 },
    SysFunc { id: 1128, name: "btlSetTargetAngle", ctx: SysCtx::Core, jp_addr: 0x00312bb0 },
    SysFunc { id: 1129, name: "btlGetModelNo", ctx: SysCtx::Core, jp_addr: 0x00312e80 },
    SysFunc { id: 1130, name: "btlStatusRecovery2", ctx: SysCtx::Core, jp_addr: 0x003116a0 },
    SysFunc { id: 1131, name: "btlSetWeponModel", ctx: SysCtx::Core, jp_addr: 0x00312f30 },
    SysFunc { id: 1132, name: "btlSetBGMParam", ctx: SysCtx::None, jp_addr: 0x003130b0 },
    SysFunc { id: 1133, name: "btlBattleCheck", ctx: SysCtx::None, jp_addr: 0x00313130 },
    SysFunc { id: 1200, name: "camCreate", ctx: SysCtx::Thread, jp_addr: 0x0030f4e0 },
    SysFunc { id: 1201, name: "camPlay", ctx: SysCtx::Thread, jp_addr: 0x0030f620 },
    SysFunc { id: 1202, name: "camStop", ctx: SysCtx::Thread, jp_addr: 0x0030f780 },
    SysFunc { id: 1203, name: "camSetMode", ctx: SysCtx::Thread, jp_addr: 0x0030f820 },
    SysFunc { id: 1204, name: "camPlay2", ctx: SysCtx::Thread, jp_addr: 0x0030f8c0 },
    SysFunc { id: 1205, name: "camGetMatrix", ctx: SysCtx::Thread, jp_addr: 0x0030fdd0 },
    SysFunc { id: 1206, name: "camSetFogColor", ctx: SysCtx::Thread, jp_addr: 0x0030fb70 },
    SysFunc { id: 1207, name: "camSetFogParam", ctx: SysCtx::Thread, jp_addr: 0x0030fd70 },
    SysFunc { id: 1209, name: "camSetFogOriginal", ctx: SysCtx::Thread, jp_addr: 0x0030fe90 },
    SysFunc { id: 1210, name: "camCreateVector", ctx: SysCtx::Thread, jp_addr: 0x0030f550 },
    SysFunc { id: 1211, name: "camSetVectorPos", ctx: SysCtx::Thread, jp_addr: 0x0030ff00 },
    SysFunc { id: 1212, name: "camSetVectorHight", ctx: SysCtx::Thread, jp_addr: 0x0030ff80 },
    SysFunc { id: 1213, name: "camSetVibPower", ctx: SysCtx::Core, jp_addr: 0x00310000 },
    SysFunc { id: 1214, name: "camSetVibParam", ctx: SysCtx::Core, jp_addr: 0x00310110 },
    SysFunc { id: 1215, name: "camPlay3", ctx: SysCtx::Core, jp_addr: 0x0030fa30 },
    SysFunc { id: 1300, name: "hitCreateCylinder", ctx: SysCtx::Thread, jp_addr: 0x0030e0e0 },
    SysFunc { id: 1302, name: "hitIsEndCylinder", ctx: SysCtx::Thread, jp_addr: 0x0030e260 },
    SysFunc { id: 1303, name: "hitIsModelCylinderHit", ctx: SysCtx::Thread, jp_addr: 0x0030e2f0 },
    SysFunc { id: 1304, name: "hitCreateShot", ctx: SysCtx::Thread, jp_addr: 0x0030e8c0 },
    SysFunc { id: 1305, name: "hitIsEndShot", ctx: SysCtx::Thread, jp_addr: 0x0030e960 },
    SysFunc { id: 1306, name: "hitIsModelShotHit", ctx: SysCtx::Thread, jp_addr: 0x0030e9e0 },
    SysFunc { id: 1307, name: "hitResetHitMark", ctx: SysCtx::Thread, jp_addr: 0x0030f040 },
    SysFunc { id: 1308, name: "hitGetShotEndPos", ctx: SysCtx::Core, jp_addr: 0x0030ee20 },
    SysFunc { id: 1310, name: "hitSetShotUpdateMode", ctx: SysCtx::Core, jp_addr: 0x0030ee90 },
    SysFunc { id: 1311, name: "hitAddShotKey", ctx: SysCtx::Core, jp_addr: 0x0030ef00 },
    SysFunc { id: 1312, name: "hitSetShotEndMode", ctx: SysCtx::Core, jp_addr: 0x0030f0d0 },
    SysFunc { id: 1313, name: "hitCreateCylinder2", ctx: SysCtx::Core, jp_addr: 0x0030e160 },
    SysFunc { id: 1314, name: "hitDeleteCylinder", ctx: SysCtx::Core, jp_addr: 0x0030e1e0 },
    SysFunc { id: 1315, name: "hitGetShotHitFrame", ctx: SysCtx::Thread, jp_addr: 0x0030f140 },
    SysFunc { id: 1400, name: "chrGetTrans", ctx: SysCtx::Thread, jp_addr: 0x0031b3b0 },
    SysFunc { id: 1401, name: "chrGetGTCount", ctx: SysCtx::Thread, jp_addr: 0x0031b470 },
    SysFunc { id: 1402, name: "chrGetRootMatrix", ctx: SysCtx::Thread, jp_addr: 0x0031b510 },
    SysFunc { id: 1403, name: "chrCreateMotion", ctx: SysCtx::Thread, jp_addr: 0x0031b5c0 },
    SysFunc { id: 1404, name: "chrSetMotion", ctx: SysCtx::Thread, jp_addr: 0x0031b6b0 },
    SysFunc { id: 1405, name: "chrSetRootMatrix", ctx: SysCtx::Core, jp_addr: 0x0031b7b0 },
    SysFunc { id: 1406, name: "chrCreateWeponMotion", ctx: SysCtx::Core, jp_addr: 0x0031b860 },
    SysFunc { id: 1407, name: "chrSetWeponMotion", ctx: SysCtx::Core, jp_addr: 0x0031b930 },
    SysFunc { id: 1408, name: "chrDynaReset", ctx: SysCtx::Core, jp_addr: 0x0031ba10 },
    SysFunc { id: 1500, name: "colGetLightColor", ctx: SysCtx::None, jp_addr: 0x003131a0 },
    SysFunc { id: 1501, name: "colSetLightColor", ctx: SysCtx::None, jp_addr: 0x003132e0 },
    SysFunc { id: 1600, name: "sprCreate", ctx: SysCtx::Thread, jp_addr: 0x00313400 },
    SysFunc { id: 1601, name: "sprShow", ctx: SysCtx::Thread, jp_addr: 0x003134b0 },
    SysFunc { id: 1602, name: "sprSetColor", ctx: SysCtx::Thread, jp_addr: 0x003135a0 },
    SysFunc { id: 1603, name: "sprDelete", ctx: SysCtx::Thread, jp_addr: 0x00313630 },
    SysFunc { id: 1604, name: "sprSetZ", ctx: SysCtx::Thread, jp_addr: 0x003136d0 },
    SysFunc { id: 1605, name: "sprSetTestReg", ctx: SysCtx::Thread, jp_addr: 0x00313760 },
    SysFunc { id: 1606, name: "sprSetAlphaReg", ctx: SysCtx::Thread, jp_addr: 0x003138f0 },
    SysFunc { id: 1700, name: "shrGetModelColor", ctx: SysCtx::Thread, jp_addr: 0x003149e0 },
    SysFunc { id: 1701, name: "shrSetModelColor", ctx: SysCtx::Thread, jp_addr: 0x00314b20 },
    SysFunc { id: 1702, name: "shrStartModelColorFader", ctx: SysCtx::Thread, jp_addr: 0x00314c50 },
    SysFunc { id: 1704, name: "shrSetModelRootMatrix", ctx: SysCtx::Thread, jp_addr: 0x00314fa0 },
    SysFunc { id: 1705, name: "shrGetModelRootMatrix", ctx: SysCtx::Thread, jp_addr: 0x00315100 },
    SysFunc { id: 1706, name: "shrGetWorldPos", ctx: SysCtx::Thread, jp_addr: 0x00315230 },
    SysFunc { id: 1707, name: "shrGetWorldRot", ctx: SysCtx::Thread, jp_addr: 0x003153c0 },
    SysFunc { id: 1708, name: "shrGetBackColor", ctx: SysCtx::None, jp_addr: 0x00315550 },
    SysFunc { id: 1709, name: "shrSetBackColor", ctx: SysCtx::None, jp_addr: 0x003156d0 },
    SysFunc { id: 1710, name: "shrSetNextMotion", ctx: SysCtx::Core, jp_addr: 0x00315860 },
    SysFunc { id: 1711, name: "shrStartModelAlphaFader", ctx: SysCtx::Core, jp_addr: 0x00314df0 },
    SysFunc { id: 1800, name: "quaGetQuat", ctx: SysCtx::None, jp_addr: 0x00315950 },
    SysFunc { id: 1801, name: "quaSlerp", ctx: SysCtx::None, jp_addr: 0x003159c0 },
    SysFunc { id: 1802, name: "quaGetMatrix", ctx: SysCtx::None, jp_addr: 0x00315a40 },
    SysFunc { id: 1900, name: "lgtCreate", ctx: SysCtx::Thread, jp_addr: 0x0031a040 },
    SysFunc { id: 1901, name: "lgtShow", ctx: SysCtx::Thread, jp_addr: 0x0031a0f0 },
    SysFunc { id: 1902, name: "lgtAttach", ctx: SysCtx::Thread, jp_addr: 0x0031a190 },
    SysFunc { id: 1903, name: "lgtSetOffset", ctx: SysCtx::Thread, jp_addr: 0x0031a2e0 },
    SysFunc { id: 1904, name: "lgtDelete", ctx: SysCtx::Core, jp_addr: 0x0031a370 },
    SysFunc { id: 2000, name: "sseLoadSe", ctx: SysCtx::Thread, jp_addr: 0x0031a440 },
    SysFunc { id: 2001, name: "sseUnloadSe", ctx: SysCtx::Thread, jp_addr: 0x0031a4c0 },
    SysFunc { id: 2002, name: "ssePlaySe", ctx: SysCtx::Thread, jp_addr: 0x0031a530 },
    SysFunc { id: 2003, name: "sseGetSysSe", ctx: SysCtx::Thread, jp_addr: 0x0031a630 },
    SysFunc { id: 2004, name: "ssePlayLoopSe", ctx: SysCtx::Thread, jp_addr: 0x0031a6f0 },
    SysFunc { id: 2005, name: "sseStopLoopSe", ctx: SysCtx::Thread, jp_addr: 0x0031a7e0 },
    SysFunc { id: 2006, name: "sseWaitLoadSe", ctx: SysCtx::Thread, jp_addr: 0x0031a8b0 },
    SysFunc { id: 2100, name: "blrCreate", ctx: SysCtx::Thread, jp_addr: 0x0031c590 },
    SysFunc { id: 2101, name: "blrShow", ctx: SysCtx::Thread, jp_addr: 0x0031c600 },
    SysFunc { id: 2102, name: "blrSetAlpha", ctx: SysCtx::Thread, jp_addr: 0x0031c6e0 },
    SysFunc { id: 2103, name: "blrDelete", ctx: SysCtx::Thread, jp_addr: 0x0031c770 },
    SysFunc { id: 2104, name: "blrSetUv", ctx: SysCtx::Thread, jp_addr: 0x0031c810 },
    SysFunc { id: 2106, name: "blrSetColor", ctx: SysCtx::Thread, jp_addr: 0x0031c910 },
    SysFunc { id: 2107, name: "blrCreateLine", ctx: SysCtx::Core, jp_addr: 0x0031c9f0 },
    SysFunc { id: 2108, name: "blrShowLine", ctx: SysCtx::Core, jp_addr: 0x0031cbb0 },
    SysFunc { id: 2109, name: "blrSetLinePower", ctx: SysCtx::Core, jp_addr: 0x0031cca0 },
    SysFunc { id: 2110, name: "blrSetLineCenter", ctx: SysCtx::Core, jp_addr: 0x0031cd40 },
    SysFunc { id: 2111, name: "blrDeleteLine", ctx: SysCtx::Core, jp_addr: 0x0031cdf0 },
    SysFunc { id: 2112, name: "blrSetLineRect", ctx: SysCtx::Core, jp_addr: 0x0031cea0 },
    SysFunc { id: 2200, name: "pphCreate", ctx: SysCtx::Core, jp_addr: 0x0031cf80 },
    SysFunc { id: 2201, name: "pphDelete", ctx: SysCtx::Core, jp_addr: 0x0031d080 },
    SysFunc { id: 2202, name: "pphShow", ctx: SysCtx::Core, jp_addr: 0x0031d120 },
    SysFunc { id: 2203, name: "pphAddPath", ctx: SysCtx::Core, jp_addr: 0x0031d250 },
    SysFunc { id: 2204, name: "pphAddColorKey", ctx: SysCtx::Core, jp_addr: 0x0031d2f0 },
    SysFunc { id: 2205, name: "pphSetTestReg", ctx: SysCtx::Core, jp_addr: 0x0031d3a0 },
    SysFunc { id: 2206, name: "pphSetAlphaReg", ctx: SysCtx::Core, jp_addr: 0x0031d4c0 },
    SysFunc { id: 2207, name: "pphCreateTexture", ctx: SysCtx::Core, jp_addr: 0x0031d5b0 },
    SysFunc { id: 2208, name: "pphAddStKey", ctx: SysCtx::Core, jp_addr: 0x0031d660 },
    SysFunc { id: 2300, name: "fldGetPos", ctx: SysCtx::Core, jp_addr: 0x0031f330 },
    SysFunc { id: 2301, name: "fldGetGTCount", ctx: SysCtx::Core, jp_addr: 0x0031f3f0 },
    SysFunc { id: 2302, name: "fldAttachBG", ctx: SysCtx::Core, jp_addr: 0x0031f480 },
    SysFunc { id: 2303, name: "fldAttachBG2", ctx: SysCtx::Core, jp_addr: 0x0031f560 },
    SysFunc { id: 2400, name: "gnyCreate", ctx: SysCtx::Core, jp_addr: 0x0031f640 },
    SysFunc { id: 2401, name: "gnyDelete", ctx: SysCtx::Core, jp_addr: 0x0031f6f0 },
    SysFunc { id: 2402, name: "gnyShow", ctx: SysCtx::Core, jp_addr: 0x0031f7a0 },
    SysFunc { id: 2403, name: "gnyAddRotKey", ctx: SysCtx::Core, jp_addr: 0x0031f8c0 },
    SysFunc { id: 2500, name: "bngCreate", ctx: SysCtx::Core, jp_addr: 0x003227b0 },
    SysFunc { id: 2501, name: "bngDelete", ctx: SysCtx::Core, jp_addr: 0x00322a30 },
    SysFunc { id: 2502, name: "bngShow", ctx: SysCtx::Core, jp_addr: 0x00322ab0 },
    SysFunc { id: 2503, name: "bngSetBackColor", ctx: SysCtx::Core, jp_addr: 0x00322bc0 },
    SysFunc { id: 2504, name: "bngCreateUser", ctx: SysCtx::Core, jp_addr: 0x003229b0 },
    SysFunc { id: 2505, name: "bngAddPolygon", ctx: SysCtx::Core, jp_addr: 0x00322be0 },
    SysFunc { id: 2506, name: "bngSetPolTrans", ctx: SysCtx::Core, jp_addr: 0x00322db0 },
    SysFunc { id: 2507, name: "bngSetPolRot", ctx: SysCtx::Core, jp_addr: 0x00322e50 },
    SysFunc { id: 2508, name: "bngSetPolScale", ctx: SysCtx::Core, jp_addr: 0x00322ec0 },
    SysFunc { id: 2600, name: "strStrCopy", ctx: SysCtx::None, jp_addr: 0x00323f40 },
    SysFunc { id: 2601, name: "strStrNCopy", ctx: SysCtx::None, jp_addr: 0x00323f90 },
    SysFunc { id: 2700, name: "pthCreate", ctx: SysCtx::Core, jp_addr: 0x00324000 },
    SysFunc { id: 2701, name: "pthDelete", ctx: SysCtx::Core, jp_addr: 0x00324100 },
    SysFunc { id: 2702, name: "pthAddPath", ctx: SysCtx::Core, jp_addr: 0x003241a0 },
    SysFunc { id: 2703, name: "pthGetPath", ctx: SysCtx::Core, jp_addr: 0x00324240 },
    SysFunc { id: 2704, name: "pthAddTime", ctx: SysCtx::Core, jp_addr: 0x00324350 },
    SysFunc { id: 2800, name: "bfdSetMode", ctx: SysCtx::None, jp_addr: 0x003246d0 },
    SysFunc { id: 2801, name: "bfdSetAlphaMode", ctx: SysCtx::None, jp_addr: 0x00324890 },
    SysFunc { id: 2802, name: "bfdSetColor", ctx: SysCtx::None, jp_addr: 0x00324970 },
    SysFunc { id: 2900, name: "lsdGetModel", ctx: SysCtx::Core, jp_addr: 0x003250a0 },
    SysFunc { id: 2901, name: "lsdAttach", ctx: SysCtx::Core, jp_addr: 0x00325100 },
    SysFunc { id: 2902, name: "lsdDetach", ctx: SysCtx::Core, jp_addr: 0x003251d0 },
    SysFunc { id: 3000, name: "fefCreateSmoke", ctx: SysCtx::Core, jp_addr: 0x00325240 },
    SysFunc { id: 3001, name: "fefDelete", ctx: SysCtx::Core, jp_addr: 0x00326550 },
    SysFunc { id: 3002, name: "fefSetLayer", ctx: SysCtx::Core, jp_addr: 0x003265e0 },
    SysFunc { id: 3003, name: "fefSetZTest", ctx: SysCtx::Core, jp_addr: 0x00326670 },
    SysFunc { id: 3004, name: "fefSetAlphaPower", ctx: SysCtx::Core, jp_addr: 0x00326710 },
    SysFunc { id: 3005, name: "fefSetPos", ctx: SysCtx::Core, jp_addr: 0x003267a0 },
    SysFunc { id: 3006, name: "fefCreateFlare", ctx: SysCtx::Core, jp_addr: 0x00325940 },
    SysFunc { id: 3007, name: "fefCreateThunder", ctx: SysCtx::Core, jp_addr: 0x00325ee0 },
    SysFunc { id: 3100, name: "padGetKeyPress", ctx: SysCtx::None, jp_addr: 0x003243d0 },
    SysFunc { id: 3200, name: "vibCreate", ctx: SysCtx::Core, jp_addr: 0x00327700 },
    SysFunc { id: 3201, name: "vibStart", ctx: SysCtx::Core, jp_addr: 0x003277f0 },
    SysFunc { id: 3202, name: "vibStop", ctx: SysCtx::Core, jp_addr: 0x00327990 },
    SysFunc { id: 3203, name: "vibDelete", ctx: SysCtx::Core, jp_addr: 0x00327a10 },
    SysFunc { id: 3204, name: "vibSetFade", ctx: SysCtx::Core, jp_addr: 0x00327ac0 },
    SysFunc { id: 3205, name: "vibSetVolume", ctx: SysCtx::Core, jp_addr: 0x00327b80 },
    SysFunc { id: 3206, name: "vibStart2", ctx: SysCtx::Core, jp_addr: 0x003278a0 },
    SysFunc { id: 3300, name: "sbgCreate", ctx: SysCtx::Core, jp_addr: 0x00327c10 },
    SysFunc { id: 3301, name: "sbgPlay", ctx: SysCtx::Core, jp_addr: 0x00327cd0 },
    SysFunc { id: 3302, name: "sbgStop", ctx: SysCtx::Core, jp_addr: 0x00327d20 },
    SysFunc { id: 3303, name: "sbgDelete", ctx: SysCtx::Core, jp_addr: 0x00327d90 },
    SysFunc { id: 3304, name: "sbgSetVolume", ctx: SysCtx::Core, jp_addr: 0x00327e10 },
    SysFunc { id: 3305, name: "sbgGetReady", ctx: SysCtx::Core, jp_addr: 0x00327e80 },
    SysFunc { id: 32000, name: "xxxCall", ctx: SysCtx::Thread, jp_addr: 0x0031b390 },
];

/// The 17 VEC system calls that exist only in the retail (US) `FuncTbl` (`SLUS_210.41` 0x0042d8e0, 286 entries = the 269 ids above + these;
/// the table is `{ id, handler, ctx_kind }`, 12 bytes per entry).  `jp_addr` holds the **US** handler address; every one of them takes the
/// `EffectCore` as context (kind 0).  Names follow the Ghidra project (`<group>Retail<id>__FiiPPcPv`); the behaviour (decompiled in pass E1,
/// `notes/integration/effects_e1.md`) is given per entry:
///
/// | id | US address | behaviour |
/// |---|---|---|
/// | 212 | 0x00347c40 | `sysGetUserA(idx, &out)`: `*out = core.user_a[idx]` (`core + 0x188 + idx * 4`, 32 shared script variables) |
/// | 213 | 0x00347ca0 | `sysGetUserB(idx, &out)`: `*out = core.user_b[idx]` (`core + 0x208 + idx * 4`) |
/// | 214 | 0x00347d10 | `sysSetUserA(idx, value)` |
/// | 215 | 0x00347d70 | `sysSetUserB(idx, value)` |
/// | 929 | 0x003448c0 | `mdlSetVector(model, FVector)`: `FindWorkModel(model) + 0x520 = vec` (extra per-model vector) |
/// | 930 | 0x00344980 | `mdlVirtual2c(model, f32)`: calls the model's vtable slot `+0x2c` with the float |
/// | 1134 | 0x00349f60 | `btlSetForceRemove(side, idx)`: `Retail_SetForceRemove(chr)` (character leaves the stage) |
/// | 1135 | 0x003484c0 | `btlIdleMotionReset(side, idx, mode)`: `IdelMotionReset(chr, mode)` |
/// | 1216 | 0x00346d10 | `camClearFlag()`: `core + 0x6b8 = 0` |
/// | 1712 | 0x0034ca40 | `shrGetMotionEndTime(kind, model, motion name, &frames)`: `getSequenceEndTime(model, 0, name) * 30` |
/// | 1713 | 0x0034bee0 | `shrCreateModelFader(kind, model, &alpha, &secs)`: `new ModelFader(model, FVector(0,0,0,alpha), secs, 2, set)` |
/// | 2705 | 0x0035b490 | `pthGetCount(path, &n)`: number of path points |
/// | 2706 | 0x0035b510 | `pthGetLength(path, idx, &len)`: segment length (`points[idx * 0x30 + 0x20]`) |
/// | 2707 | 0x0035b5b0 | `pthSample(path, step, n, init, &out[n])`: fill `out[]` with positions every `step` length units along the path |
/// | 3008 | 0x0035e3b0 | `fefSetPos2(handle, FVector)`: moves a created F-particle (`stub_fefRetail3008` -> `SetPos1`) |
/// | 3009 | 0x0035e4a0 | `fefSetActive(handle, on)`: F-particle vtable slot `+0x50` |
/// | 3010 | 0x0035d990 | `fefCreateTorch(pos, col1, col2, col3, size, &handle)`: builds an `FpTorch` (`CreateFromParam`) |
pub static VEC_RETAIL_FUNCS: [SysFunc; 17] = [
    SysFunc { id: 212, name: "sysRetail212", ctx: SysCtx::Core, jp_addr: 0x00347c40 },
    SysFunc { id: 213, name: "sysRetail213", ctx: SysCtx::Core, jp_addr: 0x00347ca0 },
    SysFunc { id: 214, name: "sysRetail214", ctx: SysCtx::Core, jp_addr: 0x00347d10 },
    SysFunc { id: 215, name: "sysRetail215", ctx: SysCtx::Core, jp_addr: 0x00347d70 },
    SysFunc { id: 929, name: "mdlRetail929", ctx: SysCtx::Core, jp_addr: 0x003448c0 },
    SysFunc { id: 930, name: "mdlRetail930", ctx: SysCtx::Core, jp_addr: 0x00344980 },
    SysFunc { id: 1134, name: "btlRetail1134", ctx: SysCtx::Core, jp_addr: 0x00349f60 },
    SysFunc { id: 1135, name: "btlRetail1135", ctx: SysCtx::Core, jp_addr: 0x003484c0 },
    SysFunc { id: 1216, name: "camRetail1216", ctx: SysCtx::Core, jp_addr: 0x00346d10 },
    SysFunc { id: 1712, name: "shrRetail1712", ctx: SysCtx::Core, jp_addr: 0x0034ca40 },
    SysFunc { id: 1713, name: "shrRetail1713", ctx: SysCtx::Core, jp_addr: 0x0034bee0 },
    SysFunc { id: 2705, name: "pthRetail2705", ctx: SysCtx::Core, jp_addr: 0x0035b490 },
    SysFunc { id: 2706, name: "pthRetail2706", ctx: SysCtx::Core, jp_addr: 0x0035b510 },
    SysFunc { id: 2707, name: "pthRetail2707", ctx: SysCtx::Core, jp_addr: 0x0035b5b0 },
    SysFunc { id: 3008, name: "fefRetail3008", ctx: SysCtx::Core, jp_addr: 0x0035e3b0 },
    SysFunc { id: 3009, name: "fefRetail3009", ctx: SysCtx::Core, jp_addr: 0x0035e4a0 },
    SysFunc { id: 3010, name: "fefRetail3010", ctx: SysCtx::Core, jp_addr: 0x0035d990 },
];

/// Look an id up in the retail (US) `FuncTbl`: the 269 shared entries plus [`VEC_RETAIL_FUNCS`] (286 ids).
pub fn us_func(id: i32) -> Option<&'static SysFunc> {
    VEC_FUNC_TABLE.iter().chain(VEC_RETAIL_FUNCS.iter()).find(|f| f.id == id)
}

#[cfg(test)]
mod retail_table_tests {
    use super::*;

    #[test]
    fn retail_table_has_286_distinct_ids() {
        let mut ids: Vec<i32> = VEC_FUNC_TABLE.iter().chain(VEC_RETAIL_FUNCS.iter()).map(|f| f.id).collect();
        assert_eq!(ids.len(), 286);
        ids.sort_unstable();
        ids.dedup();
        assert_eq!(ids.len(), 286, "ids are unique");
        // the 17 new ids named by notes/I/us_unmatched.md (N4 pass)
        let want = [212, 213, 214, 215, 929, 930, 1134, 1135, 1216, 1712, 1713, 2705, 2706, 2707, 3008, 3009, 3010];
        let got: Vec<i32> = VEC_RETAIL_FUNCS.iter().map(|f| f.id).collect();
        assert_eq!(got, want);
        assert!(VEC_RETAIL_FUNCS.iter().all(|f| f.ctx == SysCtx::Core));
        assert_eq!(us_func(3010).unwrap().name, "fefRetail3010");
        assert_eq!(us_func(900).unwrap().name, "mdlCreate");
        assert!(us_func(211).is_some() && us_func(216).is_none());
    }
}
