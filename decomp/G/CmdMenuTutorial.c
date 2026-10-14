/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdMenuTutorial   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdMenuTutorial.md).
 */

/* JP: 0x00473fc0  CmdMenuTutorial::CmdMenuTutorial()   [__ct__15CmdMenuTutorialFv]  size=0xb8 */
int __ct__15CmdMenuTutorialFv(int param_1)

{
  __ct__7CmdMenuFsPFiPvP7CmdMenu_iPv(param_1,0xffffffffffffffff,0,0);
  *(undefined1 **)(param_1 + 0x14) = &__vt__15CmdMenuTutorial;
  *(undefined4 *)(param_1 + 0x20) = 0x408a60;
  *(undefined4 *)(param_1 + 0x17f8) = 0;
  *(undefined1 *)(param_1 + 0x17fc) = 0;
  *(undefined1 *)(param_1 + 0x17fd) = 0;
  *(undefined4 *)(param_1 + 0x1800) = 0;
  __ct__10MenuWindowFv(param_1 + 0x180c);
  __ct__8FontDrawFv(param_1 + 0x18c0);
  __ct__11MenuMessageFv(param_1 + 0x1900);
  __ct__7KeyWaitFv(param_1 + 0x1998);
  return param_1;
}

/* JP: 0x00474080  CmdMenuTutorial::~CmdMenuTutorial()   [__dt__15CmdMenuTutorialFv]  size=0xe4 */
int __dt__15CmdMenuTutorialFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__15CmdMenuTutorial;
    *(undefined4 *)(param_1 + 0x20) = 0x408a60;
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x1800),1);
    __dt__7KeyWaitFv(param_1 + 0x1998,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x1900,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x18c0,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x180c,0xffffffffffffffff);
    __dt__7CmdMenuFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00474170  CmdMenuTutorial::StartTutorial(short, int(*)(int, void*, CmdMenu*)*, void*)   [StartTutorial__15CmdMenuTutorialFsPFiPvP7CmdMenu_iPv]  size=0xa0 */
void StartTutorial__15CmdMenuTutorialFsPFiPvP7CmdMenu_iPv
               (int param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 auStack_240 [512];
  int iStack_40;
  undefined2 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  sprintf(auStack_240,0x555890,pDataPath__7SysTool,param_2);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,auStack_240,0x474210,0,iStack_40,0);
  *(undefined4 *)(iStack_40 + 0x50) = uStack_20;
  *(undefined4 *)(iStack_40 + 0x54) = uStack_10;
  *(undefined2 *)(iStack_40 + 0x17fe) = uStack_30;
  return;
}

/* JP: 0x00474250  CmdMenuTutorial::Create(BufMemory*)   [Create__15CmdMenuTutorialFP9BufMemory]  size=0x28c */
undefined8 Create__15CmdMenuTutorialFP9BufMemory(int param_1,int param_2)

{
  int *piVar1;
  
  *(int *)(param_1 + 0x1800) = param_2;
  piVar1 = *(int **)(param_2 + 4);
  *(int **)(param_1 + 0x1804) = piVar1 + 1;
  *(int *)(param_1 + 0x1808) = *(int *)(param_1 + 0x1804) + *piVar1 * 0x10;
  Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(param_1 + 0x18c0,0x1b,0x200,0x1c0,0,0,0);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x1824,param_1 + 0x18c0);
  (**(code **)(*(int *)(param_1 + 0x1908) + 0x60))(param_1 + 0x1900,0x100,2);
  *(undefined2 *)(param_1 + 0x1914) = 1;
  SetFontNumber__8FontItemFUc(param_1 + 0x1900,0);
  *(byte *)(param_1 + 0x1958) = *(byte *)(param_1 + 0x1958) & 0xf7;
  *(int *)(param_1 + 0x1954) = param_1 + 0x18c0;
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x180c,param_1 + 0x1900);
  Create__7KeyWaitFv(param_1 + 0x1998);
  *(undefined2 *)(param_1 + 0x19b6) = 1;
  *(byte *)(param_1 + 0x19aa) = *(byte *)(param_1 + 0x19aa) & 0xfd;
  *(byte *)(param_1 + 0x19aa) = *(byte *)(param_1 + 0x19aa) & 0xfe;
  *(int *)(param_1 + 0x1854) = param_1 + 0x1998;
  *(int *)(param_1 + 0x19b0) = param_1 + 0x180c;
  Create__10MenuWindowFUcUcffff(0,0,0,0,param_1 + 0x180c,6,1);
  *(undefined2 *)(param_1 + 0x1820) = 30000;
  *(byte *)(param_1 + 0x181e) = *(byte *)(param_1 + 0x181e) & 0xfe;
  AddOT__7MenuObjFv(param_1 + 0x180c);
  Initialize__7CmdMenuFsPFiPvP7CmdMenu_iPv
            (param_1,0,*(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x54));
  *(undefined1 *)(param_1 + 0x3d) = 0x11;
  *(byte *)(*(int *)(param_1 + 0x68) + 0x46) = *(byte *)(*(int *)(param_1 + 0x68) + 0x46) & 0xfd;
  *(int *)(param_1 + 0x1a74) = param_1 + 0x3a0;
  return 0;
}

