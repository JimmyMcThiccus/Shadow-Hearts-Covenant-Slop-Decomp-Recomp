/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FldTeamChange   functions: 16
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FldTeamChange.md).
 */

/* JP: 0x004a31b0  FldTeamChange::SetData(BufMemory*)   [SetData__13FldTeamChangeFP9BufMemory]  size=0x24 */
void SetData__13FldTeamChangeFP9BufMemory(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x18) = param_2;
  return;
}

/* JP: 0x004dd1c0  FldTeamChange::Delete()   [Delete__13FldTeamChangeFv]  size=0x70 */
void Delete__13FldTeamChangeFv(int param_1)

{
  if (((ulong)*(byte *)(param_1 + 0x40) & 0x1f) >> 3 == 0) {
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xe7 | 8;
    Clr__13FldTeamChangeFv(param_1);
    Entry__13FldTeamChangeFv(param_1);
  }
  return;
}

/* JP: 0x004dd230  FldTeamChange::Dsp()   [Dsp__13FldTeamChangeFv]  size=0x80 */
void Dsp__13FldTeamChangeFv(int param_1)

{
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d)) {
    Dsp__5P2PktFv(param_1 + 0x50);
    MakePacket__13FldTeamChangeFv(param_1);
    Entry__13FldTeamChangeFv(param_1);
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
  }
  return;
}

/* JP: 0x004dd2b0  FldTeamChange::Clr()   [Clr__13FldTeamChangeFv]  size=0x80 */
void Clr__13FldTeamChangeFv(int param_1)

{
  if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d) < 0) {
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb;
    Clr__5P2PktFv(param_1 + 0x50);
    *(undefined1 *)(param_1 + 0x3e) = 0;
    *(undefined1 *)(param_1 + 0x3d) = 0;
  }
  *(undefined1 *)(param_1 + 0x34) = 0;
  return;
}

/* JP: 0x004dd330  FldTeamChange::CreateData()   [CreateData__13FldTeamChangeFv]  size=0x1bc */
void CreateData__13FldTeamChangeFv(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  char cVar5;
  long lVar6;
  undefined1 uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__6P2FontFv(&uStack_14);
  uStack_13 = 1;
  uStack_12 = 1;
  iVar1 = GetParty__15SaveMenuSectionFv();
  iVar3 = 0;
  lVar6 = 2;
  *(undefined1 *)(iStack_10 + 0x37) = 3;
  if (('\x02' < *(char *)(iStack_10 + 0x36)) ||
     (lVar4 = 0, (long)((ulong)*(byte *)(iStack_10 + 0x41) << 0x3e) < 0)) {
    lVar6 = (long)*(char *)(iStack_10 + 0x36);
    *(undefined1 *)(iStack_10 + 0x37) = 1;
    lVar4 = lVar6;
  }
  Clear__6CImageFUi(iStack_10 + 0x7c,0);
  for (; lVar4 <= lVar6; lVar4 = (long)((int)lVar4 + 1)) {
    iVar2 = iVar1 + (int)lVar4 * 0x20;
    cVar5 = *(char *)(iVar2 + 0x15);
    if ('\x04' < cVar5) {
      cVar5 = '\x04';
    }
    *(char *)(iStack_10 + iVar3 + 0x3a) = cVar5;
    *(int *)(iStack_10 + iVar3 * 4 + 0x24) = iVar2 + 0x16;
    DrawFont__6P2FontFP6CImageiiPCci(&uStack_14,iStack_10 + 0x7c,0,iVar3 * *(short *)(iStack_10 + 0x4a),iVar2 + 4,0);
    iVar3 = iVar3 + 1;
  }
  __dt__6P2FontFv(&uStack_14,0xffffffffffffffff);
  return;
}

/* JP: 0x004dd4f0  FldTeamChange::Entry()   [Entry__13FldTeamChangeFv]  size=0x78 */
void Entry__13FldTeamChangeFv(int param_1)

{
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e)) {
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd | 2;
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  }
  return;
}

