# CmdHelpExplain

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x428; ctor JP `0x0045bb60`
* embedded sub-objects: `+0xb8 FontDraw`, `+0xf8 FontDraw`, `+0x138 MenuText`, `+0x1b8 MenuMessage`, `+0x250 MenuTexture`, `+0x290 SendOnLocal`, `+0x2c0 MenuSprite`, `+0x320 KeyWait`
* vtable stores: `+8 __vt__14CmdHelpExplain`

| JP addr | size | method |
|---|---|---|
| `0x0045bb60` | 0xdc | `CmdHelpExplain::CmdHelpExplain()` |
| `0x0045bc40` | 0x134 | `CmdHelpExplain::~CmdHelpExplain()` |
| `0x0045bd80` | 0x1dc | `CmdHelpExplain::CreateScene(CmdHelp*)` |
| `0x0045bf60` | 0x34c | `CmdHelpExplain::UpdateScene(CmdHelp*, short)` |
| `0x0045c2b0` | 0x2a0 | `CmdHelpExplain::SetExplanation(CmdHelp*, short)` |
| `0x0045c550` | 0xfcc | `CmdHelpExplain::Run(CmdHelp*)` |
| `0x0045d520` | 0x8 | `CmdHelpExplain::~CmdHelpExplain()` |
| `0x0045d530` | 0x8 | `CmdHelpExplain::~CmdHelpExplain()` |

Decompiled source: `decomp/G/CmdHelpExplain.c`.
