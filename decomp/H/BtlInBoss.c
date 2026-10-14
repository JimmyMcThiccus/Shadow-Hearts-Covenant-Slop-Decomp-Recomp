/*
 * BtlInBoss.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 12 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003b2770 size 0x13cc  BtlInBoss::BtlInBoss(v)
 *      mangled: __ct__9BtlInBossFv */
VIF1Prim * __ct__9BtlInBossFv(VIF1Prim *param_1)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  u32 uVar4;
  u32 uVar5;
  u32 uVar6;
  u64 uVar7;
  VIF1Prim *pVVar8;
  u16 uVar9;
  VIF1Prim *pVVar10;
  u64 uVar11;
  long lVar12;
  ulong uVar13;
  ulong uVar14;
  uint uVar15;
  uint uVar16;
  void *pvVar17;
  void *pvVar18;
  u32 uVar19;
  uint uVar20;
  byte *pbVar21;
  void *pvVar22;
  void *pvVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  void *pvVar27;
  int iVar28;
  void *pvVar29;
  uint uVar30;
  uint uVar31;
  uint uStack_38;
  u8 auStack_34 [4];
  byte *pbStack_30;
  uint *puStack_2c;
  void **ppvStack_28;
  uint *puStack_24;
  byte *pbStack_20;
  VIF1Prim *pVStack_1c;
  uint *puStack_18;
  u8 auStack_14 [4];
  VIF1Prim *pVStack_10;
  
  pVStack_10 = param_1;
  __ct__8VIF1PrimFv(param_1);
  __ct__17DelayDeleteObjectFv(pVStack_10 + 1);
  __ct__7CPolObjFv(&pVStack_10[1].bFlags);
  pVStack_10->pVptr = __vt__9BtlInBoss;
  pVStack_10[1].dwEnv = 0x4075d0;
  pVStack_10[2].bFlags = 0xe0;
  pVStack_10[2].b_pad0d = 0x75;
  pVStack_10[2].nZvolume = 0x40;
  puStack_18 = &pVStack_10[3].dw_unk4;
  do {
    __ct__4_QWDFv(puStack_18);
    puStack_18 = puStack_18 + 4;
  } while ((VIF1Prim *)puStack_18 != pVStack_10 + 8);
  pVStack_1c = pVStack_10 + 8;
  do {
    __ct__4_QWDFv(pVStack_1c);
    pVStack_1c = (VIF1Prim *)&pVStack_1c->pVptr;
  } while (pVStack_1c != (VIF1Prim *)&pVStack_10[0x11].bFlags);
  pbStack_20 = &pVStack_10[0x11].bFlags;
  do {
    __ct__4_QWDFv(pbStack_20);
    pbStack_20 = pbStack_20 + 0x10;
  } while ((uint *)pbStack_20 != &pVStack_10[0x1e].dwEnv);
  puStack_24 = &pVStack_10[0x1e].dwEnv;
  do {
    __ct__4_QWDFv(puStack_24);
    puStack_24 = puStack_24 + 4;
  } while ((void **)puStack_24 != &pVStack_10[0x20].pVptr);
  ppvStack_28 = &pVStack_10[0x20].pVptr;
  do {
    __ct__4_QWDFv(ppvStack_28);
    ppvStack_28 = ppvStack_28 + 4;
  } while (ppvStack_28 != (void **)&pVStack_10[0x23].dw_unk4);
  puStack_2c = &pVStack_10[0x23].dw_unk4;
  do {
    __ct__4_QWDFv(puStack_2c);
    puStack_2c = puStack_2c + 4;
  } while (puStack_2c != (uint *)&pVStack_10[0x25].bFlags);
  pbStack_30 = &pVStack_10[0x25].bFlags;
  do {
    __ct__4_QWDFv(pbStack_30);
    pbStack_30 = (byte *)((int)pbStack_30 + 0x10);
  } while ((VIF1Prim *)pbStack_30 != pVStack_10 + 0x28);
  __ct__8LightPolFv(&pVStack_10[0x29].bFlags);
  __construct_array(&pVStack_10[0x3e].dwEnv,0x3b3cc0,0x3b3c60,0x240,8);
  __ct__10FirstLightFv(&pVStack_10[0x124].pVptr);
  __ct__12FrameTextureFv(&pVStack_10[0x134].pVptr);
  __ct__8LineBlurFv(pVStack_10 + 0x150);
  SetFase__7tagFaseFi(&pVStack_10[0x133].pVptr,0);
  SetFase__7tagFaseFi(&pVStack_10[0x134].dw_unk4,0);
  pVVar8 = pVStack_10;
  *(u16 *)&pVStack_10[0x133].dw_unk4 = 0x80;
  pVStack_10[0x133].dwEnv = 0;
  pVVar8[0x133].bFlags = 0;
  pVVar8[0x133].b_pad0d = 0;
  pVVar8[0x133].nZvolume = 0;
  pVVar10 = pVStack_10 + 3;
  memset(&pVVar10->dw_unk4,0,0x60);
  pVVar10->dw_unk4 = 0x60000005;
  pVVar8[3].pVptr = (void *)0x50000005;
  pVVar8[4].dw_unk0 = 0x8004;
  pVVar8[4].dw_unk4 = 0x10000000;
  pVVar8[4].dwEnv = 0xe;
  pVVar8[4].bFlags = 0;
  pVVar8[4].b_pad0d = 0;
  pVVar8[4].nZvolume = 0;
  *(u64 *)&pVVar8[4].pVptr = 0x30000;
  pVVar8[5].dw_unk4 = 0x47;
  pVVar8[5].dwEnv = 0;
  pVVar8[5].bFlags = 1;
  pVVar8[5].b_pad0d = 0;
  pVVar8[5].nZvolume = 0;
  pVVar8[5].pVptr = (void *)0x0;
  pVVar8[6].dw_unk0 = 0x14;
  pVVar8[6].dw_unk4 = 0;
  pVVar8[6].dwEnv = 5;
  pVVar8[6].bFlags = 0;
  pVVar8[6].b_pad0d = 0;
  pVVar8[6].nZvolume = 0;
  *(u64 *)&pVVar8[6].pVptr = 8;
  pVVar8[7].dw_unk4 = 0x44;
  pVVar8[7].dwEnv = 0;
  pVVar8[7].bFlags = 0x42;
  pVVar8[7].b_pad0d = 0;
  pVVar8[7].nZvolume = 0;
  pVVar8[7].pVptr = (void *)0x0;
  memset(pVStack_10 + 8,0,0x60);
  memset(&pVStack_10[0xc].pVptr,0,0x60);
  pVStack_10[8].dw_unk0 = 0x60000005;
  pVStack_10[8].bFlags = 5;
  pVStack_10[8].b_pad0d = 0;
  pVStack_10[8].nZvolume = 0x5000;
  *(u64 *)&pVStack_10[8].pVptr = 0x4023400000008001;
  pVStack_10[9].dw_unk4 = 0x5151;
  pVStack_10[9].dwEnv = 0;
  pVStack_10[9].bFlags = 0xff;
  pVStack_10[9].b_pad0d = 0;
  pVStack_10[9].nZvolume = 0;
  pVStack_10[9].pVptr = (void *)0xff;
  pVStack_10[10].dw_unk0 = 0xff;
  pVStack_10[10].dw_unk4 = (int)(short)pVStack_10[0x133].dw_unk4;
  pVStack_10[10].dwEnv = 0x7000;
  pVStack_10[10].bFlags = 0;
  pVStack_10[10].b_pad0d = 0x72;
  pVStack_10[10].nZvolume = 0;
  pVStack_10[10].pVptr = (void *)0x0;
  pVStack_10[0xb].dw_unk0 = 0;
  pVStack_10[0xb].dw_unk4 = 0xff;
  pVStack_10[0xb].dwEnv = 0xff;
  pVStack_10[0xb].bFlags = 0xff;
  pVStack_10[0xb].b_pad0d = 0;
  pVStack_10[0xb].nZvolume = 0;
  pVStack_10[0xb].pVptr = (void *)(int)(short)pVStack_10[0x133].dw_unk4;
  pVStack_10[0xc].dw_unk0 = 0x9000;
  pVStack_10[0xc].dw_unk4 = 0x8e00;
  pVStack_10[0xc].dwEnv = 0;
  pVStack_10[0xc].bFlags = 0;
  pVStack_10[0xc].b_pad0d = 0;
  pVStack_10[0xc].nZvolume = 0;
  uVar5 = pVStack_10[8].dw_unk0;
  uVar6 = pVStack_10[8].dw_unk4;
  uVar25 = pVStack_10[8].dwEnv;
  uVar26 = *(uint *)&pVStack_10[8].bFlags;
  pvVar27 = pVStack_10[8].pVptr;
  pvVar29 = (void *)pVStack_10[9].dw_unk0;
  uVar30 = pVStack_10[9].dw_unk4;
  uVar31 = pVStack_10[9].dwEnv;
  uVar20 = *(uint *)&pVStack_10[9].bFlags;
  pvVar22 = pVStack_10[9].pVptr;
  pvVar23 = (void *)pVStack_10[10].dw_unk0;
  uVar24 = pVStack_10[10].dw_unk4;
  uVar15 = pVStack_10[10].dwEnv;
  uVar16 = *(uint *)&pVStack_10[10].bFlags;
  pvVar17 = pVStack_10[10].pVptr;
  pvVar18 = (void *)pVStack_10[0xb].dw_unk0;
  pVStack_10[0xc].pVptr = (void *)uVar5;
  pVStack_10[0xd].dw_unk0 = uVar6;
  pVStack_10[0xd].dw_unk4 = uVar25;
  pVStack_10[0xd].dwEnv = uVar26;
  *(void **)&pVStack_10[0xd].bFlags = pvVar27;
  pVStack_10[0xd].pVptr = pvVar29;
  pVStack_10[0xe].dw_unk0 = uVar30;
  pVStack_10[0xe].dw_unk4 = uVar31;
  pVStack_10[0xe].dwEnv = uVar20;
  *(void **)&pVStack_10[0xe].bFlags = pvVar22;
  pVStack_10[0xe].pVptr = pvVar23;
  pVStack_10[0xf].dw_unk0 = uVar24;
  pVStack_10[0xf].dw_unk4 = uVar15;
  pVStack_10[0xf].dwEnv = uVar16;
  *(void **)&pVStack_10[0xf].bFlags = pvVar17;
  pVStack_10[0xf].pVptr = pvVar18;
  uVar24 = pVStack_10[0xb].dwEnv;
  uVar25 = *(uint *)&pVStack_10[0xb].bFlags;
  pvVar18 = pVStack_10[0xb].pVptr;
  pvVar17 = (void *)pVStack_10[0xc].dw_unk0;
  uVar15 = pVStack_10[0xc].dw_unk4;
  uVar16 = pVStack_10[0xc].dwEnv;
  uVar20 = *(uint *)&pVStack_10[0xc].bFlags;
  pVStack_10[0x10].dw_unk0 = pVStack_10[0xb].dw_unk4;
  pVStack_10[0x10].dw_unk4 = uVar24;
  pVStack_10[0x10].dwEnv = uVar25;
  *(void **)&pVStack_10[0x10].bFlags = pvVar18;
  pVStack_10[0x10].pVptr = pvVar17;
  pVStack_10[0x11].dw_unk0 = uVar15;
  pVStack_10[0x11].dw_unk4 = uVar16;
  pVStack_10[0x11].dwEnv = uVar20;
  memset(&pVStack_10[0x11].bFlags,0,0x80);
  memset(pVStack_10 + 0x18,0,0x80);
  pVStack_10[0x11].bFlags = 7;
  pVStack_10[0x11].b_pad0d = 0;
  pVStack_10[0x11].nZvolume = 0x6000;
  pVStack_10[0x12].dw_unk4 = 0x50000007;
  pVStack_10[0x12].dwEnv = 0x8001;
  pVStack_10[0x12].bFlags = 0;
  pVStack_10[0x12].b_pad0d = 0x40;
  pVStack_10[0x12].nZvolume = 0x60ab;
  *(u64 *)&pVStack_10[0x12].pVptr = 0x513513;
  pVStack_10[0x13].dw_unk4 = 0;
  pVStack_10[0x13].dwEnv = 0;
  pVStack_10[0x14].dw_unk0 = 0x80;
  pVStack_10[0x14].dw_unk4 = 0x80;
  pVStack_10[0x14].dwEnv = 0x80;
  pVStack_10[0x14].bFlags = 0x80;
  pVStack_10[0x14].b_pad0d = 0;
  pVStack_10[0x14].nZvolume = 0;
  pVStack_10[0x14].pVptr = (void *)0x7000;
  pVStack_10[0x15].dw_unk0 = 0x7200;
  pVStack_10[0x15].dw_unk4 = 0;
  pVStack_10[0x15].dwEnv = 0;
  pVStack_10[0x15].bFlags = 0;
  pVStack_10[0x15].b_pad0d = 0x20;
  pVStack_10[0x15].nZvolume = 0;
  pVStack_10[0x15].pVptr = (void *)0x1c00;
  pVStack_10[0x16].dwEnv = 0x80;
  pVStack_10[0x16].bFlags = 0x80;
  pVStack_10[0x16].b_pad0d = 0;
  pVStack_10[0x16].nZvolume = 0;
  pVStack_10[0x16].pVptr = &_align_segment;
  pVStack_10[0x17].dw_unk0 = 0x80;
  pVStack_10[0x17].dw_unk4 = 0x9000;
  pVStack_10[0x17].dwEnv = 0x8e00;
  pVStack_10[0x17].bFlags = 0;
  pVStack_10[0x17].b_pad0d = 0;
  pVStack_10[0x17].nZvolume = 0;
  pVStack_10[0x17].pVptr = (void *)0x0;
  pbVar21 = &pVStack_10[0x11].bFlags;
  pVVar10 = pVStack_10 + 0x18;
  iVar28 = 4;
  do {
    uVar11 = *(u64 *)pbVar21;
    uVar15 = *(uint *)(pbVar21 + 8);
    uVar19 = *(u32 *)(pbVar21 + 0xc);
    uVar7 = *(u64 *)(pbVar21 + 0x10);
    uVar16 = *(uint *)(pbVar21 + 0x18);
    uVar20 = *(uint *)(pbVar21 + 0x1c);
    pbVar21 = pbVar21 + 0x20;
    iVar28 = iVar28 + -1;
    pVVar10->dw_unk0 = (uint)uVar11;
    pVVar10->dw_unk4 = (uint)((ulong)uVar11 >> 0x20);
    pVVar10->dwEnv = uVar15;
    pVVar10->bFlags = (char)uVar19;
    pVVar10->b_pad0d = (char)((uint)uVar19 >> 8);
    pVVar10->nZvolume = (short)((uint)uVar19 >> 0x10);
    pVVar10->pVptr = (void *)uVar7;
    pVVar10[1].dw_unk0 = (uint)((ulong)uVar7 >> 0x20);
    pVVar10[1].dw_unk4 = uVar16;
    pVVar10[1].dwEnv = uVar20;
    pVVar10 = (VIF1Prim *)&pVVar10[1].bFlags;
  } while (0 < iVar28);
  uVar15 = __nwa__FUi(0x350);
  pVStack_10->dw_unk0 = uVar15;
  uVar15 = __nwa__FUi(0x350);
  pVStack_10->dw_unk4 = uVar15;
  memset((void *)pVStack_10->dw_unk0,0,0x350);
  memset((void *)pVStack_10->dw_unk4,0,0x350);
  Create__12FrameTextureF6GS_PSMUsUs(&pVStack_10[0x134].pVptr,2,0x200,0x1c0);
  Capture__12FrameTextureFv(&pVStack_10[0x134].pVptr);
  StoreImage__12FrameTextureFiiiiii(&pVStack_10[0x134].pVptr,0x200,0x1c0,0,0,0x200,0x1c0);
  SetPower__8LineBlurFf(0x3f666666,pVStack_10 + 0x150);
  __ct__7_rgba32FUcUcUcUc(auStack_14,0x80,0x80,0x80,0x80);
  Create__8LightPolFiiiifR7_rgba32(0,&pVStack_10[0x29].bFlags,0x100,0xe0,0,0,auStack_14);
  Create__9LightBeltFiiiiifR7_rgba32(0x3f4915b5,&pVStack_10[0x3e].dwEnv,10,0,1,10,0x1e,auStack_14);
  Create__9LightBeltFiiiiifR7_rgba32(0x407b5b23,&pVStack_10[0x5b].dw_unk4,10,0,1,10,0x1e,auStack_14)
  ;
  Create__9LightBeltFiiiiifR7_rgba32(0x3fc9161e,pVStack_10 + 0x78,10,0,1,10,0x1e,auStack_14);
  Create__9LightBeltFiiiiifR7_rgba32(0x4096d048,&pVStack_10[0x94].pVptr,10,0,1,10,0x1e,auStack_14);
  Create__9LightBeltFiiiiifR7_rgba32(0,&pVStack_10[0xb1].bFlags,10,0,1,10,0x1e,auStack_14);
  Create__9LightBeltFiiiiifR7_rgba32(0x40490fd8,&pVStack_10[0xce].dwEnv,10,0,1,10,0x1e,auStack_14);
  Create__9LightBeltFiiiiifR7_rgba32(0x4016d07d,&pVStack_10[0xeb].dw_unk4,10,0,1,10,0x1e,auStack_14)
  ;
  Create__9LightBeltFiiiiifR7_rgba32(0x40aff319,pVStack_10 + 0x108,10,0,1,10,0x1e,auStack_14);
  uVar11 = __ct__7_rgba32FUcUcUcUc(auStack_34,0x40,0x40,0,0x80);
  __as__7_rgba32FRC7_rgba32(auStack_14,uVar11);
  Create__10FirstLightFiiiiR7_rgba32(&pVStack_10[0x124].pVptr,0x100,0xe0,100,100,auStack_14);
  uStack_38 = __nw__FUi(0x10);
  if (uStack_38 != 0) {
    uStack_38 = __ct__9BufMemoryFUlUi(uStack_38,0x4400,0x80);
  }
  pVStack_10[0x28].dw_unk0 = uStack_38;
  uVar11 = getBuffer__9BufMemoryFv(pVStack_10[0x28].dw_unk0);
  pvVar17 = (void *)((int)(void *)uVar11 + 0x400);
  memcpy((void *)uVar11,&l_cluthead,0x400);
  memcpy(pvVar17,&l_pixelhead,0x4000);
  lVar12 = __nw__FUi(0x30);
  uVar15 = 0;
  if (lVar12 != 0) {
    uVar15 = __ct__11CVif1PacketFii(lVar12,0x28,0x10);
  }
  pVStack_10[0x28].dw_unk4 = uVar15;
  uVar9 = GetBufEntry__11GsxFrameBufFv(*(u32 *)(camera__4CApp + 0x340));
  RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
            (pVStack_10[0x28].dw_unk4,uVar9,0x1b,2,pvVar17,0x400,0,0);
  uVar15 = getAdress__17ClutAdressControlFi(app__4CApp + 0x80,10);
  RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
            (pVStack_10[0x28].dw_unk4,uVar15 & 0xffff,0,1,uVar11,0x40,0,0);
  Ref__11CVif1PacketFP1UiUiUiUi(pVStack_10[0x28].dw_unk4,&pVStack_10[0x1e].dwEnv,3,0,0x50000003,0);
  Ret__11CVif1PacketFUi(pVStack_10[0x28].dw_unk4,0);
  Terminate__11CVif1PacketFv(pVStack_10[0x28].dw_unk4);
  memset(&pVStack_10[0x1e].dwEnv,0,0x30);
  pVStack_10[0x1e].dwEnv = 0x8002;
  pVStack_10[0x1e].bFlags = 0;
  pVStack_10[0x1e].b_pad0d = 0;
  pVStack_10[0x1e].nZvolume = 0x1000;
  *(u64 *)&pVStack_10[0x1e].pVptr = 0xe;
  pVStack_10[0x1f].bFlags = 0x3f;
  pVStack_10[0x1f].b_pad0d = 0;
  pVStack_10[0x1f].nZvolume = 0;
  pVStack_10[0x1f].pVptr = (void *)0x0;
  iVar28 = GetBufEntry__11GsxFrameBufFv(*(u32 *)(camera__4CApp + 0x340));
  uVar13 = GetBekijo__FUi(0x80);
  uVar14 = GetBekijo__FUi(0x80);
  uVar13 = (long)(int)uVar15 << 0x25 |
           (uVar14 & 0xffffffff) << 0x1e | (long)iVar28 | 0x1b08000U | (uVar13 & 0xffffffff) << 0x1a
           | 0x400000000 | 0x2000000000000000;
  pVStack_10[0x20].dw_unk0 = (int)uVar13;
  pVStack_10[0x20].dw_unk4 = (int)(uVar13 >> 0x20);
  pVStack_10[0x20].dwEnv = 6;
  pVStack_10[0x20].bFlags = 0;
  pVStack_10[0x20].b_pad0d = 0;
  pVStack_10[0x20].nZvolume = 0;
  lVar12 = __nw__FUi(0x10);
  uVar15 = 0;
  if (lVar12 != 0) {
    uVar15 = __ct__9BufMemoryFUlUi(lVar12,0x1040,0x80);
  }
  pVStack_10[0x28].dwEnv = uVar15;
  uVar11 = getBuffer__9BufMemoryFv(pVStack_10[0x28].dwEnv);
  pvVar17 = (void *)((int)(void *)uVar11 + 0x40);
  memcpy((void *)uVar11,&line_001_cluthead,0x40);
  memcpy(pvVar17,&line_001_pixelhead,0x1000);
  lVar12 = __nw__FUi(0x30);
  uVar19 = 0;
  if (lVar12 != 0) {
    uVar19 = __ct__11CVif1PacketFii(lVar12,0x28,0x10);
  }
  pVStack_10[0x28].bFlags = (char)uVar19;
  pVStack_10[0x28].b_pad0d = (char)((uint)uVar19 >> 8);
  pVStack_10[0x28].nZvolume = (short)((uint)uVar19 >> 0x10);
  uVar9 = GetBufEntry__11GsxFrameBufFv(*(u32 *)(camera__4CApp + 0x340));
  uVar19._0_1_ = pVStack_10[0x28].bFlags;
  uVar19._1_1_ = pVStack_10[0x28].b_pad0d;
  uVar19._2_2_ = pVStack_10[0x28].nZvolume;
  RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi(uVar19,uVar9,0x2c,1,pvVar17,0x100,0,0);
  uVar15 = getAdress__17ClutAdressControlFi(app__4CApp + 0x80,10);
  uVar1._0_1_ = pVStack_10[0x28].bFlags;
  uVar1._1_1_ = pVStack_10[0x28].b_pad0d;
  uVar1._2_2_ = pVStack_10[0x28].nZvolume;
  RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi(uVar1,uVar15 & 0xffff,0,1,uVar11,4,0,0);
  uVar2._0_1_ = pVStack_10[0x28].bFlags;
  uVar2._1_1_ = pVStack_10[0x28].b_pad0d;
  uVar2._2_2_ = pVStack_10[0x28].nZvolume;
  Ref__11CVif1PacketFP1UiUiUiUi(uVar2,&pVStack_10[0x20].pVptr,3,0,0x50000003,0);
  uVar3._0_1_ = pVStack_10[0x28].bFlags;
  uVar3._1_1_ = pVStack_10[0x28].b_pad0d;
  uVar3._2_2_ = pVStack_10[0x28].nZvolume;
  Ret__11CVif1PacketFUi(uVar3,0);
  uVar4._0_1_ = pVStack_10[0x28].bFlags;
  uVar4._1_1_ = pVStack_10[0x28].b_pad0d;
  uVar4._2_2_ = pVStack_10[0x28].nZvolume;
  Terminate__11CVif1PacketFv(uVar4);
  memset(&pVStack_10[0x20].pVptr,0,0x30);
  *(u64 *)&pVStack_10[0x20].pVptr = 0x1000000000008002;
  pVStack_10[0x21].dw_unk4 = 0xe;
  pVStack_10[0x21].dwEnv = 0;
  pVStack_10[0x22].dw_unk0 = 0x3f;
  pVStack_10[0x22].dw_unk4 = 0;
  iVar28 = GetBufEntry__11GsxFrameBufFv(*(u32 *)(camera__4CApp + 0x340));
  uVar13 = GetBekijo__FUi(0x20);
  uVar14 = GetBekijo__FUi(0x100);
  uVar13 = (long)(int)uVar15 << 0x25 |
           (uVar14 & 0xffffffff) << 0x1e | (long)iVar28 | 0x2c04000U | (uVar13 & 0xffffffff) << 0x1a
           | 0x400000000 | 0x2000000000000000;
  pVStack_10[0x22].dwEnv = (int)uVar13;
  pVStack_10[0x22].bFlags = (char)(uVar13 >> 0x20);
  pVStack_10[0x22].b_pad0d = (char)(uVar13 >> 0x28);
  pVStack_10[0x22].nZvolume = (short)(uVar13 >> 0x30);
  *(u64 *)&pVStack_10[0x22].pVptr = 6;
  lVar12 = __nw__FUi(0x10);
  pvVar17 = (void *)0x0;
  if (lVar12 != 0) {
    pvVar17 = (void *)__ct__9BufMemoryFUlUi(lVar12,0x8040,0x80);
  }
  pVStack_10[0x28].pVptr = pvVar17;
  uVar11 = getBuffer__9BufMemoryFv(pVStack_10[0x28].pVptr);
  pvVar17 = (void *)((int)(void *)uVar11 + 0x40);
  memcpy((void *)uVar11,&ligh_09_cluthead,0x40);
  memcpy(pvVar17,&ligh_09_pixelhead,0x8000);
  lVar12 = __nw__FUi(0x30);
  uVar15 = 0;
  if (lVar12 != 0) {
    uVar15 = __ct__11CVif1PacketFii(lVar12,0x28,0x10);
  }
  pVStack_10[0x29].dw_unk0 = uVar15;
  uVar9 = GetBufEntry__11GsxFrameBufFv(*(u32 *)(camera__4CApp + 0x340));
  RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
            (pVStack_10[0x29].dw_unk0,uVar9,0x2c,4,pvVar17,0x800,0,0);
  uVar15 = getAdress__17ClutAdressControlFi(app__4CApp + 0x80,10);
  RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
            (pVStack_10[0x29].dw_unk0,uVar15 & 0xffff,0,1,uVar11,4,0,0);
  uVar11 = Ref__11CVif1PacketFP1UiUiUiUi
                     (pVStack_10[0x29].dw_unk0,&pVStack_10[0x23].dw_unk4,3,0,0x50000003,0);
  Ret__11CVif1PacketFUi(pVStack_10[0x29].dw_unk0,0,uVar11);
  Terminate__11CVif1PacketFv(pVStack_10[0x29].dw_unk0);
  memset(&pVStack_10[0x23].dw_unk4,0,0x30);
  pVStack_10[0x23].dw_unk4 = 0x8002;
  pVStack_10[0x23].dwEnv = 0x10000000;
  pVStack_10[0x23].bFlags = 0xe;
  pVStack_10[0x23].b_pad0d = 0;
  pVStack_10[0x23].nZvolume = 0;
  pVStack_10[0x23].pVptr = (void *)0x0;
  pVStack_10[0x24].dwEnv = 0x3f;
  pVStack_10[0x24].bFlags = 0;
  pVStack_10[0x24].b_pad0d = 0;
  pVStack_10[0x24].nZvolume = 0;
  iVar28 = GetBufEntry__11GsxFrameBufFv(*(u32 *)(camera__4CApp + 0x340));
  uVar13 = GetBekijo__FUi(0x100);
  uVar14 = GetBekijo__FUi(0x100);
  *(ulong *)&pVStack_10[0x24].pVptr =
       (long)(int)uVar15 << 0x25 |
       (uVar14 & 0xffffffff) << 0x1e | (long)iVar28 | 0x2c10000U | (uVar13 & 0xffffffff) << 0x1a |
       0x400000000 | 0x2000000000000000;
  pVStack_10[0x25].dw_unk4 = 6;
  pVStack_10[0x25].dwEnv = 0;
  return pVStack_10;
}

