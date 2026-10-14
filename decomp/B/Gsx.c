/* Gsx.c  --  class Gsx (libgsx.cpp)  JP SLPM_602.19 0x002228c0..0x00223110
 * Static-only singleton wrapper around the GS/DMA setup.  All state lives in globals:
 *
 *   0x0040ab94 Gsx* sys__3Gsx
 *   0x0040ab98 u16  ofsx__3Gsx          (GS primitive X offset, 12.4 fixed; used by MakeViewMatrix)
 *   0x0040ab9c u16  ofsy__3Gsx
 *   0x0040aba0 u32  HCount__3Gsx        (RCNT3 hsync counter value at last Flip, for profiling)
 *   0x0040aba8 u32  m_flags__3Gsx       (see bit table below)
 *   0x0040abac u16  m_syncCount__3Gsx   (min vblanks per frame; 1=60fps 2=30fps)
 *   0x00412e10 GsxVMode vmode__3Gsx     (12 bytes, filled by Gsx::Open)
 *   0x00412e20 u64  GSRegister__3Gsx[0x70]   (shadow copy of GS privileged/draw regs, index == GS reg addr)
 *   0x004131a0 sceGsDrawEnv1 RenderTarg__3Gsx, 0x00413220 sceGsDrawEnv2 RenderTarg2__3Gsx
 *   VCount (global, bumped in cbVSync)
 *
 * m_flags bits (derived from cbVSync / Run / SetFFMode / SetInter30):
 *   bit0  (0x01) initial=1  "gsx opened"
 *   bit3  (0x08) interlace-30 mode (SetInter30)   -> Flip uses half-offset 0 instead of field parity
 *   bit4  (0x10) flip pending (set at end of frame, consumed by cbVSync/GsxForceFlip)
 *   bit5  (0x20) "frame in flight" (set at top of CApp::Run loop and by Gsx::Start; cleared before DrawSync)
 *   bit6  (0x40) FF mode (frame-field) / 60Hz-field flag (SetFFMode arg0, copied to vmode.ffmode&1 in Open)
 *   bit7  (0x80) FF-mode sub flag (SetFFMode arg1)
 *   bit8  (0x100) initial=1 (Initialize sets 0x101); forces a flip every vsync when set
 */

typedef struct GsxVMode {          /* 0x00412e10, 12 bytes */
    u8  mode;       /* +0  sceGsResetGraph video mode (param_6 & 0xf)         */
    u8  inter;      /* +1  interlace   ((param_6>>4)&0xf)                      */
    u8  ffmode;     /* +2  field/frame ((param_6>>8)&0xf)                      */
    u8  fb_psm;     /* +3  GetBPPtoPSM(fb_bpp, 0)                              */
    u16 width;      /* +4                                                       */
    u16 height;     /* +6                                                       */
    u8  zbuf_en;    /* +8  3 if z-buffer requested else 0                       */
    u8  zbuf_psm;   /* +9  GetBPPtoPSM(z_bpp, 1)  (PSMZ32=0x30,Z24=0x31,Z16S=0x3a) */
} GsxVMode;

/* 0x002228c0 Gsx::Initialize()  [static] */
void Gsx_Initialize(void)
{
    if (sys__3Gsx == NULL) sys__3Gsx = new Gsx();   /* ctor is empty */
    m_syncCount__3Gsx = 1;
    m_flags__3Gsx     = 0x101;
    GsxFrameBuf_InitialReset();      /* memset(m_tbl,0,0x800)  -- VRAM block allocation bitmap */
    LightControl_Init();
    sceGsResetPath();
    sceDmaReset(1);
    DmaMan_InitialReset();           /* gets dmaVif0/Vif1/Gif/fIPU/tIPU channels, CHCR=0x41 */
}

/* 0x00222970 Gsx::Reset() */
int Gsx_Reset(void)
{
    sceGsResetPath();
    sceGsResetGraph(0, vmode.mode, vmode.inter, vmode.ffmode);
    ClearLocalMemory();              /* 0x002227b0: GsxFrameBuf::Clear(0) of whole VRAM via VIF1 */
    return 1;
}

/* 0x002229d0 Gsx::Open(int,int,int fb_w,int fb_h?, int zbpp, uint mode) */
void Gsx_Open(int unused, u16 width, u16 height, int fb_bpp, int z_bpp, u32 mode)
{
    vmode.mode   = mode & 0xf;
    vmode.inter  = (mode >> 4) & 0xf;
    vmode.ffmode = (mode >> 8) & 0xf;
    vmode.fb_psm = Gsx_GetBPPtoPSM(fb_bpp, 0);
    vmode.width  = width;
    vmode.height = height;
    vmode.zbuf_psm = Gsx_GetBPPtoPSM(z_bpp, 1);
    vmode.zbuf_en  = z_bpp ? 3 : 0;
    m_flags = (m_flags & ~0x40) | ((vmode.ffmode & 1) << 6);
}

