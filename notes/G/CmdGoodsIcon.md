# CmdGoodsIcon

Context: see `cmd_menu_system.md`.

* base: `MenuGroup`; allocation size: unknown; ctor JP `0x00450610`
* embedded sub-objects: `+0x50 MenuText`, `+0xd0 MenuText`, `+0x150 MenuSprite`

| JP addr | size | method |
|---|---|---|
| `0x004502f0` | 0xac | `CmdGoodsIcon::~CmdGoodsIcon()` |
| `0x00450610` | 0x60 | `CmdGoodsIcon::CmdGoodsIcon()` |

Decompiled source: `decomp/G/CmdGoodsIcon.c`.
