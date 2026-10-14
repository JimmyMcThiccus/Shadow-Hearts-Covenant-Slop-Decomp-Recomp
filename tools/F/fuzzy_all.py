#!/usr/bin/env python3
"""Page the GhidraMCP bulk_fuzzy_match endpoint over all JP main-exe functions (the `filter`
argument is ignored by the plugin; `offset`/`limit` index source functions)."""
import json, urllib.request, sys
out = sys.argv[1]
allm = {}
off = 0
while off < 4700:
    u = "http://127.0.0.1:8089/bulk_fuzzy_match?source_program=SLPM_602.19&target_program=SLUS_210.41&filter=x&threshold=0.6&limit=300&offset=%d" % off
    j = json.loads(urllib.request.urlopen(u, timeout=900).read())
    for m in j["matches"]:
        k = m["source_address"]
        if k not in allm or m["score"] > allm[k]["score"]:
            allm[k] = m
    off += 300
    print(off, len(allm), flush=True)
json.dump(list(allm.values()), open(out, "w"))
