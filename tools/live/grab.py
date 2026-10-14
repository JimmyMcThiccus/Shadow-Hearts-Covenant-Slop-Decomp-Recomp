import ctypes, ctypes.wintypes as wt, time
from PIL import Image
import keys
u = ctypes.windll.user32; g = ctypes.windll.gdi32
u.SetProcessDpiAwarenessContext(ctypes.c_void_p(-4))
class BMI(ctypes.Structure):
    _fields_ = [("biSize", wt.DWORD), ("biWidth", wt.LONG), ("biHeight", wt.LONG), ("biPlanes", wt.WORD), ("biBitCount", wt.WORD),
                ("biCompression", wt.DWORD), ("biSizeImage", wt.DWORD), ("x", wt.LONG), ("y", wt.LONG), ("a", wt.DWORD), ("b", wt.DWORD)]
def grab():
    u.SetThreadDpiAwarenessContext(ctypes.c_void_p(-4))
    if keys.H is None: keys.H = keys._hwnd()
    h = keys.H; r = wt.RECT(); u.GetWindowRect(h, ctypes.byref(r)); w, ht = r.right-r.left, r.bottom-r.top
    dc = u.GetWindowDC(h); mdc = g.CreateCompatibleDC(dc); bm = g.CreateCompatibleBitmap(dc, w, ht); g.SelectObject(mdc, bm)
    u.PrintWindow(h, mdc, 2)
    bmi = BMI(ctypes.sizeof(BMI), w, -ht, 1, 32, 0, 0, 0, 0, 0, 0); buf = ctypes.create_string_buffer(w*ht*4)
    g.GetDIBits(mdc, bm, 0, ht, buf, ctypes.byref(bmi), 0)
    g.DeleteObject(bm); g.DeleteDC(mdc); u.ReleaseDC(h, dc)
    im = Image.frombuffer("RGBA", (w, ht), buf, "raw", "BGRA", 0, 1).convert("RGB")
    return im.crop((12, 90, w-12, ht-48))
if __name__ == "__main__":
    t=time.perf_counter(); im=grab(); print(im.size, time.perf_counter()-t); im.save("g.png")
