# CmdGoodsCrestData

Context: see `cmd_menu_system.md`.

* base: `MenuGroup`; allocation size: unknown; ctor JP `0x004958c0`
* embedded sub-objects: `+0x50 MenuText`, `+0xd0 MenuText`, `+0x150 MenuPolygon`, `+0x1d4 MenuSprite`, `+0x534 MenuSprite`, `+0x594 MenuSprite`, `+0x5f4 MenuBar`

| JP addr | size | method |
|---|---|---|
| `0x00495300` | 0x12c | `CmdGoodsCrestData::~CmdGoodsCrestData()` |
| `0x004958c0` | 0xec | `CmdGoodsCrestData::CmdGoodsCrestData()` |

Decompiled source: `decomp/G/CmdGoodsCrestData.c`.
