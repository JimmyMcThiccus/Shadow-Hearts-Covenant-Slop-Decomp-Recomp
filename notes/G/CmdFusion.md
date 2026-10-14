# CmdFusion

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: unknown; ctor JP `0x0046ee40`
* vtable stores: `+8 __vt__9CmdFusion`

| JP addr | size | method |
|---|---|---|
| `0x0046ee40` | 0x8c | `CmdFusion::CmdFusion()` |
| `0x0046eed0` | 0x74 | `CmdFusion::~CmdFusion()` |
| `0x0046ef50` | 0x2fc | `CmdFusion::GetReady()` |
| `0x0046f250` | 0x118 | `CmdFusion::Run()` |
| `0x0046f370` | 0xb4 | `CmdFusion::SafeDelayDelete()` |
| `0x0046f430` | 0xac | `CmdFusion::Close()` |
| `0x0046f4e0` | 0x10 | `CmdFusion::Update(short)` |
| `0x0046f4f0` | 0x1d8 | `CmdFusion::ReadyScene()` |
| `0x0046f6d0` | 0xfc | `CmdFusion::UpdateList(short)` |
| `0x0046f7d0` | 0x138 | `CmdFusion::UpdateFence()` |
| `0x0046f910` | 0x7c | `CmdFusion::UpdateTitle(short)` |
| `0x0046f990` | 0xfc | `CmdFusion::UpdateParameter(short)` |
| `0x0046fa90` | 0x10c | `CmdFusion::UpdateStatus(short)` |
| `0x0046fba0` | 0x10c | `CmdFusion::UpdateSkillList(short)` |
| `0x0046fcb0` | 0x10c | `CmdFusion::UpdateCharge(short)` |
| `0x0046fdc0` | 0x184 | `CmdFusion::UpdateSoulEnergy(short)` |
| `0x0046ff50` | 0x4ec | `CmdFusion::SetFusionMonster(short)` |
| `0x00470440` | 0x160 | `CmdFusion::SetExplanation()` |
| `0x004705a0` | 0x110 | `CmdFusion::SetButtonReport(int)` |
| `0x004706b0` | 0x138 | `CmdFusion::GetNextExp(short)` |
| `0x004707f0` | 0xc4 | `CmdFusion::IsMaxLevel()` |
| `0x004708c0` | 0x184 | `CmdFusion::Enter()` |
| `0x00470a50` | 0x23c | `CmdFusion::Exit()` |
| `0x00470c90` | 0x610 | `CmdFusion::SelectList()` |
| `0x004712a0` | 0xb10 | `CmdFusion::SelectMenu()` |
| `0x00471db0` | 0x298 | `CmdFusion::SelectSkill()` |
| `0x00472050` | 0xb28 | `CmdFusion::SoulCharge()` |
| `0x00472b80` | 0x3a0 | `CmdFusion::ShiftList()` |
| `0x00472f20` | 0x1a4 | `CmdFusion::ShiftMenu()` |
| `0x004730d0` | 0x164 | `CmdFusion::ShiftExplain()` |
| `0x00473240` | 0x370 | `CmdFusion::ExecExplain()` |

Decompiled source: `decomp/G/CmdFusion.c`.
