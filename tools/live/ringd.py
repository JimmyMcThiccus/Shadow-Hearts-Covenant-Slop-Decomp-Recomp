"""Ring daemon: python ringd.py SECS LOG -- every Judgement Ring that appears at [CBattle+0x45d0] (any phase: attacks, skills, items) is
handed to the game's autoplayer the moment it starts: +0x50c/+0x50d abnormal flags = 0, +0xbc period = +|period| (>= 1.6), +0x58c auto_mode = 1.
Logs ring start (phase, state, areas, period, abnormal flags) and the result flags (+0x512) when it ends."""
import sys, time, struct
sys.path.insert(0, __import__("os").path.dirname(__file__))
from dbg import Dbg
d = Dbg(); W = lambda a, h: d.send(cmd="write_memory", cpu="ee", address="0x%x" % a, data=h)
secs = float(sys.argv[1]); log = open(sys.argv[2], "a", buffering=1); t0 = time.time()
def L(s): log.write("%.2f %s\n" % (time.time() - t0, s))
cur = None
while time.time() - t0 < secs:
    c = struct.unpack('<I', d.mem(0x440000, 4))[0]
    if not c: cur = None; time.sleep(0.2); continue
    p = struct.unpack('<I', d.mem(c + 0x45d0, 4))[0]
    if 0x400000 <= p < 0x2000000:
        h = d.mem(p, 0x600)
        state = struct.unpack_from('<h', h, 0x46)[0]
        fa = h[0x40]
        per = struct.unpack_from('<f', h, 0xbc)[0]
        auto = struct.unpack_from('<h', h, 0x58c)[0]
        cnt = struct.unpack_from('<I', h, 0xfc)[0]
        if (fa & 0x80) and state in (3, 4) and 1 <= cnt <= 8 and (auto != 1 or h[0x50c] or h[0x50d] or per < 0):
            ph = struct.unpack('<HH', d.mem(c + 0x28, 4))
            areas = [struct.unpack_from('<HHH', h, 0x104 + i * 0x24) for i in range(cnt)]
            W(p + 0x50c, "0000"); W(p + 0xbc, struct.pack('<f', max(abs(per), 1.6)).hex()); W(p + 0x58c, struct.pack('<h', 1).hex())
            L("force ring %x phase %s state %d areas %s period %.2f abn %s" % (p, ph, state, areas, per, h[0x50c:0x50e].hex()))
            cur = p
        elif cur == p and state not in (3, 4):
            L("ring %x ended state %d result %02x" % (p, state, h[0x512])); cur = None
    time.sleep(0.01)
