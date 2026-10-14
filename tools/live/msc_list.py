"""Linear listing of event-script code (`CScript` byte grammar, see port/crates/sh2_script/src/disasm.rs and notes/E/script_vm.md).

usage: python msc_list.py MAP.code START END [MAP.data]
Prints one line per opcode from START to END (hex offsets).  Builtins a0..af are named; 0xbc.. are `ex.sub(nargs)`.
Data-address pushes (0x15) show the Shift-JIS string at that data offset when MAP.data is given.
"""
import sys, struct

NAMES = {0xa0: "chain", 0xa1: "callEvent", 0xa2: "callEventDly", 0xa3: "getSysInfo", 0xa4: "setFlag", 0xa5: "clrFlag",
         0xa6: "chkFlag", 0xa7: "reg_clr", 0xaa: "wait", 0xab: "sprintf", 0xac: "get_pad", 0xad: "randomize", 0xae: "rnd",
         0xaf: "dprintf", 0x90: "jmp", 0x91: "jz", 0x92: "jnz", 0x94: "switch", 0x98: "retv", 0x99: "ret"}
LOADS = {0x20: "ld.s8", 0x21: "ld.u8", 0x22: "ld.s16", 0x23: "ld.u16", 0x24: "ld.i32", 0x25: "ld.f32", 0x26: "st8", 0x27: "st16",
         0x28: "st32"}
BIN = {0x67: "mul", 0x68: "div", 0x69: "mod", 0x6a: "add", 0x6b: "sub", 0x6c: "shl", 0x6d: "shr", 0x70: "eq", 0x71: "ne",
       0x72: "lt", 0x73: "le", 0x74: "gt", 0x75: "ge", 0x76: "and", 0x77: "or", 0x78: "xor", 0x79: "land", 0x7a: "lor"}


def main():
    code = open(sys.argv[1], "rb").read()
    start, end = int(sys.argv[2], 16), int(sys.argv[3], 16)
    data = open(sys.argv[4], "rb").read() if len(sys.argv) > 4 else b""
    u8 = lambda o: code[o]
    u16 = lambda o: struct.unpack_from("<H", code, o)[0]
    ip = start
    while ip < end:
        at, b = ip, code[ip]
        ip += 1
        s = ""
        if b >= 0xbc:
            s = "ex %02x.%02x(%d)" % (b, u8(ip), u8(ip + 1)); ip += 2
        elif b >= 0xa0:
            s = "%s(%d)" % (NAMES.get(b, "b%02x" % b), u8(ip)); ip += 1
        elif b in (0x90, 0x91, 0x92):
            s = "%s %#x" % (NAMES[b], u16(ip)); ip += 2
        elif b == 0x94:
            s = "switch tbl %#x" % u16(ip); ip += 2
        elif b in (0x98, 0x99):
            s = NAMES[b]
        elif 0x80 <= b <= 0x89 or 0x60 <= b <= 0x63:
            m = u8(ip); ip += 1
            if m & 0xC0 == 0xC0: ip += 1
            s = "opassign %02x mode %02x" % (b, m)
        elif b in (0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f):
            s = "buf/idx %02x" % b
            if b == 0x8b: ip += 1
            if b == 0x8d: ip += 2
        elif b in BIN:
            s = BIN[b]
        elif b in LOADS:
            s = LOADS[b]
        elif 0x20 <= b < 0x80:
            s = "op %02x" % b
        elif b == 0x00: s = "end"
        elif b == 0x01: s = "reset"
        elif b in (0x04, 0x05, 0x06, 0x07, 0x08, 0x09): s = "push %s" % {4: '""', 5: -1, 6: 0, 7: 1, 8: 2, 9: 4}[b]
        elif b == 0x0a: s = "push %#x" % u8(ip); ip += 1
        elif b == 0x0b: s = "push -%#x" % (256 - u8(ip)); ip += 1
        elif b == 0x0c: s = "push %#x" % u16(ip); ip += 2
        elif b == 0x0d: s = "push %d" % (u16(ip) - 0x10000); ip += 2
        elif b in (0x0e, 0x0f): s = "push %#x" % struct.unpack_from("<I", code, ip)[0]; ip += 4
        elif 0x10 <= b <= 0x13: s = "reg%d %#x" % ((8, 16, 32, 'f')[b - 0x10], u8(ip)); ip += 1
        elif b == 0x14: s = "regT %#x" % u16(ip); ip += 2
        elif b == 0x15:
            o = u16(ip); ip += 2
            t = data[o:data.find(b"\0", o)] if data and o < len(data) else b""
            try: t = t.decode("shift_jis")
            except Exception: t = t.hex()
            s = "data %#x %s" % (o, t[:40])
        elif b == 0x16: s = "code %#x" % u16(ip); ip += 2
        elif b == 0x18: s = "bss %#x" % u16(ip); ip += 2
        elif b == 0x19: s = "local %#x" % u8(ip); ip += 1
        elif b == 0x1a: s = "local %#x" % u16(ip); ip += 2
        elif b == 0x1b: s = "callu %#x (%d)" % (u16(ip), u8(ip + 2)); ip += 3
        else: s = "?? %02x" % b
        print("%05x: %s" % (at, s))


if __name__ == "__main__":
    main()
