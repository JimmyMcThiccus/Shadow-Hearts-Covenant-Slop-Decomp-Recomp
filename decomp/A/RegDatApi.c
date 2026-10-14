/* Section A -- RegDatApi heap (SLPM_602.19 0x0037b130..) */
#define REG_BASE 0x108000
#define REG_END  0x200000
void RegDatApi_Initialize(void) {
  *(u32*)(REG_BASE+0)=0; *(u32*)(REG_BASE+4)=0; *(u32*)(REG_BASE+8)=REG_END; *(u32*)(REG_BASE+0xc)=0xf7ff0;  /* one free block */
  GetLanguage();
  RegDataReadEntry("common/sshmes.jpn", "reg1", 0, 0);
  RegDataReadEntry("common/sshdat.jpn", "reg2", 0, 0);
}
void *RegDatApi_SetData(void *data, u32 size, const char *tag) {
  Block *best = 0; u32 need = (size + 15) & ~15;
  for (Block *b = REG_BASE; b < REG_END; b = b->next) if (b->tag[0]==0 && need <= b->size && b->size < 0x100000) best = b;   /* last fit */
  if (!best) return 0;
  if (best->size - need > 0x10) { Block *n = (u8*)best + need + 0x10; n->tag[0]=0; n->next = best->next; best->next = n; n->prev = best; n->size = (u8*)n->next - (u8*)(n+1); }
  strncpy(best->tag, tag, 4); best->size = size; memcpy(best+1, data, size); return best + 1;
}
