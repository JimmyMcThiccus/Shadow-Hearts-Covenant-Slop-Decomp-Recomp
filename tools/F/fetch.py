#!/usr/bin/env python3
"""Fetch raw Ghidra decompilation for section-F functions via the local GhidraMCP HTTP server."""
import re, sys, os, json, urllib.request, urllib.parse, concurrent.futures as cf
ROOT = "/Users/jamietheanything/Documents/Sh2 Decomp/sh2-decomp"
RAW = sys.argv[1]
MINE = set("""Menu MenuObj MenuScene MenuWindow MenuWindowPlain MenuWindowFrame MenuWindowFace MenuWindowCompact MenuWindowMessage MenuWindowGeneral MenuWindowNote MenuWindowObject MenuGroup MenuItem MenuText MenuFont MenuFontItalic MenuSprite MenuPolygon MenuModel MenuModelPack MenuModelManeger MenuEffectModel MenuTexture MenuFrame MenuFlare MenuCapture MenuPacket MenuRegister MenuRender MenuSound MenuMessage MenuDataTable MenuObjTable MenuPlace MenuElement Cursor ScrollMark PluralFontItem SaveData SaveDataSection SaveDevice SaveDeviceMC SaveDeviceHDD SaveMenuSection BtlSaveSec CFieldSaveData SystemFile dataAccess deviceChecker openingMessage openingBattleDemo GameOver GameOverScene GameOverSelect GameOverRealize ComboTrial dispTime dispCash dispSaveFile MenuBar MenuCommon MenuIcon MenuFieldData MenuFieldStationed MenuModelPrim SendOnLocal KeyWait FontItem Font""".split())
ranges=[]
for l in open(ROOT+"/symbols/SLPM_602.19_module_map.txt"):
    m=re.match(r'([0-9a-f]{8})-([0-9a-f]{8})\s+(\d+)\s+(\S+)\s',l)
    if m and m.group(4) in MINE:
        ranges.append((int(m.group(1),16),int(m.group(2),16),m.group(4)))
funcs=[]
for l in open(ROOT+"/symbols/SLPM_602.19.syms"):
    p=l.split()
    if len(p)>=6 and p[2]=="FUNC" and p[4]=="main":
        a=int(p[0],16)
        for lo,hi,c in ranges:
            if lo<=a<hi:
                funcs.append((a,int(p[1],16),p[5],c)); break
# extras: any func whose mangled name contains my class tokens
tok=["__%d%s"%(len(c),c) for c in MINE]
seen={f[0] for f in funcs}
for l in open(ROOT+"/symbols/SLPM_602.19.syms"):
    p=l.split()
    if len(p)>=6 and p[2]=="FUNC" and p[4]=="main":
        a=int(p[0],16)
        if a in seen: continue
        n=p[5]
        for t in tok:
            if re.search(t+r"(F|C|$)",n):
                funcs.append((a,int(p[1],16),n,t[2+len(str(len(t)-2)):] if False else "?")); seen.add(a); break
funcs.sort()
json.dump(funcs,open(RAW+"/_index.json","w"))
print(len(funcs),"functions")
def get(f):
    a,sz,n,c=f
    out=f"{RAW}/{a:08x}.c"
    if os.path.exists(out) and os.path.getsize(out)>0: return 0
    u="http://127.0.0.1:8089/decompile_function?address=%08x&program=SLPM_602.19"%a
    try:
        t=urllib.request.urlopen(u,timeout=180).read().decode("utf8","replace")
    except Exception as e:
        t="// FETCH ERROR %s"%e
    open(out,"w").write(t); return 1
with cf.ThreadPoolExecutor(4) as ex:
    r=list(ex.map(get,funcs))
print("fetched",sum(r))
