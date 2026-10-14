import struct,sys
from elf import rd
a=int(sys.argv[1],16)
b=rd(a,0x154*16+0x20)
# first 8 bytes DMA tag, then vif codes
tag=struct.unpack_from('<Q',b,0)[0]; qwc=tag&0xffff
print('qwc',hex(qwc))
# walk vif codes from offset 8
off=8; mpg_addr=0
prog={}
while off<8+qwc*16:
    w=struct.unpack_from('<I',b,off)[0]; cmd=(w>>24)&0x7f; num=(w>>16)&0xff; imm=w&0xffff
    off+=4
    if cmd==0x4a:
        n=num or 256
        for i in range(n):
            lo,up=struct.unpack_from('<II',b,off+i*8)
            prog[imm+i]=(lo,up)
        print('MPG at',hex(imm),'n',n)
        off+=n*8
    elif cmd==0 or cmd in(0x11,0x13,0x14,0x15,0x17):
        pass
    else:
        print('vif',hex(w),hex(off)); 
import pickle; pickle.dump(prog,open('prog_%s.pkl'%sys.argv[1],'wb'))
names={4:'ITOF0',5:'FTOI0'}
for pc,(lo,up) in sorted(prog.items()):
    op=up&0x3f
    if op>=0x3c:
        sel=(up>>6)&0x1f
        if sel in(4,5):
            print(pc,'ITOF' if sel==4 else 'FTOI',[0,4,12,15][op-0x3c],hex(up))
