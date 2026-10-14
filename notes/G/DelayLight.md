# DelayLight

* base: `AnimLight`; allocation size: 0x60; ctor JP `0x004326c0`
* embedded sub-objects: `+0x40 FVector`, `+0x50 FVector`
* vtable stores: `+0x14 __vt__10DelayLight`

| JP addr | size | method |
|---|---|---|
| `0x004326c0` | 0x13c | `DelayLight::DelayLight(FVector&, FVector&)` |
| `0x00432800` | 0x74 | `DelayLight::~DelayLight()` |
| `0x00432880` | 0x84 | `DelayLight::OnCreate()` |
| `0x00432910` | 0x60 | `DelayLight::OnUpdate()` |
| `0x00432990` | 0x2c | `DelayLight::Polling()` |
| `0x004329c0` | 0x24 | `DelayLight::OnShow()` |

Decompiled source: `decomp/G/DelayLight.c`.
