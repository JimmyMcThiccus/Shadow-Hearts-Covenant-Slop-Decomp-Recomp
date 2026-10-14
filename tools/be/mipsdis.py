#!/usr/bin/env python3
"""Tiny R5900 disassembler for reading retail overlay code that Ghidra has not disassembled (round 5 BE).

usage: mipsdis.py FILE BASE START END        (addresses = load addresses, hex)
       mipsdis.py FILE BASE --table ADDR N   (dump N u32 jump-table words)
BATTLE.BIN / FIELD.BIN of the US disc load at 0x45ea80.
Only the integer / COP1 subset the game uses is decoded; unknown words print as .word.
"""
import struct, sys

R = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7',
     's0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','s8','ra']

def s16(x): return x - 0x10000 if x & 0x8000 else x

def dis(w, pc):
    op = w >> 26; rs = (w >> 21) & 31; rt = (w >> 16) & 31; rd = (w >> 11) & 31; sa = (w >> 6) & 31; fn = w & 63
    imm = w & 0xffff; si = s16(imm); tgt = pc + 4 + (si << 2)
    if w == 0: return 'nop'
    if op == 0:
        sp = {0:'sll',2:'srl',3:'sra',0x38:'dsll',0x3a:'dsrl',0x3b:'dsra',0x3c:'dsll32',0x3e:'dsrl32',0x3f:'dsra32'}
        if fn in sp: return '%s %s, %s, %d' % (sp[fn], R[rd], R[rt], sa)
        if fn == 8: return 'jr %s' % R[rs]
        if fn == 9: return 'jalr %s, %s' % (R[rd], R[rs])
        if fn in (0x10, 0x12): return '%s %s' % ({0x10:'mfhi',0x12:'mflo'}[fn], R[rd])
        if fn in (0x18, 0x19, 0x1a, 0x1b): return '%s %s, %s, %s' % ({0x18:'mult',0x19:'multu',0x1a:'div',0x1b:'divu'}[fn], R[rd], R[rs], R[rt])
        if fn in (4, 6, 7, 0x14, 0x16, 0x17): return '%s %s, %s, %s' % ({4:'sllv',6:'srlv',7:'srav',0x14:'dsllv',0x16:'dsrlv',0x17:'dsrav'}[fn], R[rd], R[rt], R[rs])
        if fn == 0xa: return 'movz %s, %s, %s' % (R[rd], R[rs], R[rt])
        if fn == 0xb: return 'movn %s, %s, %s' % (R[rd], R[rs], R[rt])
        if fn == 0x2d and rt == 0: return 'move %s, %s' % (R[rd], R[rs])
        if fn == 0x25 and rt == 0: return 'move %s, %s' % (R[rd], R[rs])
        al = {0x20:'add',0x21:'addu',0x22:'sub',0x23:'subu',0x24:'and',0x25:'or',0x26:'xor',0x27:'nor',0x2a:'slt',0x2b:'sltu',
              0x2c:'dadd',0x2d:'daddu',0x2e:'dsub',0x2f:'dsubu'}
        if fn in al: return '%s %s, %s, %s' % (al[fn], R[rd], R[rs], R[rt])
        if fn == 0x34: return 'teq %s, %s' % (R[rs], R[rt])
        if fn == 0xd: return 'break'
        if fn == 0xf: return 'sync'
        return '.word %08x' % w
    if op == 1:
        n = {0:'bltz',1:'bgez',2:'bltzl',3:'bgezl'}.get(rt)
        return '%s %s, %08x' % (n, R[rs], tgt) if n else '.word %08x' % w
    if op in (2, 3):
        return '%s %08x' % ('j' if op == 2 else 'jal', ((pc + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2))
    br = {4:'beq',5:'bne',6:'blez',7:'bgtz',0x14:'beql',0x15:'bnel',0x16:'blezl',0x17:'bgtzl'}
    if op in br:
        if op in (4, 0x14) and rs == 0 and rt == 0: return 'b %08x' % tgt
        if op in (6, 7, 0x16, 0x17): return '%s %s, %08x' % (br[op], R[rs], tgt)
        return '%s %s, %s, %08x' % (br[op], R[rs], R[rt], tgt)
    ai = {8:'addi',9:'addiu',0xa:'slti',0xb:'sltiu',0x18:'daddi',0x19:'daddiu'}
    if op in ai:
        if op == 9 and rs == 0: return 'li %s, %d' % (R[rt], si)
        return '%s %s, %s, %d' % (ai[op], R[rt], R[rs], si)
    lo = {0xc:'andi',0xd:'ori',0xe:'xori'}
    if op in lo: return '%s %s, %s, 0x%x' % (lo[op], R[rt], R[rs], imm)
    if op == 0xf: return 'lui %s, 0x%x' % (R[rt], imm)
    mem = {0x20:'lb',0x21:'lh',0x23:'lw',0x24:'lbu',0x25:'lhu',0x27:'lwu',0x28:'sb',0x29:'sh',0x2b:'sw',0x37:'ld',0x3f:'sd',0x1e:'lq',0x1f:'sq',
           0x22:'lwl',0x26:'lwr',0x2a:'swl',0x2e:'swr'}
    if op in mem: return '%s %s, %d(%s)' % (mem[op], R[rt], si, R[rs])
    if op in (0x31, 0x39): return '%s $f%d, %d(%s)' % ('lwc1' if op == 0x31 else 'swc1', rt, si, R[rs])
    if op == 0x36: return 'lqc2 vf%d, %d(%s)' % (rt, si, R[rs])
    if op == 0x3e: return 'sqc2 vf%d, %d(%s)' % (rt, si, R[rs])
    if op == 0x11:
        fmt = rs; ft = rt; fs = rd; fd = sa
        if fmt == 0: return 'mfc1 %s, $f%d' % (R[rt], fs)
        if fmt == 4: return 'mtc1 %s, $f%d' % (R[rt], fs)
        if fmt == 8:
            return '%s %08x' % ({0:'bc1f',1:'bc1t',2:'bc1fl',3:'bc1tl'}[rt & 3], tgt)
        if fmt == 0x10:
            f = {0:'add.s',1:'sub.s',2:'mul.s',3:'div.s',4:'sqrt.s',5:'abs.s',6:'mov.s',7:'neg.s',0x24:'cvt.w.s',0x28:'max.s',0x29:'min.s',
                 0x18:'adda.s',0x1a:'mula.s',0x1c:'madd.s',0x1d:'msub.s'}
            if fn in f: return '%s $f%d, $f%d, $f%d' % (f[fn], fd, fs, ft)
            if fn == 0x32: return 'c.eq.s $f%d, $f%d' % (fs, ft)
            if fn == 0x34: return 'c.lt.s $f%d, $f%d' % (fs, ft)
            if fn == 0x36: return 'c.le.s $f%d, $f%d' % (fs, ft)
        if fmt == 0x14 and fn == 0x20: return 'cvt.s.w $f%d, $f%d' % (fd, fs)
        return '.word %08x (cop1)' % w
    if op == 0x1c:
        return 'mmi %08x' % w
    if op == 0x12: return 'cop2 %08x' % w
    return '.word %08x' % w

def main():
    f, base = sys.argv[1], int(sys.argv[2], 16)
    data = open(f, 'rb').read()
    if sys.argv[3] == '--table':
        a, n = int(sys.argv[4], 16), int(sys.argv[5], 0)
        for i in range(n):
            print('%2x %08x' % (i, struct.unpack_from('<I', data, a - base + i * 4)[0]))
        return
    a, e = int(sys.argv[3], 16), int(sys.argv[4], 16)
    out = []
    while a < e:
        w = struct.unpack_from('<I', data, a - base)[0]
        out.append((a, dis(w, a)))
        a += 4
    # --clean: drop nops, fold `dsll32 x,y,16 / dsra32 x,x,16` into `sext16 x, y` and the 0x510 BtlChr stride idiom
    if '--clean' in sys.argv:
        import re
        res = []
        i = 0
        while i < len(out):
            a, t = out[i]
            m = re.match(r'dsll32 (\w+), (\w+), (16|24)$', t)
            if m and i + 1 < len(out):
                m2 = re.match(r'dsra32 (\w+), (\w+), (16|24)$', out[i + 1][1])
                if m2 and m2.group(1) == m.group(1) and m2.group(2) == m.group(1) and m2.group(3) == m.group(3):
                    res.append((a, 'sext%s %s, %s' % ('16' if m.group(3) == '16' else '8', m.group(1), m.group(2))))
                    i += 2
                    continue
            # chr stride: sll v0,X,3; addu v1,v0,X; sll v0,v1,3; addu v0,v1,v0; sll v0,v0,4  => R = X*0x510
            if i + 4 < len(out):
                ts = [out[i + k][1] for k in range(5)]
                m = re.match(r'sll (\w+), (\w+), 3$', ts[0])
                if m and ts[1].startswith('addu') and ts[2].startswith('sll') and ts[3].startswith('addu') and re.match(r'sll (\w+), (\w+), 4$', ts[4]):
                    d = re.match(r'sll (\w+), (\w+), 4$', ts[4]).group(1)
                    res.append((a, '%s = %s * 0x510' % (d, m.group(2))))
                    i += 5
                    continue
            if t != 'nop':
                res.append((a, t))
            i += 1
        out = res
    for a, t in out:
        print('%08x  %s' % (a, t))

if __name__ == '__main__':
    main()

def grep_all(f, base, pat, lo=None, hi=None):
    """yield (addr, text) of every instruction whose text matches regex `pat`"""
    import re
    data = open(f, 'rb').read()
    r = re.compile(pat)
    a = lo or base
    e = hi or base + len(data) - 4
    while a < e:
        w = struct.unpack_from('<I', data, a - base)[0]
        t = dis(w, a)
        if r.search(t):
            yield a, t
        a += 4
