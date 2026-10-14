#!/usr/bin/env python3
"""Match JP BATTLE.BIN functions to the stripped US BATTLE.BIN by normalised instruction n-grams.
Writes notes/H/us_map.txt  (jp_addr us_addr name score)."""
import struct, sys, collections, re, os, json
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
jp = open(os.path.join(ROOT, 'overlays/SH2JP_BATTLE.BIN'), 'rb').read()
us = open(os.path.join(ROOT, 'overlays/SH2US_BATTLE.BIN'), 'rb').read()
JPB, USB = 0x430a00, 0x45ea80
def words(d): return struct.unpack('<%dI' % (len(d) // 4), d[:len(d) // 4 * 4])
jw, uw = words(jp), words(us)
def norm(w):
    op = w >> 26
    if op == 0:                       # SPECIAL
        return w & ~0 if False else w   # keep registers and funct
    if op in (2, 3):                  # j / jal
        return op << 26
    if op == 1 or 4 <= op <= 7 or op in (20, 21, 22, 23):   # branches
        return w & 0xffff0000
    if op == 0x11 or op == 0x12:      # COP1 / COP2
        return w if (w >> 21) & 0x1f not in (8,) else w & 0xffff0000
    if op in (0x0f, 0x09, 0x0d, 0x0c, 0x0e, 0x08, 0x0a, 0x0b, 0x19):   # lui addiu ori andi xori addi slti sltiu daddiu
        return w & 0xffff0000
    return w & 0xffff0000             # loads/stores/others: drop offset
def starts_us():
    # candidate function starts: 'addiu/daddiu sp,sp,-N' (27bd / 67bd with negative imm) preceded by jr ra/nop padding or at 16-byte alignment
    s = []
    for i, w in enumerate(uw):
        if (w & 0xffff8000) == 0x27bd8000 or (w & 0xffff8000) == 0x67bd8000:
            # require previous instruction to be nop or jr ra delay slot (start of function): accept if prev is jr ra or nop or j
            p = uw[i - 1] if i else 0
            if p == 0 or p == 0x03e00008 or (i >= 2 and uw[i - 2] == 0x03e00008):
                s.append(i)
    return s
def build_funcs(w, starts, total):
    out = []
    for k, s in enumerate(starts):
        e = starts[k + 1] if k + 1 < len(starts) else total
        out.append((s, e))
    return out
jp_funcs = []
for l in open(os.path.join(ROOT, 'tools/labels/BATTLE.BIN.funcs')):
    a, n = l.split(); jp_funcs.append((int(a, 16), n))
syms = {}
for l in open(os.path.join(ROOT, 'symbols/SLPM_602.19.syms')):
    p = l.split('\t')[0].split()
    if len(p) >= 6 and p[4] == 'BATTLE.BIN': syms[int(p[0], 16)] = int(p[1], 16)
jp_idx = []
for a, n in jp_funcs:
    s = (a - JPB) // 4; size = syms.get(a, 0) or 0
    e = s + max(size // 4, 1)
    jp_idx.append((s, e, a, n))
us_st = starts_us()
us_f = build_funcs(uw, us_st, len(uw))
print('us candidates', len(us_f), 'jp funcs', len(jp_idx), file=sys.stderr)
N = 3
def grams(w, s, e):
    seq = [norm(x) for x in w[s:e]]
    c = collections.Counter(tuple(seq[i:i + N]) for i in range(max(len(seq) - N + 1, 0)))
    return seq, c
us_g = [grams(uw, s, e) for s, e in us_f]
inv = collections.defaultdict(list)
for fi, (seq, c) in enumerate(us_g):
    for g in c: inv[g].append(fi)
res = []
used = set()
order = sorted(range(len(jp_idx)), key=lambda i: -(jp_idx[i][1] - jp_idx[i][0]))
for i in order:
    s, e, a, n = jp_idx[i]
    if n.startswith('@'): continue
    seq, c = grams(jw, s, e)
    if not c: continue
    cand = collections.Counter()
    for g, k in c.items():
        lst = inv.get(g)
        if lst and len(lst) < 40:
            for fi in lst: cand[fi] += 1
    best = None
    for fi, _ in cand.most_common(8):
        if fi in used: continue
        c2 = us_g[fi][1]
        inter = sum((c & c2).values())
        score = 2.0 * inter / (sum(c.values()) + sum(c2.values()))
        if best is None or score > best[0]: best = (score, fi)
    if best:
        res.append((a, USB + us_f[best[1]][0] * 4, n, best[0], best[1]))
        if best[0] >= 0.5: used.add(best[1])
res.sort()
with open(os.path.join(ROOT, 'notes/H/us_map_candidates.txt'), 'w') as fh:
    for a, ua, n, sc, fi in res:
        fh.write('%08x %08x %s %.3f\n' % (a, ua, n, sc))
import statistics
print(len(res), sum(1 for r in res if r[3] >= 0.8), sum(1 for r in res if r[3] >= 0.6), file=sys.stderr)

# ---- second pass: monotonic anchors + gap filling ----------------------------------------
import bisect
by_jp = {a: (ua, n, sc, fi) for a, ua, n, sc, fi in res}
good = sorted((a, v) for a, v in by_jp.items() if v[2] >= 0.6)
seq = [v[0] for a, v in good]
tails = []; prev = [-1] * len(seq)
for i, x in enumerate(seq):
    j = bisect.bisect_left([seq[t] for t in tails], x)
    if j == len(tails): tails.append(i)
    else: tails[j] = i
    prev[i] = tails[j - 1] if j > 0 else -1
k = tails[-1]; keep = []
while k != -1: keep.append(k); k = prev[k]
keep = sorted(keep)
anchors = [(good[i][0], good[i][1]) for i in keep]      # (jp_addr, (us_addr,name,score,fi))
final = {a: (v[0], v[2], v[3]) for a, v in anchors}
usedfi = {v[3] for a, v in anchors}
# gap filling
allj = [(a, n) for a, n in jp_funcs if not n.startswith('@')]
ai = 0
anch_sorted = sorted(final.items())
def gaps():
    prev_jp, prev_us = 0, 0
    for a, (ua, sc, fi) in anch_sorted + [(0xffffffff, (0xffffffff, 1, len(us_f)))]:
        yield prev_jp, prev_us, a, ua
        prev_jp, prev_us = a, ua
jp_info = {a: (s, e, n) for s, e, a, n in jp_idx}
added = 0
for lo_jp, lo_us, hi_jp, hi_us in gaps():
    js = [a for a, n in allj if lo_jp < a < hi_jp and a not in final]
    us_c = [fi for fi, (s, e) in enumerate(us_f) if lo_us < USB + s * 4 < hi_us and fi not in usedfi]
    if not js or not us_c: continue
    # greedy in order
    pos = 0
    for a in js:
        s, e, n = jp_info[a]
        seqj, cj = grams(jw, s, e)
        if not cj: continue
        best = None
        for fi in us_c[pos:pos + 6]:
            c2 = us_g[fi][1]
            inter = sum((cj & c2).values())
            sc = 2.0 * inter / (sum(cj.values()) + sum(c2.values()))
            if best is None or sc > best[0]: best = (sc, fi)
        if best and best[0] >= 0.3:
            final[a] = (USB + us_f[best[1]][0] * 4, best[0], best[1]); usedfi.add(best[1])
            pos = us_c.index(best[1]) + 1; added += 1
out = sorted(final.items())
def ratio(a, fi):
    js = jp_info[a][1] - jp_info[a][0]; us_ = us_f[fi][1] - us_f[fi][0]
    return us_ / max(js, 1)
kept = []; dropped = []
for a, (ua, sc, fi) in out:
    r = ratio(a, fi)
    ok = (0.75 <= r <= 1.35) or sc >= 0.93
    (kept if ok else dropped).append((a, ua, sc, r))
with open(os.path.join(ROOT, 'notes/H/us_map.txt'), 'w') as fh:
    fh.write('# jp_addr us_addr name score   (score = 3-gram dice on masked instructions; ordering/size verified, see tools/usmatch.py)\n')
    for a, ua, sc, r in kept:
        fh.write('%08x %08x %s %.3f\n' % (a, ua, jp_info[a][2], sc))
print('kept', len(kept), 'dropped(size)', len(dropped), file=sys.stderr)
print('final matches', len(out), 'gap-added', added, '>=0.8:', sum(1 for a, v in out if v[1] >= 0.8), file=sys.stderr)
