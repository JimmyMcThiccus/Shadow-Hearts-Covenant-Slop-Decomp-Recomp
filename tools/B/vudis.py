# VU1 microprogram disassembler (EE ELF + DMA packet address): python3 tools/B/vudis.py SLPM_602.19 3EA560   (_dma_228); 3E94A0 = _dma_202 (skin)
# Written 2026-10-09 for the shadow microcode; encodings follow the VU user manual tables, validated on _dma_61/_dma_202.
import struct,sys
sys.path.insert(0,'/Volumes/work/Sh2 Decomp/sh2-decomp/tools/C')
DST='xyzw'
def dest(d): return ''.join(DST[i] for i in range(4) if d&(8>>i)) or ''
def fld(n): return 'xyzw'[n]
UP={0x18:'MULx',0x19:'MULy',0x1A:'MULz',0x1B:'MULw',0x1C:'MULq',0x1D:'MAXi',0x1E:'MULi',0x1F:'MINIi',
0x20:'ADDq',0x21:'MADDq',0x22:'ADDi',0x23:'MADDi',0x24:'SUBq',0x25:'MSUBq',0x26:'SUBi',0x27:'MSUBi',
0x28:'ADD',0x29:'MADD',0x2A:'MUL',0x2B:'MAX',0x2C:'SUB',0x2D:'MSUB',0x2E:'OPMSUB',0x2F:'MINI'}
for i,b in enumerate('xyzw'):
    UP[i]='ADD'+b; UP[4+i]='SUB'+b; UP[8+i]='MADD'+b; UP[12+i]='MSUB'+b; UP[0x10+i]='MAX'+b; UP[0x14+i]='MINI'+b
FD={0:['ADDAx','ADDAy','ADDAz','ADDAw'],1:['SUBAx','SUBAy','SUBAz','SUBAw'],2:['MADDAx','MADDAy','MADDAz','MADDAw'],3:['MSUBAx','MSUBAy','MSUBAz','MSUBAw'],
4:['ITOF0','ITOF4','ITOF12','ITOF15'],5:['FTOI0','FTOI4','FTOI12','FTOI15'],6:['MULAx','MULAy','MULAz','MULAw'],
7:['MULAq','ABS','MULAi','CLIP'],8:['ADDAq','MADDAq','ADDAi','MADDAi'],9:['SUBAq','MSUBAq','SUBAi','MSUBAi'],
0xA:['ADDA','MADDA','MULA','NOP'],0xB:['SUBA','MSUBA','OPMULA','']}
def up(w):
    I=(w>>31)&1;E=(w>>30)&1;M=(w>>29)&1;D=(w>>28)&1;T=(w>>27)&1
    d=(w>>21)&15; ft=(w>>16)&31; fs=(w>>11)&31; fdd=(w>>6)&31; op=w&63
    flags=('[E]' if E else '')+('[M]' if M else '')+('[D]' if D else '')+('[T]' if T else '')
    ds=dest(d)
    if op>=0x3c:
        idx=((w>>6)&31)
        nm=FD.get(idx,['?']*4)[op&3]
        if nm=='NOP' or nm=='': return 'NOP'+flags
        if nm=='CLIP': return 'CLIPw.xyz vf%d xyz, vf%d w'%(fs,ft)+flags
        if nm=='ABS': return 'ABS.%s vf%d, vf%d'%(ds,ft,fs)+flags
        if nm.startswith('ITOF') or nm.startswith('FTOI'): return '%s.%s vf%d, vf%d'%(nm,ds,ft,fs)+flags
        if nm.endswith('q') or nm.endswith('i'):
            return '%s.%s ACC, vf%d, %s'%(nm[:-1] if False else nm,ds,fs,nm[-1].upper())+flags
        if nm[-1] in 'xyzw' and nm not in('ABS',) and nm!='': 
            return '%s.%s ACC, vf%d, vf%d%s'%(nm[:-1],ds,fs,ft,nm[-1])+flags
        return '%s.%s ACC, vf%d, vf%d'%(nm,ds,fs,ft)+flags
    nm=UP.get(op,'?%02x'%op)
    if nm in ('OPMSUB',): return 'OPMSUB.%s vf%d, vf%d, vf%d'%(ds,fdd,fs,ft)+flags
    if nm.endswith('q') and nm[:-1] in('MUL','ADD','MADD','SUB','MSUB') or nm[-1]=='i' and nm[:-1] in('ADD','MADD','SUB','MSUB','MUL','MAX','MINI') or (nm=='MULq'):
        return '%s.%s vf%d, vf%d, %s'%(nm[:-1],ds,fdd,fs,nm[-1])+flags
    if nm[-1] in 'xyzw' and nm[:-1] in ('ADD','SUB','MADD','MSUB','MAX','MINI','MUL'):
        return '%s.%s vf%d, vf%d, vf%d%s'%(nm[:-1],ds,fdd,fs,ft,nm[-1])+flags
    return '%s.%s vf%d, vf%d, vf%d'%(nm,ds,fdd,fs,ft)+flags
