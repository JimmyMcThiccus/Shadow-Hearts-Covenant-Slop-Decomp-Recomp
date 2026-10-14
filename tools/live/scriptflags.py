"""Print the event-script flags that are set in the live game, by name (flagnames.py).

usage: python scriptflags.py [REGFILE_ADDR]      default: follow the CScript pointer chain (flagnames.register_file)
"""
import sys, struct
import dbg
from flagnames import NAMES, COUNTERS, N_REGS, register_file


def main():
    d = dbg.Dbg()
    reg = int(sys.argv[1], 0) if len(sys.argv) > 1 else register_file(d)
    if reg is None:
        sys.exit("no field script running (battle / world map?)")
    raw = d.mem(reg, N_REGS * 4)
    w = struct.unpack("<%dI" % N_REGS, raw)
    print("register file at %#x" % reg)
    for n in range(N_REGS * 32):
        if (w[n >> 5] >> (n & 31)) & 1:
            print("%#06x  %s" % (n, NAMES.get(n, "")))
    for name, off, _ in COUNTERS:
        print("%s: %d" % (name, raw[off]))


if __name__ == "__main__":
    main()
