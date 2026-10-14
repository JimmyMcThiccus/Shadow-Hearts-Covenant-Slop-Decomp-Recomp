# usage: cand.py <us_lo> <us_hi> <jp_lo> <jp_hi> : top JP candidates for each unnamed US function in range (ignores order)
import sys,pickle,gapmatch,metrics
from match import *
ul,uh,jl,jh=[int(x,16) for x in sys.argv[1:5]]
us_list2,usz2=pickle.load(open('us_main.pkl','rb'))
U=[(a,n) for a,n in us_list2 if ul<=a<uh and n.startswith('FUN_')]
used=set(n for a,n in us_list2 if not n.startswith('FUN_'))
J=[(a,s,n) for a,s,n in jp_list if jl<=a<jh]
import types
P=types.SimpleNamespace()
P.J=J; P.U=[(a,usz[a],n) for a,n in U]
import feat2
P.jf=feat2.load('jpdec',[a for a,_,_ in J]); P.uf=feat2.load('usdec',[a for a,_,_ in P.U])
P.usmap=gapmatch.GUSMAP
P.jsz=lambda a: jsz[a]; P.usz_=lambda a: usz[a]
P.ucallees=lambda a: Pkg.ucallees(P,a); P.jcallees=lambda a: list(P.jf[a]['calls'])
missing=[a for a,_,_ in J if a not in P.jf]
for a,_ in U:
    if a not in P.uf: continue
    sc=[]
    for ja,js,jn_ in J:
        if ja not in P.jf: continue
        sc.append((score(P,ja,a),ja,jn_))
    sc.sort(reverse=True)
    print('%x(%x):'%(a,usz[a]),' | '.join('%.2f %s%s'%(s,n[:34],'*' if n in used else '') for s,ja,n in sc[:3]))
