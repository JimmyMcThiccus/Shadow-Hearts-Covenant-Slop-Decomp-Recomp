#!/usr/bin/env python3
"""Split a saved mcp ghidra batch_decompile result (JSON {"result": "<json map>"}) into one .c file per function.
usage: split_batch.py <tool-result.txt> <outdir>"""
import json, sys, os
d = json.load(open(sys.argv[1]))
r = json.loads(d['result']) if isinstance(d['result'], str) else d['result']
os.makedirs(sys.argv[2], exist_ok=True)
for k, v in r.items():
    open(os.path.join(sys.argv[2], k + '.c'), 'w').write(v)
    print(k, len(v))
