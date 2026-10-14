import sys
from rend import *
from tex import textures,decode
def raster(r,m,out,W=700,H=700,sc=34,ox=350,oy=640,vflip=False,verts_override=None):
    tex=[np.array(decode(t,True)) for t in textures(m)] if r['hdr'][5] not in (0,0xffffffff) else []
    allv=np.concatenate([verts(a,m) for a in r['atomics'] if a.kind in('skin','pack1','pack2')])
    mn,mx=allv.min(0),allv.max(0); sc=0.9*min(W/(mx[0]-mn[0]+1e-6),H/(mx[1]-mn[1]+1e-6)); ox=W/2-(mn[0]+mx[0])/2*sc; oy=H/2-(mn[1]+mx[1])/2*sc
    print('bbox',mn,mx,'tex',[(t.shape) for t in tex])
    img=np.full((H,W,4),255,np.uint8); zb=np.full((H,W),1e9)
    for ai,a in enumerate(r['atomics']):
        if a.kind not in('skin','pack1','pack2'): continue
        v=verts(a,m) if verts_override is None else verts_override[ai]
        q,s=a.arrays[1]
        uv=np.array([struct.unpack_from('<2H',m,q+i*4) for i in range(a.n)],float)/4096.0
        T=tex[a.b12] if a.b12<len(tex) else None
        for (i,j,k) in tri_list(a,m):
            P=np.array([[ox+v[n][0]*sc, oy+v[n][1]*sc, v[n][2]] for n in (i,j,k)])
            x0,x1=int(max(0,P[:,0].min())),int(min(W-1,P[:,0].max())); y0,y1=int(max(0,P[:,1].min())),int(min(H-1,P[:,1].max()))
            if x1<x0 or y1<y0: continue
            xs,ys=np.meshgrid(np.arange(x0,x1+1),np.arange(y0,y1+1))
            d=(P[1,1]-P[2,1])*(P[0,0]-P[2,0])+(P[2,0]-P[1,0])*(P[0,1]-P[2,1])
            if abs(d)<1e-9: continue
            l0=((P[1,1]-P[2,1])*(xs-P[2,0])+(P[2,0]-P[1,0])*(ys-P[2,1]))/d
            l1=((P[2,1]-P[0,1])*(xs-P[2,0])+(P[0,0]-P[2,0])*(ys-P[2,1]))/d
            l2=1-l0-l1
            mask=(l0>=0)&(l1>=0)&(l2>=0)
            z=l0*P[0,2]+l1*P[1,2]+l2*P[2,2]
            mask&=z<zb[y0:y1+1,x0:x1+1]
            if not mask.any(): continue
            if T is not None:
                u=l0*uv[i][0]+l1*uv[j][0]+l2*uv[k][0]; vv=l0*uv[i][1]+l1*uv[j][1]+l2*uv[k][1]
                if vflip: vv=1-vv
                th,tw=T.shape[:2]
                px=T[(vv*th).astype(int)%th,(u*tw).astype(int)%tw]
            else:
                px=np.zeros(xs.shape+(4,),np.uint8); px[...]=(150,150,150,255)
            sub=img[y0:y1+1,x0:x1+1]; sub[mask]=px[mask]; zb[y0:y1+1,x0:x1+1][mask]=z[mask]
    Image.fromarray(img).save(out)
if __name__=='__main__':
    f=sys.argv[1]; off=int(sys.argv[2],16); d=open(D+f,'rb').read(); m=d[off:off+0x300000]
    raster(load(m),m,sys.argv[3])
