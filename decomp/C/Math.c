/* FVector / Matrix / Quaternion / SVector — JP 0x00222130.. 0x0025d0b8 (+ duplicated copies in the overlays) */

/* Matrix is column-major (sceVu0FMATRIX): m[3] (+0x30) = translation; MulMatrix(this, rhs) = this * rhs, column vectors.
 * JP: 0x00225370 MulMatrix__6MatrixCFRC6Matrix — dest.col[j] = this * rhs.col[j] using VU0 vmulax/vmadday/vmaddaz/vmaddw */
/* JP: 0x00225560 ApplyMatrix__6MatrixCFRC7FVector      — sceVu0ApplyMatrix, v' = M * v (w included)
 * JP: 0x0025f9c0 Invers__6MatrixFv                      — sceVu0InversMatrix (affine inverse)
 * JP: 0x0025e100 UnitMatrix, 0x0025e090 RotMatrix(FVector rot) -> sceVu0RotMatrix, 0x00306020/0x00309a20/0x0030b9e0 RotZ/Y/X */

/* JP: 0x00246980 getMatrix__10QuaternionFPf — writes the standard column-vector rotation matrix of q=(x,y,z,w):
 *   m[0]=1-2(y²+z²) m[1]=2(xy+wz) m[2]=2(xz-wy)   m[4]=2(xy-wz) m[5]=1-2(z²+x²) m[6]=2(yz+wx)
 *   m[8]=2(xz+wy)   m[9]=2(yz-wx) m[10]=1-2(x²+y²)  m[13]=0 (the rest of the matrix is left untouched) */
void Quaternion::getMatrix(Quaternion *q, float *m) { /* as above */ }

/* JP: 0x00243d80 Quaternion::operator*  — Hamilton product
 * JP: 0x00246a70 Quaternion::slerp(const Quaternion &b, float t) — uses polynomial acos/sin approximations
 *       (constants 0x3fc90ff9 = pi/2 ..., 0x3f06dd37 ...), shortest arc (negates b when dot < 0), returns *this */
/* JP: 0x002466e0 Quaternion::Quaternion(Matrix *) — matrix to quaternion */

/* JP: 0x0023d910 SVector::ShortToFloat(float *out) — see SVector in math.rs / motion_format.md
 *   v[i] = ((s16[i] << 5) | ((w >> 5*i) & 31)) * (w & 0x8000 ? 1.0f : 0.01f); v.w = 1.0f   (uses PEXT5/PSLLW tricks)
 * JP: 0x0023d7e0 SVector::setFloatToShort(const float *in) — inverse: range check |x| <= 10485.75 else 1.0 scale flag */

/* JP: 0x00225690 FVector::Normalize, 0x002256d0 Clamp(min,max), 0x00225700 OuterProduct (cross), 0x00225740 Length, 0x0030c340 InnerProduct
 *     0x00305a70 operator+, 0x00308550 operator-, 0x003099a0 operator*(float), 0x0030a200 operator/(float), 0x00305440 Origin = (0,0,0,1)
 *     FVector ops are xyz-only; w is passed through from the left operand. */
