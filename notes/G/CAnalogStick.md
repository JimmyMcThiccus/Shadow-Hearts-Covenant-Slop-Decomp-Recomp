# CAnalogStick

Copy of a **main-executable** class statically linked into FIELD.BIN (duplicated code of another section's class); documented by the owning section. Listed here for address mapping only.

* base: `-`; allocation size: unknown; ctor JP `0x004a6150`

| JP addr | size | method |
|---|---|---|
| `0x004a6110` | 0x1c | `CAnalogStick::GetDegree` |
| `0x004a6130` | 0x1c | `CAnalogStick::GetGauge` |
| `0x004a6150` | 0x8c | `CAnalogStick::CAnalogStick(const CAnalogStick&)` |

Decompiled source: `decomp/G/_OverlayCopies_CAnalogStick.c`.