/* JP: 0x004dd570  FldTeamChange::Dispose()   [Dispose__13FldTeamChangeFv]  size=0x68 */
void Dispose__13FldTeamChangeFv(int param_1)

{
  if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
  }
  return;
}

/* JP: 0x004dd5e0  FldTeamChange::MakeCharTexPacket()   [MakeCharTexPacket__13FldTeamChangeFv]  size=0xec */
void MakeCharTexPacket__13FldTeamChangeFv(int param_1)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  puVar3 = *(undefined4 **)(param_1 + 0x30);
  uVar1 = getBuffer__9BufMemoryFv(*(undefined4 *)(param_1 + 0x18));
  for (iVar4 = 0; iVar4 < 3; iVar4 = iVar4 + 1) {
    uVar2 = GetFileEntry(uVar1,iVar4 + 1);
    SetPacket__8P2TexTexFP4_QWDPvi(puVar3,uVar2,0);
    puVar3 = puVar3 + (*(byte *)(param_1 + 0x39) - 1) * 4;
    *puVar3 = 0x60000000;
    puVar3[1] = 0;
    *(undefined8 *)(puVar3 + 2) = 0;
    puVar3 = puVar3 + 4;
  }
  *(byte *)(param_1 + 0x41) = *(byte *)(param_1 + 0x41) & 0xfe | 1;
  return;
}

/* JP: 0x004dd6d0  FldTeamChange::NextTeam(int)   [NextTeam__13FldTeamChangeFi]  size=0x80 */
undefined1 NextTeam__13FldTeamChangeFi(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  uVar1 = *(undefined1 *)(param_1 + 0x36);
  if (param_2 != 0) {
    ChengePartySet__15SaveMenuSectionFi(1);
    puVar2 = (undefined1 *)GetParty__15SaveMenuSectionFv();
    uVar1 = *puVar2;
  }
  return uVar1;
}

/* JP: 0x004dd750  FldTeamChange::PrevTeam(int)   [PrevTeam__13FldTeamChangeFi]  size=0x80 */
undefined1 PrevTeam__13FldTeamChangeFi(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  uVar1 = *(undefined1 *)(param_1 + 0x36);
  if (param_2 != 0) {
    ChengePartySet__15SaveMenuSectionFi(0xffffffffffffffff);
    puVar2 = (undefined1 *)GetParty__15SaveMenuSectionFv();
    uVar1 = *puVar2;
  }
  return uVar1;
}

