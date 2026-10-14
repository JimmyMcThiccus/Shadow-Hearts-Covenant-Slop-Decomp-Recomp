# tools/I_N6/lib.py -- helpers for naming pass N6 (talks to the GhidraMCP HTTP API on 127.0.0.1:8089).
import re,os,sys,collections,bisect,json,struct,urllib.request
sys.path.insert(0,os.path.dirname(os.path.abspath(__file__)))
import gh
HERE=os.path.dirname(os.path.abspath(__file__))
SC=os.environ.get('N6_CACHE','/private/tmp/claude-501/-Users-jamietheanything-Documents-Sh2-Decomp/358b01e4-f5fb-4974-8473-2253168698e1/scratchpad/n6')+'/'
os.makedirs(SC,exist_ok=True)
NAMES=HERE+'/names/'
LOG=HERE+'/applied_log.txt'
PAIR={'SLUS_210.41':'SLPM_602.19','SH2US_FIELD.BIN':'SH2JP_FIELD.BIN','SH2US_BATTLE.BIN':'SH2JP_BATTLE.BIN'}
MAINBOUND={'SLUS_210.41':1<<32,'SH2US_FIELD.BIN':0x45ea80,'SH2US_BATTLE.BIN':0x45ea80,'SLPM_602.19':1<<32,'SH2JP_FIELD.BIN':0x430a00,'SH2JP_BATTLE.BIN':0x430a00}
def isun(n): return n.startswith('FUN_') or n.startswith('thunk_FUN')
def fnlist(prog,refresh=False):
    p=SC+'fn_%s.txt'%prog
    if refresh or not os.path.exists(p):
        open(p,'w').write(gh.get('list_functions',prog))
    L=[]
    for l in open(p):
        m=re.match(r'(.*) at ([0-9a-f]+)$',l.strip())
        if m: L.append((int(m.group(2),16),m.group(1)))
    L.sort(); return L
def sizes(L): return {a:(L[i+1][0]-a if i+1<len(L) else 0x40) for i,(a,n) in enumerate(L)}
_names={}
def namemap(prog,refresh=False):
    if refresh or prog not in _names: _names[prog]=dict(fnlist(prog,refresh))
    return _names[prog]
def getdec(prog,a):
    d=SC+'dec/%s/'%prog; os.makedirs(d,exist_ok=True); p='%s%08x.c'%(d,a)
    if not os.path.exists(p) or os.path.getsize(p)<10:
        open(p,'w').write(gh.get('decompile_function',prog,address='%08x'%a,timeout=240))
    return open(p).read()
def subst(prog,t):
    main='SLPM_602.19' if prog in ('SLPM_602.19','SH2JP_FIELD.BIN','SH2JP_BATTLE.BIN') else 'SLUS_210.41'
    mm=namemap(main); me=namemap(prog)
    def f(m):
        a=int(m.group(2),16)
        n=me.get(a) if a>=MAINBOUND[prog] or prog==main else None
        if n is None: n=mm.get(a)
        if n is None: n=me.get(a)
        return n if n and not isun(n) else m.group(0)
    return re.sub(r'\b(func_0x|FUN_)([0-9a-f]{8})\b',f,t)
def brief(prog,a,nl=60,w=130):
    t=subst(prog,getdec(prog,a)); out=[re.sub(r'\s+',' ',t[:t.find('{')]).strip()]
    for l in t[t.find('{'):].splitlines():
        s=l.strip()
        if not s or s in('{','}') or s.startswith('/*'): continue
        if re.match(r'^(undefined\d?|int|uint|float|long|ulong|byte|short|ushort|char|bool|undefined8|code|uchar|ulonglong|float4)\s+\**[\w]+(\[\d+\])?;$',s): continue
        s=re.sub(r'\(\*\*\(code \*\*\)\(\*\(int \*\)\(([^)]*)\) \+ (0x[0-9a-f]+)\)\)','VCALL[\\2](\\1)',s)
        out.append('  '+s[:w])
    return out[:nl+1]
def jpost(ep,prog,body,timeout=120):
    rq=urllib.request.Request('http://127.0.0.1:8089/%s?program=%s'%(ep,prog),json.dumps(body).encode(),{'Content-Type':'application/json'})
    try: return urllib.request.urlopen(rq,timeout=timeout).read().decode()
    except Exception as e: return 'ERR %s %s'%(e,getattr(e,'read',lambda:b'')()[:200])
def rename(prog,a,new,tier='X',note='',force=False):
    cur=namemap(prog).get(a)
    if cur is not None and not (isun(cur) or force): return 'skip-already:'+cur
    r=jpost('rename_function_by_address',prog,{'function_address':'%08x'%a,'new_name':new})
    if 'uccess' in r:
        _names[prog][a]=new
        open(LOG,'a').write('%s %08x %s %s %s %s\n'%(prog,a,new,tier,cur,note)); return 'ok'
    return r[:120]
def create(prog,a,new,tier='X',note=''):
    r=jpost('create_function',prog,{'address':'%08x'%a,'name':new})
    if 'rror' not in r:
        namemap(prog)[a]=new; open(LOG,'a').write('%s %08x %s %s CREATED %s\n'%(prog,a,new,tier,note))
    return r[:150]
def apply_file(fn,dry=False):
    ok=0;bad=[]
    for pr in set(l.split()[0].lstrip('!') for l in open(fn) if l.strip() and not l.startswith('#')):
        fnlist(pr,True); _names.pop(pr,None)
    for l in open(fn):
        l=l.rstrip('\n')
        if not l.strip() or l.startswith('#'): continue
        head,_,note=l.partition(' | ')
        p=head.split(); force=p[0].startswith('!')
        prog=p[0].lstrip('!'); a=int(p[1],16); n=p[2]; tier=p[3] if len(p)>3 else 'X'
        cur=namemap(prog).get(a)
        if cur is None:
            if not dry: print('CREATE',prog,hex(a),n,create(prog,a,n,tier,note)[:50])
            continue
        if cur==n: continue
        if dry: print('DRY',prog,hex(a),cur,'->',n,'(force)' if force else ''); continue
        r=rename(prog,a,n,tier,note,force=force)
        if r!='ok': bad.append((prog,hex(a),n,r))
        else: ok+=1
    print('renamed',ok,'bad',bad)
def unnamed_list():
    out=[]
    for l in open('/Volumes/work/Sh2 Decomp/sh2-decomp/notes/I/us_unnamed_N5.txt'):
        if l.startswith('#') or not l.strip(): continue
        a=l.split(' | ')[0]; p=a.split(None,3)
        out.append(dict(prog=p[0],addr=int(p[1],16),size=int(p[2],16),cause=p[3].strip(),prev=(l.split(' | ')[1].strip() if ' | ' in l else '')))
    return out
def rdw(p,a,n):
    d=json.loads(gh.get('read_memory',p,address='%x'%a,length=n))
    if 'data' not in d: raise Exception(str(d)[:100])
    return struct.unpack('<%dI'%(n//4),bytes(d['data']))
