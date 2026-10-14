import gh,os,sys,pickle
from concurrent.futures import ThreadPoolExecutor
gaps=pickle.load(open('gaps.pkl','rb'))
jobs=set()
for ul,uh,jl,jh,U,J in gaps:
    for a,n in U: jobs.add((gh.MAIN,'usdec',a))
    for a,s,n in J: jobs.add((gh.JPM,'jpdec',a))
jobs=sorted(jobs)
print(len(jobs),file=sys.stderr)
def f(j):
    prog,d,a=j
    p='%s/%08x.c'%(d,a)
    if os.path.exists(p) and os.path.getsize(p)>20 and not open(p).read(4)=='ERR ': return
    for _ in range(3):
        try:
            t=gh.get('decompile_function',prog,address='%08x'%a,timeout=180); break
        except Exception as e: t='ERR %s'%e
    open(p,'w').write(t)
with ThreadPoolExecutor(5) as ex: list(ex.map(f,jobs))
print('done')
