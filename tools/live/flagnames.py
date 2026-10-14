"""Story / side-quest script flags of the US retail game, named after the debug map's Flag management pages (DB_00_U event script,
decoded 2026-10-14; notes/integration/debug_menu.md).  Flag n = bit n%32 of u32 word n/32 of the CScript register file.

Live register file: [0x43fd28] -> CScript (vtable 0x4392b0) -> +0x1c ScriptWork -> +0x44 registers (0x200 words).
"""
import struct

CSCRIPT_PTR = 0x43FD28
CSCRIPT_VTABLE = 0x4392B0
N_REGS = 0x200

FIRST = ["Opening", "Apoina part A", "Domremy", "Ardennes Forest", "Paris", "Louvre 1", "Wine cellar", "Louvre 2", "Southampton",
         "Ronda mine", "Wales 1", "Firenze 1", "Manmaria Island", "Firenze 2",
         "SG Italy branch", "Firenze 3", "Nemeton ruins", "Firenze 4", "Cannes", "Sainte-Marguerite", "Cannes 2", "Wales 2",
         "Hermitage 1", "Petrograd 1", "Hermitage 2", "Petrograd 2", "Goreme Valley", "Mirror castle",
         "Goreme Valley 2", "Corridor of the dead", "Hermitage 3", "Idar Flamme", "Apoina Tower 2", "Graveyard"]
SECOND = ["Second-half opening", "Red-brick warehouse", "Yokohama 1", "Battleship Mikasa 1", "Todo lab 1", "Battleship Mikasa 2",
          "Yokohama 2", "Foreign cemetery 1", "The other world", "Muhyoan 1", "Nihonbashi 1", "Todo lab 2", "Muhyoan 2", "Nihonbashi 2",
          "Forest of wind 1", "Inugami village 1", "Mt. Fuji (Fushi)", "Graveyard 2", "Inugami village 2", "Foreign cemetery 2",
          "Azabu Kurayamizaka mansion", "Inugami village 3", "Queen's garden", "Wales 3", "Inugami village 4", "Last dungeon"]
HIDDEN = ["Killing Stone", "Doll house", "Schwarzwald", "Wakuraba (cut content)", "Nemeton depths", "Ring Tower"]
WOLF = ["Tetsu", "Terry", "Jerome", "Henri", "Philip", "R3", "Necross", "Triple Star", "Kibolin", "Eleonore", "Matsunaga", "Robo",
        "Henri (2nd)", "Robo (2nd)", "Phantom Wolf"]
APPEAR = ["Professor 1", "Sailor Serge: start", "Sailor Serge: end", "Soldier: start", "Soldier: end", "Crybaby Katsuna: start",
          "Crybaby Katsuna: end", "Mandran: start", "Mandran: end", "Professor 2 (a)", "Professor 2 (b)", "Doris",
          "Hero and the dancer (a)", "Hero and the dancer (b)", "I am a dog", "Blue-eyed Tatsutahime", "Quiz 1: Mikasa",
          "Quiz 2: Yokohama", "Quiz 3: clear"]
GRAVE = ["Lost girl (a)", "Lost girl (b)", "What are you looking for? (a)", "What are you looking for? (b)",
         "Yuri, Karin and Jeanne (a)", "Yuri, Karin and Jeanne (b)", "Release of power (a)", "Release of power (b)",
         "Truth of the curse (a)", "Truth of the curse (b)", "Vanished Jeanne (a)", "Vanished Jeanne (b)", "Memories (a)",
         "Memories (b)", "Soon (a)", "Soon (b)", "The answer (a)", "The answer (b)"]

CATEGORIES = [
    ("First half", [(8 + i, n) for i, n in enumerate(FIRST)]),
    ("Second half", [(0x3C + i, n) for i, n in enumerate(SECOND)]),
    ("Hidden dungeons", [(0x64 + i, n) for i, n in enumerate(HIDDEN)]),
    ("Wolfbout", [(0xA0 + i, n) for i, n in enumerate(WOLF)]),
    ("Appearances", [(0x29D0 + i, n) for i, n in enumerate(APPEAR)] + [(0x54, "Last dungeon appears"),
                                                                        (0x29FE, "Trade sequence failed")]),
    ("Graveyard", [(0x29E8 + i, n) for i, n in enumerate(GRAVE)]),
]
NAMES = {f: "%s: %s" % (cat, n) for cat, rows in CATEGORIES for f, n in rows}

# byte counters in the register file (byte offset): Ring Soul visits (typed register 0x1539), secret-art books (reg8 0x18)
COUNTERS = [("Ring Soul visits", 0x539, 14), ("Secret-art books", 0x18, 10)]


def register_file(d):
    """Address of the live register file, or None (no field script, e.g. in battle / on the world map)."""
    u = lambda a: struct.unpack("<I", d.mem(a, 4))[0]
    cs = u(CSCRIPT_PTR)
    if not 0x100000 <= cs < 0x2000000 or u(cs + 0x14) != CSCRIPT_VTABLE:
        return None
    sw = u(cs + 0x1C)
    if not 0x100000 <= sw < 0x2000000:
        return None
    rg = u(sw + 0x44)
    return rg if 0x100000 <= rg < 0x2000000 else None


# Debug map Circle + R3 > "Experiment" (実験, DB_00_U script 0xf7d8): jumps to a map whose name is encoded in script register word
# 0x64 (byte 0x190 of the register file): v = L1*1_000_000 + L2*10_000 + D1*1000 + D2*100 + S, letters 0 = 'A', S 0/1/2 = suffix
# 'U'/'N'/'?', S >= 3 = '_DB' (name "%c%c_%d%d_DB").  Register 0 gives "AA_00_U", which does not exist (black screen).
WARP_REG = 0x64
SUFFIX = "UN?"


def encode_map(name):
    """'AP_02_U' -> 150200, 'AP_00_DB' -> 150003; None if the name does not fit the scheme."""
    n = name.strip().upper()
    if len(n) < 7 or n[2] != "_" or n[5] != "_" or not (n[0].isalpha() and n[1].isalpha() and n[3:5].isdigit()):
        return None
    v = (ord(n[0]) - 65) * 1_000_000 + (ord(n[1]) - 65) * 10_000 + int(n[3]) * 1000 + int(n[4]) * 100
    suf = n[6:]
    if suf == "DB":
        return v + 3
    if len(suf) == 1 and suf in SUFFIX:
        return v + SUFFIX.index(suf)
    return None


def decode_map(v):
    a, v = divmod(v, 1_000_000); b, v = divmod(v, 10_000); c, v = divmod(v, 1000); d, s = divmod(v, 100)
    return "%c%c_%d%d_%s" % (65 + a, 65 + b, c, d, "DB" if s > 2 else SUFFIX[s])
