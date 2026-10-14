/*
 * GetLanguage.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 1 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003b5f60 size 0xbc  GetLanguage
 *      mangled: GetLanguage */
u32 GetLanguage(void)

{
  u64 uVar1;
  u32 uVar2;
  
  uVar1 = sceScfGetLanguage();
  switch(uVar1) {
  default:
    uVar2 = 1;
    break;
  case 1:
    uVar2 = 2;
    break;
  case 2:
    uVar2 = 4;
    break;
  case 3:
    uVar2 = 7;
    break;
  case 4:
    uVar2 = 5;
    break;
  case 5:
    uVar2 = 6;
  }
  return uVar2;
}

