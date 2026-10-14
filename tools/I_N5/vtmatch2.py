import re,sys,collections,img,pickle
# vtmatch2.py <field|battle> : generalized slot-wise vtable pairing (prefix compare, soft base-method names)
tag=sys.argv[1]
ovl={'field':('fn_SH2US_FIELD.BIN.txt','fn_SH2JP_FIELD.BIN.txt'),'battle':('fn_SH2US_BATTLE.BIN.txt','fn_SH2JP_BATTLE.BIN.txt')}[tag]
usl=img.load_names(ovl[0]); jpl=img.load_names(ovl[1])
usmain=img.load_names('fn_SLUS_210.41.txt'); jpmain=img.load_names('fn_SLPM_602.19.txt')
un={a:n for a,n in usmain}; un.update({a:n for a,n in usl})
jn={a:n for a,n in jpmain}; jn.update({a:n for a,n in jpl})
jvt={}
for l in open('/Volumes/work/Sh2 Decomp/sh2-decomp/symbols/SLPM_602.19.syms'):
    p=l.split()
    if len(p)>=6 and p[2]=='OBJECT' and p[5].startswith('__vt__'):
        va=int(p[0],16); sz=int(p[1],16)
        jvt[p[5]]=(va,[img.JP.u32(va+8+i*4) for i in range(max(0,(sz-8)//4))])
starts=[]
for a in range(0x42f000,0x450000,4):
    if img.US.u32(a)==0 and img.US.u32(a+4)==0 and img.US.u32(a+8) in un: starts.append(a)
def base(n): return n.split('__')[0]
nvt={};newp={};matched=0;info=[]
for name,(jva,jsl) in jvt.items():
    jnames=[jn.get(w) for w in jsl]
    if sum(1 for n in jnames if n and not n.startswith('FUN_'))<1: continue
    best=[]
    for uva in starts:
        agree=dis=soft=0
        for i,(w1,) in enumerate(zip(jnames)):
            if not w1: continue
            n2=un.get(img.US.u32(uva+8+i*4))
            if n2 is None or n2.startswith('FUN_'): continue
            if w1==n2: agree+=1
            elif base(w1)==base(n2): soft+=1
            else: dis+=1
        if agree>=1 and dis==0: best.append((agree,soft,uva))
    if not best: continue
    best.sort(reverse=True)
    if len(best)>1 and best[0][0]==best[1][0] and best[0][1]==best[1][1]: continue
    agree,soft,uva=best[0]
    if agree<2 and len(jsl)>3: continue
    matched+=1
    # exclude overlap with next vt: stop at next start
    nxt=min([s for s in starts if s>uva]+[1<<32])
    for i,w1 in enumerate(jnames):
        ua=uva+8+i*4
        if ua>=nxt: break
        uw=img.US.u32(ua); n2=un.get(uw)
        if w1 and n2 and n2.startswith('FUN_'):
            newp.setdefault(uw,collections.Counter())[(w1,name,i)]+=1
            nvt.setdefault(uw,set()).add(name)
res=[]
for uw,c in newp.items():
    names=set(k[0] for k in c)
    if len(names)==1:
        k=list(c)[0]
        m=re.search(r'__(\d+)([A-Za-z_]\w*)',k[0]); own=None
        if k[0].startswith('@'): m=re.search(r'__(\d+)([A-Za-z_]\w*)',k[0][1:])
        if m: own=m.group(2)[:int(m.group(1))]
        vcls=re.match(r'__vt__(\d+)(.*)',k[1]); vc=vcls.group(2)[:int(vcls.group(1))] if vcls else None
        if own==vc or len(nvt[uw])>=2: res.append((k[0],uw,k[1],k[2]))
print('matched',matched,'new',len(res))
pickle.dump(res,open('vtres2_%s.pkl'%tag,'wb'))
