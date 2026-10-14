/* decomp/H/BtlWin.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 2 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0058c720  __dt__6BtlWinFv
 * C++: BtlWin::__dt()
 * size: 0x7c bytes
 * --------------------------------------------------------------------------- */
int __dt__6BtlWinFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__10MenuWindowFv(param_1 + 0x4c,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xc,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058c7a0  __ct__6BtlWinFv
 * C++: BtlWin::__ct()
 * size: 0x40 bytes
 * --------------------------------------------------------------------------- */
int __ct__6BtlWinFv(int param_1)

{
  __ct__8FontDrawFv(param_1 + 0xc);
  __ct__10MenuWindowFv(param_1 + 0x4c);
  return param_1;
}

