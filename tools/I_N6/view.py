# usage: view.py <usprog> addr[,addr..] [nl]  -- brief decompile + JP-unused names of the same class (neighbour classes)
import sys,re
sys.path.insert(0,'.')
from lib import *
us=sys.argv[1]; nl=int(sys.argv[3]) if len(sys.argv)>3 else 12
jp=PAIR[us]; LU=fnlist(us); LJ=fnlist(jp); SU=sizes(LU); SJ=sizes(LJ)
used=set(n for a,n in LU if not isun(n))
ju=[(a,n) for a,n in LJ if n not in used]
def cls(n):
    m=re.search(r'__(\d+)([A-Za-z_]\w*)',n)
    return m.group(2)[:int(m.group(1))] if m else None
for a in sys.argv[2].split(','):
    a=int(a,16); i=[k for k,(x,n) in enumerate(LU) if x==a][0]
    j=i-1
    while j>0 and (isun(LU[j][1]) or not cls(LU[j][1])): j-=1
    k=i+1
    while k<len(LU)-1 and (isun(LU[k][1]) or not cls(LU[k][1])): k+=1
    k=min(k,len(LU)-1)
    cs=set([cls(LU[j][1]),cls(LU[k][1])])
    cand=['%x(%x)%s'%(ja,SJ[ja],n.split('__')[0]) for ja,n in ju if cls(n) in cs]
    print('#### %08x sz=%x prev=%s next=%s'%(a,SU[a],LU[i-1][1][:40],LU[i+1][1][:40]))
    print('   JP-unused same class:',' '.join(cand[:14]))
    for l in brief(us,a,nl,112): print(l)
