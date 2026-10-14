# Atomic family — JP 0x00242620 (`Atomic`), 0x0024d2a0.. (`Pack1/Pack2/SkinAtomicPack2(NL)/PLP1/PLP2/WaterAtomicP1/BAtomic/BBAtomic`)

An `Atomic` is the runtime wrapper of one mesh ("triangle header") of a model.  Base size 0x370 + vtable at +0x370; subclasses 0x380
(Pack2/Skin/PLP/NL), 0x390 (Pack1), 0x3a0 (BBAtomic), 0x3b0 (Water), 0x3e0 (BAtomic).

| off | field |
|---|---|
| 0x00 | `_ModelTriangleHeader*` hdr (0x30 bytes in the file, see model_format.md) |
| 0x04 | Atomic** table of the owning model |
| 0x08 | vertex array base (null when `hdr+0x18 != -1`) |
| 0x0c / 0x10 | two DMA chains (double buffer) built by `initPacket` |
| 0x1c / 0x20 | packet table (chunk count, then chunks at +0x10) |
| 0x24 | Frame* frames (the model's) |
| 0x28 / 0x2c | VU1 microcode DMA chains (`_dma_61` at 0x3e55e0 for Pack1, `_dma_202` for skin) |
| 0x30.. | 6 matrices (world*camera, screen), then 16 vec4 (light / env) |
| 0x2b0 | u8 enable; 0x2b1 lit (hdr fx bit0); 0x2b2 fxMode (bit0 shadow flag set by create, bit1 hidden by `Visible `); 0x2b3 alpha (0x80 = 1.0) |
| 0x2f0.. | texture UV scroll (x,y; value*4096 into the packet), 0x300/0x310 vectors (0,0,1,0), 0x320 colour (2-pass), 0x350 Model* |
| 0x370 | vtable: +0x10 `Cleate`, +0x14 `initPacket`, +0x1c `setSpecialEffect(id)`, +0x20 `set2PathColor`, +0x24 `set2PathAlpha`, +0x28 `addTime(dt)`; getPacket / calcNeedPacket slots not verified |

* `Cleate(hdr, atomicTable, model)` sets pointers and returns the end of the arrays (= packet table).
* `initPacket(frames, packetTable)` builds the two DMA chains (GIF/VIF headers, matrix uploads for each chunk's bones, vertex UNPACKs split at 0x2a
  vertices) and returns the end of the packet table (= next atomic header).  Skin version recovered in `decomp/C/Atomic.c`.
* `getPacket(buf, prev)` per frame: refreshes the per-frame matrices (`camera * frame.world[buf]`, plus the 0x30 offset copy for the normal
  matrix), alpha*(model colour), UV scroll, returns the DMA chain (or 0 if disabled).
* Special-effect ids (`hdr+0x15 >> 4`): 1,2 take `hdr+0x16` as int, 3 as float (e.g. env-map / scroll speed).
* VU1 programs (scanned): Pack1 microcode at 0x3e55e0 (3 MPG blocks, 340 qwords) uses ITOF4 for s16 positions and ITOF12 for UVs.
