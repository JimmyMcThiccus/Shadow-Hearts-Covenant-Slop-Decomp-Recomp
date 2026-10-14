# MenuScene

Base class: `DelayDeleteObject`

A loaded `.MSD` scene. `OrderFile(path, menu)` queues a DVD read (`pDataPath + path`); the callback `ReadScene` relocates pointers (`MenuDataTable::Convert`) and `Initialize(data, buf)` indexes the chunk list into `tab_* @0x24..0x54` by chunk type, then the virtual `GetReady()` (+0x14) builds the widgets. `SetData(index, widget)` overloads fill a freshly created widget from record `index` (FontDraw 0x10, Cursor 0xc, Window 0x1c, Group 0x18, Sprite 0x20, Polygon 0x3c, Text 0x1c, Message 0x20, Font 0x1c, FontItalic 0x18 byte records). `FindAttachFile(id)` finds an embedded blob. `MoveVertical(keys)` maps pad bits to `MoveCursor/SkipCursor` on the scene cursor.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0xc | `BufMemory *` | heap |
| 0x10 | `Menu *` | menu |
| 0x18 | `Cursor *` | cursor |
| 0x1c | `s16` | scene_id |
| 0x20 | `u8` | ready |
| 0x22 | `u8` | s22 |
| 0x23 | `u8` | sflags |
| 0x24 | `Chunk *` | tab_resource |
| 0x28 | `Chunk *` | tab_text |
| 0x2c | `Chunk *` | tab_fontdraw |
| 0x30 | `Chunk *` | tab_cursor |
| 0x34 | `Chunk *` | tab_window |
| 0x38 | `Chunk *` | tab_group |
| 0x3c | `Chunk *` | tab_sprite |
| 0x40 | `Chunk *` | tab_polygon |
| 0x44 | `Chunk *` | tab_text2 |
| 0x48 | `Chunk *` | tab_message |
| 0x4c | `Chunk *` | tab_font |
| 0x50 | `Chunk *` | tab_italic |
| 0x54 | `Chunk *` | tab_attach |

## Virtual table (`__vt__MenuScene`)

| slot | function |
|---|---|
| 0x08 | `__dt__9MenuSceneFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `GetRealHeap__9MenuSceneFP9BufMemoryi` |
| 0x14 | `GetReady__9MenuSceneFv` |
| 0x18 | `Release__9MenuSceneFv` |
| 0x1c | `Run__9MenuSceneFv` |
| 0x20 | `Shutdown__9MenuSceneFv` |
| 0x24 | `Restore__9MenuSceneFv` |

## Constructed by

`__ct__10MenuCommonFv`, `__ct__13CmdSoulEnergyFv`, `__ct__13GameOverSceneFv`, `__ct__13MenuFieldDataFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00279320 | 0x7c | `ReadScene__9MenuSceneFiP9BufMemoryiPcPv` | `MenuScene::ReadScene(int, BufMemory*, int, char*, void*)` |
| 0x002793a0 | 0xac | `__ct__9MenuSceneFv` | `MenuScene::MenuScene()` |
| 0x00279450 | 0x94 | `__dt__9MenuSceneFv` | `MenuScene::~MenuScene()` |
| 0x002794f0 | 0x7c | `OrderFile__9MenuSceneFPCcP4Menu` | `MenuScene::OrderFile(const char*, Menu*)` |
| 0x00279570 | 0xd4 | `Initialize__9MenuSceneFPUcP9BufMemory` | `MenuScene::Initialize(unsigned char*, BufMemory*)` |
| 0x00279650 | 0x178 | `MoveVertical__9MenuSceneFi` | `MenuScene::MoveVertical(int)` |
| 0x002797d0 | 0xb0 | `FindAttachFile__9MenuSceneCFs` | `MenuScene::FindAttachFile(short) const` |
| 0x00279880 | 0xbc | `SetData__9MenuSceneFUsP8FontDraw` | `MenuScene::SetData(unsigned short, FontDraw*)` |
| 0x00279940 | 0x1bc | `SetData__9MenuSceneFUsP6Cursor` | `MenuScene::SetData(unsigned short, Cursor*)` |
| 0x00279b00 | 0x384 | `SetData__9MenuSceneFUsP10MenuWindow` | `MenuScene::SetData(unsigned short, MenuWindow*)` |
| 0x00279e90 | 0x1f8 | `SetData__9MenuSceneFUsP9MenuGroup` | `MenuScene::SetData(unsigned short, MenuGroup*)` |
| 0x0027a090 | 0x308 | `SetData__9MenuSceneFUsP10MenuSprite` | `MenuScene::SetData(unsigned short, MenuSprite*)` |
| 0x0027a3a0 | 0x308 | `SetData__9MenuSceneFUsP11MenuPolygon` | `MenuScene::SetData(unsigned short, MenuPolygon*)` |
| 0x0027a6b0 | 0x388 | `SetData__9MenuSceneFUsP8MenuText` | `MenuScene::SetData(unsigned short, MenuText*)` |
| 0x0027aa40 | 0x3a8 | `SetData__9MenuSceneFUsP11MenuMessage` | `MenuScene::SetData(unsigned short, MenuMessage*)` |
| 0x0027adf0 | 0x280 | `SetData__9MenuSceneFUsP8MenuFont` | `MenuScene::SetData(unsigned short, MenuFont*)` |
| 0x0027b070 | 0x1d4 | `SetData__9MenuSceneFUsP14MenuFontItalic` | `MenuScene::SetData(unsigned short, MenuFontItalic*)` |
| 0x0027b250 | 0x1c | `GetRealHeap__9MenuSceneFP9BufMemoryi` | `MenuScene::GetRealHeap(BufMemory*, int)` |
| 0x0027b270 | 0x14 | `GetReady__9MenuSceneFv` | `MenuScene::GetReady()` |
| 0x0027b290 | 0x54 | `Release__9MenuSceneFv` | `MenuScene::Release()` |
| 0x0027b2f0 | 0x14 | `Run__9MenuSceneFv` | `MenuScene::Run()` |
| 0x0027b310 | 0x10 | `Shutdown__9MenuSceneFv` | `MenuScene::Shutdown()` |
| 0x0027b320 | 0x10 | `Restore__9MenuSceneFv` | `MenuScene::Restore()` |

## Rust port

`scene::Scene`, `msd::Msd`, `SceneLogic`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuScene.c`
