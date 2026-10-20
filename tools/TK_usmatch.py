"""Match Taikenban (SLPM_602.14) functions to US retail, to recover the 455 names that the
Furokuban symbol table (SLPM_602.19) does not contain.

Method is deliberately the same as tools/usmatch.py: normalised-instruction 3-gram Dice
score, a longest-increasing-subsequence ordering filter to keep only monotonic anchors,
then in-order gap filling, then a size-ratio sanity check. `norm()` is copied verbatim.

Two differences from usmatch.py:
  * the US candidate universe is taken from the verified oracle CSVs in recomp/
    (recomp/{main,battle,field}_us_funcs.csv -- real boundaries, not a prologue guess),
    topped up with prologue-derived starts so that currently UNNAMED US functions are
    reachable. Matching a new name onto an already-named US function is a conflict, not a
    win, so those are reported separately.
  * it runs for all three modules.

Geometry (verified 2026-10-20):
  Taikenban overlays load at 0x003FE800   (Furokuban 0x00430A00, JP retail 0x00455800,
                                           US retail 0x0045EA80 -- four different bases)
  main sections: vaddr 0x00200000, file offset 0x100, in all of .14/.19/SLUS_210.41
"""
import collections, bisect, csv, os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))     # sh2-decomp/
WS = os.path.dirname(ROOT)                                             # workspace root
RECOMP = os.path.join(WS, "recomp")
OUT = os.path.join(ROOT, "notes", "TK")
N = 3

TK_OVL_BASE = 0x003FE800
US_OVL_BASE = 0x0045EA80
MAIN_VADDR, MAIN_OFF = 0x00200000, 0x100

MODULES = {
    "main": dict(
        tk=(os.path.join(WS, "SH2TK", "extracted", "SLPM_602.14"), MAIN_OFF, MAIN_VADDR),
        us=(os.path.join(WS, "SH2US", "SLUS_210.41"), MAIN_OFF, MAIN_VADDR),
        csv=os.path.join(RECOMP, "main_us_funcs.csv"),
    ),
    "BATTLE.BIN": dict(
        tk=(os.path.join(WS, "SH2TK", "extracted", "BATTLE.BIN"), 0, TK_OVL_BASE),
        us=(os.path.join(WS, "SH2US", "BATTLE.BIN"), 0, US_OVL_BASE),
        csv=os.path.join(RECOMP, "battle_us_funcs.csv"),
    ),
    "FIELD.BIN": dict(
        tk=(os.path.join(WS, "SH2TK", "extracted", "FIELD.BIN"), 0, TK_OVL_BASE),
        us=(os.path.join(WS, "SH2US", "FIELD.BIN"), 0, US_OVL_BASE),
        csv=os.path.join(RECOMP, "field_us_funcs.csv"),
    ),
}


def norm(w):
    """Verbatim from tools/usmatch.py -- masks immediates/offsets/branch targets so that two
    builds of the same function compare equal."""
    op = w >> 26
    if op == 0:
        return w
    if op in (2, 3):
        return op << 26
    if op == 1 or 4 <= op <= 7 or op in (20, 21, 22, 23):
        return w & 0xFFFF0000
    if op == 0x11 or op == 0x12:
        return w if (w >> 21) & 0x1F not in (8,) else w & 0xFFFF0000
    if op in (0x0F, 0x09, 0x0D, 0x0C, 0x0E, 0x08, 0x0A, 0x0B, 0x19):
        return w & 0xFFFF0000
    return w & 0xFFFF0000


