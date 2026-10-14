import struct
def find_container(d,off):
    for base in range(off-0x10, max(0,off-0x400000), -0x10):
        n,sz=struct.unpack_from('<II',d,base)
        if 0<n<64 and base+sz>off and sz<0x4000000:
            ents=[struct.unpack_from('<4sI',d,base+8+8*i) for i in range(n)]
            if all(e[0][:3].isalpha() for e in ents) and any(base+o==off for _,o in ents) and all(o<sz for _,o in ents):
                return base,[(t.rstrip(b'\0').decode(),base+o) for t,o in ents],sz
    return None
