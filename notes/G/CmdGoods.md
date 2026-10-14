# CmdGoods

Context: see `cmd_menu_system.md`.

* base: `MenuGroup`; allocation size: unknown; ctor JP `0x00454640`
* embedded sub-objects: `+0x50 MenuText`, `+0xd0 MenuText`

| JP addr | size | method |
|---|---|---|
| `0x00450670` | 0x8c | `CmdGoods::~CmdGoods()` |
| `0x00454640` | 0x4c | `CmdGoods::CmdGoods()` |

Decompiled source: `decomp/G/CmdGoods.c`.
