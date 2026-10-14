# CmdWhiteMagic

Context: see `cmd_menu_system.md`.

* base: `CmdPCScene`; allocation size: 0x360; ctor JP `0x00496330`
* embedded sub-objects: `+0x88 CmdTechniqueGoods`, `+0x180 CmdSubTitle`
* vtable stores: `+8 __vt__13CmdWhiteMagic`

| JP addr | size | method |
|---|---|---|
| `0x00496330` | 0x5c | `CmdWhiteMagic::CmdWhiteMagic()` |
| `0x00496390` | 0xb4 | `CmdWhiteMagic::~CmdWhiteMagic()` |
| `0x00496450` | 0x388 | `CmdWhiteMagic::GetReady()` |
| `0x004967e0` | 0xe4 | `CmdWhiteMagic::Run()` |
| `0x004968d0` | 0x2d0 | `CmdWhiteMagic::Enter()` |
| `0x00496ba0` | 0x24c | `CmdWhiteMagic::Exit()` |
| `0x00496df0` | 0x418 | `CmdWhiteMagic::SelectGoods()` |
| `0x00497210` | 0x280 | `CmdWhiteMagic::ExecSelectTarget()` |

Decompiled source: `decomp/G/CmdWhiteMagic.c`.
