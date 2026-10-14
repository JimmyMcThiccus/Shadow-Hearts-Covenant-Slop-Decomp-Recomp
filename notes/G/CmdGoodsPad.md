# CmdGoodsPad

Context: see `cmd_menu_system.md`.

* base: `MenuGroup`; allocation size: unknown; ctor JP `0x0047a010`
* embedded sub-objects: `+0x50 MenuSprite`, `+0xb0 MenuSprite`

| JP addr | size | method |
|---|---|---|
| `0x00479f60` | 0xac | `CmdGoodsPad::~CmdGoodsPad()` |
| `0x0047a010` | 0x74 | `CmdGoodsPad::CmdGoodsPad()` |

Decompiled source: `decomp/G/CmdGoodsPad.c`.