/* ---- 0x003b3d80 size 0x314  BtlInBoss::~BtlInBoss(v)
 *      mangled: __dt__9BtlInBossFv */
int * __dt__9BtlInBossFv(int *param_1,short param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 != (int *)0x0) {
    param_1[4] = (int)__vt__9BtlInBoss;
    param_1[7] = 0x4075d0;
    param_1[0xd] = 0x4075e0;
    ourBtlIn__9BtlInBoss = 0;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
      *param_1 = 0;
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
      param_1[1] = 0;
    }
    if (param_1[0xc9] != 0) {
      iVar1 = param_1[0xc9];
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0xc) + 8))(iVar1,1);
      }
      param_1[0xc9] = 0;
    }
    if (param_1[200] != 0) {
      __dt__9BufMemoryFv(param_1[200],1);
      param_1[200] = 0;
    }
    if (param_1[0xcb] != 0) {
      iVar1 = param_1[0xcb];
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0xc) + 8))(iVar1,1);
      }
      param_1[0xcb] = 0;
    }
    if (param_1[0xca] != 0) {
      __dt__9BufMemoryFv(param_1[0xca],1);
      param_1[0xca] = 0;
    }
    if (param_1[0xcc] != 0) {
      __dt__9BufMemoryFv(param_1[0xcc],1);
      param_1[0xcc] = 0;
    }
    if (param_1[0xcd] != 0) {
      iVar1 = param_1[0xcd];
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0xc) + 8))(iVar1,1);
      }
      param_1[0xcd] = 0;
    }
    piVar2 = param_1;
    if (param_1 != (int *)0x0) {
      piVar2 = param_1 + 8;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,piVar2);
    __dt__8LineBlurFv(param_1 + 0x690,0xffffffffffffffff);
    __dt__12FrameTextureFv(param_1 + 0x608,0xffffffffffffffff);
    __dt__10FirstLightFv(param_1 + 0x5b8,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x138,0x3b3c60,0x240,8);
    __dt__8LightPolFv(param_1 + 0xd0,0xffffffffffffffff);
    __dt__7CPolObjFv(param_1 + 8,0);
    __dt__17DelayDeleteObjectFv(param_1 + 5,0);
    __dt__8VIF1PrimFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003b40a0 size 0x30  BtlInBoss::getPacket(v)
 *      mangled: getPacket__9BtlInBossFv */
