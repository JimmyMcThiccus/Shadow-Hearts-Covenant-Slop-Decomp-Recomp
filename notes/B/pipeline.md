# Section B — per-frame graphics data flow (JP SLPM_602.19, evidence in decomp/B/*.c)

Everything below is exact to the JP demo unless marked *(inferred)*.  Rust mirror: `port/crates/sh2_gfx` (`world.rs`, `packet.rs`,
`dma.rs`, `gs.rs`, `camera.rs`, `sprite.rs`, `renderer.rs`).

## 0. Hardware setup (CApp::InitScreen 0x003d75a0, Gsx::Open/Start)

* `Gsx::Open(512, 448, fbBpp=24, zBpp=24, mode=0x21)` → vmode: mode=1 (interlace), inter=2 (NTSC), ffmode=0 (FIELD), frame PSMCT24 (0x01),
  Z PSMZ24 (0x31).  `Gsx::Start` resets the GS, clears all 4 MB of VRAM (`ClearLocalMemory`) and registers `cbVSync` with `sceGsSyncVCallback`.
* The game camera is `GsxCamera::Create(0,0,0,0x18,flags)` = 512x448, CT24 frame + Z24.  Default view: `SetViewMatrix(scrz=1200, ax=0.8, ay=0.9333, 1.0, 1.6777e7)`,
  `nearZ=0.1`, `farZ=30000` (GameOver::GameOver, JP 0x003abea0; other SetViewMatrix callers: JRing::Initialize, LSDCam::setCameraData, openingMessage::changeDispMode, CFieldSocket::WakeUp — values not compared).
* VRAM map (blocks of 256 B): frame0 `0x0000`, frame1 `0x0e00`, Z `0x1c00`, free texture/work area from `0x2a00`, CLUT arena (`ClutAdressControl`) `0x3eef`..`0x3fef`
  (64 slots x 1 KB).  Because the frame/Z buffers are 24-bit, the **top byte of every 32-bit word is unused**; model/menu textures live there as
  PSMT8H (0x1b, 8-bit indices at bits 24-31) and PSMT4HH (0x2c, nibble at bits 28-31).  That is why `P2GetBPPtoPSM` and `Texture::CreateData` use the *H* formats.
* Coordinates: GS window space, 12.4 fixed point; the 512x448 screen is centred on (2048,2048) → draw env `XYOFFSET = ((2048-256)<<4, (2048-224)<<4)` = (0x7000, 0x7200)
  (hence the constants `0x7000/0x7200` and `+1792.0/+1824.0` floats in the sprite code).  Z is 24-bit; `GsxCamera::zmax = 2^24-1` (or arg/2 after SetViewMatrix).

## 1. Main loop (CApp::Run, JP 0x003d7730) — the frame pipeline

```
FlipBuffer(cam0)                      ; once at start: send camera render-target packet (draw env) on VIF1
WorldGetPacket()                      ; build the first chain
loop:
  Gsx::m_flags |= 0x20                ; "frame in flight" (blocks vsync flip)
  if camera:
     World::BeginUpdate()             ; ClearRaster() if cam.flags&4 ; changebActiveFlg(): clear per-prim flags, m_Env ^= 1
     World::WorldRender()             ; FlushCache; DmaMan::DmaSend(VIF1, &buf[bufIdx])   <- kicks the chain built LAST iteration
     World::EndUpdate()               ; bufIdx ^= 1
  CPoller(0x60).Polling()             ; system objects (SSHSys)
  if !paused: CPoller(0x48), CPoller(0x54).Polling()   ; all game objects: they create/move/hide VIF1Prims, call setZvolume, AddOT...
  m_pAppFunc()                        ; optional one-shot hook (CScrCapture::UpdateSys)
  World::WorldGetPacket()             ; ask every prim for its packet, build the DMA chain into buf[bufIdx] (the NEW idx)
  ScreenBright::Draw()                ; DrawSync; [pre packet]; request ScreenBright packet on VIF1 (NOT in the OT)
  sceGsSyncPath; delayed deletes; capture (CaptureOut = GsxFrameBuf::StoreImage)
  Gsx::m_flags: clear 0x20 (set 0x10 "flip pending" if forced)
  Gsx::DrawSync()                     ; wait VIF1 DMA, GIF DMA, GS path
  wait vblank(s): m_syncCount (1=60Hz, 2=30Hz) else GsxForceFlip(); HCount=RCNT3
```
cbVSync (vblank interrupt): `VCount++; if (!(m_flags&0x20)) { cam=active; if cam double-buffered && (!(m_flags&0x80) || (m_flags&0x10)) Flip(cam,false,true); clear 0x10 }`
→ the page flip happens in the vblank handler after the frame has been fully drawn (`DrawSync`) and not while a frame is still in flight.