def low(w,pc):
    op=(w>>25)&0x7f
    d=(w>>21)&15; ft=(w>>16)&31; fs=(w>>11)&31; imm11=w&0x7ff
    s=lambda v,b:(v-(1<<b)) if v&(1<<(b-1)) else v
    ds=dest(d)
    if op==0x00: return 'LQ.%s vf%d, %d(vi%d)'%(ds,ft,s(imm11,11),fs)
    if op==0x01: return 'SQ.%s vf%d, %d(vi%d)'%(ds,fs,s(imm11,11),ft)
    if op==0x04: return 'ILW.%s vi%d, %d(vi%d)'%(ds,ft,s(imm11,11),fs)
    if op==0x05: return 'ISW.%s vi%d, %d(vi%d)'%(ds,ft,s(imm11,11),fs)
    if op==0x08: return 'IADDIU vi%d, vi%d, %d'%(ft,fs,((w>>10)&0x7800)|imm11)
    if op==0x09: return 'ISUBIU vi%d, vi%d, %d'%(ft,fs,((w>>10)&0x7800)|imm11)
    if op==0x10: return 'FCEQ vi1, 0x%x'%(w&0xffffff)
    if op==0x11: return 'FCSET 0x%x'%(w&0xffffff)
    if op==0x12: return 'FCAND vi1, 0x%x'%(w&0xffffff)
    if op==0x13: return 'FCOR vi1, 0x%x'%(w&0xffffff)
    if op==0x14: return 'FSEQ vi%d, 0x%x'%(ft,((w>>10)&0x800)|imm11)
    if op==0x15: return 'FSSET 0x%x'%(((w>>10)&0x800)|imm11)
    if op==0x16: return 'FSAND vi%d, 0x%x'%(ft,((w>>10)&0x800)|imm11)
    if op==0x17: return 'FSOR vi%d, 0x%x'%(ft,((w>>10)&0x800)|imm11)
    if op==0x18: return 'FMEQ vi%d, vi%d'%(ft,fs)
    if op==0x1A: return 'FMAND vi%d, vi%d'%(ft,fs)
    if op==0x1B: return 'FMOR vi%d, vi%d'%(ft,fs)
    if op==0x1C: return 'FCGET vi%d'%ft
    if op in(0x20,0x21,0x28,0x29,0x2c,0x2d,0x2e,0x2f):
        off=s(imm11,11); tgt=pc+1+off
        nm={0x20:'B',0x21:'BAL',0x28:'IBEQ',0x29:'IBNE',0x2c:'IBLTZ',0x2d:'IBGTZ',0x2e:'IBLEZ',0x2f:'IBGEZ'}[op]
        if op==0x20: return 'B  ->%d'%tgt
        if op==0x21: return 'BAL vi%d ->%d'%(ft,tgt)
        if op in(0x28,0x29): return '%s vi%d, vi%d ->%d'%(nm,ft,fs,tgt)
        return '%s vi%d ->%d'%(nm,fs,tgt)
    if op==0x24: return 'JR vi%d'%fs
    if op==0x25: return 'JALR vi%d, vi%d'%(ft,fs)
    if op==0x40:
        f=w&63
        fd=(w>>6)&31
        if f==0x30: return 'IADD vi%d, vi%d, vi%d'%(fd,fs,ft)
        if f==0x31: return 'ISUB vi%d, vi%d, vi%d'%(fd,fs,ft)
        if f==0x32: return 'IADDI vi%d, vi%d, %d'%(ft,fs,s(fd,5))
        if f==0x34: return 'IAND vi%d, vi%d, vi%d'%(fd,fs,ft)
        if f==0x35: return 'IOR vi%d, vi%d, vi%d'%(fd,fs,ft)
        if f==0x38: return 'CALLMS 0x%x'%((w>>6)&0x7fff)
        if f==0x39: return 'CALLMSR'
        if f>=0x3c:
            lo=f&3; key=(fd,lo)
            fsf=(w>>21)&3; ftf=(w>>23)&3
            T={(0xC,0):'MOVE.%s vf%d, vf%d'%(ds,ft,fs),(0xC,1):'MR32.%s vf%d, vf%d'%(ds,ft,fs),
            (0xD,0):'LQI.%s vf%d, (vi%d++)'%(ds,ft,fs),(0xD,1):'SQI.%s vf%d, (vi%d++)'%(ds,fs,ft),
            (0xD,2):'LQD.%s vf%d, (--vi%d)'%(ds,ft,fs),(0xD,3):'SQD.%s vf%d, (--vi%d)'%(ds,fs,ft),
            (0xE,0):'DIV Q, vf%d%s, vf%d%s'%(fs,fld(fsf),ft,fld(ftf)),(0xE,1):'SQRT Q, vf%d%s'%(ft,fld(ftf)),
            (0xE,2):'RSQRT Q, vf%d%s, vf%d%s'%(fs,fld(fsf),ft,fld(ftf)),(0xE,3):'WAITQ',
            (0xF,0):'MTIR vi%d, vf%d%s'%(ft,fs,fld(fsf)),(0xF,1):'MFIR.%s vf%d, vi%d'%(ds,ft,fs),
            (0xF,2):'ILWR.%s vi%d, (vi%d)'%(ds,ft,fs),(0xF,3):'ISWR.%s vi%d, (vi%d)'%(ds,ft,fs),
            (0x10,0):'RNEXT.%s vf%d, R'%(ds,ft),(0x10,1):'RGET.%s vf%d, R'%(ds,ft),(0x10,2):'RINIT R, vf%d%s'%(fs,fld(fsf)),(0x10,3):'RXOR R, vf%d%s'%(fs,fld(fsf)),
            (0x19,0):'MFP.%s vf%d, P'%(ds,ft),(0x1A,0):'XTOP vi%d'%ft,(0x1A,1):'XITOP vi%d'%ft,(0x1B,0):'XGKICK vi%d'%fs,
            (0x1C,0):'ESADD P, vf%d'%fs,(0x1C,1):'ERSADD P, vf%d'%fs,(0x1C,2):'ELENG P, vf%d'%fs,(0x1C,3):'ERLENG P, vf%d'%fs,
            (0x1D,0):'EATANxy P, vf%d'%fs,(0x1D,1):'EATANxz P, vf%d'%fs,(0x1D,2):'ESUM P, vf%d'%fs,
            (0x1E,0):'ESQRT P, vf%d%s'%(fs,fld(fsf)),(0x1E,1):'ERSQRT P, vf%d%s'%(fs,fld(fsf)),(0x1E,2):'ERCPR P, vf%d%s'%(fs,fld(fsf)),
            (0x1F,0):'ESIN P, vf%d%s'%(fs,fld(fsf)),(0x1F,1):'EATAN P, vf%d%s'%(fs,fld(fsf)),(0x1F,2):'EEXP P, vf%d%s'%(fs,fld(fsf)),
            (0x1B,3):'WAITP',}
            if key==(0xC,0) and w&0x7ff==0x33c and False: pass
            return T.get(key,'LOW? f=%02x fd=%02x'%(f,fd))
        return 'LOW? op40 f=%02x'%f
    return 'LOW? %02x'%op
