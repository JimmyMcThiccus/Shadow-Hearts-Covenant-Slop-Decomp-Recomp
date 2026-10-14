/* fp_retail.c -- cleaned C for the retail-new Fp* effect classes of SLUS_210.41 (0x2c84e0-0x2f3000)
 * and the retail changes of the FpPrim base class.  Section I, pass N5.
 *
 * Source: Ghidra decompiles of the functions named in notes/I/fp_retail.md.  Types are real, field names are
 * ours.  "// US 0x......" gives the main-exe address of the function a block was cleaned from.  Everything
 * here is *base-class level* behaviour (dispatch, composition, the per-frame simulations that could be
 * read with confidence); the long data tables (e.g. the 67 hard-coded mote placements of
 * FpRetailMote207::CreateObjects, 0x84f0 bytes) are not reproduced.
 * Not compilable on its own: PS2 GS packet code (SetPacket) and VU0 inline math are summarised.
 */
#include <stdint.h>

typedef struct { float x, y, z, w; } FVector;

/* ------------------------------------------------------------------------------------------ */
/* Base classes (layout from notes/D/Fp.md, retail deltas marked RETAIL)                      */
/* ------------------------------------------------------------------------------------------ */

typedef struct _FpData {            /* 0xf0 bytes, array at FpObject+0x1fc, count at +0x1f8       */
    float   period;                 /* +0x00 lifetime in frames (999.0 = "alive" marker in Mote)  */
    float   t;                      /* +0x04 local time                                           */
    float   _pad08[2];
    FVector vel;                    /* +0x10                                                      */
    FVector wind;                   /* +0x20                                                      */
    FVector pos;                    /* +0x30                                                      */
    FVector size;                   /* +0x40 (x,y = half extents, w = alpha for some classes)     */
    FVector scale;                  /* +0x50                                                      */
    FVector rot;                    /* +0x60                                                      */
    FVector v[4];                   /* +0x70..0xaf corner vertices (screen space for Rain)        */
    float   uv[12];                 /* +0xb0..                                                    */
    uint32_t flags;                 /* +0xe0 bit0 alive                                           */
    float   _pad[3];
} _FpData;

struct FpPrim;
struct FpPrimVtbl {                 /* RETAIL layout (JP: 18 slots, retail: 21)                   */
    void (*dtor)(struct FpPrim *);                  /* 0                                          */
    void *(*getPacket)(struct FpPrim *);            /* 1                                          */
    void *res2, *res3;                              /* 2,3                                        */
    void (*dtor_thunk20)(void);                     /* 4 @20@__dt__                               */
    void (*DelayDelete)(struct FpPrim *);           /* 5                                          */
    void (*TimeCall)(struct FpPrim *);              /* 6  PutiPrim                                */
    int  (*OnDelete)(struct FpPrim *);              /* 7                                          */
    void (*SetState)(struct FpPrim *, int);         /* 8                                          */
    void (*setLayer)(struct FpPrim *, int);         /* 9                                          */
    void (*setZtest)(struct FpPrim *, int);         /* 10                                         */
    void (*SetAlphaPower)(struct FpPrim *, float target, unsigned ms);  /* 11                     */
    void (*SetDrawFlag)(struct FpPrim *, int);      /* 12                                         */
    void (*SetColor1)(struct FpPrim *, uint8_t, uint8_t, uint8_t, uint8_t);   /* 13               */
    void (*SetColor2)(struct FpPrim *, uint8_t, uint8_t, uint8_t, uint8_t);   /* 14               */
    void (*SetColor3)(struct FpPrim *, uint8_t, uint8_t, uint8_t, uint8_t);   /* 15               */
    void (*SetPos1)(struct FpPrim *, FVector, int); /* 16                                         */
    int  (*GetMode)(struct FpPrim *);               /* 17 RETAIL, US 0x2a6370, default returns 0  */
    void (*ResetMode)(struct FpPrim *);             /* 18 RETAIL, US 0x2a5ca0, default empty      */
    void (*SetMode)(struct FpPrim *, int mode);     /* 19 RETAIL, US 0x2a5cb0                     */
    void (*CreateStart)(struct FpPrim *, float);    /* 20 (JP slot 17)                            */
};

