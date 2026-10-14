#!/usr/bin/env python3
"""Give every non-static section-F member function a prototype with a typed `this` in Ghidra (SLPM_602.19)."""
import json, re, sys, os, urllib.request, urllib.parse
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
S = sys.argv[1]
BASE = "http://127.0.0.1:8089"; PROG = "SLPM_602.19"
exec(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "clean.py")).read().split("# ------------------------------------------------------------------ demangler")[1].split("SLOTS =")[0].replace("RAW, OUT", "_,_"), globals())
structs = set(json.load(open(S + "/structs_done.json")))
idx = json.load(open(S + "/raw/_index.json"))
def post(ep, d):
    req = urllib.request.Request(BASE + "/" + ep + "?" + urllib.parse.urlencode({"program": PROG}), data=json.dumps(d).encode(), headers={"Content-Type": "application/json"})
    try: return urllib.request.urlopen(req, timeout=120).read().decode()
    except Exception as e: return "ERR %s" % e
PT = {"int": "int", "short": "short", "char": "char", "long": "long", "float": "float", "double": "double", "bool": "bool",
      "unsigned int": "uint", "unsigned short": "ushort", "unsigned char": "byte", "unsigned long": "ulong", "void": "void"}
def ptype(t):
    t = t.replace("const ", "").strip()
    if t in PT: return PT[t]
    m = re.match(r"^(\w+)\*$", t)
    if m and m.group(1) in structs: return m.group(1) + " *"
    return "void *"
RT = {"undefined1": "byte", "undefined2": "ushort", "undefined4": "undefined4", "undefined8": "undefined8", "ulong": "ulong", "uint": "uint", "long": "long", "int": "int", "void": "void", "bool": "bool", "short": "short", "ushort": "ushort", "byte": "byte", "float": "float", "char": "char"}
ok = fail = skip = 0
for a, sz, n, c in idx:
    if n.startswith("@"): skip += 1; continue
    cl = cls_of(n)
    if cl not in structs or n.startswith("sm_"): skip += 1; continue
    txt = open("%s/raw/%08x.c" % (S, a)).read()
    if not re.search(r"\(param_\d+ \+ ", txt) and not re.search(r"param_1", txt) and "__ct__" not in n and "__dt__" not in n:
        skip += 1; continue
    # static heuristics: Ghidra's first param is not a pointer to the object
    if re.match(r"^(Initialize__7MenuObj|IsReady__7MenuObj|UpdateTimer__7MenuObj|CreateField|CreateCmdMenu|ReleaseField|ReleaseCmdMenu|IsReadyField|IsReadyCmdMenu)", n): skip += 1; continue
    dm = demangle(n)
    am = re.search(r"\((.*)\)", dm)
    args = [x.strip() for x in am.group(1).split(",") if x.strip()] if am else []
    first = txt.strip().split("\n")[0]
    rm = re.match(r"^(?:/\*.*\*/\s*)?([\w ]+?\*?)\s+\*?%s" % re.escape(n), txt.strip().replace("\n", " "))
    ret = "undefined4"
    mm = re.search(r"([\w ]+?)\s*(\*?)\s*%s\s*\(" % re.escape(n), re.sub(r"/\*.*?\*/", "", txt, flags=re.S))
    if mm:
        r0 = mm.group(1).strip().split()[-1] if mm.group(1).strip() else "undefined4"
        ret = "void *" if mm.group(2) else RT.get(r0, "undefined4")
    if "__ct__" in n or "__dt__" in n: ret = "void *"
    params = ["%s * this" % cl] + ["%s p%d" % (ptype(t), i + 2) for i, t in enumerate(args) if ptype(t) != "void"]
    proto = "%s %s(%s)" % (ret, n, ", ".join(params))
    r = post("set_function_prototype", {"function_address": "%08x" % a, "prototype": proto})
    if "Successfully" in r: ok += 1
    else:
        fail += 1
        if fail < 15: print(n, proto, r[:120])
print("ok", ok, "fail", fail, "skip", skip)
