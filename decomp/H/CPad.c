/* decomp/H/CPad.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 2 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0057bff0  GetAnalogStickR__4CPadCFv
 * C++: CPad::GetAnalogStickR()
 * size: 0x34 bytes
 * --------------------------------------------------------------------------- */
int GetAnalogStickR__4CPadCFv(int param_1)

{
  return *(int *)(*(int *)(param_1 + 4) * 4 + 0x40ac00) + 0x88;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057c030  GetAnalogStickL__4CPadCFv
 * C++: CPad::GetAnalogStickL()
 * size: 0x34 bytes
 * --------------------------------------------------------------------------- */
int GetAnalogStickL__4CPadCFv(int param_1)

{
  return *(int *)(*(int *)(param_1 + 4) * 4 + 0x40ac00) + 0x78;
}

