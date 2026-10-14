#!/usr/bin/env python3
"""Generate C prototypes from MWCC mangled names (BATTLE.BIN funcs list)."""
import re, sys
PRIM = {'i':'int','f':'float','b':'bool','s':'short','c':'char','l':'long','v':'void','d':'double','Ui':'uint','Us':'ushort','Uc':'uchar','Ul':'ulong'}
KNOWN = {'CBattle'}
def parse_type(s, i):
    """returns (ctype, new_i)"""
    ptr = 0
    const = False
    while i < len(s) and s[i] in 'PRC':
        if s[i] in 'PR': ptr += 1
        i += 1
    if s[i] == 'U':
        t = s[i:i+2]; i += 2
        ct = PRIM[t]
    elif s[i].isdigit():
        m = re.match(r'(\d+)', s[i:]); n = int(m.group(1)); i += len(m.group(1))
        ct = s[i:i+n]; i += n
    elif s[i] == 'F':   # function pointer: skip to '_' then return type
        j = s.index('_', i)
        ct = 'void *'; i = j + 1
        k = i
        # return type
        _, i = parse_type(s, i)
        return ct, i
    else:
        ct = PRIM.get(s[i], 'int'); i += 1
    if ptr:
        ct += ' ' + '*' * ptr
    return ct, i
def proto(name):
    m = re.match(r'(.+?)__(\d+)?([A-Za-z_]\w*?)?F(.*)$', name)
    # forms: Method__7ClassFargs  or  Func__Fargs
    m = re.match(r'^(.*?)__(?:(\d+)(\w+?))?(C?)F(.*)$', name)
    if not m: return None
    meth, ln, rest, const, args = m.groups()
    cls = None
    if ln:
        n = int(ln)
        cls = (ln_str := rest)[:0]
        full = ln + rest
        cls = full[len(ln):len(ln)+n]
        args = full[len(ln)+n:] + 'F' + args if False else args
    # careful re-parse for class name
    mm = re.match(r'^(.*?)__(\d+)(.*)$', name)
    if mm:
        meth = mm.group(1); n = int(mm.group(2)); tail = mm.group(3)
        cls = tail[:n]; tail = tail[n:]
        if tail.startswith('C'): tail = tail[1:]
        assert tail.startswith('F'), name
        args = tail[1:]
    else:
        mm = re.match(r'^(.*?)__F(.*)$', name)
        if not mm: return None
        meth, args = mm.group(1), mm.group(2)
        cls = None
    params = []
    i = 0
    while i < len(args):
        if args[i] == 'v' and len(args) == 1: break
        t, i = parse_type(args, i)
        params.append(t)
    return meth, cls, params
if __name__ == '__main__':
    for l in open(sys.argv[1]):
        a, n = l.split()
        if n.startswith('@') or n.startswith('__ct') or n.startswith('__dt') or n.startswith('__sinit'): continue
        r = proto(n)
        if not r: print('# ?', a, n); continue
        meth, cls, params = r
        ps = []
        if cls: ps.append('%s * this' % (cls if cls in KNOWN else 'void'))
        for k, p in enumerate(params): ps.append('%s a%d' % (p, k + 1))
        print(a, '|', 'int %s(%s)' % (meth, ', '.join(ps)))
