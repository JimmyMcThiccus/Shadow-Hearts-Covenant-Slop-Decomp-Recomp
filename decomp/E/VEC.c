/*
 * VEC.c -- effect script VM ("VSM")   JP main 0x002fc0c0..0x002fe060 (+ small helpers in EffectCore 0x00301530/0x00301770/0x00301d90)
 * class VEC : CList   (vtable __vt__3VEC 0x406808, sizeof 0x254)   Raw Ghidra output: VEC.ghidra.c
 * Rust port: port/crates/sh2_script/src/vsm.rs   (struct layout: Ghidra struct `VEC`)
 */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef int s32; typedef signed char s8;

typedef struct VEC {
    struct VEC *child;      /* 0x00 CList link */
    u32  startIp;           /* 0x08 entry instruction index (from HECO header) */
    s32  ip;                /* 0x0c current instruction index (valid 0..0x1fff) */
    s32  sp;                /* 0x10 operand stack index (valid 0..99) */
    s32  fp;                /* 0x14 frame pointer into the data segment (threads start at 20000) */
    s32  state;             /* 0x18 -1 error, 0 idle, 1 running, 2 wait-frame (sysWaitSystem), 3 done */
    void *argv[21];         /* 0x1c..0x6b SYSCALL arguments (SETARG: pointers into dseg) */
    u32  *iseg;             /* 0x6c instruction segment (8-byte insns) */
    struct BufMemory *dsegBuf; /* 0x70 */
    u8   *dseg;             /* 0x74 data segment base (40000 bytes) */
    u32  stack[100];        /* 0x78 operand stack (S[0] unused: push pre-increments sp) */
    u32  insnCount;         /* 0x208 */  s32 maxSp; /* 0x20c */  s32 minFp; /* 0x210 init 40000 */
    s32  callCount;         /* 0x218 */  s32 stackLimit; /* 0x21c fp must stay above this (0) */
    u8   waitThreads;       /* 0x221 WAIT_THREADS active */
    s32  motionWait;        /* 0x224 EffectModel being waited on (mdlWaitMotion) */
    s32  threadCount;       /* 0x228 live threads with tag == waitTag (OnStartThread/OnEndThread) */
    u8   anyStarted;        /* 0x22c */
    struct EffectCore *core;/* 0x230 */
    u8   loadWait;          /* 0x238 tagEffectLoadWait: b0 waiting, b1 done (sysWaitCreateEffect) */
    s32  tag;               /* 0x244 thread tag (operand of the insn after SPAWN) */
    s32  waitTag;           /* 0x248 */
    void **vptr;            /* 0x250 */
} VEC;

/* 0x002fc350 Start(): ip = startIp; state = 1.   0x002fc390 Continue(): if state in {-1,3} return 0; state = 1; return DecodeVSM()
 * 0x002fdc80 CreateThread(entry, tag): new VEC; memcpy(child.dseg, dseg, 40000); child.iseg = iseg; child.fp = 20000
 * 0x002fddf0 MotionWait(model): only if model is one of core->models[0..0x27] */

