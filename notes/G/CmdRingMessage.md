# CmdRingMessage

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x3e4; ctor JP `0x0046e710`
* embedded sub-objects: `+0x5c Cursor`, `+0x158 MenuWindow`, `+0x20c FontDraw`, `+0x24c MenuMessage`
* vtable stores: `+8 __vt__14CmdRingMessage`

| JP addr | size | method |
|---|---|---|
| `0x0046e710` | 0xa4 | `CmdRingMessage::CmdRingMessage()` |
| `0x0046e7c0` | 0xe4 | `CmdRingMessage::~CmdRingMessage()` |
| `0x0046e8b0` | 0x130 | `CmdRingMessage::GetReady()` |
| `0x0046e9e0` | 0x238 | `CmdRingMessage::Run()` |
| `0x0046ec20` | 0x218 | `CmdRingMessage::StartMessage(short, char*)` |

Decompiled source: `decomp/G/CmdRingMessage.c`.
