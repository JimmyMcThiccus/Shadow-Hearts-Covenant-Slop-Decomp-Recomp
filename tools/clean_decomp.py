#!/usr/bin/env python3
"""Light-weight post-processor for Ghidra decompiler output (BATTLE.BIN, section H).

 * func_0xADDR  -> symbol name (main exe + overlay symbols from symbols/SLPM_602.19.syms)
 * iGpffff847c etc. -> gp-relative global names
 * (X + idx * 0x4f0 + OFF) / ((c*0x50 - c)*0x10) forms -> X->chr[idx].<name>
 * known CBattle header offsets -> names
Usage: clean_decomp.py in.c > out.c
"""
import re, sys, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMS = {}
for l in open(os.path.join(ROOT, 'symbols/SLPM_602.19.syms')):
    p = l.split('\t')[0].split()
    if len(p) >= 6 and p[2] == 'FUNC':
        SYMS[int(p[0], 16)] = p[5]
GP = {
    'iGpffff847c': 'ourBtlSaveDat', 'iGpffff843c': 'ourBtlSocket', 'iGpffff83f8': 'g_ptr_83f8',
    'iGpffff84f0': 'ourSSHSys', 'uGpffff8444': 'g_HNMSnd_sys',
}
CHR = {
    0xb0: 'flagsA', 0xb1: 'flagsA1', 0xb2: 'flagsA2', 0xb4: 'flagsB', 0xb5: 'flagsB1', 0xb6: 'flagsB2',
    0xb8: 'ailment', 0xb9: 'ailment2', 0xba: 'subId', 0xbc: 'formation', 0xc0: 'slot', 0x11c: 'namePtr',
    0x120: 'charId', 0x122: 'maxHP', 0x124: 'hp', 0x126: 'maxMP', 0x128: 'mp', 0x12a: 'maxSP', 0x12c: 'sp',
    0x12e: 'agl', 0x130: 'luc', 0x132: 'patk', 0x134: 'satk', 0x136: 'pdef', 0x138: 'sdef', 0x13a: 'nameSuffix',
    0x144: 'model', 0x148: 'monParam', 0x180: 'turnInterval', 0x184: 'turnTimer', 0x188: 'turnWaited',
    0x1ac: 'turnCount', 0x1b0: 'f_1b0', 0x1b4: 'nextTurnMul', 0x1b8: 'status', 0x508: 'vulnTurn', 0x510: 'vulnCount',
    0x514: 'vulnA', 0x518: 'vulnB', 0x51c: 'dmgVariance', 0x55c: 'atkTblIdx', 0x586: 'spFrac',
}
HDR = {
    0x24: 'flags24', 0x28: 'phase', 0x2a: 'step', 0x2c: 'actor', 0x2d: 'actor_b', 0x30: 'curTurnChr', 0x32: 'turnPendMask',
    0x36: 'comboCnt', 0x40: 'turnNo', 0x44: 'pcCnt', 0x4c: 'mode4c', 0x54: 'mask54', 0x90: 'f90',
    0x3edc: 'gmodFlags', 0x3ede: 'gmodStat', 0x3ee0: 'gmodVal', 0x3e14: 'turnTbl',
    0x43a4: 'monFormation', 0x43b2: 'escapeFlags', 0x45c2: 'noEvade', 0x45f0: 'comboMask', 0x45f4: 'resultFlags',
    0x4610: 'rewardExp', 0x4614: 'rewardCash', 0x4618: 'rewardSP',
}
def clean(text):
    text = re.sub(r'func_0x([0-9a-fA-F]{6,8})', lambda m: SYMS.get(int(m.group(1), 16), 'func_%s' % m.group(1)), text)
    for k, v in GP.items():
        text = text.replace(k, v)
    # chr[...] element access
    def chr_repl(m):
        typ, base, idx, off = m.group(1), m.group(2), m.group(3), int(m.group(4), 16)
        name = CHR.get(off) or 'f_%x' % off
        return '%s->chr[%s].%s' % (base, idx.strip(), name)
    text = re.sub(r'\*\((?:[a-z]+ )*\w+ \*\)\((\w+) \+ (?:\(?([^()+]*?)\)?) \* 0x4f0 \+ (0x[0-9a-fA-F]+)\)', lambda m: '%s->chr[%s].%s' % (m.group(1), m.group(2), CHR.get(int(m.group(3), 16)) or 'f_%x' % int(m.group(3), 16)), text)
    return text
if __name__ == '__main__':
    sys.stdout.write(clean(open(sys.argv[1]).read()))
