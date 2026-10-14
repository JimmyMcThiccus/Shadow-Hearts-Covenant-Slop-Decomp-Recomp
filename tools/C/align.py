import json,re,difflib,sys
R="/Users/jamietheanything/Documents/Sh2 Decomp/sh2-decomp/"
d=json.load(open("/Users/jamietheanything/.claude/projects/-Users-jamietheanything-Documents-Sh2-Decomp/358b01e4-f5fb-4974-8473-2253168698e1/tool-results/mcp-ghidra-list_functions-1791567617165.txt"))
us=[]
for l in d["result"].split("\n"):
    m=re.match(r"(\S+) at ([0-9a-f]+)",l)
    if m: us.append((int(m.group(2),16),m.group(1)))
us.sort()
# end of text: main text ends ~0x404914 in JP
jp=[]
for l in open(R+"symbols/SLPM_602.19.syms"):
    p=l.split()
    if len(p)<7: continue
    addr,size,typ,bind,sec,name=p[0],p[1],p[2],p[3],p[4],p[5]
    if typ=="FUNC" and sec=="main":
        jp.append((int(addr,16),int(size,16),name))
jp.sort()
# dedupe same address
seen={};j2=[]
for a,s,n in jp:
    if a in seen: continue
    seen[a]=1;j2.append((a,s,n))
jp=[x for x in j2 if x[0]<0x405000 and x[1]>0]
ush=[]
for i,(a,n) in enumerate(us):
    nxt=us[i+1][0] if i+1<len(us) else a+0x100
    ush.append((a,nxt-a,n))
ush=[x for x in ush if x[0]<0x420000]
print(len(jp),len(ush))
sj=[x[1] for x in jp]; su=[x[1] for x in ush]
sm=difflib.SequenceMatcher(None,sj,su,autojunk=False)
mp={}
for blk in sm.get_matching_blocks():
    for k in range(blk.size):
        mp[jp[blk.a+k][0]]=ush[blk.b+k][0]
print("mapped",len(mp))
json.dump({hex(k):hex(v) for k,v in mp.items()},open("map_all.json","w"))
for a in (0x222fe0,0x225db0,0x2228c0,0x2472e0,0x3c6b10,0x399da0,0x26c7c0,0x3d8770):
    print(hex(a),hex(mp.get(a,0)))
