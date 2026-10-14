# usage: prep_ovl.py <tag> <usprog_listfile> <jpprog_listfile> <usdecdir> <jpdecdir> <outdir>
import re,sys,pickle,os,img
tag,usl,jpl,usd,jpd,out=sys.argv[1:7]
usm=dict((a,n) for a,n in img.load_names('fn_SLUS_210.41.txt'))
jpm=dict((a,n) for a,n in img.load_names('fn_SLPM_602.19.txt'))
def lst(fn):
    L=img.load_names(fn); return L
us=lst(usl); jp=lst(jpl)
def sizes(L):
    return [(a,(L[i+1][0]-a) if i+1<len(L) else 0x40,n) for i,(a,n) in enumerate(L)]
jps=sizes(jp)
usz={a:s for a,s,n in sizes(us)}
pickle.dump((us,usz),open(out+'/us_main.pkl','wb'))
pickle.dump(jps,open(out+'/jp_main.pkl','wb'))
# main names for GUSMAP
pickle.dump({a:n for a,n in usm.items() if not n.startswith('FUN_')},open(out+'/us_mainnames.pkl','wb'))
FN=re.compile(r'func_0x([0-9a-f]{8})')
def conv(src,dst,m,pref):
    os.makedirs(dst,exist_ok=True)
    n=0
    for f in os.listdir(src):
        t=open(os.path.join(src,f)).read()
        t2=FN.sub(lambda mm: m.get(int(mm.group(1),16),pref+mm.group(1)),t)
        open(os.path.join(dst,f),'w').write(t2); n+=1
    return n
print(conv(usd,out+'/usdec',usm,'FUN_'),conv(jpd,out+'/jpdec',jpm,'FUN_'))
