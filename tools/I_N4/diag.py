import collections
import metrics,holdout
from match import *
def reason(m,s,mi):
    if s<0.7: return 'low'
    if m['nj']>=2 and m['nu']>=2 and m['dice'] is not None and m['dice']<0.7: return 'dice'
    if m['ncj']>=3 and m['ncu']>=3 and m['cjac'] is not None and m['cjac']<0.5: return 'cjac'
    small=min(m['usize'],m['jsize'])<0x120
    if small and m['adice'] is not None and m['adice']<0.85: return 'small-adice'
    if mi['margin']<0.03 and not (mi['balanced'] and mi['glen']<=40): return 'margin'
    if min(m['usize'],m['jsize'])<0x50 and m['nshared_c']==0 and not mi['balanced']: return 'tiny'
    return 'info'
out=collections.defaultdict(lambda:[0,0])
for P,pairs,J,U,S in holdout.RES:
    mi=metrics.margin_info(P,pairs,J,U,S)
    for j,u,s in pairs:
        if u not in holdout.hidU: continue
        m=metrics.metrics(P,j,u)
        t=metrics.tier2(m,s,mi[(j,u)])
        ok=jname[j]==jname[holdout.truth[u]]
        key=t if t else 'rej:'+reason(m,s,mi[(j,u)])
        out[key][0 if ok else 1]+=1
for k,v in sorted(out.items(),key=str): print(k,v)
