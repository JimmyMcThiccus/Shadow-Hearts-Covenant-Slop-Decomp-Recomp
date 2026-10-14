import ctypes, ctypes.wintypes as wt, time, subprocess
u = ctypes.windll.user32
VK = {"K":0x4B,"L":0x4C,"I":0x49,"J":0x4A,"Return":0x0D,"Up":0x26,"Down":0x28,"Left":0x25,"Right":0x27,"W":0x57,"A":0x41,"S":0x53,"D":0x44,
      # Select, L1 / R1, L2 / R2, L3 / R3, right stick (PCSX2.ini [Pad1])
      "Backspace":0x08,"Q":0x51,"E":0x45,"1":0x31,"3":0x33,"2":0x32,"4":0x34,"T":0x54,"H":0x48,"G":0x47,"F":0x46}
def _hwnd():
    pid = int(subprocess.check_output(["powershell","-NoProfile","-Command","(Get-Process pcsx2-qt).Id"]).split()[0])
    out = []
    EP = ctypes.WINFUNCTYPE(ctypes.c_bool, wt.HWND, wt.LPARAM)
    def cb(h, l):
        p = wt.DWORD(); u.GetWindowThreadProcessId(h, ctypes.byref(p))
        if p.value == pid and u.IsWindowVisible(h):
            b = ctypes.create_unicode_buffer(256); u.GetWindowTextW(h, b, 256)
            # the game window: titled after the disc ("Shadow Hearts ..." for the US disc, Japanese for the demos), not PCSX2's own windows
            if b.value and not b.value.startswith(("PCSX2", "Debugger", "Settings", "Log Window")):
                out.append((not b.value.startswith("Shadow Hearts"), h))
        return True
    u.EnumWindows(EP(cb), 0); return min(out)[1]
H = None
def _post(m, k, up):
    global H
    if H is None: H = _hwnd()
    vk = VK[k]; sc = u.MapVirtualKeyW(vk, 0)
    ext = (1 << 24) if 0x25 <= vk <= 0x28 else 0
    lp = 1 | (sc << 16) | ext | ((1<<30 | 1<<31) if up else 0)
    u.PostMessageW(H, m, vk, lp)
def down(k): _post(0x100, k, False)
def up(k): _post(0x101, k, True)
def tap(k, hold=0.08): down(k); time.sleep(hold); up(k)
