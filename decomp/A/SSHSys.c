/* Section A -- SSHmain.cpp: SSHSys / SSHApi / SSHMain (SLPM_602.19). US addresses in notes/A/us_map.txt */
/* 0x003b6130 */ bool SSHSys_SetAPI(SSHSys *s, SSHApi *api) {
  if (s->pending) return 0;
  if (s->current && s->curState < 3) s->curState = 3;
  s->pendState = 1; s->pending = api; return 1;
}
/* 0x003b6230 */ int SSHSys_Polling(SSHSys *s) {
  int t = SysTool_GetTimer(); s->frameDelta = t - s->lastTime; s->lastTime = t;
  sm_pSubstance->slot->playtime += s->frameDelta;              /* SaveMenuSection play time */
  CPad_Polling();
  if (s->fioBusy && ourFio->diskState != 0) s->fioBusy = 0;
  if (s->pauseTmr && (s->pauseTmr -= s->frameDelta) < 0) s->pauseTmr = 0;
  if (s->initPhase == 1) { if (MenuObj_IsReady() && BgEffectMan_cmnTexture) s->initPhase = 0; }
  else if (s->initPhase == 0) {
    if (s->curState == 3) { if (!s->current) s->curState = 0; else if (!s->current->vtbl->closeInquiry(s->current)) s->curState = 4; }
    if (s->pendState == 1) {
      if (!s->pending) { s->pendState = 0; goto api; }
      if (!s->pending->vtbl->preLoad(s->pending)) goto api;
      s->pendState = 2;
    }
    if (s->pendState == 2 && (!s->current || s->curState == 4)) {
      if (s->current) { s->current->vtbl->__dt(s->current, 1); s->current = 0; }
      s->curState = 0;
      if (s->pending) { s->pending->vtbl->Start(s->pending); s->current = s->pending; s->pending = 0; s->pendState = 0; }
    }
  }
api: SSHSys_PollingApi(s); return 0;
}
/* 0x003b6f40 */ void SSHSys_PollingApi(SSHSys *s) {
  if (pSysSE) { if (Sdrv_GetStatus(sys__Sdrv, sysReq) == 3) { Sdrv_CloseHandle(sys__Sdrv, sysReq); delete pSysSE; pSysSE = 0; } }
  if (s->initPhase) return;
  switch (s->request) {
  case 0x10: InitFieldSocketM(s->fieldName); s->request = 0; break;
  case 0x30: new GameOver; SSHSys_SetAPI(s, 0); s->request = 0; break;
  case 0x21: {
    MONSETTbl *tbl = RegDatApi_GetRegDat(0x2f, s->btl.regdatId, -1);
    InitBtlSocket();
    ourBtlSocket->cb = cbBattle; ourBtlSocket->cbArg = s; ourBtlSocket->field15c = s->btl.w0;
    BtlSocket_SetBtlBGMNumber(ourBtlSocket, s->btl.bgm);
    BtlSocket_SetPC(ourBtlSocket, s->btl.pcCount, s->btl.pc);
    BtlSocket_SetMonsterSet(ourBtlSocket, s->btl.monsterSet, tbl);
    s->request = 0; break; }
  }
}
/* 0x003b6c20 */ void SSHSys_StartBattle(SSHSys *s, _SysBtlParam *p, const char *field) {
  if (!p) { if (s->request == 0x20) s->request++; }
  else { s->btl = *p; s->request = 0x20; s->fieldName[0] = 0; }
  if (field && *field) strcpy(s->fieldName, field);
}
/* 0x003b6d90 */ int SSHSys_cbBattleA(SSHSys *s, int code) {
  if (code == 0) {
    u8 r = ourBtlSocket->result & 3; s->btlResult[0] = 2;
    if (r == 2 || r == 3) { s->btlResult[1] = 0xff; s->request = 0x10; SetChrPosSaveState(2); }
    else if (r == 1) { s->btlResult[1] = 0;
      if (!s->btlResult[2]) { s->request = 0x30; FieldPreLoadCancel(); } else { s->request = 0x10; SetChrPosSaveState(2); } }
    else if (r == 0) { SetChrPosSaveState(2); s->btlResult[1] = 1; s->request = 0x10; }
    s->btlResult[2] = 0;
  } else if (code == 1) FieldPreLoad(s->fieldName);
  return 1;
}
/* 0x003b7250 */ void SSHSys_ChkResetPause(SSHSys *s, CPad *pad, bool doPause, bool doReset) {
  if (!pad) return;
  CPadCore *c = CPad_m_pCoreArray[pad->port]; u16 st = c->real; CAnalogStick L = c->stickL;
  if (L.gauge >= 0.1f) st |= 0x10;
  if (doReset && CApp_CheckReset(app, st, SysTool_GetTimer(), 0)) CApp_Reset(app);
  if (doPause && CApp_CheckPause(app, st, 0) && s->pauseTmr == 0) { CApp_Pause(app); s->pauseTmr = s->pauseReload; }
}
/* 0x003b7410 */ void DoReset(void) {
  Sdrv_Reset(2); CPad_ResetSystem(); FileIOLib_ResetSystem(ourFio);
  if (sys__Gsx) Gsx_Close(sys__Gsx); Gsx_Reset(); sceDmaReset(0); scePadEnd(); sceSifExitCmd();
  CApp_SystemReset(); CApp_Reboot();                            /* LoadExecPS2(rebootPath) */
}
/* 0x0023bec0 SSHMain */
bool SSHMain(void) {
  char path[128]; sprintf(path, FMT, "IOPRP271.IMG" /*+region dir*/);
  sceSifInitRpc(0); sceCdInit(0); sceCdMmode(1);
  while (!sceSifRebootIop(path)) ; while (!sceSifSyncIop()) ;
  sceSifInitRpc(0); sceCdInit(0); sceCdMmode(1); sceSifInitIopHeap(); sceFsReset();
  if (!SSHLoadModules(pass1) || !SSHLoadModules(pass2)) return 0;   /* SIO2MAN MCMAN MCSERV PADMAN | IOPUTY FIO LIBSD SDRV_IOP */
  SSHSys_PathInit();                                                /* pDataPath = "", Language = GetLanguage() */
  if (!FileIOLib_PluginAttach()) return 0;
  Sdrv_Reset(0);
  sys__SSHSys = new SSHSys;                                         /* 0xb0 */
  return SSHSys_Initialize(sys__SSHSys) != 0;
}
