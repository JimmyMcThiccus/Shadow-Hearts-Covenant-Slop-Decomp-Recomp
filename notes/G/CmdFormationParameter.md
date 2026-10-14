# CmdFormationParameter

Context: see `cmd_menu_system.md`.

* base: `MenuGroup`; allocation size: unknown; ctor JP `0x004802f0`
* embedded sub-objects: `+0x50 MenuTexture`, `+0x90 SendOnLocal`, `+0xc0 MenuSprite`, `+0x120 MenuText`, `+0x960 MenuSprite`

| JP addr | size | method |
|---|---|---|
| `0x0047f6b0` | 0x164 | `CmdFormationParameter::~CmdFormationParameter()` |
| `0x004802f0` | 0x144 | `CmdFormationParameter::CmdFormationParameter()` |

Decompiled source: `decomp/G/CmdFormationParameter.c`.
