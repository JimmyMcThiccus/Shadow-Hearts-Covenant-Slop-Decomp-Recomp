/*
 * CScript.c -- Event-script virtual machine (SH2 JP demo, SLPM_602.19, main 0x00291ba0-0x00298b80)
 *
 * Cleaned from Ghidra output. Addresses are the JP Furokuban build.
 * Two distinct script VMs live in the executable:
 *   1. CScript / CScriptEx  (this file)  -- event/field/cutscene bytecode ("EVNT" images),
 *                                           byte-coded RPN stack machine.
 *   2. VEC::DecodeVSM        (VEC.c)     -- effect script VM (8-byte instructions, FuncTbl handlers).
 *
 * Struct names follow the symbol table; field names are ours.
 */
#include <stdint.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef int32_t s32; typedef int64_t s64;

/* ------------------------------------------------------------------------------------------
 * Script image header (first byte of the loaded .scr / LSCR payload)               ScriptHdr
 * ------------------------------------------------------------------------------------------ */
typedef struct ScriptHdr {
    u8  pad0;            /* 0x00 */
    u8  nSecUnits;       /* 0x01 number of 16-byte units from header to the first section ("EVNT" dir) */
    u8  valid;           /* 0x02 0 => InitScript refuses (returns -1) */
    u8  pad3;            /* 0x03 */
    u16 pad4;            /* 0x04 */
    u16 nDirUnits;       /* 0x06 size in 16-byte units of all directory sections ("EVNT"...) */
    u16 nCodeUnits;      /* 0x08 code length in 16-byte units; data segment follows the code */
    u16 nDataUnits;      /* 0x0a data length in 16-byte units */
    u16 bssSize;         /* 0x0c bytes of zeroed BSS (allocated unless it fits behind the data) */
    u16 startFunc;       /* 0x0e code offset of the scene start function (StartScene) */
    u16 endFunc;         /* 0x10 code offset of the scene end function, 0xffff = none (EndScene) */
    u16 resv12[3];       /* 0x12 */
    u16 relocUnit;       /* 0x18 16-byte-unit offset (from header) of the relocation table, 0 = none */
    u16 flags1a;         /* 0x1a (0x80 seen) */
    u32 resv1c;
} ScriptHdr;             /* sizeof == 0x20 */

/* directory section ("EVNT"), 16-byte aligned, chained by size field: next = this + nUnits*16 */
typedef struct EvntSec {
    u32 magic;           /* 'EVNT' = 0x544e5645 */
    u16 tableOff;        /* 0x04 byte offset of EvntEnt[] from section start (always 0x0c) */
    u16 nUnits;          /* 0x06 section size in 16-byte units */
    u16 kind;            /* 0x08 0 = triggered by id (CallEvent), 1 = triggered by LSD time (CallEventT) */
    u16 count;           /* 0x0a */
} EvntSec;
typedef struct EvntEnt {
    u32 id;              /* event number (kind 0) or LSD tick (kind 1) */
    u16 pad;
    u16 func;            /* code offset of the user function to run */
} EvntEnt;

/* relocation table (at hdr + relocUnit*16): u16 count, u16 resv, then count*8 bytes: */
typedef struct RelocEnt {
    u16 flags;           /* low nibble: where the patched word lives (0 = code, else data);
                            bits 4..7: which base to add (0 = code, else data) */
    u16 pad;
    u16 pad2;
    u16 off;             /* offset of the 32-bit word inside that segment */
} RelocEnt;

/* ------------------------------------------------------------------------------------------
 * Script job-control-block / work area (ScriptWork).
 * CScript+0x1c points at one of these (allocated by Create() in one buffer:
 *   [ScriptWork 0xa8][regs nVars*4 @+0xb0][stack nStack*4][delayed-event table 0x200])
 * The first 0x40 bytes double as the JCB; CreateNewJCB() pushes copies of it on the stack.
 * ------------------------------------------------------------------------------------------ */
