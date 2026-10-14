# usage: pairup.py <usprog> lo hi  -- order-preserving pairing of unnamed US functions with JP-unused methods of the same class
import sys,re,math,collections
sys.path.insert(0,'.')
from lib import *
from concurrent.futures import ThreadPoolExecutor
us=sys.argv[1]; lo=int(sys.argv[2],16); hi=int(sys.argv[3],16); jp=PAIR[us]
LU=fnlist(us,True); LJ=fnlist(jp); SU=sizes(LU); SJ=sizes(LJ)
used=set(n for a,n in LU if not isun(n))
def cls(n):
    m=re.search(r'__(\d+)([A-Za-z_]\w*)',n)
    return m.group(2)[:int(m.group(1))] if m else None
KW={'if','while','for','switch','return','sizeof','else','case','goto','code','undefined','int','uint','long','ulong','char','byte','float','short','ushort','void','bool'}
def calls(prog,a):
    t=subst(prog,getdec(prog,a)); body=t[t.find('{'):]
    return collections.Counter(c for c in re.findall(r'(?<![\w.>])([A-Za-z_@][\w@]*)\s*\(',body) if c not in KW and not c.startswith('_v') and not c.startswith('_lq') and not c.startswith('_sq') and not c.startswith('CONCAT') and not c.startswith('FUN_'))
ju=[(a,n) for a,n in LJ if n not in used]
runs=[]; 
us_un=[(i,a,n) for i,(a,n) in enumerate(LU) if isun(n) and lo<=a<hi]
# group into class runs
def nbcls(i):
    j=i-1
    while j>0 and (isun(LU[j][1]) or not cls(LU[j][1])): j-=1
    k=i+1
    while k<len(LU)-1 and (isun(LU[k][1]) or not cls(LU[k][1])): k+=1
    k=min(k,len(LU)-1)
    return (cls(LU[j][1]),cls(LU[k][1]))
groups=collections.OrderedDict()
for i,a,n in us_un:
    pc,nc=nbcls(i)
    key=pc if pc==nc else (pc,nc)
    groups.setdefault(key,[]).append(a)
need=[]
for key,addrs in groups.items():
    cs=set([key]) if isinstance(key,str) else set(x for x in key if x)
    for ja,jn in ju:
        if cls(jn) in cs: need.append(ja)
with ThreadPoolExecutor(6) as ex: list(ex.map(lambda a: getdec(jp,a),sorted(set(need))))
with ThreadPoolExecutor(6) as ex: list(ex.map(lambda a: getdec(us,a),[a for k,v in groups.items() for a in v]))
def sc(ua,ja):
    cu=calls(us,ua); cj=calls(jp,ja)
    inter=sum((cu&cj).values()); tot=sum(cu.values())+sum(cj.values())
    d=2*inter/tot if tot else 0.5
    r=SU[ua]/SJ[ja]; s=1.0 if .45<=r<=1.6 else max(0,1-abs(math.log(r/.9))/1.5)
    return .65*d+.35*s
for key,addrs in groups.items():
    cs=set([key]) if isinstance(key,str) else set(x for x in key if x)
    cand=[(ja,jn) for ja,jn in ju if cls(jn) in cs]
    print('== group',key,'US',['%x(%x)'%(a,SU[a]) for a in addrs])
    if not cand: print('   (no JP-unused candidates)'); continue
    print('   JP:',' '.join('%x(%x)%s'%(ja,SJ[ja],jn.split('__')[0]) for ja,jn in cand))
    n=len(addrs); m=len(cand)
    S=[[sc(addrs[i],cand[j][0]) for j in range(m)] for i in range(n)]
    D=[[0]*(m+1) for _ in range(n+1)]; B=[[0]*(m+1) for _ in range(n+1)]
    th=.45
    for i in range(1,n+1):
        for j in range(1,m+1):
            best=D[i-1][j]; b=1
            if D[i][j-1]>best: best=D[i][j-1]; b=2
            if S[i-1][j-1]>th and D[i-1][j-1]+S[i-1][j-1]>best: best=D[i-1][j-1]+S[i-1][j-1]; b=0
            D[i][j]=best; B[i][j]=b
    i,j=n,m; pairs=[]
    while i>0 and j>0:
        if B[i][j]==0: pairs.append((i-1,j-1)); i-=1; j-=1
        elif B[i][j]==1: i-=1
        else: j-=1
    for i,j in sorted(pairs): print('   %08x(%x) -> %s (%x) score %.2f'%(addrs[i],SU[addrs[i]],cand[j][1],SJ[cand[j][0]],S[i][j]))
