/* decomp/H/BMCLUT.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 1 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0051c130  __ct__6BMCLUTFv
 * C++: BMCLUT::__ct()
 * size: 0x40 bytes
 * --------------------------------------------------------------------------- */
int __ct__6BMCLUTFv(int param_1)

{
  int iVar1;
  
  iVar1 = param_1;
  do {
    iVar1 = iVar1 + 4;
  } while (iVar1 != param_1 + 0x400);
  return param_1;
}

