# usage: callerev.py <dir> <usprog> <jpprog> [--apply]
import sys,os,pickle,re,json,urllib.request,collections
d,usp,jpp=sys.argv[1:4]
os.chdir(d); sys.path.insert(0,'.')
import gh
from concurrent.futures import ThreadPoolExecutor
from match import *
rows=pickle.load(open('rows.pkl','rb'))
us_now=dict(pickle.load(open('us_main.pkl','rb'))[0])
cand=[r for r in rows.values() if us_now.get(r['u'],'FUN_').startswith('FUN_') and r['s']>=0.4 and 0.3<=usz[r['u']]/max(1,jsz[r['j']])<=3.0]
print('cand',len(cand))
def callers(prog,addr):
    try: t=gh.get('get_function_callers',prog,address='%08x'%addr,timeout=60)
    except Exception: return None
    out=[]
    for l in t.splitlines():
        m=re.match(r'(.*) @ ([0-9a-f]+)$',l.strip())
        if m: out.append(m.group(1))
    return out
def f(r): return r,callers(usp,r['u']),callers(jpp,r['j'])
sel=[]
with ThreadPoolExecutor(4) as ex:
    for r,uc,jc in ex.map(f,cand):
        if uc is None or jc is None: continue
        uc=[c for c in uc if not c.startswith('FUN_')]; 
        ov=set(uc)&set(jc)
        if not ov: continue
        jac=len(ov)/len(set(uc)|set(jc))
        m=r['m']
        if m['nj']>=2 and m['nu']>=2 and (m['dice'] is None or m['dice']<0.4): continue
        if len(ov)>=2 or jac>=0.5:
            if r['mi'] and r['mi']['margin']<0.02 and not r['mi']['balanced']: continue
            r['tier']='G'; r['ov']=len(ov); sel.append(r)
print('selected',len(sel))
pickle.dump(sel,open('sel.pkl','wb'))