typedef struct ScriptWork {
    u8 *code;            /* 0x00 code base                    (JCB) */
    u8 *data;            /* 0x04 data segment base            (JCB) */
    u8 *bss;             /* 0x08 BSS base                     (JCB) */
    u8 *ip;              /* 0x0c current instruction pointer  (JCB), NULL = job finished */
    struct ScriptWork *parent; /* 0x10 enclosing JCB (event chain) */
    u32 *frame;          /* 0x14 current function frame base (args/locals start; top of frame record) */
    u32 *sp;             /* 0x18 operand stack pointer */
    u8  *out;            /* 0x1c string/output write cursor (ops 0x8a-0x8d) */
    u32 typeBits;        /* 0x20 shift register: bit0 = top of stack is float, bit1 = next is float... */
    EvntSec *evnt;       /* 0x24 first directory section */
    int *resultAddr;     /* 0x28 where to store completion status for event calls */
    int eventId;         /* 0x2c id (or time) of the event that spawned this job */
    int eventMagic;      /* 0x30 value for Get/SetEventMagic */
    u8  resume;          /* 0x34 1 => GetParameter must re-run the pending ExecFunc first */
    u8  jcbKind;         /* 0x35 low nibble = JCB kind (0 root, 1 event); bit5 = bss was malloc'd */
    u8  pendOp;          /* 0x36 saved opcode of the pending call   */
    u8  pendSub;         /* 0x37 saved sub-opcode                   */
    int pendArg;         /* 0x38 saved nargs / resume token         */
    int waitStart;       /* 0x3c SysTool::GetTimer at the start of ifc_wait */
    u32 *regs;           /* 0x40 variable table ("registers"), indexed by flag ops */
    struct CScript *prevCurrent; /* 0x44 value of CScript::current when this script was entered */
    ScriptHdr *image;    /* 0x48 loaded image */
    u8 *delayBuf;        /* 0x4c 0x200-byte delayed-event queue (GetDlyEvent / CheckDlyEvent) */
    u16 stackWords;      /* 0x50 */
    u16 nRegs;           /* 0x52 */
    u16 timeSlice;       /* 0x54 max HCount ticks spent per Polling (JobExec yields when exceeded) */
    u16 resetParam;      /* 0x56 ResetSequence argument */
    u8  state;           /* 0x58 bits1-3: scene state (0 none,1,2 running,3 ending,4 finished)
                                  bits6-7: chain/load phase (LoadTarg)  */
    u8  flags59;         /* 0x59 bit0: statement just completed (suppress implicit step) */
    u16 nDelayed;        /* 0x5a count of queued delayed events */
    struct BufMemory *img;     /* 0x5c image buffer owned by us */
    struct BufMemory *next;    /* 0x60 pre-supplied buffer for chain */
    u8 *userBuf;         /* 0x64 caller supplied memory image buffer (LoadScript(name, buf)) */
    char name[0x40];     /* 0x68 script file name */
} ScriptWork;

/* frame record pushed by EnterUFunc (12 bytes, sits directly *below* the new frame base) */
typedef struct UFrame {
    u8  nargs;           /* -0x0c */
    u8  flag;            /* -0x0b */
    u16 retOff;          /* -0x0a code offset to resume at, 0xffff = none */
    u16 pad;             /* -0x08 */
    u16 argDepth;        /* -0x06 words between old frame base and the args */
    u32 *savedFrame;     /* -0x04 caller's frame base */
} UFrame;

typedef struct ParStack { u32 v[1]; } _ParStack;   /* args array: v[0]..v[n-1] */

/* ------------------------------------------------------------------------------------------
 * class CScript : CPolObj   (sizeof 0x28, vtable __vt__7CScript = 0x405bb0)
 *   +0x14 vptr  +0x18 flags  +0x1c ScriptWork*  +0x20 CScriptEx* list  +0x24 prev CScript (sys chain)
 * flags: b0 registered in CPoller(+0x48 prio 0x80)  b1 work buffer owned (new[])  b2 chain pending
 *        b3 BufMemory loaded/owned   b4 delete requested   b5 paused   b6 auto-restart
 * statics: sys__7CScript (0x40ac7c) latest script (list head), current__7CScript (0x40ac80),
 *          bPadR/S/D/F__7CScript (0x40ac6c..0x40ac78) per-frame pad state for ifc_get_pad
 * ------------------------------------------------------------------------------------------ */
