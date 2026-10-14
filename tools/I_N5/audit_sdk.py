import img,collections,sys
us=img.load_names('fn_SLUS_210.41.txt'); jp=img.load_names('fn_SLPM_602.19.txt')
def sz(L):
    return {a:(L[i+1][0]-a if i+1<len(L) else 0x40) for i,(a,n) in enumerate(L)}
usz=sz(us); jsz=sz(jp)
def mask(e,a,n):
    out=[]
    for i in range(n//4):
        w=e.u32(a+i*4); op=w>>26
        if op in (2,3): w=w&0xfc000000        # j/jal
        elif op==0x0f: w=w&0xffff0000         # lui
        elif op in (4,5,6,7,1,0x14,0x15,0x16,0x17): w=w&0xffff0000  # branches: drop offset
        elif op in (0x09,0x23,0x2b,0x20,0x21,0x24,0x25,0x28,0x29,0x2f,0x37,0x3f,0x1e,0x1f,0x31,0x39,0x35,0x3d,0x32,0x3a,0x22,0x26,0x2a,0x2e): w=w&0xffff0000  # addiu/ld/st offsets dropped? keep rs/rt
        out.append(w)
    return tuple(out)
LO,HI=int(sys.argv[1],16),int(sys.argv[2],16)
jbyname=collections.defaultdict(list)
for a,n in jp: jbyname[n].append(a)
jbymask=collections.defaultdict(list)
for a,n in jp:
    if a<0x440000 and jsz[a]<=0x400: jbymask[mask(img.JP,a,jsz[a])].append(n)
bad=[]
for a,n in us:
    if not (LO<=a<HI) or n.startswith('FUN_') or jsz.get(a,0)==0 or usz[a]>0x400: continue
    ms=mask(img.US,a,usz[a])
    names=jbymask.get(ms)
    if names is None: continue
    if n not in names: bad.append((a,n,names[:3]))
print(len(bad))
for a,n,nm in bad[:80]: print('%x %s -> JP-identical: %s'%(a,n,nm))
