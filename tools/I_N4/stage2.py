import collections
import feat2,metrics
from match import *
def pair_ok(m,s):
    """minimum evidence for an order-implied pair"""
    if m['nshared_c']>=30 and (m['cjac'] or 0)>=0.5 and m['shared']>=1 and 0.4<=m['ratio']<=2.5: return True
    if m['nj']>=1 and m['nu']>=1:
        if m['shared']<1: return False
        if (m['dice'] is None or m['dice']<0.5) and not (m['prec'] is not None and m['prec']>=0.8 and m['inter']>=6 and m['unk']>=0.3*(m['nu']+m['unk'])): return False
        if m['shared']>=5: return s>=0.45
        return s>=0.6
    if m['nj']==0 and m['nu']==0:
        # leaf: need numeric agreement over a handful of constants
        return m['nall']>=3 and m['adice'] is not None and m['adice']>=0.9 and s>=0.7
    # one side has callees, other none (inlined): numeric agreement
    return m['nall']>=3 and m['adice'] is not None and m['adice']>=0.85 and s>=0.7
def stage2(P,pairs,J,U,S,tiers,maxrun=8):
    """tiers: dict (j,u)->tier for confirmed. Returns list of (j,u,s,m) newly accepted."""
    ji={a:i for i,a in enumerate(J)}; ui={a:i for i,a in enumerate(U)}
    conf=sorted([(ji[j],ui[u]) for (j,u),t in tiers.items() if t in ('A','B','D','E','F')])
    # boundaries: virtual anchors at -1 and len
    bounds=[(-1,-1)]+conf+[(len(J),len(U))]
    out=[]
    for (j0,u0),(j1,u1) in zip(bounds,bounds[1:]):
        js=list(range(j0+1,j1)); us=list(range(u0+1,u1))
        if not js or len(js)!=len(us) or len(js)>maxrun: continue
        prs=[(J[a],U[b]) for a,b in zip(js,us)]
        ms=[]
        okall=True
        for j,u in prs:
            m=metrics.metrics(P,j,u); s=S[ji[j]][ui[u]]
            ms.append((j,u,s,m))
            if not pair_ok(m,s): okall=False
        if okall: out.extend(ms)
    return out
