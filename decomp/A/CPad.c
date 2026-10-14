/* Section A -- CPad (SLPM_602.19 0x0022fef0) update pipeline; see notes/A/CPad.md */
void CPad_Update(CPad *p) {
  CPadCore *c = CPad_m_pCoreArray[p->port]; u8 *d = c->padMan->padData;
  u16 btn = d[3] * 0x100 + d[2];
  CAnalogStick_Make(&c->stickL, d[6], d[7]); CAnalogStick_Make(&c->stickR, d[4], d[5]);
  if (p->mode == 2) {
    u16 t = btn & 0xff0f;
    if (!(c->stickL.up + c->stickL.down + c->stickL.left + c->stickL.right)) CAnalogStick_MakeBtn(&c->stickL, btn);
    else { if (c->stickL.up) t |= 0x10; if (c->stickL.down) t |= 0x40; if (c->stickL.left) t |= 0x80; if (c->stickL.right) t |= 0x20; btn = t; }
  } else if (p->mode == 1) {
    if (!(btn & 0xf0)) { if (c->stickL.up) btn |= 0x10; if (c->stickL.down) btn |= 0x40; if (c->stickL.left) btn |= 0x80; if (c->stickL.right) btn |= 0x20; }
    else CAnalogStick_MakeBtn(&c->stickL, btn);
  }
  CPad_MakeReal(p, btn);
  c->press = ~c->prevReal & c->real; c->release = c->prevReal & ~c->real;
  CPad_MakeRepeat(p);
  c->accPress |= c->press; c->accRelease |= c->release;
}
void CAnalogStick_Make(CAnalogStick *s, u8 x, u8 y) {
  memset(s, 0, 16); int dx = x - 0x80, dy = y - 0x80;
  if (dx > 0) { if (x - 0xaf > 0) s->right = x - 0xaf; } else if (dx < 0 && -0x30 - dx > 0) s->left = -0x30 - dx;
  if (dy > 0) { if (y - 0xaf > 0) s->down = y - 0xaf; } else if (dy < 0 && -0x30 - dy > 0) s->up = -0x30 - dy;
  if (s->up + s->down + s->left + s->right) CAnalogStick_Calculate(s);
}