typedef struct CScript {
    u8  polobj[0x14];
    void **vptr;         /* 0x14 */
    u8  flags;           /* 0x18 */
    u8  pad19[3];
    ScriptWork *w;       /* 0x1c */
    struct CScriptEx *ex;/* 0x20 head of linked CScriptEx list */
    struct CScript *prev;/* 0x24 */
} CScript;

extern CScript *sys_CScript, *current_CScript;
extern u32 bPadR, bPadS, bPadD, bPadF;

/* 0x00291ba0 __ct__7CScriptFv */
CScript *CScript_ct(CScript *t) {
    CPolObj_ct(t);
    t->vptr = __vt__7CScript;
    t->prev = sys_CScript; sys_CScript = t;
    t->flags = 0; t->w = 0; t->ex = 0;
    return t;
}

/* 0x00291ca0 GetBufferSize__7CScriptFii */
int CScript_GetBufferSize(CScript *t, int nRegs, int nStack) { return nStack * 4 + nRegs * 4 + 0x8b0; }

/* 0x00291cf0 Create__7CScriptFPUciii : buf==0 -> operator new[](GetBufferSize), sets flags.b1 */
void CScript_Create(CScript *t, void *buf, int nRegs, int nStack, u16 timeSlice) {
    if (t->w) return;
    if (!buf) { buf = new_array(CScript_GetBufferSize(t, nRegs, nStack)); t->flags = (t->flags & ~2) | 2; }
    memset(buf, 0, 0xa8);
    t->w = buf;
    t->w->regs   = (u32 *)((u8 *)buf + 0xb0);
    t->w->frame  = t->w->sp = t->w->regs + nRegs;
    t->w->delayBuf = (u8 *)(t->w->frame + nStack);
    memset(t->w->regs, 0, nRegs * 4);
    t->w->nRegs = nRegs; t->w->stackWords = nStack; t->w->timeSlice = timeSlice;
}

/* 0x00291e70 Release__7CScriptFi / 0x00291f70 Delete / 0x00292330 ReleaseBss: resource teardown (omitted) */

/* 0x00292000 LoadScript(name, userBuf): schedule load of <name> via DvdromOrder::ReadOrder on next Polling.
 * 0x002920e0 LoadScriptB(name, BufMemory*): same with caller supplied BufMemory.
 * both set state.phase = 1/2 so Polling()->JobChain()->LoadTarg() performs the read, then InitScript(). */

