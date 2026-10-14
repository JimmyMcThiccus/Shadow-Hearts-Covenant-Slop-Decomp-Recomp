/* Misc.c -- ShadowControl, ExpansionTexture, ScreenTexture/BackScreenTexture/WriteTexture/LayeredTexture, FrameTexture,
 *           ScreenBright, CScrCapture, CineMask, JRCTex, vpTexture/PutiTexture (names only)
 *
 * ---- ScreenBright : VIF1Prim + DelayDeleteObject  (size 0x38)   0x003d8770..0x003d8b20 ---------------------------
 *   +0x14/+0x18 (DelayDelete) +0x1c vptr2  +0x20 QWD* pkt[2] (2 x 0x70 B copies of template `pktData` 0x00403d50)
 *   +0x28 u8 level (0..0x80 alpha; default 0xd)?  +0x29 u8 parity  +0x2c void*(*pfnPre)(void*) +0x30 arg  +0x34 u32 rgb colour
 *   template (7 qw): DMA ret|6, FLUSHA, DIRECT 6 ; GIFtag NLOOP=2 A+D: TEST_1=0x35302(ATE off, ZTST ALWAYS), ALPHA_1=0x44 (Cs*As+Cd*(1-As));
 *                    GIFtag REGLIST 4 regs {PRIM,RGBAQ,XYZF2,XYZF2}: PRIM=0x46 (SPRITE|ABE), RGBAQ=(rgb | level<<24), XYZ = (0x800 +- w/2, 0x800 +- h/2)*16
 *   getPacket(): flips parity; if level==0 returns NULL; patches RGBAQ and the two XYZ with camera width/height (or CApp::m_scrw/h).
 *   Draw()   0x003d8a50: DrawSync(); [optional pre packet from pfnPre -> VIF1]; request getPacket() on VIF1   -- full-screen fade to colour. It is called
 *   directly from CApp::Run after WorldGetPacket (NOT part of the OT), so it always lands on top.
 *
 * ---- CScrCapture : DelayDeleteObject   0x003caf70..0x003cbf80 -------------------------------------------------
 *   Screenshot-to-sprite.  Create(mode,type,BufMemory*): vram scratch 512x480 CT32 ; type1 => StoreImage (GS->EE, 0xb4000 B buffer) else GS local copy.
 *   Polling (registered as CApp::m_pAppFunc one-shot): DrawSync; sceGsSetDefStoreImage(front buffer fbp<<5, ..); copies the displayed frame (512 x camera h)
 *   either to main memory (type 1) or inside VRAM (BITBLTBUF/TRXDIR=2 local->local); then UpdateSprite builds a P2Pkt{[MakeLoadPkt]+P2Sprite} and Dsp() puts it in the OT.
 *
 * ---- CineMask : CPolObj + P2Pkt  (letterbox bars)   0x003cf630..0x003cfb40 --------------------------------------
 *   +0x18 P2Pkt  +0x44 state flags (bits3-4: 0 idle, 1 closing, 2 opening)  +0x46 u16 timer (+= sys->frameDelta)
 *   MakePacket: t = timer/400 (clamped 1; opening: 1-t); h = 128 - cos(t*pi/2)*128 ; draws 4 black SPRITEs (top/bottom bars, alpha fixed by `fVar7<<24`)
 *   with y extent growing by t*32 px per bar ; layer 3 (flags 0x30).  Returns "finished".
 *
 * ---- ShadowControl : VIF1Prim  (size 0x3520) 0x00258230..0x00259e70 -----------------------------------------------
 *   Projected-shadow system.  +0x20 ReceiveModel list head, +0x30 ReleaseModel list head  (CList-based; Model+0x48c = registered flag)
 *   +0x310/+0x314 QWD[5000] (80000 B) packet buffers A/B ; +0x320.. Matrix[] cache  ; static m_pOur @0x0040ac34 ; m_pEnv @0x00420d10 (0x640 B template chain)
 *   Init(): looks up gTexture "FRAME" (string @0x3fe810; w/h at +0x68/+0x6c) and uses vram 0x2a00 as shadow buffer; builds fixed GS state chain (FRAME/ZBUF swap to the shadow texture,
 *           clear with grey 0x80808080, sprite compose with ALPHA, TEST), m_pProcess @0x00421350 -> chain heads @0x00421354/58.
 *   setDropShadow(Model*) : adds a ReleaseModel{model} (the shadow *caster*)  setReciveShadow(Model*): adds ReceiveModel (the shadow *receiver*)
 *   calcShadowAtomic(ReleaseModel*, Model* recv, int* outIdx): frustum-ish culling of caster atomics against the receiver's bounding area
 *        (checkArea / checkBoundingArea2, with DIntr/EIntr) -> list of caster atomic indices that can shadow `recv`
 *   getPacket() 0x00258ae0 (0x11ec B): per frame: render casters (flat colour) from the shadow-light position (LightControl::getLightMatrix shadow light)
 *        into the offscreen texture, then draw receivers modulated by that texture.   => Port: classic shadow-map/blob; see sh2_gfx::shadow.
 *
 * ---- ExpansionTexture : VIF1Prim (size 0x28)  0x00252190..0x00252840  -------------------------------------------
 *   static pOur @0x00430... ; two 0xc80-B packet buffers (+0x20/+0x24).  Owns the two screen-sized gTextures named (strings @0x3fe7b0..):
 *   "FRAME" (tbp 0 = aliases the frame buffer pages) and "FRAME_TEX" (tbp 0x2a00 = scratch area after Z), 512x448 (w=0x200,h=0x1c0) CT32, TW/TH=9
 *   (strings @0x3fe7b0..0x3fe810 are only "FRAME"/"FRAME_TEX").  ShadowControl::Init also looks up "FRAME" (via m_pOur gTextureColtrol).
 *   getPacket(): garbage-collects dead gTextures (delState countdown), and when texture present builds: [ref texture reg chain]
 *       VIF STCYCL/FLUSH..., A+D: ZBUF?/FRAME?(0x3b), 0x48(TEST_2), TEX0 from getTex0GsPacket(.., fbp<<5 of *previous* page), ALPHA ... then 2 sprites copying
 *       the previous frame buffer into the texture region (full-screen read-back for distortion/shockwave effects).
 *   changeLayer(l): re-queue in OT.  resetTexture(): deleteTexture on both.
 *
 * ---- LayeredTexture : gTexture + VIF1Prim(+0x80) + DelayDeleteObject(+0x94)  (size 0xb0)
 *      ScreenTexture (0x38fd50) / BackScreenTexture (0x390770) / WriteTexture (0x390bc0): screen-sized full-screen effects built from slices.
 *      +0xa4/+0xa8 packet buffers (800 B for Screen, 8000 B for Write), +0xac float scale (1.0), Init(w,h): gTexture w/h @0x68/0x6c, refcount=1.
 *      ScreenTexture::getW/getH = scale*512 / scale*448.   getPacket(): per-strip BitBlt of frame buffer to texture + distorted sprite draw (0x820/0xe18 B funcs).
 * FrameTexture (0x003b11c0): Create(psm,w,h) stores w/h/psm; Capture(): VIF1 chain: GS local->local copy of the *other* page of the camera into vram block 0x150<<?..
 *      then restores draw env (ref camera+0x50/+0xd0).   RenderOffscreen/StoreImage: render a model list into the texture / read back.
 *
 * ---- JRCTex (judgement-ring texture, 0x88+ B, vtbl 0x4067f8)   0x002fa380..0x002fb460 ------------------------------
 *   file: u32 ?, u16 w@4, u16 h@6, u8 fmt@8 (&7: 0=4bit,1=8bit; 2..4 unsupported), u16 clutEntries@0xa, u16 nPalettes-1@0xc, +0x10: palettes RGBA8 [n][entries], then pixels
 *   (4bit: w*h/2 bytes, 8bit: w*h).  Create(blob, clutLimit, rasterPsm, clutPsm) -> builds per-palette VIF1 chains (mTex[i]) with
 *   BITBLTBUF/TRXPOS/TRXREG/TRXDIR + REF of palette data (CLUT arena slot 0), then a second chain for the pixels;  ChangeClut(i) selects palette.
 *   GetTex0(tcc) = raster tex0 | clut bits | tw/th.
 * vpTexture/vpTextureFile (0x002fe3a0..): "vp" animated sprite textures; PutiTexture (0x0025faf0): Puti effects textures (Section D).
 */