Double buffering of *packet memory*: `VIF1Prim::m_Env` (byte @0x0040abb0) toggles once per frame in `changebActiveFlg` (called from `BeginUpdate`, i.e. right after the previous
chain is kicked).  Every prim owns two packet buffers and writes the one selected by `m_Env & 1` in `getPacket`, so the buffers the GS is still reading are never touched.
`World::bufIdx` double-buffers the DMA *chain* itself the same way (buf[bufIdx] is built while buf[bufIdx^1] is in flight).  Net latency: logic of frame N is displayed after frame N+1's kick.

## 2. World (ordering tables)

* `World` = singleton `CApp::m_World` (0x0042bf10, 0x4120 B): 16 layers (0 = drawn first … 15 = last), each a doubly-linked list of `VIF1PrimChain{next,prev,VIF1Prim*}`
  **sorted by descending `VIF1Prim::zvolume`** (s16 at +0x0e; equal z keeps insertion order).  `AddOT(layer, prim)`, `AddDoubleOT`, `AddOTBefor/After(ref,prim)`, `ReleaseOT(prim)` (removes from all layers),
  `setZvolume` → `changeZvolume` re-sorts in every layer holding the prim unless flag bit4.
* `WorldGetPacket`: `p = buf[bufIdx]`; for each layer with `layerCount>0` → `LayerGetPacket(layer, p)`; finally write `0x70000000` (DMA END).
* `LayerGetPacket`: for each node (skip if `flags&8`): `pkt = prim->vtbl[1]()` (virtual `getPacket`, may rebuild its packet), `pass counter (flags bits1-2) = (+1)&3`;
  if `pkt`: if `prim->pEnv && World.lastEnv != prim->pEnv` emit `{0x50000000, pEnv}` (DMA **call**, qwc 0) and remember it; emit `{0x50000000, pkt}`.
  `lastEnv` is *not* reset between frames (only in the ctor).  Each emitted tag is one qword `(tag, addr, 0, 0)`.
* A prim's packet is a sub-chain terminated by `ret` (`0x60000000`), so the whole frame is `call/ret` nesting depth 1 (texture-upload chains called from inside a prim packet are depth 2 — the DMAC stack holds 2).
* Rust: `World::world_get_packet(&mut PrimStore) -> DrawList` (same ordering, env elision, pass counters); `DrawList::execute(GsInterpreter)`.

## 3. Packet formats (GIF/VIF1/DMA)

DMA tag word0 = `qwc | id<<28` (ids: 0 refe, 1 cnt, 2 next, 3 ref, 4 refs, 5 call, 6 ret, 7 end), word1 = `addr`, words2/3 = two VIF codes (CHCR=0x41: TTE=1, mode=chain).
Typical prim packet block (`P2Pkt::AddRefe/AddCnt/AddRet`): `tag(qwc=n, id) | VIF FLUSHA (0x13000000) | VIF DIRECT (0x50000000|n)` then n qwords of GIF data.
VIF codes seen: FLUSHA 0x13, FLUSH 0x11, DIRECT 0x50, DIRECTHL 0x51, MSCAL/MSCNT/UNPACK/MPG for VU1 (models only).
GIF data used by the 2D layer:
* `A+D` blocks: tag `nloop=n, EOP, PACKED, NREG=1, REGS=0xE`, then `(data64, addr)` qwords.  Register addresses used: TEXFLUSH 0x3f, TEX0_1/2 0x06/07, TEX1 0x14/15,
  CLAMP 0x08/09, MIPTBP1/2 0x34/0x36, ALPHA 0x42/43, TEST 0x47/48, FRAME 0x4c, ZBUF 0x4e, XYOFFSET 0x18, SCISSOR 0x40, FOGCOL 0x3d, BITBLTBUF 0x50, TRXPOS 0x51, TRXREG 0x52, TRXDIR 0x53.
