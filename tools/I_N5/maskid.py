import img,collections,struct,sys
F=img.Flat(img.D+"Shadow Hearts - Covenant (USA) (Disc 1)-1/FIELD.BIN",0x45ea80)
B=img.Flat(img.D+"Shadow Hearts - Covenant (USA) (Disc 1)-1/BATTLE.BIN",0x45ea80)
def mask(w):
    op=w>>26
    if op in (2,3): return w&0xfc000000
    if op==0: return w
    return w&0xffff0000
def sig(e,a,n):
    ws=[e.u32(a+i*4) for i in range(n//4)]
    while ws and ws[-1]==0: ws.pop()
    return tuple(mask(w) for w in ws)
def load(fn):
    L=img.load_names(fn); return L,{a:(L[i+1][0]-a if i+1<len(L) else 0x40) for i,(a,n) in enumerate(L)}
um,umsz=load('fn_SLUS_210.41.txt'); uf,ufsz=load('fn_SH2US_FIELD.BIN.txt'); ub,ubsz=load('fn_SH2US_BATTLE.BIN.txt')
named=collections.defaultdict(list)
for a,n in um:
    if not n.startswith('FUN_') and umsz[a]>=0x10 and umsz[a]<=0x200: named[sig(img.US,a,umsz[a])].append(('main',a,n))
for L,sz,e,tag in ((uf,ufsz,F,'field'),(ub,ubsz,B,'battle')):
    for a,n in L:
        if not n.startswith('FUN_') and sz[a]>=0x10 and sz[a]<=0x200: named[sig(e,a,sz[a])].append((tag,a,n))
res=[]
for L,sz,e,tag,prog in ((um,umsz,img.US,'main','SLUS_210.41'),(uf,ufsz,F,'field','SH2US_FIELD.BIN'),(ub,ubsz,B,'battle','SH2US_BATTLE.BIN')):
    for a,n in L:
        if not n.startswith('FUN_') or sz[a]<0x10 or sz[a]>0x200: continue
        s=sig(e,a,sz[a])
        if len(s)<4: continue
        c=named.get(s)
        if not c: continue
        names=set(x[2] for x in c)
        if len(names)==1: res.append((prog,a,list(names)[0],len(c),sz[a]))
print(len(res))
for r in res[:60]: print('%s %x %s n=%d sz=%x'%r)
