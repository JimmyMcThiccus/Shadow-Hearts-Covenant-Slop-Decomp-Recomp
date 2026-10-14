import pickle, struct, sys
from PIL import Image, ImageDraw
f, t0, t1, step, out = sys.argv[1], float(sys.argv[2]), float(sys.argv[3]), float(sys.argv[4]), sys.argv[5]
cols = int(sys.argv[6]) if len(sys.argv) > 6 else 4
_p = pickle.load(open(f, "rb")); rec, frames = _p[0], _p[1]
samples = [r for r in rec if r[0] != "KEY"]
def st(t):
    best = None
    for s in samples:
        if s[0] <= t: best = s
        else: break
    return struct.unpack_from("<HH", best[1], 0x28)
sel = []; nxt = t0
for t, im in frames:
    if t0 <= t <= t1 and t >= nxt: sel.append((t, im)); nxt = t + step
W, H = frames[0][1].size; rows = (len(sel)+cols-1)//cols
sheet = Image.new("RGB", (cols*W, rows*H))
for i, (t, im) in enumerate(sel):
    im = im.copy(); d = ImageDraw.Draw(im); d.rectangle((0, 0, 140, 12), fill=(0, 0, 0)); d.text((2, 1), "%.2fs ph%s" % (t, st(t)), fill=(255, 255, 0))
    sheet.paste(im, ((i % cols)*W, (i//cols)*H))
sheet.save(out); print(sheet.size, len(sel))
