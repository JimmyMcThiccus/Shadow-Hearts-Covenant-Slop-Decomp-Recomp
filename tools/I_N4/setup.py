import re,pickle,json
us=[]
for l in open('us_now.txt'):
    m=re.match(r'(.*) at ([0-9a-f]+)$',l.strip())
    if m: us.append((int(m.group(2),16),m.group(1)))
us.sort()
jp=pickle.load(open('jp_main.pkl','rb'))
# sizes for US from next function start
usz={}
for i,(a,n) in enumerate(us):
    usz[a]=(us[i+1][0]-a) if i+1<len(us) else 0
pickle.dump((us,usz),open('us_main.pkl','wb'))
# packages: name -> (us_lo,us_hi, jp_lo,jp_hi)
PK={
 'JRing':(0x2c8ff0,0x2f2ae0+0x100, 0x2bf6f0,0x2d6c80),
 'JRingN':(0x30b4f0,0x30ba40+0x100, 0x2d5990,0x2d6c80),
 'BtlResult':(0x38d2f0,0x3b11f0+0x100, 0x34c490,0x371870),
 'Sdrv':(0x3b2180,0x3b8f30+0x100, 0x372330,0x37b130),
 'HNMSnd':(0x386680,0x38a900+0x700, 0x345e70,0x34a200),
 'prim':(0x3d58d0,0x3e3b20+0x100, 0x391c10,0x3abe10),
 'CSe':(0x3f93b0,0x3fe550+0x100, 0x3c28e0,0x3c9a90),
 'fieldhelp':(0x3fee60,0x4075a0+0x100, 0x3ca5f0,0x3d53f0),
 'MFD':(0x290920,0x293e60+0x100, 0x2913b0,0x291d00),
}
for k,(ul,uh,jl,jh) in PK.items():
    u=[(a,n) for a,n in us if ul<=a<uh]
    uu=[(a,n) for a,n in u if n.startswith('FUN_') or n.startswith('thunk')]
    j=[(a,s,n) for a,s,n in jp if jl<=a<jh]
    print(k,'us all',len(u),'unnamed',len(uu),'jp',len(j))
json.dump({k:v for k,v in PK.items()},open('pk.json','w'))
