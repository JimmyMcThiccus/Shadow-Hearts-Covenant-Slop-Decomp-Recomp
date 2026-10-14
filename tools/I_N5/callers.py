import gh,re,sys,json,os
from concurrent.futures import ThreadPoolExecutor
prog=sys.argv[1]; lf=sys.argv[2]; out=sys.argv[3]
addrs=[l.split()[0] for l in open(lf)]
def f(a):
    for _ in range(3):
        try:
            t=gh.get('get_function_callers',prog,address=a,timeout=60); break
        except Exception as e: t=''
    r=[]
    for l in t.splitlines():
        m=re.match(r'(.*) @ ([0-9a-f]+)$',l.strip())
        if m: r.append((m.group(1),m.group(2)))
    return a,r
d={}
with ThreadPoolExecutor(6) as ex:
    for a,r in ex.map(f,addrs): d[a]=r
json.dump(d,open(out,'w'))
print(len(d))
