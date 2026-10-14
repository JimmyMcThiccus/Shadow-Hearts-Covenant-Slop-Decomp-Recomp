#!/usr/bin/env python3
"""Create the section-F structs in Ghidra (program SLPM_602.19) from fields.py via the GhidraMCP HTTP API
and type the `this` of the member functions. usage: ghidra_structs.py SCRATCH [--this]"""
import json, re, sys, os, urllib.request, urllib.parse
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fields
S = sys.argv[1]
DO_THIS = "--this" in sys.argv
BASE = "http://127.0.0.1:8089"
PROG = "SLPM_602.19"
sizes = json.load(open(S + "/class_sizes.json"))
sizes.update({"SaveData": 0x2c, "MenuText": 0x80, "Menu": 0x50, "GameOver": 0x54, "Cursor": 0x100, "MenuGroup": 0x50, "MenuWindowObject": 0x1c, "MenuMessage": 0x98, "MenuPacket": 0x10})

def post(ep, d):
    # NB: the plugin only honours `program` in the query string; the JSON body falls back to the *current* program.
    d = dict(d); d["program"] = PROG
    req = urllib.request.Request(BASE + "/" + ep + "?" + urllib.parse.urlencode({"program": PROG}), data=json.dumps(d).encode(), headers={"Content-Type": "application/json"})
    try:
        return urllib.request.urlopen(req, timeout=120).read().decode()
    except Exception as e:
        return "ERR %s" % e

TM = {"u8": "byte", "s8": "char", "u16": "ushort", "s16": "short", "u32": "uint", "s32": "int", "f32": "float", "u64": "ulong"}
def map_type(t):
    t = t.strip()
    m = re.match(r"^(u8|s8|u16|s16|u32|s32|f32)\[(\w+)\]$", t)
    if m: return "%s[%s]" % (TM[m.group(1)], int(m.group(2), 0))
    m = re.match(r"^(\w+)\[(\d+)\]$", t)
    if m: return None
    if t in TM: return TM[t]
    if t.endswith("*"): return "void *"
    if t in ("fn", "ptmf"): return "void *"
    return None

def size_of(t):
    t = t.strip()
    m = re.match(r"^(\w+)\[(\w+)\]$", t)
    if m:
        el = {"byte": 1, "char": 1, "ushort": 2, "short": 2, "uint": 4, "int": 4, "float": 4}[m.group(1)]
        return el * int(m.group(2), 0)
    return {"byte": 1, "char": 1, "ushort": 2, "short": 2, "uint": 4, "int": 4, "float": 4, "ulong": 8}.get(t, 4)

done = {}
SKIP = {"CPolObj", "DelayDeleteObject", "Scissor"}   # owned by section A
for cname in list(fields.F):
    if cname in SKIP: continue
    fm = fields.resolve(cname)
    fl = []
    last = 0
    for off in sorted(fm):
        ty, nm = fm[off]
        mt = map_type(ty)
        if mt is None: continue
        if off < last: continue
        fl.append({"name": re.sub(r"\[.*\]$", "", nm), "type": mt, "offset": off})
        last = off + size_of(mt)
    if not fl: continue
    size = max(sizes.get(cname, 0), last)
    if size > last:
        fl.append({"name": "_pad_%x" % last, "type": "byte[%d]" % (size - last), "offset": last})
    r = post("create_struct", {"name": cname, "fields": json.dumps(fl), "replace_placeholder": "true"})
    if "Successfully" not in r:
        # existing struct: recreate
        post("delete_data_type", {"type_name": cname})
        r = post("create_struct", {"name": cname, "fields": json.dumps(fl), "replace_placeholder": "true"})
    done[cname] = r[:80]
    print(cname, r[:100])
json.dump(done, open(S + "/structs_done.json", "w"))

if DO_THIS:
    idx = json.load(open(S + "/raw/_index.json"))
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    n = 0
    for a, sz, name, c in idx:
        m = re.search(r"__(\d+)([A-Za-z_]\w*?)(?:C?F|$)", name)
        if not m: continue
        cl = m.group(2)[:int(m.group(1))]
        if cl not in done or name.startswith("@") or name.startswith("sm_"): continue
        # skip statics heuristically: member functions only (first arg `this`)
        txt = open("%s/raw/%08x.c" % (S, a)).read()
        if not re.search(r"\(param_\d+ \+ ", txt) and "__ct__" not in name and "__dt__" not in name: continue
        r = post("set_function_this_type", {"function_address": "%08x" % a, "this_type": cl + " *"})
        n += 1
        if n % 50 == 0: print(n, r[:100])
    print("this-typed", n)
