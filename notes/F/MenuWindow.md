# MenuWindow

Base class: `MenuObj (+ MenuObjTable @0x18, MenuPacket @0x24 as members)`

Window container, the unit the game opens and closes. Children: a priority-sorted draw table (`MenuObjTable` @0x18), a list of selectable places (@0x38, linked by `MenuPlace.next`), a style decoration object (@0x3c, one of `MenuWindow{Message,Face,Note,Frame,Plain,General,Compact}` selected by `Create`'s style argument), optional `ScrollData` (@0x40, grid scrolling), `ScrollMark` (@0x44) and a `Scissor` (@0x4c). Geometry floats @0x64..0x70, clip shorts, scroll offset @0x8c/0x90, alpha Q15 @0xac, state byte @0xa8 (0 closed, 1 open, 5 sliding, 6 zoom, 7 fade).

## Behaviour

`Open(effect, frames)` / `Close(effect, frames)`: effect 0 fade (alpha lerp to/from 0x8000), 1 slide from/to above (y = -(h+100)), 2 below (y = 548), 3 left (x = -(w+100)), 4 right (x = 612), 5 zoom (scissor shrinks to the centre). `Polling` steps the animation with the frame delta, then the scroll animation (exponential approach `d*dt*0.01`, optional per-axis speed clamp, ends below 1 px), then polls children. `Finish()` snaps the animation; for closing windows it clears the render flag. Cursor navigation helpers: `GetPlace(col,row)`, `GetPlace(dir,col,row)` (nearest in a direction), `GetCornerPlace`, `MovePlace` (with wrap flags 0xb1 bit3/bit4), `SetCursor(cursor, mode)` (nearest place to the cursor's screen position), `Scroll(col,row)` / `Scroll(place)` / `Scroll(rect)`. `AllotPacket()` attaches only the places inside the visible grid window. `SetScrollMark` selects which of the four arrows show.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x18 | `MenuObjTable` | objs |
| 0x24 | `MenuPacket` | packet |
| 0x34 | `WindowRec *` | rec |
| 0x38 | `MenuPlace *` | places |
| 0x3c | `MenuWindowObject *` | frame |
| 0x40 | `ScrollData *` | scroll |
| 0x44 | `ScrollMark *` | mark |
| 0x48 | `MenuObj *` | extra |
| 0x4c | `Scissor` | scissor |
| 0x58 | `u16` | pktqw |
| 0x5c | `s16` | clip_x |
| 0x5e | `s16` | clip_y |
| 0x60 | `s16` | clip_w |
| 0x62 | `s16` | clip_h |
| 0x64 | `f32` | x |
| 0x68 | `f32` | y |
| 0x6c | `f32` | w |
| 0x70 | `f32` | h |
| 0x84 | `s16` | clip0_x |
| 0x86 | `s16` | clip0_y |
| 0x88 | `s16` | clip0_w |
| 0x8a | `s16` | clip0_h |
| 0x8c | `f32` | scroll_x |
| 0x90 | `f32` | scroll_y |
| 0x94 | `s32` | anim_time |
| 0x98 | `f32` | anim_a |
| 0x9c | `f32` | anim_b |
| 0xa0 | `f32` | anim_da |
| 0xa4 | `f32` | anim_db |
| 0xa8 | `u8` | state |
| 0xa9 | `u8` | mark_mask |
| 0xaa | `u8` | env_dirty |
| 0xab | `u8` | env_dirty2 |
| 0xac | `u16` | alpha |
| 0xb0 | `u16` | wflags0 |
| 0xb1 | `u8` | wflags1 |
| 0xb2 | `u16` | wflags2 |

## Virtual table (`__vt__MenuWindow`)

| slot | function |
|---|---|
| 0x08 | `__dt__10MenuWindowFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__10MenuWindowFv` |
| 0x14 | `Update__10MenuWindowFiiUs` |
| 0x18 | `Connect__10MenuWindowFP4_QWD` |
| 0x1c | `Destroy__10MenuWindowFv` |
| 0x20 | `Clear__10MenuWindowFv` |
| 0x2c | `@24@__dt__10MenuWindowFv` |
| 0x38 | `@36@__dt__10MenuWindowFv` |

## Constructed by

`ExitRealize__13GameOverSceneFv`, `GetReady__13GameOverSceneFv`, `__ct__13CmdSoulEnergyFv`, `__ct__14LSDCaptionDataFv`, `__ct__7primWinFv`, `__ct__8BtlBonusFv`, `__ct__8WINParamFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00267e40 | 0xa0 | `__ct__10MenuWindowFv` | `MenuWindow::MenuWindow()` |
| 0x00267ee0 | 0xe4 | `__dt__10MenuWindowFv` | `MenuWindow::~MenuWindow()` |
| 0x00267fd0 | 0x390 | `Create__10MenuWindowFUcUcffff` | `MenuWindow::Create(unsigned char, unsigned char, float, float, float, float)` |
| 0x00268360 | 0x2f8 | `CreateScroll__10MenuWindowFUissffUc` | `MenuWindow::CreateScroll(unsigned int, short, short, float, float, unsigned char)` |
| 0x00268660 | 0xf8 | `CreateScrollMark__10MenuWindowFUc` | `MenuWindow::CreateScrollMark(unsigned char)` |
| 0x00268760 | 0x9c | `AddPlace__10MenuWindowFP9MenuPlace` | `MenuWindow::AddPlace(MenuPlace*)` |
| 0x00268800 | 0xe4 | `RemovePlace__10MenuWindowFP9MenuPlace` | `MenuWindow::RemovePlace(MenuPlace*)` |
| 0x002688f0 | 0xac | `ClearPlace__10MenuWindowFv` | `MenuWindow::ClearPlace()` |
| 0x002689a0 | 0x31c | `GetCornerPlace__10MenuWindowFis` | `MenuWindow::GetCornerPlace(int, short)` |
| 0x00268cc0 | 0xb0 | `GetPlace__10MenuWindowFss` | `MenuWindow::GetPlace(short, short)` |
| 0x00268d70 | 0x7c | `GetPlace__10MenuWindowFs` | `MenuWindow::GetPlace(short)` |
| 0x00268df0 | 0x4c0 | `GetPlace__10MenuWindowFiss` | `MenuWindow::GetPlace(int, short, short)` |
| 0x002692b0 | 0x170 | `MovePlace__10MenuWindowFiss` | `MenuWindow::MovePlace(int, short, short)` |
| 0x00269420 | 0x294 | `SetCursor__10MenuWindowFP6Cursori` | `MenuWindow::SetCursor(Cursor*, int)` |
| 0x002696c0 | 0x1e8 | `Scroll__10MenuWindowFss` | `MenuWindow::Scroll(short, short)` |
| 0x002698b0 | 0x2c4 | `Scroll__10MenuWindowFP9MenuPlace` | `MenuWindow::Scroll(MenuPlace*)` |
| 0x00269b80 | 0x310 | `Scroll__10MenuWindowFP8DrawRect` | `MenuWindow::Scroll(DrawRect*)` |
| 0x00269e90 | 0xa8 | `SetScroll__10MenuWindowFss` | `MenuWindow::SetScroll(short, short)` |
| 0x00269f40 | 0x88 | `FinishScroll__10MenuWindowFv` | `MenuWindow::FinishScroll()` |
| 0x00269fd0 | 0x268 | `Open__10MenuWindowFUci` | `MenuWindow::Open(unsigned char, int)` |
| 0x0026a240 | 0x230 | `Close__10MenuWindowFUci` | `MenuWindow::Close(unsigned char, int)` |
| 0x0026a470 | 0x2a4 | `Finish__10MenuWindowFv` | `MenuWindow::Finish()` |
| 0x0026a720 | 0xf4 | `SetupMove__10MenuWindowFiff` | `MenuWindow::SetupMove(int, float, float)` |
| 0x0026a820 | 0xf4 | `SetupFade__10MenuWindowFif` | `MenuWindow::SetupFade(int, float)` |
| 0x0026a920 | 0x138 | `SetupZoom__10MenuWindowFiUc` | `MenuWindow::SetupZoom(int, unsigned char)` |
| 0x0026aa60 | 0xc8 | `SetPosition__10MenuWindowFff` | `MenuWindow::SetPosition(float, float)` |
| 0x0026ab30 | 0x1d4 | `SetSize__10MenuWindowFff` | `MenuWindow::SetSize(float, float)` |
| 0x0026ad10 | 0x5c | `GetTargetX__10MenuWindowCFv` | `MenuWindow::GetTargetX() const` |
| 0x0026ad70 | 0x5c | `GetTargetY__10MenuWindowCFv` | `MenuWindow::GetTargetY() const` |
| 0x0026add0 | 0x108 | `SetClip__10MenuWindowFUc` | `MenuWindow::SetClip(unsigned char)` |
| 0x0026aee0 | 0x50 | `SetAlpha__10MenuWindowFUc` | `MenuWindow::SetAlpha(unsigned char)` |
| 0x0026af30 | 0xe8 | `SetOffset__10MenuWindowFff` | `MenuWindow::SetOffset(float, float)` |
| 0x0026b020 | 0x6ec | `Polling__10MenuWindowFv` | `MenuWindow::Polling()` |
| 0x0026b710 | 0x53c | `Update__10MenuWindowFiiUs` | `MenuWindow::Update(int, int, unsigned short)` |
| 0x0026bc50 | 0x1c4 | `Connect__10MenuWindowFP4_QWD` | `MenuWindow::Connect(_QWD*)` |
| 0x0026be20 | 0x1cc | `SetScrollMark__10MenuWindowFss` | `MenuWindow::SetScrollMark(short, short)` |
| 0x0026bff0 | 0x374 | `AllotPacket__10MenuWindowFv` | `MenuWindow::AllotPacket()` |
| 0x0026c370 | 0x104 | `ClearWork__10MenuWindowFv` | `MenuWindow::ClearWork()` |
| 0x0026c480 | 0x11c | `Destroy__10MenuWindowFv` | `MenuWindow::Destroy()` |
| 0x0026c660 | 0x140 | `Clear__10MenuWindowFv` | `MenuWindow::Clear()` |
| 0x0026c7a0 | 0x8 | `@24@__dt__10MenuWindowFv` | `@24@__dt__10MenuWindowFv` |
| 0x0026c7b0 | 0x8 | `@36@__dt__10MenuWindowFv` | `@36@__dt__10MenuWindowFv` |

## Rust port

`window::Window`, `WindowStyle`, `Effect`, `MenuRoot`.

## Open questions

- exact metrics of the Frame/Note/Message/Compact decorations (General's layout rule is ported in `Window::layout_deco`)

Decompilation: `decomp/F/MenuWindow.c`
