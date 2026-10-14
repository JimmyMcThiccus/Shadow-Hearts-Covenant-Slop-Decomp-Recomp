import re,collections,img,pickle,sys
tag=sys.argv[1]
ovl={'field':('fn_SH2US_FIELD.BIN.txt','fn_SH2JP_FIELD.BIN.txt','SH2US_FIELD.BIN'),'battle':('fn_SH2US_BATTLE.BIN.txt','fn_SH2JP_BATTLE.BIN.txt','SH2US_BATTLE.BIN')}[tag]
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
starts=[a for a in range(0x42f000,0x450000,4) if img.US.u32(a)==0 and img.US.u32(a+4)==0 and img.US.u32(a+8) in un]
def base(n): return n.split('__')[0]
def cls_of(n):
    if n.startswith('@'): n=n[1:].split('@',1)[-1]
    m=re.search(r'__(\d+)([A-Za-z_]\w*)',n)
    return m.group(2)[:int(m.group(1))] if m else None
vtm={}
for name,(jva,jsl) in jvt.items():
    jnames=[jn.get(w) for w in jsl]
    best=[]
    for uva in starts:
        ag=dis=0
        for i,w1 in enumerate(jnames):
            if not w1: continue
            n2=un.get(img.US.u32(uva+8+i*4))
            if n2 is None or n2.startswith('FUN_'): continue
            if w1==n2: ag+=1
            elif base(w1)==base(n2): pass
            else: dis+=1
        if ag>=2 and dis==0: best.append((ag,uva))
    best.sort(reverse=True)
    if best and (len(best)==1 or best[0][0]>best[1][0]): vtm[name]=best[0][1]
# count how many vts each US function appears in
cnt=collections.Counter()
for name,uva in vtm.items():
    for i in range(len(jvt[name][1])):
        cnt[img.US.u32(uva+8+i*4)]+=1
cands={}
for name,uva in vtm.items():
    vc=name[len("__vt__"):]; m=re.match(r"(\d+)(.*)",vc)
    if not m: continue
    vcls=m.group(2)[:int(m.group(1))]
    for i,w1 in enumerate(jvt[name][1]):
        uw=img.US.u32(uva+8+i*4); n2=un.get(uw); j1=jn.get(w1)
        if not (n2 and n2.startswith('FUN_') and j1): continue
        if cnt[uw]!=1: continue
        if uw<0x450000: prog='SLUS_210.41'
        else: prog=ovl[2]
        jc=cls_of(j1)
        if j1.startswith('@'):
            # thunk: @N@method__cls... keep prefix, replace class
            mm=re.match(r'(@\d+@)(\w+?)__(\d+)([A-Za-z_]\w*)',j1)
            if not mm: continue
            pre,meth,ln,rest=mm.groups(); k=int(ln); sig=rest[k:]
            new='%s%s__%d%s%s'%(pre,meth,len(vcls),vcls,sig)
        else:
            mm=re.match(r'(\w+?)__(\d+)([A-Za-z_]\w*)',j1)
            if not mm: continue
            meth,ln,rest=mm.groups(); k=int(ln); sig=rest[k:]
            if rest[:k]==vcls: new=j1
            else: new='%s__%d%s%s'%(meth,len(vcls),vcls,sig)
        cands.setdefault((prog,uw),[]).append((new,name,i))
out=[]
for (prog,uw),l in cands.items():
    ns=set(x[0] for x in l)
    if len(ns)==1: out.append((prog,uw,l[0][0],l[0][1],l[0][2]))
with open('apply_vtover_%s.txt'%tag,'w') as f:
    for prog,uw,n,vt,i in out: f.write('%s %08x %s VTO %s.slot%d\n'%(prog,uw,n,vt,i))
print(len(vtm),len(out))