/* JP: 0x004dd7d0  FldTeamChange::Update(int)   [Update__13FldTeamChangeFi]  size=0x3dc */
void Update__13FldTeamChangeFi(int param_1,uint param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  if (*(int *)(param_1 + 0x18) != 0) {
    cVar2 = *(char *)(param_1 + 0x34);
    if ((cVar2 == '0') || (cVar2 == ' ')) {
      iVar5 = GetTimer__7SysToolFv();
      uVar7 = iVar5 - *(int *)(param_1 + 0x1c);
      if (((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3a) < 0) && (99 < uVar7)) {
        *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xdf;
      }
      if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x38) < 0) {
        uVar6 = 4000;
      }
      else {
        uVar6 = 2000;
      }
      if (uVar7 < uVar6) {
        if (-1 < (long)((ulong)*(byte *)(param_1 + 0x40) << 0x3a)) {
          bVar1 = *(char *)(param_1 + 0x36) < '\x03';
          cVar2 = -1;
          if ((param_2 & 0x400) == 0) {
            if ((param_2 & 0x100) != 0) {
              cVar2 = PrevTeam__13FldTeamChangeFi(param_1,bVar1);
            }
          }
          else {
            cVar2 = NextTeam__13FldTeamChangeFi(param_1,bVar1);
          }
          if ((-1 < cVar2) && (cVar2 != *(char *)(param_1 + 0x36))) {
            uVar4 = GetTimer__7SysToolFv();
            *(undefined4 *)(param_1 + 0x1c) = uVar4;
            *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0x7f;
            *(char *)(param_1 + 0x36) = cVar2;
            if (cVar2 < '\x03') {
              *(char *)(param_1 + 0x38) = cVar2;
            }
            uVar4 = GetTimer__7SysToolFv();
            *(undefined4 *)(param_1 + 0x1c) = uVar4;
            *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xdf | 0x20;
            MakePacket__13FldTeamChangeFv(param_1);
          }
        }
      }
      else {
        Clr__13FldTeamChangeFv(param_1);
        Dispose__13FldTeamChangeFv(param_1);
        *(undefined1 *)(param_1 + 0x34) = 0;
      }
    }
    else if ((cVar2 == '\0') && ((param_2 & 0x500) != 0)) {
      puVar3 = (undefined1 *)GetParty__15SaveMenuSectionFv();
      *(byte *)(param_1 + 0x41) = *(byte *)(param_1 + 0x41) & 0xfd | (puVar3[1] != '\0') << 1;
      *(undefined1 *)(param_1 + 0x36) = *puVar3;
      *(undefined1 *)(param_1 + 0x38) = 0;
      if (*(char *)(param_1 + 0x36) < '\x03') {
        *(undefined1 *)(param_1 + 0x38) = *(undefined1 *)(param_1 + 0x36);
        *(undefined1 *)(param_1 + 0x35) = 1;
        uVar4 = GetTimer__7SysToolFv();
        *(undefined4 *)(param_1 + 0x1c) = uVar4;
        *(undefined4 *)(param_1 + 0x20) = uVar4;
        *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xdf | 0x20;
        *(undefined1 *)(param_1 + 0x34) = 0x10;
        *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0x7f | 0x80;
        *(undefined2 *)(param_1 + 0x46) = 0xff80;
        *(undefined2 *)(param_1 + 0x44) = 0xff80;
        *(undefined2 *)(param_1 + 0x42) = 0xff80;
        CreateData__13FldTeamChangeFv(param_1);
        Dsp__13FldTeamChangeFv(param_1);
      }
    }
  }
  return;
}

/* JP: 0x004ddbb0  FldTeamChange::MakePacket()   [MakePacket__13FldTeamChangeFv]  size=0x304 */
void MakePacket__13FldTeamChangeFv(int param_1)

{
  undefined1 in_zero_qw [16];
  undefined8 extraout_v0_udw;
  undefined1 auVar1 [16];
  int iVar2;
  uint uVar3;
  undefined4 unaff_s2_lo;
  int unaff_s4_lo;
  undefined4 uVar4;
  int iVar5;
  undefined8 *puStack_14;
  int iStack_10;
  
  iVar2 = param_1 + 0x50;
  iStack_10 = param_1;
  Init__5P2PktFv(iVar2);
  iVar5 = (uint)*(byte *)(iStack_10 + 0x37) * 2 + 1;
  puStack_14 = (undefined8 *)AddCnt__5P2PktFi(iVar2,iVar5 * 6 + 4);
  *puStack_14 = 0x1026400000000002;
  puStack_14[1] = 0xe;
  puStack_14[2] = 0x44;
  puStack_14[3] = 0x42;
  puStack_14[4] = 0x33001;
  puStack_14[5] = 0x47;
  auVar1._8_8_ = extraout_v0_udw;
  auVar1._0_8_ = 0xc000000000000000;
  auVar1 = _pcpyld(in_zero_qw,auVar1);
  puStack_14[6] = (long)iVar5 | 0x400000000008000U | auVar1._0_8_;
  puStack_14[7] = 0x41414141c1c1;
  puStack_14 = puStack_14 + 8;
  iVar5 = *(short *)(iStack_10 + 0x48) + 0x720;
  for (uVar3 = 0; (int)uVar3 < (int)(uint)*(byte *)(iStack_10 + 0x37); uVar3 = uVar3 + 1) {
    if (uVar3 == *(byte *)(iStack_10 + 0x38)) {
      uVar4 = 0x80;
    }
    else {
      uVar4 = 0x40;
    }
    if (uVar3 == *(byte *)(iStack_10 + 0x38) + 1) {
      uVar4 = 0x80;
    }
    unaff_s4_lo = *(short *)(iStack_10 + uVar3 * 2 + 0x42) + 0x700;
    MakeLinePacket__13FldTeamChangeFRP4_QWDiiiUi(iStack_10,&puStack_14,unaff_s4_lo,iVar5,4,uVar4);
    if (uVar3 == *(byte *)(iStack_10 + 0x38)) {
      unaff_s2_lo = 0x80;
    }
    else {
      unaff_s2_lo = 0x40;
    }
    MakeLinePacket__13FldTeamChangeFRP4_QWDiiiUi
              (iStack_10,&puStack_14,unaff_s4_lo,iVar5 + 0x1b,2,unaff_s2_lo);
    iVar5 = iVar5 + 0x51;
  }
  MakeLinePacket__13FldTeamChangeFRP4_QWDiiiUi
            (iStack_10,&puStack_14,unaff_s4_lo,iVar5,4,unaff_s2_lo);
  MakeNamePacket__13FldTeamChangeFP5P2Pkt(iStack_10,iVar2);
  MakeBasePacket__13FldTeamChangeFP5P2Pkt(iStack_10,iVar2);
  MakeCharPacket__13FldTeamChangeFP5P2Pkt(iStack_10,iVar2);
  if (ff$3899 == 0) {
    ff$3899 = 1;
    Dump0__5P2PktFv(iVar2);
  }
  Terminate__5P2PktFv(iVar2);
  return;
}