void getPacket__9BtlInBossFv(u32 param_1)

{
  GetDrawPacket__9BtlInBossFi(param_1,m_Env__8VIF1Prim & 1);
  return;
}

/* ---- 0x003b40d0 size 0x5a4  BtlInBoss::GetDrawPacket(i)
 *      mangled: GetDrawPacket__9BtlInBossFi */
u32 GetDrawPacket__9BtlInBossFi(int param_1,int param_2)

{
  u32 uVar1;
  u32 *puVar2;
  u32 *puVar3;
  int iVar4;
  
  puVar3 = *(u32 **)(param_1 + param_2 * 4);
  memset(puVar3,0,0x350);
  *puVar3 = 0x50000000;
  puVar3[1] = param_1 + 0x1840;
  puVar3[3] = 0x13000000;
  puVar3[4] = 0x50000000;
  uVar1 = GetBuffer__7CPacketCFv(*(u32 *)(param_1 + 0x1a24));
  puVar3[5] = uVar1;
  puVar3[8] = 0x50000000;
  puVar3[9] = param_1 + 0x40;
  puVar2 = puVar3 + 0xc;
  *(int *)(param_1 + param_2 * 0x80 + 0x1a0) = 0x7000 - *(int *)(param_1 + 0x1804);
  *(int *)(param_1 + param_2 * 0x80 + 0x1a4) = 0x7200 - *(int *)(param_1 + 0x1804);
  *(int *)(param_1 + param_2 * 0x80 + 0x1d0) = *(int *)(param_1 + 0x1804) + 0x9000;
  *(int *)(param_1 + param_2 * 0x80 + 0x1d4) = *(int *)(param_1 + 0x1804) + 0x8e00;
  if (*(int *)(param_1 + param_2 * 0x80 + 0x1a0) < 0) {
    *(u32 *)(param_1 + param_2 * 0x80 + 0x1a0) = 0;
  }
  if (*(int *)(param_1 + param_2 * 0x80 + 0x1a4) < 0) {
    *(u32 *)(param_1 + param_2 * 0x80 + 0x1a4) = 0;
  }
  if (0xffff < *(int *)(param_1 + param_2 * 0x80 + 0x1d0)) {
    *(u32 *)(param_1 + param_2 * 0x80 + 0x1d0) = 0xffff;
  }
  if (0xffff < *(int *)(param_1 + param_2 * 0x80 + 0x1d4)) {
    *(u32 *)(param_1 + param_2 * 0x80 + 0x1d4) = 0xffff;
  }
  iVar4 = *(int *)(param_1 + 0x180c);
  if (iVar4 == 9999) {
    *puVar2 = 0x50000000;
    puVar3[0xd] = param_1 + param_2 * 0x60 + 0xa0;
    puVar2 = puVar3 + 0x10;
  }
  else if ((iVar4 == 0x15) || (iVar4 == 0x14)) {
    *puVar2 = 0x50000000;
    puVar3[0xd] = param_1 + param_2 * 0x60 + 0xa0;
    puVar3[0x10] = 0x50000000;
    puVar3[0x11] = param_1 + param_2 * 0x80 + 0x160;
    puVar3[0x14] = 0x50000000;
    uVar1 = GetBuffer__7CPacketCFv(*(u32 *)(param_1 + 0x32c));
    puVar3[0x15] = uVar1;
    puVar3[0x17] = 0x13000000;
    puVar3 = puVar3 + 0x18;
    for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
      *puVar3 = 0x50000000;
      uVar1 = getPacket__9LightBeltFv(param_1 + iVar4 * 0x240 + 0x4e0);
      puVar3[1] = uVar1;
      puVar3 = puVar3 + 4;
    }
    *puVar3 = 0x50000000;
    uVar1 = GetBuffer__7CPacketCFv(*(u32 *)(param_1 + 0x324));
    puVar3[1] = uVar1;
    puVar3[3] = 0x13000000;
    puVar3[4] = 0x50000000;
    uVar1 = getPacket__8LightPolFv(param_1 + 0x340);
    puVar3[5] = uVar1;
    puVar2 = (u32 *)SetPacket__8LineBlurFP4_QWD(param_1 + 0x1a40,puVar3 + 8);
  }
  else if (((((iVar4 == 0xf) || (iVar4 == 0xe)) || (iVar4 == 0xd)) ||
           (((iVar4 == 0xc || (iVar4 == 0xb)) || ((iVar4 == 10 || ((iVar4 == 9 || (iVar4 == 8)))))))
           ) || ((iVar4 == 7 ||
                 (((((iVar4 == 6 || (iVar4 == 5)) || (iVar4 == 4)) || ((iVar4 == 3 || (iVar4 == 2)))
                   ) || ((iVar4 == 1 || (iVar4 == 0)))))))) {
    *puVar2 = 0x50000000;
    puVar3[0xd] = param_1 + param_2 * 0x60 + 0xa0;
    puVar3[0x10] = 0x50000000;
    puVar3[0x11] = param_1 + param_2 * 0x80 + 0x160;
    puVar3[0x14] = 0x50000000;
    uVar1 = GetBuffer__7CPacketCFv(*(u32 *)(param_1 + 0x334));
    puVar3[0x15] = uVar1;
    puVar3[0x17] = 0x13000000;
    puVar3[0x18] = 0x50000000;
    uVar1 = getPacket__10FirstLightFv(param_1 + 0x16e0);
    puVar3[0x19] = uVar1;
    puVar2 = (u32 *)SetPacket__8LineBlurFP4_QWD(param_1 + 0x1a40,puVar3 + 0x1c);
  }
  *puVar2 = 0x60000000;
  *(int *)(param_1 + param_2 * 0x60 + 0xcc) = (int)*(short *)(param_1 + 0x1800);
  *(int *)(param_1 + param_2 * 0x60 + 0xec) = (int)*(short *)(param_1 + 0x1800);
  return *(u32 *)(param_1 + param_2 * 4);
}

