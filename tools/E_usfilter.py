#!/usr/bin/env python3
"""Filter notes/E/us_map_all.txt down to section E functions and write notes/E/us_map.txt (+ us_map_candidates.txt).
Accept: ordering ok AND ((score>=0.85 AND |size diff|<=64) OR (score>=0.7 AND |diff|<=32 AND JP-neighbours map to US-neighbours))."""
import re, os, sys
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
E_RX = re.compile(r'(__7CScript|__9CScriptEx|^ifc_|^SafeGetFlagAddr|^ReadDataE|^GetSize__FRiRiRPUc|__6SdrvEE|__Q26SdrvEE|__4Sdrv|__3VEC|^InitSysFunc|^GetSysCallFunc|^CleanSysFunc|'
 r'__9LSDPlayer|__16LSDPlayerHandler|__16LSDDeviceHandler|__8LSDScrEx|__12EventHandler|^EventHandlerUpdate|__18GenericDataHandler|__17LSDCaptionHandler|__14LSDCaptionData|'
 r'__15LsdEffectServer|__9LsdEffect|__16MPSServerHandler|__16BGMServerHandler|__18MovieServerHandler|__10CLSDPauser|__6HNMSnd|__3CSe|__6CMusic|__9StreamBGM|__10StreamFile|'
 r'__12CSndBufCache|__9primSound|__9primMusic|__7KeyWait|__11SendOnLocal|^GetLanguage|__15SequenceControl|__20InterSequenceControl|^Cleate__8Sequence|^Cleate__5Event|^Cleate__7RotAnim|^Cleate__10TranceAnim|^Sdh|^WaveBankToAddr|FiiPPcPv$)')
rows = []
for l in open(os.path.join(ROOT, 'notes/E/us_map_all.txt')):
    if l.startswith('#'): continue
    a, u, n, sc, js, us, st = l.split()
    rows.append((int(a, 16), int(u, 16), n, float(sc), int(js), int(us), st))
rows.sort()
idx = {r[0]: i for i, r in enumerate(rows)}
# US order index among matched rows (sorted by US address)
usorder = {r[1]: i for i, r in enumerate(sorted(rows, key=lambda r: r[1]))}
acc, cand = [], []
for i, (a, u, n, sc, js, us, st) in enumerate(rows):
    if not E_RX.search(n): continue
    if n.startswith('@'): continue
    d = abs(us - ((js + 15) // 16) * 16)
    d2 = abs(us - js)
    d = min(d, d2)
    good = False
    if st == 'ok' and sc >= 0.85 and d <= 64: good = True
    elif st == 'ok' and sc >= 0.7 and d <= 32:
        # neighbour check: previous and next *matched* JP rows are adjacent in US order
        ok = 0
        for j in (i - 1, i + 1):
            if 0 <= j < len(rows) and rows[j][6] == 'ok' and abs(usorder[rows[j][1]] - usorder[u]) == 1: ok += 1
        good = ok >= 1
    (acc if good else cand).append((a, u, n, sc, js, us, st))
with open(os.path.join(ROOT, 'notes/E/us_map.txt'), 'w') as f:
    f.write('# jp_addr us_addr name score   (section E, SLPM_602.19 -> SLUS_210.41; tools/E_usmatch.py + E_usfilter.py; renamed in Ghidra program SLUS_210.41)\n')
    for a, u, n, sc, js, us, st in acc: f.write('%08x %08x %s %.3f\n' % (a, u, n, sc))
with open(os.path.join(ROOT, 'notes/E/us_map_candidates.txt'), 'w') as f:
    f.write('# jp_addr us_addr name score jp_size us_size status   (NOT renamed: low score / size mismatch / ordering outlier)\n')
    for a, u, n, sc, js, us, st in cand: f.write('%08x %08x %s %.3f %d %d %s\n' % (a, u, n, sc, js, us, st))
print(len(acc), 'accepted', len(cand), 'candidates')
