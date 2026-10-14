import sys,re,pickle,collections,math,json
import feat2
from pk2 import PK
us_list,usz=pickle.load(open('us_main.pkl','rb'))
jp_list=pickle.load(open('jp_main.pkl','rb'))
jsz={a:s for a,s,n in jp_list}; jname={a:n for a,s,n in jp_list}
jaddr={n:a for a,s,n in jp_list}
uname={a:n for a,n in us_list}
MATHCLS={'FVector','Matrix','Quaternion','SVector','FVector4','Vector'}
def clsof(n):
    m=re.search(r'__(\d+)([A-Za-z_]\w*)',n)
    if m:
        k=int(m.group(1)); return m.group(2)[:k]
    return None
LIBM={'sqrtf','sinf','cosf','tanf','atan2f','atanf','acosf','asinf','fabsf','sqrt','sin','cos','atan2','floorf','ceilf','fmodf','powf','expf','logf','abs','fabs','sceVu0Normalize','sceVu0ApplyMatrix','sceVu0MulMatrix','sceVu0CopyVector','sceVu0AddVector','sceVu0SubVector','sceVu0ScaleVector','sceVu0InnerProduct','sceVu0OuterProduct','sceVu0UnitMatrix','sceVu0TransMatrix','sceVu0RotMatrix','sceVu0RotMatrixX','sceVu0RotMatrixY','sceVu0RotMatrixZ','sceVu0InversMatrix','sceVu0TransposeMatrix','sceVu0CopyMatrix','sceVu0CameraMatrix','sceVu0Length','sceVu0ClampVector','sceVu0DivVector','sceVu0MulVector','sceVu0FTOI4Vector','sceVu0ITOF4Vector','sceVu0ITOF0Vector','sceVu0FTOI0Vector','sceVu0InterVector'}
def is_math(n):
    if n in LIBM: return True
    c=clsof(n)
    return c in MATHCLS
FUNRE=re.compile(r'^(?:thunk_)?FUN_([0-9a-fA-F]{8})$')
class Pkg:
    def __init__(self,name,usmap=None):
        ul,uh,jl,jh=PK[name]
        self.name=name
        self.J=[(a,jsz[a],jname[a]) for a,s,n in jp_list if jl<=a<jh]
        self.U=[(a,usz[a],uname[a]) for a,n in us_list if ul<=a<uh]
        self.usmap=usmap if usmap is not None else {}
        self.jf=feat2.load('jpdec',[a for a,_,_ in self.J])
        self.uf=feat2.load('usdec',[a for a,_,_ in self.U])
    def ucallees(self,a):
        """resolved callee list of US function a (list of names, 'UNK' unresolved)."""
        out=[]
        for n in self.uf[a]['calls']:
            m=FUNRE.match(n)
            if m:
                t=int(m.group(1),16)
                out.append(self.usmap.get(t,'UNK'))
            else: out.append(n)
        return out
    def jcallees(self,a):
        return list(self.jf[a]['calls'])
INTR=re.compile(r'^_(v[a-z0-9]*|lqc2|sqc2|qmtc2|qmfc2|ctc2|cfc2)$')
def filt(cs):
    return [c for c in cs if not is_math(c) and not INTR.match(c)]
def dice(c1,c2):
    a=collections.Counter(c1);b=collections.Counter(c2)
    inter=sum((a&b).values()); tot=sum(a.values())+sum(b.values())
    return (2*inter/tot if tot else None), inter
def jacc(s1,s2):
    s1=set(s1);s2=set(s2)
    if not s1 and not s2: return None
    return len(s1&s2)/len(s1|s2)
def lcs(a,b):
    n,m=len(a),len(b)
    if not n or not m: return 0
    prev=[0]*(m+1)
    for i in range(n):
        cur=[0]*(m+1)
        for j in range(m):
            cur[j+1]=prev[j]+1 if a[i]==b[j] else max(prev[j+1],cur[j])
        prev=cur
    return prev[m]