/* JP: 0x004744e0  CmdMenuTutorial::Polling()   [Polling__15CmdMenuTutorialFv]  size=0x708 */
undefined8 Polling__15CmdMenuTutorialFv(int param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  ulong uVar4;
  undefined8 uVar5;
  uint uVar6;
  
  *(undefined2 *)(param_1 + 0x48) = 0;
  if ((*(char *)(param_1 + 0x4e) != '\0') && (*(char *)(param_1 + 0x17fc) == '\0')) {
    switch(**(undefined4 **)(param_1 + 0x1804)) {
    case 1:
      *(undefined2 *)(param_1 + 0x48) = *(undefined2 *)(*(int *)(param_1 + 0x1804) + 8);
    case 2:
      uVar6 = *(int *)(param_1 + 0x17f8) + sm_iPassTime__7MenuObj;
      *(uint *)(param_1 + 0x17f8) = uVar6;
      if (*(uint *)(*(int *)(param_1 + 0x1804) + 4) < uVar6) {
        *(undefined4 *)(param_1 + 0x17f8) = 0;
        *(int *)(param_1 + 0x1804) = *(int *)(param_1 + 0x1804) + 0x10;
      }
      break;
    case 3:
      cVar1 = *(char *)(param_1 + 0x17fd);
      if (cVar1 == '\x02') {
        if ((char)*(undefined2 *)(param_1 + 0x19b6) == '\r') {
          ClearImage__8FontDrawFv(param_1 + 0x18c0);
          ClearMessage__11MenuMessageFv(param_1 + 0x1900);
          *(undefined2 *)(param_1 + 0x19b6) = 1;
          *(byte *)(param_1 + 0x19aa) = *(byte *)(param_1 + 0x19aa) & 0xfd;
          *(byte *)(param_1 + 0x19aa) = *(byte *)(param_1 + 0x19aa) & 0xfe;
          *(undefined1 *)(param_1 + 0x17fd) = 0;
          *(int *)(param_1 + 0x1804) = *(int *)(param_1 + 0x1804) + 0x10;
        }
      }
      else if (cVar1 == '\x01') {
        iVar3 = GetActive__4CPadFi(0);
        if ((*(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar3 + 4) * 4) + 0x6c) & 0x2000)
            != 0) {
          Finish__11MenuMessageFv(param_1 + 0x1900);
        }
        if (*(ushort *)(param_1 + 0x1976) <= *(ushort *)(param_1 + 0x1980)) {
          SetPosition__7KeyWaitFi(param_1 + 0x1998,1);
          *(undefined2 *)(param_1 + 0x19b6) = 10;
          uVar4 = (ulong)*(byte *)(param_1 + 0x19aa) & 0xfffffffffffffffd | 2;
          *(char *)(param_1 + 0x19aa) = (char)uVar4;
          *(byte *)(param_1 + 0x19aa) =
               *(byte *)(param_1 + 0x19aa) & 0xfe | (byte)((uVar4 << 0x3e) >> 0x3f);
          *(char *)(param_1 + 0x17fd) = *(char *)(param_1 + 0x17fd) + '\x01';
        }
      }
      else if (cVar1 == '\0') {
        Order__8FontDrawFP11MenuMessagePc(param_1 + 0x18c0,param_1 + 0x1900,
                        *(int *)(*(int *)(param_1 + 0x1804) + 4) +
                        *(int *)(*(int *)(param_1 + 0x1800) + 4));
        Start__11MenuMessageFv(param_1 + 0x1900);
        *(char *)(param_1 + 0x17fd) = *(char *)(param_1 + 0x17fd) + '\x01';
      }
      break;
    case 4:
      cVar1 = *(char *)(param_1 + 0x17fd);
      if (cVar1 == '\x02') {
        uVar6 = *(int *)(param_1 + 0x17f8) + sm_iPassTime__7MenuObj;
        *(uint *)(param_1 + 0x17f8) = uVar6;
        if (*(uint *)(*(int *)(param_1 + 0x1804) + 0xc) < uVar6) {
          *(undefined4 *)(param_1 + 0x17f8) = 0;
          *(undefined1 *)(param_1 + 0x17fd) = 0;
        }
      }
      else if (cVar1 == '\x01') {
        if ((*(short *)(*(int *)(param_1 + 0x1804) + 4) ==
             *(short *)(*(int *)(*(int *)(param_1 + 0x1a74) + 0xec) + 0x16)) ||
           (*(short *)(*(int *)(param_1 + 0x1804) + 6) ==
            *(short *)(*(int *)(*(int *)(param_1 + 0x1a74) + 0xec) + 0x22))) {
          *(int *)(param_1 + 0x1804) = *(int *)(param_1 + 0x1804) + 0x10;
          *(undefined1 *)(param_1 + 0x17fd) = 0;
        }
        else {
          *(char *)(param_1 + 0x17fd) = *(char *)(param_1 + 0x17fd) + '\x01';
        }
      }
      else if (cVar1 == '\0') {
        *(undefined2 *)(param_1 + 0x48) = *(undefined2 *)(*(int *)(param_1 + 0x1804) + 8);
        *(char *)(param_1 + 0x17fd) = *(char *)(param_1 + 0x17fd) + '\x01';
      }
      break;
    case 5:
      SetPosition__10MenuWindowFff((float)(int)*(short *)(*(int *)(param_1 + 0x1804) + 4),
                      (float)(int)*(short *)(*(int *)(param_1 + 0x1804) + 6),param_1 + 0x180c);
      SetSize__10MenuWindowFff((float)(int)*(short *)(*(int *)(param_1 + 0x1804) + 8),
                      (float)(int)*(short *)(*(int *)(param_1 + 0x1804) + 10),param_1 + 0x180c);
      Open__10MenuWindowFUci(param_1 + 0x180c,0,*(undefined4 *)(*(int *)(param_1 + 0x1804) + 0xc));
      **(undefined4 **)(param_1 + 0x1804) = 7;
      break;
    case 6:
      Close__10MenuWindowFUci(param_1 + 0x180c,0,*(undefined4 *)(*(int *)(param_1 + 0x1804) + 0xc));
      **(undefined4 **)(param_1 + 0x1804) = 7;
      break;
    case 7:
      if ((*(char *)(param_1 + 0x18b4) == '\x01') || (*(char *)(param_1 + 0x18b4) == '\0')) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        *(int *)(param_1 + 0x1804) = *(int *)(param_1 + 0x1804) + 0x10;
      }
    }
    if (*(uint *)(param_1 + 0x1808) <= *(uint *)(param_1 + 0x1804)) {
      ReleaseOT__7MenuObjFv(param_1 + 0x180c);
      *(char *)(param_1 + 0x17fc) = *(char *)(param_1 + 0x17fc) + '\x01';
    }
  }
  uVar5 = Polling__7CmdMenuFv(param_1);
  return uVar5;
}

/* JP: 0x00474bf0  CmdMenuTutorial::GetKey()   [GetKey__15CmdMenuTutorialFv]  size=0x10 */
void GetKey__15CmdMenuTutorialFv(void)

{
  return;
}

/* JP: 0x00474c00  CmdMenuTutorial::~CmdMenuTutorial()   [@24@__dt__15CmdMenuTutorialFv]  size=0x8 */
int _24___dt__15CmdMenuTutorialFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__15CmdMenuTutorial;
    *(undefined4 *)(param_1 + 8) = 0x408a60;
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x17e8),1);
    __dt__7KeyWaitFv(param_1 + 0x1980,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x18e8,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x18a8,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x17f4,0xffffffffffffffff);
    __dt__7CmdMenuFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
