/* GsxCamera.c -- class GsxCamera (libgsx.cpp)  JP SLPM_602.19 0x00226b90..0x00227d54 (+ small inlines elsewhere)
 *
 * struct GsxCamera  (size 0x398)   -- Ghidra struct "GsxCamera"
 *  +0x000 sceGsDispEnv disp     pmode@0 smode2@8 dispfb@0x10 display@0x18 bgcolor@0x20   (0x30 bytes)
 *                               (smode2 bit1 = FFMD; Gsx::SetFFMode edits camera+8 bit1)
 *  +0x030 u64 rt_dmatag         DMA tag  (id=7 END | qwc = giftag.nloop+1)        } "render target packet",
 *  +0x038 u32 rt_vif0 = 0x13000000 (FLUSHA)                                       } 0x30..0x15f = 0x130 bytes,
 *  +0x03c u32 rt_vif1 = 0x50000000|qwc (DIRECT)                                   } sent verbatim on VIF1 by
 *  +0x040 GIFtag rt_giftag      NLOOP=0x11, EOP, FLG=PACKED, NREG=1, REGS=0xE(A+D) } FlipBuffer / GetRenderTargPkt
 *  +0x050 sceGsDrawEnv1 drawenv1 (8 A+D qwords: FRAME_1,ZBUF_1,XYOFFSET_1,SCISSOR_1,PRMODECONT,COLCLAMP,DTHE,TEST_1)
 *  +0x0d0 sceGsDrawEnv2 drawenv2 (same for context 2)
 *  +0x150 qword fogcol          A+D FOGCOL(0x3d) = 0xffffff (reset by Create), SetFogColor writes it
 *  +0x160 sceGsClear clear      testa,prim,rgbaq(+0x180 = bg colour u32!),xyz2a(+0x190),xyz2b(+0x1a0),testb
 *  +0x1c0 call-packet env1      cnt(1){FLUSHA?,DIRECT 3,GIFtag A+D x3}, then REF 3 qw -> &drawenv1+0x10 (ZBUF1,XYOFFSET1,SCISSOR1), ret
 *  +0x200 call-packet env2      same, ref -> &drawenv2+0x10
 *  +0x240 Matrix frame          camera world matrix (set by game: CameraServer etc.)
 *  +0x280 Matrix viewMat        = inverse(frame)  (ApplyFrame)
 *  +0x2c0 Matrix viewScreen     sceVu0ViewScreenMatrix(scrz,ax,ay,ofsx/16,ofsy/16,zmin,zmax,near,far)
 *  +0x300 Matrix viewClip       sceVu0ViewClipMatrix(width/ax,height/ay,scrz,near,far)
 *  +0x340 GsxRaster* pFrame     colour buffer allocation (24bpp: PSMCT24)
 *  +0x344 GsxRaster* pZbuf      z-buffer allocation (PSMZ24)
 *  +0x348 u16 width   +0x34a u16 height     (512 x 448 for the game camera)
 *  +0x34c f32 scrz    +0x350 f32 ax   +0x354 f32 ay           (SetViewMatrix args 1..3)
 *  +0x360 FVector fogParam  = (0, fogNear, 256/(fogFar-fogNear), 255.0)        (SetFogParam)
 *  +0x370 f32 nearZ   +0x374 f32 farZ  +0x378 f32 zmax (=(1<<zbits)-1, or param/2)  +0x37c f32 zmin
 *  +0x380 f32 fogNear +0x384 f32 fogFar
 *  +0x38c u16 fbp[2]  frame-buffer base (block units/32 = GS FBP) for the two pages (fbp[1] = GetBufHalf>>5)
 *  +0x390 u8 flags:  bit0 double-buffered (page flip; frame raster allocated 2*height tall)
 *                    bit1 has z-buffer   bit2 clear-every-frame (BeginUpdate -> ClearRaster)
 *                    bit3 sync DMA+PutDispEnv in FlipBuffer      bit4 "flip requested last time" (latched by Flip)
 *                    bit5 capture requested (CApp::Run capture path)
 *  +0x394 u8 bufIdx (page being *displayed*? toggled in FlipBuffer)   +0x395 u8 field (even/odd field latch)
 */

/* 0x00226b90 GsxCamera::GsxCamera() -- zero the matrices to identity (vmr32/sqc2 VU0 sequence), CommonInit() */
/* 0x00226de0 CommonInit(): pFrame=pZbuf=0; frame=identity; ApplyFrame() */

/* 0x00226e10 GsxCamera::Create(uint w, uint h, int fbBpp, int zBpp, uint flags)
 *   w/h default to Gsx::vmode.width/height; fbBpp 0 => vmode.fb_psm else GetBPPtoPSM(fbBpp,0)
 *   flags: bit0 -> camflags.bit2 (clear each frame), bit1 -> camflags.bit0 (double buffer), bit3 -> camflags.bit3
 *   zBpp != 0 -> camflags.bit1, zmax=(1<<zBpp)-1, zmin=0, zpsm=GetBPPtoPSM(zBpp,1)
 *   sceGsSetDefDispEnv(&disp, psm, w, h<=0x1c0?h:h/2, 0,0)        (tall -> field mode)
 *   sceGsSetDefDrawEnv (&drawenv1, psm, w, h, zte=1|2?, zpsm)  sceGsSetDefDrawEnv2(&drawenv2, ...)
 *   pFrame = new GsxRaster; pFrame->Create(true, psm, w, h * (dbuf?2:1)); fbp[0]=pFrame.base>>5; fbp[1]=GetBufHalf()>>5
 *   if zbuf: pZbuf = new GsxRaster; Create(true, zpsm, w, h); drawenv.zbuf.zbp = pZbuf.base>>5
 *   sceGsSetDefClear(&clear, ztest, 0x800 - w/2, 0x800 - h/2, w, h, 0,0)
 *   build rt_dmatag/rt_vif0/rt_vif1, rt_giftag (NLOOP 0x11), fogcol = 0xffffff,
 *   build env1/env2 call packets (see layout above).
 */

