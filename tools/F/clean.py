#!/usr/bin/env python3
"""Generate decomp/F/<Class>.c from raw Ghidra decompiler dumps (see fetch.py).

usage: clean.py RAWDIR OUTDIR
  * demangles the CFront/Metrowerks names into a header comment,
  * renames the `this` parameter, maps `*(T *)(this + off)` to `this->field` using fields.py,
  * labels virtual calls with the MenuObj/MenuPlace vtable slot names,
  * normalises undefinedN types.
"""
import json, re, sys, os, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fields

RAW, OUT = sys.argv[1], sys.argv[2]
idx = json.load(open(RAW + "/_index.json"))

# ------------------------------------------------------------------ demangler
PRIM = {"v": "void", "c": "char", "s": "short", "i": "int", "l": "long", "f": "float", "d": "double", "b": "bool", "w": "wchar_t", "x": "long long"}
def parse_type(s, i):
    """returns (str, new_i)"""
    pre = ""
    while i < len(s) and s[i] in "UCPR":
        c = s[i]
        pre += {"U": "unsigned ", "C": "const ", "P": "*", "R": "&"}[c]
        i += 1
    if i >= len(s): return "?", i
    c = s[i]
    if c in PRIM:
        base = PRIM[c]; i += 1
    elif c.isdigit():
        j = i
        while j < len(s) and s[j].isdigit(): j += 1
        n = int(s[i:j]); base = s[j:j + n]; i = j + n
    elif c == "Q":
        k = int(s[i + 1]); i += 2; names = []
        for _ in range(k):
            j = i
            while j < len(s) and s[j].isdigit(): j += 1
            n = int(s[i:j]); names.append(s[j:j + n]); i = j + n
        base = "::".join(names)
    elif c == "F":  # function ptr
        base = "fn"; i += 1
        while i < len(s) and s[i] != "_": i += 1
        i += 1
        _, i = parse_type(s, i)
    elif c in "TN":
        j = i + 1
        while j < len(s) and s[j].isdigit(): j += 1
        base = "T" + s[i + 1:j]; i = j
    else:
        base = c; i += 1
    # pointers/refs print after
    ptrs = "".join(ch for ch in pre if ch in "*&")
    words = "".join(w for w in re.split(r"([*&])", pre) if w not in "*&")
    return (words.strip() + " " if words.strip() else "") + base + ptrs, i

def demangle(m):
    if m.startswith("@"):
        return m  # thunk
    mm = re.match(r"^(__ct|__dt|__as|__nw|__dl|__nwa|__dla|[A-Za-z_$][\w$]*?)__(\d+|Q\d)", m)
    if not mm:
        # free function: name__F...
        mm2 = re.match(r"^(.*?)__F(.*)$", m)
        if mm2:
            return mm2.group(1) + "(" + _params(mm2.group(2)) + ")"
        return m
    name = mm.group(1)
    rest = m[mm.end(1) + 2:]
    # class
    if rest[0].isdigit():
        j = 0
        while rest[j].isdigit(): j += 1
        n = int(rest[:j]); cname = rest[j:j + n]; rest = rest[j + n:]
    else:
        k = int(rest[1]); rest = rest[2:]; names = []
        for _ in range(k):
            j = 0
            while rest[j].isdigit(): j += 1
            n = int(rest[:j]); names.append(rest[j:j + n]); rest = rest[j + n:]
        cname = "::".join(names)
    const = ""
    if rest.startswith("C"):
        const = " const"; rest = rest[1:]
    if rest.startswith("F"):
        params = _params(rest[1:])
    else:
        return cname + "::" + name  # data member
    if name == "__ct": name = cname
    elif name == "__dt": name = "~" + cname
    return "%s::%s(%s)%s" % (cname, name, params, const)

def _params(s):
    out = []; i = 0
    last = []
    while i < len(s):
        t, i2 = parse_type(s, i)
        if i2 == i: break
        out.append(t); i = i2
    if out == ["void"]: return ""
    return ", ".join(out)

def cls_of(mangled):
    m = re.search(r"__(\d+)([A-Za-z_]\w*?)(?:C?F|$)", mangled)
    if not m: return None
    n = int(m.group(1)); rest = mangled[m.start(2):]
    return rest[:n]

