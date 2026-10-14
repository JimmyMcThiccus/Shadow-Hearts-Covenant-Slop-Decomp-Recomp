# usage: vtscan.py lo hi [prog dir]: for unnamed functions in range find stored vtables, print classes + slot tables
import re,sys,img,collections,os
lo,hi=int(sys.argv[1],16),int(sys.argv[2],16)
dec=sys.argv[3] if len(sys.argv)>3 else 'dec/main'
fnl=sys.argv[4] if len(sys.argv)>4 else 'fn_SLUS_210.41.txt'
L=img.load_names(fnl); names=dict(L)
um=dict(img.load_names('fn_SLUS_210.41.txt')); um.update(names)
sizes={a:(L[i+1][0]-a) for i,(a,n) in enumerate(L[:-1])}
VT=re.compile(r'\(\s*\w+\s*\+\s*(0x[0-9a-f]+|\d+)\)\s*=\s*(?:&(?:DAT|PTR_[A-Za-z_0-9]*)_?|0x)(0*4[0-9a-f]{5})\b')
by=collections.defaultdict(list)
for a,n in L:
    if lo<=a<hi and n.startswith('FUN_'):
        p='%s/%08x.c'%(dec,a)
        if not os.path.exists(p): continue
        t=open(p).read()
        for m in VT.finditer(t):
            v=int(m.group(2),16)
            if 0x42f000<=v<0x450000: by[v].append((a,int(m.group(1),0)))
def f(w):
    n=um.get(w)
    if n is None: return '%x?'%w
    return n[:26] if not n.startswith('FUN_') else 'F%x'%w
for v,l in sorted(by.items()):
    fs=sorted(set(a for a,o in l))
    print('vt %x stored by %s'%(v,' '.join('%x@+%x'%(a,o) for a,o in sorted(set(l)))))
    print('    slots:',' '.join(f(img.US.u32(v+8+i*4)) for i in range(14)))
