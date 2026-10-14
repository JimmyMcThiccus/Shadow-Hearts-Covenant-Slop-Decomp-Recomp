/*
 * VEC.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 23 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x002fc0c0 size 0x174  VEC::VEC(iP10EffectCorei)
 *      mangled: __ct__3VECFiP10EffectCorei */
int __ct__3VECFiP10EffectCorei(int param_1,u32 param_2,u32 param_3,u32 param_4)

{
  u32 uVar1;
  long lVar2;
  
  __ct__5CListFv(param_1);
  *(u8 **)(param_1 + 0x250) = __vt__3VEC;
  *(u32 *)(param_1 + 0x244) = param_4;
  *(u32 *)(param_1 + 0xc) = 0;
  *(u32 *)(param_1 + 0x10) = 0;
  *(u32 *)(param_1 + 0x14) = 0;
  *(u32 *)(param_1 + 0x21c) = 0;
  *(u32 *)(param_1 + 8) = param_2;
  *(u32 *)(param_1 + 0x240) = 0;
  *(u32 *)(param_1 + 0x234) = 0;
  lVar2 = __nw__FUi(0x10);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9BufMemoryFUlUi(lVar2,40000,0x10);
  }
  *(u32 *)(param_1 + 0x70) = uVar1;
  uVar1 = getBuffer__9BufMemoryFv(*(u32 *)(param_1 + 0x70));
  *(u32 *)(param_1 + 0x74) = uVar1;
  *(u32 *)(param_1 + 0x6c) = 0;
  *(u32 *)(param_1 + 0x18) = 0;
  *(u32 *)(param_1 + 0x230) = param_3;
  *(u8 *)(param_1 + 0x220) = 0;
  *(u8 *)(param_1 + 0x221) = 0;
  *(u32 *)(param_1 + 0x208) = 0;
  *(u32 *)(param_1 + 0x20c) = 0;
  *(u32 *)(param_1 + 0x210) = 40000;
  *(u32 *)(param_1 + 0x214) = 0;
  *(u32 *)(param_1 + 0x218) = 0;
  *(u32 *)(param_1 + 0x224) = 0;
  *(u32 *)(param_1 + 0x228) = 0;
  *(u8 *)(param_1 + 0x22c) = 0;
  *(u8 *)(param_1 + 0x24c) = 0;
  Init__17tagEffectLoadWaitFv(param_1 + 0x238);
  return param_1;
}

/* ---- 0x002fc260 size 0xe8  VEC::~VEC(v)
 *      mangled: __dt__3VECFv */
int * __dt__3VECFv(int *param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    param_1[0x94] = (int)__vt__3VEC;
    if (param_1[0x1c] != 0) {
      __dt__9BufMemoryFv(param_1[0x1c],1);
      param_1[0x1c] = 0;
    }
    if (*param_1 != 0) {
      iVar1 = *param_1;
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x250) + 8))(iVar1,1);
      }
      *param_1 = 0;
    }
    __dt__5CListFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x002fc350 size 0x34  VEC::Start(v)
 *      mangled: Start__3VECFv */
u64 Start__3VECFv(int param_1)

{
  *(u32 *)(param_1 + 0xc) = *(u32 *)(param_1 + 8);
  *(u32 *)(param_1 + 0x18) = 1;
  return 0;
}

/* ---- 0x002fc390 size 0x70  VEC::Continue(v)
 *      mangled: Continue__3VECFv */
u64 Continue__3VECFv(int param_1)

{
  u64 uVar1;
  
  if ((*(int *)(param_1 + 0x18) == -1) || (*(int *)(param_1 + 0x18) == 3)) {
    uVar1 = 0;
  }
  else {
    *(u32 *)(param_1 + 0x18) = 1;
    uVar1 = DecodeVSM__3VECFv(param_1);
  }
  return uVar1;
}

/* ---- 0x002fc400 size 0x17ac  VEC::DecodeVSM(v)
 *      mangled: DecodeVSM__3VECFv */
