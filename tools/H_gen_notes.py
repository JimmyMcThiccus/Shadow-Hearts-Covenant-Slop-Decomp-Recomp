#!/usr/bin/env python3
"""Generate notes/H/<Class>.md: method inventory (JP/US addresses, size, C++ signature) and an
observed-field-offset table (derived from the cleaned decompilation in decomp/H/<Class>.c).
Hand-written prose lives in tools/H_notes_prose.py (class -> text); this script merges both."""
import re, os, sys, collections, glob
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from protogen import proto
from H_notes_prose import PROSE
us = {}
for l in open(os.path.join(ROOT, 'notes/H/us_map.txt')):
    if l.startswith('#'): continue
    p = l.split(); us[p[0]] = (p[1], p[3])
SZ = {}
for l in open(os.path.join(ROOT, 'symbols/SLPM_602.19.syms')): pass
funcs = []
for l in open(os.path.join(ROOT, 'tools/labels/BATTLE.BIN.funcs')):
    a, n = l.split(); funcs.append((int(a, 16), n))
funcs.sort()
size = {}
for i, (a, n) in enumerate(funcs):
    size[a] = (funcs[i + 1][0] - a) if i + 1 < len(funcs) else 0
def cls_of(n):
    m = re.match(r'^.*?__(\d+)(\w+)$', n)
    if m: return m.group(2)[:int(m.group(1))]
    if n.startswith('@'): return 'thunks'
    if re.match(r'^.*?__F', n): return 'BtlFree'
    return 'misc'
by = collections.defaultdict(list)
for a, n in funcs: by[cls_of(n)].append((a, n))
FLD = re.compile(r'\*\((\w+(?: \*)?) \*\)\((?:param_1|this) \+ (0x[0-9a-f]+|\d+)\)')
TYP = {'undefined4': 'u32', 'undefined2': 'u16', 'undefined1': 'u8', 'undefined8': 'u64', 'undefined': 'u8'}
def fields(cls):
    path = os.path.join(ROOT, 'decomp/H', cls + '.c')
    if not os.path.exists(path): return {}
    txt = open(path).read()
    out = collections.defaultdict(lambda: [collections.Counter(), set()])
    for blk in re.split(r'/\* -{20,}\n \* JP: ', txt)[1:]:
        m = re.match(r'0x([0-9a-f]{8})\s+(\S+)', blk)
        if not m: continue
        meth = m.group(2).split('__')[0] or m.group(2)
        # only methods whose first param is the object (not static/free)
        hdr = re.search(r'\n(\w[\w \*]*?) ?\*?(\w+__\w+)\s*\(([^)]*)\)', blk)
        for t, off in FLD.findall(blk):
            o = int(off, 0)
            if o > 0x8000: continue
            out[o][0][TYP.get(t, t)] += 1; out[o][1].add(meth)
    return out
os.makedirs(os.path.join(ROOT, 'notes/H'), exist_ok=True)
GROUPS = {}
for c, items in sorted(by.items()):
    if c in ('thunks', 'misc', 'FVector', 'CPad', 'Matrix', '_rgba32', 'JRing', 'MenuObj'): continue
    md = ['# %s' % c, '']
    md.append(PROSE.get(c, '_No hand-written commentary yet; see inventory and field table below (auto-generated from decomp/H/%s.c)._' % c))
    md.append('')
    md.append('## Methods (%d)' % len(items))
    md.append('')
    md.append('| JP addr | US addr | ~size | C++ |')
    md.append('|---|---|---|---|')
    for a, n in items:
        key = '%08x' % a
        u = us.get(key, ('', ''))[0]
        r = proto(n) if not n.startswith('@') else None
        sig = '`%s%s(%s)`' % ((r[1] + '::') if r and r[1] else '', r[0], ', '.join(r[2])) if r else '`%s`' % n
        md.append('| %08x | %s | 0x%x | %s |' % (a, u, size[a], sig))
    f = fields(c)
    if f:
        md.append('')
        md.append('## Observed field offsets (`this + off`, from decompiled accesses)')
        md.append('')
        md.append('| off | type(s) seen | #uses | methods |')
        md.append('|---|---|---|---|')
        for o in sorted(f):
            cnt, ms = f[o]
            md.append('| +0x%x | %s | %d | %s |' % (o, '/'.join(t for t, _ in cnt.most_common(3)), sum(cnt.values()), ', '.join(sorted(ms)[:6]) + ('…' if len(ms) > 6 else '')))
    open(os.path.join(ROOT, 'notes/H', c + '.md'), 'w').write('\n'.join(md) + '\n')
    GROUPS[c] = len(items)
print(len(GROUPS), 'class notes')