/* ---- 0x003b4680 size 0x62c  BtlInBoss::Polling(v)
 *      mangled: Polling__9BtlInBossFv */
u64 Polling__9BtlInBossFv(VIF1Prim *param_1)

{
  void *pvVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  u16 uVar5;
  
  pvVar1 = param_1[0x133].pVptr;
  if (pvVar1 != (void *)0x270f) {
    if (pvVar1 == (void *)0x15) {
      uVar2 = param_1[0x134].dw_unk0 + 1;
      param_1[0x134].dw_unk0 = uVar2;
      if ((int)uVar2 < 0x5b) {
        *(int *)&param_1[0x133].bFlags = *(int *)&param_1[0x133].bFlags + 2;
        param_1[0x133].dwEnv = param_1[0x133].dwEnv + *(int *)&param_1[0x133].bFlags;
        param_1[0x3d].dw_unk4 = param_1[0x133].dwEnv >> 5;
        param_1[0x3d].dwEnv = param_1[0x133].dwEnv >> 5;
        *(float *)&param_1[0x3d].bFlags = *(float *)&param_1[0x3d].bFlags + 0.041;
        for (iVar3 = 0; iVar3 < 8; iVar3 = iVar3 + 1) {
          *(int *)((int)param_1 + iVar3 * 0x240 + 0x700) =
               *(int *)((int)param_1 + iVar3 * 0x240 + 0x700) + 10;
          *(int *)((int)param_1 + iVar3 * 0x240 + 0x708) =
               *(int *)((int)param_1 + iVar3 * 0x240 + 0x708) + 0x14;
          if (500 < *(int *)((int)param_1 + iVar3 * 0x240 + 0x708)) {
            *(u32 *)((int)param_1 + iVar3 * 0x240 + 0x708) = 500;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(&param_1[0x133].pVptr,9999);
      }
    }
    else if (pvVar1 == (void *)0x14) {
      uVar2 = param_1[0x134].dw_unk0 + 1;
      param_1[0x134].dw_unk0 = uVar2;
      if ((int)uVar2 < 0x1f) {
        *(int *)&param_1[0x133].bFlags = *(int *)&param_1[0x133].bFlags + 8;
        param_1[0x133].dwEnv = param_1[0x133].dwEnv + *(int *)&param_1[0x133].bFlags;
        param_1[0x3d].dw_unk4 = param_1[0x133].dwEnv >> 5;
        param_1[0x3d].dwEnv = param_1[0x133].dwEnv >> 5;
        *(float *)&param_1[0x3d].bFlags = *(float *)&param_1[0x3d].bFlags + 0.041;
        for (iVar3 = 0; iVar3 < 8; iVar3 = iVar3 + 1) {
          *(int *)((int)param_1 + iVar3 * 0x240 + 0x708) =
               *(int *)((int)param_1 + iVar3 * 0x240 + 0x708) + 0x14;
          if (500 < *(int *)((int)param_1 + iVar3 * 0x240 + 0x708)) {
            *(u32 *)((int)param_1 + iVar3 * 0x240 + 0x708) = 500;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(&param_1[0x133].pVptr,0x15);
      }
    }
    else if (pvVar1 == (void *)0xf) {
      SetFase__7tagFaseFi(&param_1[0x133].pVptr,0x14);
      uVar2 = (uint)param_1[0x133].pVptr & 3;
      if (((int)param_1[0x133].pVptr < 0) && (uVar2 != 0)) {
        uVar2 = uVar2 - 4;
      }
      pvVar1 = param_1[0x133].pVptr;
      if ((int)pvVar1 < 0) {
        pvVar1 = (void *)((int)pvVar1 + 3);
      }
      SetTexPos__10FirstLightFii(&param_1[0x124].pVptr,uVar2,(int)pvVar1 >> 2);
    }
    else if ((((((pvVar1 == (void *)0xe) || (pvVar1 == (void *)0xd)) || (pvVar1 == (void *)0xc)) ||
              ((pvVar1 == (void *)0xb || (pvVar1 == (void *)0xa)))) ||
             (((pvVar1 == (void *)0x9 || ((pvVar1 == (void *)0x8 || (pvVar1 == (void *)0x7)))) ||
              (pvVar1 == (void *)0x6)))) ||
            ((((pvVar1 == (void *)0x5 || (pvVar1 == (void *)0x4)) || (pvVar1 == (void *)0x3)) ||
             (((pvVar1 == (void *)0x2 || (pvVar1 == (void *)0x1)) || (pvVar1 == (void *)0x0)))))) {
      uVar2 = (uint)param_1[0x133].pVptr & 3;
      if (((int)param_1[0x133].pVptr < 0) && (uVar2 != 0)) {
        uVar2 = uVar2 - 4;
      }
      pvVar1 = param_1[0x133].pVptr;
      if ((int)pvVar1 < 0) {
        pvVar1 = (void *)((int)pvVar1 + 3);
      }
      SetTexPos__10FirstLightFii(&param_1[0x124].pVptr,uVar2,(int)pvVar1 >> 2);
      param_1[0x133].pVptr = (void *)((int)param_1[0x133].pVptr + 1);
      SetFase__7tagFaseFi(&param_1[0x133].pVptr);
    }
  }
  uVar2 = param_1[0x134].dw_unk4;
  if (uVar2 == 3) {
    if (param_1[0x133].pVptr == (void *)0x270f) {
      ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,param_1);
      pbVar4 = (byte *)0x0;
      if (param_1 != (VIF1Prim *)0x0) {
        pbVar4 = &param_1[1].bFlags;
      }
      Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,pbVar4);
      (**(code **)(param_1[1].dwEnv + 0xc))();
      SetFase__7tagFaseFi(&param_1[0x133].pVptr,10000);
    }
  }
  else if (uVar2 == 2) {
    uVar2 = param_1[0x134].dwEnv + 1;
    param_1[0x134].dwEnv = uVar2;
    if ((int)uVar2 < 9) {
      *(short *)&param_1[0x133].dw_unk4 = (short)param_1[0x133].dw_unk4 + -0x10;
      if ((short)param_1[0x133].dw_unk4 < 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = (u16)param_1[0x133].dw_unk4;
      }
      *(u16 *)&param_1[0x133].dw_unk4 = uVar5;
    }
    else {
      SetFase__7tagFaseFi(&param_1[0x134].dw_unk4,3);
    }
  }
  else if ((uVar2 == 1) && (param_1[0x133].pVptr == (void *)0x270f)) {
    SetFase__7tagFaseFi(&param_1[0x134].dw_unk4,2);
  }
  return 0;
}

/* ---- 0x003b4cf0 size 0x104  BtlInBoss::OnlyDraw(v)
 *      mangled: OnlyDraw__9BtlInBossFv */
void OnlyDraw__9BtlInBossFv(int param_1)

{
  u32 uVar1;
  
  (**(code **)(*(int *)(ourBtlIn__9BtlInBoss + 0x10) + 0x30))();
  sceDmaSync(dmaVif1__6DmaMan,0,0);
  sceGsSyncPath(0,0);
  memset((void *)(param_1 + 0x2f0),0,0x30);
  *(u32 *)(param_1 + 0x2f0) = 0x50000000;
  uVar1 = GetDrawPacket__9BtlInBossFi(param_1,(m_Env__8VIF1Prim & 1) == 0);
  *(u32 *)(param_1 + 0x2f4) = uVar1;
  *(u32 *)(param_1 + 0x300) = 0x70000000;
  FlushCache(0);
  REG_DMAC_1_VIF1_CHCR = 0x41;
  sceDmaSend(dmaVif1__6DmaMan,param_1 + 0x2f0);
  DrawSync__3GsxFii(0,0);
  return;
}

/* ---- 0x003b4e00 size 0x50  BtlInBoss::CaptureBtlIn(v)
 *      mangled: CaptureBtlIn__9BtlInBossFv */
void CaptureBtlIn__9BtlInBossFv(void)

{
  u32 uVar1;
  long lVar2;
  
  lVar2 = __nw__FUi(0x1fb20);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9BtlInBossFv(lVar2);
  }
  ourBtlIn__9BtlInBoss = uVar1;
  return;
}

/* ---- 0x003b4e50 size 0x7c  BtlInBoss::StartBtlIn(v)
 *      mangled: StartBtlIn__9BtlInBossFv */
void StartBtlIn__9BtlInBossFv(void)

{
  byte *pbVar1;
  
  if (ourBtlIn__9BtlInBoss != (VIF1Prim *)0x0) {
    pbVar1 = (byte *)0x0;
    if (ourBtlIn__9BtlInBoss != (VIF1Prim *)0x0) {
      pbVar1 = &ourBtlIn__9BtlInBoss[1].bFlags;
    }
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,pbVar1,0x80,0);
    AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,0xe,ourBtlIn__9BtlInBoss);
    OnlyDraw__9BtlInBossFv(ourBtlIn__9BtlInBoss);
  }
  return;
}

