import sys,re,collections; sys.path.insert(0,'.')
from lib import *
from concurrent.futures import ThreadPoolExecutor
rows=[r for r in unnamed_list() if r['cause'].startswith('rewritten')]
res=[]
def calls(t): return collections.Counter(re.findall(r'\b([A-Za-z_][A-Za-z0-9_@]*)\s*\(',t))
KW={'if','while','for','switch','return','sizeof','int','char','short','long','float','undefined','uint','ulong','byte','bool','void'}
def job(r):
    p=r['prog']; jp=PAIR[p]
    nm=namemap(p).get(r['addr'])
    jpm={}
    for a,n in fnlist(jp): jpm.setdefault(n,[]).append(a)
    cand=jpm.get(nm,[])
    try: ut=subst(p,getdec(p,r['addr']))
    except Exception as e: ut=''
    info=dict(r=r,name=nm,jp=cand)
    if cand:
        ja=cand[0]
        info['jpsize']=sizes(fnlist(jp)).get(ja,0)
        try: jt=subst(jp,getdec(jp,ja))
        except Exception as e: jt=''
        uc=calls(ut); jc=calls(jt)
        f=lambda c:{k for k in c if k not in KW and not re.match(r'(FUN_|func_0x|param|local|iVar|uVar|pc|pi)',k)}
        info['added']=sorted(f(uc)-f(jc)); info['removed']=sorted(f(jc)-f(uc))
        info['ulines']=ut.count('\n'); info['jlines']=jt.count('\n')
    else: info['ulines']=ut.count('\n')
    return info
with ThreadPoolExecutor(8) as ex: res=list(ex.map(job,rows))
import json; json.dump(res,open('/private/tmp/claude-501/-Users-jamietheanything-Documents-Sh2-Decomp/358b01e4-f5fb-4974-8473-2253168698e1/scratchpad/rewdiff.json','w'),default=str)
for i in res:
    r=i['r']
    print('%s %08x %s us=%x jp=%s lines %s/%s +%s -%s'%(r['prog'][:6],r['addr'],i['name'],r['size'],hex(i.get('jpsize',0)) if i['jp'] else '-',i.get('ulines'),i.get('jlines'),i.get('added','')[:6],i.get('removed','')[:6]))
