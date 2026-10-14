/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CXFModel   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CXFModel.md).
 */

/* JP: 0x004cad20  CXFModel::SetOwner(CFieldModel*)   [SetOwner__8CXFModelFP11CFieldModel]  size=0x24 */
void SetOwner__8CXFModelFP11CFieldModel(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x510) = param_2;
  return;
}

/* JP: 0x004cc530  CXFModel::CXFModel()   [__ct__8CXFModelFv]  size=0x4c */
int __ct__8CXFModelFv(int param_1)

{
  __ct__7ExModelFv(param_1);
  *(undefined1 **)(param_1 + 0x10) = &__vt__8CXFModel;
  *(undefined4 *)(param_1 + 0x1c) = 0x409660;
  return param_1;
}

/* JP: 0x004cc580  CXFModel::~CXFModel()   [__dt__8CXFModelFv]  size=0x84 */
int __dt__8CXFModelFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x10) = &__vt__8CXFModel;
    *(undefined4 *)(param_1 + 0x1c) = 0x409660;
    __dt__7ExModelFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004cc610  CXFModel::getPacket()   [getPacket__8CXFModelFv]  size=0x90 */
void getPacket__8CXFModelFv(int param_1)

{
  ulong uVar1;
  long lVar2;
  
  uVar1 = isPaused__4CAppFv(app__4CApp);
  if ((uVar1 == 0) && (sys__6CField != 0)) {
    lVar2 = isPaused__6CFieldFv(sys__6CField);
    uVar1 = (ulong)(lVar2 == 2);
  }
  if (uVar1 != 0) {
    (**(code **)(*(int *)(param_1 + 0x10) + 0x28))(param_1,0);
  }
  getPacket__7ExModelFv(param_1);
  return;
}

/* JP: 0x004cc6a0  CXFModel::EventCallBack(const char*, const char*, int, int, unsigned int)   [EventCallBack__8CXFModelFPCcPCciiUi]  size=0x74 */
void EventCallBack__8CXFModelFPCcPCciiUi
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6)

{
  EventCallBack__11CFieldModelFPCcPCciiUi
            (*(undefined4 *)(param_1 + 0x510),param_2,param_3,param_4,param_5,param_6);
  EventCallBack__7ExModelFPCcPCciiUi(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

/* JP: 0x004cc720  CXFModel::MotionEndCallBack(const char*)   [MotionEndCallBack__8CXFModelFPCc]  size=0x34 */
void MotionEndCallBack__8CXFModelFPCc(int param_1,undefined4 param_2)

{
  MotionEndCallBack__11CFieldModelFPCc(*(undefined4 *)(param_1 + 0x510),param_2);
  return;
}

/* JP: 0x004cc760  CXFModel::TranseCallBack(const FVector&, FVector)   [TranseCallBack__8CXFModelFRC7FVector7FVector]  size=0x58 */
void TranseCallBack__8CXFModelFRC7FVector7FVector
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
            (uStack_40,*(undefined4 *)(iStack_30 + 0x510),uStack_20,uVar1);
  return;
}

/* JP: 0x004ce030  CXFModel::~CXFModel()   [@20@__dt__8CXFModelFv]  size=0x8 */
int _20___dt__8CXFModelFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x14;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__8CXFModel;
    *(undefined4 *)(param_1 + 8) = 0x409660;
    __dt__7ExModelFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
