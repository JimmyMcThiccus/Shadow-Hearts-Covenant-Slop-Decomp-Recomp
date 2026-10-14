# Remaining Section B classes — summaries (full detail in decomp/B/*.c)

* **P2Pkt/P2Sprite/P2Clut/P2Filter/P2MakeBitBltPkt/SetFullSprite** → decomp/B/P2.c; Rust `sprite.rs::P2Sprite` (byte-compatible packet builder, tested through `GsInterpreter`).
* **primFade/primPacket/prim2D/primSprites/primLayer/primTex/primWin/primCursor/primModel** → decomp/B/prim.c; Rust `sprite.rs::prim2d_quad_gif`, `BlendMode`.  primWin/primCursor/dispTime… are UI logic over Menu* (Section F).
* **FontDraw/Font/FontItem/PluralFontItem/MenuFont** → decomp/B/Font.c; Rust `texture.rs::{font_code_sjis, decode_glyph_2bpp, FontHeader}`.
* **LightData/LightControl/LightServerHandler** → decomp/B/Light.c; Rust `light.rs` (pool, priority tree order, getLightMatrix without cross-fade).
* **ShadowControl/ExpansionTexture/ScreenTexture/WriteTexture/FrameTexture/CScrCapture/CineMask/ScreenBright/JRCTex** → decomp/B/Misc.c; Rust `sprite.rs::ScreenBright` (+ pipeline test).
* **GetPSMtoBPP/GetBufferWidth/GetTexWidth/GetTexBit/MakeFlags** → decomp/B/GsxFrameBuf.c; Rust `psm.rs` (MakeFlags/VRAM bitmap not ported: irrelevant on a modern GPU).
Not decompiled in depth: ShadowControl::getPacket (0x11ec B), WriteTexture/ScreenTexture::getPacket, FontDraw::Order/OrderMessage/GetRaster, MakeFlags, PluralFontItem::Update, primWin::*.
