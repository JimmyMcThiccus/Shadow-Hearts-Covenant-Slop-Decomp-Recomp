/* DynamicsControl / Dynamics — hair/cloth chains from the DYNH extension block. JP 0x00252e60..0x00253cb4 */

/* JP: 0x00252e60 __ct__15DynamicsControlFv */
DynamicsControl *DynamicsControl::DynamicsControl(DynamicsControl *this) { this->enable /*+0xc*/ = 1; this->dt /*+0x10*/ = 0; return this; }

/* JP: 0x00252f00 Create__15DynamicsControlFPUcP5Model   blk = EXHD+DYNH block */
void DynamicsControl::Create(DynamicsControl *this, u8 *blk, Model *model)
{
    Frame *frames = model->frames;
    this->block = blk;                              /* +0x00 */
    u8 *p = blk + 0x10;
    this->circles = new BoundingCircle;             /* +0x08, 0x30 bytes */
    u16 n = *(u16 *)(blk + 10);                     /* chain count */
    this->chains = new Dynamics[n];                 /* +0x04, 0x30 bytes each */
    for (int i = 0; i < n; i++) {
        p = Dynamics::Create(&this->chains[i], p, frames);
        this->chains[i].circles /*+0x10*/ = this->circles;
        BRN_LinkList::setCollisionCallBack(this->chains[i].links /*+8*/, &BoundingCircle::CollisionFnc);
        BRN_LinkList::setCollisionUserData(this->chains[i].links, this->circles);
    }
}

/* JP: 0x00253340 Create__8DynamicsFPUcP5Frame  (chain header 0x10 + node_count * 0x30) */
u8 *Dynamics::Create(Dynamics *this, u8 *chain, Frame *frames)
{
    this->hdr = chain;  this->nodes = chain + 0x10;
    u16 nn = *(u16 *)(chain + 8), flags = *(u16 *)(chain + 0xa);
    this->links = new BRN_LinkList(nn - 1);                         /* 0x5b0 bytes */
    this->frames = new Frame *[nn];                                 /* +0xc */
    if (*(i16 *)(chain + 0xc))  this->links->gravity.y = (float)*(i16 *)(chain + 0xc) * 0.01f * 9.8f;
    if (*(u16 *)(chain + 0xe))  this->links->setAirResistance((float)*(u16 *)(chain + 0xe) * 0.01f);
    if (flags >> 6)             this->links->setDampingMultiplier((float)(flags >> 6) * 0.01f);
    for (int i = 0; i < nn; i++) {
        this->frames[i] = Frame::searchFrame(frames, this->nodes + i * 0x30);          /* node name */
        if (i) {
            FVector d = *(FVector *)(this->nodes + i * 0x30 + 0x20) - *(FVector *)(this->nodes + 0x20);
            FVector up = {0, 0, 0, 1.0f};
            BRN_LinkList::setLinkParams(this->nodes[i].links /*+0xc*/ , this->links, i - 1, d, up);
        }
    }
    if (flags & 8) BRN_LinkList::initBendingForce(this->links);
    return this->nodes + nn * 0x30;
}

/* JP: 0x00253740 Init__8DynamicsFv — root = frames[ frames[0]->rec->parent ] */
void Dynamics::Init(Dynamics *this)
{
    Frame *f = *this->frames;
    if (f) this->rootFrame /*+0x18*/ = f->frames /*+0x90*/ + f->rec->parent * 0x1f0;
}

/* JP: 0x00253040 ResetLink__8DynamicsFv — reseed positions of links from current world positions */
void Dynamics::ResetLink(Dynamics *this)
{
    FVector root = Frame::getWorldPos(this->frames[0], m_Env & 1);
    for (int i = 1; i < nodeCount(this); i++) {
        FVector p = Frame::getWorldPos(this->frames[i], m_Env & 1);
        BRN_LinkList::setLinkPosition(this->links, i - 1, p - root);
    }
    Matrix m = this->rootFrame->world[m_Env & 1];  m.col3 = (0,0,0,1);
    Quaternion q(&m); q.normalize();
    BRN_LinkList::resetLink(this->links, Frame::getWorldPos(this->frames[0], m_Env & 1), q);
}
