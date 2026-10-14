# holdout evaluation: hide every k-th anchor, rerun DP on affected gaps, measure precision vs score/evidence
import sys,pickle,collections,os
import feat2,match,gapmatch,metrics,stage2
from match import *
K=int(sys.argv[1]) if len(sys.argv)>1 else 6
lis=pickle.load(open('anchors.pkl','rb'))
R=int(sys.argv[2]) if len(sys.argv)>2 else 1
hid=[x for i,x in enumerate(lis) if i%K<R]
hidU={u for u,j in hid}; truth={u:j for u,j in hid}
anch=[x for x in lis if x[0] not in hidU]
NOISE=int(sys.argv[3]) if len(sys.argv)>3 else 0
dropJ=set(j for u,j in hid if NOISE and (u>>4)%NOISE==0)
dropU=set(u for u,j in hid if j in dropJ)
print('dropped jp',len(dropJ),file=sys.stderr)
allnamed=set(a for a,n in us_list if not (n.startswith('FUN_') or n.startswith('thunk')))
unnamed=set(a for a,n in us_list if n.startswith('FUN_') or n.startswith('thunk'))|hidU
gaps=[]
for k in range(len(anch)+1):
    ul=anch[k-1][0] if k>0 else 0; uh=anch[k][0] if k<len(anch) else 1<<32
    jl=anch[k-1][1] if k>0 else 0; jh=anch[k][1] if k<len(anch) else 1<<32
    U=[(a,uname[a]) for a,n in us_list if ul<a<uh and a in unnamed]
    if not U: continue
    J=[(a,s,n) for a,s,n in jp_list if jl<a<jh and a not in dropJ]
    if not any(u in hidU for u,_ in U): continue
    gaps.append((ul,uh,jl,jh,U,J))
print('holdout gaps',len(gaps),'hidden',len(hidU),file=sys.stderr)
gapmatch.gaps=gaps
gapmatch.GUSMAP.clear()
gapmatch.GUSMAP.update(pickle.load(open('us_mainnames.pkl','rb')))
for a,n in us_list:
    if a not in unnamed: gapmatch.GUSMAP[a]=n
import os
res=gapmatch.run_all(theta=float(os.environ.get('THETA','0.5')))
rows=[]
for P,pairs,J,U,S in res:
    if not pairs: continue
    mi=metrics.margin_info(P,pairs,J,U,S)
    for j,u,s in pairs:
        if u in hidU:
            m=metrics.metrics(P,j,u)
            rows.append(dict(u=u,j=j,s=s,m=m,mi=mi[(j,u)],ok=(jname[j]==jname[truth[u]]) and u not in dropU,dropped=u in dropU))
pickle.dump((rows,list(hidU)),open('ho_rows.pkl','wb'))
print('hidden',len(hidU),'paired',len(rows),'correct pairs',sum(r['ok'] for r in rows))
# sandwich test
import gapmatch as gm
cnt=collections.Counter()
for g in gaps:
    ul,uh,jl,jh,U,J=g
    if not (1<=len(U)==len(J)<=4): continue
    if not all(u in hidU for u,_ in U): continue
    P=gm.build(g)
    for (u,_),(j,_,_) in zip(U,J):
        m=metrics.metrics(P,j,u)
        ratio=m['ratio']; nj,nu=m['nj'],m['nu']; sh=m['shared']
        ok=0.4<=ratio<=2.6
        if ok:
            if nj>=1 and nu>=1:
                if sh<1: ok=False
                elif nj>=2 and nu>=2 and (m['dice'] or 0)<0.3: ok=False
            elif nj==0 and nu==0: pass
            else: ok=(m['adice'] or 0)>=0.5 or 0.6<=ratio<=1.7
        correct=(jname[j]==jname[truth[u]]) and u not in dropU
        cnt[(len(U),ok,correct)]+=1
print('SANDWICH',sorted(cnt.items()))
