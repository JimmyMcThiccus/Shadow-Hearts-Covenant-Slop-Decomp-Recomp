import sys,pickle,collections,math,json
import feat2,match
from match import *
gaps=pickle.load(open('gaps.pkl','rb'))
class G:
    pass
def build(gap):
    ul,uh,jl,jh,U,J=gap
    P=G()
    P.J=[(a,s,n) for a,s,n in J]; P.U=[(a,usz[a],n) for a,n in U]
    P.jf=feat2.load('jpdec',[a for a,_,_ in P.J]); P.uf=feat2.load('usdec',[a for a,_,_ in P.U])
    P.usmap=GUSMAP
    P.jsz=lambda a: jsz[a]; P.usz_=lambda a: usz[a]
    P.ucallees=lambda a: Pkg.ucallees(P,a); P.jcallees=lambda a: list(P.jf[a]['calls'])
    return P
GUSMAP={}
for a,n in us_list:
    if not (n.startswith('FUN_') or n.startswith('thunk')): GUSMAP[a]=n
def run_all(rounds=4,theta=0.5,accept=0.7):
    Ps=[build(g) for g in gaps]
    res=None
    for r in range(rounds):
        res=[]
        newmap=0
        for P in Ps:
            if not P.J or not P.U: res.append((P,[],[],[],[])); continue
            pairs,J,U,S=dp(P,theta)
            res.append((P,pairs,J,U,S))
            for j,u,s in pairs:
                if s>=accept and GUSMAP.get(u)!=jname[j]:
                    GUSMAP[u]=jname[j]; newmap+=1
        print('round',r,'newmap',newmap,file=sys.stderr)
        if newmap==0: break
    return res
if __name__=='__main__':
    res=run_all()
    allp=[]
    for P,pairs,J,U,S in res:
        for j,u,s in pairs: allp.append((u,j,s,P))
    allp.sort()
    print('pairs',len(allp),'>=0.7',sum(1 for x in allp if x[2]>=0.7),'>=0.8',sum(1 for x in allp if x[2]>=0.8),'>=0.9',sum(1 for x in allp if x[2]>=0.9))
    pickle.dump([(u,j,s) for u,j,s,P in allp],open('pairs0.pkl','wb'))