/* ---- 0x003b4ed0 size 0x38  BtlInBoss::StopBtlIn(v)
 *      mangled: StopBtlIn__9BtlInBossFv */
void StopBtlIn__9BtlInBossFv(void)

{
  if (ourBtlIn__9BtlInBoss != 0) {
    SetFase__7tagFaseFi(ourBtlIn__9BtlInBoss + 0x1814,1);
  }
  return;
}

/* ---- 0x003b5dc0 size 0x8  BtlInBoss::@20@__dt(v)
 *      mangled: @20@__dt__9BtlInBossFv */
int * _20___dt__9BtlInBossFv(int param_1,short param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + -0x14);
  if (piVar1 != (int *)0x0) {
    *(u8 **)(param_1 + -4) = __vt__9BtlInBoss;
    *(u32 *)(param_1 + 8) = 0x4075d0;
    *(u32 *)(param_1 + 0x20) = 0x4075e0;
    ourBtlIn__9BtlInBoss = 0;
    if (*piVar1 != 0) {
      __dla__FPv(*piVar1);
      *piVar1 = 0;
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(u32 *)(param_1 + -0x10));
      *(u32 *)(param_1 + -0x10) = 0;
    }
    if (*(int *)(param_1 + 0x310) != 0) {
      iVar2 = *(int *)(param_1 + 0x310);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0xc) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x310) = 0;
    }
    if (*(int *)(param_1 + 0x30c) != 0) {
      __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x30c),1);
      *(u32 *)(param_1 + 0x30c) = 0;
    }
    if (*(int *)(param_1 + 0x318) != 0) {
      iVar2 = *(int *)(param_1 + 0x318);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0xc) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x318) = 0;
    }
    if (*(int *)(param_1 + 0x314) != 0) {
      __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x314),1);
      *(u32 *)(param_1 + 0x314) = 0;
    }
    if (*(int *)(param_1 + 0x31c) != 0) {
      __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x31c),1);
      *(u32 *)(param_1 + 0x31c) = 0;
    }
    if (*(int *)(param_1 + 800) != 0) {
      iVar2 = *(int *)(param_1 + 800);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0xc) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 800) = 0;
    }
    iVar2 = 0;
    if (piVar1 != (int *)0x0) {
      iVar2 = param_1 + 0xc;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    __dt__8LineBlurFv(param_1 + 0x1a2c,0xffffffffffffffff);
    __dt__12FrameTextureFv(param_1 + 0x180c,0xffffffffffffffff);
    __dt__10FirstLightFv(param_1 + 0x16cc,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x4cc,0x3b3c60,0x240,8);
    __dt__8LightPolFv(param_1 + 0x32c,0xffffffffffffffff);
    __dt__7CPolObjFv(param_1 + 0xc,0);
    __dt__17DelayDeleteObjectFv(param_1,0);
    __dt__8VIF1PrimFv(piVar1,0);
    if (0 < param_2) {
      __dl__FPv(piVar1);
    }
  }
  return piVar1;
}

