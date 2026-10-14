import pickle,json,urllib.request,sys
from match import *
res=pickle.load(open('stage3.pkl','rb'))
sel=[]
for r,uc,jc in res:
    if uc is None or jc is None: continue
    m=r['m']; mi=r['mi']; s=r['s']
    if r['u']<0x240000: continue
    ov=set(uc)&set(jc)
    if not ov: continue
    jac=len(ov)/len(set(uc)|set(jc))
    if not(jac>=0.3 or len(ov)>=2): continue
    if m['nj']>=2 and m['nu']>=2 and (m['dice'] is None or m['dice']<0.5): continue
    if s<0.6 or m['shared']<1: continue
    if mi and mi['margin']<0.03 and not mi['balanced']: continue
    ratio=usz[r['u']]/jsz[r['j']]
    if not 0.35<=ratio<=2.5: continue
    sel.append(r)
print('G candidates',len(sel))
def post(ep,prog,d):
    rq=urllib.request.Request('http://127.0.0.1:8089/%s?program=%s'%(ep,prog),json.dumps(d).encode(),{'Content-Type':'application/json'})
    return urllib.request.urlopen(rq,timeout=120).read().decode()
ok=[];fail=[]
if '--apply' in sys.argv:
    for r in sel:
        t=post('rename_function_by_address','SLUS_210.41',{'function_address':'%08x'%r['u'],'new_name':jname[r['j']]})
        if 'uccess' in t: r['tier']='G'; ok.append(r)
        else: fail.append((hex(r['u']),jname[r['j']],t[:100]))
    print('applied',len(ok),'failed',fail)
    k=1
    while os.path.exists('applied_G%d.pkl'%k) if False else False: k+=1
    import os
    k=2
    while os.path.exists('applied_G%d.pkl'%k): k+=1
    pickle.dump((ok,fail),open('applied_G%d.pkl'%k,'wb'))