def score(P,ja,ua):
    jf=P.jf[ja]; uf=P.uf[ua]
    jc=filt(P.jcallees(ja)); uc_all=P.ucallees(ua)
    unk=sum(1 for c in uc_all if c=='UNK')
    uc=filt([c for c in uc_all if c!='UNK'])
    parts=[];w=[]
    # callees
    d,inter=dice(jc,uc)
    if d is not None:
        # unknown callees reduce certainty: if unk>0 compare only against jp callees not otherwise explained
        if unk and d<1:
            # allow up to unk unmatched jp callees
            jm=collections.Counter(jc)-collections.Counter(uc)
            miss=sum(jm.values())
            if miss<=unk and not (collections.Counter(uc)-collections.Counter(jc)): d=max(d,0.9)
        parts.append(d);w.append(0.35)
        if len(jc)>1 and len(uc)>1:
            l=lcs(jc,uc)/max(len(jc),len(uc)); parts.append(l);w.append(0.1)
    elif unk==0:
        pass
    # constants
    cj=jf['consts'];cu=uf['consts']
    j=jacc(cj.keys(),cu.keys())
    if j is not None: parts.append(j);w.append(0.25)
    # vcalls
    vj=jf['vcalls'];vu=uf['vcalls']
    if vj or vu:
        d2,_=dice(vj,vu); parts.append(d2 if d2 is not None else 0);w.append(0.1)
    # cases
    if jf['cases'] or uf['cases']:
        parts.append(1.0 if jf['cases']==uf['cases'] else (jacc(jf['cases'],uf['cases']) or 0)*0.8);w.append(0.1)
    # offsets
    o=jacc(jf['offs'].keys(),uf['offs'].keys())
    if o is not None: parts.append(o);w.append(0.1)
    # size
    sj=P.jsz(ja);su=P.usz_(ua)
    r=su/sj if sj else 0
    if 0.55<=r<=1.15: sc=1.0
    else: sc=max(0.0,1-abs(math.log(r/0.85))/1.2) if r>0 else 0
    parts.append(sc);w.append(0.1)
    if not w: return 0.0
    return sum(p*x for p,x in zip(parts,w))/sum(w)
Pkg.jsz=lambda self,a: jsz[a]
Pkg.usz_=lambda self,a: usz[a]
def dp(P,theta=0.5,S=None):
    J=[a for a,_,_ in P.J if a in P.jf]; U=[a for a,_,_ in P.U if a in P.uf]
    n,m=len(J),len(U)
    if S is None: S=[[score(P,j,u) for u in U] for j in J]
    D=[[0.0]*(m+1) for _ in range(n+1)]; B=[[0]*(m+1) for _ in range(n+1)]
    for i in range(1,n+1):
        for k in range(1,m+1):
            best=D[i-1][k]; b=1
            if D[i][k-1]>best: best=D[i][k-1]; b=2
            s=S[i-1][k-1]
            if s>theta:
                v=D[i-1][k-1]+(s-theta)
                if v>best: best=v;b=0
            D[i][k]=best;B[i][k]=b
    i,k=n,m;pairs=[]
    while i>0 and k>0:
        b=B[i][k]
        if b==0: pairs.append((J[i-1],U[k-1],S[i-1][k-1])); i-=1;k-=1
        elif b==1: i-=1
        else: k-=1
    pairs.reverse()
    return pairs,J,U,S
def run(name,rounds=3,theta=0.5,accept=0.7,verbose=True,truth=True):
    P=Pkg(name)
    # seed usmap from already-named US functions
    for a,sz,n in P.U:
        if not (n.startswith('FUN_') or n.startswith('thunk')): P.usmap[a]=n
    for a,n in us_list:
        if not (n.startswith('FUN_') or n.startswith('thunk')): P.usmap[a]=n
    hist=[]
    cur={}
    for r in range(rounds):
        pairs,J,U,S=dp(P,theta)
        newmap=0
        for j,u,s in pairs:
            if s>=accept and (uname[u].startswith('FUN_') or uname[u].startswith('thunk')):
                if P.usmap.get(u)!=jname[j]: P.usmap[u]=jname[j]; newmap+=1
        if verbose: print(name,'round',r,'pairs',len(pairs),'acc>=%.2f'%accept,sum(1 for p in pairs if p[2]>=accept),'newmap',newmap,file=sys.stderr)
        cur=pairs
        if newmap==0: break
    return P,cur
if __name__=='__main__':
    name=sys.argv[1]
    P,pairs=run(name)
    # truth check: US functions with names equal to a JP name
    ok=bad=0
    for j,u,s in pairs:
        n=uname[u]
        if not(n.startswith('FUN_') or n.startswith('thunk')):
            if n==jname[j]: ok+=1
            else: bad+=1
    named_total=sum(1 for a,_,n in P.U if not(n.startswith('FUN_') or n.startswith('thunk')))
    print(name,'truth: named US',named_total,'paired correct',ok,'wrong',bad)
