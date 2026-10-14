/* Section A -- Overlay / mwOverlayInit (SLPM_602.19 0x0023d150..0x0023d770, 0x00384c60) */
void mwOverlayInit(u8 *addr, int loaded) {
  int bss = *(int *)(addr + 0x14); FlushCache(2);
  if (bss) memset(addr + loaded, 0, bss);
  __initialize_cpp_rts(*(void ***)(addr + 0x18), *(void ***)(addr + 0x1c));    /* call every ctor in [begin,end) */
}
int Overlay_Load(Overlay *o, const char *path, OverlayCb cb, int a0, void *a1) {
  if (BufMemory_getBuffer(&o->buf)) return 2;                  /* already resident / loading */
  o->loadedSize = 0; o->cb = cb; o->a0 = a0; o->a1 = a1;
  BufMemory_SetBuffer(&o->buf, 0, o->addr);                    /* DVD read goes straight to the fixed load address */
  switch (o->preState) {
    case 2: Overlay_CopyFromPrebuffer(o); cbOverlayLoad(0, &o->buf, o->preSize, path, o); return 3;
    case 1: o->loadPending = 1; return 0;
    default: DvdromOrder_ReadOrder(Dvdromour, path, cbOverlayLoad, 0, &o->buf, o, 0); return 0;
  }
}
void Overlay_InitCashe(Overlay *o, int size) {
  o->loadedSize = size; mwOverlayInit(o->addr, size);
  if (o->cb) o->cb(0, 1, o->a0, o->a1);
  o->preBuf = 0; o->preState = 0; o->preSize = 0; o->loadPending = 0;
}
