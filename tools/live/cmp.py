"""Side by side of a live PCSX2 capture (grab.py output) and a port screenshot, both normalised to the 512 x 448 virtual frame at 2x.

usage: python cmp.py LIVE.png PORT.png OUT.png [x0 y0 x1 y1]     (optional crop box in virtual pixels)
The live capture is the whole game picture (2.223 x 1.879 capture px per virtual px); the port window is 4:3 and fills the picture.
"""
import sys
from PIL import Image
LIVE_TOP = 4.5   # virtual rows of the picture cut off above the capture (PCSX2 display offset, measured on the radar ring, the party panel and the list)
def norm(path, scale=2):
    im = Image.open(path).convert("RGB")
    if im.size[0] > 1000 and abs(im.size[1] / im.size[0] - 0.74) < 0.03:
        # live grab: the capture shows rows LIVE_TOP..448 of the 512 x 448 frame
        body = im.resize((512 * scale, round((448 - LIVE_TOP) * scale)), Image.LANCZOS)
        out = Image.new("RGB", (512 * scale, 448 * scale), (0, 0, 0))
        out.paste(body, (0, round(LIVE_TOP * scale)))
        return out
    return im.resize((512 * scale, 448 * scale), Image.LANCZOS)
def main():
    live, port, out = sys.argv[1:4]
    a, b = norm(live), norm(port)
    if len(sys.argv) >= 8:
        x0, y0, x1, y1 = [int(v) * 2 for v in sys.argv[4:8]]
        a, b = a.crop((x0, y0, x1, y1)), b.crop((x0, y0, x1, y1))
    sheet = Image.new("RGB", (a.width * 2 + 8, a.height), (255, 0, 255))
    sheet.paste(a, (0, 0)); sheet.paste(b, (a.width + 8, 0))
    sheet.save(out)
main()
