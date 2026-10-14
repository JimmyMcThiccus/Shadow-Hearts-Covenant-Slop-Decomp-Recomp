# CmdGraveyard

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x31c; ctor JP `0x0045e680`
* embedded sub-objects: `+0x6c CmdGraveyardMenu`, `+0x2e0 Smooth`
* vtable stores: `+8 __vt__12CmdGraveyard`

| JP addr | size | method |
|---|---|---|
| `0x0045e680` | 0x94 | `CmdGraveyard::CmdGraveyard()` |
| `0x0045e720` | 0x9c | `CmdGraveyard::~CmdGraveyard()` |
| `0x0045e7c0` | 0xb8 | `CmdGraveyard::GetReady()` |
| `0x0045e880` | 0x5c | `CmdGraveyard::Run()` |
| `0x0045e8e0` | 0x23c | `CmdGraveyard::Enter()` |
| `0x0045eb20` | 0x19c | `CmdGraveyard::Exit()` |
| `0x0045ecc0` | 0x230 | `CmdGraveyard::SelectMenu()` |
| `0x0045eef0` | 0x168 | `CmdGraveyard::JumpGraveyard()` |

Decompiled source: `decomp/G/CmdGraveyard.c`.