/* JP: 0x004ddec0  FldTeamChange::MakeLinePacket(_QWD&*, int, int, int, unsigned int)   [MakeLinePacket__13FldTeamChangeFRP4_QWDiiiUi]  size=0x140 */
void MakeLinePacket__13FldTeamChangeFRP4_QWDiiiUi
               (undefined8 param_1,int *param_2,int param_3,short param_4,short param_5,int param_6)

{
  int iVar1;
  int iVar2;
  int aiStack_78 [30];
  
  aiStack_78[0] = param_3 << 4;
  aiStack_78[1] = (param_3 + 0x38) * 0x10;
  aiStack_78[2] = (param_3 + 0x80) * 0x10;
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    iVar2 = 0x977d82;
    if (iVar1 < 2) {
      iVar2 = param_6 * 0x1000000 + 0x977d82;
    }
    *(int *)(*param_2 + 0x10) = iVar2;
    *(int *)*param_2 = iVar2;
    iVar2 = aiStack_78[iVar1];
    *(ulong *)(*param_2 + 8) = (ulong)CONCAT22(param_4 * 0x10,(short)iVar2);
    *(ulong *)(*param_2 + 0x18) = (ulong)CONCAT22(param_4 * 0x10 + param_5 * 0x10,(short)iVar2);
    *param_2 = *param_2 + 0x20;
  }
  return;
}

/* JP: 0x004de000  FldTeamChange::MakeNamePacket(P2Pkt*)   [MakeNamePacket__13FldTeamChangeFP5P2Pkt]  size=0x49c */
void MakeNamePacket__13FldTeamChangeFP5P2Pkt(int param_1,undefined4 param_2)

