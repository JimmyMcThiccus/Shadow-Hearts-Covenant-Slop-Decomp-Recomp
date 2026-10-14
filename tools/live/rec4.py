import sys, time, pickle, threading, struct
from dbg import Dbg
import keys, grab
d = Dbg(); CB = struct.unpack("<I", d.mem(0x440000, 4))[0]; CHR = CB + 0xb0; STRIDE = 0x510
CAM = struct.unpack("<I", d.mem(CB + 0x45c4, 4))[0]
frames = []; stop = False
def grabber(t0):
    while not stop:
        t = time.perf_counter() - t0; frames.append((t, grab.grab().resize((380, 290))))
def ring_ptr():
    p = struct.unpack("<I", d.mem(CB + 0x45d0, 4))[0]
    return p if 0x400000 <= p < 0x2000000 else None
def run(dur, out):
    global stop
    t0 = time.perf_counter(); rec = []; ev = []
    th = threading.Thread(target=grabber, args=(t0,), daemon=True); th.start()
    import os
    keys.tap("K", 0.13); time.sleep(0.7)
    for _ in range(int(os.environ.get("DOWNS","0"))): keys.tap("Down", 0.13); time.sleep(0.4)
    keys.tap("K", 0.13); ev.append((time.perf_counter() - t0, "attack+target"))
    areas = None; pressed = []; prev = None; up_at = None
    while True:
        now = time.perf_counter() - t0
        if now > dur: break
        if up_at is not None and now >= up_at: keys.up("K"); up_at = None
        ph = struct.unpack("<HH", d.mem(CB + 0x28, 4))
        ring = None
        if ph == (5, 4):
            rp = ring_ptr()
            if rp:
                if areas is None:
                    cnt = struct.unpack("<I", d.mem(rp + 0xfc, 4))[0]
                    areas = [struct.unpack_from("<HH", d.mem(rp + 0x104 + i * 0x24, 4), 0) for i in range(cnt)]; pressed = [False] * cnt
                ang = struct.unpack("<f", d.mem(rp + 0x4ac, 4))[0] % 360.0
                if up_at is None:
                    for i, (s, w) in enumerate(areas):
                        trig = (s + w * 0.45 - 14.0) % 360.0
                        if not pressed[i] and prev is not None and ((prev < trig <= ang) or (trig < ang < s + w and prev < ang)):
                            keys.down("K"); up_at = now + 0.13; pressed[i] = True; ev.append((now, "press %d at %.1f" % (i, ang))); break
                prev = ang; ring = ang
        chrs = [d.mem(CHR + k * STRIDE + 0xa0, 0x40) for k in range(6)]   # +0xa0..0xdf : pos, prev pos, heading
        cam = d.mem(CAM, 0x200)
        tm = struct.unpack("<I", d.mem(CB + 0x3c, 4))[0]
        rec.append((now, tm, ph, ring, chrs, cam))
    stop = True; th.join()
    pickle.dump((rec, frames, ev), open(out, "wb")); return ev
if __name__ == "__main__":
    print(run(float(sys.argv[2]), sys.argv[1])); print(len(frames), "frames")
