/* Atomic and subclasses — one draw unit ("triangle header" + vertex arrays + packet table). JP 0x00242620.. */

/* JP: 0x00242620 __ct__6AtomicFv  (sizeof(Atomic subclasses) = 0x380; vtable at +0x370)
 *   +0x30..: 6 working matrices, +0x2b0 enabled=1, +0x2b1 lit=0, +0x2b2 fx=3, +0x2b3 alpha=0x80,
 *   +0x308/+0x318 = (0,0,1,0) vectors */
/* JP: 0x00242920 Cleate__6AtomicFPUcPP6AtomicP5Model — base: header + 0x30, arrays N*0x30 */
u8 *Atomic::Cleate(Atomic *this, _ModelTriangleHeader *hdr, Atomic **table, Model *model)
{
    this->model = model;           /* +0x350 */
    this->hdr   = hdr;  this->atomicTable = table;
    u8 *p = (u8 *)hdr + 0x30;
    if (hdr->sharedRef == -1) { this->vertexArrays = p; p += hdr->vertexCount * 0x30; }
    this->packetTable = p;                   /* +0x1c : u32 chunkCount; 0x10-byte chunks follow at +0x10 */
    this->chunkTable  = p + 0x10;            /* +0x20 */
    this->lit = (hdr->fxFlags & 1) != 0;     /* +0x2b1 */
    return p;
}

#define ALIGN16(x) ((x) = ((x) & 0xf) ? ((x) + 0x10 - ((x) & 0xf)) : (x))

/* JP: 0x0024d360 Pack1Atomic::Cleate — rigid s16 geometry. arrays: pos 8N | uv 4N | rgba 4N, each 16-aligned */
u8 *Pack1Atomic::Cleate(Pack1Atomic *this, _ModelTriangleHeader *hdr, Atomic **table, Model *model)
{
    ... same prologue ...
    if (hdr->sharedRef == -1) {
        this->vertexArrays = p;
        p += hdr->vertexCount * 8;  ALIGN16(p);
        p += hdr->vertexCount * 4;  ALIGN16(p);
        p += hdr->vertexCount * 4;  ALIGN16(p);
    }
    ...
}
/* JP: 0x0024e6a0 Pack2Atomic::Cleate           : pos 0x10N | 4N | 4N
 * JP: 0x0024f810 SkinAtomicPack2::Cleate        : pos 0x10N | 4N | 8N (normals)
 * JP: 0x00250e30 SkinAtomicPack2NL::Cleate      : pos 0x10N | 4N | 4N
 * JP: 0x00255330 PLP1Atomic::Cleate             : 8N | 4N | 8N      (never produced by shipped models)
 * JP: 0x00256690 PLP2Atomic::Cleate             : 0x10N | 4N | 8N
 * JP: 0x0025b040 BAtomic::Cleate                : 0x28N (+0x380 vertices) | 4N ; stores size at +0x3a0
 * JP: 0x0025ad00 WaterAtomicP1::Cleate         : 8N | 4N | 4N ; copies array1 to +0x3a0, builds random phase/amp arrays
 *     (rand() / 2^31 * 200 + 50 amplitude, * 2*pi phase) indexed by the vertex "bone" byte at pos+6.
 */

/* JP: 0x002500c0 SkinAtomicPack2::initPacket(Frame *frames, u8 *chunkTable)
 * Builds two (double-buffered) VIF1 DMA chains per atomic.  Layout recovered:
 *   tag: 0x10000002 / 0x50000002 : FLUSH + DIRECT? header (GIF setup)  [+0xb8/+0xb9 hold the GS regs]
 *   MPG microcode call: MSCAL addresses 0x1f(31), 0x26(38), 0x27(39) = VU1 programs for init, per-chunk and 'draw'
 *   for each 16-byte chunk entry:
 *     UNPACK matrices of bone[0..2]:  Frame[bone].world[buf] (+0x00 / +0x40 = skin matrix and its normal matrix)
 *                                       -> VU1 data regs 0xb3, 0xb8, 0xbd (5 qwords per bone slot)
 *     vertices: split into runs of <= 0x2a with ADC-boundary fixup (flag bit 2 of hdr->flags)
 *       positions  V4-32 (float x,y,z,w)    -> reg 0x00
 *       uv         V2-16 (+pad)             -> 0x75 / 0x6d
 *       normals    V4-16                    -> 0x6c...
 *   self-modifying fix-up of the vertex w word (see notes/C/model_format.md): slot -> VU1 register offset
 *   end: DMA tag 0x60000000 (END), calls vtbl+0x1c(this, hdr->fxFlags >> 4) = setSpecialEffect(id),
 *        fx id 3 -> this->fxParam(float) = hdr->fxParam ; ids 1,2 -> int
 */
