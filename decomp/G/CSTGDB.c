/* ==== CLEANED (main exe; port: sh2_field/src/mps.rs::Mps::parse) ==== */
#include "_types.h"
/* JP 0x003c1f60 CSTGDB::CSTGDB() */
CSTGDB *CSTGDB_ctor(CSTGDB *t) { t->vt0 = t->vt1 = 0; t->vtbl = __vt__17DelayDeleteObject; t->vtbl = __vt__6CSTGDB; t->buf = 0; t->order_id = -1; t->state = 0; t->data = 0; t->chunk_count = 0; t->chunks = 0; return t; }

/* JP 0x003c2390 CSTGDB::Load(const char *path): async read through DvdromOrder, callback sdbReadCB (0x003c1ef0) */
int CSTGDB_Load(CSTGDB *t, const char *path) {
    if (t->buf || t->state) return 0;
    t->order_id = DvdromOrder_ReadOrder(Dvdromour__11DvdromOrder, path, sdbReadCB, 0, t, 0);
    t->state = 1; return 1;
}
/* JP 0x003c2420 CSTGDB::LoadCB(BufMemory *b, int skip) -- buffer arrived (or was supplied by CSndBufCache) */
int CSTGDB_LoadCB(CSTGDB *t, BufMemory *b, int skip) {
    t->order_id = -1; t->buf = b; t->state = 0;
    return skip == 0 && CSTGDB_SetData(t, b->data);
}
/* JP 0x003c2070 CSTGDB::SetData(void *file) */
int CSTGDB_SetData(CSTGDB *t, void *file) {
    if (t->state != 0) { t->state = -1; return 0; }
    t->data = file;
    if (t->chunks) { delete[] t->chunks; t->chunks = 0; t->chunk_count = 0; }
    t->state = 2;
    return CSTGDB_InitSDB(t);
}
/* JP 0x003c2170 CSTGDB::InitSDB(): validate "SBD 0.10"/"SBD 0.11", date "01110623", "FILEHDR ", then walk "LINKHDR " */
int CSTGDB_InitSDB(CSTGDB *t) {
    u8 *f = t->data; if (!f) return 0;
    if (*(u64 *)(f + 0x10) != 'FILEHDR ' || !(*(u64 *)f == 'SBD 0.10' || *(u64 *)f == 'SBD 0.11') || *(u64 *)(f + 8) != '01110623') return 0;
    u32 *link = (u32 *)(f + *(u32 *)(f + 0x1c));
    if (*(u64 *)link != 'LINKHDR ' || link[2] == 0) return 0;
    u8 *entry = (u8 *)link + link[3];
    t->chunk_count = link[2];
    t->chunks = new SDB_tagHEADER *[t->chunk_count];
    for (int i = 0; i < t->chunk_count; i++, entry += 0x10) t->chunks[i] = (SDB_tagHEADER *)(entry + *(u32 *)(entry + 0xc));
    return 1;
}
/* JP 0x003c2580 CSTGDB::Find(u64 tag) */
SDB_tagHEADER *CSTGDB_Find(CSTGDB *t, u64 tag) {
    if (t->state == 2) for (int i = 0; i < t->chunk_count; i++) if (*(u64 *)t->chunks[i] == tag) return t->chunks[i];
    return 0;
}
/* JP 0x003c2630 */ int   CSTGDB_GetDataNum(CSTGDB *t, SDB_tagHEADER *h)  { return h ? h->count : -1; }
/* JP 0x003c2670 */ void *CSTGDB_GetDataAddr(CSTGDB *t, SDB_tagHEADER *h) { return h ? (char *)h + h->data_off : 0; }
/* JP 0x003c26c0 CSTGDB::FindGenericData(const char *name): GENERIC chunk = {char name[16]; u32 stride@+0x10; data@+0x20} */
char *CSTGDB_FindGenericData(CSTGDB *t, const char *name) {
    SDB_tagHEADER *h = CSTGDB_Find(t, 'GENERIC '); if (!h) return 0;
    char *e = CSTGDB_GetDataAddr(t, h);
    for (int i = 0; i < CSTGDB_GetDataNum(t, h); i++) { if (!strcmp(e, name)) return e; e += *(int *)(e + 0x10); }
    return 0;
}


