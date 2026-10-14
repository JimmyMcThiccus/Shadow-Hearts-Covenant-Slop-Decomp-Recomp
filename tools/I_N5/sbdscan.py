import struct,sys,collections,json,mmap
D="/Volumes/work/Sh2 Decomp/Shadow Hearts - Covenant (USA) (Disc 1)-1/"
res=collections.defaultdict(list)
for pk in ('BTLDATA.PKB','OPENING.PKB','WORLDMAP.PKB','COMMON.PKB','MENU.PKB','SOLOMON.PKB','SHOP.PKB','LSD.PKB','EFFECT.PKB'):
    f=open(D+pk,'rb'); mm=mmap.mmap(f.fileno(),0,access=mmap.ACCESS_READ)
    pos=0; n=0
    while True:
        i=mm.find(b'SBD 0.1',pos)
        if i<0: break
        pos=i+8
        if i%0x10: continue
        try:
            lo=struct.unpack_from('<I',mm,i+0x1c)[0]
            if mm[i+lo:i+lo+8]!=b'LINKHDR ': continue
            cnt=struct.unpack_from('<I',mm,i+lo+8)[0]; first=struct.unpack_from('<I',mm,i+lo+0xc)[0]
            if cnt>64: continue
            n+=1
            for k in range(cnt):
                eo=i+lo+first+k*16
                co=eo+struct.unpack_from('<I',mm,eo+12)[0]
                if mm[co:co+8]==b'EFFECT  ':
                    m=struct.unpack_from('<I',mm,co+8)[0]; do=struct.unpack_from('<I',mm,co+12)[0]
                    for q in range(m):
                        r=mm[co+do+q*16:co+do+q*16+16]
                        res[pk].append((hex(i),struct.unpack_from('<H',r,2)[0]))
        except Exception as e: pass
    print(pk,'sbd',n,'effects',len(res[pk]),sorted(collections.Counter(t for _,t in res[pk]).items()))
