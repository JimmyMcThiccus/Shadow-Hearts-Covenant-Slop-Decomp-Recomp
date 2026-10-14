# functions whose class differs from both neighbours that agree with each other (sandwiched outliers) -> candidate mislabels
import sys,re; sys.path.insert(0,'.')
from lib import *
def cls(n):
    if n.startswith('@'): m=re.search(r'@\d+@\w+__(\d+)([A-Za-z_]\w*)',n)
    else: m=re.search(r'__(\d+)([A-Za-z_]\w*)',n)
    return m.group(2)[:int(m.group(1))] if m else None
for prog in ('SH2US_FIELD.BIN','SH2US_BATTLE.BIN','SLUS_210.41'):
    L=fnlist(prog,True); out=[]
    for i in range(2,len(L)-2):
        a,n=L[i]; c=cls(n); pc=cls(L[i-1][1]); nc=cls(L[i+1][1])
        if c and pc and nc and pc==nc and c!=pc and not n.startswith('__ct__') and not n.startswith('__dt__') and not n.startswith('Retail_') and not n.startswith('@'):
            out.append((hex(a),n[:46],pc))
    print(prog,len(out))
    for o in out: print('  ',o)