/* ---- 0x003b5dd0 size 0x8  BtlInBoss::@32@Polling(v)
 *      mangled: @32@Polling__9BtlInBossFv */
u64 _32_Polling__9BtlInBossFv(int param_1)

{
  int iVar1;
  VIF1Prim *prim;
  uint uVar2;
  u16 uVar3;
  
  prim = (VIF1Prim *)(param_1 + -0x20);
  iVar1 = *(int *)(param_1 + 0x17ec);
  if (iVar1 != 9999) {
    if (iVar1 == 0x15) {
      iVar1 = *(int *)(param_1 + 0x17f0) + 1;
      *(int *)(param_1 + 0x17f0) = iVar1;
      if (iVar1 < 0x5b) {
        *(int *)(param_1 + 0x17e8) = *(int *)(param_1 + 0x17e8) + 2;
        *(int *)(param_1 + 0x17e4) = *(int *)(param_1 + 0x17e4) + *(int *)(param_1 + 0x17e8);
        *(uint *)(param_1 + 0x4a8) = *(uint *)(param_1 + 0x17e4) >> 5;
        *(uint *)(param_1 + 0x4ac) = *(uint *)(param_1 + 0x17e4) >> 5;
        *(float *)(param_1 + 0x4b0) = *(float *)(param_1 + 0x4b0) + 0.041;
        for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
          *(int *)((int)prim + iVar1 * 0x240 + 0x700) =
               *(int *)((int)prim + iVar1 * 0x240 + 0x700) + 10;
          *(int *)((int)prim + iVar1 * 0x240 + 0x708) =
               *(int *)((int)prim + iVar1 * 0x240 + 0x708) + 0x14;
          if (500 < *(int *)((int)prim + iVar1 * 0x240 + 0x708)) {
            *(u32 *)((int)prim + iVar1 * 0x240 + 0x708) = 500;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x17ec,9999);
      }
    }
    else if (iVar1 == 0x14) {
      iVar1 = *(int *)(param_1 + 0x17f0) + 1;
      *(int *)(param_1 + 0x17f0) = iVar1;
      if (iVar1 < 0x1f) {
        *(int *)(param_1 + 0x17e8) = *(int *)(param_1 + 0x17e8) + 8;
        *(int *)(param_1 + 0x17e4) = *(int *)(param_1 + 0x17e4) + *(int *)(param_1 + 0x17e8);
        *(uint *)(param_1 + 0x4a8) = *(uint *)(param_1 + 0x17e4) >> 5;
        *(uint *)(param_1 + 0x4ac) = *(uint *)(param_1 + 0x17e4) >> 5;
        *(float *)(param_1 + 0x4b0) = *(float *)(param_1 + 0x4b0) + 0.041;
        for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
          *(int *)((int)prim + iVar1 * 0x240 + 0x708) =
               *(int *)((int)prim + iVar1 * 0x240 + 0x708) + 0x14;
          if (500 < *(int *)((int)prim + iVar1 * 0x240 + 0x708)) {
            *(u32 *)((int)prim + iVar1 * 0x240 + 0x708) = 500;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x17ec,0x15);
      }
    }
    else if (iVar1 == 0xf) {
      SetFase__7tagFaseFi(param_1 + 0x17ec,0x14);
      uVar2 = *(uint *)(param_1 + 0x17ec) & 3;
      if (((int)*(uint *)(param_1 + 0x17ec) < 0) && (uVar2 != 0)) {
        uVar2 = uVar2 - 4;
      }
      iVar1 = *(int *)(param_1 + 0x17ec);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 3;
      }
      SetTexPos__10FirstLightFii(param_1 + 0x16c0,uVar2,iVar1 >> 2);
    }
    else if ((((((iVar1 == 0xe) || (iVar1 == 0xd)) || (iVar1 == 0xc)) ||
              ((iVar1 == 0xb || (iVar1 == 10)))) ||
             (((iVar1 == 9 || ((iVar1 == 8 || (iVar1 == 7)))) || (iVar1 == 6)))) ||
            ((((iVar1 == 5 || (iVar1 == 4)) || (iVar1 == 3)) ||
             (((iVar1 == 2 || (iVar1 == 1)) || (iVar1 == 0)))))) {
      uVar2 = *(uint *)(param_1 + 0x17ec) & 3;
      if (((int)*(uint *)(param_1 + 0x17ec) < 0) && (uVar2 != 0)) {
        uVar2 = uVar2 - 4;
      }
      iVar1 = *(int *)(param_1 + 0x17ec);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 3;
      }
      SetTexPos__10FirstLightFii(param_1 + 0x16c0,uVar2,iVar1 >> 2);
      *(int *)(param_1 + 0x17ec) = *(int *)(param_1 + 0x17ec) + 1;
      SetFase__7tagFaseFi(param_1 + 0x17ec);
    }
  }
  iVar1 = *(int *)(param_1 + 0x17f4);
  if (iVar1 == 3) {
    if (*(int *)(param_1 + 0x17ec) == 9999) {
      ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
      iVar1 = 0;
      if (prim != (VIF1Prim *)0x0) {
        iVar1 = param_1;
      }
      Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar1);
      (**(code **)(*(int *)(param_1 + -4) + 0xc))();
      SetFase__7tagFaseFi(param_1 + 0x17ec,10000);
    }
  }
  else if (iVar1 == 2) {
    iVar1 = *(int *)(param_1 + 0x17f8) + 1;
    *(int *)(param_1 + 0x17f8) = iVar1;
    if (iVar1 < 9) {
      *(short *)(param_1 + 0x17e0) = *(short *)(param_1 + 0x17e0) + -0x10;
      if (*(short *)(param_1 + 0x17e0) < 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = *(u16 *)(param_1 + 0x17e0);
      }
      *(u16 *)(param_1 + 0x17e0) = uVar3;
    }
    else {
      SetFase__7tagFaseFi(param_1 + 0x17f4,3);
    }
  }
  else if ((iVar1 == 1) && (*(int *)(param_1 + 0x17ec) == 9999)) {
    SetFase__7tagFaseFi(param_1 + 0x17f4,2);
  }
  return 0;
}

