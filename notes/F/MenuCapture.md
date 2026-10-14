# MenuCapture

Base class: `VIF1Prim`

Screen capture used as a blurred/frozen background under menus (`Capture(x,y,w,h,psm)`, `Release`, `getPacket`).

## Virtual table (`__vt__MenuCapture`)

| slot | function |
|---|---|
| 0x08 | `__dt__11MenuCaptureFv` |
| 0x0c | `getPacket__11MenuCaptureFv` |
| 0x18 | `@20@__dt__11MenuCaptureFv` |
| 0x1c | `@20@Polling__11MenuCaptureFv` |
| 0x20 | `Polling__11MenuCaptureFv` |

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002810f0 | 0xa4 | `__ct__11MenuCaptureFv` | `MenuCapture::MenuCapture()` |
| 0x002811a0 | 0xb4 | `__dt__11MenuCaptureFv` | `MenuCapture::~MenuCapture()` |
| 0x00281260 | 0x11c | `Capture__11MenuCaptureFiss6GS_PSMUc` | `MenuCapture::Capture(int, short, short, GS_PSM, unsigned char)` |
| 0x00281380 | 0xc4 | `Release__11MenuCaptureFv` | `MenuCapture::Release()` |
| 0x00281450 | 0x320 | `getPacket__11MenuCaptureFv` | `MenuCapture::getPacket()` |
| 0x00281770 | 0x2f0 | `Polling__11MenuCaptureFv` | `MenuCapture::Polling()` |
| 0x00281a60 | 0x8 | `@20@Polling__11MenuCaptureFv` | `@20@Polling__11MenuCaptureFv` |
| 0x00281a70 | 0x8 | `@20@__dt__11MenuCaptureFv` | `@20@__dt__11MenuCaptureFv` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuCapture.c`
