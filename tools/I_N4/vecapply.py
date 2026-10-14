import pickle,re,json,struct,gh,urllib.request,sys
from match import *
def post(ep,prog,d):
    rq=urllib.request.Request('http://127.0.0.1:8089/%s?program=%s'%(ep,prog),json.dumps(d).encode(),{'Content-Type':'application/json'})
    return urllib.request.urlopen(rq,timeout=120).read().decode()
tbl,rows=pickle.load(open('vectbl.pkl','rb'))
d=json.loads(gh.get('read_memory',gh.JPM,address='003f89b0',length=269*12))
jw=struct.unpack('<%dI'%(269*3),bytes(d['data']))
ji={jw[3*k]:(jw[3*k+1],jw[3*k+2]) for k in range(269)}
def cur():
    t=gh.get('list_functions',gh.MAIN); usn={}
    for l in t.splitlines():
        m=re.match(r'(.*) at ([0-9a-f]+)$',l.strip())
        if m: usn[int(m.group(2),16)]=m.group(1)
    return usn
jn={a:nm for a,s,nm in jp_list}
# group prefix for US-only ids from neighbouring JP ids
def prefix(idv):
    best=None
    for k in sorted(ji):
        if k<=idv: best=k
    return jn[ji[best][0]].split('__')[0]
want={}
for idv,fn,cx in tbl:
    if idv in ji: want[fn]=jn[ji[idv][0]]
    else:
        pre=re.match(r'[a-z]+',prefix(idv)).group(0)
        want[fn]='%sRetail%d__FiiPPcPv'%(pre,idv)
usn=cur()
# create missing
for fn,nm in list(want.items()):
    if fn not in usn:
        print('create',hex(fn),nm,post('create_function','SLUS_210.41',{'address':'%08x'%fn,'name':nm})[:100])
usn=cur()
todo={fn:nm for fn,nm in want.items() if usn.get(fn)!=nm}
print('to rename',len(todo))
log=[]
for it in range(6):
    left={}
    for fn,nm in sorted(todo.items()):
        t=post('rename_function_by_address','SLUS_210.41',{'function_address':'%08x'%fn,'new_name':nm})
        if 'uccess' in t: log.append((fn,nm))
        else: left[fn]=(nm,t[:150])
    print('pass',it,'renamed so far',len(log),'left',len(left))
    todo={fn:v[0] for fn,v in left.items()}
    if not left: break
for fn,(nm,t) in left.items(): print('LEFT',hex(fn),nm,t)
pickle.dump((log,left),open('vecapplied.pkl','wb'))
