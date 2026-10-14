"""Live story-flag editor for Shadow Hearts: Covenant (US) running in PCSX2 (DebugServer on 127.0.0.1:21512).

usage: python flag_editor.py

Tabs list the named flags of the debug map's Flag management pages (flagnames.py): tick / untick to set / clear the flag in the
running game at once.  "Counters" edits the Ring Soul / secret-art book bytes, "Raw" sets any flag number and lists everything set.
The register file is found through the CScript pointer chain on every refresh, so it follows map changes; outside the field (battle,
world map, title) the editor shows "no field script" and writes nothing.  Changes live in RAM only: save in-game (or a save state)
to keep them, reload a state to undo them.
"""
import struct
import tkinter as tk
from tkinter import ttk, messagebox

import dbg
from flagnames import CATEGORIES, COUNTERS, NAMES, N_REGS, WARP_REG, decode_map, encode_map, register_file

POLL_MS = 1000


class Live:
    """DebugServer access with reconnects."""

    def __init__(self):
        self.d = None

    def _conn(self):
        if self.d is None:
            self.d = dbg.Dbg()
        return self.d

    def call(self, fn):
        try:
            return fn(self._conn())
        except Exception:
            self.d = None
            raise

    def regs(self):
        """(address, raw bytes) of the register file, or (None, None)."""
        def f(d):
            a = register_file(d)
            return (a, d.mem(a, N_REGS * 4)) if a else (None, None)
        return self.call(f)

    def write(self, addr, data):
        self.call(lambda d: d.send(cmd="write_memory", cpu="ee", address="%#x" % addr, data=bytes(data).hex()))


