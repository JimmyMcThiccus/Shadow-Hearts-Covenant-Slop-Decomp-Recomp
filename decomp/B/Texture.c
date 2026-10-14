/* Texture.c -- Texture / gTexture / gTextureColtrol / TextureAnim / IPUTexture / Clut / ClutAdressControl
 * JP SLPM_602.19 0x002472e0..0x00249170 (Texture.cpp), Clut @0x00247180
 *
 * ===== In-file model texture ("_ModelTextureHeader", 0x20 bytes then payload) =====
 *   +0x00 u32 ?                     (unused here)
 *   +0x04 u16 width   +0x06 u16 height
 *   +0x08 u8  fmt     low 6 bits = bits-per-pixel (4, 8 or 32);  bit6 (0x40) = payload is an IPU/MPEG-2 intra frame
 *   +0x0a u8  mipCount             (0 = no extra mip levels; level headers are chained at +0x14)
 *   +0x0c u16 clutCount            0, 16 or 256  (RGBA8, alpha 0x80 = opaque)
 *   +0x0e u16 clutOffset           byte offset from header start
 *   +0x10 u32 imageOffset          byte offset to pixel data (linear raster, see Texture.md)
 *   +0x14 u32 mipOffset            byte offset to the next (mip) texture header
 *   +0x1c u16 alphaBits            non-zero => ALPHA_1 is set: A=(v&2) B=(v&0xc)>>2 C=(v&0x20)>>4 D=(v&0xc0)>>6 FIX=v>>8
 *   +0x1e u8  atestRef             non-zero => TEST_1: ATE=1 ATST=5(GEQUAL) AREF=ref AFAIL=(+0x1f&3) ZTST=1(ALWAYS)
 *   +0x1f u8  atestFail
 *
 *   GS formats chosen (Texture::CreateData):
 *      bpp 4  -> PSMT4HH (0x2c)  : nibbles stored in bits 28..31 of 32-bit words (free top byte of a 24-bit buffer)
 *      bpp 8  -> PSMT8H  (0x1b)  : bytes stored in bits 24..31
 *      bpp 32 -> PSMCT32 (0x00) at fixed vram block 0x2a00 (IPU-decoded RGBA, uploaded 16x16 tile by 16x16 tile)
 *      CLUT: always PSMCT32, 16 entries (T4) or 256 entries (T8) uploaded to the CLUT arena (ClutAdressControl).
 */

/* 0x00247180 Clut::Clut(); 0x002471e0 Clut::CreateData(uchar* data, int count, int slot, int slotHi):
 *     this->data = data;   this->count = count;
 *     this->cbp  = ClutAdressControl::getAdress(app->clutCtl /*app+0x80*/, slot + slotHi*0x10)
 *     this->tex0clut = (cbp & 0x3fff) << 37  | CPSM=0 (CT32) | CSM=0 (CSM1) | CSA=0 | CLD=1
 *     return data + count*4;            // advance to next block
 *   struct Clut { u8* data; int count; int cbp; int ?; u64 tex0bits @0x10; }
 */
/* 0x00226620 ClutAdressControl::getAdress(i) = (arena.base & 0x3fff) + i*4        (4 blocks = 1 KB per 256-entry CLUT slot)
 * 0x00226570 ClutAdressControl() : GsxRaster::CreateS(mark=1, block=0x3eef, PSMCT32, w=0x40, h=0x100)  [64 slots]  */

/* 0x00247320 Texture::~Texture, 0x002472e0 Texture::Texture (fields zeroed) */

/* 0x002474b0 Texture::CreateMipMapData(uchar* p)   [called on an element of the mip array]
 *     this->hdr = (header*)p;  this->pClut = 0;  this->pImage = p + hdr->imageOffset;   return p + hdr->mipOffset;   */

