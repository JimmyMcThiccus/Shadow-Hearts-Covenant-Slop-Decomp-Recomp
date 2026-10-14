import struct, numpy as np
from dbg import Dbg
d = Dbg()
lo, hi, ch = 0x100000, 0x2000000, 0x40000
ram = b"".join(d.mem(a, ch) for a in range(lo, hi, ch))
arr = np.frombuffer(ram[: len(ram)//4*4], dtype="<u4")
pat = np.array([0x10, 0x10, 0x6c, 0x6c], dtype="<u4")
hits = np.nonzero((arr[:-3] == 0x10) & (arr[1:-2] == 0x10) & (arr[2:-1] == 0x6c) & (arr[3:] == 0x6c))[0]
for k in hits:
    a = lo + int(k) * 4
    print(hex(a), "obj?", hex(a - 0x9c))
    o = a - 0x9c
    blk = d.mem(o, 0x120)
    print(" +0x20..:", [round(x, 3) for x in struct.unpack_from("<12f", blk, 0x20)])
    print(" +0x80 ptr", hex(struct.unpack_from("<I", blk, 0x80)[0]), "+0x84..", struct.unpack_from("<3f", blk, 0x84), "+0x8c", struct.unpack_from("<5f", blk, 0x8c), "flags", blk[0xc0:0xc4].hex())
