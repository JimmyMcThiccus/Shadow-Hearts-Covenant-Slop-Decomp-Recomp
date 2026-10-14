import pickle,struct,json,urllib.request,sys
from match import *
jsig,usig,usn,szs=pickle.load(open('sigs.pkl','rb'))
uniq,amb=pickle.load(open('sigmatch.pkl','rb'))
us_t=open('us_text.bin','rb').read(); jp_t=open('jp_text.bin','rb').read()
jn_by_addr={a:n for a,s,n in jp_list}
def jals(buf,a,size):
    o=a-0x200000; b=buf[o:o+size]; out=[]
    for i in range(0,len(b)//4*4,4):
        w=struct.unpack('<I',b[i:i+4])[0]
        if w>>26==3: out.append(((w&0x3ffffff)<<2))
    return out
def check(u,j):
    uc=[usn.get(t) for t in jals(us_t,u,szs[u])]; jc=[jn_by_addr.get(t) for t in jals(jp_t,j,jsz[j])]
    bad=0;known=0
    for x,y in zip(uc,jc):
        if x and y and not x.startswith('FUN_') and not x.startswith('thunk'):
            known+=1
            if x!=y: bad+=1
    return bad,known,len(uc),len(jc)
res=[]
for u,(j,n) in uniq:
    if not(usn[u].startswith('FUN_') or usn[u].startswith('thunk')): continue
    bad,known,nu,nj=check(u,j)
    res.append((u,j,n,bad,known,nu,nj))
    print('%x -> %-40s jal US/JP %d/%d known %d mismatches %d'%(u,n[:40],nu,nj,known,bad))
pickle.dump(res,open('sigres.pkl','wb'))