typedef struct FpPrim {
    /* PutiPrim/VIF1Prim base ... */
    const struct FpPrimVtbl *vt;    /* +0x10 (second vtable, DelayDeleteObject, at +0x1c)         */
    void *objList;                  /* +0x28 PutiObject list                                      */
    int   layer;                    /* +0x54                                                      */
    uint8_t bLoop, f59, pad5a;      /* +0x58 loop flag / +0x59 / +0x5a                            */
    float alphaPower;               /* +0x5c                                                      */
    int   mode;                     /* +0x6c RETAIL: set by SetMode, read by the Trail prims      */
    int   variant;                  /* +0x70 (Rain206/Drift208/Trail211M3: param[0]; Lenz6: object*) */
} FpPrim;

/* US 0x2a5cb0  FpPrim::SetMode(int) -- retail-new virtual 19 */
void FpPrim_SetMode(FpPrim *p, int mode)
{
    p->mode = mode;
    switch (mode) {
    case 0x1f: p->vt->SetAlphaPower(p, 0.0f, 0);   p->vt->SetAlphaPower(p, 1.0f, 500);  break; /* fade in 0.5 s  */
    case 0x1e:                                      p->vt->SetAlphaPower(p, 0.0f, 500);  break; /* fade out 0.5 s */
    case 0x15: p->vt->SetAlphaPower(p, 0.0f, 0);   p->vt->SetAlphaPower(p, 1.0f, 2000); break; /* fade in 2 s    */
    case 0x14:                                      p->vt->SetAlphaPower(p, 0.0f, 2000); break;
    case 0x0b: p->vt->SetAlphaPower(p, 0.0f, 0);   p->vt->SetAlphaPower(p, 1.0f, 1000); break; /* fade in 1 s    */
    case 0x0a:                                      p->vt->SetAlphaPower(p, 0.0f, 1000); break;
    default: break;
    }
}

/* US 0x2a63f0  FpPrim::SetRegTest(u64) (VEC fefSetZTest): propagate the GS TEST register to every object */
void FpPrim_SetRegTest(FpPrim *p, uint64_t test)
{
    for (void **o = p->objList; o; o = (void **)*o) /* PutiObject list: next at +0 */
        PutiObject_SetRegTest(o, test);
}

/* ------------------------------------------------------------------------------------------ */
/* CreateFpEffect (US 0x2a65c0) -- retail switch.  JP had 1-5, 200-204.                        */
/* ------------------------------------------------------------------------------------------ */
FpPrim *CreateFpEffect(int type, float *param)
{
    FpPrim *p = 0;
    switch (type) {
    case 1:   p = new_FpTorch (0xc0);  FpTorch_Create (p, param);  break;
    case 2:   p = new_FpCandle(0xc0);  FpCandle_Create(p, param);  break;
    case 3:   p = new_FpFlare (0x80);  FpFlare_Create (p, param);  break;   /* JP 0x70 */
    case 4:   p = new_FpSmoke (0x100); FpSmoke_Create (p, param);  break;
    case 5:   p = new_FpFog   (0xd0);  FpFog_Create   (p, param);  break;
    case 6:   p = new FpRetailLenz6 (0x78);  FpRetailLenz6_Create(p, param);            break;  /* NEW */
    case 200: p = new_FpLenzFlare(0xe0); FpLenzFlare_Create(p, param); break;           /* JP 0xd0 */
    case 201: p = new_FpFunsui(0x100); FpFunsui_Create(p, param);  break;
    case 202: p = new_FpBlackHole(0x110); FpBlackHole_Create(p, param); break;          /* JP 0xc0 */
    case 203: p = new_FpFogMCES(0x70); FpFogMCES_Create(p, param); break;
    case 204: p = new_FpTaki(0x78);    FpTaki_Create(p, param);    break;
    case 206: p = new FpRetailRain206 (0xb0);  p->variant = (int)param[0]; FpRetailRain206_CreateObjects(p); break;   /* NEW */
    case 207: p = new FpRetailMote207 (0x70);  FpRetailMote207_CreateObjects(p, (int)param[0]);                       break;   /* NEW */
    case 208: p = new FpRetailDrift208(0x78);  p->variant = (int)param[0]; FpRetailDrift208_CreateObjects(p);        break;   /* NEW */
    case 209: p = new FpRetailStorm209(0xe0);  FpPrim_InitFpFlag(param[0], p); FpRetailStorm209_CreateObjects(p);     break;   /* NEW */
    case 210: break;                                                                     /* accepted, creates nothing (BBG 100/101) */
    case 211: switch ((int)param[0]) {                                                  /* NEW: three trail emitters */
              case 3: p = new FpRetailTrail211M3(0xb0);  p->variant = 3; FpRetailTrail211M3_CreateObjects(p); break;
              case 1: p = new FpRetailTrail211M1(0x130); FpRetailTrail211M1_CreateObjects(p);                 break;
              case 0: p = new FpRetailTrail211M0(0x130); FpRetailTrail211M0_CreateObjects(p);                 break;
              } break;
    case 212: p = new FpRetail212(0xa0);  FpRetail212_Create(p, param); break;                                          /* NEW */
    case 213: p = new FpRetail213(0x100); FpRetail213_Create(p, param); break;                                          /* NEW */
    }
    return p;
}

