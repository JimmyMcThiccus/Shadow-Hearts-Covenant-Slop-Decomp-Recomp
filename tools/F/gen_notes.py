#!/usr/bin/env python3
"""Generate notes/F/<Class>.md skeletons (layout, vtable, function table, constructors' callers) and merge
the hand-written descriptions from DESC. usage: gen_notes.py SCRATCH_DIR OUT_DIR"""
import json, re, sys, os, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fields, importlib
S, OUT = sys.argv[1], sys.argv[2]
idx = json.load(open(S + "/raw/_index.json"))
vt = json.load(open(S + "/vtables.json"))
callers = json.load(open(S + "/ctor_callers.json"))
exec(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "clean.py")).read().split("# ------------------------------------------------------------------ demangler")[1].split("SLOTS =")[0].replace("RAW, OUT", "_,_"), globals())
from descs import DESC, BASES

by = collections.OrderedDict()
for a, sz, n, c in idx:
    k = cls_of(n) or c
    by.setdefault(k, []).append((a, sz, n))

os.makedirs(OUT, exist_ok=True)
for k, lst in by.items():
    if k in ("?", None): continue
    fn = re.sub(r"[^\w]", "_", k)
    d = DESC.get(k, {})
    L = ["# %s\n" % k]
    if k in BASES: L.append("Base class: `%s`\n" % BASES[k])
    L.append(d.get("what", "_(see decomp/F/%s.c)_" % fn) + "\n")
    if "flow" in d:
        L.append("## Behaviour\n\n" + d["flow"] + "\n")
    fm = fields.F.get(k)
    if fm and fm[1]:
        L.append("## Layout (byte offsets from `this`)\n\n| off | type | name |\n|---|---|---|")
        for off in sorted(fm[1]):
            ty, nm = fm[1][off]
            L.append("| 0x%x | `%s` | %s |" % (off, ty, nm))
        L.append("")
    if k in vt:
        L.append("## Virtual table (`__vt__%s`)\n\n| slot | function |\n|---|---|" % k)
        for off, nm in vt[k]:
            if nm: L.append("| 0x%02x | `%s` |" % (off, nm))
        L.append("")
    if callers.get(k):
        L.append("## Constructed by\n\n" + ", ".join("`%s`" % x for x in callers[k]) + "\n")
    L.append("## Functions (JP SLPM_602.19)\n\n| addr | size | symbol | C++ |\n|---|---|---|---|")
    for a, sz, n in lst:
        L.append("| 0x%08x | 0x%x | `%s` | `%s` |" % (a, sz, n, demangle(n)))
    L.append("")
    if d.get("rust"):
        L.append("## Rust port\n\n" + d["rust"] + "\n")
    L.append("## Open questions\n\n" + d.get("open", "- none recorded") + "\n")
    L.append("Decompilation: `decomp/F/%s.c`\n" % fn)
    open("%s/%s.md" % (OUT, fn), "w").write("\n".join(L))
print(len(by), "class notes")
