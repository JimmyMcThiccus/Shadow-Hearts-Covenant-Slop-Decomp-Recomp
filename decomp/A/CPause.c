/* Section A -- CPause (0x003d7e90..0x003d8678) */
void CPause_Pause(CPause *p) {
  if (p->disablePause == 0 && !(p->flags & 1)) {
    p->flags |= 2;
    for (CbNode *n = p->cb; n; n = n->next) for (int i = 0; i < 16; i++) if (n->e[i].fn) n->e[i].fn(0, n->e[i].arg);
    p->flags &= ~2; p->flags |= 1;
  }
}
bool CPause_CheckUnPause(CPause *p, u32 pad, u32 mask) {
  if (!mask) mask = 8;                                     /* START */
  p->padState &= pad & mask;
  bool hit = (pad & (~mask | ~(u32)p->padState)) == mask;
  if (hit) p->padState = mask;
  return hit;
}
bool CPause_CheckReset(CPause *p, u32 pad, u32 now, u32 mask) {
  if (!mask) mask = 0xf09;
  if (p->disableReset == 0) switch (p->flags >> 6) {
    case 0: if ((pad & mask) == 0) p->flags = (p->flags & 0x3f) | 0x40; break;                       /* armed */
    case 1: if (mask == (pad & mask)) { p->resetStart = now; p->flags = (p->flags & 0x3f) | 0x80; } break;
    case 2: if (mask == (pad & mask)) { if (now - p->resetStart > 1000) return 1; } else p->flags &= 0x3f; break;
  }
  return 0;
}
void CPause_Reset(CPause *p) { p->flags = (p->flags & ~8) | 8; }
