# MgcInvkParticle

Magic invocation particles. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0051fbf0 | 00545350 | 0x380 | `MgcInvkParticle::__ct(int, int, FVector, float)` |
| 0051ff70 | 005456d0 | 0x160 | `MgcInvkParticle::__dt()` |
| 005200d0 | 00545830 | 0xd0 | `MgcInvkParticle::Destruct()` |
| 005201a0 | 00545900 | 0x480 | `MgcInvkParticle::Polling()` |
| 00520620 | 00545d80 | 0x1370 | `MgcInvkParticle::MakePacket()` |
| 0054ae90 | 0057db30 | 0x20 | `MgcInvkParticle::EndSet()` |
| 0054b760 |  | 0x10 | `@24@__dt__15MgcInvkParticleFv` |
| 0054b770 |  | 0x10 | `@44@__dt__15MgcInvkParticleFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__15MgcInvkParticleFv |
| +0x18 | int/u32 | 2 | __dt__15MgcInvkParticleFv |
| +0x1c | int/u32 | 2 | __dt__15MgcInvkParticleFv |
| +0x28 | u32 | 2 | __dt__15MgcInvkParticleFv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__15MgcInvkParticleFv |
| +0x40 | byte | 9 | Destruct, MakePacket, Polling |
| +0x48 | u32 | 2 | Destruct, Polling |
| +0x50 | u32 | 1 | Polling |
| +0x5c | int/u32 | 2 | EndSet, Polling |
| +0x60 | float | 5 | MakePacket, Polling |
| +0x70 | float | 2 | MakePacket |
| +0x74 | float | 2 | MakePacket |
| +0x78 | float | 2 | MakePacket |
| +0x680 | float | 1 | Polling |
