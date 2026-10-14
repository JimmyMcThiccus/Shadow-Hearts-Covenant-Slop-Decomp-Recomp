/* GsxFrameBuf.c -- GsxFrameBuf / GsxRaster / GsxSpline / MakeFlags / PSM helpers
 * JP SLPM_602.19 0x002231e0..0x00225370, 0x002234c0..0x00223d30 (libgsx.cpp)
 *
 * GsxFrameBuf: allocator for GS local memory (4 MB = 0x4000 blocks of 256 B).  A single global
 * bitmap  m_tbl__11GsxFrameBuf[0x200] (u32, 1 bit per block, 0x00413 2a0) tracks usage.
 * Object is 16 bytes: vtable at +8.
 *
 *   +0x00 u64 pack  (a TEX0-like bitfield, NOT a real TEX0):
 *          bits  0..13 base      = block address (TBP-style, unit = 64 words = 256 bytes)
 *          bits 14..19 tbw       = buffer width in 64-px units
 *          bits 20..25 psm       = GS PSM
 *          bits 26..29 tw_log2   = ceil(log2(width))
 *          bits 30..33 th_log2   = ceil(log2(height))
 *          bits 35..45 width  (11 bits)       (u16 at +4 : (w & 0x7ff) << 3)
 *          bits 46..56 height (11 bits)
 *          byte +7: bit1 = "static" (CreateS with mark==false: not recorded in m_tbl, never released)
 *                   bit2 = "chain" (allocated through MakeFlagsChain: linear run of blocks)
 *   +0x08 vtable: [0]=dtor? [1]=Create (slot at +0x08/+0x0c?), [..+0x1c]=Release
 *
 * GsxRaster : GsxFrameBuf { +0x10 void* alias_of  (non-null => this is a sub-view, Release just clears) }
 */

/* 0x002234c0 GetPSMtoBPP(psm) -> bits per pixel.  Table PSMtoBPPtbl @0x003fd8c0 (13 pairs):
 *   00:32 01:24 02:16 0a:16 13:8 14:4 1b:8 24:4 2c:4 30:32 31:24 32:16 3a:16 ; else -1          */
/* 0x00223510 GetBufferWidth(psm) -> page width in px from PageSizeTbl (24bpp treated as 32) */
/* 0x00223580 GetTexWidth(n)  -> next power of two >= n  (min 1)
 * 0x002235c0 GetTexBit(n)    -> ceil(log2 n)                                                    */

/* PageSizeTbl @0x003fd7c0, 4 rows of 8 bytes:  { bpp, 0, pageW, pageH, blkCols, blkRows, blkW, blkH }
 *      32bpp: 64x32 page, 8x4 blocks of  8x8
 *      16bpp: 64x64 page, 4x8 blocks of 16x8
 *       8bpp:128x64 page, 8x4 blocks of 16x16
 *       4bpp:128x128 page,4x8 blocks of 32x16
 * BlkMapRefTbl @0x003fd8a0: {psm, tableIdx} -> BlkMapTblTbl[idx] (6 block-index tables: CT32,Z32,CT16,CT16S,Z16,Z16S) */

/* 0x00223600 MakeFlags(GS_PSM psm, int w, int h, uint* nwords)
 *   Builds (new[]) a bitmap of the GS blocks a w x h surface of `psm` occupies, as seen from a
 *   page-aligned origin: rows of full pages -> 0xffffffff words; a partial last column/row uses
 *   masks computed from BlkMap tables.  *nwords = pages_x * pages_y.  PSMT4HL/HH/T8H (0x24,0x2c,0x1b)
 *   are treated as PSMCT32.                                                                       */
/* 0x00223d30 MakeFlagsChain(psm, nblocks) : linear bitmap, ceil(n/32) words (last word partial)  */

/* 0x00223290 GsxFrameBuf::GetFreePtr(bool aligned, uint* flags, uint nwords)
 *   First-fit search in m_tbl for a free run matching `flags` (aligned: whole 32-block rows;
 *   else slides bit by bit).  Returns block index or -1 (prints error).                           */
/* 0x00223400 MarkTbl(int blk, uint* flags, uint n)  m_tbl |= flags << (blk&31) ...               */

/* 0x00223e50 GsxFrameBuf::Create(bool align, GS_PSM psm, uint w, uint h)
 *   Release(); flags=MakeFlags(psm,w,h,&n); blk=GetFreePtr(); MarkTbl(); fill pack:
 *      base=blk, tbw=(align_up(w, pageW))>>6, psm, tw=log2(pow2(w)), th=log2(pow2(h)), w, h.
 * 0x00224040 Create(bool, psm, uint nbytes?) -- "chain" variant: n = (len+31)>>5, byte7 bit2 set
 * 0x00224170 CreateS(bool mark, uint block, psm, w, h) -- fixed address (no search); fails if block+n > 0x4000
 * 0x00224380 CreateS(bool mark, uint block, psm, len)
 * 0x002244f0 CreateClone(bool, GsxFrameBuf* src) -> vcall Create(.., psm(src), w(src), h(src))
 * 0x00224530 Release()  : clear the same bit pattern in m_tbl; zero the 16 bytes (skipped if static)
 * 0x002246d0 GetBufHalf(): block address of the 2nd field/half = base + ceil(h/2/blkH)*ceil(w/blkW)... 
 * 0x002247c0 Clear(uint colour): builds on-heap DMA chain (0x20f0 B): fills 8 KB of colour, then
 *      GIF A+D: BITBLTBUF(dbp,dpsm)  TRXPOS(0) TRXREG(width,1) TRXDIR(0 host->local), then REF 0x800-qw blocks
 *      repeated to cover the whole surface; second part sets BITBLTBUF/TRXPOS/TRXREG/TRXDIR(2 local->local)
 *      for tiled copy doubling.  Sent on VIF1 (Request) + DmaSync(1).
 * 0x00224b40 StoreImage(void* dst, _tagSRect*) : sceGsSetDefStoreImage + sceGsExecStoreImage (VIF1 CHCR=0 during)
 */
