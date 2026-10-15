"""Round 6 RG: start a field Judgement Ring in the running retail game and record it (US build, any field map).

usage: python fring.py KIND LAP_MS ARG SPEC OUTDIR [--press DEG] [--frames N]

Writes the `CField` ring block exactly as `CField::SetRing` (US FIELD.BIN 0x004fad40) fills it -- `CField*` = [0x43ff34], block at
+0x8a8: byte 0 kind & 7 (bit 3 = result ready), +1 area count, +2 control, +3 object state (2 = create the JRing), +4/+6 x / y,
+0x8 result, +0xc lap ms, +0x10 arg, +0x14.. one u32 per area (start bits 0-8, end bits 9-17, colour bits 26-29) -- then
`RingControl(1)` (control := 1).  `UpdateRing` runs it like a script ring.  Samples the JRing (`+0x4c` of the block) every ~30 ms:
state +0x46, sub +0x48, cur angle +0x4ac, period +0xbc, event value +0x588; grabs frames; with --press DEG taps Circle when the
pointer passes DEG (spin ring) or inside each area (lap rings, DEG ignored with --press -1).  Prints the result word.
The block is the game's own; nothing else is written.  Pick the instance with SH2_PCSX2_INST.
"""
import os, struct, sys, time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dbg, keys, grab  # noqa: E402

CFIELD = 0x43FF34


def main():
    kind, lap, arg, spec, out = int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), sys.argv[4], sys.argv[5]
    press = None
    if "--press" in sys.argv:
        press = float(sys.argv[sys.argv.index("--press") + 1])
    nframes = int(sys.argv[sys.argv.index("--frames") + 1]) if "--frames" in sys.argv else 24
    os.makedirs(out, exist_ok=True)
    d = dbg.Dbg()
    f = d.u32(CFIELD)
    if not f:
        raise SystemExit("not on a field map")
    blk = f + 0x8A8
    # parse like SetRing
    areas, col, start, i, s = [], 1, 0, 0, spec.upper()
    def num():
        nonlocal i
        j = i
        while i < len(s) and s[i].isdigit():
            i += 1
        return int(s[j:i] or 0)
    while i < len(s):
        c = s[i]; i += 1
        if c == "E":
            e = num() & 0x1FF
            areas.append((start, e, col & 0xF)); col, start = 1, 0
        elif c == "S":
            start = num() & 0x1FF
        elif c == "C":
            col = num()
    body = bytearray(0x3C)
    body[0] = kind & 7
    body[1] = len(areas)
    body[3] = 2
    struct.pack_into("<hh", body, 4, 256, 224)
    struct.pack_into("<ii", body, 0xC, lap, arg)
    for k, (a0, a1, c) in enumerate(areas):
        struct.pack_into("<I", body, 0x14 + 4 * k, a0 | (a1 << 9) | (c << 26))
    grab.grab()  # the first PrintWindow takes ~1.5 s: warm it up before the ring starts
    d.write(blk, bytes(body))
    time.sleep(0.3)
    ring = d.u32(blk + 0x4C)
    print("CField", hex(f), "JRing", hex(ring), "state", d.mem(blk + 3, 1)[0])
    d.write(blk + 2, b"\x01")
    t0 = time.time()
    log = open(os.path.join(out, "samples.txt"), "w")
    shots, last_shot, pressed, prev, last_area = 0, -1.0, 0, None, None
    result = None
    while time.time() - t0 < 40:
        t = time.time() - t0
        b0, ctl = d.mem(blk, 3)[0], d.mem(blk + 2, 1)[0]
        ring = d.u32(blk + 0x4C)
        st = sub = 0; ang = per = 0.0; ev = 0
        if ring:
            st, sub = struct.unpack("<hh", d.mem(ring + 0x46, 4))
            ang = struct.unpack("<f", d.mem(ring + 0x4AC, 4))[0]
            per = struct.unpack("<f", d.mem(ring + 0xBC, 4))[0]
            ev = struct.unpack("<i", d.mem(ring + 0x588, 4))[0]
        log.write("%.3f ctl %d flag %d state %d sub %d ang %.1f period %.3f ev %d\n" % (t, ctl, (b0 >> 3) & 1, st, sub, ang, per, ev))
        if press is not None and ring and st == 4 and pressed < 64:
            a = ang % 360
            hit = False
            if press >= 0 and prev is not None:
                p = prev % 360
                hit = (p <= press <= a) if p <= a else (press >= p or press <= a)
            elif press < 0:
                inside = [k for k, (a0, a1, _) in enumerate(areas) if a0 + 4 <= a <= a1 - 4]
                hit = bool(inside) and inside[0] != last_area
                if hit:
                    last_area = inside[0]
            if press < 0 and not any(a0 <= a <= a1 for (a0, a1, _) in areas):
                last_area = None if last_area is None else last_area
            if hit and sub in (0, 1):
                keys.tap("L", 0.12); pressed += 1
                log.write("%.3f PRESS at %.1f\n" % (time.time() - t0, a))
            prev = ang
        if shots < nframes and t - last_shot > 0.25:
            grab.grab().save(os.path.join(out, "f%02d_%.1fs_c%d_s%d.png" % (shots, t, ctl, st)))
            shots += 1; last_shot = t
        if ctl == 0 and (b0 >> 3) & 1:
            result = struct.unpack("<i", d.mem(blk + 8, 4))[0]
            break
        time.sleep(0.02)
    log.close()
    print("result", result, "after %.2f s" % (time.time() - t0))


if __name__ == "__main__":
    main()
