#!/usr/bin/env python3
"""Section E: match SLPM_602.19 (JP, symbols) main-exe functions to SLUS_210.41 (US, stripped) by normalised
instruction 3-grams, then filter with a longest-increasing-subsequence ordering check.
Output: notes/E/us_map_all.txt  (jp_addr us_addr name score jp_size us_size)  -- every main function; section filters are applied later.
Function starts on the US side come from the Ghidra function list (tools: curl 127.0.0.1:8089/list_functions?program=SLUS_210.41)."""
import struct, sys, re, os, collections, bisect
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
JP = "/Users/jamietheanything/Documents/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)/SLPM_602.19"
US = "/Users/jamietheanything/Documents/Sh2 Decomp/Shadow Hearts - Covenant (USA) (Disc 1)-1/SLUS_210.41"

def segs(path):
    d = open(path, 'rb').read()
    phoff = struct.unpack_from('<I', d, 0x1c)[0]; n = struct.unpack_from('<H', d, 0x2c)[0]
    out = []
    for i in range(n):
        t, off, va, pa, fs, ms, fl, al = struct.unpack_from('<8I', d, phoff + i * 32)
        if t == 1 and fs: out.append((va, d[off:off + fs]))
    return out

def words(segl, lo, hi):
    for va, b in segl:
        if va <= lo < va + len(b):
            n = (min(hi, va + len(b)) - lo) // 4
            return struct.unpack_from('<%dI' % n, b, lo - va)
    return ()

def norm(w):
    op = w >> 26
    if op == 0:
        return w
    if op in (2, 3):
        return op << 26
    if op == 1 or 4 <= op <= 7 or 20 <= op <= 23:
        return w & 0xffff0000
    if op in (0x11, 0x12):
        return w if (w >> 21) & 0x1f != 8 else w & 0xffff0000
    return w & 0xffff0000

N = 3
def grams(ws):
    s = [norm(x) for x in ws]
    return collections.Counter(tuple(s[i:i + N]) for i in range(max(len(s) - N + 1, 0))), len(s)

def dice(a, b):
    inter = sum((a & b).values())
    t = sum(a.values()) + sum(b.values())
    return 2.0 * inter / t if t else 0.0

def main():
    jps, uss = segs(JP), segs(US)
    jp = []
    for l in open(os.path.join(ROOT, 'symbols/SLPM_602.19.syms')):
        p = l.split()
        if len(p) >= 6 and p[2] == 'FUNC' and p[4] == 'main' and not p[5].startswith('sce'):
            jp.append((int(p[0], 16), int(p[1], 16), p[5]))
    jp.sort()
    us = []
    for l in open(sys.argv[1]):
        m = re.match(r'(\S+) at ([0-9a-f]+)$', l.strip())
        if m: us.append((int(m.group(2), 16), m.group(1)))
    us.sort()
    usf = []
    for i, (a, n) in enumerate(us):
        e = us[i + 1][0] if i + 1 < len(us) else a + 16
        usf.append((a, e - a, n))
    ug = [grams(words(uss, a, a + s)) for a, s, n in usf]
    inv = collections.defaultdict(list)
    for fi, (c, n) in enumerate(ug):
        for g in c: inv[g].append(fi)
    res = {}
    for a, s, n in jp:
        if s < 16: continue
        c, ln = grams(words(jps, a, a + s))
        if not c: continue
        cand = collections.Counter()
        for g in c:
            lst = inv.get(g)
            if lst and len(lst) < 30:
                for fi in lst: cand[fi] += 1
        best = (0, None)
        for fi, _ in cand.most_common(10):
            sc = dice(c, ug[fi][0])
            if sc > best[0]: best = (sc, fi)
        if best[1] is not None and best[0] >= 0.6:
            ua, usz, un = usf[best[1]]
            res[a] = (ua, best[0], s, usz, n)
    # ordering filter: longest increasing subsequence on US address when JP sorted
    keys = sorted(res)
    seq = [res[k][0] for k in keys]
    # patience LIS with strictly increasing
    tails, idx, prev = [], [], [-1] * len(seq)
    for i, v in enumerate(seq):
        j = bisect.bisect_left(tails, v)
        if j == len(tails): tails.append(v); idx.append(i)
        else: tails[j] = v; idx[j] = i
        prev[i] = idx[j - 1] if j else -1
    keep = set(); k = idx[-1] if idx else -1
    while k >= 0: keep.add(k); k = prev[k]
    out = os.path.join(ROOT, 'notes/E/us_map_all.txt')
    with open(out, 'w') as f:
        f.write('# jp_addr us_addr name score jp_size us_size  (E_usmatch.py: 3-gram dice + LIS ordering filter; all main functions)\n')
        for i, k in enumerate(keys):
            ua, sc, js, usz, n = res[k]
            f.write('%08x %08x %s %.3f %d %d %s\n' % (k, ua, n, sc, js, usz, 'ok' if i in keep else 'outlier'))
    print(len(res), 'matched', len(keep), 'ordered')

main()
