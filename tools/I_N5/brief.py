import sys,re,img,os
prog=sys.argv[1]; dec=sys.argv[2]; fn=sys.argv[3]; lo=int(sys.argv[4],16); hi=int(sys.argv[5],16); smax=int(sys.argv[6],16); nl=int(sys.argv[7]); skip=int(sys.argv[8]) if len(sys.argv)>8 else 0
L=img.load_names(fn); sizes={a:(L[i+1][0]-a if i+1<len(L) else 0) for i,(a,n) in enumerate(L)}
cnt=0
for i,(a,n) in enumerate(L):
    if not(n.startswith('FUN_') and lo<=a<hi and sizes[a]<=smax): continue
    cnt+=1
    if cnt<=skip: continue
    p='%s/%08x.c'%(dec,a)
    if not os.path.exists(p): continue
    t=open(p).read()
    body=t[t.find('{')+1:]
    out=[]
    for l in body.splitlines():
        s=l.strip()
        if not s or re.match(r'(undefined\d?|int|uint|float|long|ulong|byte|short|ushort|char|bool|undefined8|code)\s+\**\w+(\[\d+\])?;',s) or s.startswith('/*') or s=='}' or s.startswith('}'): continue
        s=re.sub(r'\(\*\*\(code \*\*\)\(\*\(int \*\)\(([^)]*)\) \+ (0x[0-9a-f]+)\)\)','VCALL[\\2](\\1)',s)
        out.append(s[:105])
    hdr=re.sub(r'\s+',' ',t[:t.find('{')])[:90]
    print('## %x(%x) prev=%s | %s'%(a,sizes[a],L[i-1][1][:22],hdr[:80]))
    for s in out[:nl]: print('   ',s)
    if cnt>=skip+40: print('...next skip',cnt); break
