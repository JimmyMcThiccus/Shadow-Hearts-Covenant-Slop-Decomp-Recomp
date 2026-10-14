# MenuModelAuraPacket

Context: see `cmd_menu_system.md`.

* base: `VI`; allocation size: unknown; ctor JP `0x00499240`
* vtable stores: `+16 __vt__19MenuModelAuraPacket`

| JP addr | size | method |
|---|---|---|
| `0x00499240` | 0x4c | `MenuModelAuraPacket::MenuModelAuraPacket()` |
| `0x00499290` | 0x9c | `MenuModelAuraPacket::~MenuModelAuraPacket()` |
| `0x00499330` | 0x3b8 | `MenuModelAuraPacket::Create(short, unsigned char)` |
| `0x004996f0` | 0xd8 | `MenuModelAuraPacket::SetAura(_QWD*, int, int)` |
| `0x004997d0` | 0x4c | `MenuModelAuraPacket::Run()` |
| `0x00499820` | 0x1c8 | `MenuModelAuraPacket::getPacket()` |

Decompiled source: `decomp/G/MenuModelAuraPacket.c`.
