import re,collections,img,pickle,sys,json,urllib.request
tag=sys.argv[1]; do=('--apply' in sys.argv)
ovl={'field':('fn_SH2US_FIELD.BIN.txt','fn_SH2JP_FIELD.BIN.txt','SH2US_FIELD.BIN',0x45ea80,0x600000),'battle':('fn_SH2US_BATTLE.BIN.txt','fn_SH2JP_BATTLE.BIN.txt','SH2US_BATTLE.BIN',0x45ea80,0x700000)}[tag]
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
starts=[a for a in range(0x42f000,0x450000,4) if img.US.u32(a)==0 and img.US.u32(a+4)==0 and (img.US.u32(a+8) in un or img.US.u32(a+8)>=0x45ea80)]
def base(n): return n.split('__')[0]
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
        if ag>=1 and dis==0: best.append((ag,uva))
    best.sort(reverse=True)
    if best and (len(best)==1 or best[0][0]>best[1][0]): vtm[name]=best[0][1]
create={}
for name,uva in vtm.items():
    vc=re.match(r'__vt__(\d+)(.*)',name)
    if not vc: continue
    vcls=vc.group(2)[:int(vc.group(1))]
    for i,w1 in enumerate(jvt[name][1]):
        j1=jn.get(w1)
        if not j1 or not j1.startswith('@'): continue
        uw=img.US.u32(uva+8+i*4)
        if uw in un or not (0x200000<=uw<ovl[4]): continue
        m=re.match(r'@\d+@\w+?__(\d+)([A-Za-z_]\w*)',j1)
        if not m: continue
        jc=m.group(2)[:int(m.group(1))]
        if jc!=vcls: continue
        create.setdefault(uw,set()).add(j1)
res=[(a,list(s)[0]) for a,s in create.items() if len(s)==1]
print(len(vtm),len(res))
pickle.dump(res,open('thunks_%s.pkl'%tag,'wb'))
if do:
    prog=ovl[2]
    ok=0;fail=[]
    for a,n in sorted(res):
        pg=prog if a>=0x450000 else 'SLUS_210.41'
        rq=urllib.request.Request('http://127.0.0.1:8089/create_function?program=%s'%pg,json.dumps({'address':'%08x'%a,'name':n}).encode(),{'Content-Type':'application/json'})
        try:
            r=urllib.request.urlopen(rq,timeout=60).read().decode()
        except Exception as e: r='ERR %s'%e
        if '"success":true' in r.replace(' ',''): ok+=1; open('applied_log.txt','a').write('%s %08x %s THUNK vt\n'%(pg,a,n))
        else: fail.append((hex(a),n,r[:80]))
    print('created',ok,'fail',len(fail),fail[:3])
