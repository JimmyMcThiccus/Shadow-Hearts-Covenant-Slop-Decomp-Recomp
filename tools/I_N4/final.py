import pickle,collections,json,urllib.request,sys
from concurrent.futures import ThreadPoolExecutor
from match import *
APPLY='--apply' in sys.argv
rows=pickle.load(open('real2_rows.pkl','rb'))
def ok(r):
    ratio=usz[r['u']]/jsz[r['j']] if jsz[r['j']] else 0
    return 0.35<=ratio<=2.5
app=sorted([r for r in rows.values() if r['tier'] in ('A','B','D','E','F') and ok(r)],key=lambda r:r['u'])
pend=sorted([r for r in rows.values() if r['tier']=='C' or (r['tier'] in ('A','B','D','E','F') and not ok(r))],key=lambda r:r['u'])
print(len(app),len(pend),collections.Counter(r['tier'] for r in app))
def post(ep,prog,d):
    rq=urllib.request.Request('http://127.0.0.1:8089/%s?program=%s'%(ep,prog),json.dumps(d).encode(),{'Content-Type':'application/json'})
    return urllib.request.urlopen(rq,timeout=120).read().decode()
def ren(r):
    try:
        t=post('rename_function_by_address','SLUS_210.41',{'function_address':'%08x'%r['u'],'new_name':jname[r['j']]})
    except Exception as e: t='ERR %s'%e
    return r,t
if APPLY:
    fails=[];good=0
    with ThreadPoolExecutor(4) as ex:
        for r,t in ex.map(ren,app):
            if 'uccess' in t: good+=1
            else: fails.append((hex(r['u']),jname[r['j']],t[:120]))
    print('renamed',good,'failed',len(fails)); print(fails[:10])
    import os
    k=1
    while os.path.exists('applied%d.pkl'%k): k+=1
    pickle.dump((app,fails),open('applied%d.pkl'%k,'wb'))
