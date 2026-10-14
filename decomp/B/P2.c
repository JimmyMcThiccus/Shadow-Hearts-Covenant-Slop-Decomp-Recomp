/* P2.c -- P2Pkt / P2Sprite / P2Clut / P2GraTex / P2TexTex / P2Image / P2MakeBitBltPkt / SetFullSprite / P2Filter
 * JP SLPM_602.19 0x003c6b10..0x003c94fc, 0x003d33a0..0x003d3f44, 0x003d51a0
 *
 * "P2" = a small immediate-mode 2D layer used by the movie/capture/filter code.  Everything is expressed as raw
 * GIF packets embedded in a user-built DMA chain (P2Pkt), registered in the World OT as an ordinary VIF1Prim.
 */

/* ---------------- P2Pkt : VIF1Prim  (size 0x2c) ------------------------------------------------
 *  +0x00 VIF1Prim base (vptr @+0x10 = __vt__5P2Pkt; vtbl[1] = getPacket)
 *  +0x14 QWD* pBuf              1 or 2 halves of (capacity+1) qwords
 *  +0x1c u8 flags: bit0 = in OT, bit1 = double buffered (halves selected with m_Env&1), bits2.. = OT layer ((flags&0x7f)>>2); init 0x18 => layer 6
 *  +0x1e s16 capacity (qwords)   +0x20/+0x22 s16 used[2]
 *  +0x24 void(*pfnUpdate)(void*)  +0x28 void* arg   -- called at the top of getPacket to (re)build contents each frame
 *
 *  Create(cap, dbl)   0x003c6b90 : new QWD[(cap+1)*(dbl?2:1)]
 *  AddRefe(n)         0x003c6d30 : reserve n+1 qw at the tail: [DMAtag qwc=n | VIF FLUSHA | VIF DIRECT n][n qw payload]; returns payload ptr
 *  AddRet/AddCnt/AddCall(n[,addr]) : AddRefe + OR tag ID (0x60000000 ret / 0x10000000 cnt / 0x50000000 call addr)
 *  Add(n)             0x003c7060 : reserve n raw qw (caller writes its own tags)
 *  Terminate()        0x003c7210 : write `ret` tag (0x60000000) after last used qw
 *  Dsp()/Clr()        0x003c72f0/0x003c7380 : World::AddOT(layer) / ReleaseOT
 *  getPacket()        0x003c7460 : if !inOT -> NULL; pfnUpdate(arg); used==0 ? NULL : &pBuf[half*(cap+1)]
 */

/* ---------------- P2Sprite  (size 0x58) -------------------------------------------------------
 *  +0x00 u32 flags: bits0-10 = GS PRIM register value (SPRITE=6, TME=0x10, ABE=0x40 ...), bit8 FST (UV in texels), bit16 "always update"
 *  +0x01 u8: bit1 -> use context 2 (regs 0x43/0x48/0x07/0x15 instead of 0x42/0x47/0x06/0x14)
 *  +0x02 u8: bit0 dirty, bit2 "centered scale", bit3 TEX1=0x60 (linear), bit4 has register header (10 qw packet instead of 4)
 *  +0x04 QWD* pPkt   +0x08 x +0x0c y (float, screen px, centre or top-left) +0x10 z +0x14 u32 rgba
 *  +0x18 w +0x1c h +0x20 u +0x24 v +0x28 uw +0x2c vh +0x30 offx +0x34 offy +0x38 scalex +0x3c scaley
 *  +0x40 u64 ALPHA +0x48 u64 TEST +0x50 u64 TEX0
 *  Create(attr, tex)  0x003c78b0 : flags=6; tex => bit4; scale=1,1
 *  GetPktSize()       0x003c7950 : 10 (with regs) or 4 qwords
 *  UpdateObj(force)   0x003c79a0 : writes
 *     [regs]  GIFtag NLOOP=5 A+D ; TEXFLUSH(0x3f) ; ALPHA_n ; TEST_n ; TEX0_n ; TEX1_n (0 or 0x60)
 *     [quad]  GIFtag 0x6400000000008001 (EOP, NLOOP=1, FLG=REGLIST, NREG=6) regs = 0x424210 (ST variant) or 0x434310 (UV variant)
 *             = PRIM, RGBAQ, ST|UV, XYZF2, ST|UV, XYZF2      (2 corner SPRITE)
 *             coordinates in 12.4 fixed point with GS offset applied (+0x700,+0x720 for 512x448 => (2048-256, 2048-224))
 */
