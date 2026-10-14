import sys, time, struct, os
from dbg import Dbg
import keys
d = Dbg()
CB = struct.unpack('<I', d.mem(0x440000, 4))[0]
def phase():
    b = d.mem(CB + 0x28, 4); return struct.unpack("<HH", b)
RING_CACHE=[None]
def ring_ok(base):
    try:
        r=d.mem(base+0xb4,4)
        c=struct.unpack('<I',d.mem(base+0xfc,4))[0]
        return abs(struct.unpack('<f',r)[0]-1.6)<1e-3 and 1<=c<=5
    except Exception: return False
def find_ring():
    p = struct.unpack("<I", d.mem(CB + 0x45d0, 4))[0]
    if 0x400000 <= p < 0x2000000 and ring_ok(p): return p
    return None
def run_ring(base):
    cnt = struct.unpack("<I", d.mem(base + 0xfc, 4))[0]
    areas = [struct.unpack_from("<HH", d.mem(base + 0x104 + i * 0x24, 4), 0) for i in range(cnt)]
    pressed = [False] * cnt; up_at = None; t0 = time.perf_counter(); prev = None
    while time.perf_counter() - t0 < 8:
        if up_at is not None and time.perf_counter() >= up_at: keys.up("K"); up_at = None
        ph = phase()
        if ph != (5, 4): break
        ang = struct.unpack("<f", d.mem(base + 0x4ac, 4))[0] % 360.0
        if up_at is None:
            for i, (s, w) in enumerate(areas):
                trig = (s + w * 0.45 - 14.0) % 360.0
                if not pressed[i] and prev is not None and ((prev < trig <= ang) or (trig < ang < s + w and prev < ang)):
                    keys.down("K"); up_at = time.perf_counter() + 0.13; pressed[i] = True; break
        prev = ang
    if up_at is not None: keys.up("K")
    return areas, pressed
LOGF=open("fight.log","a",buffering=1)
def log(*a):
    LOGF.write("%.1f %s" % (time.time() - T0, " ".join(str(x) for x in a)) + chr(10)) if False else LOGF.write(("%.1f %s" % (time.time() - T0, " ".join(str(x) for x in a))) + chr(10))
T0 = time.time()
last_ph = None; same_since = time.time(); won_at = None; menu_press_t = 0
while time.time() - T0 < float(sys.argv[1]):
    try: ph = phase()
    except Exception as e: log("read err", e); break
    if ph != last_ph: log("phase", ph); last_ph = ph; same_since = time.time()
    if ph == (4, 1) and time.time() - same_since > 0.6 and time.time() - menu_press_t > 2.5:
        keys.tap("K", 0.13); time.sleep(0.8); keys.tap("K", 0.13); menu_press_t = time.time(); log("attack + target")
    elif ph == (5, 4):
        base = find_ring(); log("ring at", hex(base) if base else None)
        if base: log("ring result", run_ring(base))
    elif ph[0] in (0x15, 0x17, 0x16) and time.time() - menu_press_t > 1.2:
        keys.tap("K", 0.13); menu_press_t = time.time(); log("result K")
        if ph[0] == 0x15 or ph[0] == 0x17: won_at = won_at or time.time()
    time.sleep(0.02)
log("end")
