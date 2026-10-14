"""Play a key sequence against the live PCSX2 game and grab screenshots.

usage: python seq.py OUTDIR step [step ...]
  step = KEY            tap (hold 0.16 s: the pad is read at 30 Hz), then wait 0.45 s
       | KEY*N          tap N times
       | wait:SECONDS
       | shot:NAME      save OUTDIR/NAME.png (grab.py crop of the game picture)
       | shots:NAME[:N[:SECONDS]]   N frames (default 4) SECONDS apart (default 0.15) as NAME_a.png, NAME_b.png ...: use this
                        whenever something animates (the cursor orb / arrow, page arrows, glows) so every phase is on record
Keys: K cross, L circle, I triangle, J square, Return start, Up/Down/Left/Right, W/A/S/D stick.
Retail US layout: the physical Cross (K) is the logical *Circle* = confirm, the physical Circle (L) = cancel.
"""
import sys, time, os
import keys, grab

def main():
    out = sys.argv[1]
    os.makedirs(out, exist_ok=True)
    for st in sys.argv[2:]:
        if st.startswith("wait:"):
            time.sleep(float(st[5:]))
        elif st.startswith("shots:"):
            name, _, rest = st[6:].partition(":")
            n, _, gap = rest.partition(":")
            for i in range(int(n or 4)):
                time.sleep(float(gap or 0.15))
                grab.grab().save(os.path.join(out, f"{name}_{chr(97 + i)}.png"))
        elif st.startswith("shot:"):
            time.sleep(0.25)
            grab.grab().save(os.path.join(out, st[5:] + ".png"))
        else:
            k, _, n = st.partition("*")
            for _ in range(int(n or 1)):
                keys.tap(k, 0.16)
                time.sleep(0.45)

if __name__ == "__main__":
    main()