/* ==== RAW (Ghidra output, names/globals resolved; not hand-cleaned) ==== */
/* SECTION G  main-executable side: CSTGDB / SDB (MPS) container loader
 * JP SLPM_602.19 (Furokuban). Ghidra decompile with symbols/gp globals resolved. */

/* JP: 0x003c1f60  CSTGDB::CSTGDB()   [__ct__6CSTGDBFv]  size=0x7c */
undefined4 * __ct__6CSTGDBFv(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = __vt__17DelayDeleteObject;
  param_1[2] = __vt__6CSTGDB;
  param_1[3] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[5] = 0;
  param_1[4] = 0xffffffff;
  return param_1;
}

/* JP: 0x003c1fe0  CSTGDB::~CSTGDB()   [__dt__6CSTGDBFv]  size=0x8c */
int __dt__6CSTGDBFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = __vt__6CSTGDB;
    ClearData__6CSTGDBFv(param_1);
    if (param_1 != 0) {
      *(undefined1 **)(param_1 + 8) = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x003c2070  CSTGDB::SetData(void*)   [SetData__6CSTGDBFPv]  size=0xa0 */
undefined8 SetData__6CSTGDBFPv(int param_1,undefined4 param_2)

{
  undefined8 uVar1;
  
  if (*(int *)(param_1 + 0x14) == 0) {
    *(undefined4 *)(param_1 + 0x18) = param_2;
    if (*(int *)(param_1 + 0x20) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x20));
      *(undefined4 *)(param_1 + 0x20) = 0;
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
    *(undefined4 *)(param_1 + 0x14) = 2;
    uVar1 = InitSDB__6CSTGDBFv(param_1);
  }
  else {
    *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x003c2110  CSTGDB::CheckVersion(unsigned long)   [CheckVersion__6CSTGDBFUl]  size=0x54 */
undefined4 CheckVersion__6CSTGDBFUl(int param_1,long param_2)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 0x18) == 0) || (**(long **)(param_1 + 0x18) != param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x003c2170  CSTGDB::InitSDB()   [InitSDB__6CSTGDBFv]  size=0x214 */
undefined4 InitSDB__6CSTGDBFv(int param_1)

{
  undefined4 uVar1;
  long *plVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    uVar1 = 0;
  }
  else if (((*(long *)(*(int *)(param_1 + 0x18) + 0x10) == 0x20524448454c4946) &&
           (**(long **)(param_1 + 0x18) == 0x30312e3020444253 ||
            **(long **)(param_1 + 0x18) == 0x31312e3020444253)) &&
          (*(long *)(*(int *)(param_1 + 0x18) + 8) == 0x3332363031313130)) {
    plVar2 = (long *)(*(int *)(*(int *)(param_1 + 0x18) + 0x1c) + *(int *)(param_1 + 0x18));
    if ((*plVar2 == 0x205244484b4e494c) && ((int)plVar2[1] != 0)) {
      iVar3 = *(int *)((int)plVar2 + 0xc) + (int)plVar2;
      *(int *)(param_1 + 0x1c) = (int)plVar2[1];
      uVar1 = __nwa__FUi((int)plVar2[1] << 2);
      *(undefined4 *)(param_1 + 0x20) = uVar1;
      for (iVar4 = 0; iVar4 < (int)plVar2[1]; iVar4 = iVar4 + 1) {
        *(int *)(*(int *)(param_1 + 0x20) + iVar4 * 4) = iVar3 + *(int *)(iVar3 + 0xc);
        iVar3 = iVar3 + 0x10;
      }
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x003c2390  CSTGDB::Load(const char*)   [Load__6CSTGDBFPCc]  size=0x90 */
undefined4 Load__6CSTGDBFPCc(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 0xc) == 0) && (*(int *)(param_1 + 0x14) == 0)) {
    uVar1 = ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
                      (Dvdromour__11DvdromOrder,param_2,0x3c1ef0,0,param_1,0);
    *(undefined4 *)(param_1 + 0x10) = uVar1;
    *(undefined4 *)(param_1 + 0x14) = 1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x003c2420  CSTGDB::LoadCB(BufMemory*, int)   [LoadCB__6CSTGDBFP9BufMemoryi]  size=0x9c */
undefined4 LoadCB__6CSTGDBFP9BufMemoryi(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  long lVar2;
  
  *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
  *(int *)(param_1 + 0xc) = param_2;
  *(undefined4 *)(param_1 + 0x14) = 0;
  if ((param_3 == 0) &&
     (lVar2 = SetData__6CSTGDBFPv(param_1,*(undefined4 *)(param_2 + 4)), lVar2 != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x003c24c0  CSTGDB::ClearData()   [ClearData__6CSTGDBFv]  size=0xb4 */
undefined4 ClearData__6CSTGDBFv(int param_1)

{
  if (*(int *)(param_1 + 0x10) != -1) {
    deleteOrder__11DvdromOrderFi(Dvdromour__11DvdromOrder,*(undefined4 *)(param_1 + 0x10));
    *(undefined4 *)(param_1 + 0x10) = 0xffffffff;
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0xc),1);
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  *(undefined4 *)(param_1 + 0x14) = 0;
  if (*(int *)(param_1 + 0x20) != 0) {
    __dla__FPv(*(undefined4 *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  return 1;
}

/* JP: 0x003c2580  CSTGDB::Find(unsigned long)   [Find__6CSTGDBFUl]  size=0xa8 */
undefined4 Find__6CSTGDBFUl(int param_1,long param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x14) == 2) {
    for (iVar1 = 0; iVar1 < *(int *)(param_1 + 0x1c); iVar1 = iVar1 + 1) {
      if (param_2 == **(long **)(*(int *)(param_1 + 0x20) + iVar1 * 4)) {
        return *(undefined4 *)(*(int *)(param_1 + 0x20) + iVar1 * 4);
      }
    }
  }
  return 0;
}

/* JP: 0x003c2630  CSTGDB::GetDataNum(SDB::tagHEADER*)   [GetDataNum__6CSTGDBFPQ23SDB9tagHEADER]  size=0x3c */
undefined4 GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(undefined8 param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *(undefined4 *)(param_2 + 8);
  }
  return uVar1;
}

/* JP: 0x003c2670  CSTGDB::GetDataAddr(SDB::tagHEADER*)   [GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER]  size=0x48 */
int GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(undefined8 param_1,int param_2)

{
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + *(int *)(param_2 + 0xc);
  }
  return param_2;
}

/* JP: 0x003c26c0  CSTGDB::FindGenericData(const char*)   [FindGenericData__6CSTGDBFPCc]  size=0xf8 */
char * FindGenericData__6CSTGDBFPCc(undefined4 param_1,char *param_2)

{
  int iVar1;
  char *__s1;
  int iVar2;
  long lVar3;
  int iVar4;
  
  lVar3 = Find__6CSTGDBFUl(param_1,0x20434952454e4547);
  if (lVar3 != 0) {
    iVar1 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(param_1,lVar3);
    __s1 = (char *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(param_1,lVar3);
    for (iVar4 = 0; iVar4 < iVar1; iVar4 = iVar4 + 1) {
      iVar2 = strcmp(__s1,param_2);
      if (iVar2 == 0) {
        return __s1;
      }
      __s1 = __s1 + *(int *)(__s1 + 0x10);
    }
  }
  return (char *)0x0;
}
