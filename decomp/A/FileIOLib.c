/* Section A -- FileIOLib (SLPM_602.19 0x0022a910..) path resolution + name hash + open/read/close */
/* 0x0022cfb0 enCode */ void FileIOLib_enCode(FileIOLib *f, const char *name, u8 out[8]) {
  u8 d[12] = {0}; int n = 0;
  for (int i = 0; i < 12; i++) {
    for (int k = 0x25; k >= 0; k--) if (name[i] == ALPHABET[k] || name[i] - 0x20 == ALPHABET[k]) { d[n++] = k + 1; break; }
  }
  u32 hi[3], lo[3];
  for (int g = 0; g < 3; g++) { u32 u = d[g*4] + d[g*4+1]*40 + d[g*4+2]*1600 + d[g*4+3]*64000; hi[g] = u >> 16; lo[g] = u & 0xffff; }
  u32 w0 = (hi[0] + hi[1]*40 + hi[2]*1600) << 16 | lo[0], w1 = lo[1] << 16 | lo[2];
  out[0]=w0>>24; out[1]=w0>>16; out[2]=w0>>8; out[3]=w0; out[4]=w1>>24; out[5]=w1>>16; out[6]=w1>>8; out[7]=w1;
}
/* 0x0022c980 searchInfo */ int FileIOLib_searchInfo(FileIOLib *f, int start, u32 key[2], int *cnt) {
  for (int i = start; i < f->entryCount; i++) {
    if (start == 0 && Dircount < i) break;
    if (i < Dircount) ++*cnt;
    if (f->ent[i].key[0] == key[0] && f->ent[i].key[1] == key[1]) return i;
  }
  return -1;
}
/* 0x0022c7a0 SearchFile */ bool FileIOLib_SearchFile(FileIOLib *f, const char *path, _CDVDRINFO *out) {
  int sum = 0, list = 0; char tok[12]; u32 key[2];
  while (path) {
    memset(tok, 0, 12); path = gettokun(f, path, tok); FileIOLib_enCode(f, tok, key);
    int cnt = 0, i = FileIOLib_searchInfo(f, list, key, &cnt);
    if (i < 0) return 0;
    PkbEntry *e = &f->ent[i]; sum += e->off16;
    if (list == 0) out->lba = e->off16; else out->lba += e->off16 >> 7;
    if (e->size_or_dir & 0x80000000) list += (e->size_or_dir & 0x7fffffff) / f->entSize;
    else { out->size = e->size_or_dir; }
    out->sum = sum;
  }
  return 1;
}
/* 0x0022bf90 open */ _FIOHND *FileIOLib_open(FileIOLib *f, const char *path, int flags) {
  WaitSema(f->semaQueue);
  if (!f->inhibit && EEFioStatus != 0xf003 && EEFioStatus == 0) {
    _FIOHND *h = getFileHand(); memset(h, 0, 0xc0); h->self = h; h->openFlags = flags;
    if (!makeHandler(f, h, path, 1 /*cdrom*/, 0)) h = 0;
    if (h) { h->status = 0xf001; memcpy(&fioHandSend, h, 0xc0); fioCmdCall(f, 1 /*open*/, 0xc0); Dvdromour->openInFlight = 1; h->openTime = SysTool_GetTimer(); }
    SignalSema(f->semaQueue); return h;
  }
  SignalSema(f->semaQueue); return 0;
}
