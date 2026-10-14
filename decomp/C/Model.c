/* Model — Shadow Hearts: Covenant (JP demo SLPM_602.19), section C.
 * Cleaned from Ghidra output.  Layout offsets are those observed in the decompilation; see notes/C/Model.md.
 * Types used below are the Ghidra structs created for this section (Model, Frame, Atomic, ...). */

#include "sh2_types.h"

/* JP: 0x0023d9d0 __ct__5ModelFv   (size >= 0x4a8, derives from VIF1Prim + DelayDeleteObject) */
Model *Model::Model(Model *this)
{
    VIF1Prim::VIF1Prim(this);
    this->field14 = 0;  this->field18 = 0;
    this->vtbl_delete = &__vt__17DelayDeleteObject;   /* +0x1c */
    this->vtbl = &__vt__5Model;                       /* +0x10 */
    this->modelList.prev = this->modelList.next = 0;  /* CList at +0x20 */
    LevelsModel::LevelsModel[3](&this->levels);       /* +0x6c, 3 x 0x28 */
    /* +0xf0.. matrices init to identity, +0x280 ambient = (128,128,128,0x80) x2, +0x2a0 = (-1,-1,-1,0) */
    this->frames = 0; this->motionList = 0; this->atomics = 0; this->textures = 0; this->texAnims = 0;
    this->dynamics = 0; this->blendShapeCtl = 0; this->frameWeight = 0; this->centers = 0;
    this->flags484 &= ~7;
}

