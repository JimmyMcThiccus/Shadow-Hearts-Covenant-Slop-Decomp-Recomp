import struct,re,pickle,collections
from match import *
us_t=open('us_text.bin','rb').read(); jp_t=open('jp_text.bin','rb').read()
def mask(w):
    op=w>>26
    if op in (2,3): return w&0xfc000000
    if op==0: return w
    return w&0xffff0000
def sig(buf,base,a,size):
    o=a-base
    b=buf[o:o+size]
    ws=list(struct.unpack('<%dI'%(len(b)//4),b[:len(b)//4*4]))
    while ws and ws[-1]==0: ws.pop()
    return tuple(mask(w) for w in ws)
t=open('us_now.txt').read()
rows=[]
for l in t.splitlines():
    m=re.match(r'(.*) at ([0-9a-f]+)$',l.strip())
    if m: rows.append((int(m.group(2),16),m.group(1)))
rows.sort()
usn={a:n for a,n in rows}
szs={a:(rows[i+1][0]-a) if i+1<len(rows) else 0 for i,(a,n) in enumerate(rows)}
jsig=collections.defaultdict(list)
for a,s,n in jp_list:
    if a<0x410000 and s>=8: jsig[sig(jp_t,0x200000,a,s)].append((a,n))
usig=collections.defaultdict(list)
for a,n in rows:
    if a<0x440000 and szs[a]>=8: usig[sig(us_t,0x200000,a,szs[a])].append((a,n))
pickle.dump((jsig,usig,usn,szs),open('sigs.pkl','wb'))
uniq=[]
amb=[]
for s,us_ in usig.items():
    if len(s)<3: continue
    js=jsig.get(s)
    if not js: continue
    un=[(a,n) for a,n in us_ if n.startswith('FUN_') or n.startswith('thunk')]
    if not un: continue
    if len(us_)==1 and len(js)==1: uniq.append((us_[0][0],js[0]))
    else: amb.append((us_,js))
print('unique byte-identical (masked) unnamed US -> JP:',len(uniq),' ambiguous groups',len(amb))
for u,(j,n) in uniq[:80]: print('%x %s'%(u,n),usn[u])
pickle.dump((uniq,amb),open('sigmatch.pkl','wb'))
