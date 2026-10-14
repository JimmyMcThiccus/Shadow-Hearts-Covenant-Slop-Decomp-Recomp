# Cursor

Base class: `MenuObj`

The selection cursor (hand/arrow). Owns a `MenuPolygon` image @0x1c, a `SendOnLocal` texture binding @0xa0, optional shadow polygon / flare trail, and follows a target with exponential smoothing. Types are indexed in a table at 0x4217a8 (stride 0x40: image size + RasterPacket). Direction (8 right-pointing .. 1 up) controls offset and a 90/180-degree rotation; `rotate` spins the image about the X axis (`angle += dt*0.5` degrees, wraps at 180).

## Behaviour

`Select(place)` converts the cursor's screen position to window-local, scrolls the window to reveal the place, then `place->IsSelected(cursor)`; `MoveCursor(dir)` uses `MenuWindow::MovePlace`; `SkipCursor(dir)` jumps a page; `Leave()` converts back to screen space and cancels the place. `SetTarget(x,y)` plays the move sound (`MenuSound::PlaySE(0)`).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x18 | `MenuSound *` | sound |
| 0x1c | `MenuPolygon` | poly |
| 0xa0 | `SendOnLocal` | send |
| 0xd0 | `MenuPolygon *` | shadow |
| 0xd4 | `MenuFlare *` | flare |
| 0xd8 | `u8 *` | pos |
| 0xdc | `f32` | off_x |
| 0xe0 | `f32` | off_y |
| 0xe4 | `f32` | target_x |
| 0xe8 | `f32` | target_y |
| 0xec | `MenuPlace *` | place |
| 0xf0 | `MenuSprite *` | back |
| 0xf4 | `f32` | angle |
| 0xf8 | `u8` | move_state |
| 0xf9 | `s8` | gap |
| 0xfa | `u16` | cflags |
| 0xfb | `u8` | cflags2 |

## Virtual table (`__vt__Cursor`)

| slot | function |
|---|---|
| 0x08 | `__dt__6CursorFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__6CursorFv` |
| 0x14 | `Update__6CursorFiiUs` |
| 0x18 | `Connect__6CursorFP4_QWD` |
| 0x1c | `Destroy__6CursorFv` |
| 0x20 | `Clear__6CursorFv` |

## Constructed by

`ExitRealize__13GameOverSceneFv`, `__ct__10primCursorFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00270370 | 0x70 | `__ct__6CursorFv` | `Cursor::Cursor()` |
| 0x002703e0 | 0xac | `__dt__6CursorFv` | `Cursor::~Cursor()` |
| 0x00270490 | 0x10c | `Create__6CursorFUcUcUcUc` | `Cursor::Create(unsigned char, unsigned char, unsigned char, unsigned char)` |
| 0x002705a0 | 0x158 | `SetBackObject__6CursorFUc` | `Cursor::SetBackObject(unsigned char)` |
| 0x00270700 | 0x1c4 | `Select__6CursorFP9MenuPlace` | `Cursor::Select(MenuPlace*)` |
| 0x002708d0 | 0x48 | `QuickMove__6CursorFv` | `Cursor::QuickMove()` |
| 0x00270920 | 0xb0 | `Leave__6CursorFv` | `Cursor::Leave()` |
| 0x002709d0 | 0x40 | `ClearAfter__6CursorFv` | `Cursor::ClearAfter()` |
| 0x00270a10 | 0x16c | `MoveCursor__6CursorFi` | `Cursor::MoveCursor(int)` |
| 0x00270b80 | 0x3ec | `SkipCursor__6CursorFi` | `Cursor::SkipCursor(int)` |
| 0x00270f70 | 0x90 | `SetTarget__6CursorFff` | `Cursor::SetTarget(float, float)` |
| 0x00271000 | 0x4c | `SetTarget__6CursorFP8DrawRect` | `Cursor::SetTarget(DrawRect*)` |
| 0x00271050 | 0x1e4 | `GetTarget__6CursorFP8DrawRectPfPf` | `Cursor::GetTarget(DrawRect*, float*, float*)` |
| 0x00271240 | 0x60 | `GetScreen__6CursorFPfPf` | `Cursor::GetScreen(float*, float*)` |
| 0x002712a0 | 0x178 | `ConvertScreen__6CursorFPfPf` | `Cursor::ConvertScreen(float*, float*)` |
| 0x00271420 | 0x5c | `GetPoint__6CursorFPfPf` | `Cursor::GetPoint(float*, float*)` |
| 0x00271480 | 0x9c | `Restore__6CursorFv` | `Cursor::Restore()` |
| 0x00271520 | 0x64 | `Shutdown__6CursorFv` | `Cursor::Shutdown()` |
| 0x00271590 | 0x19c | `SetType__6CursorFUc` | `Cursor::SetType(unsigned char)` |
| 0x00271730 | 0x24c | `SetShadow__6CursorFUc` | `Cursor::SetShadow(unsigned char)` |
| 0x00271980 | 0x18c | `SetDirection__6CursorFUcf` | `Cursor::SetDirection(unsigned char, float)` |
| 0x00271b10 | 0x5c | `SetRotation__6CursorFUc` | `Cursor::SetRotation(unsigned char)` |
| 0x00271b70 | 0x3f0 | `SetVertex__6CursorFv` | `Cursor::SetVertex()` |
| 0x00271f60 | 0x1c0 | `SetFlareOffset__6CursorFv` | `Cursor::SetFlareOffset()` |
| 0x00272120 | 0x370 | `Polling__6CursorFv` | `Cursor::Polling()` |
| 0x00272490 | 0x484 | `Update__6CursorFiiUs` | `Cursor::Update(int, int, unsigned short)` |
| 0x00272920 | 0xf4 | `Connect__6CursorFP4_QWD` | `Cursor::Connect(_QWD*)` |
| 0x00272a20 | 0x124 | `Destroy__6CursorFv` | `Cursor::Destroy()` |
| 0x00272b50 | 0x134 | `Clear__6CursorFv` | `Cursor::Clear()` |

## Rust port

`cursor::Cursor`, `PlaceRef`.

## Open questions

- none recorded

Decompilation: `decomp/F/Cursor.c`