u32 DecodeVSM__3VECFv(int param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  u32 uVar6;
  long lVar7;
  u64 uVar8;
  uint uVar9;
  u8 *puStack_18;
  u8 *puStack_14;
  
switchD_002fc6b0_caseD_0:
  if (*(int *)(param_1 + 0x18) != 1) {
    return 0xffffffff;
  }
  if ((*(int *)(param_1 + 0xc) < 0) || (0x1fff < *(int *)(param_1 + 0xc))) {
    printf(_2579,*(u32 *)(param_1 + 0xc));
    *(u32 *)(param_1 + 0x18) = 0xffffffff;
    return 0xffffffff;
  }
  if ((99 < *(int *)(param_1 + 0x10)) || (*(int *)(param_1 + 0x10) < 0)) {
    printf(_2580,*(u32 *)(param_1 + 0x10),*(u32 *)(param_1 + 0xc));
    *(u32 *)(param_1 + 0x18) = 0xffffffff;
    return 0xffffffff;
  }
  if (*(char *)(param_1 + 0x221) != '\0') {
    if (*(char *)(param_1 + 0x22c) == '\0') {
      return 1;
    }
    if (*(int *)(param_1 + 0x228) != 0) {
      return 1;
    }
    *(u8 *)(param_1 + 0x221) = 0;
    *(u32 *)(param_1 + 0x248) = 0;
    *(u32 *)(param_1 + 0x228) = 0;
    *(u8 *)(param_1 + 0x22c) = 0;
  }
  lVar7 = IsMotionWait__3VECFv(param_1);
  if (lVar7 != 0) {
    return 1;
  }
  if (((*(byte *)(param_1 + 0x238) & 1) != 0) &&
     (-1 < (long)((ulong)*(byte *)(param_1 + 0x238) << 0x3e))) {
    return 1;
  }
  bVar1 = *(byte *)(*(int *)(param_1 + 0x6c) + *(int *)(param_1 + 0xc) * 8);
  uVar4 = *(uint *)(*(int *)(param_1 + 0x6c) + *(int *)(param_1 + 0xc) * 8 + 4);
  iVar5 = *(int *)(param_1 + 0xc);
  *(int *)(param_1 + 0xc) = iVar5 + 1;
  if (*(char *)(*(int *)(param_1 + 0x6c) + iVar5 * 8 + 1) != '\0') {
    uVar4 = uVar4 + *(int *)(param_1 + 0x14);
  }
  *(int *)(param_1 + 0x208) = *(int *)(param_1 + 0x208) + 1;
  if (*(int *)(param_1 + 0x20c) < *(int *)(param_1 + 0x10)) {
    *(u32 *)(param_1 + 0x20c) = *(u32 *)(param_1 + 0x10);
  }
  switch(bVar1) {
  case 0:
    goto switchD_002fc6b0_caseD_0;
  case 1:
    iVar5 = *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78);
    uVar6 = *(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    *(u32 *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) = uVar6;
    *(char *)(*(int *)(param_1 + 0x74) + iVar5) = (char)uVar6;
    break;
  case 2:
    iVar5 = *(int *)(param_1 + 0x74);
    iVar3 = *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78);
    uVar6 = *(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    *(u32 *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) = uVar6;
    *(u32 *)(iVar5 + iVar3) = uVar6;
    break;
  case 3:
    iVar5 = *(int *)(param_1 + 0x74);
    iVar3 = *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78);
    uVar6 = *(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    *(u32 *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) = uVar6;
    *(u32 *)(iVar5 + iVar3) = uVar6;
    break;
  case 4:
    *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) +
         *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 5:
    *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) +
         *(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 6:
    iVar5 = param_1 + *(int *)(param_1 + 0x10) * 4;
    *(uint *)(iVar5 + 0x78) = *(int *)(iVar5 + 0x78) + uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 7:
    *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) -
         *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 8:
    *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) -
         *(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 9:
    iVar5 = param_1 + *(int *)(param_1 + 0x10) * 4;
    *(uint *)(iVar5 + 0x78) = *(int *)(iVar5 + 0x78) - uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 10:
    *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) *
         *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 0xb:
    *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) *
         *(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 0xc:
    iVar5 = param_1 + *(int *)(param_1 + 0x10) * 4;
    *(uint *)(iVar5 + 0x78) = *(int *)(iVar5 + 0x78) * uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0xd:
    if (*(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) == 0) {
      printf(_2581,*(int *)(param_1 + 0xc) + -1);
      return 0xffffffff;
    }
    iVar5 = *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    if (iVar5 == 0) {
      trap(7);
    }
    *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) / iVar5;
    break;
  case 0xe:
    if (*(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) == 0.0) {
      printf(_2581,*(int *)(param_1 + 0xc) + -1);
      return 0xffffffff;
    }
    *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) /
         *(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 0xf:
    iVar5 = param_1 + *(int *)(param_1 + 0x10) * 4;
    if (uVar4 == 0) {
      trap(7);
    }
    *(int *)(iVar5 + 0x78) = *(int *)(iVar5 + 0x78) / (int)uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x10:
    if (*(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) == 0) {
      printf(_2581,*(int *)(param_1 + 0xc) + -1);
      return 0xffffffff;
    }
    iVar5 = *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    if (iVar5 == 0) {
      trap(7);
    }
    *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) =
         *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) % iVar5;
    break;
  default:
    goto switchD_002fc6b0_caseD_11;
  case 0x12:
    iVar5 = param_1 + *(int *)(param_1 + 0x10) * 4;
    if (uVar4 == 0) {
      trap(7);
    }
    *(int *)(iVar5 + 0x78) = *(int *)(iVar5 + 0x78) % (int)uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x13:
    *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) =
         -*(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x14:
    *(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) =
         -*(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x15:
    if (*(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) <
        *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78)) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = (uint)(*(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) <
                    *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78));
    }
    *(uint *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) = uVar4;
    break;
  case 0x16:
    if (*(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) <
        *(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78)) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = (uint)(*(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) <
                    *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78));
    }
    *(float *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) = (float)(int)uVar4;
    break;
  case 0x17:
    if (*(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) < (int)uVar4) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = (uint)((int)uVar4 < *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78));
    }
    *(uint *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) = uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x18:
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    __as__Q23VEC4OpdSFRCQ23VEC4OpdS
              (param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78,
               param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x19:
    cVar2 = *(char *)(*(int *)(param_1 + 0x74) + uVar4);
    iVar5 = *(int *)(param_1 + 0x10) + 1;
    *(int *)(param_1 + 0x10) = iVar5;
    *(int *)(param_1 + iVar5 * 4 + 0x78) = (int)cVar2;
    goto switchD_002fc6b0_caseD_0;
  case 0x1a:
    uVar6 = *(u32 *)(*(int *)(param_1 + 0x74) + uVar4);
    iVar5 = *(int *)(param_1 + 0x10) + 1;
    *(int *)(param_1 + 0x10) = iVar5;
    *(u32 *)(param_1 + iVar5 * 4 + 0x78) = uVar6;
    goto switchD_002fc6b0_caseD_0;
  case 0x1b:
    uVar6 = *(u32 *)(*(int *)(param_1 + 0x74) + uVar4);
    iVar5 = *(int *)(param_1 + 0x10) + 1;
    *(int *)(param_1 + 0x10) = iVar5;
    *(u32 *)(param_1 + iVar5 * 4 + 0x78) = uVar6;
    goto switchD_002fc6b0_caseD_0;
  case 0x1c:
    iVar5 = *(int *)(param_1 + 0x10) + 1;
    *(int *)(param_1 + 0x10) = iVar5;
    *(uint *)(param_1 + iVar5 * 4 + 0x78) = uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x1d:
    *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) =
         (int)*(char *)(*(int *)(param_1 + 0x74) +
                       *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78));
    goto switchD_002fc6b0_caseD_0;
  case 0x1e:
    *(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) =
         *(u32 *)
          (*(int *)(param_1 + 0x74) + *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78));
    goto switchD_002fc6b0_caseD_0;
  case 0x1f:
    *(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) =
         *(u32 *)
          (*(int *)(param_1 + 0x74) + *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78));
    goto switchD_002fc6b0_caseD_0;
  case 0x20:
    break;
  case 0x21:
    *(char *)(*(int *)(param_1 + 0x74) + uVar4) =
         (char)*(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 0x22:
    *(u32 *)(*(int *)(param_1 + 0x74) + uVar4) =
         *(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 0x23:
    *(u32 *)(*(int *)(param_1 + 0x74) + uVar4) =
         *(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 0x24:
    *(uint *)(param_1 + 0x14) = uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x25:
    uVar4 = *(int *)(param_1 + 0x14) + uVar4;
    *(uint *)(param_1 + 0x14) = uVar4;
    if (40000 < uVar4) {
      printf(_2582);
      *(u32 *)(param_1 + 0x18) = 0xffffffff;
      return 0xfffffffe;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x26:
    iVar5 = *(int *)(param_1 + 0x14) - uVar4;
    *(int *)(param_1 + 0x14) = iVar5;
    if (iVar5 < *(int *)(param_1 + 0x210)) {
      if (*(int *)(param_1 + 0x14) <= *(int *)(param_1 + 0x21c)) {
        printf(_2582);
        *(u32 *)(param_1 + 0x18) = 0xffffffff;
        return 0xfffffffe;
      }
      *(u32 *)(param_1 + 0x210) = *(u32 *)(param_1 + 0x14);
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x27:
    *(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) =
         (float)*(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x28:
    *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) =
         (int)*(float *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x29:
    *(uint *)(param_1 + 0xc) = uVar4;
    goto switchD_002fc6b0_caseD_0;
  case 0x2a:
    iVar5 = *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar5 + -1;
    if (*(int *)(param_1 + iVar5 * 4 + 0x78) < 0) {
      *(uint *)(param_1 + 0xc) = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2b:
    iVar5 = *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar5 + -1;
    if (*(int *)(param_1 + iVar5 * 4 + 0x78) < 1) {
      *(uint *)(param_1 + 0xc) = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2c:
    iVar5 = *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar5 + -1;
    if (*(int *)(param_1 + iVar5 * 4 + 0x78) == 0) {
      *(uint *)(param_1 + 0xc) = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2d:
    iVar5 = *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar5 + -1;
    if (*(int *)(param_1 + iVar5 * 4 + 0x78) != 0) {
      *(uint *)(param_1 + 0xc) = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2e:
    iVar5 = *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar5 + -1;
    if (-1 < *(int *)(param_1 + iVar5 * 4 + 0x78)) {
      *(uint *)(param_1 + 0xc) = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x2f:
    iVar5 = *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar5 + -1;
    if (0 < *(int *)(param_1 + iVar5 * 4 + 0x78)) {
      *(uint *)(param_1 + 0xc) = uVar4;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x30:
    iVar5 = *(int *)(param_1 + 0x10) + 1;
    *(int *)(param_1 + 0x10) = iVar5;
    *(u32 *)(param_1 + iVar5 * 4 + 0x78) = *(u32 *)(param_1 + 0xc);
    *(uint *)(param_1 + 0xc) = uVar4;
    *(int *)(param_1 + 0x218) = *(int *)(param_1 + 0x218) + 1;
    goto switchD_002fc6b0_caseD_0;
  case 0x31:
    iVar5 = *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar5 + -1;
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_1 + iVar5 * 4 + 0x78);
    goto switchD_002fc6b0_caseD_0;
  case 0x32:
    if (*(int *)(param_1 + 0x10) != 0) {
      printf(_2584);
      printf(_2585);
      printf(_2584);
    }
    *(u32 *)(param_1 + 0x18) = 3;
    return 0;
  case 0x33:
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -3;
    puStack_18 = (u8 *)
                 (*(int *)(param_1 + 0x74) +
                 *(int *)(param_1 + (*(int *)(param_1 + 0x10) + 2) * 4 + 0x78));
    puStack_14 = (u8 *)
                 (*(int *)(param_1 + 0x74) +
                 *(int *)(param_1 + (*(int *)(param_1 + 0x10) + 1) * 4 + 0x78));
    for (iVar5 = *(int *)(param_1 + (*(int *)(param_1 + 0x10) + 3) * 4 + 0x78); 0 < iVar5;
        iVar5 = iVar5 + -1) {
      *puStack_18 = *puStack_14;
      puStack_18 = puStack_18 + 1;
      puStack_14 = puStack_14 + 1;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x34:
    iVar5 = __nwa__FUi(*(u32 *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78));
    *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78) = iVar5 - *(int *)(param_1 + 0x74);
    goto switchD_002fc6b0_caseD_0;
  case 0x35:
    iVar5 = *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = iVar5 + -1;
    __dla__FPv(*(int *)(param_1 + 0x74) + *(int *)(param_1 + iVar5 * 4 + 0x78));
    goto switchD_002fc6b0_caseD_0;
  case 0x36:
    iVar5 = scanf((char *)(*(int *)(param_1 + 0x74) +
                          *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78)),
                  *(int *)(param_1 + 0x74) + *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78)
                 );
    *(int *)(param_1 + (*(int *)(param_1 + 0x10) + -1) * 4 + 0x78) = iVar5;
    break;
  case 0x37:
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -2;
    goto switchD_002fc6b0_caseD_0;
  case 0x38:
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    goto switchD_002fc6b0_caseD_0;
  case 0x39:
    uVar9 = uVar4 & 0xffff;
    uVar4 = (int)uVar4 >> 0x10 & 0xffff;
    if (0x14 < uVar9) {
      printf(_2583);
      *(u32 *)(param_1 + 0x18) = 0xffffffff;
      return 0xfffffffd;
    }
    lVar7 = GetSysCallFunc__Fi(uVar4);
    iVar5 = (int)lVar7;
    cVar2 = *(char *)(iVar5 + 0xc);
    if (cVar2 == '\x02') {
      (**(code **)(iVar5 + 4))(uVar4,uVar9,param_1 + 0x1c,0);
    }
    else if (cVar2 == '\x01') {
      (**(code **)(iVar5 + 4))(uVar4,uVar9,param_1 + 0x1c,param_1);
    }
    else if (cVar2 == '\0') {
      (**(code **)(iVar5 + 4))(uVar4,uVar9,param_1 + 0x1c,*(u32 *)(param_1 + 0x230));
    }
    else if (lVar7 != 0) {
      (**(code **)(iVar5 + 4))(uVar4,uVar9,param_1 + 0x1c,*(u32 *)(iVar5 + 8));
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x3a:
    if (((int)uVar4 < 0) || (0x14 < (int)uVar4)) {
      printf(_2583);
      *(u32 *)(param_1 + 0x18) = 0xffffffff;
      return 0xfffffffd;
    }
    *(int *)(param_1 + uVar4 * 4 + 0x1c) =
         *(int *)(param_1 + 0x74) + *(int *)(param_1 + *(int *)(param_1 + 0x10) * 4 + 0x78);
    break;
  case 0x3b:
    uVar8 = CreateThread__3VECFii
                      (param_1,uVar4,
                       *(u32 *)(*(int *)(param_1 + 0x6c) + *(int *)(param_1 + 0xc) * 8 + 4));
    AddThread__3VECFP3VEC(param_1,uVar8);
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
    goto switchD_002fc6b0_caseD_0;
  case 0x3c:
    RemoveThread__3VECFv(param_1);
    return 0;
  case 0x3d:
    *(uint *)(param_1 + 0x248) = uVar4;
    *(u8 *)(param_1 + 0x221) = 1;
    iVar5 = GetCore__3VECFv(param_1);
    uVar6 = GetThreadCount__3VECFi(*(u32 *)(iVar5 + 0x10),*(u32 *)(param_1 + 0x248));
    *(u32 *)(param_1 + 0x228) = uVar6;
    if (*(int *)(param_1 + 0x228) != 0) {
      *(u8 *)(param_1 + 0x22c) = 1;
    }
    goto switchD_002fc6b0_caseD_0;
  case 0x3e:
    uVar8 = GetCore__3VECFv(param_1);
    KillThread__10EffectCoreFi(uVar8,uVar4);
    goto switchD_002fc6b0_caseD_0;
  }
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
  goto switchD_002fc6b0_caseD_0;
switchD_002fc6b0_caseD_11:
  printf(_2586,(ulong)bVar1,*(u32 *)(param_1 + 0xc));
  *(u32 *)(param_1 + 0x18) = 0xffffffff;
  return 0xfffffffc;
}

/* ---- 0x002fdbb0 size 0x1c  VEC::GetCore(v)
 *      mangled: GetCore__3VECFv */
u32 GetCore__3VECFv(int param_1)

{
  return *(u32 *)(param_1 + 0x230);
}

/* ---- 0x002fdc00 size 0x4c  VEC::IsMotionWait(v)
 *      mangled: IsMotionWait__3VECFv */
bool IsMotionWait__3VECFv(int param_1)

{
  return *(int *)(param_1 + 0x224) != 0;
}

/* ---- 0x002fdc50 size 0x28  VEC::GetDsegAddr(i)
 *      mangled: GetDsegAddr__3VECFi */
int GetDsegAddr__3VECFi(int param_1,int param_2)

{
  return *(int *)(param_1 + 0x74) + param_2;
}

/* ---- 0x002fdc80 size 0xd0  VEC::CreateThread(ii)
 *      mangled: CreateThread__3VECFii */
u64 CreateThread__3VECFii(int param_1,u32 param_2,u32 param_3)

{
  void *__dest;
  void *__src;
  long lVar1;
  u64 uVar2;
  
  lVar1 = __nw__FUi(0x254);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = __ct__3VECFiP10EffectCorei(lVar1,param_2,*(u32 *)(param_1 + 0x230),param_3);
  }
  __dest = (void *)GetDsegAddr__3VECFi(uVar2,0);
  __src = (void *)GetDsegAddr__3VECFi(param_1,0);
  memcpy(__dest,__src,40000);
  SetIseg__3VECFPv(uVar2,*(u32 *)(param_1 + 0x6c));
  *(u32 *)((int)uVar2 + 0x14) = 20000;
  return uVar2;
}

/* ---- 0x002fdd50 size 0x24  VEC::SetIseg(Pv)
 *      mangled: SetIseg__3VECFPv */
void SetIseg__3VECFPv(int param_1,u32 param_2)

{
  *(u32 *)(param_1 + 0x6c) = param_2;
  return;
}

/* ---- 0x002fdd80 size 0x34  VEC::AddThread(P3VEC)
 *      mangled: AddThread__3VECFP3VEC */
void AddThread__3VECFP3VEC(int param_1,u32 param_2)

{
  AddThread__10EffectCoreFP3VEC(*(u32 *)(param_1 + 0x230),param_2);
  return;
}

/* ---- 0x002fddc0 size 0x30  VEC::RemoveThread(v)
 *      mangled: RemoveThread__3VECFv */
void RemoveThread__3VECFv(int param_1)

{
  RemoveThread__10EffectCoreFP3VEC(*(u32 *)(param_1 + 0x230),param_1);
  return;
}

/* ---- 0x002fddf0 size 0x98  VEC::MotionWait(P11EffectModel)
 *      mangled: MotionWait__3VECFP11EffectModel */
void MotionWait__3VECFP11EffectModel(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = GetCore__3VECFv(param_1);
  iVar2 = 0;
  while( true ) {
    if (0x27 < iVar2) {
      return;
    }
    if (*(int *)(iVar1 + iVar2 * 4 + 0x198) == param_2) break;
    iVar2 = iVar2 + 1;
  }
  *(int *)(param_1 + 0x224) = param_2;
  return;
}

/* ---- 0x002fde90 size 0x70  VEC::ReleaseMotionWait(P11EffectModel)
 *      mangled: ReleaseMotionWait__3VECFP11EffectModel */
void ReleaseMotionWait__3VECFP11EffectModel(int *param_1,int param_2)

{
  if (param_1[0x89] == param_2) {
    param_1[0x89] = 0;
  }
  else if (*param_1 != 0) {
    ReleaseMotionWait__3VECFP11EffectModel(*param_1,param_2);
  }
  return;
}

/* ---- 0x002fdf00 size 0x80  VEC::OnStartThread(P3VEC)
 *      mangled: OnStartThread__3VECFP3VEC */
void OnStartThread__3VECFP3VEC(int *param_1,int param_2)

{
  if (param_1[0x92] == *(int *)(param_2 + 0x244)) {
    param_1[0x8a] = param_1[0x8a] + 1;
    *(u8 *)(param_1 + 0x8b) = 1;
  }
  if (*param_1 != 0) {
    OnStartThread__3VECFP3VEC(*param_1,param_2);
  }
  return;
}

/* ---- 0x002fdf80 size 0x70  VEC::OnEndThread(P3VEC)
 *      mangled: OnEndThread__3VECFP3VEC */
void OnEndThread__3VECFP3VEC(int *param_1,int param_2)

{
  if (param_1[0x92] == *(int *)(param_2 + 0x244)) {
    param_1[0x8a] = param_1[0x8a] + -1;
  }
  if (*param_1 != 0) {
    OnEndThread__3VECFP3VEC(*param_1,param_2);
  }
  return;
}

/* ---- 0x002fdff0 size 0x70  VEC::GetThreadCount(i)
 *      mangled: GetThreadCount__3VECFi */
int GetThreadCount__3VECFi(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (*param_1 != 0) {
    iVar1 = GetThreadCount__3VECFi(*param_1,param_2);
  }
  if (param_1[0x91] == param_2) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

/* ---- 0x002fe060 size 0x170  InitSysFunc(v)
 *      mangled: InitSysFunc__Fv */
void InitSysFunc__Fv(void)

{
  int iVar1;
  u32 *puVar2;
  int iVar3;
  
  if (funcReader == 0) {
    for (iVar3 = 0; iVar3 < 0x83; iVar3 = iVar3 + 1) {
      *(u32 *)(&funcHash + iVar3 * 4) = 0;
    }
    for (iVar3 = 0; iVar3 < 0x10d; iVar3 = iVar3 + 1) {
      iVar1 = *(int *)(FuncTbl + iVar3 * 0xc);
      puVar2 = (u32 *)__nw__FUi(0x14);
      *puVar2 = *(u32 *)(FuncTbl + iVar3 * 0xc);
      puVar2[1] = *(u32 *)(FuncTbl + iVar3 * 0xc + 4);
      puVar2[2] = 0;
      *(u8 *)(puVar2 + 3) = FuncTbl[iVar3 * 0xc + 8];
      puVar2[4] = *(u32 *)(&funcHash + (iVar1 % 0x83) * 4);
      *(u32 **)(&funcHash + (iVar1 % 0x83) * 4) = puVar2;
    }
  }
  funcReader = funcReader + 1;
  return;
}

/* ---- 0x002fe1d0 size 0x94  GetSysCallFunc(i)
 *      mangled: GetSysCallFunc__Fi */
int * GetSysCallFunc__Fi(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(&funcHash + (param_1 % 0x83) * 4);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    if (*piVar1 == param_1) break;
    piVar1 = (int *)piVar1[4];
  }
  return piVar1;
}

/* ---- 0x002fe270 size 0xc4  CleanSysFunc(v)
 *      mangled: CleanSysFunc__Fv */
void CleanSysFunc__Fv(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  funcReader = funcReader + -1;
  if (funcReader < 1) {
    for (iVar3 = 0; iVar3 < 0x83; iVar3 = iVar3 + 1) {
      iVar2 = *(int *)(&funcHash + iVar3 * 4);
      while (iVar2 != 0) {
        iVar1 = *(int *)(iVar2 + 0x10);
        __dl__FPv(iVar2);
        iVar2 = iVar1;
      }
      *(u32 *)(&funcHash + iVar3 * 4) = 0;
    }
  }
  return;
}

/* ---- 0x00301530 size 0x24  VEC::SetRunState(i)
 *      mangled: SetRunState__3VECFi */
void SetRunState__3VECFi(int param_1,u32 param_2)

{
  *(u32 *)(param_1 + 0x18) = param_2;
  return;
}

/* ---- 0x00301770 size 0x1c  VEC::GetRunState(v)
 *      mangled: GetRunState__3VECFv */
u32 GetRunState__3VECFv(int param_1)

{
  return *(u32 *)(param_1 + 0x18);
}

/* ---- 0x00301d90 size 0x20  VEC::Stop(v)
 *      mangled: Stop__3VECFv */
void Stop__3VECFv(int param_1)

{
  *(u32 *)(param_1 + 0x18) = 3;
  return;
}

