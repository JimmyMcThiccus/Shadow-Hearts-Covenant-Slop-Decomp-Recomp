import pickle,collections,sys
from match import *
rows=pickle.load(open('rows.pkl','rb'))
def accept(r):
    m=r['m'];s=r['s'];mi=r['mi']
    ratio=usz[r['u']]/jsz[r['j']] if jsz[r['j']] else 0
    if not 0.3<=ratio<=3.0: return None
    nj,nu=m['nj'],m['nu']
    d=m['dice']; sh=m['shared']
    if nj>=1 and nu>=1:
        if sh<1: return None
        if nj>=2 and nu>=2 and (d is None or d<0.5) and not (m['unk']>0 and m['prec'] and m['prec']>=0.8): return None
        if s>=0.6 and mi['margin']>=0.03: return 'C1'
        if s>=0.5 and d is not None and d>=0.8 and sh>=2 and mi['margin']>=0.1: return 'C2'
        if s>=0.3 and sh>=1 and d is not None and d>=0.5 and mi['margin']>=0.03: return 'C3'
        return None
    if nj==0 and nu==0:
        # leaf: need numeric agreement
        if m['nall']>=3 and m['adice'] is not None and m['adice']>=0.9 and s>=0.7 and (mi['margin']>=0.2 or mi['balanced'] and mi['glen']<=30): return 'L1'
        return None
    # one side has no callees (inlined): numeric agreement only
    if m['nall']>=4 and m['adice'] is not None and m['adice']>=0.85 and s>=0.7 and mi['margin']>=0.2: return 'L2'
    return None
sel=[]
cnt=collections.Counter()
for r in sorted(rows.values(),key=lambda r:r['u']):
    t=accept(r)
    cnt[t]+=1
    if t: r['tier']=t; sel.append(r)
print(cnt)
pickle.dump(sel,open('sel.pkl','wb'))
