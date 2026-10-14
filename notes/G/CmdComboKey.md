# CmdComboKey

Context: see `cmd_menu_system.md`.

* base: `CmdPCScene`; allocation size: 0xcc0; ctor JP `0x00485ef0`
* embedded sub-objects: `+0x88 CmdComboKeySlot`, `+0xad0 CmdSubTitle`
* vtable stores: `+8 __vt__11CmdComboKey`

| JP addr | size | method |
|---|---|---|
| `0x00485ef0` | 0xb4 | `CmdComboKey::CmdComboKey()` |
| `0x00485fb0` | 0x184 | `CmdComboKey::~CmdComboKey()` |
| `0x00486140` | 0x1fc | `CmdComboKey::GetReady()` |
| `0x00486340` | 0x104 | `CmdComboKey::Run()` |
| `0x00486450` | 0x1b8 | `CmdComboKey::Update(short)` |
| `0x00486610` | 0x10c | `CmdComboKey::UpdateCommand(short)` |
| `0x00486720` | 0xfc | `CmdComboKey::UpdateCharacter(short)` |
| `0x00486820` | 0x104 | `CmdComboKey::UpdateGoods(short, short)` |
| `0x00486930` | 0x170 | `CmdComboKey::UpdateFence(CmdFence*, short, short, short)` |
| `0x00486aa0` | 0x140 | `CmdComboKey::CreateMask(short)` |
| `0x00486be0` | 0x16c | `CmdComboKey::IsComboKeyData(SHORTCUTCommand*, char, short)` |
| `0x00486d50` | 0xdc | `CmdComboKey::StartButtonReport()` |
| `0x00486e30` | 0x188 | `CmdComboKey::SetComboKeyGoods(short, CmdGoodsComboKey*)` |
| `0x00486fc0` | 0xe0 | `CmdComboKey::SetSlot(short, short, short)` |
| `0x004870a0` | 0x170 | `CmdComboKey::SelectSlot(short, MenuPlace*, MenuPlace*)` |
| `0x00487210` | 0x280 | `CmdComboKey::Enter()` |
| `0x00487490` | 0x28c | `CmdComboKey::Exit()` |
| `0x00487720` | 0x420 | `CmdComboKey::SelectSlot()` |
| `0x00487b40` | 0x290 | `CmdComboKey::SelectCharacter()` |
| `0x00487dd0` | 0x414 | `CmdComboKey::SelectCommand()` |
| `0x004881f0` | 0x420 | `CmdComboKey::SelectComboKey()` |

Decompiled source: `decomp/G/CmdComboKey.c`.
