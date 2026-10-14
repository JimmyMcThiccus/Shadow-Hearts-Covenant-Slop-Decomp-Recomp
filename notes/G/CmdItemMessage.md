# CmdItemMessage

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x268; ctor JP `0x0045e1e0`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 MenuMessage`, `+0x18c KeyWait`
* vtable stores: `+8 __vt__14CmdItemMessage`

| JP addr | size | method |
|---|---|---|
| `0x0045e1e0` | 0x8c | `CmdItemMessage::CmdItemMessage()` |
| `0x0045e270` | 0xcc | `CmdItemMessage::~CmdItemMessage()` |
| `0x0045e340` | 0x16c | `CmdItemMessage::CreateScene(CmdItem*)` |
| `0x0045e4b0` | 0x1a8 | `CmdItemMessage::Run(unsigned short)` |
| `0x0045e660` | 0x8 | `CmdItemMessage::~CmdItemMessage()` |
| `0x0045e670` | 0x8 | `CmdItemMessage::~CmdItemMessage()` |

Decompiled source: `decomp/G/CmdItemMessage.c`.