/* US 0x2c3e10  FpTaki::Create(int mode) -- retail adds the third layer (FpObjectRetailTaki3)  */
void FpTaki_Create(FpTaki *t, int mode)
{
    t->mode = mode;
    SetWhiteTex(tex = commonTex + 0x8c); PutiPrim_SetTexture(t, tex, 0);
    if (!t->bLoop) t->flags24 |= 1;
    int n1 = mode ? 0x96 : 200;                      /* FpObjectTaki  : main streams     */
    add(t, new FpObjectTaki  (0x2c0, n1 * 12 + 0x14))->Init(n1, t->bLoop);
    int n2 = (mapActive || mode) ? 0x32 : 100;      /* FpObjectTaki2 : second layer     */
    add(t, new FpObjectTaki2 (0x2c0, n2 * 12 + 0x14))->Init(n2, t->bLoop);
    FpObjectRetailTaki3 *s = new FpObjectRetailTaki3(0x2c0, 0x26c);   /* NEW: 50 sprites, spray layer */
    add(t, s)->Init(0x32, t->bLoop);
    s->flags14 &= ~1;                                /* not billboarded */
    t->vt->SetState(t, mode ? 6 : 3);
    PutiManager_AddPrim(ourManager, t->layer, t);
}

/* ------------------------------------------------------------------------------------------ */
/* FpRetailRain206 -- screen-space rain (effect type 206)                                      */
/* ------------------------------------------------------------------------------------------ */
/* US 0x2c99b0 (CreateObjects, condensed): variant 1 = heavy rain (1000 streaks) else 500;
 * heavy adds a 20-particle splash object and three ScreenTint prims (white flash layers).     */
void FpRetailRain206_CreateObjects(FpPrim *p)
{
    tex = commonTex + 0x104; SetWhiteTex(tex); PutiPrim_SetTexture(p, tex, 0);
    int n = (p->variant == 1) ? 1000 : 500;
    FpObjectRetailRain206 *rain = new FpObjectRetailRain206(0x250, n * 12 + 0x14);
    PutiPrim_AddObject(p, rain);
    if (p->variant == 1) rain->vt->Setup2(rain);                    /* 0x2ca270 */
    rain->vt->Init(rain, n, p->bLoop);
    if (p->variant == 1) {
        FpObjectRetailRain206C *splash = new FpObjectRetailRain206C(0x220, 0x14);
        PutiPrim_AddObject(p, splash);
        splash->vt->Init(splash, 0, p->bLoop);
        /* three FpRetailScreenTint layers stored at p+0x74/+0x78/+0x7c */
        p->tint[0] = FpRetailScreenTint_New(2, (FVector){ 118.0f, 118.0f, 128.0f, 20.0f });
        p->tint[1] = FpRetailScreenTint_New(2, (FVector){ 0, 0, 0, 56.0f }); SetRegAlpha(p->tint[1], 0x44);
        p->tint[2] = FpRetailScreenTint_New(9, (FVector){ 0, 0, 0, 20.0f }); SetRegAlpha(p->tint[2], 0x44);
    } else {
        FpObjectRetailRain206B *b = new FpObjectRetailRain206B(0x250, n * 12 + 0x14);   /* light rain  */
        /* ... */
    }
    PutiManager_AddPrim(ourManager, p->layer, p);
}

