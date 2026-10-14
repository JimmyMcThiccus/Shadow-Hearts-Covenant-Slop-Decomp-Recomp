import collections
import metrics,holdout,stage2
from match import *
tot=collections.Counter()
for P,pairs,J,U,S in holdout.RES:
    if not pairs: continue
    mi=metrics.margin_info(P,pairs,J,U,S)
    tiers={}
    for j,u,s in pairs:
        m=metrics.metrics(P,j,u)
        t=metrics.tier2(m,s,mi[(j,u)])
        if t: tiers[(j,u)]=t
    new=stage2.stage2(P,pairs,J,U,S,tiers)
    for j,u,s,m in new:
        if u in holdout.hidU:
            tot['ok' if jname[j]==jname[holdout.truth[u]] else 'wrong']+=1
            if jname[j]!=jname[holdout.truth[u]]: print('WRONG',hex(u),jname[holdout.truth[u]],'->',jname[j],'s=%.2f'%s)
        else: tot['nonhidden']+=1
print(dict(tot))