/* 0x00222b90 Gsx::VSync(int n)  -- spin until VCount>=n then VCount=0 */
void Gsx_VSync(int n) { while (VCount < n) ; VCount = 0; }

/* 0x00222bc0/0x00222bd0 */
int  GsxGetVSyncCount(void) { return VCount; }
void GsxClrVSyncCount(void) { VCount = 0; }

/* 0x00222be0 GsxForceFlip() */
void GsxForceFlip(void)
{
    if (GsxCamera_m_pActiveCamera && (GsxCamera_m_pActiveCamera->flags & 1))
        GsxCamera_Flip(GsxCamera_m_pActiveCamera, 0, 1);
    m_flags &= ~0x10;
}

/* 0x00222ab0 cbVSync(int)  -- registered with sceGsSyncVCallback in Gsx::Start */
int cbVSync(int count)
{
    VCount++;
    if (!(m_flags & 0x20)) {                      /* frame not in flight */
        GsxCamera* c = GsxCamera_m_pActiveCamera;
        if (!c || !(c->flags & 1)) {
            m_flags &= ~0x10;
        } else if (!(m_flags & 0x80) || (m_flags & 0x10)) {
            GsxCamera_Flip(c, 0, 1);
            m_flags &= ~0x10;
        }
    }
    CTimer_TimerWatcherV(count);
    return 0;
}

/* 0x00222c40 Gsx::Start() */
int Gsx_Start(void)
{
    sceGsResetGraph(0, vmode.mode, vmode.inter, vmode.ffmode);
    sceGsSyncPath(0, 0);
    ClearLocalMemory();
    sceGsSyncPath(0, 0);
    m_flags = (m_flags & ~0x20) | 0x20;
    sceGsSyncVCallback(cbVSync);
    return 1;
}

/* 0x00222cc0 Gsx::SetRenderTarget(sceGsDrawEnv1*)  -- copies the 16 qwords into RenderTarg and
 * mirrors every (data,addr) pair into GSRegister[addr] so later code can read shadow regs. */
/* 0x00222e50 Gsx::SetRenderTarget2(sceGsDrawEnv2*) -- same for env2 (RenderTarg2) */

/* 0x00222fe0 Gsx::GetBPPtoPSM(bpp, z) */
int Gsx_GetBPPtoPSM(int bpp, int z)
{
    switch (bpp) {
    case 32: return z ? 0x30 /*PSMZ32*/  : 0x00 /*PSMCT32*/;
    case 24: return z ? 0x31 /*PSMZ24*/  : 0x01 /*PSMCT24*/;
    case 16: return z ? 0x3a /*PSMZ16S*/ : 0x02 /*PSMCT16*/;
    case  8: return 0x13; /*PSMT8*/
    case  4: return 0x14; /*PSMT4*/
    default: return -1;
    }
}

/* 0x00223070 Gsx::SetInter30(int b)   returns old bit3 */
int  Gsx_SetInter30(int b) { int old = (m_flags & 0xf) >> 3; m_flags = (m_flags & ~8) | ((b & 1) << 3); return old; }

/* 0x002230a0 Gsx::SetFFMode(int ff, bool sub, int syncCount) */
void Gsx_SetFFMode(int ff, bool sub, u16 syncCount)
{
    m_flags = (m_flags & 0x3f) | ((ff & 1) << 6) | (sub << 7);
    m_syncCount = syncCount;
    if (m_pActiveCamera) m_pActiveCamera->mode = (m_pActiveCamera->mode & ~2) | ((ff & 1) << 1);   /* camera+0x08 bit1 */
}

/* 0x00223110 Gsx::DrawSync(int,int timeout)
 * Waits for VIF1 DMA then GIF DMA then GIF path.  Returns 1 on timeout. Uses RCNT3 (HCount) to budget
 * the remaining timeout between the two DMA waits. */
int Gsx_DrawSync(int mode, int timeout)
{
    u32 t0 = ((u16)RCNT3 < HCount ? RCNT3+0x10000 : RCNT3) - HCount;
    if (DmaMan_DmaSync(1 /*VIF1*/, timeout)) return 1;
    if (timeout) { timeout -= (now_hcount() - HCount) - t0; if (timeout < 0) timeout = 1; }
    if (DmaMan_DmaSync(2 /*GIF*/, timeout)) return 1;
    return sceGsSyncPath(0, 0);
}

/* 0x00375e50 Gsx::GetHCount() -> RCNT3 - HCount (wraps at 0x10000) */
