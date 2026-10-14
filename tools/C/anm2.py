import struct,math,sys
D="/Users/jamietheanything/Documents/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)/"
def al(x): return (x+15)&~15
def s3(b):
    x,y,z,w=struct.unpack('<4H',b)
    def sx(v): return v-65536 if v>=32768 else v
    big = w&0x8000
    out=[]
    for i,v in enumerate((x,y,z)):
        iv=(sx(v)<<5)|((w>>(5*i))&31)
        out.append(iv*(1.0 if big else 0.01))
    return out
def parse_anm(d,a):
    assert d[a:a+4]==b'SQHD'
    name=d[a+4:a+16].split(b'\0')[0]
    nframes,nseq,u14,fps,nev,u18,u1a=struct.unpack_from('<HHBBHHH',d,a+0x10)
    p=a+0x20; seqs=[]
    for i in range(nseq):
        nm=d[p:p+16].split(b'\0')[0]; r,t=struct.unpack_from('<HH',d,p+0x10)
        p+=0x20
        rt=struct.unpack_from('<%dH'%r,d,p); p=al(p+2*r)
        rk=[struct.unpack_from('<4h',d,p+8*j) for j in range(r)]; p=al(p+8*r)
        tt=struct.unpack_from('<%dH'%t,d,p); p=al(p+2*t)
        tk=[s3(d[p+8*j:p+8*j+8]) for j in range(t)]; p=al(p+8*t)
        seqs.append((nm,rt,rk,tt,tk))
    evs=[]
    for i in range(nev):
        nm=d[p:p+8].split(b'\0')[0]; cnt,idx,typ=struct.unpack_from('<HHB',d,p+8)
        grp=2 if (typ&0xf)==3 else 4
        n=((cnt+grp-1)//grp)*grp
        sz=n*8 if (typ&0xf) in (2,3) else n*4
        evs.append((nm,cnt,idx,typ,d[p+0x10:p+0x10+sz])); p+=0x10+sz
    return dict(name=name,nframes=nframes,fps=fps,u14=u14,u18=u18,u1a=u1a,seqs=seqs,events=evs,end=p)
if __name__=='__main__':
    d=open(D+'COMMON.PKB','rb').read()
    a=int(sys.argv[1],16)
    m=parse_anm(d,a)
    print({k:v for k,v in m.items() if k not in('seqs','events')}, hex(m['end']))
    for s in m['seqs'][:int(sys.argv[2])]:
        print(s[0],len(s[1]),s[1][:6],[tuple(round(c/4096,3) for c in k) for k in s[2][:3]],'len',[round(math.sqrt(sum((c/4096)**2 for c in k)),3) for k in s[2][:3]], s[3][:4],[tuple(round(c,2) for c in k) for k in s[4][:3]])
    for e in m['events'][:12]: print(e[:4],e[4][:16].hex(' ',4))