int Texture_CreateData(Texture* t, uchar* data, int clutSlot, int vramBlock, int clutSlotHi)   /* 0x002474e0 */
{
    t->hdr = (ModelTextureHeader*)data;
    if (t->hdr->clutCount) {
        t->pClut = new Clut;
        Clut_CreateData(t->pClut, data + t->hdr->clutOffset, t->hdr->clutCount, vramBlock?, clutSlot);
    }
    int w = hdr->width, h = hdr->height;
    if (!(hdr->bpp_flags & 0x40)) t->pImage = data + hdr->imageOffset;
    else { sceIpuInit(); t->pIpuTex = new IPUTexture; IPUTexture_create(t->pIpuTex, hdr, vramBlock, data + hdr->imageOffset); }
    hdr->bpp_flags &= 0x3f;                    /* IPU flag consumed */
    t->vramAddr = vramBlock;
    tw_log2 = log2(w); th_log2 = log2(h);       /* the two odd `for` loops */
    switch (bpp) { case 4: psm=0x2c; pixPerQw=32; break; case 8: psm=0x1b; pixPerQw=16; break;
                   case 32: vramBlock = t->vramAddr = 0x2a00; psm=0 (CT32); pixPerQw=4; break; }
    if (!t->pIpuTex) {
        /* one VIF1 DMA chain per texture: */
        t->pLoadPktA = new CVif1Packet((mipCount+1)*100 qw, 0x10);
        RefLoadImage(pkt, dbp=vramBlock, psm, dbw=max(w/64,1), data, qwc = w*h/pixPerQw, 0,0);
        if (t->pClut) RefLoadImage(pkt, clut->cbp, PSMCT32, 4, clut->data, (bpp==8)?0x40:4, 0,0);  // 256*4B=64qw / 16*4B=4qw
        for each mip level i (hdr->mipCount):  mip[i] = Texture; p = mip[i].CreateData-like MipMap; tbp[i] cumulative (w*h/64 words),
                  tbw[i] = max(w/64,1);   RefLoadImage(pkt, tbp[i], psm, tbw[i], mip image, w*h/pixPerQw, 0,0)
        pad to qword, patch last tag qwc, append `ret` tag (0x60000000), sceVif1PkTerminate
        t->pLoadDmaA = t->pLoadDmaB = pkt->pBase;
    } else {
        /* IPU texture: two chains (A/B) of 16x16-pixel tiles, each `RefLoadImage(vram 0x2a00, CT32, dbw, tile ptr, 0x100/4 qw, x, y)`
         * x += 16 across, y += 16 down; tile data pointer += 0x400 bytes (16*16*4); chain A reads decode buffer 0, B buffer 1 */
    }
    createRegsterPacket(t, clutSlot, mipCount, vramBlock, w, tw_log2, th_log2, psm);   /* builds pRegPkt0/1 and pTex0Pkt0/1 */
    if (hdr->alphaBits) changeGSAlpha(t, a&2, (a&0xc)>>2, (a&0x20)>>4, (a&0xc0)>>6, (a&0xff00)>>8);
    if (hdr->atestRef) changeGSTest(t, 1, 5 /*ATST*/, ref, fail&3, 0, 0, 1);
    return pEndOfData;
}

/* 0x00247eb0 Texture::createRegsterPacket(clutMode, mipCount, tbp, tbw, tw, th, psm)
 *   pRegPkt0/1  (0xa0 B, 10 qwords) = DMA(ret|8) VIF DIRECT 8 ; GIFtag NLOOP=7 EOP A+D;
 *        TEXFLUSH(0x3f)          | MIPTBP1_1(0x34) mip1..3 {tbp,tbw} | MIPTBP2_1(0x36) mip4..6 |
 *        TEX1_1(0x14) = (mipCount<<2) | MMAG=1<<5 | MMIN=1<<6 | L=? K=0xffffff6c.. | CLAMP_1(0x08)=0 |
 *        ALPHA_1? (0x42)  value @+0x70 (changeGSAlpha) | TEST_1(0x47) = 0x5370b default
 *   pTex0Pkt0/1 (0x50 B) = GIFtag NLOOP=2 EOP A+D; TEXFLUSH ; TEX0_1(0x06) =
 *        clut.tex0bits | TBP0=tbp | TBW=max(w/64,1)<<14 | PSM<<20 | TW<<26 | TH<<30 | TCC=1<<34 (RGBA) [TFX=MODULATE 0]
 *   Two copies A/B exist for double buffering (m_Env&1). getTex0GsPacket(i, tbp, tcc, tfx) edits copy i in place.
 */
