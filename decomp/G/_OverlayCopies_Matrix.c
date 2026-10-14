/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: Matrix   functions: 12
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_Matrix.md).
 */

/* JP: 0x00431fe0  Matrix::GetPos()   [GetPos__6MatrixFv]  size=0x1c */
int GetPos__6MatrixFv(int param_1)

{
  return param_1 + 0x30;
}

/* JP: 0x00432620  Matrix::RotYMatrix(float)   [RotYMatrix__6MatrixFf]  size=0x34 */
void RotYMatrix__6MatrixFf(undefined4 param_1,undefined4 param_2)

{
  sceVu0RotMatrixY(param_1,param_2,param_2);
  return;
}

/* JP: 0x00432660  Matrix::Matrix()   [__ct__6MatrixFv]  size=0x2c */
undefined4 __ct__6MatrixFv(undefined4 param_1)

{
  UnitMatrix__6MatrixFv(param_1);
  return param_1;
}

/* JP: 0x00432690  Matrix::UnitMatrix()   [UnitMatrix__6MatrixFv]  size=0x24 */
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

/* JP: 0x00434a20  Matrix::__as(const Matrix&)   [__as__6MatrixFRC6Matrix]  size=0x5c */
undefined4 * __as__6MatrixFRC6Matrix(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  uVar3 = param_2[3];
  *param_1 = *param_2;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  param_1[3] = uVar3;
  uVar1 = param_2[5];
  uVar2 = param_2[6];
  uVar3 = param_2[7];
  param_1[4] = param_2[4];
  param_1[5] = uVar1;
  param_1[6] = uVar2;
  param_1[7] = uVar3;
  uVar1 = param_2[9];
  uVar2 = param_2[10];
  uVar3 = param_2[0xb];
  param_1[8] = param_2[8];
  param_1[9] = uVar1;
  param_1[10] = uVar2;
  param_1[0xb] = uVar3;
  uVar1 = param_2[0xd];
  uVar2 = param_2[0xe];
  uVar3 = param_2[0xf];
  param_1[0xc] = param_2[0xc];
  param_1[0xd] = uVar1;
  param_1[0xe] = uVar2;
  param_1[0xf] = uVar3;
  return param_1;
}

/* JP: 0x00434aa0  Matrix::RotMatrix(const FVector&)   [RotMatrix__6MatrixFRC7FVector]  size=0x34 */
void RotMatrix__6MatrixFRC7FVector(undefined4 param_1,undefined4 param_2)

{
  sceVu0RotMatrix(param_1,param_1,param_2);
  return;
}

/* JP: 0x004a80a0  Matrix::GetAt()   [GetAt__6MatrixFv]  size=0x1c */
int GetAt__6MatrixFv(int param_1)

{
  return param_1 + 0x20;
}

/* JP: 0x004aa660  Matrix::RotXMatrix(float)   [RotXMatrix__6MatrixFf]  size=0x34 */
void RotXMatrix__6MatrixFf(undefined4 param_1,undefined4 param_2)

{
  sceVu0RotMatrixX(param_1,param_2,param_2);
  return;
}

/* JP: 0x004beec0  Matrix::TransMatrix(const FVector&)   [TransMatrix__6MatrixFRC7FVector]  size=0x18 */
void TransMatrix__6MatrixFRC7FVector(int param_1,undefined1 (*param_2) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  
  auVar1 = _lqc2(*param_2);
  auVar2 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x30));
  auVar1 = _vadd(auVar2,auVar1);
  auVar1 = _sqc2(auVar1);
  *(undefined1 (*) [16])(param_1 + 0x30) = auVar1;
  return;
}

/* JP: 0x004beee0  Matrix::RotZMatrix(float)   [RotZMatrix__6MatrixFf]  size=0x34 */
void RotZMatrix__6MatrixFf(undefined4 param_1,undefined4 param_2)

{
  sceVu0RotMatrixZ(param_1,param_2,param_2);
  return;
}

/* JP: 0x004c6e70  Matrix::SetPos(const FVector&)   [SetPos__6MatrixFRC7FVector]  size=0x34 */
void SetPos__6MatrixFRC7FVector(undefined4 param_1,undefined4 param_2)

{
  SetVector__6MatrixFiRC7FVector(param_1,3,param_2);
  return;
}

/* JP: 0x004c6eb0  Matrix::SetVector(int, const FVector&)   [SetVector__6MatrixFiRC7FVector]  size=0x40 */
void SetVector__6MatrixFiRC7FVector(int param_1,int param_2,undefined4 param_3)

{
  __as__7FVectorFRC7FVector(param_1 + param_2 * 0x10,param_3);
  return;
}