SLOTS = {0x8: "dtor", 0xc: "DelayDelete", 0x10: "Polling", 0x14: "Update", 0x18: "Connect", 0x1c: "Destroy", 0x20: "Clear",
         0x24: "SetPosition", 0x28: "SetSize", 0x2c: "SetAlpha", 0x30: "SetColor", 0x34: "SetBright", 0x38: "SetOwner",
         0x3c: "GetKeyPlace", 0x40: "GetKeyRect", 0x44: "AllotPacket", 0x48: "GetAllotCount", 0x4c: "Attach", 0x50: "Detach"}

TYPEMAP = [("undefined1", "u8"), ("undefined2", "u16"), ("undefined4", "u32"), ("undefined8", "u64"), ("ushort", "u16"), ("byte", "u8")]

def process(a, sz, mangled, cname, text):
    text = re.sub(r"\n\s*\n", "\n", text.strip("\n")) + "\n"
    kind = cls_of(mangled)
    cname_eff = kind or cname
    # this param
    this = None
    sig = re.search(r"\n?[^\n]*\((.*?)\)\s*\n\s*\{", text, re.S)
    params = re.findall(r"\b(param_\d+)\b", text)
    cnt = collections.Counter(re.findall(r"\((param_\d+) \+ ", text))
    is_static = bool(re.match(r"^(sm_|Initialize__7MenuObj|IsReady|UpdateTimer|SetBright__7MenuObjFP|Create(Field|CmdMenu)|Release(Field|CmdMenu)|IsReadyField|AddOT|ReleaseOT)", mangled)) or cname_eff is None
    if cnt and not is_static:
        this = cnt.most_common(1)[0][0]
    elif not is_static and params:
        this = "param_1"
    fmap = fields.resolve(cname_eff) if cname_eff else {}
    if this:
        text = re.sub(r"\b%s\b" % this, "this", text)
        def fld(m):
            ty, off = m.group(1), int(m.group(2), 0)
            if off in fmap:
                return "this->%s" % fmap[off][1].replace("[", "_").replace("]", "")
            return "this->f_%02x" % off if off >= 0x10 else "this->f_%x" % off
        text = re.sub(r"\*\(([A-Za-z0-9_ ]+?(?: \*)?) ?\*?\)\(this \+ (0x[0-9a-fA-F]+|\d+)\)", lambda m: fld_typed(m, fmap), text)
    # vtable calls
    def vcall(m):
        who, slot = m.group(1), int(m.group(2), 0)
        nm = SLOTS.get(slot, "slot_%x" % slot)
        return "VCALL(%s, 0x%x /*%s*/)" % (who, slot, nm)
    text = re.sub(r"\(\*\*\(code \*\*\)\(\*\(int \*\)\(([\w>\-.]+) \+ 8\) \+ (0x[0-9a-fA-F]+|\d+)\)\)", vcall, text)
    text = re.sub(r"\(\*\*\(code \*\*\)\(([\w>\-.]+)->vptr \+ (0x[0-9a-fA-F]+|\d+)\)\)", vcall, text)
    text = re.sub(r"\(\*\*\(code \*\*\)\(\*\(int \*\)\(([\w>\-.]+) \+ 0x14\) \+ (0x[0-9a-fA-F]+|\d+)\)\)", lambda m: "VCALL14(%s, %s)" % (m.group(1), m.group(2)), text)
    if this and cname_eff:
        text = re.sub(r"^([^\n(]*\()([A-Za-z0-9_ *]+?) ?\bthis\b", lambda m: "%s%s *this" % (m.group(1), cname_eff), text, count=1, flags=re.M)
    # typed object parameters (pointer-to-known-class args)
    dm = demangle(mangled)
    am = re.search(r"\((.*)\)", dm)
    if am and this and "float" not in am.group(1) and "double" not in am.group(1):
        args = [x.strip() for x in am.group(1).split(",") if x.strip()]
        for i, ty in enumerate(args):
            pm = re.match(r"^(?:const )?(\w+)\*$", ty)
            if pm and pm.group(1) in fields.F:
                pn = "param_%d" % (i + 2)
                nice = pm.group(1)[0].lower() + pm.group(1)[1:]
                pmap = fields.resolve(pm.group(1))
                def pf(m, pmap=pmap, pn=pn, nice=nice):
                    off = int(m.group(2), 0)
                    if off in pmap:
                        return "%s->%s" % (nice, re.sub(r"\[.*\]", "", pmap[off][1]))
                    return m.group(0).replace(pn, nice)
                text = re.sub(r"\*\(([A-Za-z0-9_ ]+?(?: \*)?) ?\*?\)\(%s \+ (0x[0-9a-fA-F]+|\d+)\)" % pn, pf, text)
                text = re.sub(r"\b%s\b" % pn, nice, text)
                text = re.sub(r"(\b(?:int|u32|long|u64|ulong)) %s\b" % nice, "%s *%s" % (pm.group(1), nice), text)
    for a1, b1 in TYPEMAP:
        text = re.sub(r"\b%s\b" % a1, b1, text)
    # second pass: chained pointer members  *(T *)(a->b + off)  ->  a->b->field
    def chain_type(expr, root_cls, extra):
        parts = expr.split("->")
        cur = extra.get(parts[0]) if parts[0] != "this" else cname_eff
        for nm in parts[1:]:
            if cur is None: return None
            mp = fields.resolve(cur)
            hit = [v for k, v in mp.items() if re.sub(r"\[.*\]", "", v[1]) == nm]
            if not hit: return None
            ty = hit[0][0].strip()
            m2 = re.match(r"^(\w+) \*$", ty)
            cur = m2.group(1) if m2 and m2.group(1) in fields.F else None
        return cur
    extra = {}
    if am and this:
        args2 = [x.strip() for x in am.group(1).split(",") if x.strip()]
        for i, ty in enumerate(args2):
            pm = re.match(r"^(?:const )?(\w+)\*$", ty)
            if pm and pm.group(1) in fields.F:
                extra[pm.group(1)[0].lower() + pm.group(1)[1:]] = pm.group(1)
    for _ in range(3):
        def cm(m):
            expr, off = m.group(2), int(m.group(3), 0)
            c = chain_type(expr, cname_eff, extra)
            if c:
                mp = fields.resolve(c)
                if off in mp:
                    return "%s->%s" % (expr, re.sub(r"\[.*\]", "", mp[off][1]))
            return m.group(0)
        text = re.sub(r"\*\(([A-Za-z0-9_ ]+?(?: \*)?) ?\*?\)\(((?:\w+->)+\w+) \+ (0x[0-9a-fA-F]+|\d+)\)", cm, text)
    hdr = "// JP: 0x%08x  %s  size 0x%x\n// %s\n" % (a, mangled, sz, demangle(mangled))
    return hdr + text

