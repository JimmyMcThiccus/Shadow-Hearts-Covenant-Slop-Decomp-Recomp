# Texture formats (Texture.cpp, ExpantionTexture.cpp, JRCTex, CImage, ClutRaster, MenuTexture, P2* blobs) → RGBA8

Decoders: `port/crates/sh2_gfx/src/texture.rs`.  Verified on real data: SAVELOAD.PKB menu texture (palette ramp), COMMON.PKB TIHD model textures (12 rendered; magic circles, glows),
and cross-checked against the independent decoder of Section C (`sh2_formats::model::TextureDef`).

**Universal rules**
* Pixel data = linear raster, top row first (the GS does the swizzle; files are NOT pre-swizzled). 4-bit: 2 px/byte, **low nibble first**.
* Palette = RGBA8 (PSMCT32), alpha 0x80 = opaque → `min(a*2,255)`.  16 or 256 entries.
* 8-bit palettes in files are in GS **CSM1 order**: logical colour `p` = `file[(p&~0x18)|((p&8)<<1)|((p&0x10)>>1)]` (swap bits 3,4; involution). Runtime-built palettes (`ClutRaster`, fonts) use `ClutSort` = same permutation (swaps the 0x20-byte blocks 1,2 of each 0x80).
* GS formats the engine uses: indexed data is uploaded as PSMT8H (0x1b)/PSMT4HH (0x2c) into the unused top byte of the 24-bit frame/Z buffers; 32-bit/IPU textures as PSMCT32 at block 0x2a00; CLUTs as PSMCT32 (CSM1, 16/256 entries) into the CLUT arena @0x3eef (64 slots x 1 KB, `ClutAdressControl::getAdress(i)=base+i*4`).

**1. Model texture (`_ModelTextureHeader`, magic 'TIHD' at +0, 0x20 B header)**
`+4 u16 w, +6 u16 h, +8 u8 fmt (&0x3f = bpp 4/8/32, 0x40 = IPU/MPEG-2 payload), +0xa u8 mipCount, +0xc u16 clutCount (0/16/256), +0xe u16 clutOffset, +0x10 u32 imageOffset, +0x14 u32 nextOffset (next mip level header / end of block),
+0x1c u16 alpha (A=(v&2) B=(v&0xc)>>2 C=(v&0x20)>>4 D=(v&0xc0)>>6 FIX=v>>8 → ALPHA_1), +0x1e u8 alphaTestRef (ATE, ATST=GEQUAL), +0x1f AFAIL`.  Mip levels are further headers of the same layout chained by +0x14; level n GS address = cumulative `w*h/64` blocks.
`TextureAnim` (animated sub-rect; header in model's TXAH table): `+0x10 u8 texIndex, +0x11 u8 frames, +0x12/14 u16 frameW/H, +0x18 u16 stride, +0x1a u16 dstX, +0x1c u16 srcY-inset, +0x20 u16 size/16`, frames follow at +0x30.
IPU textures: payload is MPEG-2 intra frames (w/16*h/16 macroblocks) decoded by the IPU → RGBA32; use any MPEG-2 I-frame decoder.

**2. MenuTexture image (primLayer/prim2D/primTex/FontDraw/Menu*)** — verified
`{u16 w; u16 h; u8 bpp(4|8); u8 hasClut; u16 clutCount; u32 pixOff; u32 clutOff}` offsets relative to header; pixels linear T4HH/T8H; palette RGBA8 (CSM1 for 256).  Containers: PKB-like bundles `{u32 count; u32 total; {char ext[4]; u32 off}[count]}` (see SAVELOAD.PKB; `primTex::getData/GetFileEntry`).

**3. P2 blobs**: P2TexTex `{w,h,u8 bpp@4,u16 clut@6,u32 imgOff@8,u32 clutOff@0xc}`; P2GraTex `{w,h,..,bpp-code@8 (1=8,2=4,3=24),clutCount@0xc}` clut at +0x10, image after `((clut+3)&~3)*4` bytes; CImage (memory) `{u8 bpp,u8 flags,u16 w@4,u16 h@6,pix*@8,pal*@0xc}`.
**4. JRCTex**: `{u32 ?, u16 w@4, u16 h@6, u8 fmt@8 (&7: 0=4bit,1=8bit), u16 clutEntries@0xa, u16 nPalettes-1@0xc}` then palettes then pixels.
**5. Fonts**: 2 bpp glyphs (4 px/byte LSB first), SJIS-indexed (`GetFontCode`: (hi'-0x81)*0xbc+(lo'-0x40)), header in decomp/B/Font.c; CLUT = 4-colour palettes (RGBA8) at +0x20. Text codes: `$` newline, `%I n` icon, `%W n` wait, `%T n` timer, `%P n` pause.
**6. GS address swizzle** (only needed to read PCSX2 VRAM dumps): `psm::ct32_word_addr` (PSMCT32 only).
Open: byte-level layout of font +0x18/+0x1c/+0x20 tables not fully verified; IPUTexture decode path (frames, buffers) described only structurally.
