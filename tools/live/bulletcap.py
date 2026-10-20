"""Capture a ranged (Bullet1) enemy attack in the live retail game.

Start it right after confirming バトル開始 on the debug map's Event battle page (monster set 134 = one gun soldier, model 191):
waits for the new CBattle, pins every party member's HP (BtlChr +0x7c / +0x80 = 999), then for SECS seconds grabs a frame every
~80 ms (`cap_NNN.png`) and dumps the first enemy's BtlChr (0x200 bytes) with each frame (`cap.bin`: u32 frame, f32 time, 0x200 bytes).

usage: python bulletcap.py OUTDIR SECS
"""
import os, struct, sys, time
from dbg import Dbg
import grab

out, secs = sys.argv[1], float(sys.argv[2])
os.makedirs(out, exist_ok=True)
d = Dbg()
old = struct.unpack("<I", d.mem(0x440000, 4))[0]
t0 = time.time()
cb = None
while time.time() - t0 < 20:
    p = struct.unpack("<I", d.mem(0x440000, 4))[0]
    if p and p != old and 0x400000 <= p < 0x2000000:
        # the enemy slot is filled once the battle has set up
        m = d.mem(p + 0xb0 + 0x510, 0x90)
        if struct.unpack_from("<I", m, 0x80)[0] > 0:
            cb = p
            break
    time.sleep(0.02)
print("CBattle", hex(cb) if cb else None)
if not cb:
    sys.exit(1)
party = [k for k in range(7) if d.mem(cb + 0xb0 + k * 0x510 + 4, 1)[0] & 1 == 0 and d.mem(cb + 0xb0 + k * 0x510, 1)[0]]
enemy = next(k for k in range(7) if d.mem(cb + 0xb0 + k * 0x510 + 4, 1)[0] & 1)
print("party slots", party, "enemy slot", enemy)
log = open(os.path.join(out, "cap.bin"), "wb")
n = 0
t0 = time.time()
while time.time() - t0 < secs:
    for k in party:
        b = cb + 0xb0 + k * 0x510
        d.send(cmd="write_memory", cpu="ee", address=hex(b + 0x7c), data="e7030000e7030000")
    m = d.mem(cb + 0xb0 + enemy * 0x510, 0x200)
    log.write(struct.pack("<If", n, time.time() - t0) + m)
    grab.grab().save(os.path.join(out, "cap_%03d.png" % n))
    n += 1
    time.sleep(0.05)
print("frames", n)
