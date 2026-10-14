# CmdWolfBout

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0x90; ctor JP `0x00483620`
* vtable stores: `+8 __vt__11CmdWolfBout`

| JP addr | size | method |
|---|---|---|
| `0x00483620` | 0x54 | `CmdWolfBout::CmdWolfBout()` |
| `0x00483680` | 0x74 | `CmdWolfBout::~CmdWolfBout()` |
| `0x00483700` | 0x270 | `CmdWolfBout::GetReady()` |
| `0x00483970` | 0x68 | `CmdWolfBout::Run()` |
| `0x004839e0` | 0x74 | `CmdWolfBout::SafeDelayDelete()` |
| `0x00483a60` | 0x4c | `CmdWolfBout::Close()` |
| `0x00483ab0` | 0x244 | `CmdWolfBout::ReadyScene()` |
| `0x00483d00` | 0x104 | `CmdWolfBout::UpdateStamp(short, short)` |
| `0x00483e10` | 0xfc | `CmdWolfBout::UpdateProfile(short)` |
| `0x00483f10` | 0x284 | `CmdWolfBout::SetWolf(short)` |
| `0x004841a0` | 0x138 | `CmdWolfBout::SetExplanation()` |
| `0x004842e0` | 0x9c | `CmdWolfBout::SetButtonReport(int)` |
| `0x00484380` | 0xc0 | `CmdWolfBout::Enter()` |
| `0x00484440` | 0xec | `CmdWolfBout::Exit()` |
| `0x00484530` | 0x5c8 | `CmdWolfBout::SelectStamp()` |
| `0x00484b00` | 0x134 | `CmdWolfBout::ShiftExplain()` |
| `0x00484c40` | 0x470 | `CmdWolfBout::ExecExplain()` |
| `0x004850b0` | 0x194 | `CmdWolfBout::DisplayMessage()` |

Decompiled source: `decomp/G/CmdWolfBout.c`.
