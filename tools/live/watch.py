import time, sys, struct
from dbg import Dbg
import grab
d = Dbg(); LOG = open("watch.log", "a", buffering=1)
def st():
    s = d.mem(0x749500, 0x80)
    return (s[0x36], s[0x58:0x70].split(b"\0")[0].decode("ascii","replace"), struct.unpack_from("<I", s, 0x44)[0])
T0 = time.time(); last = None; n = 0
LOG.write("watcher start\n")
while time.time() - T0 < float(sys.argv[1]):
    cur = st()
    if cur != last:
        LOG.write("%.1f request=%d next_map=%s monset=%d\n" % (time.time() - T0, *cur)); last = cur
        time.sleep(0.8); grab.grab().resize((570, 435)).save("watch_%d.png" % n); LOG.write("   screenshot watch_%d.png\n" % n); n += 1
    time.sleep(0.03)
LOG.write("watcher end\n")