/* 0x002273b0 CaptureOut(): buf = new[0xe0000]; GsxFrameBuf::StoreImage(pFrame, buf, {0,0,width,height}); return buf   */

/* 0x00227420 GetRenderTargPkt(QWD* out)  -- copy of the RT packet with the frame/zbuf base patched for the
 * *current page*:  page = 0;
 *    if (flags&1) { page = (bufIdx ^ 1) & 1; if (m_flags & 0x10 /*Gsx inter30?*/) page ^= 1; }
 *    drawenv1.frame.fbp = drawenv2.frame.fbp = fbp[page] & 0x1ff;
 *  returns qword count = giftag.nloop + 1  (so a P2Pkt can embed a camera switch, see P2Filter::MakePacket)  */

/* 0x00227650 FlipBuffer(bool inIntr)
 *   if (!pFrame) return;  bufIdx ^= 1;
 *   if (flags & 1) { disp.dispfb.fbp = fbp[bufIdx ^ 1]; drawenv1.frame.fbp = fbp[bufIdx]; drawenv2.frame.fbp = fbp[bufIdx]; }
 *   inIntr ? iFlushCache(0) : FlushCache(0);
 *   if (flags & 8) { sceDmaSync(GIF); sceDmaSync(VIF1); sceGsPutDispEnv(&disp); }
 *   Gsx::SetRenderTarget(&drawenv1); Gsx::SetRenderTarget2(&drawenv2);     // shadow copies into Gsx::GSRegister
 *   sceDmaSync(VIF1); DMAC_1.CHCR = 0x41; DmaMan::DmaSend(1, &rt_dmatag);   // draw-env switch goes down VIF1
 */

/* 0x002277b0 Flip(bool syncV, bool inIntr)
 *   flags.bit4 = field latch; if (!syncV) cur = GS CSR.FIELD else cur = sceGsSyncV(0) ...; field = !cur
 *   if (flags.bit5) { field = (flags.bit4 ^ 1); flags.bit5 = 0; }
 *   sceGsSetHalfOffset(&drawenv1, 0x800, 0x800, (Gsx::m_flags & 8) ? 0 : field);   // field-dependent y half-pixel offset
 *   FlipBuffer(inIntr);  Gsx::HCount = RCNT3;
 */

/* 0x002278e0 SetViewMatrix(scrz, ax, ay, nearz, farz)   nearz/farz < 0 => keep; zmax = farz'/2 ; zmin = nearz'
 *   [JP fields]: +0x34c=scrz +0x350=ax +0x354=ay +0x378=zmax(=farz arg/2) +0x37c=zmin(=nearz arg)
 *   -> MakeViewMatrix()                                                                              */
/* 0x002279e0 MakeViewMatrix():
 *   sceVu0ViewScreenMatrix(scrz, ax, ay, ofsx/16.0, ofsy/16.0, zmin, zmax, nearZ, farZ, &viewScreen)
 *   sceVu0ViewClipMatrix  (width/ax, height/ay, scrz, nearZ, farZ, &viewClip)                         */
/* 0x00227b50 GetViewScreenMatrix() -> returns viewScreen * viewMat  (full world->screen)               */
/* 0x00227bd0 ApplyFrame(): viewMat = inverse(frame)  (sceVu0InversMatrix)                              */
/* 0x00227c00 ClearRaster(): builds & sends a 7-qword packet (new[0x80]) on VIF1:
 *     A+D: PRIM=6(SPRITE) ... RGBAQ = *(u64*)(this+0x180) (bg colour), XYZ2 = (0x800 - w/2)*16 ..,
 *          XYZ2 (0x800 + w/2)*16, then ZBUF write-mask / TEST from drawenv1+0x?? (this+0xc0) to also clear Z.
 *   Called from World::BeginUpdate when camflags.bit2.                                                  */
/* 0x0025fa70 GetMatrix() -> &frame ; 0x0030fe70 GetViewMatrix() -> &viewScreen? (returns this+0x2c0)   */
/* 0x002ff510 SetBgColor(_rgba32&) : *(u32*)(this+0x180) = rgba.GetVal()                                */
/* 0x00300de0 SetFogParam(near, far): fogNear/fogFar stored; fogParam = FVector(0, near, 256/(far-near), 255.0) */
/* 0x003083d0 SetScreenZ(f) : scrz = f; MakeViewMatrix()                                                 */
/* 0x0030fd00 SetFogColor(_rgba32&) : fogcol.data = rgba                                                 */
/* static GsxCamera* m_pActiveCamera @0x0040abb4 ; GetActiveCamera 0x004a80c0 ; GetFrame 0x004a80d?       */
