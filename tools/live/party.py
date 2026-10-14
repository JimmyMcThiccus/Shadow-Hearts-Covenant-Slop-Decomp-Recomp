"""Poke a custom party / inventory into the live US game (PCSX2 DebugServer writes; reload a save state to undo).

usage: python party.py RECORDS.txt IDS [--fill-equip N] [--items id=n,...] [--battle K]
  RECORDS.txt  output of `cargo run -p sh2_battle --example us_pc_records -- <ids>` (records built like the game's `PCInit`)
  IDS          comma list of PC ids in party order, e.g. 0,5,6,0xb  (0 Yuri 1 Blanca 2 Gepetto 3 Lucia 4 Anastasia 5 Karin
               6 Joachim 7 Young Swordsman 8 Ouka 9 Hien 0xa Raiden 0xb Nicolai)
  --fill-equip N   give N of every named weapon / armour / accessory (names listed in RECORDS.txt)
  --items          consumable counts, e.g. 1=5,13=3 (item ids as in `us_menu_dump`)
  --battle K       members that fight (party set +0x11), default min(len, 3)

Addresses (slot 8, AP_02_U, found 2026-10-14 by scanning for the bag and the party set; re-check after other states):
  BTL0 (`BtlSaveSec`, retail layout `sh2_menu::save::retail_btl`) = 0x100130, active bag byte +2;
  MENU = 0x102d2c: +0x80 current party set, +0x82 joined mask (bit per PC id), sets of 0x20 bytes from +0x84
  ({name[15], count, battle_max, battle_count, members[8], ...}).
New members' equipped gear is also counted into the inventory (`AddEquip`), so the Equipment page's "owned - worn" stays right.
"""
import sys, dbg

BTL0, MENU = 0x100130, 0x102d2c
PC_BASE, SLOTS = 0x3c, 0x10bc
ITEMS, WEAPONS, ARMOR, ACCS, BAG = 0xabc, 0xb2c, 0xb8c, 0xbbc, 0x200


def parse(path):
    recs, slots, names = {}, {}, {}
    cur = None
    for l in open(path, encoding="utf8"):
        s = l.strip()
        if l.startswith("pc 0x"):
            cur = int(l.split()[1], 16)
        elif s.startswith("rec "):
            recs[cur] = bytes.fromhex(s.split()[1])
        elif s.startswith("slots "):
            slots[cur] = bytes.fromhex(s.split()[1])
        elif s.split(":")[0] in ("weapon", "armor", "accessory"):
            kind, rest = s.split(":", 1)
            names[kind] = [int(t.split("=")[0], 16) for t in rest.split(", ") if "=" in t]
    return recs, slots, names


def main():
    a = sys.argv[1:]
    recs, slots, names = parse(a[0])
    ids = [int(x, 0) for x in a[1].split(",")]
    opt = dict(zip(a[2::2], a[3::2]))
    d = dbg.Dbg()
    w = lambda addr, b: d.send(cmd="write_memory", cpu="ee", address="0x%x" % addr, data=bytes(b).hex())
    bag = d.mem(BTL0 + 2, 1)[0] * BAG
    joined = int.from_bytes(d.mem(MENU + 0x82, 2), "little")
    for pc in ids:
        o = BTL0 + PC_BASE + pc * 0xc0
        if d.mem(o, 1)[0] & 1:
            continue  # already created: keep the live record
        r = recs[pc]
        w(o, r)
        w(BTL0 + SLOTS + pc * 0x10, slots[pc])
        for base, idx in ((WEAPONS, r[0x2d]), (ARMOR, r[0x2e]), (ACCS, r[0x2f]), (ACCS, r[0x30]), (ACCS, r[0x31])):
            if idx < 0x80:
                c = BTL0 + base + bag + idx
                w(c, [min(99, d.mem(c, 1)[0] + 1)])
        print("created pc", hex(pc))
    for pc in ids:
        joined |= 1 << (pc & 15)
    w(MENU + 0x82, joined.to_bytes(2, "little"))
    cur = d.mem(MENU + 0x80, 1)[0]
    so = MENU + 0x84 + cur * 0x20
    st = bytearray(d.mem(so, 0x20))
    st[0xf] = len(ids)
    st[0x11] = int(opt.get("--battle", min(len(ids), 3)))
    st[0x12:0x1a] = bytes(ids + [0xff] * (8 - len(ids)))
    w(so, st)
    print("party set", cur, "=", [hex(i) for i in ids], "joined mask", hex(joined))
    if "--fill-equip" in opt:
        n = int(opt["--fill-equip"])
        for kind, base in (("weapon", WEAPONS), ("armor", ARMOR), ("accessory", ACCS)):
            for idx in names.get(kind, []):
                c = BTL0 + base + bag + idx
                w(c, [max(n, d.mem(c, 1)[0])])
        print("equipment bags filled with", n)
    if "--items" in opt:
        for kv in opt["--items"].split(","):
            i, n = (int(x, 0) for x in kv.split("="))
            w(BTL0 + ITEMS + bag + i, [n])
        print("items set", opt["--items"])


if __name__ == "__main__":
    main()
