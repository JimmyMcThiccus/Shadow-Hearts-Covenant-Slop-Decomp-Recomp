import struct,os,sys
class Emu:
    def __init__(self,exe):
        d=open(exe,'rb').read(); self.d=d
        phoff=struct.unpack_from('<I',d,0x1c)[0]; phent,phnum=struct.unpack_from('<HH',d,0x2a)
        self.segs=[]
        for i in range(phnum):
            off,va,pa,fsz,msz=struct.unpack_from('<IIIII',d,phoff+i*phent+4)
            self.segs.append((va,off,fsz))
        self.mem={}   # byte-addressed overlay for stores
        self.r=[0]*32; self.f=[0]*32
        self.calls=[]
    def rb(self,va,n=1):
        out=bytearray()
        for k in range(n):
            a=va+k
            if a in self.mem: out.append(self.mem[a]); continue
            for v,o,f in self.segs:
                if v<=a<v+f: out.append(self.d[o+a-v]); break
            else: out.append(0)
        return bytes(out)
    def wb(self,va,b):
        for k,x in enumerate(b): self.mem[va+k]=x
    def r32(self,va): return struct.unpack('<I',self.rb(va,4))[0]
    def w32(self,va,v): self.wb(va,struct.pack('<I',v&0xffffffff))
    def fl(self,va): return struct.unpack('<f',self.rb(va,4))[0]