/* 0x002923e0 InitScript__7CScriptFPcPUc : bind an image to this CScript. returns 0 ok, -1 if !valid */
int CScript_InitScript(CScript *t, const char *name, ScriptHdr *img) {
    ScriptWork *w = t->w;
    t->flags &= ~0x40;
    w->state &= 0xf1; w->state &= 0x3f;
    w->image = img;
    CScript_ReleaseBss(t);
    w->frame = w->sp = w->regs + w->nRegs;            /* reset stack */
    if (name) strcpy(w->name, name);
    if (!img->valid) return -1;
    CScript_CreateNewJCB(t, 0);
    ScriptWork *j = w->jcb_current;                    /* *(w+0x10) after CreateNewJCB */
    j->eventId /* [9]*/ = 0;
    u8 *sec = (u8 *)img + img->nSecUnits * 0x10;
    u8 *code = sec;
    if (img->nDirUnits) {
        code = sec + img->nDirUnits * 0x10;
        for (u8 *p = sec; p < code; p += ((EvntSec *)p)->nUnits * 0x10)
            if (((EvntSec *)p)->magic == 0x544e5645 && j->evnt == 0) j->evnt = (EvntSec *)p;
    }
    j->code = code;
    j->data = code + img->nCodeUnits * 0x10;
    /* relocation */
    u16 relocEnd = 0;
    if (img->relocUnit) {
        u16 *r = (u16 *)((u8 *)img + img->relocUnit * 0x10);
        int n = r[0]; relocEnd = r[1];
        for (int i = 0; i < n; i++, r += 4) {
            u8 *loc = ((r[2] & 0xf) == 0 ? j->code : j->data) + r[3];
            u32 v; memcpy(&v, loc, 4);
            v += ((r[2] >> 4) == 0 ? (u32)j->code : (u32)j->data);
            memcpy(loc, &v, 4);
        }
    }
    if (img->bssSize) {
        if (img->bssSize < relocEnd) j->bss = (u8 *)img + img->relocUnit * 0x10;      /* reuse slack */
        else { j->bss = new_array(img->bssSize); j->jcbKind |= 0x20; }
    }
    j->frame /*[3]*/ = code + img->startFunc;
    memcpy(w, j, 0x40); w->jcb = j;
    w->ip = CScript_EnterUFunc(t, 0, code + img->startFunc, 0, 0);
    if (w->userBuf && w->img) { BufMemory_dt(w->img); w->img = 0; }
    return 0;
}

/* 0x00292f30 CreateNewJCB__7CScriptFi : push a copy of the running JCB on the stack (kind = 0/1) */
void *CScript_CreateNewJCB(CScript *t, u8 kind) {
    ScriptWork *w = t->w;
    if (w->parent) { u32 keep = (u32)w->parent->parent; memcpy(w->parent, w, 0x40); w->parent->parent = (void *)keep; }
    ScriptWork *n = (ScriptWork *)w->sp;
    memset(n, 0, 0x40); memcpy(n, w, 0x40);
    n->frame = n->sp = (u32 *)((u8 *)n + 0x40);
    n->jcbKind = (n->jcbKind & 0xf0) | (kind & 0xf);
    memcpy(w, n, 0x40); w->parent = n;
    return n;
}

/* 0x00293050 DeleteCurJCB : pop a finished event job */
void CScript_DeleteCurJCB(CScript *t) {
    ScriptWork *w = t->w;
    if (w->resultAddr) {                         /* notify completion */
        int *ra = w->resultAddr;
        if ((u32)*ra < 0x10000) *ra = 1; else *(u32 *)*ra = *(u32 *)((u8 *)w->sp - 4);
    }
    ScriptWork *par = w->parent ? w->parent->parent : 0;
    if (!par) w->ip = 0; else { memcpy(w, par, 0x40); w->parent = par; }
}

/* 0x00293570 StartScene / 0x00293620 EndScene / 0x00293880 ResetScene / 0x00293470 TerminateJob:
 * see notes/E/script_vm.md section "Scene state machine". */

/* 0x00292a60 Polling__7CScriptFv  -- one tick of the VM, returns 1 when the script is dead.
 * 0x00293ca0 JobExec   -- run the instruction loop until yield (returns 0 paused, 1 timeslice, 2 suspended, -1 finished)
 * 0x00294130 Statement -- 0x90-0x9f control flow
 * 0x00294620 GetParameter  -- push/dispatch loop for one statement
 * 0x00295840 Expression    -- 0x20-0x8f arithmetic / memory ops
 * 0x00297610 ExecFunc      -- 0xa0-0xaf builtins (ifc_*) and 0xbc-0xff CScriptEx::CallFunc
 */

