import numpy as np
from dbg import Dbg
def dump(d, lo=0x400000, hi=0x1800000, ch=0x20000):
    return b"".join(d.mem(a, ch) for a in range(lo, hi, ch))
