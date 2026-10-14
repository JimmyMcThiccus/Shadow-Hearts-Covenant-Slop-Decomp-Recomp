import struct,re
D="/Volumes/work/Sh2 Decomp/"
class ELF:
    def __init__(s,path):
        s.d=open(path,'rb').read()
        po=struct.unpack_from('<I',s.d,0x1c)[0]; n=struct.unpack_from('<H',s.d,0x2c)[0]
        s.P=[]
        for i in range(n):
            t,off,va,pa,fs,ms,fl,al=struct.unpack_from('<8I',s.d,po+i*32)
            if t==1: s.P.append((off,va,fs,ms))
    def rd(s,va,n):
        for off,v,fs,ms in s.P:
            if v<=va<v+fs: return s.d[off+va-v:off+va-v+n]
        return b'\0'*n
    def u32(s,va): return struct.unpack('<I',s.rd(va,4))[0]
    def f32(s,va): return struct.unpack('<f',s.rd(va,4))[0]
class Flat:
    def __init__(s,path,base,hdr=0):
        s.d=open(path,'rb').read(); s.base=base
    def rd(s,va,n):
        o=va-s.base
        if 0<=o<len(s.d): return s.d[o:o+n]
        return b'\0'*n
    def u32(s,va): return struct.unpack('<I',s.rd(va,4))[0]
    def f32(s,va): return struct.unpack('<f',s.rd(va,4))[0]
US=ELF(D+"Shadow Hearts - Covenant (USA) (Disc 1)-1/SLUS_210.41")
JP=ELF(D+"Shadow Hearts II (Japan) (Furokuban)/SLPM_602.19")
def load_names(fn):
    L=[]
    for l in open(fn):
        m=re.match(r'(\S+) at ([0-9a-f]+)$',l.strip())
        if m: L.append((int(m.group(2),16),m.group(1)))
    L.sort(); return L
if __name__=='__main__':
    import sys
    e=US
    a=int(sys.argv[1],16); n=int(sys.argv[2],16)
    b=e.rd(a,n)
    for i in range(0,n,16): print(hex(a+i),b[i:i+16].hex(' ',4))
