# CmdComboMagic

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x188; ctor JP `0x0048c130`
* embedded sub-objects: `+0x68 FontDraw`, `+0xa8 MenuWindow`
* vtable stores: `+8 __vt__13CmdComboMagic`

| JP addr | size | method |
|---|---|---|
| `0x0048c130` | 0x94 | `CmdComboMagic::CmdComboMagic()` |
| `0x0048c1d0` | 0xec | `CmdComboMagic::~CmdComboMagic()` |
| `0x0048c2c0` | 0x7b0 | `CmdComboMagic::GetReady()` |
| `0x0048ca70` | 0x5c | `CmdComboMagic::Run()` |
| `0x0048cad0` | 0x1f4 | `CmdComboMagic::Enter()` |
| `0x0048ccd0` | 0x238 | `CmdComboMagic::Exit()` |
| `0x0048cf10` | 0x140 | `CmdComboMagic::Exec()` |
| `0x0048d050` | 0x258 | `CmdComboMagic::SelectGoods(MenuGroup*, MenuGroup*, bool)` |

Decompiled source: `decomp/G/CmdComboMagic.c`.
