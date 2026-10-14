# Matrix

Copy of a **main-executable** class statically linked into FIELD.BIN (duplicated code of another section's class); documented by the owning section. Listed here for address mapping only.

* base: `-`; allocation size: unknown; ctor JP `0x00432660`

| JP addr | size | method |
|---|---|---|
| `0x00431fe0` | 0x1c | `Matrix::GetPos()` |
| `0x00432620` | 0x34 | `Matrix::RotYMatrix(float)` |
| `0x00432660` | 0x2c | `Matrix::Matrix()` |
| `0x00432690` | 0x24 | `Matrix::UnitMatrix()` |
| `0x00434a20` | 0x5c | `Matrix::__as(const Matrix&)` |
| `0x00434aa0` | 0x34 | `Matrix::RotMatrix(const FVector&)` |
| `0x004a80a0` | 0x1c | `Matrix::GetAt()` |
| `0x004aa660` | 0x34 | `Matrix::RotXMatrix(float)` |
| `0x004beec0` | 0x18 | `Matrix::TransMatrix(const FVector&)` |
| `0x004beee0` | 0x34 | `Matrix::RotZMatrix(float)` |
| `0x004c6e70` | 0x34 | `Matrix::SetPos(const FVector&)` |
| `0x004c6eb0` | 0x40 | `Matrix::SetVector(int, const FVector&)` |

Decompiled source: `decomp/G/_OverlayCopies_Matrix.c`.
