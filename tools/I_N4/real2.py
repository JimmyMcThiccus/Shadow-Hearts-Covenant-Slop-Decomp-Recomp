import pickle,collections,sys
import gapmatch,metrics,stage2
from match import *
res=gapmatch.run_all()
rows={}
for P,pairs,J,U,S in res:
    if not P.J or not P.U or not J or not U: continue
    mi=metrics.margin_info(P,pairs,J,U,S) if pairs else {}
    tiers={}
    for j,u,s in pairs:
        m=metrics.metrics(P,j,u)
        t=metrics.tier2(m,s,mi[(j,u)])
        rows[u]=dict(u=u,j=j,s=s,tier=t,m=m,mi=mi[(j,u)])
        if t: tiers[(j,u)]=t
    for it in range(4):
        new=stage2.stage2(P,pairs,J,U,S,tiers)
        added=0
        for j,u,s,m in new:
            if tiers.get((j,u)) in ('A','B','D','E','F'): continue
            tiers[(j,u)]='E'; added+=1
            r=rows.get(u)
            if r is None: rows[u]=dict(u=u,j=j,s=s,tier='E',m=m,mi=None)
            elif r['tier'] is None or r['tier']=='C': r['tier']='E'
        if not added: break
pickle.dump(rows,open('real2_rows.pkl','wb'))
print(collections.Counter(r['tier'] for r in rows.values()),len(rows))
