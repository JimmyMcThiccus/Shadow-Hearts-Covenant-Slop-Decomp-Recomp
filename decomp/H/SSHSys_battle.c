/*
 * SSHSys_battle.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 3 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003b6c20 size 0x128  SSHSys::StartBattle(P12_SysBtlParamPCc)
 *      mangled: StartBattle__6SSHSysFP12_SysBtlParamPCc */
void StartBattle__6SSHSysFP12_SysBtlParamPCc(int param_1,u32 *param_2,char *param_3)

{
  u8 uVar1;
  u8 uVar2;
  u8 uVar3;
  
  if (param_2 == (u32 *)0x0) {
    if (*(char *)(param_1 + 0x36) == ' ') {
      *(char *)(param_1 + 0x36) = *(char *)(param_1 + 0x36) + '\x01';
    }
  }
  else {
    *(u32 *)(param_1 + 0x40) = *param_2;
    *(u32 *)(param_1 + 0x44) = param_2[1];
    *(u16 *)(param_1 + 0x48) = *(u16 *)(param_2 + 2);
    *(u8 *)(param_1 + 0x4a) = *(u8 *)((int)param_2 + 10);
    *(u8 *)(param_1 + 0x4b) = *(u8 *)((int)param_2 + 0xb);
    uVar1 = *(u8 *)((int)param_2 + 0xd);
    uVar2 = *(u8 *)((int)param_2 + 0xe);
    uVar3 = *(u8 *)((int)param_2 + 0xf);
    *(u8 *)(param_1 + 0x4c) = *(u8 *)(param_2 + 3);
    *(u8 *)(param_1 + 0x4d) = uVar1;
    *(u8 *)(param_1 + 0x4e) = uVar2;
    *(u8 *)(param_1 + 0x4f) = uVar3;
    *(u8 *)(param_1 + 0x36) = 0x20;
    *(u8 *)(param_1 + 0x54) = 0;
  }
  if ((param_3 != (char *)0x0) && (*param_3 != '\0')) {
    strcpy((char *)(param_1 + 0x54),param_3);
  }
  return;
}

/* ---- 0x003b6d50 size 0x34  SSHSys::cbBattle(iiPv)
 *      mangled: cbBattle__6SSHSysFiiPv */
void cbBattle__6SSHSysFiiPv(u32 param_1,u32 param_2)

{
  cbBattleA__6SSHSysFii(sys__6SSHSys,param_1,param_2);
  return;
}

/* ---- 0x003b6d90 size 0x18c  SSHSys::cbBattleA(ii)
 *      mangled: cbBattleA__6SSHSysFii */
u32 cbBattleA__6SSHSysFii(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  if (param_2 == 0) {
    bVar1 = *(byte *)(ourBtlSocket__9BtlSocket + 0x16c);
    bVar2 = bVar1 & 3;
    *(u8 *)(param_1 + 0x50) = 2;
    if ((bVar2 == 2) || (bVar2 == 3)) {
      *(u8 *)(param_1 + 0x51) = 0xff;
      *(u8 *)(param_1 + 0x36) = 0x10;
      SetChrPosSaveState__Fi(2);
    }
    else if (bVar2 == 1) {
      *(u8 *)(param_1 + 0x51) = 0;
      if (*(char *)(param_1 + 0x52) == '\0') {
        *(u8 *)(param_1 + 0x36) = 0x30;
        FieldPreLoadCancel__Fv();
      }
      else {
        *(u8 *)(param_1 + 0x36) = 0x10;
        SetChrPosSaveState__Fi(2);
      }
    }
    else if ((bVar1 & 3) == 0) {
      SetChrPosSaveState__Fi(2);
      *(u8 *)(param_1 + 0x51) = 1;
      *(u8 *)(param_1 + 0x36) = 0x10;
    }
    *(u8 *)(param_1 + 0x52) = 0;
  }
  else if (param_2 == 1) {
    FieldPreLoad__FPCc(param_1 + 0x54);
  }
  return 1;
}

