# CmdProfile

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0x58c; ctor JP `0x00455310`
* embedded sub-objects: `+0x60 CmdExplain`
* vtable stores: `+8 __vt__10CmdProfile`

| JP addr | size | method |
|---|---|---|
| `0x00455310` | 0x4c | `CmdProfile::CmdProfile()` |
| `0x00455360` | 0x84 | `CmdProfile::~CmdProfile()` |
| `0x004553f0` | 0x12c | `CmdProfile::GetReady()` |
| `0x00455520` | 0x40 | `CmdProfile::SafeDelayDelete()` |
| `0x00455560` | 0x40 | `CmdProfile::Close()` |
| `0x004555a0` | 0x108 | `CmdProfile::Update(short)` |
| `0x004556b0` | 0x5c | `CmdProfile::BackGroundRun()` |
| `0x00455710` | 0x10 | `CmdProfile::Release()` |

Decompiled source: `decomp/G/CmdProfile.c`.
