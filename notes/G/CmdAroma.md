# CmdAroma

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0x520; ctor JP `0x0045f4e0`
* embedded sub-objects: `+0x70 CmdAromaBaseOil`, `+0x3f0 CmdAromaBlend`
* vtable stores: `+8 __vt__8CmdAroma`

| JP addr | size | method |
|---|---|---|
| `0x0045f4e0` | 0x5c | `CmdAroma::CmdAroma()` |
| `0x0045f540` | 0x9c | `CmdAroma::~CmdAroma()` |
| `0x0045f5e0` | 0x1ac | `CmdAroma::GetReady()` |
| `0x0045f790` | 0x68 | `CmdAroma::Run()` |
| `0x0045f800` | 0x50 | `CmdAroma::SafeDelayDelete()` |
| `0x0045f850` | 0x48 | `CmdAroma::Close()` |
| `0x0045f8a0` | 0x178 | `CmdAroma::ReadyScene()` |
| `0x0045fa20` | 0x12c | `CmdAroma::SetExplanation()` |
| `0x0045fb50` | 0x424 | `CmdAroma::SelectBaseOil()` |
| `0x0045ff80` | 0x220 | `CmdAroma::SelectBlend()` |
| `0x004601a0` | 0x168 | `CmdAroma::ShiftExplain()` |
| `0x00460310` | 0x260 | `CmdAroma::ExecExplain()` |
| `0x00460570` | 0x10 | `CmdAroma::Release()` |

Decompiled source: `decomp/G/CmdAroma.c`.
