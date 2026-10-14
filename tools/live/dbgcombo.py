"""Open a debug-map shortcut menu (shoulder/Select + face button), follow a row path, screenshot, print the save bytes that changed,
then back out with Circle (debug map, user's save; see notes/integration/debug_menu.md).

usage: python dbgcombo.py OUT.png COMBO [ROW ...]
  COMBO  = FACE+HOLD key names from keys.py, e.g. L+4 (Circle + R3), J+3 (Square + R2), L+Backspace (Circle + Select)
  ROW    = Down presses before each confirm (X)
"""
import sys, time
import dbg, keys, grab

SKIP = {("BTL0", i) for i in range(0x10BC, 0x133C)} | {("MENU", i) for i in range(0xC, 0x10)}


def snap(d):
    return {"BTL0": d.mem(0x100130, 0x21BC), "MENU": d.mem(0x102D2C, 0x400)}


def main():
    out, combo, rows = sys.argv[1], sys.argv[2], [int(x) for x in sys.argv[3:]]
    face, hold = combo.split("+")
    d = dbg.Dbg()
    before = snap(d)
    keys.down(hold); time.sleep(0.05); keys.down(face); time.sleep(0.2); keys.up(face); keys.up(hold)
    time.sleep(1.2)
    for r in rows:
        for _ in range(r):
            keys.tap("Down", 0.1); time.sleep(0.3)
        keys.tap("K", 0.1); time.sleep(1.0)
    grab.grab().save(out)
    after = snap(d)
    for n in ("BTL0", "MENU"):
        ch = [i for i in range(len(before[n])) if before[n][i] != after[n][i] and (n, i) not in SKIP]
        print(n, len(ch), ["+%#x %02x->%02x" % (i, before[n][i], after[n][i]) for i in ch[:20]])
    for _ in range(len(rows) + 2):
        keys.tap("L", 0.1); time.sleep(0.7)


if __name__ == "__main__":
    main()