/* JP: 0x0023e710 create__5ModelFPUc — build the runtime object graph from an in-memory "SSH1.01a" image */
bool Model::create(Model *this, u8 *file)
{
    this->file = file;
    if (memcmp(file, "SSH1.01a", 8) != 0)                       /* @0x3fe658 */
        return false;

    /* ---- frames */
    this->frhd = file + *(u32 *)(file + 0x10);
    u8 *rec = this->frhd + 0x10;
    int nTotal = *(u16 *)(this->frhd + 4) + *(u16 *)(this->frhd + 6);   /* file frames + runtime extra frames */
    this->frames = __construct_new_array(new[nTotal * 0x1f0 + 0x10], Frame::Frame, Frame::~Frame, 0x1f0, nTotal);
    for (int i = 0; i < *(u16 *)(this->frhd + 4); i++) {
        Frame::Cleate(&this->frames[i], rec, this->frames);      /* rec += 0x40 */
        rec += 0x40;
        this->frames[i].flags = (this->frames[i].flags & 0xfc03) | (*(u8 *)(this->frhd + 4) << 2);
        /* NB: only the low byte of the frame count is stored, bits 2..9 of Frame.flags */
    }

    /* ---- motions embedded after the frame table ("SQHD"), then INTER_A / INTER_B blend motions */
    Model::createInterMotion(this);
    Model::createMotion(this, rec);                              /* returns 0 if rec is not "SQHD" */

    /* ---- atomics */
    this->athd = file + *(u32 *)(file + 0x0c);
    u8 *p = this->athd + 0x10;
    u16 nAtomics = *(u16 *)(this->athd + 4);
    if (nAtomics) {
        this->atomics = new Atomic *[nAtomics];
        for (int i = 0; i < nAtomics; i++) {
            Atomic *a = (*this->vtbl->setAtomic)(this, file, p);        /* vtbl+0x3c : Model::setAtomic */
            this->atomics[i] = a;
            p = a->vtbl->Cleate(a, p, this->atomics, this);             /* vtbl+0x10 -> returns next header */
            p = a->vtbl->initPacket(a, this->frames, p);                /* vtbl+0x14 -> end of packet table */
            if (!(a->hdr->fxFlags /*0x14*/ & 0x40)) a->shadowFlag /*+0x2b2*/ = 1;
        }
        this->bbhd = p;                  /* +0x60 */
        this->bboxTable = p + 0x10;      /* +0xe4 */
    }

    /* ---- textures */
    if (*(i32 *)(file + 0x18) != -1) {
        this->txhd = file + *(i32 *)(file + 0x18);
        u16 nTex = *(u16 *)(this->txhd + 4);
        this->textures = new Texture[nTex];            /* 0x4c each */
        u8 *t = this->txhd + 0x10;
        for (int i = 0; i < nTex; i++) {
            if (t[0x1f] & 4)  { t = Texture::CreateData(&this->textures[i], t, 1, 0x2a00, 0);
                                Texture::changeGSAlpha(&this->textures[i], 0, 2, 0, 1, 0); }
            else                t = Texture::CreateData(&this->textures[i], t, 0, 0, i);
        }
    }

    /* ---- texture animation */
    if (*(u32 *)(file + 0x24)) {
        this->txah = file + *(u32 *)(file + 0x24);
        u16 n = *(u16 *)(this->txah + 4);
        this->texAnims = new TextureAnim[n];           /* 0x10 each */
        u8 *q = this->txah + 0x10;
        for (int i = 0; i < n; i++) q = TextureAnim::CreateData(&this->texAnims[i], q, this->textures);
    }

    /* ---- blend shapes */
    if (*(u32 *)(file + 0x20)) {
        this->blendShapeCtl = new BlendShapeControl;   /* 0xc */
        if (!BlendShapeControl::create(this->blendShapeCtl, file + *(u32 *)(file + 0x20), this)) return false;
    }

    /* ---- bounding spheres: average of the 8 box corners per BBHD entry, radius = |corner0 - centre| */
    if (this->atomics && !this->centers) {
        int n = *(u32 *)(this->bbhd + 4) + *(u32 *)(this->bbhd + 8);
        this->centers  = new FVector[n];               /* +0x458 */
        this->centers2 = new FVector[n];               /* +0x45c */
        for (u32 i = 1; i < n; i++) {
            FVector c = {0,0,0,0};
            for (int j = 0; j < 8; j++) c.xyz += ((FVector *)(this->bboxTable + i * 0x110 + 0x10))[j].xyz;
            c.xyz /= 8.0f;
            this->centers[i] = c;
            FVector d = corner0(i) - c;
            this->centers[i].w = Length(d);
        }
    }

    /* ---- EXHD extension chain (tags compared as little-endian u32) */
    if (*(u32 *)(file + 0x28)) {
        for (u32 *e = (u32 *)(file + *(u32 *)(file + 0x28)); e[0] == 'DHXE'; e += e[3] * 4) {
            switch (e[1]) {
            case 'LBAL': this->labels = (u8 *)(e + 4); break;                           /* "LABL" */
            case 'HSHD': if (this->dynamics && this->dynamics->circles)                  /* "DHSH" */
                             BoundingCircle::Create(this->dynamics->circles, this, e); break;
            case 'HRFW': this->frameWeight = new FrameWeight;                            /* "WFRH" */
                         FrameWeight::Create(this->frameWeight, e, this->frames, *(u16 *)(this->frhd + 4)); break;
            case 'HNYD': Frame::calcMatrix(this->frames, 0, m_Env__VIF1Prim & 1);        /* "DYNH" */
                         Frame::calcMatrix(this->frames, 0, (m_Env__VIF1Prim & 1) ^ 1);
                         this->dynamics = new DynamicsControl;
                         DynamicsControl::Create(this->dynamics, e, this);
                         DynamicsControl::Init(this->dynamics); break;
            }
        }
    }
    this->field4a4 = 0;
    LevelsModel::setData(&this->levels[0], this);
    this->levels[0].enabled /* +0x6d */ = 1;
    this->buf_e8 = new u8[16000]; this->buf_ec = new u8[16000];   /* 1000 x FVector scratch each, zeroed */
    this->rootFrame = this->frames ? (Frame::searchFrame(this->frames, "WAIST0") ?: this->frames) : 0;
    this->bboxResults = new BBoxResult[ ((u32 *)this->bbhd)[1] ];   /* 0x80 each */
    return true;
}

