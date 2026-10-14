/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CFModel   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CFModel.md).
 */

/* JP: 0x004cacf0  CFModel::SetOwner(CFieldModel*)   [SetOwner__7CFModelFP11CFieldModel]  size=0x24 */
void SetOwner__7CFModelFP11CFieldModel(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x4b0) = param_2;
  return;
}

/* JP: 0x004cc280  CFModel::CFModel()   [__ct__7CFModelFv]  size=0x4c */
int __ct__7CFModelFv(int param_1)

{
  __ct__5ModelFv(param_1);
  *(undefined1 **)(param_1 + 0x10) = &__vt__7CFModel;
  *(undefined4 *)(param_1 + 0x1c) = 0x4096b0;
  return param_1;
}

/* JP: 0x004cc2d0  CFModel::~CFModel()   [__dt__7CFModelFv]  size=0x84 */
int __dt__7CFModelFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x10) = &__vt__7CFModel;
    *(undefined4 *)(param_1 + 0x1c) = 0x4096b0;
    __dt__5ModelFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004cc360  CFModel::getPacket()   [getPacket__7CFModelFv]  size=0x7c */
void getPacket__7CFModelFv(int param_1)

{
  long lVar1;
  
  lVar1 = isPaused__4CAppFv(app__4CApp);
  if (((lVar1 == 0) && (sys__6CField != 0)) && (lVar1 = isPaused__6CFieldFv(sys__6CField), lVar1 == 2)
     ) {
    (**(code **)(*(int *)(param_1 + 0x10) + 0x28))(param_1,0);
  }
  getPacket__5ModelFv(param_1);
  return;
}

/* JP: 0x004cc410  CFModel::EventCallBack(const char*, const char*, int, int, unsigned int)   [EventCallBack__7CFModelFPCcPCciiUi]  size=0x74 */
void EventCallBack__7CFModelFPCcPCciiUi
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6)

{
  EventCallBack__11CFieldModelFPCcPCciiUi
            (*(undefined4 *)(param_1 + 0x4b0),param_2,param_3,param_4,param_5,param_6);
  EventCallBack__5ModelFPCcPCciiUi(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

/* JP: 0x004cc490  CFModel::MotionEndCallBack(const char*)   [MotionEndCallBack__7CFModelFPCc]  size=0x34 */
void MotionEndCallBack__7CFModelFPCc(int param_1,undefined4 param_2)

{
  MotionEndCallBack__11CFieldModelFPCc(*(undefined4 *)(param_1 + 0x4b0),param_2);
  return;
}

/* JP: 0x004cc4d0  CFModel::TranseCallBack(const FVector&, FVector)   [TranseCallBack__7CFModelFRC7FVector7FVector]  size=0x58 */
void TranseCallBack__7CFModelFRC7FVector7FVector
               (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined8 uVar1;
  undefined1 auStack_50 [16];
  undefined4 uStack_40;
  int iStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  uStack_40 = param_1;
  iStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  uVar1 = __ct__7FVectorFRC7FVector(auStack_50,param_4);
  TransCallBack__11CFieldModelFRC7FVector7FVector
            (uStack_40,*(undefined4 *)(iStack_30 + 0x4b0),uStack_20,uVar1);
  return;
}

/* JP: 0x004ce020  CFModel::~CFModel()   [@20@__dt__7CFModelFv]  size=0x8 */
int _20___dt__7CFModelFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x14;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__7CFModel;
    *(undefined4 *)(param_1 + 8) = 0x4096b0;
    __dt__5ModelFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
