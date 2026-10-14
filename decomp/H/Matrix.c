/* decomp/H/Matrix.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 1 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0044b470  UnitMatrix__6MatrixFv
 * C++: Matrix::UnitMatrix()
 * size: 0x24 bytes
 * --------------------------------------------------------------------------- */
void UnitMatrix__6MatrixFv(undefined1 (*param_1) [16])

{
  undefined1 auVar1 [16];
  undefined1 in_vf0 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  
  auVar2 = _vmr32(in_vf0);
  auVar3 = _vmr32(auVar2);
  auVar4 = _vmr32(auVar3);
  auVar1 = _sqc2(in_vf0);
  param_1[3] = auVar1;
  auVar1 = _sqc2(auVar2);
  param_1[2] = auVar1;
  auVar1 = _sqc2(auVar3);
  param_1[1] = auVar1;
  auVar1 = _sqc2(auVar4);
  *param_1 = auVar1;
  return;
}

