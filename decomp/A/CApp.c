/* Section A -- app.cpp (SLPM_602.19 0x003d53f0..0x003d8768). Cleaned from Ghidra; types from notes/A/CApp.md */
typedef struct CList { struct CList *next, *prev; } CList;
typedef struct CPolObj { struct CPoller *owner; struct CPolObj *next, *prev; u8 autoDelete, linked, killReq, _f; u16 priority; u16 _p; void **vtbl; } CPolObj;
typedef struct CPoller { CPolObj *head, *tail, *current; } CPoller;

/* 0x003d6470 CPolObj::CPolObj */
CPolObj *CPolObj_ct(CPolObj *this) { this->vtbl = __vt__7CPolObj; this->owner = 0; this->prev = 0; this->next = 0; this->priority = 0x80; this->autoDelete = 0; return this; }

/* 0x003d6550 CPolObj::Remove */
void CPolObj_Remove(CPolObj *this) {
  if (this->linked) {
    CPolObj *n = this->next, *p = this->prev;
    if (this->owner->head == this) this->owner->head = n;
    if (this->owner->tail == this) this->owner->tail = p;
    if (this->owner->current == this) this->killReq = 1;       /* removed while being polled */
    if (n) n->prev = p;
    if (p) p->next = n;
    this->linked = 0; this->_f = 0;
  }
}
/* 0x002ff6e0 CPolObj::SetAutoDelete */
void CPolObj_SetAutoDelete(CPolObj *this, bool b) { this->autoDelete = b; this->killReq = 0; }

/* 0x003d6710 CPoller::Entry -- sorted insert, ascending priority */
int CPoller_Entry(CPoller *this, CPolObj *o, int prio, bool autoDelete) {
  int dup = CPoller_Find(this, o) ? printf("already linked %p", o) : 0;
  o->autoDelete = autoDelete; o->killReq = 0; o->priority = prio;
  if (!this->head) { o->owner = this; o->linked = 1; this->head = this->tail = o; }
  else {
    CPolObj *prev = 0;
    for (CPolObj *c = this->head; c; c = c->next) {
      if (prio < c->priority) { insert_before(c, prev, o); o->owner = this; o->linked = 1; return dup; }
      prev = c;
    }
    insert_after(prev, o); o->owner = this; o->linked = 1; this->tail = o;
  }
  return dup;
}
/* 0x003d6b30 CPoller::Dispose */
void CPoller_Dispose(CPoller *this, CPolObj *o) {
  if (this->head && o && CPoller_Find(this, o) == o) {
    CPolObj_Remove(o);
    if (o->autoDelete && !o->killReq) o->vtbl[2](o, 1);          /* __dt */
  }
}
/* 0x003d6c90 CPoller::Polling */
void CPoller_Polling(CPoller *this) {
  CPolObj *o = this->head;
  while (o) {
    this->current = o;
    char done = o->vtbl[3](o);                                    /* Polling() */
    CPolObj *next = o->next;
    if (done || o->killReq) { CPolObj_Remove(o); if (o->autoDelete) o->vtbl[2](o, 1); }
    o = next;
  }
}

/* 0x00221ea0 main */
int main(int argc, char **argv) {
  FullAllocAndFree(); mwInit(); CApp_InitialReset(); CApp_SetRebootPath(argv[0]); CApp_InitScreen(512, 448);
  CApp *app = new CApp(/*prio*/1, /*flag*/0xF, /*stack*/0x10000);   /* operator new(0x150) */
  CApp__app = app; CThread_StartThread(app); SleepThread(); mwExit(); return 0;
}
/* 0x003d76d0 */ void CApp_InitInstance(CApp *this) { this->m_pause = new CPause; InitMain(); }
/* 0x002221d0 */ int InitMain(void) { return SSHMain() && (opening(), 1); }

/* 0x003d7730 CApp::Run -- frame loop, see notes/A/CApp.md */
void CApp_Run(CApp *this) {
  GsxCamera *cam = World_GetCamera(&m_World, 0); if (cam) GsxCamera_FlipBuffer(cam, 0);
  m_wcount = m_ecount = m_hcount = m_vcount = 0;
  World_GetPacket(&m_World);
  this->vec[0] = this->vec[1] = (FVector){1/256.f, 1/256.f, DAT_0040a880, 0.875f};
  for (;;) {
    Gsx_m_flags |= 0x20;
    if (m_camera) { World_BeginUpdate(&m_World); World_WorldRender(&m_World); World_EndUpdate(&m_World); }
    CPoller_Polling(&this->pollSys);                                  /* +0x60 */
    if (!(this->pause->flags & 1)) { CPoller_Polling(&this->pollGame0); CPoller_Polling(&this->pollGame1); }
    if (m_pAppFunc) m_pAppFunc();
    World_GetPacket(&m_World);
    h0 = rcnt3_elapsed(); ScreenBright_Draw(m_pBright); h1 = rcnt3_elapsed();
    sceGsSyncPath(0, 0);
    for (CList *n = RemoveHead(&this->delayDelete); n; ) { CList *nx = n->next; CList_Remove(n); n->vtbl[2](n, 1); n = nx; }
    if (m_capmd) { m_capmd--; this->capReq = 1; }
    if (this->capReq && m_camera) {
      for (i = 0; i < 60; i++) if (!capTbl[i]) { capTbl[i] = GsxCamera_CaptureOut(m_camera); if (m_capmd && i == 59) CApp_CaptureFlush(); goto done; }
      printf("capture overflow"); done: this->capReq = 0;
    }
    m_ecount += (h0 - h1) + elapsed();
    Gsx_DrawSync(0, 0); u32 used = elapsed(); m_hcount += used; if (used > m_wcount) m_wcount = used; m_vcount++;
    if (GsxGetVSyncCount() < Gsx_m_syncCount) { while (Gsx_m_flags & 0x10) ; Gsx_VSync(Gsx_m_syncCount); }
    else { GsxForceFlip(); GsxClrVSyncCount(); }
    HCount = REG_RCNT3_COUNT; UpdatePolBreakState();
    if (this->pause->flags & 8) DoReset();
  }
}
/* 0x003d7bf0 */ void CApp_SetBright(float f) { if (f > 1.f) f = 1.f; m_pBright->alpha = (u8)(128.f - f * 128.f); }