def words(path, off, size=None):
    d = open(path, "rb").read()
    d = d[off:] if size is None else d[off:off + size]
    return struct.unpack_from("<%dI" % (len(d) // 4), d, 0)


def load_syms(which):
    """FUNC symbols of one module from the Taikenban symbol table: addr -> (size, name)."""
    out = {}
    p = os.path.join(ROOT, "symbols", "SLPM_602.14.syms")
    for ln in open(p):
        f = ln.split("\t")[0].split()
        if len(f) >= 6 and f[2] == "FUNC" and f[4] == which:
            out[int(f[0], 16)] = (int(f[1], 16), f[5])
    return out


def new_names():
    """The genuine names present in .14 and absent from .19 (no adjustor thunks)."""
    def names(p):
        s = set()
        for ln in open(os.path.join(ROOT, "symbols", p)):
            f = ln.split("\t")[0].split()
            if len(f) >= 6 and f[2] == "FUNC":
                s.add(f[5])
        return s
    return {n for n in names("SLPM_602.14.syms") - names("SLPM_602.19.syms")
            if not n.startswith("@")}


def us_universe(cfg, uw, base):
    """Verified boundaries from the oracle CSV, plus prologue-derived starts for the US
    functions that are not named yet. Returns (list of (s,e) word indices, named set)."""
    named = {}
    with open(cfg["csv"]) as fh:
        r = csv.reader(fh)
        next(r)
        for name, start, end, _sz in r:
            named[int(start, 16)] = name
    starts = set(named)
    # prologue candidates: addiu/daddiu sp,sp,-N preceded by nop / jr ra (usmatch.py's rule)
    for i, w in enumerate(uw):
        if (w & 0xFFFF8000) in (0x27BD8000, 0x67BD8000):
            p = uw[i - 1] if i else 0
            if p == 0 or p == 0x03E00008 or (i >= 2 and uw[i - 2] == 0x03E00008):
                starts.add(base + i * 4)
    st = sorted(s for s in starts if base <= s < base + len(uw) * 4)
    funcs, idx = [], []
    for k, a in enumerate(st):
        nxt = st[k + 1] if k + 1 < len(st) else base + len(uw) * 4
        funcs.append(((a - base) // 4, (nxt - base) // 4))
        idx.append(a)
    return funcs, idx, named


def grams(w, s, e):
    seq = [norm(x) for x in w[s:e]]
    return collections.Counter(tuple(seq[i:i + N]) for i in range(max(len(seq) - N + 1, 0)))


def match_module(mod, wanted):
    cfg = MODULES[mod]
    tkp, tko, tkb = cfg["tk"]
    usp, uso, usb = cfg["us"]
    jw = words(tkp, tko)
    uw = words(usp, uso)
    syms = load_syms(mod)
    us_f, us_a, named = us_universe(cfg, uw, usb)

    tk_idx = []
    for a, (size, n) in sorted(syms.items()):
        if n.startswith("@"):
            continue
        s = (a - tkb) // 4
        if s < 0 or s >= len(jw):
            continue
        tk_idx.append((s, s + max(size // 4, 1), a, n))

    print("[%s] taikenban funcs %d (%d of them new), us candidates %d (%d already named)"
          % (mod, len(tk_idx), sum(1 for _, _, _, n in tk_idx if n in wanted),
             len(us_f), len(named)))

    us_g = [grams(uw, s, e) for s, e in us_f]
    inv = collections.defaultdict(list)
    for fi, c in enumerate(us_g):
        for g in c:
            inv[g].append(fi)

    # pass 1: best-scoring candidate per TK function, biggest functions first
    res, used = {}, set()
    for s, e, a, n in sorted(tk_idx, key=lambda t: -(t[1] - t[0])):
        c = grams(jw, s, e)
        if not c:
            continue
        cand = collections.Counter()
        for g in c:
            lst = inv.get(g)
            if lst and len(lst) < 40:
                for fi in lst:
                    cand[fi] += 1
        best = None
        tot = sum(c.values())
        for fi, _ in cand.most_common(8):
            if fi in used:
                continue
            c2 = us_g[fi]
            score = 2.0 * sum((c & c2).values()) / (tot + sum(c2.values()))
            if best is None or score > best[0]:
                best = (score, fi)
        if best:
            res[a] = (best[1], best[0])
            if best[0] >= 0.5:
                used.add(best[1])

    # pass 2: keep only a monotonic (order-preserving) subset of the confident matches
    good = sorted((a, v) for a, v in res.items() if v[1] >= 0.6)
    seq = [us_a[v[0]] for _, v in good]
    tails, prev = [], [-1] * len(seq)
    for i, x in enumerate(seq):
        j = bisect.bisect_left([seq[t] for t in tails], x)
        if j == len(tails):
            tails.append(i)
        else:
            tails[j] = i
        prev[i] = tails[j - 1] if j > 0 else -1
    keep = []
    if tails:
        k = tails[-1]
        while k != -1:
            keep.append(k)
            k = prev[k]
    anchors = {good[i][0]: good[i][1] for i in sorted(keep)}
    print("      pass1 %d, confident(>=0.6) %d, monotonic anchors %d"
          % (len(res), len(good), len(anchors)))

    # pass 3: in-order gap filling between anchors
    info = {a: (s, e, n) for s, e, a, n in tk_idx}
    used_fi = {v[0] for v in anchors.values()}
    anch = sorted(anchors.items())
    added = 0
    bounds = [(0, -1)] + [(a, v[0]) for a, v in anch] + [(0xFFFFFFFF, len(us_f))]
    for (lo_a, lo_fi), (hi_a, hi_fi) in zip(bounds, bounds[1:]):
        js = [a for a in sorted(info) if lo_a < a < hi_a and a not in anchors]
        cands = [fi for fi in range(lo_fi + 1, hi_fi) if fi not in used_fi]
        if not js or not cands:
            continue
        pos = 0
        for a in js:
            s, e, n = info[a]
            cj = grams(jw, s, e)
            if not cj:
                continue
            tot = sum(cj.values())
            best = None
            for fi in cands[pos:pos + 6]:
                c2 = us_g[fi]
                sc = 2.0 * sum((cj & c2).values()) / (tot + sum(c2.values()))
                if best is None or sc > best[0]:
                    best = (sc, fi)
            if best and best[0] >= 0.3:
                anchors[a] = (best[1], best[0])
                used_fi.add(best[1])
                pos = cands.index(best[1]) + 1
                added += 1
    print("      gap-filled %d -> %d total" % (added, len(anchors)))

    # size-ratio sanity, then split into new names vs conflicts
    rows = []
    for a, (fi, sc) in sorted(anchors.items()):
        s, e, n = info[a]
        tk_sz, us_sz = (e - s) * 4, (us_f[fi][1] - us_f[fi][0]) * 4
        ratio = us_sz / max(tk_sz, 1)
        ok = (0.75 <= ratio <= 1.35) or sc >= 0.93
        rows.append((a, us_a[fi], n, sc, ratio, ok, named.get(us_a[fi])))
    return rows


def main():
    os.makedirs(OUT, exist_ok=True)
    wanted = new_names()
    print("genuine .14-only names: %d\n" % len(wanted))
    allrows, summary = [], {}
    for mod in ("main", "BATTLE.BIN", "FIELD.BIN"):
        rows = match_module(mod, wanted)
        got = [r for r in rows if r[2] in wanted]
        kept = [r for r in got if r[5] and not r[6]]
        conflict = [r for r in got if r[5] and r[6]]
        badsize = [r for r in got if not r[5]]
        summary[mod] = (len(got), len(kept), len(conflict), len(badsize))
        print("      NEW names matched %d -> kept %d, name-conflict %d, size-rejected %d\n"
              % (len(got), len(kept), len(conflict), len(badsize)))
        for r in rows:
            allrows.append((mod,) + r)

    with open(os.path.join(OUT, "us_map_tk.txt"), "w", newline="\n") as fh:
        fh.write("# module tk_addr us_addr name score us/tk_size_ratio status\n")
        fh.write("# Taikenban SLPM_602.14 -> SLUS_210.41 retail, by tools/TK_usmatch.py\n")
        fh.write("# status: new = names a US function nothing had named; conflict = that US\n")
        fh.write("#   address already carries a SLPM_602.19-derived name; size = ratio rejected\n")
        for mod, a, ua, n, sc, ratio, ok, existing in allrows:
            st = "size" if not ok else ("conflict:" + existing if existing else "new")
            fh.write("%s %08x %08x %s %.3f %.2f %s\n" % (mod, a, ua, n, sc, ratio, st))

    print("=== summary (new .14-only names only) ===")
    print("%-12s %7s %7s %9s %7s" % ("module", "matched", "kept", "conflict", "size"))
    for m, (g, k, c, b) in summary.items():
        print("%-12s %7d %7d %9d %7d" % (m, g, k, c, b))
    print("\nwrote %s" % os.path.join(OUT, "us_map_tk.txt"))


main()
