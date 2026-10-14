#!/usr/bin/env python3
"""Fetch decompiler output for all BATTLE.BIN funcs missing in <raw_dir> via GhidraMCP HTTP (127.0.0.1:8089)."""
import sys, os, urllib.request, urllib.parse
raw = sys.argv[1]; P = 'SH2JP_BATTLE.BIN'
os.makedirs(raw, exist_ok=True)
n = 0
for l in open('tools/labels/BATTLE.BIN.funcs'):
    a = l.split()[0]
    f = os.path.join(raw, a + '.c')
    if os.path.exists(f) and os.path.getsize(f) > 20: continue
    try:
        t = urllib.request.urlopen('http://127.0.0.1:8089/decompile_function?' + urllib.parse.urlencode({'address': a, 'program': P}), timeout=180).read().decode('utf-8', 'replace')
    except Exception as e:
        t = 'Error: %s' % e
    open(f, 'w').write(t); n += 1
    if n % 25 == 0: print(n, flush=True)
print('done', n)
