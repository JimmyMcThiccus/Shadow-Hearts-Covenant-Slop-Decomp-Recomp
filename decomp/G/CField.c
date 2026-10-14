/* ==== CLEANED excerpts (lifecycle / SDB consumption; port: sh2_field/src/field.rs) ==== */
#include "_types.h"
/* JP 0x004a30b0 CField::Init(const char *map) */
int CField_Init(CField *t, const char *map) { sys__6CField = t; CField_preLoad(t); CField_Start(t); MenuObj_CreateField(); if (map && *map) CField_MapJump(t, map); return 1; }
/* JP 0x004a31e0 */ int CField_preLoad(CField *t) { t->player_pos = (FVector){0, 0, 0, 1}; InitFieldModel(); return 1; }
/* JP 0x004a3240 CField::Start */
int CField_Start(CField *t) {
    if (!t->pad) { t->pad = new CPad(0); CPad_Enable(t->pad); CPad_SetPriority(t->pad, &prio_normal); }
    if (!t->camera) { t->camera = new CFieldCamera; CFieldCamera_Init(t->camera); }
    CScriptEx_Entry(t, 0x70); t->flags_18d = (t->flags_18d & 0xef) | 0x10; return 1;
}
/* JP 0x004a33c0 CField::Restart: re-arm after a map change */
void CField_Restart(CField *t) { t->flags_18d &= 0xdf; t->flags_18c &= 0x1f; t->cam_yaw_adjust = 0; t->scr_camera_active = 0;
    CFieldCamera_SetViewDelay(t->camera, 0); t->flags_18d &= 0xf3; CField_SetEncountRate(t, -1);
    CFieldSocket_LoadScriptRegister(m_socket); CFieldSocket_SetGameOverType(m_socket, -2, 0); }
/* JP 0x004ac100 CField::GetEntryPoint(int i, int &dirOrCount) -> SDB_tagENTRYPOS* ; i<0 returns the count in *out */
SDB_tagENTRYPOS *CField_GetEntryPoint(CField *t, int i, int *out) {
    SDB_tagENTRYPOS *e = 0; *out = -1; SDB_tagHEADER *h = CSTGDB_Find(m_pSTGDB, 'ENTRYPOS');
    if (h) { e = CSTGDB_GetDataAddr(m_pSTGDB, h); int n = CSTGDB_GetDataNum(m_pSTGDB, h);
             if (i < 0) *out = n; else if (i < n) { e += i; *out = e->dir; } }
    return e;
}
/* JP 0x004ab860 CField::InitSDB(CSTGDB *db) -- everything a map needs, in order */
int CField_InitSDB(CField *t, CSTGDB *db) {
    t->unk5fc = -1; t->unk600 = 0; t->flags_18c = (t->flags_18c & 0xe3) | 0x14;
    if ((t->flags_18e & 3) == 1) t->flags_18e = (t->flags_18e & 0xfc) | 2;
    m_pSTGDB = db; t->camera_id = FieldCameraID(-2);
    if (t->team_change) FldTeamChange_Clr(t->team_change);
    int ctrl_shown = (ctrl = CField_GetCtrlModel(t)) && CFieldModel_isDsp(ctrl);
    for (int i = 0; i < t->model_count; i++) if (t->models[i]) { CFieldModel_ClearShadow(t->models[i]); CFieldModel_ClearModel(t->models[i]); }
    if (!t->bg) t->bg = new CFieldBG;
    CFieldBG_Create(t->bg, db, 0); CFieldBG_Dsp(t->bg);
    SDB_tagHEADER *h;
    if ((h = CSTGDB_Find(db, 'MONSET  '))) { CField_SetEncountRate(t, *(u8 *)((char *)h + 0x14)); CField_SetFieldData(t, 6, *(u16 *)((char *)h + 0x16), 0); CField_SetFieldData(t, 7, *(u16 *)((char *)h + 0x18), 0); }
    else CField_SetEncountRate(t, 0);
    CField_AutoLoadSE(t);
    if (CSTGDB_Find(db, 'SLICE   ')) { t->floor = new CFloorMan; CFloorMan_SetData(t->floor, db); }
    t->player_pos = (FVector){0, 0, 0, 1};
    if ((h = CSTGDB_Find(db, 'ENTRYPOS'))) { t->player_pos = *(FVector *)CSTGDB_GetDataAddr(db, h); t->player_pos.w = 1; }  /* default start = entry 0 */
    m_pCAMDAT = m_pCAMOLD = 0;
    if ((h = CSTGDB_Find(db, 'CAMEVENT'))) { t->cam_events = new CFieldEvent; CFieldEvent_Init(t->cam_events, CSTGDB_GetDataAddr(db, h), CSTGDB_GetDataNum(db, h), 1); }
    if ((h = CSTGDB_Find(db, 'CAMERA  '))) { SDB_tagFCAMERA *c = CSTGDB_GetDataAddr(db, h);                 /* blob offsets -> pointers */
        for (int i = 0; i < CSTGDB_GetDataNum(db, h); i++, c++) c->blob = (char *)c + (u32)c->blob; }
    if ((h = CSTGDB_Find(db, 'EVENTBOX'))) { t->event_boxes = new CFieldEvent; CFieldEvent_Init(t->event_boxes, CSTGDB_GetDataAddr(db, h), CSTGDB_GetDataNum(db, h), 0); }
    if ((h = CSTGDB_Find(db, 'NAVIMAP '))) { t->navimap = new CNaviMap; CNaviMap_SetData(t->navimap, CSTGDB_GetDataAddr(db, h)); }
    ShadowControl *sc = CFieldBG_GetShadowCtrl(t->bg, 0);
    if (sc && (ctrl = CField_GetCtrlModel(t)) && ctrl_shown && t->entry_id >= 0) {
        int dir; SDB_tagENTRYPOS *e = CField_GetEntryPoint(t, t->entry_id, &dir);
        if (e) { FVector p = {e->x, e->y, e->z, 1}; CFieldModel_SetDir(ctrl, dir, 2, 0); CFieldModel_SetPos(ctrl, p, 1); t->player_pos = p; m_pCAMDAT = m_pCAMOLD = 0; CField_CameraUpdate(t, 0); }
        CFieldModel_DispModel(ctrl, -1); CFieldModel_DispShadow(ctrl, sc);
    }
    CFieldBG_Update(t->bg, 0);
    for (int i = 0; i < t->model_count; i++) if (t->models[i]) CFieldModel_Update(t->models[i], 0);
    Gsx_SetFFMode(0, 1, 2); Gsx_SetInter30(1); t->state = 2; return 1;
}


/* ==== RAW (Ghidra output, names/globals resolved; not hand-cleaned) ==== */
/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CField   functions: 201
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CField.md).
 */

/* JP: 0x004a2b00  CField::CField()   [__ct__6CFieldFv]  size=0x1ec */
int __ct__6CFieldFv(CField *this)

{
  byte *pbVar1;
  int iVar2;
  void *pvVar3;
  long lVar4;
  
  __ct__9CScriptExFv(this);
  this->pVtbl_CField = &__vt__6CField;
  __ct__7FVectorFv(&this->cam_pos);
  __ct__7FVectorFv(&this->cam_angle);
  __ct__7FVectorFv(&this->player_pos);
  __ct__9BufMemoryFv(&this->field_0x1d00);
  __ct__7FVectorFv(&this->vec_1d10);
  __ct__7FVectorFv(&this->vec_1d20);
  Report__4SdrvFv(sys__4Sdrv);
  memset(&this->field_0x24,0,0xe98);
  this->wState = 1;
  for (iVar2 = 0; iVar2 < 0x30; iVar2 = iVar2 + 1) {
    pbVar1 = this->aObjse_slots + iVar2 * 0x28;
    pbVar1[0] = 0xff;
    pbVar1[1] = 0xff;
    pbVar1[2] = 0xff;
    pbVar1[3] = 0xff;
  }
  if (sys__6CMusic == 0) {
    this->bFlags_18e = this->bFlags_18e & 0xf7 | 8;
    lVar4 = __nw__FUi(0x94);
    iVar2 = 0;
    if (lVar4 != 0) {
      iVar2 = __ct__6CMusicFv(lVar4);
    }
    sys__6CMusic = iVar2;
    SetCallback__6CMusicFPFUcUiUi_vUi(sys__6CMusic,0x4d93a0,this);
  }
  lVar4 = __nw__FUi(8);
  pvVar3 = (void *)0x0;
  if (lVar4 != 0) {
    pvVar3 = (void *)__ct__3CSeFv(lVar4);
  }
  this->pSe = pvVar3;
  (**(code **)(*(int *)((int)this->pSe + 4) + 0xc))(this->pSe,8,0x20,0);
  return (int)this;
}

/* JP: 0x004a2db0  CField::~CField()   [__dt__6CFieldFv]  size=0xec */
int __dt__6CFieldFv(CField *this,short flag)

{
  undefined8 uVar1;
  
  if (this != (CField *)0x0) {
    this->pVtbl_CField = &__vt__6CField;
    sys__6CField = 0;
    ReleaseHandle__11FileManegerFv(sm_pFace__7MenuObj);
    ReleaseField__7MenuObjFv();
    if ((long)((ulong)this->bFlags_18c << 0x3e) < 0) {
      InvokeGameOver__Fv();
    }
    else {
      uVar1 = GetCurMPSname__12CFieldSocketFv(m_socket__12CFieldSocket);
      StartBattle__6SSHSysFP12_SysBtlParamPCc(sys__6SSHSys,0,uVar1);
    }
    __dt__9BufMemoryFv(&this->field_0x1d00,0xffffffffffffffff);
    __dt__9CScriptExFv(this,0);
    if (0 < flag) {
      __dl__FPv(this);
    }
  }
  return (int)this;
}

/* JP: 0x004a2ef0  CField::CheckResetPause()   [CheckResetPause__6CFieldFv]  size=0xbc */
void CheckResetPause__6CFieldFv(CField *this)

{
  long lVar1;
  
  lVar1 = isFaderDsp__12CFieldSocketFi(m_socket__12CFieldSocket,1);
  if ((((this->pPad != (void *)0x0) && ((this->bFlags_18c & 1) == 0)) &&
      ((this->bFlags_18e & 3) == 0)) && ((this->bFlags_18d & 3) == 0)) {
    ChkResetPause__6SSHSysFP4CPadbb(sys__6SSHSys,this->pPad,lVar1 == 0,lVar1 == 0);
  }
  return;
}

/* JP: 0x004a2fb0  CField::Delete()   [Delete__6CFieldFv]  size=0xfc */
void Delete__6CFieldFv(CField *this)

{
  long lVar1;
  
  if ((this->bFlags_18c & 1) == 0) {
    this->bFlags_18c = this->bFlags_18c & 0xfe | 1;
    ResetSE__6CFieldFv(this);
    UnloadCharacter__6CFieldFi(this,-1);
    ClearSDB__6CFieldFi(this,0);
    VibRelease__6CFieldFv(this);
    if (this->pTeam_change != (void *)0x0) {
      Delete__13FldTeamChangeFv(this->pTeam_change);
      this->pTeam_change = (void *)0x0;
    }
  }
  if (sys__6CMusic != 0) {
    Release__6CMusicFv(sys__6CMusic);
  }
  lVar1 = GetFieldScript__Fi(1);
  if (lVar1 != 0) {
    Delete__7CScriptFv(lVar1);
  }
  return;
}

/* JP: 0x004a30b0  CField::Init(const char*)   [Init__6CFieldFPCc]  size=0x7c */
undefined4 Init__6CFieldFPCc(CField *this,char *a0)

{
  pCGpffff85ec = this;
  preLoad__6CFieldFv(this);
  Start__6CFieldFv(this);
  CreateField__7MenuObjFv();
  if ((a0 != (char *)0x0) && (*a0 != '\0')) {
    MapJump__6CFieldFPCc(this,a0);
  }
  return 1;
}

/* JP: 0x004a3130  CField::LinkA()   [LinkA__6CFieldFv]  size=0x30 */
void LinkA__6CFieldFv(CField *this)

{
  Link__9CScriptExFiP7CScript(this,0xc2,0);
  return;
}

/* JP: 0x004a3160  CField::SetTeamChgData(BufMemory*)   [SetTeamChgData__6CFieldFP9BufMemory]  size=0x50 */
void SetTeamChgData__6CFieldFP9BufMemory(CField *this,void *a0)

{
  *(void **)&this->field_0x188 = a0;
  if (this->pTeam_change != (void *)0x0) {
    SetData__13FldTeamChangeFP9BufMemory(this->pTeam_change,a0);
  }
  return;
}

/* JP: 0x004a31e0  CField::preLoad()   [preLoad__6CFieldFv]  size=0x5c */
undefined4 preLoad__6CFieldFv(CField *this)

{
  undefined8 uVar1;
  undefined1 auStack_20 [16];
  CField *pCStack_10;
  
  pCStack_10 = this;
  uVar1 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_20);
  __as__7FVectorFRC7FVector(&pCStack_10->player_pos,uVar1);
  InitFieldModel__Fv();
  return 1;
}

/* JP: 0x004a3240  CField::Start()   [Start__6CFieldFv]  size=0x120 */
undefined4 Start__6CFieldFv(CField *this)

{
  void *pvVar1;
  CFieldCamera *pCVar2;
  long lVar3;
  
  if (this->pPad == (void *)0x0) {
    lVar3 = __nw__FUi(0x18);
    pvVar1 = (void *)0x0;
    if (lVar3 != 0) {
      pvVar1 = (void *)__ct__4CPadFi(lVar3,0);
    }
    this->pPad = pvVar1;
    Enable__4CPadFv(this->pPad);
    SetPriority__4CPadFRCQ24CPad8Priority(this->pPad,&gp0xffff8194);
  }
  if (this->pCamera == (CFieldCamera *)0x0) {
    lVar3 = __nw__FUi(0xd0);
    pCVar2 = (CFieldCamera *)0x0;
    if (lVar3 != 0) {
      pCVar2 = (CFieldCamera *)__ct__12CFieldCameraFv((CFieldCamera *)lVar3);
    }
    this->pCamera = pCVar2;
    Init__12CFieldCameraFv(this->pCamera);
  }
  Entry__9CScriptExFi(this,0x70);
  this->bFlags_18d = this->bFlags_18d & 0xef | 0x10;
  return 1;
}

/* JP: 0x004a3390  CField::closeInquiry()   [closeInquiry__6CFieldFv]  size=0x2c */
undefined8 closeInquiry__6CFieldFv(CField *this)

{
  Dispose__9CScriptExFv(this);
  return 0;
}

/* JP: 0x004a33c0  CField::Restart()   [Restart__6CFieldFv]  size=0xd4 */
void Restart__6CFieldFv(CField *this)

{
  this->bFlags_18d = this->bFlags_18d & 0xdf;
  this->bFlags_18c = this->bFlags_18c & 0x1f;
  this->flCam_yaw_adjust = 0.0;
  this->bScr_camera_active = 0;
  SetViewDelay__12CFieldCameraFf(this->pCamera,0.0);
  this->bFlags_18d = this->bFlags_18d & 0xf3;
  SetEncountRate__6CFieldFi(this,-1);
  LoadScriptRegister__12CFieldSocketFv(m_socket__12CFieldSocket);
  SetGameOverType__12CFieldSocketFii(m_socket__12CFieldSocket,0xfffffffffffffffe,0);
  return;
}

/* JP: 0x004a34d0  CField::PurgeModel()   [PurgeModel__6CFieldFv]  size=0x9c */
void PurgeModel__6CFieldFv(CField *this)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = this->bModel_count;
  for (iVar2 = 0; iVar2 < (int)(uint)bVar1; iVar2 = iVar2 + 1) {
    if (this->aModels[iVar2] != (void *)0x0) {
      Delete__11CFieldModelFv(this->aModels[iVar2]);
      this->aModels[iVar2] = (void *)0x0;
    }
  }
  return;
}

/* JP: 0x004a3570  CField::SaveModel()   [SaveModel__6CFieldFv]  size=0xc0 */
void SaveModel__6CFieldFv(CField *this)

{
  byte bVar1;
  void *pvVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  undefined1 auStack_20 [16];
  CField *pCStack_10;
  
  bVar1 = this->bModel_count;
  pCStack_10 = this;
  for (iVar5 = 0; iVar5 < (int)(uint)bVar1; iVar5 = iVar5 + 1) {
    pvVar2 = pCStack_10->aModels[iVar5];
    if ((pvVar2 != (void *)0x0) && (lVar3 = isDsp__11CFieldModelFv(pvVar2), lVar3 != 0)) {
      GetPos__11CFieldModelFv(auStack_20,pvVar2);
      uVar4 = GetDir__11CFieldModelFv(pvVar2);
      SaveChrPos__FiP7FVectori(iVar5,auStack_20,uVar4);
    }
  }
  return;
}

/* JP: 0x004a36a0  CField::ClearSDB(int)   [ClearSDB__6CFieldFi]  size=0x25c */
undefined4 ClearSDB__6CFieldFi(CField *this,int a0)

{
  byte bVar1;
  void *pvVar2;
  undefined4 uVar3;
  int a1;
  
  m_pCAMDAT__6CField = 0;
  CompClear__12CFieldCameraFv(this->pCamera);
  if (m_pSTGDB__6CField == 0) {
    uVar3 = 0;
  }
  else {
    AutoDelLight__6CFieldFv(this);
    bVar1 = this->bModel_count;
    for (a1 = 0; a1 < (int)(uint)bVar1; a1 = a1 + 1) {
      pvVar2 = this->aModels[a1];
      if (pvVar2 != (void *)0x0) {
        ClearShadow__11CFieldModelFv(pvVar2);
        ClearModel__11CFieldModelFv(pvVar2);
        DetachModel__6CFieldFii(this,(uint)*(byte *)((int)pvVar2 + 0xfc),a1);
      }
    }
    if (this->pEvent_boxes != (CFieldEvent *)0x0) {
      __dt__11CFieldEventFv(this->pEvent_boxes,1);
      this->pEvent_boxes = (CFieldEvent *)0x0;
    }
    if (this->pCam_events != (CFieldEvent *)0x0) {
      __dt__11CFieldEventFv(this->pCam_events,1);
      this->pCam_events = (CFieldEvent *)0x0;
    }
    if (this->pFloor != (CFloorMan *)0x0) {
      __dt__9CFloorManFv(this->pFloor,1);
      this->pFloor = (CFloorMan *)0x0;
    }
    if (this->pBg != (CFieldBG *)0x0) {
      __dt__8CFieldBGFv(this->pBg,1);
      this->pBg = (CFieldBG *)0x0;
    }
    if (this->pNavimap != (void *)0x0) {
      Delete__8CNaviMapFv(this->pNavimap);
      this->pNavimap = (void *)0x0;
    }
    m_pSTGDB__6CField = 0;
    this->nUnk5fc = -1;
    this->nUnk600 = 0;
    if (a0 == 0) {
      ClrSavePoint__6CFieldFi(this,-1);
      ClrWarpPoint__6CFieldFi(this,-1);
      ClrLookPoint__6CFieldFi(this,-1);
      this->bClr_flag_5ec = 0;
    }
    else {
      ShowSavePoint__6CFieldFi(this,0);
      ShowWarpPoint__6CFieldFi(this,0);
    }
    uVar3 = 1;
  }
  return uVar3;
}

/* JP: 0x004a3980  CField::GetBGModel(int)   [GetBGModel__6CFieldFi]  size=0x68 */
long GetBGModel__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  long lVar2;
  
  if (this->pBg == (CFieldBG *)0x0) {
    lVar2 = 0;
  }
  else {
    iVar1 = GetModel__8CFieldBGFi(this->pBg,a0 & 0x7f);
    lVar2 = (long)iVar1;
  }
  return lVar2;
}

/* JP: 0x004a39f0  CField::GetCtrlModel()   [GetCtrlModel__6CFieldFv]  size=0x34 */
void * GetCtrlModel__6CFieldFv(CField *this)

{
  return this->aModels[(char)this->field_0x6cc];
}

/* JP: 0x004a3a30  CField::CheckEventBox(FVector&)   [CheckEventBox__6CFieldFR7FVector]  size=0x70 */
long CheckEventBox__6CFieldFR7FVector(CField *this,FVector *a0)

{
  FVector *a0_00;
  int iVar1;
  undefined1 auStack_30 [16];
  CField *pCStack_20;
  FVector *pFStack_10;
  
  if (this->pEvent_boxes == (CFieldEvent *)0x0) {
    iVar1 = -1;
  }
  else {
    pCStack_20 = this;
    pFStack_10 = a0;
    a0_00 = (FVector *)__ct__7FVectorFRC7FVector(auStack_30,a0);
    iVar1 = HitCheck__11CFieldEventF7FVectorii(pCStack_20->pEvent_boxes,a0_00,0,2);
  }
  return (long)iVar1;
}

/* JP: 0x004a3aa0  CField::Pause(int)   [Pause__6CFieldFi]  size=0xe0 */
void Pause__6CFieldFi(CField *this,int a0)

{
  if (a0 == 0) {
    if (((ulong)this->bFlags_18d & 0xf) >> 2 == 0) {
      this->bFlags_18d = this->bFlags_18d & 0xf3 | 8;
      SetPriority__4CPadFRCQ24CPad8Priority(this->pPad,&gp0xffff819c);
    }
  }
  else if (((ulong)this->bFlags_18d & 0xf) >> 2 != 0) {
    this->bFlags_18d = this->bFlags_18d & 0xf3;
    Pause__7CScriptFi(fldScript__12CFieldSocket,0);
    SetPriority__4CPadFRCQ24CPad8Priority(this->pPad,&gp0xffff8198);
  }
  return;
}

/* JP: 0x004a3bc0  CField::Dsp()   [Dsp__6CFieldFv]  size=0x1b8 */
void Dsp__6CFieldFv(CField *this)

{
  byte bVar1;
  long lVar2;
  int iVar3;
  
  lVar2 = isCreate__6P2ClutFv();
  if (lVar2 == 0) {
    Create__6P2ClutFv();
  }
  if (-1 < (long)((ulong)this->bFlags_18d << 0x3b)) {
    SetFFMode__3GsxFibi(0,1,2);
    SetInter30__3GsxFi(1);
    SetHalfVol__6CFieldFi(this,0);
    this->bFlags_18d = this->bFlags_18d & 0xef | 0x10;
    Dsp__8CFieldBGFv(this->pBg);
    bVar1 = this->bModel_count;
    for (iVar3 = 0; iVar3 < (int)(uint)bVar1; iVar3 = iVar3 + 1) {
      if (this->aModels[iVar3] != (void *)0x0) {
        Dsp__11CFieldModelFi(this->aModels[iVar3],1);
      }
    }
    ShowSavePoint__6CFieldFi(this,1);
    ShowWarpPoint__6CFieldFi(this,1);
    if (this->pNavimap != (void *)0x0) {
      Dsp__8CNaviMapFi(this->pNavimap,1);
    }
    if (sys__8FldTimer != 0) {
      Mask__8FldTimerFi(sys__8FldTimer,0);
    }
    if (this->bMces_state == 0) {
      DspFilter__12CFieldSocketFv(m_socket__12CFieldSocket);
    }
    this->field_0x3c8 = 0;
  }
  return;
}

/* JP: 0x004a3dc0  CField::SetHalfVol(int)   [SetHalfVol__6CFieldFi]  size=0x40 */
void SetHalfVol__6CFieldFi(CField *this,int a0)

{
  this->bFlags_191 = this->bFlags_191 & 0xbf | (byte)((a0 & 1U) << 6);
  return;
}

/* JP: 0x004a3e20  CField::Clr()   [Clr__6CFieldFv]  size=0x170 */
void Clr__6CFieldFv(CField *this)

{
  byte bVar1;
  int iVar2;
  
  if ((long)((ulong)this->bFlags_18d << 0x3b) < 0) {
    this->bFlags_18d = this->bFlags_18d & 0xef;
    bVar1 = this->bModel_count;
    for (iVar2 = 0; iVar2 < (int)(uint)bVar1; iVar2 = iVar2 + 1) {
      if (this->aModels[iVar2] != (void *)0x0) {
        Clr__11CFieldModelFi(this->aModels[iVar2],1);
      }
    }
    Clr__8CFieldBGFv(this->pBg);
    if (this->pNavimap != (void *)0x0) {
      Clr__8CNaviMapFi(this->pNavimap,1);
    }
    if (sys__8FldTimer != 0) {
      Mask__8FldTimerFi(sys__8FldTimer,1);
    }
    ShowSavePoint__6CFieldFi(this,0);
    ShowWarpPoint__6CFieldFi(this,0);
    ClrFilter__12CFieldSocketFv(m_socket__12CFieldSocket);
    if (this->pTeam_change != (void *)0x0) {
      Clr__13FldTeamChangeFv(this->pTeam_change);
    }
  }
  return;
}

/* JP: 0x004a41e0  CField::SaveModelS(int)   [SaveModelS__6CFieldFi]  size=0x288 */
undefined4 SaveModelS__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  char cVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 uVar5;
  long lVar6;
  int iVar7;
  undefined1 *puVar8;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  CField *pCStack_20;
  int iStack_10;
  
  pCStack_20 = this;
  iStack_10 = a0;
  iVar4 = GetModel__6CFieldFi(this,a0);
  if (iVar4 == 0) {
    uVar5 = 0;
  }
  else {
    puVar8 = &pCStack_20->field_0xebc;
    if (*(int *)puVar8 < 0x20) {
      iVar1 = *(int *)puVar8;
      *(int *)puVar8 = iVar1 + 1;
      puVar8[iVar1 * 0x4c + 0x11] = (char)iStack_10;
      *(undefined2 *)(puVar8 + iVar1 * 0x4c + 0x12) = *(undefined2 *)(iVar4 + 0x88);
      GetPos__11CFieldModelFv(auStack_30,iVar4);
      SetShortPos__FPsP7FVector(puVar8 + (iVar1 * 0x13 + 6) * 4,auStack_30);
      uVar3 = GetDir__11CFieldModelFv(iVar4);
      *(undefined2 *)(puVar8 + iVar1 * 0x4c + 0x1e) = uVar3;
      *(undefined2 *)(puVar8 + (iVar1 * 0x13 + 5) * 4) = *(undefined2 *)(iVar4 + 0x8e);
      puVar8[iVar1 * 0x4c + 0x16] = *(undefined1 *)(iVar4 + 0x92);
      puVar8[iVar1 * 0x4c + 0x17] = *(undefined1 *)(iVar4 + 0x93);
      *(undefined4 *)(puVar8 + (iVar1 * 0x13 + 8) * 4) = *(undefined4 *)(iVar4 + 0xc0);
      memcpy(puVar8 + (iVar1 * 0x13 + 9) * 4,iVar4 + 0xa4,0xc);
      *(undefined4 *)(puVar8 + (iVar1 * 0x13 + 0xc) * 4) = *(undefined4 *)(iVar4 + 0xb4);
      puVar8[(iVar1 * 0x13 + 0xf) * 4] = *(undefined1 *)(iVar4 + 0xfc);
      puVar8[iVar1 * 0x4c + 0x3d] = *(byte *)(iVar4 + 0x104) >> 5;
      *(undefined4 *)(puVar8 + (iVar1 * 0x13 + 0xd) * 4) = *(undefined4 *)(iVar4 + 300);
      *(undefined4 *)(puVar8 + (iVar1 * 0x13 + 0xe) * 4) = *(undefined4 *)(iVar4 + 0x130);
      if (*(int *)(iVar4 + 0xf4) != 0) {
        uVar5 = *(undefined4 *)(*(int *)(iVar4 + 0xf4) + 0x80);
        lVar6 = strlen(uVar5);
        if (0xc < lVar6) {
          lVar6 = 0xc;
        }
        memcpy(puVar8 + (iVar1 * 0x13 + 0x14) * 4,uVar5,lVar6);
      }
      GetName__15_FieldDataCacheFPc(*(undefined4 *)(iVar4 + 0x148),auStack_40);
      cVar2 = FindFileTbl__14_FieldSaveInfoFPc(puVar8,auStack_40);
      puVar8[iVar1 * 0x4c + 0x3e] = cVar2 + '\x01';
      Release__15_FieldDataCacheFv(*(undefined4 *)(iVar4 + 0x148));
      for (iVar7 = 0; iVar7 < 0x10; iVar7 = iVar7 + 1) {
        if (*(int *)(iVar4 + iVar7 * 4 + 0x14c) != 0) {
          GetName__15_FieldDataCacheFPc(*(undefined4 *)(iVar4 + iVar7 * 4 + 0x14c),auStack_40);
          cVar2 = FindFileTbl__14_FieldSaveInfoFPc(puVar8,auStack_40);
          puVar8[iVar7 + iVar1 * 0x4c + 0x40] = cVar2 + '\x01';
          Release__15_FieldDataCacheFv(*(undefined4 *)(iVar4 + iVar7 * 4 + 0x14c));
        }
      }
      uVar5 = 1;
    }
    else {
      uVar5 = 0xffffffff;
    }
  }
  return uVar5;
}

/* JP: 0x004a44b0  CField::GetModel(int)   [GetModel__6CFieldFi]  size=0x2c */
void * GetModel__6CFieldFi(CField *this,int a0)

{
  return this->aModels[a0];
}

/* JP: 0x004a44e0  CField::RestoreModel(int, int)   [RestoreModel__6CFieldFii]  size=0x34c */
undefined4 RestoreModel__6CFieldFii(CField *this,int a0,int a1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  FVector *a2;
  long lVar5;
  byte *pbVar6;
  int iVar7;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  char acStack_40 [12];
  undefined1 uStack_34;
  CField *pCStack_30;
  int iStack_20;
  int iStack_10;
  
  iVar7 = a0 * 0x4c;
  pbVar6 = this->aObjse_slots + iVar7 + 0x790;
  bVar1 = this->aObjse_slots[iVar7 + 0x791];
  bVar2 = *pbVar6;
  pCStack_30 = this;
  iStack_20 = a0;
  iStack_10 = a1;
  if (bVar2 == 3) {
    __ct__7FVectorFv(auStack_50);
    GetShortPos__FP7FVectorPs(auStack_50,this->aObjse_slots + iVar7 + 0x798);
    a2 = (FVector *)__ct__7FVectorFRC7FVector(auStack_60,auStack_50);
    DispCharacter__6CFieldFii7FVectoriiiPCc
              (pCStack_30,(uint)bVar1,1,a2,(int)*(short *)(this->aObjse_slots + iVar7 + 0x79e),0,0,
               (char *)0x0);
    return 0;
  }
  if (bVar2 != 2) {
    if (bVar2 != 1) {
      if (bVar2 != 0) {
        return 1;
      }
      if (*(short *)(this->aObjse_slots + iVar7 + 0x794) < 0) {
        LoadCharacter__6CFieldFiPCciUi
                  (this,(uint)bVar1,
                   &this->field_0x183c + (uint)this->aObjse_slots[iVar7 + 0x7be] * 0x10,-1,
                   *(uint *)(this->aObjse_slots + iVar7 + 0x7a0));
      }
      else {
        LoadCharacter__6CFieldFiiUi
                  (this,(uint)bVar1,(int)*(short *)(this->aObjse_slots + iVar7 + 0x794),
                   *(uint *)(this->aObjse_slots + iVar7 + 0x7a0));
      }
      iVar3 = GetModel__6CFieldFi(pCStack_30,(uint)bVar1);
      memcpy(iVar3 + 0xa4,this->aObjse_slots + iVar7 + 0x7a4,0xc);
      *(undefined4 *)(iVar3 + 0xb4) = *(undefined4 *)(this->aObjse_slots + iVar7 + 0x7b0);
      *(byte *)(iVar3 + 0x104) =
           *(byte *)(iVar3 + 0x104) & 0x1f | this->aObjse_slots[iVar7 + 0x7bd] << 5;
      *(undefined4 *)(iVar3 + 300) = *(undefined4 *)(this->aObjse_slots + iVar7 + 0x7b4);
      *(undefined4 *)(iVar3 + 0x130) = *(undefined4 *)(this->aObjse_slots + iVar7 + 0x7b8);
      for (iVar7 = 0; iVar7 < 0x10; iVar7 = iVar7 + 1) {
        if (pbVar6[iVar7 + 0x30] != 0) {
          LoadMotion__11CFieldModelFPCcUiPFUiUiPv_vPv
                    (iVar3,&this->field_0x183c + (uint)pbVar6[iVar7 + 0x30] * 0x10,0,0,0);
        }
      }
      *pbVar6 = *pbVar6 + 1;
      return 1;
    }
    uVar4 = GetModel__6CFieldFi(this,(uint)bVar1);
    lVar5 = CheckLastCmdComplete__11CFieldModelFv(uVar4);
    if (lVar5 < 1) {
      return 1;
    }
    *pbVar6 = *pbVar6 + 1;
  }
  if (iStack_10 == 1) {
    GetModel__6CFieldFi(pCStack_30,(uint)bVar1);
    uStack_34 = 0;
    memcpy(acStack_40,this->aObjse_slots + iVar7 + 2000,0xc);
    if (this->aObjse_slots[iVar7 + 0x7bc] != 0xff) {
      CharAddItem__6CFieldFiiPCci
                (pCStack_30,(uint)this->aObjse_slots[iVar7 + 0x7bc],(uint)bVar1,acStack_40,0);
    }
    *pbVar6 = *pbVar6 + 1;
    return 1;
  }
  return 2;
}

/* JP: 0x004a4830  CField::SaveField()   [SaveField__6CFieldFv]  size=0x140 */
void SaveField__6CFieldFv(CField *this)

{
  byte bVar1;
  void *pvVar2;
  undefined8 uVar3;
  int a0;
  long lVar4;
  undefined1 auStack_20 [16];
  CField *pCStack_10;
  
  pCStack_10 = this;
  memset(&this->field_0xebc,0,0xe10);
  SaveRestoreMotion__8CFieldBGFiPc(pCStack_10->pBg,0,&this->field_0x1c4c);
  bVar1 = pCStack_10->bModel_count;
  lVar4 = 0;
  while (lVar4 < (long)(ulong)bVar1) {
    a0 = (int)lVar4;
    pvVar2 = pCStack_10->aModels[a0];
    if (pvVar2 != (void *)0x0) {
      if (lVar4 == (char)pCStack_10->field_0x6cc) {
        GetPos__11CFieldModelFv(auStack_20,pvVar2);
        uVar3 = GetDir__11CFieldModelFv(pvVar2);
        FieldSaveCharPosition__FP7FVectori(auStack_20,uVar3);
      }
      SaveModelS__6CFieldFi(pCStack_10,a0);
    }
    lVar4 = (long)(a0 + 1);
  }
  Clr__6CFieldFv(pCStack_10);
  ClearSDB__6CFieldFi(pCStack_10,1);
  PurgeModel__6CFieldFv(pCStack_10);
  ReleaseWindow__6CFieldFv(pCStack_10);
  return;
}

/* JP: 0x004a4970  CField::RestoreField()   [RestoreField__6CFieldFv]  size=0x1ec */
undefined4 RestoreField__6CFieldFv(CField *this)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  
  cVar1 = this->field_0xec4;
  if (cVar1 == '\x03') {
    bVar2 = true;
    for (iVar5 = 0; iVar5 < *(int *)&this->field_0xebc; iVar5 = iVar5 + 1) {
      iVar3 = RestoreModel__6CFieldFii(this,iVar5,1);
      if (iVar3 != 0) {
        bVar2 = false;
      }
    }
    if (bVar2) {
      return 1;
    }
  }
  else {
    if (cVar1 != '\x02') {
      if (cVar1 != '\x01') {
        if (cVar1 != '\0') {
          return 0;
        }
        ReloadMPS__12CFieldSocketFv(m_socket__12CFieldSocket);
        this->bFlags_18d = this->bFlags_18d & 0xf3 | 4;
        this->field_0xec4 = this->field_0xec4 + '\x01';
      }
      lVar4 = isLoading__12CFieldSocketFv(m_socket__12CFieldSocket);
      if (lVar4 == 0) {
        SaveRestoreMotion__8CFieldBGFiPc(this->pBg,1,&this->field_0x1c4c);
        this->field_0xec4 = 2;
      }
    }
    bVar2 = true;
    for (iVar5 = 0; iVar5 < *(int *)&this->field_0xebc; iVar5 = iVar5 + 1) {
      iVar3 = RestoreModel__6CFieldFii(this,iVar5,0);
      if (iVar3 != 2) {
        bVar2 = false;
      }
    }
    if ((bVar2) && (this->field_0xec4 == '\x02')) {
      this->field_0xec4 = this->field_0xec4 + '\x01';
    }
  }
  return 0;
}

/* JP: 0x004a4b80  CField::PlayMCES(const char*, int, int)   [PlayMCES__6CFieldFPCcii]  size=0x174 */
void PlayMCES__6CFieldFPCcii(CField *this,char *a0,int a1,int a2)

{
  if (this->bMces_state == 0) {
    strcpy(&this->field_0x684,a0);
    FldInitLSDPlayer__Fv();
    this->field_0x6a5 = (char)a1;
    this->bMces_state = 1;
    *(int *)&this->field_0x6ac = a2;
    if ((a1 & 4U) != 0) {
      this->bFlags_18f = this->bFlags_18f & 0xf7 | 8;
    }
    if ((a1 & 1U) == 0) {
      this->field_0x6a8 = this->field_0x6a8 & 0xfd | 2;
      DisablePause__6CPauseFv(*(undefined4 *)(app__4CApp + 0x78));
    }
    else {
      SetPauserType__6SSHSysFi(sys__6SSHSys,1);
    }
    if (a2 < 0) {
      *(ushort *)&this->field_0x6a6 = *(ushort *)&this->field_0x6a6 | 2;
      if (((int)(uint)*(ushort *)&this->field_0x6a6 >> 8 & 0xfU) == 0) {
        Clr__6CFieldFv(this);
      }
      if (((int)(uint)*(ushort *)&this->field_0x6a6 >> 4 & 0xfU) == 0) {
        SaveField__6CFieldFv(this);
      }
    }
  }
  return;
}

/* JP: 0x004a4d40  CField::cbMCES()   [cbMCES__6CFieldFv]  size=0x1a0 */
undefined4 cbMCES__6CFieldFv(CField *this)

{
  CField *this_00;
  undefined4 uVar1;
  
  this_00 = pCGpffff85ec;
  if ((*(int *)&pCGpffff85ec->field_0x6ac == 0) &&
     ((*(ushort *)&pCGpffff85ec->field_0x6a6 & 2) == 0)) {
    *(ushort *)&pCGpffff85ec->field_0x6a6 = *(ushort *)&pCGpffff85ec->field_0x6a6 | 2;
    if (((int)(uint)*(ushort *)&pCGpffff85ec->field_0x6a6 >> 8 & 0xfU) == 0) {
      Clr__6CFieldFv(pCGpffff85ec);
    }
    if (((int)(uint)*(ushort *)&this_00->field_0x6a6 >> 4 & 0xfU) == 0) {
      SaveField__6CFieldFv(this_00);
    }
  }
  if (*(int *)&this_00->field_0x6ac < 1) {
    if (((int)(uint)*(ushort *)&this_00->field_0x6a6 >> 8 & 0xfU) == 0) {
      this_00->bMces_state = 8;
      Pause__7CScriptFi(fldScript__12CFieldSocket,1);
      Pause__6CFieldFi(this_00,0);
    }
    if (this_00->pTeam_change != (void *)0x0) {
      Clr__13FldTeamChangeFv(this_00->pTeam_change);
    }
    this_00->bFlags_18e = this_00->bFlags_18e & 0xfc;
    Report__4SdrvFv(sys__4Sdrv);
    SetPauseTmr__6SSHSysFi(sys__6SSHSys,1000);
    uVar1 = 1;
  }
  else {
    if ((0 < *(int *)&this_00->field_0x6ac) && (this_00->bMces_state == 2)) {
      this_00->bMces_state = 3;
      SetFieldEvent__6CFieldFiUiiii(this_00,3,*(uint *)&this_00->field_0x6ac,0,0,0);
    }
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x004a4ee0  CField::StartMCES()   [StartMCES__6CFieldFv]  size=0x4c */
void StartMCES__6CFieldFv(CField *this)

{
  if (this->bMces_state == 3) {
    *(undefined4 *)&this->field_0x6ac = 0;
    cbMCES__6CFieldFv((CField *)0x3);
  }
  return;
}

/* JP: 0x004a4f30  CField::SetMCESMode(const char*, int, int)   [SetMCESMode__6CFieldFPCcii]  size=0xa8 */
void SetMCESMode__6CFieldFPCcii(CField *this,char *a0,int a1,int a2)

{
  ushort uVar1;
  int iStack_10;
  
  uVar1 = 0;
  if ((a0 != (char *)0x0) && (*a0 != '\0')) {
    strcpy(&this->field_0x694,a0);
    uVar1 = 1;
  }
  iStack_10 = a2;
  if (a1 == 0) {
    iStack_10 = 0;
  }
  *(ushort *)&this->field_0x6a6 = uVar1 | (ushort)(a1 << 4) | (ushort)(iStack_10 << 8);
  return;
}

/* JP: 0x004a50c0  CField::BreakMCES(int)   [BreakMCES__6CFieldFi]  size=0x150 */
void BreakMCES__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  long lVar2;
  int iStack_10;
  
  if (this->bMces_state == 8) {
    iStack_10 = a0;
    if (((this->field_0x6a5 & 4) != 0) && (sys__6CField != 0)) {
      iStack_10 = 2;
    }
    if (iStack_10 != 2) {
      iVar1 = sys__11CScrCapture;
      if (sys__11CScrCapture == 0) {
        lVar2 = __nw__FUi(0x24);
        iVar1 = 0;
        if (lVar2 != 0) {
          iVar1 = __ct__11CScrCaptureFv(lVar2);
        }
      }
      sys__11CScrCapture = iVar1;
      Create__11CScrCaptureFiiP9BufMemory(sys__11CScrCapture,0,0,0);
      SetLayer__11CScrCaptureFi(sys__11CScrCapture,0xd);
    }
    ClrFilter__12CFieldSocketFv(m_socket__12CFieldSocket);
    Pause__9LSDPlayerFv(sys__9LSDPlayer);
    Exit__9LSDPlayerFv(sys__9LSDPlayer);
    this->bMces_state = 0xb;
    if (iStack_10 == 1) {
      this->bMces_state = 10;
    }
    if (iStack_10 == 2) {
      this->bMces_state = 0x12;
    }
  }
  return;
}

/* JP: 0x004a5340  CField::ResetMCES(int)   [ResetMCES__6CFieldFi]  size=0x124 */
void ResetMCES__6CFieldFi(CField *this,int a0)

{
  if (sys__9LSDPlayer != 0) {
    if (sys__9LSDPlayer != 0) {
      (**(code **)(*(int *)(sys__9LSDPlayer + 0x14) + 8))(sys__9LSDPlayer,1);
    }
    sys__9LSDPlayer = 0;
  }
  if (sys__11CScrCapture != 0) {
    Delete__11CScrCaptureFv(sys__11CScrCapture);
    sys__11CScrCapture = 0;
  }
  Unpause__4SdrvFv(sys__4Sdrv);
  if (a0 == 0) {
    Pause__6CFieldFi(this,1);
  }
  SetPauserType__6SSHSysFi(sys__6SSHSys,0);
  SetPauseTmr__6SSHSysFi(sys__6SSHSys,0xfffffffffffffffe);
  if ((long)((ulong)(byte)this->field_0x6a8 << 0x3e) < 0) {
    EnablePause__6CPauseFi(*(undefined4 *)(app__4CApp + 0x78),1);
  }
  PauseFader__12CFieldSocketFi(m_socket__12CFieldSocket,1);
  memset(&this->field_0x684,0,0x2c);
  return;
}

/* JP: 0x004a54a0  CField::UpdateMCES()   [UpdateMCES__6CFieldFv]  size=0x410 */
undefined4 UpdateMCES__6CFieldFv(CField *this)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  undefined1 auStack_60 [80];
  CField *pCStack_10;
  
  pCStack_10 = this;
  GetReal__4CPadCFv(this->pPad);
  bVar1 = this->bMces_state;
  if (bVar1 == 0x12) {
    if ((sys__9LSDPlayer == 0) || (lVar3 = Reset__9LSDPlayerFv(sys__9LSDPlayer), lVar3 != 0)) {
      ResetMCES__6CFieldFi(pCStack_10,0);
      return 1;
    }
  }
  else if (bVar1 == 0x10) {
    SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,1,0);
    if ((sys__9LSDPlayer == 0) || (lVar3 = Reset__9LSDPlayerFv(sys__9LSDPlayer), lVar3 != 0)) {
      SetChrPosSaveState__Fi(0xffffffffffffffff);
      MapJump__6CFieldFPCc(pCStack_10,&this->field_0x694);
      DspFilter__12CFieldSocketFv(m_socket__12CFieldSocket);
      ResetMCES__6CFieldFi(pCStack_10,1);
    }
  }
  else {
    if (bVar1 != 0xe) {
      if (bVar1 != 0xd) {
        if (bVar1 != 0xc) {
          if ((bVar1 != 0xb) && (bVar1 != 10)) {
            if (bVar1 == 8) {
              lVar3 = Reset__9LSDPlayerFv(sys__9LSDPlayer);
              if (lVar3 == 0) {
                return 0;
              }
              if (((int)(uint)*(ushort *)&this->field_0x6a6 >> 8 & 0xfU) == 0) {
                SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,1,0);
              }
              this->bMces_state = 0xc;
              return 0;
            }
            if (bVar1 != 1) {
              return 0;
            }
            lVar3 = Reset__9LSDPlayerFv(sys__9LSDPlayer);
            if (lVar3 == 0) {
              return 0;
            }
            sprintf(auStack_60,0x5559c8,pDataPath__7SysTool,&this->field_0x684);
            setStartCallBack__9LSDPlayerFPFv_b(sys__9LSDPlayer,0x4a4d40);
            startStream__9LSDPlayerFPc(sys__9LSDPlayer,auStack_60);
            this->bMces_state = this->bMces_state + 1;
            return 0;
          }
          lVar3 = Reset__9LSDPlayerFv(sys__9LSDPlayer);
          if (lVar3 == 0) {
            return 0;
          }
          this->bMces_state = 0xc;
          if (this->bMces_state == 10) {
            uVar4 = 0;
          }
          else {
            uVar4 = 700;
          }
          SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,1,uVar4);
          PauseFader__12CFieldSocketFi(m_socket__12CFieldSocket,1);
        }
        if (sys__9LSDPlayer != 0) {
          if (sys__9LSDPlayer != 0) {
            (**(code **)(*(int *)(sys__9LSDPlayer + 0x14) + 8))(sys__9LSDPlayer,1);
          }
          sys__9LSDPlayer = 0;
        }
        if ((*(ushort *)&this->field_0x6a6 & 1) != 0) {
          this->bMces_state = 0x10;
          return 0;
        }
        if (((int)(uint)*(ushort *)&this->field_0x6a6 >> 4 & 0xfU) == 0) {
          RestoreField__6CFieldFv(pCStack_10);
          this->bMces_state = 0xd;
          return 0;
        }
        this->bMces_state = 0xe;
        return 0;
      }
      iVar2 = RestoreField__6CFieldFv(pCStack_10);
      if (iVar2 == 0) {
        return 0;
      }
      this->bMces_state = 0xe;
    }
    lVar3 = isFaderBusy__12CFieldSocketFi(m_socket__12CFieldSocket,1);
    if (lVar3 == 0) {
      if (((int)(uint)*(ushort *)&this->field_0x6a6 >> 8 & 0xfU) == 0) {
        SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,1,0);
        Dsp__6CFieldFv(pCStack_10);
        DspFilter__12CFieldSocketFv(m_socket__12CFieldSocket);
      }
      ResetMCES__6CFieldFi(pCStack_10,0);
      return 1;
    }
  }
  return 0;
}

/* JP: 0x004a5990  CField::FileReadOrder(int, const char*, void*)   [FileReadOrder__6CFieldFiPCcPv]  size=0x58 */
void FileReadOrder__6CFieldFiPCcPv(CField *this,int a0,char *a1,void *a2)

{
  *(short *)(sys__6CField + 0x1aa) = *(short *)(sys__6CField + 0x1aa) + 1;
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,a0,0x4a5ae0,this,a1,0);
  return;
}

/* JP: 0x004a5ae0  CField::cbDataRead(int, BufMemory*, int, char*, void*)   [cbDataRead__6CFieldFiP9BufMemoryiPcPv]  size=0x154 */
undefined4
cbDataRead__6CFieldFiP9BufMemoryiPcPv(CField *this,int a0,void *a1,int a2,char *a3,void *a4)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  
  *(short *)&pCGpffff85ec->field_0x1aa = *(short *)&pCGpffff85ec->field_0x1aa + -1;
  if (this == (CField *)0x82) {
    OnLoadEffect__6CFieldFP9BufMemoryiPv(pCGpffff85ec,(void *)a0,(int)a1,a3);
    uVar1 = 0;
  }
  else if (this == (CField *)0x81) {
    iVar2 = strlen(a2);
    lVar3 = _stricmp__FPCcPCc(0x5559d8,a2 + iVar2 + -3);
    Create__9FldSpriteFP9BufMemoryib(a3,a0,lVar3 != 0,0);
    uVar1 = 0;
  }
  else if ((this == (CField *)0x7) || (this == (CField *)0x6)) {
    uVar1 = cbReadSoundFile__6CFieldFiP9BufMemoryiPv(pCGpffff85ec,(int)this,(void *)a0,(int)a1,a3);
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x004a5c40  CField::ReleaseWindow()   [ReleaseWindow__6CFieldFv]  size=0x2dc */
void ReleaseWindow__6CFieldFv(CField *this)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    if (*(int *)(&this->field_0x60c + iVar2 * 0x14) != 0) {
      DestroyWindow__12FieldMessageFv(*(undefined4 *)(&this->field_0x60c + iVar2 * 0x14));
      iVar1 = *(int *)(&this->field_0x60c + iVar2 * 0x14);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
      }
      *(undefined4 *)(&this->field_0x60c + iVar2 * 0x14) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
    if (*(int *)(&this->field_0x65c + iVar2 * 0x14) != 0) {
      DestroyWindow__12FieldMessageFv(*(undefined4 *)(&this->field_0x65c + iVar2 * 0x14));
      iVar1 = *(int *)(&this->field_0x65c + iVar2 * 0x14);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
      }
      *(undefined4 *)(&this->field_0x65c + iVar2 * 0x14) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
    if (*(int *)(&this->field_0x6b0 + iVar2 * 4) != 0) {
      Release__9FaceImageFv(*(undefined4 *)(&this->field_0x6b0 + iVar2 * 4));
      iVar1 = *(int *)(&this->field_0x6b0 + iVar2 * 4);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
      }
      *(undefined4 *)(&this->field_0x6b0 + iVar2 * 4) = 0;
    }
  }
  for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
    if (*(int *)(&this->field_0x6b8 + iVar2 * 4) != 0) {
      Release__9FldSpriteFv(*(undefined4 *)(&this->field_0x6b8 + iVar2 * 4));
      iVar1 = *(int *)(&this->field_0x6b8 + iVar2 * 4);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
      }
      *(undefined4 *)(&this->field_0x6b8 + iVar2 * 4) = 0;
    }
  }
  return;
}

/* JP: 0x004a6260  CField::Polling()   [Polling__6CFieldFv]  size=0x1e34 */
undefined4 Polling__6CFieldFv(CField *this)

{
  void *pvVar1;
  byte bVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  ushort *puVar6;
  void *pvVar7;
  undefined4 uVar8;
  byte *pbVar9;
  FVector *pFVar10;
  long lVar11;
  ulong uVar12;
  undefined8 uVar13;
  byte bVar14;
  uint a1;
  float fVar15;
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  CFieldCamera CStack_1c0;
  undefined1 auStack_f0 [28];
  uint uStack_d4;
  uint uStack_d0;
  ushort *puStack_cc;
  undefined4 uStack_c8;
  int iStack_c4;
  void *pvStack_c0;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  int iStack_b0;
  uint uStack_ac;
  uint uStack_a8;
  int iStack_a4;
  uint uStack_a0;
  int iStack_9c;
  uint uStack_98;
  float fStack_94;
  int iStack_90;
  int iStack_8c;
  float fStack_88;
  int iStack_84;
  uint uStack_80;
  uint uStack_7c;
  float fStack_78;
  int iStack_74;
  int iStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  void *pvStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  uint uStack_4c;
  float fStack_48;
  float fStack_44;
  undefined4 uStack_40;
  void *pvStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  uint uStack_28;
  int iStack_24;
  float fStack_20;
  uint uStack_1c;
  int iStack_18;
  char cStack_14;
  char cStack_13;
  char cStack_12;
  byte bStack_11;
  CField *pCStack_10;
  
  pCStack_10 = this;
  if ((this->bFlags_18c & 1) != 0) {
    iStack_18 = 0;
    PollingSound__6CFieldFv(this);
    if (pCStack_10->pSe != (void *)0x0) {
      lVar11 = (**(code **)(*(int *)((int)pCStack_10->pSe + 4) + 0x10))();
      if (lVar11 == 0) {
        iStack_18 = 1;
      }
      else {
        pvStack_c0 = pCStack_10->pSe;
        if (pvStack_c0 != (void *)0x0) {
          (**(code **)(*(int *)((int)pvStack_c0 + 4) + 8))(pvStack_c0,1);
        }
        pCStack_10->pSe = (void *)0x0;
      }
    }
    if (sys__6CMusic != 0) {
      lVar11 = Release__6CMusicFv(sys__6CMusic);
      if (lVar11 == 0) {
        iStack_18 = 1;
      }
      else {
        iStack_c4 = sys__6CMusic;
        if (sys__6CMusic != 0) {
          (**(code **)(*(int *)(sys__6CMusic + 0x14) + 8))(sys__6CMusic,1);
        }
        sys__6CMusic = 0;
      }
    }
    if (iStack_18 == 0) {
      Report__4SdrvFv(sys__4Sdrv);
      PurgeModel__6CFieldFv(pCStack_10);
      if (pCStack_10->pPad != (void *)0x0) {
        __dt__4CPadFv(pCStack_10->pPad,1);
      }
      if (pCStack_10->pCamera != (CFieldCamera *)0x0) {
        __dt__12CFieldCameraFv(pCStack_10->pCamera,1);
      }
      ReleaseWindow__6CFieldFv(pCStack_10);
      pCStack_10->field_0x22 = pCStack_10->field_0x22 & 0xfe;
      closeInquiry__6CFieldFv(pCStack_10);
      SetAutoDelete__7CPolObjFb(pCStack_10,1);
      return 1;
    }
    return 0;
  }
  if ((long)((ulong)this->bFlags_18c << 0x3e) < 0) {
    Delete__6CFieldFv(this);
    return 0;
  }
  if ((this->bFlags_18d & 3) != 0) {
    bVar14 = this->bFlags_18d & 3;
    if (bVar14 == 2) {
      StartBtlIn__9BtlInBossFv();
    }
    else if (bVar14 == 1) {
      StartBtlIn__5BtlInFv();
    }
    ClrFilter__12CFieldSocketFv(m_socket__12CFieldSocket);
    Delete__6CFieldFv(pCStack_10);
    StartBattle__6SSHSysFP12_SysBtlParamPCc(sys__6SSHSys,0x55f180,0);
    SetChrPosSaveState__Fi(1);
    return 0;
  }
  lVar11 = isStable__12CFieldSocketFv(m_socket__12CFieldSocket);
  if (lVar11 == 0) {
    return 0;
  }
  if ((pCStack_10->bFlags_18e & 3) != 0) {
    pCStack_10->field_0x719 = 0;
  }
  if (((pCStack_10->field_0x719 != '\0') && ((pCStack_10->bFlags_190 & 3) == 0)) &&
     (((ulong)pCStack_10->bFlags_191 & 0x1f) >> 2 == 0)) {
    CacheMPS__12CFieldSocketFPCc(m_socket__12CFieldSocket,&pCStack_10->field_0x719);
    pCStack_10->field_0x719 = 0;
  }
  if (pCStack_10->bMces_state != 0) {
    UpdateMCES__6CFieldFv(pCStack_10);
  }
  PollingSound__6CFieldFv(pCStack_10);
  if (((ulong)pCStack_10->bFlags_18d & 0xf) >> 2 == 2) {
    if (((long)((ulong)pCStack_10->bFlags_191 << 0x39) < 0) &&
       ((byte)pCStack_10->field_0x5ef < 0x50)) {
      UpdateObjSE__6CFieldFv(pCStack_10);
    }
    return 0;
  }
  iVar5 = isLoadBusy__6CFieldFv(pCStack_10);
  if ((iVar5 == 0) && (-1 < (long)((ulong)pCStack_10->bFlags_18f << 0x3c))) {
    LoadFieldData__12CFieldSocketFv(m_socket__12CFieldSocket);
  }
  UpdateRing__6CFieldFv(pCStack_10);
  uStack_1c = GetFrameDelta__6SSHSysFv(sys__6SSHSys);
  *(uint *)&pCStack_10->field_0x6e4 = *(int *)&pCStack_10->field_0x6e4 + uStack_1c;
  fStack_20 = (float)uStack_1c / 1000.0;
  UpdateDelayEvent__6CFieldFv(pCStack_10);
  UpdateMsgState__6CFieldFv(pCStack_10);
  if (pCStack_10->wState == 3) {
    fStack_20 = 0.0;
  }
  uStack_28 = (uint)pCStack_10->bModel_count;
  if (pCStack_10->pBg != (CFieldBG *)0x0) {
    Update__8CFieldBGFf(pCStack_10->pBg,fStack_20);
  }
  for (iStack_24 = 0; iStack_24 < (int)uStack_28; iStack_24 = iStack_24 + 1) {
    pvVar7 = pCStack_10->aModels[iStack_24];
    if (((pvVar7 != (void *)0x0) &&
        (Update__11CFieldModelFf(fStack_20,pvVar7), *(char *)((int)pvVar7 + 0xb0) != '\0')) &&
       (pCStack_10->pNavimap != (void *)0x0)) {
      iStack_2c = *(byte *)((int)pvVar7 + 0xb0) - 1;
      lVar11 = isDsp__11CFieldModelFv(pvVar7);
      if (lVar11 == 0) {
        DspItem__8CNaviMapFib(pCStack_10->pNavimap,iStack_2c,0);
      }
      else {
        GetWorldPos__11CFieldModelFv(auStack_f0,pvVar7);
        fVar15 = (float)GetRotY__11CFieldModelFv(pvVar7);
        iStack_30 = (int)(fVar15 * 57.29579);
        if (iStack_30 < 0) {
          iStack_30 = iStack_30 + 0x168;
        }
        if (*(byte *)((int)pvVar7 + 0xb1) >> 4 == 0) {
          uStack_c8 = 2;
        }
        else {
          uStack_c8 = 5;
        }
        SetItem__8CNaviMapFiiR7FVectoriibUi
                  (pCStack_10->pNavimap,iStack_2c,uStack_c8,auStack_f0,iStack_30,
                   *(byte *)((int)pvVar7 + 0xb1) & 0xf,1,0);
      }
    }
  }
  if (pCStack_10->wState == 1) {
    iStack_34 = 0;
    iStack_38 = 0;
    do {
      if ((int)uStack_28 <= iStack_38) {
LAB_004a6a20:
        if (iStack_34 == 0) {
          pCStack_10->wState = 2;
        }
        return 0;
      }
      pvStack_3c = pCStack_10->aModels[iStack_38];
      if ((pvStack_3c != (void *)0x0) &&
         (lVar11 = isLoading__11CFieldModelFv(pvStack_3c), lVar11 != 0)) {
        iStack_34 = 1;
        goto LAB_004a6a20;
      }
      iStack_38 = iStack_38 + 1;
    } while( true );
  }
  uStack_40 = 1;
  iVar5 = CheckEncount__6CFieldFv(pCStack_10);
  if (0 < iVar5) {
    uStack_4c = 0;
    iStack_50 = Find__6CSTGDBFUl(m_pSTGDB__6CField,0x20205445534e4f4d);
    if (iStack_50 != 0) {
      puVar6 = (ushort *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(m_pSTGDB__6CField,iStack_50);
      iStack_54 = rand();
      iStack_54 = iStack_54 % 100;
      iStack_58 = *(int *)(iStack_50 + 8);
      for (iStack_5c = 0; iStack_5c < iStack_58; iStack_5c = iStack_5c + 1) {
        if (iStack_54 < (int)(uint)(byte)puVar6[1]) {
          uStack_4c = (uint)*puVar6;
          break;
        }
        iStack_54 = iStack_54 - (uint)(byte)puVar6[1];
        puStack_cc = puVar6;
        puVar6 = puVar6 + 2;
      }
    }
    ScriptSuspend__6CFieldFv(pCStack_10);
    InvokeBattle__6CFieldFiiiiii(pCStack_10,0,-1,-1,-1,uStack_4c,1);
    return 0;
  }
  fStack_48 = 0.0;
  fStack_44 = 0.0;
  pvStack_60 = pCStack_10->pPad;
  uVar3 = GetReal__4CPadCFv(pvStack_60);
  uVar4 = GetPress__4CPadCFv(pvStack_60);
  uStack_40 = MakeMoveControl__FRfRfP4CPad(&fStack_44,&fStack_48,pvStack_60);
  *(float *)&pCStack_10->field_0x6f4 = fStack_44;
  *(float *)&pCStack_10->field_0x6f8 = fStack_48;
  *(ushort *)&pCStack_10->field_0x6fc = uVar3;
  if (((pCStack_10->bFlags_18e & 3) != 0) && (fStack_44 < 0.1)) {
    *(undefined4 *)&pCStack_10->field_0x700 = 0;
  }
  if ((pCStack_10->bFlags_18e & 3) == 1) {
    uVar3 = *(ushort *)&pCStack_10->field_0x6ea;
    fStack_44 = *(float *)&pCStack_10->field_0x6ec;
    fStack_48 = *(float *)&pCStack_10->field_0x6f0;
  }
  a1 = (uint)uVar3;
  if ((((ulong)pCStack_10->bFlags_18d & 0xf) >> 2 == 1) ||
     ((long)((ulong)pCStack_10->bFlags_18d << 0x3a) < 0)) {
    uVar4 = 0;
    a1 = 0;
    fStack_48 = 0.0;
    fStack_44 = 0.0;
  }
  *(float *)&pCStack_10->field_0x6ec = fStack_44;
  *(float *)&pCStack_10->field_0x6f0 = fStack_48;
  *(short *)&pCStack_10->field_0x6ea = (short)a1;
  if (fStack_44 < 0.1) {
    pCStack_10->bFlags_18c = pCStack_10->bFlags_18c & 0x1f;
    pCStack_10->flCam_yaw_adjust = 0.0;
  }
  pvVar7 = (void *)GetCtrlModel__6CFieldFv(pCStack_10);
  bVar14 = 0;
  if (pvVar7 != (void *)0x0) {
    lVar11 = isDsp__11CFieldModelFv(pvVar7);
    bVar14 = lVar11 != 0;
    lVar11 = isManual__11CFieldModelFv(pvVar7);
    if (lVar11 != 0) {
      bVar14 = bVar14 | 2;
    }
  }
  if ((pCStack_10->bFlags_18e & 3) == 2) {
    lVar11 = GetFaderLevel__12CFieldSocketFi(m_socket__12CFieldSocket,1);
    if (lVar11 < 0x61) {
      if (bVar14 == 3) {
        pCStack_10->bFlags_18e = pCStack_10->bFlags_18e & 0xfc | 3;
      }
    }
    else {
      bVar14 = bVar14 & 0xfd;
    }
  }
  if (bVar14 == 0) goto LAB_004a76a8;
  __ct__7FVectorFv(&CStack_1c0.flPitch_deg);
  GetCameraAngle__12CFieldCameraFv(&CStack_1c0);
  __as__7FVectorFRC7FVector(&pCStack_10->cam_angle,&CStack_1c0);
  GetRot__11CFieldModelFv(auStack_1d0,pvVar7);
  __as__7FVectorFRC7FVector(&CStack_1c0.flPitch_deg,auStack_1d0);
  if (bVar14 == 3) {
    fStack_64 = (pCStack_10->cam_angle).flY;
    bVar2 = pCStack_10->bFlags_18c >> 5;
    if (bVar2 == 4) {
      iStack_74 = GetTimer__7SysToolFv();
      iStack_74 = iStack_74 - *(int *)&pCStack_10->field_0x6d8;
      fStack_78 = *(float *)&pCStack_10->field_0x6dc - fStack_48;
      if (fStack_78 < 0.0) {
        fStack_78 = -fStack_78;
      }
      if (180.0 < fStack_78) {
        fStack_78 = 180.0;
      }
      fStack_78 = 1.0 - fStack_78 / 180.0;
      fStack_78 = fStack_78 * fStack_78;
      if (0.99 < fStack_78) {
        fStack_78 = 0.99;
      }
      pCStack_10->flCam_yaw_adjust = pCStack_10->flCam_yaw_adjust * fStack_78;
      if ((-1.0 <= pCStack_10->flCam_yaw_adjust) && (pCStack_10->flCam_yaw_adjust < 1.0)) {
        pCStack_10->bFlags_18c = pCStack_10->bFlags_18c & 0x1f;
        pCStack_10->flCam_yaw_adjust = 0.0;
      }
      fStack_48 = fStack_48 + pCStack_10->flCam_yaw_adjust;
    }
    else {
      if (bVar2 != 3) {
        if (bVar2 != 2) {
          if (bVar2 != 1) goto LAB_004a7448;
          *(float *)&pCStack_10->field_0x6dc = fStack_48;
        }
        fStack_68 = pCStack_10->flCam_yaw_adjust - fStack_64;
        pCStack_10->flCam_yaw_adjust = fStack_68;
        if (180.0 < pCStack_10->flCam_yaw_adjust) {
          pCStack_10->flCam_yaw_adjust = pCStack_10->flCam_yaw_adjust - 360.0;
        }
        if (pCStack_10->flCam_yaw_adjust < -180.0) {
          pCStack_10->flCam_yaw_adjust = pCStack_10->flCam_yaw_adjust + 360.0;
        }
        uVar8 = GetTimer__7SysToolFv();
        *(undefined4 *)&pCStack_10->field_0x6d8 = uVar8;
        pCStack_10->bFlags_18c = pCStack_10->bFlags_18c & 0x1f | 0x60;
      }
      fStack_6c = *(float *)&pCStack_10->field_0x6dc - fStack_48;
      if (180.0 < fStack_6c) {
        fStack_6c = fStack_6c - 360.0;
      }
      if (fStack_6c < -180.0) {
        fStack_6c = fStack_6c + 360.0;
      }
      iStack_70 = GetTimer__7SysToolFv();
      iStack_70 = iStack_70 - *(int *)&pCStack_10->field_0x6d8;
      if (((pCStack_10->flCam_yaw_adjust < 0.0) && (fStack_6c < 0.0)) ||
         ((0.0 < pCStack_10->flCam_yaw_adjust && (0.0 < fStack_6c)))) {
        pCStack_10->bFlags_18c = pCStack_10->bFlags_18c & 0x1f | 0x80;
        uVar8 = GetTimer__7SysToolFv();
        *(undefined4 *)&pCStack_10->field_0x6d8 = uVar8;
      }
      else {
        if (((pCStack_10->flCam_yaw_adjust < 0.0) && (-fStack_6c < pCStack_10->flCam_yaw_adjust)) ||
           ((0.0 < pCStack_10->flCam_yaw_adjust && (pCStack_10->flCam_yaw_adjust < -fStack_6c)))) {
          pCStack_10->bFlags_18c = pCStack_10->bFlags_18c & 0x1f;
          pCStack_10->flCam_yaw_adjust = 0.0;
        }
        else {
          pCStack_10->flCam_yaw_adjust = pCStack_10->flCam_yaw_adjust + fStack_6c;
        }
        if ((-1.0 < pCStack_10->flCam_yaw_adjust) && (pCStack_10->flCam_yaw_adjust < 1.0)) {
          pCStack_10->bFlags_18c = pCStack_10->bFlags_18c & 0x1f;
          pCStack_10->flCam_yaw_adjust = 0.0;
        }
        *(float *)&pCStack_10->field_0x6dc = fStack_48;
      }
      fStack_48 = fStack_48 + pCStack_10->flCam_yaw_adjust;
    }
LAB_004a7448:
    if (0.1 <= fStack_44) {
      fStack_48 = (float)GetRad((fStack_64 + fStack_48) - 180.0);
      clipRadian__FRf(&fStack_48);
      CStack_1c0.flYaw_deg = fStack_48;
      PlayMoveMotion__11CFieldModelFi(pvVar7,uStack_40);
    }
    else {
      PlayMoveMotion__11CFieldModelFi(pvVar7,0);
    }
    fVar15 = (float)GetRotY__11CFieldModelFv(pvVar7);
    if (CStack_1c0.flYaw_deg != fVar15) {
      SetDir__11CFieldModelFR7FVectorii(pvVar7,&CStack_1c0.flPitch_deg,2,3);
    }
    ChkLookPoint__6CFieldFi(pCStack_10,1);
    UpdateNavi__6CFieldFUii(pCStack_10,uStack_1c,a1);
  }
  else if ((-1 < (long)((ulong)*(byte *)((int)pvVar7 + 0x80) << 0x3a)) &&
          (lVar11 = isAutoCtrl__11CFieldModelFv(pvVar7), lVar11 == 0)) {
    PlayMoveMotion__11CFieldModelFi(pvVar7,0);
  }
  if (-1 < (long)((ulong)pCStack_10->bFlags_18e << 0x38)) {
    GetWorldPos__11CFieldModelFv(auStack_1e0,pvVar7);
    __as__7FVectorFRC7FVector(&pCStack_10->player_pos,auStack_1e0);
  }
  if (pCStack_10->pNavimap != (void *)0x0) {
    iVar5 = GetOption__15SaveMenuSectionFv();
    uStack_d0 = (uint)(((ulong)*(byte *)(iVar5 + 9) & 0xf) >> 2 == 0);
    uStack_7c = uStack_d0;
    pbVar9 = (byte *)GetFldGSFlag__Fv();
    if ((*pbVar9 & 1) == 0) {
      uStack_d4 = 2;
    }
    else {
      uStack_d4 = 0;
    }
    uStack_7c = uStack_7c | uStack_d4;
    DspClr__8CNaviMapFi(pCStack_10->pNavimap,uStack_7c);
    Update__8CNaviMapFfP7FVectorf
              (fStack_20,*(undefined4 *)((int)pvVar7 + 0x24),pCStack_10->pNavimap,
               &pCStack_10->player_pos);
  }
LAB_004a76a8:
  bStack_11 = 1;
  cStack_12 = '\x01';
  cStack_13 = '\x01';
  cStack_14 = '\x01';
  if ((-1 < (long)((ulong)pCStack_10->bFlags_18d << 0x3a)) && (pCStack_10->bFlags_18d >> 6 == 0)) {
    cStack_14 = '\0';
  }
  if ((cStack_14 == '\0') && ((pCStack_10->bFlags_18e & 3) == 0)) {
    cStack_13 = '\0';
  }
  if ((cStack_13 == '\0') && ((pCStack_10->bFlags_18d & 3) == 0)) {
    cStack_12 = '\0';
  }
  if ((cStack_12 == '\0') && (((ulong)pCStack_10->bFlags_18d & 0xf) >> 2 == 0)) {
    bStack_11 = 0;
  }
  uStack_80 = (uint)bStack_11;
  uVar12 = (ulong)(int)uStack_80;
  if (((uVar12 == 0) && (uVar12 = isFaderDsp__12CFieldSocketFi(m_socket__12CFieldSocket,0), uVar12 == 0)) &&
     (uVar12 = isFaderDsp__12CFieldSocketFi(m_socket__12CFieldSocket,1), uVar12 == 0)) {
    if (((uVar4 == 0x1000) && (bVar14 == 3)) && (lVar11 = CheckCmdMenu__12CFieldSocketFv(m_socket__12CFieldSocket), lVar11 != 0)
       ) {
      pCStack_10->bFlags_18d = pCStack_10->bFlags_18d & 0xdf | 0x20;
      Pause__7CScriptFi(fldScript__12CFieldSocket,1);
      return 0;
    }
    if ((bVar14 == 3) && (pCStack_10->pTeam_change != (void *)0x0)) {
      Update__13FldTeamChangeFi(pCStack_10->pTeam_change,uVar4);
    }
    if (((uVar4 & 0x2000) != 0) && (bVar14 == 3)) {
      uVar13 = __ct__7FVectorFv(&CStack_1c0.vec_b0);
      __ct__7FVectorFv(&CStack_1c0.flGoal_angle,uVar13);
      __ct__7FVectorFffff(0,0,0x3f800000,0x3f800000,&CStack_1c0.goal_target);
      GetPos__11CFieldModelFv(auStack_1f0,pvVar7);
      __as__7FVectorFRC7FVector(&CStack_1c0.vec_b0,auStack_1f0);
      __ct__6MatrixFv(&CStack_1c0.from_target);
      UnitMatrix__6MatrixFv(&CStack_1c0.from_target);
      RotYMatrix__6MatrixFf(*(undefined4 *)((int)pvVar7 + 0x24),&CStack_1c0.from_target);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_200,&CStack_1c0.from_target,&CStack_1c0.goal_target);
      __as__7FVectorFRC7FVector(&CStack_1c0.goal_target,auStack_200);
      iStack_84 = -1;
      fStack_88 = 0.0;
      iStack_8c = 0;
      for (iStack_90 = 0; iStack_90 < (int)uStack_28; iStack_90 = iStack_90 + 1) {
        pvVar1 = pCStack_10->aModels[iStack_90];
        if (((pvVar1 != (void *)0x0) && (pvVar1 != pvVar7)) &&
           (lVar11 = isDsp__11CFieldModelFv(pvVar1), lVar11 != 0)) {
          GetPos__11CFieldModelFv(auStack_220,pvVar1);
          __mi__7FVectorCFRC7FVector(auStack_210,&CStack_1c0.vec_b0,auStack_220);
          __as__7FVectorFRC7FVector(&CStack_1c0.flGoal_angle,auStack_210);
          fStack_94 = (float)Length__7FVectorCFv(&CStack_1c0.flGoal_angle);
          if (fStack_94 <= 12.0) {
            Normalize__7FVectorFv(&CStack_1c0.flGoal_angle);
            fStack_94 = (float)InnerProduct__7FVectorCFRC7FVector
                                         (&CStack_1c0.flGoal_angle,&CStack_1c0.goal_target);
            if ((0.5 <= fStack_94) && (fStack_88 < fStack_94)) {
              iStack_84 = iStack_90;
              fStack_88 = fStack_94;
            }
          }
        }
      }
      if (iStack_84 < 0) {
        __ml__7FVectorCFf(0x40c00000,auStack_240,&CStack_1c0.goal_target);
        __mi__7FVectorCFRC7FVector(auStack_230,&CStack_1c0.vec_b0,auStack_240);
        __as__7FVectorFRC7FVector(&CStack_1c0.flGoal_angle,auStack_230);
        iStack_9c = -1;
        if (pCStack_10->pEvent_boxes != (CFieldEvent *)0x0) {
          pFVar10 = (FVector *)__ct__7FVectorFRC7FVector(auStack_250,&CStack_1c0.flGoal_angle);
          iStack_9c = HitCheck__11CFieldEventF7FVectorii(pCStack_10->pEvent_boxes,pFVar10,0,1);
        }
        if (-1 < iStack_9c) {
          uStack_a0 = GetEventNum__11CFieldEventFi(pCStack_10->pEvent_boxes,iStack_9c);
          iStack_a4 = GetEventBox__11CFieldEventFi(pCStack_10->pEvent_boxes,iStack_9c);
          if ((((ulong)pCStack_10->bFlags_18c & 0x1f) >> 2 & (ulong)*(byte *)(iStack_a4 + 8) & 0xf &
              4) != 0) {
            SetFieldEvent__6CFieldFiUiiii(pCStack_10,1,uStack_a0,4,1,0);
            iStack_8c = 2;
          }
        }
      }
      else {
        uStack_98 = *(uint *)((int)pCStack_10->aModels[iStack_84] + 0xc0);
        if (uStack_98 != 0) {
          SetFieldEvent__6CFieldFiUiiii(pCStack_10,1,uStack_98,4,1,0);
          iStack_8c = 1;
        }
      }
      if (((iStack_8c == 0) && (pCStack_10->bClr_flag_5ec != 0)) &&
         (iVar5 = (int)(char)pCStack_10->bClr_flag_5ec,
         *(int *)(&pCStack_10->field_0x3e8 + iVar5 * 0x10) != 0)) {
        SetFieldEvent__6CFieldFiUiiii
                  (pCStack_10,2,*(uint *)(&pCStack_10->field_0x3e8 + iVar5 * 0x10),0,0,
                   (uint)*(ushort *)(&pCStack_10->field_0x3ec + iVar5 * 0x10));
      }
    }
    if ((pCStack_10->pEvent_boxes != (CFieldEvent *)0x0) && ((bVar14 & 1) != 0)) {
      pFVar10 = (FVector *)__ct__7FVectorFRC7FVector(auStack_260,&pCStack_10->player_pos);
      iVar5 = HitCheck__11CFieldEventF7FVectorii(pCStack_10->pEvent_boxes,pFVar10,0,0);
      uStack_ac = 0;
      uStack_a8 = 0;
      if (pCStack_10->nUnk5fc != -1) {
        uStack_a8 = GetEventNum__11CFieldEventFi(pCStack_10->pEvent_boxes,pCStack_10->nUnk5fc);
      }
      if (iVar5 != -1) {
        uStack_ac = GetEventNum__11CFieldEventFi(pCStack_10->pEvent_boxes,iVar5);
      }
      if (uStack_a8 != uStack_ac) {
        if ((pCStack_10->nUnk5fc != -1) &&
           (iStack_b0 = GetEventBox__11CFieldEventFi(pCStack_10->pEvent_boxes,pCStack_10->nUnk5fc),
           (((ulong)pCStack_10->bFlags_18c & 0x1f) >> 2 & (ulong)*(byte *)(iStack_b0 + 8) & 0xf & 2)
           != 0)) {
          SetFieldEvent__6CFieldFiUiiii(pCStack_10,1,uStack_a8,2,0,0);
        }
        if (iVar5 != -1) {
          iStack_b4 = GetEventBox__11CFieldEventFi(pCStack_10->pEvent_boxes,iVar5);
          pCStack_10->nUnk600 = uStack_ac;
          if ((((ulong)pCStack_10->bFlags_18c & 0x1f) >> 2 &
               ~((ulong)*(byte *)(iStack_b4 + 8) & 0xf) & 1) != 0) {
            SetFieldEvent__6CFieldFiUiiii(pCStack_10,1,uStack_ac,1,0,0);
          }
        }
      }
      pCStack_10->nUnk5fc = iVar5;
    }
    uVar12 = (ulong)(int)pCStack_10;
    if ((*(int *)&pCStack_10->field_0x604 != 0) && (uVar12 = 0, sys__8FldTimer != 0)) {
      lVar11 = isAlerm__8FldTimerFv(sys__8FldTimer);
      uVar12 = 0;
      if (lVar11 != 0) {
        iStack_b8 = GetEventMagic__7CScriptFv(fldScript__12CFieldSocket);
        uVar12 = (ulong)(iStack_b8 >> 8);
        if ((uVar12 & 0xff) != 0xc2) {
          SetFieldEvent__6CFieldFiUiiii(pCStack_10,0,*(uint *)&pCStack_10->field_0x604,0,0,0);
          ClrAlerm__8FldTimerFv(sys__8FldTimer);
          uVar12 = (ulong)(int)pCStack_10;
          *(undefined4 *)&pCStack_10->field_0x604 = 0;
        }
      }
    }
  }
  CameraUpdate__6CFieldFf(pCStack_10,fStack_20);
  iStack_bc = GetActiveCamera__9GsxCameraFv(uVar12);
  if (iStack_bc != 0) {
    uVar13 = GetFrame__9GsxCameraFv(iStack_bc);
    __ct__6MatrixFRC6Matrix(&CStack_1c0.flRoll,uVar13);
    uVar13 = GetPos__6MatrixFv(&CStack_1c0.flRoll);
    __as__7FVectorFRC7FVector(&pCStack_10->vec_1d10,uVar13);
    uVar13 = GetAt__6MatrixFv(&CStack_1c0.flRoll);
    __as__7FVectorFRC7FVector(&pCStack_10->vec_1d20,uVar13);
    (pCStack_10->vec_1d20).flW = *(float *)(iStack_bc + 0x34c);
  }
  CheckMirror__6CFieldFv(pCStack_10);
  UpdateLight__6CFieldFv(pCStack_10);
  return 0;
}

/* JP: 0x004a83f0  CField::UpdateNavi(unsigned int, int)   [UpdateNavi__6CFieldFUii]  size=0xcc */
void UpdateNavi__6CFieldFUii(CField *this,uint a0,int a1)

{
  int iVar1;
  
  iVar1 = GetOption__15SaveMenuSectionFv(this,a0);
  if (this->field_0x6e8 == '\x01') {
    if ((a1 & 1U) != 0) {
      *(byte *)(iVar1 + 9) =
           *(byte *)(iVar1 + 9) & 0xf3 |
           (byte)(((uint)(((ulong)*(byte *)(iVar1 + 9) << 0x3c) >> 0x3e) ^ 1) << 2);
      this->field_0x6e8 = 0;
    }
  }
  else if ((this->field_0x6e8 == '\0') && ((a1 & 1U) == 0)) {
    this->field_0x6e8 = 1;
  }
  return;
}

/* JP: 0x004a84c0  CField::CameraUpdate(float)   [CameraUpdate__6CFieldFf]  size=0x4e8 */
void CameraUpdate__6CFieldFf(CField *this,float a0)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  CField *pCStack_20;
  float fStack_10;
  
  pCStack_20 = this;
  fStack_10 = a0;
  if ((this->bScr_camera_active == 0) ||
     (UpdateScrCamera__6CFieldFf(this,a0), pCStack_20->bScr_camera_active == 0)) {
    iVar2 = GetCtrlModel__6CFieldFv(pCStack_20);
    if (iVar2 == 0) {
      pCStack_20->bFlags_18c = pCStack_20->bFlags_18c & 0x1f;
      pCStack_20->flCam_yaw_adjust = 0.0;
    }
    else {
      lVar3 = isDsp__11CFieldModelFv(iVar2);
      bVar1 = lVar3 == 0;
      if ((!bVar1) &&
         (GetWorldPos__11CFieldModelFv(auStack_40,iVar2),
         -1 < (long)((ulong)pCStack_20->bFlags_18e << 0x38))) {
        __as__7FVectorFRC7FVector(&pCStack_20->player_pos,auStack_40);
        bVar1 = true;
      }
      if (bVar1) {
        UpdateFieldCamera__6CFieldFv(pCStack_20);
      }
      if (pCStack_20->pCamera != (CFieldCamera *)0x0) {
        fStack_24 = 0.0;
        lVar3 = isDsp__11CFieldModelFv(iVar2);
        if (lVar3 != 0) {
          fStack_24 = -*(float *)(iVar2 + 0x48);
        }
        Apply__12CFieldCameraFf(pCStack_20->pCamera,fStack_24);
        fStack_28 = (pCStack_20->cam_angle).flY;
        GetCameraAngle__12CFieldCameraFv((CFieldCamera *)auStack_50);
        __as__7FVectorFRC7FVector(&pCStack_20->cam_angle,auStack_50);
        if (((pCStack_20->bFlags_18e & 3) == 3) &&
           (lVar3 = isDsp__11CFieldModelFv(iVar2), lVar3 != 0)) {
          pCStack_20->bFlags_18e = pCStack_20->bFlags_18e & 0xfc;
          fStack_2c = (float)GetRotY__11CFieldModelFv(iVar2);
          fStack_2c = fStack_2c * 57.29579;
          pCStack_20->flCam_yaw_adjust = fStack_2c + 180.0;
          if (0.1 <= *(float *)&pCStack_20->field_0x6f4) {
            pCStack_20->flCam_yaw_adjust =
                 pCStack_20->flCam_yaw_adjust - *(float *)&pCStack_20->field_0x6f8;
            if (180.0 < pCStack_20->flCam_yaw_adjust) {
              pCStack_20->flCam_yaw_adjust = pCStack_20->flCam_yaw_adjust - 360.0;
            }
            if (pCStack_20->flCam_yaw_adjust < -180.0) {
              pCStack_20->flCam_yaw_adjust = pCStack_20->flCam_yaw_adjust + 360.0;
            }
            pCStack_20->bFlags_18c = pCStack_20->bFlags_18c & 0x1f | 0x20;
          }
          if ((0.1 <= *(float *)&pCStack_20->field_0x6f4) &&
             (0.1 <= *(float *)&pCStack_20->field_0x700)) {
            fStack_30 = *(float *)&pCStack_20->field_0x704 - *(float *)&pCStack_20->field_0x6f8;
            if (180.0 < fStack_30) {
              fStack_30 = fStack_30 - 360.0;
            }
            if (fStack_30 < -180.0) {
              fStack_30 = fStack_30 + 360.0;
            }
            if ((fStack_30 < -5.0) || (5.0 < fStack_30)) {
              pCStack_20->bFlags_18c = pCStack_20->bFlags_18c & 0x1f;
              pCStack_20->flCam_yaw_adjust = 0.0;
            }
          }
          if (*(float *)&pCStack_20->field_0x700 < 0.1) {
            pCStack_20->bFlags_18c = pCStack_20->bFlags_18c & 0x1f;
            pCStack_20->flCam_yaw_adjust = 0.0;
          }
        }
        GetCameraPos__12CFieldCameraFv((CFieldCamera *)auStack_60);
        __as__7FVectorFRC7FVector(&pCStack_20->cam_pos,auStack_60);
      }
    }
  }
  else {
    Apply__12CFieldCameraFf(pCStack_20->pCamera,fStack_10);
  }
  return;
}

/* JP: 0x004a89f0  CField::CheckMirror()   [CheckMirror__6CFieldFv]  size=0x12c */
void CheckMirror__6CFieldFv(CField *this)

{
  byte bVar1;
  void *pvVar2;
  void *a0;
  long lVar3;
  int iVar4;
  FVector FStack_30;
  int iStack_14;
  CField *pCStack_10;
  
  if ((this->pBg != (CFieldBG *)0x0) &&
     (pCStack_10 = this, GetMirrorInfo__8CFieldBGFRi(this->pBg,&iStack_14), a0 = camera__4CApp,
     iStack_14 != 0)) {
    bVar1 = pCStack_10->bModel_count;
    for (iVar4 = 0; iVar4 < (int)(uint)bVar1; iVar4 = iVar4 + 1) {
      pvVar2 = pCStack_10->aModels[iVar4];
      if (((pvVar2 != (void *)0x0) && (lVar3 = isDsp__11CFieldModelFv(pvVar2), lVar3 != 0)) &&
         (((ulong)*(byte *)((int)pvVar2 + 0x89) & 0x3f) >> 3 != 0)) {
        GetWorldPos__11CFieldModelFv(&FStack_30,pvVar2);
        lVar3 = CheckMirror__8CFieldBGFP9GsxCameraR7FVector(pCStack_10->pBg,a0,&FStack_30);
        UpdateMirrorOfs__11CFieldModelFiR7FVector(pvVar2,lVar3,&FStack_30);
      }
    }
  }
  return;
}

/* JP: 0x004a8b20  CField::ReverseVector(FVector&)   [ReverseVector__6CFieldFR7FVector]  size=0xb8 */
void ReverseVector__6CFieldFR7FVector(CField *this,FVector *a0)

{
  byte bVar1;
  
  if ((this->bFlags_18f & 7) != 0) {
    bVar1 = this->bFlags_18f;
    if ((bVar1 & 1) != 0) {
      a0->flX = a0->flX * -1.0;
    }
    if ((bVar1 & 2) != 0) {
      a0->flY = a0->flY * -1.0;
    }
    if ((bVar1 & 4) != 0) {
      a0->flZ = a0->flZ * -1.0;
    }
  }
  return;
}

/* JP: 0x004a8be0  CField::UpdateFieldCamera()   [UpdateFieldCamera__6CFieldFv]  size=0x19fc */
/* WARNING: Removing unreachable block (ram,0x004a8fb4) */
/* WARNING: Removing unreachable block (ram,0x004a92f0) */
/* WARNING: Removing unreachable block (ram,0x004a91d8) */
/* WARNING: Removing unreachable block (ram,0x004a8f14) */
/* WARNING: Removing unreachable block (ram,0x004a9794) */

void UpdateFieldCamera__6CFieldFv(CField *this)

{
  int iVar1;
  bool bVar2;
  void *pvVar3;
  FVector *pFVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  undefined8 uVar8;
  int iVar9;
  uint uVar10;
  int a0;
  int iVar11;
  float fVar12;
  undefined1 auStack_570 [16];
  undefined1 auStack_560 [16];
  undefined1 auStack_550 [16];
  undefined1 auStack_540 [48];
  undefined1 auStack_510 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [48];
  undefined1 auStack_4a0 [16];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [16];
  undefined1 auStack_430 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [16];
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [176];
  undefined1 auStack_2c0 [16];
  FVector FStack_2b0;
  FVector FStack_2a0;
  FVector FStack_290;
  undefined1 auStack_280 [12];
  void *pvStack_274;
  undefined1 auStack_270 [16];
  float fStack_260;
  void *apvStack_25c [3];
  float fStack_250;
  float fStack_24c;
  undefined1 auStack_240 [64];
  undefined1 auStack_200 [16];
  undefined4 auStack_1f0 [4];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [4];
  float fStack_1cc;
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  float fStack_190;
  float afStack_18c [3];
  float fStack_180;
  float fStack_17c;
  undefined1 auStack_170 [64];
  undefined1 auStack_130 [16];
  undefined4 auStack_120 [4];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [4];
  void *pvStack_fc;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [64];
  undefined1 auStack_a0 [4];
  void *pvStack_9c;
  void *pvStack_94;
  undefined1 auStack_90 [16];
  FVector FStack_80;
  FVector FStack_70;
  FVector FStack_60;
  void *pvStack_48;
  void *pvStack_44;
  void *pvStack_40;
  void *pvStack_3c;
  void *pvStack_38;
  void *pvStack_34;
  void *pvStack_30;
  void *pvStack_2c;
  void *pvStack_28;
  void *pvStack_24;
  void *pvStack_20;
  void *pvStack_1c;
  void *pvStack_18;
  void *pvStack_14;
  CField *pCStack_10;
  
  pCStack_10 = this;
  __ct__7FVectorFRC7FVector(&FStack_60,&this->player_pos);
  ReverseVector__6CFieldFR7FVector(pCStack_10,&FStack_60);
  if (pCStack_10->pCam_events != (CFieldEvent *)0x0) {
    pFVar4 = (FVector *)__ct__7FVectorFRC7FVector(auStack_370 + 0x50,&pCStack_10->player_pos);
    iVar5 = HitCheck__11CFieldEventF7FVectorii(pCStack_10->pCam_events,pFVar4,0,0);
    lVar6 = (long)iVar5;
    if (lVar6 < 0) {
      lVar6 = FieldCameraID__Fi(0xfffffffffffffffe);
    }
    if (-1 < lVar6) {
      lVar7 = Find__6CSTGDBFUl(m_pSTGDB__6CField,0x20204152454d4143);
      if (lVar7 != 0) {
        pvStack_14 = (void *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(m_pSTGDB__6CField,lVar7);
        iVar5 = GetEventNum__11CFieldEventFi(pCStack_10->pCam_events,(int)lVar6);
        m_pCAMDAT__6CField = (undefined4 *)((int)pvStack_14 + iVar5 * 0x10);
        if ((((m_pCAMOLD__6CField != (undefined4 *)0x0) && (m_pCAMOLD__6CField != m_pCAMDAT__6CField)) &&
            (*(char *)(m_pCAMDAT__6CField + 3) != '\0')) && (*(char *)(m_pCAMOLD__6CField + 3) != '\0')) {
          CompFrame__12CFieldCameraFf(pCStack_10->pCamera,50.0);
        }
        if (lVar6 != pCStack_10->nCamera_id) {
          pvStack_18 = (void *)(uint)(pCStack_10->nCamera_id < 0);
          pCStack_10->nCamera_id = (short)lVar6;
          if (pvStack_18 == (void *)0x0) {
            pCStack_10->flCam_yaw_adjust =
                 pCStack_10->flCam_yaw_adjust + (pCStack_10->cam_angle).flY;
            if (pCStack_10->bFlags_18c >> 5 == 4) {
              pCStack_10->bFlags_18c = pCStack_10->bFlags_18c & 0x1f | 0x40;
            }
            else {
              pCStack_10->bFlags_18c = pCStack_10->bFlags_18c & 0x1f | 0x20;
            }
          }
        }
      }
      if ((pCStack_10->bFlags_18e & 3) == 0) {
        FieldCameraID__Fi(lVar6);
      }
    }
  }
  if (m_pCAMDAT__6CField != (undefined4 *)0x0) {
    __ct__7FVectorFv(&FStack_70);
    __ct__7FVectorFv(&FStack_80);
    iVar5 = m_pCAMDAT__6CField[2];
    bVar2 = false;
    if (iVar5 == 0) {
      return;
    }
    switch(*m_pCAMDAT__6CField) {
    case 0:
      __as__7FVectorFRC7FVector(&FStack_70,iVar5);
      __as__7FVectorFRC7FVector(&FStack_80,iVar5 + 0x10);
      pvStack_1c = (void *)(float)*(ushort *)(iVar5 + 0x20);
      bVar2 = true;
      break;
    case 1:
      __ct__7FVectorFv(auStack_90);
      __ct__7FVectorFv(auStack_a0);
      __ct__6MatrixFv(auStack_e0);
      __as__7FVectorFRC7FVector(&FStack_80,&FStack_60);
      FStack_80.flY = FStack_80.flY - 12.0;
      pvStack_1c = (void *)(float)*(ushort *)(iVar5 + 0x20);
      __mi__7FVectorCFRC7FVector(auStack_370 + 0x40,iVar5,iVar5 + 0x10);
      __as__7FVectorFRC7FVector(auStack_90,auStack_370 + 0x40);
      pvStack_20 = (void *)GetCtrlModel__6CFieldFv(pCStack_10);
      GetMdlRot__11CFieldModelFv(auStack_370 + 0x30,pvStack_20);
      __as__7FVectorFRC7FVector(auStack_a0,auStack_370 + 0x30);
      UnitMatrix__6MatrixFv(auStack_e0);
      RotYMatrix__6MatrixFf(pvStack_9c,auStack_e0);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_370 + 0x20,auStack_e0,auStack_90);
      __as__7FVectorFRC7FVector(auStack_a0,auStack_370 + 0x20);
      __apl__7FVectorFRC7FVector(auStack_a0,&FStack_60);
      GetCameraPos__12CFieldCameraFv((CFieldCamera *)auStack_370);
      __mi__7FVectorCFRC7FVector(auStack_370 + 0x10,auStack_370,auStack_a0);
      __as__7FVectorFRC7FVector(auStack_90,auStack_370 + 0x10);
      __ml__7FVectorCFf(0x3f70a3d7,auStack_380,auStack_90);
      __apl__7FVectorFRC7FVector(auStack_a0,auStack_380);
      pvStack_94 = (void *)0x3f800000;
      __as__7FVectorFRC7FVector(&FStack_70,auStack_a0);
      bVar2 = true;
      break;
    case 2:
      __ct__7FVectorFv(auStack_f0);
      __as__7FVectorFRC7FVector(&FStack_80,&FStack_60);
      FStack_80.flY = FStack_80.flY - 12.0;
      __mi__7FVectorCFRC7FVector(auStack_390,iVar5,iVar5 + 0x10);
      __as__7FVectorFRC7FVector(&FStack_70,auStack_390);
      FStack_70.flY = FStack_70.flY - 12.0;
      __apl__7FVectorFRC7FVector(&FStack_70,&FStack_60);
      pvStack_1c = (void *)(float)*(ushort *)(iVar5 + 0x20);
      bVar2 = true;
      break;
    case 3:
      __ct__7FVectorFv(auStack_100);
      __ct__7FVectorFv(auStack_110);
      __ct__7FVectorFv(auStack_120);
      uVar8 = __ct__7FVectorFv(auStack_130);
      __ct__6MatrixFv(auStack_170,uVar8);
      __ct__7FVectorFv(&fStack_180);
      __ct__7FVectorFv(&fStack_190);
      __as__7FVectorFRC7FVector(auStack_100,&FStack_60);
      pvStack_fc = (void *)((float)pvStack_fc - 12.0);
      __as__7FVectorFRC7FVector(auStack_110,iVar5);
      __mi__7FVectorCFRC7FVector(auStack_3a0,iVar5,iVar5 + 0x10);
      __as__7FVectorFRC7FVector(auStack_120,auStack_3a0);
      pvStack_1c = (void *)(float)*(ushort *)(iVar5 + 0x20);
      fStack_17c = (float)atan2f(auStack_120[0],auStack_120[2]);
      UnitMatrix__6MatrixFv(auStack_170);
      RotYMatrix__6MatrixFf(-fStack_17c,auStack_170);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_3b0,auStack_170,auStack_120);
      __as__7FVectorFRC7FVector(auStack_130,auStack_3b0);
      fStack_180 = (float)atan2f(auStack_130._4_4_,auStack_130._8_4_);
      fStack_180 = -fStack_180;
      __mi__7FVectorCFRC7FVector(auStack_3c0,iVar5,auStack_100);
      __as__7FVectorFRC7FVector(auStack_120,auStack_3c0);
      pvStack_28 = (void *)Length__7FVectorCFv(auStack_120);
      afStack_18c[0] = (float)atan2f(auStack_120[0],auStack_120[2]);
      uVar8 = UnitMatrix__6MatrixFv(auStack_170);
      RotYMatrix__6MatrixFf(-afStack_18c[0],auStack_170,uVar8);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_3d0,auStack_170,auStack_120);
      uVar8 = __as__7FVectorFRC7FVector(auStack_130,auStack_3d0);
      fStack_190 = (float)atan2f(auStack_130._4_4_,auStack_130._8_4_,uVar8);
      fStack_190 = -fStack_190;
      pvStack_24 = (void *)(fStack_190 - fStack_180);
      clipRadian__FRf(&pvStack_24);
      if (0.0 < (float)pvStack_24) {
        if (*(float *)(iVar5 + 0x40) < (float)pvStack_24) {
          pvStack_24 = *(void **)(iVar5 + 0x40);
        }
      }
      else if ((float)pvStack_24 < *(float *)(iVar5 + 0x50)) {
        pvStack_24 = *(void **)(iVar5 + 0x50);
      }
      fStack_190 = fStack_180 + (float)pvStack_24;
      clipRadian__FRf(&fStack_190);
      pvStack_24 = (void *)(afStack_18c[0] - fStack_17c);
      clipRadian__FRf(&pvStack_24);
      if (0.0 < (float)pvStack_24) {
        if (*(float *)(iVar5 + 0x44) < (float)pvStack_24) {
          pvStack_24 = *(void **)(iVar5 + 0x44);
        }
      }
      else if ((float)pvStack_24 < *(float *)(iVar5 + 0x54)) {
        pvStack_24 = *(void **)(iVar5 + 0x54);
      }
      afStack_18c[0] = fStack_17c + (float)pvStack_24;
      clipRadian__FRf(afStack_18c);
      uVar8 = __ct__7FVectorFffff(0,0,-(float)pvStack_28,0x3f800000,auStack_3e0);
      __as__7FVectorFRC7FVector(auStack_120,uVar8);
      UnitMatrix__6MatrixFv(auStack_170);
      RotXMatrix__6MatrixFf(fStack_190,auStack_170);
      RotYMatrix__6MatrixFf(afStack_18c[0],auStack_170);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_3f0,auStack_170,auStack_120);
      __as__7FVectorFRC7FVector(auStack_130,auStack_3f0);
      __pl__7FVectorCFRC7FVector(auStack_400,iVar5,auStack_130);
      __as__7FVectorFRC7FVector(auStack_100,auStack_400);
      __as__7FVectorFRC7FVector(&FStack_80,auStack_100);
      __as__7FVectorFRC7FVector(&FStack_70,iVar5);
      bVar2 = true;
      break;
    case 4:
      __ct__7FVectorFv(auStack_1b0);
      __ct__7FVectorFv(auStack_1a0);
      __ct__7FVectorFv(auStack_1c0);
      __ct__7FVectorFv(auStack_1d0);
      __ct__7FVectorFv(auStack_1e0);
      __ct__7FVectorFv(auStack_1f0);
      __ct__7FVectorFv(auStack_200);
      uVar8 = __ct__6MatrixFv(auStack_240);
      __ct__7FVectorFv(&fStack_250,uVar8);
      __ct__7FVectorFv(&fStack_260);
      __as__7FVectorFRC7FVector(auStack_1d0,&FStack_60);
      fStack_1cc = fStack_1cc - 12.0;
      pvStack_1c = (void *)(float)*(ushort *)(iVar5 + 0x20);
      __as__7FVectorFRC7FVector(auStack_1e0,iVar5);
      __mi__7FVectorCFRC7FVector(auStack_410,iVar5,iVar5 + 0x10);
      uVar8 = __as__7FVectorFRC7FVector(auStack_1f0,auStack_410);
      fStack_24c = (float)atan2f(auStack_1f0[0],auStack_1f0[2],uVar8);
      UnitMatrix__6MatrixFv(auStack_240);
      RotYMatrix__6MatrixFf(-fStack_24c,auStack_240);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_420,auStack_240,auStack_1f0);
      __as__7FVectorFRC7FVector(auStack_200,auStack_420);
      fStack_250 = (float)atan2f(auStack_200._4_4_,auStack_200._8_4_);
      fStack_250 = -fStack_250;
      __mi__7FVectorCFRC7FVector(auStack_430,iVar5,auStack_1d0);
      __as__7FVectorFRC7FVector(auStack_1f0,auStack_430);
      pvStack_34 = (void *)Length__7FVectorCFv(auStack_1f0);
      apvStack_25c[0] = (void *)atan2f(auStack_1f0[0],auStack_1f0[2]);
      UnitMatrix__6MatrixFv(auStack_240);
      RotYMatrix__6MatrixFf(-(float)apvStack_25c[0],auStack_240);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_440,auStack_240,auStack_1f0);
      __as__7FVectorFRC7FVector(auStack_200,auStack_440);
      fStack_260 = (float)atan2f(auStack_200._4_4_,auStack_200._8_4_);
      fStack_260 = -fStack_260;
      pvStack_30 = (void *)(fStack_260 - fStack_250);
      clipRadian__FRf(&pvStack_30);
      if (0.0 < (float)pvStack_30) {
        if (*(float *)(iVar5 + 0x40) < (float)pvStack_30) {
          pvStack_30 = *(void **)(iVar5 + 0x40);
        }
      }
      else if ((float)pvStack_30 < *(float *)(iVar5 + 0x50)) {
        pvStack_30 = *(void **)(iVar5 + 0x50);
      }
      fStack_260 = fStack_250 + (float)pvStack_30;
      clipRadian__FRf(&fStack_260);
      pvStack_30 = (void *)((float)apvStack_25c[0] - fStack_24c);
      uVar8 = clipRadian__FRf(&pvStack_30);
      if (0.0 < (float)pvStack_30) {
        if (*(float *)(iVar5 + 0x44) < (float)pvStack_30) {
          pvStack_30 = *(void **)(iVar5 + 0x44);
        }
      }
      else if ((float)pvStack_30 < *(float *)(iVar5 + 0x54)) {
        pvStack_30 = *(void **)(iVar5 + 0x54);
      }
      apvStack_25c[0] = (void *)(fStack_24c + (float)pvStack_30);
      clipRadian__FRf(apvStack_25c,uVar8);
      uVar8 = __ct__7FVectorFffff(0,0,-(float)pvStack_34,0x3f800000,auStack_450);
      __as__7FVectorFRC7FVector(auStack_1f0,uVar8);
      uVar8 = UnitMatrix__6MatrixFv(auStack_240);
      RotXMatrix__6MatrixFf(fStack_260,auStack_240,uVar8);
      RotYMatrix__6MatrixFf(apvStack_25c[0],auStack_240);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_460,auStack_240,auStack_1f0);
      __as__7FVectorFRC7FVector(auStack_200,auStack_460);
      __pl__7FVectorCFRC7FVector(auStack_470,iVar5,auStack_200);
      uVar8 = __as__7FVectorFRC7FVector(auStack_1d0,auStack_470);
      __as__7FVectorFRC7FVector(auStack_1b0,auStack_1d0,uVar8);
      __as__7FVectorFRC7FVector(auStack_1a0,auStack_1e0);
      __mi__7FVectorCFRC7FVector(auStack_480,auStack_1a0,auStack_1b0);
      __as__7FVectorFRC7FVector(auStack_1c0,auStack_480);
      pvStack_2c = (void *)Length__7FVectorCFv(auStack_1c0);
      if (100.0 < (float)pvStack_2c) {
        pvStack_2c = (void *)(100.0 / (float)pvStack_2c);
        GetPathPoint__6CFieldFfP7FVector
                  ((CField *)auStack_270,(float)pvStack_2c,(FVector *)pCStack_10);
        __as__7FVectorFRC7FVector(auStack_1a0,auStack_270);
      }
      __as__7FVectorFRC7FVector(&FStack_70,auStack_1a0);
      __as__7FVectorFRC7FVector(auStack_1d0,&FStack_60);
      fStack_1cc = fStack_1cc - 12.0;
      __as__7FVectorFRC7FVector(&FStack_80,auStack_1d0);
      bVar2 = true;
      break;
    case 5:
      uVar10 = 0xffffffff;
      if ((*(uint *)(iVar5 + 0x3c) & 0xff000000) == 0) {
        uVar10 = *(uint *)(iVar5 + 0x3c) & 2;
      }
      if ((int)uVar10 < 1) {
        __ct__7FVectorFv(&FStack_2b0);
        __ct__7FVectorFv(auStack_370 + 0x80);
        __ct__7FVectorFv(auStack_370 + 0x90);
        __ct__7FVectorFv(auStack_370 + 0xa0);
        __ct__7FVectorFv(auStack_2c0);
        iVar1 = m_pCAMDAT__6CField[1];
        pvStack_1c = (void *)0x43a00000;
        pvStack_40 = (void *)0x46fa0000;
        a0 = -1;
        for (iVar9 = 0; iVar9 < iVar1 + -1; iVar9 = iVar9 + 1) {
          __mi__7FVectorCFRC7FVector(auStack_4f0,iVar5 + iVar9 * 0x40 + 0x30,&FStack_60);
          uVar8 = __as__7FVectorFRC7FVector(&FStack_2b0,auStack_4f0);
          pvStack_44 = (void *)Length__7FVectorCFv(&FStack_2b0,uVar8);
          if (iVar9 == iVar1 + -1) {
            pvStack_44 = (void *)((float)pvStack_44 * 2.0);
          }
          else {
            __as__7FVectorFRC7FVector(auStack_370 + 0x80,iVar5 + iVar9 * 0x40 + 0x30);
            __as__7FVectorFRC7FVector(auStack_370 + 0x90,iVar5 + (iVar9 + 1) * 0x40 + 0x30);
            GetPathPoint__6CFieldFfP7FVector((CField *)auStack_500,0.5,(FVector *)pCStack_10);
            __as__7FVectorFRC7FVector(&FStack_2b0,auStack_500);
            __ami__7FVectorFRC7FVector(&FStack_2b0,&FStack_60);
            fVar12 = (float)Length__7FVectorCFv(&FStack_2b0);
            pvStack_44 = (void *)((float)pvStack_44 + fVar12);
          }
          pvStack_44 = (void *)((float)pvStack_44 * 0.5);
          iVar11 = iVar9;
          pvVar3 = pvStack_44;
          if ((float)pvStack_40 <= (float)pvStack_44) {
            iVar11 = a0;
            pvVar3 = pvStack_40;
          }
          pvStack_40 = pvVar3;
          a0 = iVar11;
        }
        for (iVar9 = 0; iVar9 < iVar1 + -2; iVar9 = iVar9 + 1) {
          __as__7FVectorFRC7FVector(auStack_370 + 0x80,iVar5 + iVar9 * 0x40 + 0x30);
          __as__7FVectorFRC7FVector(auStack_370 + 0x90,iVar5 + (iVar9 + 1) * 0x40 + 0x30);
          pFVar4 = (FVector *)__ct__7FVectorFRC7FVector(auStack_510,&FStack_60);
          pvStack_48 = (void *)ChkPathPoint__6CFieldF7FVectorP7FVectorPf
                                         (pCStack_10,pFVar4,(FVector *)(auStack_370 + 0x80),
                                          (float *)(auStack_370 + 0x60));
          if ((pvStack_48 == (void *)0x0) && ((float)auStack_370._108_4_ < (float)pvStack_40)) {
            pvStack_40 = (void *)auStack_370._108_4_;
            a0 = iVar9;
          }
        }
        if (a0 == 0) {
          a0 = 1;
        }
        if ((1 < a0) && (iVar1 + -1 <= a0)) {
          a0 = a0 + -1;
        }
        iVar5 = GetCamPath__6CFieldFiP7FVectorf(pCStack_10,a0,(FVector *)(auStack_370 + 0x80),0.0);
        if ((a0 < iVar1 + -2) && (iVar5 == 2)) {
          a0 = a0 + 1;
          iVar5 = GetCamPath__6CFieldFiP7FVectorf(pCStack_10,a0,(FVector *)(auStack_370 + 0xa0),0.0)
          ;
          if ((iVar5 == 0) || (iVar5 == 1)) {
            __as__7FVectorFRC7FVector(auStack_370 + 0x80,auStack_370 + 0xa0);
            __as__7FVectorFRC7FVector(auStack_370 + 0x90,auStack_2c0);
          }
        }
        if ((a0 < iVar1 + -2) &&
           (iVar5 = GetCamPath__6CFieldFiP7FVectorf
                              (pCStack_10,a0 + 1,(FVector *)(auStack_370 + 0xa0),0.0), iVar5 == 1))
        {
          __as__7FVectorFRC7FVector(auStack_370 + 0x80,auStack_370 + 0xa0);
          __as__7FVectorFRC7FVector(auStack_370 + 0x90,auStack_2c0);
        }
        if (m_pCAMOLD__6CField == m_pCAMDAT__6CField) {
          GetTargetPos__12CFieldCameraFv((CFieldCamera *)(auStack_540 + 0x20));
          uVar8 = __as__7FVectorFRC7FVector(&FStack_2b0,auStack_540 + 0x20);
          ReverseVector__6CFieldFR7FVector(pCStack_10,&FStack_2b0);
          __ami__7FVectorFRC7FVector(&FStack_2b0,auStack_370 + 0x80,uVar8);
          __ml__7FVectorCFf(0x3f4f5c29,auStack_540 + 0x10,&FStack_2b0);
          __apl__7FVectorFRC7FVector(auStack_370 + 0x80,auStack_540 + 0x10);
          auStack_370._140_4_ = (void *)0x3f800000;
          GetCameraPos__12CFieldCameraFv((CFieldCamera *)auStack_540);
          __as__7FVectorFRC7FVector(&FStack_2b0,auStack_540);
          ReverseVector__6CFieldFR7FVector(pCStack_10,&FStack_2b0);
          __ami__7FVectorFRC7FVector(&FStack_2b0,auStack_370 + 0x90);
          __ml__7FVectorCFf(0x3f4f5c29,auStack_550,&FStack_2b0);
          __apl__7FVectorFRC7FVector(auStack_370 + 0x90,auStack_550);
          auStack_370._156_4_ = (void *)0x3f800000;
        }
        __as__7FVectorFRC7FVector(&FStack_80,auStack_370 + 0x80);
        __as__7FVectorFRC7FVector(&FStack_70,auStack_370 + 0x90);
      }
      else {
        __ct__7FVectorFv(&FStack_290);
        __ct__7FVectorFv(auStack_280);
        uVar8 = __ct__7FVectorFRC7FVector(auStack_490,&FStack_60);
        pvStack_3c = (void *)GetNearestPath__FPQ23SDB10tagFCAMERA7FVectorRi
                                       (m_pCAMDAT__6CField,uVar8,&pvStack_38);
        if (1000.0 <= (float)pvStack_3c) {
          fVar12 = (float)pvStack_3c - 1000.0;
          pFVar4 = (FVector *)__ct__7FVectorFRC7FVector(auStack_4a0,&FStack_60);
          GetCamPath2__6CFieldFP7FVectori7FVector(pCStack_10,&FStack_290,(int)fVar12,pFVar4);
        }
        else {
          GetCamPathA__6CFieldFiP7FVectorf(pCStack_10,(int)pvStack_38,&FStack_290,(float)pvStack_3c)
          ;
        }
        pvStack_1c = pvStack_274;
        if (m_pCAMOLD__6CField == m_pCAMDAT__6CField) {
          __ct__7FVectorFv(&FStack_2a0);
          GetTargetPos__12CFieldCameraFv((CFieldCamera *)(auStack_4d0 + 0x20));
          __as__7FVectorFRC7FVector(&FStack_2a0,auStack_4d0 + 0x20);
          ReverseVector__6CFieldFR7FVector(pCStack_10,&FStack_2a0);
          __ami__7FVectorFRC7FVector(&FStack_2a0,&FStack_290);
          __ml__7FVectorCFf(0x3f4f5c29,auStack_4d0 + 0x10,&FStack_2a0);
          __apl__7FVectorFRC7FVector(&FStack_290,auStack_4d0 + 0x10);
          FStack_290.flW = 1.0;
          GetCameraPos__12CFieldCameraFv((CFieldCamera *)auStack_4d0);
          __as__7FVectorFRC7FVector(&FStack_2a0,auStack_4d0);
          ReverseVector__6CFieldFR7FVector(pCStack_10,&FStack_2a0);
          __ami__7FVectorFRC7FVector(&FStack_2a0,auStack_280);
          __ml__7FVectorCFf(0x3f4f5c29,auStack_4e0,&FStack_2a0);
          __apl__7FVectorFRC7FVector(auStack_280,auStack_4e0);
          pvStack_274 = (void *)0x3f800000;
        }
        __as__7FVectorFRC7FVector(&FStack_80,&FStack_290);
        __as__7FVectorFRC7FVector(&FStack_70,auStack_280);
      }
      bVar2 = true;
    }
    if (bVar2) {
      SetViewAngle__12CFieldCameraFf(pCStack_10->pCamera,(float)pvStack_1c / 512.0);
      ReverseVector__6CFieldFR7FVector(pCStack_10,&FStack_80);
      ReverseVector__6CFieldFR7FVector(pCStack_10,&FStack_70);
      pFVar4 = (FVector *)__ct__7FVectorFRC7FVector(auStack_560,&FStack_80);
      SetTargetPos__12CFieldCameraF7FVector(pCStack_10->pCamera,pFVar4);
      pFVar4 = (FVector *)__ct__7FVectorFRC7FVector(auStack_570,&FStack_70);
      SetCameraPos__12CFieldCameraF7FVector(pCStack_10->pCamera,pFVar4);
    }
  }
  if (m_pCAMDAT__6CField != (undefined4 *)0x0) {
    m_pCAMOLD__6CField = m_pCAMDAT__6CField;
  }
  return;
}

/* JP: 0x004aa6e0  CField::WaitCamera()   [WaitCamera__6CFieldFv]  size=0x30 */
bool WaitCamera__6CFieldFv(CField *this)

{
  bool bVar1;
  
  bVar1 = bComp__12CFieldCameraFv(this->pCamera);
  return bVar1;
}

/* JP: 0x004aa750  CField::UpdateScrCamera(float)   [UpdateScrCamera__6CFieldFf]  size=0x10ac */
/* WARNING: Removing unreachable block (ram,0x004ab220) */
/* WARNING: Removing unreachable block (ram,0x004ab240) */
/* WARNING: Removing unreachable block (ram,0x004ab238) */
/* WARNING: Removing unreachable block (ram,0x004ab200) */
/* WARNING: Removing unreachable block (ram,0x004ab20c) */
/* WARNING: Removing unreachable block (ram,0x004ab218) */
/* WARNING: Removing unreachable block (ram,0x004ab260) */
/* WARNING: Removing unreachable block (ram,0x004ab280) */
/* WARNING: Removing unreachable block (ram,0x004ab278) */

void UpdateScrCamera__6CFieldFf(CField *this,float a0)

{
  byte bVar1;
  float fVar2;
  bool bVar3;
  undefined4 uVar4;
  FVector *pFVar5;
  undefined8 uVar6;
  long lVar7;
  byte bVar8;
  int iVar9;
  undefined4 uVar10;
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [32];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [64];
  float fStack_150;
  float fStack_14c;
  float fStack_144;
  float fStack_130;
  float fStack_12c;
  float fStack_124;
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [4];
  float fStack_dc;
  undefined1 auStack_d0 [4];
  float fStack_cc;
  undefined1 auStack_c0 [4];
  float fStack_bc;
  undefined1 auStack_b0 [4];
  float fStack_ac;
  undefined1 auStack_a0 [4];
  float fStack_9c;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [12];
  float fStack_64;
  undefined4 uStack_60;
  float fStack_5c;
  undefined4 uStack_54;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  uint uStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  CField *pCStack_20;
  
  pCStack_20 = this;
  __ct__7FVectorFv(&uStack_60);
  __ct__7FVectorFv(auStack_70);
  GetShortPos4__FP7FVectorPs(auStack_70,&pCStack_20->field_0x194);
  fVar2 = fStack_64;
  fStack_24 = fStack_64;
  fStack_64 = 1.0;
  iVar9 = 0;
  if (fVar2 < 4.0) {
    iVar9 = (int)fVar2;
    fStack_24 = 0.625;
  }
  else {
    uVar10 = GetRad(fVar2);
    fStack_24 = (float)tanf(uVar10);
    fStack_24 = fStack_24 * 1.3333334;
  }
  switch(pCStack_20->bScr_camera_active) {
  case 1:
    uVar10 = GetModel__6CFieldFi(pCStack_20,(int)*(short *)&pCStack_20->field_0x19c);
    bVar1 = pCStack_20->field_0x1a8;
    bVar8 = bVar1 & 0xf;
    if (pCStack_20->field_0x1a9 == '\0') {
      SetCmpMode__12CFieldCameraFi(pCStack_20->pCamera,1);
      CompFrame__12CFieldCameraFf(pCStack_20->pCamera,*(float *)&pCStack_20->field_0x1a4);
      pCStack_20->field_0x1a9 = 1;
      lVar7 = 0;
      GetWorldPos__11CFieldModelFv(auStack_1a0,uVar10);
      __as__7FVectorFRC7FVector(&uStack_60,auStack_1a0);
      if (bVar8 == 2) {
        lVar7 = FindFrame__FP11CFieldModelPCc(uVar10,FRAME_WAIST);
      }
      else if (bVar8 == 1) {
        __ct__7FVectorFv(auStack_80);
        lVar7 = FindFrame__FP11CFieldModelPCc(uVar10,FRAME_NECK);
        if (lVar7 == 0) {
          lVar7 = FindFrame__FP11CFieldModelPCc(uVar10,FRAME_HEAD);
        }
        if (lVar7 != 0) {
          getWorldPos__5FrameFi(auStack_1b0,lVar7,m_Env__8VIF1Prim & 1);
          __as__7FVectorFRC7FVector(auStack_80,auStack_1b0);
          lVar7 = FindFrame__FP11CFieldModelPCc(uVar10,FRAME_WAIST);
          if (lVar7 != 0) {
            getWorldPos__5FrameFi(auStack_1e0,lVar7,m_Env__8VIF1Prim & 1);
            __pl__7FVectorCFRC7FVector(auStack_1d0,auStack_80,auStack_1e0);
            __ml__7FVectorCFf(0x3f000000,auStack_1c0,auStack_1d0);
            __as__7FVectorFRC7FVector(auStack_80,auStack_1c0);
            GetWorldPos__11CFieldModelFv(auStack_200,uVar10);
            __mi__7FVectorCFRC7FVector(auStack_1f0,auStack_80,auStack_200);
            __as__7FVectorFRC7FVector(&uStack_60,auStack_1f0);
          }
        }
        lVar7 = 0;
      }
      else if (((bVar1 & 0xf) == 0) &&
              (lVar7 = FindFrame__FP11CFieldModelPCc(uVar10,FRAME_NECK), lVar7 == 0)) {
        lVar7 = FindFrame__FP11CFieldModelPCc(uVar10,FRAME_HEAD);
      }
      if (lVar7 != 0) {
        getWorldPos__5FrameFi(auStack_220,lVar7,m_Env__8VIF1Prim & 1);
        __mi__7FVectorCFRC7FVector(auStack_210,auStack_220,&uStack_60);
        __as__7FVectorFRC7FVector(&uStack_60,auStack_210);
      }
      *(short *)&pCStack_20->field_0x1a2 = (short)(int)(fStack_5c * 16.0);
    }
    GetWorldPos__11CFieldModelFv(auStack_230,uVar10);
    __as__7FVectorFRC7FVector(&uStack_60,auStack_230);
    fStack_5c = fStack_5c + (float)(int)*(short *)&pCStack_20->field_0x1a2 / 16.0;
    if (iVar9 != 0) {
      fStack_24 = 0.625;
      uVar6 = GetModel__11CFieldModelFv(uVar10);
      CalcModelBBox__FP5ModelPf(uVar6,auStack_a0);
      if (iVar9 == 3) {
        lVar7 = FindFrame__FP11CFieldModelPCc(uVar10,FRAME_WAIST);
        if (lVar7 == 0) {
          iVar9 = 0;
        }
        else {
          getWorldPos__5FrameFi(auStack_e0,lVar7,m_Env__8VIF1Prim & 1);
          fStack_28 = (fStack_9c - fStack_dc) * 1.3;
        }
      }
      else if (iVar9 == 2) {
        lVar7 = FindFrame__FP11CFieldModelPCc(uVar10,FRAME_WAIST);
        if (lVar7 == 0) {
          iVar9 = 0;
        }
        else {
          __ct__7FVectorFv(auStack_c0);
          __ct__7FVectorFv(auStack_d0);
          getWorldPos__5FrameFi(auStack_240,lVar7,m_Env__8VIF1Prim & 1);
          __as__7FVectorFRC7FVector(auStack_c0,auStack_240);
          GetWorldPos__11CFieldModelFv(auStack_250,uVar10);
          __as__7FVectorFRC7FVector(auStack_d0,auStack_250);
          __mi__7FVectorCFRC7FVector(auStack_260,auStack_c0,auStack_d0);
          __as__7FVectorFRC7FVector(auStack_d0,auStack_260);
          fStack_bc = fStack_bc + fStack_cc * 0.5;
          fStack_28 = (fStack_9c - fStack_bc) * 3.5;
        }
      }
      else if (iVar9 == 1) {
        GetWorldPos__11CFieldModelFv(auStack_b0,uVar10);
        fStack_28 = (fStack_9c - fStack_ac) * 1.4;
      }
      if (iVar9 != 0) {
        __ct__7FVectorFv(auStack_f0);
        __mi__7FVectorCFRC7FVector(auStack_270,&uStack_60,auStack_70);
        __as__7FVectorFRC7FVector(auStack_f0,auStack_270);
        fStack_2c = (float)Length__7FVectorCFv(auStack_f0);
        if (fStack_28 < 0.0) {
          fStack_28 = -fStack_28;
        }
        fStack_24 = fStack_28 / fStack_2c;
      }
    }
    pFVar5 = (FVector *)__ct__7FVectorFRC7FVector(auStack_280,auStack_70);
    SetCameraPos__12CFieldCameraF7FVector(pCStack_20->pCamera,pFVar5);
    pFVar5 = (FVector *)__ct__7FVectorFRC7FVector(auStack_290,&uStack_60);
    SetTargetPos__12CFieldCameraF7FVector(pCStack_20->pCamera,pFVar5);
    SetViewAngle__12CFieldCameraFf(pCStack_20->pCamera,fStack_24);
    SetViewDelay__12CFieldCameraFf(pCStack_20->pCamera,0.5);
    break;
  case 2:
    uStack_30 = (byte)pCStack_20->field_0x1a8 & 0xf;
    if (pCStack_20->field_0x1a9 == '\0') {
      SetCmpMode__12CFieldCameraFi(pCStack_20->pCamera,1);
      CompFrame__12CFieldCameraFf(pCStack_20->pCamera,1.0);
      pCStack_20->bScr_camera_active = 0xf;
      __ct__7FVectorFv(auStack_100);
      __ct__7FVectorFv(auStack_110);
      uVar10 = GetModel__6CFieldFi(pCStack_20,(int)*(short *)&pCStack_20->field_0x19c);
      GetWorldPos__11CFieldModelFv(auStack_2a0,uVar10);
      __as__7FVectorFRC7FVector(auStack_100,auStack_2a0);
      uVar4 = GetModel__6CFieldFi(pCStack_20,(int)*(short *)&pCStack_20->field_0x19e);
      GetWorldPos__11CFieldModelFv(auStack_2b0,uVar4);
      __as__7FVectorFRC7FVector(auStack_110,auStack_2b0);
      uVar6 = GetModel__11CFieldModelFv(uVar10);
      CalcModelBBox__FP5ModelPf(uVar6,&fStack_130);
      uVar6 = GetModel__11CFieldModelFv(uVar4);
      CalcModelBBox__FP5ModelPf(uVar6,&fStack_150);
      if (fStack_150 < fStack_130) {
        fStack_130 = fStack_150;
      }
      if (fStack_124 < fStack_144) {
        fStack_124 = fStack_144;
      }
      fStack_34 = fStack_12c;
      if (fStack_14c < fStack_12c) {
        fStack_34 = fStack_14c;
      }
      __ami__7FVectorFRC7FVector(auStack_100,auStack_70);
      __ami__7FVectorFRC7FVector(auStack_110,auStack_70);
      fStack_40 = (float)Length__7FVectorCFv(auStack_100);
      fStack_44 = (float)Length__7FVectorCFv(auStack_110);
      Normalize__7FVectorFv(auStack_100);
      Normalize__7FVectorFv(auStack_110);
      __pl__7FVectorCFRC7FVector(auStack_2d0,auStack_100,auStack_110);
      __ml__7FVectorCFf(0x3f000000,auStack_2c0,auStack_2d0);
      __as__7FVectorFRC7FVector(&uStack_60,auStack_2c0);
      if (fStack_44 < fStack_40) {
        fStack_40 = fStack_44;
        fStack_48 = (float)InnerProduct__7FVectorCFRC7FVector(&uStack_60,auStack_110);
      }
      else {
        fStack_48 = (float)InnerProduct__7FVectorCFRC7FVector(&uStack_60,auStack_100);
      }
      fStack_3c = fStack_40 * fStack_48;
      __ml__7FVectorCFf(fStack_3c,auStack_2f0,&uStack_60);
      __pl__7FVectorCFRC7FVector(auStack_2e0,auStack_70,auStack_2f0);
      __as__7FVectorFRC7FVector(&uStack_60,auStack_2e0);
      fStack_5c = fStack_34 * 0.7;
      if (iVar9 != 0) {
        uVar10 = acosf(fStack_48);
        fStack_38 = (float)tanf(uVar10);
        fStack_38 = fStack_38 * 2.0;
        fStack_24 = fStack_38 * 0.75;
        if (fStack_24 < 0.28) {
          fStack_24 = 0.28;
        }
        if (0.7 < fStack_24) {
          fStack_24 = 0.7;
        }
      }
      pFVar5 = (FVector *)__ct__7FVectorFRC7FVector(auStack_300,auStack_70);
      SetCameraPos__12CFieldCameraF7FVector(pCStack_20->pCamera,pFVar5);
      pFVar5 = (FVector *)__ct__7FVectorFRC7FVector(auStack_310,&uStack_60);
      SetTargetPos__12CFieldCameraF7FVector(pCStack_20->pCamera,pFVar5);
      SetViewAngle__12CFieldCameraFf(pCStack_20->pCamera,fStack_24);
    }
    break;
  case 3:
  case 4:
  case 5:
    GetCameraPos__12CFieldCameraFv((CFieldCamera *)(auStack_340 + 0x10));
    GetTargetPos__12CFieldCameraFv((CFieldCamera *)auStack_340);
    __mi__7FVectorCFRC7FVector(auStack_320,auStack_340 + 0x10,auStack_340);
    uVar6 = __as__7FVectorFRC7FVector(&uStack_60,auStack_320);
    fStack_4c = (float)Length__7FVectorCFv(&uStack_60,uVar6);
    if (fStack_4c == 0.0) {
      fStack_4c = 30.0;
    }
    GetShortPos4__FP7FVectorPs(&uStack_60,&pCStack_20->field_0x19c);
    SetCmpMode__12CFieldCameraFi(pCStack_20->pCamera,1);
    CompFrame__12CFieldCameraFf(pCStack_20->pCamera,*(float *)&pCStack_20->field_0x1a4);
    if (pCStack_20->bScr_camera_active == 4) {
      Normalize__7FVectorFv(&uStack_60);
      __ml__7FVectorCFf(0x41a00000,auStack_360,&uStack_60);
      __pl__7FVectorCFRC7FVector(auStack_350,auStack_70,auStack_360);
      __as__7FVectorFRC7FVector(&uStack_60,auStack_350);
    }
    else if (pCStack_20->bScr_camera_active == 5) {
      __ct__6MatrixFv(auStack_190);
      uVar6 = UnitMatrix__6MatrixFv(auStack_190);
      uVar10 = GetRad(uStack_60,uVar6);
      RotXMatrix__6MatrixFf(uVar10,auStack_190);
      uVar10 = GetRad(fStack_5c);
      RotYMatrix__6MatrixFf(uVar10,auStack_190);
      uVar6 = __ct__7FVectorFffff(0,0,fStack_4c,0x3f800000,auStack_380);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_370,auStack_190,uVar6);
      __as__7FVectorFRC7FVector(&uStack_60,auStack_370);
      __apl__7FVectorFRC7FVector(&uStack_60,auStack_70);
    }
    uStack_54 = 0x3f800000;
    pFVar5 = (FVector *)__ct__7FVectorFRC7FVector(auStack_390,auStack_70);
    SetCameraPos__12CFieldCameraF7FVector(pCStack_20->pCamera,pFVar5);
    pFVar5 = (FVector *)__ct__7FVectorFRC7FVector(auStack_3a0,&uStack_60);
    SetTargetPos__12CFieldCameraF7FVector(pCStack_20->pCamera,pFVar5);
    SetViewAngle__12CFieldCameraFf(pCStack_20->pCamera,fStack_24);
    SetViewDelay__12CFieldCameraFf(pCStack_20->pCamera,0.0);
    pCStack_20->bScr_camera_active = 0xf;
    break;
  case 7:
    if (pCStack_20->field_0x1a9 != '\x01') {
      if (pCStack_20->field_0x1a9 != '\0') {
        return;
      }
      if (*(float *)&pCStack_20->field_0x1a4 == 0.0) {
        SetCmpMode__12CFieldCameraFi(pCStack_20->pCamera,0);
        SetViewDelay__12CFieldCameraFf(pCStack_20->pCamera,0.0);
        pCStack_20->bScr_camera_active = 0;
        return;
      }
      SetCmpMode__12CFieldCameraFi(pCStack_20->pCamera,1);
      SetViewDelay__12CFieldCameraFf(pCStack_20->pCamera,0.0);
      CompFrame__12CFieldCameraFf(pCStack_20->pCamera,*(float *)&pCStack_20->field_0x1a4);
      pCStack_20->field_0x1a9 = 1;
    }
    UpdateFieldCamera__6CFieldFv(pCStack_20);
    bVar3 = bComp__12CFieldCameraFv(pCStack_20->pCamera);
    if (!bVar3) {
      SetCmpMode__12CFieldCameraFi(pCStack_20->pCamera,0);
      pCStack_20->bScr_camera_active = 0;
    }
  }
  return;
}

/* JP: 0x004ab860  CField::InitSDB(CSTGDB*)   [InitSDB__6CFieldFP6CSTGDB]  size=0x894 */
undefined4 InitSDB__6CFieldFP6CSTGDB(CField *this,CSTGDB *a0)

{
  short sVar1;
  CFloorMan *pCVar2;
  CFieldEvent *pCVar3;
  void *pvVar4;
  int iVar5;
  long lVar6;
  undefined8 uVar7;
  long lVar8;
  int iVar9;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [12];
  undefined4 uStack_64;
  CFieldBG *pCStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  void *pvStack_48;
  int iStack_44;
  undefined4 uStack_40;
  void *pvStack_3c;
  int iStack_38;
  uint uStack_34;
  undefined4 uStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  CField *pCStack_20;
  CSTGDB *pCStack_10;
  
  this->nUnk5fc = -1;
  this->nUnk600 = 0;
  this->bFlags_18c = this->bFlags_18c & 0xe3 | 0x14;
  if ((this->bFlags_18e & 3) == 1) {
    this->bFlags_18e = this->bFlags_18e & 0xfc | 2;
  }
  pCGpffff85e8 = a0;
  pCStack_20 = this;
  pCStack_10 = a0;
  sVar1 = FieldCameraID__Fi(0xfffffffffffffffe);
  pCStack_20->nCamera_id = sVar1;
  if (pCStack_20->pTeam_change != (void *)0x0) {
    Clr__13FldTeamChangeFv(pCStack_20->pTeam_change);
  }
  iStack_28 = 0;
  iStack_2c = GetCtrlModel__6CFieldFv(pCStack_20);
  if ((iStack_2c != 0) && (lVar6 = isDsp__11CFieldModelFv(iStack_2c), lVar6 != 0)) {
    iStack_28 = 1;
  }
  uStack_30 = 0;
  uStack_34 = (uint)pCStack_20->bModel_count;
  for (iStack_38 = 0; iStack_38 < (int)uStack_34; iStack_38 = iStack_38 + 1) {
    pvStack_3c = pCStack_20->aModels[iStack_38];
    if (pvStack_3c != (void *)0x0) {
      ClearShadow__11CFieldModelFv(pvStack_3c);
      ClearModel__11CFieldModelFv(pvStack_3c);
    }
  }
  if (pCStack_20->pBg == (CFieldBG *)0x0) {
    pCStack_58 = (CFieldBG *)__nw__FUi(8);
    if (pCStack_58 != (CFieldBG *)0x0) {
      pCStack_58 = (CFieldBG *)__ct__8CFieldBGFv(pCStack_58);
    }
    pCStack_20->pBg = pCStack_58;
  }
  Create__8CFieldBGFP6CSTGDBi(pCStack_20->pBg,pCGpffff85e8,0);
  Dsp__8CFieldBGFv(pCStack_20->pBg);
  lVar6 = Find__6CSTGDBFUl(pCGpffff85e8,0x20205445534e4f4d);
  if (lVar6 == 0) {
    SetEncountRate__6CFieldFi(pCStack_20,0);
  }
  else {
    iVar5 = (int)lVar6;
    SetEncountRate__6CFieldFi(pCStack_20,(uint)*(byte *)(iVar5 + 0x14));
    SetFieldData__6CFieldFiii(pCStack_20,6,(uint)*(ushort *)(iVar5 + 0x16),0);
    SetFieldData__6CFieldFiii(pCStack_20,7,(uint)*(ushort *)(iVar5 + 0x18),0);
  }
  AutoLoadSE__6CFieldFv(pCStack_20);
  lVar6 = Find__6CSTGDBFUl(pCGpffff85e8,0x2020204543494c53);
  if (lVar6 != 0) {
    lVar6 = __nw__FUi(0x20);
    pCVar2 = (CFloorMan *)0x0;
    if (lVar6 != 0) {
      pCVar2 = (CFloorMan *)__ct__9CFloorManFv((CFloorMan *)lVar6);
    }
    pCStack_20->pFloor = pCVar2;
    SetData__9CFloorManFP6CSTGDB(pCStack_20->pFloor,pCGpffff85e8);
  }
  uVar7 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_80);
  __as__7FVectorFRC7FVector(&pCStack_20->player_pos,uVar7);
  lVar6 = Find__6CSTGDBFUl(pCGpffff85e8,0x534f505952544e45);
  if (lVar6 != 0) {
    uStack_40 = GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(pCGpffff85e8,lVar6);
    uVar7 = __ct__7FVectorFPC7FVector(auStack_90,uStack_40);
    __as__7FVectorFRC7FVector(&pCStack_20->player_pos,uVar7);
    (pCStack_20->player_pos).flW = 1.0;
  }
  m_pCAMOLD__6CField = 0;
  m_pCAMDAT__6CField = 0;
  lVar6 = Find__6CSTGDBFUl(pCGpffff85e8,0x544e4556454d4143);
  if (lVar6 != 0) {
    lVar8 = __nw__FUi(0xc);
    pCVar3 = (CFieldEvent *)0x0;
    if (lVar8 != 0) {
      pCVar3 = (CFieldEvent *)__ct__11CFieldEventFv((CFieldEvent *)lVar8);
    }
    pCStack_20->pCam_events = pCVar3;
    pvVar4 = (void *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(pCGpffff85e8,lVar6);
    iVar5 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(pCGpffff85e8,lVar6);
    Init__11CFieldEventFPQ23SDB11tagEVENTBOXii(pCStack_20->pCam_events,pvVar4,iVar5,1);
  }
  lVar6 = Find__6CSTGDBFUl(pCGpffff85e8,0x20204152454d4143);
  if (lVar6 != 0) {
    iVar5 = GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(pCGpffff85e8,lVar6);
    iStack_24 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(pCGpffff85e8,lVar6);
    for (iVar9 = 0; iVar9 < iStack_24; iVar9 = iVar9 + 1) {
      iStack_44 = iVar5 + *(int *)(iVar5 + 8);
      *(int *)(iVar5 + 8) = iStack_44;
      iVar5 = iVar5 + 0x10;
    }
  }
  lVar6 = Find__6CSTGDBFUl(pCGpffff85e8,0x584f42544e455645);
  if (lVar6 != 0) {
    lVar8 = __nw__FUi(0xc);
    pCVar3 = (CFieldEvent *)0x0;
    if (lVar8 != 0) {
      pCVar3 = (CFieldEvent *)__ct__11CFieldEventFv((CFieldEvent *)lVar8);
    }
    pCStack_20->pEvent_boxes = pCVar3;
    pvVar4 = (void *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(pCGpffff85e8,lVar6);
    iVar5 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(pCGpffff85e8,lVar6);
    Init__11CFieldEventFPQ23SDB11tagEVENTBOXii(pCStack_20->pEvent_boxes,pvVar4,iVar5,0);
  }
  lVar6 = Find__6CSTGDBFUl(pCGpffff85e8,0x2050414d4956414e);
  if (lVar6 != 0) {
    lVar8 = __nw__FUi(0x120);
    pvStack_48 = (void *)0x0;
    if (lVar8 != 0) {
      pvStack_48 = (void *)__ct__8CNaviMapFv(lVar8);
    }
    pCStack_20->pNavimap = pvStack_48;
    uVar7 = GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(pCGpffff85e8,lVar6);
    SetData__8CNaviMapFP15_NaviMapDataHdr(pvStack_48,uVar7);
  }
  iStack_4c = GetShadowCtrl__8CFieldBGFb(pCStack_20->pBg,false);
  if (iStack_4c != 0) {
    iVar5 = GetCtrlModel__6CFieldFv(pCStack_20);
    if (((iVar5 != 0) && (iStack_28 != 0)) && (-1 < pCStack_20->nEntry_id)) {
      iStack_54 = GetEntryPoint__6CFieldFiRi(pCStack_20,(int)pCStack_20->nEntry_id,&iStack_50);
      if (iStack_54 != 0) {
        __ct__7FVectorFv(auStack_70);
        memcpy(auStack_70,iStack_54,0xc);
        uStack_64 = 0x3f800000;
        SetDir__11CFieldModelFiii(iVar5,iStack_50,2,0);
        uVar7 = __ct__7FVectorFRC7FVector(auStack_a0,auStack_70);
        SetPos__11CFieldModelF7FVectorb(iVar5,uVar7,1);
        __as__7FVectorFRC7FVector(&pCStack_20->player_pos,auStack_70);
        m_pCAMOLD__6CField = 0;
        m_pCAMDAT__6CField = 0;
        CameraUpdate__6CFieldFf(pCStack_20,0.0);
      }
      DispModel__11CFieldModelFi(iVar5,0xffffffffffffffff);
      DispShadow__11CFieldModelFP13ShadowControl(iVar5,iStack_4c);
    }
  }
  Update__8CFieldBGFf(pCStack_20->pBg,0.0);
  for (iVar5 = 0; iVar5 < (int)uStack_34; iVar5 = iVar5 + 1) {
    if (pCStack_20->aModels[iVar5] != (void *)0x0) {
      Update__11CFieldModelFf(0,pCStack_20->aModels[iVar5]);
    }
  }
  SetFFMode__3GsxFibi(0,1,2);
  SetInter30__3GsxFi(1);
  pCStack_20->wState = 2;
  return 1;
}

/* JP: 0x004ac100  CField::GetEntryPoint(int, int&)   [GetEntryPoint__6CFieldFiRi]  size=0xf0 */
int GetEntryPoint__6CFieldFiRi(CField *this,int a0,int *a1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  
  iVar1 = 0;
  *a1 = -1;
  lVar3 = Find__6CSTGDBFUl(m_pSTGDB__6CField,0x534f505952544e45);
  if (lVar3 != 0) {
    iVar1 = GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(m_pSTGDB__6CField,lVar3);
    iVar2 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(m_pSTGDB__6CField,lVar3);
    if (a0 < 0) {
      *a1 = iVar2;
    }
    else if (a0 < iVar2) {
      iVar1 = iVar1 + a0 * 0x10;
      *a1 = (int)*(char *)(iVar1 + 0xc);
    }
  }
  return iVar1;
}

/* JP: 0x004ac1f0  CField::AddLight(Frame*, unsigned int)   [AddLight__6CFieldFP5FrameUi]  size=0x1f8 */
/* WARNING: Removing unreachable block (ram,0x004ac2ac) */
/* WARNING: Removing unreachable block (ram,0x004ac254) */
/* WARNING: Removing unreachable block (ram,0x004ac304) */

void AddLight__6CFieldFP5FrameUi(CField *this,void *a0,uint a1)

{
  byte abStack_80 [4];
  undefined4 uStack_7c;
  undefined1 auStack_70 [48];
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  undefined4 uStack_34;
  CField *pCStack_30;
  void *pvStack_20;
  uint uStack_10;
  
  pCStack_30 = this;
  pvStack_20 = a0;
  uStack_10 = a1;
  RemoveExLight__8CFieldBGFv(this->pBg);
  pCStack_30->pLight_frame = pvStack_20;
  __ct__7FVectorFv(&fStack_40);
  fStack_40 = (float)(uStack_10 & 0xff) / 255.0;
  fStack_3c = (float)(uStack_10 >> 8 & 0xff) / 255.0;
  fStack_38 = (float)(uStack_10 >> 0x10 & 0xff) / 255.0;
  uStack_34 = 0x3f800000;
  memset(abStack_80,0,0x40);
  memcpy(auStack_70,&fStack_40,0x10);
  abStack_80[0] = abStack_80[0] & 0xe0 | 10;
  uStack_7c = 0x3fe66666;
  AddExLight__8CFieldBGFPv(pCStack_30->pBg,abStack_80);
  return;
}

/* JP: 0x004ac3f0  CField::UpdateLight()   [UpdateLight__6CFieldFv]  size=0x444 */
void UpdateLight__6CFieldFv(CField *this)

{
  int iVar1;
  int iVar2;
  void *a0;
  FVector *a2;
  uint uVar3;
  long lVar4;
  undefined8 uVar5;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [4];
  undefined4 uStack_3c;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_14;
  CField *pCStack_10;
  
  pCStack_10 = this;
  if ((((this->field_0x6cf != '\0') &&
       (iVar1 = GetModel__6CFieldFi(this,(uint)(byte)this->field_0x6cf), iVar1 != 0)) &&
      (lVar4 = isLoaded__11CFieldModelFv(iVar1), lVar4 != 0)) &&
     ((iVar2 = GetModel__6CFieldFi(pCStack_10,(uint)(byte)pCStack_10->field_0x6ce), iVar2 != 0 &&
      (lVar4 = isLoaded__11CFieldModelFv(iVar2), lVar4 != 0)))) {
    a0 = (void *)SearchFrame__11CFieldModelFPCc(iVar2,*(undefined4 *)&pCStack_10->field_0x6d0);
    AddLight__6CFieldFP5FrameUi(pCStack_10,a0,*(uint *)&pCStack_10->field_0x6d4);
    CharAddItem__6CFieldFiiPCci
              (pCStack_10,(uint)(byte)pCStack_10->field_0x6ce,(uint)(byte)pCStack_10->field_0x6cf,
               *(char **)&pCStack_10->field_0x6d0,0);
    SetMoveMotion__11CFieldModelFiii(iVar2,0x1b,0x1c,0x1d);
    lVar4 = isDsp__11CFieldModelFv(iVar2);
    if ((lVar4 != 0) && (lVar4 = isDsp__11CFieldModelFv(iVar1), lVar4 == 0)) {
      a2 = (FVector *)__ct__7FVectorFffff(0,0,0,0x3f800000,auStack_50);
      DispCharacter__6CFieldFii7FVectoriiiPCc
                (pCStack_10,(uint)(byte)pCStack_10->field_0x6cf,1,a2,0,0,0,(char *)0x0);
    }
    pCStack_10->field_0x6cf = 0;
  }
  iVar1 = -1;
  if (pCStack_10->pBg != (CFieldBG *)0x0) {
    iVar1 = GetExLight__8CFieldBGFv(pCStack_10->pBg);
  }
  if ((pCStack_10->pLight_frame != (void *)0x0) && (-1 < iVar1)) {
    getWorldPos__5FrameFi(&fStack_30,pCStack_10->pLight_frame,m_Env__8VIF1Prim & 1);
    GetCameraPos__12CFieldCameraFv((CFieldCamera *)auStack_40);
    __mi__7FVectorCFRC7FVector(auStack_60,&fStack_30,auStack_40);
    __as__7FVectorFRC7FVector(auStack_40,auStack_60);
    uStack_3c._0_2_ = 0;
    uStack_3c._2_1_ = 0;
    uStack_3c._3_1_ = 0;
    Normalize__7FVectorFv(auStack_40);
    __amu__7FVectorFf(0xbf800000,auStack_40);
    __apl__7FVectorFRC7FVector(&fStack_30,auStack_40);
    fStack_24 = 1.0;
    uVar5 = __ct__7FVectorFRC7FVector(auStack_70,&fStack_30);
    changePos__12LightControlFi7FVector(iVar1,uVar5);
    uVar3 = rand();
    if ((uVar3 & 7) == 0) {
      lv$10227 = ((float)((int)uVar3 >> 4 & 0x1f) * 0.3) / 31.0 + 0.7;
    }
    if ((lv$10227 <= clv$10228) ||
       (clv$10228 = clv$10228 + 0.02, clv$10228 <= lv$10227)) {
      if ((lv$10227 < clv$10228) &&
         (clv$10228 = clv$10228 - 0.02, clv$10228 < lv$10227)) {
        clv$10228 = lv$10227;
      }
    }
    else {
      clv$10228 = lv$10227;
    }
    fStack_14 = clv$10228 / 255.0;
    fStack_30 = fStack_14 * 224.0;
    fStack_2c = fStack_14 * 177.0;
    fStack_28 = fStack_14 * 75.0;
    fStack_24 = 1.0;
    uVar5 = __ct__7FVectorFRC7FVector(auStack_80,&fStack_30);
    changeCol__12LightControlFi7FVector(iVar1,uVar5);
  }
  return;
}

/* JP: 0x004ac870  CField::AutoDelLight()   [AutoDelLight__6CFieldFv]  size=0xe0 */
void AutoDelLight__6CFieldFv(CField *this)

{
  int iVar1;
  long lVar2;
  
  if (this->pLight_frame != (void *)0x0) {
    iVar1 = GetCtrlModel__6CFieldFv(this);
    if (iVar1 != 0) {
      lVar2 = CharRemoveItem__6CFieldFiPCc
                        (this,(int)(char)this->field_0x6cc,
                         *(char **)((int)this->pLight_frame + 0x80));
      SetMoveMotion__11CFieldModelFiii(iVar1,1,2,3);
      if (-1 < lVar2) {
        ClrCharacter__6CFieldFii(this,(int)lVar2,0);
      }
    }
    if (this->pBg != (CFieldBG *)0x0) {
      RemoveExLight__8CFieldBGFv(this->pBg);
    }
    this->pLight_frame = (void *)0x0;
  }
  return;
}

/* JP: 0x004ac950  CField::CallFunc(int, int, _ParStack*)   [CallFunc__6CFieldFiiP9_ParStack]  size=0x3ae4 */
uint CallFunc__6CFieldFiiP9_ParStack(CField *this,int a0,int a1,void *a2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  char cVar5;
  FVector *a2_00;
  int iVar6;
  undefined4 uVar7;
  ushort *puVar8;
  char *pcVar9;
  uint uVar10;
  long lVar11;
  undefined8 uVar12;
  byte *pbVar13;
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  int iStack_1d0;
  int iStack_1cc;
  int iStack_1c8;
  undefined4 uStack_1c4;
  int aiStack_1b8 [7];
  char *pcStack_19c;
  undefined4 uStack_198;
  int iStack_194;
  float *pfStack_190;
  int iStack_18c;
  float *pfStack_188;
  undefined4 uStack_184;
  float fStack_180;
  float *pfStack_17c;
  float *pfStack_178;
  int iStack_174;
  uint uStack_170;
  int iStack_16c;
  int iStack_160;
  int iStack_15c;
  int iStack_158;
  int iStack_154;
  int iStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  int iStack_144;
  undefined4 uStack_140;
  float *pfStack_13c;
  int iStack_138;
  float *pfStack_134;
  int iStack_12c;
  int iStack_124;
  int iStack_120;
  uint uStack_110;
  char *pcStack_10c;
  uint uStack_104;
  int iStack_100;
  int iStack_fc;
  int iStack_f8;
  int aiStack_f0 [2];
  int iStack_e8;
  int iStack_e4;
  int iStack_e0;
  int iStack_dc;
  int iStack_d8;
  int iStack_d4;
  int iStack_d0;
  int iStack_cc;
  int iStack_c8;
  undefined4 uStack_c4;
  void *pvStack_c0;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  int iStack_b0;
  void *pvStack_ac;
  int iStack_a8;
  uint uStack_a4;
  uint uStack_a0;
  int iStack_9c;
  int iStack_98;
  undefined4 uStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  uint uStack_80;
  void *pvStack_7c;
  void *pvStack_78;
  void *pvStack_74;
  void *pvStack_70;
  int iStack_6c;
  int iStack_68;
  void *pvStack_64;
  int iStack_60;
  void *pvStack_5c;
  void *pvStack_58;
  void *pvStack_54;
  int iStack_50;
  void *pvStack_4c;
  int iStack_48;
  uint uStack_44;
  CField *pCStack_40;
  int iStack_30;
  uint uStack_20;
  uint *puStack_10;
  
  pCStack_40 = this;
  iStack_30 = a0;
  uStack_20 = a1;
  puStack_10 = a2;
  if (a0 < 0x20) {
    switch(a0) {
    case 0:
      lVar11 = GetCharacterInfo__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      *puStack_10 = (int)lVar11;
      return 1;
    case 1:
      SetCharacterInfo__6CFieldFiii(this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      break;
    case 2:
      CharAddItem__6CFieldFiiPCci
                (this,*(int *)a2,*(int *)((int)a2 + 4),*(char **)((int)a2 + 8),
                 *(int *)((int)a2 + 0xc));
      break;
    case 3:
      CharRemoveItem__6CFieldFiPCc(this,*(int *)a2,*(char **)((int)a2 + 4));
      break;
    case 4:
      if ((int)*(uint *)((int)a2 + 4) < 0) {
        uStack_44 = 0x80;
      }
      else {
        uStack_44 = *(uint *)((int)a2 + 4) | 0x80;
      }
      CharAddItem__6CFieldFiiPCci
                (this,uStack_44,*(int *)a2,*(char **)((int)a2 + 8),*(int *)((int)a2 + 0xc));
      break;
    case 5:
      if (*(int *)a2 == 1) {
        if (this->pBg != (CFieldBG *)0x0) {
          uVar12 = FindFrame__8CFieldBGFiPCc
                             (this->pBg,*(int *)((int)a2 + 0xc),*(char **)((int)a2 + 4));
          pvStack_4c = (void *)uVar12;
          if (pvStack_4c != (void *)0x0) {
            LgtAttachFrame__8CFieldBGFiP5Frame
                      (pCStack_40->pBg,*(int *)((int)puStack_10 + 8),pvStack_4c);
          }
        }
      }
      else if ((*(int *)a2 == 0) && (this->pNavimap != (void *)0x0)) {
        uVar12 = FindFrame__8CFieldBGFiPCc
                           (this->pBg,*(int *)((int)a2 + 0xc),*(char **)((int)a2 + 4));
        iStack_48 = (int)uVar12;
        if (iStack_48 != 0) {
          AttachFrame__8CNaviMapFiP5Frame
                    (pCStack_40->pNavimap,*(undefined4 *)((int)puStack_10 + 8),iStack_48);
        }
      }
      break;
    case 7:
      LoadCharacter__6CFieldFiPCciUi
                (this,*(int *)a2,*(char **)((int)a2 + 4),-1,*(uint *)((int)a2 + 8));
      break;
    case 8:
      LoadCharacter__6CFieldFiiUi(this,*(int *)a2,*(int *)((int)a2 + 4),*(uint *)((int)a2 + 8));
      break;
    case 9:
      UnloadCharacter__6CFieldFi(this,*(int *)a2);
      break;
    case 10:
      iStack_50 = *(int *)((int)a2 + 0x10);
      __ct__7FVectorFv(&iStack_1d0);
      iStack_1d0 = puStack_10[1];
      iStack_1cc = puStack_10[2];
      iStack_1c8 = puStack_10[3];
      uStack_1c4 = 0x3f800000;
      a2_00 = (FVector *)__ct__7FVectorFRC7FVector(auStack_240,&iStack_1d0);
      DispCharacter__6CFieldFii7FVectoriiiPCc
                (pCStack_40,*puStack_10,2,a2_00,iStack_50,puStack_10[5],puStack_10[6],(char *)0x0);
      break;
    case 0xb:
      DispCharacterEP__6CFieldFiiiiPCc
                (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8),*(int *)((int)a2 + 0xc)
                 ,(char *)0x0);
      break;
    case 0xc:
      ClrCharacter__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0xd:
      pvStack_54 = this->aModels[*(int *)a2];
      if ((pvStack_54 != (void *)0x0) && (*(uint *)((int)a2 + 4) < 3)) {
        aiStack_1b8[2] = 0xffffffff;
        aiStack_1b8[1] = 0xffffffff;
        aiStack_1b8[0] = -1;
        aiStack_1b8[*(int *)((int)a2 + 4)] = *(int *)((int)a2 + 8);
        SetMoveMotion__11CFieldModelFiii(pvStack_54,aiStack_1b8[0],aiStack_1b8[1],aiStack_1b8[2]);
      }
      break;
    case 0xe:
      pvStack_58 = this->aModels[*(int *)a2];
      if (pvStack_58 != (void *)0x0) {
        LoadMotion__11CFieldModelFPCcUiPFUiUiPv_vPv
                  (pvStack_58,*(undefined4 *)((int)a2 + 4),*(undefined4 *)((int)a2 + 8),0x4b2b10,
                   this);
      }
      break;
    case 0xf:
      pvStack_5c = this->aModels[*(int *)a2];
      if (pvStack_5c != (void *)0x0) {
        UnloadMotion__11CFieldModelFPCc(pvStack_5c,*(undefined4 *)((int)a2 + 4));
      }
      break;
    case 0x10:
      SetMotion__6CFieldFiii(this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      break;
    case 0x11:
      iStack_60 = EncodeMotionName__FPCc(*(undefined4 *)((int)a2 + 4));
      SetMotion__6CFieldFiii(pCStack_40,*puStack_10,iStack_60,puStack_10[2]);
      break;
    case 0x12:
      DispCharacterEP__6CFieldFiiiiPCc
                (this,*(int *)a2,*(int *)((int)a2 + 4),0,*(int *)((int)a2 + 0xc),
                 *(char **)((int)a2 + 8));
      break;
    case 0x14:
      if (a1 < 1) {
        uVar10 = a1 + 0x100;
      }
      else {
        uVar10 = *(uint *)a2;
      }
      if ((-1 < (int)uVar10) && ((int)uVar10 < 0x100)) {
        if ((uVar10 & 0x80) == 0) {
          pvStack_64 = this->aModels[uVar10];
        }
        else {
          uVar12 = GetBGModel__6CFieldFi(this,uVar10 & 0x7f);
          pvStack_64 = (void *)uVar12;
        }
        if (pvStack_64 != (void *)0x0) {
          iStack_68 = *(int *)((int)puStack_10 + 4);
          iStack_6c = CheckLastCmdComplete__11CFieldModelFv(pvStack_64);
          if (-1 < iStack_6c) {
            if (iStack_6c == 0) {
              if (((int)uStack_20 < 1) || (iStack_68 == 0)) {
                return uVar10 - 0x100;
              }
              SetLastCmdEvent__11CFieldModelFUi(pvStack_64,iStack_68);
            }
            else if (((0 < iStack_6c) && (0 < (int)uStack_20)) && (iStack_68 != 0)) {
              SetLastCmdEvent__11CFieldModelFUi(pvStack_64,iStack_68);
            }
          }
        }
      }
      break;
    case 0x15:
      pvStack_70 = this->aModels[*(int *)a2];
      if (pvStack_70 != (void *)0x0) {
        SetMotionSpeed__11CFieldModelFf(*(undefined4 *)((int)a2 + 4),pvStack_70);
      }
      break;
    case 0x16:
      SetCharacterDir__6CFieldFiiii
                (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8),*(int *)((int)a2 + 0xc)
                );
      break;
    case 0x17:
      pvStack_74 = this->aModels[*(int *)a2];
      if (pvStack_74 == (void *)0x0) {
        memset(*(undefined4 *)((int)a2 + 4),0,0xc);
      }
      else {
        __ct__7FVectorFv(auStack_1e0);
        GetPos__11CFieldModelFv(auStack_250,pvStack_74);
        __as__7FVectorFRC7FVector(auStack_1e0,auStack_250);
        memcpy(*(undefined4 *)((int)puStack_10 + 4),auStack_1e0,0xc);
      }
      break;
    case 0x18:
      pvStack_78 = this->aModels[*(int *)a2];
      if (pvStack_78 != (void *)0x0) {
        __ct__7FVectorFv(auStack_1f0);
        memcpy(auStack_1f0,*(undefined4 *)((int)puStack_10 + 4),0xc);
        SetCmd__11CFieldModelFi(pvStack_78,9);
        *(byte *)((int)pvStack_78 + 0x8b) = *(byte *)((int)pvStack_78 + 0x8b) & 0xfe;
        AutoMove__11CFieldModelFP7FVectoriii
                  (pvStack_78,auStack_1f0,*(undefined4 *)((int)puStack_10 + 8),
                   *(undefined4 *)((int)puStack_10 + 0xc),*(undefined4 *)((int)puStack_10 + 0x10));
      }
      break;
    case 0x19:
      pvStack_7c = this->aModels[*(int *)a2];
      if (pvStack_7c != (void *)0x0) {
        uStack_80 = *(uint *)((int)a2 + 4);
        iStack_84 = *(int *)((int)a2 + 8);
        if (iStack_84 == 0) {
          iStack_88 = Find__6CSTGDBFUl(m_pSTGDB__6CField,0x48544150594d4e45);
          if (iStack_88 == 0) {
            return 0;
          }
          iStack_8c = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(m_pSTGDB__6CField,iStack_88);
          if (iStack_8c <= (int)uStack_80) {
            return 0;
          }
          iStack_90 = GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(m_pSTGDB__6CField,iStack_88);
          iStack_90 = iStack_90 + uStack_80 * 0x10;
          uStack_80 = (uint)*(ushort *)(iStack_90 + 10);
          iStack_84 = iStack_90 + *(int *)(iStack_90 + 0xc);
        }
        uStack_94 = 0;
        if (3 < iStack_30) {
          uStack_94 = *(undefined4 *)((int)puStack_10 + 0xc);
        }
        PathMove__11CFieldModelFiPC9_PATHLISTUi(pvStack_7c,uStack_80,iStack_84,uStack_94);
        SetCmd__11CFieldModelFi(pvStack_7c,9);
        *(byte *)((int)pvStack_7c + 0x8b) = *(byte *)((int)pvStack_7c + 0x8b) & 0xfe;
      }
      break;
    case 0x1a:
      if (a1 < 0) {
        iStack_98 = a1 + 0x80;
      }
      else {
        if (a1 < 2) {
          uStack_198 = 0;
        }
        else {
          uStack_198 = *(undefined4 *)((int)a2 + 4);
        }
        this->field_0x718 = (char)uStack_198;
        iStack_98 = *(int *)a2;
      }
      iVar6 = WaitCharacterEx__6CFieldFii(this,iStack_98,(uint)(byte)this->field_0x718);
      if (iVar6 == 0) {
        return iStack_98 - 0x80;
      }
      break;
    case 0x1c:
      iStack_9c = *(int *)a2;
      uStack_a0 = (uint)(*(int *)((int)a2 + 4) != 0);
      uStack_a4 = (uint)this->bModel_count;
      for (iStack_a8 = 0; iStack_a8 < (int)uStack_a4; iStack_a8 = iStack_a8 + 1) {
        pvStack_ac = pCStack_40->aModels[iStack_a8];
        if (((pvStack_ac != (void *)0x0) && (iStack_a8 == iStack_9c)) &&
           (SetManual__11CFieldModelFi(pvStack_ac,uStack_a0), uStack_a0 != 0)) {
          ChgCtrl__11CFieldModelFi(pvStack_ac,1);
        }
      }
      break;
    case 0x1d:
      __ct__7FVectorFv(auStack_200);
      memcpy(auStack_200,puStack_10[1],0xc);
      uVar7 = GetModel__6CFieldFi(pCStack_40,*puStack_10);
      SetViewPoint__11CFieldModelFP7FVectorfii
                (puStack_10[2],uVar7,auStack_200,puStack_10[3],0xffffffffffffffff);
      break;
    case 0x1e:
      iStack_b0 = *(int *)((int)a2 + 4);
      if (iStack_b0 < 0x80) {
        iStack_b8 = GetEntryPoint__6CFieldFiRi(this,iStack_b0,&iStack_b4);
        __ct__7FVectorFv(auStack_210);
        memcpy(auStack_210,iStack_b8,0xc);
        uVar7 = GetModel__6CFieldFi(pCStack_40,*puStack_10);
        SetViewPoint__11CFieldModelFP7FVectorfii
                  (puStack_10[2],uVar7,auStack_210,puStack_10[3],0xffffffffffffffff);
      }
      else {
        uVar7 = GetModel__6CFieldFi(this,*(int *)a2);
        SetViewPoint__11CFieldModelFP7FVectorfii
                  (*(undefined4 *)((int)puStack_10 + 8),uVar7,0,
                   *(undefined4 *)((int)puStack_10 + 0xc),iStack_b0);
      }
      break;
    case 0x1f:
      uVar7 = GetModel__6CFieldFi(this,*(int *)a2);
      ClrViewPoint__11CFieldModelFv(uVar7);
    }
  }
  else if (a0 < 0x50) {
    switch(a0) {
    case 0x20:
      *(undefined1 *)(sys__6SSHSys + 0x50) = 1;
      MapJumpA__6CFieldFPCci(this,*(char **)a2,*(int *)((int)a2 + 4));
      return 7;
    case 0x21:
      if ((this->bFlags_18e & 3) == 0) {
        strcpy(&this->field_0x719,*(undefined4 *)a2);
      }
      break;
    case 0x22:
      iStack_bc = GetModel__6CFieldFi(this,*(int *)a2);
      if (iStack_bc != 0) {
        pvStack_c0 = (void *)SearchFrame__11CFieldModelFPCc
                                       (iStack_bc,*(undefined4 *)((int)puStack_10 + 4));
        AddLight__6CFieldFP5FrameUi(pCStack_40,pvStack_c0,*(uint *)((int)puStack_10 + 8));
      }
      break;
    case 0x23:
      SetFieldData__6CFieldFiii(this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      break;
    case 0x24:
      lVar11 = GetFieldData__6CFieldFiii
                         (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      *puStack_10 = (int)lVar11;
      return 1;
    case 0x25:
      if (a1 == 2) {
        pcStack_19c = (char *)0x0;
      }
      else {
        pcStack_19c = *(char **)((int)a2 + 8);
      }
      SetBGMotion__6CFieldFiPCcPCc(this,*(int *)a2,*(char **)((int)a2 + 4),pcStack_19c);
      break;
    case 0x26:
      uStack_c4 = 0;
      uVar12 = GetBGModel__6CFieldFi(this,*(int *)((int)a2 + 4));
      iStack_c8 = (int)uVar12;
      if ((iStack_c8 != 0) &&
         (iStack_cc = SearchFrame__11CFieldModelFPCc(iStack_c8,puStack_10[2]), iStack_cc != 0)) {
        getWorldPos__5FrameFi(auStack_220,iStack_cc,m_Env__8VIF1Prim & 1);
        memcpy(*puStack_10,auStack_220,0x10);
      }
      return 1;
    case 0x27:
      iStack_d0 = *(int *)((int)a2 + 4);
      iStack_d8 = GetEntryPoint__6CFieldFiRi(this,iStack_d0,&iStack_d4);
      if ((-1 < iStack_d0) && (-1 < iStack_d4)) {
        memcpy(*puStack_10,iStack_d8,0xc);
      }
      *puStack_10 = iStack_d4;
      return 1;
    case 0x28:
      SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,1,*(undefined4 *)a2,*(undefined4 *)((int)a2 + 4));
      break;
    case 0x29:
      SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,0,*(undefined4 *)a2,*(undefined4 *)((int)a2 + 4));
      break;
    case 0x2a:
      uVar12 = GetBGModel__6CFieldFi(this,*(int *)a2);
      iStack_dc = (int)uVar12;
      if ((iStack_dc != 0) && (lVar11 = isEmpty__11CFieldModelFv(iStack_dc), lVar11 == 0)) {
        SetMotionSpeed__11CFieldModelFf(*(undefined4 *)((int)puStack_10 + 4),iStack_dc);
      }
      break;
    case 0x2c:
      LoadImage__6CFieldFPCci(this,*(char **)a2,*(int *)((int)a2 + 4));
      break;
    case 0x2d:
      DspImage__6CFieldFiiiii
                (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8),*(int *)((int)a2 + 0xc)
                 ,*(int *)((int)a2 + 0x10));
      break;
    case 0x2e:
      ClrImage__6CFieldFiiib
                (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8),
                 *(int *)((int)a2 + 0xc) != 0);
      break;
    case 0x30:
      lVar11 = IsReadyField__7MenuObjFv();
      if (lVar11 == 0) {
        return 0xffffffff;
      }
      CreateWindow__6CFieldFiiii(pCStack_40,*puStack_10,puStack_10[1],puStack_10[2],puStack_10[3]);
      break;
    case 0x31:
      SetActiveWindow__6CFieldFi(this,*(int *)a2);
      break;
    case 0x32:
      SetWindowPos__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x33:
      SetWindowSize__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x34:
      OpenWindow__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x35:
      CloseWindow__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x36:
      OpenMessage__6CFieldFPcii(this,*(char **)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      break;
    case 0x37:
      ClearMessage__6CFieldFv(this);
      break;
    case 0x38:
      uVar10 = KeyWait__6CFieldFv(this);
      return uVar10;
    case 0x39:
      lVar11 = IsReadyField__7MenuObjFv();
      if (lVar11 == 0) {
        return 0xffffffff;
      }
      CreateName__6CFieldFiiii(pCStack_40,*puStack_10,puStack_10[1],puStack_10[2],puStack_10[3]);
      break;
    case 0x3a:
      SetActiveName__6CFieldFi(this,*(int *)a2);
      break;
    case 0x3b:
      SetNamePos__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x3c:
      OpenName__6CFieldFPcii(this,*(char **)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      break;
    case 0x3d:
      CloseName__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x40:
      LoadFace__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x41:
      ReleaseFace__6CFieldFi(this,*(int *)a2);
      break;
    case 0x42:
      SetActiveFace__6CFieldFi(this,*(int *)a2);
      break;
    case 0x43:
      SetFacePos__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x44:
      SetFaceSize__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x45:
      OpenFace__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x46:
      CloseFace__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x48:
      if (a1 < 0) {
        iVar6 = Select__6CFieldFRi(this,&iStack_e8);
        if (0 < iVar6) {
          *puStack_10 = iStack_e8;
          return 1;
        }
      }
      else {
        SelectInit__6CFieldFi(this,*(int *)a2);
        SelectInitItem__6CFieldFv(pCStack_40);
        for (iStack_e0 = 1; iStack_e0 < (int)uStack_20; iStack_e0 = iStack_e0 + 1) {
          if (puStack_10[iStack_e0] != 0) {
            SelectAddItem__6CFieldFPCc(pCStack_40,(char *)puStack_10[iStack_e0]);
          }
        }
        iVar6 = Select__6CFieldFRi(pCStack_40,&iStack_e4);
        if (iVar6 < 0) {
          *puStack_10 = 0xfffffffe;
          return 1;
        }
      }
      return 0xffffffff;
    case 0x49:
      SelectInit__6CFieldFi(this,*(int *)a2);
      SelectInitItem__6CFieldFv(pCStack_40);
      break;
    case 0x4a:
      SelectAddItem__6CFieldFPCc(this,*(char **)a2);
      break;
    case 0x4b:
      iVar6 = Select__6CFieldFRi(this,aiStack_f0);
      if (iVar6 < 0) {
        aiStack_f0[0] = -2;
      }
      if (iVar6 == 0) {
        return 0xffffffff;
      }
      *puStack_10 = aiStack_f0[0];
      return 1;
    case 0x4e:
      if (sys__8FldTimer == 0) {
        aiStack_1b8[6] = __nw__FUi(0x68);
        if (aiStack_1b8[6] != 0) {
          aiStack_1b8[6] = __ct__8FldTimerFv(aiStack_1b8[6]);
        }
        sys__8FldTimer = aiStack_1b8[6];
      }
      Create__8FldTimerFi(sys__8FldTimer,puStack_10[4]);
      SetPos__8FldTimerFii(sys__8FldTimer,*puStack_10,puStack_10[1]);
      iStack_f8 = puStack_10[2] * 10;
      iStack_fc = puStack_10[3];
      if (0 < iStack_fc) {
        iStack_fc = iStack_fc * 10;
      }
      SetCount__8FldTimerFii(sys__8FldTimer,iStack_f8,iStack_fc);
      *(uint *)&pCStack_40->field_0x604 = puStack_10[5];
      break;
    case 0x4f:
      iStack_100 = 0;
      if (sys__8FldTimer != 0) {
        iStack_100 = GetCount__8FldTimerFv(sys__8FldTimer);
        iVar6 = *puStack_10;
        if (iVar6 == 4) {
          Clr__8FldTimerFv(sys__8FldTimer);
        }
        else if (iVar6 == 3) {
          Dsp__8FldTimerFv(sys__8FldTimer);
        }
        else if (iVar6 == 1) {
          Stop__8FldTimerFv(sys__8FldTimer);
        }
        else if (iVar6 == 0) {
          Start__8FldTimerFv(sys__8FldTimer);
        }
      }
      *puStack_10 = iStack_100;
      return 1;
    }
  }
  else if (a0 < 0x60) {
    switch(a0) {
    case 0x50:
      LoadBgm__6CFieldFPCc(this,*(char **)a2);
      break;
    case 0x51:
      PlayBgm__6CFieldFiUi(this,*(int *)a2,*(uint *)((int)a2 + 4));
      break;
    case 0x52:
      BgmFade__6CFieldFUiUi(this,*(uint *)a2,*(uint *)((int)a2 + 4));
      break;
    case 0x53:
      SetBgmVolume__6CFieldFi(this,*(int *)a2);
      break;
    case 0x54:
      uStack_104 = *(uint *)a2;
      if (a1 < 0) {
        uStack_104 = a1 & 0xffff;
      }
      lVar11 = WaitBgm__6CFieldFi(this,uStack_104 & 0x7f);
      if (((uStack_104 & 0x80) == 0) && ((int)lVar11 == 0)) {
        return uStack_104 | 0xffff0000;
      }
      *puStack_10 = (uint)((int)lVar11 != 0);
      return 1;
    case 0x55:
      SetBattleBgm__6CFieldFPCc(this,*(char **)a2);
      break;
    case 0x56:
      if (a1 == 1) {
        aiStack_1b8[5] = 0;
      }
      else {
        aiStack_1b8[5] = *(int *)((int)a2 + 4);
      }
      LoadSe__6CFieldFPCci(this,*(char **)a2,aiStack_1b8[5]);
      break;
    case 0x57:
      pcStack_10c = *(char **)a2;
      if (pcStack_10c == (char *)0x0) {
        pcStack_10c = (char *)0xffffffff;
      }
      else if (pcStack_10c == (char *)0xffffffff) {
        pcStack_10c = (char *)0x0;
      }
      UnloadSe__6CFieldFPCc(this,pcStack_10c);
      break;
    case 0x58:
      PlaySe__6CFieldFUii(this,*(uint *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x59:
      SetSeVolume__6CFieldFi(this,*(int *)a2);
      break;
    case 0x5a:
      StopSe__6CFieldFUi(this,*(uint *)a2);
      break;
    case 0x5b:
      uStack_110 = *(uint *)((int)a2 + 4);
      if (a0 < 0) {
        uStack_110 = a0 & 0xffff;
      }
      else {
        *(undefined4 *)&this->field_0x168 = *(undefined4 *)a2;
      }
      bVar4 = WaitSe__6CFieldFUii(this,*(uint *)&this->field_0x168,uStack_110 & 0x7f);
      if (((uStack_110 & 0x80) == 0) && (!bVar4)) {
        return uStack_110 | 0xffff0000;
      }
      *puStack_10 = (uint)bVar4;
      break;
    case 0x5c:
      SetObjSE__6CFieldFiUiUiiP7FVector
                (this,*(int *)a2,*(uint *)((int)a2 + 4),*(uint *)((int)a2 + 8),
                 *(int *)((int)a2 + 0xc),*(FVector **)((int)a2 + 0x10));
      break;
    case 0x5d:
      if (a1 < 0) {
        iVar6 = SetSoundData__6CFieldFiii(this,a1,0,0);
        if (iVar6 < 0) {
          return uStack_20;
        }
      }
      else {
        iVar6 = SetSoundData__6CFieldFiii
                          (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
        if (iVar6 < 0) {
          return *puStack_10 - 0x100;
        }
      }
      break;
    case 0x5e:
      PlayStreamBgm__6CFieldFPCci(this,*(char **)a2,*(int *)((int)a2 + 4));
      break;
    case 0x5f:
      if (0 < a1) {
        iStack_120 = *(int *)a2;
        if (iStack_120 != 2) {
          uVar12 = PlaySeR__6CFieldFiUiii
                             (this,iStack_120,*(uint *)((int)a2 + 4),*(int *)((int)a2 + 8),
                              *(int *)((int)a2 + 0xc));
          *puStack_10 = (int)uVar12;
          return 1;
        }
        *(undefined4 *)&this->field_0x708 = *(undefined4 *)((int)a2 + 4);
        *(undefined4 *)&this->field_0x70c = *(undefined4 *)((int)a2 + 8);
        uStack_20 = 0xfffffff6;
        iStack_120 = 2;
      }
      if (uStack_20 != 0xfffffff5) {
        if (uStack_20 != 0xfffffff6) {
          return uStack_20;
        }
        PlaySeR__6CFieldFiUiii(this,0,*(uint *)&this->field_0x708,*(int *)&this->field_0x70c,0);
        uStack_20 = uStack_20 - 1;
      }
      uVar12 = PlaySeR__6CFieldFiUiii(pCStack_40,1,*(uint *)&pCStack_40->field_0x708,0,0);
      iStack_124 = (int)uVar12;
      if (-1 < iStack_124) {
        *puStack_10 = iStack_124;
        return 1;
      }
      if (iStack_124 == -2) {
        StopSe__6CFieldFUi(pCStack_40,*(uint *)&pCStack_40->field_0x708);
        uStack_20 = 0xfffffff6;
      }
      if (iStack_124 == -3) {
        return 0xfffffff6;
      }
      return uStack_20;
    }
  }
  else if (a0 < 0x70) {
    switch(a0) {
    case 0x60:
      uVar7 = StartEffect__6CFieldFPCcUiPvPv
                        (this,*(char **)a2,*(uint *)((int)a2 + 4),*(void **)((int)a2 + 8),
                         *(void **)((int)a2 + 0xc));
      *puStack_10 = uVar7;
      return 1;
    case 0x61:
      uVar10 = EffectControl__6CFieldFiiii
                         (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8),
                          *(int *)((int)a2 + 0xc));
      *puStack_10 = uVar10;
      return 1;
    case 0x62:
      if (-1 < a0) {
        iStack_12c = 0;
        iVar6 = *(int *)a2;
        if (iVar6 == 3) {
          if (this->bMces_state != 0) {
            Pause__6CFieldFi(this,0);
            Pause__7CScriptFi(fldScript__12CFieldSocket,1);
            *puStack_10 = *puStack_10 + -0x100;
            return 0xffffffff;
          }
        }
        else if (iVar6 == 2) {
          if (this->bMces_state != 0) {
            StartMCES__6CFieldFv(this);
            *puStack_10 = *puStack_10 + -0x100;
            return 0xffffffff;
          }
        }
        else if (iVar6 == 1) {
          PlayMCES__6CFieldFPCcii
                    (this,*(char **)((int)a2 + 4),*(int *)((int)a2 + 8),*(int *)((int)a2 + 0xc));
          if ((int)puStack_10[3] < 0) {
            Pause__6CFieldFi(pCStack_40,0);
            Pause__7CScriptFi(fldScript__12CFieldSocket,1);
            *puStack_10 = *puStack_10 + -0x100;
            return 0xffffffff;
          }
        }
        else if (iVar6 == 0) {
          SetMCESMode__6CFieldFPCcii
                    (this,*(char **)((int)a2 + 4),*(int *)((int)a2 + 8),*(int *)((int)a2 + 0xc));
        }
        *puStack_10 = iStack_12c;
        return 1;
      }
      if (this->bMces_state != 0) {
        *(int *)a2 = a0;
        return 0xffffffff;
      }
      return 1;
    case 99:
      SetRing__6CFieldFiiiiiPCc
                (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8),*(int *)((int)a2 + 0xc)
                 ,*(int *)((int)a2 + 0x10),*(char **)((int)a2 + 0x14));
      break;
    case 100:
      if (-1 < a1) {
        RingControl__6CFieldFiiii
                  (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8),
                   *(int *)((int)a2 + 0xc));
        return 0xfffffff6;
      }
      iVar6 = RingResult__6CFieldFv(this);
      if (-1 < iVar6) {
        *puStack_10 = iVar6;
        return 1;
      }
      return 0xffffffff;
    case 0x65:
      if (-1 < a1) {
        pfStack_134 = *(float **)((int)a2 + 4);
        iVar6 = *(int *)((int)a2 + 0xc);
        if (pfStack_134 == (float *)0x0) {
          if (iVar6 == -1) {
            uVar12 = ClrWarpPoint__6CFieldFi(this,*(int *)a2);
            iVar6 = (int)uVar12;
          }
          else {
            if (iVar6 == -2) {
              lVar11 = (long)*(int *)((int)a2 + 8);
              DoWarp__6CFieldFiiUiUi(this,*(int *)a2,*(int *)((int)a2 + 8),0,0);
              SetWarp__12CFieldSocketFi(m_socket__12CFieldSocket,puStack_10[2],lVar11);
              return *puStack_10 - 0x100;
            }
            if (iVar6 == -3) {
              uVar12 = WarpFade__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 8));
              iVar6 = (int)uVar12;
            }
            else {
              pfStack_13c = (float *)GetEntryPoint__6CFieldFiRi(this,iVar6,&iStack_138);
              if (pfStack_13c == (float *)0x0) {
                iVar6 = -1;
              }
              else {
                iVar6 = SetWarpPoint__6CFieldFiPfii
                                  (pCStack_40,*puStack_10,pfStack_13c,puStack_10[2],0);
              }
            }
          }
        }
        else {
          iVar6 = SetWarpPoint__6CFieldFiPfii
                            (this,*(int *)a2,pfStack_134,*(int *)((int)a2 + 8),iVar6);
        }
        *puStack_10 = iVar6;
        return 1;
      }
      bVar4 = IsWarp__6CFieldFi(this,a1 + 0x100);
      if (!bVar4) {
        *puStack_10 = 0;
        SetWarp__12CFieldSocketFi(m_socket__12CFieldSocket,0xffffffffffffffff);
        return 1;
      }
      return uStack_20;
    case 0x66:
      uVar7 = *(undefined4 *)((int)a2 + 4);
      uVar2 = *(undefined4 *)((int)a2 + 8);
      switch(*(undefined4 *)a2) {
      case 0:
        InventoryChange__Fiii(0x3c,uVar7,uVar2);
        break;
      case 1:
        InventoryChange__Fiii(0x3e,uVar7,uVar2);
        break;
      case 2:
        InventoryChange__Fiii(0x21,uVar7,uVar2);
        break;
      case 3:
        InventoryChange__Fiii(0x39,uVar7,uVar2);
        break;
      case 4:
        InventoryChange__Fiii(0x22,uVar7,uVar2);
        break;
      case 5:
        InventoryChange__Fiii(0x23,uVar7,uVar2);
        break;
      case 6:
        InventoryChange__Fiii(0x24,uVar7,uVar2);
        break;
      case 7:
        InventoryChange__Fiii(0x25,uVar7,uVar2);
        break;
      case 8:
        InventoryChange__Fiii(0x3d,uVar7,uVar2);
      }
      break;
    case 0x67:
      __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_230);
      iStack_150 = puStack_10[4];
      if (iStack_150 != 0) {
        memcpy(auStack_230,iStack_150,0xc);
      }
      uStack_140 = puStack_10[1];
      iStack_144 = puStack_10[2];
      uStack_14c = puStack_10[3];
      uStack_148 = puStack_10[5];
      switch(*puStack_10) {
      case 0:
        SetItem__8CNaviMapFiiR7FVectoriibUi
                  (pCStack_40->pNavimap,uStack_140,iStack_144,auStack_230,uStack_148,uStack_14c,1,
                   puStack_10[6]);
        break;
      case 1:
        iStack_154 = GetModel__6CFieldFi(pCStack_40,iStack_144);
        if (iStack_154 != 0) {
          AddNaviItem__11CFieldModelFiii(iStack_154,uStack_140,uStack_14c,0);
        }
        break;
      case 2:
        DspItem__8CNaviMapFib(pCStack_40->pNavimap,uStack_140,iStack_144 != 0);
        break;
      case 3:
        RemoveItem__8CNaviMapFi(pCStack_40->pNavimap,uStack_140);
        break;
      case 4:
        DspMesh__8CNaviMapFii(pCStack_40->pNavimap,iStack_144,uStack_14c);
        break;
      case 5:
        iStack_158 = GetModel__6CFieldFi(pCStack_40,iStack_144);
        if (iStack_158 != 0) {
          AddNaviItem__11CFieldModelFiii(iStack_158,uStack_140,uStack_14c,1);
        }
      }
      break;
    case 0x68:
      uVar7 = CharacterEquip__Fiiiii(*(undefined4 *)a2,*(undefined4 *)((int)a2 + 4),
                              *(undefined4 *)((int)a2 + 8),*(undefined4 *)((int)a2 + 0xc),
                              *(undefined4 *)((int)a2 + 0x10));
      *puStack_10 = uVar7;
      return 1;
    case 0x69:
      StartVib__6CFieldFiii(this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      break;
    case 0x6a:
      StartVib__6CFieldFiPCci(this,*(int *)a2,*(char **)((int)a2 + 4),*(int *)((int)a2 + 8));
      break;
    case 0x6b:
      VibControl__6CFieldFiiii(this,0,*(int *)a2,*(int *)((int)a2 + 4),0);
      break;
    case 0x6c:
      VibControl__6CFieldFiiii(this,1,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      break;
    case 0x6d:
      VibControl__6CFieldFiiii(this,2,*(int *)a2,*(int *)((int)a2 + 4),0);
      break;
    case 0x6e:
      cVar5 = VibControl__6CFieldFiiii(this,3,*(int *)a2,0,0);
      *puStack_10 = (int)cVar5;
      return 1;
    case 0x6f:
      if (a1 < 0) {
        iStack_160 = DiskChangeStat__6SSHSysFv(sys__6SSHSys);
        if (iStack_160 == 3) {
          if (*(int *)&pCStack_40->field_0x608 == 0) {
            DiskChangeRetry__6SSHSysFv(sys__6SSHSys);
          }
          else {
            SetFieldEvent__6CFieldFiUiiii(pCStack_40,0,*(uint *)&pCStack_40->field_0x608,1,0,0);
          }
        }
        else if (iStack_160 == 2) {
          return 0;
        }
      }
      else {
        if (*(int *)a2 == 0) {
          iStack_15c = DiskChangeStat__6SSHSysFv(sys__6SSHSys);
          if (iStack_15c != 3) {
            return 0;
          }
          DiskChangeRetry__6SSHSysFv(sys__6SSHSys);
          return 0;
        }
        *(undefined4 *)&this->field_0x608 = *(undefined4 *)((int)a2 + 4);
        DiskChange__6SSHSysFi(sys__6SSHSys,*(undefined4 *)a2);
      }
      return 0xffffffff;
    }
  }
  else {
    if (0x7f < a0) {
      uVar10 = VectorOperation__FiP9_ParStack(a0,a2);
      return uVar10;
    }
    switch(a0) {
    case 0x70:
      iVar6 = GetWorldMapInfo__Fv();
      pbVar13 = (byte *)(iVar6 + 0xc + *puStack_10);
      iStack_16c = puStack_10[1];
      bVar4 = iStack_16c == 3;
      if (bVar4) {
        iStack_16c = 2;
      }
      uStack_170 = (uint)bVar4;
      *pbVar13 = *pbVar13 & 0xfc | (byte)iStack_16c & 3;
      *pbVar13 = *pbVar13 & 0xfb |
                 (byte)(((uint)(((ulong)*pbVar13 << 0x3d) >> 0x3f) | uStack_170) << 2);
      if (iStack_16c == 1) {
        *pbVar13 = *pbVar13 & 0xfb;
      }
      break;
    case 0x71:
      uVar12 = SetChrPosSaveState__Fi(0xffffffffffffffff);
      FieldCameraID__Fi(0xffffffffffffffff,uVar12);
      ResetSE__6CFieldFv(pCStack_40);
      WorldMapJump__12CFieldSocketFiiUi(m_socket__12CFieldSocket,*puStack_10,puStack_10[1],puStack_10[2]);
      ScriptSuspend__6CFieldFv(pCStack_40);
      return 7;
    case 0x72:
      ScriptSuspend__6CFieldFv(this);
      InvokeBattle__6CFieldFiiiiii
                (pCStack_40,1,*puStack_10,puStack_10[1],puStack_10[2],puStack_10[3],puStack_10[4]);
      return 7;
    case 0x73:
      iStack_174 = FindDTCInfo__FPCc(0x555a40);
      if (iStack_174 != 0) {
        puVar8 = (ushort *)GetDTCData__FP8_DTCINFOi(iStack_174,*puStack_10);
        ScriptSuspend__6CFieldFv(pCStack_40);
        InvokeBattle__6CFieldFiiiiii
                  (pCStack_40,(uint)(byte)puVar8[3],(uint)*puVar8,(uint)puVar8[1],puStack_10[1],
                   (uint)puVar8[2],1);
        return 7;
      }
      break;
    case 0x74:
      SetCamera__6CFieldFPfifi
                (this,*(float **)a2,*(int *)((int)a2 + 4),*(float *)((int)a2 + 8),
                 *(int *)((int)a2 + 0xc));
      break;
    case 0x75:
      SetCamera__6CFieldFPfiif
                (this,*(float **)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8),
                 *(float *)((int)a2 + 0xc));
      break;
    case 0x76:
      if (a1 < 0) {
        cVar5 = WaitCamera__6CFieldFv(this);
        if (cVar5 != '\0') {
          return 0xfffffff6;
        }
      }
      else {
        pfStack_178 = *(float **)((int)a2 + 4);
        pfStack_17c = *(float **)((int)a2 + 8);
        fStack_180 = *(float *)((int)a2 + 0xc);
        if (*(int *)a2 < 0) {
          cVar5 = WaitCamera__6CFieldFv(this);
          if (cVar5 != '\0') {
            return 0xfffffff6;
          }
        }
        else {
          SetCamera__6CFieldFiPfPff(this,*(int *)a2,pfStack_178,pfStack_17c,fStack_180);
        }
      }
      break;
    default:
      return 0x10;
    case 0x78:
      RestoreCamera__6CFieldFf(this,*(float *)a2);
      break;
    case 0x79:
      pcVar9 = TreasureControl__6CFieldFiii
                         (this,*(int *)a2,*(int *)((int)a2 + 4),*(int *)((int)a2 + 8));
      *puStack_10 = (uint)pcVar9;
      return 1;
    case 0x7a:
      uVar7 = SetLookPoint__6CFieldFiPffUiii
                        (this,*(int *)a2,*(float **)((int)a2 + 4),*(float *)((int)a2 + 8),
                         *(uint *)((int)a2 + 0xc),*(int *)((int)a2 + 0x10),*(int *)((int)a2 + 0x14))
      ;
      *puStack_10 = uVar7;
      return 1;
    case 0x7b:
      ClrLookPoint__6CFieldFi(this,*(int *)a2);
      break;
    case 0x7c:
      DspIcon__6CFieldFii(this,*(int *)a2,*(int *)((int)a2 + 4));
      break;
    case 0x7d:
      uStack_184 = *(undefined4 *)a2;
      iVar6 = *(int *)((int)a2 + 4);
      iVar3 = *(int *)((int)a2 + 8);
      if (iVar6 == 5) {
        uVar7 = *(undefined4 *)((int)a2 + 0xc);
        if (iVar3 < 0) {
          uVar7 = 0;
        }
        if (iVar3 == 0) {
          aiStack_1b8[4] = 0x40;
        }
        else {
          aiStack_1b8[4] = 0x3f;
        }
        uVar7 = InventoryChange__Fiii(aiStack_1b8[4],0,uVar7);
      }
      else if (iVar6 == 6) {
        if (iVar3 < 0) {
          uVar7 = InventoryChange__Fiii(0x3a,0,*(undefined4 *)((int)a2 + 0xc));
        }
        else {
          if (iVar3 == 0) {
            aiStack_1b8[3] = 0x3b;
          }
          else {
            aiStack_1b8[3] = 0x3a;
          }
          uVar7 = InventoryChange__Fiii(aiStack_1b8[3],0,*(undefined4 *)((int)a2 + 0xc));
        }
      }
      else {
        uVar1 = (&paramChgTbl)[iVar6];
        uVar7 = GetPCParam__10BtlSaveSecFii(uStack_184,uVar1);
        if (iVar3 == 0) {
          SetPCParam__10BtlSaveSecFiii(uStack_184,uVar1,puStack_10[3]);
        }
        else if (iVar3 == 1) {
          AddPCParam__10BtlSaveSecFiii(uStack_184,uVar1,puStack_10[3]);
        }
      }
      *puStack_10 = uVar7;
      return 1;
    case 0x7e:
      pfStack_188 = *(float **)((int)a2 + 4);
      iVar6 = *(int *)((int)a2 + 8);
      if (pfStack_188 == (float *)0x0) {
        if (iVar6 == -1) {
          uVar12 = ClrSavePoint__6CFieldFi(this,*(int *)a2);
          iVar6 = (int)uVar12;
        }
        else {
          pfStack_190 = (float *)GetEntryPoint__6CFieldFiRi(this,iVar6,&iStack_18c);
          if (pfStack_190 == (float *)0x0) {
            iVar6 = -1;
          }
          else {
            iVar6 = SetSavePoint__6CFieldFiPfi(pCStack_40,*puStack_10,pfStack_190,0);
          }
        }
      }
      else {
        iVar6 = SetSavePoint__6CFieldFiPfi(this,*(int *)a2,pfStack_188,iVar6);
      }
      *puStack_10 = iVar6;
      return 1;
    case 0x7f:
      if (-1 < a1) {
        iStack_194 = *(int *)a2;
        iVar6 = SpecialMenu__6CFieldFii(this,iStack_194,*(int *)((int)a2 + 4));
        if (iVar6 != 0) {
          Pause__7CScriptFi(fldScript__12CFieldSocket,1);
          return 0xffffffff;
        }
      }
    }
  }
  return 0;
}

/* JP: 0x004b04b0  CField::SetActiveFace(int)   [SetActiveFace__6CFieldFi]  size=0x28 */
void SetActiveFace__6CFieldFi(CField *this,int a0)

{
  this->field_0x6c1 = (char)a0;
  return;
}

/* JP: 0x004b04e0  CField::SetActiveName(int)   [SetActiveName__6CFieldFi]  size=0x28 */
void SetActiveName__6CFieldFi(CField *this,int a0)

{
  this->field_0x6c2 = (char)a0;
  return;
}

/* JP: 0x004b0510  CField::SetActiveWindow(int)   [SetActiveWindow__6CFieldFi]  size=0x28 */
void SetActiveWindow__6CFieldFi(CField *this,int a0)

{
  this->field_0x6c0 = (char)a0;
  return;
}

/* JP: 0x004b06b0  CField::SpecialMenu(int, int)   [SpecialMenu__6CFieldFii]  size=0x294 */
undefined4 SpecialMenu__6CFieldFii(CField *this,int a0,int a1)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  switch(a0 >> 8 & 0xf) {
  case 0:
    if (a0 == 2) {
      SetHelp__15SaveMenuSectionFs((short)a1);
    }
    else if (a0 == 3) {
      SetMenuFlag__15SaveMenuSectionFcc((char)a1,(char)((uint)a1 >> 8));
    }
    else {
      CommandMenu__12CFieldSocketFii(m_socket__12CFieldSocket,a0,a1);
      if (3 < a0) {
        return 1;
      }
    }
  default:
    uVar1 = 0;
    break;
  case 1:
    lVar2 = __nw__FUi(0x134);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = __ct__4shopFv(lVar2);
    }
    initialize__4shopFiPFiPv_vPv(uVar3,a1,0x4b0a20,this);
    *(int *)&this->field_0x708 = (int)uVar3;
    start__4shopFv(uVar3);
    Pause__6CFieldFi(this,0);
    uVar1 = 1;
    break;
  case 2:
    if (a1 == 1) {
      uVar3 = 5;
    }
    else {
      uVar3 = 0;
    }
    CommandMenu__12CFieldSocketFii(m_socket__12CFieldSocket,6,uVar3);
    uVar1 = 1;
    break;
  case 3:
    lVar2 = __nw__FUi(0x170);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = __ct__6tailorFv(lVar2);
    }
    initialize__6tailorFPFiPv_vPvi(uVar3,0x4b0b40,this,0);
    *(int *)&this->field_0x708 = (int)uVar3;
    start__6tailorFv(uVar3);
    Pause__6CFieldFi(this,0);
    uVar1 = 1;
    break;
  case 5:
    this->bFlags_18c = this->bFlags_18c & 0xfd | 2;
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x004b0a20  CField::cbShop(int, void*)   [cbShop__6CFieldFiPv]  size=0x11c */
void cbShop__6CFieldFiPv(CField *this,int a0,void *a1)

{
  if (this == (CField *)0x3) {
    Pause__6CFieldFi((CField *)a0,1);
    SetFFMode__3GsxFibi(0,1,2);
    SetInter30__3GsxFi(1);
  }
  else if (this == (CField *)0x2) {
    Dsp__6CFieldFv((CField *)a0);
    *(byte *)(a0 + 0x18d) = *(byte *)(a0 + 0x18d) & 0xf3 | 4;
  }
  else if (this == (CField *)0x1) {
    Clr__6CFieldFv((CField *)a0);
  }
  else if (this == (CField *)0x0) {
    if (sys__8FldTimer != 0) {
      Mask__8FldTimerFi(sys__8FldTimer,1,a1);
    }
    SetHalfVol__6CFieldFi((CField *)a0,1);
  }
  return;
}

/* JP: 0x004b0b40  CField::cbTailor(int, void*)   [cbTailor__6CFieldFiPv]  size=0x10c */
void cbTailor__6CFieldFiPv(CField *this,int a0,void *a1)

{
  if (this == (CField *)0x3) {
    Pause__6CFieldFi((CField *)a0,1);
    SetFFMode__3GsxFibi(0,1,2);
    SetInter30__3GsxFi(1);
  }
  else if (this == (CField *)0x2) {
    Dsp__6CFieldFv((CField *)a0);
    *(byte *)(a0 + 0x18d) = *(byte *)(a0 + 0x18d) & 0xf3 | 4;
  }
  else if (this == (CField *)0x1) {
    Clr__6CFieldFv((CField *)a0);
  }
  else if ((this == (CField *)0x0) && (sys__8FldTimer != 0)) {
    Mask__8FldTimerFi(sys__8FldTimer,1,a1);
  }
  return;
}

/* JP: 0x004b0ce0  CField::SetRing(int, int, int, int, int, const char*)   [SetRing__6CFieldFiiiiiPCc]  size=0x200 */
uint SetRing__6CFieldFiiiiiPCc(CField *this,int a0,int a1,int a2,int a3,int a4,char *a5)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  undefined1 *puVar4;
  byte bVar5;
  int iVar6;
  byte *apbStack_10 [4];
  
  puVar4 = &this->field_0x5b0;
  apbStack_10[0] = (byte *)a5;
  uVar1 = memset(puVar4,0,0x3c);
  *puVar4 = *puVar4 & 0xf8 | (byte)a0 & 7;
  *(int *)&this->field_0x5bc = a1;
  *(int *)&this->field_0x5c0 = a2;
  *(short *)&this->field_0x5b4 = (short)a3;
  *(short *)&this->field_0x5b6 = (short)a4;
  iVar6 = 0;
  uVar2 = 1;
  while( true ) {
    pbVar3 = apbStack_10[0] + 1;
    bVar5 = *apbStack_10[0];
    if (bVar5 == 0) break;
    apbStack_10[0] = pbVar3;
    if ((bVar5 != 0x20) && (bVar5 != 9)) {
      bVar5 = bVar5 & 0xdf;
      if (bVar5 == 0x45) {
        puVar4[iVar6 * 4 + 0x17] = puVar4[iVar6 * 4 + 0x17] & 0xc3 | (byte)((uVar2 & 0xf) << 2);
        uVar1 = GetNumber__FRPCc(apbStack_10);
        *(uint *)(puVar4 + iVar6 * 4 + 0x14) =
             *(uint *)(puVar4 + iVar6 * 4 + 0x14) & 0xfffc01ff | (uVar1 & 0x1ff) << 9;
        iVar6 = iVar6 + 1;
        uVar2 = 1;
      }
      else if (bVar5 == 0x53) {
        uVar1 = GetNumber__FRPCc(apbStack_10);
        *(ushort *)(puVar4 + iVar6 * 4 + 0x14) =
             *(ushort *)(puVar4 + iVar6 * 4 + 0x14) & 0xfe00 | (ushort)uVar1 & 0x1ff;
      }
      else if (bVar5 == 0x43) {
        uVar2 = GetNumber__FRPCc(apbStack_10);
        uVar1 = uVar2;
      }
    }
  }
  this->field_0x5b1 = (char)iVar6;
  this->field_0x5b3 = 2;
  return uVar1;
}

/* JP: 0x004b0ee0  CField::RingControl(int, int, int, int)   [RingControl__6CFieldFiiii]  size=0x48 */
void RingControl__6CFieldFiiii(CField *this,int a0,int a1,int a2,int a3)

{
  if (a0 == 1) {
    this->field_0x5b2 = 1;
  }
  return;
}

/* JP: 0x004b0f30  CField::cbRing(int, void*, void*)   [cbRing__6CFieldFiPvPv]  size=0xd0 */
undefined4 cbRing__6CFieldFiPvPv(CField *this,int a0,void *a1,void *a2)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)((int)a1 + 0x5b0);
  if (this == (CField *)0x200) {
    if (((ulong)*pbVar1 & 0x3f) >> 4 == 0) {
      Destruct__5JRingFb(*(undefined4 *)((int)a1 + 0x5f8),0,a1,a2);
      *(undefined4 *)((int)a1 + 0x5f8) = 0;
    }
  }
  else if (this == (CField *)0x80) {
    *(undefined4 *)((int)a1 + 0x5b8) = *(undefined4 *)a0;
    *pbVar1 = *pbVar1 & 0xf7 | 8;
  }
  return 1;
}

/* JP: 0x004b1000  CField::UpdateRing()   [UpdateRing__6CFieldFv]  size=0x524 */
void UpdateRing__6CFieldFv(CField *this)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  undefined8 uVar4;
  long lVar5;
  undefined1 *puVar6;
  ushort *puVar7;
  int iVar8;
  undefined4 uVar9;
  
  puVar6 = &this->field_0x5b0;
  if ((this->field_0x5b2 != '\0') || (1 < (byte)this->field_0x5b3)) {
    iVar3 = *(int *)&this->field_0x5f8;
    while (cVar1 = this->field_0x5b3, cVar1 != '\x04') {
      if (cVar1 == '\x03') {
        lVar5 = AutoLoadEndCheck__5JRingFv(iVar3);
        if (lVar5 == 0) goto LAB_004b1280;
        this->field_0x5b3 = 4;
        break;
      }
      if (cVar1 != '\x02') goto LAB_004b1280;
      if (iVar3 == 0) {
        lVar5 = __nw__FUi(0x5d0);
        uVar4 = 0;
        if (lVar5 != 0) {
          uVar4 = __ct__5JRingFsi(lVar5,0,0xd);
        }
        *(int *)&this->field_0x5f8 = (int)uVar4;
        SetPad__5JRingFP4CPad(this->pPad);
        SetRingPos__5JRingFff((float)(int)*(short *)&this->field_0x5b4,
                        (float)(int)*(short *)&this->field_0x5b6,uVar4);
        AutoLoadSet__5JRingFv(uVar4);
        this->field_0x5b3 = this->field_0x5b3 + '\x01';
        return;
      }
      this->field_0x5b3 = 4;
    }
    if ((*puVar6 & 7) == 1) {
      uVar9 = *(undefined4 *)&this->field_0x5c0;
    }
    else {
      uVar9 = 1;
    }
    SetEventRing__5JRingFibi(iVar3,*puVar6 & 7,0,uVar9);
    SetCallBack__5JRingFPFiPvPv_bPvUi(iVar3,0x4b0f30,this,0x280);
    SetRingPos__5JRingFff(0x43aaaaab,0x43600000,iVar3);
    bVar2 = this->field_0x5b1;
    puVar7 = (ushort *)&this->field_0x5c4;
    for (iVar8 = 0; iVar8 < (int)(uint)bVar2; iVar8 = iVar8 + 1) {
      AddEventRingArea__5JRingFssc(iVar3,*puVar7 & 0x1ff,
                      ((ushort)((ulong)((long)*(int *)puVar7 << 0x2e) >> 0x37) - (*puVar7 & 0x1ff))
                      + 1,(char)(((ulong)*(byte *)((int)puVar7 + 3) & 0x3f) >> 2));
      puVar7 = puVar7 + 2;
    }
    this->field_0x5b3 = 1;
LAB_004b1280:
    if (this->field_0x5b3 == '\x01') {
      cVar1 = this->field_0x5b2;
      if (cVar1 == '\x06') {
        lVar5 = isFaderBusy__12CFieldSocketFi(m_socket__12CFieldSocket,0);
        if (lVar5 == 0) {
          this->field_0x5b2 = 0;
          SetFFMode__3GsxFibi(0,1,2);
        }
      }
      else if (cVar1 == '\x05') {
        if (999 < *(uint *)&this->field_0x6e4) {
          if (sys__11CScrCapture != 0) {
            Delete__11CScrCaptureFv(sys__11CScrCapture);
            sys__11CScrCapture = 0;
          }
          Dsp__6CFieldFv(this);
          SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,0,6,300);
          this->field_0x5b2 = this->field_0x5b2 + '\x01';
        }
      }
      else if (cVar1 == '\x04') {
        if ((long)((ulong)(byte)*puVar6 << 0x3c) < 0) {
          *(undefined4 *)&this->field_0x6e4 = 0;
          this->field_0x5b2 = this->field_0x5b2 + '\x01';
        }
      }
      else if (cVar1 == '\x02') {
        SetFFMode__3GsxFibi(0,1,1);
        SetFader__12CFieldSocketFiii(m_socket__12CFieldSocket,0,7,300);
        SetRotSpeed__5JRingFfff((float)*(int *)&this->field_0x5bc * 0.001,0xbe19999a,0x3f800000,iVar3);
        if ((*puVar6 & 7) != 1) {
          SetEventRingAbnormal__5JRingFi(iVar3,*(undefined4 *)&this->field_0x5c0);
        }
        RingActive__5JRingFv(iVar3);
        this->field_0x5b2 = 4;
      }
      else if (cVar1 == '\x01') {
        Clr__6CFieldFv(this);
        iVar3 = sys__11CScrCapture;
        if (sys__11CScrCapture == 0) {
          lVar5 = __nw__FUi(0x24);
          iVar3 = 0;
          if (lVar5 != 0) {
            iVar3 = __ct__11CScrCaptureFv(lVar5);
          }
        }
        sys__11CScrCapture = iVar3;
        Create__11CScrCaptureFiiP9BufMemory(sys__11CScrCapture,0,0,0);
        SetLayer__11CScrCaptureFi(sys__11CScrCapture,10);
        this->field_0x5b2 = this->field_0x5b2 + '\x01';
      }
    }
  }
  return;
}

/* JP: 0x004b1530  CField::RingResult()   [RingResult__6CFieldFv]  size=0x60 */
undefined4 RingResult__6CFieldFv(CField *this)

{
  undefined4 uVar1;
  
  if ((this->field_0x5b2 == '\0') && ((long)((ulong)(byte)this->field_0x5b0 << 0x3c) < 0)) {
    uVar1 = *(undefined4 *)&this->field_0x5b8;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

/* JP: 0x004b1b70  CField::SetFieldData(int, int, int)   [SetFieldData__6CFieldFiii]  size=0x854 */
void SetFieldData__6CFieldFiii(CField *this,int a0,int a1,int a2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  undefined1 uVar4;
  uint uVar5;
  undefined4 uVar6;
  short asStack_c0 [16];
  short asStack_a0 [16];
  short asStack_80 [20];
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  CField *pCStack_40;
  int iStack_30;
  int iStack_20;
  uint uStack_10;
  
  bVar1 = (byte)a1;
  uVar4 = (undefined1)a2;
  pCStack_40 = this;
  iStack_30 = a0;
  iStack_20 = a1;
  uStack_10 = a2;
  switch(a0) {
  case 0:
    this->bFlags_18c = this->bFlags_18c & 0xe3 | (byte)((a1 & 7U) << 2);
    break;
  case 1:
    if (this->pEvent_boxes != (CFieldEvent *)0x0) {
      iStack_44 = GetEventBoxFromID__11CFieldEventFiPs(this->pEvent_boxes,a1,asStack_80);
      for (iVar3 = 0; iVar3 < iStack_44; iVar3 = iVar3 + 1) {
        iStack_48 = GetEventBox__11CFieldEventFi(pCStack_40->pEvent_boxes,(int)asStack_80[iVar3]);
        *(byte *)(iStack_48 + 8) = *(byte *)(iStack_48 + 8) & 0xf0 | ((byte)uStack_10 ^ 1) & 0xf;
      }
    }
    break;
  case 2:
    if (this->pEvent_boxes != (CFieldEvent *)0x0) {
      iStack_4c = GetEventBoxFromID__11CFieldEventFiPs(this->pEvent_boxes,a1,asStack_a0);
      for (iVar3 = 0; iVar3 < iStack_4c; iVar3 = iVar3 + 1) {
        iStack_50 = GetEventBox__11CFieldEventFi(pCStack_40->pEvent_boxes,(int)asStack_a0[iVar3]);
        *(byte *)(iStack_50 + 8) = *(byte *)(iStack_50 + 8) & 0xcf | (byte)((uStack_10 & 3) << 4);
      }
    }
    break;
  case 3:
    if (this->pCam_events != (CFieldEvent *)0x0) {
      iStack_54 = GetEventBoxFromGroup__11CFieldEventFiPs(this->pCam_events,a1,asStack_c0);
      for (iVar3 = 0; iVar3 < iStack_54; iVar3 = iVar3 + 1) {
        iStack_58 = GetEventBox__11CFieldEventFi(pCStack_40->pCam_events,(int)asStack_c0[iVar3]);
        *(byte *)(iStack_58 + 8) = *(byte *)(iStack_58 + 8) & 0xcf | (uStack_10 == 0) << 4;
      }
    }
    break;
  case 4:
    m_flags__12CFieldSocket = m_flags__12CFieldSocket & 0xdf | (byte)((a1 & 1U) << 5);
    break;
  case 5:
    SetEncountRate__6CFieldFi(this,a1);
    break;
  case 6:
    iVar3 = GetFieldBattleInfo__Fv();
    *(short *)(iVar3 + 2) = (short)iStack_20;
    break;
  case 7:
    iVar3 = GetFieldBattleInfo__Fv();
    *(short *)(iVar3 + 4) = (short)iStack_20;
    break;
  case 8:
    *(byte *)(sys__6SSHSys + 0x52) = bVar1;
    break;
  case 10:
    if (a1 == -1) {
      ClearBattleTeam__15SaveMenuSectionFc(0);
      ClearBattleTeam__15SaveMenuSectionFc(1);
      ClearBattleTeam__15SaveMenuSectionFc(2);
    }
    else {
      ClearBattleTeam__15SaveMenuSectionFc(bVar1);
    }
    break;
  case 0xb:
    uVar5 = a2 >> 0x10;
    if (a1 == -1) {
      JoinBattle__15SaveMenuSectionFccUc(uVar4,0,uVar5 & 0xff);
      JoinBattle__15SaveMenuSectionFccUc(uVar4,1,uVar5 & 0xff);
      JoinBattle__15SaveMenuSectionFccUc(uVar4,2,uVar5 & 0xff);
    }
    else {
      JoinBattle__15SaveMenuSectionFccUc(uVar4,bVar1,uVar5 & 0xff);
    }
    break;
  case 0xe:
    if (a2 == 1) {
      StartEffect__8CFieldBGFi(this->pBg,a1);
    }
    else if (a2 == 0) {
      StopEffect__8CFieldBGFi(this->pBg,a1);
    }
    break;
  case 0xf:
    SetGameOverType__12CFieldSocketFii(m_socket__12CFieldSocket,a1,a2);
    break;
  case 0x11:
    SetObstacle__9CFloorManFii(this->pFloor,a1,a2);
    break;
  case 0x12:
    GraveYardEnable__Fi(a1);
    break;
  case 0x13:
    SceneInit__Fi(a1);
    break;
  case 0x14:
    JoinParty__15SaveMenuSectionFcc(uVar4,bVar1);
    break;
  case 0x15:
    LeaveParty__15SaveMenuSectionFcc(uVar4,bVar1);
    break;
  case 0x16:
    SetLockParty__15SaveMenuSectionFUc(0);
    SetCurrentPartySet__15SaveMenuSectionFc((char)iStack_20);
    if ((int)uStack_10 >> 8 != 0) {
      SetBattleCount__15SaveMenuSectionFcc((char)(uStack_10 >> 8),(char)iStack_20);
    }
    SetLockParty__15SaveMenuSectionFUc(uStack_10 & 0xff);
    break;
  case 0x17:
    pbVar2 = (byte *)GetFldGSFlag__Fv();
    *pbVar2 = *pbVar2 & 0xfe | a1 == 0;
    if (iStack_20 == 2) {
      iVar3 = GetOption__15SaveMenuSectionFv();
      *(byte *)(iVar3 + 9) = *(byte *)(iVar3 + 9) & 0xf3;
    }
    break;
  case 0x18:
    this->bFlags_18e = this->bFlags_18e & 0xef | (byte)((a1 & 1U) << 4);
    break;
  case 0x19:
    if (-1 < a1) {
      SetYoahism__10BtlSaveSecFi((&joachismTbl)[a1]);
    }
    SetYoahismMode__10BtlSaveSecFb(uStack_10 != 0);
    break;
  case 0x1a:
    if ((a1 == 5) || (a1 == 6)) {
      if (a1 == 5) {
        if (a2 == 0) {
          uVar6 = 6;
        }
        else {
          uVar6 = 5;
        }
        SetPCModelNum__10BtlSaveSecFii(5,uVar6);
      }
      else {
        SetGranHatenaMode__10BtlSaveSecFb(a2 != 0);
      }
    }
    break;
  case 0x1e:
    this->bFlags_18f = this->bFlags_18f & 0xf8 | bVar1 & 7;
    break;
  case 0x1f:
    SetSaveID__15SaveMenuSectionFUi(a1);
    break;
  case 0x20:
    PCAddInit__10BtlSaveSecFi(a1);
    break;
  case 0x22:
    if (this->pFloor != (CFloorMan *)0x0) {
      SetRotY__9CFloorManFf(this->pFloor,(float)a1);
    }
  }
  return;
}

/* JP: 0x004b24e0  CField::GetFieldData(int, int, int)   [GetFieldData__6CFieldFiii]  size=0x36c */
long GetFieldData__6CFieldFiii(CField *this,int a0,int a1,int a2)

{
  int iVar1;
  ulong uVar2;
  short asStack_80 [16];
  short asStack_60 [16];
  CField *pCStack_40;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  uVar2 = 0xffffffffffffffff;
  pCStack_40 = this;
  iStack_30 = a0;
  iStack_20 = a1;
  iStack_10 = a2;
  if (a0 == 0x23) {
    iVar1 = KeyWaitStat__6CFieldFv(this);
    uVar2 = (ulong)iVar1;
  }
  else if (a0 == 0x21) {
    iVar1 = GetPartySet__15SaveMenuSectionFc((char)a1);
    uVar2 = 0xffffffffffffffff;
    if ((long)iStack_10 < (long)*(char *)(iVar1 + 0x11)) {
      uVar2 = (ulong)*(char *)(iVar1 + iStack_10 + 0x12);
    }
  }
  else if (a0 == 0x1f) {
    uVar2 = GetSaveID__15SaveMenuSectionFv();
  }
  else if (a0 == 0x1d) {
    uVar2 = GetTimer__7SysToolFv();
  }
  else if (a0 == 0x1c) {
    if ((&RDnumTbl)[a1] == '\0') {
      uVar2 = 0x555da0;
    }
    else {
      uVar2 = GetRegDat__9RegDatApiFiii((&RDnumTbl)[a1],a2,0xffffffffffffffff);
    }
  }
  else if (a0 == 0x1b) {
    uVar2 = InventoryChange__Fiii(0x20,a1,0);
  }
  else if (a0 == 0x10) {
    uVar2 = (ulong)this->nEntry_id;
  }
  else if (a0 == 0xc) {
    uVar2 = FieldNpcLibrary__Fii(a1,a2);
  }
  else if (a0 == 0xd) {
    uVar2 = (ulong)*(byte *)(sys__6SSHSys + 0x50);
  }
  else if (a0 == 9) {
    uVar2 = (ulong)*(char *)(sys__6SSHSys + 0x51);
  }
  else if (a0 == 2) {
    if ((this->pEvent_boxes != (CFieldEvent *)0x0) &&
       (iVar1 = GetEventBoxFromID__11CFieldEventFiPs(this->pEvent_boxes,a1,asStack_80), iVar1 != 0))
    {
      iVar1 = GetEventBox__11CFieldEventFi(pCStack_40->pEvent_boxes,(int)asStack_80[0]);
      uVar2 = ((ulong)*(byte *)(iVar1 + 8) & 0x3f) >> 4;
    }
  }
  else if (a0 == 1) {
    if ((this->pEvent_boxes != (CFieldEvent *)0x0) &&
       (iVar1 = GetEventBoxFromID__11CFieldEventFiPs(this->pEvent_boxes,a1,asStack_60), iVar1 != 0))
    {
      iVar1 = GetEventBox__11CFieldEventFi(pCStack_40->pEvent_boxes,(int)asStack_60[0]);
      uVar2 = (ulong)*(byte *)(iVar1 + 8) & 0xf ^ 1;
    }
  }
  else if (a0 == 0) {
    uVar2 = ((ulong)this->bFlags_18c & 0x1f) >> 2;
  }
  return uVar2;
}

/* JP: 0x004b28b0  CField::MapJump(const char*)   [MapJump__6CFieldFPCc]  size=0x128 */
void MapJump__6CFieldFPCc(CField *this,char *a0)

{
  long lVar1;
  char *pcStack_10;
  
  *(undefined2 *)&this->field_0x6fe = 0;
  *(undefined4 *)&this->field_0x704 = 0;
  *(undefined4 *)&this->field_0x700 = 0;
  if (fldScript__12CFieldSocket != 0) {
    ResetEvent__7CScriptFv(fldScript__12CFieldSocket);
    SetEventMagic__7CScriptFi(fldScript__12CFieldSocket,0);
  }
  this->field_0x6c3 = 0;
  SaveScriptRegister__12CFieldSocketFv(m_socket__12CFieldSocket);
  pcStack_10 = a0;
  if (a0 == (char *)0x1) {
    pcStack_10 = (char *)GetSavedMpsName__Fi(1);
  }
  this->bFlags_18d = this->bFlags_18d & 0xf3 | 4;
  if ((pcStack_10 == (char *)0x0) || (lVar1 = strcmp(pcStack_10,WORLDMAP_NAME), lVar1 != 0))
  {
    LoadMPS__12CFieldSocketFPCc(m_socket__12CFieldSocket,pcStack_10);
  }
  else {
    SetChrPosSaveState__Fi(0xffffffffffffffff);
    WorldMapJump__12CFieldSocketFiiUi(m_socket__12CFieldSocket,0xffffffffffffffff,0xffffffffffffffff,0);
  }
  return;
}

/* JP: 0x004b29e0  CField::MapJumpA(const char*, int)   [MapJumpA__6CFieldFPCci]  size=0x124 */
void MapJumpA__6CFieldFPCci(CField *this,char *a0,int a1)

{
  int iVar1;
  long lVar2;
  
  this->nEntry_id = (short)a1;
  SetChrPosSaveState__Fi(0xffffffffffffffff);
  FieldCameraID__Fi(0xffffffffffffffff);
  this->bFlags_18e = this->bFlags_18e & 0xfc | 1;
  MapJump__6CFieldFPCc(this,a0);
  *(undefined2 *)&this->field_0x6fe = *(undefined2 *)&this->field_0x6fc;
  *(undefined4 *)&this->field_0x700 = *(undefined4 *)&this->field_0x6f4;
  *(undefined4 *)&this->field_0x704 = *(undefined4 *)&this->field_0x6f8;
  iVar1 = GetCtrlModel__6CFieldFv(this);
  if (iVar1 == 0) {
    *(undefined4 *)&this->field_0x704 = 0;
    *(undefined4 *)&this->field_0x700 = 0;
  }
  else {
    lVar2 = isManual__11CFieldModelFv(iVar1);
    if (lVar2 == 0) {
      *(undefined4 *)&this->field_0x700 = *(undefined4 *)&this->field_0x6ec;
      *(undefined4 *)&this->field_0x704 = *(undefined4 *)&this->field_0x6f0;
    }
  }
  return;
}

/* JP: 0x004b2b50  CField::LoadMotionCB(unsigned int, unsigned int)   [LoadMotionCB__6CFieldFUiUi]  size=0x38 */
void LoadMotionCB__6CFieldFUiUi(CField *this,uint a0,uint a1)

{
  CallEvent__7CScriptFUiiP9_ParStackPi(fldScript__12CFieldSocket,a1,0,0,0);
  return;
}

/* JP: 0x004b2b90  CField::CharPathEvent(CFieldModel*, unsigned int, int)   [CharPathEvent__6CFieldFP11CFieldModelUii]  size=0xc8 */
int CharPathEvent__6CFieldFP11CFieldModelUii(CField *this,void *a0,uint a1,int a2)

{
  int iVar1;
  undefined4 uVar2;
  int a4;
  
  iVar1 = isLoadBusy__6CFieldFv(this);
  if (iVar1 == 0) {
    for (a4 = 0; a4 < (int)(uint)this->bModel_count; a4 = a4 + 1) {
      if (a0 == this->aModels[a4]) {
        uVar2 = SetFieldEvent__6CFieldFiUiiii(this,4,a1,a2,0,a4);
        return uVar2;
      }
    }
  }
  return iVar1;
}

/* JP: 0x004b2c60  CField::SetFieldEvent(int, unsigned int, int, int, int)   [SetFieldEvent__6CFieldFiUiiii]  size=0x100 */
undefined4 SetFieldEvent__6CFieldFiUiiii(CField *this,int a0,uint a1,int a2,int a3,int a4)

{
  bool bVar1;
  undefined4 in_v0_lo;
  uint uVar2;
  
  if (((ulong)this->bFlags_18d & 0xf) >> 2 == 0) {
    uVar2 = GetEventMagic__7CScriptFv(fldScript__12CFieldSocket);
    bVar1 = false;
    if (((((int)uVar2 >> 8 & 0xffU) == 0xc2) && ((uVar2 & 0xff) != 1)) && (a0 == 1)) {
      bVar1 = true;
    }
    if (bVar1) {
      in_v0_lo = AddDelayEvent__6CFieldFiUiiii(this,a0,a1,a2,a3,a4);
    }
    else {
      in_v0_lo = CallFieldEvent__6CFieldFiUiii(this,a0,a1,a2,a4);
    }
  }
  return in_v0_lo;
}

/* JP: 0x004b2d60  CField::AddDelayEvent(int, unsigned int, int, int, int)   [AddDelayEvent__6CFieldFiUiiii]  size=0x110 */
undefined4 AddDelayEvent__6CFieldFiUiiii(CField *this,int a0,uint a1,int a2,int a3,int a4)

{
  byte bVar1;
  undefined4 in_v0_lo;
  int iVar2;
  
  if ((byte)this->field_0x6c3 < 4) {
    if (a3 != 0) {
      for (iVar2 = 0; iVar2 < (int)(uint)(byte)this->field_0x6c3; iVar2 = iVar2 + 1) {
        if ((uint)(byte)(&this->field_0x3d4)[iVar2 * 8] == a2) {
          return in_v0_lo;
        }
      }
    }
    bVar1 = this->field_0x6c3;
    this->field_0x6c3 = bVar1 + 1;
    *(uint *)(&this->field_0x3d0 + (uint)bVar1 * 8) = a1;
    (&this->field_0x3d4)[(uint)bVar1 * 8] = (char)a2;
    (&this->field_0x3d5)[(uint)bVar1 * 8] = (char)a0;
    *(short *)(&this->field_0x3d6 + (uint)bVar1 * 8) = (short)a4;
    this->field_0x6c3 = this->field_0x6c3 + '\x01';
  }
  return in_v0_lo;
}

/* JP: 0x004b2e70  CField::UpdateDelayEvent()   [UpdateDelayEvent__6CFieldFv]  size=0xe8 */
void UpdateDelayEvent__6CFieldFv(CField *this)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  
  if (((this->field_0x6c3 != '\0') && (*(int *)&this->field_0x6c4 != 0)) &&
     (iVar3 = GetEventMagic__7CScriptFv(fldScript__12CFieldSocket), (iVar3 >> 8 & 0xffU) != 0xc2)) {
    cVar1 = this->field_0x6c3;
    this->field_0x6c3 = cVar1 + -1;
    bVar2 = cVar1 - 1;
    CallFieldEvent__6CFieldFiUiii
              (this,(uint)(byte)(&this->field_0x3d5)[(uint)bVar2 * 8],
               *(uint *)(&this->field_0x3d0 + (uint)bVar2 * 8),
               (uint)(byte)(&this->field_0x3d4)[(uint)bVar2 * 8],
               (uint)*(ushort *)(&this->field_0x3d6 + (uint)bVar2 * 8));
    memcpy(&this->field_0x3d0,&this->field_0x3d8,0x18);
  }
  return;
}

/* JP: 0x004b2f60  CField::CallFieldEvent(int, unsigned int, int, int)   [CallFieldEvent__6CFieldFiUiii]  size=0xbc */
undefined4 CallFieldEvent__6CFieldFiUiii(CField *this,int a0,uint a1,int a2,int a3)

{
  undefined4 uVar1;
  long lVar2;
  int iStack_60;
  int iStack_5c;
  CField *pCStack_50;
  int iStack_40;
  uint uStack_30;
  int iStack_20;
  int iStack_10;
  
  uVar1 = 1;
  if ((a0 == 4) || (a0 == 2)) {
    uVar1 = 2;
    iStack_5c = a3;
  }
  *(undefined4 *)&this->field_0x6c4 = 0;
  iStack_60 = a2;
  pCStack_50 = this;
  iStack_40 = a0;
  uStack_30 = a1;
  iStack_20 = a2;
  iStack_10 = a3;
  lVar2 = CallEvent__7CScriptFUiiP9_ParStackPi(fldScript__12CFieldSocket,a1,uVar1,&iStack_60,&this->field_0x6c4);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = SetEventMagic__7CScriptFi(fldScript__12CFieldSocket,iStack_40 + 0xc200);
  }
  return uVar1;
}

/* JP: 0x004b3020  CField::LoadCharacter(int, int, unsigned int)   [LoadCharacter__6CFieldFiiUi]  size=0x5c */
undefined4 LoadCharacter__6CFieldFiiUi(CField *this,int a0,int a1,uint a2)

{
  undefined4 uVar1;
  char acStack_50 [16];
  CField *pCStack_40;
  int iStack_30;
  int iStack_20;
  uint uStack_10;
  
  pCStack_40 = this;
  iStack_30 = a0;
  iStack_20 = a1;
  uStack_10 = a2;
  sprintf(acStack_50,0x555da8,a1);
  uVar1 = LoadCharacter__6CFieldFiPCciUi(pCStack_40,iStack_30,acStack_50,iStack_20,uStack_10);
  return uVar1;
}

/* JP: 0x004b3080  CField::LoadModelCB(CFieldModel*)   [LoadModelCB__6CFieldFP11CFieldModel]  size=0x50 */
void LoadModelCB__6CFieldFP11CFieldModel(CField *this,void *a0)

{
  void *pvVar1;
  
  pvVar1 = (void *)GetCtrlModel__6CFieldFv(this);
  if (pvVar1 == a0) {
    UpdateSavePoint__6CFieldFv(this);
    UpdateWarpPoint__6CFieldFv(this);
  }
  return;
}

/* JP: 0x004b30d0  CField::LoadCharacter(int, const char*, int, unsigned int)   [LoadCharacter__6CFieldFiPCciUi]  size=0x290 */
undefined4 LoadCharacter__6CFieldFiPCciUi(CField *this,int a0,char *a1,int a2,uint a3)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  void *pvVar4;
  
  if ((int)(uint)this->bModel_count <= a0) {
    this->bModel_count = (char)a0 + 1;
  }
  pvVar4 = this->aModels[a0];
  if (((pvVar4 == (void *)0x0) || (a2 == -1)) || ((uint)*(ushort *)((int)pvVar4 + 0x8e) != a2)) {
    if (pvVar4 != (void *)0x0) {
      if ((long)a0 == (long)(char)this->field_0x6cc) {
        AutoDelLight__6CFieldFv(this);
      }
      CharRemoveItem__6CFieldFiPCc(this,a0,(char *)0x0);
      Delete__11CFieldModelFv(pvVar4);
      if ((long)a0 == (long)(char)this->field_0x6cc) {
        UpdateSavePoint__6CFieldFv(this);
        UpdateWarpPoint__6CFieldFv(this);
      }
    }
    lVar2 = __nw__FUi(0x2e0);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = __ct__11CFieldModelFv(lVar2);
    }
    pvVar4 = (void *)uVar3;
    this->aModels[a0] = pvVar4;
    *(short *)((int)pvVar4 + 0x8e) = (short)a2;
    *(uint *)((int)pvVar4 + 0xc0) = a3;
    Reset__11CFieldModelFi(uVar3,(long)a0 == (long)(char)this->field_0x6cc);
    uVar1 = LoadModel__11CFieldModelFPCc(uVar3,a1);
  }
  else {
    ClrCharacter__6CFieldFii(this,a0,0);
    CharRemoveItem__6CFieldFiPCc(this,a0,(char *)0x0);
    if ((*(char *)((int)pvVar4 + 0xfc) != -1) && (*(int *)((int)pvVar4 + 0xf4) != 0)) {
      DetachModel__6CFieldFii(this,(uint)*(byte *)((int)pvVar4 + 0xfc),a0);
    }
    *(undefined4 *)((int)pvVar4 + 0xf4) = 0;
    *(undefined1 *)((int)pvVar4 + 0xfc) = 0xff;
    Reset__11CFieldModelFi(pvVar4,a0 == 0);
    *(uint *)((int)pvVar4 + 0xc0) = a3;
    uVar1 = SetCmd__11CFieldModelFi(pvVar4,1);
    *(byte *)((int)pvVar4 + 0x8a) = *(byte *)((int)pvVar4 + 0x8a) & 0xfe | 1;
  }
  return uVar1;
}

/* JP: 0x004b3360  CField::UnloadCharacter(int)   [UnloadCharacter__6CFieldFi]  size=0x180 */
void UnloadCharacter__6CFieldFi(CField *this,int a0)

{
  void *pvVar1;
  long lVar2;
  int a0_00;
  long lVar3;
  long lVar4;
  
  lVar3 = (long)a0;
  lVar4 = lVar3;
  if (a0 < 0) {
    lVar3 = 0;
    lVar4 = (long)(int)(this->bModel_count - 1);
  }
  if (a0 == -2) {
    lVar3 = 1;
  }
  while (lVar3 <= lVar4) {
    a0_00 = (int)lVar3;
    pvVar1 = this->aModels[a0_00];
    if ((pvVar1 != (void *)0x0) &&
       ((a0 != -3 || (lVar2 = isDsp__11CFieldModelFv(pvVar1), lVar2 == 0)))) {
      if ((*(char *)((int)pvVar1 + 0xb0) != '\0') && (this->pNavimap != (void *)0x0)) {
        RemoveItem__8CNaviMapFi(this->pNavimap,*(byte *)((int)pvVar1 + 0xb0) - 1);
      }
      CharRemoveItem__6CFieldFiPCc(this,a0_00,(char *)0x0);
      Delete__11CFieldModelFv(pvVar1);
      SetCmd__11CFieldModelFi(pvVar1,2);
      this->aModels[a0_00] = (void *)0x0;
      if (lVar3 == (char)this->field_0x6cc) {
        UpdateSavePoint__6CFieldFv(this);
        UpdateWarpPoint__6CFieldFv(this);
      }
    }
    lVar3 = (long)(a0_00 + 1);
  }
  return;
}

/* JP: 0x004b34e0  CField::DispCharacterEP(int, int, int, int, const char*)   [DispCharacterEP__6CFieldFiiiiPCc]  size=0x1bc */
undefined4 DispCharacterEP__6CFieldFiiiiPCc(CField *this,int a0,int a1,int a2,int a3,char *a4)

{
  int iVar1;
  FVector *a2_00;
  undefined4 uVar2;
  long lVar3;
  int a1_00;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [28];
  int iStack_64;
  CField *pCStack_60;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  char *pcStack_10;
  
  iStack_64 = -1;
  pCStack_60 = this;
  iStack_50 = a0;
  iStack_40 = a1;
  iStack_30 = a2;
  iStack_20 = a3;
  pcStack_10 = a4;
  __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_80);
  a1_00 = 0;
  if (-1 < iStack_40) {
    a1_00 = 2;
  }
  if ((iStack_40 == -1) && (pCStack_60->nEntry_id != -1)) {
    iStack_40 = (int)pCStack_60->nEntry_id;
  }
  if (iStack_40 < 0) {
    __ct__7FVectorFv(auStack_90);
    lVar3 = RestoreChrPos__FiP7FVector(iStack_50,auStack_90);
    if (-1 < lVar3) {
      ClrChrPosSave__Fi(iStack_50);
      __as__7FVectorFRC7FVector(auStack_80,auStack_90);
      iStack_64 = (int)lVar3;
      a1_00 = 1;
    }
    if (iStack_40 == -2) {
      a1_00 = 1;
    }
  }
  else {
    iVar1 = GetEntryPoint__6CFieldFiRi(pCStack_60,iStack_40,&iStack_64);
    if ((-1 < iStack_64) && (memcpy(auStack_80,iVar1,0xc), a1_00 == 0)) {
      a1_00 = 1;
    }
  }
  a2_00 = (FVector *)__ct__7FVectorFRC7FVector(auStack_a0,auStack_80);
  uVar2 = DispCharacter__6CFieldFii7FVectoriiiPCc
                    (pCStack_60,iStack_50,a1_00,a2_00,iStack_64,iStack_30,iStack_20,pcStack_10);
  return uVar2;
}

/* JP: 0x004b36a0  CField::DispCharacter(int, int, FVector, int, int, int, const char*)   [DispCharacter__6CFieldFii7FVectoriiiPCc]  size=0x3fc */
undefined4
DispCharacter__6CFieldFii7FVectoriiiPCc
          (CField *this,int a0,int a1,FVector *a2,int a3,int a4,int a5,char *a6)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  long in_v0;
  undefined8 uVar6;
  undefined8 uVar7;
  long lVar8;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  CField *pCStack_80;
  int iStack_70;
  int iStack_60;
  FVector *pFStack_50;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  char *pcStack_10;
  
  pvVar1 = this->aModels[a0];
  if ((pvVar1 == (void *)0x0) ||
     (pCStack_80 = this, iStack_70 = a0, iStack_60 = a1, pFStack_50 = a2, iStack_40 = a3,
     iStack_30 = a4, iStack_20 = a5, pcStack_10 = a6, in_v0 = isEmpty__11CFieldModelFv(pvVar1),
     in_v0 != 0)) {
    uVar5 = (undefined4)in_v0;
  }
  else {
    if (iStack_60 != 0) {
      __ct__7FVectorFv(auStack_90);
      lVar8 = -1;
      if (iStack_60 == 1) {
        if (((long)iStack_70 == (long)(char)pCStack_80->field_0x6cc) &&
           (pCStack_80->nEntry_id == -2)) {
          lVar8 = GetSavedChrPos__FPf(auStack_90);
          pCStack_80->nEntry_id = -1;
          if (-1 < lVar8) {
            iStack_40 = (int)lVar8;
            __as__7FVectorFRC7FVector(pFStack_50,auStack_90);
          }
        }
        if ((lVar8 < 0) && (lVar8 = RestoreChrPos__FiP7FVector(iStack_70,auStack_90), -1 < lVar8)) {
          ClrChrPosSave__Fi(iStack_70);
          __as__7FVectorFRC7FVector(pFStack_50,auStack_90);
          iStack_40 = (int)lVar8;
        }
      }
      uVar6 = __ct__7FVectorFRC7FVector(auStack_a0,pFStack_50);
      SetPos__11CFieldModelF7FVectorb(pvVar1,uVar6,0);
      SetDir__11CFieldModelFiii(pvVar1,iStack_40,2,0);
    }
    iVar3 = 0;
    iVar2 = 0;
    if (*(char *)((int)pvVar1 + 0xfd) != -1) {
      iVar2 = GetModel__6CFieldFi(pCStack_80,(uint)*(byte *)((int)pvVar1 + 0xfd));
    }
    if (*(char *)((int)pvVar1 + 0xfe) != -1) {
      iVar3 = GetModel__6CFieldFi(pCStack_80,(uint)*(byte *)((int)pvVar1 + 0xfe));
    }
    uVar6 = LayerMan_GetLayer__Fi(3);
    uVar7 = LayerMan_GetLayer__Fi(4);
    DispModel__11CFieldModelFiii(pvVar1,uVar6,uVar7,iStack_20);
    if (iVar2 != 0) {
      DispModel__11CFieldModelFiii(iVar2,uVar6,uVar7,iStack_20);
    }
    if (iVar3 != 0) {
      DispModel__11CFieldModelFiii(iVar3,uVar6,uVar7,iStack_20);
    }
    iVar4 = GetShadowCtrl__8CFieldBGFb(pCStack_80->pBg,false);
    if (iVar4 != 0) {
      DispShadow__11CFieldModelFP13ShadowControl(pvVar1,iVar4);
      if (iVar2 != 0) {
        DispShadow__11CFieldModelFP13ShadowControl(iVar2,iVar4);
      }
      if (iVar3 != 0) {
        DispShadow__11CFieldModelFP13ShadowControl(iVar3,iVar4);
      }
    }
    if ((0 < iStack_30) || (pcStack_10 != (char *)0x0)) {
      *(byte *)((int)pvVar1 + 0x81) = *(byte *)((int)pvVar1 + 0x81) & 0xdf;
      if (pcStack_10 == (char *)0x0) {
        SetMotion__11CFieldModelFi(pvVar1,iStack_30);
      }
      else {
        SetMotion__11CFieldModelFPCc(pvVar1,pcStack_10);
      }
    }
    uVar5 = Update__11CFieldModelFf(0,pvVar1);
    if ((long)iStack_70 == (long)(char)pCStack_80->field_0x6cc) {
      GetWorldPos__11CFieldModelFv(auStack_b0,pvVar1);
      uVar5 = __as__7FVectorFRC7FVector(&pCStack_80->player_pos,auStack_b0);
      m_pCAMOLD__6CField = 0;
      m_pCAMDAT__6CField = 0;
      CameraUpdate__6CFieldFf(pCStack_80,0.0);
      UpdateSavePoint__6CFieldFv(pCStack_80);
      UpdateWarpPoint__6CFieldFv(pCStack_80);
    }
  }
  return uVar5;
}

/* JP: 0x004b3aa0  CField::ClrCharacter(int, int)   [ClrCharacter__6CFieldFii]  size=0xe4 */
void ClrCharacter__6CFieldFii(CField *this,int a0,int a1)

{
  void *pvVar1;
  undefined4 uVar2;
  long lVar3;
  
  pvVar1 = this->aModels[a0];
  if ((pvVar1 != (void *)0x0) && (lVar3 = isEmpty__11CFieldModelFv(pvVar1), lVar3 == 0)) {
    Clear__11CFieldModelFi(pvVar1,a1);
    if (*(char *)((int)pvVar1 + 0xfd) != -1) {
      uVar2 = GetModel__6CFieldFi(this,(uint)*(byte *)((int)pvVar1 + 0xfd));
      Clear__11CFieldModelFi(uVar2,a1);
    }
    if (*(char *)((int)pvVar1 + 0xfe) != -1) {
      uVar2 = GetModel__6CFieldFi(this,(uint)*(byte *)((int)pvVar1 + 0xfe));
      Clear__11CFieldModelFi(uVar2,a1);
    }
  }
  return;
}

/* JP: 0x004b3b90  CField::WaitCharacterEx(int, int)   [WaitCharacterEx__6CFieldFii]  size=0x178 */
undefined4 WaitCharacterEx__6CFieldFii(CField *this,int a0,int a1)

{
  void *pvVar1;
  long lVar2;
  uint uVar3;
  int iStack_20;
  
  if (a0 < 0) {
    uVar3 = (uint)this->bModel_count;
    iStack_20 = 0;
  }
  else {
    uVar3 = a0 + 1;
    iStack_20 = a0;
  }
  do {
    if ((int)uVar3 <= iStack_20) {
      return 1;
    }
    pvVar1 = this->aModels[iStack_20];
    if (pvVar1 != (void *)0x0) {
      if (a1 == 2) {
        if ((-1 < (long)((ulong)*(byte *)((int)pvVar1 + 0x8a) << 0x3d)) &&
           ((lVar2 = isDsp__11CFieldModelFv(pvVar1), lVar2 != 0 ||
            (((ulong)*(byte *)((int)pvVar1 + 0x84) & 0x3f) >> 4 != 0)))) {
          return 0;
        }
      }
      else if (a1 == 1) {
        if (((*(byte *)((int)pvVar1 + 0x8a) & 1) == 0) && ((*(byte *)((int)pvVar1 + 0x80) & 3) != 0)
           ) {
          return 0;
        }
      }
      else if ((a1 == 0) && (lVar2 = isMove__11CFieldModelFv(pvVar1), lVar2 != 0)) {
        return 0;
      }
    }
    iStack_20 = iStack_20 + 1;
  } while( true );
}

/* JP: 0x004b3dd0  CField::DetachModel(int, int)   [DetachModel__6CFieldFii]  size=0x220 */
void DetachModel__6CFieldFii(CField *this,int a0,int a1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  float fVar6;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [4];
  float fStack_4c;
  float fStack_34;
  CField *pCStack_30;
  uint uStack_20;
  uint uStack_10;
  
  iVar5 = -1;
  pCStack_30 = this;
  uStack_20 = a0;
  uStack_10 = a1;
  iVar1 = GetModel__6CFieldFi(this,a1);
  if (uStack_20 != 0xff) {
    if ((uStack_20 & 0x80) == 0) {
      iVar2 = GetModel__6CFieldFi(pCStack_30,uStack_20);
      lVar3 = (long)iVar2;
    }
    else {
      lVar3 = GetBGModel__6CFieldFi(pCStack_30,uStack_20);
    }
    CalcMatrix__11CFieldModelFv(lVar3);
    iVar2 = (int)lVar3;
    if (*(byte *)(iVar2 + 0xfd) == uStack_10) {
      iVar5 = 1;
    }
    if (*(byte *)(iVar2 + 0xfe) == uStack_10) {
      iVar5 = 2;
    }
    if (-1 < iVar5) {
      *(undefined1 *)(iVar2 + iVar5 + 0xfc) = 0xff;
    }
    fVar6 = (float)GetRotY__11CFieldModelFv(lVar3);
    fStack_34 = (float)GetRotY__11CFieldModelFv(iVar1);
    fStack_34 = fVar6 + fStack_34;
    clipRadian__FRf(&fStack_34);
    __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_50);
    fStack_4c = fStack_34;
    SetDir__11CFieldModelFR7FVectorii(iVar1,auStack_50,0,3);
  }
  if (*(int *)(iVar1 + 0xf4) != 0) {
    GetWorldPos__11CFieldModelFv(auStack_60,iVar1);
    unChainModel__5FrameFv(*(undefined4 *)(iVar1 + 0xf4));
    uVar4 = __ct__7FVectorFRC7FVector(auStack_70,auStack_60);
    SetPos__11CFieldModelF7FVectorb(iVar1,uVar4,1);
    lVar3 = isFloorChk__11CFieldModelFv(iVar1);
    if ((lVar3 != 0) && (lVar3 = isDsp__11CFieldModelFv(iVar1), lVar3 != 0)) {
      FloorChk__11CFieldModelFv(iVar1);
    }
    CalcMatrix__11CFieldModelFv(iVar1);
  }
  *(undefined4 *)(iVar1 + 0xf4) = 0;
  *(undefined1 *)(iVar1 + 0xfc) = 0xff;
  return;
}

/* JP: 0x004b4130  CField::CharAddItem(int, int, const char*, int)   [CharAddItem__6CFieldFiiPCci]  size=0x278 */
int CharAddItem__6CFieldFiiPCci(CField *this,int a0,int a1,char *a2,int a3)

{
  int iVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [4];
  undefined4 uStack_6c;
  undefined1 auStack_60 [16];
  CField *pCStack_50;
  int iStack_40;
  int iStack_30;
  char *pcStack_20;
  int iStack_10;
  
  pCStack_50 = this;
  iStack_40 = a0;
  iStack_30 = a1;
  pcStack_20 = a2;
  iStack_10 = a3;
  if ((a0 & 0x80U) == 0) {
    iVar2 = GetModel__6CFieldFi(this,a0);
    lVar3 = (long)iVar2;
  }
  else {
    lVar3 = GetBGModel__6CFieldFi(this,a0);
    if (iStack_30 < 0) {
      lVar3 = CharRemoveItem__6CFieldFiPCc(pCStack_50,iStack_40,(char *)0x0);
      return (int)lVar3;
    }
  }
  iVar1 = GetModel__6CFieldFi(pCStack_50,iStack_30);
  iVar2 = iVar1;
  if ((lVar3 != 0) && (iVar1 != 0)) {
    DetachModel__6CFieldFii(pCStack_50,(uint)*(byte *)(iVar1 + 0xfc),iStack_30);
    lVar4 = FindFrame__FP11CFieldModelPCc(lVar3,pcStack_20);
    iVar2 = 0;
    if (lVar4 != 0) {
      __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_60);
      __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_70);
      if (iStack_10 != 0) {
        getWorldPos__5FrameFi(auStack_80,lVar4,m_Env__8VIF1Prim & 1);
        __as__7FVectorFRC7FVector(auStack_60,auStack_80);
        uVar6 = GetRotY__11CFieldModelFv(lVar3);
        uStack_6c = CalcStandParent__FR7FVectorP11CFieldModelf(uVar6,auStack_60,iVar1);
      }
      SetDir__11CFieldModelFR7FVectorii(iVar1,auStack_70,0,3);
      uVar5 = __ct__7FVectorFRC7FVector(auStack_90,auStack_60);
      SetPos__11CFieldModelF7FVectorb(iVar1,uVar5,1);
      unChainModel__5FrameFv(lVar4);
      uVar5 = GetBaseModel__11CFieldModelFv(iVar1);
      chainModel__5FrameFP5Model(lVar4,uVar5);
      *(int *)(iVar1 + 0xf4) = (int)lVar4;
      iVar2 = CalcMatrix__11CFieldModelFv(iVar1);
      *(char *)(iVar1 + 0xfc) = (char)iStack_40;
      for (iVar1 = 1; iVar1 < 3; iVar1 = iVar1 + 1) {
        if (*(char *)((int)lVar3 + iVar1 + 0xfc) == -1) {
          *(char *)((int)lVar3 + iVar1 + 0xfc) = (char)iStack_30;
          return iVar2;
        }
      }
    }
  }
  return iVar2;
}

/* JP: 0x004b43b0  CField::CharRemoveItem(int, const char*)   [CharRemoveItem__6CFieldFiPCc]  size=0x158 */
long CharRemoveItem__6CFieldFiPCc(CField *this,int a0,char *a1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  ulong uVar6;
  
  uVar6 = 0xffffffffffffffff;
  if ((a0 & 0x80U) == 0) {
    iVar2 = GetModel__6CFieldFi(this,a0);
    lVar4 = (long)iVar2;
  }
  else {
    lVar4 = GetBGModel__6CFieldFi(this,a0);
  }
  if (lVar4 == 0) {
    uVar6 = 0xffffffffffffffff;
  }
  else {
    iVar2 = FindFrame__FP11CFieldModelPCc(lVar4,a1);
    for (iVar5 = 1; iVar5 < 3; iVar5 = iVar5 + 1) {
      bVar1 = *(byte *)((int)lVar4 + iVar5 + 0xfc);
      if ((((ulong)bVar1 != 0xff) &&
          (iVar3 = GetModel__6CFieldFi(this,(uint)bVar1), *(int *)(iVar3 + 0xf4) != 0)) &&
         ((iVar2 == 0 || (*(int *)(iVar3 + 0xf4) == iVar2)))) {
        DetachModel__6CFieldFii(this,a0,(uint)bVar1);
        uVar6 = (ulong)bVar1;
      }
    }
  }
  return uVar6;
}

/* JP: 0x004b4510  CField::SetMotion(int, int, int)   [SetMotion__6CFieldFiii]  size=0x74 */
void SetMotion__6CFieldFiii(CField *this,int a0,int a1,int a2)

{
  void *pvVar1;
  long lVar2;
  
  pvVar1 = this->aModels[a0];
  if ((pvVar1 != (void *)0x0) && (lVar2 = isEmpty__11CFieldModelFv(pvVar1), lVar2 == 0)) {
    SetMotion__11CFieldModelFii(pvVar1,a1,a2);
  }
  return;
}

/* JP: 0x004b4590  CField::SetBGMotion(int, const char*, const char*)   [SetBGMotion__6CFieldFiPCcPCc]  size=0x120 */
void SetBGMotion__6CFieldFiPCcPCc(CField *this,int a0,char *a1,char *a2)

{
  char *pcVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  
  lVar2 = GetBGModel__6CFieldFi(this,a0);
  if ((lVar2 != 0) && (lVar3 = isEmpty__11CFieldModelFv(lVar2), lVar3 == 0)) {
    iVar4 = (int)lVar2;
    *(byte *)(iVar4 + 0x8a) = *(byte *)(iVar4 + 0x8a) & 0xbf | 0x40;
    *(byte *)(iVar4 + 0x81) = *(byte *)(iVar4 + 0x81) & 0xdf;
    pcVar1 = a1;
    if (a2 != (char *)0x0) {
      pcVar1 = a2;
    }
    SetLastMotion__11CFieldModelFPCc(lVar2,pcVar1);
    lVar3 = SetMotion__11CFieldModelFPCc(lVar2,a1);
    if (lVar3 != 0) {
      SetCmd__11CFieldModelFi(lVar2,7);
      *(byte *)(iVar4 + 0x8a) = *(byte *)(iVar4 + 0x8a) & 0xbf;
    }
  }
  return;
}

/* JP: 0x004b46b0  CField::SetCharacterDir(int, int, int, int)   [SetCharacterDir__6CFieldFiiii]  size=0x51c */
undefined4 SetCharacterDir__6CFieldFiiii(CField *this,int a0,int a1,int a2,int a3)

{
  void *pvVar1;
  void *pvVar2;
  bool bVar3;
  undefined4 uVar4;
  long lVar5;
  undefined8 uVar6;
  uint uVar7;
  undefined1 *puVar8;
  int iVar9;
  float extraout_f0;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  float afStack_80 [4];
  undefined1 auStack_70 [4];
  float fStack_6c;
  float fStack_5c;
  int iStack_58;
  uint uStack_54;
  CField *pCStack_50;
  int iStack_40;
  uint uStack_30;
  int iStack_20;
  int iStack_10;
  
  pCStack_50 = this;
  iStack_40 = a0;
  uStack_30 = a1;
  iStack_20 = a2;
  iStack_10 = a3;
  lVar5 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_70);
  pvVar1 = pCStack_50->aModels[iStack_40];
  if ((pvVar1 == (void *)0x0) || (lVar5 = isEmpty__11CFieldModelFv(pvVar1), lVar5 != 0)) {
    return (int)lVar5;
  }
  uVar7 = (int)uStack_30 >> 0x10 & 0xf;
  if (uVar7 == 3) {
    uVar7 = 10;
  }
  else if (uVar7 == 2) {
    uVar7 = 9;
  }
  else if (uVar7 == 1) {
    uVar7 = 8;
  }
  else {
    uVar7 = (int)uStack_30 >> 7 & 0xf;
  }
  lVar5 = __ct__7FVectorFffff(0,0,0,0x3f800000,afStack_80);
  bVar3 = false;
  if (uVar7 == 10) {
    iVar9 = GetEntryPoint__6CFieldFiRi(pCStack_50,uStack_30 & 0xffff,&iStack_58);
    if (-1 < iStack_58) {
      memcpy(afStack_80,iVar9,0xc);
    }
    bVar3 = true;
  }
  else if (uVar7 == 9) {
    uVar6 = GetActiveCamera__9GsxCameraFv();
    uVar6 = GetFrame__9GsxCameraFv(uVar6);
    uVar6 = GetPos__6MatrixFv(uVar6);
    __as__7FVectorFRC7FVector(afStack_80,uVar6);
    bVar3 = true;
  }
  else if (uVar7 == 8) {
    uStack_54 = uStack_30 & 0xffff;
    iVar9 = 0;
    for (puVar8 = &pCStack_50->field_0x3f0;
        (iVar9 < 0x10 && ((*(short *)(puVar8 + 6) == 0 || (*(ushort *)(puVar8 + 0xc) != uStack_54)))
        ); puVar8 = puVar8 + 0x10) {
      iVar9 = iVar9 + 1;
    }
    if (0xf < iVar9) {
      return (int)lVar5;
    }
    GetShortPos__FP7FVectorPs(afStack_80,puVar8);
    bVar3 = true;
  }
  else if (uVar7 == 1) {
    pvVar2 = pCStack_50->aModels[uStack_30 & 0x7f];
    if ((pvVar2 == (void *)0x0) || (lVar5 = isEmpty__11CFieldModelFv(pvVar2), lVar5 != 0)) {
      return (int)lVar5;
    }
    GetPos__11CFieldModelFv(auStack_90,pvVar2);
    __as__7FVectorFRC7FVector(afStack_80,auStack_90);
    bVar3 = true;
  }
  else {
    fStack_6c = (float)GetRotAngle__Fi(uStack_30);
  }
  if (bVar3) {
    GetPos__11CFieldModelFv(auStack_a0,pvVar1);
    __ami__7FVectorFRC7FVector(afStack_80,auStack_a0);
    afStack_80[1] = 0.0;
    uVar4 = Length__7FVectorCFv(afStack_80);
    if (extraout_f0 == 0.0) {
      return uVar4;
    }
    Normalize__7FVectorFv(afStack_80);
    if (afStack_80[2] == 0.0) {
      if (0.0 < afStack_80[0]) {
        fStack_5c = 0.0;
      }
      else {
        fStack_5c = 3.141592;
      }
      fStack_6c = fStack_5c;
    }
    else if (afStack_80[2] < 0.0) {
      fStack_6c = (float)atanf(afStack_80[0] / afStack_80[2]);
    }
    else if (afStack_80[0] < 0.0) {
      fStack_6c = (float)atanf((afStack_80[0] * -1.0) / afStack_80[2]);
      fStack_6c = 3.141592 - fStack_6c;
    }
    else {
      fStack_6c = (float)atanf(afStack_80[0] / afStack_80[2]);
      fStack_6c = fStack_6c - 3.141592;
    }
  }
  SetDir__11CFieldModelFR7FVectorii(pvVar1,auStack_70,iStack_20,iStack_10);
  uVar4 = SetCmd__11CFieldModelFi(pvVar1,8);
  return uVar4;
}

/* JP: 0x004b4bd0  CField::GetCharacterInfo(int, int)   [GetCharacterInfo__6CFieldFii]  size=0x214 */
long GetCharacterInfo__6CFieldFii(CField *this,int a0,int a1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  
  uVar4 = 0;
  if ((a0 & 0x80U) == 0) {
    iVar1 = GetModel__6CFieldFi(this,a0);
    lVar3 = (long)iVar1;
  }
  else {
    lVar3 = GetBGModel__6CFieldFi(this,a0);
  }
  if (lVar3 == 0) {
    uVar4 = 0xffffffffffffffff;
  }
  else {
    iVar1 = (int)lVar3;
    switch(a1) {
    case 0:
      uVar4 = (ulong)*(ushort *)(iVar1 + 0x8e);
      break;
    case 1:
      uVar4 = GetDir__11CFieldModelFv(lVar3);
      break;
    case 2:
      uVar4 = (ulong)*(int *)(iVar1 + 0xc0);
      break;
    case 3:
      uVar4 = (ulong)*(byte *)(iVar1 + 0x80) & 3;
      break;
    case 4:
      uVar4 = ((ulong)*(byte *)(iVar1 + 0x80) & 0xf) >> 2;
      break;
    case 5:
      if (*(byte *)(iVar1 + 0xfc) == 0xff) {
        uVar4 = 0;
      }
      else if ((*(byte *)(iVar1 + 0xfc) & 0x80) == 0) {
        uVar4 = 1;
      }
      else {
        uVar4 = 2;
      }
      break;
    case 6:
      if ((ulong)*(byte *)(iVar1 + 0xfc) == 0xff) {
        uVar4 = 0xffffffffffffffff;
      }
      else {
        uVar4 = (ulong)*(byte *)(iVar1 + 0xfc) & 0x7f;
      }
      break;
    case 7:
      uVar4 = ((ulong)*(byte *)(iVar1 + 0x81) & 0x7f) >> 6;
      break;
    case 8:
      iVar1 = isHitChk__11CFieldModelFv(lVar3);
      iVar2 = isFloorChk__11CFieldModelFv(lVar3);
      uVar4 = (ulong)(iVar1 * 2 + iVar2);
      break;
    case 9:
      uVar4 = (ulong)(*(byte *)(iVar1 + 0x88) >> 7);
      break;
    case 0xd:
      uVar4 = GetMotionCode__11CFieldModelFv(lVar3);
    }
  }
  return uVar4;
}

/* JP: 0x004b4e20  CField::SetCharacterInfo(int, int, int)   [SetCharacterInfo__6CFieldFiii]  size=0x19c */
void SetCharacterInfo__6CFieldFiii(CField *this,int a0,int a1,int a2)

{
  void *pvVar1;
  
  pvVar1 = this->aModels[a0];
  if (pvVar1 != (void *)0x0) {
    if (a1 == 0x10) {
      SetGhost__11CFieldModelFv(pvVar1);
    }
    else if (a1 == 0xf) {
      SetBlink__11CFieldModelFi(pvVar1,a2);
    }
    else if (a1 == 0xe) {
      SetMirror__11CFieldModelFi(pvVar1,a2);
    }
    else if (a1 == 0xc) {
      PauseAutoMove__11CFieldModelFi(pvVar1,a2);
    }
    else if (a1 == 10) {
      *(int *)((int)pvVar1 + 300) = a2;
    }
    else if (a1 == 9) {
      *(byte *)((int)pvVar1 + 0x88) = *(byte *)((int)pvVar1 + 0x88) & 0x7f | (byte)((a2 & 1U) << 7);
    }
    else if (a1 == 8) {
      SetFloorChk__11CFieldModelFi(pvVar1,a2 & 1);
      SetHitCheck__11CFieldModelFi(pvVar1,a2 >> 1 & 1);
    }
    else if (a1 == 2) {
      *(int *)((int)pvVar1 + 0xc0) = a2;
    }
  }
  return;
}

/* JP: 0x004b5040  CField::CreateWindow(int, int, int, int)   [CreateWindow__6CFieldFiiii]  size=0x9c */
undefined4 CreateWindow__6CFieldFiiii(CField *this,int a0,int a1,int a2,int a3)

{
  undefined4 uVar1;
  
  this->field_0x6c0 = (char)a0;
  (&this->field_0x610)[a0 * 0x14] = (char)a1;
  (&this->field_0x611)[a0 * 0x14] = (char)a2;
  *(short *)(&this->field_0x614 + a0 * 0x14) = (short)a3;
  uVar1 = 0x100;
  *(undefined2 *)(&this->field_0x616 + a0 * 0x14) = 0x100;
  RecreateWindow__6CFieldFPQ26CField8_WndInfo(this,&this->field_0x60c + a0 * 0x14);
  return uVar1;
}

/* JP: 0x004b50e0  CField::RecreateWindow(CField::_WndInfo*)   [RecreateWindow__6CFieldFPQ26CField8_WndInfo]  size=0x140 */
void RecreateWindow__6CFieldFPQ26CField8_WndInfo(CField *this,void *a0)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)a0 == 0) {
    lVar2 = __nw__FUi(0x1c);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__12FieldMessageFv(lVar2);
    }
    *(undefined4 *)a0 = uVar1;
  }
  else {
    DestroyWindow__12FieldMessageFv(*(undefined4 *)a0);
  }
  CreateWindow__12FieldMessageFsUcUcUcs
            (*(undefined4 *)a0,this->field_0x6c0,*(undefined1 *)((int)a0 + 4),
             (&fontTypeTbl)[*(byte *)((int)a0 + 5) & 3],*(ushort *)((int)a0 + 8) & 0xff,
             *(undefined2 *)((int)a0 + 10));
  ClearMessage__12FieldMessageFv(*(undefined4 *)a0);
  SetVariable__12FieldMessageFUc(*(undefined4 *)a0,(int)(uint)*(byte *)((int)a0 + 5) >> 2 & 1);
  return;
}

/* JP: 0x004b52a0  CField::SetWindowPos(int, int)   [SetWindowPos__6CFieldFii]  size=0x68 */
void SetWindowPos__6CFieldFii(CField *this,int a0,int a1)

{
  byte bVar1;
  
  bVar1 = this->field_0x6c0;
  *(short *)(&this->field_0x618 + (uint)bVar1 * 0x14) = (short)a0;
  *(short *)(&this->field_0x61a + (uint)bVar1 * 0x14) = (short)a1;
  return;
}

/* JP: 0x004b5310  CField::SetWindowSize(int, int)   [SetWindowSize__6CFieldFii]  size=0x60 */
void SetWindowSize__6CFieldFii(CField *this,int a0,int a1)

{
  byte bVar1;
  
  bVar1 = this->field_0x6c0;
  (&this->field_0x61c)[(uint)bVar1 * 0x14] = (char)a0;
  (&this->field_0x61d)[(uint)bVar1 * 0x14] = (char)a1;
  return;
}

/* JP: 0x004b5370  CField::OpenWindow(int, int)   [OpenWindow__6CFieldFii]  size=0xcc */
void OpenWindow__6CFieldFii(CField *this,int a0,int a1)

{
  byte bVar1;
  int *a0_00;
  
  bVar1 = this->field_0x6c0;
  a0_00 = (int *)(&this->field_0x60c + (uint)bVar1 * 0x14);
  if (*a0_00 == 0) {
    RecreateWindow__6CFieldFPQ26CField8_WndInfo(this,a0_00);
  }
  SetSize__12FieldMessageFss
            (*a0_00,(&this->field_0x61c)[(uint)bVar1 * 0x14],
             (&this->field_0x61d)[(uint)bVar1 * 0x14]);
  SetPosition__12FieldMessageFff
            ((float)(int)*(short *)(&this->field_0x618 + (uint)bVar1 * 0x14),
             (float)(int)*(short *)(&this->field_0x61a + (uint)bVar1 * 0x14),*a0_00);
  OpenWindow__12FieldMessageFUci(*a0_00,a0 & 0xff,a1);
  return;
}

/* JP: 0x004b5440  CField::CloseWindow(int, int)   [CloseWindow__6CFieldFii]  size=0x74 */
void CloseWindow__6CFieldFii(CField *this,int a0,int a1)

{
  if (*(int *)(&this->field_0x60c + (uint)(byte)this->field_0x6c0 * 0x14) != 0) {
    CloseWindow__12FieldMessageFUci
              (*(int *)(&this->field_0x60c + (uint)(byte)this->field_0x6c0 * 0x14),a0 & 0xff,a1);
  }
  return;
}

/* JP: 0x004b54c0  CField::UpdateMsgState()   [UpdateMsgState__6CFieldFv]  size=0x114 */
void UpdateMsgState__6CFieldFv(CField *this)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  
  bVar1 = this->field_0x6c0;
  piVar4 = (int *)(&this->field_0x60c + (uint)bVar1 * 0x14);
  if ((piVar4 != (int *)0x0) && (*piVar4 != 0)) {
    sVar2 = GetState__12FieldMessageCFv(*piVar4);
    if (((sVar2 == 1) || (sVar2 == 0xe)) &&
       ((long)((ulong)(byte)(&this->field_0x612)[(uint)bVar1 * 0x14] << 0x3e) < 0)) {
      iVar3 = GetModel__6CFieldFi(this,(int)(char)this->field_0x6ca);
      if (iVar3 != 0) {
        SetTalk__11CFieldModelFi(iVar3,2);
      }
      (&this->field_0x612)[(uint)bVar1 * 0x14] = (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfd;
      this->field_0x6ca = 0xff;
    }
  }
  return;
}

/* JP: 0x004b5600  CField::OpenMessage(char*, int, int)   [OpenMessage__6CFieldFPcii]  size=0x110 */
void OpenMessage__6CFieldFPcii(CField *this,char *a0,int a1,int a2)

{
  byte bVar1;
  int iVar2;
  
  *(int *)&this->field_0x24 = a1;
  this->field_0x6ca = (char)a2;
  bVar1 = this->field_0x6c0;
  if (*(int *)(&this->field_0x60c + (uint)bVar1 * 0x14) != 0) {
    if (-1 < a2) {
      iVar2 = GetModel__6CFieldFi(this,a2);
      if (iVar2 != 0) {
        SetTalk__11CFieldModelFi(iVar2,1);
        (&this->field_0x612)[(uint)bVar1 * 0x14] =
             (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfd | 2;
      }
    }
    OpenMessage__12FieldMessageFPc(*(int *)(&this->field_0x60c + (uint)bVar1 * 0x14),a0);
    (&this->field_0x612)[(uint)bVar1 * 0x14] = (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfb | 4;
  }
  return;
}

/* JP: 0x004b5710  CField::ClearMessage()   [ClearMessage__6CFieldFv]  size=0x64 */
void ClearMessage__6CFieldFv(CField *this)

{
  if (*(int *)(&this->field_0x60c + (uint)(byte)this->field_0x6c0 * 0x14) != 0) {
    ClearMessage__12FieldMessageFv
              (*(int *)(&this->field_0x60c + (uint)(byte)this->field_0x6c0 * 0x14));
  }
  return;
}

/* JP: 0x004b5780  CField::KeyWait()   [KeyWait__6CFieldFv]  size=0xf8 */
undefined4 KeyWait__6CFieldFv(CField *this)

{
  byte bVar1;
  short sVar2;
  int *piVar3;
  
  bVar1 = this->field_0x6c0;
  piVar3 = (int *)(&this->field_0x60c + (uint)bVar1 * 0x14);
  if (*piVar3 != 0) {
    sVar2 = GetState__12FieldMessageCFv(*piVar3);
    if (((long)((ulong)(byte)(&this->field_0x612)[(uint)bVar1 * 0x14] << 0x3d) < 0) &&
       ((&this->field_0x612)[(uint)bVar1 * 0x14] = (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfb,
       sVar2 != 0)) {
      EnableKeyWait__12FieldMessageFs(*piVar3,0);
      sVar2 = GetState__12FieldMessageCFv(*piVar3);
    }
    if ((sVar2 != 0) && (sVar2 != 1)) {
      return 0xffffffff;
    }
  }
  return 0;
}

/* JP: 0x004b5880  CField::KeyWaitStat()   [KeyWaitStat__6CFieldFv]  size=0xf8 */
undefined4 KeyWaitStat__6CFieldFv(CField *this)

{
  byte bVar1;
  short sVar2;
  int *piVar3;
  
  bVar1 = this->field_0x6c0;
  piVar3 = (int *)(&this->field_0x60c + (uint)bVar1 * 0x14);
  if (*piVar3 != 0) {
    sVar2 = GetState__12FieldMessageCFv(*piVar3);
    if (((long)((ulong)(byte)(&this->field_0x612)[(uint)bVar1 * 0x14] << 0x3d) < 0) &&
       ((&this->field_0x612)[(uint)bVar1 * 0x14] = (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfb,
       sVar2 != 0)) {
      EnableKeyWait__12FieldMessageFs(*piVar3,0);
      sVar2 = GetState__12FieldMessageCFv(*piVar3);
    }
    if ((sVar2 != 0) && (sVar2 != 1)) {
      return 1;
    }
  }
  return 0;
}

/* JP: 0x004b5980  CField::LoadFace(int, int)   [LoadFace__6CFieldFii]  size=0xcc */
void LoadFace__6CFieldFii(CField *this,int a0,int a1)

{
  int iVar1;
  long lVar2;
  
  this->field_0x6c1 = (char)a0;
  iVar1 = *(int *)(&this->field_0x6b0 + a0 * 4);
  if (iVar1 == 0) {
    lVar2 = __nw__FUi(0x1c);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__9FaceImageFv(lVar2);
    }
    *(int *)(&this->field_0x6b0 + a0 * 4) = iVar1;
  }
  Create__9FaceImageFi(iVar1,a1);
  SetSize__9FaceImageFff(0x42c00000,0x42c00000,iVar1);
  return;
}

/* JP: 0x004b5ac0  CField::ReleaseFace(int)   [ReleaseFace__6CFieldFi]  size=0x74 */
void ReleaseFace__6CFieldFi(CField *this,int a0)

{
  if (a0 < 0) {
    ReleaseHandle__11FileManegerFv(sm_pFace__7MenuObj);
  }
  else if (*(int *)(&this->field_0x6b0 + a0 * 4) != 0) {
    Release__9FaceImageFv(*(int *)(&this->field_0x6b0 + a0 * 4));
  }
  return;
}

/* JP: 0x004b5b40  CField::SetFacePos(int, int)   [SetFacePos__6CFieldFii]  size=0x7c */
void SetFacePos__6CFieldFii(CField *this,int a0,int a1)

{
  if (*(int *)(&this->field_0x6b0 + (uint)(byte)this->field_0x6c1 * 4) != 0) {
    SetPosition__9FaceImageFff
              ((float)a0,(float)a1,*(int *)(&this->field_0x6b0 + (uint)(byte)this->field_0x6c1 * 4))
    ;
  }
  return;
}

/* JP: 0x004b5c00  CField::SetFaceSize(int, int)   [SetFaceSize__6CFieldFii]  size=0x7c */
void SetFaceSize__6CFieldFii(CField *this,int a0,int a1)

{
  if (*(int *)(&this->field_0x6b0 + (uint)(byte)this->field_0x6c1 * 4) != 0) {
    SetSize__9FaceImageFff
              ((float)a0,(float)a1,*(int *)(&this->field_0x6b0 + (uint)(byte)this->field_0x6c1 * 4))
    ;
  }
  return;
}

/* JP: 0x004b5c80  CField::OpenFace(int, int)   [OpenFace__6CFieldFii]  size=0x6c */
void OpenFace__6CFieldFii(CField *this,int a0,int a1)

{
  if (*(int *)(&this->field_0x6b0 + (uint)(byte)this->field_0x6c1 * 4) != 0) {
    Open__9FaceImageFUci
              (*(int *)(&this->field_0x6b0 + (uint)(byte)this->field_0x6c1 * 4),a0 & 0xff,a1);
  }
  return;
}

/* JP: 0x004b5cf0  CField::CloseFace(int, int)   [CloseFace__6CFieldFii]  size=0x6c */
void CloseFace__6CFieldFii(CField *this,int a0,int a1)

{
  if (*(int *)(&this->field_0x6b0 + (uint)(byte)this->field_0x6c1 * 4) != 0) {
    Close__9FaceImageFUci
              (*(int *)(&this->field_0x6b0 + (uint)(byte)this->field_0x6c1 * 4),a0 & 0xff,a1);
  }
  return;
}

/* JP: 0x004b5d60  CField::CreateName(int, int, int, int)   [CreateName__6CFieldFiiii]  size=0xb8 */
undefined4 CreateName__6CFieldFiiii(CField *this,int a0,int a1,int a2,int a3)

{
  undefined4 uVar1;
  
  this->field_0x6c2 = (char)a0;
  (&this->field_0x660)[a0 * 0x14] = (char)a1;
  (&this->field_0x661)[a0 * 0x14] = (char)a2;
  *(short *)(&this->field_0x664 + a0 * 0x14) = (short)a3;
  *(undefined2 *)(&this->field_0x666 + a0 * 0x14) = 0x10;
  RecreateWindow__6CFieldFPQ26CField8_WndInfo(this,&this->field_0x65c + a0 * 0x14);
  uVar1 = SetSize__12FieldMessageFss
                    (*(undefined4 *)(&this->field_0x65c + a0 * 0x14),
                     *(undefined2 *)(&this->field_0x666 + a0 * 0x14),1);
  return uVar1;
}

/* JP: 0x004b5e20  CField::SetNamePos(int, int)   [SetNamePos__6CFieldFii]  size=0x8c */
void SetNamePos__6CFieldFii(CField *this,int a0,int a1)

{
  if (*(int *)(&this->field_0x65c + (uint)(byte)this->field_0x6c2 * 0x14) != 0) {
    SetPosition__12FieldMessageFff
              ((float)a0,(float)a1,
               *(int *)(&this->field_0x65c + (uint)(byte)this->field_0x6c2 * 0x14));
  }
  return;
}

/* JP: 0x004b5eb0  CField::OpenName(char*, int, int)   [OpenName__6CFieldFPcii]  size=0x8c */
void OpenName__6CFieldFPcii(CField *this,char *a0,int a1,int a2)

{
  int *piVar1;
  
  piVar1 = (int *)(&this->field_0x65c + (uint)(byte)this->field_0x6c2 * 0x14);
  if (*piVar1 != 0) {
    OpenWindow__12FieldMessageFUci(*piVar1,a1 & 0xff,a2);
    OpenMessage__12FieldMessageFPc(*piVar1,a0);
  }
  return;
}

/* JP: 0x004b5f40  CField::CloseName(int, int)   [CloseName__6CFieldFii]  size=0x74 */
void CloseName__6CFieldFii(CField *this,int a0,int a1)

{
  if (*(int *)(&this->field_0x65c + (uint)(byte)this->field_0x6c2 * 0x14) != 0) {
    CloseWindow__12FieldMessageFUci
              (*(int *)(&this->field_0x65c + (uint)(byte)this->field_0x6c2 * 0x14),a0 & 0xff,a1);
  }
  return;
}

/* JP: 0x004b5fc0  CField::SelectInitItem()   [SelectInitItem__6CFieldFv]  size=0xac */
void SelectInitItem__6CFieldFv(CField *this)

{
  byte bVar1;
  int *piVar2;
  
  bVar1 = this->field_0x6c0;
  piVar2 = (int *)(&this->field_0x60c + (uint)bVar1 * 0x14);
  if (*piVar2 != 0) {
    ClearMessage__12FieldMessageFv(*piVar2);
    SetSize__12FieldMessageFss
              (*piVar2,(&this->field_0x61c)[(uint)bVar1 * 0x14],
               (&this->field_0x61d)[(uint)bVar1 * 0x14]);
    SetPosition__12FieldMessageFff
              ((float)(int)*(short *)(&this->field_0x618 + (uint)bVar1 * 0x14),
               (float)(int)*(short *)(&this->field_0x61a + (uint)bVar1 * 0x14),*piVar2);
  }
  return;
}

/* JP: 0x004b6070  CField::SelectAddItem(const char*)   [SelectAddItem__6CFieldFPCc]  size=0x70 */
undefined4 SelectAddItem__6CFieldFPCc(CField *this,char *a0)

{
  if (*(int *)(&this->field_0x60c + (uint)(byte)this->field_0x6c0 * 0x14) != 0) {
    SetSelectMessage__12FieldMessageFPc
              (*(int *)(&this->field_0x60c + (uint)(byte)this->field_0x6c0 * 0x14),a0);
  }
  return 1;
}

/* JP: 0x004b60e0  CField::SelectInit(int)   [SelectInit__6CFieldFi]  size=0x8c */
void SelectInit__6CFieldFi(CField *this,int a0)

{
  int *piVar1;
  
  piVar1 = (int *)(&this->field_0x60c + (uint)(byte)this->field_0x6c0 * 0x14);
  if (*piVar1 != 0) {
    SetSelectMode__12FieldMessageFUc(*piVar1,a0 & 3);
    SetCancel__12FieldMessageFUc(*piVar1,(a0 & 4U) != 0);
  }
  return;
}

/* JP: 0x004b6230  CField::Select(int&)   [Select__6CFieldFRi]  size=0x268 */
undefined4 Select__6CFieldFRi(CField *this,int *a0)

{
  byte bVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  
  bVar1 = this->field_0x6c0;
  piVar4 = (int *)(&this->field_0x60c + (uint)bVar1 * 0x14);
  if (*piVar4 == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    sVar2 = GetState__12FieldMessageCFv(*piVar4);
    if (sVar2 == 9) {
      (&this->field_0x612)[(uint)bVar1 * 0x14] = (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfe | 1
      ;
      StartSelect__12FieldMessageFs(*piVar4,0);
      this->bFlags_18d =
           this->bFlags_18d & 0x3f |
           (byte)(((uint)(((ulong)this->bFlags_18d << 0x38) >> 0x3e) + 1 & 3) << 6);
    }
    else if (sVar2 == 1) {
      if (((&this->field_0x612)[(uint)bVar1 * 0x14] & 1) != 0) {
        sVar2 = GetResult__12FieldMessageCFv(*piVar4);
        *a0 = (int)sVar2;
        (&this->field_0x612)[(uint)bVar1 * 0x14] = (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfe;
        this->bFlags_18d =
             this->bFlags_18d & 0x3f |
             (byte)(((uint)(((ulong)this->bFlags_18d << 0x38) >> 0x3e) - 1 & 3) << 6);
        return 1;
      }
      (&this->field_0x612)[(uint)bVar1 * 0x14] = (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfe | 1
      ;
      this->bFlags_18d =
           this->bFlags_18d & 0x3f |
           (byte)(((uint)(((ulong)this->bFlags_18d << 0x38) >> 0x3e) + 1 & 3) << 6);
    }
    else if (sVar2 == 0) {
      (&this->field_0x612)[(uint)bVar1 * 0x14] = (&this->field_0x612)[(uint)bVar1 * 0x14] & 0xfe | 1
      ;
      StartSelect__12FieldMessageFs(*piVar4,0);
      OpenWindow__12FieldMessageFUci(*piVar4,0,0);
      this->bFlags_18d =
           this->bFlags_18d & 0x3f |
           (byte)(((uint)(((ulong)this->bFlags_18d << 0x38) >> 0x3e) + 1 & 3) << 6);
    }
    uVar3 = 0;
  }
  return uVar3;
}

/* JP: 0x004b6500  CField::LoadImage(const char*, int)   [LoadImage__6CFieldFPCci]  size=0xb4 */
void LoadImage__6CFieldFPCci(CField *this,char *a0,int a1)

{
  char *a1_00;
  long lVar1;
  void *a2;
  undefined1 auStack_80 [80];
  CField *pCStack_30;
  char *pcStack_20;
  int iStack_10;
  
  pCStack_30 = this;
  pcStack_20 = a0;
  iStack_10 = a1;
  ClrImage__6CFieldFiiib(this,a1,0,0,false);
  lVar1 = __nw__FUi(0xd0);
  a1_00 = (char *)0x0;
  if (lVar1 != 0) {
    a1_00 = (char *)__ct__9FldSpriteFv(lVar1);
  }
  *(char **)(&pCStack_30->field_0x6b8 + iStack_10 * 4) = a1_00;
  GetImgName__FPcPCc(auStack_80,pcStack_20);
  FileReadOrder__6CFieldFiPCcPv((CField *)0x81,(int)auStack_80,a1_00,a2);
  return;
}

/* JP: 0x004b65c0  CField::DspImage(int, int, int, int, int)   [DspImage__6CFieldFiiiii]  size=0x78 */
undefined4 DspImage__6CFieldFiiiii(CField *this,int a0,int a1,int a2,int a3,int a4)

{
  undefined4 in_v0_lo;
  
  if (*(int *)(&this->field_0x6b8 + a0 * 4) != 0) {
    in_v0_lo = Dsp__9FldSpriteFiiii(*(undefined4 *)(&this->field_0x6b8 + a0 * 4),a1,a2,a3,a4);
  }
  return in_v0_lo;
}

/* JP: 0x004b6640  CField::ClrImage(int, int, int, bool)   [ClrImage__6CFieldFiiib]  size=0x90 */
undefined4 ClrImage__6CFieldFiiib(CField *this,int a0,int a1,int a2,bool a3)

{
  undefined4 in_v0_lo;
  
  if ((*(int *)(&this->field_0x6b8 + a0 * 4) != 0) &&
     (in_v0_lo = Clr__9FldSpriteFiib(*(undefined4 *)(&this->field_0x6b8 + a0 * 4),a1,a2,a3), !a3)) {
    *(undefined4 *)(&this->field_0x6b8 + a0 * 4) = 0;
  }
  return in_v0_lo;
}

/* JP: 0x004b66d0  CField::SetEncountRate(int)   [SetEncountRate__6CFieldFi]  size=0x84 */
void SetEncountRate__6CFieldFi(CField *this,int a0)

{
  short *psVar1;
  uint uStack_10;
  
  psVar1 = (short *)GetFieldBattleInfo__Fv();
  if (a0 < 0) {
    uStack_10 = (int)*psVar1 & 0xff;
  }
  else {
    *psVar1 = (short)a0;
    uStack_10 = a0;
  }
  this->field_0x3c6 = (char)uStack_10;
  this->field_0x3c8 = 0;
  return;
}

/* JP: 0x004b6760  CField::UpdateMoveDistance(float, int)   [UpdateMoveDistance__6CFieldFfi]  size=0x70 */
void UpdateMoveDistance__6CFieldFfi(CField *this,float a0,int a1)

{
  bool bVar1;
  
  bVar1 = this->field_0x3c6 != '\0';
  if (bVar1) {
    *(float *)&this->field_0x3cc = *(float *)&this->field_0x3cc + a0;
  }
  FieldUpdateTotalDistance__Ffii(a0,a1,bVar1);
  return;
}

/* JP: 0x004b67d0  CField::TreasureControl(int, int, int)   [TreasureControl__6CFieldFiii]  size=0x250 */
char * TreasureControl__6CFieldFiii(CField *this,int a0,int a1,int a2)

{
  byte *pbVar1;
  char *pcVar2;
  long lVar3;
  
  pbVar1 = (byte *)0x0;
  if ((a0 < 5) && (lVar3 = FindDTCInfo__FPCc(0x555e20), lVar3 != 0)) {
    pbVar1 = (byte *)GetDTCData__FP8_DTCINFOi(lVar3,a1);
  }
  switch(a0) {
  case 0:
    pcVar2 = (char *)SetTreasureFlag__Fii(a1,0xffffffffffffffff);
    break;
  case 1:
    if (((pbVar1[1] & 0x3f) == 0) || (*pbVar1 == 0xff)) {
      pcVar2 = (char *)0xffffffff;
    }
    else {
      pcVar2 = (char *)((pbVar1[1] & 0x3f) << 8 | (uint)*pbVar1);
    }
    break;
  case 2:
    if ((&RDnumTbl)[pbVar1[1] & 0x3f] == '\0') {
      pcVar2 = _11288;
    }
    else {
      pcVar2 = (char *)GetRegDat__9RegDatApiFiii((&RDnumTbl)[pbVar1[1] & 0x3f],*pbVar1,0xffffffffffffffff);
    }
    break;
  case 3:
    lVar3 = SetTreasureFlag__Fii(a1,0xffffffffffffffff);
    if (lVar3 == 1) {
      pcVar2 = (char *)(uint)*(ushort *)(pbVar1 + 2);
    }
    else {
      pcVar2 = (char *)0x0;
    }
    break;
  case 4:
    lVar3 = SetTreasureFlag__Fii(a1,1);
    if (lVar3 == 1) {
      pcVar2 = (char *)InventoryChange__Fiii(pbVar1[1] & 0x3f,*pbVar1,*(undefined2 *)(pbVar1 + 2));
    }
    else {
      pcVar2 = (char *)0x0;
    }
    break;
  case 5:
    pcVar2 = (char *)InventoryChange__Fiii(a1 >> 8,a1 & 0xff,a2);
    break;
  default:
    pcVar2 = (char *)0xffffffff;
  }
  return pcVar2;
}

/* JP: 0x004b6a20  CField::DspIcon(int, int)   [DspIcon__6CFieldFii]  size=0x5c */
void DspIcon__6CFieldFii(CField *this,int a0,int a1)

{
  int iVar1;
  
  iVar1 = GetModel__6CFieldFi(this,a0);
  if (iVar1 != 0) {
    DspIcon__11CFieldModelFi(iVar1,a1);
  }
  return;
}

/* JP: 0x004b6a80  CField::SetLookPoint(int, float*, float, unsigned int, int, int)   [SetLookPoint__6CFieldFiPffUiii]  size=0x1d8 */
uint SetLookPoint__6CFieldFiPffUiii(CField *this,int a0,float *a1,float a2,uint a3,int a4,int a5)

{
  uint uVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_80 [12];
  float fStack_74;
  CField *pCStack_70;
  int iStack_60;
  float *pfStack_50;
  float fStack_40;
  uint uStack_30;
  int iStack_20;
  uint uStack_10;
  
  iVar5 = -1;
  iVar4 = 0;
  for (puVar2 = &this->field_0x3f0;
      (iVar3 = -1, iVar4 < 0x10 &&
      ((*(short *)(puVar2 + 6) == 0 || (iVar3 = iVar4, (uint)*(ushort *)(puVar2 + 0xc) != a0))));
      puVar2 = puVar2 + 0x10) {
    if ((*(short *)(puVar2 + 6) == 0) && (iVar5 < 0)) {
      iVar5 = iVar4;
    }
    iVar4 = iVar4 + 1;
  }
  if ((iVar3 < 0) && (iVar5 < 0)) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar4 = iVar3;
    if (iVar3 < 0) {
      iVar4 = iVar5;
    }
    uVar1 = (uint)(iVar3 < 0);
    pCStack_70 = this;
    iStack_60 = a0;
    pfStack_50 = a1;
    fStack_40 = a2;
    uStack_30 = a3;
    iStack_20 = a4;
    uStack_10 = a5;
    __ct__7FVectorFv(auStack_80);
    memcpy(auStack_80,pfStack_50,0xc);
    fStack_74 = fStack_40;
    SetShortPos4__FPsP7FVector(&this->field_0x3f0 + iVar4 * 0x10,auStack_80);
    *(uint *)(&this->field_0x3f8 + iVar4 * 0x10) = uStack_30;
    *(short *)(&this->field_0x3fc + iVar4 * 0x10) = (short)iStack_60;
    (&this->field_0x3fe)[iVar4 * 0x10] =
         (&this->field_0x3fe)[iVar4 * 0x10] & 0xf0 | (byte)iStack_20 & 0xf;
    (&this->field_0x3fe)[iVar4 * 0x10] =
         (&this->field_0x3fe)[iVar4 * 0x10] & 0xf | (byte)((uStack_10 & 0xf) << 4);
  }
  return uVar1;
}

/* JP: 0x004b6c60  CField::ClrLookPoint(int)   [ClrLookPoint__6CFieldFi]  size=0xd8 */
void ClrLookPoint__6CFieldFi(CField *this,int a0)

{
  undefined1 *puVar1;
  int a0_00;
  
  puVar1 = &this->field_0x3f0;
  for (a0_00 = 0; a0_00 < 0x10; a0_00 = a0_00 + 1) {
    if ((*(short *)(puVar1 + 6) != 0) && ((a0 < 0 || ((uint)*(ushort *)(puVar1 + 0xc) == a0)))) {
      if ((char)this->bClr_flag_5ec + -1 == a0_00) {
        DetachLookPoint__6CFieldFi(this,a0_00);
      }
      *(undefined2 *)(puVar1 + 6) = 0;
    }
    puVar1 = puVar1 + 0x10;
  }
  return;
}

/* JP: 0x004b6d40  CField::ChkLookPoint(int)   [ChkLookPoint__6CFieldFi]  size=0x1fc */
int ChkLookPoint__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  undefined4 uVar2;
  int a0_00;
  int iVar3;
  int iVar4;
  int a0_01;
  undefined1 *puVar5;
  undefined1 auStack_50 [12];
  float fStack_44;
  undefined1 auStack_40 [20];
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  CField *pCStack_20;
  int iStack_10;
  
  pCStack_20 = this;
  iStack_10 = a0;
  uVar2 = GetCtrlModel__6CFieldFv(this);
  GetPos__11CFieldModelFv(auStack_40,uVar2);
  __ct__7FVectorFv(auStack_50);
  fStack_24 = 0.0;
  a0_00 = -1;
  a0_01 = -1;
  iVar4 = (char)pCStack_20->bClr_flag_5ec + -1;
  puVar5 = &pCStack_20->field_0x3f0;
  for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
    iVar1 = a0_00;
    if (*(short *)(puVar5 + 6) != 0) {
      GetShortPos4__FP7FVectorPs(auStack_50,puVar5);
      fStack_28 = fStack_44;
      __ami__7FVectorFRC7FVector(auStack_50,auStack_40);
      fStack_2c = (float)Length__7FVectorCFv(auStack_50);
      if (fStack_2c <= fStack_28) {
        iVar1 = iVar3;
        if ((-1 < a0_00) && (fStack_24 <= fStack_2c)) {
          iVar1 = a0_00;
        }
      }
      else if (iVar4 == iVar3) {
        a0_01 = iVar3;
      }
    }
    a0_00 = iVar1;
    puVar5 = puVar5 + 0x10;
  }
  if ((((a0_01 < 0) && (-1 < a0_00)) && (-1 < iVar4)) && (a0_00 != iVar4)) {
    a0_01 = iVar4;
  }
  if (iStack_10 != 0) {
    if (-1 < a0_01) {
      DetachLookPoint__6CFieldFi(pCStack_20,a0_01);
    }
    if ((-1 < a0_00) && (iVar4 != a0_00)) {
      AttachLookPoint__6CFieldFi(pCStack_20,a0_00);
    }
  }
  return a0_00;
}

/* JP: 0x004b6f40  CField::DetachLookPoint(int)   [DetachLookPoint__6CFieldFi]  size=0xb8 */
void DetachLookPoint__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  
  iVar1 = GetCtrlModel__6CFieldFv(this);
  if (iVar1 != 0) {
    if (((&this->field_0x3fe)[a0 * 0x10] & 0xf) != 0xf) {
      DspIcon__6CFieldFii(this,(int)(char)this->field_0x6cc,-1);
    }
    if ((byte)(&this->field_0x3fe)[a0 * 0x10] >> 4 != 0) {
      ClrViewPoint__11CFieldModelFv(iVar1);
    }
  }
  this->bClr_flag_5ec = 0;
  return;
}

/* JP: 0x004b7000  CField::AttachLookPoint(int)   [AttachLookPoint__6CFieldFi]  size=0x10c */
void AttachLookPoint__6CFieldFi(CField *this,int a0)

{
  undefined1 *puVar1;
  CField *pCVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 auStack_40 [12];
  undefined4 uStack_34;
  undefined4 uStack_24;
  CField *pCStack_20;
  int iStack_10;
  
  pCStack_20 = this;
  iStack_10 = a0;
  __ct__7FVectorFv(auStack_40);
  iVar3 = iStack_10;
  pCVar2 = pCStack_20;
  iVar5 = iStack_10 * 0x10;
  puVar1 = &pCStack_20->field_0x3f0;
  if (((&pCStack_20->field_0x3fe)[iStack_10 * 0x10] & 0xf) != 0xf) {
    DspIcon__6CFieldFii(pCStack_20,(int)(char)pCStack_20->field_0x6cc,
                        (byte)(&pCStack_20->field_0x3fe)[iStack_10 * 0x10] & 0xf);
  }
  if ((byte)(&pCVar2->field_0x3fe)[iVar3 * 0x10] >> 4 != 0) {
    GetShortPos4__FP7FVectorPs(auStack_40,puVar1 + iVar5);
    uStack_24 = uStack_34;
    uStack_34 = 0x3f800000;
    uVar4 = GetCtrlModel__6CFieldFv(pCStack_20);
    SetViewPoint__11CFieldModelFP7FVectorfii
              (uStack_24,uVar4,auStack_40,(byte)(&pCVar2->field_0x3fe)[iVar3 * 0x10] >> 4,
               0xffffffffffffffff);
  }
  pCStack_20->bClr_flag_5ec = (char)iStack_10 + 1;
  return;
}

/* JP: 0x004b71f0  CField::SetSavePoint(int, float*, int)   [SetSavePoint__6CFieldFiPfi]  size=0x360 */
int SetSavePoint__6CFieldFiPfi(CField *this,int a0,float *a1,int a2)

{
  FVector *pFVar1;
  void *a1_00;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  undefined1 *puVar5;
  float extraout_f0;
  float fVar6;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [4];
  float fStack_4c;
  undefined4 uStack_44;
  CField *pCStack_40;
  int iStack_30;
  float *pfStack_20;
  int iStack_10;
  
  puVar5 = &this->field_0x4f0;
  if (a0 < 0) {
    iVar2 = 0;
    for (; (iStack_30 = a0, iVar2 < 8 && (iStack_30 = iVar2, (puVar5[6] & 1) != 0));
        puVar5 = puVar5 + 0xc) {
      iVar2 = iVar2 + 1;
    }
    if (iStack_30 < 0) {
      return -1;
    }
  }
  else {
    puVar5 = puVar5 + a0 * 0xc;
    iStack_30 = a0;
  }
  pCStack_40 = this;
  pfStack_20 = a1;
  iStack_10 = a2;
  if ((*(int *)(puVar5 + 8) != 0) && (iVar2 = *(int *)(puVar5 + 8), iVar2 != 0)) {
    (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
  }
  if ((((ulong)*(ushort *)(puVar5 + 6) & 0x3fff) >> 4 != 0) && (pCStack_40->pNavimap != (void *)0x0)
     ) {
    RemoveItem__8CNaviMapFi
              (pCStack_40->pNavimap,(uint)(((ulong)*(ushort *)(puVar5 + 6) << 0x32) >> 0x36) - 1);
  }
  memset(puVar5,0,0xc);
  __ct__7FVectorFv(auStack_50);
  uStack_44 = 0x3f800000;
  memcpy(auStack_50,pfStack_20,0xc);
  if (iStack_10 != 0) {
    pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_60,auStack_50);
    a1_00 = (void *)OnFloorChk__9CFloorManF7FVector(pCStack_40->pFloor,pFVar1);
    if (a1_00 != (void *)0x0) {
      pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_70,auStack_50);
      fVar6 = extraout_f0;
      OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE(pCStack_40->pFloor,pFVar1,a1_00);
      fStack_4c = fVar6;
    }
  }
  fStack_4c = fStack_4c - 0.2;
  puVar5[6] = puVar5[6] & 0xfe | 1;
  SetShortPos__FPsP7FVector(puVar5,auStack_50);
  iVar2 = GetCtrlModel__6CFieldFv(pCStack_40);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = GetModel__11CFieldModelFv(iVar2);
  }
  CreateSavePoint__FP9_SavPointP5Model(puVar5,uVar3);
  if ((long)((ulong)pCStack_40->bFlags_18d << 0x3b) < 0) {
    Show__9SavePointFii(*(undefined4 *)(puVar5 + 8),10,0xb);
  }
  if ((pCStack_40->pNavimap != (void *)0x0) &&
     (lVar4 = AddItem__8CNaviMapFiR7FVectoriibUi(pCStack_40->pNavimap,0x10001,auStack_50,0,5,1,1),
     -1 < lVar4)) {
    *(ushort *)(puVar5 + 6) =
         *(ushort *)(puVar5 + 6) & 0xc00f | (ushort)(((int)lVar4 + 1U & 0x3ff) << 4);
  }
  return iStack_30;
}

/* JP: 0x004b7550  CField::UpdateSavePoint()   [UpdateSavePoint__6CFieldFv]  size=0xcc */
void UpdateSavePoint__6CFieldFv(CField *this)

{
  int iVar1;
  undefined1 *puVar2;
  undefined8 uVar3;
  
  iVar1 = GetCtrlModel__6CFieldFv(this);
  uVar3 = 0;
  if (iVar1 != 0) {
    uVar3 = GetModel__11CFieldModelFv(iVar1);
  }
  puVar2 = &this->field_0x4f0;
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    if (*(int *)(puVar2 + 8) != 0) {
      SetCheckModel__9SavePointFP5Model(*(int *)(puVar2 + 8),uVar3);
    }
    puVar2 = puVar2 + 0xc;
  }
  return;
}

/* JP: 0x004b7620  CField::ClrSavePoint(int)   [ClrSavePoint__6CFieldFi]  size=0x150 */
undefined8 ClrSavePoint__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 8;
  iVar3 = 0;
  if (-1 < a0) {
    iVar4 = a0 + 1;
    iVar3 = a0;
  }
  puVar2 = &this->field_0x4f0 + iVar3 * 0xc;
  for (; iVar3 < iVar4; iVar3 = iVar3 + 1) {
    puVar2[6] = puVar2[6] & 0xfe;
    if (*(int *)(puVar2 + 8) != 0) {
      iVar1 = *(int *)(puVar2 + 8);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
      }
      *(undefined4 *)(puVar2 + 8) = 0;
    }
    if ((this->pNavimap != (void *)0x0) && (((ulong)*(ushort *)(puVar2 + 6) & 0x3fff) >> 4 != 0)) {
      RemoveItem__8CNaviMapFi
                (this->pNavimap,(uint)(((ulong)*(ushort *)(puVar2 + 6) << 0x32) >> 0x36) - 1);
    }
    puVar2 = puVar2 + 0xc;
  }
  return 0;
}

/* JP: 0x004b7770  CField::ChkSavePoint()   [ChkSavePoint__6CFieldFv]  size=0xec */
int ChkSavePoint__6CFieldFv(CField *this)

{
  int iVar1;
  long lVar2;
  undefined1 *puVar3;
  
  iVar1 = GetCtrlModel__6CFieldFv(this);
  if ((iVar1 != 0) && (lVar2 = isDsp__11CFieldModelFv(iVar1), lVar2 != 0)) {
    puVar3 = &this->field_0x4f0;
    for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
      if ((*(int *)(puVar3 + 8) != 0) &&
         (lVar2 = IsOn__9SavePointFv(*(int *)(puVar3 + 8)), lVar2 != 0)) {
        return iVar1;
      }
      puVar3 = puVar3 + 0xc;
    }
  }
  return -1;
}

/* JP: 0x004b78b0  CField::ShowSavePoint(int)   [ShowSavePoint__6CFieldFi]  size=0x108 */
void ShowSavePoint__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  long lVar2;
  undefined1 *puVar3;
  
  iVar1 = GetCtrlModel__6CFieldFv(this);
  if ((iVar1 != 0) && (lVar2 = isDsp__11CFieldModelFv(iVar1), lVar2 == 0)) {
    GetModel__11CFieldModelFv(iVar1);
  }
  puVar3 = &this->field_0x4f0;
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    if ((puVar3[6] & 1) != 0) {
      if (a0 == 0) {
        Hide__9SavePointFv(*(undefined4 *)(puVar3 + 8));
      }
      else {
        Show__9SavePointFii(*(undefined4 *)(puVar3 + 8),10,0xb);
      }
    }
    puVar3 = puVar3 + 0xc;
  }
  return;
}

/* JP: 0x004b7ac0  CField::SetWarpPoint(int, float*, int, int)   [SetWarpPoint__6CFieldFiPfii]  size=0x2cc */
int SetWarpPoint__6CFieldFiPfii(CField *this,int a0,float *a1,int a2,int a3)

{
  FVector *pFVar1;
  void *a1_00;
  undefined1 *puVar2;
  int iVar3;
  bool bVar4;
  uint uVar5;
  float extraout_f0;
  float fVar6;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [4];
  float fStack_5c;
  undefined4 uStack_54;
  CField *pCStack_50;
  int iStack_40;
  float *pfStack_30;
  uint uStack_20;
  int iStack_10;
  
  puVar2 = &this->field_0x550;
  if (a0 < 0) {
    iVar3 = 0;
    for (; (iStack_40 = a0, iVar3 < 8 && (iStack_40 = iVar3, (puVar2[6] & 1) != 0));
        puVar2 = puVar2 + 0xc) {
      iVar3 = iVar3 + 1;
    }
    if (iStack_40 < 0) {
      return -1;
    }
  }
  else {
    puVar2 = puVar2 + a0 * 0xc;
    iStack_40 = a0;
  }
  pCStack_50 = this;
  pfStack_30 = a1;
  uStack_20 = a2;
  iStack_10 = a3;
  if ((*(int *)(puVar2 + 8) != 0) && (iVar3 = *(int *)(puVar2 + 8), iVar3 != 0)) {
    (**(code **)(*(int *)(iVar3 + 0x14) + 8))(iVar3,1);
  }
  memset(puVar2,0,0xc);
  __ct__7FVectorFv(auStack_60);
  uStack_54 = 0x3f800000;
  memcpy(auStack_60,pfStack_30,0xc);
  if (iStack_10 != 0) {
    pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_70,auStack_60);
    a1_00 = (void *)OnFloorChk__9CFloorManF7FVector(pCStack_50->pFloor,pFVar1);
    if (a1_00 != (void *)0x0) {
      pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_80,auStack_60);
      fVar6 = extraout_f0;
      OnFloorPoint__9CFloorManF7FVectorPQ23SDB12tagFTRIANGLE(pCStack_50->pFloor,pFVar1,a1_00);
      fStack_5c = fVar6;
    }
  }
  fStack_5c = fStack_5c - 0.2;
  uVar5 = uStack_20 & 0xff;
  puVar2[6] = puVar2[6] & 0xfe | 1;
  SetShortPos__FPsP7FVector(puVar2,auStack_60);
  CreateWarpPoint__FP9_WapPointi(puVar2,uVar5);
  bVar4 = (uStack_20 & 100) != 0;
  if ((uVar5 < 3) || (5 < uVar5)) {
    bVar4 = true;
  }
  puVar2[6] = puVar2[6] & 0xfb | bVar4 << 2;
  if ((long)((ulong)pCStack_50->bFlags_18d << 0x3b) < 0) {
    Show__9WarpPointFiib(*(undefined4 *)(puVar2 + 8),10,0xb,bVar4 != false);
  }
  return iStack_40;
}

/* JP: 0x004b7d90  CField::UpdateWarpPoint()   [UpdateWarpPoint__6CFieldFv]  size=0xcc */
void UpdateWarpPoint__6CFieldFv(CField *this)

{
  int iVar1;
  undefined1 *puVar2;
  undefined8 uVar3;
  
  iVar1 = GetCtrlModel__6CFieldFv(this);
  uVar3 = 0;
  if (iVar1 != 0) {
    uVar3 = GetModel__11CFieldModelFv(iVar1);
  }
  puVar2 = &this->field_0x550;
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    if (*(int *)(puVar2 + 8) != 0) {
      SetCheckModel__9WarpPointFP5Model(*(int *)(puVar2 + 8),uVar3);
    }
    puVar2 = puVar2 + 0xc;
  }
  return;
}

/* JP: 0x004b7e90  CField::ClrWarpPoint(int)   [ClrWarpPoint__6CFieldFi]  size=0x128 */
undefined8 ClrWarpPoint__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 8;
  iVar3 = 0;
  if (-1 < a0) {
    iVar4 = a0 + 1;
    iVar3 = a0;
  }
  puVar2 = &this->field_0x550 + iVar3 * 0xc;
  for (; iVar3 < iVar4; iVar3 = iVar3 + 1) {
    puVar2[6] = puVar2[6] & 0xfe;
    puVar2[6] = puVar2[6] & 0xfb;
    if (*(int *)(puVar2 + 8) != 0) {
      iVar1 = *(int *)(puVar2 + 8);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
      }
      *(undefined4 *)(puVar2 + 8) = 0;
    }
    puVar2 = puVar2 + 0xc;
  }
  return 0;
}

/* JP: 0x004b7fc0  CField::WarpFade(int, int)   [WarpFade__6CFieldFii]  size=0xe8 */
undefined8 WarpFade__6CFieldFii(CField *this,int a0,int a1)

{
  if (((&this->field_0x556)[a0 * 0xc] & 1) != 0) {
    if (a1 == 0) {
      StartShowEffect__9WarpPointFv(*(undefined4 *)(&this->field_0x558 + a0 * 0xc));
      (&this->field_0x556)[a0 * 0xc] = (&this->field_0x556)[a0 * 0xc] & 0xfb | 4;
    }
    else {
      StartHideEffect__9WarpPointFv(*(undefined4 *)(&this->field_0x558 + a0 * 0xc));
      (&this->field_0x556)[a0 * 0xc] = (&this->field_0x556)[a0 * 0xc] & 0xfb;
    }
    (&this->field_0x556)[a0 * 0xc] = (&this->field_0x556)[a0 * 0xc] & 0xfd | 2;
  }
  return 0;
}

/* JP: 0x004b80b0  CField::ShowWarpPoint(int)   [ShowWarpPoint__6CFieldFi]  size=0x120 */
void ShowWarpPoint__6CFieldFi(CField *this,int a0)

{
  int iVar1;
  long lVar2;
  undefined1 *puVar3;
  
  iVar1 = GetCtrlModel__6CFieldFv(this);
  if ((iVar1 != 0) && (lVar2 = isDsp__11CFieldModelFv(iVar1), lVar2 == 0)) {
    GetModel__11CFieldModelFv(iVar1);
  }
  puVar3 = &this->field_0x550;
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    if ((puVar3[6] & 1) != 0) {
      if (a0 == 0) {
        Hide__9WarpPointFv(*(undefined4 *)(puVar3 + 8));
      }
      else {
        Show__9WarpPointFiib
                  (*(undefined4 *)(puVar3 + 8),10,0xb,(long)((ulong)(byte)puVar3[6] << 0x3d) < 0);
      }
    }
    puVar3 = puVar3 + 0xc;
  }
  return;
}

/* JP: 0x004b81d0  CField::DoWarp(int, int, unsigned int, unsigned int)   [DoWarp__6CFieldFiiUiUi]  size=0x3b0 */
/* WARNING: Removing unreachable block (ram,0x004b838c) */
/* WARNING: Removing unreachable block (ram,0x004b84a8) */
/* WARNING: Removing unreachable block (ram,0x004b8418) */
/* WARNING: Removing unreachable block (ram,0x004b8344) */
/* WARNING: Removing unreachable block (ram,0x004b82b4) */
/* WARNING: Removing unreachable block (ram,0x004b82fc) */
/* WARNING: Removing unreachable block (ram,0x004b83d0) */
/* WARNING: Removing unreachable block (ram,0x004b8460) */

void DoWarp__6CFieldFiiUiUi(CField *this,int a0,int a1,uint a2,uint a3)

{
  undefined4 uVar1;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  CField *pCStack_50;
  int iStack_40;
  int iStack_30;
  uint uStack_20;
  uint uStack_10;
  
  pCStack_50 = this;
  iStack_40 = a0;
  iStack_30 = a1;
  uStack_20 = a2;
  uStack_10 = a3;
  __ct__7FVectorFv(&fStack_60);
  __ct__7FVectorFv(&fStack_70);
  if (uStack_20 == 0) {
    if (iStack_30 == 0) {
      uStack_20 = 0xfff0ff;
    }
    else {
      uStack_20 = 0x80ffffff;
    }
  }
  if (uStack_10 == 0) {
    if (iStack_30 == 0) {
      uStack_10 = 0x80ffffff;
    }
    else {
      uStack_10 = 0xfff0ff;
    }
  }
  *(undefined4 *)&pCStack_50->field_0x6e4 = 0;
  fStack_60 = (float)(uStack_20 & 0xff);
  fStack_5c = (float)(uStack_20 >> 8 & 0xff);
  fStack_58 = (float)(uStack_20 >> 0x10 & 0xff);
  fStack_54 = (float)(uStack_20 >> 0x18);
  fStack_70 = (float)(uStack_10 & 0xff);
  fStack_6c = (float)(uStack_10 >> 8 & 0xff);
  fStack_68 = (float)(uStack_10 >> 0x10 & 0xff);
  fStack_64 = (float)(uStack_10 >> 0x18);
  if ((((&pCStack_50->field_0x556)[iStack_40 * 0xc] & 1) != 0) &&
     (*(int *)(&pCStack_50->field_0x558 + iStack_40 * 0xc) != 0)) {
    if (iStack_30 == 0) {
      uVar1 = 0x4b0;
      WarpOut__9WarpPointFR7FVectorR7FVectorsb
                (*(undefined4 *)(&pCStack_50->field_0x558 + iStack_40 * 0xc),&fStack_60,&fStack_70,
                 0x4b0,1);
    }
    else {
      uVar1 = 0x578;
      WarpIn__9WarpPointFR7FVectorR7FVectorsb
                (*(undefined4 *)(&pCStack_50->field_0x558 + iStack_40 * 0xc),&fStack_60,&fStack_70,
                 0x578,0);
    }
    *(undefined4 *)&pCStack_50->field_0x708 = uVar1;
  }
  return;
}

/* JP: 0x004b8580  CField::IsWarp(int)   [IsWarp__6CFieldFi]  size=0x8c */
bool IsWarp__6CFieldFi(CField *this,int a0)

{
  bool bVar1;
  long lVar2;
  
  if ((((&this->field_0x556)[a0 * 0xc] & 1) == 0) || (*(int *)(&this->field_0x558 + a0 * 0xc) == 0))
  {
    bVar1 = false;
  }
  else {
    lVar2 = IsWarpEnded__9WarpPointFv(*(undefined4 *)(&this->field_0x558 + a0 * 0xc));
    bVar1 = lVar2 == 0;
  }
  return bVar1;
}

/* JP: 0x004b8670  CField::VibRelease()   [VibRelease__6CFieldFv]  size=0x98 */
void VibRelease__6CFieldFv(CField *this)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
    if (this->aVib[iVar1] != (void *)0x0) {
      __dt__5CVibeFv(this->aVib[iVar1],1);
    }
  }
  memset(this->aVib,0,0x10);
  return;
}

/* JP: 0x004b8710  CField::StartVib(int, int, int)   [StartVib__6CFieldFiii]  size=0x104 */
void StartVib__6CFieldFiii(CField *this,int a0,int a1,int a2)

{
  void *pvVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = FindGenericData__6CSTGDBFPCc(m_pSTGDB__6CField,ID_VIBRATION);
  lVar3 = 0;
  if (lVar2 != 0) {
    lVar3 = GetSeqData__8CVibeManFPvi((int)lVar2 + 0x20,a1);
  }
  if (lVar3 != 0) {
    pvVar1 = this->aVib[a0];
    if (pvVar1 == (void *)0x0) {
      lVar2 = __nw__FUi(0x44);
      pvVar1 = (void *)0x0;
      if (lVar2 != 0) {
        pvVar1 = (void *)__ct__5CVibeFv(lVar2);
      }
      this->aVib[a0] = pvVar1;
    }
    Volume__5CVibeFi(pvVar1,a2);
    Start__8CVibeManFP5CVibeP10_ActSeqHdri(sys__8CVibeMan,pvVar1,lVar3,0);
  }
  return;
}

/* JP: 0x004b8820  CField::StartVib(int, const char*, int)   [StartVib__6CFieldFiPCci]  size=0x128 */
void StartVib__6CFieldFiPCci(CField *this,int a0,char *a1,int a2)

{
  int iVar1;
  undefined1 *puVar2;
  void *pvVar3;
  long lVar4;
  undefined4 uStack_44;
  CField *pCStack_40;
  int iStack_30;
  char *pcStack_20;
  int iStack_10;
  
  pCStack_40 = this;
  iStack_30 = a0;
  pcStack_20 = a1;
  iStack_10 = a2;
  lVar4 = CnvSeqData__5CVibeFPCcRi(a1,&uStack_44);
  if (lVar4 != 0) {
    iVar1 = iStack_30 * 0x180;
    puVar2 = &pCStack_40->field_0x1d30;
    memcpy(puVar2 + iVar1,lVar4,uStack_44);
    __dla__FPv(lVar4);
    pvVar3 = pCStack_40->aVib[iStack_30];
    if (pvVar3 == (void *)0x0) {
      lVar4 = __nw__FUi(0x44);
      pvVar3 = (void *)0x0;
      if (lVar4 != 0) {
        pvVar3 = (void *)__ct__5CVibeFv(lVar4);
      }
      pCStack_40->aVib[iStack_30] = pvVar3;
    }
    Volume__5CVibeFi(pvVar3,iStack_10);
    Start__8CVibeManFP5CVibeP10_ActSeqHdri(sys__8CVibeMan,pvVar3,puVar2 + iVar1,0);
  }
  return;
}

/* JP: 0x004b8950  CField::VibControl(int, int, int, int)   [VibControl__6CFieldFiiii]  size=0x254 */
undefined1 VibControl__6CFieldFiiii(CField *this,int a0,int a1,int a2,int a3)

{
  undefined1 uVar1;
  long lVar2;
  void *unaff_s0_lo;
  
  uVar1 = 0;
  if (-1 < a1) {
    unaff_s0_lo = this->aVib[a1];
  }
  if (a0 == 3) {
    if (unaff_s0_lo != (void *)0x0) {
      uVar1 = isPlay__5CVibeFv(unaff_s0_lo);
    }
  }
  else if (a0 == 2) {
    if (a1 < 0) {
      Pause__8CVibeManFi(sys__8CVibeMan,a2);
    }
    else if (unaff_s0_lo != (void *)0x0) {
      Pause__5CVibeFi(unaff_s0_lo,a2);
    }
  }
  else if (a0 == 1) {
    if (a1 < 0) {
      if (a3 < 1) {
        Volume__8CVibeManFi(sys__8CVibeMan,a2);
      }
      else {
        SetFader__8CVibeManFii(sys__8CVibeMan,a2,a3);
      }
    }
    else if ((unaff_s0_lo != (void *)0x0) && (lVar2 = isPlay__5CVibeFv(unaff_s0_lo), lVar2 != 0)) {
      SetFader__5CVibeFiii(unaff_s0_lo,a2,a3,0);
    }
  }
  else if (a0 == 0) {
    if (a1 < 0) {
      if (a2 < 1) {
        ReleaseAllVibe__8CVibeManFv(sys__8CVibeMan);
      }
      else {
        SetFader__8CVibeManFii(sys__8CVibeMan,0,a2);
      }
    }
    else if (unaff_s0_lo != (void *)0x0) {
      lVar2 = isPlay__5CVibeFv(unaff_s0_lo);
      if ((lVar2 == 0) || (a2 < 1)) {
        __dt__5CVibeFv(unaff_s0_lo,1);
        this->aVib[a1] = (void *)0x0;
      }
      else {
        SetFader__5CVibeFiii(unaff_s0_lo,0,a2,1);
      }
    }
  }
  return uVar1;
}

/* JP: 0x004b8be0  CField::isLoadBusy()   [isLoadBusy__6CFieldFv]  size=0xc0 */
undefined4 isLoadBusy__6CFieldFv(CField *this)

{
  undefined4 uVar1;
  long lVar2;
  
  if (this->pBg == (CFieldBG *)0x0) {
    uVar1 = 1;
  }
  else if ((((this->field_0x6cb == '\0') && (lVar2 = GetModelReadCt__Fv(), lVar2 == 0)) &&
           (lVar2 = GetOrder__12CSndBufCacheFv(), lVar2 == 0)) &&
          (((*(short *)&this->field_0x1aa == 0 && (-1 < (long)((ulong)this->bFlags_18d << 0x3a))) &&
           ((this->bFlags_18e & 3) == 0)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x004b8cc0  CField::CheckEncount()   [CheckEncount__6CFieldFv]  size=0x520 */
/* WARNING: Removing unreachable block (ram,0x004b8fac) */
/* WARNING: Removing unreachable block (ram,0x004b8e68) */
/* WARNING: Removing unreachable block (ram,0x004b8dd8) */
/* WARNING: Removing unreachable block (ram,0x004b8f0c) */
/* WARNING: Removing unreachable block (ram,0x004b9048) */

undefined4 CheckEncount__6CFieldFv(CField *this)

{
  byte bVar1;
  int iVar2;
  long lVar3;
  undefined1 uVar4;
  undefined1 *puVar5;
  float fVar6;
  undefined4 uVar7;
  
  if ((this->wState == 2) && (m_pSTGDB__6CField != 0)) {
    puVar5 = &this->field_0x3c4;
    if (this->field_0x3c6 == '\0') {
      uVar7 = 0;
    }
    else {
      if (this->field_0x3c8 != '\0') {
        bVar1 = FieldChkEncountItem__Fv();
        this->field_0x3c8 = bVar1 | 0x80;
      }
      if (((ulong)this->bFlags_18d & 0xf) >> 2 == 0) {
        if (this->field_0x3c5 == '\0') {
          iVar2 = rand();
          fVar6 = (float)(byte)(&encDist)[iVar2 % 3];
          if (fVar6 < 2.1474836e+09) {
            uVar4 = (undefined1)(int)fVar6;
          }
          else {
            uVar4 = (undefined1)(int)(fVar6 - 2.1474836e+09);
          }
          this->field_0x3c5 = uVar4;
          if (this->field_0x3c8 == -0x7f) {
            fVar6 = (float)(byte)this->field_0x3c5 * 2.0;
            if (fVar6 < 2.1474836e+09) {
              uVar4 = (undefined1)(int)fVar6;
            }
            else {
              uVar4 = (undefined1)(int)(fVar6 - 2.1474836e+09);
            }
            this->field_0x3c5 = uVar4;
          }
          if (this->field_0x3c8 == -0x7e) {
            fVar6 = (float)(byte)this->field_0x3c5 * 0.5;
            if (fVar6 < 2.1474836e+09) {
              uVar4 = (undefined1)(int)fVar6;
            }
            else {
              uVar4 = (undefined1)(int)(fVar6 - 2.1474836e+09);
            }
            this->field_0x3c5 = uVar4;
          }
        }
        if (*(float *)&this->field_0x3cc * 0.1 < (float)(byte)this->field_0x3c5) {
          uVar7 = 0;
        }
        else {
          iVar2 = rand();
          iVar2 = iVar2 % 100;
          if (((ulong)this->bFlags_18e & 0x7f) >> 5 == 2) {
            iVar2 = 0;
          }
          uVar7 = *(undefined4 *)&this->field_0x3cc;
          fVar6 = (float)(byte)this->field_0x3c5;
          this->field_0x3c5 = 0;
          *(undefined4 *)&this->field_0x3cc = 0;
          if (this->field_0x3c6 == '\0') {
            uVar7 = 0;
          }
          else if (((byte)*puVar5 < 2) && ((int)(uint)(byte)this->field_0x3c6 <= iVar2)) {
            *puVar5 = *puVar5 + '\x01';
            uVar7 = 0;
          }
          else {
            iVar2 = isLoadBusy__6CFieldFv(this);
            if ((iVar2 == 0) && (lVar3 = isFaderDsp__12CFieldSocketFi(m_socket__12CFieldSocket,1), lVar3 == 0)) {
              if ((((ulong)this->bFlags_18e & 0x7f) >> 5 & 1) == 0) {
                uVar7 = 1;
              }
              else {
                uVar7 = 0;
              }
            }
            else {
              *(undefined4 *)&this->field_0x3cc = uVar7;
              if ((long)((ulong)this->bFlags_18d << 0x3a) < 0) {
                *(float *)&this->field_0x3cc = *(float *)&this->field_0x3cc - 1.0;
              }
              if (fVar6 < 2.1474836e+09) {
                uVar4 = (undefined1)(int)fVar6;
              }
              else {
                uVar4 = (undefined1)(int)(fVar6 - 2.1474836e+09);
              }
              this->field_0x3c5 = uVar4;
              *puVar5 = 2;
              uVar7 = 0;
            }
          }
        }
      }
      else {
        uVar7 = 0xffffffff;
      }
    }
  }
  else {
    uVar7 = 0xffffffff;
  }
  return uVar7;
}

/* JP: 0x004b91e0  CField::ScriptSuspend()   [ScriptSuspend__6CFieldFv]  size=0x48 */
void ScriptSuspend__6CFieldFv(CField *this)

{
  ResetEvent__7CScriptFv(fldScript__12CFieldSocket);
  Pause__7CScriptFi(fldScript__12CFieldSocket,1);
  Pause__6CFieldFi(this,0);
  return;
}

/* JP: 0x004b9230  CField::InvokeBattle(int, int, int, int, int, int)   [InvokeBattle__6CFieldFiiiiii]  size=0x300 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 InvokeBattle__6CFieldFiiiiii(CField *this,int a0,int a1,int a2,int a3,int a4,int a5)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  undefined8 uVar5;
  long lVar6;
  byte bVar7;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  
  this->field_0x3c5 = 0;
  *(undefined4 *)&this->field_0x3cc = 0;
  Clear__12CSndBufCacheFv();
  SaveModel__6CFieldFv(this);
  FieldCameraID__Fi(this->nCamera_id);
  ResetSE__6CFieldFv(this);
  SaveScriptRegister__12CFieldSocketFv(m_socket__12CFieldSocket);
  if (((ulong)this->bFlags_18e & 0x7f) >> 5 == 3) {
    uVar5 = GetCurMPSname__12CFieldSocketFv(m_socket__12CFieldSocket);
    uVar2 = FieldMapJump__FPCci(uVar5,0xfffffffffffffffe);
  }
  else {
    lVar6 = GetFieldScript__Fi(1);
    if (lVar6 != 0) {
      Delete__7CScriptFv(lVar6);
    }
    pcVar3 = (char *)GetParty__15SaveMenuSectionFv();
    iStack_30 = a3;
    if (a3 < 0) {
      iStack_30 = (int)*pcVar3;
    }
    iVar4 = GetFieldBattleInfo__Fv();
    iStack_40 = a2;
    if (a2 < 0) {
      iStack_40 = (int)*(short *)(iVar4 + 2);
    }
    iStack_50 = a1;
    if (a1 < 0) {
      iStack_50 = (int)*(short *)(iVar4 + 4);
    }
    if (iStack_40 == 0) {
      iStack_40 = 0x191;
    }
    if (iStack_50 < 0) {
      iStack_50 = 0;
    }
    memset(0x55f180,0,0x10);
    _btlParam = iStack_50;
    uRam0055f188 = (undefined2)iStack_40;
    uRam0055f18b = (undefined1)a5;
    cVar1 = pcVar3[iStack_30 * 0x20 + 0x15];
    iRam0055f184 = a4;
    uVar2 = memcpy(0x55f18c,pcVar3 + iStack_30 * 0x20 + 0x16,cVar1);
    cRam0055f18a = cVar1;
    if ((ourBtlIn__5BtlIn == 0) && (ourBtlIn__9BtlInBoss == 0)) {
      if (a0 == 0) {
        bVar7 = 1;
      }
      else {
        bVar7 = 2;
      }
      this->bFlags_18d = this->bFlags_18d & 0xfc | bVar7;
      if ((this->bFlags_18d & 3) == 1) {
        uVar2 = CaptureBtlIn__5BtlInFv();
      }
      else {
        uVar2 = CaptureBtlIn__9BtlInBossFv();
      }
    }
    else {
      this->bFlags_18d = this->bFlags_18d & 0xfc | 3;
    }
  }
  return uVar2;
}

/* JP: 0x004b9550  CField::SetCamera(float*, int, float, int)   [SetCamera__6CFieldFPfifi]  size=0xa4 */
undefined4 SetCamera__6CFieldFPfifi(CField *this,float *a0,int a1,float a2,int a3)

{
  undefined4 uVar1;
  undefined1 auStack_60 [16];
  CField *pCStack_50;
  float *pfStack_40;
  int iStack_30;
  float fStack_20;
  int iStack_10;
  
  pCStack_50 = this;
  pfStack_40 = a0;
  iStack_30 = a1;
  fStack_20 = a2;
  iStack_10 = a3;
  __ct__7FVectorFv(auStack_60);
  memcpy(auStack_60,pfStack_40,0x10);
  uVar1 = SetShortPos4__FPsP7FVector(&pCStack_50->field_0x194,auStack_60);
  pCStack_50->bScr_camera_active = 1;
  pCStack_50->field_0x1a9 = 0;
  *(short *)&pCStack_50->field_0x19c = (short)iStack_30;
  *(float *)&pCStack_50->field_0x1a4 = fStack_20;
  pCStack_50->field_0x1a8 = (char)iStack_10;
  return uVar1;
}

/* JP: 0x004b9600  CField::SetCamera(float*, int, int, float)   [SetCamera__6CFieldFPfiif]  size=0xa8 */
undefined4 SetCamera__6CFieldFPfiif(CField *this,float *a0,int a1,int a2,float a3)

{
  undefined4 uVar1;
  undefined1 auStack_60 [16];
  CField *pCStack_50;
  float *pfStack_40;
  int iStack_30;
  int iStack_20;
  float fStack_10;
  
  pCStack_50 = this;
  pfStack_40 = a0;
  iStack_30 = a1;
  iStack_20 = a2;
  fStack_10 = a3;
  __ct__7FVectorFv(auStack_60);
  memcpy(auStack_60,pfStack_40,0x10);
  uVar1 = SetShortPos4__FPsP7FVector(&pCStack_50->field_0x194,auStack_60);
  pCStack_50->bScr_camera_active = 2;
  pCStack_50->field_0x1a9 = 0;
  *(short *)&pCStack_50->field_0x19c = (short)iStack_30;
  *(short *)&pCStack_50->field_0x19c = (short)iStack_20;
  *(float *)&pCStack_50->field_0x1a4 = fStack_10;
  return uVar1;
}

/* JP: 0x004b96b0  CField::SetCamera(int, float*, float*, float)   [SetCamera__6CFieldFiPfPff]  size=0xb0 */
undefined4 SetCamera__6CFieldFiPfPff(CField *this,int a0,float *a1,float *a2,float a3)

{
  undefined4 uVar1;
  undefined1 auStack_60 [16];
  CField *pCStack_50;
  int iStack_40;
  float *pfStack_30;
  float *pfStack_20;
  float fStack_10;
  
  pCStack_50 = this;
  iStack_40 = a0;
  pfStack_30 = a1;
  pfStack_20 = a2;
  fStack_10 = a3;
  __ct__7FVectorFv(auStack_60);
  memcpy(auStack_60,pfStack_30,0x10);
  SetShortPos4__FPsP7FVector(&pCStack_50->field_0x194,auStack_60);
  memcpy(auStack_60,pfStack_20,0x10);
  uVar1 = SetShortPos4__FPsP7FVector(&pCStack_50->field_0x19c,auStack_60);
  pCStack_50->bScr_camera_active = (char)iStack_40 + 3;
  pCStack_50->field_0x1a9 = 0;
  *(float *)&pCStack_50->field_0x1a4 = fStack_10;
  return uVar1;
}

/* JP: 0x004b9760  CField::RestoreCamera(float)   [RestoreCamera__6CFieldFf]  size=0x38 */
void RestoreCamera__6CFieldFf(CField *this,float a0)

{
  *(float *)&this->field_0x1a4 = a0;
  this->bScr_camera_active = 7;
  this->field_0x1a9 = 0;
  return;
}

/* JP: 0x004b97a0  CField::GetCamPath(int, FVector*, float)   [GetCamPath__6CFieldFiP7FVectorf]  size=0x7a4 */
int GetCamPath__6CFieldFiP7FVectorf(CField *this,int a0,FVector *a1,float a2)

{
  FVector *pFVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  float afStack_100 [4];
  float fStack_f0;
  float afStack_e0 [4];
  float fStack_d0;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  FVector FStack_80;
  undefined1 auStack_70 [16];
  FVector FStack_60;
  float fStack_4c;
  float fStack_48;
  void *pvStack_44;
  CField *pCStack_40;
  void *pvStack_30;
  FVector *pFStack_20;
  
  pCStack_40 = this;
  pvStack_30 = (void *)a0;
  pFStack_20 = a1;
  __ct__7FVectorFRC7FVector(&FStack_60,&this->player_pos);
  ReverseVector__6CFieldFR7FVector(pCStack_40,&FStack_60);
  __ct__7FVectorFv(&FStack_80);
  __ct__7FVectorFv(auStack_70);
  __ct__7FVectorFv(auStack_a0);
  __ct__7FVectorFv(auStack_90);
  __ct__7FVectorFv(auStack_c0);
  __ct__7FVectorFv(auStack_b0);
  iVar3 = *(int *)(m_pCAMDAT__6CField + 8);
  __as__7FVectorFRC7FVector(&FStack_80,iVar3 + (int)pvStack_30 * 0x40 + 0x30);
  __as__7FVectorFRC7FVector(auStack_70,iVar3 + ((int)pvStack_30 - 1U) * 0x40 + 0x30);
  pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_110,&FStack_60);
  iVar2 = ChkPathPoint__6CFieldF7FVectorP7FVectorPf(pCStack_40,pFVar1,&FStack_80,afStack_e0);
  __as__7FVectorFRC7FVector(&FStack_80,iVar3 + (int)pvStack_30 * 0x40 + 0x10);
  __as__7FVectorFRC7FVector(auStack_70,iVar3 + ((int)pvStack_30 - 1U) * 0x40 + 0x10);
  GetPathPoint__6CFieldFfP7FVector((CField *)auStack_120,afStack_e0[0],(FVector *)pCStack_40);
  __as__7FVectorFRC7FVector(auStack_a0,auStack_120);
  __as__7FVectorFRC7FVector(&FStack_80,iVar3 + (int)pvStack_30 * 0x40);
  __as__7FVectorFRC7FVector(auStack_70,iVar3 + ((int)pvStack_30 - 1U) * 0x40);
  GetPathPoint__6CFieldFfP7FVector((CField *)auStack_130,afStack_e0[0],(FVector *)pCStack_40);
  __as__7FVectorFRC7FVector(auStack_c0,auStack_130);
  __as__7FVectorFRC7FVector(pFStack_20,auStack_a0);
  __as__7FVectorFRC7FVector(pFStack_20 + 1,auStack_c0);
  if (iVar2 == 1) {
    iVar3 = -1;
  }
  else if ((iVar2 == -1) && ((void *)(*(int *)(m_pCAMDAT__6CField + 4) - 1U) <= pvStack_30)) {
    iVar3 = 2;
  }
  else if (pvStack_30 < (void *)(*(int *)(m_pCAMDAT__6CField + 4) - 1U)) {
    __as__7FVectorFRC7FVector(&FStack_80,iVar3 + (int)pvStack_30 * 0x40 + 0x30);
    __as__7FVectorFRC7FVector(auStack_70,iVar3 + ((int)pvStack_30 + 1U) * 0x40 + 0x30);
    pFVar1 = (FVector *)__ct__7FVectorFRC7FVector(auStack_140,&FStack_60);
    iVar4 = ChkPathPoint__6CFieldF7FVectorP7FVectorPf(pCStack_40,pFVar1,&FStack_80,afStack_100);
    __as__7FVectorFRC7FVector(&FStack_80,iVar3 + (int)pvStack_30 * 0x40 + 0x10);
    __as__7FVectorFRC7FVector(auStack_70,iVar3 + ((int)pvStack_30 + 1U) * 0x40 + 0x10);
    GetPathPoint__6CFieldFfP7FVector((CField *)auStack_150,afStack_100[0],(FVector *)pCStack_40);
    __as__7FVectorFRC7FVector(auStack_90,auStack_150);
    __as__7FVectorFRC7FVector(&FStack_80,iVar3 + (int)pvStack_30 * 0x40);
    __as__7FVectorFRC7FVector(auStack_70,iVar3 + ((int)pvStack_30 + 1U) * 0x40);
    GetPathPoint__6CFieldFfP7FVector((CField *)auStack_160,afStack_100[0],(FVector *)pCStack_40);
    __as__7FVectorFRC7FVector(auStack_b0,auStack_160);
    if (iVar4 == 1) {
      __as__7FVectorFRC7FVector(pFStack_20,auStack_90);
      __as__7FVectorFRC7FVector(pFStack_20 + 1,auStack_b0);
      iVar3 = 2;
    }
    else {
      pvStack_44 = (void *)(fStack_f0 - fStack_d0);
      __mi__7FVectorCFRC7FVector(auStack_170,&FStack_60,iVar3 + (int)pvStack_30 * 0x40 + 0x30);
      __as__7FVectorFRC7FVector(&FStack_80,auStack_170);
      fStack_48 = (float)atan2f(FStack_80.flX,FStack_80.flZ);
      fStack_48 = fStack_48 - fStack_d0;
      clipRadian__FRf(&pvStack_44);
      clipRadian__FRf(&fStack_48);
      if ((float)pvStack_44 < 0.0) {
        pvStack_44 = (void *)-(float)pvStack_44;
        fStack_48 = -fStack_48;
      }
      iVar3 = 0;
      if ((fStack_48 < 0.0) || ((float)pvStack_44 == 0.0)) {
        if (iVar2 == -1) {
          __as__7FVectorFRC7FVector(pFStack_20,auStack_90);
          __as__7FVectorFRC7FVector(pFStack_20 + 1,auStack_b0);
        }
      }
      else if ((float)pvStack_44 <= fStack_48) {
        __as__7FVectorFRC7FVector(pFStack_20,auStack_90);
        __as__7FVectorFRC7FVector(pFStack_20 + 1,auStack_b0);
      }
      else if (afStack_e0[0] < 0.5) {
        if (1.570796 < (float)pvStack_44) {
          pvStack_44 = (void *)0x3fc90fd8;
        }
        fStack_4c = (fStack_48 / (float)pvStack_44) * (0.5 - afStack_e0[0]) * 2.0;
        if (1.0 < fStack_4c) {
          fStack_4c = 1.0;
        }
        GetPathPoint__6CFieldFfP7FVector((CField *)auStack_180,fStack_4c,(FVector *)pCStack_40);
        __as__7FVectorFRC7FVector(&FStack_80,auStack_180);
        __as__7FVectorFRC7FVector(pFStack_20,&FStack_80);
        GetPathPoint__6CFieldFfP7FVector((CField *)auStack_190,fStack_4c,(FVector *)pCStack_40);
        __as__7FVectorFRC7FVector(&FStack_80,auStack_190);
        __as__7FVectorFRC7FVector(pFStack_20 + 1,&FStack_80);
        if (0.5 < afStack_100[0]) {
          fStack_4c = (afStack_100[0] - 0.5) * 2.0;
          __as__7FVectorFRC7FVector(auStack_a0,pFStack_20);
          __as__7FVectorFRC7FVector(auStack_c0,pFStack_20 + 1);
          GetPathPoint__6CFieldFfP7FVector((CField *)auStack_1a0,fStack_4c,(FVector *)pCStack_40);
          __as__7FVectorFRC7FVector(&FStack_80,auStack_1a0);
          __as__7FVectorFRC7FVector(pFStack_20,&FStack_80);
          GetPathPoint__6CFieldFfP7FVector((CField *)auStack_1b0,fStack_4c,(FVector *)pCStack_40);
          __as__7FVectorFRC7FVector(&FStack_80,auStack_1b0);
          __as__7FVectorFRC7FVector(pFStack_20 + 1,&FStack_80);
        }
        iVar3 = 1;
      }
      if ((iVar2 == -1) && (iVar3 == 0)) {
        iVar3 = 2;
      }
    }
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}

/* JP: 0x004bb1c0  CField::GetCamPathA(int, FVector*, float)   [GetCamPathA__6CFieldFiP7FVectorf]  size=0x5a4 */
/* WARNING: Removing unreachable block (ram,0x004bb2dc) */
/* WARNING: Removing unreachable block (ram,0x004bb28c) */
/* WARNING: Removing unreachable block (ram,0x004bb640) */

undefined4 GetCamPathA__6CFieldFiP7FVectorf(CField *this,int a0,FVector *a1,float a2)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [24];
  undefined1 auStack_68 [12];
  int iStack_5c;
  undefined4 uStack_58;
  float fStack_54;
  int iStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  CField *pCStack_40;
  int iStack_30;
  FVector *pFStack_20;
  float fStack_10;
  
  iVar1 = *(int *)(m_pCAMDAT__6CField + 8);
  iVar2 = *(int *)(m_pCAMDAT__6CField + 4);
  pCStack_40 = this;
  iStack_30 = a0;
  pFStack_20 = a1;
  fStack_10 = a2;
  __ct__7FVectorFv(auStack_a0);
  __ct__7FVectorFv(auStack_90);
  __ct__7FVectorFv(auStack_80);
  if (iVar2 + -1 <= iStack_30) {
    iStack_30 = iVar2 + -2;
    fStack_10 = 1.0;
  }
  fStack_44 = (float)*(ushort *)(iVar1 + iStack_30 * 0x40 + 0x20);
  fStack_48 = (float)*(ushort *)(iVar1 + (iStack_30 + 1) * 0x40 + 0x20);
  if (fStack_44 == 0.0) {
    fStack_44 = 320.0;
  }
  if (fStack_48 == 0.0) {
    fStack_48 = 320.0;
  }
  fStack_4c = fStack_44 + fStack_10 * (fStack_48 - fStack_44);
  __as__7FVectorFRC7FVector(auStack_a0,iVar1 + iStack_30 * 0x40 + 0x10);
  __as__7FVectorFRC7FVector(auStack_90,iVar1 + (iStack_30 + 1) * 0x40 + 0x10);
  GetPathPoint__6CFieldFfP7FVector((CField *)auStack_b0,fStack_10,(FVector *)pCStack_40);
  __as__7FVectorFRC7FVector(pFStack_20,auStack_b0);
  __as__7FVectorFRC7FVector(auStack_a0,iVar1 + iStack_30 * 0x40);
  __as__7FVectorFRC7FVector(auStack_90,iVar1 + (iStack_30 + 1) * 0x40);
  GetPathPoint__6CFieldFfP7FVector((CField *)auStack_c0,fStack_10,(FVector *)pCStack_40);
  __as__7FVectorFRC7FVector(pFStack_20 + 1,auStack_c0);
  pFStack_20[1].flW = fStack_4c;
  if (fStack_10 < 0.0) {
    iStack_30 = iStack_30 + -1;
    fStack_10 = fStack_10 + 1.0;
  }
  iVar5 = 0;
  iStack_50 = iVar2;
  for (iVar4 = 0; iVar4 < iVar2; iVar4 = iVar4 + 1) {
    iVar6 = iVar5;
    if ((*(float *)(iVar1 + iVar4 * 0x40 + 0x3c) == 2.0) && (iVar6 = iVar4, iStack_30 < iVar4)) {
      iStack_50 = iVar4 + 1;
      iVar6 = iVar5;
    }
    iVar5 = iVar6;
  }
  __ct__9FldSplineFv(auStack_68);
  Create__9FldSplineFUiUiP7FVector(auStack_68,1,0,0);
  iVar4 = iStack_50 - iVar5;
  uVar3 = __nwa__FUi(iVar4 * 0x10 + 0x10);
  iVar2 = __construct_new_array(uVar3,0x430c50,0,0x10,iVar4);
  iStack_5c = iVar2;
  for (iVar6 = 0; iVar6 < iVar4; iVar6 = iVar6 + 1) {
    __as__7FVectorFRC7FVector(iVar2 + iVar6 * 0x10,iVar1 + (iVar6 + iVar5) * 0x40 + 0x10);
  }
  SetPoint__9FldSplineFUiP7FVector(auStack_68,iVar4,iVar2);
  GetPosition__9FldSplineFf(fStack_10 + (float)(iStack_30 - iVar5),auStack_d0,auStack_68);
  __as__7FVectorFRC7FVector(pFStack_20,auStack_d0);
  for (iVar6 = 0; iVar6 < iVar4; iVar6 = iVar6 + 1) {
    __as__7FVectorFRC7FVector(iVar2 + iVar6 * 0x10,iVar1 + (iVar6 + iVar5) * 0x40);
    fStack_54 = (float)*(ushort *)(iVar1 + (iVar6 + iVar5) * 0x40 + 0x20);
    if (fStack_54 == 0.0) {
      fStack_54 = 320.0;
    }
    *(float *)(iVar2 + iVar6 * 0x10 + 0xc) = fStack_54;
  }
  SetPoint__9FldSplineFUiP7FVector(auStack_68,iVar4,iVar2);
  GetPosition__9FldSplineFf(fStack_10 + (float)(iStack_30 - iVar5),auStack_e0,auStack_68);
  __as__7FVectorFRC7FVector(pFStack_20 + 1,auStack_e0);
  if (iVar2 != 0) {
    __dla__FPv(iVar2 + -0x10);
  }
  uStack_58 = 0;
  __dt__9FldSplineFv(auStack_68,0xffffffffffffffff);
  return uStack_58;
}

/* JP: 0x004bb770  CField::GetCamPath2(FVector*, int, FVector)   [GetCamPath2__6CFieldFP7FVectori7FVector]  size=0x5a4 */
/* WARNING: Removing unreachable block (ram,0x004bb898) */

undefined4 GetCamPath2__6CFieldFP7FVectori7FVector(CField *this,FVector *a0,int a1,FVector *a2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  float extraout_f0;
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  FVector FStack_120;
  undefined1 auStack_110 [16];
  FVector FStack_100;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [24];
  float afStack_58 [5];
  float fStack_44;
  CField *pCStack_40;
  FVector *pFStack_30;
  int iStack_20;
  FVector *pFStack_10;
  
  iVar1 = *(int *)(m_pCAMDAT__6CField + 8);
  pCStack_40 = this;
  pFStack_30 = a0;
  iStack_20 = a1;
  pFStack_10 = a2;
  __ct__7FVectorFv(auStack_70);
  __ct__7FVectorFv(auStack_80);
  __ct__7FVectorFv(auStack_90);
  __ct__7FVectorFv(auStack_b0);
  __ct__7FVectorFv(auStack_a0);
  __ct__7FVectorFv(auStack_e0);
  __ct__7FVectorFv(auStack_d0);
  __ct__7FVectorFv(auStack_c0);
  __ct__7FVectorFv(&FStack_120);
  __ct__7FVectorFv(auStack_110);
  __ct__7FVectorFv(&FStack_100);
  __ct__7FVectorFv(auStack_f0);
  __as__7FVectorFRC7FVector(pFStack_30,iVar1 + iStack_20 * 0x40 + 0x10);
  __as__7FVectorFRC7FVector(pFStack_30 + 1,iVar1 + iStack_20 * 0x40);
  fStack_44 = (float)*(ushort *)(iVar1 + iStack_20 * 0x40 + 0x20);
  if (fStack_44 == 0.0) {
    fStack_44 = 320.0;
  }
  pFStack_30[1].flW = fStack_44;
  __as__7FVectorFRC7FVector(auStack_70,iVar1 + iStack_20 * 0x40 + 0x30);
  iVar3 = 0;
  while( true ) {
    if (1 < iVar3) {
      GetCamPath__6CFieldFiP7FVectorf(pCStack_40,iStack_20 + -1,&FStack_120,1.0 - afStack_58[0]);
      GetCamPath__6CFieldFiP7FVectorf(pCStack_40,iStack_20,&FStack_100,afStack_58[1]);
      __as__7FVectorFRC7FVector(auStack_80,&FStack_120);
      __as__7FVectorFRC7FVector(auStack_90,&FStack_100);
      __mi__7FVectorCFRC7FVector(auStack_180,auStack_80,auStack_90);
      __ml__7FVectorCFf(afStack_58[0] * 2.0,auStack_170,auStack_180);
      __pl__7FVectorCFRC7FVector(auStack_160,auStack_90,auStack_170);
      __as__7FVectorFRC7FVector(auStack_a0,auStack_160);
      __mi__7FVectorCFRC7FVector(auStack_1b0,auStack_90,auStack_80);
      __ml__7FVectorCFf(afStack_58[1] * 2.0,auStack_1a0,auStack_1b0);
      __pl__7FVectorCFRC7FVector(auStack_190,auStack_80,auStack_1a0);
      __as__7FVectorFRC7FVector(auStack_b0,auStack_190);
      __pl__7FVectorCFRC7FVector(auStack_1d0,auStack_b0,auStack_a0);
      __ml__7FVectorCFf(0x3f000000,auStack_1c0,auStack_1d0);
      __as__7FVectorFRC7FVector(pFStack_30,auStack_1c0);
      __as__7FVectorFRC7FVector(auStack_80,auStack_110);
      __as__7FVectorFRC7FVector(auStack_90,auStack_f0);
      __mi__7FVectorCFRC7FVector(auStack_200,auStack_80,auStack_90);
      __ml__7FVectorCFf(afStack_58[0] * 2.0,auStack_1f0,auStack_200);
      __pl__7FVectorCFRC7FVector(auStack_1e0,auStack_90,auStack_1f0);
      __as__7FVectorFRC7FVector(auStack_a0,auStack_1e0);
      __mi__7FVectorCFRC7FVector(auStack_230,auStack_90,auStack_80);
      __ml__7FVectorCFf(afStack_58[1] * 2.0,auStack_220,auStack_230);
      __pl__7FVectorCFRC7FVector(auStack_210,auStack_80,auStack_220);
      __as__7FVectorFRC7FVector(auStack_b0,auStack_210);
      __pl__7FVectorCFRC7FVector(auStack_250,auStack_b0,auStack_a0);
      __ml__7FVectorCFf(0x3f000000,auStack_240,auStack_250);
      uVar2 = __as__7FVectorFRC7FVector(pFStack_30 + 1,auStack_240);
      pFStack_30[1].flW = 320.0;
      return uVar2;
    }
    if (iVar3 == 0) {
      __mi__7FVectorCFRC7FVector(auStack_130,iVar1 + (iStack_20 + -1) * 0x40 + 0x30,auStack_70);
      __as__7FVectorFRC7FVector(auStack_80,auStack_130);
    }
    else {
      __mi__7FVectorCFRC7FVector(auStack_140,iVar1 + (iStack_20 + 1) * 0x40 + 0x30,auStack_70);
      __as__7FVectorFRC7FVector(auStack_80,auStack_140);
    }
    uVar2 = Length__7FVectorCFv(auStack_80);
    if (extraout_f0 == 0.0) break;
    afStack_58[4] = extraout_f0;
    Normalize__7FVectorFv(auStack_80);
    __mi__7FVectorCFRC7FVector(auStack_150,pFStack_10,auStack_70);
    __as__7FVectorFRC7FVector(auStack_90,auStack_150);
    afStack_58[3] = (float)InnerProduct__7FVectorCFRC7FVector(auStack_90,auStack_80);
    afStack_58[3] = afStack_58[3] / afStack_58[4];
    if (afStack_58[3] < 0.0) {
      afStack_58[3] = 0.0;
    }
    if (1.0 < afStack_58[3]) {
      afStack_58[3] = 1.0;
    }
    afStack_58[iVar3] = afStack_58[3];
    iVar3 = iVar3 + 1;
  }
  return uVar2;
}

/* JP: 0x004bbd20  CField::ChkPathPoint(FVector, FVector*, float*)   [ChkPathPoint__6CFieldF7FVectorP7FVectorPf]  size=0x27c */
undefined4 ChkPathPoint__6CFieldF7FVectorP7FVectorPf(CField *this,FVector *a0,FVector *a1,float *a2)

{
  undefined4 uVar1;
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  float afStack_c0 [2];
  float fStack_b8;
  undefined1 auStack_b0 [4];
  float fStack_ac;
  float fStack_a8;
  undefined4 auStack_a0 [2];
  undefined4 uStack_98;
  undefined1 auStack_90 [72];
  float fStack_48;
  undefined4 uStack_44;
  FVector *pFStack_30;
  FVector *pFStack_20;
  float *pfStack_10;
  
  pFStack_30 = a0;
  pFStack_20 = a1;
  pfStack_10 = a2;
  __ct__6MatrixFv(auStack_90);
  __ct__7FVectorFv(auStack_a0);
  __ct__7FVectorFv(auStack_b0);
  __ct__7FVectorFv(afStack_c0);
  uVar1 = 0;
  __mi__7FVectorCFRC7FVector(auStack_d0,pFStack_20 + 1,pFStack_20);
  __as__7FVectorFRC7FVector(auStack_a0,auStack_d0);
  fStack_48 = (float)atan2f(auStack_a0[0],uStack_98);
  fStack_48 = -fStack_48;
  UnitMatrix__6MatrixFv(auStack_90);
  RotYMatrix__6MatrixFf(fStack_48,auStack_90);
  pfStack_10[4] = -fStack_48;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_e0,auStack_90,auStack_a0);
  __as__7FVectorFRC7FVector(auStack_b0,auStack_e0);
  uStack_44 = atan2f(-fStack_ac,-fStack_a8);
  RotXMatrix__6MatrixFf(uStack_44,auStack_90);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_f0,auStack_90,auStack_a0);
  __as__7FVectorFRC7FVector(auStack_b0,auStack_f0);
  if (fStack_a8 == 0.0) {
    memset(pfStack_10,0,0x14);
    uVar1 = 0xffffffff;
  }
  else {
    __mi__7FVectorCFRC7FVector(auStack_100,pFStack_30,pFStack_20);
    __as__7FVectorFRC7FVector(auStack_a0,auStack_100);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_110,auStack_90,auStack_a0);
    __as__7FVectorFRC7FVector(afStack_c0,auStack_110);
    if (0.0 < fStack_b8) {
      fStack_b8 = 0.0;
      uVar1 = 0xffffffff;
    }
    if (fStack_b8 < fStack_a8) {
      fStack_b8 = fStack_a8;
      uVar1 = 1;
    }
    pfStack_10[3] = afStack_c0[0];
    if (pfStack_10[3] < 0.0) {
      pfStack_10[3] = -afStack_c0[0];
    }
    pfStack_10[1] = -fStack_b8;
    pfStack_10[2] = -fStack_a8;
    *pfStack_10 = fStack_b8 / fStack_a8;
  }
  return uVar1;
}

/* JP: 0x004bbfa0  CField::GetPathPoint(float, FVector*)   [GetPathPoint__6CFieldFfP7FVector]  size=0xa0 */
undefined4 GetPathPoint__6CFieldFfP7FVector(CField *this,float a0,FVector *a1)

{
  undefined4 uVar1;
  int in_a2_lo;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [12];
  undefined4 uStack_44;
  CField *pCStack_40;
  float fStack_20;
  int iStack_10;
  
  pCStack_40 = this;
  fStack_20 = a0;
  iStack_10 = in_a2_lo;
  __ct__7FVectorFv(auStack_50,a1);
  __mi__7FVectorCFRC7FVector(auStack_80,iStack_10 + 0x10,iStack_10);
  __ml__7FVectorCFf(fStack_20,auStack_70,auStack_80);
  __pl__7FVectorCFRC7FVector(auStack_60,iStack_10,auStack_70);
  __as__7FVectorFRC7FVector(auStack_50,auStack_60);
  uStack_44 = 0x3f800000;
  uVar1 = __ct__7FVectorFRC7FVector(pCStack_40,auStack_50);
  return uVar1;
}

/* JP: 0x004cc3e0  CField::isPaused()   [isPaused__6CFieldFv]  size=0x24 */
long isPaused__6CFieldFv(CField *this)

{
  return ((ulong)this->bFlags_18d & 0xf) >> 2;
}

/* JP: 0x004d56b0  CField::OnLoadBGM()   [OnLoadBGM__6CFieldFv]  size=0x7c */
void OnLoadBGM__6CFieldFv(CField *this)

{
  memcpy(&this->field_0x158,&this->field_0x160,8);
  this->bFlags_190 = this->bFlags_190 & 0xfc | 2;
  this->bFlags_190 = this->bFlags_190 & 0xef | 0x10;
  return;
}

/* JP: 0x004d57c0  CField::SetObjSE(int, unsigned int, unsigned int, int, FVector*)   [SetObjSE__6CFieldFiUiUiiP7FVector]  size=0x1c8 */
int SetObjSE__6CFieldFiUiUiiP7FVector(CField *this,int a0,uint a1,uint a2,int a3,FVector *a4)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  uint uStack_90;
  byte bStack_8c;
  byte bStack_8b;
  undefined1 auStack_88 [40];
  CField *pCStack_60;
  int iStack_50;
  uint uStack_40;
  uint uStack_30;
  uint uStack_20;
  FVector *pFStack_10;
  
  pCStack_60 = this;
  iStack_50 = a0;
  uStack_40 = a1;
  uStack_30 = a2;
  uStack_20 = a3;
  pFStack_10 = a4;
  if (a1 == 0) {
    iVar1 = SetObjSE__6CFieldFiPUli(this,a0,0,0);
  }
  else {
    memset(&uStack_90,0,8);
    uStack_90 = uStack_40;
    bStack_8b = bStack_8b & 0xf3 | (byte)((uStack_30 >> 4 & 3) << 2);
    uVar2 = uStack_30 & 0xf;
    if (uVar2 != 2) {
      uStack_20 = 1;
    }
    if (uVar2 == 0) {
      uStack_20 = 0;
    }
    bStack_8c = (byte)uStack_30 & 0xf | (byte)((uStack_20 & 0xf) << 4);
    if (2 < uVar2) {
      uStack_20 = 2;
    }
    puVar3 = auStack_88;
    for (iVar1 = 0; iVar1 < (int)uStack_20; iVar1 = iVar1 + 1) {
      SetShortPos4__FPsP7FVector(puVar3,pFStack_10);
      puVar3 = puVar3 + 8;
      pFStack_10 = pFStack_10 + 1;
    }
    iVar1 = SetObjSE__6CFieldFiPUli(pCStack_60,iStack_50,&uStack_90,uStack_30 >> 8 & 1);
  }
  return iVar1;
}

/* JP: 0x004d5990  CField::SetObjSE(int, unsigned long*, int)   [SetObjSE__6CFieldFiPUli]  size=0x57c */
int SetObjSE__6CFieldFiPUli(CField *this,int a0,int *a1,int a2)

{
  int iVar1;
  byte bVar2;
  byte *unaff_s0_lo;
  byte *pbVar3;
  byte bVar4;
  int *piVar5;
  uint uVar6;
  int iStack_30;
  
  if (a1 == (int *)0x0) {
    if (a0 < 0) {
      pbVar3 = this->aObjse_slots;
      for (uVar6 = 0; uVar6 < 0x30; uVar6 = uVar6 + 1) {
        if (-1 < *(int *)pbVar3) {
          SeRelease__3CSeFi(this->pSe,*(int *)pbVar3);
        }
        memset(pbVar3,0,0x28);
        pbVar3[0] = 0xff;
        pbVar3[1] = 0xff;
        pbVar3[2] = 0xff;
        pbVar3[3] = 0xff;
        pbVar3 = pbVar3 + 0x28;
      }
    }
    else {
      pbVar3 = this->aObjse_slots + a0 * 0x28;
      if (-1 < *(int *)pbVar3) {
        SeRelease__3CSeFi(this->pSe,*(int *)pbVar3);
        memset(pbVar3,0,0x28);
        pbVar3[0] = 0xff;
        pbVar3[1] = 0xff;
        pbVar3[2] = 0xff;
        pbVar3[3] = 0xff;
      }
    }
    return 0;
  }
  if (a0 < 0) {
    iStack_30 = 0;
    while ((iStack_30 < 0x30 &&
           (unaff_s0_lo = this->aObjse_slots + iStack_30 * 0x28,
           *(int *)(this->aObjse_slots + iStack_30 * 0x28 + 4) != 0))) {
      iStack_30 = iStack_30 + 1;
    }
    if (0x2f < iStack_30) {
      return -1;
    }
  }
  else {
    unaff_s0_lo = this->aObjse_slots + a0 * 0x28;
    iStack_30 = a0;
  }
  bVar4 = (*(byte *)(a1 + 1) & 0xf) == 3;
  if (3 < (*(byte *)(a1 + 1) & 0xf)) {
    bVar4 = 2;
  }
  if (-1 < *(int *)unaff_s0_lo) {
    if ((*(int *)(unaff_s0_lo + 4) == *a1) && ((unaff_s0_lo[8] & 0xf) == bVar4)) {
      if (((unaff_s0_lo[9] & 3) != 0) && ((*(byte *)((int)a1 + 5) & 3) == 0)) {
        SeRelease__3CSeFi(this->pSe,*(int *)unaff_s0_lo);
        unaff_s0_lo[9] = unaff_s0_lo[9] & 0xfc;
        unaff_s0_lo[0] = 0xff;
        unaff_s0_lo[1] = 0xff;
        unaff_s0_lo[2] = 0xff;
        unaff_s0_lo[3] = 0xff;
      }
    }
    else {
      SeRelease__3CSeFi(this->pSe,*(int *)unaff_s0_lo);
      memset(unaff_s0_lo,0,0x28);
      unaff_s0_lo[0] = 0xff;
      unaff_s0_lo[1] = 0xff;
      unaff_s0_lo[2] = 0xff;
      unaff_s0_lo[3] = 0xff;
    }
  }
  *(int *)(unaff_s0_lo + 4) = *a1;
  unaff_s0_lo[8] = unaff_s0_lo[8] & 0xf0 | bVar4;
  bVar4 = (*(byte *)(a1 + 1) & 0xf) != 0;
  if ((*(byte *)(a1 + 1) & 0xf) == 2) {
    bVar4 = *(byte *)(a1 + 1) >> 4;
  }
  unaff_s0_lo[8] = unaff_s0_lo[8] & 0xf | bVar4 << 4;
  unaff_s0_lo[9] =
       unaff_s0_lo[9] & 0xf3 | (byte)((uint)(((ulong)*(byte *)((int)a1 + 5) << 0x3c) >> 0x3e) << 2);
  unaff_s0_lo[9] = unaff_s0_lo[9] & 0xef | (byte)((a2 & 1U) << 4);
  bVar2 = *(byte *)(a1 + 1) & 0xf;
  if (bVar2 == 2) {
    pbVar3 = unaff_s0_lo + 10;
    piVar5 = a1;
    for (iVar1 = 0; piVar5 = piVar5 + 2, iVar1 < (int)(uint)bVar4; iVar1 = iVar1 + 1) {
      memcpy(pbVar3,piVar5,6);
      pbVar3 = pbVar3 + 6;
    }
  }
  else {
    if (bVar2 != 1) {
      if (((bVar2 != 5) && (bVar2 != 4)) && (bVar2 != 3)) goto LAB_004d5df0;
      memcpy(unaff_s0_lo + 0x10,a1 + 4,8);
    }
    memcpy(unaff_s0_lo + 10,a1 + 2,6);
  }
LAB_004d5df0:
  if ((*(byte *)(a1 + 1) & 0xf) == 0) {
    if (((unaff_s0_lo[9] & 3) == 0) && ((*(byte *)((int)a1 + 5) & 3) != 0)) {
      if (this->field_0x6cb == '\0') {
        iVar1 = SePlay__3CSeFUiP8_SeParam(this->pSe,*(int *)(unaff_s0_lo + 4),0);
        *(int *)unaff_s0_lo = iVar1;
        unaff_s0_lo[9] = unaff_s0_lo[9] & 0xfc | 2;
      }
      else {
        unaff_s0_lo[9] = unaff_s0_lo[9] & 0xfc | 1;
      }
    }
  }
  else if ((unaff_s0_lo[9] & 3) == 0) {
    unaff_s0_lo[9] = unaff_s0_lo[9] & 0xfc | 1;
  }
  return iStack_30;
}

/* JP: 0x004d5f10  CField::AutoLoadSE()   [AutoLoadSE__6CFieldFv]  size=0x1d0 */
void AutoLoadSE__6CFieldFv(CField *this)

{
  ushort uVar1;
  ushort *puVar2;
  int iVar3;
  long lVar4;
  uint a0;
  
  lVar4 = Find__6CSTGDBFUl(m_pSTGDB__6CField,0x20202045534a424f);
  if (lVar4 != 0) {
    MarkSE__6CFieldFv(this);
    puVar2 = (ushort *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(m_pSTGDB__6CField,lVar4);
    if ((char)puVar2[8] != '\0') {
      LoadSe__6CFieldFPCci(this,(char *)(puVar2 + 8),1);
    }
    if ((char)puVar2[0x10] != '\0') {
      LoadSe__6CFieldFPCci(this,(char *)(puVar2 + 0x10),2);
    }
    if ((char)puVar2[0x18] != '\0') {
      LoadSe__6CFieldFPCci(this,(char *)(puVar2 + 0x18),3);
    }
    SetSoundData__6CFieldFiii(this,0,(uint)puVar2[2],0);
    ReleaseMarkSE__6CFieldFv(this);
    uVar1 = *puVar2;
    puVar2 = puVar2 + 0x30;
    for (a0 = 0; a0 < 0x30; a0 = a0 + 1) {
      if (a0 < uVar1) {
        SetObjSE__6CFieldFiPUli(this,a0,puVar2,0);
      }
      else if (-1 < *(int *)(this->aObjse_slots + a0 * 0x28)) {
        SetObjSE__6CFieldFiPUli(this,a0,0,0);
      }
      iVar3 = GetObjSeSize__FPQ23SDB9tagFOBJSE(puVar2);
      puVar2 = puVar2 + iVar3 * 4;
    }
  }
  return;
}

/* JP: 0x004d7380  CField::UpdateObjSE()   [UpdateObjSE__6CFieldFv]  size=0x600 */
void UpdateObjSE__6CFieldFv(CField *this)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  byte *pbVar8;
  uint uVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [12];
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 uStack_30;
  undefined1 uStack_2f;
  float fStack_24;
  int iStack_20;
  uint uStack_1c;
  float fStack_18;
  float fStack_14;
  CField *pCStack_10;
  
  if ((long)((ulong)this->bFlags_191 << 0x39) < 0) {
    if ((byte)this->field_0x5ef < 0x50) {
      this->field_0x5ef = this->field_0x5ef + '\b';
    }
  }
  else if (this->field_0x5ef != '\0') {
    this->field_0x5ef = this->field_0x5ef + -8;
  }
  pCStack_10 = this;
  __ct__7FVectorFv(auStack_40);
  __ct__7FVectorFv(auStack_50);
  __ct__7FVectorFRC7FVector(auStack_60,&pCStack_10->vec_1d10);
  __ct__7FVectorFRC7FVector(auStack_70,&pCStack_10->vec_1d20);
  fStack_14 = (pCStack_10->vec_1d20).flW;
  uVar11 = atanf(320.0 / fStack_14);
  fStack_14 = (float)cosf(uVar11);
  uStack_64 = 0x3f800000;
  pbVar8 = pCStack_10->aObjse_slots;
  for (uVar9 = 0; uVar9 < 0x30; uVar9 = uVar9 + 1) {
    if ((*(int *)(pbVar8 + 4) != 0) &&
       ((((pbVar8[9] & 3) != 1 || (pCStack_10->field_0x6cb == '\0')) && ((pbVar8[9] & 3) != 0)))) {
      if (pbVar8[8] >> 4 == 0) {
        if ((-1 < *(int *)pbVar8) &&
           ((lVar4 = isPlaying__3CSeFi(pCStack_10->pSe,*(int *)pbVar8), lVar4 == 0 || (lVar4 == -2))))
        {
          SeRelease__3CSeFi(pCStack_10->pSe,*(int *)pbVar8);
          pbVar8[0] = 0xff;
          pbVar8[1] = 0xff;
          pbVar8[2] = 0xff;
          pbVar8[3] = 0xff;
        }
        if (*(int *)pbVar8 < 0) {
          if ((-1 < (long)((ulong)pbVar8[9] << 0x3b)) || ((pbVar8[9] & 3) == 1)) {
            pbVar8[9] = pbVar8[9] & 0xfc | 2;
            iVar3 = SePlay__3CSeFUiP8_SeParam(pCStack_10->pSe,*(int *)(pbVar8 + 4),0);
            *(int *)pbVar8 = iVar3;
          }
        }
        else {
          uVar10 = 0x7f - (byte)pCStack_10->field_0x5ef;
          iVar3 = SeGetWork__3CSeFi(pCStack_10->pSe,*(int *)pbVar8);
          if (*(byte *)(iVar3 + 0x14) != uVar10) {
            *(char *)(iVar3 + 0x14) = (char)uVar10;
            SeUpdate__3CSeFi(pCStack_10->pSe,*(int *)pbVar8);
          }
        }
      }
      else {
        __as__7FVectorFRC7FVector(auStack_50,auStack_60);
        fStack_18 = (float)Calc3DPosition__FP7FVectorP7FVectorP6_ObjSE(auStack_50,auStack_40,pbVar8)
        ;
        uVar5 = __ct__7FVectorFRC7FVector(auStack_80,auStack_50);
        uVar6 = __ct__7FVectorFRC7FVector(auStack_90,auStack_40);
        uVar7 = __ct__7FVectorFRC7FVector(auStack_a0,auStack_70);
        Exp3DVolume__F7FVector7FVector7FVectorRiRii
                  (uVar5,uVar6,uVar7,&uStack_1c,&iStack_20,((ulong)pbVar8[9] & 0xf) >> 2);
        fStack_24 = (float)Exp3DVolumeC__FR7FVectorR7FVectorR7FVectorf
                                     (fStack_14,auStack_50,auStack_70,auStack_40);
        fStack_18 = fStack_18 * fStack_24;
        if ((-1 < *(int *)pbVar8) &&
           ((lVar4 = isPlaying__3CSeFi(pCStack_10->pSe,*(int *)pbVar8), lVar4 == 0 || (lVar4 == -2))))
        {
          SeRelease__3CSeFi(pCStack_10->pSe,*(int *)pbVar8);
          pbVar8[0] = 0xff;
          pbVar8[1] = 0xff;
          pbVar8[2] = 0xff;
          pbVar8[3] = 0xff;
        }
        uStack_1c = (uint)((float)(int)uStack_1c * fStack_18);
        if ((int)uStack_1c < 1) {
          if (-1 < *(int *)pbVar8) {
            SeRelease__3CSeFi(pCStack_10->pSe,*(int *)pbVar8);
            pbVar8[0] = 0xff;
            pbVar8[1] = 0xff;
            pbVar8[2] = 0xff;
            pbVar8[3] = 0xff;
          }
        }
        else {
          if (pCStack_10->field_0x5ef != '\0') {
            uStack_1c = (int)(uStack_1c * (0x80 - (uint)(byte)pCStack_10->field_0x5ef)) >> 7;
          }
          if (*(int *)pbVar8 < 0) {
            if ((-1 < (long)((ulong)pbVar8[9] << 0x3b)) || ((pbVar8[9] & 3) == 1)) {
              InitSeParam__4SdrvFP8_SeParamiPv(sys__4Sdrv,&uStack_30,0,0);
              uStack_30 = (undefined1)uStack_1c;
              uStack_2f = (undefined1)iStack_20;
              iVar3 = SePlay__3CSeFUiP8_SeParam(pCStack_10->pSe,*(int *)(pbVar8 + 4),&uStack_30);
              *(int *)pbVar8 = iVar3;
              pbVar8[9] = pbVar8[9] & 0xfc | 2;
            }
          }
          else {
            iVar3 = SeGetWork__3CSeFi(pCStack_10->pSe,*(int *)pbVar8);
            bVar1 = *(byte *)(iVar3 + 0x14) != uStack_1c;
            if (bVar1) {
              *(char *)(iVar3 + 0x14) = (char)uStack_1c;
            }
            bVar2 = (long)*(char *)(iVar3 + 0x15) != (long)iStack_20;
            if (bVar2) {
              *(char *)(iVar3 + 0x15) = (char)iStack_20;
            }
            if (bVar2 || bVar1) {
              SeUpdate__3CSeFi(pCStack_10->pSe,*(int *)pbVar8);
            }
          }
        }
      }
    }
    pbVar8 = pbVar8 + 0x28;
  }
  return;
}

/* JP: 0x004d7980  CField::CallSe(int, int, unsigned int)   [CallSe__6CFieldFiiUi]  size=0x4d8 */
void CallSe__6CFieldFiiUi(CField *this,int a0,int a1,uint a2)

{
  FVector *a0_00;
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  ulong uVar6;
  uint uVar7;
  short sVar8;
  uint uVar9;
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [64];
  undefined1 auStack_70 [24];
  undefined1 auStack_58 [2];
  short sStack_56;
  undefined1 auStack_48 [4];
  int iStack_44;
  CField *pCStack_40;
  int iStack_30;
  int iStack_20;
  uint uStack_10;
  
  pCStack_40 = this;
  iStack_30 = a0;
  iStack_20 = a1;
  uStack_10 = a2;
  InitSeParam__4SdrvFP8_SeParamiPv(sys__4Sdrv,auStack_58,0,0);
  uVar2 = uStack_10;
  uVar7 = 0;
  if ((iStack_20 == 1) && (uStack_10 != 0)) {
    __ct__7FVectorFv(auStack_70);
    GetPos__11CFieldModelFv(auStack_e0,uVar2);
    __as__7FVectorFRC7FVector(auStack_70,auStack_e0);
    uVar3 = GetActiveCamera__9GsxCameraFv();
    uVar3 = GetFrame__9GsxCameraFv(uVar3);
    __ct__6MatrixFRC6Matrix(auStack_b0,uVar3);
    uVar3 = GetPos__6MatrixFv(auStack_b0);
    __ct__7FVectorFRC7FVector(auStack_c0,uVar3);
    uVar3 = GetAt__6MatrixFv(auStack_b0);
    __ct__7FVectorFRC7FVector(auStack_d0,uVar3);
    uVar3 = __ct__7FVectorFRC7FVector(auStack_f0,auStack_c0);
    uVar4 = __ct__7FVectorFRC7FVector(auStack_100,auStack_70);
    uVar5 = __ct__7FVectorFRC7FVector(auStack_110,auStack_d0);
    Exp3DVolume__F7FVector7FVector7FVectorRiRii(uVar3,uVar4,uVar5,&iStack_44,auStack_48,1);
    if ((iStack_30 == 3) || (iStack_30 == 2)) {
      if (*(int *)(uVar2 + 0x130) != 0) {
        uVar7 = rand();
        uVar7 = *(int *)(uVar2 + 0x130) + (uVar7 & 1);
        if ((long)((ulong)pCStack_40->bFlags_191 << 0x3e) < 0) {
          uVar7 = uVar7 | 0x1000;
        }
        uVar2 = rand();
        iStack_44 = (int)(iStack_44 * (uVar2 & 0x3f)) / 0x3f;
        if (iStack_30 != 3) {
          iStack_44 = iStack_44 >> 1;
        }
        if (iStack_44 < 6) {
          uVar7 = 0;
        }
        else {
          auStack_58[0] = (undefined1)iStack_44;
          uVar6 = rand();
          if ((uVar6 & 3) == 0) {
            iVar1 = rand();
            sStack_56 = ((short)(iVar1 % 0x11) + -8) * 8;
          }
        }
      }
    }
    else if ((iStack_30 == 1) || (iStack_30 == 0)) {
      uVar7 = 0;
      if ((long)((ulong)pCStack_40->bFlags_191 << 0x3a) < 0) {
        uVar7 = (uint)*(ushort *)(uVar2 + 0x8e) * 0x10 + 0x41000000;
        uVar9 = 0;
      }
      else {
        if (*(int *)(uVar2 + 300) == 0) goto LAB_004d7e08;
        a0_00 = (FVector *)__ct__7FVectorFRC7FVector(auStack_120,auStack_70);
        iVar1 = OnFloorChk__9CFloorManF7FVector(pCStack_40->pFloor,a0_00);
        if ((iVar1 != 0) && (uVar7 = *(byte *)(iVar1 + 0x14) & 0xf, uVar7 == 0xc))
        goto LAB_004d7e08;
        uVar7 = uVar7 * 0x1000 + *(int *)(uVar2 + 300);
        uVar9 = uVar7;
      }
      uVar7 = uVar7 - (int)((long)((ulong)*(byte *)(uVar2 + 0x86) << 0x3a) >> 0x3f);
      *(byte *)(uVar2 + 0x86) =
           *(byte *)(uVar2 + 0x86) & 0xdf |
           (byte)(((uint)(((ulong)*(byte *)(uVar2 + 0x86) << 0x3a) >> 0x3f) ^ 1) << 5);
      if (iStack_30 != 1) {
        iStack_44 = iStack_44 >> 1;
      }
      if (iStack_44 < 1) {
        uVar7 = 0;
      }
      else {
        auStack_58[0] = (undefined1)iStack_44;
        if ((uVar9 & 0x10) == 0) {
          iVar1 = rand();
          iVar1 = iVar1 % 0x11 + -8;
          if (iVar1 < 0) {
            sVar8 = (short)((iVar1 * 0x100) / 5) + (short)(iVar1 * 0x100 >> 0x1f) +
                    (((ushort)((uint)iVar1 >> 0x10) & 0xff) >> 7);
          }
          else {
            sVar8 = (short)iVar1 * 0x20;
          }
          if (iStack_30 == 0) {
            sVar8 = sVar8 + -0x80;
          }
          sStack_56 = sStack_56 + sVar8;
        }
      }
    }
  }
LAB_004d7e08:
  if (uVar7 != 0) {
    SePlayN__3CSeFUiP8_SeParam(pCStack_40->pSe,uVar7,auStack_58);
  }
  return;
}

/* JP: 0x004d7e60  CField::LoadBgm(const char*)   [LoadBgm__6CFieldFPCc]  size=0x210 */
void LoadBgm__6CFieldFPCc(CField *this,char *a0)

{
  long lVar1;
  undefined1 auStack_a0 [80];
  undefined1 auStack_50 [40];
  undefined1 auStack_28 [4];
  undefined4 uStack_24;
  CField *pCStack_20;
  char *pcStack_10;
  
  this->bFlags_190 = this->bFlags_190 & 0xef;
  pCStack_20 = this;
  pcStack_10 = a0;
  DecodeKey__15_FieldDataCacheFPcUiUi
            (auStack_50,*(undefined4 *)&this->field_0x154,*(undefined4 *)&this->field_0x150);
  uStack_24 = EncodeKey__15_FieldDataCacheFPCcRUi(pcStack_10,auStack_28);
  GetBgmFileName__FPcPCc(auStack_a0,pcStack_10);
  if (((pCStack_20->bFlags_190 & 3) == 0) &&
     (lVar1 = memcmp(&pCStack_20->field_0x150,auStack_28,8), lVar1 == 0)) {
    pCStack_20->bFlags_190 = pCStack_20->bFlags_190 & 0xef | 0x10;
  }
  else if (((pCStack_20->bFlags_190 & 3) == 2) &&
          (lVar1 = Find__12CSndBufCacheFPCci(auStack_a0,3), lVar1 != 0)) {
    memcpy(&pCStack_20->field_0x158,auStack_28,8);
    pCStack_20->bFlags_190 = pCStack_20->bFlags_190 & 0xef | 0x10;
  }
  else if (((pCStack_20->bFlags_190 & 3) != 1) ||
          (lVar1 = Find__12CSndBufCacheFPCci(auStack_a0,3), lVar1 == 0)) {
    if ((((ulong)pCStack_20->bFlags_191 & 0x1f) >> 2 == 0) && ((pCStack_20->bFlags_190 & 3) == 0)) {
      LoadOrder__6CFieldFPCc(pCStack_20,pcStack_10);
    }
    else {
      if (pCStack_20->field_0x729 != '\0') {
        CancelPlayOrder__6CFieldFv(pCStack_20);
      }
      strcpy(&pCStack_20->field_0x729,pcStack_10);
    }
  }
  return;
}

/* JP: 0x004d8070  CField::LoadOrder(const char*)   [LoadOrder__6CFieldFPCc]  size=0xa4 */
void LoadOrder__6CFieldFPCc(CField *this,char *a0)

{
  undefined1 auStack_80 [88];
  undefined1 auStack_28 [4];
  undefined4 uStack_24;
  CField *pCStack_20;
  char *pcStack_10;
  
  pCStack_20 = this;
  pcStack_10 = a0;
  GetBgmFileName__FPcPCc(auStack_80,a0);
  uStack_24 = EncodeKey__15_FieldDataCacheFPCcRUi(pcStack_10,auStack_28);
  memcpy(&pCStack_20->field_0x160,auStack_28,8);
  Clear__12CSndBufCacheFv();
  Load__12CSndBufCacheFPCciiPFiP9BufMemoryiPcPv_iPv(auStack_80,3,0,0x4d5680,0);
  pCStack_20->bFlags_190 = pCStack_20->bFlags_190 & 0xfc | 1;
  return;
}

/* JP: 0x004d8120  CField::CancelPlayOrder()   [CancelPlayOrder__6CFieldFv]  size=0xe8 */
void CancelPlayOrder__6CFieldFv(CField *this)

{
  uint uVar1;
  int iVar2;
  
  if (2 < ((ulong)this->bFlags_191 & 0x1f) >> 2) {
    iVar2 = 3;
    for (uVar1 = (uint)(byte)this->field_0x14c; uVar1 != (byte)this->field_0x14d;
        uVar1 = uVar1 + 1 & 7) {
      if ((&this->field_0x2c)[uVar1 * 4] == '\x02') {
        iVar2 = iVar2 + -1;
        if (iVar2 == 0) {
          (&this->field_0x2c)[uVar1 * 4] = '\0';
          this->bFlags_191 =
               this->bFlags_191 & 0xe3 |
               (byte)(((uint)(((ulong)this->bFlags_191 << 0x3b) >> 0x3d) - 1 & 7) << 2);
        }
      }
    }
  }
  return;
}

/* JP: 0x004d8210  CField::PlayBgm(int, unsigned int)   [PlayBgm__6CFieldFiUi]  size=0x1d4 */
void PlayBgm__6CFieldFiUi(CField *this,int a0,uint a1)

{
  ushort uVar1;
  char *pcVar2;
  long lVar3;
  
  this->bFlags_190 = this->bFlags_190 & 0xdf;
  if ((this->bFlags_190 & 3) == 0) {
    this->bFlags_190 = this->bFlags_190 & 0xdf | 0x20;
  }
  else if ((((ulong)this->bFlags_191 & 0x1f) >> 2 == 0) ||
          (((pcVar2 = FindSoundReq__6CFieldFv(this), pcVar2 == (char *)0x0 ||
            ((uint)(byte)pcVar2[1] != a0)) &&
           ((((ulong)this->bFlags_190 & 0xf) >> 2 != 1 ||
            (lVar3 = memcmp(&this->field_0x150,&this->field_0x158,8), lVar3 != 0)))))) {
    uVar1._0_1_ = this->bFlags_190;
    uVar1._1_1_ = this->bFlags_191;
    this->bFlags_190 = (char)(uVar1 & 0xfe7f);
    this->bFlags_191 = (char)((uVar1 & 0xfe7f) >> 8);
    this->bFlags_191 =
         this->bFlags_191 & 0xe3 |
         (byte)(((uint)(((ulong)this->bFlags_191 << 0x3b) >> 0x3d) + 1 & 7) << 2);
    if (((this->bFlags_190 & 3) == 1) || (this->field_0x729 != '\0')) {
      AddQ__6CFieldFUcUcUs(this,2,(byte)a0,(ushort)a1);
    }
    else {
      CmdBgmPlayReq__6CFieldFiUi(this,a0,a1);
    }
  }
  return;
}

/* JP: 0x004d83f0  CField::BgmFade(unsigned int, unsigned int)   [BgmFade__6CFieldFUiUi]  size=0x78 */
void BgmFade__6CFieldFUiUi(CField *this,uint a0,uint a1)

{
  ushort uVar1;
  
  uVar1._0_1_ = this->bFlags_190;
  uVar1._1_1_ = this->bFlags_191;
  uVar1 = uVar1 & 0xfe7f | (ushort)(a1 != 0) << 7;
  this->bFlags_190 = (char)uVar1;
  this->bFlags_191 = (char)(uVar1 >> 8);
  FadeBGM__6CMusicFUiUi(sys__6CMusic,a0,a1 * 100);
  return;
}

/* JP: 0x004d8470  CField::SetBgmVolume(int)   [SetBgmVolume__6CFieldFi]  size=0x2c */
void SetBgmVolume__6CFieldFi(CField *this,int a0)

{
  SetVolume__6CMusicFi(sys__6CMusic,a0);
  return;
}

/* JP: 0x004d84a0  CField::WaitBgm(int)   [WaitBgm__6CFieldFi]  size=0x94 */
long WaitBgm__6CFieldFi(CField *this,int a0)

{
  ulong uVar1;
  
  if (a0 == 2) {
    uVar1 = ((ulong)this->bFlags_190 & 0x1f) >> 4;
  }
  else if (a0 == 1) {
    uVar1 = ((ulong)this->bFlags_190 & 0x3f) >> 5;
  }
  else if (a0 == 0) {
    uVar1 = ((ulong)this->bFlags_190 & 0x7f) >> 6;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x004d8540  CField::SetBattleBgm(const char*)   [SetBattleBgm__6CFieldFPCc]  size=0x10 */
void SetBattleBgm__6CFieldFPCc(CField *this,char *a0)

{
  return;
}

/* JP: 0x004d8550  CField::LoadSe(const char*, int)   [LoadSe__6CFieldFPCci]  size=0x208 */
undefined4 LoadSe__6CFieldFPCci(CField *this,char *a0,int a1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  void *extraout_a3_lo;
  void *extraout_a3_lo_00;
  void *a2;
  undefined4 *puVar4;
  char *a1_00;
  undefined1 auStack_80 [80];
  CField *pCStack_30;
  char *pcStack_20;
  int iStack_10;
  
  pCStack_30 = this;
  pcStack_20 = a0;
  iStack_10 = a1;
  GetSeFileName__FPcPCc(auStack_80,a0);
  uVar3 = StripFileNameB__12CSndBufCacheFPCc(auStack_80);
  piVar1 = FindSE__6CFieldFPCc(pCStack_30,(char *)uVar3);
  if (piVar1 == (int *)0x0) {
    puVar4 = (undefined4 *)&pCStack_30->field_0x4c;
    a1_00 = (char *)0x0;
    while ((a1_00 < (char *)0x10 && (((ulong)*(byte *)((int)puVar4 + 0xd) & 0x1f) >> 2 != 0))) {
      a1_00 = a1_00 + 1;
      puVar4 = puVar4 + 4;
    }
    if (a1_00 == (char *)0x10) {
      uVar2 = 0;
    }
    else {
      uVar2 = EncodeKey__15_FieldDataCacheFPCcRUi(uVar3,puVar4 + 1);
      *puVar4 = uVar2;
      *(byte *)(puVar4 + 3) = (byte)iStack_10 & 0xf;
      *(byte *)((int)puVar4 + 0xd) =
           *(byte *)((int)puVar4 + 0xd) & 0xfe | (byte)((uint)iStack_10 >> 8) & 1;
      *(byte *)((int)puVar4 + 0xd) = *(byte *)((int)puVar4 + 0xd) & 0xe3 | 8;
      pCStack_30->field_0x6cb = pCStack_30->field_0x6cb + '\x01';
      a2 = extraout_a3_lo;
      if (iStack_10 == 1) {
        SetObjSE__6CFieldFiPUli(pCStack_30,-1,0,0);
        a2 = extraout_a3_lo_00;
      }
      FileReadOrder__6CFieldFiPCcPv((CField *)0x6,(int)auStack_80,a1_00,a2);
      uVar2 = 1;
    }
  }
  else {
    *(byte *)((int)piVar1 + 0xd) = *(byte *)((int)piVar1 + 0xd) & 0xfd;
    *(byte *)(piVar1 + 3) = (byte)iStack_10 & 0xf;
    *(byte *)((int)piVar1 + 0xd) =
         *(byte *)((int)piVar1 + 0xd) & 0xfe | (byte)((uint)iStack_10 >> 8) & 1;
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004d8760  CField::UnloadSeAll()   [UnloadSeAll__6CFieldFv]  size=0xc0 */
void UnloadSeAll__6CFieldFv(CField *this)

{
  undefined1 *puVar1;
  uint uVar2;
  
  puVar1 = &this->field_0x4c;
  for (uVar2 = 0; uVar2 < 0x10; uVar2 = uVar2 + 1) {
    if (((ulong)(byte)puVar1[0xd] & 0x1f) >> 2 < 2) {
      memset(puVar1,0,0x10);
    }
    else {
      puVar1[0xd] = puVar1[0xd] & 0xe3 | 0xc;
    }
    puVar1 = puVar1 + 0x10;
  }
  return;
}

/* JP: 0x004d8820  CField::UnloadSeAll2()   [UnloadSeAll2__6CFieldFv]  size=0x124 */
void UnloadSeAll2__6CFieldFv(CField *this)

{
  undefined1 *puVar1;
  uint uVar2;
  
  puVar1 = &this->field_0x4c;
  for (uVar2 = 0; uVar2 < 0x10; uVar2 = uVar2 + 1) {
    if ((((*(int *)(puVar1 + 4) != 0) && (((ulong)(byte)puVar1[0xd] & 0x1f) >> 2 != 0)) &&
        ((puVar1[0xd] & 1) == 0)) && (((byte)puVar1[0xe] < 0x21 || (0x23 < (byte)puVar1[0xe])))) {
      if (((ulong)(byte)puVar1[0xd] & 0x1f) >> 2 == 1) {
        RemoveSDH__3CSeFUi(this->pSe,*(undefined4 *)(puVar1 + 8));
        memset(puVar1,0,0x10);
      }
      else {
        puVar1[0xd] = puVar1[0xd] & 0xe3 | 0xc;
      }
    }
    puVar1 = puVar1 + 0x10;
  }
  return;
}

/* JP: 0x004d8950  CField::UnloadSeFromBank(int)   [UnloadSeFromBank__6CFieldFi]  size=0x108 */
void UnloadSeFromBank__6CFieldFi(CField *this,int a0)

{
  undefined1 *puVar1;
  uint uVar2;
  
  if (((a0 & 0xffU) != 0) && ((a0 & 0xfU) != 0xf)) {
    puVar1 = &this->field_0x4c;
    for (uVar2 = 0; uVar2 < 0x10; uVar2 = uVar2 + 1) {
      if ((((ulong)(byte)puVar1[0xd] & 0x1f) >> 2 == 1) && ((uint)(byte)puVar1[0xe] == (a0 & 0xffU))
         ) {
        RemoveSDH__3CSeFUi(this->pSe,*(undefined4 *)(puVar1 + 8));
        memset(puVar1,0,0x10);
      }
      puVar1 = puVar1 + 0x10;
    }
  }
  return;
}

/* JP: 0x004d8a60  CField::UnloadSe(const char*)   [UnloadSe__6CFieldFPCc]  size=0x178 */
undefined4 UnloadSe__6CFieldFPCc(CField *this,char *a0)

{
  char *a0_00;
  int *piVar1;
  undefined1 auStack_70 [80];
  CField *pCStack_20;
  char *pcStack_10;
  
  pCStack_20 = this;
  pcStack_10 = a0;
  if (a0 == (char *)0x0) {
    SetObjSE__6CFieldFiPUli(this,-1,0,0);
    RemoveAllSDH__3CSeFv(pCStack_20->pSe);
    SeReleaseAll__3CSeFv(pCStack_20->pSe);
    UnloadSeAll__6CFieldFv(pCStack_20);
  }
  else if (a0 == (char *)0xffffffff) {
    UnloadSeAll2__6CFieldFv(this);
  }
  else {
    GetSeFileName__FPcPCc(auStack_70,a0);
    a0_00 = (char *)StripFileNameB__12CSndBufCacheFPCc(auStack_70);
    piVar1 = FindSE__6CFieldFPCc(pCStack_20,a0_00);
    if ((piVar1 != (int *)0x0) && (((ulong)*(byte *)((int)piVar1 + 0xd) & 0x1f) >> 2 != 0)) {
      if (((ulong)*(byte *)((int)piVar1 + 0xd) & 0x1f) >> 2 == 1) {
        RemoveSDH__3CSeFUi(pCStack_20->pSe,piVar1[2]);
        memset(piVar1,0,0x10);
      }
      else {
        *(byte *)((int)piVar1 + 0xd) = *(byte *)((int)piVar1 + 0xd) & 0xe3 | 0xc;
      }
    }
  }
  return 1;
}

/* JP: 0x004d8be0  CField::MarkSE()   [MarkSE__6CFieldFv]  size=0xb8 */
void MarkSE__6CFieldFv(CField *this)

{
  undefined1 *puVar1;
  uint uVar2;
  
  puVar1 = &this->field_0x4c;
  for (uVar2 = 0; uVar2 < 0x10; uVar2 = uVar2 + 1) {
    if (((*(int *)(puVar1 + 4) != 0) && (puVar1[0xc] != '\0')) && ((puVar1[0xd] & 1) == 0)) {
      puVar1[0xd] = puVar1[0xd] & 0xfd | 2;
    }
    puVar1 = puVar1 + 0x10;
  }
  return;
}

/* JP: 0x004d8ca0  CField::ReleaseMarkSE()   [ReleaseMarkSE__6CFieldFv]  size=0x108 */
void ReleaseMarkSE__6CFieldFv(CField *this)

{
  undefined1 *puVar1;
  uint uVar2;
  
  puVar1 = &this->field_0x4c;
  for (uVar2 = 0; uVar2 < 0x10; uVar2 = uVar2 + 1) {
    if ((*(int *)(puVar1 + 4) != 0) && ((long)((ulong)(byte)puVar1[0xd] << 0x3e) < 0)) {
      if (((ulong)(byte)puVar1[0xd] & 0x1f) >> 2 == 1) {
        RemoveSDH__3CSeFUi(this->pSe,*(undefined4 *)(puVar1 + 8));
        memset(puVar1,0,0x10);
      }
      else {
        puVar1[0xd] = puVar1[0xd] & 0xe3 | 0xc;
      }
    }
    puVar1[0xd] = puVar1[0xd] & 0xfd;
    puVar1 = puVar1 + 0x10;
  }
  return;
}

/* JP: 0x004d8db0  CField::PlaySe(unsigned int, int)   [PlaySe__6CFieldFUii]  size=0x74 */
void PlaySe__6CFieldFUii(CField *this,uint a0,int a1)

{
  undefined1 auStack_40 [16];
  CField *pCStack_30;
  uint uStack_20;
  int iStack_10;
  
  pCStack_30 = this;
  uStack_20 = a0;
  iStack_10 = a1;
  InitSeParam__4SdrvFP8_SeParamiPv(sys__4Sdrv,auStack_40,0,0);
  if (iStack_10 == 0) {
    iStack_10 = 0x80;
  }
  auStack_40[0] = (undefined1)iStack_10;
  SePlayN__3CSeFUiP8_SeParam(pCStack_30->pSe,uStack_20,auStack_40);
  return;
}

/* JP: 0x004d8e30  CField::PlaySeR(int, unsigned int, int, int)   [PlaySeR__6CFieldFiUiii]  size=0x168 */
undefined8 PlaySeR__6CFieldFiUiii(CField *this,int a0,uint a1,int a2,int a3)

{
  long lVar1;
  undefined8 uVar2;
  undefined1 auStack_60 [16];
  CField *pCStack_50;
  int iStack_40;
  uint uStack_30;
  int iStack_20;
  int iStack_10;
  
  pCStack_50 = this;
  iStack_40 = a0;
  uStack_30 = a1;
  iStack_20 = a2;
  iStack_10 = a3;
  InitSeParam__4SdrvFP8_SeParamiPv(sys__4Sdrv,auStack_60,0,0);
  if (iStack_40 == 4) {
    lVar1 = SeFind2__3CSeFUi(pCStack_50->pSe,uStack_30);
    if (-1 < lVar1) {
      SeFade__3CSeFiii(pCStack_50->pSe,lVar1,iStack_20,iStack_10);
      return 1;
    }
  }
  else {
    if (iStack_40 == 1) {
      lVar1 = SeFind2__3CSeFUi(pCStack_50->pSe,uStack_30);
      if (-1 < lVar1) {
        uVar2 = isPlaying__3CSeFi(pCStack_50->pSe,lVar1);
        return uVar2;
      }
      return 0xfffffffffffffffd;
    }
    if (iStack_40 == 0) {
      if (iStack_20 == 0) {
        iStack_20 = 0x80;
      }
      auStack_60[0] = (undefined1)iStack_20;
      SePlay__3CSeFUiP8_SeParam(pCStack_50->pSe,uStack_30,auStack_60);
    }
  }
  return 0;
}

/* JP: 0x004d8fa0  CField::SetSeVolume(int)   [SetSeVolume__6CFieldFi]  size=0x10 */
void SetSeVolume__6CFieldFi(CField *this,int a0)

{
  return;
}

/* JP: 0x004d8fb0  CField::StopSe(unsigned int)   [StopSe__6CFieldFUi]  size=0x5c */
void StopSe__6CFieldFUi(CField *this,uint a0)

{
  long lVar1;
  
  lVar1 = SeFind2__3CSeFUi(this->pSe,a0);
  if (-1 < lVar1) {
    SeRelease__3CSeFi(this->pSe,lVar1);
  }
  return;
}

/* JP: 0x004d9010  CField::WaitSe(unsigned int, int)   [WaitSe__6CFieldFUii]  size=0x48 */
bool WaitSe__6CFieldFUii(CField *this,uint a0,int a1)

{
  long lVar1;
  
  lVar1 = SeFind__3CSeFUi(this->pSe,a0,a1);
  return lVar1 < 0;
}

/* JP: 0x004d9060  CField::SetSoundData(int, int, int)   [SetSoundData__6CFieldFiii]  size=0x10c */
undefined4 SetSoundData__6CFieldFiii(CField *this,int a0,int a1,int a2)

{
  int iStack_30;
  
  iStack_30 = a0;
  if (a0 < 0) {
    iStack_30 = a0 + 0x100;
  }
  if (iStack_30 == 3) {
    if (this->field_0x6cb != '\0') {
      return 0xffffffff;
    }
  }
  else if (iStack_30 == 2) {
    FadeStreamBgm__6CFieldFi(this,a1);
  }
  else if (iStack_30 == 1) {
    this->bFlags_191 = this->bFlags_191 & 0xdf | (byte)((a1 & 1U) << 5);
  }
  else if (iStack_30 == 0) {
    SetReverbMode__6CFieldFi(this,a1);
  }
  return 0;
}

/* JP: 0x004d9170  CField::SetReverbMode(int)   [SetReverbMode__6CFieldFi]  size=0x40 */
void SetReverbMode__6CFieldFi(CField *this,int a0)

{
  this->bFlags_191 = this->bFlags_191 & 0xfd | (byte)((a0 & 1U) << 1);
  return;
}

/* JP: 0x004d91b0  CField::PlayStreamBgm(const char*, int)   [PlayStreamBgm__6CFieldFPCci]  size=0xc4 */
void PlayStreamBgm__6CFieldFPCci(CField *this,char *a0,int a1)

{
  int iVar1;
  long lVar2;
  undefined1 auStack_70 [80];
  char *pcStack_20;
  int iStack_10;
  
  iVar1 = sys__9StreamBGM;
  pcStack_20 = a0;
  iStack_10 = a1;
  if (sys__9StreamBGM == 0) {
    lVar2 = __nw__FUi(0xbc);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__9StreamBGMFv(lVar2);
    }
  }
  sys__9StreamBGM = iVar1;
  if (iStack_10 == 0) {
    iStack_10 = 0x7f;
  }
  sprintf(auStack_70,0x558fc0,pDataPath__7SysTool,pcStack_20);
  Create__9StreamBGMFPCc(sys__9StreamBGM,auStack_70);
  SetVolume__9StreamBGMFi(sys__9StreamBGM,iStack_10);
  Play__9StreamBGMFv(sys__9StreamBGM);
  return;
}

/* JP: 0x004d9280  CField::FadeStreamBgm(int)   [FadeStreamBgm__6CFieldFi]  size=0x40 */
void FadeStreamBgm__6CFieldFi(CField *this,int a0)

{
  if (sys__9StreamBGM != 0) {
    Stop__9StreamBGMFib(sys__9StreamBGM,a0,1);
    sys__9StreamBGM = 0;
  }
  return;
}

/* JP: 0x004d92c0  CField::cbReadSoundFile(int, BufMemory*, int, void*)   [cbReadSoundFile__6CFieldFiP9BufMemoryiPv]  size=0xe0 */
undefined4 cbReadSoundFile__6CFieldFiP9BufMemoryiPv(CField *this,int a0,void *a1,int a2,void *a3)

{
  if (a0 == 6) {
    *(char *)(sys__6CField + 0x6cb) = *(char *)(sys__6CField + 0x6cb) + -1;
    if (((ulong)(byte)(&this->field_0x59)[(int)a3 * 0x10] & 0x1f) >> 2 == 3) {
      memset(&this->field_0x4c + (int)a3 * 0x10,0,0x10,a2);
      __dt__9BufMemoryFv(a1,1);
    }
    else {
      *(void **)(&this->field_0x54 + (int)a3 * 0x10) = a1;
      AddQ__6CFieldFUcUcUs(this,3,(byte)a3,0);
    }
  }
  return 0;
}

/* JP: 0x004d93a0  CField::cbMusic(unsigned char, unsigned int, unsigned int)   [cbMusic__6CFieldFUcUiUi]  size=0x34 */
void cbMusic__6CFieldFUcUiUi(CField *this,byte a0,uint a1,uint a2)

{
  cbMusicA__6CFieldFUcUi(pCGpffff85ec,(byte)this,(int)(char)a0);
  return;
}

/* JP: 0x004d93e0  CField::cbMusicA(unsigned char, unsigned int)   [cbMusicA__6CFieldFUcUi]  size=0x1d0 */
void cbMusicA__6CFieldFUcUi(CField *this,byte a0,uint a1)

{
  ushort uVar1;
  ushort uVar2;
  
  if (a0 == 3) {
    uVar1._0_1_ = this->bFlags_190;
    uVar1._1_1_ = this->bFlags_191;
    if (((ulong)uVar1 & 0x1ff) >> 7 != 2) {
      this->bFlags_190 = this->bFlags_190 & 0xbf | 0x40;
      *(undefined4 *)&this->field_0x154 = 0;
      this->bFlags_190 = this->bFlags_190 & 0xf3;
    }
    uVar2._0_1_ = this->bFlags_190;
    uVar2._1_1_ = this->bFlags_191;
    this->bFlags_190 = (char)(uVar2 & 0xfe7f);
    this->bFlags_191 = (char)((uVar2 & 0xfe7f) >> 8);
  }
  else if (a0 == 2) {
    this->bFlags_190 = this->bFlags_190 & 0xdf | 0x20;
    ClearBgmData__6CFieldFv(this);
    this->bFlags_191 =
         this->bFlags_191 & 0xe3 |
         (byte)(((uint)(((ulong)this->bFlags_191 << 0x3b) >> 0x3d) - 1 & 7) << 2);
    if (this->field_0x729 != '\0') {
      LoadOrder__6CFieldFPCc(this,&this->field_0x729);
      this->field_0x729 = 0;
    }
    this->bFlags_190 = this->bFlags_190 & 0xf3 | 8;
  }
  else if (a0 == 1) {
    this->bFlags_190 = this->bFlags_190 & 0xef | 0x10;
  }
  return;
}

/* JP: 0x004d95b0  CField::ResetSE()   [ResetSE__6CFieldFv]  size=0x70 */
void ResetSE__6CFieldFv(CField *this)

{
  SetObjSE__6CFieldFiPUli(this,-1,0,0);
  UnloadSe__6CFieldFPCc(this,(char *)0x0);
  if (this->pSe != (void *)0x0) {
    (**(code **)(*(int *)((int)this->pSe + 4) + 0x10))();
  }
  return;
}

/* JP: 0x004d9620  CField::AddQ(unsigned char, unsigned char, unsigned short)   [AddQ__6CFieldFUcUcUs]  size=0x94 */
void AddQ__6CFieldFUcUcUs(CField *this,byte a0,byte a1,ushort a2)

{
  byte bVar1;
  uint uVar2;
  
  bVar1 = this->field_0x14d;
  uVar2 = (uint)bVar1;
  if ((uVar2 + 1 & 7) != (uint)(byte)this->field_0x14c) {
    (&this->field_0x2c)[uVar2 * 4] = a0;
    (&this->field_0x2d)[uVar2 * 4] = a1;
    *(ushort *)(&this->field_0x2e + uVar2 * 4) = a2;
    this->field_0x14d = bVar1 + 1 & 7;
  }
  return;
}

/* JP: 0x004d96c0  CField::ClearBgmData()   [ClearBgmData__6CFieldFv]  size=0x8c */
void ClearBgmData__6CFieldFv(CField *this)

{
  long lVar1;
  undefined1 auStack_30 [32];
  CField *pCStack_10;
  
  pCStack_10 = this;
  if (*(int *)&this->field_0x158 != 0) {
    DecodeKey__15_FieldDataCacheFPcUiUi
              (auStack_30,*(undefined4 *)&this->field_0x15c,*(undefined4 *)&this->field_0x158);
    lVar1 = Find__12CSndBufCacheFPCci(auStack_30,3);
    if (lVar1 != 0) {
      Clear__12CSndBufCacheFv();
    }
  }
  *(undefined4 *)&pCStack_10->field_0x158 = 0;
  pCStack_10->bFlags_190 = pCStack_10->bFlags_190 & 0xfc;
  return;
}

/* JP: 0x004d9750  CField::CmdBgmPlayReq(int, unsigned int)   [CmdBgmPlayReq__6CFieldFiUi]  size=0x178 */
undefined4 CmdBgmPlayReq__6CFieldFiUi(CField *this,int a0,uint a1)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 uVar3;
  long lVar4;
  
  this->bFlags_190 = this->bFlags_190 & 0xbf;
  if ((this->bFlags_18c & 1) == 0) {
    if ((this->bFlags_190 & 3) == 2) {
      lVar4 = FindType__12CSndBufCacheFi(3);
      if (lVar4 != 0) {
        PlayBGM__6CMusicFUiUiPUc(sys__6CMusic,a0,(&playModeTbl)[a1],*(undefined4 *)((int)lVar4 + 4));
        uVar2._0_1_ = this->bFlags_190;
        uVar2._1_1_ = this->bFlags_191;
        if (((ulong)uVar2 & 0x1ff) >> 7 != 0) {
          uVar1._0_1_ = this->bFlags_190;
          uVar1._1_1_ = this->bFlags_191;
          uVar2 = uVar1 & 0xfe7f | 0x100;
          this->bFlags_190 = (char)uVar2;
          this->bFlags_191 = (char)(uVar2 >> 8);
        }
        memcpy(&this->field_0x150,&this->field_0x158,8);
        this->bFlags_190 = this->bFlags_190 & 0xf3 | 4;
      }
      uVar3 = 0;
    }
    else {
      uVar3 = 0xffffffff;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

/* JP: 0x004d98d0  CField::CmdSeLoadSDH(int)   [CmdSeLoadSDH__6CFieldFi]  size=0x2b0 */
undefined4 CmdSeLoadSDH__6CFieldFi(CField *this,int a0)

{
  undefined8 uVar1;
  long lVar2;
  undefined1 *puVar3;
  
  puVar3 = &this->field_0x4c + a0 * 0x10;
  if (this->field_0x14e == '\x01') {
    if (this->pSe == (void *)0x0) {
      if (*(int *)(&this->field_0x54 + a0 * 0x10) != 0) {
        __dt__9BufMemoryFv(*(undefined4 *)(&this->field_0x54 + a0 * 0x10),1);
      }
      memset(puVar3,0,0x10);
      return 0;
    }
    uVar1 = getBuffer__9BufMemoryFv(*(undefined4 *)(&this->field_0x54 + a0 * 0x10));
    lVar2 = FindSDH__3CSeFPv(this->pSe,uVar1);
    if (lVar2 != 0) {
      __dt__9BufMemoryFv(*(undefined4 *)(&this->field_0x54 + a0 * 0x10),1);
      *(int *)(&this->field_0x54 + a0 * 0x10) = (int)lVar2;
      MarkSDH__3CSeFUii(this->pSe,lVar2,1);
      if ((((ulong)(byte)(&this->field_0x59)[a0 * 0x10] & 0x1f) >> 2 == 3) ||
         ((this->bFlags_18c & 1) != 0)) {
        RemoveSDH__3CSeFUi(this->pSe,lVar2);
        memset(puVar3,0,0x10);
      }
      else {
        (&this->field_0x59)[a0 * 0x10] = (&this->field_0x59)[a0 * 0x10] & 0xe3 | 4;
      }
      return 0;
    }
  }
  else if (this->field_0x14e == '\0') {
    if ((((ulong)(byte)(&this->field_0x59)[a0 * 0x10] & 0x1f) >> 2 == 3) ||
       ((this->bFlags_18c & 1) != 0)) {
      __dt__9BufMemoryFv(*(undefined4 *)(&this->field_0x54 + a0 * 0x10),1);
      memset(puVar3,0,0x10);
      return 0;
    }
    uVar1 = getBuffer__9BufMemoryFv(*(undefined4 *)(&this->field_0x54 + a0 * 0x10));
    lVar2 = GetWaveBank__4SdrvFPv(sys__4Sdrv,uVar1);
    UnloadSeFromBank__6CFieldFi(this,(int)lVar2);
    (&this->field_0x5a)[a0 * 0x10] = (byte)lVar2;
    if ((0x20 < lVar2) && (lVar2 < 0x24)) {
      (&this->field_0x58)[a0 * 0x10] = (byte)lVar2 & 0xf;
    }
    LoadSDH__3CSeFPv(this->pSe,uVar1);
    this->field_0x14e = this->field_0x14e + '\x01';
  }
  return 0xffffffff;
}

/* JP: 0x004d9b80  CField::FindSE(const char*)   [FindSE__6CFieldFPCc]  size=0xd0 */
int * FindSE__6CFieldFPCc(CField *this,char *a0)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int iStack_24;
  CField *pCStack_20;
  char *pcStack_10;
  
  pCStack_20 = this;
  pcStack_10 = a0;
  iVar1 = EncodeKey__15_FieldDataCacheFPCcRUi(a0,&iStack_24);
  piVar2 = (int *)&pCStack_20->field_0x4c;
  uVar3 = 0;
  while( true ) {
    if (0xf < uVar3) {
      return (int *)0x0;
    }
    if ((((uint)(((ulong)*(byte *)((int)piVar2 + 0xd) << 0x3b) >> 0x3d) - 1 < 2) &&
        (*piVar2 == iVar1)) && (piVar2[1] == iStack_24)) break;
    uVar3 = uVar3 + 1;
    piVar2 = piVar2 + 4;
  }
  return piVar2;
}

/* JP: 0x004d9c50  CField::FindSoundReq()   [FindSoundReq__6CFieldFv]  size=0xb4 */
char * FindSoundReq__6CFieldFv(CField *this)

{
  uint uVar1;
  
  uVar1 = (uint)(byte)this->field_0x14c;
  if (uVar1 != (byte)this->field_0x14d) {
    do {
      if ((&this->field_0x2c)[uVar1 * 4] == '\x02') {
        return &this->field_0x2c + uVar1 * 4;
      }
      uVar1 = uVar1 + 1 & 7;
    } while (uVar1 != (byte)this->field_0x14d);
  }
  return (char *)0x0;
}

/* JP: 0x004d9d10  CField::PollingSound()   [PollingSound__6CFieldFv]  size=0x174 */
void PollingSound__6CFieldFv(CField *this)

{
  int iVar1;
  uint uVar2;
  
  if ((this->bFlags_18c & 1) == 0) {
    UpdateObjSE__6CFieldFv(this);
  }
  uVar2 = (uint)(byte)this->field_0x14c;
  if (uVar2 != (byte)this->field_0x14d) {
    do {
      iVar1 = 0;
      if ((&this->field_0x2c)[uVar2 * 4] == '\x03') {
        iVar1 = CmdSeLoadSDH__6CFieldFi(this,(uint)(byte)(&this->field_0x2d)[uVar2 * 4]);
      }
      else if ((&this->field_0x2c)[uVar2 * 4] == '\x02') {
        iVar1 = CmdBgmPlayReq__6CFieldFiUi
                          (this,(int)(char)(&this->field_0x2d)[uVar2 * 4],
                           (uint)*(ushort *)(&this->field_0x2e + uVar2 * 4));
      }
      if (-1 < iVar1) {
        uVar2 = uVar2 + 1 & 7;
        this->field_0x14e = 0;
      }
    } while ((iVar1 == 0) && (uVar2 != (byte)this->field_0x14d));
    this->field_0x14c = (char)uVar2;
  }
  if (this->pSe != (void *)0x0) {
    (**(code **)(*(int *)((int)this->pSe + 4) + 0x14))();
  }
  return;
}

/* JP: 0x004d9e90  CField::SetEffParameter(void*, void*)   [SetEffParameter__6CFieldFPvPv]  size=0x154 */
void SetEffParameter__6CFieldFPvPv(CField *this,void *a0,void *a1)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  bVar2 = *(byte *)((int)a0 + 1);
  if (*(char *)a0 == '\0') {
    piVar5 = *(int **)((int)a0 + 4);
    for (iVar6 = 0; iVar6 < (int)(uint)bVar2; iVar6 = iVar6 + 1) {
      cVar1 = *(char *)a1;
      *piVar5 = (int)cVar1;
      uVar3 = GetModel__6CFieldFi(this,(int)cVar1);
      iVar4 = GetBaseModel__11CFieldModelFv(uVar3);
      piVar5[1] = iVar4;
      piVar5 = piVar5 + 5;
      a1 = (void *)((int)a1 + 1);
    }
  }
  else {
    iVar6 = *(int *)((int)a0 + 4);
    for (iVar4 = 0; iVar4 < (int)(uint)bVar2; iVar4 = iVar4 + 1) {
      memcpy(iVar6,a1,0xc);
      *(undefined4 *)(iVar6 + 0xc) = 0x3f800000;
      iVar6 = iVar6 + 0x10;
      a1 = (void *)((int)a1 + 0xc);
    }
  }
  return;
}

/* JP: 0x004d9ff0  CField::StartEffect(const char*, unsigned int, void*, void*)   [StartEffect__6CFieldFPCcUiPvPv]  size=0x264 */
int StartEffect__6CFieldFPCcUiPvPv(CField *this,char *a0,uint a1,void *a2,void *a3)

{
  undefined8 uVar1;
  void *a2_00;
  char *a1_00;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined1 auStack_b0 [80];
  uint uStack_60;
  uint uStack_5c;
  uint uStack_58;
  uint uStack_54;
  CField *pCStack_50;
  char *pcStack_40;
  uint uStack_30;
  void *pvStack_20;
  void *pvStack_10;
  
  uStack_5c = a1 & 0xff;
  uStack_60 = a1 >> 8 & 0xff;
  uStack_54 = a1 >> 0x10 & 0xf;
  uStack_58 = a1 >> 0x14 & 0xf;
  if (uStack_54 == 0) {
    iVar4 = 0x14;
  }
  else {
    iVar4 = 0x10;
  }
  if (uStack_58 == 0) {
    iVar6 = 0x14;
  }
  else {
    iVar6 = 0x10;
  }
  uVar3 = uStack_5c * iVar4 + 0xf & 0xfffffff0;
  uVar5 = uStack_60 * iVar6 + 0xf & 0xfffffff0;
  pCStack_50 = this;
  pcStack_40 = a0;
  uStack_30 = a1;
  pvStack_20 = a2;
  pvStack_10 = a3;
  uVar1 = __nwa__FUi(uVar5 + uVar3 + 0x20);
  memset(uVar1,0,uVar5 + uVar3 + 0x20);
  a1_00 = (char *)uVar1;
  a1_00[0x10] = (char)uStack_54;
  a1_00[0x11] = (char)uStack_5c;
  *(char **)(a1_00 + 0x14) = a1_00 + 0x20;
  a1_00[0x18] = (char)uStack_58;
  a1_00[0x19] = (char)uStack_60;
  *(char **)(a1_00 + 0x1c) = a1_00 + 0x20 + uVar3;
  SetEffParameter__6CFieldFPvPv(pCStack_50,a1_00 + 0x10,pvStack_20);
  SetEffParameter__6CFieldFPvPv(pCStack_50,a1_00 + 0x18,pvStack_10);
  iVar4 = 0;
  if (pCStack_50->pEffect_list == (void *)0x0) {
    pCStack_50->pEffect_list = a1_00;
  }
  else {
    for (piVar2 = pCStack_50->pEffect_list; *piVar2 != 0; piVar2 = (int *)*piVar2) {
      iVar4 = iVar4 + 1;
    }
    *piVar2 = (int)a1_00;
    iVar4 = iVar4 + 1;
  }
  a1_00[0xc] = a1_00[0xc] & 0xfcU | 1;
  sprintf(auStack_b0,0x558fe0,pDataPath__7SysTool,pcStack_40);
  FileReadOrder__6CFieldFiPCcPv((CField *)0x82,(int)auStack_b0,a1_00,a2_00);
  return iVar4 + 1;
}

/* JP: 0x004da290  CField::OnLoadEffect(BufMemory*, int, void*)   [OnLoadEffect__6CFieldFP9BufMemoryiPv]  size=0x16c */
undefined4 OnLoadEffect__6CFieldFP9BufMemoryiPv(CField *this,void *a0,int a1,void *a2)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  *(void **)((int)a2 + 8) = a0;
  lVar2 = __nw__FUi(0x48,a0,a1);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = __ct__6EffectFPFPvi_vPvi(lVar2,0x4da400,a2,0);
  }
  *(int *)((int)a2 + 4) = (int)uVar3;
  Create__6EffectFP9BufMemory(uVar3,a0);
  SetReplaceCallback__6EffectFPFP6EffectPvi_vPvi(uVar3,0x4da260,a2,0);
  if (*(char *)((int)a2 + 0x10) == '\0') {
    SetGenModel__6EffectFiP11tagModelSet(uVar3,*(undefined1 *)((int)a2 + 0x11),*(undefined4 *)((int)a2 + 0x14));
  }
  else {
    SetGenPos__6EffectFiP7FVector(uVar3,*(undefined1 *)((int)a2 + 0x11),*(undefined4 *)((int)a2 + 0x14));
  }
  if (*(char *)((int)a2 + 0x18) == '\0') {
    SetTarModel__6EffectFiP11tagModelSet(uVar3,*(undefined1 *)((int)a2 + 0x19),*(undefined4 *)((int)a2 + 0x1c));
  }
  else {
    SetTarPos__6EffectFiP7FVector(uVar3,*(undefined1 *)((int)a2 + 0x19),*(undefined4 *)((int)a2 + 0x1c));
  }
  *(byte *)((int)a2 + 0xc) = *(byte *)((int)a2 + 0xc) & 0xfc | 2;
  uVar1 = Run__6EffectFv(uVar3);
  return uVar1;
}

/* JP: 0x004da400  CField::OnEffectEnd(void*, int)   [OnEffectEnd__6CFieldFPvi]  size=0x38 */
void OnEffectEnd__6CFieldFPvi(CField *this,void *a0,int a1)

{
  this->field_0xc = this->field_0xc & 0xfc;
  return;
}

/* JP: 0x004da440  CField::EffectControl(int, int, int, int)   [EffectControl__6CFieldFiiii]  size=0xd4 */
uint EffectControl__6CFieldFiiii(CField *this,int a0,int a1,int a2,int a3)

{
  undefined4 *a0_00;
  uint uVar1;
  int iStack_40;
  
  iStack_40 = a0;
  for (a0_00 = this->pEffect_list;
      (iStack_40 = iStack_40 + -1, 0 < iStack_40 && (a0_00 != (undefined4 *)0x0));
      a0_00 = (undefined4 *)*a0_00) {
  }
  if (a0_00 == (undefined4 *)0x0) {
    uVar1 = 0xffffffff;
  }
  else if (a1 == 1) {
    RemoveEffect__6CFieldFPv(this,a0_00);
    uVar1 = 0;
  }
  else if (a1 == 0) {
    uVar1 = *(byte *)(a0_00 + 3) & 3;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

/* JP: 0x004da520  CField::RemoveEffect(void*)   [RemoveEffect__6CFieldFPv]  size=0xf8 */
/* WARNING: Removing unreachable block (ram,0x004da5b8) */

void RemoveEffect__6CFieldFPv(CField *this,void *a0)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = this->pEffect_list;
  do {
    do {
      puVar3 = puVar1;
      if (puVar3 == (undefined4 *)0x0) {
        return;
      }
      puVar1 = (undefined4 *)*puVar3;
    } while ((a0 != (void *)0x0) && (puVar3 != a0));
    if (puVar3[1] != 0) {
      iVar2 = puVar3[1];
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
      }
      puVar3[1] = 0;
    }
    this->pEffect_list = puVar1;
    __dla__FPv(puVar3);
  } while (a0 == (void *)0x0);
  return;
}