/* JP: 0x0023e510 setAtomic__5ModelFP16_ModelFileHeaderP20_ModelTriangleHeader */
Atomic *Model::setAtomic(Model *this, _ModelFileHeader *fh, _ModelTriangleHeader *th)
{
    switch ((th->fxFlags /*+0x15*/ & 0xf) >> 1) {
    case 7: return new WaterAtomicP1;     /* 0x3b0 */
    case 6: return new BAtomic;           /* 0x3e0 */
    }
    u8 t = th->typeFlags;                 /* +0x14 */
    if ((t & 0x80) || (t & 0xf) == 0) {
        if ((t & 0xf) == 0) return (fh->flagsByte10 & 3) ? new SkinAtomicPack2 : NULL;   /* 0x380 */
        return new SkinAtomicPack2NL;     /* 0x380 */
    }
    if ((t & 0xf) == 1) return (fh->flagsByte10 & 3) ? ((fh->flagsByte10 & 4) ? new Pack2Atomic /*0x380*/ : new Pack1Atomic /*0x390*/) : NULL;
    if ((t & 0xf) == 2) return (fh->flagsByte10 & 3) ? ((fh->flagsByte10 & 4) ? new PLP2Atomic  : new PLP1Atomic) : NULL;
    return NULL;
}

/* JP: 0x0023f170 createMotion__5ModelFPUc — append a motion ("SQHD") to Model.motionList */
u8 *Model::createMotion(Model *this, u8 *sqhd)
{
    if (*(u32 *)sqhd != 'DHQS') return 0;
    SequenceControl *sc = new SequenceControl;
    SequenceControl::Cleate(sc, sqhd);
    if (!this->motionList) this->motionList = sc;
    else CList::InsertAfter(CList::GetTail(this->motionList), sc);
    return sc->hdr + 4;                   /* NB: returns hdr+4 (name field), not the end of the motion */
}

/* JP: 0x0023f080 createInterMotion__5ModelFv — the two built-in blend motions INTER_A / INTER_B */
void Model::createInterMotion(Model *this)
{
    InterSequenceControl *a = new InterSequenceControl(this->frames, *(u16 *)(this->frhd + 4), "INTER_A");
    if (!this->motionList) this->motionList = a; else CList::InsertAfter(CList::GetTail(this->motionList), a);
    a->hdr->flags14 = (a->hdr->flags14 & ~2) | 2;                  /* mark as main motion */
    InterSequenceControl *b = new InterSequenceControl(this->frames, *(u16 *)(this->frhd + 4), "INTER_B");
    CList::InsertAfter(CList::GetTail(this->motionList), b);
}

/* JP: 0x0023ffb0 setMotion__5ModelFPCcf */
bool Model::setMotion(Model *this, const char *name, float startTime)
{
    SequenceControl *sc;
    if (!this->motionList || !(sc = SequenceControl::SeachSequenceControl(this->motionList, name)))
        return false;
    if (sc->hdr->flags14 & 2) {                                     /* full-body motion */
        if (this->dynamics && (!this->curMotion || strncmp(this->curMotion->hdr + 4, "<DYNA-reset-name>", 12) != 0))
            Model::DynaFunction(this, 1);
        this->curMotion = sc;
        Frame::setSequence(this->frames, this->curMotion, 0);
        SequenceControl::setCTime(sc, startTime);
        this->rootOffset /* +0x430 */ = (FVector){0, 0, 0, 1.0f};
        this->field444 = 0;
        this->field480 = 0;
        return true;
    }
    return Model::setSubMotion(this, name);
}

/* JP: 0x0023e100 Initialize__5ModelFv — static init of shared textures and ShadowControl */
void Model::Initialize(void)
{
    ExpansionTexture::changeLayer(3);
    char path[256]; SysTool::SetPathname(path, "<model common texture bin>");   /* @0x3fe620 */
    FIOHND *h; do h = FileIOLib::open(ourFio, path, 1, 1); while (!h);
    while (FileIOLib::getStatus(ourFio, h)) ;
    while (FileIOLib::read(ourFio, h, 0, 0) != 1) ;
    while (FileIOLib::getStatus(ourFio, h)) ;
    gTextureColtrol::CreateTexture(m_pOur, "<name>", FileIOLib::getBuffer(ourFio, h));
    FileIOLib::close(ourFio, h);
    changeGSAlpha(gTextureColtrol::findTexture(m_pOur, "<name2>"), 0, 2, 0, 1, 0);
    /* three dummy render-target gTextures: 128x128 and two 512x448 (screen copy / shadow buffers) */
    ShadowControl::Init(m_pOur__13ShadowControl);
}
