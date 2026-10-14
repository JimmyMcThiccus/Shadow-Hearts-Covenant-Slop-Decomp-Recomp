import os,sys,struct,json
sys.path.insert(0,'.')
from mipsemu import *
out={}
for variant in (0,1,2,4,5):
    e=Emu(os.environ['SH2_US_DISC_DIR']+'/SLUS_210.41')
    objs=[]
    heap=[0x5000000]
    def vec(e,p): return [round(e.fl(p+4*k),4) for k in range(4)]
    def hook(e,tgt,pc):
        r=e.r
        if tgt==0x222f00:
            e.wb(r[4],e.rb(r[5],16)); r[2]=r[4]
        elif tgt==0x2d8120: objs.append({'ctor_arg':r[5]}); r[2]=r[4]
        elif tgt==0x3c56e0: heap[0]+=0x1000; r[2]=heap[0]
        elif tgt==0x2d8290:
            o=objs[-1]
            o.update(pos=vec(e,r[5]),a2=vec(e,r[6]),a3=vec(e,r[7]),count=s32(r[8]),flag=r[9]&0xff)
    run(e,0x2cfbe0,0,{4:0x4000000,5:variant},hook,3000000)
    out[variant]=objs
    print(variant,len(objs))
    for o in objs[:4]: print('  ',o)
json.dump(out,open('mote207.json','w'))