{
  short sVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  short sVar4;
  short sVar5;
  undefined8 *puVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  short sVar10;
  short sVar11;
  ulong uVar12;
  int *piVar13;
  uint uVar14;
  int iVar15;
  short sVar16;
  int iStack_38;
  
  uVar9 = GetPktSize__7P2ImageFi(4);
  uVar9 = Add__5P2PktFi(param_2,uVar9);
  SetPacket__7P2ImageFP4_QWDP6CImageiii(uVar9,param_1 + 0x7c,0,0,8);
  uVar2 = *(undefined2 *)(param_1 + 0x80);
  uVar3 = *(undefined2 *)(param_1 + 0x82);
  iVar15 = 0;
  for (iVar7 = 0; iVar7 < (int)(uint)*(byte *)(param_1 + 0x37); iVar7 = iVar7 + 1) {
    if (*(char *)(param_1 + iVar7 + 0x3a) != '\0') {
      iVar15 = iVar15 + 1;
    }
  }
  puVar6 = (undefined8 *)AddCnt__5P2PktFi(param_2,iVar15 * 6 + 5);
  *puVar6 = 0x10ab400000000003;
  puVar6[1] = 0xe;
  puVar6[2] = 0;
  puVar6[3] = 0x3f;
  iVar7 = pix2tex(uVar2);
  iVar8 = pix2tex(uVar3);
  uVar12 = (long)iVar7 << 0x1a | 0x2c20000U | (long)iVar8 << 0x1e;
  iVar7 = GetEntry__6P2ClutFi(0);
  iVar8 = GetPSM__6P2ClutFv();
  puVar6[4] = (long)iVar8 << 0x33 |
              CONCAT44((uint)((ulong)((long)iVar7 << 0x25) >> 0x20) | (uint)(uVar12 >> 0x20) | 4,
                       (int)uVar12) | 0x2000000000000000;
  puVar6[5] = 6;
  puVar6[6] = 0x60;
  puVar6[7] = 0x14;
  puVar6[8] = (ulong)(uint)(iVar15 << 1) | 0x6400000000008000;
  puVar6[9] = 0xf43431;
  piVar13 = (int *)(puVar6 + 10);
  sVar1 = *(short *)(param_1 + 0x4c);
  sVar11 = *(short *)(param_1 + 0x48) + 0x726;
  for (uVar14 = 0; uVar14 < *(byte *)(param_1 + 0x37); uVar14 = uVar14 + 1) {
    if (*(char *)(param_1 + uVar14 + 0x3a) != '\0') {
      if (uVar14 == *(byte *)(param_1 + 0x38)) {
        iStack_38 = 0x80;
      }
      else {
        iStack_38 = 0x40;
      }
      sVar10 = (*(short *)(param_1 + uVar14 * 2 + 0x42) + 0x70b) * 0x10;
      for (iVar7 = 0; iVar7 < 2; iVar7 = iVar7 + 1) {
        iVar15 = iStack_38 * 0x1000000;
        if (iVar7 == 0) {
          sVar5 = sVar10 + 2;
          sVar16 = sVar11 + 2;
        }
        else {
          iVar15 = iVar15 + 0xb1b1b1;
          sVar5 = sVar10;
          sVar16 = sVar11;
        }
        *piVar13 = iVar15;
        sVar4 = (short)uVar14 * *(short *)(param_1 + 0x4a) * 0x10 + 8;
        *(ulong *)(piVar13 + 2) = (ulong)CONCAT22(sVar4,8);
        *(ulong *)(piVar13 + 6) =
             (ulong)CONCAT22(sVar4 + *(short *)(param_1 + 0x4a) * 0x10 + -8,
                             *(short *)(param_1 + 0x4c) * 0x10 + -8);
        *(ulong *)(piVar13 + 4) = (ulong)CONCAT22(sVar16 * 0x10,sVar5);
        *(ulong *)(piVar13 + 8) =
             (ulong)CONCAT22(sVar16 * 0x10 + *(short *)(param_1 + 0x4a) * 0x10,
                             sVar5 + (short)(int)((float)(int)sVar1 * 0.9) * 0x10);
        piVar13 = piVar13 + 0xc;
      }
    }
    sVar11 = sVar11 + 0x51;
  }
  return;
}

/* JP: 0x004de4a0  FldTeamChange::MakeBasePacket(P2Pkt*)   [MakeBasePacket__13FldTeamChangeFP5P2Pkt]  size=0x414 */
void MakeBasePacket__13FldTeamChangeFP5P2Pkt(int param_1,undefined4 param_2)

