# CmdNoteMessage

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x2b0; ctor JP `0x00483150`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 MenuText`, `+0x174 MenuSprite`, `+0x1d4 KeyWait`
* vtable stores: `+8 __vt__14CmdNoteMessage`

| JP addr | size | method |
|---|---|---|
| `0x00483150` | 0x9c | `CmdNoteMessage::CmdNoteMessage()` |
| `0x004831f0` | 0xe4 | `CmdNoteMessage::~CmdNoteMessage()` |
| `0x004832e0` | 0x1f8 | `CmdNoteMessage::CreateScene(MenuScene*, char*, int)` |
| `0x004834e0` | 0xc8 | `CmdNoteMessage::Run(unsigned short)` |
| `0x004835b0` | 0x44 | `CmdNoteMessage::DelayDelete()` |
| `0x00483600` | 0x8 | `CmdNoteMessage::~CmdNoteMessage()` |
| `0x00483610` | 0x8 | `CmdNoteMessage::~CmdNoteMessage()` |

Decompiled source: `decomp/G/CmdNoteMessage.c`.
