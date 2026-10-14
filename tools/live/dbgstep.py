"""Press keys in the live game, take a screenshot and print which bytes of the save blocks changed (for mapping the
built-in debug menu and other screens onto the save layout).

usage: python dbgstep.py SHOT.png KEY [KEY ...]      KEY as in keys.py (K = X / confirm, L = circle / cancel, Up, Down ...);
       a short 0.1 s tap each, 0.4 s apart, then 1 s settle.
Blocks: BTL0 0x100130 (0x21bc bytes), MENU 0x102d2c (0x400, the play-time bytes +0xc..+0xf are ignored); re-check them for other saves.
"""
import sys, time
import dbg, keys, grab

BLOCKS = (("BTL0", 0x100130, 0x21BC), ("MENU", 0x102D2C, 0x400))
IGNORE = {("MENU", i) for i in range(0xC, 0x10)}


def main():
    out, ks = sys.argv[1], sys.argv[2:]
    d = dbg.Dbg()
    before = {n: d.mem(a, s) for n, a, s in BLOCKS}
    for k in ks:
        keys.tap(k, 0.1)
        time.sleep(0.4)
    time.sleep(1.0)
    grab.grab().save(out)
    for n, a, s in BLOCKS:
        x, y = before[n], d.mem(a, s)
        diffs = [i for i in range(s) if x[i] != y[i] and (n, i) not in IGNORE]
        runs = []
        for i in diffs:
            if runs and i - runs[-1][1] <= 4:
                runs[-1][1] = i
            else:
                runs.append([i, i])
        print(n, len(diffs), "bytes changed")
        for lo, hi in runs[:40]:
            print("  +%#x..%#x  %s -> %s" % (lo, hi, x[lo:hi + 1].hex(), y[lo:hi + 1].hex()))


if __name__ == "__main__":
    main()
