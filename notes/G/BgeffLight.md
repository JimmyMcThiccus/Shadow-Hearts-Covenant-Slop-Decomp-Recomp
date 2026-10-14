# BgeffLight

* base: `PutiObject`; allocation size: 0x200; ctor JP `0x004ce240`

| JP addr | size | method |
|---|---|---|
| `0x004ce240` | 0x2dc | `BgeffLight::BgeffLight(int, void*)` |
| `0x004ce520` | 0x7c | `BgeffLight::~BgeffLight()` |
| `0x004ce5a0` | 0x80 | `BgeffLight::DeleteLight()` |
| `0x004ce620` | 0x324 | `BgeffLight::Calculate()` |
| `0x004ce950` | 0x62c | `BgeffLight::SetPacket()` |

Decompiled source: `decomp/G/BgeffLight.c`.
