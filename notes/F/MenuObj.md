# MenuObj

Base class: `DelayDeleteObject`

Root of the menu widget hierarchy **and** a static holder for the toolkit's global state (`sm_*` members): `sm_menuRender` (the world layer that draws all menu windows, JP 0x00421a30), `sm_common` (the shared `COMMON/CMNMENU.DAT` scene, 0x00421600), `sm_pFieldData`/`sm_pCmdMenu` (field menu resource scenes), `sm_pFace` (`FileManeger` for face textures `MENU/FACE/FI_%03d.TEX`), `sm_pSound` (`MenuSound`), `sm_iPassTime/sm_fPassTime/sm_prevTime` (frame delta in ticks), `sm_fZero`, `sm_freeBlock`, `sm_clearRect`.

## Behaviour

`Initialize()` (0x002744b0) loads the common scene (`OrderFile(&sm_common, "COMMON/CMNMENU.DAT")`), creates the render layer (`Create` + `Entry(13)` = world OT layer 13) and `new SaveMenuSection`. `CreateField/ReleaseField` and `CreateCmdMenu/ReleaseCmdMenu` are reference counted (`+0x22`) loaders of the field-menu scenes (`MenuFieldStationed`, `MenuFieldData`) plus `MenuSound`/face file manager. `UpdateTimer()` computes `sm_iPassTime = GetTimer() - prev`; every widget's `Polling` uses it as the time step (ticks of the SysTool timer; the title code counts frames of 16 ticks). `AddOT/ReleaseOT` insert/remove a window in the render layer's priority-ordered `MenuObjTable`.

Instance layout: a `MenuObj` is 0x18 bytes: `DelayDeleteObject` links (0,4), vptr @8, chain `next` @0xc (used by `MenuObjTable`), two per-VIF-buffer dirty byte masks @0x10/0x11 (bit0 header, bit1 env/position-in-window, bit3 rect, bit4 rgba, bit5 uv...), flags @0x12 (bit0 render, bit1 poll, bit2 in table, bit3 delay-delete, bit4 created), priority @0x14, id @0x16 (-1 anonymous).

Vtable (shared by all widgets): 0x08 dtor, 0x0c DelayDelete, 0x10 Polling, 0x14 Update(x,y,alpha), 0x18 Connect(packet), 0x1c Destroy, 0x20 Clear; `MenuPlace` adds 0x24 SetPosition, 0x28 SetSize, 0x2c SetAlpha, 0x30 SetColor, 0x34 SetBright, 0x38 SetOwner, 0x3c GetKeyPlace, 0x40 GetKeyRect, 0x44 AllotPacket, 0x48 GetAllotCount, 0x4c Attach, 0x50 Detach.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0xc | `MenuObj *` | next |
| 0x10 | `u8` | dirty0 |
| 0x11 | `u8` | dirty1 |
| 0x12 | `u8` | flags |
| 0x14 | `s16` | priority |
| 0x16 | `s16` | id |

## Virtual table (`__vt__MenuObj`)

| slot | function |
|---|---|
| 0x08 | `__dt__7MenuObjFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__7MenuObjFiiUs` |
| 0x18 | `Connect__7MenuObjFP4_QWD` |
| 0x1c | `Destroy__7MenuObjFv` |
| 0x20 | `Clear__7MenuObjFv` |

## Constructed by

`__ct__10MenuWindowFv`, `__ct__10ScrollMarkFv`, `__ct__11SendOnLocalFv`, `__ct__12MenuRegisterFv`, `__ct__16MenuWindowObjectFv`, `__ct__6CursorFv`, `__ct__7KeyWaitFv`, `__ct__8FontDrawFv`, `__ct__9MenuFlareFv`, `__ct__9MenuFrameFv`, `__ct__9MenuPlaceFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002744b0 | 0xa4 | `Initialize__7MenuObjFv` | `MenuObj::Initialize()` |
| 0x00274560 | 0x18 | `IsReady__7MenuObjFv` | `MenuObj::IsReady()` |
| 0x00274580 | 0x7c | `UpdateTimer__7MenuObjFv` | `MenuObj::UpdateTimer()` |
| 0x00274600 | 0x2d8 | `SetBright__7MenuObjFP7_rgba32f` | `MenuObj::SetBright(_rgba32*, float)` |
| 0x002748e0 | 0x134 | `CreateField__7MenuObjFv` | `MenuObj::CreateField()` |
| 0x00274a20 | 0x9c | `CreateCmdMenu__7MenuObjFv` | `MenuObj::CreateCmdMenu()` |
| 0x00274ac0 | 0xb4 | `ReleaseField__7MenuObjFv` | `MenuObj::ReleaseField()` |
| 0x00274b80 | 0x64 | `ReleaseCmdMenu__7MenuObjFv` | `MenuObj::ReleaseCmdMenu()` |
| 0x00274bf0 | 0x48 | `IsReadyField__7MenuObjFv` | `MenuObj::IsReadyField()` |
| 0x00274c40 | 0x48 | `__ct__7MenuObjFv` | `MenuObj::MenuObj()` |
| 0x00274c90 | 0x84 | `__dt__7MenuObjFv` | `MenuObj::~MenuObj()` |
| 0x00274d20 | 0x30 | `AddOT__7MenuObjFv` | `MenuObj::AddOT()` |
| 0x00274d50 | 0x30 | `ReleaseOT__7MenuObjFv` | `MenuObj::ReleaseOT()` |
| 0x00274d80 | 0x94 | `Release__7MenuObjFv` | `MenuObj::Release()` |
| 0x00274e20 | 0x10 | `Polling__7MenuObjFv` | `MenuObj::Polling()` |
| 0x00274e30 | 0x10 | `Update__7MenuObjFiiUs` | `MenuObj::Update(int, int, unsigned short)` |
| 0x00274e40 | 0x18 | `Connect__7MenuObjFP4_QWD` | `MenuObj::Connect(_QWD*)` |
| 0x00274e60 | 0x10 | `Destroy__7MenuObjFv` | `MenuObj::Destroy()` |
| 0x00274e70 | 0x4c | `Clear__7MenuObjFv` | `MenuObj::Clear()` |
| 0x00371720 | 0x60 | `UpdateRgba__7MenuObjFv` | `MenuObj::UpdateRgba()` |
| 0x00371780 | 0x60 | `UpdateEnv__7MenuObjFv` | `MenuObj::UpdateEnv()` |

## Rust port

`widget::ObjBase`, `window::MenuRoot` (render layer + window table), timer in `MenuRoot::update_timer`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuObj.c`