{
  byte bVar1;
  undefined4 uVar2;
  undefined8 *puVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  short sVar8;
  ulong uVar9;
  uint uVar10;
  short *psVar11;
  short sVar12;
  short sVar13;
  uint uVar14;
  short sVar15;
  undefined4 uStack_3c;
  int iStack_38;
  
  uVar2 = getBuffer__9BufMemoryFv(*(undefined4 *)(param_1 + 0x18));
  uVar6 = GetFileEntry(uVar2,0);
  psVar11 = (short *)uVar6;
  sVar13 = *psVar11;
  sVar12 = psVar11[1];
  if ((char)psVar11[2] == '\x04') {
    iStack_38 = 0x2c;
  }
  else {
    iStack_38 = 0x1b;
  }
  bVar1 = *(byte *)(param_1 + 0x37);
  uVar14 = 0;
  for (uVar10 = 0; uVar10 < bVar1; uVar10 = uVar10 + 1) {
    uVar14 = uVar14 + *(byte *)(param_1 + uVar10 + 0x3a);
  }
  uVar7 = GetPktSize__8P2TexTexFPv(uVar6);
  uVar7 = Add__5P2PktFi(param_2,uVar7);
  SetPacket__8P2TexTexFP4_QWDPvi(uVar7,uVar6,0);
  puVar3 = (undefined8 *)AddCnt__5P2PktFi(param_2,uVar14 * 3 + 5);
  *puVar3 = 0x10ab400000000003;
  puVar3[1] = 0xe;
  puVar3[2] = 0;
  puVar3[3] = 0x3f;
  iVar4 = pix2tex(sVar13);
  iVar5 = pix2tex(sVar12);
  uVar9 = (long)iStack_38 << 0x14 | 0x20000U | (long)iVar4 << 0x1a | (long)iVar5 << 0x1e;
  iVar4 = GetEntry__6P2ClutFi(0);
  iVar5 = GetPSM__6P2ClutFv();
  puVar3[4] = (long)iVar5 << 0x33 |
              CONCAT44((uint)((ulong)((long)iVar4 << 0x25) >> 0x20) | (uint)(uVar9 >> 0x20) | 4,
                       (int)uVar9) | 0x2000000000000000;
  puVar3[5] = 6;
  puVar3[6] = 0;
  puVar3[7] = 0x14;
  puVar3[8] = (ulong)uVar14 | 0x6400000000008000;
  puVar3[9] = 0xf43431;
  puVar3 = puVar3 + 10;
  sVar13 = sVar13 * 0x10;
  sVar12 = sVar12 * 0x10;
  sVar8 = *(short *)(param_1 + 0x48) + 0x740;
  for (uVar10 = 0; uVar10 < bVar1; uVar10 = uVar10 + 1) {
    if (uVar10 == *(byte *)(param_1 + 0x38)) {
      uStack_3c = 0x80808080;
    }
    else {
      uStack_3c = 0x40606060;
    }
    sVar15 = (*(short *)(param_1 + uVar10 * 2 + 0x42) + 0x70b) * 0x10;
    for (iVar4 = 0; iVar4 < (int)(uint)*(byte *)(param_1 + uVar10 + 0x3a); iVar4 = iVar4 + 1) {
      *(undefined4 *)puVar3 = uStack_3c;
      puVar3[1] = 0x80008;
      puVar3[3] = (ulong)CONCAT22(sVar12,sVar13);
      puVar3[2] = (ulong)CONCAT22(sVar8 * 0x10,sVar15);
      puVar3[4] = (ulong)CONCAT22(sVar8 * 0x10 + sVar12,sVar15 + sVar13);
      puVar3 = puVar3 + 6;
      sVar15 = sVar15 + 0x1a0;
    }
    sVar8 = sVar8 + 0x51;
  }
  return;
}

