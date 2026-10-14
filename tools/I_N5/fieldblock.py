import re,sys,img,collections,os
lo,hi=int(sys.argv[1],16),int(sys.argv[2],16)
tagp=sys.argv[3] if len(sys.argv)>3 else 'CmdRetail'
dec='dec/field'; fnl='fn_SH2US_FIELD.BIN.txt'
L=img.load_names(fnl); names=dict(L)
um=dict(img.load_names('fn_SLUS_210.41.txt')); um.update(names)
sizes={a:(L[i+1][0]-a) for i,(a,n) in enumerate(L[:-1])}
VT=re.compile(r'\(\s*\w+\s*\+\s*(0x[0-9a-f]+|\d+)\)\s*=\s*(?:&(?:DAT|PTR_[A-Za-z_0-9]*)_?|0x)(0*4[0-9a-f]{5})\b')
unn=[a for a,n in L if lo<=a<hi and n.startswith('FUN_')]
st={}
for a in unn:
    t=open('%s/%08x.c'%(dec,a)).read()
    v=[]
    for m in VT.finditer(t):
        va=int(m.group(2),16)
        if 0x42f000<=va<0x450000: v.append((int(m.group(1),0),va))
    if v: st[a]=tuple(sorted(set(v)))
cls=collections.defaultdict(list)
for a,v in st.items(): cls[v].append(a)
groups=sorted(((sorted(fs),v) for v,fs in cls.items()),key=lambda x:x[0][0])
cnt=collections.Counter(); out=[]; creates=[]
classof={}   # addr -> (cls)
firsts=[g[0][0] for g in groups]
def mk(cls,meth,sig): return '%s__%d%s%s'%(meth,len(cls),cls,sig)
plan=[]
for gi,(fs,v) in enumerate(groups):
    offs=[o for o,va in v]
    if offs==[8,0x18,0x24]: kind='Win'
    elif offs==[0x14,0x20]: kind='Sel'
    elif offs==[8]: kind='Page'
    else: kind='Misc'
    s1=img.US.u32(v[0][1]+8+4)
    if kind=='Page' and um.get(s1,'')=='DelayDelete__17DelayDeleteObjectFv': kind='Place'
    cnt[kind]+=1
    c='%s%s%02d'%(tagp,kind,cnt[kind])
    plan.append((c,kind,fs,v))
    nxt=groups[gi+1][0][0] if gi+1<len(groups) else hi
    # members: functions in unn between fs[0] and nxt
    mem=[a for a in unn if fs[0]<=a<nxt]
    names_for={}
    if len(fs)>=1: names_for[fs[0]]=('__ct','Fv')
    if len(fs)>=2: names_for[fs[1]]=('__dt','Fv')
    rest=[a for a in mem if a not in names_for]
    if kind=='Win':
        meths=[('CreateScene','Fv'),('UpdateScene','Fs')]
        for a,(m,sg) in zip(rest,meths): names_for[a]=(m,sg)
        # thunks
        for off,va in v[1:]:
            tw=img.US.u32(va+8)
            creates.append((tw,'@%d@__dt__%d%sFv'%(24 if off==0x18 else 36,len(c),c)))
    elif kind in ('Page','Place'):
        base=v[0][1]
        slotnames={3:'GetReady',5:'Run',11:'SafeDelayDelete',12:'Close',14:'ReadyScene',15:'DisposeScene',16:'BackGroundRun'}
        if kind=='Place': slotnames={}
        for i,m in slotnames.items():
            w=img.US.u32(base+8+i*4)
            if w in rest: names_for[w]=(m,'Fv')
        rest=[a for a in rest if a not in names_for]
    for a in mem:
        if a in names_for: m,sg=names_for[a]
        else: m,sg='Sub%x'%a,'Fv'
        out.append((a,mk(c,m,sg)))
# also dedupe
d={}
for a,n in out: d[a]=n
print(cnt,len(d),len(creates))
with open('apply_fieldblock.txt','w') as f:
    for a,n in sorted(d.items()): f.write('SH2US_FIELD.BIN %08x %s CLSBLOCK vt-class\n'%(a,n))
import pickle
pickle.dump(creates,open('fieldblock_thunks.pkl','wb'))
for c,kind,fs,v in plan[:40]: print(c,kind,' '.join('%x'%a for a in fs))
