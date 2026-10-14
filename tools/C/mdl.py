import struct,re
import numpy as np
from ex2 import kind,SZ,align
D="/Users/jamietheanything/Documents/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)/"
class Atom: pass
def load(m):
    r={}
    h=struct.unpack_from('<8s10I',m,0)
    r['hdr']=h
    fb10=m[10]
    fo=h[3]
    nf=struct.unpack_from('<H',m,fo+4)[0]
    fr=[]
    for i in range(nf):
        b=m[fo+0x10+i*0x40:fo+0x10+(i+1)*0x40]
        name=b[:12].split(b'\0')[0].decode('latin1')
        par,child,u,sib=b[12],b[13],b[14],b[15]
        t=struct.unpack_from('<4f',b,0x20); q=struct.unpack_from('<4f',b,0x30)
        fr.append(dict(name=name,parent=par,child=child,u=u,sib=sib,t=t,q=q,raw=b))
    r['frames']=fr
    sec=h[2]; cnt=struct.unpack_from('<H',m,sec+4)[0]
    p=sec+0x10; at=[]
    for i in range(cnt):
        a=Atom()
        a.off=p
        a.name=m[p:p+12].split(b'\0')[0].decode('latin1')
        a.n=struct.unpack_from('<I',m,p+0xc)[0]
        a.flags16=struct.unpack_from('<H',m,p+0x10)[0]
        a.b12,a.b13,a.b14,a.b15,a.b16,a.b17=m[p+0x12:p+0x18]
        a.ref=struct.unpack_from('<h',m,p+0x18)[0]
        a.ntri=struct.unpack_from('<H',m,p+0x1a)[0]
        a.hdr=m[p:p+0x30]
        a.kind=kind(fb10,a.b14,a.b15)
        q=p+0x30
        a.arrays=[]
        for s in SZ[a.kind]:
            a.arrays.append((q,s)); q=align(q+a.n*s)
        c=struct.unpack_from('<I',m,q)[0]
        a.chunks=[struct.unpack_from('<4B3I',m,q+0x10+j*16) for j in range(c)]
        a.chunk_raw=[m[q+0x10+j*16:q+0x20+j*16] for j in range(c)]
        p=q+0x10+0x10*c
        at.append(a)
    r['atomics']=at
    r['atend']=p
    return r
def tri_list(a,m):
    """return list of (i,j,k) vertex index triangles from strips; vertex w with ADC bit"""
    q,s=a.arrays[0]
    tris=[]
    for ch in a.chunks:
        start,cnt=ch[5],ch[6]
        for i in range(start,start+cnt):
            if a.kind=='pack1':
                w=struct.unpack_from('<h',m,q+i*8+6)[0]; adc=(w&-32768)!=0 if False else (struct.unpack_from('<H',m,q+i*8+6)[0]&0x8000)!=0
            else:
                w=struct.unpack_from('<I',m,q+i*16+12)[0]; adc=(w&0x8000)!=0
            if i-start>=2 and not adc:
                if ((i-start)&1): tris.append((i-2,i,i-1))
                else: tris.append((i-2,i-1,i))
    return tris
