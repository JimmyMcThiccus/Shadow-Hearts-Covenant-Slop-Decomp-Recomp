/* Frame — bone/node of a Model. JP 0x002433c0..0x0024442c. Struct: Frame (0x1f0 bytes), see notes/C/Frame.md */

/* JP: 0x002436d0 Cleate__5FrameFPUcP5Frame
 * rec   = 0x40-byte FRHD record, table = Model.frames (base of the Frame array) */
bool Frame::Cleate(Frame *this, FrameRec *rec, Frame *table)
{
    this->rec   = rec;        /* +0x80 */
    this->frames = table;     /* +0x90 */
    Quaternion q(rec->rot);                     /* rec+0x30 (x,y,z,w) */
    Quaternion::getMatrix(&q, &this->rotMat);   /* +0xa0 */
    this->invBind.m[3] = FVector(rec->pivot);   /* +0x110 = column 3 of +0xe0 : translation t, w=1 */
    Matrix tmp = this->rotMat * this->invBind;  /* R * T(t) = bind matrix B */
    this->invBind = tmp;
    sceVu0InversMatrix(&this->invBind, &this->invBind);   /* invBind = B^-1 */
    Frame::myMatrixUpdate(this);
    return true;
}

/* JP: 0x00243610 myMatrixUpdate__5FrameFv
 * animMat (+0x1a0) = rotMat * extraMat(+0x160) * T(rec->pivot)   (extraMat is identity unless overridden by script/IK) */
void Frame::myMatrixUpdate(Frame *this)
{
    this->animMat = Matrix::Identity();
    this->animMat.m[3] = this->rec->pivot;             /* +0x1d0 */
    this->animMat = this->extraMat * this->animMat;    /* MulMatrix(+0x160, +0x1a0) */
    this->animMat = this->rotMat   * this->animMat;
}

/* JP: 0x00243ed0 calcMotion__5FrameFv — sample each frame's Sequence into motionMat (+0x120) */
void Frame::calcMotion(Frame *this)       /* this = first frame; count = (flags >> 2) & 0xff */
{
    for (int i = 0; i < ((this->flags & 0x3ff) >> 2); i++) {
        Frame *f = &this->frames[i];
        Sequence *s = f->seq;                           /* +0x88 */
        if (!s || !s->enabled)                          /* +0x1c */
            f->motionMat = Matrix::Identity();
        else
            Sequence::getMatrix(s->control->curTime, &f->motionMat, s);   /* [R(q)|d] at time */
    }
}

/* JP: 0x00243fb0 calcMatrix__5FrameFP6Matrixi
 * buf selects one of the two world matrices at +0x00 / +0x40 (double buffering: m_Env__VIF1Prim & 1)
 * Result: world[buf] is the *skinning* matrix: identity in bind pose. */
bool Frame::calcMatrix(Frame *this, Matrix *root, int buf)
{
    if (this->noRecalc /* +0x1e0 */ && root == NULL) return false;
    for (int i = 0; i < ((this->flags & 0x3ff) >> 2); i++) {
        Frame *f = &this->frames[i];
        u8 parent = f->rec->parent;                                    /* rec+0x0c */
        if (parent == 0xff)  f->world[buf] = root ? *root : Matrix::Identity();
        else                 f->world[buf] = this->frames[parent].world[buf];
        if (f->seq == 0 && !(f->flags & 1))
            f->world[buf] = f->world[buf] * (f->invBind * f->animMat);               /* bind pose: identity */
        else
            f->world[buf] = f->world[buf] * (f->invBind * (f->motionMat * f->animMat));
        if (f->chain_flag /* +0x94 */) {                                /* a Model chained to this bone (weapon, hair...) */
            Matrix r = Frame::getWorldRot(f, buf);  Vector p = Frame::getWorldPos(f, buf);
            f->chain_model->vtbl->calcMatrix(f->chain_model, &worldmat(r, p));       /* vtbl+0x28 */
        }
    }
    return true;
}