/* 0x002483d0 Texture::setFrame(): IPU textures: decodeFrame(m_Env&1)  -- advance animation frame           */
/* 0x00248400 getTex0() = *(u64*)(pTex0Pkt0+0x20)   0x00248410 getTex1() = *(u64*)(pRegPkt0+0x50)  0x00248420 setTex1(u64&) */
/* 0x00248430 getTex0GsPacket(i,tbp,tcc,tfx) -> pTex0Pkt[i]  (patch TBP0 / TCC bit / TFX bits then return DMA addr) */
/* 0x002484c0 changeGSClump(a..): CLAMP_1 value @ pRegPkt0+0x60 = WMS|WMT<<2|MINU<<4|MAXU<<14|MINV<<24|MAXV<<34  */
/* 0x00248530 changeGSAlpha(a,b,c,d,fix): ALPHA_1 value @ pRegPkt0+0x70                                       */
/* 0x00248590 changeGSTest(...): TEST_1 value @ pRegPkt0+0x80                                                */

/* ---- gTexture (named, ref-counted texture; size 0x80) / gTextureColtrol (global list head) ----
 *   struct gTexture : Texture { char name[12] @0x4c; ...; BufMemory* @0x64; int w@0x68, h@0x6c (screen-size textures);
 *                               int refCount @0x70; int delState @0x74; gTexture* next @0x78; gTexture* prev @0x7c }
 *   gTextureColtrol::m_pOur (@0x0040ac2c) = list head.  setTexture(name,tex) strcpy name, addTex (insert after head)
 *   findTexture(name) strcmp-walk.  CreateTexture(name, BufMemory*): new gTexture, CreateData(buf->ptr, 1, 0x2a00, 0); ALPHA (1,2,0,0,0)
 *   gTexture::deleteTexture(): --refCount; if (<1) delState=2 (collected later by ExpansionTexture::getPacket)         */

/* ---- TextureAnim (animated sub-rect texture; element of Texture+0x3c, 0x10 bytes) ----
 *   hdr(+0x10 u8 texIndex, +0x11 u8 frameCount, +0x12 u16 frameW, +0x14 u16 frameH, +0x18 u16 frameStride(qw?),
 *       +0x1a u16 dstX, +0x1c u16 srcYinset, +0x20 u16 dataQwords)  data follows header at +0x30
 *   CreateData: for each frame builds a CVif1Packet (100 qw) with RefLoadImage(tbp = tex[texIndex].tbp, T4HH/T8H by clut count 16/256,
 *       dbw = w/64, frameData, w*h/pixPerQw, x=dstX, y=texH - srcYinset - frameH) ; returns next block
 *   getTexAnimPacket(): packet of frame (current-1)*0x30+4 ; setCurrentIndex(i<=frames)                       */

/* ---- IPUTexture (0x6a0 bytes; MPEG-2 intra "movie" texture) ----
 *   +0 u32* buf0 (w*h*4)  +4 u32* buf1  +8 src MPEG ptr  +0xc w +0x10 h +0x14 bpp(32) +0x1c frameCount +0x20 curFrame
 *   +0x24/+0x28 flags +0x2c qwc(...)  +0x30.. DMA tag list (40000-qw pieces) fed to IPU_TO channel (DmaMan ch 4)
 *   decodeFrame(parity): first call: IPU reset, CMD=0 (BCLR), feed bitstream by DMA; every call: IPU_CMD IDEC (0x40000000?)..
 *       FROM-IPU DMA (channel 3) -> buf[parity]; w/16*h/16 macroblocks, 32-bit RGB (RGBA32 with A=0x80).
 *   PORT NOTE: decode with any MPEG-2 intra decoder (I-frame, 4:2:0, 16x16 MB) to RGBA8; no GS emulation needed.    */
