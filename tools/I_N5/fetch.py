import gh,os,sys,re
from concurrent.futures import ThreadPoolExecutor
prog=sys.argv[1]; listfile=sys.argv[2]; out=sys.argv[3]; ep=sys.argv[4] if len(sys.argv)>4 else 'decompile_function'
os.makedirs(out,exist_ok=True)
addrs=[l.split()[0] for l in open(listfile) if l.strip()]
def f(a):
    p='%s/%s.c'%(out,a)
    if os.path.exists(p) and os.path.getsize(p)>20 and not open(p).read(4)=='ERR ': return
    for _ in range(3):
        try: t=gh.get(ep,prog,address=a,timeout=180); break
        except Exception as e: t='ERR %s'%e
    open(p,'w').write(t)
with ThreadPoolExecutor(6) as ex: list(ex.map(f,addrs))
print('done',len(addrs))
