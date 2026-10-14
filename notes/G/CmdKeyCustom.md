# CmdKeyCustom

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x1c10; ctor JP `0x00478840`
* embedded sub-objects: `+0x68 Cursor`, `+0x168 MenuTexture`, `+0x1a8 MenuTexture`, `+0x1e8 MenuTexture`, `+0x228 CmdKeyCustomPad`, `+0x111c CmdKeyCustomMenu`
* vtable stores: `+8 __vt__12CmdKeyCustom`

| JP addr | size | method |
|---|---|---|
| `0x00478840` | 0xec | `CmdKeyCustom::CmdKeyCustom()` |
| `0x004789f0` | 0x10c | `CmdKeyCustom::~CmdKeyCustom()` |
| `0x00478b00` | 0x30c | `CmdKeyCustom::GetReady()` |
| `0x00478e10` | 0x5c | `CmdKeyCustom::Run()` |
| `0x00478e70` | 0x170 | `CmdKeyCustom::SetButton(int)` |
| `0x00478fe0` | 0x11c | `CmdKeyCustom::SetAssign(int)` |
| `0x00479100` | 0x2ec | `CmdKeyCustom::Select(MenuPlace*, MenuPlace*, short)` |
| `0x004793f0` | 0x1e4 | `CmdKeyCustom::Enter()` |
| `0x004795e0` | 0x1dc | `CmdKeyCustom::Exit()` |
| `0x004797c0` | 0x3b0 | `CmdKeyCustom::SelectButton()` |
| `0x00479b70` | 0x2e0 | `CmdKeyCustom::SwapButton()` |

Decompiled source: `decomp/G/CmdKeyCustom.c`.
