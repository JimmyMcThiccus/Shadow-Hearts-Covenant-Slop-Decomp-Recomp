import socket, json, time, struct
import inst

class DebugServer:
    def __init__(s, port=21512):
        s.s = socket.create_connection(("127.0.0.1", port), timeout=5); s.s.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1); s.buf=b""
    def send(s, **kw):
        s.s.sendall((json.dumps(kw)+"\n").encode())
        while b"\n" not in s.buf:
            c = s.s.recv(65536)
            if not c: raise EOFError
            s.buf += c
        line, s.buf = s.buf.split(b"\n", 1)
        return json.loads(line)
    def mem(s, addr, n):
        r = s.send(cmd="read_memory", cpu="ee", address="0x%x" % addr, length=n)
        if not r.get("ok"): raise RuntimeError(r)
        return bytes.fromhex(r["hex"])
    def u32(s, a): return struct.unpack("<I", s.mem(a, 4))[0]

class Pine:
    """PINE client with the subset of the DebugServer interface the live tools use (status / read_memory / write_memory).
    For the portable instances, which have no DebugServer.  Deliberately no save / load state commands."""
    def __init__(s, port):
        s.s = socket.create_connection(("127.0.0.1", port), timeout=5); s.s.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
    def _call(s, body, reply_len):
        s.s.sendall(struct.pack("<I", 4 + len(body)) + body)
        buf = b""
        while len(buf) < 4 or len(buf) < struct.unpack("<I", buf[:4])[0]:
            c = s.s.recv(65536)
            if not c: raise EOFError
            buf += c
        if buf[4] != 0: raise RuntimeError("PINE call failed")
        return buf[5:5 + reply_len]
    def mem(s, addr, n):
        out = b""
        a, end = addr & ~7, addr + n
        while a < end:                      # batched 64-bit reads, <= 4096 per message
            k = min((end - a + 7) // 8, 4096)
            out += s._call(b"".join(struct.pack("<BI", 3, a + 8 * i) for i in range(k)), 8 * k)
            a += 8 * k
        off = addr & 7
        return out[off:off + n]
    def write(s, addr, data):
        for i in range(0, len(data), 4096):
            chunk = data[i:i + 4096]
            s._call(b"".join(struct.pack("<BIB", 4, addr + i + j, b) for j, b in enumerate(chunk)), 0)
    def u32(s, a): return struct.unpack("<I", s.mem(a, 4))[0]
    def send(s, cmd, **kw):
        if cmd == "read_memory":
            return {"ok": True, "hex": s.mem(int(str(kw["address"]), 0), int(kw["length"])).hex()}
        if cmd == "write_memory":
            s.write(int(str(kw["address"]), 0), bytes.fromhex(kw["data"])); return {"ok": True}
        if cmd == "status":
            st = struct.unpack("<I", s._call(b"\x0f", 4))[0]
            return {"ok": True, "data": {"alive": True, "paused": st == 1, "pine_status": st}}
        raise RuntimeError(f"{cmd!r} needs the DebugServer (main instance only); PINE copies support read_memory / write_memory / status")

def Dbg(port=None):
    """DebugServer on the main instance, PINE on the portable copies (SH2_PCSX2_INST, see inst.py)."""
    if port is not None: return DebugServer(port)
    return DebugServer(inst.debug_port()) if inst.debug_port() else Pine(inst.pine_port())

if __name__ == "__main__":
    d = Dbg()
    t0 = time.time(); print(inst.name(), d.send(cmd="status")); print((time.time()-t0)*1000, "ms")
    t0 = time.time(); print(hex(d.u32(0xaffa5c)));
    t0 = time.time()
    for _ in range(200): d.mem(0xb00090, 16)
    print("200 reads", (time.time()-t0)*1000, "ms")
