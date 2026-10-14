import struct,sys
from ex import *
from collections import Counter
def kind(fb10,b14,b15):
    t=(b15&0xf)>>1
    if t==7: return 'water'
    if t==6: return 'B'
    if (b14&0x80) or (b14&0xf)==0:
        if (b14&0xf)==0:
            return 'skin' if fb10&3 else None
        return 'skinNL'
    lo=b14&0xf
    if lo==1:
        if fb10&3==0: return None
        return 'pack2' if fb10&4 else 'pack1'
    if lo==2:
        if fb10&3==0: return None
        return 'plp2' if fb10&4 else 'plp1'
    return None
SZ={'B':(0x28,4),'water':(8,4,4),'pack1':(8,4,4),'pack2':(16,4,4),'skin':(16,4,8),'skinNL':(16,4,4),'plp1':(8,4,8),'plp2':(16,4,8)}
def walk(m):
    h=parse(m); fb10=m[10]
    sec=h[2]; cnt=struct.unpack_from('<HH',m,sec+4)[0]
    p=sec+0x10; out=[]
    for i in range(cnt):
        n=struct.unpack_from('<I',m,p+0xc)[0]
        b14,b15=m[p+0x14],m[p+0x15]
        k=kind(fb10,b14,b15)
        inl=struct.unpack_from('<h',m,p+0x18)[0]
        name=m[p:p+12].split(b'\0')[0]
        if k is None or inl!=-1:
            out.append((p,name,k,n,b14,b15,inl,'STOP')); return out,p
        q=p+0x30
        for s in SZ[k]:
            q=align(q+n*s)
        c=struct.unpack_from('<I',m,q)[0]
        out.append((p,name,k,n,b14,b15,c))
        p=q+0x10+0x10*c
    return out,p
if __name__=='__main__':
    for f in sys.argv[1:]:
        ok=bad=0
        kinds=Counter()
        for o,d in models(f):
            m=d[o:o+0x100000]
            try:
                out,end=walk(m)
            except Exception as e:
                bad+=1;continue
            h=parse(m)
            kinds.update(x[2] for x in out)
            nxt=[v for v in (h[5],h[7],h[8],h[9],h[10]) if v and v!=0xffffffff and v>h[2]]
            if out and out[-1][-1]!='STOP' and end==h[6] : ok+=1
            else:
                bad+=1
                if bad<4: print(f,hex(o),'bad',hex(end),[hex(x) for x in h[2:]],out[-2:])
        print(f,ok,bad,kinds)
