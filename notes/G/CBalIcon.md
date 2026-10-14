# CBalIcon

* base: `DelayDeleteObject`; allocation size: 0x2c; ctor JP `0x004cc7c0`
* vtable stores: `+8 __vt__8CBalIcon`

| JP addr | size | method |
|---|---|---|
| `0x004cc7c0` | 0x54 | `CBalIcon::CBalIcon()` |
| `0x004cc840` | 0x74 | `CBalIcon::~CBalIcon()` |
| `0x004cc8c0` | 0x3c | `CBalIcon::Delete()` |
| `0x004cc900` | 0x58 | `CBalIcon::Release()` |
| `0x004cc960` | 0x2b8 | `CBalIcon::SetPat(int, int)` |
| `0x004cce50` | 0x34 | `CBalIcon::Dsp()` |
| `0x004cce90` | 0x38 | `CBalIcon::Clr()` |
| `0x004cced0` | 0x13c | `CBalIcon::SetCenter(FVector*)` |
| `0x004cd010` | 0xb24 | `CBalIcon::AddTime(float)` |

Decompiled source: `decomp/G/CBalIcon.c`.
