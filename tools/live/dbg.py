import socket, json, time, struct
class Dbg:
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
if __name__ == "__main__":
    d = Dbg()
    t0 = time.time(); print(d.send(cmd="status")); print((time.time()-t0)*1000, "ms")
    t0 = time.time(); print(hex(d.u32(0xaffa5c))); 
    t0 = time.time()
    for _ in range(200): d.mem(0xb00090, 16)
    print("200 reads", (time.time()-t0)*1000, "ms")
