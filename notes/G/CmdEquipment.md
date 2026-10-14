# CmdEquipment

Context: see `cmd_menu_system.md`.

* base: `CmdPCScene`; allocation size: 0xd0; ctor JP `0x0044b820`
* vtable stores: `+8 __vt__12CmdEquipment`

| JP addr | size | method |
|---|---|---|
| `0x0044b820` | 0x84 | `CmdEquipment::CmdEquipment()` |
| `0x0044b8b0` | 0x18c | `CmdEquipment::~CmdEquipment()` |
| `0x0044ba40` | 0x3fc | `CmdEquipment::GetReady()` |
| `0x0044be40` | 0x104 | `CmdEquipment::Run()` |
| `0x0044bf50` | 0x1cc | `CmdEquipment::Update(short)` |
| `0x0044c120` | 0x258 | `CmdEquipment::UpdateSlot(short, short)` |
| `0x0044c380` | 0x140 | `CmdEquipment::UpdateStatus(short, CmdPCStatus*)` |
| `0x0044c4c0` | 0x1b4 | `CmdEquipment::UpdateGoods(short, char, char)` |
| `0x0044c680` | 0x410 | `CmdEquipment::SetProperty(char, unsigned short)` |
| `0x0044ca90` | 0xc4 | `CmdEquipment::GetPropertyMax()` |
| `0x0044cb60` | 0x1fc | `CmdEquipment::GetPropertyCount(char)` |
| `0x0044cd60` | 0x3fc | `CmdEquipment::StartExplain(short)` |
| `0x0044d160` | 0x14c | `CmdEquipment::SetExplanation()` |
| `0x0044d2b0` | 0xb0 | `CmdEquipment::SetButtonReport(short, short)` |
| `0x0044d360` | 0x2bc | `CmdEquipment::Enter()` |
| `0x0044d620` | 0x2c0 | `CmdEquipment::Exit()` |
| `0x0044d8e0` | 0x68c | `CmdEquipment::SelectMenu()` |
| `0x0044df70` | 0x490 | `CmdEquipment::SelectSlot()` |
| `0x0044e400` | 0x3d0 | `CmdEquipment::SelectEquipment()` |
| `0x0044e7d0` | 0x198 | `CmdEquipment::ShiftExplain()` |
| `0x0044e970` | 0x3b0 | `CmdEquipment::ExecExplain()` |

Decompiled source: `decomp/G/CmdEquipment.c`.
