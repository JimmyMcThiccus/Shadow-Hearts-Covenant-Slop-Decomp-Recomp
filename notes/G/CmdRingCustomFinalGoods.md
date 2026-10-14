# CmdRingCustomFinalGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0046d520`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`
* vtable stores: `+8 __vt__23CmdRingCustomFinalGoods`

| JP addr | size | method |
|---|---|---|
| `0x0046d520` | 0x84 | `CmdRingCustomFinalGoods::CmdRingCustomFinalGoods()` |
| `0x0046d5b0` | 0xe4 | `CmdRingCustomFinalGoods::~CmdRingCustomFinalGoods()` |
| `0x0046d6a0` | 0x350 | `CmdRingCustomFinalGoods::CreateScene(CmdRingCustom*)` |
| `0x0046d9f0` | 0x374 | `CmdRingCustomFinalGoods::UpdateScene(CmdRingCustom*, short)` |
| `0x0046dd70` | 0x18c | `CmdRingCustomFinalGoods::Select(CmdRingCustom*, MenuGroup*, MenuGroup*, short)` |
| `0x0046df00` | 0x170 | `CmdRingCustomFinalGoods::SetMessage(CmdRingCustom*, short, CmdGoodsIcon*)` |
| `0x0046e070` | 0x8 | `CmdRingCustomFinalGoods::~CmdRingCustomFinalGoods()` |
| `0x0046e080` | 0x8 | `CmdRingCustomFinalGoods::~CmdRingCustomFinalGoods()` |

Decompiled source: `decomp/G/CmdRingCustomFinalGoods.c`.
