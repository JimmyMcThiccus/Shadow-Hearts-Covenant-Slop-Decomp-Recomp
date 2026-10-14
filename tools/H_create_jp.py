#!/usr/bin/env python3
"""Create any function from tools/labels/BATTLE.BIN.funcs missing in SH2JP_BATTLE.BIN (GhidraMCP HTTP API)."""
import json, urllib.request, re
P='SH2JP_BATTLE.BIN'
have=set(l.split(' at ')[1].strip() for l in urllib.request.urlopen(f'http://127.0.0.1:8089/list_functions?program={P}&limit=5000').read().decode().splitlines() if ' at ' in l)
n=bad=0
for l in open('tools/labels/BATTLE.BIN.funcs'):
    p=l.split()
    if len(p)<2 or p[0] in have: continue
    r=urllib.request.Request(f'http://127.0.0.1:8089/create_function?program={P}', json.dumps({'address':p[0],'name':p[1]}).encode(), {'Content-Type':'application/json'})
    try:
        o=urllib.request.urlopen(r,timeout=120).read().decode()
        if '"success":true' in o: n+=1
        else: bad+=1; print(p, o[:120])
    except Exception as e: bad+=1; print(p,e)
print('created',n,'failed',bad)
