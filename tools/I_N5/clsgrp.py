# group unnamed functions in FIELD range into classes by (ctor,dtor) pairs sharing vtable stores
import re,sys,img,collections,os
lo,hi=int(sys.argv[1],16),int(sys.argv[2],16)
dec='dec/field'; fnl='fn_SH2US_FIELD.BIN.txt'
L=img.load_names(fnl); names=dict(L)
um=dict(img.load_names('fn_SLUS_210.41.txt')); um.update(names)
sizes={a:(L[i+1][0]-a) for i,(a,n) in enumerate(L[:-1])}
VT=re.compile(r'\(\s*\w+\s*\+\s*(0x[0-9a-f]+|\d+)\)\s*=\s*(?:&(?:DAT|PTR_[A-Za-z_0-9]*)_?|0x)(0*4[0-9a-f]{5})\b')
st={}
for a,n in L:
    if lo<=a<hi:
        p='%s/%08x.c'%(dec,a)
        t=open(p).read()
        v=[]
        for m in VT.finditer(t):
            va=int(m.group(2),16)
            if 0x42f000<=va<0x450000: v.append((int(m.group(1),0),va))
        if v: st[a]=tuple(sorted(set(v)))
# classes: functions sharing identical store sets
cls=collections.defaultdict(list)
for a,v in st.items(): cls[v].append(a)
def f(w):
    n=um.get(w)
    if n is None: return '%x?'%w
    return n[:20] if not n.startswith('FUN_') else 'F%x'%w
res=[]
for v,fs in sorted(cls.items(),key=lambda x:min(x[1])):
    fs.sort()
    prim=v[0][1]
    s1=f(img.US.u32(prim+8+4))
    res.append((fs,v,s1))
for fs,v,s1 in res:
    print(' '.join('%x(%x)%s'%(a,sizes[a],'' if names[a].startswith('FUN_') else ':'+names[a][:18]) for a in fs),'| vt',' '.join('%x@%x'%(va,o) for o,va in v),'| s1',s1)
