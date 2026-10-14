# CmdCrest

Context: see `cmd_menu_system.md`.

* base: `CmdPCScene`; allocation size: 0x9c0; ctor JP `0x00490ca0`
* embedded sub-objects: `+0x88 MenuScene`, `+0xe0 MenuScene`, `+0x1f8 CmdSubMenu`, `+0x350 CmdCrestPCInfo`
* vtable stores: `+8 __vt__8CmdCrest`

| JP addr | size | method |
|---|---|---|
| `0x00490ca0` | 0xd8 | `CmdCrest::CmdCrest()` |
| `0x00490d80` | 0x204 | `CmdCrest::~CmdCrest()` |
| `0x00490f90` | 0x400 | `CmdCrest::GetReady()` |
| `0x00491390` | 0x104 | `CmdCrest::Run()` |
| `0x004914a0` | 0x31c | `CmdCrest::Update(short)` |
| `0x004917c0` | 0x27c | `CmdCrest::UpdateSlot(short)` |
| `0x00491a40` | 0x3c4 | `CmdCrest::UpdateGoods(short, short, short)` |
| `0x00491e10` | 0x114 | `CmdCrest::UpdateCrestMagic(short, short, char)` |
| `0x00491f30` | 0x148 | `CmdCrest::CreateEquipCrest()` |
| `0x00492080` | 0x190 | `CmdCrest::Disarm(short)` |
| `0x00492210` | 0x30c | `CmdCrest::Recommend()` |
| `0x00492520` | 0xb0 | `CmdCrest::SetMenu(char, short)` |
| `0x004925d0` | 0x338 | `CmdCrest::StartDetail()` |
| `0x00492910` | 0x18c | `CmdCrest::SetButtonReport()` |
| `0x00492aa0` | 0xc0 | `CmdCrest::UpdateComboKeyMagic()` |
| `0x00492b60` | 0x1d4 | `CmdCrest::Enter()` |
| `0x00492d40` | 0x274 | `CmdCrest::Exit()` |
| `0x00492fc0` | 0x2e0 | `CmdCrest::ShiftMenu()` |
| `0x004932a0` | 0x310 | `CmdCrest::SelectMenu()` |
| `0x004935b0` | 0x320 | `CmdCrest::SelectDisarm()` |
| `0x004938d0` | 0x4b0 | `CmdCrest::SelectSlot()` |
| `0x00493d80` | 0x7dc | `CmdCrest::SelectGoods()` |
| `0x00494560` | 0x220 | `CmdCrest::EnterDetail()` |
| `0x00494780` | 0x3d0 | `CmdCrest::ExitDetail()` |
| `0x00494b50` | 0x290 | `CmdCrest::ExecDetail()` |
| `0x00494de0` | 0x2c8 | `CmdCrest::ExecSort()` |

Decompiled source: `decomp/G/CmdCrest.c`.
