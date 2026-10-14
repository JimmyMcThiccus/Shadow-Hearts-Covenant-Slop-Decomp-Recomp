#!/usr/bin/env python3
"""Bulk-export Ghidra decompiler output for section E into decomp/E/*.c (tidied).

Talks to the GhidraMCP plugin's local HTTP endpoint (127.0.0.1:8089) -- the same data the MCP tools return.
usage: E_gen_decomp.py <out_dir> <program> <group-name> <regex-over-mangled-names> [--addr-range lo-hi]
"""
import re, sys, urllib.request, urllib.parse, os, collections

SYMS = os.path.join(os.path.dirname(__file__), '..', 'symbols', 'SLPM_602.19.syms')
BASE = 'http://127.0.0.1:8089'

def load_syms():
    out = []
    for l in open(SYMS):
        p = l.split()
        if len(p) >= 6 and p[2] == 'FUNC':
            out.append((int(p[0], 16), int(p[1], 16), p[4], p[5]))
    return out

def demangle(m):
    # name__<len><Class>F<args>   |   name__F<args>
    r = re.match(r'^(.*?)__(\d+)([A-Za-z_][A-Za-z0-9_]*?)F(.*)$', m)
    if r:
        name, ln, rest, args = r.groups()
        ln = int(ln)
        cls = (rest)[:0]
        # class name is the first `ln` chars of ( ln-digits stripped ) text
        m2 = re.match(r'^(\d+)(.*)$', m[len(name)+2:])
        l2 = int(m2.group(1)); body = m2.group(2)
        cls = body[:l2]; args = body[l2:]
        if args.startswith('F'): args = args[1:]
        if name == '__ct': name = cls
        elif name == '__dt': name = '~' + cls
        return '%s::%s(%s)' % (cls, name, args)
    r = re.match(r'^(.*?)__F(.*)$', m)
    if r:
        return '%s(%s)' % (r.group(1), r.group(2))
    return m

def fetch(addr, prog):
    q = urllib.parse.urlencode({'address': '%08x' % addr, 'program': prog})
    with urllib.request.urlopen(BASE + '/decompile_function?' + q, timeout=120) as f:
        return f.read().decode('utf-8', 'replace')

TYPEMAP = [('undefined8', 'u64'), ('undefined4', 'u32'), ('undefined2', 'u16'), ('undefined1', 'u8'), ('undefined', 'u8')]
def tidy(txt, mangled):
    for a, b in TYPEMAP:
        txt = re.sub(r'\b%s\b' % a, b, txt)
    txt = txt.replace('\r', '')
    txt = re.sub(r'/\* WARNING: Removing unreachable block[^*]*\*/\n', '', txt)
    if re.search(r'__FiiPPcPv$', mangled):
        sig = re.search(r'\n(\w+)\s*\n?\s*%s\(' % re.escape(mangled), txt)
        for old, new in (('param_1', 'id'), ('param_2', 'argc'), ('param_3', 'args'), ('param_4', 'ctx')):
            txt = re.sub(r'\b%s\b' % old, new, txt)
    return txt.strip() + '\n'

def main():
    out_dir, prog, group, pat = sys.argv[1:5]
    lo, hi = 0, 1 << 32
    if len(sys.argv) > 6 and sys.argv[5] == '--addr-range':
        lo, hi = [int(x, 16) for x in sys.argv[6].split('-')]
    rx = re.compile(pat)
    funcs = sorted([f for f in load_syms() if rx.search(f[3]) and lo <= f[0] < hi and f[2] == 'main'])
    os.makedirs(out_dir, exist_ok=True)
    path = os.path.join(out_dir, group + '.c')
    with open(path, 'w') as fo:
        fo.write('/*\n * %s.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py\n' % group)
        fo.write(' * %d functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.\n */\n\n' % len(funcs))
        for addr, size, sec, name in funcs:
            try:
                body = fetch(addr, prog)
            except Exception as e:
                body = '/* decompile failed: %s */\n' % e
            fo.write('/* ---- 0x%08x size 0x%x  %s\n *      mangled: %s */\n' % (addr, size, demangle(name), name))
            fo.write(tidy(body, name))
            fo.write('\n')
    print(path, len(funcs))

if __name__ == '__main__':
    main()
