# CmdGoodsTarot

Context: see `cmd_menu_system.md`.

* base: `MenuGroup`; allocation size: unknown; ctor JP `0x00456210`
* embedded sub-objects: `+0x50 MenuSprite`, `+0xb0 MenuText`

| JP addr | size | method |
|---|---|---|
| `0x00455e60` | 0x8c | `CmdGoodsTarot::~CmdGoodsTarot()` |
| `0x00456210` | 0x4c | `CmdGoodsTarot::CmdGoodsTarot()` |

Decompiled source: `decomp/G/CmdGoodsTarot.c`.