/* 0x00293ca0 JobExec__7CScriptFv  (structure only; time-slice uses Gsx::HCount / RCNT3) */
int CScript_JobExec(CScript *t) {
    ScriptWork *w = t->w;
    u32 t0 = hcount_now();
    u8 *ip;
    if (!CScript_CheckDlyEvent(t)) {
        ip = w->ip;
        if (w->resume == 0 || w->resume > 3) goto step;     /* normal */
        FlushCache(0);
    } else ip = w->ip;
    for (;;) {
        int r = CScript_GetParameter(t, &ip);          /* run RPN pushes/ops/calls until a 0x90-0x9f statement or end */
        if (r == -1) { w->ip = 0; return -1; }
        if (t->flags & 0x10) return 0;                 /* script deleted from inside a call */
        if (r == -2) { w->ip = ip; w->resume = 1; return 2; }
        u8 op = *ip;
        if (op >= 0x90 && op < 0xa0) {
            CScript_Statement(t, op, &ip);
            if (op == 0x98) continue;
        }
        if (!(w->flags59 & 1)) goto step;
      post:
        w->ip = ip;
        CScript_CheckDlyEvent(t);
        if (!ip) {                                      /* fell off the end of an event function */
            CScript_DeleteCurJCB(t);
            if (((w->state & 0xf) >> 1) != 2 || !w->ip) {
                w->ip = 0; if (((w->state & 0xf) >> 1) == 3) w->state = (w->state & 0xf1) | 8;
                return -1;
            }
            ip = w->ip;
        }
        op = *ip;
        if (op < 0x90 || op > 0x9f) {
            if (op == 0) { w->ip = 0; return -1; }
            if (op != 1) continue;                      /* start of a new expression statement */
            ip++;                                       /* explicit NOP */
        } else {
            CScript_Statement(t, op, &ip);
            if (op == 0x98) continue;
        }
      step:
        w->sp = w->frame;                               /* statement boundary: drop temporaries */
        if (w->timeSlice < hcount_now() - t0) { w->ip = ip; return 1; }
    }
}

/* 0x00294620 GetParameter__7CScriptFRPUc   -- returns 1 = hit statement/unknown byte, 0 = paused, -1 = end, -2 = suspended */
int CScript_GetParameter(CScript *t, u8 **pip) {
    ScriptWork *w = t->w;
    if (w->resume == 1) {                              /* re-enter the call that yielded */
        int r = CScript_ExecFunc(t, w->pendOp, w->pendSub, w->pendArg);
        if (r < 0) { w->pendArg = r; return -2; }
        CScript_ApplyCallResult(t, r, pip);            /* see below */
        w->jcbKind &= ~0x10; w->resume = 0;
    } else if (w->resume == 2 || w->resume == 3) w->resume = 0;
    for (;;) {
        if (t->flags & 0x10) return 0;
        if (((w->state & 0xf) >> 1) == 4) return -1;
        u8 b = *(*pip)++;
        if (b >= 0x20) {
            if (b < 0x90) { CScript_Expression(t, b, pip); continue; }
            if (b < 0xa0) { (*pip)--; return 1; }                      /* statement */
            u8 sub = b;
            if (b > 0xbb) sub = *(*pip)++;                             /* second opcode byte */
            u32 nargs = *(*pip)++;
            w->pendOp = b; w->pendSub = sub;
            w->sp -= nargs;                                            /* args now at w->sp[0..nargs) */
            w->ip = *pip;
            int r = CScript_ExecFunc(t, b, sub, nargs);
            if (r < 0) { w->pendArg = r; w->resume = 1; return -2; }
            CScript_ApplyCallResult(t, r, pip);
            continue;
        }
        w->typeBits <<= 1;
        switch (b) {
        case 0x1b: *pip = CScript_EnterUFunc(t, *pip + 3, w->code + rd16(*pip), (*pip)[2], 0); return 1;
        case 0x1a: push(w, w->frame[-1] /*saved*/ + w->frameRec->argDepth*4 + rd16(*pip)*4); *pip += 2; break;
        case 0x19: push(w, savedFrame + argDepth*4 + *(*pip)++); break;
        case 0x18: push(w, w->bss + rd16(*pip)); *pip += 2; break;
        case 0x16: push(w, w->code + rd16(*pip)); *pip += 2; break;
        case 0x15: push(w, w->data + rd16(*pip)); *pip += 2; break;
        case 0x14: { u16 v = rd16(*pip); *pip += 2; push(w, SafeGetFlagAddr(v >> 12, v & 0xfff)); break; }
        case 0x13: w->typeBits |= 1; /* fallthrough */
        case 0x12: push(w, SafeGetFlagAddr(4, *(*pip)++)); break;
        case 0x11: push(w, SafeGetFlagAddr(2, *(*pip)++)); break;
        case 0x10: push(w, SafeGetFlagAddr(0, *(*pip)++)); break;
        case 0x0f: w->typeBits |= 1; /* fallthrough */
        case 0x0e: push(w, rd32(*pip)); *pip += 4; break;
        case 0x0d: push(w, rd16(*pip) | 0xffff0000); *pip += 2; break;
        case 0x0c: push(w, rd16(*pip)); *pip += 2; break;
        case 0x0b: push(w, *(*pip)++ | 0xffffff00); break;
        case 0x0a: push(w, *(*pip)++); break;
        case 9: push(w, 4); break;  case 8: push(w, 2); break;  case 7: push(w, 1); break;
        case 6: push(w, 0); break;  case 5: push(w, -1); break; case 4: push(w, (u32)""); break;
        case 0x4f: return -1;
        case 1: w->sp = w->frame; break;               /* reset operand stack */
        default: w->typeBits >>= 1; return 1;          /* unknown byte: leave to caller */
        }
    }
}
/* ApplyCallResult(r):  0 -> clear stack (void call)   1 -> push int result already in sp[0]   2 -> float result
 *                      7 -> jump back: *pip = w->ip (script restarted / event re-entered)   0x10 -> error: clear stack
 *   int/float: sp += 1; typeBits = typeBits<<1 | (r==2) */

