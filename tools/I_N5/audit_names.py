import img,os,re,collections,sys,feat2
usfn,jpfn,usd,jpd=sys.argv[1:5]; lim=int(sys.argv[5],16)
usl=img.load_names(usfn); jpl=[(a,n) for a,n in img.load_names(jpfn) if a<lim]
jby=collections.defaultdict(list)
for a,n in jpl: jby[n].append(a)
uby=collections.defaultdict(list)
for a,n in usl: uby[n].append(a)
names_us=set(n for a,n in usl)
MATH=re.compile(r'^(__ct__7FVector|__as__7FVector|Normalize__7FVector|_v|_sqc|_lqc|_qm|_ctc2|_cfc2|ApplyMatrix__6Matrix|__pl__7FVector|__mi__7FVector|__ml__7FVector|sceVu0|__dv__7FVector|__amu__7FVector|Length__7FVector|sqrtf|sinf|cosf|atan2f)')
def calls(path):
    t=open(path).read(); b=t[t.find('{'):]
    out=[]
    for m in re.finditer(r'(?<![\w.>])([A-Za-z_]\w*)\s*\(',b):
        c=m.group(1)
        if c in feat2.KW or MATH.match(c) or c.startswith('FUN_') or c.startswith('thunk') or c.startswith('func_0x'): continue
        out.append(c)
    return out
bad=[]
usz={a:(usl[i+1][0]-a if i+1<len(usl) else 0) for i,(a,n) in enumerate(usl)}
jsz={a:(jpl[i+1][0]-a if i+1<len(jpl) else 0) for i,(a,n) in enumerate(jpl)}
for a,n in usl:
    if n.startswith('FUN_') or len(uby[n])!=1 or len(jby.get(n,[]))!=1: continue
    ja=jby[n][0]
    pu='%s/%08x.c'%(usd,a); pj='%s/%08x.c'%(jpd,ja)
    if not(os.path.exists(pu) and os.path.exists(pj)): continue
    cu=collections.Counter(calls(pu)); cj=collections.Counter(calls(pj))
    nu,nj=sum(cu.values()),sum(cj.values())
    if nu<3 or nj<3: continue
    inter=sum((cu&cj).values()); d=2*inter/(nu+nj)
    if d<float(sys.argv[6]) if len(sys.argv)>6 else d<0.3: bad.append((d,a,ja,n,nu,nj,usz[a],jsz[ja]))
bad.sort()
print(len(bad))
for x in bad[:80]: print('%.2f us %x jp %x %s ncallee %d/%d size %x/%x'%x)
