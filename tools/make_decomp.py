#!/usr/bin/env python3
"""Assemble decomp/H/<Class>.c from raw typed decompiler dumps (scratch dir of <addr>.c files)."""
import sys, os, re, glob, collections
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from protogen import proto
RAW = sys.argv[1]
OUT = os.path.join(ROOT, 'decomp/H')
# symbol tables
SYMS = {}
for l in open(os.path.join(ROOT, 'symbols/SLPM_602.19.syms')):
    p = l.split('\t')[0].split()
    if len(p) >= 6 and p[2] == 'FUNC':
        SYMS[int(p[0], 16)] = (p[5], int(p[1], 16))
GP = {'iGpffff847c': 'ourBtlSaveDat', 'iGpffff843c': 'ourBtlSocket', 'iGpffff83f8': 'g_83f8', 'iGpffff84f0': 'ourSSHSys',
      'uGpffff8444': 'sys__6HNMSnd_ptr', 'iGpffff86bc': 'g_86bc', 'iGpffff86c0': 'g_86c0'}
names = {}
for l in open(os.path.join(ROOT, 'tools/labels/BATTLE.BIN.funcs')):
    a, n = l.split()
    names[a] = n
def clean(t):
    t = re.sub(r'func_0x([0-9a-fA-F]{6,8})', lambda m: SYMS.get(int(m.group(1), 16), ('func_' + m.group(1), 0))[0], t)
    for k, v in GP.items(): t = t.replace(k, v)
    return t
def cls_of(n):
    m = re.match(r'^.*?__(\d+)(\w+)$', n)
    if m:
        k = int(m.group(1)); return m.group(2)[:k]
    if n.startswith('@'): return 'thunks'
    if re.match(r'^.*?__F', n): return 'BtlFree'
    return 'misc'
groups = collections.defaultdict(list)
for f in sorted(glob.glob(os.path.join(RAW, '*.c'))):
    a = os.path.basename(f)[:-2]
    if a not in names: continue
    txt = open(f).read().strip('\n')
    if txt.startswith('Error') or len(txt) < 10: continue
    n = names[a]
    sz = SYMS.get(int(a, 16), (n, 0))[1]
    r = proto(n) if not n.startswith('@') else None
    sig = ''
    if r:
        meth, cls, params = r
        sig = '%s%s(%s)' % ((cls + '::') if cls else '', meth, ', '.join(params))
    hdr = '/* ---------------------------------------------------------------------------\n * JP: 0x%s  %s\n * C++: %s\n * size: 0x%x bytes\n * --------------------------------------------------------------------------- */\n' % (a, n, sig or n, sz)
    groups[cls_of(n)].append((int(a, 16), hdr + clean(txt) + '\n'))
for c, items in groups.items():
    items.sort()
    with open(os.path.join(OUT, c + '.c'), 'w') as fh:
        fh.write('/* decomp/H/%s.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).\n * %d function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */\n#include "types.h"\n\n' % (c, len(items)))
        for _, body in items: fh.write(body + '\n')
    print(c, len(items))