/* 0x00297610 ExecFunc__7CScriptFiii */
int CScript_ExecFunc(CScript *t, int op, int sub, int nargs) {
    ParStack *args = (ParStack *)t->w->sp;
    if (op < 0xbc) switch (op) {
        case 0xa0: return ifc_chain(t, args);         case 0xa1: return ifc_callEvent(t, nargs, args);
        case 0xa2: return ifc_callEventDly(t, nargs, args);
        case 0xa3: return ifc_getSysInfo(t, args);    case 0xa4: return ifc_setFlag(t, args);
        case 0xa5: return ifc_clrFlag(t, args);       case 0xa6: return ifc_chkFlag(t, args);
        case 0xa7: return ifc_reg_clr(t, args);
        case 0xaa: return ifc_wait(t, nargs, args);   case 0xab: return ifc_sprintf(t, nargs, args);
        case 0xac: return ifc_get_pad(t, args);       case 0xad: return ifc_randomize();
        case 0xae: return ifc_rnd(t, args);           case 0xaf: return ifc_dprintf(t, nargs, args);
        default:   return 0x10;
    }
    return CScriptEx_CallFunc(t->ex, op /*ex id*/, sub, nargs, args);
}

/* 0x00293790 JobChain : LoadScript() driven script switching (ResetScene -> LoadTarg) */

