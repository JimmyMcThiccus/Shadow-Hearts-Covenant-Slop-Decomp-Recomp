# Math types (FVector / Matrix / Quaternion / SVector) — shared by all sections

Rust: `port/crates/sh2_formats/src/math.rs` (`sh2_formats::math::{FVector, Matrix, Quaternion, SVector}`), 4 unit tests.

* `FVector` = `{x,y,z,w}` f32, 16-byte aligned (`lqc2/sqc2`).  Binary ops (`+ - * /`, `Length`, `Normalize`, `InnerProduct`, `OuterProduct`) touch **xyz only**
  and keep `w` of the left operand (JP `0x00305a70 __pl__`, `0x003099a0 __ml__`, ...).  `Origin()` = (0,0,0,1).
* `Matrix` = four column `FVector`s (`sceVu0FMATRIX`): `m[3]` (+0x30) is the translation; `MulMatrix(this, rhs)` (JP 0x00225370) computes
  `this * rhs` with column vectors (`dest.col[j] = this * rhs.col[j]`); `ApplyMatrix(v)` = `M * v` including `w`.  Memory layout = `glam::Mat4`.
* `Quaternion` = `{x,y,z,w}`; `getMatrix` (JP 0x00246980) writes the standard column-vector rotation matrix; `operator*` Hamilton product; `slerp` uses polynomial
  approximations but is shortest-arc slerp; `Quaternion(Matrix*)` converts back.
* `SVector` = 3 x s16 + u16 (20-bit fixed point per component, scale 0.01 or 1.0): motion translation keys.
* `VEC` in the class list of this section is **not** math: `VEC` (JP 0x002fc0c0..) is the effect-script "VSM" executor (`DecodeVSM`, `MotionWait(EffectModel*)`) and belongs to section D.
* The overlays carry private copies of FVector/Matrix helpers (e.g. FIELD.BIN 0x00431330 `__ct__7FVectorFffff`); same code.
