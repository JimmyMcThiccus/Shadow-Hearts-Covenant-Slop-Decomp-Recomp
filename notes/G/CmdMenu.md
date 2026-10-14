# CmdMenu

Context: see `cmd_menu_system.md`.

* base: `Menu`; allocation size: 0x17f8; ctor JP `0x00435860`
* embedded sub-objects: `+0x70 MenuRender`, `+0xb8 CmdParty`, `+0x348 CmdCommon`, `+0x4e0 CmdNote`, `+0x780 CmdTitleLog`, `+0xa60 CmdButtonReport`, `+0x10f0 CmdElement`, `+0x17a0 MenuScene`
* vtable stores: `+0x14 __vt__7CmdMenu`

| JP addr | size | method |
|---|---|---|
| `0x00435610` | 0x12c | `CmdMenu::DataEvent(int, void*)` |
| `0x00435740` | 0x4c | `CmdMenu::SolomonEvent(int, void*)` |
| `0x00435790` | 0xc8 | `CmdMenu::SetParameter(MenuText*, short, short)` |
| `0x00435860` | 0x104 | `CmdMenu::CmdMenu(short, int(*)(int, void*, CmdMenu*)*, void*)` |
| `0x00435970` | 0x12c | `CmdMenu::~CmdMenu()` |
| `0x00435aa0` | 0x7b4 | `CmdMenu::Polling()` |
| `0x00436260` | 0x12c | `CmdMenu::Active(short)` |
| `0x00436390` | 0x6e4 | `CmdMenu::Ready(short, short, short)` |
| `0x00436a80` | 0x180 | `CmdMenu::Initialize(short, int(*)(int, void*, CmdMenu*)*, void*)` |
| `0x00436c00` | 0x170 | `CmdMenu::Release()` |
| `0x00436d70` | 0x1a4 | `CmdMenu::CreateScene()` |
| `0x00436f20` | 0xac | `CmdMenu::ReleaseScene()` |
| `0x00436fd0` | 0x70 | `CmdMenu::MapJump(short)` |
| `0x00437040` | 0x304 | `CmdMenu::CreateBackGround(short)` |
| `0x00437350` | 0x94 | `CmdMenu::DestroyBackGround(short)` |
| `0x004373f0` | 0xdc | `CmdMenu::SetCamera(MenuDataModel*)` |
| `0x004374d0` | 0x74 | `CmdMenu::IsSetupScene()` |
| `0x00437550` | 0x168 | `CmdMenu::CreateLight()` |
| `0x004376c0` | 0x68 | `CmdMenu::ReleaseLight()` |
| `0x00437730` | 0x8 | `CmdMenu::~CmdMenu()` |

Decompiled source: `decomp/G/CmdMenu.c`.