/* ----- builtin interface functions ('ifc_', signature (CScript*, [int nargs,] ParStack*) -> status) ----- */
/* 0x00297890 */ int ifc_chain(CScript *t, u32 *a) {                    /* 0xa0  chain("next.scr") */
    CScript_EndScene(current_CScript);
    strcpy(current_CScript->w->name, (char *)a[0]);
    t->flags = (t->flags & ~4) | 4;
    t->w->state = (t->w->state & 0x3f) | 0x40;                         /* phase 1: load requested */
    return 0;
}
/* 0x00297930 */ int ifc_callEvent(CScript *t, int n, u32 *a) {          /* 0xa1  callEvent(id, args...) */
    u32 id = a[0]; a[0] = (u32)a;                                       /* result slot pointer */
    t->w->sp += 1;
    u32 tmp[32]; if (n > 1) memcpy(tmp, a + 1, (n - 1) * 4);
    CScript_CallEvent(t, id, n - 1, tmp, a);
    return 7;                                                            /* restart at new ip */
}
/* 0x002979f0 */ int ifc_callEventDly(CScript *t, int n, u32 *a) {      /* 0xa2  callEventDly(delay, id, args...) */
    n -= 2;
    u8 *e = GetDlyEvent(t, n);
    if (e) { *(u32 *)(e + 0xc) = a[0]; *(u32 *)(e + 4) = a[1]; *(u32 *)(e + 8) = SysTool_GetTimer(); memcpy(e + 0x10, a + 2, n * 4); }
    return 0;
}
/* 0x00297aa0 */ int ifc_getSysInfo(CScript *t, u32 *a) { a[0] = 0; return 1; }  /* 0xa3 (CScript::GetSysInfo is a stub: 0) */
/* 0x00297b00 */ int ifc_setFlag(CScript *t, u32 *a) { regs()[a[0] >> 5] |=  1u << (a[0] & 31); return 0; }  /* 0xa4 */
/* 0x00297ba0 */ int ifc_clrFlag(CScript *t, u32 *a) { regs()[a[0] >> 5] &= ~(1u << (a[0] & 31)); return 0; } /* 0xa5 */
/* 0x00297c40 */ int ifc_chkFlag(CScript *t, u32 *a) { a[0] = (regs()[a[0] >> 5] >> (a[0] & 31)) & 1; return 1; } /* 0xa6 */
/* 0x00297ce0 */ int ifc_reg_clr(CScript *t, int *a) {                  /* 0xa7  reg_clr(first, last, value) */
    int lo = a[0], hi = a[1], val = a[2]; u16 n = cur()->w->nRegs;
    if (hi >= n) hi = n - 1; if (lo < 0) lo = 0;
    for (; lo <= hi; lo++) regs()[lo] = val;                            /* memset when val==0 */
    return 0;
}
/* 0x00297e10 */ int ifc_wait(CScript *t, int n, int *a) {              /* 0xaa  wait(frames|-ms) ; returns <0 while waiting */
    if (n < 0) { if (-n <= SysTool_GetTimer() - t->w->waitStart) n = 0; }
    else {
        n = a[0];
        if (n < 0) n = (int)((float)(n * -1000) / ((ntsc ? 60.0f : 50.0f) / (float)Gsx_syncCount));
        if (n < 1) n = 0; else { t->w->waitStart = SysTool_GetTimer(); n = -n; }
    }
    return n;
}
/* 0x00298170 */ int ifc_sprintf(CScript *t, int n, u32 *a) { ifc_xprintf(t, (char *)a[0], (char *)a[1], n - 2, a + 2); return 0; } /* 0xab */
/* 0x00297fc0 */ int ifc_get_pad(CScript *t, u32 *a) {                  /* 0xac  get_pad(mode, mask) */
    u32 mask = (u16)a[1]; u8 mode = a[0];
    if (mode == 4 || mode == 3) { bPadF |= mask; bPadS &= ~mask; bPadD &= ~mask; a[0] = bPadR; }  /* consume */
    else a[0] = mode == 2 ? bPadD : mode == 1 ? bPadS : bPadR;   /* 1 = new press, 2 = repeat, other = raw */
    return 1;
}
/* 0x002980a0 */ int ifc_randomize(void) { ipRandomize(); return 0; }   /* 0xad */
/* 0x002980d0 */ int ifc_rnd(CScript *t, int *a) { a[0] = a[0] ? iprnd(a[0]) : ipMakeRand(); return 1; } /* 0xae */
/* 0x00298150 */ int ifc_dprintf(CScript *t, int n, u32 *a) { return 0; }        /* 0xaf  (debug print stripped) */
/* 0x002981d0 ifc_xprintf: minimal printf into a script buffer; handles %d %x %X %c %s %f (f reads a float arg) */

/* ------------------------------------------------------------------------------------------
 * CScriptEx : CPolObj   (sizeof 0x24, vtable __vt__9CScriptEx = 0x405bc0)
 *   +0x14 vptr  +0x18 next CScriptEx  +0x1c CScript*  +0x20 u16 id (= first opcode byte)  +0x22 flags
 *   vtable: [0] dtor?  [1]=8 dtor  [2]=0x10 OnStart()  [3]=0x14 OnEnd(int)  [4]=0x18 CallFunc(sub,nargs,args)
 * ------------------------------------------------------------------------------------------ */
