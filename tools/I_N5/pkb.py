import struct,os,sys
D="/Volumes/work/Sh2 Decomp/Shadow Hearts - Covenant (USA) (Disc 1)-1/"
CH=".0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_"
def decode(b8):
    a,l0,l1,l2=struct.unpack('>HHHH',b8)
    ds=[a%40,a//40%40,a//1600%40]
    out=''
    for d,lo in zip(ds,(l0,l1,l2)):
        w=(d<<16)|lo
        for k in (w%40,w//40%40,w//1600%40,w//64000%40):
            if k: out+=CH[k-1]
    return out
tbl=open(D+'PKFINFO.TBL','rb').read()
body=tbl[0x10:]
def entries(off):
    # scan until end of table
    res=[]
    o=off
    while o+16<=len(body):
        nm=decode(body[o:o+8]); dofs=struct.unpack('<I',body[o+8:o+12])[0]; sz=struct.unpack('<I',body[o+12:o+16])[0]
        res.append((o,nm,dofs,sz)); o+=16
    return res
if __name__=='__main__':
    allr=entries(0)
    print(len(allr))
    for r in allr[:40]: print(r[0],r[1],hex(r[2]),hex(r[3]))

def build():
    # returns tree: dict path -> (data_abs_offset_units..., size) ; handle recursion
    allr=entries(0)
    # all dir child starts
    starts={}
    def walk(listbase,start,dataBase,prefix,end):
        o=start; out=[]
        dirs=[]
        while o<end:
            nm=decode(body[o:o+8]); dofs=struct.unpack('<I',body[o+8:o+12])[0]; sz=struct.unpack('<I',body[o+12:o+16])[0]
            out.append((o,nm,dofs,sz))
            o+=16
        return out
    return allr

class Tree: pass
def load_tree():
    # discover all lists
    lists={}   # start-> entries
    pend=[(0,'',0)]
    starts=set([0])
    # first discover starts via iterating: need ends; do two passes
    def parse(start,end):
        o=start;out=[]
        while o<end:
            nm=decode(body[o:o+8]); dofs,sz=struct.unpack('<II',body[o+8:o+16])
            out.append((o,nm,dofs,sz)); o+=16
        return out
    # pass 1: crude: assume list continues until a bogus name (empty) or end -> instead iterate dirs as discovered
    ends={}
    # root end
    root=[];o=0;mn=1<<31
    while o<mn:
        nm=decode(body[o:o+8]); dofs,sz=struct.unpack('<II',body[o+8:o+16]); root.append((o,nm,dofs,sz))
        if sz&0x80000000: mn=min(mn,sz&0x7fffffff)
        o+=16
    allstarts=set([0])
    queue=[(0,root)]
    # discover all dir child starts by walking with unknown ends: use heuristic that entries have non-empty names
    def scan(start,limit):
        out=[];o=start
        while o<limit and o+16<=len(body):
            nm=decode(body[o:o+8])
            if not nm: break
            dofs,sz=struct.unpack('<II',body[o+8:o+16]); out.append((o,nm,dofs,sz)); o+=16
        return out
    res={}
    def rec(path,listbase,start,database,limit):
        ents=scan(start,limit)
        sub=[]
        for o,nm,dofs,sz in ents:
            p=path+'/'+nm
            if sz&0x80000000:
                cs=listbase+(sz&0x7fffffff)
                sub.append((p,cs,database+dofs*16))
            else:
                res[p]=(database+dofs*16,sz)
        return sub
    # Without known ends, recursion limit = next larger start among all dirs seen so far; do iterative
    work=[('',0,0,0)]  # path, listbase, start, database
    seen=set()
    dirs=[]
    # gather dir list iteratively with limit=len(body) but break on empty names / duplicates
    while work:
        path,listbase,start,database=work.pop()
        if (path,start) in seen: continue
        seen.add((path,start))
        ents=[]
        o=start
        # stop when reaching a start of another already-known list? unknown; rely on blank name
        while o+16<=len(body):
            nm=decode(body[o:o+8])
            if not nm: break
            dofs,sz=struct.unpack('<II',body[o+8:o+16])
            ents.append((o,nm,dofs,sz)); o+=16
            if start==0 and o>=0xe0: break
        for o,nm,dofs,sz in ents:
            p=path+'/'+nm
            if sz&0x80000000:
                work.append((p,start if False else (start if path=='' else start),(start if path=='' else start)*0+ (0 if path=='' else 0) ,0))
        # placeholder, replaced below
        break
    return None
