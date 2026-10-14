# retail-new Fp classes spec -> names
# class entries: name -> dict(role->addr)
SIG={'ct':'FiPv','dt':'Fv','SetPacket':'Fv','Init':'Fib','CalculateFunc':'Fv','CreateFpData':'FP7_FpDatai','CreateFpDataInit':'FP7_FpDatai','InitSetData':'Fv',
     'pct':'Fv','pdt':'Fv','Create':'FPv','CreateObjects':'Fv','DelayDelete':'Fv','SetAlphaPower':'FfUi'}
def mk(cls,meth,sig=None):
    m={'ct':'__ct','dt':'__dt','pct':'__ct','pdt':'__dt'}.get(meth,meth)
    s=sig if sig is not None else SIG.get(meth,'Fv')
    return '%s__%d%s%s'%(m,len(cls),cls,s)
S=[]   # (addr, cls, meth, sig, note)
def add(cls,**kw):
    for meth,v in kw.items():
        if isinstance(v,str): v=[v]
        for a in v:
            sig=None
            if ':' in a: a,sig=a.split(':')
            S.append((int(a,16),cls,meth,sig))
def sub(cls,addrs):
    for a in addrs.split():
        S.append((int(a,16),cls,'Sub%s'%a,'Fv'))
# --- Taki3 (derived from FpObjectTaki)
add('FpObjectRetailTaki3',ct='2c84e0',dt='2c8530',InitSetData='2c85b0',CreateFpDataInit='2c8d00',CreateFpData='2c8ff0',CalculateFunc='2c91b0')
# --- Rain 206
add('FpRetailRain206',pct='2c9460',pdt='2c9500',DelayDelete='2c9590',Create='2c9fa0',CreateObjects='2c99b0')
add('FpObjectRetailRain206',ct='2c9ff0',dt='2ca1f0',SetPacket='2cb270',Init='2caa00',CalculateFunc='2cabc0',CreateFpData='2ca760',CreateFpDataInit='2ca430')
sub('FpObjectRetailRain206','2c96e0 2c9890 2c9920 2ca270 2ca420')
add('FpObjectRetailRain206B',ct='2cb850',dt='2cb9f0',Init='2cf0f0',CalculateFunc='2cf160',CreateFpDataInit='2cee90')
sub('FpObjectRetailRain206B','2cba70 2cba90')
add('FpObjectRetailRain206C',ct='2cf5c0',dt='2cf660',Init='2cf6e0',CalculateFunc='2cf7c0')
# --- ScreenTint (aux)
add('FpRetailScreenTint',pct='2d9920',pdt='2d9970',Create='2d9a00:FiP7FVector')
add('FpObjectRetailScreenTint',ct='2d9b10',dt='2d9b60',Init='2d9be0',CalculateFunc='2d9dd0',SetPacket='2d9de0')
# --- Mote 207
add('FpRetailMote207',pct='2cfb00',pdt='2cfb50',Create='2d80d0',CreateObjects='2cfbe0:Fi')
add('FpObjectRetailMote207',ct='2d8120',dt='2d8210',Init='2d8ab0',CalculateFunc='2d8d20',SetPacket='2d9020',CreateFpData='2d8810',CreateFpDataInit='2d83a0')
S.append((0x2d8290,'FpObjectRetailMote207','SetData','F7FVector7FVector7FVectorib'))
# --- Drift 208
add('FpRetailDrift208',pct='2da3e0',pdt='2da440',Create='2dafc0',CreateObjects='2da4d0')
add('FpObjectRetailDrift208',ct='2db010',dt='2db1a0',Init='2dbb40',CalculateFunc='2dbd10',SetPacket='2dbef0',CreateFpData='2db5e0',CreateFpDataInit='2db220')
sub('FpObjectRetailDrift208','2db8f0 2dbb50')
add('FpObjectRetailDrift208B',ct='2dc410',dt='2dc590',Init='2dce50',CalculateFunc='2dd390',CreateFpData='2dc940',CreateFpDataInit='2dc610')
sub('FpObjectRetailDrift208B','2dd020')
# --- Lenz6
add('FpRetailLenz6',pct='2dd520',pdt='2dd580',Create='2dda70',CreateObjects='2dd8a0')
S.append((0x2dd610,'FpRetailLenz6','Sub2dd610','Fv'))
add('FpRetailLenz6B',pct='2ddb60',pdt='2ddbc0',Create='2ddc50:F7FVector')
add('FpObjectRetailLenz6',ct='2df930',dt='2df990',Init='2dff80',CalculateFunc='2dff90',SetPacket='2e02e0',CreateFpData='2dfce0',CreateFpDataInit='2dfa10')
sub('FpObjectRetailLenz6','2dfd00 2df440')
# --- Storm 209
add('FpRetailStorm209',pct='2e0830',pdt='2e0910',Create='2e3150',CreateObjects='2e17c0',DelayDelete='2e1070',SetAlphaPower='2e0d00')
sub('FpRetailStorm209','2e09a0 2e1570')
add('FpObjectRetailStorm209',ct='2e3230',dt='2e32d0',Init='2e3910',CalculateFunc='2e3920',SetPacket='2e5c70',CreateFpData='2e35d0',CreateFpDataInit='2e3350')
sub('FpObjectRetailStorm209','2e35f0')
add('FpObjectRetailStorm209B',ct='2e6190',dt='2e6240',Init='2e62c0',CalculateFunc='2e62d0')
# --- Trail base (mode 3 prim)
add('FpRetailTrail211M3',pct='2e67a0',pdt='2e68d0',Create='2e6c30',CreateObjects='2e6ae0',SetAlphaPower='2e6990')
sub('FpRetailTrail211M3','2e6960 2e69d0 2e75a0')
add('FpObjectRetailTrail',ct='2e6c80',dt='2e6e50',Init='2e7590',CalculateFunc='2e7840',SetPacket='2e8390',CreateFpData='2e73b0',CreateFpDataInit='2e70c0')
sub('FpObjectRetailTrail','2e6ed0 2e6f50 2e7020 2e73d0')
# trail 212 (child of 212 prim)
add('FpRetailTrail212',pct='2e89b0',pdt='2e8a70',Create='2e8c20',SetAlphaPower='2e8b30')
sub('FpRetailTrail212','2e8b00 2e8b70')
add('FpObjectRetailTrail212',ct='2e8d80',dt='2e8e40',CalculateFunc='2e8ec0')
# trail 211 mode 0
add('FpRetailTrail211M0',pct='2e96f0',pdt='2e9b40',Create='2e9e20',CreateObjects='2e9ca0',SetAlphaPower='2e9c00')
sub('FpRetailTrail211M0','2e9bd0 2e9c40')
add('FpObjectRetailTrail211M0',ct='2e9e60',dt='2e9f00',CalculateFunc='2ea1c0')
sub('FpObjectRetailTrail211M0','2e9f80')
# trail 211 mode 1
add('FpRetailTrail211M1',pct='2ea5d0',pdt='2eaa40',Create='2ead30',CreateObjects='2eaba0',SetAlphaPower='2eab00')
sub('FpRetailTrail211M1','2eaad0 2eab40')
add('FpObjectRetailTrail211M1',ct='2ead70',dt='2eae20',CalculateFunc='2eba00')
sub('FpObjectRetailTrail211M1','2eaea0 2eaf30')
# --- 212
add('FpRetail212',pct='2ebef0',pdt='2ebf90',Create='2eca10',CreateObjects='2ec670',DelayDelete='2ec020',SetAlphaPower='2ec100')
sub('FpRetail212','2ec0a0 2ec170 2ec1e0 2ed170')
add('FpObjectRetail212',ct='2ecb60',dt='2ecbb0',SetPacket='2ed790',Init='2ed4c0',CalculateFunc='2ed4d0',CreateFpData='2ecf90',CreateFpDataInit='2ecc30')
sub('FpObjectRetail212','2ed220')
# --- 213
add('FpRetail213',pct='2edce0',pdt='2eddd0',Create='2f00b0',CreateObjects='2ef520',DelayDelete='2ede60',SetAlphaPower='2edf40')
sub('FpRetail213','2edee0 2edfb0 2ee160 2ee440 2ee500 2f1a20 2f1aa0 2f0aa0 2f2960 2f29e0 2f2a60')
add('FpObjectRetail213A',ct='2f04b0',dt='2f0530',SetPacket='2f1130',Init='2f0d70',CalculateFunc='2f0d80',CreateFpData='2f0910',CreateFpDataInit='2f05b0')
sub('FpObjectRetail213A','2f0ac0')
add('FpObjectRetail213B',ct='2f1660',dt='2f16b0',SetPacket='2f1d40',Init='2f1d00',CalculateFunc='2f1d10',CreateFpDataInit='2f1730')
sub('FpObjectRetail213B','2f1ad0')
add('FpObjectRetailTrail213',ct='2f2270',dt='2f23b0',CalculateFunc='2f2ae0')
sub('FpObjectRetailTrail213','2f2430')
PRIMVT={0x43a0a0:'FpRetailRain206',0x43a160:'FpRetailMote207',0x43a210:'FpRetailScreenTint',0x43a330:'FpRetailDrift208',0x43a3f0:'FpRetailLenz6B',0x43a450:'FpRetailLenz6',0x43a560:'FpRetailStorm209',0x43a620:'FpRetailTrail211M1',0x43a6e0:'FpRetailTrail211M0',0x43a7a0:'FpRetailTrail212',0x43a860:'FpRetailTrail211M3',0x43a920:'FpRetail212',0x43aaa0:'FpRetail213'}
PSLOT={11:('SetAlphaPower','FfUi'),12:('SetDrawFlag','Fb'),13:('SetColor1','FUcUcUcUc'),14:('SetColor2','FUcUcUcUc'),15:('SetColor3','FUcUcUcUc'),16:('SetPos1','F7FVectorb'),17:('CreateStart','Ff')}
def vt_override():
    import img
    nm=dict(img.load_names('fn_SLUS_210.41.txt'))
    ov={}
    for v,c in PRIMVT.items():
        for i,(m,sg) in PSLOT.items():
            w=img.US.u32(v+8+i*4)
            if nm.get(w,'').startswith('FUN_') and 0x2c84e0<=w<0x2f3000: ov[w]=(c,m,sg)
    return ov
OV=vt_override()
S[:]=[x for x in S if x[0] not in OV]
for a,(c,m,sg) in OV.items(): S.append((a,c,m,sg))
if __name__=='__main__':
    import img
    names=dict(img.load_names('fn_SLUS_210.41.txt'))
    seen={}
    out=[]
    for a,cls,meth,sig in S:
        n=mk(cls,meth,sig)
        if a in seen: print('DUP addr',hex(a),n,seen[a])
        seen[a]=n
        out.append((a,n))
    # coverage
    un=[a for a,n in names.items() if n.startswith('FUN_') and 0x2c84e0<=a<0x2f3000]
    print('unnamed in region',len(un),'covered',len([a for a in un if a in seen]),'missing',[hex(a) for a in un if a not in seen])
    with open('apply_fp.txt','w') as f:
        for a,n in out: f.write('SLUS_210.41 %08x %s FPSPEC class-structure\n'%(a,n))
    print(len(out))