/* JP: 0x004de8c0  FldTeamChange::MakeCharPacket(P2Pkt*)   [MakeCharPacket__13FldTeamChangeFP5P2Pkt]  size=0x464 */
void MakeCharPacket__13FldTeamChangeFP5P2Pkt(int param_1,undefined4 param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  short sVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined2 *puVar9;
  undefined8 *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  ulong uVar14;
  uint uVar15;
  int iVar16;
  short sVar17;
  short sVar18;
  undefined4 uStack_4c;
  char *pcStack_38;
  uint uStack_28;
  
  uVar7 = getBuffer__9BufMemoryFv(*(undefined4 *)(param_1 + 0x18));
  uStack_28 = 0xffffffff;
  bVar1 = *(byte *)(param_1 + 0x37);
  if ((*(byte *)(param_1 + 0x41) & 1) == 0) {
    MakeCharTexPacket__13FldTeamChangeFv(param_1);
  }
  sVar18 = *(short *)(param_1 + 0x48) + 0x740;
  for (uVar15 = 0; uVar15 < bVar1; uVar15 = uVar15 + 1) {
    if (uVar15 == *(byte *)(param_1 + 0x38)) {
      uStack_4c = 0x80808080;
    }
    else {
      uStack_4c = 0x40606060;
    }
    sVar17 = (*(short *)(param_1 + uVar15 * 2 + 0x42) + 0x70b) * 0x10;
    bVar2 = *(byte *)(param_1 + uVar15 + 0x3a);
    pcStack_38 = *(char **)(param_1 + uVar15 * 4 + 0x24);
    for (iVar16 = 0; iVar16 < (int)(uint)bVar2; iVar16 = iVar16 + 1) {
      uVar8 = (uint)(byte)(&charTexList)[*pcStack_38 * 2];
      bVar3 = (&DAT_00559001)[*pcStack_38 * 2];
      if (uVar8 != uStack_28) {
        puVar9 = (undefined2 *)GetFileEntry(uVar7,uVar8 + 1);
        uVar4 = *puVar9;
        uVar5 = puVar9[1];
        if (*(char *)(puVar9 + 2) == '\x04') {
          iVar13 = 0x2c;
        }
        else {
          iVar13 = 0x1b;
        }
        AddCall__5P2PktFiUi(param_2,0,
                        *(int *)(param_1 + 0x30) + uVar8 * *(byte *)(param_1 + 0x39) * 0x10);
        puVar10 = (undefined8 *)AddCnt__5P2PktFi(param_2,3);
        *puVar10 = 0x1000000000008002;
        puVar10[1] = 0xe;
        puVar10[2] = 0;
        puVar10[3] = 0x3f;
        iVar11 = pix2tex(uVar4);
        iVar12 = pix2tex(uVar5);
        uVar14 = (long)iVar13 << 0x14 | 0x20000U | (long)iVar11 << 0x1a | (long)iVar12 << 0x1e;
        iVar13 = GetEntry__6P2ClutFi(0);
        iVar11 = GetPSM__6P2ClutFv();
        puVar10[4] = (long)iVar11 << 0x33 |
                     CONCAT44((uint)((ulong)((long)iVar13 << 0x25) >> 0x20) |
                              (uint)(uVar14 >> 0x20) | 4,(int)uVar14) | 0x2000000000000000;
        puVar10[5] = 6;
        uStack_28 = uVar8;
      }
      puVar10 = (undefined8 *)AddCnt__5P2PktFi(param_2,4);
      *puVar10 = 0x6400000000008001;
      puVar10[1] = 0xf43431;
      *(undefined4 *)(puVar10 + 2) = uStack_4c;
      sVar6 = ((ushort)bVar3 * 0x18 - (ushort)bVar3) * 0x20;
      puVar10[3] = (ulong)CONCAT22(sVar6 + 8,8);
      puVar10[5] = (ulong)CONCAT22(sVar6 + 0x2e8,0x200);
      puVar10[4] = (ulong)CONCAT22(sVar18 * 0x10,sVar17);
      puVar10[6] = (ulong)CONCAT22(sVar18 * 0x10 + 0x2e0,sVar17 + 0x200);
      sVar17 = sVar17 + 0x1a0;
      pcStack_38 = pcStack_38 + 1;
    }
    sVar18 = sVar18 + 0x51;
  }
  return;
}
