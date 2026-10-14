/* SequenceControl / Sequence / RotAnim / TranceAnim / Event — motion playback. JP 0x00242ae0..0x002466d4 */

/* JP: 0x00245820 Cleate__15SequenceControlFPUc (sqhd = motion file image) */
u8 *SequenceControl::Cleate(SequenceControl *this, u8 *sqhd)
{
    this->hdr = sqhd;
    u16 nSeq = *(u16 *)(sqhd + 0x12);
    this->sequences = new Sequence[nSeq];            /* 0x24 each */
    u8 *p = sqhd + 0x20;
    for (int i = 0; i < nSeq; i++) p = Sequence::Cleate(&this->sequences[i], p, this);
    u16 nEv = *(u16 *)(sqhd + 0x16);
    if (nEv) {
        this->events = new Event[nEv];               /* 0x14 each */
        for (int i = 0; i < nEv; i++) p = Event::Cleate(&this->events[i], p, this);
    }
    this->frameTime = this->hdr ? 1.0f / sqhd[0x15] : 1.0f / 60;     /* +0x14 */
    if (*(u16 *)(sqhd + 0x1a) == 0) { *(u16 *)(sqhd + 0x10) -= 1; *(u16 *)(sqhd + 0x1a) = 1; }
    return p;
}

/* JP: 0x00245670 addTime__15SequenceControlFf  — returns 1 on wrap/finish */
int SequenceControl::addTime(SequenceControl *this, float dt)
{
    int ret = 0;
    float dur = (float)*(u16 *)(this->hdr + 0x10) * this->frameTime;
    if (*(i16 *)&this->field18 == 0) {               /* not finished */
        this->curTime += dt;
        if (this->curTime > dur) {
            if (!(this->hdr[0x14] & 1)) { this->curTime = dur; *(i16 *)&this->field18 = 1; }   /* clamp, finished */
            else this->curTime -= dur;                                                             /* loop */
            ret = 1;
        }
    }
    return ret;
}

/* JP: 0x00245ec0 setCTime__15SequenceControlFf — seek and reset event cursors */
void SequenceControl::setCTime(SequenceControl *this, float t)
{
    this->curTime = t; *(i16 *)&this->field18 = 0;
    for (int i = 0; i < *(u16 *)(this->hdr + 0x16); i++) Event::setIndex(&this->events[i], t);
}

/* JP: 0x002457b0 SeachSequenceControl__15SequenceControlFPUc — walk the CList comparing the 12-byte names at hdr+4 */
/* JP: 0x00245af0 Sequence::Cleate:  RotAnim(count=*(u16*)(seqhdr+0x10)), TranceAnim(count=*(u16*)(seqhdr+0x12));
 *      RotAnim::Cleate(data = seqhdr + 0x20), TranceAnim::Cleate(data = after rot keys) */

/* JP: 0x00242b40 RotAnim::Cleate:  times = p; keys = align16(p + 2*count); returns align16(keys + 8*count) */
/* JP: 0x00243010 TranceAnim::Cleate: identical layout (8-byte SVector keys)                                */

/* JP: 0x00242c00 RotAnim::getQuaternion(t) — cursor search (this->cursor at +8, resumes from last index, wraps to 0),
 *     keys decoded with PEXTLH/VITOF12 (s16 / 4096), Quaternion::slerp between key i and i+1 */
/* JP: 0x002430d0 TranceAnim::getTrance(t) — SVector::ShortToFloat on both keys then lerp */
/* JP: 0x00245be0 Sequence::getMatrix(t) — M = identity; if (rot) M = RotAnim::getMatrix(t); if (trance) M.col3 = getTrance(t) */

/* JP: 0x00246260 Event::checkEvent(t, Model *m) — see notes/C/motion_format.md for key encodings.
 *   kind&0xf == 0 : f32 trigger times:   callback(model, name, hdr, 0, 0, 0)
 *   kind&0xf == 1 : {u16 t, s16 v}:      hi nibble 0 -> interpolated between keys (+0.01 rounding), else value at key
 *   kind&0xf == 2 : {u16 t, u16 v, u32 extra}
 *   kind&0xf == 3 : {u16 t, u8 v, u8 v2, u32 extra}
 *   callback = m->vtbl[0x34/4](m, motionName=control->hdr+4, hdr, value, hdr->bone(+0xa), extra)
 */
