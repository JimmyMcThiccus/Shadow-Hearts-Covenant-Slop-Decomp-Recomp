# CmdTechnique

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0x8c; ctor JP `0x00453540`
* vtable stores: `+8 __vt__12CmdTechnique`

| JP addr | size | method |
|---|---|---|
| `0x00453540` | 0x44 | `CmdTechnique::CmdTechnique()` |
| `0x00453590` | 0x74 | `CmdTechnique::~CmdTechnique()` |
| `0x00453610` | 0x4a8 | `CmdTechnique::GetReady()` |
| `0x00453ac0` | 0x68 | `CmdTechnique::Run()` |
| `0x00453b30` | 0x78 | `CmdTechnique::SafeDelayDelete()` |
| `0x00453bb0` | 0xac | `CmdTechnique::Close()` |
| `0x00453c60` | 0x124 | `CmdTechnique::ReadyScene()` |
| `0x00453d90` | 0x144 | `CmdTechnique::Enter()` |
| `0x00453ee0` | 0x1d4 | `CmdTechnique::SelectGoods()` |
| `0x004540c0` | 0x10 | `CmdTechnique::Release()` |

Decompiled source: `decomp/G/CmdTechnique.c`.