/* 0x002fc400 DecodeVSM__3VECFv : returns 0 done/ok, 1 yield, <0 fatal.  Instruction = u8 op, u8 fpRel, u16 pad, u32 operand. */
int VEC_DecodeVSM(VEC *t) {
 again:
    if (t->state != 1) return -1;
    if (t->ip < 0 || t->ip > 0x1fff) { printf("ip out of range %d", t->ip); t->state = -1; return -1; }
    if (t->sp > 99 || t->sp < 0)     { printf("sp out of range %d @%d", t->sp, t->ip); t->state = -1; return -1; }
    if (t->waitThreads) {
        if (!t->anyStarted) return 1;
        if (t->threadCount) return 1;
        t->waitThreads = 0; t->waitTag = 0; t->threadCount = 0; t->anyStarted = 0;
    }
    if (t->motionWait) return 1;
    if ((t->loadWait & 1) && !(t->loadWait & 2)) return 1;
    u8  op  = ((u8 *)t->iseg)[t->ip * 8];
    u8  rel = ((u8 *)t->iseg)[t->ip * 8 + 1];
    u32 opd = *(u32 *)((u8 *)t->iseg + t->ip * 8 + 4);
    t->ip++;
    if (rel) opd += t->fp;
    t->insnCount++; if (t->sp > t->maxSp) t->maxSp = t->sp;
    u32 *S = t->stack; float *F = (float *)t->stack;
    switch (op) {
    case 0x00: goto again;
    case 0x01: t->dseg[S[t->sp-1]] = (u8)S[t->sp]; S[t->sp-1] = S[t->sp]; break;                 /* STB */
    case 0x02: case 0x03: *(u32 *)(t->dseg + S[t->sp-1]) = S[t->sp]; S[t->sp-1] = S[t->sp]; break; /* STW/STF */
    case 0x04: S[t->sp-1] += S[t->sp]; break;   case 0x05: F[t->sp-1] += F[t->sp]; break;   case 0x06: S[t->sp] += opd; goto again;
    case 0x07: S[t->sp-1] -= S[t->sp]; break;   case 0x08: F[t->sp-1] -= F[t->sp]; break;   case 0x09: S[t->sp] -= opd; goto again;
    case 0x0a: S[t->sp-1] *= S[t->sp]; break;   case 0x0b: F[t->sp-1] *= F[t->sp]; break;   case 0x0c: S[t->sp] *= opd; goto again;
    case 0x0d: if (!S[t->sp]) { printf("divide by zero @%d", t->ip-1); return -1; } S[t->sp-1] = (s32)S[t->sp-1] / (s32)S[t->sp]; break;
    case 0x0e: if (F[t->sp] == 0.f) { printf("divide by zero"); return -1; } F[t->sp-1] /= F[t->sp]; break;
    case 0x0f: S[t->sp] = (s32)S[t->sp] / (s32)opd; goto again;
    case 0x10: if (!S[t->sp]) { printf("mod by zero"); return -1; } S[t->sp-1] = (s32)S[t->sp-1] % (s32)S[t->sp]; break;
    case 0x12: S[t->sp] = (s32)S[t->sp] % (s32)opd; goto again;
    case 0x13: S[t->sp] = -(s32)S[t->sp]; goto again;   case 0x14: F[t->sp] = -F[t->sp]; goto again;
    case 0x15: S[t->sp-1] = (s32)S[t->sp-1] < (s32)S[t->sp] ? -1 : ((s32)S[t->sp] < (s32)S[t->sp-1]); break;
    case 0x16: F[t->sp-1] = (float)(F[t->sp-1] < F[t->sp] ? -1 : (F[t->sp] < F[t->sp-1])); break;
    case 0x17: S[t->sp] = (s32)S[t->sp] < (s32)opd ? -1 : ((s32)opd < (s32)S[t->sp]); goto again;
    case 0x18: t->sp++; S[t->sp] = S[t->sp-1]; goto again;
    case 0x19: S[++t->sp] = (s8)t->dseg[opd]; goto again;
    case 0x1a: case 0x1b: S[++t->sp] = *(u32 *)(t->dseg + opd); goto again;
    case 0x1c: S[++t->sp] = opd; goto again;
    case 0x1d: S[t->sp] = (s8)t->dseg[S[t->sp]]; goto again;
    case 0x1e: case 0x1f: S[t->sp] = *(u32 *)(t->dseg + S[t->sp]); goto again;
    case 0x20: break;
    case 0x21: t->dseg[opd] = (u8)S[t->sp]; break;
    case 0x22: case 0x23: *(u32 *)(t->dseg + opd) = S[t->sp]; break;
    case 0x24: t->fp = opd; goto again;
    case 0x25: t->fp += opd; if (t->fp > 40000) { printf("stack overflow"); t->state = -1; return -2; } goto again;
    case 0x26: t->fp -= opd; if (t->fp < t->minFp) { if (t->fp <= t->stackLimit) { printf("stack overflow"); t->state = -1; return -2; } t->minFp = t->fp; } goto again;
    case 0x27: F[t->sp] = (float)(s32)S[t->sp]; goto again;
    case 0x28: S[t->sp] = (s32)F[t->sp]; goto again;
    case 0x29: t->ip = opd; goto again;
    case 0x2a: if ((s32)S[t->sp--] <  0) t->ip = opd; goto again;
    case 0x2b: if ((s32)S[t->sp--] <= 0) t->ip = opd; goto again;
    case 0x2c: if ((s32)S[t->sp--] == 0) t->ip = opd; goto again;
    case 0x2d: if ((s32)S[t->sp--] != 0) t->ip = opd; goto again;
    case 0x2e: if ((s32)S[t->sp--] >= 0) t->ip = opd; goto again;
    case 0x2f: if ((s32)S[t->sp--] >  0) t->ip = opd; goto again;
    case 0x30: S[++t->sp] = t->ip; t->ip = opd; t->callCount++; goto again;
    case 0x31: t->ip = S[t->sp--]; goto again;
    case 0x32: if (t->sp != 0) printf("stack not empty at END"); t->state = 3; return 0;
    case 0x33: { t->sp -= 3; u8 *dst = t->dseg + S[t->sp+2], *src = t->dseg + S[t->sp+1]; for (s32 n = S[t->sp+3]; n > 0; n--) *dst++ = *src++; goto again; }
    case 0x34: S[t->sp] = (u8 *)new_array(S[t->sp]) - t->dseg; goto again;
    case 0x35: delete_array(t->dseg + S[t->sp--]); goto again;
    case 0x36: S[t->sp-1] = scanf((char *)(t->dseg + S[t->sp-1]), t->dseg + S[t->sp]); break;
    case 0x37: t->sp -= 2; goto again;   case 0x38: t->sp -= 1; goto again;
    case 0x39: {
        u32 argc = opd & 0xffff, id = (opd >> 16) & 0xffff;
        if (argc > 20) { printf("too many syscall args"); t->state = -1; return -3; }
        SysFunc *f = GetSysCallFunc(id);                       /* hash id % 0x83 over FuncTbl */
        switch (f->ctxKind) {
            case 2: f->fn(id, argc, t->argv, 0);       break;
            case 1: f->fn(id, argc, t->argv, t);       break;
            case 0: f->fn(id, argc, t->argv, t->core); break;
            default: f->fn(id, argc, t->argv, f->userCtx);
        }
        goto again; }
    case 0x3a: if ((s32)opd < 0 || opd > 20) { printf("bad arg index"); t->state = -1; return -3; } t->argv[opd] = t->dseg + S[t->sp]; break;
    case 0x3b: { VEC *c = VEC_CreateThread(t, opd, t->iseg[t->ip*2 + 1] /* operand of next insn = tag */); EffectCore_AddThread(t->core, c); t->ip++; goto again; }
    case 0x3c: VEC_RemoveThread(t); return 0;
    case 0x3d: t->waitTag = opd; t->waitThreads = 1; t->threadCount = GetThreadCount(t->core->threads, t->waitTag); if (t->threadCount) t->anyStarted = 1; goto again;
    case 0x3e: EffectCore_KillThread(t->core, opd); goto again;
    default: printf("illegal opcode %d @%d", op, t->ip); t->state = -1; return -4;
    }
    t->sp--;      /* ops that `break` pop one operand */
    goto again;
}
