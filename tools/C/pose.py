import sys
from trender import *
from anm2 import parse_anm
def bind(fr):
    B=[]
    for f in fr:
        R=quat_mat(f['q']); t=np.array(f['t'][:3])
        M=np.eye(4); M[:3,:3]=R; M[:3,3]=R@t; B.append(M)
    return B
def sample(seq,f,fps=30.0):
    nm,rt,rk,tt,tk=seq
    def seg(times,n):
        if n==1: return 0,0,0.0
        if f>=times[-1]: return n-1,n-1,0.0
        for i in range(n-1):
            if times[i]<=f<times[i+1]: return i,i+1,(f-times[i])/(times[i+1]-times[i])
        return 0,0,0.0
    i,j,u=seg(rt,len(rt))
    q0=np.array(rk[i])/4096.0; q1=np.array(rk[j])/4096.0
    if q0@q1<0: q1=-q1
    q=q0*(1-u)+q1*u; q/=np.linalg.norm(q)
    i,j,u=seg(tt,len(tt))
    t=np.array(tk[i])*(1-u)+np.array(tk[j])*u
    return q,t
def pose(fr,B,anm,f,mode):
    n=len(fr); S=[None]*n; W=[None]*n
    seqs={s[0].decode('latin1'):s for s in anm['seqs']}
    for i,fm in enumerate(fr):
        p=fm['parent']
        s=seqs.get(fm['name'])
        D=np.eye(4)
        if s is not None:
            q,t=sample(s,f)
            R=quat_mat(q)
            D[:3,:3]=R; D[:3,3]=t[:3]   # T*R
        Bp=B[p] if p!=255 else np.eye(4)
        Wp=W[p] if p!=255 else np.eye(4)
        if mode=='H1': W[i]=Wp@np.linalg.inv(Bp)@B[i]@D
        elif mode=='H3': W[i]=Wp@D@np.linalg.inv(Bp)@B[i]
        elif mode=='H4':  # D conjugated into model space: W = Wp * Binv_p*B_i; then rotate in model axes
            L=np.linalg.inv(Bp)@B[i]; W[i]=Wp@L@D
        if mode in('G1','G2','G3'):
            D2=np.eye(4)
            if s is not None:
                q,t=sample(s,f); R=quat_mat(q)
                if mode=='G1': D2[:3,:3]=R; D2[:3,3]=t[:3]
                elif mode=='G2': D2[:3,:3]=R; D2[:3,3]=R@t[:3]
                else: D2[:3,:3]=R; D2[:3,3]=0; 
            Sp=S[p] if p!=255 else np.eye(4)
            S[i]=Sp@np.linalg.inv(B[i])@D2@B[i]; W[i]=S[i]; continue
        S[i]=W[i]@np.linalg.inv(B[i])
    return S
def skinned_verts(r,m,S):
    outs=[]
    for a in r['atomics']:
        v=verts(a,m)
        if a.kind=='skin':
            q,_=a.arrays[0]; q2,_=a.arrays[2]
            res=np.zeros_like(v)
            # chunk -> bones
            for ch in a.chunks:
                bones=[ch[0],ch[1],ch[2]]
                for i in range(ch[5],ch[5]+ch[6]):
                    w=struct.unpack_from('<I',m,q+i*16+12)[0]
                    s0=w&0xff; wt=((w>>16)&0xff)/255.0; s1=(w>>24)&0xff
                    p=np.append(v[i],1.0)
                    pa=(S[bones[s0]]@p)[:3] if bones[s0]<len(S) else v[i]
                    pb=(S[bones[s1]]@p)[:3] if s1<3 and bones[s1]<len(S) else pa
                    res[i]=pa*(1-wt)+pb*wt
            outs.append(res)
        elif a.kind=='pack1':
            res=v.copy()
            q,_=a.arrays[0]
            for ch in a.chunks:
                b=ch[0]
                for i in range(ch[5],ch[5]+ch[6]):
                    res[i]=(S[b]@np.append(v[i],1.0))[:3] if b<len(S) else v[i]
            outs.append(res)
        else: outs.append(v)
    return outs
if __name__=='__main__':
    f=sys.argv[1]; off=int(sys.argv[2],16); ao=int(sys.argv[3],16); frame=float(sys.argv[4]); out=sys.argv[5]
    d=open(D+f,'rb').read(); m=d[off:off+0x300000]
    r=load(m); anm=parse_anm(d,ao); fr=r['frames']; B=bind(fr)
    print(len(fr),len(anm['seqs']),anm['nframes'])
    for mode in sys.argv[6:]:
        S=pose(fr,B,anm,frame,mode)
        vo=skinned_verts(r,m,S)
        raster(r,m,out.replace('.png',f'_{mode}.png'),verts_override=vo)