/* ---- 0x003b5de0 size 0x8  BtlInBoss::@32@__dt(v)
 *      mangled: @32@__dt__9BtlInBossFv */
int * _32___dt__9BtlInBossFv(int param_1,short param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + -0x20);
  if (piVar1 != (int *)0x0) {
    *(u8 **)(param_1 + -0x10) = __vt__9BtlInBoss;
    *(u32 *)(param_1 + -4) = 0x4075d0;
    *(u32 *)(param_1 + 0x14) = 0x4075e0;
    ourBtlIn__9BtlInBoss = 0;
    if (*piVar1 != 0) {
      __dla__FPv(*piVar1);
      *piVar1 = 0;
    }
    if (*(int *)(param_1 + -0x1c) != 0) {
      __dla__FPv(*(u32 *)(param_1 + -0x1c));
      *(u32 *)(param_1 + -0x1c) = 0;
    }
    if (*(int *)(param_1 + 0x304) != 0) {
      iVar2 = *(int *)(param_1 + 0x304);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0xc) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x304) = 0;
    }
    if (*(int *)(param_1 + 0x300) != 0) {
      __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x300),1);
      *(u32 *)(param_1 + 0x300) = 0;
    }
    if (*(int *)(param_1 + 0x30c) != 0) {
      iVar2 = *(int *)(param_1 + 0x30c);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0xc) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x30c) = 0;
    }
    if (*(int *)(param_1 + 0x308) != 0) {
      __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x308),1);
      *(u32 *)(param_1 + 0x308) = 0;
    }
    if (*(int *)(param_1 + 0x310) != 0) {
      __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x310),1);
      *(u32 *)(param_1 + 0x310) = 0;
    }
    if (*(int *)(param_1 + 0x314) != 0) {
      iVar2 = *(int *)(param_1 + 0x314);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0xc) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x314) = 0;
    }
    iVar2 = 0;
    if (piVar1 != (int *)0x0) {
      iVar2 = param_1;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    __dt__8LineBlurFv(param_1 + 0x1a20,0xffffffffffffffff);
    __dt__12FrameTextureFv(param_1 + 0x1800,0xffffffffffffffff);
    __dt__10FirstLightFv(param_1 + 0x16c0,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x4c0,0x3b3c60,0x240,8);
    __dt__8LightPolFv(param_1 + 800,0xffffffffffffffff);
    __dt__7CPolObjFv(param_1,0);
    __dt__17DelayDeleteObjectFv(param_1 + -0xc,0);
    __dt__8VIF1PrimFv(piVar1,0);
    if (0 < param_2) {
      __dl__FPv(piVar1);
    }
  }
  return piVar1;
}

