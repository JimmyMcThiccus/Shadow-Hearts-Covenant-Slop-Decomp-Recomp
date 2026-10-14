/* Font.c -- Font / FontDraw / FontItem / PluralFontItem / MenuFont  (CFontDraw.cpp, CMenuFont.cpp)
 * JP SLPM_602.19 0x0026c7c0..0x00270360, 0x00272c90..0x00273dc0, 0x0027fda0.., 0x00283b70.., 0x002851a0..
 *
 * ===== Font file (header at blob start; 4 font slots `Font::fontWork[4]`, 0x28 bytes each @0x00421550) =====
 *   +0x00 u8 cellW(=advance of full-width glyph?)  +0x01 u8 lineHeight   +0x02 u8 nPalettesLog (<2 => 4-colour clut, else 8)
 *   +0x04 u16 fullGlyphBytes (e.g. 0x24 = 12x12 @2bpp)   +0x06 u16 halfGlyphBytes (e.g. 0x18)
 *   +0x08 u8 nHalf?   +0x09 u8 proportional flag   +0x0c u16 nRanges
 *   +0x10 u32 off -> CLUT  (RGBA8, 4 colours per palette, alpha 0x80; many palettes = text colours)
 *   +0x14 u32 off -> full-width glyph bitmaps      +0x18 u32 off -> range table {u16 start,u16 count}[nRanges]
 *   +0x1c u32 off -> second glyph bitmap block / width table     +0x20.. width tables (2 bytes/glyph: {lsb-bearing, advance})
 *   glyph bitmaps are 2 bits per pixel, 4 px per byte, LSB first, rows padded to bytes.
 *   Glyph index for SJIS code c (hi,lo):  hi'= hi>=0xe0 ? hi-0x40 : hi ;  lo' = lo>=0x80 ? lo-1 : lo ;  idx = (hi'-0x81)*0xbc + (lo'-0x40)
 *   (GetFontCode 0x00272ec0).  Codes < 0x100 are half-width: (code-0x20).  Range table maps idx -> sequential glyph number.
 *   Verified header example (SAVELOAD.PKB entry 'fnt' @0x1fe40): 0c 0c 10 00 | 24 00 | 18 00 | .. | 0b 00 (11 ranges) | clut@0x20 | glyphs@0x750
 * Font::CreateFont(slot,blob) 0x00272c90: ref-counted; fills fontWork; FontDraw::CreateClut(slot) (ClutRaster 16x16/8x2, 8bpp -> ClutSort)
 * Font::GetFont(code, FontRect*) 0x00273050 -> glyph bitmap ptr + rect{+0 x,+2 y,+4 w,+6 h,+8 lsb,+10 adv}
 * Font::SetFont(CImage* dst, glyph*, FontRect*, palOffset, shadow) 0x00273470 : expands 2bpp -> dst 8bpp (value+pal) or 4bpp (two px/byte, odd x handled)
 *
 * ===== FontDraw : MenuObj + MenuPacket (size 0x40) =====
 *   Renders a string into a 2-buffer CImage (PSMT8H or PSMT4HH), uploads it with a RasterPacket, and exposes a 512x?? texture for a sprite.
 *   +0x28 psm  +0x2c RasterPacket[2]  +0x30 ClutRaster*  +0x34 CImage[2]  +0x38/3a/3c x,y,line cursor  +0x3e flags (bit0 dbl buf, bit1 cur buf, bits2.. bpp)
 *   Text mini-language (GetRect 0x0026cea0 / GetMacro 0x0026e240):  '$' = newline ;  '%' + cmd :
 *        I/i n  = inline icon n  (0x07)   W/w n = wait n*100 (0x04)   T/t n = timer n*100 (0x05)   P/p n = pause n*4 (0x02)   else cmd 0
 *   GetCode 0x0026e170: byte <0x80 or in 0xA0..0xDF => single byte; else 2-byte SJIS.
 *   Order(MenuMessage*, char*) 0x0026e9d0 / OrderMessage(MenuText*,...) 0x0026f780 / GetRaster 0x0026c930: layout+render engine
 *   SetShadow4/SetShadow8 (CImage*, FontRect*, ..) 0x0026d1c0/0x0026dd30 : drop-shadow pass for 4bpp / 8bpp targets (offset copy with darker palette idx)
 *   Update(...) 0x0026ff60 : per frame builds DMA: [ref image upload chain][ref clut][A+D: TEXFLUSH, TEX0_2(clut mode), TEST?, ALPHA=0x44...]
 * FontItem / PluralFontItem / MenuFont / MenuFontItalic : Section F widget wrappers (kept in notes/B/Font.md).
 */
