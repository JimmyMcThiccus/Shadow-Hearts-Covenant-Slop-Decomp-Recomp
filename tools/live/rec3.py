import sys, time, pickle, threading, struct
from dbg import Dbg
import keys, grab
CB = 0xaffa20; CHR = CB + 0xb0; STRIDE = 0x510; RING = 0x11718b0
AREAS = [(169, 90), (279, 72)]
d = Dbg(); frames = []; stop = False
IW, IH = 380, 290
def grabber(t0):
    while not stop:
        t = time.perf_counter()-t0; im = grab.grab(); frames.append((t, im.resize((IW, IH))))
def run(dur, out, lead=0.0, frac=0.45, trig_lead=14.0, press=True):
    global stop
    t0 = time.perf_counter(); rec = []; events = []
    th = threading.Thread(target=grabber, args=(t0,), daemon=True); th.start()
    keys.tap("K", 0.13); events.append((time.perf_counter()-t0, "K menu")); time.sleep(0.7)
    keys.tap("K", 0.13); events.append((time.perf_counter()-t0, "K target"))
    pressed = [False]*len(AREAS); up_at = None; prev_ang = None
    while True:
        now = time.perf_counter()-t0
        if now > dur: break
        if up_at is not None and now >= up_at: keys.up("K"); up_at = None
        rg = d.mem(RING+0x4a0, 0x40)
        ang = struct.unpack_from("<f", rg, 0xc)[0] % 360.0
        if press and up_at is None:
            for i, (s, w) in enumerate(AREAS):
                trig = s + w*frac - trig_lead
                if not pressed[i] and prev_ang is not None and prev_ang < ang and prev_ang <= trig <= ang + 0.001 or (not pressed[i] and trig < ang < s + w):
                    keys.down("K"); up_at = now + 0.13; pressed[i] = True; events.append((now, "press area %d at ang %.1f"%(i, ang))); break
        prev_ang = ang
        rec.append((now, d.mem(CB, 0x100), d.mem(CHR+1*STRIDE, STRIDE), d.mem(CHR+2*STRIDE, STRIDE), rg, d.mem(0xaffa5c, 4)))
    stop = True; th.join()
    pickle.dump((rec, frames, events), open(out, "wb")); return events
if __name__ == "__main__":
    ev = run(float(sys.argv[2]), sys.argv[1]); print(ev); print(len(frames), "frames")
