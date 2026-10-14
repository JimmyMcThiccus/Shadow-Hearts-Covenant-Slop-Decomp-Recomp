"""Find the live CNaviMap object (slot 8 of the 2026-10 session): locate the NAVM data in RAM, then the object whose +0x80 points at it."""
import struct, sys
from dbg import Dbg
d = Dbg()
lo, hi, ch = 0x100000, 0x2000000, 0x40000
ram = b"".join(d.mem(a, ch) for a in range(lo, hi, ch))
i = 0; navm = []
while True:
    i = ram.find(b"NAVM\x01\x00\x40\x00", i)
    if i < 0: break
    navm.append(lo + i); i += 4
print("NAVM at", [hex(a) for a in navm])
for a in navm:
    pat = struct.pack("<I", a); j = 0
    while True:
        j = ram.find(pat, j)
        if j < 0: break
        if j % 4 == 0:
            obj = lo + j - 0x80
            print("ptr to", hex(a), "at", hex(lo + j), "-> CNaviMap candidate", hex(obj))
        j += 4
import numpy as np
arr = np.frombuffer(ram[: len(ram)//4*4], dtype="<u4")
for a in navm:
    idx = np.nonzero((arr >= a - 0x100) & (arr <= a + 0x100))[0]
    print([(hex(lo + int(k)*4), hex(int(arr[k]))) for k in idx][:20])
for a in navm:
    idx = np.nonzero((arr & 0x1ffffff) == a)[0]
    print("masked", [(hex(lo + int(k)*4), hex(int(arr[k]))) for k in idx][:20])
