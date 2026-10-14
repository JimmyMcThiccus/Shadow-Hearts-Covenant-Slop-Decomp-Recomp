import re,os,collections,pickle
KW={'if','while','for','switch','return','sizeof','do','else','case','goto','code','undefined','undefined1','undefined2','undefined4','undefined8','int','uint','long','ulong','char','byte','float','short','ushort','void','bool','double','uchar','ulonglong','longlong','float4','float10','pointer'}
CALL=re.compile(r'(?<![\w.>])([A-Za-z_@][\w@]*)\s*\(')
NUM=re.compile(r'(?<![\w.])(0x[0-9a-fA-F]+|-?\d+\.\d+(?:e[-+]?\d+)?f?|\d+)(?![\w.])')
OFF=re.compile(r'\+\s*(0x[0-9a-fA-F]+|\d+)\)')
CASE=re.compile(r'\bcase\s+(0x[0-9a-fA-F]+|-?\d+)\s*:')
VCALL=re.compile(r'\(\*\*\(code \*\*\)\(\*\(int \*\)\([^;]*?\+\s*(0x[0-9a-fA-F]+|\d+)\)\s*\+\s*(0x[0-9a-fA-F]+|\d+)\)\)\(')
GLOB=re.compile(r'\b(?:[a-z]?Ram|DAT_|PTR_[A-Za-z_]*|LAB_)_?([0-9a-fA-F]{8})\b')
STR=re.compile(r'"([^"]{3,})"')
def parse_int(t):
    try:
        if t.startswith('0x'): return int(t,16)
        if '.' in t or 'e' in t.lower(): return float(t.rstrip('f'))
        return int(t)
    except: return None
def feats(txt):
    body=txt
    # drop header (first lines until '{')
    i=body.find('{')
    hdr=body[:i] if i>=0 else ''
    body=body[i:] if i>=0 else body
    calls=[]
    for m in CALL.finditer(body):
        n=m.group(1)
        if n in KW: continue
        calls.append(n)
    vc=[ 'V'+m.group(2) for m in VCALL.finditer(body)]
    consts=collections.Counter()
    for m in NUM.finditer(body):
        v=parse_int(m.group(1))
        if v is None: continue
        if isinstance(v,int) and -16<=v<=16: continue
        if isinstance(v,float) and v in (0.0,1.0,-1.0): continue
        consts[v]+=1
    offs=collections.Counter(parse_int(m.group(1)) for m in OFF.finditer(body))
    cases=sorted(parse_int(m.group(1)) for m in CASE.finditer(body))
    strs=STR.findall(body)
    nif=len(re.findall(r'\bif\b',body)); nloop=len(re.findall(r'\b(?:while|for|do)\b',body)); nsw=len(re.findall(r'\bswitch\b',body))
    glob=collections.Counter(m.group(1).lower() for m in GLOB.finditer(body))
    return dict(calls=calls,vcalls=vc,consts=consts,offs=offs,cases=cases,strs=strs,nif=nif,nloop=nloop,nsw=nsw,glob=glob,lines=body.count('\n'),nparam=hdr.count('param') if False else len(re.findall(r'\bparam_\d+',hdr)))
def load(d,addrs):
    out={}
    for a in addrs:
        p='%s/%08x.c'%(d,a)
        if not os.path.exists(p): continue
        t=open(p).read()
        f=feats(t); f['addr']=a; f['txt']=t
        out[a]=f
    return out
