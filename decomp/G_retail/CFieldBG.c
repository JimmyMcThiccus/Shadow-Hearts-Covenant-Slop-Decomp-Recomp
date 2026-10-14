/* Cleaned retail CFieldBG (SH2US_FIELD.BIN 0x0051e560..). Handle {Impl *impl; CSTGDB *sdb;}, Impl = 0xc0 bytes (JP 0x1d4). */
#include "_types_retail.h"
#define BG(i, t, o) RF(t, o, (i))

/* US 0x0051e640 CFieldBG::Create(CSTGDB *db, int arg) */
int CFieldBG_Create(CFieldBG *bg, CSTGDB *db, int arg) {
    LayerMan_Init();                                              /* 0x003f5420 */
    if (!bg->impl) bg->impl = new(0xc0);
    memset(bg->impl, 0, 0xc0);  BG(bg->impl, s32, 0x74) = -1;     /* exlight id */
    bg->sdb = db;  BG(bg->impl, s16, 0xb2) = arg;
    if ((h = CSTGDB_Find(db, 'FIELD   '))) {
        BG(bg->impl, u8, 0xb0) = (BG(bg->impl, u8, 0xb0) & ~2) | ((*(u16 *)((u8 *)h + 0x12) & 1) << 1);
        BG(bg->impl, u8, 0xba) = *(u16 *)((u8 *)h + 0x10);
        if (*((u8 *)h + 0x14)) LayerMan_LoadLayer(LayerProg1 /*0x00613db0*/);
        ExpansionTexture_changeLayer(LayerMan_GetLayer(7)); }
    if ((h = CSTGDB_Find(db, 'MODEL   '))) {                       /* 0x40 byte records: name[16], kind(+0x10), flags(+0x11), blob(+0x14), target(+0x1c), pos(+0x20), rot(+0x30) */
        int n = CSTGDB_GetDataNum(db, h); u8 *rec = CSTGDB_GetDataAddr(db, h);
        if (!n) return 0;
        count motions (kind 3) -> BG(impl, s16, 0xb6) and allocate the 8-byte link table at +0x70; memset(+0x7c, 0xff, 0x14);
        for each record: kind 0/1/2 -> CFieldModel_ctor(new(0x340)); models[impl.count++] = m; m.flags92.0 = (rec.flags & 4) != 0 (ExModel);
                                     CFieldModel_SetModel(m, blob, kind == 1 ? 0x82 : kind == 0 ? 0x81 : 0x80); SetPos(m, rec.pos, 0); SetDir(m, rec.rot, 0, 3); m.flags90 |= 3;
                         kind 3 -> if (target model has an ExModel and CreateMotion ok) link into the per-model list (u16 head at impl+0x7c+2*model) with the animation name;
    }
    if (BG(bg->impl, s16, 0xb4)) CFieldBG_GetShadowCtrl(bg, 1);
    BG(bg->impl, void *, 0x68) = CBgElement_ctor(new(0x288)); CBgElement_Create(BG(bg->impl, void *, 0x68), db->data /*+0x18*/, (BG(bg->impl, u16, 0xb2) & 0xf) != 0); CBgElement_Init(...);
    BG(bg->impl, float, 0x90) = BG(bg->impl, float, 0xa0) = 10.0f;  BG(bg->impl, float, 0x94) = BG(bg->impl, float, 0xa4) = 16777000.0f;     /* fog defaults */
    if ((h = CSTGDB_Find(db, 'FOG     '))) { f = CSTGDB_GetDataAddr(db, h); near=f[0]; far=f[1]; color=f[2]; copied to +0x90..0x98 and +0xa0..0xa8 }
    BG(bg->impl, u32, 0x9c) = BG(bg->impl, u32, 0xac) = 0;                                                                                  /* background colour */
    if ((h = CSTGDB_Find(db, 'BGCOLOR '))) BG(bg->impl, u32, 0x9c) = BG(bg->impl, u32, 0xac) = *(u32 *)CSTGDB_GetDataAddr(db, h);          /* retail data: 49 maps */
    if ((h = CSTGDB_Find(db, 'MIRROR  '))) { BG(bg->impl, void *, 0x6c) = (u8 *)h + 0x20; BG(bg->impl, s16, 0xb8) = *(u32 *)((u8 *)h + 8); } /* 0x30 byte records: 3 corners; 23 maps */
    return 1;
}

/* US 0x0051f850 CFieldBG::Dsp() */
void CFieldBG_Dsp(CFieldBG *bg) {
    Impl *i = bg->impl; if (!i || (BG(i, u8, 0xb0) & 1)) return;
    BG(i, u8, 0xb0) |= 1;  g_bgDspCount++;
    GsxCamera *cam = g_pGsxCamera;
    cam->bgcolor = BG(i, u32, 0x9c);                                   /* +0x180: clear colour from BGCOLOR */
    cam->fog_near = BG(i, float, 0x90); cam->fog_far = BG(i, float, 0x94);
    cam->fog_scale = 256.0f / (cam->fog_far - cam->fog_near); cam->fog_max = 255.0f;
    cam->fog_rgba = BG(i, u32, 0x98);                                  /* bytes at +0x388..0x38b */
    ShadowControl *sc = CFieldBG_GetShadowCtrl(bg, 1);
    for (int k = 0; k < BG(i, s16, 0xb4); k++) { CFieldModel *m = BG(i, CFieldModel *, 0x40 + 4 * k);
        switch (m->kind /* +0xa8 */) { case 2: DispModel(m, LayerMan_GetLayer(0), LayerMan_GetLayer(1), 0); break;
                                       case 0: DispModel(m, LayerMan_GetLayer(8), LayerMan_GetLayer(9), 0); break;
                                       case 1: ShadowControl_setRecive(sc, m->model); DispModel(m, LayerMan_GetLayer(2), LayerMan_GetLayer((BG(i, u8, 0xb0) & 2) ? 6 : 5), 0); break; } }
    if (sc && !World_HasOT(0x45a200, sc)) World_AddOT(0x45a200, LayerMan_GetLayer((BG(i, u8, 0xb0) & 2) ? 5 : 6), sc);
    CBgElement_Dsp(BG(i, void *, 0x68));
    if (BG(i, u8, 0xb0) & 0xc) CFieldBG_RecreateExLight(bg);
}
