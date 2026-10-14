import struct,sys
jp=open('overlays/SH2JP_BATTLE.BIN','rb').read(); us=open('overlays/SH2US_BATTLE.BIN','rb').read()
JPB,USB=0x430a00,0x45ea80
rows=[l.split() for l in open('notes/H/us_map.txt') if not l.startswith('#')]
rows=[(int(a,16),int(b,16),n,float(s)) for a,b,n,s in rows]
rows.sort()
def w(d,b,a): o=a-b; return struct.unpack_from('<I',d,o)[0]
def stats(d,b,a,nxt):
    n=(nxt-a)//4; ws=[w(d,b,a+4*i) for i in range(n)]
    jal=sum(1 for x in ws if x>>26==3); fl=sum(1 for x in ws if x>>26==0x11); mem=sum(1 for x in ws if x>>26 in (0x23,0x2b,0x37,0x3f))
    return n,jal,fl,mem
out=[]
for i,(j,u,n,s) in enumerate(rows):
    if s>=0.6: continue
    nj=rows[i+1][0] if i+1<len(rows) else j+0x400
    nu=rows[i+1][1] if i+1<len(rows) else u+0x400
    # use function end = next anchor (upper bound); compare sizes of gap
    a=stats(jp,JPB,j,nj); b=stats(us,USB,u,nu)
    r=b[0]/max(a[0],1)
    out.append((n,s,a,b,r))
    print(f'{n:45s} {s:.3f} jp(n,jal,fp)={a[:3]} us={b[:3]} ratio={r:.2f}')
