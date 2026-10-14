/* decomp/H/MenuObj.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 2 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x005bb0e0  SetRendering__7MenuObjFUc
 * C++: MenuObj::SetRendering(uchar)
 * size: 0x38 bytes
 * --------------------------------------------------------------------------- */
void SetRendering__7MenuObjFUc(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) & 0xfe | param_2 & 1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005bb120  UpdateEnv__7MenuObjFv
 * C++: MenuObj::UpdateEnv()
 * size: 0x60 bytes
 * --------------------------------------------------------------------------- */
void UpdateEnv__7MenuObjFv(int param_1)

{
  ulong uVar1;
  
  uVar1 = (ulong)*(byte *)(param_1 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(param_1 + 0x11) = (char)uVar1;
  *(byte *)(param_1 + 0x10) =
       *(byte *)(param_1 + 0x10) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
  return;
}

