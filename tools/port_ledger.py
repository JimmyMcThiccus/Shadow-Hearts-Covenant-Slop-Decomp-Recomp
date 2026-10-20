"""Function-level port ledger.

For every FUNC in the JP symbol table (SLPM_602.19, the name source for SLUS_210.41) decide whether the Rust port
already references it.  "Referenced" = the port source contains one of
  * the JP address (`0x003b6f40` / `003b6f40`), or the US address from notes/I/us_map_N*.txt
  * the mangled name (`Polling__6SSHSysFv`)
  * the demangled `Class::Method` (or `Class::Class` / `Class::~Class` for ctors / dtors)
  * for free functions: the bare name as a whole word (names of 6+ chars only, to keep noise down)
SDK / libc / runtime functions (module map `SCE:*`, `_`-prefixed, MW runtime) are counted separately and not expected
to be ported (they map to Rust std / Bevy).

Writes notes/integration/port_ledger.md (summary per class) and port_ledger.tsv (one row per function).
Usage:  python -I tools/port_ledger.py
"""
import os
import re
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMS = os.path.join(ROOT, "symbols", "SLPM_602.19.syms")
MODMAP = os.path.join(ROOT, "symbols", "SLPM_602.19_module_map.txt")
PORT = os.path.join(ROOT, "port", "crates")
OUT_MD = os.path.join(ROOT, "notes", "integration", "port_ledger.md")
OUT_TSV = os.path.join(ROOT, "notes", "integration", "port_ledger.tsv")

SDK_PREFIXES = ("sce", "_", "mw", "__", "Sif", "Sdr", "Isce", "isce")
SDK_FREE = set("""memclr memcpy memset memmove strcpy strncpy strcmp strncmp strlen strcat sprintf vsprintf printf puts
malloc free realloc calloc abs labs atoi atof strtol strtoul qsort rand srand sin cos tan atan atan2 sqrt sqrtf fabs floor
ceil fmod pow exp log log10 sinf cosf atan2f acosf asinf main WaitDma WatchDma CheckAddress""".split())


def demangle(m):
    """Metrowerks/cfront mangling, enough for Class::Method.  Returns (cls, method) ; cls None for free functions."""
    base = m
    if base.startswith("__ct__"):
        mm = re.match(r"__ct__(\d+)([A-Za-z_]\w*)", base)
        if mm:
            cls = mm.group(2)[: int(mm.group(1))]
            return cls, cls
    if base.startswith("__dt__"):
        mm = re.match(r"__dt__(\d+)([A-Za-z_]\w*)", base)
        if mm:
            cls = mm.group(2)[: int(mm.group(1))]
            return cls, "~" + cls
    i = base.find("__", 1)
    if i <= 0:
        return None, base
    name, rest = base[:i], base[i + 2:]
    mm = re.match(r"(\d+)([A-Za-z_]\w*)", rest)
    if mm and not rest.startswith("F"):
        n = int(mm.group(1))
        cls = mm.group(2)[:n]
        if len(cls) == n:
            return cls, name
    return None, name


def load_modmap():
    spans = []
    for line in open(MODMAP, encoding="utf-8", errors="replace"):
        mm = re.match(r"([0-9a-f]{8})-([0-9a-f]{8})\s+\d+\s+(\S+)", line)
        if mm:
            spans.append((int(mm.group(1), 16), int(mm.group(2), 16), mm.group(3)))
    return spans


def load_us_addrs():
    m = defaultdict(set)  # jp addr -> us addrs ; also name -> us addrs
    for fn in ("us_map_N4.txt", "us_map_N5.txt"):
        p = os.path.join(ROOT, "notes", "I", fn)
        if not os.path.exists(p):
            continue
        for line in open(p, encoding="utf-8", errors="replace"):
            if line.startswith("#"):
                continue
            f = line.split()
            if fn == "us_map_N4.txt" and len(f) >= 3:
                m[f[0].lower()].add(f[1].lower())
            elif len(f) >= 4:
                m[f[1].lower()].add(f[2].lower())
    return m


