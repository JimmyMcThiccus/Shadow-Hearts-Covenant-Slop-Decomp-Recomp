/* prim.c -- primFade, primPacket, prim2D, primSprite(s), primLayer, primTex, primWin, primCursor, primModel
 * JP SLPM_602.19 0x00399da0..0x003a7cf8  (source file ybase? / prim*.cpp)
 *
 * High-level 2D UI primitive layer built on VIF1Prim + MenuTexture.  Menu/battle code (sections F,H) use it.
 *
 * ---- primFade (16 B) -----------------------------------------------------------------------------
 *   +0 state(0 idle,1 fading in,2 out) +4 level (float? init 1) +8 counter +0xc total
 *   fadein(n): state=1,total=n,counter=0,level=1     fadeout(n): state=2,total=counter=n,level=0
 *   fadePolling(): out: counter--, level=counter/total, idle at 0 ; in: counter++, level=counter/total, idle at total ; returns level
 *
 * ---- primPacket : DelayDeleteObject  (base of prim2D-like items, size 0x130+) ------------------------
 *   +0x0c primFade fade
 *   +0x1c primLayer* layer +0x20 int slot     (set by setDisp -> primLayer::addPrim)
 *   +0x24/+0x28 QWD* packet buffers (A/B by m_Env&1)    +0x2c primPacket* next (intrusive list in layer slot)
 *   +0x30 u8 sizeSet  +0x31 u8 attached   +0x40/+0x54 scale x/y  +0x70/+0x74 pos x/y   +0x80..+0x8c rgba (0..0x80 each, 0x7f default)
 *   +0x90 u32 packet qwords  +0x94 blendMode (0 normal,1 add,2 sub)  +0xa4 centerMode (0 TL,1 BL?,2 centre,3 top-right?,4 BR)
 *   +0xb0/+0xb4 size w/h  +0x100..+0x10c uv (x16)  +0x110 Matrix* parent  +0x120 centre offset
 *
 * ---- prim2D : VIF1Prim + DelayDeleteObject  (size 0x254) --------------------------------------------
 *   Rotated textured quad.  Ctor(layer): AddOT(layer, this);  two 0x40-qword packet buffers (+0x88/+0x8c, m_Env&1).
 *   +0x20 primFade  +0x30 file idx  +0x38 MenuTexture tex (0x40 B)  +0x4c ClutRaster*  +0x50 tex0 base  +0x6c transfer-chain addr
 *   +0x78 loadRequested +0x79 loaded +0x7a needUpload  +0x110..0x138 per-corner rgba (7f default) +0x13c packet size (0x40)
 *   +0x144 blend 0/1/2   +0x150 u64 extra reg  +0x160 rot +0x164 rotspeed +0x168 xscale +0x170 pos vec +0x180 centre vec
 *   +0x190/+0x194 w/h  +0x1b0 screen centre (1792+..., 1824+...)  +0x1c0.. 4 transformed corners  +0x200 uv (x16)  +0x210 2x2 rot matrix  +0x250 parent Matrix*
 *   getPacket() 0x0039b170: [call tex-upload chain once][call CLUT chain] then
 *        cnt(3){A+D NLOOP=2: TEXFLUSH, TEX0_1 = tex0 | CLUT flags(GetClutFlag(0,1))}
 *        cnt(0xc){A+D NLOOP=3: TEST_1=0x3000d (ATE, GREATER, ref0, ZTST GREATER?), ALPHA_1 = blend(0x44/0x48/0x42), PRIM...}
 *        GIFtag 0xe400000000008001 (REGLIST NREG=14): PRIM=0x15c (TRISTRIP|IIP|TME|ABE|FST) then 4 x { RGBAQ, UV, XYZF3|XYZF2 } -> 4-vertex strip
 *        ret
 *      colours are multiplied by the fade level (fadePolling) in calcPos.   Z = camera->zmax (+0x378).
 *   calcPos() 0x0039bd50: rot += rotspeed; builds 2x2 matrix (cos*sx, -sin*sx / sin*sy, cos*sy) [x parent Matrix], rotates the 4 corner offsets,
 *        adds screen centre, scales x by +0x168.
 *
 * ---- primSprite / primSprites (batched sprites, N quads in one packet), primLayer (texture slot table of 0x80-byte Layer records,
 *      one DMA chain per layer: [tex upload][CLUT][TEX0 reg][ref each prim's packet]) -------------------
 *   primLayer::initialize(file, n): n Layer slots, OT layer 6.   setTex(slot, fileIdx, clutIdx): MenuTexture.Create(T8H(0x1b)|T4HH(0x2c))
 *   getPacket(): for each slot: mTransTex(...) then call to head primPacket chain.
 *
 * ---- primTex (atlas; size 0x4a0..): file blob (PKB-like {count,size,{ext[4],off}[]}) of MenuTexture images; up to 0x60 window textures,
 *      uv grid (per-slot block w/h at +0x488), 8 FontDraw text areas (stride 0x14 @+0x490..).  getUV(slot,col,row) = (col*bw+1, row*bh+1, (col+1)*bw, (row+1)*bh)
 *      NOTE the +1 texel inset on u0/v0.
 * ---- primWin (menu window built from MenuPolygon/MenuText, polling/fade/scroll), primCursor, udScrollMark, dispSaveFile/dispTime/dispCash:
 *      pure UI logic on top of the Menu* toolkit (Section F); only the draw-primitive plumbing above is Section B.
 * ---- primModel : CPolObj wrapper for a Model + motion (CBFunc loads, setMotion, Polling) -> Section C
 */
