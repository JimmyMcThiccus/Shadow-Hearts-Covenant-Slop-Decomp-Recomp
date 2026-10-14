# CmdMenuTutorial

Context: see `cmd_menu_system.md`.

* base: `CmdMenu`; allocation size: unknown; ctor JP `0x00473fc0`
* embedded sub-objects: `+0x180c MenuWindow`, `+0x18c0 FontDraw`, `+0x1900 MenuMessage`, `+0x1998 KeyWait`
* vtable stores: `+0x14 __vt__15CmdMenuTutorial`

| JP addr | size | method |
|---|---|---|
| `0x00473fc0` | 0xb8 | `CmdMenuTutorial::CmdMenuTutorial()` |
| `0x00474080` | 0xe4 | `CmdMenuTutorial::~CmdMenuTutorial()` |
| `0x00474170` | 0xa0 | `CmdMenuTutorial::StartTutorial(short, int(*)(int, void*, CmdMenu*)*, void*)` |
| `0x00474250` | 0x28c | `CmdMenuTutorial::Create(BufMemory*)` |
| `0x004744e0` | 0x708 | `CmdMenuTutorial::Polling()` |
| `0x00474bf0` | 0x10 | `CmdMenuTutorial::GetKey()` |
| `0x00474c00` | 0x8 | `CmdMenuTutorial::~CmdMenuTutorial()` |

Decompiled source: `decomp/G/CmdMenuTutorial.c`.
