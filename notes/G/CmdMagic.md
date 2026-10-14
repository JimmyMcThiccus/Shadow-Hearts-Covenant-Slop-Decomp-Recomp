# CmdMagic

Context: see `cmd_menu_system.md`.

* base: `CmdPCScene`; allocation size: 0x368; ctor JP `0x0048d2b0`
* embedded sub-objects: `+0x88 CmdMagicGoods`, `+0x180 CmdSubTitle`
* vtable stores: `+8 __vt__8CmdMagic`

| JP addr | size | method |
|---|---|---|
| `0x0048d2b0` | 0x6c | `CmdMagic::CmdMagic()` |
| `0x0048d320` | 0xe4 | `CmdMagic::~CmdMagic()` |
| `0x0048d410` | 0x308 | `CmdMagic::GetReady()` |
| `0x0048d720` | 0x104 | `CmdMagic::Run()` |
| `0x0048d830` | 0x20c | `CmdMagic::Update(short)` |
| `0x0048da40` | 0x274 | `CmdMagic::Enter()` |
| `0x0048dcc0` | 0x280 | `CmdMagic::Exit()` |
| `0x0048df40` | 0x600 | `CmdMagic::SelectGoods()` |
| `0x0048e540` | 0x278 | `CmdMagic::ExecSelectTarget()` |
| `0x0048e7c0` | 0x218 | `CmdMagic::ExecSort()` |

Decompiled source: `decomp/G/CmdMagic.c`.
