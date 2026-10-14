import sys,pickle,collections
import feat2,match,gapmatch
from match import *
lis=pickle.load(open('anchors.pkl','rb'))
hid=pickle.load(open('hidden.pkl','rb'))
hidU={u for u,j in hid}; truth={u:j for u,j in hid}
anch=[x for x in lis if x[0] not in hidU]
unnamed=set(a for a,n in us_list if n.startswith('FUN_') or n.startswith('thunk'))|hidU
gaps=[]
for k in range(len(anch)+1):
    ul=anch[k-1][0] if k>0 else 0; uh=anch[k][0] if k<len(anch) else 1<<32
    jl=anch[k-1][1] if k>0 else 0; jh=anch[k][1] if k<len(anch) else 1<<32
    U=[(a,uname[a]) for a,n in us_list if ul<a<uh and a in unnamed]
    if not U: continue
    J=[(a,s,n) for a,s,n in jp_list if jl<a<jh]
    # only gaps containing a hidden function, to limit work
    if not any(u in hidU for u,_ in U): continue
    gaps.append((ul,uh,jl,jh,U,J))
print('holdout gaps',len(gaps),file=sys.stderr)
gapmatch.gaps=gaps
gapmatch.GUSMAP.clear()
for a,n in us_list:
    if a not in unnamed: gapmatch.GUSMAP[a]=n
res=gapmatch.run_all()
rows=[]
RES=res
for P,pairs,J,U,S in res:
    for j,u,s in pairs:
        if u in hidU: rows.append((s,u,j,P))
print('hidden',len(hidU),'paired',len(rows))
import math
for thr in [0.5,0.6,0.7,0.8,0.9,0.95]:
    sel=[r for r in rows if r[0]>=thr]
    ok=sum(1 for s,u,j,P in sel if jname[j]==jname[truth[u]])
    print('thr %.2f selected %d correct %d wrong %d  recall %.2f'%(thr,len(sel),ok,len(sel)-ok,ok/len(hidU)))
pickle.dump([(s,u,j) for s,u,j,P in rows],open('holdout_rows.pkl','wb'))
# wrong ones
for s,u,j,P in sorted(rows,key=lambda r:-r[0]):
    if jname[j]!=jname[truth[u]] and s>=0.6:
        print('WRONG %.2f us %x (truth %s) -> jp %s  sizes %x/%x'%(s,u,jname[truth[u]][:40],jname[j][:40],usz[u],jsz[j]))
