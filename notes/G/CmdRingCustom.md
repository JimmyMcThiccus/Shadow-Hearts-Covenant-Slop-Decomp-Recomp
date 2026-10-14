# CmdRingCustom

Context: see `cmd_menu_system.md`.

* base: `CmdPCScene`; allocation size: 0x128, 0x220, 0x254; ctor JP `0x00466e30`
* embedded sub-objects: `+0x8c CmdSubMenu`
* vtable stores: `+8 __vt__13CmdRingCustom`

| JP addr | size | method |
|---|---|---|
| `0x00466e30` | 0xa8 | `CmdRingCustom::CmdRingCustom()` |
| `0x00466ee0` | 0x21c | `CmdRingCustom::~CmdRingCustom()` |
| `0x00467100` | 0x34c | `CmdRingCustom::GetReady()` |
| `0x00467470` | 0x104 | `CmdRingCustom::Run()` |
| `0x00467580` | 0x264 | `CmdRingCustom::Update(short)` |
| `0x004677f0` | 0x64 | `CmdRingCustom::DelayDelete()` |
| `0x00467860` | 0xc4 | `CmdRingCustom::UpdateMenu()` |
| `0x00467930` | 0x124 | `CmdRingCustom::UpdateTitle(short, short)` |
| `0x00467a60` | 0x1a8 | `CmdRingCustom::UpdateFence(short, short)` |
| `0x00467c10` | 0x118 | `CmdRingCustom::UpdateHitArea(short)` |
| `0x00467d30` | 0x12c | `CmdRingCustom::UpdateInfo(short, short, short, short)` |
| `0x00467e60` | 0x1c8 | `CmdRingCustom::UpdateFinal(short, short)` |
| `0x00468030` | 0xfc | `CmdRingCustom::UpdateGoods(short)` |
| `0x00468130` | 0xfc | `CmdRingCustom::UpdateCount(short)` |
| `0x00468230` | 0xfc | `CmdRingCustom::UpdateAutoRing(short)` |
| `0x00468330` | 0x130 | `CmdRingCustom::CreateContent(short)` |
| `0x00468460` | 0x190 | `CmdRingCustom::DestroyContent(short)` |
| `0x004685f0` | 0x3a4 | `CmdRingCustom::StartExplain()` |
| `0x004689a0` | 0x174 | `CmdRingCustom::SetExplain()` |
| `0x00468b20` | 0xb0 | `CmdRingCustom::SetButtonReport(short, short)` |
| `0x00468bd0` | 0x120 | `CmdRingCustom::ShiftMenu()` |
| `0x00468cf0` | 0x120 | `CmdRingCustom::StartMessage(char*)` |
| `0x00468e10` | 0x2b8 | `CmdRingCustom::Enter()` |
| `0x004690d0` | 0x480 | `CmdRingCustom::Exit()` |
| `0x00469550` | 0x560 | `CmdRingCustom::SelectMenu()` |
| `0x00469ab0` | 0x218 | `CmdRingCustom::SelectHitArea()` |
| `0x00469cd0` | 0x340 | `CmdRingCustom::SelectFinalSlot()` |
| `0x0046a010` | 0x320 | `CmdRingCustom::SelectFinalGoods()` |
| `0x0046a330` | 0x46c | `CmdRingCustom::SelectGoods()` |
| `0x0046a7a0` | 0x414 | `CmdRingCustom::SelectCount()` |
| `0x0046abc0` | 0x5f4 | `CmdRingCustom::SelectAutoRing()` |
| `0x0046b1c0` | 0x224 | `CmdRingCustom::ShiftExplain()` |
| `0x0046b3f0` | 0x488 | `CmdRingCustom::ExecExplain()` |

Decompiled source: `decomp/G/CmdRingCustom.c`.
