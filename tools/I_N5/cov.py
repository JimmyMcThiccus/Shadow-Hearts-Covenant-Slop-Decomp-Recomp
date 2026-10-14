import img,collections
GROUPS_MAIN=[('SDK / libc / libkernl / crt0 (0x200000-0x240000)',0x200000,0x240000),
('Model / Atomic / Frame / Dynamics / CBBox / ClutRaster (0x240000-0x262000)',0x240000,0x262000),
('Menu toolkit: Menu*/Font*/Cursor/Window* (0x262000-0x290000)',0x262000,0x290000),
('Menu retail-new scenes + MenuEffectModel/MenuModelPrim (0x290000-0x294000)',0x290000,0x294000),
('CScript / CScriptEx (0x294000-0x298b60)',0x294000,0x298b60),
('Fp*/Puti* JP-named classes (0x298b60-0x2c84e0)',0x298b60,0x2c84e0),
('Fp*/Puti* retail-new classes (0x2c84e0-0x2f3550)',0x2c84e0,0x2f3550),
('JRing family (0x2f3550-0x331df0)',0x2f3550,0x331df0),
('Effect / EffectCore / VEC handlers / BgEffect (0x331df0-0x35f000)',0x331df0,0x35f000),
('SaveData / SaveDevice / CPath / BtlSocket / HNMSnd (0x35f000-0x38a000)',0x35f000,0x38a000),
('BtlBonus / BtlResult / BtlFader (0x38a000-0x3b2090)',0x38a000,0x3b2090),
('Sdrv / SdrvEE / SifCmd (0x3b2090-0x3b9000)',0x3b2090,0x3b9000),
('BtlSaveSec / AnimServer / LSDPlayer handlers (0x3b9000-0x3d5800)',0x3b9000,0x3d5800),
('dataAccess / prim* / disp* / deviceChecker (0x3d5800-0x3e5000)',0x3d5800,0x3e5000),
('BtlIn / BtlInBoss / CFieldSocket / CSe / CMusic / BgEffectMan (0x3e5000-0x3fee60)',0x3e5000,0x3fee60),
('Field-side helpers: CPauser/CLSDPauser/CScrCapture/GenericData/EventHandler/LSDScrEx/StreamBGM (0x3fee60-0x4075a0)',0x3fee60,0x4075a0),
('CBBPolygon / CBGBat / M524 / sinit / kernel-patch tail (0x4075a0-0x440000)',0x4075a0,0x440000)]
def load(p):
    return img.load_names('fn_%s.txt'%p)
def base(fn):
    return set(int(l.split()[0],16) for l in open(fn) if l.strip())
out=[]
progs=[('SLUS_210.41',base('unn_main.txt')),('SH2US_FIELD.BIN',base('unn_field.txt')),('SH2US_BATTLE.BIN',base('unn_battle.txt')),('SH2US_OPENING.BIN',set())]
tot={}
for p,b in progs:
    L=load(p); un=[a for a,n in L if n.startswith('FUN_')]
    tot[p]=(len(L),len(L)-len(un),len(un),len(b))
print(tot)
L=load('SLUS_210.41'); b=base('unn_main.txt')
rows=[]
for name,lo,hi in GROUPS_MAIN:
    allf=[a for a,n in L if lo<=a<hi]; un=[a for a,n in L if lo<=a<hi and n.startswith('FUN_')]
    b0=len([a for a in b if lo<=a<hi])
    rows.append((name,len(allf),len(allf)-len(un),len(un),b0))
    print('%-110s total %4d named %4d unnamed %4d (start of pass %4d)'%rows[-1])
import json
json.dump({'tot':tot,'rows':rows},open('cov.json','w'))
