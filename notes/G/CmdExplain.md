# CmdExplain

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x52c; ctor JP `0x0043ea00`
* embedded sub-objects: `+0x6c MenuWindow`, `+0x120 KeyWait`, `+0x1fc FontDraw`, `+0x23c MenuMessage`, `+0x2d4 FontDraw`, `+0x314 MenuText`, `+0x394 MenuText`
* vtable stores: `+8 __vt__10CmdExplain`

| JP addr | size | method |
|---|---|---|
| `0x0043ea00` | 0x1b8 | `CmdExplain::CmdExplain()` |
| `0x0043ebc0` | 0x1ec | `CmdExplain::~CmdExplain()` |
| `0x0043edb0` | 0x1b8 | `CmdExplain::GetReady()` |
| `0x0043ef70` | 0x5c | `CmdExplain::DelayDelete()` |
| `0x0043efd0` | 0x100 | `CmdExplain::SetInfo(Menu*, short, unsigned char, unsigned char)` |
| `0x0043f0d0` | 0x148 | `CmdExplain::SetIcon(MenuTexture*)` |
| `0x0043f220` | 0x1b8 | `CmdExplain::SetImage(char*, short, short)` |
| `0x0043f3e0` | 0xac | `CmdExplain::DestroyImage()` |
| `0x0043f490` | 0x7f4 | `CmdExplain::Exec(unsigned short)` |
| `0x0043fc90` | 0x3cc | `CmdExplain::Open()` |
| `0x00440060` | 0x44 | `CmdExplain::Close()` |
| `0x004400b0` | 0xc8 | `CmdExplain::Reset()` |
| `0x00440180` | 0xb4 | `CmdExplain::SendPage()` |
| `0x00440240` | 0xac | `CmdExplain::SetExplanation(char*)` |

Decompiled source: `decomp/G/CmdExplain.c`.