* sprites: `GIFtag 0x6400000000008001`-style REGLIST: `{PRIM, RGBAQ, UV|ST, XYZF2, UV|ST, XYZF2}` (P2Sprite, ScreenBright uses `{PRIM,RGBAQ,XYZF2,XYZF2}`), PRIM bits: SPRITE=6, TME 0x10, ABE 0x40, FST 0x100.
* prim2D quads: REGLIST 14 regs `{PRIM,NOP, 4x{RGBAQ,UV,XYZF3|XYZF2}}`, PRIM=0x15c (TRISTRIP|IIP|TME|ABE|FST); 3rd and 4th vertex use XYZF2 (kick) → 2 triangles.
* blend modes (`ALPHA_1` value): 0x44 normal `(Cs-Cd)*As+Cd`, 0x48 additive `Cs*As+Cd`, 0x42 subtractive `(0-Cs)*As+Cd`.  Default alpha test `TEST_1=0x3000d` (ATE, GREATER 0, ZTE ztst=3).
* texture upload: `BITBLTBUF(dbp,dpsm,dbw)`, `TRXPOS(x,y)`, `TRXREG(w,h)`, `TRXDIR=0`, `GIFtag IMAGE nloop=qwc` followed by a DMA `ref` to the pixel data (CVif1Packet::RefLoadImage emits 8 qw: 6 setup + REF).
* screen copy: same with `TRXDIR=2` (local→local) — used by P2Filter / ExpansionTexture / FrameTexture / ScreenTexture / CScrCapture.
* render target switch (`GsxCamera::GetRenderTargPkt`, 18 qw): `GIFtag nloop=17 A+D`, `FRAME_1,ZBUF_1,XYOFFSET_1,SCISSOR_1,PRMODECONT,COLCLAMP,DTHE,TEST_1`, same 8 for ctx 2, `FOGCOL`.
* models (Section C): VU1 microprogram packets (`UNPACK` vertex/skin data + `MSCAL`) — *not* GS-ready; `PacketItem::Model` is the Rust hook.

## 4. Re-implementation guidance for a modern GPU

1. Keep `World`/`VIF1Prim` semantics (layers 0..15, descending z, env elision is only an optimisation — drop it).
2. Replace DMA with `DrawList` of `Arc<Packet>`; 2D prims already emit GS-ready GIF (use `GsInterpreter` to turn them into `DrawPrim`s → `RenderBatch`es);
   textures: decode with `texture.rs`, key by what the GS saw (`TexKey{tbp0,psm,cbp,..}`) — or better, key directly by the owning `Texture` object since uploads are done once at load.
3. Colours: GS RGBA is 0..0x80 = 0..1 (`gs_alpha_to_u8`); vertex colour modulates the texture (TFX=MODULATE) and is `x2` saturated in hardware: `out = clamp(tex*vtx/128)`.
4. Z is 24-bit with `ZTST`; the 2D layer mostly draws with `ztst=3`(GREATER vs the camera's `zmax` Z) so sort by layer/z-volume only.
5. Frame-buffer read-back effects (`TRXDIR=2` copies, FRAME/FRAME_TEX gTextures at tbp 0 / 0x2a00) → render-to-texture of the previous frame.
6. Light/shadow: `LightControl::getLightMatrix` → up to 3 directional lights + ambient (see light.rs); `ShadowControl` is a projected-shadow pass into an offscreen texture (tbp 0x2a00).
7. Resolution/aspect: view is 4:3 (`tan_half = (W/2)/(scrz*asp)` → 0.2667 x 0.2); 512x448 internal; field-offset jitter (`GsxCamera::Flip` half-offset) can be ignored.

## 5. sce* SDK usage per class (not decompiled)
Gsx: sceGsResetGraph/ResetPath/SyncPath/SyncVCallback, sceDmaReset/GetChan/Send/SendN/Sync.  GsxCamera: sceGsSetDefDispEnv/DrawEnv/DrawEnv2/Clear, sceGsPutDispEnv, sceGsSetHalfOffset, sceGsSyncV, sceVu0ViewScreenMatrix, sceVu0ViewClipMatrix, sceVu0InversMatrix, FlushCache/iFlushCache.
GsxFrameBuf/CScrCapture/FrameTexture: sceGsSetDefStoreImage, sceGsExecStoreImage. GsxSpline: sceVu0ScaleVectorXYZ/AddVector. CVif1Packet/Texture: sceVif1PkTerminate.
IPUTexture: sceIpuInit/Sync/RestartDMA/StopDMA + IPU regs. LightControl: sceVu0TransposeMatrix. P2Filter/prim2D/primSprites: libm sinf/cosf/asinf.
