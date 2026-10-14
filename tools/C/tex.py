from mdl import *
from PIL import Image
def textures(m):
    h=struct.unpack_from('<10I',m,8); sec=h[4]
    n=struct.unpack_from('<H',m,sec+4)[0]; p=sec+0x10; out=[]
    for i in range(n):
        w,hh=struct.unpack_from('<HH',m,p+4); fmt=m[p+8]
        nclut,cofs=struct.unpack_from('<HH',m,p+0xc); dofs,mofs=struct.unpack_from('<II',m,p+0x10)
        pal=[tuple(m[p+cofs+4*j:p+cofs+4*j+4]) for j in range(nclut)]
        data=m[p+dofs:p+mofs]
        out.append(dict(w=w,h=hh,fmt=fmt,pal=pal,data=data,hdr=m[p:p+0x20]))
        p+=mofs
    return out
def decode(t,swz=True):
    w,h=t['w'],t['h']; pal=t['pal']; d=t['data']
    img=Image.new('RGBA',(w,h))
    px=img.load()
    for i in range(w*h):
        if t['fmt']==4:
            b=d[i>>1]; idx=(b>>4) if i&1 else (b&15)
        else:
            idx=d[i]
            if swz and t['fmt']==8: idx=(idx&0xe7)|((idx&8)<<1)|((idx&16)>>1)
        r,g,b_,a=pal[idx]
        px[i%w,i//w]=(r,g,b_,min(255,a*2))
    return img
if __name__=='__main__':
    d=open(D+'FIELD.PKB','rb').read()
    # find a model with T8 textures
    k=0
    for mt in re.finditer(b'SSH1\\.01a',d):
        m=d[mt.start():mt.start()+0x400000]
        h=struct.unpack_from('<10I',m,8)
        if h[4] in (0,0xffffffff): continue
        ts=textures(m)
        if any(t['fmt']==8 for t in ts):
            for i,t in enumerate(ts[:3]):
                print(i,t['w'],t['h'],t['fmt'],len(t['pal']),t['hdr'][0x18:].hex(' ',4))
                decode(t,True).save(f'tex{k}_{i}_swz.png'); decode(t,False).save(f'tex{k}_{i}_raw.png')
            k+=1
            if k>=1: break