def fld_typed(m, fmap):
    ty, off = m.group(1).strip(), int(m.group(2), 0)
    if off in fmap:
        nm = fmap[off][1]
        nm = re.sub(r"\[.*\]", "", nm)
        return "this->%s" % nm
    return "this->f_%02x /*%s*/" % (off, ty) if off >= 0x10 else "this->f_%x /*%s*/" % (off, ty)

by = collections.OrderedDict()
for a, sz, n, c in idx:
    k = cls_of(n) or c
    if n.startswith("@"):
        m = re.search(r"__(\d+)([A-Za-z_]\w*?)(?:C?F|$)", n)
        k = cls_of(n) or c
    if c == "?" or c not in fields.F and k in fields.F: pass
    by.setdefault(k if k else c, []).append((a, sz, n, c))

os.makedirs(OUT, exist_ok=True)
HEADER = '''/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */
'''
files = {}
for k, lst in by.items():
    body = [HEADER]
    for a, sz, n, c in lst:
        t = open("%s/%08x.c" % (RAW, a)).read()
        body.append(process(a, sz, n, k, t))
    fn = re.sub(r"[^\w]", "_", k)
    open("%s/%s.c" % (OUT, fn), "w").write("\n".join(body))
    files[fn] = len(lst)
print(len(files), "files,", sum(files.values()), "functions")
