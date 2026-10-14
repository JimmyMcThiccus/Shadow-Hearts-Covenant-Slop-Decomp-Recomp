# Model file format (`SSH1.01a`, PKB entry type `mdl`)

Recovered from `Model::create(unsigned char*)` (JP `create__5ModelFPUc` 0x0023e710), `Model::setAtomic`
(0x0023e510), `Frame::Cleate` (0x002436d0), `*Atomic::Cleate` (0x00242920, 0x0024d360, 0x0024e6a0, 0x0024f810, 0x00250e30, 0x00255330, 0x00256690, 0x0025ad00, 0x0025b040),
`Texture::CreateData` (0x002474e0), and verified by parsing **1,438 real models** (all of COMMON/FIELD/BTLDATA/
EFFECT/MENU/SHOP/SOLOMON.PKB) and rendering a textured skinned character (BTLDATA.PKB 0x1bf2860) and a monster
(FIELD.PKB 0x1dd2820).  Rust parser: `port/crates/sh2_formats/src/model.rs` (`Model::parse`).

`checkModelVersion` (JP 0x00200430) is **not** a model-file check: it opens `rom0:ROMVER`, reads the PS2 BIOS
version string and returns `atoi(date) > 0x1315670`.  It only gates a hardware workaround.

The loader maps the file in place (the engine never copies it), so every section is 16-byte aligned relative to the
(16-byte aligned) start of the file.  Little endian.  A PKB package (`u32 count, u32 size, {type[4], u32 off}*count`) holds
`mdl` and `anm` entries side by side; the model's motions are the `anm` entries of the same package.

## File header (0x30 bytes)

