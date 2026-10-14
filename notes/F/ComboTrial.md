# ComboTrial

Combo judgement-ring trial display (listed in section F's scope but it is a `JRing`-adjacent VIF1Prim; `MakePacket`/`Polling` draw ring markers) -- constructed by `JRing::Sequence`.

## Virtual table (`__vt__ComboTrial`)

| slot | function |
|---|---|
| 0x08 | `__dt__10ComboTrialFv` |
| 0x0c | `Polling__10ComboTrialFv` |
| 0x18 | `@24@__dt__10ComboTrialFv` |
| 0x1c | `@24@getPacket__10ComboTrialFv` |
| 0x28 | `@44@__dt__10ComboTrialFv` |
| 0x2c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x30 | `getPacket__10ComboTrialFv` |

## Constructed by

`Sequence__5JRingFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002c9750 | 0x44 | `getPacket__10ComboTrialFv` | `ComboTrial::getPacket()` |
| 0x002e1ac0 | 0x450 | `__ct__10ComboTrialFP5JRingis` | `ComboTrial::ComboTrial(JRing*, int, short)` |
| 0x002e1f10 | 0x114 | `__dt__10ComboTrialFv` | `ComboTrial::~ComboTrial()` |
| 0x002e2030 | 0x48 | `Destruct__10ComboTrialFv` | `ComboTrial::Destruct()` |
| 0x002e2080 | 0xa9c | `Polling__10ComboTrialFv` | `ComboTrial::Polling()` |
| 0x002e2b20 | 0x1518 | `MakePacket__10ComboTrialFv` | `ComboTrial::MakePacket()` |
| 0x002fa2c0 | 0x8 | `@24@getPacket__10ComboTrialFv` | `@24@getPacket__10ComboTrialFv` |
| 0x002fa2d0 | 0x8 | `@24@__dt__10ComboTrialFv` | `@24@__dt__10ComboTrialFv` |
| 0x002fa2e0 | 0x8 | `@44@__dt__10ComboTrialFv` | `@44@__dt__10ComboTrialFv` |

## Open questions

- belongs with section D (JRing); only decompiled here

Decompilation: `decomp/F/ComboTrial.c`