/* 0x002986b0 */ CScriptEx *CScriptEx_ct(CScriptEx *e) { CPolObj_ct(e); e->vptr = __vt__9CScriptEx; e->next = 0; e->script = 0; e->id = 0; e->flags = 0; return e; }
/* 0x00298710 Link(id, script): append to script->ex chain; id = the opcode byte (0xc0 LSD, 0xc2 Field) */
void CScriptEx_Link(CScriptEx *e, int id, CScript *s) {
    e->id = id; if (!s) s = sys_CScript; e->script = s;
    CScriptEx **pp = &s->ex;
    while (*pp) { if (*pp == e) return; pp = &(*pp)->next; }
    *pp = e; e->next = 0;
}
/* 0x002987f0 */ int CScriptEx_CallFunc(CScriptEx *e, u32 id, int sub, int nargs, void *args) {
    for (; e; e = e->next) if (e->id == id) return e->vptr->CallFunc(e, sub, nargs, args);
    return 0x10;                                       /* unhandled -> error */
}
/* 0x00298970 StartSequence: call OnStart() of every linked ex.   0x002989d0 ResetSequence(token): OnEnd chain. */

/* ------------------------------------------------------------------------------------------
 * 0x00294130 Statement  (opcodes 0x90-0x9f)
 * ------------------------------------------------------------------------------------------ */
void CScript_Statement(CScript *t, int op, u8 **pip) {
    ScriptWork *w = t->w;
    ++*pip;                                                         /* consume opcode */
    switch (op) {
    case 0x99:                                                       /* ret */
        *pip = CScript_LeaveUFunc(t);
        if (*pip == 0) { *w->sp++ = 0; return; }                    /* returned out of the root frame: end of job */
        w->flags59 |= 1; break;
    case 0x98: {                                                     /* retv: keep top-of-stack as return value */
        u32 v = *--w->sp;
        *pip = CScript_LeaveUFunc(t);
        *w->sp++ = v; return;
    }
    case 0x94: {                                                     /* switch */
        u32 key = *--w->sp;
        *pip = GetCodePtr(t, pip);                                  /* ip := &table */
        u16 h = rd16(*pip); *pip += 2;
        int kt = (h >> 12) & 7, n = h & 0xfff;                      /* kt: 0=u8 1=u16 2=u32 keys */
        w->flags59 &= ~1;
        for (; n > 0; n--) {
            u32 k = kt == 2 ? rd32(*pip) : kt == 1 ? rd16(*pip) : **pip;
            *pip += kt == 2 ? 4 : kt == 1 ? 2 : 1;
            if (k == key) { *pip = GetCodePtr(t, pip); goto done; }
            *pip += 2;
        }
        if (h & 0x8000) *pip = GetCodePtr(t, pip);                  /* default target */
        break;                                                       /* else fall past the table */
    }
    case 0x92: { u8 *tgt = GetCodePtr(t, pip); if (*--w->sp != 0) *pip = tgt; break; }   /* jnz */
    case 0x91: { u8 *tgt = GetCodePtr(t, pip); if (*--w->sp == 0) *pip = tgt; break; }   /* jz  */
    case 0x90: *pip = GetCodePtr(t, pip); break;                                         /* jmp */
    }
done:
    w->sp = w->frame; w->typeBits = 0; w->flags59 |= 1;
}
/* 0x002940a0 GetCodePtr: reads u16 at *pip (advances 2) and returns code_base + u16 */
/* 0x002953c0 EnterUFunc(retIP, funcAddr, nargs, flag): see UFrame above; returns funcAddr+2 (skip u16 locals-size)
 * 0x00295550 LeaveUFunc: pops UFrame, restores frame/sp, returns code+retOff or 0 if none */
