"""Which PCSX2 instance the live tools talk to.

Set SH2_PCSX2_INST to pick one (default "main"):
  main  user's PCSX2 (PCSX2-MCP-v1.0.0-win64): DebugServer 21512 + PINE 28011 (PINE held by the pcsx2 MCP)
  2/3   portable copies, US disc 1 (booted into their own copy of slot 1 = debug map): PINE 28012 / 28013, no DebugServer
  4     portable copy, US disc 2: PINE 28014, no DebugServer
The copies live in "Shadow Hearts 2 Decomp\\pcsx2-instances\\instN" (launch-instances.bat there).  Lock file per instance:
notes/integration/locks/pcsx2-<inst>.lock.
"""
import os, subprocess

INSTANCES = {
    "main": ("PCSX2-MCP-v1.0.0-win64\\pcsx2-qt.exe", 28011, 21512),
    "2": ("pcsx2-instances\\inst2\\pcsx2-qt.exe", 28012, None),
    "3": ("pcsx2-instances\\inst3\\pcsx2-qt.exe", 28013, None),
    "4": ("pcsx2-instances\\inst4\\pcsx2-qt.exe", 28014, None),
}

def name():
    n = os.environ.get("SH2_PCSX2_INST", "main")
    if n not in INSTANCES: raise SystemExit(f"SH2_PCSX2_INST={n!r}: expected one of {', '.join(INSTANCES)}")
    return n

def pine_port(): return INSTANCES[name()][1]
def debug_port(): return INSTANCES[name()][2]

def pid():
    """PID of the selected instance's pcsx2-qt.exe (matched by executable path, never 'the first pcsx2')."""
    suffix = INSTANCES[name()][0].lower()
    out = subprocess.check_output(["powershell", "-NoProfile", "-Command",
        "Get-CimInstance Win32_Process -Filter \"Name='pcsx2-qt.exe'\" | ForEach-Object { \"$($_.ProcessId)|$($_.ExecutablePath)\" }"], text=True)
    for line in out.splitlines():
        p, _, path = line.strip().partition("|")
        if path.lower().endswith(suffix): return int(p)
    raise SystemExit(f"PCSX2 instance {name()} ({suffix}) is not running")
