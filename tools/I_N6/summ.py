# usage: summ.py <usprog> lo hi -- one line per unnamed function: size, neighbour classes, callee names
import sys,re
sys.path.insert(0,'.')
from lib import *
us=sys.argv[1]; lo=int(sys.argv[2],16); hi=int(sys.argv[3],16)
LU=fnlist(us,True); SU=sizes(LU)
KW={'if','while','for','switch','return','sizeof','else','case','goto','code','undefined','int','uint','long','ulong','char','byte','float','short','ushort','void','bool'}
def cls(n):
    m=re.search(r'__(\d+)([A-Za-z_]\w*)',n)
    return m.group(2)[:int(m.group(1))] if m else None
for i,(a,n) in enumerate(LU):
    if not isun(n) or not(lo<=a<hi): continue
    j=i-1
    while j>0 and (isun(LU[j][1]) or not cls(LU[j][1])): j-=1
    k=i+1
    while k<len(LU)-1 and (isun(LU[k][1]) or not cls(LU[k][1])): k+=1
    k=min(k,len(LU)-1)
    t=subst(us,getdec(us,a)); body=t[t.find('{'):]
    calls=[c for c in dict.fromkeys(re.findall(r'(?<![\w.>])([A-Za-z_@][\w@]*)\s*\(',body)) if c not in KW and not c.startswith('_v') and not c.startswith('_lq') and not c.startswith('_sq') and not c.startswith('CONCAT')]
    print('%08x(%x) [%s|%s] ln=%d: %s'%(a,SU[a],cls(LU[j][1]) or '',cls(LU[k][1]) or '',body.count('\n'),', '.join(c[:30] for c in calls[:7])))