def s16(x): return x-0x10000 if x&0x8000 else x
def run(e,start,end,regs,callhook,maxsteps=2000000):
    pc=start; e.r[29]=0x7000000
    for k,v in regs.items(): e.r[k]=v
    steps=0; unk=set()
    def fetch(a): return e.r32(a)
    while steps<maxsteps and pc!=end:
        steps+=1
        w=fetch(pc); op=w>>26; rs=(w>>21)&31; rt=(w>>16)&31; rd=(w>>11)&31; sh=(w>>6)&31; fn=w&63; imm=w&0xffff; simm=s16(imm)
        npc=pc+4; delay=None; r=e.r
        def exec_delay(a):
            # execute one instruction (simple ones)
            step(a)
        def step(a):
            w=fetch(a); op=w>>26; rs=(w>>21)&31; rt=(w>>16)&31; rd=(w>>11)&31; sh=(w>>6)&31; fn=w&63; imm=w&0xffff; simm=s16(imm)
            if w==0: return
            if op==0x0f: r[rt]=(imm<<16)&0xffffffff
            elif op==0x0d: r[rt]=r[rs]|imm
            elif op in (0x09,0x08): r[rt]=(r[rs]+simm)&0xffffffff
            elif op==0x0c: r[rt]=r[rs]&imm
            elif op==0x0a: r[rt]=1 if (s32(r[rs])<simm) else 0
            elif op==0x0b: r[rt]=1 if r[rs]<(simm&0xffffffff) else 0
            elif op==0x23: r[rt]=e.r32((r[rs]+simm)&0xffffffff)
            elif op==0x2b: e.w32((r[rs]+simm)&0xffffffff,r[rt])
            elif op==0x31: e.f[rt]=e.r32((r[rs]+simm)&0xffffffff)
            elif op==0x39: e.w32((r[rs]+simm)&0xffffffff,e.f[rt])
            elif op==0x20: b=e.rb((r[rs]+simm)&0xffffffff,1)[0]; r[rt]=b-256 if b&128 else b; r[rt]&=0xffffffff
            elif op==0x24: r[rt]=e.rb((r[rs]+simm)&0xffffffff,1)[0]
            elif op==0x28: e.wb((r[rs]+simm)&0xffffffff,bytes([r[rt]&255]))
            elif op==0x21: v=struct.unpack('<h',e.rb((r[rs]+simm)&0xffffffff,2))[0]; r[rt]=v&0xffffffff
            elif op==0x25: r[rt]=struct.unpack('<H',e.rb((r[rs]+simm)&0xffffffff,2))[0]
            elif op==0x29: e.wb((r[rs]+simm)&0xffffffff,struct.pack('<H',r[rt]&0xffff))
            elif op==0x1e: # lq
                b=e.rb((r[rs]+simm)&0xffffffff,16); r[rt]=struct.unpack('<I',b[:4])[0]
                if not hasattr(e,'q128'): e.q128={}
                e.q128[rt]=(r[rt],b)
            elif op==0x1f: # sq
                if not hasattr(e,'q128'): e.q128={}
                q=e.q128.get(rt)
                b=q[1] if q and q[0]==r[rt] else struct.pack('<I',r[rt])+bytes(12)
                e.wb((r[rs]+simm)&0xffffffff,b)
            elif op==0x37: # ld
                b=e.rb((r[rs]+simm)&0xffffffff,8); r[rt]=struct.unpack('<I',b[:4])[0]; e.hi=getattr(e,'hi',{}); e.hi[rt]=struct.unpack('<I',b[4:])[0]
            elif op==0x3f: # sd
                e.hi=getattr(e,'hi',{}); e.wb((r[rs]+simm)&0xffffffff,struct.pack('<II',r[rt],e.hi.get(rt,0)))
            elif op==0x11 and rs==4: e.f[rd]=r[rt]       # mtc1
            elif op==0x11 and rs==0: r[rt]=e.f[rd]       # mfc1
            elif op==0x11 and rs==0x10:  # COP1.S
                a=struct.unpack('<f',struct.pack('<I',e.f[rd]))[0]; b=struct.unpack('<f',struct.pack('<I',e.f[rt]))[0]
                fd=sh; fs=rd; ft=rt
                A=struct.unpack('<f',struct.pack('<I',e.f[fs]))[0]; B=struct.unpack('<f',struct.pack('<I',e.f[ft]))[0]
                def put(x): e.f[fd]=struct.unpack('<I',struct.pack('<f',x))[0]
                if fn==0: put(A+B)
                elif fn==1: put(A-B)
                elif fn==2: put(A*B)
                elif fn==3: put(A/B if B else 0.0)
                elif fn==6: e.f[fd]=e.f[fs]
                elif fn==7: put(-A)
                elif fn==0x24: e.f[fd]=int(A)&0xffffffff
                elif fn==0x20: put(float(s32(e.f[fs])))
                else: unk.add(('cop1',fn))
            elif op==0 and fn==0x21: r[rd]=(r[rs]+r[rt])&0xffffffff
            elif op==0 and fn==0x25: r[rd]=r[rs]|r[rt]
            elif op==0 and fn==0x24: r[rd]=r[rs]&r[rt]
            elif op==0 and fn==0x23: r[rd]=(r[rs]-r[rt])&0xffffffff
            elif op==0 and fn==0x00: r[rd]=(r[rt]<<sh)&0xffffffff
            elif op==0 and fn==0x02: r[rd]=r[rt]>>sh
            elif op==0 and fn==0x03: r[rd]=(s32(r[rt])>>sh)&0xffffffff
            elif op==0 and fn==0x2a: r[rd]=1 if s32(r[rs])<s32(r[rt]) else 0
            elif op==0 and fn==0x2b: r[rd]=1 if r[rs]<r[rt] else 0
            elif op==0 and fn==0x2d: r[rd]=(r[rs]+r[rt])&0xffffffff
            elif op==0 and fn==0x25: r[rd]=r[rs]|r[rt]
            elif op==0 and fn==0x0a: r[rd]=r[rs] if r[rt]==0 else r[rd]   # movz
            elif op==0 and fn==0x0b: r[rd]=r[rs] if r[rt]!=0 else r[rd]
            elif op==0 and fn==0x18: e.lo=(s32(r[rs])*s32(r[rt]))&0xffffffff
            elif op==0 and fn==0x12: r[rd]=getattr(e,'lo',0)
            elif op==0x1c and fn==0x02: r[rd]=(s32(r[rs])*s32(r[rt]))&0xffffffff
            else: unk.add((hex(a),hex(w)))
            r[0]=0
        if op==3: # jal
            tgt=(w&0x3ffffff)<<2; exec_delay(pc+4); callhook(e,tgt,pc); pc+=8; continue
        if op==2:
            exec_delay(pc+4); pc=(w&0x3ffffff)<<2|(pc&0xf0000000); continue
        if op==0 and fn==8: # jr
            exec_delay(pc+4); 
            if rs==31: break
            pc=r[rs]; continue
        if op==0 and fn==9: exec_delay(pc+4); callhook(e,r[rs],pc); pc+=8; continue
        taken=None; likely=False
        if op in (4,0x14): taken=r[rs]==r[rt]; likely=op==0x14
        elif op in (5,0x15): taken=r[rs]!=r[rt]; likely=op==0x15
        elif op in (6,0x16): taken=s32(r[rs])<=0; likely=op==0x16
        elif op in (7,0x17): taken=s32(r[rs])>0; likely=op==0x17
        elif op==1:
            if rt in (0,2): taken=s32(r[rs])<0; likely=rt==2
            elif rt in (1,3): taken=s32(r[rs])>=0; likely=rt==3
        if taken is not None:
            if taken: exec_delay(pc+4); pc=pc+4+(simm<<2); 
            else:
                if likely: pc+=8
                else: exec_delay(pc+4); pc+=8
            continue
        step(pc); pc+=4
    return unk
def s32(x): return x-(1<<32) if x&0x80000000 else x
