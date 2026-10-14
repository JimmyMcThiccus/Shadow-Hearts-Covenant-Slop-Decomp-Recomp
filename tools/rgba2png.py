#!/usr/bin/env python3
"""rgba2png.py DIR  -- convert every NN_WxH.rgba in DIR (written by sh2_menu/examples/opening_dump.rs) to PNG."""
import sys, os, zlib, struct, re
def png(path, w, h, data):
    raw = b''.join(b'\x00' + data[y*w*4:(y+1)*w*4] for y in range(h))
    def chunk(t, d): c = struct.pack('>I', len(d)) + t + d; return c + struct.pack('>I', zlib.crc32(t + d) & 0xffffffff)
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 6, 0, 0, 0)) + chunk(b'IDAT', zlib.compress(raw)) + chunk(b'IEND', b''))
for f in sorted(os.listdir(sys.argv[1])):
    m = re.match(r'(\d+)_(\d+)x(\d+)\.rgba$', f)
    if m:
        w, h = int(m.group(2)), int(m.group(3)); d = open(os.path.join(sys.argv[1], f), 'rb').read()
        if len(d) == w*h*4: png(os.path.join(sys.argv[1], f[:-5] + '.png'), w, h, d)