| off | type | meaning |
|---|---|---|
| 0x00 | char[8] | `"SSH1.01a"` (checked with `memcmp(...,8)`) |
| 0x08 | u32 | flags. Observed `0x00110004` / `0x000e0004`. Byte 10 = geometry flags: `&3 != 0` model has vertex data, `&4` = float ("Pack2") vertex layout |
| 0x0c | u32 | offset of `ATHD` atomic section |
| 0x10 | u32 | offset of `FRHD` frame section (always 0x40) |
| 0x14 | u32 | 0 (a `SQHD` motion could follow the frames: `createMotion` is called on the byte after the last frame, no shipped model embeds one) |
| 0x18 | u32 | offset of `TXHD` texture section, 0 / -1 = none (character models keep their textures in separate `bin` entries) |
| 0x1c | u32 | offset of `BBHD` bounding-box table = end of the atomic section |
| 0x20 | u32 | blend-shape block (`BlendShapeControl::create`, `BSAH`): 0 in every JP model; **used by 2 US retail models** (BTLDATA/CHR/409.BCM, 470.BCM: the frog's eyelids), see below |
| 0x24 | u32 | offset of `TXAH` texture-animation table, 0 = none |
| 0x28 | u32 | offset of first `EXHD` extension block, 0 = none |

Order in the file: header, `FRHD`, `ATHD`, `BBHD`, `TXHD`, `TXAH`, `EXHD`...

Section headers are 0x10 bytes: `magic[4]`, then `u16 count @+4`.  (`FRHD`: `u16 count`, `u16 extra_frames @+6`; the
runtime allocates `count + extra_frames` `Frame`s but only `count` records exist in the file; chunk bone indices
can point at the extra frames, e.g. index 37 in a 37-bone model.)

## FRHD — frames (bones)

`count * 0x40` bytes after the 0x10 header.

| off | type | meaning |
|---|---|---|
| 0x00 | char[12] | bone name (`ROOT`, `ROOT1`, `WAIST0`, `HEAD0`, `L_hand`..) |
| 0x0c | u8 | parent index, 0xFF none |
| 0x0d | u8 | first child, 0xFF none |
| 0x0e | u8 | ? (0) |
| 0x0f | u8 | next sibling, 0xFF none |
| 0x10 | 16 | zeros |
| 0x20 | f32[4] | pivot position (x,y,z,1) in **y-up authoring space** |
| 0x30 | f32[4] | orientation quaternion xyzw — nearly always `(-1,0,0,0)`: 180 degrees around X (y-up -> PS2 y-down) |

Frames are stored parents-first.  `Frame::Cleate`:
`R = Quaternion::getMatrix(rec+0x30)`, `B = R * T(rec+0x20)` (= `[R | R*t]`), `invBind = B^-1`.
Model-space (mesh) coordinates are therefore y-down, with the feet at y=0 and the head at negative y.

## ATHD — atomics (draw units / meshes)

`count` atomics follow back to back; atomic size is determined by its arrays (no size field).

### Atomic header (0x30 bytes)

| off | type | meaning |
|---|---|---|
| 0x00 | char[12] | name (`kao`, `body_s`, `R_hand_A`, `All`...) |
| 0x0c | u32 | vertex count N |
| 0x10 | u16 | flags: 0x7c (pack1 static), 0x5c, 0x4c. Bit 2 changes the 0x2a-vertex packet splitting rule in `calcNeedPacket`/`initPacket` |
| 0x12 | u8 | texture index in this model's TXHD table, 0xFF = texture supplied from outside |
| 0x13 | u8 | second texture / layer index, 0xFF none |
| 0x14 | u8 | type byte: low nibble 0=skin 1=Pack(1/2) 2=PLP(1/2); bit7 = no-light variant; bits 4-6 per-atomic flags (0xC0/0xE0/0xD0 seen on skin) |
| 0x15 | u8 | bit0 = `m_enable` copy (`Atomic+0x2b1`); bits1-3 = special: 6=`BAtomic` (billboard) 7=`WaterAtomicP1`; high nibble = special-effect id passed to `Atomic::setSpecialEffect` (`vtbl+0x1c`) |
| 0x16 | u8 | effect parameter (float for id 3, int for ids 1,2) |
| 0x18 | s16 | -1 = vertex arrays are inline; else index of the atomic that owns them (only in LSD cutscene models) |
| 0x1a | u16 | triangle-count hint |
| 0x20 | u32 | 0/1 |

### Class selection (`Model::setAtomic`, 0x0023e510)
```
t = (b15 & 0xf) >> 1
t == 7 -> WaterAtomicP1 (0x3b0)    t == 6 -> BAtomic (0x3e0)
if (b14 & 0x80) || (b14 & 0xf) == 0:
     (b14 & 0xf) == 0 ? (file_flags & 3 ? SkinAtomicPack2 : none) : SkinAtomicPack2NL
elif (b14&0xf)==1: file_flags&3 ? ((file_flags&4) ? Pack2Atomic : Pack1Atomic) : none
elif (b14&0xf)==2: file_flags&3 ? ((file_flags&4) ? PLP2Atomic  : PLP1Atomic ) : none
```
(0x380 bytes for Pack2/Skin/PLP, 0x390 Pack1.)

### Vertex arrays (inline when +0x18 == -1), each padded to 16 bytes

| class | array0 | array1 | array2 |
|---|---|---|---|
| Pack1 (rigid, s16) | N x 8: `s16 x,y,z` (value/16.0), `u16 w` (bit15 = strip ADC) | N x 4: `u16 u,v` (/4096) | N x 4: `rgba8`, 0x80 = 1.0 |
| Pack2 (rigid, float) | N x 16: `f32 x,y,z`, `u32 w` (bit15 ADC) | N x 4 uv | N x 4 rgba |
| SkinAtomicPack2 | N x 16: `f32 x,y,z`, `u32 w` | N x 4 uv | N x 8: `s16 nx,ny,nz` (/32768), `s16 0x7fff` |
| SkinAtomicPack2NL | N x 16 (as skin) | N x 4 uv | N x 4 rgba |
| PLP1 / PLP2 | 8 / 16 | 4 | 8 (never seen in shipped data) |
| BAtomic (billboard) | N x 0x28: 5 x `s16 x,y,z,w` (centre + 4 corners, `w=0x8000`) | N x 4 rgba | — |
| WaterAtomicP1 | N x 8 | N x 4 | N x 4 |

Skin `w` word (**resolved 2026-10-09**, VU1 microcode `_dma_61` 0x003e3e00 / `_dma_202` 0x003e94a0 disassembled): there is **no blend
weight and no second bone**.  The microcode does, per vertex, `MTIR vi13, vf15w` (= the low 16 bits of `w`), `IADDIU vi13, vi13, 179`,
`IAND vi13, vi13, 255`, loads the four rows at that VU1 address into vf18..vf21 and applies that single matrix to the position
(`MULAx/MADDAy/MADDAz/MADDw`) and its 3x3 part to the normal; the rest of the program is lighting, projection and GIF output.
Only bytes 0-1 of `w` matter to it:

| byte | file | meaning |
|---|---|---|
| `b0` | `slot` 0..2 | palette slot (index into the chunk's 3 frame indices).  `initPacket` rewrites it to `base + slot*5` (VU1 matrix register offset; `base` alternates 0 / 15 per chunk = double buffered matrix bank; register 0xb3 + offset) |
| `b1` | 0 | `initPacket` sets `b1 = (b1 & 0xc0) \| (slot & 0x3f) \| 0x40`; **bit 7 = strip ADC** (kept) |
| `b2,b3` | `u16 id` | **vertex identity**, never seen by the VU1 (ignored by `MTIR`, float-denormal otherwise).  All copies of one position in an atomic carry the same id (face atomic: > 256 distinct ids, hence `b3` = 1 for 134 vertices).  Probably the key for blend-shape / dynamics link tables |

So the three bytes the earlier agents read as "weight 0..255 / second slot" were the id.  The weighting of the character is done
**per frame, not per vertex**: see `WFRH` below.  Rust: `SkinVertex { slot, id }`, `AtomicDef::vertex_bone_indices[_clamped]`.

### WFRH — weighted virtual frames (`FrameWeight`, JP `Create` 0x00257790 / `calcWeight` 0x002577b0)
`FRHD.extra_frames` (11 on the BTLDATA PC model) are *virtual frames*: frame `count + i` has no file record; its skinning matrix
`world[buf]` is computed after `Frame::calcMatrix` as a normalised weighted sum of 2..4 real frames' matrices (element-wise on the 4x4,
translation row included).  Chunk palettes reference these indices (e.g. a chunk `[12, 18, 41]` = UBODY1, LSH0, virtual 41), so
shoulder, collar, wrist and jaw vertices bend smoothly while the VU1 still applies exactly one matrix per vertex.  Every copy of a welded
position uses the same virtual frame, so seams cannot tear.

Block: `EXHD` header (`u16 @+10` = entry count) then `count` 16-byte entries:
```
+0 u8 ?  +1 u8 k (2..4 source frames)  +2..3 pad  +4 u8 frame[4]  +8 u16 weight[4]   (weights sum to ~4096)
M_virtual = (w0*M[frame0] + w1*M[frame1]) / (w0 + w1)                    (k = 2, the only case in shipped data)
k > 2: M = lerp(M, M[frame_i], f_i), f_i = (w_i/4096) / (f_{i-1} + w_i/4096)  (original keeps f, not the running sum -- bug kept)
```
BTLDATA PC model: 37 -> HEAD0/JAW0 .6/.4, 38 -> LSH0/carpL0 .2/.8, 39 -> carpL0/carp_B0 .6/.4, 40 -> LSH0/carpL0 .5/.5, 41 -> .3/.7,
42..45 the right-hand-side mirror (RSH0/carpR0), 46 -> LARM1/LHAND0 .5/.5, 47 -> RARM1/RHAND0 .5/.5.  Rust:
`Model::frame_weights()`, `ModelInstance::update_pose` (pose table = frames + virtual frames), test `sh2_gfx/tests/skin_weight.rs`.

Positions: Pack1 uses fixed point 1/16 (VU1 `ITOF4`), UV 1/4096 (`ITOF12`), normals 1/32768 (`ITOF15`) — scanned from the
Pack1 microcode (`0x003e55e0`: ITOF4 on positions, ITOF12 on UV).

### Packet table (follows the arrays) — `Pack1Atomic::calcNeedPacket`, `SkinAtomicPack2::initPacket`

```
u32 chunk_count; u32[3] pad
chunk[chunk_count] (0x10 bytes each):
   u8 bone0, u8 bone1, u8 bone2, u8 flag     Pack1/2: bone0 = frame the chunk is local to (bone1/2 = 0xFF)
                                              Skin: matrix palette (3 frames, 0xFF unused; index >= FRHD count = WFRH virtual frame)
   u32 tag      = atomic_index << 16
   u32 start    first vertex of this chunk
   u32 count    vertex count (sum of counts == N)
```
Each chunk is a triangle strip (or several): vertices with `ADC` set do not complete a triangle; a strip restarts
after two consecutive ADC vertices and the facing alternates inside a strip.  The engine splits chunks into
VU1 packets of <= 0x2a vertices (`0x2a` = 42; with flag bit 2 the cut is moved back to an ADC boundary).

The next atomic header follows immediately after the last chunk.

## BBHD — bounding boxes
`u32 n1 @+4, u32 n2 @+8`; `(n1+n2)` entries of 0x110 bytes: `u32 tag` (frame idx / parent), 8 x `FVector` box corners at +0x10.
`Model::create` averages the 8 corners into a centre (`Model+0x458`) and radius (`.w`).

## TXHD — textures (`Texture::CreateData`, 0x002474e0)
`u16 count @+4`, textures follow back to back, each:

| off | meaning |
|---|---|
| 0 | `"TIHD"` |
| 4,6 | u16 width, height |
| 8 | u8 format: 4 = PSMT4(HH upload, GS psm 0x2c), 8 = PSMT8 (psm 0x1b), 0x20 = PSMCT32; bit 0x40 = IPU (MPEG intra) compressed |
| 10 | u8 mip count (0 in all shipped data) |
| 0x0c | u16 CLUT entry count (16 or 256) |
| 0x0e | u16 CLUT offset from header start (RGBA8, alpha 0x80 = opaque) |
| 0x10 | u32 pixel data offset |
| 0x14 | u32 end of base image = offset of the next texture (mip levels, if any, are included) |
| 0x1c | u16 GS ALPHA setup (`changeGSAlpha(this, flag&2, (flag&0xc)>>2, (flag&0x20)>>4, (flag&0xc0)>>6, flag>>8)`) |
| 0x1e | u8 alpha-test reference (`changeGSTest`) |
| 0x1f | u8 flags (bit 2 = additive/alpha variant, &3 = test method) |

Pixels: 4bpp low nibble first, row major; 8bpp indexes the CLUT with **bits 3 and 4 swapped** (CSM1 CLUT swizzle).

## TXAH — texture animation table
`u16 count @+4`; `count` variable-size `TXAD` entries (`TextureAnim::CreateData`, 0x002489f0) starting at +0x10, each `0x30 + payload` bytes:
`+0 "TXAD"`, `+4 name[12]` (`eye`, `dr5`, `fl` ...), `+0x10 u8 texture index`, `+0x11 u8 frame count`, `+0x12/+0x14 u16 w/h`, `+0x18 u16 frame stride`,
`+0x1a u16 dstX`, `+0x1c u16 y inset`, `+0x20 u16 payload/16`, frames (indexed pixels of the target texture's depth) from +0x30.  A frame is
copied into the target texture at `(dstX, texH - inset - h)` (`RefLoadImage`).  Selected by motion events `TXA<name>` (`Model::changeTextureAnim(name, i)`
-> `TextureAnim::setCurrentIndex`, ignores `i > frame count`) and by the field engine's blink machine for the entry called `eye`.
Rust: `sh2_formats::model::{TexAnimDef, Model::texanims}`, `sh2_gfx::bevy::texanim` (RGBA frames), `ModelInstance::{texanim_frame, change_texture_anim}`.
Characters: 80 field + 23 battle models carry an `eye` entry (2-3 frames: open / half / closed).

## BSAH — blend shapes (`BlendShapeControl`, `BlendShape`; JP 0x0024b4f0..0x0024d294; decoded 2026-10-09 from the US eyelid data)
Block: `"BSAH"`, `u16 shape_count @+4`, `u8 flags @+6` (`& 0xf` = has data), shapes from +0x10, each followed by `+0x18 * 16` bytes to the next one.
Shape (offsets from the shape start; `*16` = 16-byte units):
```
+0x00 char name[12]   +0x0d u8 group   +0x0e u16 target count T
+0x10 u32 UV array *16 (N x {u16 u, u16 v}/4096)   +0x14 u32 chunk table *16 (u32 count, pad[3], chunk[count] as in an atomic)   +0x18 u32 next *16
+0x20 a regular 0x30-byte atomic header: name, N @+0x2c, PRIM flags u16 @+0x30, texture @+0x32, type bytes @+0x34.. (0xf0 = SkinAtomicPack2), shared_ref -1
+0x50 u32 target[T] *16
target = 0x10 header + N x 16 positions (f32 xyz + u32 w: skin slot / strip ADC bit 15) + N x 8 normals (s16 xyz /32768, pad), 16-byte aligned
```
So a blend shape is a **skin atomic with its own chunk table and UVs and T vertex-array versions**.  `calcBlend` (0x0024beb0):
`out = (1 - w1) P0 + w1 P1 + sum_{k >= 2} w_k (P_k - P0)` (normals likewise, renormalised); weights `w_k` (`changeSlider(k, f)`) come from the motion event
`BSASeq01` (kind 0x13: key `{u16 time, u8 group, u8 n, u32 bytes}`: `w_{j+1} = byte_j / 255` for `j < min(n, 4)` of every shape whose group matches);
`BSASeq00` = `changeShapeGrp(t/4096, group, shape)` (shape presets with a transition time; no shipped data uses it).
The 409 / 470 idle motions drive a 2-slider eyelid (open <-> closed).  Rust: `Model::blend_shapes` (the shape atomic is also appended to `Model::atomics`,
drawn like any skin atomic), `ModelInstance::{shape_weights, shape_geometry}`, `bevy::model::skin` swaps in the blended arrays.

## Special atomics (census 2026-10-09, `sh2_gfx/examples/model_census.rs`, every `SSH1.01a` image of both discs)
* **Water (`WaterAtomicP1`, `b15 >> 1 & 7 == 7`)**: 0 models on either disc.  Recovered anyway from `Cleate` 0x0025ad00 / `addTime` 0x0025ab60: it is a `Pack1`
  atomic whose **U coordinate** wobbles (`u = u0 + (short)(amp[g] sin(phase[g]))`, `amp = 50 + 200 rand`, `phase += 1.5 dt` once *per vertex of the group*, `g` = low byte of the
  vertex `w`); the vertices do not move (the earlier "vertex y wobble" guess was wrong).  `sh2_gfx::model::water`.
* **Billboard (`BAtomic`, `b15 >> 1 & 7 == 6`)**: JP 168 / US 262 models, all effect-like: `EFFECT/*.EFD`, `FIELD/EFF/*.EFD`, `LSD` cutscene models, `COMMON/SVP.BIN` (save point
  sparkles), `BTLDATA/BTL_001.BIN` (battle-start flash).  No field map contains one.  Semantics in `sh2_gfx::bevy::billboard`.
* Atomic special-effect id (`b15 >> 4`): 0 = 195k atomics, 1 = 330, 2 = 28, 3 = 117 (US) -- the VU1 environment / specular variants, not drawn.
* `DYNH` 109 JP / 611 US models, `WFRH` 98 / 439, `DHSH` 86 / 392, `TXAH` 144 / 534 models (see the per-container counts in the tool output).

## EXHD — extension chain
`"EXHD"`, `char tag[4]`, `u32 ?`, `u32 size_in_16B_units @+0xc`; payload starts at +0x10.  Tags (stored byte-reversed on
the wire = what the loader compares):

| tag | handler | meaning |
|---|---|---|
| `LABL` | `Model+0x454` | label table (pointer only) |
| `DHSH` | `BoundingCircle::Create` | bounding circles (collision with `Dynamics`) |
| `WFRH` | `FrameWeight::Create` | per-frame weights |
| `DYNH` | `DynamicsControl::Create` + `Init` | soft-body / hair / cloth dynamics (`Dynamics`, `BRN_*`) |

## Not decoded / open
* PLP1/PLP2, an unidentified atomic variant in LSD.PKB cutscene models (23 of 53 LSD models stop with a warning at an atomic whose arrays are larger than N), shared-geometry atomics (`+0x18 != -1`).
* `BSASeq00` shape presets, `DHSH` collision circles, atomic special-effect ids (`b15 >> 4`).