def disasm(prog,start=0,end=None):
    out=[]
    pcs=sorted(prog)
    for pc in pcs:
        lo,upw=prog[pc]
        u=up(upw)
        I=(upw>>31)&1
        l=('LOI %g'%struct.unpack('<f',struct.pack('<I',lo))[0]) if I else low(lo,pc)
        out.append('%4d: %-52s | %s'%(pc,u,l))
    return out
if __name__=='__main__':
    path=sys.argv[1]; addr=int(sys.argv[2],16)
    f=open(path,'rb').read()
    phoff=struct.unpack_from('<I',f,0x1c)[0]; phentsize,phnum=struct.unpack_from('<HH',f,0x2a)
    def rd(a,n):
        for i in range(phnum):
            t,off,va,pa,fsz,msz,fl,al=struct.unpack_from('<IIIIIIII',f,phoff+i*phentsize)
            if t==1 and va<=a<va+fsz: return f[off+a-va:off+a-va+n]
    b=rd(addr,16)
    tag=struct.unpack_from('<Q',b,0)[0]; qwc=tag&0xffff
    b=rd(addr,16+qwc*16)
    off=8;prog={}
    while off<8+qwc*16:
        w=struct.unpack_from('<I',b,off)[0]; cmd=(w>>24)&0x7f; num=(w>>16)&0xff; imm=w&0xffff
        off+=4
        if cmd==0x4a:
            n=num or 256
            for i in range(n):
                lo,upw=struct.unpack_from('<II',b,off+i*8); prog[imm+i]=(lo,upw)
            print('; MPG at',imm,'n',n)
            off+=n*8
        elif off>=8+qwc*16: break
        elif cmd not in (0,0x11,0x13,0x14,0x15,0x17): print('; vif',hex(w),'at',off)
    print('\n'.join(disasm(prog)))
