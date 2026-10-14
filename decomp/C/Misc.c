/* ModelEffManager / LipsHandler / CPath / PolGroup / PolData / BlendShape — cleaned excerpts (see notes/C/Misc.md) */

/* ---- ModelEffManager (JP 0x003daee0): attach a per-monster polygon effect to a bone of `model`.
 * kind -> effect object (all CBBPolygon-derived, vtable at +0x7e4, model at +0x7d0, bone Frame* at +0x7d4):
 *   1 CBRingSoulOT + CBRingSoul(0x32 polys)   bone "EX01"
 *   2 4 x CBCatherine(0x23)                   bones "M_B0_A".."M_B0_D"
 *   3 CBJack(0x50)  4 CBJill(0x50)            bone "WAIST0"
 *   5 CBM412OT + CBM412(0x32)                 "WAIST0"/"TAIL4"
 *   6 CBM413OT + CBM413(0x32)
 *   7 CBM524 + M524_2(100, 2nd pkb entry)     "TAIL4"
 *   8 CBM477(200)                             "HEAD0"      9 CBGBat(0x3c)  "WAIST0"
 */
bool ModelEffManager::createMF(int kind, Model *model, int slot, void *res)
{
    if (!sys) { sys = new ModelEffManager /*CPolObj, 0x20*/; CPoller::Entry(&app->pollers, sys, 0x80, 0); m_SelfCreate = 1; }
    CBBPolygon *e = newEffect(kind, res);
    e->model = model; e->bone = Frame::searchFrame(model->frames, boneName(kind));
    e->vtbl->init(e); e->vtbl->start(e, slot);
    CList::InsertAfter(&sys->list /*+0x18*/, e);
    return true;
}
int ModelEffManager::Polling(void) { for (e : sys->list) e->vtbl->update(e, m_Time); return 0; }  /* JP 0x003db920 */
/* Dip/Clr/Reset/changeAlpha/deleteMF: iterate sys->list, act on entries whose +0x7d0 == model; deleteMF frees the manager when empty */

/* ---- LipsHandler (JP 0x0038d3e0) */
struct LipsChannel { int time, duration; float value, from, to; Frame *frame; };      /* 0x18 bytes */
void LipsHandler::calcLips(LipsHandler *this, float dt)
{
    for (int i = 0; i < this->nChannels /*+0x36*/; i++) {
        LipsChannel *c = &this->channels[i];
        if (c->time < c->duration) {
            c->time += dt * 60; if (c->time > c->duration) c->time = c->duration;
            c->value = c->time / c->duration * c->to + (1 - c->time / c->duration) * c->from;
            Matrix m = Identity;
            switch ((this->desc[i].byte1c & 0x1f) >> 3) { case 0: sceVu0RotMatrixX(c->value, &m, &m); break;
                                                          case 1: sceVu0RotMatrixY(...); break; case 2: sceVu0RotMatrixZ(...); break; }
            if (c->frame) { c->frame->extraMat = m; Frame::myMatrixUpdate(c->frame); }
        }
    }
}

/* ---- CPath (JP 0x0032aae0): ring of 0x30-byte points (pos, dir, length, age), 10 colour keys, 10 ST keys */
void CPath::AddPath(CPath *this, FVector *pos, FVector *dir)       /* JP 0x0032b260 */
{
    if (this->count < this->capacity) this->count++;
    memmove(this->points + 1, this->points, (this->capacity - 1) * 0x30);
    this->points[0].pos = *pos; this->points[0].dir = *dir; this->points[0].age = 0;
    this->points[0].length = this->count < 2 ? 0 : Length(this->points[0].pos - this->points[1].pos);
}
void CPath::AddTime(CPath *this, float dt) { for (int i = 0; i < this->count; i++) this->points[i].age += dt; }   /* 0x0032bd50 */

/* ---- PolGroup (JP 0x00315aa0) */
PolGroup::PolGroup(PolGroup *this) { CList::CList(this); this->vtbl = &__vt__8PolGroup;
    Matrix::Matrix(&this->local /*+0x40*/); Matrix::Matrix(&this->place /*+0x80*/); Matrix::Matrix(&this->view /*+0xc0*/);
    this->buf[0] = this->buf[1] = this->tex = this->first = 0;
    this->reg_test = 0x70000; this->reg_alpha = 0x44; this->reg_clamp = 5; }
void PolGroup::CreateDrawPacket(PolGroup *this) {     /* JP 0x00315d90: two 200-qword DMA buffers */
    this->buf[0] = new FVector[200]; this->buf[1] = new FVector[200]; memset(this->buf[0], 0, 0xc80); memset(this->buf[1], 0, 0xc80); }
void PolGroup::AddData(PolGroup *this, PolData *d) { d->group = this; if (!this->first) this->first = d; else CList::Add(this->first, d); }  /* 0x00316610 */
/* PolData::SetCenter(x,y,z): matrix(+0xa0).pos = (x,y,z,1); SetVertex(x,y): vec(+0x10).xy; SetSt(i,u,v): vec(+0x20+i*0x10).xy;
 * SetColor(i,r,g,b,a): vec(+0x60+i*0x10); SetRot(rx,ry,rz): RotMatrix -> matrix(+0xa0); DelayDelete(): byte(+8) = (byte & ~7) | 5 */

/* ---- BlendShape (JP 0x0024b700) */
void BlendShape::changePercent(BlendShape *this, float f) { this->percent /*+0x44*/ = f > 1.0f ? 1.0f : f; this->dirty /*+0x58*/ = 1; }
void BlendShape::changeSlider(BlendShape *this, int i, float f) { this->sliders[i].value /*i*0x14+8+0xc*/ = f * this->sliderScale /*+0x50*/; this->dirty = 1; }
bool BlendShape::changeShape(BlendShape *this, int shape)   /* JP 0x0024b7c0-ish: start a transition to target `shape` */
{
    if (shape >= this->hdr->nTargets /* u16 +0xe */) return false;
    memcpy(this->work[2], this->work[(m_Env & 1) ^ 1], this->bytes /*+0x2c*/);
    this->cur = shape;
    if (this->prev == this->cur) { this->blend += this->w * this->percent; this->w = 1 - this->blend; }
    else { this->blend += this->w * this->percent; this->prev = this->cur; this->blend = 0; this->w = 1; }
    BlendShape::changePercent(this, 0);
    return true;
}
