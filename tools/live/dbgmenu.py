"""Walk the built-in debug menu of the debug map (user's save): open it with a short X, follow a path of row indices, screenshot
the page that opens, then close everything with Circle.  Nothing is confirmed past the last index, so pages that *do* something
(map jump, battle player, movie player) only show their list.

usage: python dbgmenu.py OUT.png 2        main menu row 2 (Items / params) -> screenshot of its page
       python dbgmenu.py OUT.png 1 7      Party settings -> Equipment change
       python dbgmenu.py OUT.png          just the main menu
Karin must face north (where the menu was first opened); X opens the menu with a 0.05 s press (a 0.1 s press also confirms
the remembered row).  Circle closes the menu from the first level but only steps back one level on deeper pages (the Items page),
so the script presses it once per level plus one.  If a run is interrupted, check the screen before the next one: a page left open
eats the next X / Down presses (2026-10-14: that walked into the Items quantity prompt and set Thera Seed to 98).
"""
import sys, time
import keys, grab


def main():
    out = sys.argv[1]
    path = [int(x) for x in sys.argv[2:]]
    keys.tap("K", 0.05)
    time.sleep(0.9)
    for idx in path:
        for _ in range(idx):
            keys.tap("Down", 0.1)
            time.sleep(0.3)
        keys.tap("K", 0.1)
        time.sleep(0.9)
    grab.grab().save(out)
    for _ in range(len(path) + 1):
        keys.tap("L", 0.1)
        time.sleep(0.8)


if __name__ == "__main__":
    main()
