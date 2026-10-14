# usage: applyl.py <file>   lines: prog addr(hex) newname tier note...   ; logs to applied_log.txt, failures to failed_log.txt
import sys,json,urllib.request,urllib.parse,re,collections
from concurrent.futures import ThreadPoolExecutor
import gh
f=sys.argv[1]
dry='--dry' in sys.argv
items=[]
for l in open(f):
    p=l.rstrip('\n').split(' ',4)
    if len(p)<4 or l.startswith('#'): continue
    items.append((p[0],p[1],p[2],p[3],p[4] if len(p)>4 else ''))
# current names per program
cur={}
for prog in set(i[0] for i in items):
    d={}
    for l in gh.get('list_functions',prog).splitlines():
        m=re.match(r'(.*) at ([0-9a-f]+)$',l.strip())
        if m: d[int(m.group(2),16)]=m.group(1)
    cur[prog]=d
byname=collections.defaultdict(set)
for prog,d in cur.items():
    for a,n in d.items(): byname[(prog,n)].add(a)
todo=[];skip=collections.Counter()
seen={}
for prog,a,n,t,note in items:
    ai=int(a,16)
    c=cur[prog].get(ai)
    if c is None: skip['nofunc']+=1; continue
    if not (c.startswith('FUN_') or c.startswith('thunk_FUN') ): skip['already']+=1; continue
    if (prog,ai) in seen:
        if seen[(prog,ai)]!=n: skip['conflict']+=1
        continue
    seen[(prog,ai)]=n
    if byname.get((prog,n)): skip['dupname']+=1; continue
    byname[(prog,n)].add(ai)
    todo.append((prog,a,n,t,note))
print('todo',len(todo),dict(skip))
if dry: sys.exit()
def post(prog,a,n):
    rq=urllib.request.Request('http://127.0.0.1:8089/rename_function_by_address?program=%s'%prog,json.dumps({'function_address':a,'new_name':n}).encode(),{'Content-Type':'application/json'})
    return urllib.request.urlopen(rq,timeout=120).read().decode()
def ren(x):
    prog,a,n,t,note=x
    try: r=post(prog,a,n)
    except Exception as e: r='ERR %s'%e
    return x,r
ok=0;fail=[]
with ThreadPoolExecutor(4) as ex:
    for x,r in ex.map(ren,todo):
        if 'uccess' in r:
            ok+=1; open('applied_log.txt','a').write('%s %s %s %s %s\n'%x)
        else:
            fail.append((x,r[:100])); open('failed_log.txt','a').write('%s %s %s %s %s | %s\n'%(x+(r[:100].replace('\n',' '),)))
print('renamed',ok,'failed',len(fail)); print(fail[:5])
