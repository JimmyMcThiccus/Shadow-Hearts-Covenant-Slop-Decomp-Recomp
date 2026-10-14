import struct,re,sys,glob
D="/Users/jamietheanything/Documents/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)/"
def models(f):
    d=open(D+f,'rb').read()
    for m in re.finditer(b'SSH1\\.01a',d):
        yield m.start(), d
def align(x): return (x+15)&~15
def parse(m):
    h=struct.unpack_from('<8s10I',m,0)
    ver=h[1]
    return h
def atomics(m):
    h=parse(m)
    sec=h[2]; # atomics
    cnt=struct.unpack_from('<HH',m,sec+4)
    p=sec+0x10
    res=[]
    for i in range(cnt[0]):
        hd=m[p:p+0x30]
        name=hd[:12].split(b'\0')[0]
        n=struct.unpack_from('<I',hd,0xc)[0]
        t=hd[0x14]&0xf; fl14=hd[0x14]; fl15=hd[0x15]
        inl=struct.unpack_from('<h',hd,0x18)[0]
        res.append((p,name,n,fl14,fl15,inl,hd.hex(' ',4)))
        # compute size
        break
    return cnt,res
if __name__=='__main__':
    f=sys.argv[1]
    k=0
    for o,d in models(f):
        m=d[o:o+0x400000]
        print(hex(o),parse(m)[1:], atomics(m)[0])
        k+=1
        if k>8:break
