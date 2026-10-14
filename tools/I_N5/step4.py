# extended sandwich: equal counts 5..14, require every pair to pass lenient check AND positional score decent
import pickle,collections,sys
import gapmatch,metrics
from match import *
gaps=pickle.load(open('gaps.pkl','rb'))
sel=[];cnt=collections.Counter()
for g in gaps:
    ul,uh,jl,jh,U,J=g
    if not (5<=len(U)==len(J)<=16): continue
    P=gapmatch.build(g)
    ms=[]
    allok=True
    for (u,_),(j,_,_) in zip(U,J):
        m=metrics.metrics(P,j,u); s=score(P,j,u)
        ratio=m['ratio']; nj,nu=m['nj'],m['nu']; sh=m['shared']
        ok=0.4<=ratio<=2.6
        if ok:
            if nj>=1 and nu>=1:
                if sh<1: ok=False
                elif nj>=2 and nu>=2 and (m['dice'] or 0)<0.4: ok=False
            elif nj==0 and nu==0: ok = s>=0.3
            else: ok=(m['adice'] or 0)>=0.5 or 0.6<=ratio<=1.7
        ms.append((u,j,s,m,ok))
        allok&=ok
    cnt[(len(U),allok)]+=1
    if allok:
        for u,j,s,m,ok in ms: sel.append(dict(u=u,j=j,s=s,m=m,tier='S%d'%len(U),mi=None))
print(cnt)
pickle.dump(sel,open('sel.pkl','wb'))
