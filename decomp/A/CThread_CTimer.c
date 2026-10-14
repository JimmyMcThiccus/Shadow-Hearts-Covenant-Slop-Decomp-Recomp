/* Section A -- CThread / CTimer (SLPM_602.19 0x003d53f0..0x003d6454) */
/* 0x003d55b0 */ bool CThread_CreateThread(CThread *t, CThread *arg, void (*entry)(void*), u16 usePrio, u16 prio, u32 stackSize) {
  u32 sz = (stackSize + 15) & ~15;
  if (!t->timer) t->timer = new CTimer(TIMER_CLOCK_MS, t);           /* kind 2: wake this thread */
  t->_8 = arg; t->tp.entry = entry; t->stack = new u8[sz]; t->stackSize = sz;
  if (usePrio == 0) { t->tp.initPriority = 0xf; t->flags |= 4; } else { t->tp.initPriority = prio; t->flags &= ~4; }
  t->tp.gp = &_gp; t->tp.option = t;
  t->tid = CreateThread(&t->tp); t->flags = (t->flags & ~3) | 3;      /* alive */
  return t->tid != 0;
}
/* 0x003d5950 */ void CThread_EnterInstance(CThread *t) {
  t->exitCode = -1;
  t->exitCode = t->vtbl[4](t) /*InitInstance*/ ? t->vtbl[5](t) /*Run*/ : t->vtbl[3](t) /*ExitInstance*/;
  CThread_Delete(t, t);
}
/* 0x003d5890 */ void CThread_StartThread(CThread *t) { if (t->flags & 1) StartThread(t->tid, t); }
/* 0x003d58e0 */ void CThread_Wait(CThread *t, int ms) { CTimer_ResetStart(t->timer, ms, 0); SleepThread(); }

/* 0x003d5a60 CTimer::InitialReset */
void CTimer_InitialReset(short videoMode) {
  m_pTblMS = m_pTblVV = m_pTblVS = 0; DisableIntc(9); RCNT0_MODE = 0;
  RCNT0_TARGET = videoMode < 7 ? 0x823 : 0x249f; RCNT0_MODE = 0xdd1;
  m_hid0 = AddIntcHandler(9, TimerWatcher0, 0); EnableIntc(9);
}
/* 0x003d5b70 TimerWatcher0 (INTC 9): ms list every irq, VV list every 17th */
int CTimer_TimerWatcher0(int) {
  RCNT0_MODE |= 0xc00; m_fractionVV++;
  tick_list(m_pTblMS);
  if (m_fractionVV > 16) { tick_list(m_pTblVV); m_fractionVV = 0; }
  SYNC(0); EI(); return 0;
}
static void tick_list(CTimer *t) {
  for (; t; t = t->next) if ((t->flags & 1) && (t->total++, t->flags & 2) && ++t->count >= t->period) {
    if (t->kind == 2) { iWakeupThread(t->thread->tid); CTimer_Stop(t); }
    else if (t->kind == 1 && (!t->cb(t) || !(t->flags & 4))) CTimer_Stop(t);
    t->count = 0;
  }
}
/* 0x00 SysTool::GetTimer (0x0023c6d0) */
int SysTool_GetTimer(void) {
  int d = timer->total - delta;
  if (d > 0) { float f = fraction + d * timerScale; int w = (int)f; counter += w; fraction = f - w; delta = timer->total; }
  return counter;
}
