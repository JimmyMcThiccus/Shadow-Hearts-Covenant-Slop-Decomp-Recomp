import struct
F="/Users/jamietheanything/Documents/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)/SLPM_602.19"
d=open(F,'rb').read()
def phdrs():
    e_phoff=struct.unpack_from('<I',d,0x1c)[0]; n=struct.unpack_from('<H',d,0x2c)[0]
    r=[]
    for i in range(n):
        t,off,va,pa,fs,ms,fl,al=struct.unpack_from('<8I',d,e_phoff+i*32)
        r.append((t,off,va,fs,ms))
    return r
P=phdrs()
def rd(va,n):
    for t,off,v,fs,ms in P:
        if t==1 and v<=va<v+fs:
            return d[off+va-v:off+va-v+n]
    raise Exception('unmapped %x'%va)
if __name__=='__main__':
    print([(t,hex(o),hex(v),hex(f),hex(m)) for t,o,v,f,m in P])
    import sys
    a=int(sys.argv[1],16); n=int(sys.argv[2],16)
    b=rd(a,n)
    for i in range(0,n,16): print(hex(a+i),b[i:i+16].hex(' ',4))
