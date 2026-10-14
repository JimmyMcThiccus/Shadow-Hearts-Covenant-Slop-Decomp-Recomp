import re,collections
import feat2,match
from match import *
ALLNUM=re.compile(r'(?<![\w.])(0x[0-9a-fA-F]+|-?\d+\.\d+(?:e[-+]?\d+)?f?|\d+)(?![\w.])')
_cache={}
def allnums(txt):
    # numbers in body, excluding param_/local var names handled by lookbehind
    i=txt.find('{'); body=txt[i:]
    c=collections.Counter()
    for m in ALLNUM.finditer(body):
        v=feat2.parse_int(m.group(1))
        if v is None: continue
        c[v]+=1
    return c
def metrics(P,j,u,S_row=None,S_col=None):
    jf=P.jf[j];uf=P.uf[u]
    jc=filt(P.jcallees(j)); uca=P.ucallees(u); unk=sum(1 for c in uca if c=='UNK'); uc=filt([c for c in uca if c!='UNK'])
    d,inter=dice(jc,uc)
    shared=len((set(jc)&set(uc)))
    cj=set(jf['consts']);cu=set(uf['consts'])
    cjac=len(cj&cu)/len(cj|cu) if (cj|cu) else None
    aj=allnums(jf['txt']);au=allnums(uf['txt'])
    sj=set(aj)|set(); su=set(au)
    ajac=len(sj&su)/len(sj|su) if (sj|su) else None
    # multiset equality ignoring tiny differences
    inter_ms=sum((aj&au).values()); tot=sum(aj.values())+sum(au.values())
    adice=2*inter_ms/tot if tot else None
    lcsr=(lcs(jc,uc)/max(len(jc),len(uc))) if (jc and uc and max(len(jc),len(uc))<=900) else None
    inter_c=sum((collections.Counter(jc)&collections.Counter(uc)).values()); prec=(inter_c/len(uc)) if uc else None
    m=dict(inter=inter_c,prec=prec,lcsr=lcsr,nall=sum(aj.values()),dice=d,shared=shared,nj=len(jc),nu=len(uc),unk=unk,cjac=cjac,nshared_c=len(cj&cu),ncj=len(cj),ncu=len(cu),ajac=ajac,adice=adice,
           cases_eq=(jf['cases']==uf['cases'] and len(jf['cases'])>=2),ncases=len(jf['cases']),
           ratio=usz[u]/jsz[j] if jsz[j] else 0,usize=usz[u],jsize=jsz[j],
           vj=jf['vcalls'],vu=uf['vcalls'])
    return m
def margins(P,pairs,S):
    # S is the full score matrix indexed by (J list, U list); compute best competing score per row/col
    pass
def tier(m,s):
    """return 'A','B' or None"""
    if s<0.7: return None
    info=0
    if m['shared']>=1: info+=1
    if m['nshared_c']>=3: info+=1
    if m['cases_eq']: info+=1
    if m['shared']>=3: info+=1
    if m['nshared_c']>=8: info+=1
    # contradictions
    if m['nj']>=2 and m['nu']>=2 and m['dice'] is not None and m['dice']<0.7: return None
    if m['ncj']>=3 and m['ncu']>=3 and m['cjac'] is not None and m['cjac']<0.5: return None
    small=min(m['usize'],m['jsize'])<0x120
    if small and m['adice'] is not None and m['adice']<0.85: return None
    if info>=2 and s>=0.8: return 'A'
    if info>=1 and s>=0.75: return 'B'
    if small and info==0 and m['adice'] is not None and m['adice']>=0.95 and s>=0.8: return 'C'
    return None

def margin_info(P,pairs,J,U,S):
    """per pair: margin vs best competitor in row/col, and gap balance (unmatched JP vs US counts)."""
    ji={a:i for i,a in enumerate(J)}; ui={a:i for i,a in enumerate(U)}
    nm_j=len(J)-len(pairs); nm_u=len(U)-len(pairs)
    out={}
    for j,u,s in pairs:
        row=sorted(S[ji[j]],reverse=True)  # competitors of j among U
        col=sorted((S[i][ui[u]] for i in range(len(J))),reverse=True)
        sec=max(row[1] if len(row)>1 else 0, col[1] if len(col)>1 else 0)
        out[(j,u)]=dict(margin=s-sec,balanced=(nm_j==nm_u),nm_j=nm_j,nm_u=nm_u,glen=len(J))
    return out
def tier2(m,s,mi):
    t=tier(m,s)
    if t is None:
        # D: callee-strong although constants/size disagree (retail retuning)
        if s>=0.7 and m['shared']>=3 and m['dice'] is not None and m['dice']>=0.8 and m['nj']>=3 and m['nu']>=3:
            t='D'
        elif (m['nj']>=12 and m['nu']>=12 and m['shared']>=8 and 0.5<=m['ratio']<=2.0 and
              ((m['lcsr'] is not None and m['lcsr']>=0.8) or (m['dice'] is not None and m['dice']>=0.9))) or \
             (m['nj']>=12 and m['inter']>=12 and m['prec'] is not None and m['prec']>=0.8 and 0.5<=m['ratio']<=2.0 and s>=0.45):
            t='F'   # large function: ordered callee sequence / multiset agree on a dozen+ calls
        else:
            return None
    if mi['margin']<0.03 and not (mi['balanced'] and mi['glen']<=40): return None
    if min(m['usize'],m['jsize'])<0x50 and m['nshared_c']==0 and not mi['balanced']: return None
    return t