/* US 0x2ca760  FpObjectRetailRain206::CreateFpData -- spawn one streak above the screen */
void Rain206_CreateFpData(FpObjectRetailRain206 *o, _FpData *d)
{
    d->t = 0;
    float k = 1.0f - 0.5f * rand01();
    d->size.y = o->baseLen * k;                              /* +0x44 = *(o+0x114) * [0.5,1] */
    float depth = 15.0f * rand01();
    float s = 1.0f - (15.0f - depth) / 30.0f;                /* streak scale 0.5..1.0 */
    d->uv_alpha = o->alpha * s;                              /* +0xbc */
    d->scale.x = s;                                          /* +0x50 */
    d->vel = o->velTemplate;                                 /* o+0xa0 */
    d->vel.x *= -0.5f - 0.5f * rand01();                     /* slanted left */
    d->vel.y *=  0.5f + 0.5f * rand01();
    float y0 = -d->size.y - 448.0f * rand01();               /* start above the top edge */
    d->pos.y = y0;
    d->pos.x = (y0 * 2.0f * d->vel.x) / d->vel.y + 512.0f * rand01();
    d->pos.z = depth;  d->pos.w = 1.0f;
}

/* US 0x2cabc0  FpObjectRetailRain206::CalculateFunc (condensed) */
void Rain206_CalculateFunc(FpObjectRetailRain206 *o)
{
    FpPrim *p = o->prim;
    float dt = FpPrim_GetFrameSpeed(p);                      /* Gsx::m_syncCount * 0.5 */
    p->flashFlag = 0;
    if (p->variant == 1) Rain_StrobeLightning(o);            /* 0x2ca420 */
    else if (curMap) {
        unsigned mapNo = (unsigned)(curMap->f1c * curMap->u3e);
        /* thunder flashes on maps 6374..6378 and 6274..6278: ...8e8/8ea -> flag, 8e9/8e7 -> alpha power,
           8e6 -> two-vector Thunder::SetPos + alpha, same set at 0x1882-0x1886 */
        Rain_MapTriggers(p, mapNo);
        Rain206_UpdateGlow(p);                               /* 0x2c96e0: reads light slots kind 2 / 6 (0x448a30 table) */
    }
    for (int i = 0; i < o->count; ++i) {
        _FpData *d = &o->data[i];
        d->t += dt;
        if (d->pos.y + 448.0f < d->size.y) /* below the bottom edge */ o->vt->CreateFpData(o, d, i);
        else d->pos = vadd(d->pos, vmul(d->vel, dt));
        float w = d->size.x * d->scale.x, h = d->size.y * d->scale.x;
        float dx = (h * 2.0f * d->vel.x) / d->vel.y;           /* slant of the streak */
        d->v[0] = (FVector){1792.0f - w,      1824.0f - h, 0, 1};
        d->v[1] = (FVector){1792.0f - w + dx, 1824.0f + h, 0, 1};
        d->v[2] = (FVector){1792.0f + w,      1824.0f - h, 0, 1};
        d->v[3] = (FVector){1792.0f + w + dx, 1824.0f + h, 0, 1};
        for (int k = 0; k < 4; ++k) d->v[k] = vadd(d->v[k], d->pos);   /* GS coordinates, centre (1792,1824) */
    }
    o->vt->CalcFpVertex(o);
}

/* ------------------------------------------------------------------------------------------ */
/* FpRetailMote207 / FpObjectRetailMote207                                                      */
/* ------------------------------------------------------------------------------------------ */
/* US 0x2d8d20  CalculateFunc: random-walk motes; period==999 marks an "alive" mote            */
void Mote207_CalculateFunc(FpObjectRetailMote207 *o)
{
    float dt = FpPrim_GetFrameSpeed(o->prim);
    float rise = dt * 0.0001f;
    for (int i = 0; i < o->count; ++i) {
        _FpData *d = &o->data[i];
        d->t += dt;
        if (d->period == 999.0f) {
            d->vel.x += (0.5f - rand01()) * 0.02f;           /* jitter */
            d->vel.z += (0.5f - rand01()) * 0.02f;
            clamp_symmetric(&d->vel.x, o->maxVelX);          /* o+0xa0 */
            clamp_symmetric(&d->vel.z, o->maxVelZ);          /* o+0xa8 */
            d->vel.y += rise;                                 /* slowly accelerates upward */
            d->pos = vadd(d->pos, vmul(d->vel, dt));
            if (d->pos.y > o->ceilingY) { d->pos.y = o->ceilingY; d->period = 20.0f; }   /* start fading */
        } else if (d->period > 0.0f) d->period -= dt;
        else o->vt->CreateFpData(o, d, i);                   /* respawn */
    }
    o->vt->CalcFpVertex(o);
}

