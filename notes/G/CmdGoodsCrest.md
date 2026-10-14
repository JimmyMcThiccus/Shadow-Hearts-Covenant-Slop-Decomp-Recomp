# CmdGoodsCrest

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x1c8; ctor JP `0x004950b0`
* embedded sub-objects: `+0xb4 SendOnLocal`, `+0xe4 SendOnLocal`, `+0x114 SendOnLocal`, `+0x144 SendOnLocal`, `+0x174 FontDraw`
* vtable stores: `+8 __vt__13CmdGoodsCrest`

| JP addr | size | method |
|---|---|---|
| `0x004950b0` | 0xbc | `CmdGoodsCrest::CmdGoodsCrest()` |
| `0x00495170` | 0x188 | `CmdGoodsCrest::~CmdGoodsCrest()` |
| `0x00495430` | 0x484 | `CmdGoodsCrest::CreateScene(MenuScene*, short, short, short)` |
| `0x004959b0` | 0xd4 | `CmdGoodsCrest::CreateImage(MenuTexture*)` |
| `0x00495a90` | 0x12c | `CmdGoodsCrest::Select(MenuScene*, CmdNote*, MenuGroup*, MenuGroup*)` |
| `0x00495bc0` | 0xe4 | `CmdGoodsCrest::SetClut(MenuGroup*, unsigned char)` |
| `0x00495cb0` | 0x7c | `CmdGoodsCrest::Start()` |
| `0x00495d30` | 0x54 | `CmdGoodsCrest::Reset()` |
| `0x00495d90` | 0x57c | `CmdGoodsCrest::SetCrest(MenuScene*, short, int, int)` |
| `0x00496310` | 0x8 | `CmdGoodsCrest::~CmdGoodsCrest()` |
| `0x00496320` | 0x8 | `CmdGoodsCrest::~CmdGoodsCrest()` |

Decompiled source: `decomp/G/CmdGoodsCrest.c`.
