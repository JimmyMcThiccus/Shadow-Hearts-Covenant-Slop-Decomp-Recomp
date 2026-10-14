import pickle,re,gh,collections
from concurrent.futures import ThreadPoolExecutor
from match import *
rr=pickle.load(open('real2_rows.pkl','rb'))
cand=[r for r in rr.values() if r['tier'] in (None,'C') and r['s']>=0.5]
print(len(cand))
def callers(prog,addr):
    try: t=gh.get('get_function_callers',prog,address='%08x'%addr,timeout=60)
    except Exception as e: return None
    out=[]
    for l in t.splitlines():
        m=re.match(r'(.*) @ ([0-9a-f]+)$',l.strip())
        if m: out.append(m.group(1))
    return out
def f(r): return r,callers(gh.MAIN,r['u']),callers(gh.JPM,r['j'])
res=[]
with ThreadPoolExecutor(4) as ex:
    for x in ex.map(f,cand): res.append(x)
pickle.dump(res,open('stage3.pkl','wb'))