/* P2Clut : static 64x64 PSMCT32 raster used as shared CLUT area for P2 images (ref counted).  Create 0x003c8050: GsxRaster.Create(0,0,0x40,0x40)
 *          slot (idx) -> x=(idx&3)*16, y=(idx>>2)*16 ; 16x16 for 8bpp, 8x2 for 4bpp ; CSM2 uploads. */

/* ---------------- P2 image blobs ---------------------------------------------------------------
 * P2GraTex (file) : u16 w, u16 h, u16 ?, u16 ?, u16 bpcode(1=8bpp,2=4bpp,3=24bpp else literal bpp), u16 ?, u16 clutCount, u16 ?,
 *                   +0x10: clut RGBA8[clutCount] , image at +0x10 + ((clutCount+3)&~3)*4 ;  linear raster, PSMT8H(0x1b) / PSMT4HH(0x2c) / CT32 / CT24
 * P2TexTex (file) : u16 w, h; u8 bpp @+4; u16 clutCount @+6; u32 imageOff @+8; u32 clutOff @+0xc (relative to blob)
 * CImage (memory) : u8 bpp @0; u8 flags @1 (bit2 owns pixels, bit3 owns pal, bits0-1 pal format 0=RGBA8 1/2=RGB565-ish); u16 w@4; u16 h@6; void* pix @8; void* pal @0xc
 *   Create(w,h,bpp,buf) 0x00226780 ; CreatePal(fmt,buf) 0x00226910 ; Clear(col) 0x00226a10 (fills by bpp; 4bpp uses col*0x11)
 * P2GetBPPtoPSM(bpp,z): 32->0/0x30  24->1/0x31  16->2/0x3a  8->0x1b(T8H)  4->0x2c(T4HH)    (note: *H* formats, unlike Gsx::GetBPPtoPSM 8->0x13 4->0x14)
 * SetLoadPacket(QWD* out, _TEXLOADPARAM* p, tag, void* data) 0x003c8120: builds
 *      DMA(cnt or ref) | FLUSHA | DIRECT 6 ; GIFtag A+D NLOOP=4 ; BITBLTBUF(dbp,dpsm,dbw=p+8..) ; TRXPOS ; TRXREG(w,h) ; TRXDIR=0 ;
 *      GIFtag IMAGE(NLOOP=qwc) ; REF qwc -> data     (>0x7fff qw is split into two REFs) ; size 8 or 0xb qwords
 */
/* P2MakeBitBltPkt(QWD* out, RECT* r, bool filter) 0x003c8da0 : copies P2BitBltPkt template (0xa0 B) and fills
 *      BITBLTBUF(src fbp>>5, ...), TRXPOS, TRXREG(w-1,h-1), then TEX0 for the copy, then 1 or 5 sprite quads drawn from the copy
 *      (5 = four offset taps (±1px) + centre for a cheap blur) ; returns size+10 qwords.  P2ChangeCamera(out,cam) 0x003c9?: switch draw env.
 * SetFullSprite / SetFullSprite2 (P2Pkt*, rgba, ?, dx, dy) 0x003d51a0/0x003d52a0 : AddCnt(4): full-screen SPRITE 0x156 (SPRITE|ABE|TME|FST...)
 */

/* ---------------- P2Filter : CPolObj  (size 0x34+) ---------------------------------------------
 *  full-screen "ghost/blur" post effect:  +0x18 P2Pkt* ; +0x1c flags ; +0x20/+0x22 vram block of two scratch rasters (256x224, 128x112 CT32)
 *  +0x24 float strength (z) +0x2c float alpha(=min(z*z*0.1, 31700)) +0x30 int taps
 *  Create 0x003d3570 : P2Pkt(cap 0x80, dbl) layer 5|? zvolume 0x7ff8 ; pfnUpdate = UpdateS ; allocs the two rasters via GsxFrameBuf.Create
 *  MakePacket 0x003d3970 : each frame: BitBlt front buffer -> scratch (P2MakeBitBltPkt), GetRenderTargPkt, then N sprite quads
 *        sampling the scratch with alpha ramp (asinf/cosf spread), producing a radial/ghost blur.
 */
