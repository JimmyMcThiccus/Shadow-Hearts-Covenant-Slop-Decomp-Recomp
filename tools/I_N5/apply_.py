import pickle,json,urllib.request,sys,os
from concurrent.futures import ThreadPoolExecutor
from match import *
prog=sys.argv[1]; tag=sys.argv[2]
sel=pickle.load(open('sel.pkl','rb'))
def post(ep,d):
    rq=urllib.request.Request('http://127.0.0.1:8089/%s?program=%s'%(ep,prog),json.dumps(d).encode(),{'Content-Type':'application/json'})
    return urllib.request.urlopen(rq,timeout=120).read().decode()
def ren(r):
    try: t=post('rename_function_by_address',{'function_address':'%08x'%r['u'],'new_name':jname[r['j']]})
    except Exception as e: t='ERR %s'%e
    return r,t
ok=[];fail=[]
with ThreadPoolExecutor(4) as ex:
    for r,t in ex.map(ren,sel):
        if 'uccess' in t: ok.append(r)
        else: fail.append((hex(r['u']),jname[r['j']],t[:100]))
print('renamed',len(ok),'failed',len(fail)); print(fail[:8])
with open('applied_%s.txt'%tag,'a') as f:
    for r in ok: f.write('%08x %08x %s %s %.2f %x %x\n'%(r['j'],r['u'],jname[r['j']],r['tier'],r['s'],usz[r['u']],jsz[r['j']]))
pickle.dump(fail,open('fail_%s.pkl'%tag,'wb'))
