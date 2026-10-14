# FaceImage

* base: `CPolObj`; allocation size: 0x1c; ctor JP `0x004a0440`
* vtable stores: `+0x14 __vt__9FaceImage`

| JP addr | size | method |
|---|---|---|
| `0x004a0440` | 0x10c | `FaceImage::FaceImage()` |
| `0x004a0550` | 0xc0 | `FaceImage::~FaceImage()` |
| `0x004a0610` | 0xb8 | `FaceImage::Create(int)` |
| `0x004a06d0` | 0x58 | `FaceImage::Release()` |
| `0x004a0730` | 0xbc | `FaceImage::Open(unsigned char, int)` |
| `0x004a07f0` | 0xbc | `FaceImage::Close(unsigned char, int)` |
| `0x004a08b0` | 0x108 | `FaceImage::Polling()` |
| `0x004a09c0` | 0x114 | `FaceImage::CreateImage()` |
| `0x004a0ae0` | 0xcc | `FaceImage::ShiftState(short)` |
| `0x004b5a50` | 0x64 | `FaceImage::SetSize(float, float)` |
| `0x004b5bc0` | 0x40 | `FaceImage::SetPosition(float, float)` |

Decompiled source: `decomp/G/FaceImage.c`.