class Editor(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("SH2 story flags (PCSX2)")
        self.geometry("760x620")
        self.live = Live()
        self.addr = None
        self.raw = None
        self.vars = {}          # flag -> BooleanVar
        self.updating = False

        top = ttk.Frame(self, padding=6)
        top.pack(fill="x")
        self.status = tk.StringVar(value="connecting ...")
        ttk.Label(top, textvariable=self.status).pack(side="left")
        self.auto = tk.BooleanVar(value=True)
        ttk.Checkbutton(top, text="Auto refresh", variable=self.auto).pack(side="right")
        ttk.Button(top, text="Refresh", command=self.refresh).pack(side="right", padx=6)

        nb = ttk.Notebook(self)
        nb.pack(fill="both", expand=True, padx=6, pady=(0, 6))
        for title, rows in CATEGORIES:
            nb.add(self._flag_tab(nb, rows), text=title)
        nb.add(self._counter_tab(nb), text="Counters")
        nb.add(self._raw_tab(nb), text="Raw")
        nb.add(self._warp_tab(nb), text="Warp")

        self.refresh()
        self.after(POLL_MS, self._tick)

    # ---------------------------------------------------------------- tabs
    def _flag_tab(self, parent, rows):
        outer = ttk.Frame(parent)
        bar = ttk.Frame(outer, padding=(4, 4))
        bar.pack(fill="x")
        ttk.Button(bar, text="Set all", command=lambda: self._set_many([f for f, _ in rows], True)).pack(side="left")
        ttk.Button(bar, text="Clear all", command=lambda: self._set_many([f for f, _ in rows], False)).pack(side="left", padx=4)
        canvas = tk.Canvas(outer, highlightthickness=0)
        sb = ttk.Scrollbar(outer, orient="vertical", command=canvas.yview)
        inner = ttk.Frame(canvas)
        inner.bind("<Configure>", lambda e: canvas.configure(scrollregion=canvas.bbox("all")))
        canvas.create_window((0, 0), window=inner, anchor="nw")
        canvas.configure(yscrollcommand=sb.set)
        canvas.pack(side="left", fill="both", expand=True)
        sb.pack(side="right", fill="y")
        half = (len(rows) + 1) // 2
        for i, (flag, name) in enumerate(rows):
            v = tk.BooleanVar(value=False)
            self.vars[flag] = v
            cb = ttk.Checkbutton(inner, text="%#06x  %s" % (flag, name), variable=v,
                                 command=lambda f=flag, var=v: self._clicked(f, var))
            cb.grid(row=i % half, column=i // half, sticky="w", padx=8, pady=1)
        return outer

    def _counter_tab(self, parent):
        f = ttk.Frame(parent, padding=10)
        self.counters = {}
        for i, (name, off, mx) in enumerate(COUNTERS):
            ttk.Label(f, text=name).grid(row=i, column=0, sticky="w", pady=4)
            v = tk.IntVar(value=0)
            self.counters[off] = v
            ttk.Spinbox(f, from_=0, to=max(mx, 255), textvariable=v, width=6).grid(row=i, column=1, padx=6)
            ttk.Button(f, text="Write", command=lambda o=off, var=v: self._write_counter(o, var)).grid(row=i, column=2)
            ttk.Label(f, text="register byte +%#x (0 = reset, max %d on the debug page)" % (off, mx)).grid(row=i, column=3, sticky="w")
        return f

    def _raw_tab(self, parent):
        f = ttk.Frame(parent, padding=8)
        bar = ttk.Frame(f)
        bar.pack(fill="x")
        ttk.Label(bar, text="Flag (hex 0x.. or decimal):").pack(side="left")
        self.raw_entry = ttk.Entry(bar, width=10)
        self.raw_entry.pack(side="left", padx=4)
        for label, val in (("Set", True), ("Clear", False)):
            ttk.Button(bar, text=label, command=lambda v=val: self._raw_set(v)).pack(side="left", padx=2)
        ttk.Button(bar, text="Toggle", command=lambda: self._raw_set(None)).pack(side="left", padx=2)
        ttk.Label(f, text="Flags set now:").pack(anchor="w", pady=(8, 2))
        self.listbox = tk.Listbox(f, font=("Consolas", 10))
        self.listbox.pack(fill="both", expand=True)
        return f

    def _warp_tab(self, parent):
        f = ttk.Frame(parent, padding=10)
        ttk.Label(f, wraplength=680, justify="left", text=(
            "Debug-map warp: sets the map register used by the debug map's Circle + R3 > 実験 (Experiment) row.  Type a map name "
            "(e.g. AP_02_U, PA_00_DB, DB_00_U), press Set, then on the DUMMY debug map press Circle + R3, go to the last row and "
            "press X.  A map that is not on the disc gives a black screen: reload a state.")).pack(anchor="w")
        bar = ttk.Frame(f)
        bar.pack(anchor="w", pady=8)
        ttk.Label(bar, text="Map:").pack(side="left")
        self.warp_entry = ttk.Entry(bar, width=12)
        self.warp_entry.insert(0, "AP_02_U")
        self.warp_entry.pack(side="left", padx=4)
        ttk.Button(bar, text="Set", command=self._warp_set).pack(side="left")
        self.warp_now = tk.StringVar(value="")
        ttk.Label(f, textvariable=self.warp_now).pack(anchor="w")
        return f

    def _warp_set(self):
        v = encode_map(self.warp_entry.get())
        if v is None:
            messagebox.showerror("Bad map name", "Use XX_nn_U / _N / _DB, e.g. AP_02_U or PA_00_DB.")
            return
        self.refresh()
        if self.addr is None:
            messagebox.showwarning("Not written", "No field script is running.")
            return
        self.live.write(self.addr + WARP_REG * 4, struct.pack("<I", v))
        self.refresh()

    # ---------------------------------------------------------------- data
    def flag(self, n):
        if self.raw is None:
            return False
        w = struct.unpack_from("<I", self.raw, (n >> 5) * 4)[0]
        return bool((w >> (n & 31)) & 1)

    def refresh(self):
        try:
            self.addr, self.raw = self.live.regs()
        except Exception as e:
            self.addr = self.raw = None
            self.status.set("PCSX2 DebugServer not reachable (%s)" % e.__class__.__name__)
            return
        if self.addr is None:
            self.status.set("Connected - no field script running (battle / world map / title?)")
            return
        n_set = sum(bin(b).count("1") for b in self.raw)
        self.warp_now.set("Warp register now: %d -> %s" % (struct.unpack_from("<I", self.raw, WARP_REG * 4)[0],
                                                           decode_map(struct.unpack_from("<I", self.raw, WARP_REG * 4)[0])))
        self.status.set("Register file at %#x - %d flags set" % (self.addr, n_set))
        self.updating = True
        for flag, v in self.vars.items():
            v.set(self.flag(flag))
        for off, v in self.counters.items():
            if self.focus_get() is None or str(self.focus_get()).find("spinbox") < 0:
                v.set(self.raw[off])
        self.listbox.delete(0, "end")
        for n in range(N_REGS * 32):
            if self.flag(n):
                self.listbox.insert("end", "%#06x  %s" % (n, NAMES.get(n, "")))
        self.updating = False

    def _tick(self):
        if self.auto.get():
            self.refresh()
        self.after(POLL_MS, self._tick)

    def _write_flags(self, changes):
        """changes: {flag: bool}.  Read-modify-write of each touched word against fresh memory."""
        self.refresh()
        if self.addr is None:
            messagebox.showwarning("Not written", "No field script is running, so there is no register file to write.")
            return
        words = {}
        for n, on in changes.items():
            words.setdefault(n >> 5, []).append((n & 31, on))
        for wi, bits in words.items():
            w = struct.unpack_from("<I", self.raw, wi * 4)[0]
            for b, on in bits:
                w = (w | (1 << b)) if on else (w & ~(1 << b))
            self.live.write(self.addr + wi * 4, struct.pack("<I", w & 0xFFFFFFFF))
        self.refresh()

    def _clicked(self, flag, var):
        if not self.updating:
            self._write_flags({flag: var.get()})

    def _set_many(self, flags, on):
        self._write_flags({f: on for f in flags})

    def _write_counter(self, off, var):
        self.refresh()
        if self.addr is None:
            return
        try:
            v = max(0, min(255, int(var.get())))
        except (tk.TclError, ValueError):
            return
        self.live.write(self.addr + off, bytes([v]))
        self.refresh()

    def _raw_set(self, on):
        try:
            n = int(self.raw_entry.get().strip(), 0)
        except ValueError:
            messagebox.showerror("Bad flag", "Enter a number like 0x54 or 84.")
            return
        if not 0 <= n < N_REGS * 32:
            messagebox.showerror("Bad flag", "Flags run from 0 to %#x." % (N_REGS * 32 - 1))
            return
        self.refresh()
        self._write_flags({n: (not self.flag(n)) if on is None else on})


if __name__ == "__main__":
    Editor().mainloop()
