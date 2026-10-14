import pickle,bisect,collections
us_list,usz=pickle.load(open('us_main.pkl','rb'))
jp_list=pickle.load(open('jp_main.pkl','rb'))
jaddr=collections.defaultdict(list)
for a,s,n in jp_list: jaddr[n].append(a)
USED=set(n for a,n in us_list if not(n.startswith('FUN_') or n.startswith('thunk')))
anch=[]
for a,n in us_list:
    if n.startswith('FUN_') or n.startswith('thunk'): continue
    js=jaddr.get(n)
    if js and len(js)==1: anch.append((a,js[0]))
# LIS on jp addr
import bisect
seq=[j for u,j in anch]
tails=[];idx=[];prev=[-1]*len(seq)
for i,v in enumerate(seq):
    k=bisect.bisect_left(tails,v)
    if k==len(tails): tails.append(v);idx.append(i)
    else: tails[k]=v;idx[k]=i
    prev[i]=idx[k-1] if k>0 else -1
lis=[];i=idx[-1]
while i!=-1: lis.append(anch[i]);i=prev[i]
lis.reverse()
print('anchors',len(anch),'monotone',len(lis))
pickle.dump(lis,open('anchors.pkl','wb'))
# gaps
umap={}
uidx=[a for a,n in us_list]
gaps=[]
for k in range(len(lis)+1):
    ul=lis[k-1][0] if k>0 else 0; uh=lis[k][0] if k<len(lis) else 1<<32
    jl=lis[k-1][1] if k>0 else 0; jh=lis[k][1] if k<len(lis) else 1<<32
    U=[(a,n) for a,n in us_list if ul<a<uh and (n.startswith('FUN_') or n.startswith('thunk'))]
    if not U: continue
    J=[(a,s,n) for a,s,n in jp_list if jl<a<jh and n not in USED]
    gaps.append((ul,uh,jl,jh,U,J))
print('gaps with unnamed',len(gaps),'US unnamed',sum(len(g[4]) for g in gaps),'JP in gaps',sum(len(g[5]) for g in gaps))
pickle.dump(gaps,open('gaps.pkl','wb'))
# distribution
c=collections.Counter()
for g in gaps:
    nu=len(g[4]);nj=len(g[5])
    c['u>0,j=0' if nj==0 else ('j>0' )]+=nu
print(c)
big=sorted(gaps,key=lambda g:-len(g[4]))[:15]
for g in big: print('us %x-%x jp %x-%x  U%d J%d'%(g[0],g[1],g[2],g[3],len(g[4]),len(g[5])))
