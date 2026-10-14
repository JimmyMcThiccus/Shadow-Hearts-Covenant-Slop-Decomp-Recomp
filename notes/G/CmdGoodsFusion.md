# CmdGoodsFusion

Context: see `cmd_menu_system.md`.

* base: `MenuGroup`; allocation size: unknown; ctor JP `0x004739f0`
* embedded sub-objects: `+0x50 MenuText`, `+0xd0 MenuText`, `+0x150 MenuText`

| JP addr | size | method |
|---|---|---|
| `0x00473730` | 0x9c | `CmdGoodsFusion::~CmdGoodsFusion()` |
| `0x004739f0` | 0x5c | `CmdGoodsFusion::CmdGoodsFusion()` |

Decompiled source: `decomp/G/CmdGoodsFusion.c`.