/* ------------------------------------------------------------------------------------------ */
/* FpObjectRetailDrift208 -- US 0x2dd020 (update of the B subtype)                              */
/* ------------------------------------------------------------------------------------------ */
void Drift208_Update(float dt, FpObjectRetailDrift208B *o)
{
    _FpData *d = o->data;
    float fadeIn = d->period * 0.1f, fadeOut = d->period * (o->subtype == 5 ? 0.5f : 0.9f);
    for (int i = 0; i < o->count; ++i, ++d) {
        d->t += dt;
        if (d->t > d->period) { o->vt->CreateFpData(o, d, i); d->size.z = 0; d->size.w = 0; continue; }
        float a = o->alphaMax;
        if (d->t < fadeIn)       a *= d->t / fadeIn;                       /* fade in over 10 %  */
        else if (d->t > fadeOut) a *= (d->period - d->t) / (d->period - fadeOut);   /* fade out */
        d->alpha = a;
        d->pos = vadd(d->pos, vmul(d->vel, dt));
        d->swayT += dt;
        if (d->swayT > 30.0f) { d->swayT = 0; d->swayDir = -d->swayDir; } /* reverse sway every 30 frames */
        if (d->swayDir > 0.0f) d->rotAcc += rand01() + 0.5f;
    }
}

/* ------------------------------------------------------------------------------------------ */
/* FpRetailScreenTint -- full-screen overlay (US 0x2d9a00 / 0x2d9be0 / 0x2d9de0)                */
/* ------------------------------------------------------------------------------------------ */
void ScreenTint_Create(FpPrim *p, int mode, FVector *rgba)
{
    p->bLoop = 0; p->flags24 |= 1;
    FpObjectRetailScreenTint *o = new FpObjectRetailScreenTint(0x210, 0x20);
    PutiPrim_AddObject(p, o);
    o->vt->Init(o, 1, p->bLoop);
    o->data[0].colour = *rgba;                               /* +0xb0: r,g,b,a(0..128) */
    p->vt->SetState(p, mode);
    PutiManager_AddPrim(ourManager, p->layer, p);
}
void ScreenTint_Init(FpObjectRetailScreenTint *o, int n, char zTestOff)
{
    o->count = o->count2 = n;
    o->data = alloc_array(_FpData, n);                       /* 0xf0 each, memset 0 */
    o->life = -1;
    o->flags14 = (o->flags14 & 0xe01f) | 0x1fe0;             /* priority 0xff */
    SetRegTest(o, zTestOff ? 0x33001 : 0x73001);
}
/* SetPacket: one GIF sprite covering the screen; alpha = clamp(data[0].a * o->fade * prim->alphaPower, 0, 128) */

/* ------------------------------------------------------------------------------------------ */
/* FpObjectRetailTrail -- ribbon (US 0x2e7840, head only)                                       */
/* ------------------------------------------------------------------------------------------ */
void Trail_CalculateFunc_head(FpObjectRetailTrail *o)
{
    for (int i = 19; i > 0; --i) {                          /* shift the 20-entry history */
        o->histPos[i]  = o->histPos[i - 1];                  /* +0x260 + i*0x10 */
        o->histCol[i]  = o->histCol[i - 1];                  /* +0x3a0 + i*0x10 */
    }
    o->age += FpPrim_GetFrameSpeed(o->prim);                 /* +0x21c */
    if (o->age > o->maxAge) {                                /* +0x218: respawn the head */
        o->age = 0;
        o->head = (FVector){ 0, 0, (0.5f - rand01()) * 0.01f, 1 };
        o->pos  = (FVector){ prim_range.x * (0.5f - rand01()) * 5.0f,
                             prim_range.y * (0.5f - rand01()) * 10.0f, 0, 1 };
        o->pos  = vadd(o->pos, prim_origin);                 /* prim+0x90 */
        UpdateBBox(o, o->pos, (FVector){ o->size * 1.5f, o->size * 4.5f, o->size * 6.0f });
    } else {
        /* head steps by a randomised velocity; prim->mode 1 or (mode 2 && z < -200) re-randomises */
    }
    /* ... per-variant steering lives in the derived CalculateFunc (Trail211M0/M1, Trail212, Trail213) */
}
