# Frame (bone / scene node) — JP 0x002433c0..0x00244424, `Frame` is 0x1f0 bytes

| off | type | name |
|---|---|---|
| 0x000 | Matrix[2] | `world[buf]` — **skinning matrix** per double-buffer slot (`m_Env__8VIF1Prim & 1`); identity in bind pose |
| 0x080 | FrameRec* | file record (name, parent/child/sibling bytes, pivot, orientation) |
| 0x088 | Sequence* | track of the current main motion for this frame (set by `Frame::setSequence`) |
| 0x090 | Frame* | base of the frame table (so `parent = this->frames[rec->parent]`) |
| 0x094 / 0x098 | int / Model* | chained Model (weapon etc.) and its flag; `calcMatrix` calls its `vtbl+0x28` with this frame's world rot/pos |
| 0x0a0 | Matrix | `rotMat` = R(rec.q) |
| 0x0e0 | Matrix | `invBind` = (R * T(rec.pivot))^-1 |
| 0x120 | Matrix | `motionMat` D = `Sequence::getMatrix(time)` = [R(q)|d], identity when no track |
| 0x160 | Matrix | `extraMat` (script/ExModel transform, identity by default) |
| 0x1a0 | Matrix | `animMat` A = rotMat * extraMat * T(pivot) (`myMatrixUpdate`) |
| 0x1e0 | int | "skip" flag: `calcMatrix` returns 0 if set and no root matrix is supplied |
| 0x1e4 | u16 | bit0 = force-animated, bit1 = ?, bits 2..9 = frame count (only valid in frame 0) |

`Frame::calcMatrix(root, buf)`:
```
for i in 0..count:                       // parents precede children
    M = parent==0xFF ? (root ? *root : I) : frames[parent].world[buf]
    M = M * invBind[i] * (seq? D[i] : I) * A[i]
    frames[i].world[buf] = M
```
Because `A = B` when `extraMat = I`, a pure bind pose yields identity and an animated pose yields `M_p * B^-1 * D * B`
(delta keys expressed in the bone's own bind frame).  Other members: `searchFrame(name)` (linear 12-byte strcmp),
`searchFrameIndex`, `getWorldPos/Rot(buf)`, `chainModel/unChainModel`, `setSequence(SequenceControl*, kind)`
(links each frame to the same-named `Sequence`), `deleteSequence`.  Rust: `sh2_gfx::model::skeleton::Skeleton::evaluate`.