def main():
    text = []
    for d, _, files in os.walk(PORT):
        for f in files:
            if f.endswith(".rs"):
                text.append(open(os.path.join(d, f), encoding="utf-8", errors="replace").read())
    blob = "\n".join(text)
    low = blob.lower()
    words = set(re.findall(r"[A-Za-z_]\w{5,}", blob))
    pairs = set(re.findall(r"([A-Za-z_]\w*)::(~?[A-Za-z_]\w*)", blob))
    hexes = set(re.findall(r"(?:0x)?([0-9a-f]{6,8})\b", low))
    hexes = {h.zfill(8) for h in hexes}

    spans = load_modmap()
    us = load_us_addrs()
    rows = []
    for line in open(SYMS, encoding="utf-8", errors="replace"):
        f = line.split()
        if len(f) < 6 or f[2] != "FUNC":
            continue
        addr, size, module, name = f[0].lower(), int(f[1], 16), f[4], f[5]
        a = int(addr, 16)
        lib = ""
        if module == "main":
            for lo, hi, tag in spans:
                if lo <= a < hi:
                    lib = tag
                    break
        cls, meth = demangle(name)
        sdk = lib.startswith("SCE:") or (cls is None and (name.startswith(SDK_PREFIXES) or meth in SDK_FREE))
        hit = ""
        if addr in hexes:
            hit = "jp_addr"
        elif any(u.zfill(8) in hexes for u in us.get(addr, ())):
            hit = "us_addr"
        elif name in blob:
            hit = "mangled"
        elif cls and (cls, meth) in pairs:
            hit = "Class::Method"
        elif cls is None and len(meth) >= 6 and meth in words:
            hit = "name"
        elif cls and cls in words and len(cls) >= 4:
            hit = "class_only"
        rows.append((module, addr, size, cls or "", meth, name, "sdk" if sdk else "game", hit))

    with open(OUT_TSV, "w", encoding="utf-8") as o:
        o.write("module\tjp_addr\tsize\tclass\tmethod\tmangled\tkind\tport_ref\n")
        for r in rows:
            o.write("\t".join(str(x) for x in r) + "\n")

    game = [r for r in rows if r[6] == "game"]
    by_mod = defaultdict(lambda: [0, 0, 0, 0])
    by_cls = defaultdict(lambda: [0, 0, 0, 0, ""])
    for r in game:
        k = by_mod[r[0]]
        k[0] += 1; k[2] += r[2]
        if r[7] and r[7] != "class_only":
            k[1] += 1; k[3] += r[2]
        c = by_cls[(r[0], r[3] or "<free>")]
        c[0] += 1; c[2] += r[2]
        if r[7] and r[7] != "class_only":
            c[1] += 1; c[3] += r[2]
        if r[7] == "class_only":
            c[4] = "yes"
    with open(OUT_MD, "w", encoding="utf-8") as o:
        o.write("# Function-level port ledger\n\nGenerated by `python -I tools/port_ledger.py` from the JP symbol table (name source for "
                "SLUS_210.41) and the Rust sources under `port/crates`.  A function counts as *referenced* when the port names it "
                "(JP / US address, mangled name, `Class::Method`, or a free function's name).  This is a lower bound on what is "
                "ported: much of the port reimplements behaviour without naming every original function, and a reference is not "
                "proof of a faithful port.  SDK / libc / runtime functions (%d) are excluded.  Per-function rows: `port_ledger.tsv`.\n\n"
                % (len(rows) - len(game)))
        o.write("| module | game funcs | referenced | % | code bytes | referenced bytes | % |\n|---|---|---|---|---|---|---|\n")
        tot = [0, 0, 0, 0]
        for m, k in sorted(by_mod.items()):
            o.write("| %s | %d | %d | %.0f | %d | %d | %.0f |\n" % (m, k[0], k[1], 100 * k[1] / k[0], k[2], k[3], 100 * k[3] / max(1, k[2])))
            tot = [a + b for a, b in zip(tot, k)]
        o.write("| **all** | %d | %d | %.0f | %d | %d | %.0f |\n\n" % (tot[0], tot[1], 100 * tot[1] / tot[0], tot[2], tot[3], 100 * tot[3] / tot[2]))
        o.write("## Largest unreferenced classes (by code bytes)\n\n| module | class | funcs | referenced | unreferenced bytes |\n|---|---|---|---|---|\n")
        gaps = sorted(by_cls.items(), key=lambda kv: -(kv[1][2] - kv[1][3]))
        for (m, c), k in gaps[:150]:
            o.write("| %s | %s | %d | %d | %d |\n" % (m, c, k[0], k[1], k[2] - k[3]))
    print("game %d referenced %d (%.1f%%), bytes %.1f%%" % (tot[0], tot[1], 100 * tot[1] / tot[0], 100 * tot[3] / tot[2]))


if __name__ == "__main__":
    sys.exit(main())
