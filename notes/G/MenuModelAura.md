# MenuModelAura

Context: see `cmd_menu_system.md`.

* base: `MenuModelManeger`; allocation size: 0x1bc; ctor JP `0x004999f0`
* vtable stores: `+0x14 __vt__13MenuModelAura`

| JP addr | size | method |
|---|---|---|
| `0x004999f0` | 0x11c | `MenuModelAura::MenuModelAura()` |
| `0x00499b10` | 0xd4 | `MenuModelAura::~MenuModelAura()` |
| `0x00499bf0` | 0x70c | `MenuModelAura::CreateAura(MenuModelManeger*, MenuAuraData*)` |
| `0x0049a3c0` | 0x234 | `MenuModelAura::Boot()` |
| `0x0049a600` | 0x150 | `MenuModelAura::Standby(unsigned char)` |
| `0x0049a750` | 0x38 | `MenuModelAura::Close()` |
| `0x0049a790` | 0xe4 | `MenuModelAura::CloseEffect()` |
| `0x0049a880` | 0x5f0 | `MenuModelAura::Polling()` |
| `0x0049ae70` | 0x104 | `MenuModelAura::Event(MenuModel*, const char*, const char*)` |

Decompiled source: `decomp/G/MenuModelAura.c`.
