# refresh US function list from Ghidra and rebuild us_main.pkl (usage: refresh.py <usprog>)
import sys,re,pickle,gh
prog=sys.argv[1]
t=gh.get('list_functions',prog)
open('us_now.txt','w').write(t)
us=[]
for l in t.splitlines():
    m=re.match(r'(.*) at ([0-9a-f]+)$',l.strip())
    if m: us.append((int(m.group(2),16),m.group(1)))
us.sort()
usz={}
for i,(a,n) in enumerate(us): usz[a]=(us[i+1][0]-a) if i+1<len(us) else 0x40
pickle.dump((us,usz),open('us_main.pkl','wb'))
print(len(us),sum(1 for a,n in us if n.startswith('FUN_')))
