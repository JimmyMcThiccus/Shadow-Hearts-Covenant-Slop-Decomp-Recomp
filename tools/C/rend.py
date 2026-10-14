import sys
from mdl import *
from PIL import Image,ImageDraw
def quat_mat(q):
    x,y,z,w=q
    return np.array([[1-2*(y*y+z*z),2*(x*y-z*w),2*(x*z+y*w)],
                     [2*(x*y+z*w),1-2*(x*x+z*z),2*(y*z-x*w)],
                     [2*(x*z-y*w),2*(y*z+x*w),1-2*(x*x+y*y)]])
def skel(fr,order):
    W=[None]*len(fr)
    for i,f in enumerate(fr):
        R=quat_mat(f['q']); t=np.array(f['t'][:3])
        L=np.eye(4); 
        if order=='TR':  # translate then rotate in parent: M = T*R
            L[:3,:3]=R; L[:3,3]=t
        else:  # R*T
            L[:3,:3]=R; L[:3,3]=R@t
        W[i]=(W[f['parent']] if f['parent']!=255 else np.eye(4))@L
    return W
def verts(a,m):
    q,s=a.arrays[0]
    if a.kind=='pack1':
        v=np.array([struct.unpack_from('<3h',m,q+i*8) for i in range(a.n)],float)/16.0
    else:
        v=np.array([struct.unpack_from('<3f',m,q+i*16) for i in range(a.n)],float)
    return v
if __name__=='__main__':
    f=sys.argv[1]; off=int(sys.argv[2],16); out=sys.argv[3]
    d=open(D+f,'rb').read()
    m=d[off:off+0x300000]
    r=load(m)
    fr=r['frames']
    print(len(fr),[ (x['name'],x['parent']) for x in fr][:40])
    allv=[]
    ntri=0
    for a in r['atomics']:
        v=verts(a,m); allv.append((a,v))
        t=tri_list(a,m); ntri+=len(t)
        print(a.name,a.kind,a.n,a.ntri,len(t),v.min(0).round(1),v.max(0).round(1))
    W=skel(fr,'TR')
    for i,x in enumerate(fr[:40]): print(i,x['name'],W[i][:3,3].round(1))
