import pickle,collections,sys
import gapmatch,metrics,stage2
from match import *
import os
res=gapmatch.run_all(theta=float(os.environ.get('THETA','0.5')))
rows={}
for P,pairs,J,U,S in res:
    if not P.J or not P.U or not J or not U: continue
    mi=metrics.margin_info(P,pairs,J,U,S) if pairs else {}
    for j,u,s in pairs:
        m=metrics.metrics(P,j,u)
        rows[u]=dict(u=u,j=j,s=s,m=m,mi=mi[(j,u)],glen=(len(J),len(U)))
pickle.dump(rows,open('rows.pkl','wb'))
print(len(rows))
