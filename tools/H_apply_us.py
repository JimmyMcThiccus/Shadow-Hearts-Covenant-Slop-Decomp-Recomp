#!/usr/bin/env python3
"""Apply notes/H/us_map.txt names (score>=MIN) to SH2US_BATTLE.BIN via GhidraMCP HTTP API (127.0.0.1:8089)."""
import sys, json, urllib.request, urllib.parse
MIN = float(sys.argv[1]) if len(sys.argv) > 1 else 0.6
P = 'SH2US_BATTLE.BIN'
def post(ep, d):
    r = urllib.request.Request(f'http://127.0.0.1:8089/{ep}?program={P}', json.dumps(d).encode(), {'Content-Type': 'application/json'})
    return urllib.request.urlopen(r, timeout=60).read().decode()
def get(ep, **q):
    return urllib.request.urlopen(f'http://127.0.0.1:8089/{ep}?program={P}&' + urllib.parse.urlencode(q), timeout=60).read().decode()
ok = cr = bad = 0
for l in open('notes/H/us_map.txt'):
    if l.startswith('#'): continue
    p = l.split()
    if len(p) < 4 or float(p[3]) < MIN: continue
    us, name = p[1], p[2]
    if get('get_function_by_address', address=us).startswith('No function'):
        post('create_function', {'address': us, 'name': name}); cr += 1
    r = post('rename_function_by_address', {'function_address': us, 'new_name': name})
    if 'uccess' in r: ok += 1
    else: bad += 1; print('FAIL', l.strip(), r[:100])
print('renamed', ok, 'created', cr, 'failed', bad)
