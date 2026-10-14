# Gsx, GsxFrameBuf, GsxRaster, GsxSpline, GsxCamera, World, VIF1Prim, VIF1PrimChain  (libgsx.cpp, JP 0x002228c0..0x00227d54)

See decomp/B/Gsx.c, GsxFrameBuf.c, GsxCamera.c, World.c and pipeline.md. Rust: camera.rs, psm.rs, world.rs.

## Gsx (static)
| addr | name | meaning |
|---|---|---|
| 0x0040ab94 | sys | singleton |
| 0x0040ab98/9c | ofsx/ofsy u16 | GS prim offset (12.4) used by MakeViewMatrix |
| 0x0040aba0 | HCount | RCNT3 at last flip |
| 0x0040aba8 | m_flags u32 | b0 open, b3 inter30, b4 flip pending, b5 frame in flight, b6 FF mode, b7 FF sub, b8 force flip |
| 0x0040abac | m_syncCount u16 | vblanks per frame |
| 0x00412e10 | vmode (GsxVMode 10 B) | mode,inter,ffmode,fbpsm,w,h,zen,zpsm |
| 0x00412e20 | GSRegister[0x70] u64 | shadow GS regs (SetRenderTarget) |
| 0x004131a0/0x00413220 | RenderTarg/RenderTarg2 | sceGsDrawEnv1/2 copies |

## GsxFrameBuf (0x10 B) / GsxRaster (0x18 B, +0x10 alias ptr)
`+0 u64 pack` (base:14, tbw:6, psm:6, tw:4, th:4, w:11 @35, h:11 @46; byte7 b1 static, b2 chain), `+8 vptr`. VRAM bitmap `m_tbl` (0x800 B @0x004132a0, 1 bit / 256 B block).
Tables: PageSizeTbl @0x003fd7c0, PSMtoBPPtbl @0x003fd8c0, BlkMapRefTbl @0x003fd8a0, BlkMapTblTbl @0x003f8030.

## GsxCamera (0x398 B; Ghidra struct `GsxCamera`)
| off | type | name |
|---|---|---|
| 0x000 | sceGsDispEnv(0x30) | pmode,smode2(+8 b1=FFMD),dispfb(+0x10),display(+0x18),bgcolor(+0x20) |
| 0x030 | u64+2xu32 | RT packet: dmatag(END,qwc),FLUSHA,DIRECT |
| 0x040 | GIFtag | NLOOP=0x11 A+D |
| 0x050/0x0d0 | sceGsDrawEnv1/2 (0x80) | frame,zbuf,xyoffset,scissor,prmodecont,colclamp,dthe,test |
| 0x150 | qword | A+D FOGCOL |
| 0x160 | sceGsClear (0x60) | rgbaq @0x180 = background colour |
| 0x1c0/0x200 | call packets (0x40) | env1/env2 re-send via ref |
| 0x240/0x280/0x2c0/0x300 | Matrix | frame, inverse(frame)=view, viewScreen, viewClip |
| 0x340/0x344 | GsxRaster* | frame, zbuf |
| 0x348/0x34a | u16 | width, height |
| 0x34c/0x350/0x354 | f32 | scrz, ax, ay |
| 0x360 | FVector | fogParam (0, near, 256/(far-near), 255) |
| 0x370/0x374 | f32 | nearZ, farZ |
| 0x378/0x37c | f32 | zmax, zmin |
| 0x380/0x384 | f32 | fogNear, fogFar |
| 0x388 | u8[4] | RGBA (set by GameOver) — fog/bg colour copy |
| 0x38c | u16[2] | fbp pages |
| 0x390 | u8 flags | b0 dbl-buf, b1 zbuf, b2 clear/frame, b3 sync disp, b4 flip latch, b5 capture |
| 0x394/0x395 | u8 | bufIdx, field |
Static `m_pActiveCamera` @0x0040abb4.  `CApp::camera` is the game camera (cam[0] of World).

## World (0x4120 B), VIF1Prim (0x14 B), VIF1PrimChain (0xc B): see decomp/B/World.c.
## Open questions
* exact sceVu0ViewScreenMatrix convention (inferred `screen = centre + (ax*scrz, ay*scrz)*xy/z`, 4:3 aspect check passes);
* `GsxCamera::flags` creation values used by the game (callers pass 0 in GameOver).
